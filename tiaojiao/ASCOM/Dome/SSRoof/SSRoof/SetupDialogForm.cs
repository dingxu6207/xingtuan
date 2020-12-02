using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Runtime.InteropServices;
using System.Text;
using System.Windows.Forms;
using ASCOM.Utilities;
using ASCOM.SSRoof;

namespace ASCOM.SSRoof
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
            Dome.comPort = (string)comboBoxComPort.SelectedItem;
            Dome.RoofOperTime = Convert.ToUInt16(textBoxRoofOperTime.Text);
            Dome.BrakeTime = Convert.ToUInt16(textBoxBrakeTime.Text);
            Dome.OpenCode = textBoxOpenCode.Text;
            Dome.CloseCode = textBoxCloseCode.Text;
            Dome.StopCode = textBoxStopCode.Text;
            Dome.LockCode = textBoxLockCode.Text;
            Dome.UnlockCode = textBoxUnlockCode.Text;

            Dome.tl.Enabled = chkTrace.Checked;
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
            //chkTrace.Checked = Dome.tl.Enabled;
            // set the list of com ports to those that are currently available
            /*
            comboBoxComPort.Items.Clear();
            comboBoxComPort.Items.AddRange(System.IO.Ports.SerialPort.GetPortNames());      // use System.IO because it's static
            // select the current port if possible
            if (comboBoxComPort.Items.Contains(Dome.ComPort))
            {
                comboBoxComPort.SelectedItem = Dome.ComPort;
            }
            */
            Display();
        }

        private void Display()
        {
            if (Dome.connectedState)
                comboBoxComPort.Enabled = false;
            comboBoxComPort.Items.Clear();
            comboBoxComPort.Items.AddRange(System.IO.Ports.SerialPort.GetPortNames());      // use System.IO because it's static
            if (comboBoxComPort.Items.Count > 0)
            {
                if (comboBoxComPort.Items.Contains(Dome.comPort))
                {
                    comboBoxComPort.SelectedItem = Dome.comPort;
                }
                else
                    comboBoxComPort.SelectedIndex = 0;
            }
            textBoxOpenCode.Text = Dome.OpenCode;
            textBoxCloseCode.Text = Dome.CloseCode;
            textBoxStopCode.Text = Dome.StopCode;
            textBoxLockCode.Text = Dome.LockCode;
            textBoxUnlockCode.Text = Dome.UnlockCode;
            textBoxRoofOperTime.Text = Dome.RoofOperTime.ToString();
            textBoxBrakeTime.Text = Dome.BrakeTime.ToString();
            
        }
        // 只能输入数字（含负号小数点）
        public static void OnlyEnterNumber(object sender, KeyPressEventArgs e)
        {
            if ((e.KeyChar < 48 || e.KeyChar > 57) && e.KeyChar != 8 && e.KeyChar != 13 && e.KeyChar != 45 && e.KeyChar != 46)
            {
                e.Handled = true;
            }

            //输入为负号时，只能输入一次且只能输入一次
            if (e.KeyChar == 45 && (((TextBox)sender).SelectionStart != 0 || ((TextBox)sender).Text.IndexOf("-") >= 0)) e.Handled = true;
            if (e.KeyChar == 46 && ((TextBox)sender).Text.IndexOf(".") >= 0) e.Handled = true;
        }
        // 只能输入正实数
        public static void OnlyEnterPlusNumber(object sender, KeyPressEventArgs e)
        {
            if ((e.KeyChar < 48 || e.KeyChar > 57) && e.KeyChar != 8 && e.KeyChar != 13 && e.KeyChar != 46)
            {
                e.Handled = true;
            }
            if (e.KeyChar == 46 && ((TextBox)sender).Text.IndexOf(".") >= 0) e.Handled = true;
        }
        // 只能输入整数
        public static void OnlyEnterInt(object sender, KeyPressEventArgs e)
        {
            if ((e.KeyChar < 48 || e.KeyChar > 57) && e.KeyChar != 8 && e.KeyChar != 13 && e.KeyChar != 45)
            {
                e.Handled = true;
            }

            //输入为负号时，只能输入一次且只能输入一次
            if (e.KeyChar == 45 && (((TextBox)sender).SelectionStart != 0 || ((TextBox)sender).Text.IndexOf("-") >= 0)) e.Handled = true;
        }
        // 只能输入正整数
        public static void OnlyEnterPlusInt(object sender, KeyPressEventArgs e)
        {
            if ((e.KeyChar < 48 || e.KeyChar > 57) && e.KeyChar != 8 && e.KeyChar != 13)
            {
                e.Handled = true;
            }
        }

        private void textBoxRoofOperTime_KeyPress(object sender, KeyPressEventArgs e)
        {
            OnlyEnterPlusInt(sender, e);
        }

        private void textBoxBrakeTime_KeyPress(object sender, KeyPressEventArgs e)
        {
            OnlyEnterPlusInt(sender, e);
        }

        private void linkLabel1_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            System.Diagnostics.Process.Start("http://www.fhxy.com");
        }
    }
}