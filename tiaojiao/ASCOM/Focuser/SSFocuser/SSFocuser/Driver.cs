//tabs=4
// --------------------------------------------------------------------------------
// TODO fill in this information for your driver, then remove this line!
//
// ASCOM Focuser driver for SSFocuser
//
// Description:	Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam 
//				nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam 
//				erat, sed diam voluptua. At vero eos et accusam et justo duo 
//				dolores et ea rebum. Stet clita kasd gubergren, no sea takimata 
//				sanctus est Lorem ipsum dolor sit amet.
//
// Implements:	ASCOM Focuser interface version: <To be completed by driver developer>
// Author:		(XXX) Your N. Here <your@email.here>
//
// Edit Log:
//
// Date			Who	Vers	Description
// -----------	---	-----	-------------------------------------------------------
// dd-mmm-yyyy	XXX	6.0.0	Initial edit, created from ASCOM driver template
// --------------------------------------------------------------------------------
//


// This is used to define code in the template that is specific to one class implementation
// unused code canbe deleted and this definition removed.
#define Focuser

using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Text;
using System.Runtime.InteropServices;

using ASCOM;
using ASCOM.Astrometry;
using ASCOM.Astrometry.AstroUtils;
using ASCOM.Utilities;
using ASCOM.DeviceInterface;
using System.Globalization;
using System.Collections;

//引用
using System.IO;
using System.IO.Ports;
//using System.Net;
//using System.Net.Sockets;
using System.Timers;
using System.Threading;
using System.Windows.Forms;
using System.Text.RegularExpressions;//正则表达
using System.Data;

namespace ASCOM.SSFocuser
{
    //
    // Your driver's DeviceID is ASCOM.SSFocuser.Focuser
    //
    // The Guid attribute sets the CLSID for ASCOM.SSFocuser.Focuser
    // The ClassInterface/None addribute prevents an empty interface called
    // _SSFocuser from being created and used as the [default] interface
    //
    // TODO Replace the not implemented exceptions with code to implement the function or
    // throw the appropriate ASCOM exception.
    //

    /// <summary>
    /// ASCOM Focuser Driver for SSFocuser.
    /// </summary>
    [Guid("da3205ae-dd6e-4188-9fea-7bed542cba3d")]
    [ClassInterface(ClassInterfaceType.None)]
    public class Focuser : IFocuserV2
    {
        /// <summary>
        /// ASCOM DeviceID (COM ProgID) for this driver.
        /// The DeviceID is used by ASCOM applications to load the driver at runtime.
        /// </summary>
        internal static string driverID = "ASCOM.SSFocuser.Focuser";
        // TODO Change the descriptive string for your driver then remove this line
        /// <summary>
        /// Driver description that displays in the ASCOM Chooser.
        /// </summary>
        //private static string driverDescription = "ASCOM Focuser Driver for SSFocuser.";

        //private static string driverDescription = "SS Focuser";
        private static string driverDescription = "SS Focuser";

        internal static string comPortProfileName = "COM Port"; // Constants used for Profile persistence
        internal static string comPortDefault = "COM1";
        internal static string traceStateProfileName = "Trace Level";
        internal static string traceStateDefault = "false";

        internal static string comPort; // Variables to hold the currrent device configuration
        internal static int baudRate; // graycode
        

        /// <summary>
        /// Private variable to hold the connected state
        /// </summary>
        //private bool connectedState;
        public static bool connectedState;//供设置对话框访问graycode

        /// <summary>
        /// Private variable to hold an ASCOM Utilities object
        /// </summary>
        private Util utilities;

        /// <summary>
        /// Private variable to hold an ASCOM AstroUtilities object to provide the Range method
        /// </summary>
        private AstroUtils astroUtilities;

        /// <summary>
        /// Variable to hold the trace logger object (creates a diagnostic log file with information that you specify)
        /// </summary>
        internal static TraceLogger tl;


        //////////////graycode///////////
        private System.Timers.Timer Timer1;
        private SerialPort MySerialPort;
        
        private string RecvBuf;
        private int BChar = -1;
        private int EChar = -1;
        public char m_rCmd;
        //Device info
        public static bool m_DeviceOk;
        public static string m_Device, m_Vendor,m_Website,m_Email,m_Tel;
        //Low power mode
        public static bool m_LowPower;
        //Focuser
        public static int m_MaxStep, m_MaxIncrement;
        public static float m_StepSize;
        //Temperature
        //public static float m_TempCompRatio;
        //public static float m_TempCompDegs;
        //Motor
        public static bool m_MotorReverse;
        public static byte m_MotorMicrostep;
        public static byte m_MotorSpeed;
        //Other
        public static bool m_IsMoving, m_TempCompAvailable, m_TempComp;
        public static int m_CurrentPosition;//, m_LastPosition;
        public static double m_StartTemperature, m_CurrentTemperature;

        public static bool UseToolbox = false;
        public static bool ToolboxOpened = false;
        public static bool InitFocuser = false;
        public static bool FocuserInitialized = false;
        public static bool SavePosition = false;
        private Toolbox MyToolbox;
        
        internal static byte TimeCount = 0;
        internal static byte TimeOut = 60;//60秒超时
        //public static byte ErrorInfo = 0;
        //public static byte m_Initialized;//初始配置状态 0 - 未初始化 1 - 已初始化 2 - 开机状态
        private String ErrorInfo;

