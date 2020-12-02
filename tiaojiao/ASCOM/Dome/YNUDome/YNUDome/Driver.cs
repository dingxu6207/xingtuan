//tabs=4
// --------------------------------------------------------------------------------
// TODO fill in this information for your driver, then remove this line!
//
// ASCOM Dome driver for YNUDome
//
// Description:	Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam 
//				nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam 
//				erat, sed diam voluptua. At vero eos et accusam et justo duo 
//				dolores et ea rebum. Stet clita kasd gubergren, no sea takimata 
//				sanctus est Lorem ipsum dolor sit amet.
//
// Implements:	ASCOM Dome interface version: <To be completed by driver developer>
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
#define Dome

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
using System.Timers;
using System.Threading;
using System.Windows.Forms;
using System.Text.RegularExpressions;//正则表达
using System.Data;

namespace ASCOM.YNUDome
{
    //
    // Your driver's DeviceID is ASCOM.YNUDome.Dome
    //
    // The Guid attribute sets the CLSID for ASCOM.YNUDome.Dome
    // The ClassInterface/None addribute prevents an empty interface called
    // _YNUDome from being created and used as the [default] interface
    //
    // TODO Replace the not implemented exceptions with code to implement the function or
    // throw the appropriate ASCOM exception.
    //

    /// <summary>
    /// ASCOM Dome Driver for YNUDome.
    /// </summary>
    [Guid("46257770-ffa3-453f-aa68-2087ecb1de87")]
    [ClassInterface(ClassInterfaceType.None)]
    public class Dome : IDomeV2
    {
        /// <summary>
        /// ASCOM DeviceID (COM ProgID) for this driver.
        /// The DeviceID is used by ASCOM applications to load the driver at runtime.
        /// </summary>
        internal static string driverID = "ASCOM.YNUDome.Dome";
        // TODO Change the descriptive string for your driver then remove this line
        /// <summary>
        /// Driver description that displays in the ASCOM Chooser.
        /// </summary>
        private static string driverDescription = "ASCOM Dome Driver for YNUDome.";

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
        private SerialPort MySerialPort;
        private byte RecvByte = 0, LastByte = 0;
        private byte[] RecvBuf;
        private bool HeadCmd = false;
        private int RecvCnt=0;  
        private UInt16 ChkSum = 0;
        internal static byte SlewSpeed = 0;
        internal static byte CtrMode = 0;
        internal static double AzimuthDeg = 0;
        internal static int AzimuthOffset = 0;
        internal static byte AzimuthSta = 0;
        internal static byte Shutter1Sta = 0;
        internal static byte Shutter2Sta = 0;
        internal static int PulseCnt = 0;
        internal static bool SlaveSta = false;

        private Toolbox MyToolbox;
        public static bool UseToolbox = false;
        public static bool ToolboxOpened = false;
        public static bool EnableShutter2 = false;

        internal static double AzimuthGoto=0;
        internal static double AltitudeGoto = 0;
        internal static byte TimeCount = 0;
        internal static byte TimeOut = 60;//60秒超时


        //Device info
        public static bool m_DeviceOk=true;


        /// <summary>
        /// Initializes a new instance of the <see cref="YNUDome"/> class.
        /// Must be public for COM registration.
        /// </summary>
        public Dome()
        {
            tl = new TraceLogger("", "YNUDome");
            ReadProfile(); // Read device configuration from the ASCOM Profile store

            tl.LogMessage("Dome", "Starting initialisation");

            connectedState = false; // Initialise connected to false
            utilities = new Util(); //Initialise util object
            astroUtilities = new AstroUtils(); // Initialise astro utilities object
            //TODO: Implement your additional construction here

            MySerialPort = new SerialPort();
            RecvBuf = new byte[17];
            MyToolbox = new Toolbox(this);

            tl.LogMessage("Dome", "Completed initialisation");
        }


