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
using System.Text.RegularExpressions;//正则表达

namespace ASCOM.SSFocuser
{
    [ComVisible(false)]					// Form not registered for COM!
    public partial class SetupDialogForm : Form
    {
        public SerialPort MySerialPort;
        //public static string ComPort;
        public static int BaudRate;
        private string RecvBuf;
        private int BChar = -1;
        private int EChar = -1;
        public char m_rCmd;
        public bool FirstTime;
        private string ErrorInfo;

        public SetupDialogForm()
        {
            InitializeComponent();
            // Initialise current values of user settings from the ASCOM Profile
            //串口初始化要在UI之前，因为UI初始化有调用
            MySerialPort = new SerialPort();
            BaudRate = 9600;
            FirstTime = true;

            InitUI();
            if (!Focuser.connectedState)//用一个定时器执行第一次串口初始化，避免界面打开缓慢
            {
                System.Timers.Timer aTimer = new System.Timers.Timer();
                aTimer.Elapsed += new ElapsedEventHandler(FirstInit);
                aTimer.Interval = 200;
                aTimer.AutoReset = false;//执行一次 false，一直执行true  
                //是否执行System.Timers.Timer.Elapsed事件  
                aTimer.Enabled = true;
            }
        }
        private void FirstInit(object source, System.Timers.ElapsedEventArgs e)
        {
            if (comboBoxcomPort.Items.Count > 0)//检测到串口才执行
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
            if (Focuser.connectedState)//非连接状态才操作
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
                /*
                if ((textBoxStepPerDeg.Text != "") && (Convert.ToSingle(textBoxStepPerDeg.Text) > 0))
                    Focuser.m_TempCompRatio = Convert.ToSingle(textBoxStepPerDeg.Text);
                if ((textBoxThreshold.Text != "") && (Convert.ToSingle(textBoxThreshold.Text) > 0))
                    Focuser.m_TempCompDegs = Convert.ToSingle(textBoxThreshold.Text);
               */
                Focuser.UseToolbox = checkBoxUseToolbox.Checked;
                Focuser.InitFocuser = checkBoxInitFocuser.Checked;
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
        }