        /// <summary>
        /// Initializes a new instance of the <see cref="SSFocuser"/> class.
        /// Must be public for COM registration.
        /// </summary>
        public Focuser()
        {
            tl = new TraceLogger("", "SSFocuser");
            ReadProfile(); // Read device configuration from the ASCOM Profile store

            tl.LogMessage("Focuser", "Starting initialisation");

            connectedState = false; // Initialise connected to false
            utilities = new Util(); //Initialise util object
            astroUtilities = new AstroUtils(); // Initialise astro utilities object
            //TODO: Implement your additional construction here

            tl.LogMessage("Focuser", "Completed initialisation");
            //这里是setupdialog后才初始化
            MySerialPort = new SerialPort();
            //buffer = new byte[1024];
            RecvBuf = "";
            m_rCmd = 'U';

            MyToolbox = new Toolbox(this);

            m_IsMoving = false;
            m_TempComp = false;
            m_TempCompAvailable = true;

            
        }
        //
        // PUBLIC COM INTERFACE IFocuserV2 IMPLEMENTATION
        //

        #region Common properties and methods.

        /// <summary>
        /// Displays the Setup Dialog form.
        /// If the user clicks the OK button to dismiss the form, then
        /// the new settings are saved, otherwise the old values are reloaded.
        /// THIS IS THE ONLY PLACE WHERE SHOWING USER INTERFACE IS ALLOWED!
        /// </summary>
        public void SetupDialog()
        {
            // consider only showing the setup dialog if not connected
            // or call a different dialog if connected
            if (IsConnected)
                System.Windows.Forms.MessageBox.Show("Already connected, just press OK");

            using (SetupDialogForm F = new SetupDialogForm())
            {
                var result = F.ShowDialog();
                if (result == System.Windows.Forms.DialogResult.OK)
                {
                    WriteProfile(); // Persist device configuration values to the ASCOM Profile store
                }
            }
        }

        public ArrayList SupportedActions
        {
            get
            {
                tl.LogMessage("SupportedActions Get", "Returning empty arraylist");
                return new ArrayList();
            }
        }

        public string Action(string actionName, string actionParameters)
        {
            LogMessage("", "Action {0}, parameters {1} not implemented", actionName, actionParameters);
            throw new ASCOM.ActionNotImplementedException("Action " + actionName + " is not implemented by this driver");
        }

        public void CommandBlind(string command, bool raw)
        {
            CheckConnected("CommandBlind");
            // Call CommandString and return as soon as it finishes
            this.CommandString(command, raw);
            // or
            throw new ASCOM.MethodNotImplementedException("CommandBlind");
            // DO NOT have both these sections!  One or the other
        }

        public bool CommandBool(string command, bool raw)
        {
            CheckConnected("CommandBool");
            string ret = CommandString(command, raw);
            // TODO decode the return string and return true or false
            // or
            throw new ASCOM.MethodNotImplementedException("CommandBool");
            // DO NOT have both these sections!  One or the other
        }

        public string CommandString(string command, bool raw)
        {
            CheckConnected("CommandString");
            // it's a good idea to put all the low level communication with the device here,
            // then all communication calls this function
            // you need something to ensure that only one command is in progress at a time

            throw new ASCOM.MethodNotImplementedException("CommandString");
        }

        public void Dispose()
        {
            // Clean up the tracelogger and util objects
            tl.Enabled = false;
            tl.Dispose();
            tl = null;
            utilities.Dispose();
            utilities = null;
            astroUtilities.Dispose();
            astroUtilities = null;
        }

        public bool Connected
        {
            get
            {
                LogMessage("Connected", "Get {0}", IsConnected);
                return IsConnected;
            }
            set
            {
                tl.LogMessage("Connected", "Set {0}", value);
                if (value == IsConnected)
                    return;

                if (value)
                {
                    //
                    //LogMessage("Connected Set", "Connecting to port {0}", comPort);
                    // TODO connect to the device
                    UartInitial();
                    if (m_DeviceOk)
                    {
                        connectedState = true;
                        if (UseToolbox)//设置了需要打开
                            MyToolbox.Show();
                    }
                    else
                    {
                        UartUninitial();
                        connectedState = false;
                        MessageBox.Show("No device detected, please check connection!");
                    }
                }
                else
                {
                    //LogMessage("Connected Set", "Disconnecting from port {0}", comPort);
                    // TODO disconnect from the device
                    //if (UseToolbox)
                    if(ToolboxOpened)//打开状态则关闭
                        MyToolbox.Close();
                    UartUninitial();
                    connectedState = false;
                }
            }
        }

        public string Description
        {
            // TODO customise this device description
            get
            {
                tl.LogMessage("Description Get", driverDescription);
                return driverDescription;
            }
        }

        public string DriverInfo
        {
            get
            {
                Version version = System.Reflection.Assembly.GetExecutingAssembly().GetName().Version;
                // TODO customise this driver description
                string driverInfo = "Information about the driver itself. Version: " + String.Format(CultureInfo.InvariantCulture, "{0}.{1}", version.Major, version.Minor);
                tl.LogMessage("DriverInfo Get", driverInfo);
                return driverInfo;
            }
        }

        public string DriverVersion
        {
            get
            {
                Version version = System.Reflection.Assembly.GetExecutingAssembly().GetName().Version;
                string driverVersion = String.Format(CultureInfo.InvariantCulture, "{0}.{1}", version.Major, version.Minor);
                tl.LogMessage("DriverVersion Get", driverVersion);
                return driverVersion;
            }
        }

        public short InterfaceVersion
        {
            // set by the driver wizard
            get
            {
                LogMessage("InterfaceVersion Get", "2");
                return Convert.ToInt16("2");
            }
        }

