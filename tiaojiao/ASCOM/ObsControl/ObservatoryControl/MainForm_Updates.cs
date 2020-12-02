﻿using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms.DataVisualization.Charting;
//using LoggingLib;
//using AsrtoUtils;

namespace ObservatoryCenter
{
    /// <summary>
    /// UPDATE VISUAL ELEMENTS OF MAIN FORM
    ///  Contains methods to update some controls
    ///  usually calls from Timers 
    /// </summary>
    public partial class MainForm
    {

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Block with update elements
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#region *** Update visual elements (Status bar, telescope, etc) *****************************************************************************************************
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        /// <summary>
        /// This function updates all elements interconnected with switch state
        /// </summary>
        private void Update_SWITCH_related_elements()
        { 
            UpdatePowerButtonsStatus();
            UpdateStatusbarASCOMStatus();
            UpdateSettingsTabStatusFileds();
        }


        /// <summary>
        /// This function updates all elements interconnected with switch state
        /// </summary>
        private void Update_DOME_related_elements()
        {
            UpdateRoofStatus();
            UpdateStatusbarASCOMStatus();
            UpdateSettingsTabStatusFileds();
        }


        /// <summary>
        /// This function updates all elements interconnected with switch state
        /// </summary>
        private void Update_TELESCOPE_related_elements()
        {
            UpdateTelescopeStatus();
            UpdateStatusbarASCOMStatus();
            UpdateSettingsTabStatusFileds();
        }

        /// <summary>
        /// Update application status
        /// </summary>
        private void UpdateApplicationsRunningStatus()
        {
            //PHD2 status
            if (ObsControl.objPHD2App.IsRunning())
            {
                linkPHD2.LinkColor = Color.Green;
                btnGuiderConnect.Enabled = true;
                btnGuide.Enabled = true;
            }
            else
            {
                linkPHD2.LinkColor = Color.DeepPink;
                btnGuiderConnect.Enabled = false;
                btnGuide.Enabled = false;
            }
            //PHD Broker status
            if (ObsControl.objPHDBrokerApp.IsRunning()) { linkPHDBroker.LinkColor = Color.Green; } else { linkPHDBroker.LinkColor = Color.DeepPink; }

            //CdC status
            if (ObsControl.objCdCApp.IsRunning()) { linkCdC.LinkColor = Color.Green; } else { linkCdC.LinkColor = Color.DeepPink; }

            //FocusMax status
            //if (ObsControl.objFocusMaxApp.IsRunning()) { linkFocusMax.LinkColor = Color.Green; } else { linkFocusMax.LinkColor = Color.DeepPink; }

            //CCDAP status
            if (ObsControl.objCCDAPApp.IsRunning()) { linkCCDAP.LinkColor = Color.Green; } else { linkCCDAP.LinkColor = Color.DeepPink; }

            //CCDC status
            if (ObsControl.objCCDCApp.IsRunning()) { linkCCDC.LinkColor = Color.Green; } else { linkCCDC.LinkColor = Color.DeepPink; }

            //MaximDl status
            if (ObsControl.objMaxim.IsRunning()) { linkMaximDL.LinkColor = Color.Green; } else { linkMaximDL.LinkColor = Color.DeepPink; }

            //WeatherStation status
            if (ObsControl.objWSApp.IsRunning()) { linkWeatherStation.LinkColor = Color.Green; } else { linkWeatherStation.LinkColor = Color.DeepPink; }

            //TelescopeTempControl status
            if (ObsControl.objTTCApp.IsRunning()) { linkTelescopeTempControl.LinkColor = Color.Green; } else { linkTelescopeTempControl.LinkColor = Color.DeepPink; }
        }



        /// <summary>
        /// Updates markers in status bar
        /// </summary>
        private void UpdateStatusbarASCOMStatus()
        {
            //toolStripLogSize.Text = "LogRec: " + Logging.GetCount();

            //SWITCH
            if (ObsControl.ASCOMSwitch.Connected_flag)
            {
                toolStripStatus_Switch.ForeColor = Color.Blue;
            }
            else
            {
                toolStripStatus_Switch.ForeColor = Color.Gray;
            }
            toolStripStatus_Switch.ToolTipText = "DRIVER: " + ObsControl.ASCOMSwitch.DRIVER_NAME + Environment.NewLine;

            //DOME
            if (ObsControl.ASCOMDome.Connected_flag)
            {
                toolStripStatus_Dome.ForeColor = Color.Blue;
            }
            else
            {
                toolStripStatus_Dome.ForeColor = Color.Gray;
            }
            toolStripStatus_Dome.ToolTipText = "DRIVER: " + ObsControl.ASCOMDome.DRIVER_NAME + Environment.NewLine;

            //TELESCOPE
            bool Tprog = (ObsControl.ASCOMTelescope.Connected_flag);
            bool Tmaxim = (ObsControl.objMaxim.TelescopeConnected);
            bool Tcdc = false; //later organize checking
            toolStripStatus_Telescope.ToolTipText = "DRIVER: " + ObsControl.ASCOMTelescope.DRIVER_NAME + Environment.NewLine;
            toolStripStatus_Telescope.ToolTipText += "Control center direct connection: " + (Tprog ? "ON" : "off") + Environment.NewLine;
            toolStripStatus_Telescope.ToolTipText += "Maxim telescope connection: " + (Tmaxim ? "ON" : "off") + Environment.NewLine;
            toolStripStatus_Telescope.ToolTipText += "CdC telescope connection: " + (Tcdc ? "ON" : "off") + Environment.NewLine;

            if (Tprog && Tmaxim && Tcdc)
            {
                toolStripStatus_Telescope.ForeColor = Color.Blue;
            }
            else if (Tprog || Tmaxim || Tcdc)
            {
                toolStripStatus_Telescope.ForeColor = Color.MediumOrchid;
            }
            else
            {
                toolStripStatus_Telescope.ForeColor = Color.Gray;
            }

            //FOCUSER
            bool testFocus = false;
            string FocusSt = "";
            try
            {
                testFocus = (ObsControl.objMaxim.FocuserConnected);
            }
            catch { testFocus = false; }
            if (testFocus)
            {
                toolStripStatus_Focuser.ForeColor = Color.Blue;
                FocusSt = "";//?

            }
            else
            {
                toolStripStatus_Focuser.ForeColor = Color.Gray;
            }
            toolStripStatus_Focuser.ToolTipText = "DRIVER: " + FocusSt + Environment.NewLine;

            //CAMERA
            bool testCamera = (ObsControl.objMaxim.CameraConnected);
            if (testCamera)
            {
                toolStripStatus_Camera.ForeColor = Color.Blue;
            }
            else
            {
                toolStripStatus_Camera.ForeColor = Color.Gray;
            }

        }

