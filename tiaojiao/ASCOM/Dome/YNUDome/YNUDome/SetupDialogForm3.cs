using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Runtime.InteropServices;
using System.Text;
using System.Windows.Forms;
using ASCOM.Utilities;
//using ASCOM.YNUDome;

using System.Net;

using System.Timers;
using System.IO;
using System.IO.Ports;
using System.Threading;
using System.Text.RegularExpressions;//������

namespace ASCOM.YNUDome
{
    [ComVisible(false)]					// Form not registered for COM!
    public partial class SetupDialogForm : Form
    {
        public SerialPort MySerialPort;
        public static string ComPort;
        public static int BaudRate;
        private byte[] buffer;
        //private string RecvBuffer;
        public bool FirstTime;

        public SetupDialogForm()
        {
            InitializeComponent();
            // Initialise current values of user settings from the ASCOM Profile
            //���ڳ�ʼ��Ҫ��UI֮ǰ����ΪUI��ʼ���е���
            MySerialPort = new SerialPort();
            BaudRate = 9600;
            buffer = new byte[1024];
            FirstTime = true;

            InitUI();

            if (!Dome.connectedState)
            {
                //��һ����ʱ��ִ�е�һ�δ��ڳ�ʼ�����������򿪻���
                System.Timers.Timer aTimer = new System.Timers.Timer();
                aTimer.Elapsed += new ElapsedEventHandler(FirstInit);
                aTimer.Interval = 200;
                aTimer.AutoReset = false;//ִ��һ�� false��һֱִ��true  
                //�Ƿ�ִ��System.Timers.Timer.Elapsed�¼�  
                aTimer.Enabled = true;
            }
        }
        private void FirstInit(object source, System.Timers.ElapsedEventArgs e)
        {
            if (comboBoxPortIP.Items.Count > 0)//��⵽���ڲ�ִ��
            {
                UartUninitial();
                UartInitial(); 
            }
            FirstTime = false;
        } 
        private void cmdOK_Click(object sender, EventArgs e) // OK button event handler
        {
            // Place any validation constraint checks here
            // Update the state variables with results from the dialogue
            //Dome.comPort = (string)comboBoxComPort.SelectedItem;
            Dome.tl.Enabled = chkTrace.Checked;
            if (Dome.connectedState)//������״̬�Ų���
                return;
            try
            {
                UartUninitial();

                Dome.ComPort = (string)comboBoxPortIP.SelectedItem;
                if ((textBoxMaxStep.Text!="")&&(Convert.ToInt32(textBoxMaxStep.Text)>0))
                {
                    Dome.m_MaxStep = Convert.ToInt32(textBoxMaxStep.Text);
                    Dome.m_MaxIncrement = Dome.m_MaxStep;
                }
                if ((textBoxStepSize.Text != "") && (Convert.ToSingle(textBoxStepSize.Text) > 0))
                    Dome.m_StepSize = Convert.ToSingle(textBoxStepSize.Text);
                if ((textBoxStepPerDeg.Text != "") && (Convert.ToSingle(textBoxStepPerDeg.Text) > 0))
                    Dome.m_TempCompRatio = Convert.ToSingle(textBoxStepPerDeg.Text);
                if ((textBoxThreshold.Text != "") && (Convert.ToSingle(textBoxThreshold.Text) > 0))
                    Dome.m_TempCompDegs = Convert.ToSingle(textBoxThreshold.Text);
                if (checkboxUseToolbox.Checked)
                    Dome.UseToolbox = true;
                else
                    Dome.UseToolbox = false;
                if (checkBoxLocalStorage.Checked)
                    Dome.LocalStorage = true;
                else
                    Dome.LocalStorage = false;
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
        }

        private void cmdCancel_Click(object sender, EventArgs e) // Cancel button event handler
        {
            if (!Dome.connectedState)//������״̬�Ų������ҷ�����ʱ�鿴���ô��ڵ��´��ڳ�ͻ
                UartUninitial();
            Close();
        }

        private void buttonRefresh_Click(object sender, EventArgs e)
        {
            //if (comboBoxPortIP.SelectedText!="")//��⵽���ڲ�ִ��
            {
                UartUninitial();
                UartInitial();
            }
        }

        private void SetupDialogForm_FormClosed(object sender, FormClosedEventArgs e)
        {
            if (!Dome.connectedState)
                UartUninitial();
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
            chkTrace.Checked = Dome.tl.Enabled;
            // set the list of com ports to those that are currently available
            /*
            comboBoxComPort.Items.Clear();
            comboBoxComPort.Items.AddRange(System.IO.Ports.SerialPort.GetPortNames());      // use System.IO because it's static
            // select the current port if possible
            if (comboBoxComPort.Items.Contains(Dome.comPort))
            {
                comboBoxComPort.SelectedItem = Dome.comPort;
            }
            */
            Display();
        }

        private void linkLabel_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            if ((Dome.m_DeviceOk) || (Dome.connectedState))
                System.Diagnostics.Process.Start("http://" + Dome.m_Website);
            else
            { 
                System.Diagnostics.Process.Start("http://www.fhxy.com");
                System.Diagnostics.Process.Start("http://www.graycode.cn");
            }
        }
        private void linkLabel1_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            System.Diagnostics.Process.Start("http://www.fhxy.com");
            System.Diagnostics.Process.Start("http://www.graycode.cn");
            //AboutBox MyAboutBox = new AboutBox();
            //MyAboutBox.Show();
        }
        private void Display()
        {
            comboBoxPortIP.Items.Clear();
            //label1.Text = "Com Port";
            comboBoxPortIP.Items.AddRange(System.IO.Ports.SerialPort.GetPortNames());      // use System.IO because it's static
            if (comboBoxPortIP.Items.Count > 0)
            {
                if (comboBoxPortIP.Items.Contains(Dome.ComPort))
                {
                    //comboBoxComPort.SelectedItem = Dome.comPort;
                    comboBoxPortIP.SelectedItem = Dome.ComPort;
                }
                else
                    comboBoxPortIP.SelectedIndex = 0;
            }
            if (Dome.connectedState)//����״̬���ɸ���
            {
                labelDevice.ForeColor = System.Drawing.Color.Black;
                labelDevice.Text = "Device: " + Dome.m_Device;
                labelVendor.Text = "Company: " + Dome.m_Vendor;
                linkLabel.Text = Dome.m_Website;
                labelEmail.Text = "Email: " + Dome.m_Email;
                labelTel.Text = "Tel: " + Dome.m_Tel;
                comboBoxPortIP.Enabled = false;
                textBoxMaxStep.Enabled = false;
                textBoxStepSize.Enabled = false;
                textBoxStepPerDeg.Enabled = false;
                textBoxThreshold.Enabled = false;
                checkboxUseToolbox.Enabled = false;
                checkBoxLocalStorage.Enabled = false;
                buttonRefresh.Enabled = false;
            }
            textBoxMaxStep.Text = Dome.m_MaxStep.ToString();
            textBoxStepSize.Text = Dome.m_StepSize.ToString("F2");

            textBoxStepPerDeg.Text = (Dome.m_TempCompRatio >= 0 ? "+" : "-") + Dome.m_TempCompRatio.ToString("F2");
            textBoxThreshold.Text = Dome.m_TempCompDegs.ToString();

            checkboxUseToolbox.Checked = Dome.UseToolbox;
            checkBoxLocalStorage.Checked = Dome.LocalStorage;

            
        }