        private void cmdCancel_Click(object sender, EventArgs e) // Cancel button event handler
        {
            if (!Focuser.connectedState)//非连接状态才操作，乙方连接时查看设置串口导致串口冲突
                UartUninitial();
            Close();
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
                OpenJoinUsForm();
            }
        }
        private void linkLabelJoinUs_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            OpenJoinUsForm();
        }
        private void OpenJoinUsForm()
        {
            Form OpenedForm = Application.OpenForms["JoinUsForm"];  //查找是否打开过about窗体  
            if ((OpenedForm == null) || (OpenedForm.IsDisposed)) //如果没有打开过
            {
                JoinUsForm MyJoinUsForm = new JoinUsForm();
                MyJoinUsForm.Show();   //打开子窗体出来
            }
            else
            {
                OpenedForm.Activate(); //如果已经打开过就让其获得焦点  
                OpenedForm.WindowState = FormWindowState.Normal;//使Form恢复正常窗体大小
            }
        }
        private void Display()
        {
            comboBoxcomPort.Items.Clear();
            comboBoxcomPort.Items.AddRange(System.IO.Ports.SerialPort.GetPortNames());      // use System.IO because it's static
            if (comboBoxcomPort.Items.Count > 0)
            {
                if (comboBoxcomPort.Items.Contains(Focuser.comPort))
                {
                    comboBoxcomPort.SelectedItem = Focuser.comPort;
                }
                else
                    comboBoxcomPort.SelectedIndex = 0;
            }
            if (Focuser.connectedState)//连接状态不可更改
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
                //textBoxStepPerDeg.Enabled = false;
                //textBoxThreshold.Enabled = false;
                checkBoxUseToolbox.Enabled = false;
                checkBoxInitFocuser.Enabled = false;
                chkTrace.Enabled = false;
            }
            textBoxMaxStep.Text = Focuser.m_MaxStep.ToString();
            textBoxStepSize.Text = Focuser.m_StepSize.ToString("F2");

            //textBoxStepPerDeg.Text = (Focuser.m_TempCompRatio >= 0 ? "+" : "-") + Focuser.m_TempCompRatio.ToString("F2");
            //textBoxThreshold.Text = Focuser.m_TempCompDegs.ToString();

            checkBoxUseToolbox.Checked = Focuser.UseToolbox;
            checkBoxInitFocuser.Checked = Focuser.InitFocuser;  
        }

        private void comboBoxcomPort_SelectedValueChanged(object sender, EventArgs e)
        {
            if (Focuser.connectedState)//非连接状态才操作，乙方连接时查看设置串口导致串口冲突
                return;
            if (!FirstTime)//第一次在界面初始化后调用，避免界面打开缓慢
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
                    MySerialPort.Close();
                MySerialPort.PortName = (string)comboBoxcomPort.SelectedItem;
                MySerialPort.DataBits = 8;
                MySerialPort.Parity = Parity.None;
                MySerialPort.StopBits = StopBits.One;
                MySerialPort.BaudRate = BaudRate;
                MySerialPort.NewLine = "\r\n";
                MySerialPort.DataReceived += new SerialDataReceivedEventHandler(UartRecvMsg);
                MySerialPort.Open();
                //查询版本信息
                Focuser.m_DeviceOk = false;
                byte i=0,j=0;
                for (i = 0; i < 3; i++)
                {
                    UartSendMsg(":F?#");
                    //Thread.Sleep(300);
                    for (j = 0; j < 60; j++)//每个5mS查一次，最长可执行60次（等待300mS）
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
                ErrorInfo = ex.ToString();
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
                ErrorInfo = ex.ToString();
            }
        }

        public void UartSendMsg(string Msg)
        {
            try
            {
                if (MySerialPort.IsOpen)
                    MySerialPort.Write(Msg);
            }
            catch (IOException ex)//不能弹出窗口，否则串口线拔出后一直提示无法关闭控制软件
            {
                MessageBox.Show(ex.ToString());
            }
        }
        
        public void UartRecvMsg(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            try
            {
                RecvBuf = RecvBuf + MySerialPort.ReadExisting();
                for (int i = 0; i < RecvBuf.Length; i++)//可能有多条命令
                {
                    if (RecvBuf[i] == ':')//找到协议头
                        BChar = i;
                    if (RecvBuf[i] == '#')//找到协议尾
                        EChar = i;
                    if ((BChar >= 0) && (EChar > BChar))//找到一条完整命令
                    {
                        //m_rCmd = RecvBuf[BChar + 1];//当前返回命令标志位
                        //string data = RecvBuf.Substring(BChar + 2, EChar - BChar - 2);
                        //处理数据
                        ProcessData(RecvBuf.Substring(BChar, EChar - BChar + 1));
                        BChar = -1;
                        EChar = -1;
                    }
                }
                if (BChar < 0)//找不到协议头
                    RecvBuf = "";
                else
                {
                    RecvBuf = RecvBuf.Substring(BChar, RecvBuf.Length - BChar);
                }
                if (RecvBuf.Length >= 256)//避免有一个冒号的非命令字节堵塞
                    RecvBuf = "";
                //MessageBox.Show(RecvBuf.ToString());
                BChar = -1;
                EChar = -1;
            }
            catch (Exception ex)
            {
                //MessageBox.Show(ex.ToString());
                ErrorInfo = ex.ToString();
            }
        }
        private void ProcessData(string data)
        {
            m_rCmd = data[1];//当前返回命令标志位
            data = data.Substring(2, data.Length - 3);
            switch (m_rCmd)
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
                    {
                        break;
                    }
            }
        }
        private void textBoxStepPerDeg_KeyPress(object sender, KeyPressEventArgs e)
        {
            Focuser.OnlyEnterNumber(sender, e);
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