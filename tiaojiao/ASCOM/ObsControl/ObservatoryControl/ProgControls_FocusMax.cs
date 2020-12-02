﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//using FocusMax;;
using System.Threading;

using System.Diagnostics;

//using LoggingLib;

namespace ObservatoryCenter
{
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    // Focusmax class
    //
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary>
    /// Focusmax class
    /// </summary>
    public class FocusMax_ExternalApplication : ExternalApplication
    {
        /// <summary>
        /// FOCUS MAX Object
        /// </summary>
        private FocusMax.FocusControl FocusControlObj;       //Application object
        internal FocusMax.FocusControl _FocusControlObj;     //todo: remove this temp reference


        /// <summary>
        /// FOCUS MAX Direct access to ASCOM Focuser object
        /// </summary>
        private FocusMax.Focuser FocuserObj;                 //Focuser object
        internal FocusMax.Focuser _FocuserObj;              //todo: remove this temp reference

        /// <summary>
        /// Current Focus Status when running Focus Async
        /// </summary>
        public int FocusAsyncStatus = -2;
        public string FocusAsyncStatusSt = "";
        private Dictionary<int, string> FocusAsyncStatusDictionary = new Dictionary<int, string> { { -1, "operation is in progress" }, { 0, "operation failed" }, { 1, "operation succeeded" } };

        public DateTime FocusAsync_StartTime;

        public int FM_FocuserPos;
        public double FM_FocuserTemp= Maxim_ExternalApplication.TEMP_MIN;

        public double HalfFluxDiameter;


        private ObservatoryControls ParentObsControl;


        public FocusMax_ExternalApplication(ObservatoryControls ExtObsControl) : base()
        {
            ParentObsControl = ExtObsControl;
        }

        /// <summary>
        /// Init main COM objects for FOCUS MAX
        /// </summary>
        public void InitObjects()
        {
            try { 
                if (FocusControlObj == null)  FocusControlObj = new FocusMax.FocusControl();
                if (FocuserObj == null) FocuserObj = new FocusMax.Focuser();
                _FocusControlObj = FocusControlObj;
                _FocuserObj = FocuserObj;
            }
            catch (Exception ex)
            {
                Logging.AddLog("FocusMax COM objects creation error", LogLevel.Important, Highlight.Error);
                Logging.AddLog("Exception details: " + ex.ToString(), LogLevel.Debug, Highlight.Error);
            }
        }


        /// <summary>
        /// Focus with the help of FocusMax
        /// </summary>
        public void Focus()
        {
            //Reinit objects (just in case)
            InitObjects();

            //1.1. Check if connected 
            if (FocusControlObj == null)
            {
                Logging.AddLog("FocusMax isn't connected", LogLevel.Important, Highlight.Error);
                return;
            }
            
            //1.2. Check if focusmax is busy
            if (FocusControlObj.IsBusy)
            {
                Logging.AddLog("FocusMax is already busy", LogLevel.Important, Highlight.Normal);
                return;
            }

            //1.3. Check if Camera isn't busy
            if (ParentObsControl.objMaxim.CameraConnected && ParentObsControl.objMaxim.CameraCurrentStatus != MaxIm.CameraStatusCode.csError && ParentObsControl.objMaxim.CameraCurrentStatus != MaxIm.CameraStatusCode.csIdle)
            {
                Logging.AddLog("Camera is busy [camera status=" + ParentObsControl.objMaxim.CameraCurrentStatus.ToString() + "], try again later", LogLevel.Important, Highlight.Normal);
                return;
            }

            //2. Start focusing
            try
            {
                FocusControlObj.FocusAsync();
                FocusAsync_StartTime = DateTime.Now;
            }
            catch (Exception ex)
            {
                Logging.AddLog("Exception during FocusAsync method [" + ex.ToString() + "]", LogLevel.Important, Highlight.Error);
            }
            Logging.AddLog("Start focusing...", LogLevel.Activity, Highlight.Normal);
        }

        /// <summary>
        /// Check current status
        /// </summary>
        public void CheckFocusMaxFocusStatus()
        {
            try
            {
                InitObjects();

                FM_FocuserPos = FocuserObj.Position;
                FM_FocuserTemp = FocusControlObj.Temperature;

                HalfFluxDiameter = FocusControlObj.HalfFluxDiameter;

                FocusAsyncStatus = FocusControlObj.FocusAsyncStatus;
                if (!FocusAsyncStatusDictionary.TryGetValue(FocusControlObj.FocusAsyncStatus, out FocusAsyncStatusSt))
                {
                    FocusAsyncStatusSt = "Status: " + FocusAsyncStatus;
                }
                
            }
            catch (Exception ex)
            {
                Logging.AddLog("Exception in CheckFocusMaxFocusStatus [" + ex.ToString() + "]", LogLevel.Debug, Highlight.Error);
            }
        }



        /// <summary>
        /// Connect focuser
        /// </summary>
        /// <returns></returns>
        public string ConnectFocuser()
        {
            InitObjects();

            try
            {
                FocuserObj.Link = true;
                Logging.AddLog("Focuser in FocusMax is connected", LogLevel.Activity);

                return "Focuser in FocusMax is connected";
            }
            catch (Exception ex)
            {
                StackTrace st = new StackTrace(ex, true);
                StackFrame[] frames = st.GetFrames();
                string messstr = "";

                // Iterate over the frames extracting the information you need
                foreach (StackFrame frame in frames)
                {
                    messstr += String.Format("{0}:{1}({2},{3})", frame.GetFileName(), frame.GetMethod().Name, frame.GetFileLineNumber(), frame.GetFileColumnNumber());
                }

                string FullMessage = "FocusMax focuser connection failed!" + Environment.NewLine;
                FullMessage += Environment.NewLine + Environment.NewLine + "Debug information:" + Environment.NewLine + "IOException source: " + ex.Data + " " + ex.Message
                        + Environment.NewLine + Environment.NewLine + messstr;
                //MessageBox.Show(this, FullMessage, "Invalid value", MessageBoxButtons.OK);

                Logging.AddLog("FocusMax focuser connection failed [" + ex.Message + "]", LogLevel.Important, Highlight.Error);
                Logging.AddLog(FullMessage, LogLevel.Debug, Highlight.Error);
                return "FocusMax focuser connection failed";
            }
        }


    }
}