        public string Name
        {
            get
            {
                string name = "Short driver name - please customise";
                tl.LogMessage("Name Get", name);
                return name;
            }
        }

        #endregion

        #region IFocuser Implementation

        //private int focuserPosition = 0; // Class level variable to hold the current focuser position
        //private const int focuserSteps = 10000;

        public bool Absolute
        {
            get
            {
                tl.LogMessage("Absolute Get", true.ToString());
                return true; // This is an absolute focuser
            }
        }

        public void Halt()
        {
            //tl.LogMessage("Halt", "Not implemented");
            //throw new ASCOM.MethodNotImplementedException("Halt");
            tl.LogMessage("Halt", "Halt");
            StopMove();
            //    m_IsMoving = false;
            //Thread.Sleep(500);
        }

        public bool IsMoving
        {
            get
            {
                //tl.LogMessage("IsMoving Get", false.ToString());
                //return false; // This focuser always moves instantaneously so no need for IsMoving ever to be True
                tl.LogMessage("IsMoving Get", m_IsMoving.ToString());
                if (m_IsMoving)//Moving期间不查询Position
                {
                    if (TimeCount < TimeOut)
                        TimeCount++;
                }
                if (!ToolboxOpened)//工具箱打开时这里不查询
                    GetMovState();
                return m_IsMoving;
            }
        }

        public bool Link
        {
            get
            {
                tl.LogMessage("Link Get", this.Connected.ToString());
                return this.Connected; // Direct function to the connected method, the Link method is just here for backwards compatibility
            }
            set
            {
                tl.LogMessage("Link Set", value.ToString());
                this.Connected = value; // Direct function to the connected method, the Link method is just here for backwards compatibility
            }
        }

        public int MaxIncrement
        {
            get
            {
                //tl.LogMessage("MaxIncrement Get", focuserSteps.ToString());
                //return focuserSteps; // Maximum change in one move
                tl.LogMessage("MaxIncrement Get", m_MaxIncrement.ToString());
                return m_MaxIncrement;
            }
        }

        public int MaxStep
        {
            get
            {
                //tl.LogMessage("MaxStep Get", focuserSteps.ToString());
                //return focuserSteps; // Maximum extent of the focuser, so position range is 0 to 10,000
                tl.LogMessage("MaxStep Get", m_MaxStep.ToString());
                return m_MaxStep;
            }
        }

        public void Move(int Position)//
        {
            tl.LogMessage("Move", Position.ToString());
            //focuserPosition = Position; // Set the focuser position
            if (!InitFocuser)//调焦器存储模式下可以直接转动
            {
                if (FocuserInitialized)//已初始化则去初始化
                {
                    SetFocuserInitState(false);//设置为本地存储模式 
                    //GetFocuserInitState();
                }
                if (StartMove(Position))
                    m_IsMoving = true;//避免运动状态变化立即发送两次Move命令导致齿轮回差无法执行
               
            }
            else//电脑存储模式下未初始化则不能转动
            {
                if (!FocuserInitialized)//未初始化则先初始化
                {
                    m_CurrentPosition = ReadPosition();//从本地电脑读取上次存储位置
                    //m_LastPosition = m_CurrentPosition;
                    DefinePosition(m_CurrentPosition);//校准调焦器位置
                    SetFocuserInitState(true);//设置为本地存储模式 
                    //GetFocuserInitState();
                }
                if (StartMove(Position))
                    m_IsMoving = true;//避免运动状态变化立即发送两次Move命令导致齿轮回差无法执行
            }   
        }

        public int Position//Moving期间不发Position，只查询IsMoving,所以如果采用同步模式Toolbox无法实时显示步数
        {
            get
            {
                //return focuserPosition; // Return the focuser position
                if (TimeCount < TimeOut)//Moving期间在IsMoving函数中计数
                    TimeCount++;
                if (!ToolboxOpened)
                    GetPosition();
                return m_CurrentPosition; // Return the focuser position
            }
        }

        public double StepSize
        {
            get
            {
                //tl.LogMessage("StepSize Get", "Not implemented");
                //throw new ASCOM.PropertyNotImplementedException("StepSize", false);
                tl.LogMessage("StepSize Get", m_StepSize.ToString());
                return m_StepSize;
            }
        }

        public bool TempComp
        {
            get
            {
                //tl.LogMessage("TempComp Get", false.ToString());
                //return false;
                tl.LogMessage("TempComp Get", m_TempComp.ToString());
                return m_TempComp; 
            }
            set
            {
                //tl.LogMessage("TempComp Set", "Not implemented");
                //throw new ASCOM.PropertyNotImplementedException("TempComp", false);
                tl.LogMessage("TempComp Set", value.ToString ());
                m_TempComp = value;
            }
        }

        public bool TempCompAvailable
        {
            get
            {
                //tl.LogMessage("TempCompAvailable Get", false.ToString());
                //return false; // Temperature compensation is not available in this driver
                tl.LogMessage("TempCompAvailable Get", m_TempCompAvailable.ToString());
                return m_TempCompAvailable;
                //return true;
            }
        }

        public double Temperature
        {
            get
            {
                //tl.LogMessage("Temperature Get", "Not implemented");
                //throw new ASCOM.PropertyNotImplementedException("Temperature", false);
                tl.LogMessage("Temperature Get", m_CurrentTemperature.ToString ());
                /*
               if (m_TempComp)//温度补偿
               {
                   TempCompensation(m_TempCompRatio, m_TempCompDegs);
               }
               else
               {
                   m_StartTemperature = m_CurrentTemperature;
               }
               */
                if (!ToolboxOpened)
                    GetTemperature();
                return m_CurrentTemperature;
            }
        }

