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
    public class SSCamera
    {
        /// <summary>
        /// ASCOM DeviceID (COM ProgID) for this driver.
        /// The DeviceID is used by ASCOM applications to load the driver at runtime.
        /// </summary>
        /// 
        public byte MyDriverType;
        public ASCOM.DriverAccess.Camera MySSCamera;

        internal static string driverID = "ASCOM.TCamera.Camera";
        // TODO Change the descriptive string for your driver then remove this line
        /// <summary>
        /// Driver description that displays in the ASCOM Chooser.
        /// </summary>
        private static string driverDescription = "ASCOM Camera Driver for TCamera.";

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
        /// Initializes a new instance of the <see cref="TCamera"/> class.
        /// Must be public for COM registration.
        /// </summary>
        public SSCamera(string DriverID, byte DriverType)
        {
            MyDriverType = DriverType;
            if (MyDriverType == 0)
                MySSCamera = new ASCOM.DriverAccess.Camera(DriverID);
            else
            {
                tl = new TraceLogger("", "TCamera");
                //ReadProfile(); // Read device configuration from the ASCOM Profile store

                tl.LogMessage("Camera", "Starting initialisation");

                connectedState = false; // Initialise connected to false
                utilities = new Util(); //Initialise util object
                astroUtilities = new AstroUtils(); // Initialise astro utilities object
                //TODO: Implement your additional construction here

                tl.LogMessage("Camera", "Completed initialisation");
            }
        }

        //
        // PUBLIC COM INTERFACE ICameraV2 IMPLEMENTATION
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
                MySSCamera.SetupDialog();
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
                    return MySSCamera.SupportedActions;
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
                return MySSCamera.Action(actionName, actionParameters);
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
                MySSCamera.Dispose();
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
                    return MySSCamera.Connected;
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
                    MySSCamera.Connected = value;
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
                    return MySSCamera.Description;
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
                    return MySSCamera.DriverInfo;
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
                    return MySSCamera.DriverVersion;
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
                    return MySSCamera.InterfaceVersion;
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
                    return MySSCamera.Name;
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

        #region ICamera Implementation

        private const int ccdWidth = 1394; // Constants to define the ccd pixel dimenstions
        private const int ccdHeight = 1040;
        private const double pixelSize = 6.45; // Constant for the pixel physical dimension

        private int cameraNumX = ccdWidth; // Initialise variables to hold values required for functionality tested by Conform
        private int cameraNumY = ccdHeight;
        private int cameraStartX = 0;
        private int cameraStartY = 0;
        private DateTime exposureStart = DateTime.MinValue;
        private double cameraLastExposureDuration = 0.0;
        private bool cameraImageReady = false;
        private int[,] cameraImageArray;
        private object[,] cameraImageArrayVariant;

        public void AbortExposure()
        {

            if (MyDriverType == 0)
            {
                MySSCamera.AbortExposure();
            }
            else
            {
                tl.LogMessage("AbortExposure", "Not implemented");
                throw new MethodNotImplementedException("AbortExposure");
            }
        }

        public short BayerOffsetX
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSCamera.BayerOffsetX;
                }
                else
                {
                    tl.LogMessage("BayerOffsetX Get Get", "Not implemented");
                    throw new ASCOM.PropertyNotImplementedException("BayerOffsetX", false);
                }
            }
        }

        public short BayerOffsetY
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSCamera.BayerOffsetY;
                }
                else
                {
                    tl.LogMessage("BayerOffsetY Get Get", "Not implemented");
                    throw new ASCOM.PropertyNotImplementedException("BayerOffsetX", true);
                }
            }
        }

        public short BinX
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSCamera.BinX;
                }
                else
                {
                    tl.LogMessage("BinX Get", "1");
                    return 1;
                }
            }
            set
            {
                if (MyDriverType == 0)
                {
                    MySSCamera.BinX = value;
                }
                else
                {
                    tl.LogMessage("BinX Set", value.ToString());
                    if (value != 1) throw new ASCOM.InvalidValueException("BinX", value.ToString(), "1"); // Only 1 is valid in this simple template
                }
            }
        }

        public short BinY
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSCamera.BinY;
                }
                else
                {
                    tl.LogMessage("BinY Get", "1");
                    return 1;
                }
            }
            set
            {
                if (MyDriverType == 0)
                {
                    MySSCamera.BinY = value;
                }
                else
                {
                    tl.LogMessage("BinY Set", value.ToString());
                    if (value != 1) throw new ASCOM.InvalidValueException("BinY", value.ToString(), "1"); // Only 1 is valid in this simple template
                }
            }
        }

        public double CCDTemperature
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSCamera.CCDTemperature;
                }
                else
                {
                    tl.LogMessage("CCDTemperature Get Get", "Not implemented");
                    throw new ASCOM.PropertyNotImplementedException("CCDTemperature", false);
                }
            }
        }

        public CameraStates CameraState
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSCamera.CameraState;
                }
                else
                {
                    tl.LogMessage("CameraState Get", CameraStates.cameraIdle.ToString());
                    return CameraStates.cameraIdle;
                }
            }
        }

        public int CameraXSize
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSCamera.CameraXSize;
                }
                else
                {
                    tl.LogMessage("CameraXSize Get", ccdWidth.ToString());
                    return ccdWidth;
                }
            }
        }

        public int CameraYSize
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSCamera.CameraYSize;
                }
                else
                {
                    tl.LogMessage("CameraYSize Get", ccdHeight.ToString());
                    return ccdHeight;
                }
            }
        }

        public bool CanAbortExposure
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSCamera.CanAbortExposure;
                }
                else
                {
                    tl.LogMessage("CanAbortExposure Get", false.ToString());
                    return false;
                }
            }
        }

        public bool CanAsymmetricBin
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSCamera.CanAsymmetricBin;
                }
                else
                {
                    tl.LogMessage("CanAsymmetricBin Get", false.ToString());
                    return false;
                }
            }
        }

        public bool CanFastReadout
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSCamera.CanFastReadout;
                }
                else
                {
                    tl.LogMessage("CanFastReadout Get", false.ToString());
                    return false;
                }
            }
        }

        public bool CanGetCoolerPower
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSCamera.CanGetCoolerPower;
                }
                else
                {
                    tl.LogMessage("CanGetCoolerPower Get", false.ToString());
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
                    return MySSCamera.CanPulseGuide;
                }
                else
                {
                    tl.LogMessage("CanPulseGuide Get", false.ToString());
                    return false;
                }
            }
        }

        public bool CanSetCCDTemperature
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSCamera.CanSetCCDTemperature;
                }
                else
                {
                    tl.LogMessage("CanSetCCDTemperature Get", false.ToString());
                    return false;
                }
            }
        }

        public bool CanStopExposure
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSCamera.CanStopExposure;
                }
                else
                {
                    tl.LogMessage("CanStopExposure Get", false.ToString());
                    return false;
                }
            }
        }

        public bool CoolerOn
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSCamera.CoolerOn;
                }
                else
                {
                    tl.LogMessage("CoolerOn Get Get", "Not implemented");
                    throw new ASCOM.PropertyNotImplementedException("CoolerOn", false);
                }
            }
            set
            {
                if (MyDriverType == 0)
                {
                    MySSCamera.CoolerOn = value;
                }
                else
                {
                    tl.LogMessage("CoolerOn Set Get", "Not implemented");
                    throw new ASCOM.PropertyNotImplementedException("CoolerOn", true);
                }
            }
        }

        public double CoolerPower
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSCamera.CoolerPower;
                }
                else
                {
                    tl.LogMessage("CoolerPower Get Get", "Not implemented");
                    throw new ASCOM.PropertyNotImplementedException("CoolerPower", false);
                }
            }
        }

        public double ElectronsPerADU
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSCamera.ElectronsPerADU;
                }
                else
                {
                    tl.LogMessage("ElectronsPerADU Get Get", "Not implemented");
                    throw new ASCOM.PropertyNotImplementedException("ElectronsPerADU", false);
                }
            }
        }

        public double ExposureMax
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSCamera.ExposureMax;
                }
                else
                {
                    tl.LogMessage("ExposureMax Get Get", "Not implemented");
                    throw new ASCOM.PropertyNotImplementedException("ExposureMax", false);
                }
            }
        }

        public double ExposureMin
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSCamera.ExposureMin;
                }
                else
                {
                    tl.LogMessage("ExposureMin Get", "Not implemented");
                    throw new ASCOM.PropertyNotImplementedException("ExposureMin", false);
                }
            }
        }

        public double ExposureResolution
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSCamera.ExposureResolution;
                }
                else
                {
                    tl.LogMessage("ExposureResolution Get", "Not implemented");
                    throw new ASCOM.PropertyNotImplementedException("ExposureResolution", false);
                }
            }
        }

        public bool FastReadout
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSCamera.FastReadout;
                }
                else
                {
                    tl.LogMessage("FastReadout Get", "Not implemented");
                    throw new ASCOM.PropertyNotImplementedException("FastReadout", false);
                }
            }
            set
            {
                if (MyDriverType == 0)
                {
                    MySSCamera.FastReadout=value;
                }
                else
                {
                    tl.LogMessage("FastReadout Set", "Not implemented");
                    throw new ASCOM.PropertyNotImplementedException("FastReadout", true);
                }
            }
        }

        public double FullWellCapacity
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSCamera.FullWellCapacity;
                }
                else
                {
                    tl.LogMessage("FullWellCapacity Get", "Not implemented");
                    throw new ASCOM.PropertyNotImplementedException("FullWellCapacity", false);
                }
            }
        }

        public short Gain
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSCamera.Gain;
                }
                else
                {
                    tl.LogMessage("Gain Get", "Not implemented");
                    throw new ASCOM.PropertyNotImplementedException("Gain", false);
                }
            }
            set
            {
                if (MyDriverType == 0)
                {
                    MySSCamera.Gain = value;
                }
                else
                {
                    tl.LogMessage("Gain Set", "Not implemented");
                    throw new ASCOM.PropertyNotImplementedException("Gain", true);
                }
            }
        }

        public short GainMax
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSCamera.GainMax;
                }
                else
                {
                    tl.LogMessage("GainMax Get", "Not implemented");
                    throw new ASCOM.PropertyNotImplementedException("GainMax", false);
                }
            }
        }

        public short GainMin
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSCamera.GainMin;
                }
                else
                {
                    tl.LogMessage("GainMin Get", "Not implemented");
                    throw new ASCOM.PropertyNotImplementedException("GainMin", true);
                }
            }
        }

        public ArrayList Gains
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSCamera.Gains;
                }
                else
                {
                    tl.LogMessage("Gains Get", "Not implemented");
                    throw new ASCOM.PropertyNotImplementedException("Gains", true);
                }
            }
        }

        public bool HasShutter
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSCamera.HasShutter;
                }
                else
                {
                    tl.LogMessage("HasShutter Get", false.ToString());
                    return false;
                }
            }
        }

        public double HeatSinkTemperature
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSCamera.HeatSinkTemperature;
                }
                else
                {
                    tl.LogMessage("HeatSinkTemperature Get", "Not implemented");
                    throw new ASCOM.PropertyNotImplementedException("HeatSinkTemperature", false);
                }
            }
        }

        public object ImageArray
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSCamera.ImageArray;
                }
                else
                {
                    if (!cameraImageReady)
                    {
                        tl.LogMessage("ImageArray Get", "Throwing InvalidOperationException because of a call to ImageArray before the first image has been taken!");
                        throw new ASCOM.InvalidOperationException("Call to ImageArray before the first image has been taken!");
                    }

                    cameraImageArray = new int[cameraNumX, cameraNumY];
                    return cameraImageArray;
                }
            }
        }

        public object ImageArrayVariant
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSCamera.ImageArrayVariant;
                }
                else
                {
                    if (!cameraImageReady)
                    {
                        tl.LogMessage("ImageArrayVariant Get", "Throwing InvalidOperationException because of a call to ImageArrayVariant before the first image has been taken!");
                        throw new ASCOM.InvalidOperationException("Call to ImageArrayVariant before the first image has been taken!");
                    }
                    cameraImageArrayVariant = new object[cameraNumX, cameraNumY];
                    for (int i = 0; i < cameraImageArray.GetLength(1); i++)
                    {
                        for (int j = 0; j < cameraImageArray.GetLength(0); j++)
                        {
                            cameraImageArrayVariant[j, i] = cameraImageArray[j, i];
                        }

                    }

                    return cameraImageArrayVariant;
                }
            }
        }

        public bool ImageReady
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSCamera.ImageReady;
                }
                else
                {
                    tl.LogMessage("ImageReady Get", cameraImageReady.ToString());
                    return cameraImageReady;
                }
            }
        }

        public bool IsPulseGuiding
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSCamera.IsPulseGuiding;
                }
                else
                {
                    tl.LogMessage("IsPulseGuiding Get", "Not implemented");
                    throw new ASCOM.PropertyNotImplementedException("IsPulseGuiding", false);
                }
            }
        }

        public double LastExposureDuration
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSCamera.LastExposureDuration;
                }
                else
                {
                    if (!cameraImageReady)
                    {
                        tl.LogMessage("LastExposureDuration Get", "Throwing InvalidOperationException because of a call to LastExposureDuration before the first image has been taken!");
                        throw new ASCOM.InvalidOperationException("Call to LastExposureDuration before the first image has been taken!");
                    }
                    tl.LogMessage("LastExposureDuration Get", cameraLastExposureDuration.ToString());
                    return cameraLastExposureDuration;
                }
            }
        }

        public string LastExposureStartTime
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSCamera.LastExposureStartTime;
                }
                else
                {
                    if (!cameraImageReady)
                    {
                        tl.LogMessage("LastExposureStartTime Get", "Throwing InvalidOperationException because of a call to LastExposureStartTime before the first image has been taken!");
                        throw new ASCOM.InvalidOperationException("Call to LastExposureStartTime before the first image has been taken!");
                    }
                    string exposureStartString = exposureStart.ToString("yyyy-MM-ddTHH:mm:ss");
                    tl.LogMessage("LastExposureStartTime Get", exposureStartString.ToString());
                    return exposureStartString;
                }
            }
        }

        public int MaxADU
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSCamera.MaxADU;
                }
                else
                {
                    tl.LogMessage("MaxADU Get", "20000");
                    return 20000;
                }
            }
        }

        public short MaxBinX
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSCamera.MaxBinX;
                }
                else
                {
                    tl.LogMessage("MaxBinX Get", "1");
                    return 1;
                }
            }
        }

        public short MaxBinY
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSCamera.MaxBinY;
                }
                else
                {
                    tl.LogMessage("MaxBinY Get", "1");
                    return 1;
                }
            }
        }

        public int NumX
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSCamera.NumX;
                }
                else
                {
                    tl.LogMessage("NumX Get", cameraNumX.ToString());
                    return cameraNumX;
                }
            }
            set
            {
                if (MyDriverType == 0)
                {
                    MySSCamera.NumX = value;
                }
                else
                {
                    cameraNumX = value;
                    tl.LogMessage("NumX set", value.ToString());
                }
            }
        }

        public int NumY
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSCamera.NumY;
                }
                else
                {
                    tl.LogMessage("NumY Get", cameraNumY.ToString());
                    return cameraNumY;
                }
            }
            set
            {
                if (MyDriverType == 0)
                {
                    MySSCamera.NumY=value;
                }
                else
                {
                    cameraNumY = value;
                    tl.LogMessage("NumY set", value.ToString());
                }
            }
        }

        public short PercentCompleted
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSCamera.PercentCompleted;
                }
                else
                {
                    tl.LogMessage("PercentCompleted Get", "Not implemented");
                    throw new ASCOM.PropertyNotImplementedException("PercentCompleted", false);
                }
            }
        }

        public double PixelSizeX
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSCamera.PixelSizeX;
                }
                else
                {
                    tl.LogMessage("PixelSizeX Get", pixelSize.ToString());
                    return pixelSize;
                }
            }
        }

        public double PixelSizeY
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSCamera.PixelSizeY;
                }
                else
                {
                    tl.LogMessage("PixelSizeY Get", pixelSize.ToString());
                    return pixelSize;
                }
            }
        }

        public void PulseGuide(GuideDirections Direction, int Duration)
        {
            if (MyDriverType == 0)
            {
                MySSCamera.PulseGuide(Direction, Duration);
            }
            else
            {
                tl.LogMessage("PulseGuide", "Not implemented");
                throw new ASCOM.MethodNotImplementedException("PulseGuide");
            }
        }

        public short ReadoutMode
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSCamera.ReadoutMode;
                }
                else
                {
                    tl.LogMessage("ReadoutMode Get", "Not implemented");
                    throw new ASCOM.PropertyNotImplementedException("ReadoutMode", false);
                }
            }
            set
            {
                if (MyDriverType == 0)
                {
                    MySSCamera.ReadoutMode = value;
                }
                else
                {
                    tl.LogMessage("ReadoutMode Set", "Not implemented");
                    throw new ASCOM.PropertyNotImplementedException("ReadoutMode", true);
                }
            }
        }

        public ArrayList ReadoutModes
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSCamera.ReadoutModes;
                }
                else
                {
                    tl.LogMessage("ReadoutModes Get", "Not implemented");
                    throw new ASCOM.PropertyNotImplementedException("ReadoutModes", false);
                }
            }
        }

        public string SensorName
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSCamera.SensorName;
                }
                else
                {
                    tl.LogMessage("SensorName Get", "Not implemented");
                    throw new ASCOM.PropertyNotImplementedException("SensorName", false);
                }
            }
        }

        public SensorType SensorType
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSCamera.SensorType;
                }
                else
                {
                    tl.LogMessage("SensorType Get", "Not implemented");
                    throw new ASCOM.PropertyNotImplementedException("SensorType", false);
                }
            }
        }

        public double SetCCDTemperature
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSCamera.SetCCDTemperature;
                }
                else
                {
                    tl.LogMessage("SetCCDTemperature Get", "Not implemented");
                    throw new ASCOM.PropertyNotImplementedException("SetCCDTemperature", false);
                }
            }
            set
            {
                if (MyDriverType == 0)
                {
                    MySSCamera.SetCCDTemperature = value;
                }
                else
                {
                    tl.LogMessage("SetCCDTemperature Set", "Not implemented");
                    throw new ASCOM.PropertyNotImplementedException("SetCCDTemperature", true);
                }
            }
        }

        public void StartExposure(double Duration, bool Light)
        {
            if (MyDriverType == 0)
            {
                MySSCamera.StartExposure(Duration, Light);
            }
            else
            {
                if (Duration < 0.0) throw new InvalidValueException("StartExposure", Duration.ToString(), "0.0 upwards");
                if (cameraNumX > ccdWidth) throw new InvalidValueException("StartExposure", cameraNumX.ToString(), ccdWidth.ToString());
                if (cameraNumY > ccdHeight) throw new InvalidValueException("StartExposure", cameraNumY.ToString(), ccdHeight.ToString());
                if (cameraStartX > ccdWidth) throw new InvalidValueException("StartExposure", cameraStartX.ToString(), ccdWidth.ToString());
                if (cameraStartY > ccdHeight) throw new InvalidValueException("StartExposure", cameraStartY.ToString(), ccdHeight.ToString());

                cameraLastExposureDuration = Duration;
                exposureStart = DateTime.Now;
                System.Threading.Thread.Sleep((int)Duration * 1000);  // Sleep for the duration to simulate exposure 
                tl.LogMessage("StartExposure", Duration.ToString() + " " + Light.ToString());
                cameraImageReady = true;
            }
        }

        public int StartX
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSCamera.StartX;
                }
                else
                {
                    tl.LogMessage("StartX Get", cameraStartX.ToString());
                    return cameraStartX;
                }
            }
            set
            {
                if (MyDriverType == 0)
                {
                    MySSCamera.StartX = value;
                }
                else
                {
                    cameraStartX = value;
                    tl.LogMessage("StartX Set", value.ToString());
                }
            }
        }

        public int StartY
        {
            get
            {
                if (MyDriverType == 0)
                {
                    return MySSCamera.StartY;
                }
                else
                {
                    tl.LogMessage("StartY Get", cameraStartY.ToString());
                    return cameraStartY;
                }
            }
            set
            {
                if (MyDriverType == 0)
                {
                    MySSCamera.StartY = value;
                }
                else
                {
                    cameraStartY = value;
                    tl.LogMessage("StartY set", value.ToString());
                }
            }
        }

        public void StopExposure()
        {
            if (MyDriverType == 0)
            {
                MySSCamera.StopExposure();
            }
            else
            {
                tl.LogMessage("StopExposure", "Not implemented");
                throw new MethodNotImplementedException("StopExposure");
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
                P.DeviceType = "Camera";
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
                driverProfile.DeviceType = "Camera";
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
                driverProfile.DeviceType = "Camera";
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

        #region User properties and methods(graycode)
        //Camera曝光，根据Frame分别曝光Light，Bias，Dark，Flat
        public void CameraExpose(byte Frame, double Duration)
        {
            switch (Frame)
            {
                case 0://Light
                    {
                        StartExposure(Duration, true);
                        break;
                    }
                case 1://Flat
                    {
                        StartExposure(Duration, true);
                        
                        break;
                    }
                case 2://Bias
                    {
                        StartExposure(0, false);
                        break;
                    }
                case 3://Dark
                    {
                        StartExposure(Duration, false);
                        break;
                    }
            }
        }
        #endregion
    }
}
