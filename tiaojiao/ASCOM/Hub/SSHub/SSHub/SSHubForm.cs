using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

//引用
using System.IO;
using System.IO.Ports;
using System.Timers;
using System.Threading;


namespace SSHub
{
    public partial class SSHubForm : Form
    {
        //串口
        private SerialPort MySerialPort;
        internal static string comPort; // 串口号
        internal static int baudRate; // 波特率
        private string RecvBuf;//接收字符串缓存
        private int BChar = -1;
        private int EChar = -1;
        public char m_rCmd;
        private string ErrorInfo;
        private static string data;
        //设备信息
        public static bool m_DeviceOk;
        public static string m_Device, m_Vendor, m_Website, m_Email, m_Tel;
        private CheckBox[] ChkBoxDC, ChkBoxUSB;
        //线程处理显示问题
        System.Timers.Timer aTimer;

        public SSHubForm()
        {
            InitializeComponent();
            Control.CheckForIllegalCrossThreadCalls = false;
            comPort = "";
            baudRate = 9600;
            MySerialPort = new SerialPort();
            CheckcomPort();
            ChkBoxDC = new CheckBox[6];
            ChkBoxUSB = new CheckBox[6];
            ChkBoxDC[0] = checkBoxDC1; ChkBoxDC[1] = checkBoxDC2; ChkBoxDC[2] = checkBoxDC3;
            ChkBoxDC[3] = checkBoxDC4; ChkBoxDC[4] = checkBoxDC5; ChkBoxDC[5] = checkBoxDC6;
            ChkBoxUSB[0] = checkBoxUSB1; ChkBoxUSB[1] = checkBoxUSB2; ChkBoxUSB[2] = checkBoxUSB3;
            ChkBoxUSB[3] = checkBoxUSB4; ChkBoxUSB[4] = checkBoxUSB5; ChkBoxUSB[5] = checkBoxUSB6;
            for (byte i = 0; i < 6; i++)
            {
                ChkBoxDC[i].Checked = false;
                ChkBoxDC[i].BackColor = Color.Gray;
                ChkBoxUSB[i].Checked = false;
                ChkBoxUSB[i].BackColor = Color.Gray;
            }
            data = "000000000000";
            buttonUpdate.Enabled = false;
            aTimer = new System.Timers.Timer();
            aTimer.Elapsed += new ElapsedEventHandler(DisplayFun);
            aTimer.Interval = 500;
            aTimer.AutoReset = true;//执行一次 false，一直执行true  
            //是否执行System.Timers.Timer.Elapsed事件  
            aTimer.Enabled = true;
        }
        //串口选择
        private void comboBoxComPort_SelectedIndexChanged(object sender, EventArgs e)
        {
            UartUninitial();
            UartInitial();
        }
        //网站链接
        private void linkLabel_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            if (m_DeviceOk)
                System.Diagnostics.Process.Start("http://" + m_Website);
        }
        //保存数据到Hub
        private void SSHubForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (m_DeviceOk)
            {
                //aTimer.Close();
                SaveData();
            }
        }
        //更新函数
        private void buttonUpdate_Click(object sender, EventArgs e)
        {
            for (byte i = 0; i < 6; i++)
            {
                if ((ChkBoxDC[i].Checked) && (ChkBoxDC[i].BackColor != Color.Green))
                {
                    OpenDC(i + 1);
                }
                else if ((!ChkBoxDC[i].Checked) && (ChkBoxDC[i].BackColor != Color.Red))
                {
                    CloseDC(i + 1);
                }
                if ((ChkBoxUSB[i].Checked) && (ChkBoxUSB[i].BackColor != Color.Green))
                {
                    OpenUSB(i + 1);
                }
                else if ((!ChkBoxUSB[i].Checked) && (ChkBoxUSB[i].BackColor != Color.Red))
                {
                    CloseUSB(i + 1);
                }
            }
            Thread.Sleep(250);
            CheckState();
        }

        #region User Properties and methods

        //////////////graycode//////////////
        //检查电脑串口
        private void CheckcomPort()
        {
            comboBoxcomPort.Items.Clear();
            comboBoxcomPort.Items.AddRange(System.IO.Ports.SerialPort.GetPortNames());      // use System.IO because it's static
            if (comboBoxcomPort.Items.Count > 0)
            {
                comboBoxcomPort.SelectedIndex = 0;
            }
        }
        //定时器函数
        private void DisplayFun(object source, System.Timers.ElapsedEventArgs e)
        {
            if (m_DeviceOk)
            {
                for (byte i = 0; i < 6; i++)//更新状态，关闭用红色表示，打开用绿色表示
                {
                    if ((data[i] == '0') && (ChkBoxDC[i].BackColor != Color.Red))
                    {
                        ChkBoxDC[i].BackColor = Color.Red;
                        ChkBoxDC[i].Checked = false;
                    }
                    else if ((data[i] == '1') && (ChkBoxDC[i].BackColor != Color.Green))
                    {
                        ChkBoxDC[i].BackColor = Color.Green;
                        ChkBoxDC[i].Checked = true;
                    }
                    if ((data[6 + i] == '0') && (ChkBoxUSB[i].BackColor != Color.Red))
                    {
                        ChkBoxUSB[i].BackColor = Color.Red;
                        ChkBoxUSB[i].Checked = false;
                    }
                    else if ((data[6 + i] == '1') && (ChkBoxUSB[i].BackColor != Color.Green))
                    {
                        ChkBoxUSB[i].BackColor = Color.Green;
                        ChkBoxUSB[i].Checked = true;
                    }
                }
            }
            else
            {
                for (byte i = 0; i < 6; i++)
                {
                    ChkBoxDC[i].Checked = false;
                    ChkBoxDC[i].BackColor = Color.Gray;
                    ChkBoxUSB[i].Checked = false;
                    ChkBoxUSB[i].BackColor = Color.Gray;
                }
            }
        } 
        //串口初始化
        public void UartInitial()
        {
            try
            {
                if (MySerialPort.IsOpen)
                    MySerialPort.Close();
                comPort = (string)comboBoxcomPort.SelectedItem;
                if (comPort == "")
                    return;
                MySerialPort.PortName = comPort;
                MySerialPort.DataBits = 8;
                MySerialPort.Parity = Parity.None;
                MySerialPort.StopBits = StopBits.One;
                MySerialPort.BaudRate = baudRate;
                MySerialPort.NewLine = "\r\n";
                MySerialPort.DataReceived += new SerialDataReceivedEventHandler(UartRecvMsg);
                MySerialPort.Open();
                Thread.Sleep(250);
                //查询版本信息
                m_DeviceOk = false;
                byte i = 0, j = 0;
                for (i = 0; i < 3; i++)
                {
                    UartSendMsg(":H?#");
                    //Thread.Sleep(300);
                    for (j = 0; j < 60; j++)//每个5mS查一次，最长可执行60次（等待300mS）
                    {
                        if (m_DeviceOk)
                            break;
                        Thread.Sleep(5);
                    }
                    if (m_DeviceOk)
                        break;
                }
                if (m_DeviceOk)
                {
                    labelDevice.ForeColor = System.Drawing.Color.Black;
                    labelDevice.Text = "Device: " + m_Device;
                    labelVendor.Text = "Company: " + m_Vendor;
                    linkLabel.Text = m_Website;
                    labelEmail.Text = "Email: " + m_Email;
                    labelTel.Text = "Tel: " + m_Tel;
                    buttonUpdate.Enabled = true;
                    CheckState();
                }
                else
                {
                    labelDevice.ForeColor = System.Drawing.Color.Red;
                    labelDevice.Text = "No device detected,Check connection and refresh!";
                    labelVendor.Text = "Developer: Graycode Team";
                    linkLabel.Text = "Graycode Team";
                    labelEmail.Text = "Email: graycode(at)qq.com";
                    labelTel.Text = "WeChat: graycode";
                    buttonUpdate.Enabled = false;
                }
            }
            //catch (IOException ex)
            catch (Exception ex)
            {
                m_DeviceOk = false;
                //MessageBox.Show(ex.ToString());
                labelDevice.ForeColor = System.Drawing.Color.Red;
                labelDevice.Text = "No device detected,Check connection and refresh!";
                labelVendor.Text = "Developer: Graycode Team";
                linkLabel.Text = "Graycode Team";
                labelEmail.Text = "Email: graycode(at)qq.com";
                labelTel.Text = "WeChat: graycode";
                buttonUpdate.Enabled = false;
                ErrorInfo = ex.ToString();
            }
        }
        //关闭串口资源
        public void UartUninitial()
        {
            try
            {
                if (MySerialPort.IsOpen)
                {
                    MySerialPort.BreakState = true;
                    MySerialPort.Close();
                }
            }
            //catch (IOException ex)
            catch (Exception ex)
            {
                //MessageBox.Show(ex.ToString());
                ErrorInfo = ex.ToString();
            }
        }
        //发送命令函数，带返回确认
        public bool SendMsg(string command)
        {
            bool ret = false;
            byte i = 0, j = 0;
            char m_sCmd = Convert.ToChar(command.Substring(2, 1));
            m_rCmd = 'U';
            for (i = 0; i < 3; i++)
            {
                UartSendMsg(command);
                for (j = 0; j < 60; j++)//每个5mS查一次，最长可执行60次（等待300mS）
                {
                    if (m_rCmd == m_sCmd)//接收命令正确则退出本循环
                    {
                        ret = true;
                        break;
                    }
                    Thread.Sleep(5);
                }
                if (m_rCmd == m_sCmd)//接收命令正确则退出不在发送命令
                {
                    break;
                }
            }
            return ret;
        }
        //串口发送函数
        public void UartSendMsg(string Msg)
        {
            try
            {
                if (!MySerialPort.IsOpen)
                    MySerialPort.Open();
                MySerialPort.Write(Msg);
            }
            catch (IOException ex)//不能弹出窗口，否则串口线拔出后一直提示无法关闭控制软件
            {
                //if (!m_ConnectError)//只弹出一次
                {
                    MessageBox.Show(ex.ToString());
                    //m_ConnectError = true;
                }
            }
        }
        //串口中断接收数据
        public void UartRecvMsg(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            try
            {
                RecvBuf = RecvBuf + MySerialPort.ReadExisting();
                //MessageBox.Show(RecvBuf);
                for (int i = 0; i < RecvBuf.Length; i++)//可能有多条命令
                {
                    if (RecvBuf[i] == ':')//找到协议头
                        BChar = i;
                    if (RecvBuf[i] == '#')//找到协议尾
                        EChar = i;
                    if ((BChar >= 0) && (EChar > BChar))//找到一条完整命令
                    {
                        //处理数据
                        ProcessData(RecvBuf.Substring(BChar, EChar - BChar + 1));
                        BChar = -1;
                        EChar = -1;
                        //TimeCount = 0;//超时计数复位
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
        //处理命令函数
        private void ProcessData(string data2)
        {
            m_rCmd = data2[1];//当前返回命令标志位
            data2 = data2.Substring(2, data2.Length - 3);
            switch (m_rCmd)
            {
                case '?':
                    {
                        string[] TempArray = data2.Split('~');
                        if ((TempArray.Length >= 5) && (TempArray[0] == "SS"))
                        {
                            m_DeviceOk = true;
                            m_Device = TempArray[1];
                            m_Vendor = TempArray[2];
                            m_Website = TempArray[3];
                            m_Email = TempArray[4];
                            m_Tel = TempArray[5];
                        }
                        break;
                    }
                case 'Q':
                    {
                        //MessageBox.Show(data);
                        data = data2;
                        break;
                    }
                
            }
        }
        //打开DC口
        public bool OpenDC(int Port)
        {
            return SendMsg(":HOD" + Port.ToString() + "#");
        }
        //关闭DC口
        public bool CloseDC(int Port)
        {
            return SendMsg(":HCD" + Port.ToString() + "#");
        }
        //打开USB口
        public bool OpenUSB(int Port)
        {
            return SendMsg(":HOU" + Port.ToString() + "#");
        }
        //关闭USB口
        public bool CloseUSB(int Port)
        {
            return SendMsg(":HCU" + Port.ToString() + "#");
        }
        //查询状态
        public bool CheckState()
        {
            return SendMsg(":HQ#");
        }
        //保存数据
        public bool SaveData()
        {
            return SendMsg(":HS#");
        }
        
        #endregion
    }
}