        #endregion

        #region Private properties and methods
        // here are some useful properties and methods that can be used as required
        // to help with driver development

        #region ASCOM Registration

        // Register or unregister driver for ASCOM. This is harmless if already
        // registered or unregistered. 
        //
        /// <summary>
        /// Register or unregister the driver with the ASCOM Platform.
        /// This is harmless if the driver is already registered/unregistered.
        /// </summary>
        /// <param name="bRegister">If <c>true</c>, registers the driver, otherwise unregisters it.</param>
        private static void RegUnregASCOM(bool bRegister)
        {
            using (var P = new ASCOM.Utilities.Profile())
            {
                P.DeviceType = "Focuser";
                if (bRegister)
                {
                    P.Register(driverID, driverDescription);
                }
                else
                {
                    P.Unregister(driverID);
                }
            }
        }

        /// <summary>
        /// This function registers the driver with the ASCOM Chooser and
        /// is called automatically whenever this class is registered for COM Interop.
        /// </summary>
        /// <param name="t">Type of the class being registered, not used.</param>
        /// <remarks>
        /// This method typically runs in two distinct situations:
        /// <list type="numbered">
        /// <item>
        /// In Visual Studio, when the project is successfully built.
        /// For this to work correctly, the option <c>Register for COM Interop</c>
        /// must be enabled in the project settings.
        /// </item>
        /// <item>During setup, when the installer registers the assembly for COM Interop.</item>
        /// </list>
        /// This technique should mean that it is never necessary to manually register a driver with ASCOM.
        /// </remarks>
        [ComRegisterFunction]
        public static void RegisterASCOM(Type t)
        {
            RegUnregASCOM(true);
        }

        /// <summary>
        /// This function unregisters the driver from the ASCOM Chooser and
        /// is called automatically whenever this class is unregistered from COM Interop.
        /// </summary>
        /// <param name="t">Type of the class being registered, not used.</param>
        /// <remarks>
        /// This method typically runs in two distinct situations:
        /// <list type="numbered">
        /// <item>
        /// In Visual Studio, when the project is cleaned or prior to rebuilding.
        /// For this to work correctly, the option <c>Register for COM Interop</c>
        /// must be enabled in the project settings.
        /// </item>
        /// <item>During uninstall, when the installer unregisters the assembly from COM Interop.</item>
        /// </list>
        /// This technique should mean that it is never necessary to manually unregister a driver from ASCOM.
        /// </remarks>
        [ComUnregisterFunction]
        public static void UnregisterASCOM(Type t)
        {
            RegUnregASCOM(false);
        }

        #endregion

        /// <summary>
        /// Returns true if there is a valid connection to the driver hardware
        /// </summary>
        private bool IsConnected
        {
            get
            {
                // TODO check that the driver hardware connection exists and is connected to the hardware
                return connectedState;
            }
        }

        /// <summary>
        /// Use this function to throw an exception if we aren't connected to the hardware
        /// </summary>
        /// <param name="message"></param>
        private void CheckConnected(string message)
        {
            if (!IsConnected)
            {
                throw new ASCOM.NotConnectedException(message);
            }
        }

        /// <summary>
        /// Read the device configuration from the ASCOM Profile store
        /// </summary>
        internal void ReadProfile()
        {
            using (Profile driverProfile = new Profile())
            {
                driverProfile.DeviceType = "Focuser";
                //tl.Enabled = Convert.ToBoolean(driverProfile.GetValue(driverID, traceStateProfileName, string.Empty, traceStateDefault));
                comPort = driverProfile.GetValue(driverID, comPortProfileName, string.Empty, comPortDefault);
                baudRate = Convert.ToInt32(driverProfile.GetValue(driverID, "BaudRate", string.Empty, "9600"));

                //m_Device = driverProfile.GetValue(driverID, "Device", string.Empty, "SSFocuser");
                //m_Website = driverProfile.GetValue(driverID, "Website", string.Empty, "www.graycode.cn");

                m_LowPower = Convert.ToBoolean(driverProfile.GetValue(driverID, "LowPower", string.Empty, true.ToString()));

                m_MotorReverse = Convert.ToBoolean(driverProfile.GetValue(driverID, "MotorReverse", string.Empty, false.ToString()));
                m_MotorMicrostep = Convert.ToByte(driverProfile.GetValue(driverID, "MotorMicrostep", string.Empty, "8"));
                m_MotorSpeed = Convert.ToByte(driverProfile.GetValue(driverID, "MotorSpeed", string.Empty, "4"));

                //m_TempCompRatio = Convert.ToSingle(driverProfile.GetValue(driverID, "TempCompRatio", string.Empty, "0.0"));
                //m_TempCompDegs = Convert.ToSingle(driverProfile.GetValue(driverID, "TempCompDegs", string.Empty, "10.0"));

                m_MaxStep = Convert.ToInt32(driverProfile.GetValue(driverID, "MaxStep", string.Empty, "50000"));
                m_StepSize = Convert.ToSingle(driverProfile.GetValue(driverID, "StepSize", string.Empty, "10.0"));
                m_MaxIncrement = Convert.ToInt32(driverProfile.GetValue(driverID, "MaxIncrement", string.Empty, "10000"));

                UseToolbox = Convert.ToInt32(driverProfile.GetValue(driverID, "UseToolbox", string.Empty, "0")) == 1 ? true : false;
                InitFocuser = Convert.ToInt32(driverProfile.GetValue(driverID, "InitFocuser", string.Empty, "0")) == 1 ? true : false;               
            }
        }