        /// <summary>
        /// Updates buttons status
        /// </summary>
        private void UpdatePowerButtonsStatus()
        {
            //Mount
            if (ObsControl.ASCOMSwitch.Telescope_power_flag == null) //if (ObsControl.objSwitch == null || ObsControl.Mount_power_flag == null)
            {
                btnTelescopePower.Enabled = false;
                btnTelescopePower.BackColor = DisabledColor;
            }
            else
            {
                btnTelescopePower.Enabled = true;
                btnTelescopePower.BackColor = ((bool)ObsControl.ASCOMSwitch.Telescope_power_flag ? OnColor : OffColor);
            }

            //Camera
            if (ObsControl.ASCOMSwitch.Camera_power_flag == null)
            {
                btnCameraPower.Enabled = false;
                btnCameraPower.BackColor = DisabledColor;
            }
            else
            {
                btnCameraPower.Enabled = true;
                btnCameraPower.BackColor = ((bool)ObsControl.ASCOMSwitch.Camera_power_flag ? OnColor : OffColor);
            }

            /*
            //Focuser
            if (ObsControl.ASCOMSwitch.Focuser_power_flag == null)
            {
                btnFocuserPower.Enabled = false;
                btnFocuserPower.BackColor = DisabledColor;
            }
            else
            {
                btnFocuserPower.Enabled = true;
                btnFocuserPower.BackColor = ((bool)ObsControl.ASCOMSwitch.Focuser_power_flag ? OnColor : OffColor);
            }

            //Roof power
            if (ObsControl.ASCOMSwitch.Roof_power_flag == null)
            {
                btnRoofPower.Enabled = false;
                btnRoofPower.BackColor = DisabledColor;
            }
            else
            {
                btnRoofPower.Enabled = true;
                btnRoofPower.BackColor = ((bool)ObsControl.ASCOMSwitch.Roof_power_flag ? OnColor : OffColor);
            }

            //All button
            if (ObsControl.ASCOMSwitch.Roof_power_flag == true && ObsControl.ASCOMSwitch.Telescope_power_flag == true && ObsControl.ASCOMSwitch.Focuser_power_flag == true && ObsControl.ASCOMSwitch.Camera_power_flag == true)
            {
                btnPowerAll.Text = "Depower all";
            }
            else
            {
                btnPowerAll.Text = "Power all";
                if (ObsControl.ASCOMSwitch.Roof_power_flag == null || ObsControl.ASCOMSwitch.Telescope_power_flag == null || ObsControl.ASCOMSwitch.Focuser_power_flag == null || ObsControl.ASCOMSwitch.Camera_power_flag == null)
                {
                    btnPowerAll.Enabled = false;
                    btnPowerAll.BackColor = DisabledColor;
                }
                else
                {
                    btnPowerAll.Enabled = true;
                    btnPowerAll.BackColor = OffColor;
                }
            }

            */

            //SHORT PANNEL: Power buttons
            if (ObsControl.ASCOMSwitch.Connected_flag)
            {
                chkPower.Checked = true;
                if (ObsControl.ASCOMSwitch.Telescope_power_flag == true)
                {
                    chkPower.BackColor = OnColor;
                }
                else
                {
                    chkPower.BackColor = OffColor;
                }
            }
            else
            {
                chkPower.Checked = false;
                chkPower.BackColor = DefBackColor;
            }


        }

        /// <summary>
        /// Updates CCD camera status
        /// </summary>
        private void UpdateCCDCameraStatus()
        {
            if (ObsControl.objMaxim.IsRunning())
            {
                if (ObsControl.objMaxim.CameraConnected)
                {
                    //Camera current status
                    txtCameraStatus.Text = ObsControl.objMaxim.CameraCurrentStatus.ToString();
                    txtCameraStatus.BackColor = OnColor;

                    //Binning
                    if (txtCameraBinMode.Text == "") txtCameraBinMode.Text = Convert.ToString(ObsControl.objMaxim.CameraBin) + "x" + Convert.ToString(ObsControl.objMaxim.CameraBin);

                    //Filter
                    if (txtFilterName.Text == "") txtFilterName.Text = Convert.ToString(ObsControl.objMaxim.CurrentFilter);

                }
                else
                {
                    txtCameraStatus.Text = "";

                    txtCameraStatus.BackColor = SystemColors.Control;
                }
            }

            //SHORT PANNEL: Maxim DL status
            Color tmpMaximColor = new Color();
            if (ObsControl.objMaxim.IsRunning())
            {
                chkMaxim.Checked = true;
                tmpMaximColor = InterColor;
                if (ObsControl.objMaxim.CameraConnected)
                {
                    if (ObsControl.objMaxim.TelescopeConnected)
                    {
                        tmpMaximColor = OnColor;
                    }
                }
            }
            else
            {
                chkMaxim.Checked = false;
                tmpMaximColor = OffColor;
            }
            chkMaxim.BackColor = tmpMaximColor;

        }



        /// <summary>
        /// Updates CCD camera status
        /// </summary>
        private void UpdateCCDCameraCoolerStatus()
        {

            if (ObsControl.objMaxim.IsRunning())
            {
                if (ObsControl.objMaxim.CameraConnected)
                {
                    //Large form
                    txtCameraTemp.Text = String.Format("{0:0.0}", ObsControl.objMaxim.CameraTemp);
                    if (canUpdate_updownCameraSetPoint)
                        updownCameraSetPoint.Text = String.Format("{0:0.0}", ObsControl.objMaxim.CameraSetPoint);
                    txtCameraCoolerPower.Text = String.Format("{0:0}%", ObsControl.objMaxim.CameraCoolerPower);

                    //Short form
                    txtShortTemp.Text = String.Format("{0:0.0}", ObsControl.objMaxim.CameraTemp);
                    txtShortSetPoint.Text = String.Format("{0:0}", ObsControl.objMaxim.CameraSetPoint);
                    txtShortPower.Text = String.Format("{0:0}%", ObsControl.objMaxim.CameraCoolerPower);

                    if (ObsControl.objMaxim.CameraCoolerOnStatus)
                    {
                        //large
                        txtCameraTemp.BackColor = OnColor;
                        updownCameraSetPoint.BackColor = OnColor;
                        txtCameraCoolerPower.BackColor = OnColor;

                        //short
                        chkCoolerFlag.Checked = true;
                        if (ObsControl.objMaxim.CameraWarmpUpNow)
                        {
                            chkCoolerFlag.BackColor = InterColor;
                        }
                        else
                        {
                            chkCoolerFlag.BackColor = OnColor;
                        }

                        //Check temp is set?
                        if (!ObsControl.objMaxim.checkTempNearSetpoint())
                        {
                            txtShortTemp.BackColor = OffColor;
                            panelShortTemp.BackColor = OffColor;
                        }
                        else
                        {
                            txtShortTemp.BackColor = DefBackColor;
                            panelShortTemp.BackColor = DefBackColor;
                        }

                        //Check power is to high?
                        if (ObsControl.objMaxim.CameraCoolerPower >= 99.0)
                        {
                            txtShortPower.BackColor = OffColor;
                            panelShortPower.BackColor = OffColor;
                        }
                        else
                        {
                            txtShortPower.BackColor = DefBackColor;
                            panelShortPower.BackColor = DefBackColor;
                        }

                    }
                    else
                    {
                        txtCameraTemp.BackColor = OffColor;
                        updownCameraSetPoint.BackColor = OffColor;
                        txtCameraCoolerPower.BackColor = OffColor;


                        //short form
                        chkCoolerFlag.Checked = false;
                        chkCoolerFlag.BackColor = OffColor;
                    }

                }
                else
                //If camera is not connected
                {
                    txtCameraTemp.Text = "";
                    if (canUpdate_updownCameraSetPoint)
                        updownCameraSetPoint.Text = String.Format("{0:0.0}", ObsControl.objMaxim.TargetCameraSetTemp);
                    txtCameraCoolerPower.Text = "";
                    txtCameraStatus.Text = "";

                    txtCameraTemp.BackColor = SystemColors.Control;
                    updownCameraSetPoint.BackColor = SystemColors.Control;
                    txtCameraCoolerPower.BackColor = SystemColors.Control;


                    //short form
                    txtShortTemp.Text = "";
                    txtShortSetPoint.Text = String.Format("{0:0}", ObsControl.objMaxim.TargetCameraSetTemp);
                    txtShortPower.Text = "";

                    chkCoolerFlag.Checked = false;
                    chkCoolerFlag.BackColor = DefBackColor;
                }
            }
            else
            //If MaximDL isn't running
            {
                txtCameraTemp.Text = "";
                if (canUpdate_updownCameraSetPoint)
                    updownCameraSetPoint.Text = String.Format("{0:0.0}", ObsControl.objMaxim.TargetCameraSetTemp);
                txtCameraCoolerPower.Text = "";
                txtCameraStatus.Text = "";

                txtCameraTemp.BackColor = SystemColors.Control;
                updownCameraSetPoint.BackColor = SystemColors.Control;
                txtCameraCoolerPower.BackColor = SystemColors.Control;

                //short form
                txtShortPower.BackColor = DefBackColor;
                panelShortPower.BackColor = DefBackColor;
                txtShortTemp.BackColor = DefBackColor;
                panelShortTemp.BackColor = DefBackColor;

                txtShortTemp.Text = "";
                txtShortSetPoint.Text = String.Format("{0:0}", ObsControl.objMaxim.TargetCameraSetTemp);
                txtShortPower.Text = "";

                chkCoolerFlag.Checked = false;
                chkCoolerFlag.BackColor = DefBackColor;
            }

            //UpdateMinMax Temp
            txtCameraTemp_Min.Text = String.Format("{0:0.0}", ObsControl.objMaxim.CameraTemp_MinRecorded);
            txtCameraTemp_Max.Text = String.Format("{0:0.0}", ObsControl.objMaxim.CameraTemp_MaxRecorded);

            txtCameraTemp_Recommended.Text = String.Format("{0:0.0}", ObsControl.objMaxim.CalcRecommendedCoolerTemp());

        }