        //
        // PUBLIC COM INTERFACE IDomeV2 IMPLEMENTATION
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
                    //connectedState = true;
                    LogMessage("Connected Set", "Connecting to port {0}", comPort);
                    // TODO connect to the device
                    UartUninitial();
                    UartInitial();
                    if (m_DeviceOk)
                    {
                        connectedState = true;
                        if (UseToolbox)//设置了需要打开
                            MyToolbox.Show();
                    }
                    else
                    {
                        try
                        {
                            UartUninitial();
                            connectedState = false;
                            MessageBox.Show("No device detected, please check connection!");
                        }
                        catch (Exception ex)
                        {
                            MessageBox.Show(ex.ToString ());
                        }
                    }
                }
                else
                {
                    //connectedState = false;
                    LogMessage("Connected Set", "Disconnecting from port {0}", comPort);
                    // TODO disconnect from the device
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

        #region IDome Implementation

        private bool domeShutterState = false; // Variable to hold the open/closed status of the shutter, true = Open

        public void AbortSlew()
        {
            // This is a mandatory parameter but we have no action to take in this simple driver
            //tl.LogMessage("AbortSlew", "Completed");
            StopAll();
        }

        public double Altitude
        {
            get
            {
                tl.LogMessage("Altitude Get", "Not implemented");
                throw new ASCOM.PropertyNotImplementedException("Altitude", false);
            }
        }

        public bool AtHome
        {
            get
            {
                tl.LogMessage("AtHome Get", "Not implemented");
                throw new ASCOM.PropertyNotImplementedException("AtHome", false);
            }
        }

        public bool AtPark
        {
            get
            {
                //tl.LogMessage("AtPark Get", "Not implemented");
                //throw new ASCOM.PropertyNotImplementedException("AtPark", false);
                if ((Azimuth == 0) && (AzimuthSta == 0x2F) && (Shutter1Sta == 0x2D) && (Shutter2Sta == 0x2D))
                    return true;
                else
                    return false;
            }
        }

        public double Azimuth
        {
            get
            {
                //tl.LogMessage("Azimuth Get", "Not implemented");
                //throw new ASCOM.PropertyNotImplementedException("Azimuth", false);
                if(TimeCount<TimeOut)
                    TimeCount++;
                ChkState();
                return AzimuthDeg;
            }
        }

        public bool CanFindHome
        {
            get
            {
                tl.LogMessage("CanFindHome Get", false.ToString());
                return false;
            }
        }

        public bool CanPark
        {
            get
            {
                tl.LogMessage("CanPark Get", false.ToString());
                //return false;
                return true;
            }
        }

        public bool CanSetAltitude
        {
            get
            {
                tl.LogMessage("CanSetAltitude Get", false.ToString());
                return false;
            }
        }

        public bool CanSetAzimuth
        {
            get
            {
                tl.LogMessage("CanSetAzimuth Get", false.ToString());
                //return false;
                return true;
            }
        }

        public bool CanSetPark
        {
            get
            {
                tl.LogMessage("CanSetPark Get", false.ToString());
                //return false;
                return true;
            }
        }

        public bool CanSetShutter
        {
            get
            {
                tl.LogMessage("CanSetShutter Get", true.ToString());
                return true;
            }
        }

        public bool CanSlave
        {
            get
            {
                tl.LogMessage("CanSlave Get", false.ToString());
                //return false;
                return true;
            }
        }

        public bool CanSyncAzimuth
        {
            get
            {
                tl.LogMessage("CanSyncAzimuth Get", false.ToString());
                //return false;
                return true;
            }
        }

        public void CloseShutter()
        {
            tl.LogMessage("CloseShutter", "Shutter has been closed");
            //domeShutterState = false;
            //Shutter1
            SendMsg(0x0B, 0);
            //Shutter2
            if (EnableShutter2)
                SendMsg(0x0E, 0);
        }

        public void FindHome()
        {
            tl.LogMessage("FindHome", "Not implemented");
            throw new ASCOM.MethodNotImplementedException("FindHome");
        }

        public void OpenShutter()
        {
            tl.LogMessage("OpenShutter", "Shutter has been opened");
            //domeShutterState = true;
            //Shutter1
            SendMsg(0x0A,0);
            //Shutter2
            if(EnableShutter2)
                SendMsg(0x0D,0);
        }

        public void Park()
        {
            //tl.LogMessage("Park", "Not implemented");
            //throw new ASCOM.MethodNotImplementedException("Park");
            SendMsg(0x03,0);//回零位
            SendMsg(0x0B,0);//关闭主天窗
            SendMsg(0x0E,0);//关闭副天窗
        }

        public void SetPark()
        {
            tl.LogMessage("SetPark", "Not implemented");
            throw new ASCOM.MethodNotImplementedException("SetPark");
        }

        public ShutterState ShutterStatus
        {
            get
            {
                tl.LogMessage("ShutterStatus Get", false.ToString());
                /*
                if (domeShutterState)
                {
                    tl.LogMessage("ShutterStatus", ShutterState.shutterOpen.ToString());
                    return ShutterState.shutterOpen;
                }
                else
                {
                    tl.LogMessage("ShutterStatus", ShutterState.shutterClosed.ToString());
                    return ShutterState.shutterClosed;
                }
                 */
                if (EnableShutter2)//主副天窗都启用
                {
                    if ((Shutter1Sta == 0xFF) || (Shutter2Sta == 0xFF))
                        return ShutterState.shutterError;//通信中断算错误发生
                    else if ((Shutter1Sta == 0x2F) || (Shutter2Sta == 0x2F))
                        return ShutterState.shutterError;//中途停止算错误发生
                    else if ((Shutter1Sta == 0x2A) || (Shutter2Sta == 0x2A))//只要其中一个在开就算正在打开，一个正在开一个正在关也算正在打开
                        return ShutterState.shutterOpening;
                    else if ((Shutter1Sta == 0x2B) || (Shutter2Sta == 0x2B))//只要其中一个在关就算正在关闭
                        return ShutterState.shutterClosing;
                    else if ((Shutter1Sta == 0x2C) && (Shutter2Sta == 0x2C))//二者都打开才算已打开
                        return ShutterState.shutterOpen;
                    else if ((Shutter1Sta == 0x2D) && (Shutter2Sta == 0x2D))//二者都关闭才算已关闭
                        return ShutterState.shutterClosed;
                    else
                        return ShutterState.shutterError;
                }
                else//只启用主天窗
                {
                    if (Shutter1Sta == 0xFF)
                        return ShutterState.shutterError;//通信中断算错误发生
                    else if (Shutter1Sta == 0x2F)
                        return ShutterState.shutterError;//中途停止算错误发生
                    else if (Shutter1Sta == 0x2A)//正在打开
                        return ShutterState.shutterOpening;
                    else if (Shutter1Sta == 0x2B)//正在关闭
                        return ShutterState.shutterClosing;
                    else if (Shutter1Sta == 0x2C)//已打开
                        return ShutterState.shutterOpen;
                    else if (Shutter1Sta == 0x2D)//已关闭
                        return ShutterState.shutterClosed;
                    else
                        return ShutterState.shutterError;
                }

            }
        }

        public bool Slaved
        {
            get
            {
                tl.LogMessage("Slaved Get", false.ToString());
                return false;
                //return SlaveSta;
            }
            set
            {
                tl.LogMessage("Slaved Set", "not implemented");
                throw new ASCOM.PropertyNotImplementedException("Slaved", true);
                //SlaveSta = value;
            }
        }

        public void SlewToAltitude(double Altitude)
        {
            tl.LogMessage("SlewToAltitude", "Not implemented");
            throw new ASCOM.MethodNotImplementedException("SlewToAltitude");
        }

        public void SlewToAzimuth(double Azimuth)
        {
            tl.LogMessage("SlewToAzimuth", "Not implemented");
            //throw new ASCOM.MethodNotImplementedException("SlewToAzimuth");
            GotoAzimuth(Azimuth);
        }

        public bool Slewing
        {
            get
            {
                tl.LogMessage("Slewing Get", false.ToString());
                return false;
            }
        }

        public void SyncToAzimuth(double Azimuth)
        {
            tl.LogMessage("SyncToAzimuth", "Not implemented");
            //throw new ASCOM.MethodNotImplementedException("SyncToAzimuth");
            SlewToAzimuth(Azimuth);
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
                P.DeviceType = "Dome";
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
                driverProfile.DeviceType = "Dome";
                tl.Enabled = Convert.ToBoolean(driverProfile.GetValue(driverID, traceStateProfileName, string.Empty, traceStateDefault));
                comPort = driverProfile.GetValue(driverID, comPortProfileName, string.Empty, comPortDefault);
                baudRate = Convert.ToInt32(driverProfile.GetValue(driverID, "BaudRate", string.Empty, "9600"));
                UseToolbox = Convert.ToInt32(driverProfile.GetValue(driverID, "UseToolbox", string.Empty, "0")) == 1 ? true : false;
                EnableShutter2 = Convert.ToInt32(driverProfile.GetValue(driverID, "EnableShutter2", string.Empty, "0")) == 1 ? true : false;
                AzimuthOffset = Convert.ToInt32(driverProfile.GetValue(driverID, "AzimuthOffset", string.Empty, "0"));
                SlewSpeed = Convert.ToByte(driverProfile.GetValue(driverID, "SlewSpeed", string.Empty, "0"));
            }
        }