        /// <summary>
        /// Write the device configuration to the  ASCOM  Profile store
        /// </summary>
        internal void WriteProfile()
        {
            using (Profile driverProfile = new Profile())
            {
                driverProfile.DeviceType = "Focuser";
                //driverProfile.WriteValue(driverID, traceStateProfileName, tl.Enabled.ToString());
                //driverProfile.WriteValue(driverID, comPortProfileName, comPort.ToString());

                driverProfile.WriteValue(driverID, comPortProfileName, comPort.ToString());
                driverProfile.WriteValue(driverID, "BaudRate", baudRate.ToString());

                //driverProfile.WriteValue(driverID, "Device", m_Device);
                //driverProfile.WriteValue(driverID, "Website", m_Website);

                driverProfile.WriteValue(driverID, "LowPower", m_LowPower.ToString());

                driverProfile.WriteValue(driverID, "MotorReverse", m_MotorReverse.ToString());
                driverProfile.WriteValue(driverID, "MotorMicrostep", m_MotorMicrostep.ToString());
                driverProfile.WriteValue(driverID, "MotorSpeed", m_MotorSpeed.ToString());

                //driverProfile.WriteValue(driverID, "TempCompRatio", m_TempCompRatio.ToString());
                //driverProfile.WriteValue(driverID, "TempCompDegs", m_TempCompDegs.ToString());

                driverProfile.WriteValue(driverID, "MaxStep", m_MaxStep.ToString());
                driverProfile.WriteValue(driverID, "StepSize", m_StepSize.ToString());
                driverProfile.WriteValue(driverID, "MaxIncrement", m_MaxIncrement.ToString());

                driverProfile.WriteValue(driverID, "UseToolbox", UseToolbox == true ? "1" : "0");
                driverProfile.WriteValue(driverID, "InitFocuser", InitFocuser==true?"1":"0");                
            }
        }
        int ReadPosition()
        {
            using (Profile driverProfile = new Profile())
            {
                driverProfile.DeviceType = "Focuser";
                return Convert.ToInt32(driverProfile.GetValue(driverID, "StorePosition", string.Empty, "0"));
            }
        }
        void WritePosition(int mpos)
        {
            using (Profile driverProfile = new Profile())
            {
                driverProfile.DeviceType = "Focuser";
                driverProfile.WriteValue(driverID, "StorePosition", mpos.ToString());
            }
        }
        /// <summary>
        /// Log helper function that takes formatted strings and arguments
        /// </summary>
        /// <param name="identifier"></param>
        /// <param name="message"></param>
        /// <param name="args"></param>
        internal static void LogMessage(string identifier, string message, params object[] args)
        {
            var msg = string.Format(message, args);
            tl.LogMessage(identifier, msg);
        }
        #endregion

        #region User Properties and methods
        //////////////graycode//////////////

        public void UartInitial()
        {
            try
            {
                if (MySerialPort.IsOpen)
                    MySerialPort.Close();
                MySerialPort.PortName = comPort;
                MySerialPort.DataBits = 8;
                MySerialPort.Parity = Parity.None;
                MySerialPort.StopBits = StopBits.One;
                MySerialPort.BaudRate = baudRate;
                MySerialPort.NewLine = "\r\n";
                MySerialPort.DataReceived += new SerialDataReceivedEventHandler(UartRecvMsg);
                MySerialPort.Open();
                if (!m_DeviceOk)//查询版本信息
                {
                    byte i = 0, j = 0;
                    for (i = 0; i < 3; i++)
                    {
                        UartSendMsg(":F?#");
                        //Thread.Sleep(300);
                        for (j = 0; j < 60; j++)//每个5mS查一次，最长可执行60次（等待300mS）
                        {
                            if (m_DeviceOk)
                                break;
                            Thread.Sleep(5);
                        }
                        if (m_DeviceOk)
                            break;
                    }
                }
                if (m_DeviceOk)//查询是否初始化
                {
                    GetFocuserInitState();
                }
            }
            //catch (IOException ex)
            catch (Exception ex)
            {
                //MessageBox.Show(ex.ToString());
                ErrorInfo = ex.ToString();
            }
        }
        public void UartUninitial()
        {
            try
            {
                if (MySerialPort.IsOpen)
                {
                    MySerialPort.BreakState = true;
                    MySerialPort.Close();
                }
            }
            //catch (IOException ex)
            catch (Exception ex)
            {
                //MessageBox.Show(ex.ToString());
                ErrorInfo = ex.ToString();
            }
        }
        //发送命令，带返回确认
        public bool SendMsg(string command)
        {
            bool ret = false;
            byte i = 0, j = 0;
            char m_sCmd = Convert.ToChar(command.Substring(2, 1));
            m_rCmd = 'U';
            for (i = 0; i < 3; i++)
            {
                UartSendMsg(command);
                for (j = 0; j < 60; j++)//每个5mS查一次，最长可执行60次（等待300mS）
                {
                    if (m_rCmd == m_sCmd)//接收命令正确则退出本循环
                    {
                        ret = true;
                        break;
                    }
                    Thread.Sleep(5);
                }
                if (m_rCmd == m_sCmd)//接收命令正确则退出不在发送命令
                {
                    break;
                }
            }
            return ret;
        }
        public void UartSendMsg(string Msg)
        {
            try
            {
                if (!MySerialPort.IsOpen)
                    MySerialPort.Open();
                MySerialPort.Write(Msg);
            }
            catch (IOException ex)//不能弹出窗口，否则串口线拔出后一直提示无法关闭控制软件
            {
                ErrorInfo = ex.ToString();
                //if (!m_ConnectError)//只弹出一次
                //{
                    //MessageBox.Show(ex.ToString());
                //}
            }
        }
        