        /// <summary>
        /// Update guider status fields (if guiding By Maxim)
        /// </summary>
        private void ___UpdateGuiderFieldsStatus()
        {
            bool testCamera = false;
            try
            {
                testCamera = (ObsControl.objMaxim.CCDCamera != null && ObsControl.objMaxim.CCDCamera.LinkEnabled);
            }
            catch { testCamera = false; }

            if (testCamera)
            {
                ObsControl.objMaxim.GuiderRunnig = ObsControl.objMaxim.CCDCamera.GuiderRunning;

                btnGuider.Text = (ObsControl.objMaxim.GuiderRunnig ? "Guider running" : "Guider stoped");
                btnGuider.BackColor = (ObsControl.objMaxim.GuiderRunnig ? OnColor : OffColor);

                txtGuider_AggX.Text = Convert.ToString(ObsControl.objMaxim.CCDCamera.GuiderAggressivenessX);
                txtGuider_AggY.Text = Convert.ToString(ObsControl.objMaxim.CCDCamera.GuiderAggressivenessY);

                txtGuiderExposure.Text = Convert.ToString(ObsControl.objMaxim.CCDCamera.GuiderAngle); //for now
                txtGuiderLastErrSt.Text = ObsControl.objMaxim.CCDCamera.LastGuiderError;

                if (ObsControl.objMaxim.CCDCamera.GuiderNewMeasurement)
                {
                    ObsControl.objMaxim.GuiderXError = ObsControl.objMaxim.CCDCamera.GuiderXError;
                    ObsControl.objMaxim.GuiderYError = ObsControl.objMaxim.CCDCamera.GuiderYError;

                    string ErrTxt = String.Format("{0:0.00}  {1:0.00}" + Environment.NewLine, ObsControl.objMaxim.GuiderXError, ObsControl.objMaxim.GuiderYError);
                    //if (txtGuiderError.Lines.Count() > 4)
                    //{
                    //    Array.Resize<String>(ref txtGuiderError.Lines,4);
                    //    txtGuiderError.AppendText(ErrTxt);
                    //}
                }

            }
            else
            {
            }
        }


        /// <summary>
        /// Update Telescope Fields and Draw
        /// </summary>
        private void UpdateTelescopeStatus()
        {
            if (ObsControl.ASCOMTelescope.Enabled)
            {
                txtTelescopeAz.Enabled = true;
                txtTelescopeAlt.Enabled = true;
                txtTelescopeRA.Enabled = true;
                txtTelescopeDec.Enabled = true;
                btnPark.Enabled = true;
                btnTrack.Enabled = true;

                //Change Connect Button for current status
                if (ObsControl.ASCOMTelescope.Connected_flag)
                {
                    btnConnectTelescope.Text = "Diconnect";
                    btnConnectTelescope.BackColor = OnColor;

                    if (ObsControl.ASCOMTelescope.curAtPark)
                    {
                        btnPark.Text = "Unpark";
                        btnPark.BackColor = OffColor;
                    }
                    else
                    {
                        btnPark.Text = "Park";
                        btnPark.BackColor = OnColor;
                    }

                    if (ObsControl.ASCOMTelescope.curTracking)
                    {
                        //btnTrack.Text = "Parked";
                        btnTrack.BackColor = OnColor;
                    }
                    else
                    {
                        //btnTrack.Text = "UnParked";
                        btnTrack.BackColor = OffColor;
                    }

                }
                else
                {
                    btnConnectTelescope.Text = "Connect";
                    btnConnectTelescope.BackColor = OffColor;
                    btnTrack.BackColor = SystemColors.Control;
                    btnPark.BackColor = SystemColors.Control;
                }


                //update fields
                DrawTelescope_calculateTelescopePositionsVars(); //recalculate vars
                panelTele3D.Invalidate(); //calls repaint, which invoke panelTele3D_Paint event handler and calls Draw3DTelescope(e)
            }
            else
            {
                txtTelescopeAz.Enabled = false;
                txtTelescopeAlt.Enabled = false;
                txtTelescopeRA.Enabled = false;
                txtTelescopeDec.Enabled = false;

                btnPark.Enabled = false;
                btnTrack.Enabled = false;
            }



            //SHORT PANNEL: Telescope park & track status
            if (ObsControl.ASCOMTelescope.Connected_flag)
            {
                if (ObsControl.ASCOMTelescope.curAtPark)
                {
                    //btnPark.Text = "Parked";
                    chkMountPark.BackColor = OffColor;
                }
                else
                {
                    //btnPark.Text = "UnParked";
                    chkMountPark.BackColor = OnColor;
                }

                if (ObsControl.ASCOMTelescope.curTracking)
                {
                    //btnTrack.Text = "Parked";
                    chkMountTrack.BackColor = OnColor;
                }
                else
                {
                    //btnTrack.Text = "UnParked";
                    chkMountTrack.BackColor = OffColor;
                }

                txtShortAz.Text = String.Format("{0:0}", ObsControl.ASCOMTelescope.curAzimuth);
                txtShortAlt.Text = String.Format("{0:0}", ObsControl.ASCOMTelescope.curAltitude);
                if (ObsControl.ASCOMTelescope.curSlewing)
                {
                    txtShortAz.BackColor = InterColor;
                    txtShortAlt.BackColor = InterColor;
                }
                else
                {
                    txtShortAz.BackColor = DefBackColorTextBoxes;
                    txtShortAlt.BackColor = DefBackColorTextBoxes;
                }
            }
            else
            {
                chkMountPark.BackColor = DefBackColor;
                chkMountTrack.BackColor = DefBackColor;
                txtShortAz.Text = "";
                txtShortAlt.Text = "";
            }


        }


