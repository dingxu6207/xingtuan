using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using System.Threading;
using System.Runtime.InteropServices;//ComRegister
using System.Globalization;//CultureInfo
using System.Collections;//Arraylist

using ASCOM.DriverAccess;
using ASCOM.DeviceInterface;
using ASCOM.Utilities;
using ASCOM.Astrometry;
using ASCOM.Astrometry.AstroUtils;

namespace CAO
{
    public class SSDome
    {
        public byte MyDriverType;
        public ASCOM.DriverAccess.Dome MySSDome;

        internal static string driverID = "ASCOM.TDome.Dome";
        // TODO Change the descriptive string for your driver then remove this line
        /// <summary>
        /// Driver description that displays in the ASCOM Chooser.
        /// </summary>
        private static string driverDescription = "ASCOM Dome Driver for TDome.";

        internal static string comPortProfileName = "COM Port"; // Constants used for Profile persistence
        internal static string comPortDefault = "COM1";
        internal static string traceStateProfileName = "Trace Level";
        internal static string traceStateDefault = "false";

        internal static string comPort; // Variables to hold the currrent device configuration

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

        /// <summary>
        /// Initializes a new instance of the <see cref="TDome"/> class.
        /// Must be public for COM registration.
        /// </summary>
        public SSDome(string DriverID,byte DriverType)
        {
            MyDriverType = DriverType;
            if (MyDriverType == 0)
                MySSDome = new ASCOM.DriverAccess.Dome(DriverID);
            else
            {
                tl = new TraceLogger("", "TDome");
                //ReadProfile(); // Read device configuration from the ASCOM Profile store

                tl.LogMessage("Dome", "Starting initialisation");

                connectedState = false; // Initialise connected to false
                utilities = new Util(); //Initialise util object
                astroUtilities = new AstroUtils(); // Initialise astro utilities object
                //TODO: Implement your additional construction here

                tl.LogMessage("Dome", "Completed initialisation");
            }
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
            if (MyDriverType == 0)
                MySSDome.SetupDialog();
            // consider only showing the setup dialog if not connected
            // or call a different dialog if connected
            else
            {
                if (IsConnected)
                    System.Windows.Forms.MessageBox.Show("Already connected, just press OK");

                using (SetupDialogForm F = new SetupDialogForm(0))//设备类型，0-ASCOM，1-Serial,2-Socket
                {
                    var result = F.ShowDialog();
                    if (result == System.Windows.Forms.DialogResult.OK)
                    {
                        WriteProfile(); // Persist device configuration values to the ASCOM Profile store
                    }
                }
            }
        }

