//tabs=4
// --------------------------------------------------------------------------------
// TODO fill in this information for your driver, then remove this line!
//
// ASCOM Dome driver for ADIMM
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
using System.Text;
using System.Runtime.InteropServices;

using ASCOM;
using ASCOM.Astrometry;
using ASCOM.Astrometry.AstroUtils;
using ASCOM.Utilities;
using ASCOM.DeviceInterface;
using System.Globalization;
using System.Collections;
using System.Net;
using System.Net.Sockets;
using System.Windows.Forms;

namespace ASCOM.ADIMM
{
    //
    // Your driver's DeviceID is ASCOM.ADIMM.Dome
    //
    // The Guid attribute sets the CLSID for ASCOM.ADIMM.Dome
    // The ClassInterface/None addribute prevents an empty interface called
    // _ADIMM from being created and used as the [default] interface
    //
    // TODO Replace the not implemented exceptions with code to implement the function or
    // throw the appropriate ASCOM exception.
    //

    /// <summary>
    /// ASCOM Dome Driver for ADIMM.
    /// </summary>
    [Guid("0304112d-e2e0-437a-876d-b0df6efd60ee")]
    [ClassInterface(ClassInterfaceType.None)]
    public class Dome : IDomeV2
    {
        /// <summary>
        /// ASCOM DeviceID (COM ProgID) for this driver.
        /// The DeviceID is used by ASCOM applications to load the driver at runtime.
        /// </summary>
        internal static string driverID = "ASCOM.ADIMM.Dome";
        // TODO Change the descriptive string for your driver then remove this line
        /// <summary>
        /// Driver description that displays in the ASCOM Chooser.
        /// </summary>
        private static string driverDescription = "ASCOM Dome Driver for ADIMM.";

        internal static string ProfileName_IP = "ADIMM IP"; // Constants used for Profile persistence
        internal static string Default_IP = "192.168.1.168";
        internal static string ProfileName_Port = "ADIMM Port"; // Constants used for Profile persistence
        internal static string Default_Port = "8888";
        internal static string traceStateProfileName = "Trace Level";
        internal static string traceStateDefault = "false";

        internal static string ADIMM_IP; // Variables to hold the currrent device configuration
        internal static string ADIMM_Port; // Variables to hold the currrent device configuration
        internal static bool traceState;

        //*********************************
        //Modbus
        //*********************************
        private Socket sk;
        private IPEndPoint iep;
        //private Zelio zelioDome;
        private Int16 transId;
        private Byte unitId;
        //*********************************
        //Zelio
        //*********************************
        /* 
         * Driver for Zelio dome controll.
         * Copyright (C) 2008-2010 Petr Kubanek <petr@kubanek.net>
         *
         * This program is free software; you can redistribute it and/or
         * modify it under the terms of the GNU General Public License
         * as published by the Free Software Foundation; either version 2
         * of the License, or (at your option) any later version.
         *
         * This program is distributed in the hope that it will be useful,
         * but WITHOUT ANY WARRANTY; without even the implied warranty of
         * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
         * GNU General Public License for more details.
         *
         * You should have received a copy of the GNU General Public License
         * along with this program; if not, write to the Free Software
         * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
         */

        //private const UInt16 EVENT_DEADBUT=RTS2_LOCAL_EVENT + 1350;

        // Zelio registers

        private const UInt16 ZREG_J1XT1 = 16;
        private const UInt16 ZREG_J2XT1 = 17;
        private const UInt16 ZREG_J3XT1 = 18;
        private const UInt16 ZREG_J4XT1 = 19;

        private const UInt16 ZREG_O1XT1 = 20;
        private const UInt16 ZREG_O2XT1 = 21;
        private const UInt16 ZREG_O3XT1 = 22;
        private const UInt16 ZREG_O4XT1 = 23;

        // bite mask for O1 and O2 registers
        private const UInt16 ZO_EP_OPEN = 0x0004;
        private const UInt16 ZO_EP_CLOSE = 0x0008;
        private const UInt16 ZO_STATE_OPEN = 0x0020;
        private const UInt16 ZO_STATE_CLOSE = 0x0040;
        private const UInt16 ZO_TIMEO_CLOSE = 0x0080;
        private const UInt16 ZO_TIMEO_OPEN = 0x0100;
        private const UInt16 ZO_MOT_OPEN = 0x0200;
        private const UInt16 ZO_MOT_CLOSE = 0x0400;
        private const UInt16 ZO_BLOCK_OPEN = 0x0800;
        private const UInt16 ZO_BLOCK_CLOSE = 0x1000;

        // bite mask for state register
        private const UInt16 ZS_SW_AUTO = 0x0001;
        private const UInt16 ZS_SW_OPENCLOSE = 0x0002;
        private const UInt16 ZS_TIMEOUT = 0x0004;
        private const UInt16 ZS_POWER = 0x0008;
        private const UInt16 ZS_RAIN = 0x0010;
        private const UInt16 ZS_COMP_RUN = 0x0020;
        // does not have rain signal
        private const UInt16 ZS_WITHOUT_RAIN = 0x0040;
        private const UInt16 ZS_3RELAYS = 0x0080;
        private const UInt16 ZS_HUMIDITY = 0x0100;
        private const UInt16 ZS_FRAM = 0x0200;
        private const UInt16 ZS_SIMPLE = 0x0400;
        private const UInt16 ZS_COMPRESSOR = 0x0800;
        private const UInt16 ZS_WEATHER = 0x1000;
        private const UInt16 ZS_OPENING_IGNR = 0x2000;
        private const UInt16 ZS_EMERGENCY_B = 0x4000;
        private const UInt16 ZS_DEADMAN = 0x8000;

        // dead man timeout
        private const UInt16 ZI_DEADMAN_MASK = 0x007f;
        // emergency button reset
        private const UInt16 ZI_EMMERGENCY_R = 0x2000;
        // bit for Q9 - remote switch
        private const UInt16 ZI_Q9 = 0x4000;

        private const UInt16 ZI_FRAM_Q8 = 0x0100;
        private const UInt16 ZI_FRAM_Q9 = 0x0200;
        private const UInt16 ZI_FRAM_QA = 0x0400;

        // bit mask for rain ignore
        private const UInt16 ZI_IGNORE_RAIN = 0x8000;

        //private const UInt16 OPT_BATTERY     = OPT_LOCAL + 501;
        //private const UInt16 OPT_Q8_NAME     = OPT_LOCAL + 502;
        //private const UInt16 OPT_Q9_NAME     = OPT_LOCAL + 503;
        //private const UInt16 OPT_QA_NAME     = OPT_LOCAL + 504;
        enum zelioModeltype : byte { ZELIO_UNKNOW, ZELIO_BOOTES3_WOUTPLUGS, ZELIO_BOOTES3, ZELIO_COMPRESSOR_WOUTPLUGS, ZELIO_COMPRESSOR, ZELIO_SIMPLE, ZELIO_FRAM };
        /**
         * Driver for Bootes IR dome.
         *
         * @author Petr Kubanek <petr@kubanek.net>
         */
        //UInt16 deadManNum = 0;
        //Modbus zelioMudbus = new Modbus();
        zelioModeltype zelioModel = new zelioModeltype();
        //bool haveRainSignal,haveBatteryLevel,haveHumidityOutput;
        //public Zelio (int argc, char **argv):Dome (argc, argv)
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
        /// Private variable to hold the trace logger object (creates a diagnostic log file with information that you specify)
        /// </summary>
        private TraceLogger tl;

