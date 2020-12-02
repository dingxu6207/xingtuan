using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using System.Threading;
using System.Runtime.InteropServices;//ComRegister
using System.Globalization;//CultureInfo
using System.Collections;//Arraylist

using ASCOM;
using ASCOM.Astrometry;
using ASCOM.Astrometry.AstroUtils;
using ASCOM.Utilities;
using ASCOM.DeviceInterface;

namespace CAO
{
    public class SSFocuser
    {
        /// <summary>
        /// ASCOM DeviceID (COM ProgID) for this driver.
        /// The DeviceID is used by ASCOM applications to load the driver at runtime.
        /// </summary>
        public byte MyDriverType;
        public ASCOM.DriverAccess.Focuser MySSFocuser;

        internal static string driverID = "ASCOM.TFocuser.Focuser";
        // TODO Change the descriptive string for your driver then remove this line
        /// <summary>
        /// Driver description that displays in the ASCOM Chooser.
        /// </summary>
        private static string driverDescription = "ASCOM Focuser Driver for TFocuser.";

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
        /// Initializes a new instance of the <see cref="TFocuser"/> class.
        /// Must be public for COM registration.
        /// </summary>
        public SSFocuser(string DriverID, byte DriverType)
        {
            MyDriverType = DriverType;
            if (MyDriverType == 0)
                MySSFocuser = new ASCOM.DriverAccess.Focuser(DriverID);
            else
            {
                tl = new TraceLogger("", "TFocuser");
                //ReadProfile(); // Read device configuration from the ASCOM Profile store

                tl.LogMessage("Focuser", "Starting initialisation");

                connectedState = false; // Initialise connected to false
                utilities = new Util(); //Initialise util object
                astroUtilities = new AstroUtils(); // Initialise astro utilities object
                //TODO: Implement your additional construction here

                tl.LogMessage("Focuser", "Completed initialisation");
            }
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
            if (MyDriverType == 0)
                MySSFocuser.SetupDialog();
            else
            {
                // consider only showing the setup dialog if not connected
                // or call a different dialog if connected
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
                    return MySSFocuser.SupportedActions;
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
                return MySSFocuser.Action(actionName, actionParameters);
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
                MySSFocuser.Dispose();
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
                    return MySSFocuser.Connected;
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
                    MySSFocuser.Connected = value;
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
                    return MySSFocuser.Description;
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
                    return MySSFocuser.DriverInfo;
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
                    return MySSFocuser.DriverVersion;
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
                    return MySSFocuser.InterfaceVersion;
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
                    return MySSFocuser.Name;
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

        #region IFocuser Implementation

        private int focuserPosition = 0; // Class level variable to hold the current focuser position
        private const int focuserSteps = 10000;

        public bool Absolute
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSFocuser.Absolute;
                }
                else
                {
                    tl.LogMessage("Absolute Get", true.ToString());
                    return true; // This is an absolute focuser
                }
            }
        }

        public void Halt()
        {
            if (MyDriverType == 0)
            {
                MySSFocuser.Halt();
            }
            else
            {
                tl.LogMessage("Halt", "Not implemented");
                throw new ASCOM.MethodNotImplementedException("Halt");
            }
        }

        public bool IsMoving
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSFocuser.IsMoving;
                }
                else
                {
                    tl.LogMessage("IsMoving Get", false.ToString());
                    return false; // This focuser always moves instantaneously so no need for IsMoving ever to be True
                }
            }
        }

        public bool Link
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSFocuser.Link;
                }
                else
                {
                    tl.LogMessage("Link Get", this.Connected.ToString());
                    return this.Connected; // Direct function to the connected method, the Link method is just here for backwards compatibility
                }
            }
            set
            {
                if (MyDriverType == 0)
                {
                    MySSFocuser.Link = value;
                }
                else
                {
                    tl.LogMessage("Link Set", value.ToString());
                    this.Connected = value; // Direct function to the connected method, the Link method is just here for backwards compatibility
                }
            }
        }

        public int MaxIncrement
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSFocuser.MaxIncrement;
                }
                else
                {
                    tl.LogMessage("MaxIncrement Get", focuserSteps.ToString());
                    return focuserSteps; // Maximum change in one move
                }
            }
        }

        public int MaxStep
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSFocuser.MaxStep;
                }
                else
                {
                    tl.LogMessage("MaxStep Get", focuserSteps.ToString());
                    return focuserSteps; // Maximum extent of the focuser, so position range is 0 to 10,000
                }
            }
        }

        public void Move(int Position)
        {
            if (MyDriverType == 0)
            {
                MySSFocuser.Move(Position);
            }
            else
            {
                tl.LogMessage("Move", Position.ToString());
                focuserPosition = Position; // Set the focuser position
            }
        }

        public int Position
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSFocuser.Position;
                }
                else
                {
                    return focuserPosition; // Return the focuser position
                }
            }
        }

        public double StepSize
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSFocuser.StepSize;
                }
                else
                {
                    tl.LogMessage("StepSize Get", "Not implemented");
                    throw new ASCOM.PropertyNotImplementedException("StepSize", false);
                }
            }
        }

        public bool TempComp
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSFocuser.TempComp;
                }
                else
                {
                    tl.LogMessage("TempComp Get", false.ToString());
                    return false;
                }
            }
            set
            {
                if (MyDriverType == 0)
                {
                    MySSFocuser.TempComp = value;
                }
                else
                {
                    tl.LogMessage("TempComp Set", "Not implemented");
                    throw new ASCOM.PropertyNotImplementedException("TempComp", false);
                }
            }
        }

        public bool TempCompAvailable
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSFocuser.TempCompAvailable;
                }
                else
                {
                    tl.LogMessage("TempCompAvailable Get", false.ToString());
                    return false; // Temperature compensation is not available in this driver
                }
            }
        }

        public double Temperature
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSFocuser.Temperature;
                }
                else
                {
                    tl.LogMessage("Temperature Get", "Not implemented");
                    throw new ASCOM.PropertyNotImplementedException("Temperature", false);
                }
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
                driverProfile.DeviceType = "Focuser";
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