        /// <summary>
        /// Write the device configuration to the  ASCOM  Profile store
        /// </summary>
        internal void WriteProfile()
        {
            using (Profile driverProfile = new Profile())
            {
                driverProfile.DeviceType = "Dome";
                driverProfile.WriteValue(driverID, traceStateProfileName, tl.Enabled.ToString());
                driverProfile.WriteValue(driverID, comPortProfileName, comPort.ToString());
                driverProfile.WriteValue(driverID, "BaudRate", baudRate.ToString());
                driverProfile.WriteValue(driverID, "UseToolbox", UseToolbox == true ? "1" : "0");
                driverProfile.WriteValue(driverID, "EnableShutter2", EnableShutter2 == true ? "1" : "0");
                driverProfile.WriteValue(driverID, "AzimuthOffset", AzimuthOffset.ToString());
                driverProfile.WriteValue(driverID, "SlewSpeed", SlewSpeed.ToString());
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


        public void SendMsg(byte Cmd,int Dat)
        {
            byte[] SendBuf = new byte[7];
            SendBuf[0] = 0xA5;
            SendBuf[1] = 0x5A;
            SendBuf[2] = Cmd;
            if (Cmd == 0x02)
            {
                if (Dat >= 0)
                    SendBuf[3] = 0x2B;
                else
                {
                    SendBuf[3] = 0x2D;
                    Dat = -Dat;
                }
                SendBuf[4] = (byte)(Dat / 256);
                SendBuf[5] = (byte)(Dat % 256);
            }
            else if (Cmd == 0x03)
            {
                SendBuf[3] = (byte)(Dat / 256);
                SendBuf[4] = (byte)(Dat % 256);
                SendBuf[5] = 0;
            }
            else
            {
                SendBuf[3] = 0x00;
                SendBuf[4] = 0x00;
                SendBuf[5] = 0x00;
            }
            SendBuf[6] = (byte)(SendBuf[2] + SendBuf[3] + SendBuf[4] + SendBuf[5]);
            UartSendMsg(SendBuf);
        }
        //初始化串口
        public void UartInitial()
        {
            try
            {
                MySerialPort.PortName = comPort;
                MySerialPort.DataBits = 8;
                MySerialPort.Parity = Parity.None;
                MySerialPort.StopBits = StopBits.One;
                MySerialPort.BaudRate = baudRate;
                //MySerialPort.NewLine = "\r\n";
                MySerialPort.DataReceived += new SerialDataReceivedEventHandler(UartRecvMsg);
                MySerialPort.Open();
            }
            //catch (IOException ex)
            catch (Exception ex)
            {
                //MessageBox.Show(ex.ToString());
            }
        }
        //释放串口资源
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
            }
        }

