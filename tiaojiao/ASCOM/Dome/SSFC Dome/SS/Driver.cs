//tabs=4
// --------------------------------------------------------------------------------
// TODO fill in this information for your driver, then remove this line!
//
// ASCOM Dome driver for SSFC
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

using System.IO;
using System.IO.Ports;
using System.Windows.Forms;
using System.Text.RegularExpressions;//正则表达

namespace ASCOM.SSFC
{
    //
    // Your driver's DeviceID is ASCOM.SSFC.Dome
    //
    // The Guid attribute sets the CLSID for ASCOM.SSFC.Dome
    // The ClassInterface/None addribute prevents an empty interface called
    // _SSFC from being created and used as the [default] interface
    //
    // TODO Replace the not implemented exceptions with code to implement the function or
    // throw the appropriate ASCOM exception.
    //

    /// <summary>
    /// ASCOM Dome Driver for SSFC.
    /// </summary>
    [Guid("38b16f35-2812-421b-ad02-2d9c92b7c6ad")]
    [ClassInterface(ClassInterfaceType.None)]
    public class Dome : IDomeV2
    {
        /// <summary>
        /// ASCOM DeviceID (COM ProgID) for this driver.
        /// The DeviceID is used by ASCOM applications to load the driver at runtime.
        /// </summary>
        internal static string driverID = "ASCOM.SSFC.Dome";
        // TODO Change the descriptive string for your driver then remove this line
        /// <summary>
        /// Driver description that displays in the ASCOM Chooser.
        /// </summary>
        //private static string driverDescription = "ASCOM Dome Driver for SSFC.";
        private static string driverDescription = " SSFC Dome";

        internal static string comPortProfileName = "COM Port"; // Constants used for Profile persistence
        internal static string comPortDefault = "COM1";
        internal static string traceStateProfileName = "Trace Level";
        internal static string traceStateDefault = "false";

        //internal static string comPort; // Variables to hold the currrent device configuration


        //////////////graycode///////////
        internal static string ComPort;
        //public Profile driverProfile;
        SerialPort SerialCom;


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
        //internal static TraceLogger tl;