        public ArrayList SupportedActions
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSDome.SupportedActions;
                }
                else
                {
                    tl.LogMessage("SupportedActions Get", "Returning empty arraylist");
                    return new ArrayList();
                }
            }
        }

        public string Action(string actionName, string actionParameters)
        {
            if (MyDriverType == 0)
            {
                return MySSDome.Action(actionName, actionParameters);
            }
            else
            {
                LogMessage("", "Action {0}, parameters {1} not implemented", actionName, actionParameters);
                throw new ASCOM.ActionNotImplementedException("Action " + actionName + " is not implemented by this driver");
            }
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
            if (MyDriverType == 0)
            {
                MySSDome.Dispose();
            }
            else
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
        }

        public bool Connected
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSDome.Connected;
                }
                else
                {
                    LogMessage("Connected", "Get {0}", IsConnected);
                    return IsConnected;
                }
            }
            set
            {
                if (MyDriverType == 0)
                {
                    MySSDome.Connected = value;
                }
                else
                {
                    tl.LogMessage("Connected", "Set {0}", value);
                    if (value == IsConnected)
                        return;

                    if (value)
                    {
                        connectedState = true;
                        LogMessage("Connected Set", "Connecting to port {0}", comPort);
                        // TODO connect to the device
                    }
                    else
                    {
                        connectedState = false;
                        LogMessage("Connected Set", "Disconnecting from port {0}", comPort);
                        // TODO disconnect from the device
                    }
                }
            }
        }

        public string Description
        {
            // TODO customise this device description
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSDome.Description;
                }
                else
                {
                    tl.LogMessage("Description Get", driverDescription);
                    return driverDescription;
                }
            }
        }

        public string DriverInfo
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSDome.DriverInfo;
                }
                else
                {
                    Version version = System.Reflection.Assembly.GetExecutingAssembly().GetName().Version;
                    // TODO customise this driver description
                    string driverInfo = "Information about the driver itself. Version: " + String.Format(CultureInfo.InvariantCulture, "{0}.{1}", version.Major, version.Minor);
                    tl.LogMessage("DriverInfo Get", driverInfo);
                    return driverInfo;
                }
            }
        }

        public string DriverVersion
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSDome.DriverVersion;
                }
                else
                {
                    Version version = System.Reflection.Assembly.GetExecutingAssembly().GetName().Version;
                    string driverVersion = String.Format(CultureInfo.InvariantCulture, "{0}.{1}", version.Major, version.Minor);
                    tl.LogMessage("DriverVersion Get", driverVersion);
                    return driverVersion;
                }
            }
        }

        public short InterfaceVersion
        {
            // set by the driver wizard
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSDome.InterfaceVersion;
                }
                else
                {
                    LogMessage("InterfaceVersion Get", "2");
                    return Convert.ToInt16("2");
                }
            }
        }

        public string Name
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSDome.Name;
                }
                else
                {
                    string name = "Short driver name - please customise";
                    tl.LogMessage("Name Get", name);
                    return name;
                }
            }
        }

        #endregion

        #region IDome Implementation

        private bool domeShutterState = false; // Variable to hold the open/closed status of the shutter, true = Open

        public void AbortSlew()
        {
            if (MyDriverType == 0)
            {
                MySSDome.AbortSlew();
            }
            else
            {
                // This is a mandatory parameter but we have no action to take in this simple driver
                tl.LogMessage("AbortSlew", "Completed");
            }
        }

        public double Altitude
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSDome.Altitude;
                }
                else
                {
                    tl.LogMessage("Altitude Get", "Not implemented");
                    throw new ASCOM.PropertyNotImplementedException("Altitude", false);
                }
            }
        }

        public bool AtHome
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSDome.AtHome;
                }
                else
                {
                    tl.LogMessage("AtHome Get", "Not implemented");
                    throw new ASCOM.PropertyNotImplementedException("AtHome", false);
                }
            }
        }

        public bool AtPark
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSDome.AtPark;
                }
                else
                {
                    tl.LogMessage("AtPark Get", "Not implemented");
                    throw new ASCOM.PropertyNotImplementedException("AtPark", false);
                }
            }
        }

        public double Azimuth
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSDome.Azimuth;
                }
                else
                {
                    tl.LogMessage("Azimuth Get", "Not implemented");
                    throw new ASCOM.PropertyNotImplementedException("Azimuth", false);
                }
            }
        }

        public bool CanFindHome
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSDome.CanFindHome;
                }
                else
                {
                    tl.LogMessage("CanFindHome Get", false.ToString());
                    return false;
                }
            }
        }

        public bool CanPark
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSDome.CanPark;
                }
                else
                {
                    tl.LogMessage("CanPark Get", false.ToString());
                    return false;
                }
            }
        }

        public bool CanSetAltitude
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSDome.CanSetAltitude;
                }
                else
                {
                    tl.LogMessage("CanSetAltitude Get", false.ToString());
                    return false;
                }
            }
        }

        public bool CanSetAzimuth
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSDome.CanSetAzimuth;
                }
                else
                {
                    tl.LogMessage("CanSetAzimuth Get", false.ToString());
                    return false;
                }
            }
        }

        public bool CanSetPark
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSDome.CanSetPark;
                }
                else
                {
                    tl.LogMessage("CanSetPark Get", false.ToString());
                    return false;
                }
            }
        }

        public bool CanSetShutter
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSDome.CanSetShutter;
                }
                else
                {
                    tl.LogMessage("CanSetShutter Get", true.ToString());
                    return true;
                }
            }
        }

        public bool CanSlave
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSDome.CanSlave;
                }
                else
                {
                    tl.LogMessage("CanSlave Get", false.ToString());
                    return false;
                }
            }
        }

        public bool CanSyncAzimuth
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSDome.CanSyncAzimuth;
                }
                else
                {
                    tl.LogMessage("CanSyncAzimuth Get", false.ToString());
                    return false;
                }
            }
        }

        public void CloseShutter()
        {
            if (MyDriverType == 0)
            {
                MySSDome.CloseShutter();
            }
            else
            {
                tl.LogMessage("CloseShutter", "Shutter has been closed");
                domeShutterState = false;
            }
        }

        public void FindHome()
        {
            if (MyDriverType == 0)
            {
                MySSDome.FindHome();
            }
            else
            {
                tl.LogMessage("FindHome", "Not implemented");
                throw new ASCOM.MethodNotImplementedException("FindHome");
            }
        }

        public void OpenShutter()
        {
            if (MyDriverType == 0)
            {
                MySSDome.OpenShutter();
            }
            else
            {
                tl.LogMessage("OpenShutter", "Shutter has been opened");
                domeShutterState = true;
            }
        }

        public void Park()
        {
            if (MyDriverType == 0)
            {
                MySSDome.Park();
            }
            else
            {
                tl.LogMessage("Park", "Not implemented");
                throw new ASCOM.MethodNotImplementedException("Park");
            }
        }

        public void SetPark()
        {
            if (MyDriverType == 0)
            {
                MySSDome.SetPark();
            }
            else
            {
                tl.LogMessage("SetPark", "Not implemented");
                throw new ASCOM.MethodNotImplementedException("SetPark");
            }
        }

        public ShutterState ShutterStatus
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSDome.ShutterStatus;
                }
                else
                {
                    tl.LogMessage("ShutterStatus Get", false.ToString());
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
                }
            }
        }

        public bool Slaved
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSDome.Slaved;
                }
                else
                {
                    tl.LogMessage("Slaved Get", false.ToString());
                    return false;
                }
            }
            set
            {
                if (MyDriverType == 0)
                {
                    MySSDome.Slaved = value;
                }
                else
                {
                    tl.LogMessage("Slaved Set", "not implemented");
                    throw new ASCOM.PropertyNotImplementedException("Slaved", true);
                }
            }
        }

        public void SlewToAltitude(double Altitude)
        {
            if (MyDriverType == 0)
            {
                MySSDome.SlewToAltitude(Altitude);
            }
            else
            {
                tl.LogMessage("SlewToAltitude", "Not implemented");
                throw new ASCOM.MethodNotImplementedException("SlewToAltitude");
            }
        }

        public void SlewToAzimuth(double Azimuth)
        {
            if (MyDriverType == 0)
            {
                MySSDome.SlewToAzimuth(Azimuth);
            }
            else
            {
                tl.LogMessage("SlewToAzimuth", "Not implemented");
                throw new ASCOM.MethodNotImplementedException("SlewToAzimuth");
            }
        }

        public bool Slewing
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSDome.Slewing;
                }
                else
                {
                    tl.LogMessage("Slewing Get", false.ToString());
                    return false;
                }
            }
        }

        public void SyncToAzimuth(double Azimuth)
        {
            if (MyDriverType == 0)
            {
                MySSDome.SyncToAzimuth(Azimuth);
            }
            else
            {
                tl.LogMessage("SyncToAzimuth", "Not implemented");
                throw new ASCOM.MethodNotImplementedException("SyncToAzimuth");
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
    }
}
/*
public static void ThreadMethod(object parameter)  
        {
            Console.WriteLine("我是:{0},我要终止了", Thread.CurrentThread.Name);
            //开始终止线程
            Thread.CurrentThread.Abort();
            //下面的代码不会执行
            for (int i = 0; i < 10; i++)
            {
                Console.WriteLine("我是:{0},我循环{1}次", Thread.CurrentThread.Name,i);
            }
        }
*/