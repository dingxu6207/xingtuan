using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using System.Threading;
using System.Runtime.InteropServices;//ComRegister
using System.Globalization;//CultureInfo
using System.Collections;//Arraylist
//using System.Diagnostics;
//using System.Globalization;

using ASCOM.DriverAccess;
using ASCOM.DeviceInterface;
using ASCOM.Utilities;
using ASCOM.Astrometry;
using ASCOM.Astrometry.AstroUtils;

namespace CAO
{
    public class SSTelescope
    {
        public byte MyDriverType;
        public ASCOM.DriverAccess.Telescope MySSTelescope;

        internal static string driverID = "ASCOM.TTelescope.Telescope";
        // TODO Change the descriptive string for your driver then remove this line
        /// <summary>
        /// Driver description that displays in the ASCOM Chooser.
        /// </summary>
        private static string driverDescription = "ASCOM Telescope Driver for TTelescope.";

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
        /// Initializes a new instance of the <see cref="TTelescope"/> class.
        /// Must be public for COM registration.
        /// </summary>
        public SSTelescope(string DriverID, byte DriverType)
        {
            MyDriverType = DriverType;
            if (MyDriverType == 0)
                MySSTelescope = new ASCOM.DriverAccess.Telescope(DriverID);
            else
            {
                tl = new TraceLogger("", "TTelescope");
                //ReadProfile(); // Read device configuration from the ASCOM Profile store

                tl.LogMessage("Telescope", "Starting initialisation");

                connectedState = false; // Initialise connected to false
                utilities = new Util(); //Initialise util object
                astroUtilities = new AstroUtils(); // Initialise astro utilities object
                //TODO: Implement your additional construction here

                tl.LogMessage("Telescope", "Completed initialisation");
            }
        }