        private void textBoxStepPerDeg_KeyPress(object sender, KeyPressEventArgs e)
        {
            Dome.OnlyEnterNumber(sender,e);
        }

        private void textBoxThreshold_KeyPress(object sender, KeyPressEventArgs e)
        {
            Dome.OnlyEnterPlusNumber(sender, e);
        }

        private void textBoxMaxStep_KeyPress(object sender, KeyPressEventArgs e)
        {
            Dome.OnlyEnterPlusInt(sender, e);
        }

        private void textBoxStepSize_KeyPress(object sender, KeyPressEventArgs e)
        {
            Dome.OnlyEnterPlusNumber(sender, e);
        }

        private void comboBoxPortIP_SelectedValueChanged(object sender, EventArgs e)
        {
            if (Dome.connectedState)//������״̬�Ų������ҷ�����ʱ�鿴���ô��ڵ��´��ڳ�ͻ
                return;
            if (!FirstTime)//��һ���ڽ����ʼ������ã��������򿪻���
            {
                UartUninitial();
                UartInitial();
            }
        }

        public void SendChkMsg()
        {
            byte[] SendBuf = new byte[7];
            SendBuf[0] = 0xA5;
            SendBuf[1] = 0x5A;
            SendBuf[2] = 0x01;
            SendBuf[3] = 0x00;
            SendBuf[4] = 0x00;
            SendBuf[5] = 0x00;
            SendBuf[6] = (byte)(SendBuf[2] + SendBuf[3] + SendBuf[4] + SendBuf[5]);
            UartSendMsg(SendBuf);
        }

