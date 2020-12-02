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
        private static string driverDescription = "Sky-Rover Focuser";

        //internal static string comPortProfileName = "COM Port"; // Constants used for Profile persistence
        //internal static string comPortDefault = "COM1";
        internal static string traceStateProfileName = "Trace Level";
        internal static string traceStateDefault = "false";

        //internal static string comPort; // Variables to hold the currrent device configuration

        /// <summary>
        /// Private variable to hold the connected state
        /// </summary>
        private bool connectedState;

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
        private SerialPort MySerialPort;
        public static string ComPort;
        public static int BaudRate;
        private byte[] buffer;
        
        private string RecvBuffer;
        public char m_rCmd;
        //Device
        public static string m_Device, m_Version;
        //Low power mode
        public static bool m_LowPower;
        //Bluetooth
        public static string m_BTName;
        //Focuser
        public static int m_MaxStep, m_MaxIncrement;
        public static float m_StepSize;
        //Temperature
        public static float m_TempCompRatio;
        public static float m_TempCompDegs;
        //Motor
        public static bool m_MotorReverse;
        public static byte m_SubDivision;
        public static UInt16 m_MotorSpeed;
        //Cover
        //public static UInt16 m_OpenCoverCode, m_CloseCoverCode;
        //Other
        public static bool m_IsMoving, m_TempCompEnable, m_TempComp;
        public static int m_CurrentPosition;//, m_LastPosition;
        public static double m_StartTemperature, m_CurrentTemperature;

        public static bool UseToolbox = false;
        private FocuserToolbox MyToolbox;
        public static byte TimeCount = 0;
        //public static byte m_Initialized;//初始配置状态 0 - 未初始化 1 - 已初始化 2 - 开机状态

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


            MySerialPort = new SerialPort();
            buffer = new byte[1024];

            m_rCmd = 'U';

            MyToolbox = new FocuserToolbox(this);

            m_IsMoving = false;
            m_TempComp = false;
            m_TempCompEnable = true;
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
                    connectedState = true;
                    //LogMessage("Connected Set", "Connecting to port {0}", comPort);
                    // TODO connect to the device
                    ConnectDevice();
                }
                else
                {
                    connectedState = false;
                    //LogMessage("Connected Set", "Disconnecting from port {0}", comPort);
                    // TODO disconnect from the device
                    DisconnectDevice();
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
            //if(StopMove())
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
                //GetAllData();
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

        public void Move(int Position)
        {
            tl.LogMessage("Move", Position.ToString());
            //focuserPosition = Position; // Set the focuser position
            if(StartMove(Position))
                m_IsMoving = true;//避免运动状态变化立即发送两次Move命令导致齿轮回差无法执行
            //Thread.Sleep(500);
        }

        public int Position//Moving期间不发Position，只查询IsMoving,所以如果采用同步模式Toolbox无法实时显示步数
        {
            get
            {
                //return focuserPosition; // Return the focuser position
                if (IsMoving)
                    GetPosition();
                else
                    GetAllData();
                //Thread.Sleep(500);
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
                tl.LogMessage("TempCompAvailable Get", m_TempCompEnable.ToString());
                return m_TempCompEnable;
            }
        }

        public double Temperature
        {
            get
            {
                //tl.LogMessage("Temperature Get", "Not implemented");
                //throw new ASCOM.PropertyNotImplementedException("Temperature", false);
                tl.LogMessage("Temperature Get", m_CurrentTemperature.ToString ());
                if (m_TempComp)//温度补偿
                {
                    TempCompensation(m_TempCompRatio, m_TempCompDegs);
                }
                else
                {
                    m_StartTemperature = m_CurrentTemperature;
                }
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
                //comPort = driverProfile.GetValue(driverID, comPortProfileName, string.Empty, comPortDefault);

                ComPort = driverProfile.GetValue(driverID, "ComPort", string.Empty, "COM1");
                BaudRate = Convert.ToInt32(driverProfile.GetValue(driverID, "BaudRate", string.Empty, "9600"));

                m_Device = driverProfile.GetValue(driverID, "Device", string.Empty, "SSFocuser");
                m_Version = driverProfile.GetValue(driverID, "Version", string.Empty, "WF1.0");

                m_LowPower = Convert.ToBoolean(driverProfile.GetValue(driverID, "LowPower", string.Empty, true.ToString()));

                m_BTName = driverProfile.GetValue(driverID, "BTName", string.Empty, "SkyRoverFocuser");

                m_MotorReverse = Convert.ToBoolean(driverProfile.GetValue(driverID, "MotorReverse", string.Empty, false.ToString()));
                m_SubDivision = Convert.ToByte(driverProfile.GetValue(driverID, "SubDivision", string.Empty, "1"));
                m_MotorSpeed = Convert.ToUInt16(driverProfile.GetValue(driverID, "MotorSpeed", string.Empty, "64"));

                //m_OpenCoverCode = Convert.ToUInt16(driverProfile.GetValue(driverID, "OpenCoverCode", string.Empty, "20"));
                //m_CloseCoverCode = Convert.ToUInt16(driverProfile.GetValue(driverID, "CloseCoverCode", string.Empty, "5"));

                m_TempCompRatio = Convert.ToSingle(driverProfile.GetValue(driverID, "TempCompRatio", string.Empty, "0.0"));
                m_TempCompDegs = Convert.ToSingle(driverProfile.GetValue(driverID, "TempCompDegs", string.Empty, "10.0"));

                m_MaxStep = Convert.ToInt32(driverProfile.GetValue(driverID, "MaxStep", string.Empty, "10000"));
                m_StepSize = Convert.ToSingle(driverProfile.GetValue(driverID, "StepSize", string.Empty, "10.0"));
                m_MaxIncrement = Convert.ToInt32(driverProfile.GetValue(driverID, "MaxIncrement", string.Empty, "10000"));

                UseToolbox = Convert.ToInt32(driverProfile.GetValue(driverID, "UseToolbox", string.Empty, "0"))==1?true:false;
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

                driverProfile.WriteValue(driverID, "ComPort", ComPort.ToString());
                driverProfile.WriteValue(driverID, "BaudRate", BaudRate.ToString());

                driverProfile.WriteValue(driverID, "Device", m_Device);
                driverProfile.WriteValue(driverID, "Version", m_Version);

                driverProfile.WriteValue(driverID, "LowPower", m_LowPower.ToString());

                driverProfile.WriteValue(driverID, "BTName", m_BTName);

                driverProfile.WriteValue(driverID, "MotorReverse", m_MotorReverse.ToString());
                driverProfile.WriteValue(driverID, "SubDivision", m_SubDivision.ToString());
                driverProfile.WriteValue(driverID, "MotorSpeed", m_MotorSpeed.ToString());

                //driverProfile.WriteValue(driverID, "OpenCoverCode", m_OpenCoverCode.ToString());
                //driverProfile.WriteValue(driverID, "CloseCoverCode", m_CloseCoverCode.ToString());

                driverProfile.WriteValue(driverID, "TempCompRatio", m_TempCompRatio.ToString());
                driverProfile.WriteValue(driverID, "TempCompDegs", m_TempCompDegs.ToString());

                driverProfile.WriteValue(driverID, "MaxStep", m_MaxStep.ToString());
                driverProfile.WriteValue(driverID, "StepSize", m_StepSize.ToString());
                driverProfile.WriteValue(driverID, "MaxIncrement", m_MaxIncrement.ToString());

                driverProfile.WriteValue(driverID, "UseToolbox", UseToolbox==true?"1":"0");
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

        
        //////////////graycode//////////////

        //发送命令，带返回确认
        public bool SendMsg(string command)
        {
            bool ret = false;
            byte i=0,j=0;
            char m_sCmd=Convert.ToChar(command.Substring(2,1));
            m_rCmd = 'U';
            for (i = 0; i < 3; i++)
            {
                //MessageBox.Show("send:" + scmd.ToString() + "-recv:" + m_rCmd.ToString());
                UartSendMsg(command);
                //Thread.Sleep(300);
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

        public void ConnectDevice()
        {
            UartInitial();
        }

        public void DisconnectDevice()
        {
            UartUninitial();
        }
        
        public bool StartMove(int Destnation)
        {
            return SendMsg(":FP" + Destnation.ToString() + "#");
        }
        public bool StopMove()
        {
            return SendMsg(":FQ#");
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
        public bool GetAllData()
        {
            return SendMsg(":Fa#");
        }
        public bool DefinePosition(int Position)
        {
            return SendMsg(":FD" + Position.ToString() + "#");
        }
        public bool SetReverse(bool reversed)
        {
            if (reversed)
                return SendMsg(":FR1#");
            else
                return SendMsg(":FR0#");
        }
        public bool SetLowPower(bool LowPower)
        {
            if (LowPower)
                return SendMsg(":FL1#");
            else
                return SendMsg(":FL0#");
        }
        public bool SetSpeed(UInt16 Speed)
        {
            return SendMsg(":FV" + Speed.ToString("D3") + "#");
        }
        public void SetBluetooth(string Name)
        {
            //SendMsg(":Fb" + Name.Trim() + "#");//发三次单片机会死机
            UartSendMsg(":Fb" + Name.Trim() + "#");
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
        public bool SetMotor(bool reversed, byte Mode, UInt16 Speed)
        {
            if (reversed)
                return SendMsg(":FM1" + Mode.ToString("D3") + Speed.ToString("D3") + "#");
            else
                return SendMsg(":FM0" + Mode.ToString("D3") + Speed.ToString("D3") + "#");
        }
        public void UartInitial()
        {
            try
            {
                if (MySerialPort.IsOpen)
                    MySerialPort.Close();
                MySerialPort.PortName = ComPort;
                MySerialPort.DataBits = 8;
                MySerialPort.Parity = Parity.None;
                MySerialPort.StopBits = StopBits.One;
                MySerialPort.BaudRate = BaudRate;
                MySerialPort.NewLine = "\r\n";
                MySerialPort.DataReceived += new SerialDataReceivedEventHandler(UartRecvMsg);
                MySerialPort.Open();
                //SendMsg(":FZ1000#");//设置为主动模式，主动发送周期1000mS
                if (UseToolbox)
                {
                    Thread.Sleep(1000);//等待接收调焦器参数
                    MyToolbox.Show();
                }
            }
            catch (IOException ex)
            {
                MessageBox.Show(ex.ToString());
            }
        }

        public void UartUninitial()
        {
            try
            {
                if (MySerialPort.IsOpen)
                {
                    if (UseToolbox)//先关Toolbox
                        MyToolbox.Close();
                    MySerialPort.BreakState = true;
                    MySerialPort.Close();
                }
            }
            catch (IOException ex)
            {
                MessageBox.Show(ex.ToString());
            }
        }

        public void UartSendMsg(string Msg)
        {
            try
            {
                //if (!MySerialPort.IsOpen)
                //    MySerialPort.Open();
                MySerialPort.Write(Msg);
            }
            catch (IOException ex)//不能弹出窗口，否则串口线拔出后一直提示无法关闭控制软件
            {
                //if (!m_ConnectError)//只弹出一次
                {
                    MessageBox.Show(ex.ToString());
                    //m_ConnectError = true;
                }
            }
        }

        private void UartRecvMsg(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            RecvBuffer = RecvBuffer + MySerialPort.ReadExisting();
            ProcessCommand(RecvBuffer);
        }

        public bool ProcessCommand(string command)
        {
            //判断有效性，没法判断两个冒号：连#号的情况如:123:222#，需改进
            string re1 = "(:)";	// Any Single Character 1
            string re2 = ".*?";	// Non-greedy match on filler
            string re3 = "(#)";	// Any Single Character 2
            string Pattern = re1 + re2 + re3;
            MatchCollection Matches = Regex.Matches(
                command,
                Pattern,
                RegexOptions.ExplicitCapture | RegexOptions.IgnoreCase    //提高检索效率  
                );
            if (Matches.Count > 0)
            {
                foreach (Match NextMatch in Matches)
                {
                    //MessageBox.Show(NextMatch.Value);
                    char cmd = Convert.ToChar( NextMatch.Value.Substring(1, 1));
                    string data = NextMatch.Value.Substring(2, NextMatch.Value.Length - 3);
                    //MessageBox.Show(data);
                    m_rCmd = cmd;//当前返回命令标志位
                    switch (cmd)
                    {
                        case '?':
                            {
                                m_Version = data;
                                break;
                            }
                        case 'a':
                            {
                                string[] TempArray = data.Split('~');
                                m_CurrentPosition = Convert.ToInt32(TempArray[0]);
                                m_IsMoving = (Convert.ToInt16(TempArray[1]) == 0) ? false : true;
                                m_CurrentTemperature = Convert.ToDouble(TempArray[2]);
                                bool TmpReverse = (Convert.ToInt16(TempArray[3]) == 0) ? false : true;
                                byte TmpDivision = Convert.ToByte(TempArray[4]);
                                UInt16 TmpSpeed = Convert.ToUInt16(TempArray[5]);
                                m_LowPower = (Convert.ToInt16(TempArray[6]) == 0) ? false : true;
                                if ((TmpReverse != m_MotorReverse) || (TmpDivision != m_SubDivision) || (TmpSpeed != m_MotorSpeed))
                                {
                                    m_MotorReverse = TmpReverse;
                                    m_SubDivision = TmpDivision;
                                    m_MotorSpeed = TmpSpeed;
                                    WriteProfile();
                                }

                                break;
                            }
                        case 'B':
                            {
                                m_IsMoving = (Convert.ToInt16(data) == 0) ? false : true;
                                break;
                            }
                        case 'm':
                            {
                                string[] TempArray = data.Split('~');
                                bool TmpReverse = (Convert.ToInt16(TempArray[0]) == 0) ? false : true;
                                byte TmpDivision = Convert.ToByte(TempArray[1]);
                                UInt16 TmpSpeed = Convert.ToUInt16(TempArray[2]);
                                if ((TmpReverse != m_MotorReverse)||(TmpDivision != m_SubDivision)||(TmpSpeed != m_MotorSpeed))
                                {
                                    m_MotorReverse = TmpReverse;
                                    m_SubDivision = TmpDivision;
                                    m_MotorSpeed = TmpSpeed;
                                    WriteProfile();
                                }
                                break;
                            }
                        case 'p':
                            {
                                m_CurrentPosition = Convert.ToInt32(data);
                                break;
                            }
                        case 't':
                            {
                                m_CurrentTemperature = Convert.ToDouble(data);
                                break;
                            }

                    }

                }
                RecvBuffer = "";//命令处理完后清空
                return true;
            }
            else//无匹配时判断是否含有冒号，如含冒号可能传输未完成
            {
                if (command.IndexOf(":") < 0)//如果不含：号清空
                    RecvBuffer = "";
                //MessageBox.Show(RecvBuffer);
                return false;
            }
        }
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
        /*
        private void UartRecvMsg2(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            RecvBuffer = MySerialPort.ReadLine();
            //MessageBox.Show("RecvBuffer:" + RecvBuffer);
            int StartIndex1 = RecvBuffer.IndexOf(':');
            int StartIndex2 = RecvBuffer.IndexOf('#');
            if ((StartIndex1 > -1) && (StartIndex2 > StartIndex1))
            {
                string cmd = RecvBuffer.Substring(StartIndex1 + 1, 1);
                string data = RecvBuffer.Substring(StartIndex1 + 2, StartIndex2 - StartIndex1 - 2);

                switch (cmd)
                {
                    
                }
            }
            RecvBuffer = "";
        }
        */
    }
}