        //
        // PUBLIC COM INTERFACE ITelescopeV3 IMPLEMENTATION
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
                MySSTelescope.SetupDialog();
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
                    return MySSTelescope.SupportedActions;
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
                return MySSTelescope.Action(actionName, actionParameters);
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
                MySSTelescope.Dispose();
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
                    return MySSTelescope.Connected;
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
                    MySSTelescope.Connected = value;
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
                    return MySSTelescope.Description;
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
                    return MySSTelescope.DriverInfo;
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
                    return MySSTelescope.DriverVersion;
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
                    return MySSTelescope.InterfaceVersion;
                }
                else
                {
                    LogMessage("InterfaceVersion Get", "3");
                    return Convert.ToInt16("3");
                }
            }
        }

        public string Name
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSTelescope.Name;
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

        #region ITelescope Implementation
        public void AbortSlew()
        {
            if (MyDriverType == 0)
            {
                MySSTelescope.AbortSlew();
            }
            else
            {
                tl.LogMessage("AbortSlew", "Not implemented");
                throw new ASCOM.MethodNotImplementedException("AbortSlew");
            }
        }

        public AlignmentModes AlignmentMode
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSTelescope.AlignmentMode;
                }
                else
                {
                    tl.LogMessage("AlignmentMode Get", "Not implemented");
                    throw new ASCOM.PropertyNotImplementedException("AlignmentMode", false);
                }
            }
        }

        public double Altitude
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSTelescope.Altitude;
                }
                else
                {
                    tl.LogMessage("Altitude", "Not implemented");
                    throw new ASCOM.PropertyNotImplementedException("Altitude", false);
                }
            }
        }

        public double ApertureArea
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSTelescope.ApertureArea;
                }
                else
                {
                    tl.LogMessage("ApertureArea Get", "Not implemented");
                    throw new ASCOM.PropertyNotImplementedException("ApertureArea", false);
                }
            }
        }

        public double ApertureDiameter
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSTelescope.ApertureDiameter;
                }
                else
                {
                    tl.LogMessage("ApertureDiameter Get", "Not implemented");
                    throw new ASCOM.PropertyNotImplementedException("ApertureDiameter", false);
                }
            }
        }

        public bool AtHome
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSTelescope.AtHome;
                }
                else
                {
                    tl.LogMessage("AtHome", "Get - " + false.ToString());
                    return false;
                }
            }
        }

        public bool AtPark
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSTelescope.AtPark;
                }
                else
                {
                    tl.LogMessage("AtPark", "Get - " + false.ToString());
                    return false;
                }
            }
        }

        public IAxisRates AxisRates(TelescopeAxes Axis)
        {
            if (MyDriverType == 0)
            {
                return MySSTelescope.AxisRates(Axis);
            }
            else
            {
                tl.LogMessage("AxisRates", "Get - " + Axis.ToString());
                return new AxisRates(Axis);
            }
        }

        public double Azimuth
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSTelescope.Azimuth;
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
                    return MySSTelescope.CanFindHome;
                }
                else
                {
                    tl.LogMessage("CanFindHome", "Get - " + false.ToString());
                    return false;
                }
            }
        }

        public bool CanMoveAxis(TelescopeAxes Axis)
        {
            if (MyDriverType == 0)
            {
                return MySSTelescope.CanMoveAxis(Axis);
            }
            else
            {
                tl.LogMessage("CanMoveAxis", "Get - " + Axis.ToString());
                switch (Axis)
                {
                    case TelescopeAxes.axisPrimary: return false;
                    case TelescopeAxes.axisSecondary: return false;
                    case TelescopeAxes.axisTertiary: return false;
                    //default: throw new InvalidValueException("CanMoveAxis", Axis.ToString(), "0 to 2");
                    default: return false;
                }
            }
        }

        public bool CanPark
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSTelescope.CanPark;
                }
                else
                {
                    tl.LogMessage("CanPark", "Get - " + false.ToString());
                    return false;
                }
            }
        }

        public bool CanPulseGuide
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSTelescope.CanPulseGuide;
                }
                else
                {
                    tl.LogMessage("CanPulseGuide", "Get - " + false.ToString());
                    return false;
                }
            }
        }

        public bool CanSetDeclinationRate
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSTelescope.CanSetDeclinationRate;
                }
                else
                {
                    tl.LogMessage("CanSetDeclinationRate", "Get - " + false.ToString());
                    return false;
                }
            }
        }

        public bool CanSetGuideRates
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSTelescope.CanSetGuideRates;
                }
                else
                {
                    tl.LogMessage("CanSetGuideRates", "Get - " + false.ToString());
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
                    return MySSTelescope.CanSetPark;
                }
                else
                {
                    tl.LogMessage("CanSetPark", "Get - " + false.ToString());
                    return false;
                }
            }
        }

        public bool CanSetPierSide
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSTelescope.CanSetPierSide;
                }
                else
                {
                    tl.LogMessage("CanSetPierSide", "Get - " + false.ToString());
                    return false;
                }
            }
        }

        public bool CanSetRightAscensionRate
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSTelescope.CanSetRightAscensionRate;
                }
                else
                {
                    tl.LogMessage("CanSetRightAscensionRate", "Get - " + false.ToString());
                    return false;
                }
            }
        }

        public bool CanSetTracking
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSTelescope.CanSetTracking;
                }
                else
                {
                    tl.LogMessage("CanSetTracking", "Get - " + false.ToString());
                    return false;
                }
            }
        }

        public bool CanSlew
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSTelescope.CanSlew;
                }
                else
                {
                    tl.LogMessage("CanSlew", "Get - " + false.ToString());
                    return false;
                }
            }
        }

        public bool CanSlewAltAz
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSTelescope.CanSlewAltAz;
                }
                else
                {
                    tl.LogMessage("CanSlewAltAz", "Get - " + false.ToString());
                    return false;
                }
            }
        }

        public bool CanSlewAltAzAsync
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSTelescope.CanSlewAltAzAsync;
                }
                else
                {
                    tl.LogMessage("CanSlewAltAzAsync", "Get - " + false.ToString());
                    return false;
                }
            }
        }

        public bool CanSlewAsync
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSTelescope.CanSlewAsync;
                }
                else
                {
                    tl.LogMessage("CanSlewAsync", "Get - " + false.ToString());
                    return false;
                }
            }
        }

        public bool CanSync
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSTelescope.CanSync;
                }
                else
                {
                    tl.LogMessage("CanSync", "Get - " + false.ToString());
                    return false;
                }
            }
        }

        public bool CanSyncAltAz
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSTelescope.CanSyncAltAz;
                }
                else
                {
                    tl.LogMessage("CanSyncAltAz", "Get - " + false.ToString());
                    return false;
                }
            }
        }

        public bool CanUnpark
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSTelescope.CanUnpark;
                }
                else
                {
                    tl.LogMessage("CanUnpark", "Get - " + false.ToString());
                    return false;
                }
            }
        }

        public double Declination
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSTelescope.Declination;
                }
                else
                {
                    double declination = 0.0;
                    tl.LogMessage("Declination", "Get - " + utilities.DegreesToDMS(declination, ":", ":"));
                    return declination;
                }
            }
        }

        public double DeclinationRate
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSTelescope.DeclinationRate;
                }
                else
                {
                    double declination = 0.0;
                    tl.LogMessage("DeclinationRate", "Get - " + declination.ToString());
                    return declination;
                }
            }
            set
            {
                if (MyDriverType == 0)
                {
                    MySSTelescope.DeclinationRate = value;
                }
                else
                {
                    tl.LogMessage("DeclinationRate Set", "Not implemented");
                    throw new ASCOM.PropertyNotImplementedException("DeclinationRate", true);
                }
            }
        }

        public PierSide DestinationSideOfPier(double RightAscension, double Declination)
        {
            if (MyDriverType == 0)
            {
                return MySSTelescope.DestinationSideOfPier(RightAscension, Declination);
            }
            else
            {
                tl.LogMessage("DestinationSideOfPier Get", "Not implemented");
                throw new ASCOM.PropertyNotImplementedException("DestinationSideOfPier", false);
            }
        }

        public bool DoesRefraction
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSTelescope.DoesRefraction;
                }
                else
                {
                    tl.LogMessage("DoesRefraction Get", "Not implemented");
                    throw new ASCOM.PropertyNotImplementedException("DoesRefraction", false);
                }
            }
            set
            {
                if (MyDriverType == 0)
                {
                    MySSTelescope.DoesRefraction = value;
                }
                else
                {
                    tl.LogMessage("DoesRefraction Set", "Not implemented");
                    throw new ASCOM.PropertyNotImplementedException("DoesRefraction", true);
                }
            }
        }

        public EquatorialCoordinateType EquatorialSystem
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSTelescope.EquatorialSystem;
                }
                else
                {
                    EquatorialCoordinateType equatorialSystem = EquatorialCoordinateType.equLocalTopocentric;
                    tl.LogMessage("DeclinationRate", "Get - " + equatorialSystem.ToString());
                    return equatorialSystem;
                }
            }
        }

        public void FindHome()
        {
            if (MyDriverType == 0)
            {
                MySSTelescope.FindHome();
            }
            else
            {
                tl.LogMessage("FindHome", "Not implemented");
                throw new ASCOM.MethodNotImplementedException("FindHome");
            }
        }

        public double FocalLength
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSTelescope.FocalLength;
                }
                else
                {
                    tl.LogMessage("FocalLength Get", "Not implemented");
                    throw new ASCOM.PropertyNotImplementedException("FocalLength", false);
                }
            }
        }

        public double GuideRateDeclination
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSTelescope.GuideRateDeclination;
                }
                else
                {
                    tl.LogMessage("GuideRateDeclination Get", "Not implemented");
                    throw new ASCOM.PropertyNotImplementedException("GuideRateDeclination", false);
                }
            }
            set
            {
                if (MyDriverType == 0)
                {
                    MySSTelescope.GuideRateDeclination = value;
                }
                else
                {
                    tl.LogMessage("GuideRateDeclination Set", "Not implemented");
                    throw new ASCOM.PropertyNotImplementedException("GuideRateDeclination", true);
                }
            }
        }

        public double GuideRateRightAscension
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSTelescope.GuideRateRightAscension;
                }
                else
                {
                    tl.LogMessage("GuideRateRightAscension Get", "Not implemented");
                    throw new ASCOM.PropertyNotImplementedException("GuideRateRightAscension", false);
                }
            }
            set
            {
                if (MyDriverType == 0)
                {
                    MySSTelescope.GuideRateRightAscension = value;
                }
                else
                {
                    tl.LogMessage("GuideRateRightAscension Set", "Not implemented");
                    throw new ASCOM.PropertyNotImplementedException("GuideRateRightAscension", true);
                }
            }
        }

        public bool IsPulseGuiding
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSTelescope.IsPulseGuiding;
                }
                else
                {
                    tl.LogMessage("IsPulseGuiding Get", "Not implemented");
                    throw new ASCOM.PropertyNotImplementedException("IsPulseGuiding", false);
                }
            }
        }

        public void MoveAxis(TelescopeAxes Axis, double Rate)
        {
            if (MyDriverType == 0)
            {
                MySSTelescope.MoveAxis(Axis, Rate);
            }
            else
            {
                tl.LogMessage("MoveAxis", "Not implemented");
                throw new ASCOM.MethodNotImplementedException("MoveAxis");
            }
        }

        public void Park()
        {
            if (MyDriverType == 0)
            {
                MySSTelescope.Park();
            }
            else
            {
                tl.LogMessage("Park", "Not implemented");
                throw new ASCOM.MethodNotImplementedException("Park");
            }
        }

        public void PulseGuide(GuideDirections Direction, int Duration)
        {
            if (MyDriverType == 0)
            {
                MySSTelescope.PulseGuide(Direction, Duration);
            }
            else
            {
                tl.LogMessage("PulseGuide", "Not implemented");
                throw new ASCOM.MethodNotImplementedException("PulseGuide");
            }
        }

        public double RightAscension
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSTelescope.RightAscension;
                }
                else
                {
                    double rightAscension = 0.0;
                    tl.LogMessage("RightAscension", "Get - " + utilities.HoursToHMS(rightAscension));
                    return rightAscension;
                }
            }
        }

        public double RightAscensionRate
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSTelescope.RightAscensionRate;
                }
                else
                {
                    double rightAscensionRate = 0.0;
                    tl.LogMessage("RightAscensionRate", "Get - " + rightAscensionRate.ToString());
                    return rightAscensionRate;
                }
            }
            set
            {
                if (MyDriverType == 0)
                {
                    MySSTelescope.RightAscensionRate = value;
                }
                else
                {
                    tl.LogMessage("RightAscensionRate Set", "Not implemented");
                    throw new ASCOM.PropertyNotImplementedException("RightAscensionRate", true);
                }
            }
        }

        public void SetPark()
        {
            if (MyDriverType == 0)
            {
                MySSTelescope.SetPark();
            }
            else
            {
                tl.LogMessage("SetPark", "Not implemented");
                throw new ASCOM.MethodNotImplementedException("SetPark");
            }
        }

        public PierSide SideOfPier
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSTelescope.SideOfPier;
                }
                else
                {
                    tl.LogMessage("SideOfPier Get", "Not implemented");
                    throw new ASCOM.PropertyNotImplementedException("SideOfPier", false);
                }
            }
            set
            {
                if (MyDriverType == 0)
                {
                    MySSTelescope.SideOfPier = value;
                }
                else
                {
                    tl.LogMessage("SideOfPier Set", "Not implemented");
                    throw new ASCOM.PropertyNotImplementedException("SideOfPier", true);
                }
            }
        }

        public double SiderealTime
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSTelescope.SiderealTime;
                }
                else
                {
                    // get greenwich sidereal time: https://en.wikipedia.org/wiki/Sidereal_time
                    //double siderealTime = (18.697374558 + 24.065709824419081 * (utilities.DateUTCToJulian(DateTime.UtcNow) - 2451545.0));

                    // alternative using NOVAS 3.1
                    double siderealTime = 0.0;
                    using (var novas = new ASCOM.Astrometry.NOVAS.NOVAS31())
                    {
                        var jd = utilities.DateUTCToJulian(DateTime.UtcNow);
                        novas.SiderealTime(jd, 0, novas.DeltaT(jd),
                            ASCOM.Astrometry.GstType.GreenwichApparentSiderealTime,
                            ASCOM.Astrometry.Method.EquinoxBased,
                            ASCOM.Astrometry.Accuracy.Reduced, ref siderealTime);
                    }
                    // allow for the longitude
                    siderealTime += SiteLongitude / 360.0 * 24.0;
                    // reduce to the range 0 to 24 hours
                    siderealTime = siderealTime % 24.0;
                    tl.LogMessage("SiderealTime", "Get - " + siderealTime.ToString());
                    return siderealTime;
                }
            }
        }

        public double SiteElevation
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSTelescope.SiteElevation;
                }
                else
                {
                    tl.LogMessage("SiteElevation Get", "Not implemented");
                    throw new ASCOM.PropertyNotImplementedException("SiteElevation", false);
                }
            }
            set
            {
                if (MyDriverType == 0)
                {
                    MySSTelescope.SiteElevation = value;
                }
                else
                {
                    tl.LogMessage("SiteElevation Set", "Not implemented");
                    throw new ASCOM.PropertyNotImplementedException("SiteElevation", true);
                }
            }
        }

        public double SiteLatitude
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSTelescope.SiteLatitude;
                }
                else
                {
                    tl.LogMessage("SiteLatitude Get", "Not implemented");
                    throw new ASCOM.PropertyNotImplementedException("SiteLatitude", false);
                }
            }
            set
            {
                if (MyDriverType == 0)
                {
                    MySSTelescope.SiteLatitude = value;
                }
                else
                {
                    tl.LogMessage("SiteLatitude Set", "Not implemented");
                    throw new ASCOM.PropertyNotImplementedException("SiteLatitude", true);
                }
            }
        }

        public double SiteLongitude
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSTelescope.SiteLongitude;
                }
                else
                {
                    tl.LogMessage("SiteLongitude Get", "Not implemented");
                    throw new ASCOM.PropertyNotImplementedException("SiteLongitude", false);
                }
            }
            set
            {
                if (MyDriverType == 0)
                {
                    MySSTelescope.SiteLongitude = value;
                }
                else
                {
                    tl.LogMessage("SiteLongitude Set", "Not implemented");
                    throw new ASCOM.PropertyNotImplementedException("SiteLongitude", true);
                }
            }
        }

        public short SlewSettleTime
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSTelescope.SlewSettleTime;
                }
                else
                {
                    tl.LogMessage("SlewSettleTime Get", "Not implemented");
                    throw new ASCOM.PropertyNotImplementedException("SlewSettleTime", false);
                }
            }
            set
            {
                if (MyDriverType == 0)
                {
                    MySSTelescope.SlewSettleTime = value;
                }
                else
                {
                    tl.LogMessage("SlewSettleTime Set", "Not implemented");
                    throw new ASCOM.PropertyNotImplementedException("SlewSettleTime", true);
                }
            }
        }

        public void SlewToAltAz(double Azimuth, double Altitude)
        {
            if (MyDriverType == 0)
            {
                MySSTelescope.SlewToAltAz(Azimuth, Altitude);
            }
            else
            {
                tl.LogMessage("SlewToAltAz", "Not implemented");
                throw new ASCOM.MethodNotImplementedException("SlewToAltAz");
            }
        }

        public void SlewToAltAzAsync(double Azimuth, double Altitude)
        {
            if (MyDriverType == 0)
            {
                MySSTelescope.SlewToAltAzAsync(Azimuth, Altitude);
            }
            else
            {
                tl.LogMessage("SlewToAltAzAsync", "Not implemented");
                throw new ASCOM.MethodNotImplementedException("SlewToAltAzAsync");
            }
        }

        public void SlewToCoordinates(double RightAscension, double Declination)
        {
            if (MyDriverType == 0)
            {
                MySSTelescope.SlewToCoordinates(RightAscension, Declination);
            }
            else
            {
                tl.LogMessage("SlewToCoordinates", "Not implemented");
                throw new ASCOM.MethodNotImplementedException("SlewToCoordinates");
            }
        }

        public void SlewToCoordinatesAsync(double RightAscension, double Declination)
        {
            if (MyDriverType == 0)
            {
                MySSTelescope.SlewToCoordinatesAsync(RightAscension, Declination);
            }
            else
            {
                tl.LogMessage("SlewToCoordinatesAsync", "Not implemented");
                throw new ASCOM.MethodNotImplementedException("SlewToCoordinatesAsync");
            }
        }

        public void SlewToTarget()
        {
            if (MyDriverType == 0)
            {
                MySSTelescope.SlewToTarget();
            }
            else
            {
                tl.LogMessage("SlewToTarget", "Not implemented");
                throw new ASCOM.MethodNotImplementedException("SlewToTarget");
            }
        }

        public void SlewToTargetAsync()
        {
            if (MyDriverType == 0)
            {
                MySSTelescope.SlewToTargetAsync();
            }
            else
            {
                tl.LogMessage("SlewToTargetAsync", "Not implemented");
                throw new ASCOM.MethodNotImplementedException("SlewToTargetAsync");
            }
        }

        public bool Slewing
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSTelescope.Slewing;
                }
                else
                {
                    tl.LogMessage("Slewing Get", "Not implemented");
                    throw new ASCOM.PropertyNotImplementedException("Slewing", false);
                }
            }
        }

        public void SyncToAltAz(double Azimuth, double Altitude)
        {
            if (MyDriverType == 0)
            {
                MySSTelescope.SyncToAltAz(Azimuth, Altitude);
            }
            else
            {
                tl.LogMessage("SyncToAltAz", "Not implemented");
                throw new ASCOM.MethodNotImplementedException("SyncToAltAz");
            }
        }

        public void SyncToCoordinates(double RightAscension, double Declination)
        {
            if (MyDriverType == 0)
            {
                MySSTelescope.SyncToCoordinates(RightAscension, Declination);
            }
            else
            {
                tl.LogMessage("SyncToCoordinates", "Not implemented");
                throw new ASCOM.MethodNotImplementedException("SyncToCoordinates");
            }
        }

        public void SyncToTarget()
        {
            if (MyDriverType == 0)
            {
                MySSTelescope.SyncToTarget();
            }
            else
            {
                tl.LogMessage("SyncToTarget", "Not implemented");
                throw new ASCOM.MethodNotImplementedException("SyncToTarget");
            }
        }

        public double TargetDeclination
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSTelescope.TargetDeclination;
                }
                else
                {
                    tl.LogMessage("TargetDeclination Get", "Not implemented");
                    throw new ASCOM.PropertyNotImplementedException("TargetDeclination", false);
                }
            }
            set
            {
                if (MyDriverType == 0)
                {
                    MySSTelescope.TargetDeclination = value;
                }
                else
                {
                    tl.LogMessage("TargetDeclination Set", "Not implemented");
                    throw new ASCOM.PropertyNotImplementedException("TargetDeclination", true);
                }
            }
        }

        public double TargetRightAscension
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSTelescope.TargetRightAscension;
                }
                else
                {
                    tl.LogMessage("TargetRightAscension Get", "Not implemented");
                    throw new ASCOM.PropertyNotImplementedException("TargetRightAscension", false);
                }
            }
            set
            {
                if (MyDriverType == 0)
                {
                    MySSTelescope.TargetRightAscension = value;
                }
                else
                {
                    tl.LogMessage("TargetRightAscension Set", "Not implemented");
                    throw new ASCOM.PropertyNotImplementedException("TargetRightAscension", true);
                }
            }
        }

        public bool Tracking
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSTelescope.Tracking;
                }
                else
                {
                    bool tracking = true;
                    tl.LogMessage("Tracking", "Get - " + tracking.ToString());
                    return tracking;
                }
            }
            set
            {
                if (MyDriverType == 0)
                {
                    MySSTelescope.Tracking = value;
                }
                else
                {
                    tl.LogMessage("Tracking Set", "Not implemented");
                    throw new ASCOM.PropertyNotImplementedException("Tracking", true);
                }
            }
        }

        public DriveRates TrackingRate
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSTelescope.TrackingRate;
                }
                else
                {
                    tl.LogMessage("TrackingRate Get", "Not implemented");
                    throw new ASCOM.PropertyNotImplementedException("TrackingRate", false);
                }
            }
            set
            {
                if (MyDriverType == 0)
                {
                    MySSTelescope.TrackingRate = value;
                }
                else
                {
                    tl.LogMessage("TrackingRate Set", "Not implemented");
                    throw new ASCOM.PropertyNotImplementedException("TrackingRate", true);
                }
            }
        }

        public ITrackingRates TrackingRates
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSTelescope.TrackingRates;
                }
                else
                {
                    ITrackingRates trackingRates = new TrackingRates();
                    tl.LogMessage("TrackingRates", "Get - ");
                    foreach (DriveRates driveRate in trackingRates)
                    {
                        tl.LogMessage("TrackingRates", "Get - " + driveRate.ToString());
                    }
                    return trackingRates;
                }
            }
        }

        public DateTime UTCDate
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSTelescope.UTCDate;
                }
                else
                {
                    DateTime utcDate = DateTime.UtcNow;
                    tl.LogMessage("TrackingRates", "Get - " + String.Format("MM/dd/yy HH:mm:ss", utcDate));
                    return utcDate;
                }
            }
            set
            {
                if (MyDriverType == 0)
                {
                    MySSTelescope.UTCDate = value;
                }
                else
                {
                    tl.LogMessage("UTCDate Set", "Not implemented");
                    throw new ASCOM.PropertyNotImplementedException("UTCDate", true);
                }
            }
        }

        public void Unpark()
        {
            if (MyDriverType == 0)
            {
                MySSTelescope.Unpark();
            }
            else
            {
                tl.LogMessage("Unpark", "Not implemented");
                throw new ASCOM.MethodNotImplementedException("Unpark");
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
                P.DeviceType = "Telescope";
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
                driverProfile.DeviceType = "Telescope";
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
                driverProfile.DeviceType = "Telescope";
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




    public class AxisRates : IAxisRates, IEnumerable
    {
        private TelescopeAxes axis;
        private readonly Rate[] rates;

        //
        // Constructor - Internal prevents public creation
        // of instances. Returned by Telescope.AxisRates.
        //
        internal AxisRates(TelescopeAxes axis)
        {
            this.axis = axis;
            //
            // This collection must hold zero or more Rate objects describing the 
            // rates of motion ranges for the Telescope.MoveAxis() method
            // that are supported by your driver. It is OK to leave this 
            // array empty, indicating that MoveAxis() is not supported.
            //
            // Note that we are constructing a rate array for the axis passed
            // to the constructor. Thus we switch() below, and each case should 
            // initialize the array for the rate for the selected axis.
            //
            switch (axis)
            {
                case TelescopeAxes.axisPrimary:
                    // TODO Initialize this array with any Primary axis rates that your driver may provide
                    // Example: m_Rates = new Rate[] { new Rate(10.5, 30.2), new Rate(54.0, 43.6) }
                    this.rates = new Rate[0];
                    break;
                case TelescopeAxes.axisSecondary:
                    // TODO Initialize this array with any Secondary axis rates that your driver may provide
                    this.rates = new Rate[0];
                    break;
                case TelescopeAxes.axisTertiary:
                    // TODO Initialize this array with any Tertiary axis rates that your driver may provide
                    this.rates = new Rate[0];
                    break;
            }
        }

        #region IAxisRates Members

        public int Count
        {
            get { return this.rates.Length; }
        }

        public void Dispose()
        {
            throw new System.NotImplementedException();
        }

        public IEnumerator GetEnumerator()
        {
            return rates.GetEnumerator();
        }

        public IRate this[int index]
        {
            get { return this.rates[index - 1]; }	// 1-based
        }

        #endregion
    }

    #region TrackingRates
    //
    // TrackingRates is a strongly-typed collection that must be enumerable by
    // both COM and .NET. The ITrackingRates and IEnumerable interfaces provide
    // this polymorphism. 
    //
    // The Guid attribute sets the CLSID for ASCOM.TTelescope.TrackingRates
    // The ClassInterface/None addribute prevents an empty interface called
    // _TrackingRates from being created and used as the [default] interface
    //
    // This class is implemented in this way so that applications based on .NET 3.5
    // will work with this .NET 4.0 object.  Changes to this have proved to be challenging
    // and it is strongly suggested that it isn't changed.
    //
    [Guid("1de9903f-72cd-4062-9b89-0fb9ea64a388")]
    [ClassInterface(ClassInterfaceType.None)]
    [ComVisible(true)]
    public class TrackingRates : ITrackingRates, IEnumerable, IEnumerator
    {
        private readonly DriveRates[] trackingRates;

        // this is used to make the index thread safe
        private readonly ThreadLocal<int> pos = new ThreadLocal<int>(() => { return -1; });
        private static readonly object lockObj = new object();

        //
        // Default constructor - Internal prevents public creation
        // of instances. Returned by Telescope.AxisRates.
        //
        internal TrackingRates()
        {
            //
            // This array must hold ONE or more DriveRates values, indicating
            // the tracking rates supported by your telescope. The one value
            // (tracking rate) that MUST be supported is driveSidereal!
            //
            this.trackingRates = new[] { DriveRates.driveSidereal };
            // TODO Initialize this array with any additional tracking rates that your driver may provide
        }

        #region ITrackingRates Members

        public int Count
        {
            get { return this.trackingRates.Length; }
        }

        public IEnumerator GetEnumerator()
        {
            pos.Value = -1;
            return this as IEnumerator;
        }

        public void Dispose()
        {
            throw new System.NotImplementedException();
        }

        public DriveRates this[int index]
        {
            get { return this.trackingRates[index - 1]; }	// 1-based
        }

        #endregion

        #region IEnumerable members

        public object Current
        {
            get
            {
                lock (lockObj)
                {
                    if (pos.Value < 0 || pos.Value >= trackingRates.Length)
                    {
                        throw new System.InvalidOperationException();
                    }
                    return trackingRates[pos.Value];
                }
            }
        }

        public bool MoveNext()
        {
            lock (lockObj)
            {
                if (++pos.Value >= trackingRates.Length)
                {
                    return false;
                }
                return true;
            }
        }

        public void Reset()
        {
            pos.Value = -1;
        }
        #endregion
    }
    #endregion
}