        public void UartInitial()
        {
            try
            {
                if (MySerialPort.IsOpen)
                {
                    MessageBox.Show("MySerialPort.IsOpen");
                    MySerialPort.Close();
                }
                //ComPort = (string)comboBoxPortIP.SelectedItem;
                if (ComPort == "")
                    return;
                //MySerialPort.PortName = ComPort;
                MySerialPort.PortName = (string)comboBoxPortIP.SelectedItem;
                MySerialPort.DataBits = 8;
                MySerialPort.Parity = Parity.None;
                MySerialPort.StopBits = StopBits.One;
                MySerialPort.BaudRate = BaudRate;
                MySerialPort.NewLine = "\r\n";
                MySerialPort.DataReceived += new SerialDataReceivedEventHandler(UartRecvMsg);
                MySerialPort.Open();
                //��ѯ�汾��Ϣ
                Dome.m_DeviceOk = false;
                byte i=0,j=0;
                for (i = 0; i < 3; i++)
                {
                    SendChkMsg();
                    //Thread.Sleep(300);
                    for (j = 0; j < 60; j++)//ÿ��5mS��һ�Σ����ִ��60�Σ��ȴ�300mS��
                    {
                        if (Dome.m_DeviceOk)
                            break;
                        Thread.Sleep(5);
                    }
                    if (Dome.m_DeviceOk)
                            break;
                }
                if (Dome.m_DeviceOk)
                {
                    labelDevice.ForeColor = System.Drawing.Color.Black ;
                    labelDevice.Text = "Device: " + Dome.m_Device;
                    labelVendor.Text = "Company: " + Dome.m_Vendor;
                    linkLabel.Text = Dome.m_Website;
                    labelEmail.Text = "Email: " + Dome.m_Email;
                    labelTel.Text = "Tel: " + Dome.m_Tel;
                }
                else
                {
                    labelDevice.ForeColor = System.Drawing.Color.Red;
                    labelDevice.Text = "No device detected,Check connection and refresh!";
                    labelVendor.Text = "Developer: Graycode Team";
                    linkLabel.Text = "Graycode Team";
                    labelEmail.Text = "Email: graycode(at)qq.com";
                    labelTel.Text = "WeChat: graycode";
                }
            }
            //catch (IOException ex)
            catch (Exception ex)
            {
                Dome.m_DeviceOk = false;
                //MessageBox.Show(ex.ToString());
                labelDevice.ForeColor = System.Drawing.Color.Red;
                labelDevice.Text = "No device detected,Check connection and refresh!";
                labelVendor.Text = "Developer: Graycode Team";
                linkLabel.Text = "Graycode Team";
                labelEmail.Text = "Email: graycode(at)qq.com";
                labelTel.Text = "WeChat: graycode";
            }
        }

        public void UartUninitial()
        {
            try
            {
                if (MySerialPort.IsOpen)
                {
                    MySerialPort.BreakState = true;
                    MySerialPort.Close();
                    Thread.Sleep(200);
                }
            }
            //catch (IOException ex)
            catch (Exception ex)
            {
                //MessageBox.Show(ex.ToString());"Communication Error, Please Check !"
                labelDevice.ForeColor = System.Drawing.Color.Red;
                labelDevice.Text = "No device detected,Check connection and refresh!";
            }
        }

        public void UartSendMsg(byte[] Msg)
        {
            try
            {
                if (!MySerialPort.IsOpen)
                    MySerialPort.Open();
                MySerialPort.Write(Msg, 0, 7);
            }
            catch (IOException ex)//���ܵ������ڣ����򴮿��߰γ���һֱ��ʾ�޷��رտ������
            {
                //if (!m_ConnectError)//ֻ����һ��
                {
                    MessageBox.Show(ex.ToString());
                    //m_ConnectError = true;
                }
            }
        }

        private void UartRecvMsg(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
           // RecvBuffer = RecvBuffer + MySerialPort.ReadExisting();
           // ProcessCommand(RecvBuffer);
            byte recvbyte = (byte)MySerialPort.ReadByte();
            MessageBox.Show(recvbyte.ToString ());
        }
        /*
        public bool ProcessCommand(string command)
        {
            //�ж���Ч�ԣ�û���ж�����ð�ţ���#�ŵ������:123:222#����Ľ�
            string re1 = "(:)";	// Any Single Character 1
            string re2 = ".*?";	// Non-greedy match on filler
            string re3 = "(#)";	// Any Single Character 2
            string Pattern = re1 + re2 + re3;
            MatchCollection Matches = Regex.Matches(
                command,
                Pattern,
                RegexOptions.ExplicitCapture | RegexOptions.IgnoreCase    //��߼���Ч��  
                );
            if (Matches.Count > 0)
            {
                foreach (Match NextMatch in Matches)
                {
                    char cmd = Convert.ToChar(NextMatch.Value.Substring(1, 1));
                    string data = NextMatch.Value.Substring(2, NextMatch.Value.Length - 3);
                    switch (cmd)
                    {
                        case '?':
                            {
                                string[] TempArray = data.Split('~');
                                if ((TempArray.Length >= 5) && (TempArray[0] == "SS"))
                                {
                                    Dome.m_DeviceOk = true;
                                    Dome.m_Device = TempArray[1];
                                    Dome.m_Vendor = TempArray[2];
                                    Dome.m_Website = TempArray[3];
                                    Dome.m_Email = TempArray[4];
                                    Dome.m_Tel = TempArray[5];
                                }
                                break;
                            }
                        case 'i':
                            break;
                    }

                }
                RecvBuffer = "";//�����������
                return true;
            }
            else//��ƥ��ʱ�ж��Ƿ���ð�ţ��纬ð�ſ��ܴ���δ���
            {
                if (command.IndexOf(":") < 0)//��������������
                    RecvBuffer = "";
                //MessageBox.Show(RecvBuffer);
                return false;
            }
        }
         * */
    }
}