        /// <summary>
        /// Initializes a new instance of the <see cref="SSFC"/> class.
        /// Must be public for COM registration.
        /// </summary>
        public Dome()
        {
            //tl = new TraceLogger("", "SSFC");
            //ReadProfile(); // Read device configuration from the ASCOM Profile store

            //tl.LogMessage("Dome", "Starting initialisation");

            connectedState = false; // Initialise connected to false
            utilities = new Util(); //Initialise util object
            astroUtilities = new AstroUtils(); // Initialise astro utilities object
            //TODO: Implement your additional construction here
            //graycode
            //ComPort = ReadValue("ComPort", "COM1");
            //driverProfile = new Profile();
            //driverProfile.DeviceType = "Dome";
            SerialCom = new SerialPort();
            //tl.LogMessage("Dome", "Completed initialisation");
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
                    //WriteProfile(); // Persist device configuration values to the ASCOM Profile store
                }
            }
        }

        public ArrayList SupportedActions
        {
            get
            {
                //tl.LogMessage("SupportedActions Get", "Returning empty arraylist");
                return new ArrayList();
            }
        }

        public string Action(string actionName, string actionParameters)
        {
            //LogMessage("", "Action {0}, parameters {1} not implemented", actionName, actionParameters);
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
            //tl.Enabled = false;
            //tl.Dispose();
            //tl = null;
            utilities.Dispose();
            utilities = null;
            astroUtilities.Dispose();
            astroUtilities = null;
        }

        public bool Connected
        {
            get
            {
                //LogMessage("Connected", "Get {0}", IsConnected);
                return IsConnected;
            }
            set
            {
                //tl.LogMessage("Connected", "Set {0}", value);
                if (value == IsConnected)
                    return;

                if (value)
                {
                    try
                    {
                        if (SerialCom.IsOpen)
                            SerialCom.Close();
                        SerialCom.PortName = ComPort;
                        //MessageBox.Show(ComPort.ToString());
                        SerialCom.DataBits = 8;
                        SerialCom.Parity = Parity.None;
                        SerialCom.StopBits = StopBits.One;
                        SerialCom.BaudRate = 9600;
                        //SerialCom.DataReceived += new SerialDataReceivedEventHandler(SerialReciveMsg);
                        SerialCom.Open();
                    }
                    catch(IOException ex)
                    {
                        MessageBox.Show(ex.ToString());
                    }
                    connectedState = true;
                    //LogMessage("Connected Set", "Connecting to port {0}", comPort);
                    // TODO connect to the device
                }
                else
                {
                    SerialCom.Close();
                    connectedState = false;
                    //LogMessage("Connected Set", "Disconnecting from port {0}", comPort);
                    // TODO disconnect from the device
                }
            }
        }

        public string Description
        {
            // TODO customise this device description
            get
            {
                //tl.LogMessage("Description Get", driverDescription);
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
                //tl.LogMessage("DriverInfo Get", driverInfo);
                return driverInfo;
            }
        }

        public string DriverVersion
        {
            get
            {
                Version version = System.Reflection.Assembly.GetExecutingAssembly().GetName().Version;
                string driverVersion = String.Format(CultureInfo.InvariantCulture, "{0}.{1}", version.Major, version.Minor);
                //tl.LogMessage("DriverVersion Get", driverVersion);
                return driverVersion;
            }
        }

        public short InterfaceVersion
        {
            // set by the driver wizard
            get
            {
                //LogMessage("InterfaceVersion Get", "2");
                return Convert.ToInt16("2");
            }
        }

        public string Name
        {
            get
            {
                string name = "Short driver name - please customise";
                //tl.LogMessage("Name Get", name);
                return name;
            }
        }

        #endregion

        #region IDome Implementation

        private bool domeShutterState = false; // Variable to hold the open/closed status of the shutter, true = Open

        public void AbortSlew()
        {
            Stop();
            // This is a mandatory parameter but we have no action to take in this simple driver
            //tl.LogMessage("AbortSlew", "Completed");
        }

        public double Altitude
        {
            get
            {
                //tl.LogMessage("Altitude Get", "Not implemented");
                throw new ASCOM.PropertyNotImplementedException("Altitude", false);
            }
        }

        public bool AtHome
        {
            get
            {
                //tl.LogMessage("AtHome Get", "Not implemented");
                throw new ASCOM.PropertyNotImplementedException("AtHome", false);
            }
        }

        public bool AtPark
        {
            get
            {
                //tl.LogMessage("AtPark Get", "Not implemented");
                throw new ASCOM.PropertyNotImplementedException("AtPark", false);
            }
        }

        public double Azimuth
        {
            get
            {
                //tl.LogMessage("Azimuth Get", "Not implemented");
                throw new ASCOM.PropertyNotImplementedException("Azimuth", false);
            }
        }

        public bool CanFindHome
        {
            get
            {
                //tl.LogMessage("CanFindHome Get", false.ToString());
                return false;
            }
        }

        public bool CanPark
        {
            get
            {
                //tl.LogMessage("CanPark Get", false.ToString());
                return false;
            }
        }

        public bool CanSetAltitude
        {
            get
            {
                //tl.LogMessage("CanSetAltitude Get", false.ToString());
                return false;
            }
        }

        public bool CanSetAzimuth
        {
            get
            {
                //tl.LogMessage("CanSetAzimuth Get", false.ToString());
                return false;
            }
        }

        public bool CanSetPark
        {
            get
            {
                //tl.LogMessage("CanSetPark Get", false.ToString());
                return false;
            }
        }

        public bool CanSetShutter
        {
            get
            {
                //tl.LogMessage("CanSetShutter Get", true.ToString());
                return true;
            }
        }

        public bool CanSlave
        {
            get
            {
                //tl.LogMessage("CanSlave Get", false.ToString());
                return false;
            }
        }

        public bool CanSyncAzimuth
        {
            get
            {
                //tl.LogMessage("CanSyncAzimuth Get", false.ToString());
                return false;
            }
        }

        public void CloseShutter()
        {
            //tl.LogMessage("CloseShutter", "Shutter has been closed");
            Shut();
            domeShutterState = false;
        }

        public void FindHome()
        {
            //tl.LogMessage("FindHome", "Not implemented");
            throw new ASCOM.MethodNotImplementedException("FindHome");
        }

        public void OpenShutter()
        {
            //tl.LogMessage("OpenShutter", "Shutter has been opened");
            Open();
            domeShutterState = true;
        }

        public void Park()
        {
            //tl.LogMessage("Park", "Not implemented");
            throw new ASCOM.MethodNotImplementedException("Park");
        }

        public void SetPark()
        {
            //tl.LogMessage("SetPark", "Not implemented");
            throw new ASCOM.MethodNotImplementedException("SetPark");
        }

        public ShutterState ShutterStatus
        {
            get
            {
                //tl.LogMessage("ShutterStatus Get", false.ToString());
                if (domeShutterState)
                {
                    //tl.LogMessage("ShutterStatus", ShutterState.shutterOpen.ToString());
                    return ShutterState.shutterOpen;
                }
                else
                {
                    //tl.LogMessage("ShutterStatus", ShutterState.shutterClosed.ToString());
                    return ShutterState.shutterClosed;
                }
            }
        }

        public bool Slaved
        {
            get
            {
                //tl.LogMessage("Slaved Get", false.ToString());
                return false;
            }
            set
            {
                //tl.LogMessage("Slaved Set", "not implemented");
                throw new ASCOM.PropertyNotImplementedException("Slaved", true);
            }
        }

        public void SlewToAltitude(double Altitude)
        {
            //tl.LogMessage("SlewToAltitude", "Not implemented");
            throw new ASCOM.MethodNotImplementedException("SlewToAltitude");
        }

        public void SlewToAzimuth(double Azimuth)
        {
            //tl.LogMessage("SlewToAzimuth", "Not implemented");
            throw new ASCOM.MethodNotImplementedException("SlewToAzimuth");
        }

        public bool Slewing
        {
            get
            {
                //tl.LogMessage("Slewing Get", false.ToString());
                return false;
            }
        }

        public void SyncToAzimuth(double Azimuth)
        {
            //tl.LogMessage("SyncToAzimuth", "Not implemented");
            throw new ASCOM.MethodNotImplementedException("SyncToAzimuth");
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
        /// 
        /*
        internal void ReadProfile()
        {
            using (Profile driverProfile = new Profile())
            {
                driverProfile.DeviceType = "Dome";
                //tl.Enabled = Convert.ToBoolean(driverProfile.GetValue(driverID, traceStateProfileName, string.Empty, traceStateDefault));
                ComPort = driverProfile.GetValue(driverID, comPortProfileName, string.Empty, comPortDefault);
            }
        }
        */
        /// <summary>
        /// Write the device configuration to the  ASCOM  Profile store
        /// </summary>
        /// 
        /*
        internal void WriteProfile()
        {
            using (Profile driverProfile = new Profile())
            {
                driverProfile.DeviceType = "Dome";
                //driverProfile.WriteValue(driverID, traceStateProfileName, tl.Enabled.ToString());
                driverProfile.WriteValue(driverID, comPortProfileName, ComPort.ToString());
            }
        }
        */
        /// <summary>
        /// Log helper function that takes formatted strings and arguments
        /// </summary>
        /// <param name="identifier"></param>
        /// <param name="message"></param>
        /// <param name="args"></param>
        internal static void LogMessage(string identifier, string message, params object[] args)
        {
            var msg = string.Format(message, args);
            //tl.LogMessage(identifier, msg);
        }
        #endregion

        //////////////graycode//////////////
        //存储配置数据，4种重载
        public void WriteValue(string key, string value)
        {
            using (Profile driverProfile = new Profile())
            {
                driverProfile.DeviceType = "Dome";
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
                driverProfile.DeviceType = "Dome";
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
            //return (Int32.Parse(ReadValue(key, defaultvalue.ToString())) == 0) ? false : true;
            return ReadValue(key, Convert.ToInt32(defaultvalue)) == 0 ? false : true;
        }

        void SerialSendMsg(byte[] Command)
        {
            try
            {
                if (!SerialCom.IsOpen)
                    SerialCom.Open();
                SerialCom.Write(Command, 0, Command.Length);
                //SerialCom.Write("ttt");
            }
            catch (IOException ex)
            {
                MessageBox.Show(ex.ToString());
            }
        }
        void Open()
        {
            //SerialCom.Write("Open");
            //MessageBox.Show("Open");
            SerialSendMsg(SendBuffer(ReadValue("Open", "FD 7D 9E 98 6B DF"), ReadValue("Time", "02")));
        }
        void Shut()
        {
            //SerialCom.Write("Shut");
            //MessageBox.Show("Shut");
            SerialSendMsg(SendBuffer(ReadValue("Shut", "FD 7D 9E 94 6B DF"), ReadValue("Time", "02")));
        }
        void Stop()
        {
            //SerialCom.Write("Stop");
            //MessageBox.Show("Stop");
            SerialSendMsg(SendBuffer(ReadValue("Stop", "FD 7D 9E 92 6B DF"), ReadValue("Time", "02")));
        }
        void Lock()
        {
            SerialSendMsg(SendBuffer(ReadValue("Lock", "FD 7D 9E 91 6B DF"), ReadValue("Time", "02")));
        }
        Byte[] SendBuffer(string ReadCode, string SendTime)
        {
            byte[] SendBytes = null;
            string SendData = ReadCode.Replace(" ", "");//剔除所有空格
            SendData = SendData.Substring(2, SendData.Length - 4);//去掉头和尾
            SendData = "99" + SendTime + SendData + "99";//加协议头和发射时间参数
            //每两个字符放进认为一个字节
            List<string> SendDataList = new List<string>();
            for (int i = 0; i < SendData.Length; i = i + 2)
            {
                SendDataList.Add(SendData.Substring(i, 2));
            }
            SendBytes = new byte[SendDataList.Count];
            for (int j = 0; j < SendBytes.Length; j++)
            {
                SendBytes[j] = (byte)(Convert.ToInt32(SendDataList[j], 16));
            }
            return SendBytes;
        }
    }
}