        public void UartSendMsg(byte[] Msg)
        {
            try
            {
                //if (!MySerialPort.IsOpen)
                //    MySerialPort.Open();
                MySerialPort.Write(Msg, 0, 7);
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
        //查询状态
        public void ChkState()
        {
            SendMsg(0x01, 0);
        }
        //设置零位偏差
        public void SetOffset(int OffSet)
        {
            SendMsg(0x02, OffSet);
        }
        //定位到Azimuth
        public void GotoAzimuth(double Azimuth)
        {
            while (Azimuth < 0)
            {
                Azimuth += 360;
            }
            while (Azimuth > 360)
            {
                Azimuth -= 360;
            }
            //MessageBox.Show(Azimuth.ToString ());
            SendMsg(0x03, (int)(Azimuth*10));//0-3600
        }
        //方位停止
        public void AbortAzimuth()
        {
            SendMsg(0x04, 0);
        }
        //方位逆时针慢动
        public void SlewAzimuthCCWSlow()
        {
            SendMsg(0x05, 0);
        }
        //方位逆时针快动
        public void SlewAzimuthCCWFast()
        {
            SendMsg(0x06, 0);
        }
        //方位顺时针慢动
        public void SlewAzimuthCWSlow()
        {
            SendMsg(0x07, 0);
        }
        //逆时针快动
        public void SlewAzimuthCWFast()
        {
            SendMsg(0x08, 0);
        }
        //主天窗停止
        public void AbortShutter1()
        {
            SendMsg(0x09, 0);
        }
        //主天窗打开
        public void OpenShutter1()
        {
            SendMsg(0x0A, 0);
        }
        //主天窗关闭
        public void CloseShutter1()
        {
            SendMsg(0x0B, 0);
        }
        //副天窗停止
        public void AbortShutter2()
        {
            SendMsg(0x0C, 0);
        }
        //副天窗打开
        public void OpenShutter2()
        {
            SendMsg(0x0D, 0);
        }
        //副天窗关闭
        public void CloseShutter2()
        {
            SendMsg(0x0E, 0);
        }
        //停止所有
        public void StopAll()
        {
            SendMsg(0x0F, 0);
        }
        //设置Goto窗口
        public void GotoDialog()
        {
            using (GotoForm F = new GotoForm(this))
            {
                var result = F.ShowDialog();
                if (result == System.Windows.Forms.DialogResult.OK)
                {
                    SlewToAzimuth(AzimuthGoto);
                    if (CanSetAltitude)
                        SlewToAltitude(Dome.AltitudeGoto);
                }
            }
        }
        private void UartRecvMsg(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            try
            {
                int BtoR = MySerialPort.BytesToRead;
                byte[] TempBuf = new byte[BtoR];
                int TempCnt = MySerialPort.Read(TempBuf, 0, BtoR);
                //MessageBox.Show(TempCnt.ToString ());
                for (int i = 0; i < TempCnt; i++)
                {
                    RecvCnt++;
                    RecvByte = TempBuf[i];
                    //MessageBox.Show(RecvByte.ToString ("X2"));
                    if ((RecvByte == 0x5A) && (LastByte == 0xA5))//找到协议头则RecvCnt = 2
                    {
                        RecvBuf[0] = 0xA5;
                        RecvBuf[1] = 0x5A;
                        RecvCnt = 2;
                        ChkSum = 0;
                        HeadCmd = true;
                    }
                    if (!HeadCmd)//协议头不正确则重新查找，不再往上计数，最多只能到1
                        RecvCnt = 0;
                    if (RecvCnt > 2)//3-17
                    {
                        RecvBuf[RecvCnt - 1] = RecvByte;
                        if (RecvCnt < 17)//3-16
                            ChkSum += RecvByte;
                    }
                    if (RecvCnt >= 17)
                    {
                        //if ((ChkSum&0x00FF) == RecvBuf[16])//低字节为校验码
                        {
                            CtrMode = RecvBuf[2];
                            //AzimuthDeg = (RecvBuf[3] * 256 + RecvBuf[4])/10.0;
                            //AzimuthOffset = RecvBuf[6] * 65536 + RecvBuf[7] * 256 + RecvBuf[8];
                            //if (RecvBuf[5] == 0x2D)//+:2B -:2D
                            //    AzimuthOffset = -AzimuthOffset;
                            AzimuthDeg = RecvBuf[3] * 256 + RecvBuf[4];//需要除以10吗？
                            AzimuthSta = RecvBuf[9];
                            Shutter1Sta = RecvBuf[10];
                            Shutter2Sta = RecvBuf[11];
                            //PulseCnt = RecvBuf[12] * 256 * 256 * 256 + RecvBuf[13] * 256 * 256 + RecvBuf[14] * 256 + RecvBuf[15];
                            /*
                            string str = "";
                            for (byte j = 0; j < 17; j++)
                                str += RecvBuf[j].ToString("X2") + " ";
                            MessageBox.Show(str);
                            */
                        }
                        RecvCnt = 0;
                        ChkSum = 0;
                        HeadCmd = false;
                        TimeCount = 0;//超时计数复位
                    }
                    LastByte = RecvByte;
                }
            }
            catch (Exception ex)
            {
                //MessageBox.Show(ex.ToString());
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
    }
}
