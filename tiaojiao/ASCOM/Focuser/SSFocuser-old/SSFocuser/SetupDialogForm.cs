using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Runtime.InteropServices;
using System.Text;
using System.Windows.Forms;
using ASCOM.Utilities;
using ASCOM.SSFocuser;

using System.Net;

namespace ASCOM.SSFocuser
{
    [ComVisible(false)]					// Form not registered for COM!
    public partial class SetupDialogForm : Form
    {
        public SetupDialogForm()
        {
            InitializeComponent();
            // Initialise current values of user settings from the ASCOM Profile
            InitUI();
        }

        private void cmdOK_Click(object sender, EventArgs e) // OK button event handler
        {
            // Place any validation constraint checks here
            // Update the state variables with results from the dialogue
            //Focuser.comPort = (string)comboBoxComPort.SelectedItem;
            Focuser.tl.Enabled = chkTrace.Checked;

            try
            {
              
                Focuser.ComPort = (string)comboBoxPortIP.SelectedItem;
                if ((textBoxMaxStep.Text!="")&&(Convert.ToInt32(textBoxMaxStep.Text)>0))
                {
                    Focuser.m_MaxStep = Convert.ToInt32(textBoxMaxStep.Text);
                    Focuser.m_MaxIncrement = Focuser.m_MaxStep;
                }
                if ((textBoxStepSize.Text != "") && (Convert.ToSingle(textBoxStepSize.Text) > 0))
                    Focuser.m_StepSize = Convert.ToSingle(textBoxStepSize.Text);
                if ((textBoxStepPerDeg.Text != "") && (Convert.ToSingle(textBoxStepPerDeg.Text) > 0))
                    Focuser.m_TempCompRatio = Convert.ToSingle(textBoxStepPerDeg.Text);
                if ((textBoxThreshold.Text != "") && (Convert.ToSingle(textBoxThreshold.Text) > 0))
                    Focuser.m_TempCompDegs = Convert.ToSingle(textBoxThreshold.Text);
                if (checkboxUseToolbox.Checked)
                    Focuser.UseToolbox = true;
                else
                    Focuser.UseToolbox = false;
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
        }

        private void cmdCancel_Click(object sender, EventArgs e) // Cancel button event handler
        {
            Close();
        }

        private void BrowseToAscom(object sender, EventArgs e) // Click on ASCOM logo event handler
        {
            try
            {
                System.Diagnostics.Process.Start("http://ascom-standards.org/");
            }
            catch (System.ComponentModel.Win32Exception noBrowser)
            {
                if (noBrowser.ErrorCode == -2147467259)
                    MessageBox.Show(noBrowser.Message);
            }
            catch (System.Exception other)
            {
                MessageBox.Show(other.Message);
            }
        }

        private void InitUI()
        {
            chkTrace.Checked = Focuser.tl.Enabled;
            // set the list of com ports to those that are currently available
            /*
            comboBoxComPort.Items.Clear();
            comboBoxComPort.Items.AddRange(System.IO.Ports.SerialPort.GetPortNames());      // use System.IO because it's static
            // select the current port if possible
            if (comboBoxComPort.Items.Contains(Focuser.comPort))
            {
                comboBoxComPort.SelectedItem = Focuser.comPort;
            }
            */
            Display();
        }

        private void linkLabel_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            System.Diagnostics.Process.Start("http://www.sky-rover.com");
        }
        private void Display()
        {
            comboBoxPortIP.Items.Clear();
            label1.Text = "Com Port";
            comboBoxPortIP.Items.AddRange(System.IO.Ports.SerialPort.GetPortNames());      // use System.IO because it's static
            if (comboBoxPortIP.Items.Count > 0)
            {
                if (comboBoxPortIP.Items.Contains(Focuser.ComPort))
                {
                    //comboBoxComPort.SelectedItem = Focuser.comPort;
                    comboBoxPortIP.SelectedItem = Focuser.ComPort;
                }
                else
                    comboBoxPortIP.SelectedIndex = 0;
            }
            textBoxMaxStep.Text = Focuser.m_MaxStep.ToString();
            textBoxStepSize.Text = Focuser.m_StepSize.ToString("F2");

            textBoxStepPerDeg.Text = (Focuser.m_TempCompRatio>=0?"+":"-")+Focuser.m_TempCompRatio.ToString("F2");
            textBoxThreshold.Text = Focuser.m_TempCompDegs.ToString();

            checkboxUseToolbox.Checked = Focuser.UseToolbox;
        }

        private void textBoxStepPerDeg_KeyPress(object sender, KeyPressEventArgs e)
        {
            Focuser.OnlyEnterNumber(sender,e);
        }

        private void textBoxThreshold_KeyPress(object sender, KeyPressEventArgs e)
        {
            Focuser.OnlyEnterPlusNumber(sender, e);
        }

        private void textBoxMaxStep_KeyPress(object sender, KeyPressEventArgs e)
        {
            Focuser.OnlyEnterPlusInt(sender, e);
        }

        private void textBoxStepSize_KeyPress(object sender, KeyPressEventArgs e)
        {
            Focuser.OnlyEnterPlusNumber(sender, e);
        }
    }
}