        /// <summary>
        /// Initializes a new instance of the <see cref="ADIMM"/> class.
        /// Must be public for COM registration.
        /// </summary>
        public Dome()
        {
            ReadProfile(); // Read device configuration from the ASCOM Profile store

            tl = new TraceLogger("", "ADIMM");
            tl.Enabled = traceState;
            tl.LogMessage("Dome", "Starting initialisation");

            sk = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            iep = new IPEndPoint(IPAddress.Parse(ADIMM_IP), Convert.ToInt32(ADIMM_Port));
            connZelio();
            
            connectedState = false; // Initialise connected to false
            utilities = new Util(); //Initialise util object
            astroUtilities = new AstroUtils(); // Initialise astro utilities object
            //TODO: Implement your additional construction here
            //zelioDome = new Zelio();
            transId = 1;
            unitId = 0;
            zelioModel = zelioModeltype.ZELIO_UNKNOW;
            //haveRainSignal = false;
            //haveBatteryLevel = false;
            //haveHumidityOutput = false;
            init();

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
            throw new ASCOM.ActionNotImplementedException("Action " + actionName + " is not implemented by this driver");
        }

        public void CommandBlind(string command, bool raw)
        {
            CheckConnected("CommandBlind");
            // Call CommandString and return as soon as it finishes
            this.CommandString(command, raw);
            // or
            throw new ASCOM.MethodNotImplementedException("CommandBlind");
        }

        public bool CommandBool(string command, bool raw)
        {
            CheckConnected("CommandBool");
            string ret = CommandString(command, raw);
            // TODO decode the return string and return true or false
            // or
            throw new ASCOM.MethodNotImplementedException("CommandBool");
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
                tl.LogMessage("Connected Get", IsConnected.ToString());
                return IsConnected;
            }
            set
            {
                tl.LogMessage("Connected Set", value.ToString());
                if (value == IsConnected)
                    return;

                if (value)
                {
                    connectedState = true;
                    tl.LogMessage("Connected Set", "Connecting to port " + ADIMM_IP);
                    // TODO connect to the device
                }
                else
                {
                    connectedState = false;
                    tl.LogMessage("Connected Set", "Disconnecting from port " + ADIMM_IP);
                    // TODO disconnect from the device
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
                tl.LogMessage("InterfaceVersion Get", "2");
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
            tl.LogMessage("AbortSlew", "Completed");
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
                tl.LogMessage("AtPark Get", "Not implemented");
                throw new ASCOM.PropertyNotImplementedException("AtPark", false);
            }
        }

        public double Azimuth
        {
            get
            {
                tl.LogMessage("Azimuth Get", "Not implemented");
                throw new ASCOM.PropertyNotImplementedException("Azimuth", false);
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
                return false;
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
                return false;
            }
        }

        public bool CanSetPark
        {
            get
            {
                tl.LogMessage("CanSetPark Get", false.ToString());
                return false;
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
                return false;
            }
        }

        public bool CanSyncAzimuth
        {
            get
            {
                tl.LogMessage("CanSyncAzimuth Get", false.ToString());
                return false;
            }
        }

        public void CloseShutter()
        {
            //tl.LogMessage("CloseShutter", "Shutter has been closed");
            //domeShutterState = false;
            startClose();
            domeShutterState = false;
        }

        public void FindHome()
        {
            tl.LogMessage("FindHome", "Not implemented");
            throw new ASCOM.MethodNotImplementedException("FindHome");
        }

        public void OpenShutter()
        {
            //tl.LogMessage("OpenShutter", "Shutter has been opened");
            //domeShutterState = true;
            startOpen();
            domeShutterState = true;
        }