        public void UpdateFocuserStatus()
        {

            if (ObsControl.ASCOMFocuser.Enabled)
            {
                txtFocuser_pos.Enabled = true;
                txtFocuser_Temp.Enabled = true;

                txtFocuser_pos.Text = ObsControl.ASCOMFocuser.FocuserPos.ToString("N0");
                txtFocuser_Temp.Text = ObsControl.ASCOMFocuser.FocuserTemp.ToString("N1");
            }
            else
            {
                txtFocuser_pos.Enabled = false;
                txtFocuser_Temp.Enabled = false;

                txtFocuser_pos.Text = "";
                txtFocuser_Temp.Text = "";
            }
        }

        /// <summary>
        /// Update values on settings tab
        /// </summary>
        public void UpdateSettingsTabStatusFileds()
        {
            //SWITCH
            txtSet_Switch.Text = ObsControl.ASCOMSwitch.DRIVER_NAME;
            if (ObsControl.ASCOMSwitch.Enabled)
            {
                txtSet_Switch.Enabled = true;
                if (ObsControl.ASCOMSwitch.Connected_flag == true)
                {
                    txtSet_Switch.BackColor = OnColor;
                }
                else
                {
                    txtSet_Switch.BackColor = DefBackColorTextBoxes;
                }
                chkASCOM_Enable_Switch.Checked = true;
            }
            else
            {
                txtSet_Switch.Enabled = false;
                txtSet_Switch.BackColor = DefBackColorTextBoxes;
                chkASCOM_Enable_Switch.Checked = false;
            }

            //DOME
            txtSet_Dome.Text = ObsControl.ASCOMDome.DRIVER_NAME;
            if (ObsControl.ASCOMDome.Enabled)
            {
                txtSet_Dome.Enabled = true;
                if (ObsControl.ASCOMDome.Connected_flag == true)
                {
                    txtSet_Dome.BackColor = OnColor;
                }
                else
                {
                    txtSet_Dome.BackColor = DefBackColorTextBoxes;
                }
                chkASCOM_Enable_Dome.Checked = true;
            }
            else
            {
                txtSet_Dome.Enabled = false;
                txtSet_Dome.BackColor = DefBackColorTextBoxes;
                chkASCOM_Enable_Dome.Checked = false;
            }


            //TELESCOPE
            txtSet_Telescope.Text = ObsControl.ASCOMTelescope.DRIVER_NAME;
            if (ObsControl.ASCOMTelescope.Enabled)
            {
                txtSet_Telescope.Enabled = true;
                if (ObsControl.ASCOMTelescope.Connected_flag == true)
                {
                    txtSet_Telescope.BackColor = OnColor;
                }
                else
                {
                    txtSet_Telescope.BackColor = DefBackColorTextBoxes;
                }
                chkASCOM_Enable_Telescope.Checked = true;
            }
            else
            {
                txtSet_Telescope.Enabled = false;
                txtSet_Telescope.BackColor = DefBackColorTextBoxes;
                chkASCOM_Enable_Telescope.Checked = false;
            }

            //FOCUSER
            txtSet_Focuser.Text = ObsControl.ASCOMFocuser.DRIVER_NAME;
            if (ObsControl.ASCOMFocuser.Enabled)
            {
                txtSet_Focuser.Enabled = true;
                if (ObsControl.ASCOMFocuser.Connected_flag == true)
                {
                    txtSet_Focuser.BackColor = OnColor;
                }
                else
                {
                    txtSet_Focuser.BackColor = DefBackColorTextBoxes;
                }
                chkASCOM_Enable_Focuser.Checked = true;
            }
            else
            {
                txtSet_Focuser.Enabled = false;
                txtSet_Focuser.BackColor = DefBackColorTextBoxes;
                chkASCOM_Enable_Focuser.Checked = false;
            }


            //testFocus = (ObsControl.objMaxim.MaximApplicationObj != null && ObsControl.objMaxim.MaximApplicationObj.FocuserConnected);
            //testCamera2 = (ObsControl.objMaxim.CCDCamera != null && ObsControl.objMaxim.CCDCamera.LinkEnabled && ObsControl.objMaxim.CCDCamera.GuiderName != "");


        }


        /// <summary>
        /// Called from InterfaceUpdateTimer
        /// </summary>
        public void UpdateFocusMaxStatus()
        {
            /*
            if (ObsControl.objFocusMaxApp.IsRunning())
            {
                //Check status
                ObsControl.objFocusMaxApp.CheckFocusMaxFocusStatus();

                txtFocusMax_FocusStartTime.Text = ObsControl.objFocusMaxApp.FocusAsync_StartTime.ToString();
                txtFocusMax_FocusStartTimeElapsed.Text = ((DateTime.Now - ObsControl.objFocusMaxApp.FocusAsync_StartTime).TotalSeconds> 10000 ? "" : (DateTime.Now - ObsControl.objFocusMaxApp.FocusAsync_StartTime).TotalSeconds.ToString("N0"));

                txtFocusMax_FocusAsyncStatus.Text = ObsControl.objFocusMaxApp.FocusAsyncStatusSt;
                txtFocusMax_FocuserPosition.Text = ObsControl.objFocusMaxApp.FM_FocuserPos.ToString("N0");
                txtFocusMax_Debug.Text = ObsControl.objFocusMaxApp.HalfFluxDiameter.ToString("N2");
            }
            else
            {
                txtFocusMax_FocusStartTime.Text = "";
                txtFocusMax_FocusStartTimeElapsed.Text = "" ;

                txtFocusMax_FocusAsyncStatus.Text = "";
                txtFocusMax_FocuserPosition.Text = "";
                txtFocusMax_Debug.Text = "";
            }
            */
        }



