using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Runtime.InteropServices;
using System.Text;
using System.Windows.Forms;
using ASCOM.Utilities;
using ASCOM.SSFC;

namespace ASCOM.SSFC
{
    [ComVisible(false)]					// Form not registered for COM!
    public partial class SetupDialogForm : Form
    {
        Dome MyDome = new Dome();//graycode

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
            Dome.ComPort = (string)comboBoxComPort.SelectedItem;
            //MessageBox.Show(comboBoxComPort.SelectedItem.ToString());
            MyDome.WriteValue("ComPort", comboBoxComPort.SelectedItem.ToString());
            MyDome.WriteValue("Open", textBoxOpen.Text);
            MyDome.WriteValue("Shut", textBoxShut.Text);
            MyDome.WriteValue("Stop", textBoxStop.Text);
            MyDome.WriteValue("Lock", textBoxLock.Text);
            MyDome.WriteValue("Time", comboBoxTime.SelectedItem.ToString());
            //Dome.tl.Enabled = chkTrace.Checked;
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
            comboBoxComPort.Items.Clear();
            comboBoxComPort.Items.AddRange(System.IO.Ports.SerialPort.GetPortNames());      // use System.IO because it's static
            if (comboBoxComPort.Items.Count > 0)
            {
                if (comboBoxComPort.Items.Contains(MyDome.ReadValue("ComPort", "COM1")))
                {
                    comboBoxComPort.SelectedItem = MyDome.ReadValue("ComPort", "COM1");
                }
                else
                    comboBoxComPort.SelectedIndex = 0;
            }

            textBoxOpen.Text = MyDome.ReadValue("Open", "FD 7D 9E 98 6B DF");
            textBoxShut.Text = MyDome.ReadValue("Shut", "FD 7D 9E 94 6B DF");
            textBoxStop.Text = MyDome.ReadValue("Stop", "FD 7D 9E 92 6B DF");
            textBoxLock.Text = MyDome.ReadValue("Lock", "FD 7D 9E 91 6B DF");
            //textBoxTime.Text = MyDome.ReadValue("Time", "02");
            for( int i=0;i<comboBoxTime.Items.Count;i++)
            {
                if(comboBoxTime.Items[i].ToString().Equals(MyDome.ReadValue("Time", "02")))
                {
                    comboBoxTime.SelectedIndex=i;
                    break;
                }
            }
        }
    }
}