        public void UartRecvMsg(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            try
            {
                RecvBuf = RecvBuf+MySerialPort.ReadExisting();
                for (int i = 0; i < RecvBuf.Length; i++)//可能有多条命令
                {
                    if (RecvBuf[i] == ':')//找到协议头
                        BChar = i;
                    if (RecvBuf[i] == '#')//找到协议尾
                        EChar = i;
                    if ((BChar >= 0) && (EChar > BChar))//找到一条完整命令
                    {
                        //m_rCmd = RecvBuf[BChar + 1];//当前返回命令标志位
                        //string data = RecvBuf.Substring(BChar + 2, EChar - BChar - 2);
                        //处理数据
                        ProcessData(RecvBuf.Substring(BChar, EChar - BChar + 1));
                        BChar = -1;
                        EChar = -1;
                        TimeCount = 0;//超时计数复位
                    }
                }
                if (BChar < 0)//找不到协议头
                    RecvBuf = "";
                else
                {
                    RecvBuf = RecvBuf.Substring(BChar, RecvBuf.Length - BChar);
                }
                if (RecvBuf.Length >= 256)//避免有一个冒号的非命令字节堵塞
                    RecvBuf = "";
                //MessageBox.Show(RecvBuf.ToString());
                BChar = -1;
                EChar = -1;
            }
            catch (Exception ex)
            {
                //MessageBox.Show(ex.ToString());
                ErrorInfo = ex.ToString();
            }
        }
       