        /// <summary>
        /// Update solver messages
        /// </summary>
        public void UpdateSolverFileds()
        {
            //AstroTortilla
            txtATSolver_Status.Text = ObsControl.objAstroTortilla.LastAttemptMessage;
            txtATSolutionRA.Text = ObsControl.objAstroTortilla.Solution_RA;
            txtATSolutionDec.Text = ObsControl.objAstroTortilla.Solution_Dec;

            txtATSolver_Status.BackColor = (ObsControl.objAstroTortilla.LastAttemptSolvedFlag == false ? OffColor : SystemColors.Control);
            txtATSolutionRA.BackColor = (ObsControl.objAstroTortilla.LastAttemptSolvedFlag == false ? OffColor : SystemColors.Control);
            txtATSolutionDec.BackColor = (ObsControl.objAstroTortilla.LastAttemptSolvedFlag == false ? OffColor : SystemColors.Control);
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        #endregion *** update visual elements *************************************************************************************************************
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end of block
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#region *** Update CCDAP and CCDC data *****************************************************************
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        /// <summary>
        /// Update state of CCDAP prog
        /// including log details
        /// </summary>
        private void UpdateCCDAPstate()
        {
            if (ObsControl.objCCDAPApp.IsRunning())
            {
                ObsControl.objCCDAPApp.GetLastLogFile(); //needs to be constanly updated
                if (ObsControl.objCCDAPApp.checkLogFileIsValid())
                {
                    ObsControl.objCCDAPApp.ParseLogFile();
                    txtCCDAutomationStatus.Text = (ObsControl.objCCDAPApp.MessageText) + txtCCDAutomationStatus.Text;
                }
            }
        }

        /// <summary>
        /// Update state of CCDC prog
        /// including log details
        /// </summary>
        private void UpdateCCDCstate()
        {
            if (ObsControl.objCCDCApp.IsRunning())
            {
                //1. Определяем, какой лог актуальный
                ObsControl.objCCDCApp.GetLastLogFile(); //needs to be constanly updated
                //2. Проверямем - он валидный?
                if (ObsControl.objCCDCApp.checkLogFileIsValid())
                {
                    //3. Читаем содержимое в память
                    ObsControl.objCCDCApp.ReadLogFileContents();
                    //4. Парсим содержимое и возвращаем строки для отображения в лог
                    List<string> NewLogLines = new List<string>();
                    if (ObsControl.objCCDCApp.ParseLogFile(out NewLogLines))
                    {
                        //5. Выводим строки в логи
                        foreach (string st in NewLogLines) txtCCDAutomationStatus.Text = st + txtCCDAutomationStatus.Text;

                        //6. Отображаем полученные данные в интерфейсе

                        //Obj data
                        txtShort_CurrentObj.Text = ObsControl.objCCDCApp.ObjName;
                        txtCCDCLog_Obj.Text = ObsControl.objCCDCApp.ObjName;
                        txtObjName.Text = ObsControl.objCCDCApp.ObjName; //Telescope panel
                        txtCCDCLog_ObjRA.Text = ObsControl.objCCDCApp.ObjRA_st;
                        txtCCDCLog_ObjDec.Text = ObsControl.objCCDCApp.ObjDec_st;

                        //Image data
                        txtCCDCImageName.Text = ObsControl.objCCDCApp.LastImageName; // main panel
                        txtCCDCL_lastImage.Text = ObsControl.objCCDCApp.LastImageName;
                        txtCCDCL_lastSequence.Text = ObsControl.objCCDCApp.LastSequenceInfo;
                        txtCCDC_SeriesNum.Text = "#" + ObsControl.objCCDCApp.LastSequence_Iteration.ToString();

                        txtCCDCLog_exp.Text = ObsControl.objCCDCApp.LastExposure_ExposureLength.ToString();
                        txtExposure.Text = ObsControl.objCCDCApp.LastExposure_ExposureLength.ToString();// main panel

                        txtFilterName.Text = ObsControl.objCCDCApp.LastExposure_filter;// main panel
                        txtCameraBinMode.Text = ObsControl.objCCDCApp.LastExposure_bin;// main panel
                        txtCCDCLog_filter.Text = ObsControl.objCCDCApp.LastExposure_filter;
                        txtCCDCLog_bin.Text = ObsControl.objCCDCApp.LastExposure_bin;

                        txtCCDCLog_ExpStartTime.Text = (ObsControl.objCCDCApp.LastExposureStartTime.Year == 2015 ? "" : ObsControl.objCCDCApp.LastExposureStartTime.ToString("HH:mm:ss"));
                        txtCCDCLog_ExpEndTime.Text = (ObsControl.objCCDCApp.LastExposureEndTime.Year == 2015 ? "" : ObsControl.objCCDCApp.LastExposureEndTime.ToString("HH:mm:ss"));
                        if (ObsControl.objCCDCApp.LastExposureStartTime > ObsControl.objCCDCApp.LastExposureEndTime)
                        {
                            txtCCDCLog_ExpEndTime.ForeColor = DefBackColorTextBoxes;
                        }
                        else
                        {
                            txtCCDCLog_ExpEndTime.ForeColor = DefaultForeColor;
                        }


                        txtCCDCLog_ActionsStart.Text = (ObsControl.objCCDCApp.ActionRunStartTime.Year == 2015 ? "" : ObsControl.objCCDCApp.ActionRunStartTime.ToString());
                        txtCCDCLog_ActionsFinish.Text = (ObsControl.objCCDCApp.ActionRunEndTime.Year == 2015 ? "" : ObsControl.objCCDCApp.ActionRunEndTime.ToString());

                    }

                    //7. Проверяем на внешние реквесты 
                    ObsControl.objCCDCApp.CheckEvents_async();

                    UpdateCCDCState_progressbar();

                    //Debug interface update
                    txtCCDC_Request_Start_Flag.Text = ObsControl.objCCDCApp.Request_StartAfterStop.RequestActive.ToString();
                    txtCCDC_Request_Start_Time.Text = ObsControl.objCCDCApp.Request_StartAfterStop.RequestedTime.ToString("HH:mm:ss");
                    txtCCDC_Request_Start_Fulfiled_Flag.Text = ObsControl.objCCDCApp.Request_StartAfterStop.RequestWasFulfiled.ToString();
                    txtCCDC_Request_Start_Fulfiled_Res.Text = ObsControl.objCCDCApp.Request_StartAfterStop.RequestWasSuccessful.ToString();
                    txtCCDC_Request_Start_Fulfiled_Time.Text = ObsControl.objCCDCApp.Request_StartAfterStop.FulfiledTime.ToString("HH:mm:ss");

                    txtCCDC_Request_Stop_Flag.Text = ObsControl.objCCDCApp.Request_StopAfterImage.RequestActive.ToString();
                    txtCCDC_Request_Stop_Time.Text = ObsControl.objCCDCApp.Request_StopAfterImage.RequestedTime.ToString("HH:mm:ss");
                    txtCCDC_Request_Stop_Fulfiled_Flag.Text = ObsControl.objCCDCApp.Request_StopAfterImage.RequestWasFulfiled.ToString();
                    txtCCDC_Request_Stop_Fulfiled_Res.Text = ObsControl.objCCDCApp.Request_StopAfterImage.RequestWasSuccessful.ToString();
                    txtCCDC_Request_Stop_Fulfiled_Time.Text = ObsControl.objCCDCApp.Request_StopAfterImage.FulfiledTime.ToString("HH:mm:ss");

                    txtCCDC_Request_Abort_Flag.Text = ObsControl.objCCDCApp.Request_AbortAfterStop.RequestActive.ToString();
                    txtCCDC_Request_Abort_Fulfiled_Flag.Text = ObsControl.objCCDCApp.Request_AbortAfterStop.RequestWasFulfiled.ToString();
                    txtCCDC_Request_Abort_Fulfiled_Res.Text = ObsControl.objCCDCApp.Request_AbortAfterStop.RequestWasSuccessful.ToString();


                    //Request event interface elements
                    //Restart after end
                    if (ObsControl.objCCDCApp.Request_StartAfterStop.RequestActive)
                    {
                        btnReStartCCDC.BackColor = InterColor;
                        chkShort_Restart.BackColor = InterColor;
                        chkShort_Restart.Checked = true;

                        chkPause.BackColor = InterColor;
                    }
                    else
                    {
                        btnReStartCCDC.BackColor = DefBackColor;
                        chkShort_Restart.BackColor = DefBackColor;
                        chkShort_Restart.Checked = false;

                        if (chkPause.BackColor == InterColor) chkPause.BackColor = DefBackColor;
                    }
                    //Abort after end
                    if (ObsControl.objCCDCApp.Request_AbortAfterStop.RequestActive)
                    {
                        btnCCDCAbortAtEnd.BackColor = InterColor;
                        chkAbort.BackColor = InterColor;
                    }
                    else
                    {
                        btnCCDCAbortAtEnd.BackColor = DefBackColor;
                        if (chkAbort.BackColor == InterColor) chkAbort.BackColor = DefBackColor;
                    }
                }
            }


            //SHORT PANNEL: CCDC status
            Color tmpCCDCColor = new Color();
            if (ObsControl.objCCDCApp.IsRunning())
            {
                chkCCDC.Checked = true;
                tmpCCDCColor = OnColor;
            }
            else
            {
                chkCCDC.Checked = false;
                tmpCCDCColor = OffColor;
            }
            chkCCDC.BackColor = tmpCCDCColor;
        }

        //Обновить прогресс бар
        private void UpdateCCDCState_progressbar()
        {
            int ExpLen = (Int32)Math.Ceiling(ObsControl.objCCDCApp.LastExposure_ExposureLength);
            //Если все еще идет экспозиция 
            if ( (DateTime.Now - ObsControl.objCCDCApp.LastExposureStartTime).TotalSeconds < ExpLen)
            {
                progressBar_Exposure.Maximum = ExpLen;
                progressBar_CCDCL_exposure.Maximum = progressBar_Exposure.Maximum;
                progressBar_MainExposure.Maximum = progressBar_Exposure.Maximum;

                //Проверить:
                // - не закончилось ли экспозиция
                // - не был ли прерван ActionList
                // - не был ли запущен новый ActionList
                if (ObsControl.objCCDCApp.LastExposureEndTime > ObsControl.objCCDCApp.LastExposureStartTime || ObsControl.objCCDCApp.ActionRunEndTime.Year != 2015 || ObsControl.objCCDCApp.ActionRunStartTime > ObsControl.objCCDCApp.LastExposureStartTime)
                {
                    //Поставить на максимум
                    progressBar_Exposure.Value = ExpLen;
                    progressBar_CCDCL_exposure.Value = progressBar_Exposure.Value;
                    progressBar_MainExposure.Value = progressBar_Exposure.Value;
                }
                else
                {
                    progressBar_Exposure.Value = Convert.ToInt32((DateTime.Now - ObsControl.objCCDCApp.LastExposureStartTime).TotalSeconds);
                    progressBar_CCDCL_exposure.Value = progressBar_Exposure.Value;
                    progressBar_MainExposure.Value = progressBar_Exposure.Value;
                }

                lblCCDC_Exp_progress.Text = progressBar_Exposure.Value + " of " + ExpLen + " sec";
                toolTip1.SetToolTip(progressBar_Exposure, lblCCDC_Exp_progress.Text);
            }
            //Если экспозиция закончилась
            else if (ObsControl.objCCDCApp.LastExposureStartTime.Year != 2015)
            {
                //Поставить на максимум
                progressBar_Exposure.Maximum = ExpLen; //а иначе exception
                progressBar_CCDCL_exposure.Maximum = progressBar_Exposure.Maximum; //а иначе exception
                progressBar_MainExposure.Maximum = progressBar_Exposure.Maximum; //а иначе exception

                progressBar_Exposure.Value = ExpLen;
                progressBar_CCDCL_exposure.Value = progressBar_Exposure.Value;
                progressBar_MainExposure.Value = progressBar_Exposure.Value;

                lblCCDC_Exp_progress.Text = progressBar_Exposure.Value + " of " + ExpLen + " sec";
                toolTip1.SetToolTip(progressBar_Exposure, lblCCDC_Exp_progress.Text);
            }


        }

        /// <summary>
        /// Update Pointing accuracy and Foucsing stat
        /// </summary>
        private void UpdateFocusAndPointAccuracy()
        {
            //From CCCDC
            if (ObsControl.objCCDCApp.IsRunning())
            {
                //FOCUSING
                //short pannel
                txtShort_HFDLast.Text = ObsControl.objCCDCApp.LastFocusHFD.ToString();
                if (ObsControl.objCCDCApp.LastFocusHFD > 3.5)
                {
                    txtShort_HFDLast.BackColor = OffColor;
                }
                else if (ObsControl.objCCDCApp.LastFocusHFD >= 3.0)
                {
                    txtShort_HFDLast.BackColor = InterColor;
                }
                else
                {
                    txtShort_HFDLast.BackColor = DefBackColorTextBoxes;
                }
                

                //ccdc pannel
                txtCCDCLog_HFD.Text = ObsControl.objCCDCApp.LastFocusHFD.ToString();
                txtCCDCLog_FocusTime.Text = ObsControl.objCCDCApp.LastFocusTime.ToString("HH:mm:ss");

                //main pannel
                txtLastFocusHFD.Text = ObsControl.objCCDCApp.LastFocusHFD.ToString(); //Main

                //POINTING
                //short
                txtShort_PointingError.Text = ObsControl.objCCDCApp.LastPointingError.ToString(); //Short
                if (ObsControl.objCCDCApp.LastPointingError > 30)
                {
                    txtShort_PointingError.BackColor = OffColor;
                }
                else if (ObsControl.objCCDCApp.LastPointingError > 15)
                {
                    txtShort_PointingError.BackColor = InterColor;
                }
                else
                {
                    txtShort_PointingError.BackColor = DefBackColorTextBoxes;
                }

                //ccdc pannel
                txtCCDCLog_PointingError.Text = ObsControl.objCCDCApp.LastPointingError.ToString(); //CCDC tab

                //main pannel
                txtPointingError.Text = ObsControl.objCCDCApp.LastPointingError.ToString(); //Telescope panel
            }
            /*
            //From FocusMax
            if (ObsControl.objFocusMaxApp.IsRunning())
            {
                txtLastFocusHFD.Text = ObsControl.objFocusMaxApp.HalfFluxDiameter.ToString("N2");
            }
            */
        }


        private void UpdateBoltwoodStatus()
        {
            //Update weather file
            ObsControl.objBoltwoodControl.UpdateFile();

            //Update fields
            txtDewPoint.Text = ObsControl.objBoltwoodControl.BoltwoodObj.DewPoint.ToString("0.#");
            txtSkyTemp.Text = ObsControl.objBoltwoodControl.BoltwoodObj.SkyTemp.ToString();
            txtWindSpeed.Text = ObsControl.objBoltwoodControl.BoltwoodObj.WindSpeed.ToString();

            comboBoxCloudCond.SelectedItem = ObsControl.objBoltwoodControl.BoltwoodObj.CloudCond.ToString();
            comboBoxWindCond.SelectedItem = ObsControl.objBoltwoodControl.BoltwoodObj.WindCond.ToString();
            //comboBoxRainCond.SelectedItem = BoltwoodObj.RainCond.ToString();
            comboBoxDaylightCond.SelectedItem = ObsControl.objBoltwoodControl.BoltwoodObj.DaylightCond.ToString();

            comboBoxRoofCloseFlag.SelectedItem = ObsControl.objBoltwoodControl.BoltwoodObj.RoofCloseFlag.ToString();
            comboBoxAlertFlag.SelectedItem = ObsControl.objBoltwoodControl.BoltwoodObj.AlertFlag.ToString();

            comboBoxRainCond.SelectedItem = ObsControl.objBoltwoodControl.BoltwoodObj.RainCond.ToString();
            comboBoxRainFlag.SelectedItem = ObsControl.objBoltwoodControl.BoltwoodObj.RainFlag.ToString();
            comboBoxWetFlag.SelectedItem = ObsControl.objBoltwoodControl.BoltwoodObj.WetFlag.ToString();
        }


        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        #endregion *** The end of Update PHD and CCDAP data *****************************************************************
        // end of block
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        #region *** Update Weather And TelescopeTempControl Data *****************************************************************
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        private bool HadWeatherData = false; //was at least once data received?
        /// <summary>
        /// Update weather state
        /// </summary>
        private void UpdateWeatherData()
        {

            double Temp = -100;
            double Cloud = -100;
            double RGC = -1;
            double Wet = 0;
            DateTime XVal;

            DataPoint EmptyP = new DataPoint { IsEmpty = true, XValue = DateTime.Now.AddSeconds(-5).ToOADate(), YValues = new double[] { 0 } };

            //Read weather station value
            if (ObsControl.objWSApp.IsRunning() && ObsControl.objWSApp.CMD_GetBoltwoodString())
            {
                if (!HadWeatherData)
                {
                    Logging.AddLog("Weather Station connected", LogLevel.Activity);
                }
                HadWeatherData = true; //flag, that at least one value was received

                //Display small widget
                Temp = ObsControl.objWSApp.BoltwoodState.Bolt_Temp;
                Cloud = ObsControl.objWSApp.BoltwoodState.Bolt_CloudIdx;
                XVal = ObsControl.objWSApp.BoltwoodState.LastMeasure;
                RGC = ObsControl.objWSApp.BoltwoodState.RGCVal;
                Wet = ObsControl.objWSApp.BoltwoodState.WetSensorVal;


                //draw value
                if (Temp > -100)
                {
                    weatherSmallChart.Series["Temp"].Points.AddXY(XVal.ToOADate(), Temp);
                }
                else
                {
                    weatherSmallChart.Series["Temp"].Points.Add(EmptyP);
                }
                if (Cloud > -100)
                {
                    weatherSmallChart.Series["CloudIdx"].Points.AddXY(XVal.ToOADate(), Cloud);
                }
                else
                {
                    weatherSmallChart.Series["CloudIdx"].Points.Add(EmptyP);
                }

                txtRainCondition.Text = ObsControl.objWSApp.BoltwoodState.Bolt_RainFlag.ToString();

                //Data in small widget
                txtTemp.Text = Temp.ToString();
                txtCloudState.Text = Cloud.ToString();


                //Display large widget
                //draw value
                if (Temp > -100)
                {
                    chartWT.Series["Temp"].Points.AddXY(XVal.ToOADate(), Temp);
                }
                else
                {
                    chartWT.Series["Temp"].Points.Add(EmptyP);
                }
                if (Cloud > -100)
                {
                    chartWT.Series["CloudIdx"].Points.AddXY(XVal.ToOADate(), Cloud);
                }
                else
                {
                    chartWT.Series["CloudIdx"].Points.Add(EmptyP);
                }
                if (RGC >= 0)
                {
                    chartWT.Series["RGC"].Points.AddXY(XVal.ToOADate(), RGC);
                }
                else
                {
                    chartWT.Series["RGC"].Points.Add(EmptyP);
                }
                if (Wet > 0)
                {
                    chartWT.Series["Wet"].Points.AddXY(XVal.ToOADate(), 1024 - Wet);
                }
                else
                {
                    chartWT.Series["Wet"].Points.Add(EmptyP);
                }

                //Data in large widget
                txtWTTemp.Text = Temp.ToString();
                txtWTCloudIdx.Text = Cloud.ToString();
                txtWTCaseTemp.Text = ObsControl.objWSApp.BoltwoodState.Bolt_Heater.ToString();
                txtWTPreassure.Text = ObsControl.objWSApp.BoltwoodState.Preassure.ToString();
                txtWTRGC.Text = RGC.ToString();
                txtWTWet.Text = Wet.ToString();

            }
            else if (HadWeatherData)
            {

                weatherSmallChart.Series["Temp"].Points.Add(EmptyP);
                weatherSmallChart.Series["CloudIdx"].Points.Add(EmptyP);

                chartWT.Series["Temp"].Points.Add(EmptyP);
                chartWT.Series["CloudIdx"].Points.Add(EmptyP);
                chartWT.Series["RGC"].Points.Add(EmptyP);
                chartWT.Series["Wet"].Points.Add(EmptyP);

                //Data in small widget
                txtTemp.Text = String.Empty;
                txtCloudState.Text = String.Empty;
                //Data in large widget
                txtWTTemp.Text = String.Empty;
                txtWTCloudIdx.Text = String.Empty;
                txtWTCaseTemp.Text = String.Empty;
                txtWTPreassure.Text = String.Empty;
                txtWTRGC.Text = String.Empty;
                txtWTWet.Text = String.Empty;
            }
            else
            {
                double ExternalTemp = Maxim_ExternalApplication.TEMP_MIN;
                if (ObsControl.ASCOMFocuser.FocuserTemp != Maxim_ExternalApplication.TEMP_MIN)
                {
                    ExternalTemp = ObsControl.ASCOMFocuser.FocuserTemp;
                }
                /*
                else if (ObsControl.objFocusMaxApp.FM_FocuserTemp!= Maxim_ExternalApplication.TEMP_MIN)
                {
                    ExternalTemp = ObsControl.objFocusMaxApp.FM_FocuserTemp;
                }
                */
                if (ExternalTemp != Maxim_ExternalApplication.TEMP_MIN)
                {
                    weatherSmallChart.Series["Temp"].Points.AddXY(DateTime.Now.ToOADate(), ExternalTemp);
                    chartWT.Series["Temp"].Points.AddXY(DateTime.Now.ToOADate(), ExternalTemp);

                    txtTemp.Text = ExternalTemp.ToString("N1");
                    txtWTTemp.Text = ExternalTemp.ToString("N1");
                }
            }

        }

    private bool HadTTCData = false; //was at least once data received?


    /// <summary>
    /// Update TelecopeTempControl state
    /// </summary>
    private void UpdateTelescopeTempControlData()
    {

        DateTime XVal;

        DataPoint EmptyP = new DataPoint { IsEmpty = true, XValue = DateTime.Now.AddSeconds(-5).ToOADate(), YValues = new double[] { 0 } };

        //Read TTC value
        if (ObsControl.objTTCApp.IsRunning() && ObsControl.objTTCApp.CMD_GetJSONData())
        //If there is a fresh data 
        {
            if (!HadTTCData)
            {
                Logging.AddLog("TelescopeTempControl connected", LogLevel.Activity);
            }
            HadTTCData = true; //flag, that at least one value was received

            //Data in small widget
            txtTTC_W_MainDelta.Text = (ObsControl.objTTCApp.TelescopeTempControl_State.DeltaTemp_Main >= 0 ? "+" : "") + Convert.ToString(Math.Round(ObsControl.objTTCApp.TelescopeTempControl_State.DeltaTemp_Main, 1));
            if (ObsControl.objTTCApp.TelescopeTempControl_State.AutoControl_FanSpeed)
            {
                txtTTC_W_MainDelta.BackColor = OnColor;
            }
            else
            {
                txtTTC_W_MainDelta.BackColor=SystemColors.Control;
            }
                
            txtTTC_W_SecondDelta.Text = (ObsControl.objTTCApp.TelescopeTempControl_State.DeltaTemp_Secondary >= 0 ? "+" : "") + Convert.ToString(Math.Round(ObsControl.objTTCApp.TelescopeTempControl_State.DeltaTemp_Secondary, 1));
            if (ObsControl.objTTCApp.TelescopeTempControl_State.AutoControl_Heater)
            {
                txtTTC_W_SecondDelta.BackColor = OnColor;
            }
            else
            {
                txtTTC_W_SecondDelta.BackColor = SystemColors.Control;
            }



            txtTTC_W_FanRPM.Text = ObsControl.objTTCApp.TelescopeTempControl_State.FAN_RPM.ToString();
            txtTTC_W_Heater.Text = Convert.ToString(Math.Round(ObsControl.objTTCApp.TelescopeTempControl_State.HeaterPower, 0))+"%"; 

            //Graphics
            XVal = ObsControl.objTTCApp.TelescopeTempControl_State.LastTimeDataParsed;
            //draw value
            if (ObsControl.objTTCApp.TelescopeTempControl_State.DeltaTemp_Main > -100)
            {
                chartTTC.Series["MainDelta"].Points.AddXY(XVal.ToOADate(), ObsControl.objTTCApp.TelescopeTempControl_State.DeltaTemp_Main);
            }
            else
            {
                chartTTC.Series["MainDelta"].Points.Add(EmptyP);
            }
            if (ObsControl.objTTCApp.TelescopeTempControl_State.FAN_RPM >= 0)
            {
                chartTTC.Series["FanRPM"].Points.AddXY(XVal.ToOADate(), ObsControl.objTTCApp.TelescopeTempControl_State.FAN_RPM);
            }
            else
            {
                chartTTC.Series["FanRPM"].Points.Add(EmptyP);
            }

            if (ObsControl.objTTCApp.TelescopeTempControl_State.DeltaTemp_Secondary > -100)
            {
                chartTTC.Series["SecondDelta"].Points.AddXY(XVal.ToOADate(), ObsControl.objTTCApp.TelescopeTempControl_State.DeltaTemp_Secondary);
            }
            else
            {
                chartTTC.Series["SecondDelta"].Points.Add(EmptyP);
            }
            if (ObsControl.objTTCApp.TelescopeTempControl_State.HeaterPower >= 0)
            {
                chartTTC.Series["Heater"].Points.AddXY(XVal.ToOADate(), ObsControl.objTTCApp.TelescopeTempControl_State.HeaterPower);
            }
            else
            {
                chartTTC.Series["Heater"].Points.Add(EmptyP);
            }

            //Display temp in Weather widget if no weather station detected
            if (!ObsControl.objWSApp.IsRunning())
            {
                double TempTTC = ObsControl.objTTCApp.TelescopeTempControl_State.Temp;
                txtTemp.Text = TempTTC.ToString();
                //draw value
                if (TempTTC > -100)
                {
                    weatherSmallChart.Series["Temp"].Points.AddXY(XVal.ToOADate(), TempTTC);
                }
                else
                {
                    weatherSmallChart.Series["Temp"].Points.Add(EmptyP);
                }
            }


            //Data in large widget
            txtTTC_Temp.Text = ObsControl.objTTCApp.TelescopeTempControl_State.Temp.ToString();
            txtTTC_Hum.Text = ObsControl.objTTCApp.TelescopeTempControl_State.Humidity.ToString();

            txtTTC_MainMirrorTemp.Text = ObsControl.objTTCApp.TelescopeTempControl_State.MainMirrorTemp.ToString();
            txtTTC_SecondMirrorTemp.Text = ObsControl.objTTCApp.TelescopeTempControl_State.SecondMirrorTemp.ToString();

            txtTTC_MainMirrorDelta.Text = ObsControl.objTTCApp.TelescopeTempControl_State.DeltaTemp_Main.ToString();
            txtTTC_SecondMirrorDelta.Text = ObsControl.objTTCApp.TelescopeTempControl_State.DeltaTemp_Secondary.ToString();

            txtTTC_FanPower.Text = ObsControl.objTTCApp.TelescopeTempControl_State.FAN_FPWM.ToString();
            txtTTC_HeaterPower.Text = ObsControl.objTTCApp.TelescopeTempControl_State.HeaterPower.ToString();
            txtTTC_FanRPM.Text = ObsControl.objTTCApp.TelescopeTempControl_State.FAN_RPM.ToString();
        }
        else if (HadTTCData)
        //If there is NO fresh data 
        {
            chartTTC.Series["MainDelta"].Points.Add(EmptyP);
            chartTTC.Series["FanRPM"].Points.Add(EmptyP);
            chartTTC.Series["SecondDelta"].Points.Add(EmptyP);
            chartTTC.Series["Heater"].Points.Add(EmptyP);

            //Data in small widget

            //Data in large widget
            txtTTC_Temp.Text = String.Empty;
            txtTTC_Hum.Text = String.Empty;

            txtTTC_MainMirrorTemp.Text = String.Empty;
            txtTTC_SecondMirrorTemp.Text = String.Empty;

            txtTTC_MainMirrorDelta.Text = String.Empty;
            txtTTC_SecondMirrorDelta.Text = String.Empty;

            txtTTC_FanPower.Text = String.Empty;
            txtTTC_HeaterPower.Text = String.Empty;
            txtTTC_FanRPM.Text = String.Empty;
        }

    }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endregion *** Update Weather And TelescopeTempControl Data *****************************************************************
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end of block  Update Weather And TelescopeTempControl Data 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#region *** Update AstroEvents *****************************************************************
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        /// <summary>
        /// Update times (Sideral, UTC, etc)
        /// </summary>
        private void UpdateTimePannel()
        {
            txtTime_local.Text = DateTime.Now.ToString("HH:mm:ss");
            txtTime_UTC.Text = DateTime.UtcNow.ToString("HH:mm:ss");
            txtTime_sideral.Text = AstroUtilsASCOM.ConvertToTimeString(AstroUtilsASCOM.NowLAST());

            txtTime_CurDate.Text = DateTime.Now.ToString("dd.MM.yyyy");
            txtTime_JD.Text = Math.Truncate(AstroUtilsASCOM.GetJD()).ToString("N0");
        }

        /// <summary>
        /// Update astro events
        /// </summary>
        private void UpdateAstronomyEvents()
        {
            txtEvents_SunSet.Text = AstroUtilsASCOM.ConvertToTimeString(AstroUtilsASCOM.SunSet());
            txtEvents_NautTwilBeg.Text = AstroUtilsASCOM.ConvertToTimeString(AstroUtilsASCOM.NautTwilightSet());
            txtEvents_AstrTwilBeg.Text = AstroUtilsASCOM.ConvertToTimeString(AstroUtilsASCOM.AstronTwilightSet());

            txtEvents_AstrTwilEnd.Text = AstroUtilsASCOM.ConvertToTimeString(AstroUtilsASCOM.AstronTwilightRise(1));
            txtEvents_NautTwilEnd.Text = AstroUtilsASCOM.ConvertToTimeString(AstroUtilsASCOM.NautTwilightRise(1));

            txtEvents_SunRise.Text = AstroUtilsASCOM.ConvertToTimeString(AstroUtilsASCOM.SunRise(1));


            txtEvents_MoonRise.Text = AstroUtilsASCOM.ConvertToTimeString(AstroUtilsASCOM.MoonRise());
            txtEvents_MoonSet.Text = AstroUtilsASCOM.ConvertToTimeString(AstroUtilsASCOM.MoonSet());
            txtEvents_MoonPhase.Text = AstroUtilsASCOM.MoonIllumination().ToString("P0");
        }

#endregion *** Update AstroEvents *****************************************************************
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end of block 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    }
}