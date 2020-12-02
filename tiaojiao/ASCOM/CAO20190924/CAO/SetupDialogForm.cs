using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Runtime.InteropServices;
using System.Text;
using System.Windows.Forms;
using ASCOM.Utilities;
//using ASCOM.SSFocuser;

using System.Net;

namespace CAO
{
    [ComVisible(false)]					// Form not registered for COM!
    public partial class SetupDialogForm : Form
    {
        private byte MyDeviceType;
        public SetupDialogForm(byte DeviceType)
        {
            MyDeviceType = DeviceType;
            InitializeComponent();
            // Initialise current values of user settings from the ASCOM Profile
            InitUI();
        }

        private void cmdOK_Click(object sender, EventArgs e) // OK button event handler
        {
            // Place any validation constraint checks here
            // Update the state variables with results from the dialogue
            //Focuser.comPort = (string)comboBoxComPort.SelectedItem;
            if (tabControlProtocol.SelectedTab.Name == "tabPageASCOM")
            {              
                if (string.IsNullOrEmpty(textBoxASCOMDriverID.Text))
                {
                    MessageBox.Show("No Driver Selected");
                }
                else
                {
                    MainForm.DriverType[MyDeviceType] = 0;//ASCOM
                    MainForm.DriverID[MyDeviceType] = textBoxASCOMDriverID.Text;
                    this.DialogResult = DialogResult.OK; 
                }
            }
            else if (tabControlProtocol.SelectedTab.Name == "tabPageSerial")
            {
                MainForm.DriverType[MyDeviceType] = 1;//Serial
                MainForm.DriverID[MyDeviceType] = "Serial Device";
                this.DialogResult = DialogResult.OK;
            }
            else if (tabControlProtocol.SelectedTab.Name == "tabPageSocket")
            {
                MainForm.DriverType[MyDeviceType] = 2;//Socket
                MainForm.DriverID[MyDeviceType] = "Socket Device";
                this.DialogResult = DialogResult.OK;
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
            //chkTrace.Checked = Focuser.tl.Enabled;
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
            System.Diagnostics.Process.Start("http://www.fhxy.com");
        }

        private void Display()
        {
            comboBoxPort.Items.Clear();
            comboBoxPort.Items.AddRange(System.IO.Ports.SerialPort.GetPortNames());      // use System.IO because it's static
            if (comboBoxPort.Items.Count > 0)
            {
                /*
                if (comboBoxPortIP.Items.Contains(Focuser.ComPort))
                {
                    //comboBoxComPort.SelectedItem = Focuser.comPort;
                    comboBoxPortIP.SelectedItem = Focuser.ComPort;
                }
                else
                */
                comboBoxPort.SelectedIndex = 0;
                 
            }

            IPAddress[] addressList = Dns.GetHostEntry(Dns.GetHostName()).AddressList;
            if (addressList.Length > 0)
            {
                foreach (IPAddress add in addressList)
                {
                    comboBoxLocalIP.Items.Add(add.ToString());
                }
                foreach (IPAddress add in addressList)
                {
                    try
                    {
                        long a = add.ScopeId;//IPV6独有属性
                    }
                    catch
                    {
                        comboBoxLocalIP.SelectedItem = add.ToString();
                    }
                }
                //if (comboBoxLocalIP.Items.Contains(Focuser.LocalIP))
                //    comboBoxLocalIP.SelectedItem = Focuser.LocalIP;
                //else
                    comboBoxLocalIP.SelectedIndex = comboBoxLocalIP.Items.Count - 1;//选择最后一个
            }
            //textBoxMaxStep.Text = Focuser.m_MaxStep.ToString();
            //textBoxStepSize.Text = Focuser.m_StepSize.ToString("F2");

        }

        private void textBoxStepPerDeg_KeyPress(object sender, KeyPressEventArgs e)
        {
            //Focuser.OnlyEnterNumber(sender,e);
        }

        private void textBoxThreshold_KeyPress(object sender, KeyPressEventArgs e)
        {
            //Focuser.OnlyEnterPlusNumber(sender, e);
        }

        private void textBoxMaxStep_KeyPress(object sender, KeyPressEventArgs e)
        {
            //Focuser.OnlyEnterPlusInt(sender, e);
        }

        private void textBoxStepSize_KeyPress(object sender, KeyPressEventArgs e)
        {
            //Focuser.OnlyEnterPlusNumber(sender, e);
        }

        private void buttonASCOMChooser_Click(object sender, EventArgs e)
        {
            switch (MyDeviceType)
            {
                case 0:
                    textBoxASCOMDriverID.Text = ASCOM.DriverAccess.Camera.Choose(null);
                    break;
                case 1:
                    textBoxASCOMDriverID.Text = ASCOM.DriverAccess.Dome.Choose(null);
                    break;
                case 2:
                    textBoxASCOMDriverID.Text = ASCOM.DriverAccess.FilterWheel.Choose(null);
                    break;
                case 3:
                    textBoxASCOMDriverID.Text = ASCOM.DriverAccess.Focuser.Choose(null);
                    break;
                case 4:
                    textBoxASCOMDriverID.Text = ASCOM.DriverAccess.ObservingConditions.Choose(null);
                    break;
                case 5:
                    textBoxASCOMDriverID.Text = ASCOM.DriverAccess.Rotator.Choose(null);
                    break;
                case 6:
                    textBoxASCOMDriverID.Text = ASCOM.DriverAccess.Switch.Choose(null);
                    break;
                case 7:
                    textBoxASCOMDriverID.Text = ASCOM.DriverAccess.Telescope.Choose(null);
                    break;
            }
        }
    }
}