        public void UartRecvMsg2(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            RecvBuf = RecvBuf + MySerialPort.ReadExisting();
            //判断有效性，没法判断两个冒号：连#号的情况如:123:222#，需改进
            string re1 = "(:)";	// Any Single Character 1
            string re2 = ".*?";	// Non-greedy match on filler
            string re3 = "(#)";	// Any Single Character 2
            string Pattern = re1 + re2 + re3;
            MatchCollection Matches = Regex.Matches(
                RecvBuf,
                Pattern,
                RegexOptions.ExplicitCapture | RegexOptions.IgnoreCase    //提高检索效率  
                );
            if (Matches.Count > 0)
            {
                foreach (Match NextMatch in Matches)
                {
                    //MessageBox.Show(NextMatch.Value);
                    char cmd = Convert.ToChar(NextMatch.Value.Substring(1, 1));
                    string data = NextMatch.Value.Substring(0, NextMatch.Value.Length);
                    //MessageBox.Show(data);
                    ProcessData(data);
                    TimeCount = 0;//超时计数复位
                }
                RecvBuf = "";//命令处理完后清空
            }
            else//无匹配时判断是否含有冒号，如含冒号可能传输未完成
            {
                if (RecvBuf.IndexOf(":") < 0)//如果不含：号清空
                    RecvBuf = "";
                //MessageBox.Show(RecvBuffer);
            }
        }
        /*
        private int RecvCnt=0;
        private char RecvChar,LastChar;
        private char[] RecvBuf3;
        private bool HeadCmd = false;
        public void UartRecvMsg3(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            try
            {
                int BtoR = MySerialPort.BytesToRead;
                char[] TempBuf = new char[BtoR];
                int TempCnt = MySerialPort.Read(TempBuf,0,BtoR);
                for (int i = 0; i < TempCnt; i++)
                {
                    RecvCnt++;
                    RecvChar = TempBuf[i];
                    if (RecvChar == ':')//找到协议头则RecvCnt = 1
                    {
                        RecvBuf3[0] = ':';
                        RecvCnt = 1;
                        HeadCmd = true;
                    }
                    if (!HeadCmd)//协议头不正确则重新查找，不再往上计数，最多只能到1
                        RecvCnt = 0;
                    if (RecvCnt > 1)
                        RecvBuf3[RecvCnt - 1] = RecvChar;
                    if (RecvChar == '#')
                    {
                        if (HeadCmd)
                        {
                            m_rCmd = RecvBuf[1];//当前返回命令标志位
                            string data = new string(RecvBuf3, 0, RecvCnt);
                            //MessageBox.Show(data);
                            ProcessData(data);
                        }
                        RecvCnt = 0;
                        HeadCmd = false;
                        TimeCount = 0;//超时计数复位
                    }
                    LastChar = RecvChar;
                }
            }
            catch (Exception ex)
            {
                //MessageBox.Show(ex.ToString());
            }
        }
        */
        private void ProcessData(string data)
        {
            m_rCmd = data[1];//当前返回命令标志位
            data = data.Substring(2, data.Length - 3);
            switch (m_rCmd)
            {
                case '?':
                    {
                        string[] TempArray = data.Split('~');
                        if ((TempArray.Length >= 5) && (TempArray[0] == "SS"))
                        {
                            m_DeviceOk = true;
                            m_Device = TempArray[1];
                            m_Vendor = TempArray[2];
                            m_Website = TempArray[3];
                            m_Email = TempArray[4];
                            m_Tel = TempArray[5];
                        }
                        break;
                    }
                case 'a'://不处理
                    {
                        break;
                    }
                case 'B':
                    {
                        m_IsMoving = (Convert.ToByte(data) == 0) ? false : true;
                        break;
                    }
                case 'i':
                    {
                        FocuserInitialized = (Convert.ToByte(data) == 0) ? false : true;
                        if (InitFocuser)//电脑存储
                        {
                            if (!FocuserInitialized)//未初始化就进行初始化
                            {
                                //用一个定时器执行串口初始化，避免界面打开缓慢
                                Timer1 = new System.Timers.Timer();
                                Timer1.Elapsed += new ElapsedEventHandler(InitializeFocuser);
                                Timer1.Interval = 10;
                                Timer1.AutoReset = false;//执行一次 false，一直执行true  
                                //是否执行System.Timers.Timer.Elapsed事件  
                                Timer1.Enabled = true;
                            }
                        }
                        else//调焦器存储
                        {
                            if (FocuserInitialized)//已初始化
                                SetFocuserInitState(false);
                        }
                        break;
                    }
                case 'l':
                    {
                        bool TmpLowPower = (Convert.ToByte(data) == 0) ? false : true;
                        if (TmpLowPower != m_LowPower)
                        {
                            m_LowPower = TmpLowPower;
                            WriteProfile();
                        }
                        break;
                    }
                case 'r':
                    {
                        bool TmpReverse = (Convert.ToByte(data) == 0) ? false : true;
                        if (TmpReverse != m_MotorReverse)
                        {
                            m_MotorReverse = TmpReverse;
                            WriteProfile();
                        }
                        break;
                    }
                case 'm':
                    {
                        byte TmpMotorMicrostep = Convert.ToByte(data);
                        if (TmpMotorMicrostep != m_MotorMicrostep)
                        {
                            m_MotorMicrostep = TmpMotorMicrostep;
                            WriteProfile();
                        }
                        break;
                    }
                case 'v':
                    {
                        byte TmpSpeed = Convert.ToByte(data);
                        if (TmpSpeed != m_MotorSpeed)
                        {
                            m_MotorSpeed = TmpSpeed;
                            WriteProfile();
                        }
                        break;
                    }
                case 'p':
                    {
                        int TmpPosition = Convert.ToInt32(data);
                        if (TmpPosition != m_CurrentPosition)//有变化才存储，否则效率太低
                        {
                            m_CurrentPosition = TmpPosition;//设置当前位置
                            //SavePosition = false;
                            if (InitFocuser)//电脑存储
                            {
                                WritePosition(m_CurrentPosition);//存储位置
                                /*
                                if (Math.Abs(m_LastPosition - m_CurrentPosition) >= 100)//转动时每大于100步存一次
                                {
                                    WritePosition(m_CurrentPosition);//存储位置
                                    m_LastPosition = m_CurrentPosition;
                                }
                                if (!m_IsMoving)//不转动时立即存储，否则数据量太大反应慢
                                {
                                    WritePosition(m_CurrentPosition);//存储位置
                                    m_LastPosition = m_CurrentPosition;
                                }
                                */
                            }
                        }
                        /*
                        if (!m_IsMoving)//转动时不存储，否则数据量太大反应慢
                        {
                            if (!SavePosition)
                            {
                                WritePosition(m_CurrentPosition);//存储位置
                                SavePosition = true;
                            }
                        }
                        */
                        break;
                    }
                case 't':
                    {
                        m_CurrentTemperature = Convert.ToDouble(data);
                        break;
                    }
            }
        }
        public void SlewOut()
        {
            //SendMsg(":F+#");
            UartSendMsg(":F+#");//只发送一次，不接收返回，否则效率低
        }
        public void SlewIn()
        {
            //SendMsg(":F-#");
            UartSendMsg(":F-#");
        }
        public bool StartMove(int Destnation)
        {
            return SendMsg(":FP" + Destnation.ToString() + "#");
        }
        public bool StopMove()
        {
            return SendMsg(":FQ#");
        }
        public bool GetAllData()
        {
            return SendMsg(":Fa#");
        }
        public bool DefinePosition(int Position)
        {
            return SendMsg(":FD" + Position.ToString() + "#");
        }
        public void SetBluetooth(string Name)
        {
            //SendMsg(":Fb" + Name.Trim() + "#");//发三次单片机会死机
            UartSendMsg(":Fb" + Name.Trim() + "#");
        }
        public bool GetVersion()
        {
            return SendMsg(":F?#");
        }
        public bool GetMovState()
        {
            return SendMsg(":FB#");
        }
        public bool GetPosition()
        {
            return SendMsg(":Fp#");
        }
        public bool GetTemperature()
        {
            return SendMsg(":Ft#");
        }
        public bool SetFocuserInitState(bool LocalStore)
        {
            if (LocalStore)
                return SendMsg(":FI1#");
            else
                return SendMsg(":FI0#");
        }
        public bool GetFocuserInitState()
        {
            return SendMsg(":Fi#");
        }

