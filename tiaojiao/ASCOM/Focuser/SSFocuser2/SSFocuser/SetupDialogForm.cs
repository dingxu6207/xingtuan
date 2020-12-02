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

using System.Timers;
using System.IO;
using System.IO.Ports;
using System.Threading;
using System.Text.RegularExpressions;//������

namespace ASCOM.SSFocuser
{
    [ComVisible(false)]					// Form not registered for COM!
    public partial class SetupDialogForm : Form
    {
        public SerialPort MySerialPort;
        public static string ComPort;
        public static int BaudRate;
        private byte[] buffer;
        private string RecvBuffer;
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
            if (!Focuser.connectedState)
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
            if (comboBoxcomPort.Items.Count > 0)//��⵽���ڲ�ִ��
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
            //Focuser.comPort = (string)comboBoxComPort.SelectedItem;
            Focuser.tl.Enabled = chkTrace.Checked;
            if (Focuser.connectedState)//������״̬�Ų���
                return;
            try
            {
                UartUninitial();

                Focuser.comPort = (string)comboBoxcomPort.SelectedItem;
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
                if (checkBoxUseToolbox.Checked)
                    Focuser.UseToolbox = true;
                else
                    Focuser.UseToolbox = false;
                if (checkBoxLocalStorage.Checked)
                    Focuser.LocalStorage = true;
                else
                    Focuser.LocalStorage = false;
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
        }

        private void cmdCancel_Click(object sender, EventArgs e) // Cancel button event handler
        {
            if (!Focuser.connectedState)//������״̬�Ų������ҷ�����ʱ�鿴���ô��ڵ��´��ڳ�ͻ
                UartUninitial();
            Close();
        }

        private void buttonRefresh_Click(object sender, EventArgs e)
        {
            //if (comboBoxcomPort.SelectedText!="")//��⵽���ڲ�ִ��
            {
                UartUninitial();
                UartInitial();
            }
        }

        private void SetupDialogForm_FormClosed(object sender, FormClosedEventArgs e)
        {
            if (!Focuser.connectedState)
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
            if ((Focuser.m_DeviceOk) || (Focuser.connectedState))
                System.Diagnostics.Process.Start("http://" + Focuser.m_Website);
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
            comboBoxcomPort.Items.Clear();
            //label1.Text = "Com Port";
            comboBoxcomPort.Items.AddRange(System.IO.Ports.SerialPort.GetPortNames());      // use System.IO because it's static
            if (comboBoxcomPort.Items.Count > 0)
            {
                if (comboBoxcomPort.Items.Contains(Focuser.comPort))
                {
                    //comboBoxComPort.SelectedItem = Focuser.comPort;
                    comboBoxcomPort.SelectedItem = Focuser.comPort;
                }
                else
                    comboBoxcomPort.SelectedIndex = 0;
            }
            if (Focuser.connectedState)//����״̬���ɸ���
            {
                labelDevice.ForeColor = System.Drawing.Color.Black;
                labelDevice.Text = "Device: " + Focuser.m_Device;
                labelVendor.Text = "Company: " + Focuser.m_Vendor;
                linkLabel.Text = Focuser.m_Website;
                labelEmail.Text = "Email: " + Focuser.m_Email;
                labelTel.Text = "Tel: " + Focuser.m_Tel;
                comboBoxcomPort.Enabled = false;
                textBoxMaxStep.Enabled = false;
                textBoxStepSize.Enabled = false;
                textBoxStepPerDeg.Enabled = false;
                textBoxThreshold.Enabled = false;
                checkBoxUseToolbox.Enabled = false;
                checkBoxLocalStorage.Enabled = false;
                buttonRefresh.Enabled = false;
            }
            textBoxMaxStep.Text = Focuser.m_MaxStep.ToString();
            textBoxStepSize.Text = Focuser.m_StepSize.ToString("F2");

            textBoxStepPerDeg.Text = (Focuser.m_TempCompRatio >= 0 ? "+" : "-") + Focuser.m_TempCompRatio.ToString("F2");
            textBoxThreshold.Text = Focuser.m_TempCompDegs.ToString();

            checkBoxUseToolbox.Checked = Focuser.UseToolbox;
            checkBoxLocalStorage.Checked = Focuser.LocalStorage;

            
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

        private void comboBoxPortIP_SelectedValueChanged(object sender, EventArgs e)
        {
            if (Focuser.connectedState)//������״̬�Ų������ҷ�����ʱ�鿴���ô��ڵ��´��ڳ�ͻ
                return;
            if (!FirstTime)//��һ���ڽ����ʼ������ã��������򿪻���
            {
                UartUninitial();
                UartInitial();
            }
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
                //ComPort = (string)comboBoxcomPort.SelectedItem;
                if (ComPort == "")
                    return;
                //MySerialPort.PortName = ComPort;
                MySerialPort.PortName = (string)comboBoxcomPort.SelectedItem;
                MySerialPort.DataBits = 8;
                MySerialPort.Parity = Parity.None;
                MySerialPort.StopBits = StopBits.One;
                MySerialPort.BaudRate = BaudRate;
                MySerialPort.NewLine = "\r\n";
                MySerialPort.DataReceived += new SerialDataReceivedEventHandler(UartRecvMsg);
                MySerialPort.Open();
                //��ѯ�汾��Ϣ
                Focuser.m_DeviceOk = false;
                byte i=0,j=0;
                for (i = 0; i < 3; i++)
                {
                    UartSendMsg(":F?#");
                    //Thread.Sleep(300);
                    for (j = 0; j < 60; j++)//ÿ��5mS��һ�Σ����ִ��60�Σ��ȴ�300mS��
                    {
                        if (Focuser.m_DeviceOk)
                            break;
                        Thread.Sleep(5);
                    }
                    if (Focuser.m_DeviceOk)
                            break;
                }
                if (Focuser.m_DeviceOk)
                {
                    labelDevice.ForeColor = System.Drawing.Color.Black ;
                    labelDevice.Text = "Device: " + Focuser.m_Device;
                    labelVendor.Text = "Company: " + Focuser.m_Vendor;
                    linkLabel.Text = Focuser.m_Website;
                    labelEmail.Text = "Email: " + Focuser.m_Email;
                    labelTel.Text = "Tel: " + Focuser.m_Tel;
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
                Focuser.m_DeviceOk = false;
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

        public void UartSendMsg(string Msg)
        {
            try
            {
                if (MySerialPort.IsOpen)
                    MySerialPort.Write(Msg);
            }
            catch (IOException ex)//���ܵ������ڣ����򴮿��߰γ���һֱ��ʾ�޷��رտ������
            {
                MessageBox.Show(ex.ToString());
            }
        }

        private void UartRecvMsg(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            RecvBuffer = RecvBuffer + MySerialPort.ReadExisting();
            ProcessCommand(RecvBuffer);
        }

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
                                    Focuser.m_DeviceOk = true;
                                    Focuser.m_Device = TempArray[1];
                                    Focuser.m_Vendor = TempArray[2];
                                    Focuser.m_Website = TempArray[3];
                                    Focuser.m_Email = TempArray[4];
                                    Focuser.m_Tel = TempArray[5];
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
    }
}