        public void Park()
        {
            tl.LogMessage("Park", "Not implemented");
            throw new ASCOM.MethodNotImplementedException("Park");
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
                tl.LogMessage("CanSyncAzimuth Get", false.ToString());
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

        public bool Slaved
        {
            get
            {
                tl.LogMessage("Slaved Get", false.ToString());
                return false;
            }
            set
            {
                tl.LogMessage("Slaved Set", "not implemented");
                throw new ASCOM.PropertyNotImplementedException("Slaved", true);
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
            throw new ASCOM.MethodNotImplementedException("SlewToAzimuth");
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
        internal void ReadProfile()
        {
            using (Profile driverProfile = new Profile())
            {
                driverProfile.DeviceType = "Dome";
                traceState = Convert.ToBoolean(driverProfile.GetValue(driverID, traceStateProfileName, string.Empty, traceStateDefault));
                ADIMM_IP = driverProfile.GetValue(driverID, ProfileName_IP, string.Empty, Default_IP);
                ADIMM_Port = driverProfile.GetValue(driverID, ProfileName_Port, string.Empty, Default_Port);
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
                driverProfile.WriteValue(driverID, traceStateProfileName, traceState.ToString());
                driverProfile.WriteValue(driverID, ProfileName_IP, ADIMM_IP.ToString());
                driverProfile.WriteValue(driverID, ProfileName_Port, ADIMM_Port.ToString());
            }

        }

        #endregion

        //*********************************
        //Modbus
        //*********************************
        //连接
        public void connZelio()
        {
            //建立网络连接
            iep = new IPEndPoint(IPAddress.Parse(ADIMM_IP), Convert.ToInt32(ADIMM_Port));
            sk = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            try
            {
                sk.Connect(iep);
            }
            catch (SocketException sex)
            {
                MessageBox.Show(sex.ToString());
            }
        }
        //断开
        public void disconZelio()
        {
            try
            {
                sk.Disconnect(true);
            }
            catch (SocketException sex)
            {
                MessageBox.Show(sex.ToString());
            }
        }
        //发送数据
        public void sendData(Byte[] data, UInt16 size)
        {
            try
            {
                sk.Send(data, size, SocketFlags.None);
            }
            catch (SocketException sex)
            {
                MessageBox.Show(sex.ToString());
            }
        }
        //接收数据
        public void receiveData(ref Byte[] data, UInt16 size, UInt16 wtime)
        {
            sk.ReceiveTimeout = wtime;
            try
            {
                //sk.Receive(data, size, SocketFlags.None);
                sk.Receive(data, size, SocketFlags.None);

            }
            catch (SocketException sex)
            {
                MessageBox.Show(sex.ToString());
            }
        }
        /**
		 * Call Modbus function.
		 *
		 * @param func       Function index.
		 * @param data       Function data.
		 * @param data_size  Size of input data.
		 * @param reply      Data returned from function call.
		 * @param reply_size Size of return data.
		 *
		 * @throw ConnError if connection error occured.
		 */
        //void ConnModbus::callFunction (char func, const void *data, size_t data_size, void *reply, size_t reply_size)
        public void callFunction (Byte func, Byte[] data, UInt16 data_size, ref Byte[] reply, UInt16 reply_size)
        {
	        //char send_data[8 + data_size];
            Byte[] send_data=new Byte[data_size+8];
	        // fill header
	        //*((uint16_t *) send_data) = htons (transId);
            Byte[] t1=BitConverter.GetBytes(transId);
            t1.CopyTo(send_data,0);
	        send_data[2] = 0;
	        send_data[3] = 0;
	        //*((uint16_t *) (send_data + 4)) = htons (data_size + 2);
            Byte[] t2=BitConverter.GetBytes((UInt16)(data_size + 2));
            t2.CopyTo(send_data,4);
	        send_data[6] = unitId;
	        send_data[7] = func;
	        //bcopy (data, send_data + 8, data_size);
            data.CopyTo(send_data,8);
	        data_size += 8;
	        try
	        {
		        sendData (send_data, data_size);
		        reply_size += 8;
		        //char reply_data[reply_size];
                Byte[] reply_data=new Byte[reply_size];
                receiveData(ref reply_data, reply_size, 50);
                /*
		        if (reply_data[7] & 0x80)
		        {
			        std::ostringstream _os;
			        _os << "Error executiong function " << func 
				        << " error code is: 0x" << std::hex << (int) reply_data[8];
			        throw ModbusError (this, _os.str ().c_str ());
		        }
		        else if (reply_data[7] != func)
		        {
		  	        std::ostringstream _os;
			        _os << "Invalid reply from modbus read, reply function is 0x" << std::hex << (int) reply_data[7]
				        << ", expected 0x" << std::hex << (int) func;
			        throw ModbusError (this, _os.str ().c_str ());
		        }
		        bcopy (reply_data + 8, reply, reply_size - 8);
		        transId++;
                */
                if (((reply_data[7] & 0x80) != 0) && (reply_data[7] == func))
                {
                    reply=new Byte[reply_size - 8];
                    Array.Copy(reply_data, 8, reply, 0, reply_size - 8);
                    transId++;
                }
	        }
	        catch (Exception err)
	        {
		        //logStream (MESSAGE_ERROR) << err << sendLog;
		        //throw (err);
                MessageBox.Show(err.ToString());
	        }
        }
        /**
		 * Call modbus function with two unsigned integer parameters and return expected as char array.
		 *
		 * @param func       Function index.
		 * @param p1         First parameter.
		 * @param p2         Second parameter.
		 * @param reply      Data returned from function call.
		 * @param reply_size Number of returned integers expected from the call.
		 *
		 * @throw ConnError if connection error occured.
		 */
        //void ConnModbus::callFunction (char func, int16_t p1, int16_t p2, void *reply, size_t reply_size)
        public void callFunction (Byte func, UInt16 p1, UInt16 p2, ref Byte[] reply, UInt16 reply_size)
        {
	        //Int16 req_data[2];
	        //req_data[0] = htons (p1);
	        //req_data[1] = htons (p2);
            Byte[] req_data=new Byte[4];
            Byte[] t1=BitConverter.GetBytes(p1);
            Byte[] t2=BitConverter.GetBytes(p2);
            t1.CopyTo(req_data, 0);
            t2.CopyTo(req_data, 2);
	        callFunction (func, req_data, 4, ref reply, reply_size);
        }
        /**
		 * Call modbus function with two unsigned integer parameters and return expected as array of unsigned interger.
		 *
		 * @param func       Function index.
		 * @param p1         First parameter.
		 * @param p2         Second parameter.
		 * @param reply      Data returned from function call.
		 * @param qty        Number of returned integers expected from the call.
		 */
        //void ConnModbus::callFunction (char func, int16_t p1, int16_t p2, uint16_t *reply_data, int16_t qty)
        public void callFunction (Byte func, UInt16 p1, UInt16 p2, ref UInt16[] reply_data, UInt16 qty)
        {
	        //int reply_size = 1 + qty * 2;
	        //char reply[reply_size];
            UInt16 reply_size = (UInt16)(qty * 2+1);
            Byte[] reply=new Byte[reply_size];

	        callFunction (func, p1, p2, ref reply, reply_size);
            /*
	        if (reply[0] != qty * 2)
	        {
		        throw ModbusError (this, "Invalid quantity in reply packet!");
	        }
            */
            if (reply[0] == qty * 2)//第一字节等于后面数组字节数
            {
                //char* rtop = reply + 1;
                for (reply_size = 0; reply_size < qty; reply_size++)
                {
                    //reply_data[reply_size] = ntohs(*((uint16_t*)rtop));
                    //rtop += 2;
                    reply_data[reply_size] = BitConverter.ToUInt16(reply, reply_size*2+1);
                }
            }
        }
        /**
		 * Read Modbus PLC coil states.
		 *
		 * @param start   Coil start address.
		 * @param size    Number of coils to read.
		 *
		 * @throw         ConnError on error.
		 */
        //void ConnModbus::readCoils (int16_t start, int16_t size)
        public void readCoils (UInt16 start, UInt16 size)
        {
	        //int reply_size = 1 + (size / 8) + ((size % 8) == 0 ? 0 : 1);
            UInt16 reply_size = (UInt16)(1 + (size / 8) + ((size % 8) == 0 ? 0 : 1));
	        //char reply_data[reply_size];
            Byte[] reply_data=new Byte[reply_size];

	        callFunction (0x01, start, size, ref reply_data, reply_size);
        }
        /**
		 * Read Modbus PLC discrete input states.
		 *
		 * @param start   Discrete input start address.
		 * @param size    Quantity of inputs.
		 *
		 * @throw         ConnError on error.
		 */
        //void ConnModbus::readDiscreteInputs (int16_t start, int16_t size)
        public void readDiscreteInputs (UInt16 start, UInt16 size)
        {
	        //int reply_size = 1 + (size / 8) + ((size % 8) == 0 ? 0 : 1);
	        //char reply_data[reply_size];
            UInt16 reply_size = (UInt16)(1 + (size / 8) + ((size % 8) == 0 ? 0 : 1));
	        Byte[] reply_data=new Byte[reply_size];

	        callFunction (0x02, start, size, ref reply_data, reply_size);
        }
        /**
		 * Read holding registers.
		 *
		 * @param start      Holding register starting address.
		 * @param qty        Quantity of registers.
		 * @param reply_data Returned data, converted to uint16_t (including network endian conversion).
		 *
		 * @throw            ConnError on error.
		 */
        //void ConnModbus::readHoldingRegisters (int16_t start, int16_t qty, uint16_t *reply_data)
        public void readHoldingRegisters(UInt16 start, UInt16 qty, ref UInt16[] reply_data)
        {
	        callFunction (0x03, start, qty, ref reply_data, qty);
        }
        /**
         * Read holding registers.
         *
         * @param start      Holding register starting address.
         * @param qty        Quantity of registers.
         * @param reply_data Returned data, converted to uint16_t (including network endian conversion).
         *
         * @throw            ConnError on error.
         */
        //void ConnModbus::readHoldingRegisters (int16_t start, int16_t qty, uint16_t *reply_data)
        public void readHoldingRegisters(UInt16 start, UInt16 qty, ref UInt16 reply_data)//用于qty=1的情况
        {
            UInt16[] array_reply = new UInt16[2];
            callFunction(0x03, start, qty, ref array_reply, qty);
            reply_data = array_reply[0];
        }
        /**
		 * Read input registers.
		 *
		 * @param start      Input register starting address.
		 * @param qty        Quantity of registers.
		 * @param reply_data Returned data, converted to uint16_t (including network endian conversion).
		 *
		 * @throw            ConnError on error.
		 */
        //void ConnModbus::readInputRegisters (int16_t start, int16_t qty, uint16_t *reply_data)
        public void readInputRegisters(UInt16 start, UInt16 qty, ref UInt16[] reply_data)
        {
	        callFunction (0x04, start, qty, ref reply_data, qty);
        }
        /**
        * Read input registers.
        *
        * @param start      Input register starting address.
        * @param qty        Quantity of registers.
        * @param reply_data Returned data, converted to uint16_t (including network endian conversion).
        *
        * @throw            ConnError on error.
        */
        //void ConnModbus::readInputRegisters (int16_t start, int16_t qty, uint16_t *reply_data)
        public void readInputRegisters(UInt16 start, UInt16 qty, ref UInt16 reply_data)//用于qty=1的情况
        {
            UInt16[] array_reply = new UInt16[2];
            callFunction(0x04, start, qty, ref array_reply, qty);
            reply_data = array_reply[0];
        }
        /**
		 * Write value to a register.
		 *
		 * @param reg  register address
		 * @param val  new register value
		 *
		 * @throw            ConnError on error.
		 */
        //void ConnModbus::writeHoldingRegister (int16_t reg, int16_t val)
        public void writeHoldingRegister (UInt16 reg, UInt16 val)
        {
  	        //int16_t reply[2];
            UInt16[] reply=new UInt16[2];
	        callFunction (0x06, reg, val, ref reply, 4);
        }
        /**
		 * Write masked value to a register. Actually read register,
		 * mask out mask values, or with masked val, and write it back.
		 *
		 * @param reg  register address
		 * @param mask mask (only bits with this mask will be written).
		 * @param val  new register value.
		 *
		 * @throw            ConnError on error.
		 */
        //void ConnModbus::writeHoldingRegisterMask (int16_t reg, int16_t mask, int16_t val)
        public void writeHoldingRegisterMask(UInt16 reg, UInt16 mask, UInt16 val)
        {            
	        //uint16_t old_value;
	        //readHoldingRegisters (reg, 1, &old_value);
	        //old_value &= ~mask;
	        //old_value |= (val & mask);
	        //writeHoldingRegister (reg, old_value);
            UInt16 old_value=0;
            readHoldingRegisters(reg, 1, ref old_value);
            old_value &= (UInt16)~mask;
            old_value |= (UInt16)(val & mask);
            writeHoldingRegister(reg, old_value);
        }


        //*********************************
        //Zelio
        //*********************************
        //public int setBitsInput (uint16_t reg, uint16_t mask, bool value)
        public int setBitsInput(UInt16 reg, UInt16 mask, bool value)
        {
            UInt16 oldValue = 0;
            try
            {
                readHoldingRegisters(reg, 1, ref oldValue);
                // switch mask..
                oldValue &= (UInt16)~mask;
                if (value)
                    oldValue |= mask;
                writeHoldingRegister(reg, oldValue);
            }
            catch (Exception err)
            {
                //logStream (MESSAGE_ERROR) << err << sendLog;
                return -1;
            }
            return 0;
        }
        /**
         * Open dome. Called either for open command, or when system
         * transitioned to on state.
         *
         * @return 0 on success, -1 on error.
         */
        //public int startOpen ()
        public int startOpen()
        {
            // check auto state..
            //uint16_t reg;
            //uint16_t reg_J1;
            UInt16 reg = 0;
            UInt16 reg_J1 = 0;
            try
            {
                readHoldingRegisters(ZREG_O4XT1, 1, ref reg);
                readHoldingRegisters(ZREG_J1XT1, 1, ref reg_J1);
                //if (!(reg & ZS_SW_AUTO))
                if ((reg & ZS_SW_AUTO) == 0)
                {
                    //logStream (MESSAGE_WARNING) << "dome not in auto mode" << sendLog;
                    return -1;
                }
                //if (reg & ZS_EMERGENCY_B)
                if ((reg & ZS_EMERGENCY_B) != 0)
                {
                    //logStream (MESSAGE_WARNING) << "emergency button pusshed" << sendLog;
                    return -1;
                }
                //if (reg & ZS_TIMEOUT)
                if ((reg & ZS_TIMEOUT) != 0)
                {
                    //logStream (MESSAGE_WARNING) << "timeout occured" << sendLog;
                    return -1;
                }
                //if ((zelioModel == ZELIO_BOOTES3_WOUTPLUGS || zelioModel == ZELIO_BOOTES3) && !(reg & ZS_POWER))
                if ((zelioModel == zelioModeltype.ZELIO_BOOTES3_WOUTPLUGS || zelioModel == zelioModeltype.ZELIO_BOOTES3) && ((reg & ZS_POWER) == 0))
                {
                    //logStream (MESSAGE_WARNING) << "power failure" << sendLog;
                    return -1;
                }
                /*
                //if (haveRainSignal && !(reg & ZS_RAIN) && !(reg_J1 & ZI_IGNORE_RAIN))
                if (haveRainSignal && ((reg & ZS_RAIN)==0) && ((reg_J1 & ZI_IGNORE_RAIN)==0))
                {
                    //logStream (MESSAGE_WARNING) << "it is raining and rain is not ignored" << sendLog;
                    return -1;
                }
                if (haveBatteryLevel && battery.getValueFloat () < batteryMin.getValueFloat ())
                {
                    //logStream (MESSAGE_WARNING) << "current battery level (" << battery.getValueFloat () << ") is bellow minimal level (" << batteryMin.getValueFloat () << sendLog;
                }
                */
                //zelioConn.writeHoldingRegisterMask (ZREG_J1XT1, ZI_DEADMAN_MASK, deadTimeout.getValueInteger ());
                writeHoldingRegisterMask(ZREG_J1XT1, ZI_DEADMAN_MASK, 5000);
                writeHoldingRegister(ZREG_J2XT1, 0);
                writeHoldingRegister(ZREG_J2XT1, 1);
            }
            //catch (rts2core::ConnError err)
            catch (Exception err)
            {
                //logStream (MESSAGE_ERROR) << err << sendLog;
                return -1;
            }
            //deadManNum = 0;
            //addTimer (deadTimeout.getValueInteger () / 5.0, new rts2core::Event (EVENT_DEADBUT, this));
            return 0;
        }
        /*
            //public bool isGoodWeather ()
            public bool isGoodWeather ()
            {
                if (getIgnoreMeteo ())
                    return true;
                if (ignoreAutomode.getValueBool () == true && isOpened () == -2)
                    return true;
                uint16_t reg;
                uint16_t reg3;
                try
                {
                    zelioConn.readHoldingRegisters (ZREG_O4XT1, 1, &reg);
                    if (haveBatteryLevel || haveHumidityOutput)
                        zelioConn.readHoldingRegisters (ZREG_O3XT1, 1, &reg3);
                }
                catch (rts2core::ConnError err)
                {
                    logStream (MESSAGE_ERROR) << err << sendLog;
                    return false;
                }
                if (haveRainSignal)
                {
                    rain.setValueBool (!(reg & ZS_RAIN));
                    sendValueAll (rain);
                    openingIgnoreRain.setValueBool (reg & ZS_OPENING_IGNR);
                    sendValueAll (openingIgnoreRain);
                }
                if (haveBatteryLevel)
                {
                    battery.setValueFloat (reg3 * 24.0f / 255.0f);
                    sendValueAll (battery);
                }
                if (haveHumidityOutput)
                {
                    humidity.setValueFloat (getHumidity (reg3));
                    sendValueAll (humidity);
                }
                weather.setValueBool (reg & ZS_WEATHER);
                sendValueAll (weather);
                // now check for rain..
                if (haveRainSignal && !(reg & ZS_RAIN) && weather.getValueBool () == false)
                {
                    setWeatherTimeout (3600, "raining");
                    return false;
                }
                // battery too weak
                if (haveBatteryLevel && battery.getValueFloat () < batteryMin.getValueFloat ())
                {
                    setWeatherTimeout (300, "battery level too low");
                    return false;
                }
                // not in auto mode..
                if (!(reg & ZS_SW_AUTO))
                {
                    if (ignoreAutomode.getValueBool () == false)
                    {
                        setWeatherTimeout (30, "not in auto mode");
                        return false;
                    }
                    // not in automode, and not opened - switch to bad weather
                    else if (isOpened () != -2)
                    {
                        setWeatherTimeout (30, "automode ignored, but dome is not opened");
                        return false;
                    }
                }
                return Dome::isGoodWeather ();
            }
            */
        public bool isGoodWeather()//天气情况设置为true
        {
            return true;
        }
        /**
         * Check if dome is opened.
         *
         * @return -2 if dome is opened, -1 if there was an error, >=0 is timeout in miliseconds till
         * next isOpened call.
         */
        //public long isOpened ()
        public long isOpened()
        {
            //uint16_t regs[2];
            UInt16[] regs = new UInt16[2];
            try
            {
                readHoldingRegisters(ZREG_O1XT1, 2, ref regs);
                //sendSwInfo (regs);
            }
            //catch (rts2core::ConnError err)
            catch (Exception err)
            {
                //logStream (MESSAGE_ERROR) << err << sendLog;
                return -1;
            }
            // check states of end switches..
            switch (zelioModel)
            {
                case zelioModeltype.ZELIO_SIMPLE:
                    //if ((regs[0] & ZO_EP_OPEN))
                    if ((regs[0] & ZO_EP_OPEN) != 0)
                        return -2;
                    break;
                case zelioModeltype.ZELIO_BOOTES3_WOUTPLUGS:
                case zelioModeltype.ZELIO_BOOTES3:
                case zelioModeltype.ZELIO_COMPRESSOR_WOUTPLUGS:
                case zelioModeltype.ZELIO_COMPRESSOR:
                case zelioModeltype.ZELIO_FRAM:
                    //if ((regs[0] & ZO_EP_OPEN) && (regs[1] & ZO_EP_OPEN))
                    if (((regs[0] & ZO_EP_OPEN) != 0) && ((regs[1] & ZO_EP_OPEN) != 0))
                        return -2;
                    break;
                case zelioModeltype.ZELIO_UNKNOW:
                    break;
            }

            return 0;
        }

        //public int endOpen ()
        public int endOpen()
        {
            return 0;
        }
        /**
         * Called when dome needs to be closed. Should start dome
         * closing sequence.
         *
         * @return -1 on error, 0 on success, 1 if dome will close (trigger for close) after equipment is stowed
         */
        //public int startClose ()
        public int startClose()
        {
            try
            {
                //uint16_t reg;
                UInt16 reg = 0;
                writeHoldingRegisterMask(ZREG_J1XT1, ZI_DEADMAN_MASK, 0);
                // update automode status..
                readHoldingRegisters(ZREG_O4XT1, 1, ref reg);
                //automode.setValueBool (reg & ZS_SW_AUTO);
                // reset ignore rain value
                /*
                if (ignoreRain.getValueBool ())
                {
                    setBitsInput (ZREG_J1XT1, ZI_IGNORE_RAIN, false);
                    ignoreRain.setValueBool (false);
                }
                if (automode.getValueBool () == false)
                {
                    return 0;
                }
                */
                return 0;
            }
            //catch (rts2core::ConnError err)
            catch (Exception err)
            {
                //logStream (MESSAGE_ERROR) << err << sendLog;
                return -1;
            }
            // 20 minutes timeout..
            //setWeatherTimeout (1200, "closed, timeout for opening (to allow dissipate motor heat)");
        }
        /**
         * Called to check if dome is closed. It is called also outside
         * of the closing sequence, to check if dome is closed when bad
         * weather arrives. When implemented correctly, it should check
         * state of dome end switches, and return proper values.
         *
         * @return -2 if dome is closed, -1 if there was an error, >=0 is timeout in miliseconds till
         * next isClosed call (when dome is closing).
         */
        //public long isClosed ()
        public long isClosed()
        {
            //uint16_t regs[2];
            UInt16[] regs = new UInt16[2];
            try
            {
                readHoldingRegisters(ZREG_O1XT1, 2, ref regs);
                //sendSwInfo (regs);
            }
            //catch (rts2core::ConnError err)
            catch (Exception err)
            {
                //logStream (MESSAGE_ERROR) << err << sendLog;
                return -1;
            }
            // check states of end switches..
            switch (zelioModel)
            {
                case zelioModeltype.ZELIO_SIMPLE:
                    //if ((regs[0] & ZO_EP_CLOSE))
                    if ((regs[0] & ZO_EP_CLOSE) != 0)
                        return -2;
                    break;
                case zelioModeltype.ZELIO_BOOTES3_WOUTPLUGS:
                case zelioModeltype.ZELIO_BOOTES3:
                case zelioModeltype.ZELIO_COMPRESSOR_WOUTPLUGS:
                case zelioModeltype.ZELIO_COMPRESSOR:
                case zelioModeltype.ZELIO_FRAM:
                    //if ((regs[0] & ZO_EP_CLOSE) && (regs[1] & ZO_EP_CLOSE))
                    if (((regs[0] & ZO_EP_CLOSE) != 0) && ((regs[1] & ZO_EP_CLOSE) != 0))
                        return -2;
                    break;
                case zelioModeltype.ZELIO_UNKNOW:
                    break;
            }

            return 0;
        }

        //public int endClose ()
        public int endClose()
        {
            return 0;
        }
        /*
        //public int processOption (int in_opt)
        public int processOption (int in_opt)
        {
            switch (in_opt)
            {
                case 'z':
                    host = new HostString (optarg, "502");
                    break;
                case OPT_BATTERY:
                    batteryMin.setValueCharArr (optarg);
                    break;
                case OPT_Q8_NAME:
                    Q8_name = optarg;
                    break;
                case OPT_Q9_NAME:
                    Q9_name = optarg;
                    break;
                case OPT_QA_NAME:
                    QA_name = optarg;
                    break;
                default:
                    return Dome::processOption (in_opt);
            }
            return 0;
        }

        //public void postEvent (rts2core::Event *event)
        public void postEvent (rts2core::Event *event)
        {
            switch (event.getType ())
            {
                case EVENT_DEADBUT:
                    if (isGoodWeather () && ((getState () & DOME_DOME_MASK) == DOME_OPENED || (getState () & DOME_DOME_MASK) == DOME_OPENING))
                    {
                        try
                        {
                            zelioConn.writeHoldingRegister (ZREG_J2XT1, deadManNum);
                        }
                        catch (rts2core::ConnError err)
                        {
                            logStream (MESSAGE_ERROR) << err << sendLog;
                        }
                        deadManNum = (deadManNum + 1) % 2;
                        addTimer (deadTimeout.getValueInteger () / 5.0, event);
                        return;
                    }
            }
            Dome::postEvent (event);
        }
        */

        //public int info ()
        public int info()
        {
            //uint16_t regs[8];
            UInt16[] regs = new UInt16[8];
            try
            {
                readHoldingRegisters(16, 8, ref regs);
            }
            //catch (rts2core::ConnError err)
            catch (Exception err)
            {
                //logStream (MESSAGE_ERROR) << err << sendLog;
                return -1;
            }
            /*
                        if (haveRainSignal)
                        {
                            rain.setValueBool (!(regs[7] & ZS_RAIN));
                            ignoreRain.setValueBool (regs[0] & ZI_IGNORE_RAIN);
                            openingIgnoreRain.setValueBool (regs[7] & ZS_OPENING_IGNR);

                            sendValueAll (rain);
                            sendValueAll (ignoreRain);
                            sendValueAll (openingIgnoreRain);
                        }
 
                        automode.setValueBool (regs[7] & ZS_SW_AUTO);
                        sendValueAll (automode);

                        timeoutOccured.setValueBool (regs[7] & ZS_TIMEOUT);
                        if (timeoutOccured.getValueBool ())
                            valueError (timeoutOccured);
                        else
                            valueGood (timeoutOccured);

                        weather.setValueBool (regs[7] & ZS_WEATHER);

                        emergencyButton.setValueBool (regs[7] & ZS_EMERGENCY_B);

                        sendValueAll (weather);
                        sendValueAll (emergencyButton);

                        switch (zelioModel)
                        {
                            case zelioModeltype.ZELIO_BOOTES3_WOUTPLUGS:
                            case zelioModeltype.ZELIO_BOOTES3:
                                onPower.setValueBool (regs[7] & ZS_POWER);

                                sendValueAll (onPower);
                            case zelioModeltype.ZELIO_FRAM:
                            case zelioModeltype.ZELIO_COMPRESSOR_WOUTPLUGS:
                            case zelioModeltype.ZELIO_COMPRESSOR:
                            case zelioModeltype.ZELIO_SIMPLE:
                                sendSwInfo (regs + 4);
                            case zelioModeltype.ZELIO_UNKNOW:
                                break;
                        }

                        if (haveBatteryLevel)
                        {
                            battery.setValueFloat (regs[6] * 24.0f / 255.0f);
                            sendValueAll (battery);
                        }

                        if (haveHumidityOutput)
                        {
                            humidity.setValueFloat (getHumidity (regs[6]));
                            sendValueAll (humidity);
                        }

                        J1XT1.setValueInteger (regs[0]);
                        J2XT1.setValueInteger (regs[1]);
                        J3XT1.setValueInteger (regs[2]);
                        J4XT1.setValueInteger (regs[3]);

                        sendValueAll (J1XT1);
                        sendValueAll (J2XT1);
                        sendValueAll (J3XT1);
                        sendValueAll (J4XT1);

                        O1XT1.setValueInteger (regs[4]);
                        O2XT1.setValueInteger (regs[5]);
                        O3XT1.setValueInteger (regs[6]);
                        O4XT1.setValueInteger (regs[7]);

                        sendValueAll (O1XT1);
                        sendValueAll (O2XT1);
                        sendValueAll (O3XT1);
                        sendValueAll (O4XT1);

                        return Dome::info ();
                     */
            return 0;//???
        }

        //public int init ()
        public int init()
        {
            /*
            //int ret = Dome::init ();
            int ret = Dome::init ();
            if (ret)
                return ret;

            if (host == NULL)
            {
                logStream (MESSAGE_ERROR) << "You must specify zelio hostname (with -z option)." << sendLog;
                return -1;
            }
            
            zelioConn = new rts2core::ConnModbus (this, host.getHostname (), host.getPort ());
            */
            //uint16_t regs[8];
            UInt16[] regs = new UInt16[8];
            try
            {
                //zelioConn.init ();
                readHoldingRegisters(16, 8, ref regs);
            }
            //catch (rts2core::ConnError er)
            catch (Exception er)
            {
                //logStream (MESSAGE_ERROR) << er << sendLog;
                return -1;
            }

            // O4XT1
            int model = regs[7] & (ZS_COMPRESSOR | ZS_SIMPLE | ZS_FRAM | ZS_3RELAYS);
            switch (model)
            {
                case 0:
                    zelioModel = zelioModeltype.ZELIO_BOOTES3_WOUTPLUGS;
                    //zelioModelString.setValueString ("ZELIO_BOOTES3_WITHOUT_PLUGS");
                    break;
                case ZS_3RELAYS:
                    zelioModel = zelioModeltype.ZELIO_BOOTES3;
                    //zelioModelString.setValueString ("ZELIO_BOOTES3");
                    break;
                case ZS_COMPRESSOR | ZS_FRAM:
                    zelioModel = zelioModeltype.ZELIO_FRAM;
                    //haveBatteryLevel = true;
                    //zelioModelString.setValueString ("ZELIO_FRAM");
                    break;
                case ZS_COMPRESSOR:
                    zelioModel = zelioModeltype.ZELIO_COMPRESSOR_WOUTPLUGS;
                    //zelioModelString.setValueString ("ZELIO_COMPRESSOR_WOUTPLUGS");
                    break;
                case ZS_COMPRESSOR | ZS_3RELAYS:
                    zelioModel = zelioModeltype.ZELIO_COMPRESSOR;
                    //zelioModelString.setValueString ("ZELIO_COMPRESSOR");
                    break;
                case ZS_SIMPLE:
                    zelioModel = zelioModeltype.ZELIO_SIMPLE;
                    //zelioModelString.setValueString ("ZELIO_SIMPLE");
                    break;
                default:
                    //logStream (MESSAGE_ERROR) << "cannot retrieve dome model (" << model << ")" << sendLog;
                    return -1;
            }
            // have this model rain signal?
            //haveRainSignal = !(regs[7] & ZS_WITHOUT_RAIN);
            //haveRainSignal = (regs[7] & ZS_WITHOUT_RAIN)==0?true:false;
            //haveHumidityOutput = (regs[7] & ZS_HUMIDITY)==0?false:true;

            //createZelioValues ();

            int ret = info();
            //if (ret)
            if (ret > 0)
                return ret;

            // switch on dome state
            switch (zelioModel)
            {
                case zelioModeltype.ZELIO_BOOTES3_WOUTPLUGS:
                case zelioModeltype.ZELIO_BOOTES3:
                case zelioModeltype.ZELIO_COMPRESSOR_WOUTPLUGS:
                case zelioModeltype.ZELIO_COMPRESSOR:
                case zelioModeltype.ZELIO_FRAM:
                    /*
                    if (swOpenLeft.getValueBool () == true && swOpenRight.getValueBool () == true)
                    {
                        maskState (DOME_DOME_MASK, DOME_OPENED, "initial dome state is opened");
                    }
                    else if (swCloseLeft.getValueBool () == true && swCloseRight.getValueBool () == true)
                    {
                        maskState (DOME_DOME_MASK, DOME_CLOSED, "initial dome state is closed");
                    }
                    else if (motOpenLeft.getValueBool () == true || motOpenRight.getValueBool () == true)
                    {
                        maskState (DOME_DOME_MASK, DOME_OPENING, "initial dome state is opening");
                    }
                    else if (motCloseLeft.getValueBool () == true || motCloseRight.getValueBool () == true)
                    {
                        maskState (DOME_DOME_MASK, DOME_CLOSING, "initial dome state is closing");
                    }
                    */
                    break;
                case zelioModeltype.ZELIO_SIMPLE:
                    /*
                    if (swOpenLeft.getValueBool () == true)
                    {
                        maskState (DOME_DOME_MASK, DOME_OPENED, "initial dome state is opened");
                    }
                    else if (swCloseLeft.getValueBool () == true)
                    {
                        maskState (DOME_DOME_MASK, DOME_CLOSED, "initial dome state is closed");
                    }
                    else if (motOpenLeft.getValueBool () == true)
                    {
                        maskState (DOME_DOME_MASK, DOME_OPENING, "initial dome state is opening");
                    }
                      else if (motCloseLeft.getValueBool () == true)
                    {
                        maskState (DOME_DOME_MASK, DOME_CLOSING, "initial dome state is closing");
                    }
                     */
                    break;
                case zelioModeltype.ZELIO_UNKNOW:
                    return -1;
            }
            //addTimer (1, new rts2core::Event (EVENT_DEADBUT, this));
            return 0;
        }
        /*
        //public void createZelioValues ()
        public void createZelioValues ()
        {
            switch (zelioModel)
            {
                case zelioModeltype.ZELIO_SIMPLE:
                    createValue (swOpenLeft, "sw_open", "state of open switch", false);
                    createValue (swCloseLeft, "sw_close", "state of close switch", false);

                    createValue (motOpenLeft, "motor_open", "state of opening motor", false);
                    createValue (motCloseLeft, "motor_close", "state of closing motor", false);

                    createValue (timeoOpenLeft, "timeo_open", "open timeout", false);
                    createValue (timeoCloseLeft, "timeo_close", "close timeout", false);

                    createValue (blockOpenLeft, "block_open", "open block", false);
                    createValue (blockCloseLeft, "block_close", "close block", false);
                    break;
	
                case zelioModeltype.ZELIO_BOOTES3_WOUTPLUGS:
                case zelioModeltype.ZELIO_BOOTES3:
                    createValue (onPower, "on_power", "true if power is connected", false);
                case zelioModeltype.ZELIO_FRAM:
                case zelioModeltype.ZELIO_COMPRESSOR_WOUTPLUGS:
                case zelioModeltype.ZELIO_COMPRESSOR:
                    createValue (swOpenLeft, "sw_open_left", "state of left open switch", false);
                    createValue (swCloseLeft, "sw_close_left", "state of left close switch", false);
                    createValue (swCloseRight, "sw_close_right", "state of right close switch", false);
                    createValue (swOpenRight, "sw_open_right", "state of right open switch", false);

                    createValue (motOpenLeft, "motor_open_left", "state of left opening motor", false);
                    createValue (motCloseLeft, "motor_close_left", "state of left closing motor", false);
                    createValue (motOpenRight, "motor_open_right", "state of right opening motor", false);
                    createValue (motCloseRight, "motor_close_right", "state of right closing motor", false);

                    createValue (timeoOpenLeft, "timeo_open_left", "left open timeout", false);
                    createValue (timeoCloseLeft, "timeo_close_left", "left close timeout", false);
                    createValue (timeoOpenRight, "timeo_open_right", "right open timeout", false);
                    createValue (timeoCloseRight, "timeo_close_right", "right close timeout", false);

                    createValue (blockOpenLeft, "block_open_left", "left open block", false);
                    createValue (blockCloseLeft, "block_close_left", "left close block", false);
                    createValue (blockOpenRight, "block_open_right", "right open block", false);
                    createValue (blockCloseRight, "block_close_right", "right close block", false);

                    break;
                case zelioModeltype.ZELIO_UNKNOW:
                    break;
            }

            if (haveBatteryLevel)
            {
                createValue (battery, "battery", "[V] battery level", false);
                createValue (batteryMin, "battery_min", "[V] battery minimal level for good weather", false, RTS2_VALUE_WRITABLE);
                batteryMin.setValueFloat (0);
            }

            if (haveHumidityOutput)
            {
                createValue (humidity, "humidity", "Humidity sensor raw output", false);
            }

            if (zelioModel == ZELIO_FRAM || zelioModel == ZELIO_BOOTES3)
            {
                createValue (Q8, Q8_name, "Q8 switch", false, RTS2_VALUE_WRITABLE);
                createValue (Q9, Q9_name, "Q9 switch", false, RTS2_VALUE_WRITABLE);
                createValue (QA, QA_name, "QA switch", false, RTS2_VALUE_WRITABLE);
            }
            else 
            {
                createValue (Q9, Q9_name, "Q9 switch", false, RTS2_VALUE_WRITABLE);
            }

            // create rain values only if rain sensor is present
            if (haveRainSignal)
            {
                createValue (rain, "rain", "state of rain sensor", false);
                createValue (openingIgnoreRain, "opening_ignore", "ignore rain during opening", false);
                createValue (ignoreRain, "ignore_rain", "whenever rain is ignored (know issue with interference between dome and rain sensor)", false, RTS2_VALUE_WRITABLE);
            }

            createValue (J1XT1, "J1XT1", "first input", false, RTS2_DT_HEX | RTS2_VALUE_WRITABLE);
            createValue (J2XT1, "J2XT1", "second input", false, RTS2_DT_HEX | RTS2_VALUE_WRITABLE);
            createValue (J3XT1, "J3XT1", "third input", false, RTS2_DT_HEX | RTS2_VALUE_WRITABLE);
            createValue (J4XT1, "J4XT1", "fourth input", false, RTS2_DT_HEX | RTS2_VALUE_WRITABLE);

            createValue (O1XT1, "O1XT1", "first output", false, RTS2_DT_HEX);
            createValue (O2XT1, "O2XT1", "second output", false, RTS2_DT_HEX);
            createValue (O3XT1, "O3XT1", "third output", false, RTS2_DT_HEX);
            createValue (O4XT1, "O4XT1", "fourth output", false, RTS2_DT_HEX);
        }
        
        //public int setValue (rts2core::Value *oldValue, rts2core::Value *newValue)
        public int setValue (rts2core::Value *oldValue, rts2core::Value *newValue)
        {
            if (oldValue == emergencyReset)
                return setBitsInput (ZREG_J1XT1, ZI_EMMERGENCY_R, ((rts2core::ValueBool*) newValue).getValueBool ()) == 0 ? 0 : -2;
            if (zelioModel == ZELIO_FRAM || zelioModel == ZELIO_BOOTES3)
            {
                if (oldValue == Q8)
                    return setBitsInput (ZREG_J1XT1, ZI_FRAM_Q8, ((rts2core::ValueBool*) newValue).getValueBool ()) == 0 ? 0 : -2;
                if (oldValue == Q9)
                    return setBitsInput (ZREG_J1XT1, ZI_FRAM_Q9, ((rts2core::ValueBool*) newValue).getValueBool ()) == 0 ? 0 : -2;
                if (oldValue == QA)
                    return setBitsInput (ZREG_J1XT1, ZI_FRAM_QA, ((rts2core::ValueBool*) newValue).getValueBool ()) == 0 ? 0 : -2;
            }
            else
            {
                if (oldValue == Q9)
                    return setBitsInput (ZREG_J1XT1, ZI_Q9, ((rts2core::ValueBool*) newValue).getValueBool ()) == 0 ? 0 : -2;
            }
            if (oldValue == ignoreRain)
                return setBitsInput (ZREG_J1XT1, ZI_IGNORE_RAIN, ((rts2core::ValueBool*) newValue).getValueBool ()) == 0 ? 0 : -2;
            if (oldValue == deadTimeout)
                return 0;
            try
            {
                if (oldValue == J1XT1)
                {
                    zelioConn.writeHoldingRegister (ZREG_J1XT1, newValue.getValueInteger ());
                    return 0;
                }
                else if (oldValue == J2XT1)
                {
                    zelioConn.writeHoldingRegister (ZREG_J2XT1, newValue.getValueInteger ());
                    return 0;
                }
                else if (oldValue == J3XT1)
                {
                    zelioConn.writeHoldingRegister (ZREG_J3XT1, newValue.getValueInteger ());
                    return 0;
                }
                else if (oldValue == J4XT1)
                {
                    zelioConn.writeHoldingRegister (ZREG_J4XT1, newValue.getValueInteger ());
                    return 0;
                }
            }
            catch (rts2core::ConnError err)
            {
                logStream (MESSAGE_ERROR) << err << sendLog;
                return -2;
            }
            return Dome::setValue (oldValue, newValue);
        }
        //public void sendSwInfo (uint16_t regs[2])
        public void sendSwInfo (UInt16 ref regs[2])
        {
            switch (zelioModel)
            {
                case zelioModeltype.ZELIO_BOOTES3_WOUTPLUGS:
                case zelioModeltype.ZELIO_BOOTES3:
                case zelioModeltype.ZELIO_FRAM:
                case zelioModeltype.ZELIO_COMPRESSOR_WOUTPLUGS:
                case zelioModeltype.ZELIO_COMPRESSOR:
                    swCloseRight.setValueBool (regs[1] & ZO_EP_CLOSE);
                    swOpenRight.setValueBool (regs[1] & ZO_EP_OPEN);

                    sendValueAll (swCloseRight);
                    sendValueAll (swOpenRight);

                    motOpenRight.setValueBool (regs[1] & ZO_MOT_OPEN);
                    motCloseRight.setValueBool (regs[1] & ZO_MOT_CLOSE);

                    sendValueAll (motOpenRight);
                    sendValueAll (motCloseRight);

                    timeoOpenRight.setValueBool (regs[1] & ZO_TIMEO_OPEN);
                    timeoCloseRight.setValueBool (regs[1] & ZO_TIMEO_CLOSE);

                    sendValueAll (timeoOpenRight);
                    sendValueAll (timeoCloseRight);

                    blockOpenRight.setValueBool (regs[1] & ZO_BLOCK_OPEN);
                    blockCloseRight.setValueBool (regs[1] & ZO_BLOCK_CLOSE);

                    sendValueAll (blockOpenRight);
                    sendValueAll (blockCloseRight);

                case zelioModeltype.ZELIO_SIMPLE:
                    swOpenLeft.setValueBool (regs[0] & ZO_EP_OPEN);
                    swCloseLeft.setValueBool (regs[0] & ZO_EP_CLOSE);

                    sendValueAll (swOpenLeft);
                    sendValueAll (swCloseLeft);

                    motOpenLeft.setValueBool (regs[0] & ZO_MOT_OPEN);
                    motCloseLeft.setValueBool (regs[0] & ZO_MOT_CLOSE);

                    sendValueAll (motOpenLeft);
                    sendValueAll (motCloseLeft);

                    timeoOpenLeft.setValueBool (regs[0] & ZO_TIMEO_OPEN);
                    timeoCloseLeft.setValueBool (regs[0] & ZO_TIMEO_CLOSE);

                    sendValueAll (timeoOpenLeft);
                    sendValueAll (timeoCloseLeft);

                    blockOpenLeft.setValueBool (regs[0] & ZO_BLOCK_OPEN);
                    blockCloseLeft.setValueBool (regs[0] & ZO_BLOCK_CLOSE);

                    sendValueAll (blockOpenLeft);
                    sendValueAll (blockCloseLeft);
                    break;
                case zelioModeltype.ZELIO_UNKNOW:
                    break;
            }
        }
        public int main (int argc, char **argv)
        {
            Zelio device (argc, argv);
            return device.run ();
        }
        */

    }
}