        public bool SetLowPower(bool LowPower)
        {
            if (LowPower)
                return SendMsg(":FL1#");
            else
                return SendMsg(":FL0#");
        }
        public bool GetPowerWaste()
        {
            return SendMsg(":Fl#");
        }
        public bool SetReverse(bool reversed)
        {
            if (reversed)
                return SendMsg(":FR1#");
            else
                return SendMsg(":FR0#");
        }
        public bool GetReverse()
        {
            return SendMsg(":Fr#");
        }
        public bool SetMicrostep(byte Mode)
        {
            return SendMsg(":FM" + Mode.ToString("D3") + "#");
        }
        public bool GetMicrostep()
        {
            return SendMsg(":Fm#");
        }
        public bool SetSpeed(byte Speed)
        {
            return SendMsg(":FV" + Speed.ToString("D1") + "#");
        }
        public bool GetSpeed()
        {
            return SendMsg(":Fv#");
        }
        private void InitializeFocuser(object source, System.Timers.ElapsedEventArgs e)
        {
            m_CurrentPosition = ReadPosition();//从本地电脑读取上次存储位置
            //m_LastPosition = m_CurrentPosition;
            DefinePosition(m_CurrentPosition);//校准调焦器位置
            SetFocuserInitState(true);//设置为本地存储模式 
            GetFocuserInitState();
        } 
        //温度补偿功能，实际不需要，由控制软件提供
        public void TempCompensation(float TempCompRatio, float TempCompDegs)
        {
            //MessageBox.Show(m_CurrentPosition.ToString() + " : " + TempCompDegs.ToString()+" : "+m_CurrentTemperature.ToString() + " : " + m_StartTemperature.ToString());
            if ((m_CurrentTemperature >= 80)||(m_CurrentTemperature <= -80))//温度传感器初始值为85度，说明未获取到实际温度
                return;
            else if ((m_StartTemperature >= 80) || (m_StartTemperature <= -80))//温度传感器初始值为85度，说明未记录初始温度
                m_StartTemperature = m_CurrentTemperature;
            else
            {
                double DeltTemp = m_CurrentTemperature - m_StartTemperature;
                if (Math.Abs(DeltTemp) >= 30) return;//温度补偿每隔20秒执行一次，增加30度以上认为是错的直接跳出；
                int DeltStep = (int)(DeltTemp * TempCompRatio);
                if ((DeltStep > TempCompDegs) || (DeltStep < (-TempCompDegs)))//超过调整读数才生效
                {
                    //MessageBox.Show(DeltStep.ToString());
                    Move(m_CurrentPosition - DeltStep);//温度升高焦距变短，反之则变长
                }
                m_StartTemperature = m_CurrentTemperature;//补偿完成后 m_StartTemperature重新计算
            }
        }
        // 只能输入数字（含负号小数点）
        public static void OnlyEnterNumber(object sender, KeyPressEventArgs e)
        {
            if ((e.KeyChar < 48 || e.KeyChar > 57) && e.KeyChar != 8 && e.KeyChar != 13 && e.KeyChar != 45 && e.KeyChar != 46)
            {
                e.Handled = true;
            }

            //输入为负号时，只能输入一次且只能输入一次
            if (e.KeyChar == 45 && (((TextBox)sender).SelectionStart != 0 || ((TextBox)sender).Text.IndexOf("-") >= 0)) e.Handled = true;
            if (e.KeyChar == 46 && ((TextBox)sender).Text.IndexOf(".") >= 0) e.Handled = true;
        }
        // 只能输入正实数
        public static void OnlyEnterPlusNumber(object sender, KeyPressEventArgs e)
        {
            if ((e.KeyChar < 48 || e.KeyChar > 57) && e.KeyChar != 8 && e.KeyChar != 13 && e.KeyChar != 46)
            {
                e.Handled = true;
            }
            if (e.KeyChar == 46 && ((TextBox)sender).Text.IndexOf(".") >= 0) e.Handled = true;
        }
        // 只能输入整数
        public static void OnlyEnterInt(object sender, KeyPressEventArgs e)
        {
            if ((e.KeyChar < 48 || e.KeyChar > 57) && e.KeyChar != 8 && e.KeyChar != 13 && e.KeyChar != 45)
            {
                e.Handled = true;
            }

            //输入为负号时，只能输入一次且只能输入一次
            if (e.KeyChar == 45 && (((TextBox)sender).SelectionStart != 0 || ((TextBox)sender).Text.IndexOf("-") >= 0)) e.Handled = true;
        }
        // 只能输入正整数
        public static void OnlyEnterPlusInt(object sender, KeyPressEventArgs e)
        {
            if ((e.KeyChar < 48 || e.KeyChar > 57) && e.KeyChar != 8 && e.KeyChar != 13)
            {
                e.Handled = true;
            }
        }
        //存储配置数据，4种重载
        public void WriteValue(string key, string value)
        {
            using (Profile driverProfile = new Profile())
            {
                driverProfile.DeviceType = "Focuser";
                driverProfile.WriteValue(driverID, key, value);
            }
        }

        public void WriteValue(string key, int value)
        {
            WriteValue(key, value.ToString());
        }

        public void WriteValue(string key, double value)
        {
            WriteValue(key, value.ToString());
        }

        public void WriteValue(string key, bool value)
        {
            //this.WriteValue(key, ((value == true) ? 1 : 0).ToString());
            WriteValue(key, ((value == true) ? 1 : 0).ToString());
        }
        //读取配置数据，4种重载，无数据返回默认值
        public string ReadValue(string key, string defaultvalue)
        {
            using (Profile driverProfile = new Profile())
            {
                driverProfile.DeviceType = "Focuser";
                return driverProfile.GetValue(driverID, key, string.Empty, defaultvalue);
            }
        }

        public int ReadValue(string key, int defaultvalue)
        {
            return Int32.Parse(ReadValue(key, defaultvalue.ToString()));
        }

        public double ReadValue(string key, double defaultvalue)
        {
            return Double.Parse(ReadValue(key, defaultvalue.ToString()));
        }

        public bool ReadValue(string key, bool defaultvalue)
        {
            return ReadValue(key, Convert.ToInt32(defaultvalue)) == 0 ? false : true;
        }
        
        #endregion
    }
}
