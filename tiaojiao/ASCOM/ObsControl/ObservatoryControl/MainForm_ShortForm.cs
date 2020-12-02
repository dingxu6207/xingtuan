﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Diagnostics;
using System.Reflection;
using System.Configuration;
using System.Threading;

using ASCOM;
using ASCOM.DeviceInterface;
using ASCOM.Utilities;
using System.IO;
using System.Xml;
using System.Windows.Forms.DataVisualization.Charting;

namespace ObservatoryCenter
{
    /// <summary>
    /// Events handler for VISUAL ELEMENTS OF MAIN FORM
    ///  Contains events hadnlers of some controls
    /// </summary>
    public partial class MainForm
    {

        // ShortForm interface events
            #region //// ShortForm interface events  //////////////////////////////////////////////////

        private void chkPower_Click(object sender, EventArgs e)
        {
            if (((CheckBox)sender).BackColor != OnColor)
            {
                ObsControl.CommandParser.ParseSingleCommand2("POWER_ON");
            }
            else
            {
                ObsControl.CommandParser.ParseSingleCommand2("POWER_OFF");
            }
        }

        private void chkMaxim_Click(object sender, EventArgs e)
        {
            //always can press
            //because COM obj and real Maxim live in diffrent way
            if (((CheckBox)sender).BackColor != OnColor || true) 
            {
                LinkLabelLinkClickedEventArgs dummy = new LinkLabelLinkClickedEventArgs(linkMaximDL.Links[0]);
                linkMaximDL_LinkClicked(sender, dummy);
            }
        }

        private void chkPHD_Click(object sender, EventArgs e)
        {
            if (((CheckBox)sender).BackColor != OnColor)
            {
                LinkLabelLinkClickedEventArgs dummy;

                //run php2 && connect equipment
                dummy = new LinkLabelLinkClickedEventArgs(linkPHD2.Links[0]);
                linkPHD2_LinkClicked(sender, dummy);

                //run broker
                dummy = new LinkLabelLinkClickedEventArgs(linkPHDBroker.Links[0]);
                linkPHDBroker_LinkClicked(sender, dummy);

            }

        }

        private void chkCCDC_Click(object sender, EventArgs e)
        {
            if (!((CheckBox)sender).Checked && ((CheckBox)sender).BackColor != OnColor)
            {
                LinkLabelLinkClickedEventArgs dummy = new LinkLabelLinkClickedEventArgs(linkCCDC.Links[0]);
                linkCCDC_LinkClicked(sender, dummy);
            }

        }

        private void chkCoolerFlag_Click(object sender, EventArgs e)
        {
            if (ObsControl.objMaxim.IsRunning() && ObsControl.objMaxim.CameraConnected)
            {
                if  (!ObsControl.objMaxim.CameraCoolerOnStatus)
                {
                    ObsControl.objMaxim.CameraCoolingOn(); //switch on
                }
                else if (ObsControl.objMaxim.CameraCoolerOnStatus && ObsControl.objMaxim.CameraWarmpUpNow)
                {
                    ObsControl.objMaxim.CameraCoolingOff(); //switch off cooler
                }
                else if (ObsControl.objMaxim.CameraCoolerOnStatus && ObsControl.objMaxim.checkTempNearSetpoint())
                {
                    ObsControl.objMaxim.CameraCoolingOff(true); //warmup
                }
            }
        }

        private void chkMountPark_Click(object sender, EventArgs e)
        {
            btnPark_Click(sender, e);
        }
        private void chkMountTrack_Click(object sender, EventArgs e)
        {
            btnTrack_Click(sender, e);
        }


        private void chkRun_Click(object sender, EventArgs e)
        {
            if (!((CheckBox)sender).Checked)
            {
                //redirect to start button
                btnStartAll_Click(sender, e);
            }
        }


        /// <summary>
        /// Pause action
        /// </summary>
        private void chkPause_CheckedChanged(object sender, EventArgs e)
        {
            if (((CheckBox)sender).Checked)
            {
                ((CheckBox)sender).Checked = false;
                ((CheckBox)sender).BackColor = DefBackColor;

                //Switch off abort button
                chkAbort.BackColor = DefBackColor;
                btnEmergencyStop.BackColor = DefBackColor;

                //Resume run
                ObsControl.CommandParser.ParseSingleCommand2("IMAGING_RUN_RESUME",true);

                //toggle main window state
                btnSoftStop.BackColor = DefBackColor;
            }
            else
            {
                ((CheckBox)sender).Checked = true;
                ((CheckBox)sender).BackColor = OffColor;

                //Pause and park
                ObsControl.CommandParser.ParseSingleCommand2("IMAGING_RUN_PAUSE",true);

                //toggle main window state
                btnSoftStop.BackColor = OffColor;
            }
        }


        /// <summary>
        /// Abort action
        /// </summary>
        private void chkAbort_Click(object sender, EventArgs e)
        {
            if (((CheckBox)sender).Checked)
            {
                ((CheckBox)sender).BackColor = DefaultBackColor;
                ((CheckBox)sender).Checked = false;
                btnEmergencyStop.BackColor = DefaultBackColor;

                //toogle pause buttons
                chkPause.Checked = true;
                chkPause_CheckedChanged(chkPause, e);
                ObsControl.CommandParser.ParseSingleCommand2("IMAGING_RUN_ABORT_CANCEL", true);
            }
            else
            { 
                ((CheckBox)sender).BackColor = OffColor;
                ((CheckBox)sender).Checked = true;
                btnEmergencyStop.BackColor = OffColor;

                //toogle pause buttons
                chkPause.Checked = false;
                chkPause_CheckedChanged(chkPause, e);
                ObsControl.CommandParser.ParseSingleCommand2("IMAGING_RUN_ABORT",true);
            }
        }

        private void chkKill_Click(object sender, EventArgs e)
        {
            btnKILL_Click(sender, e);
        }



        #endregion // ShortForm interface events ////////////////////////////////////////////////
        // End of ShortForm interface events





    }
}
