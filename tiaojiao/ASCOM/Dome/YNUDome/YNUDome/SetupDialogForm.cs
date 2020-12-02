using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Runtime.InteropServices;
using System.Text;
using System.Windows.Forms;
using ASCOM.Utilities;
using ASCOM.YNUDome;

using System.Timers;
using System.IO;
using System.IO.Ports;
using System.Threading;

namespace ASCOM.YNUDome
{
    [ComVisible(false)]					// Form not registered for COM!
    public partial class SetupDialogForm : Form
    {
        public SerialPort MySerialPort;
        public string ComPort;
        public int BaudRate;
        private byte RecvByte = 0, LastByte = 0;
        //private byte[] RecvBuf;
        private bool HeadCmd = false;
        private byte RecvCnt = 0;
        private UInt16 ChkSum = 0;

        public static bool FirstTime;

        public SetupDialogForm()
        {
            InitializeComponent();
            // Initialise current values of user settings from the ASCOM Profile
            InitUI();

            //串口初始化要在UI之前，因为UI初始化有调用
            MySerialPort = new SerialPort();
            BaudRate = 9600;
            FirstTime = true;
            //RecvBuf=new byte[17];

            if (!Dome.connectedState)
            {
                //用一个定时器执行第一次串口初始化，避免界面打开缓慢
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
            if (comboBoxComPort.Items.Count > 0)//检测到串口才执行
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

            if (Dome.connectedState)//如果已连接则返回
                return;
            try
            {
                Dome.comPort = (string)comboBoxComPort.SelectedItem;
                Dome.AzimuthOffset = int.Parse(textBoxAzimuthOffset.Text);
                
                if (checkBoxUseToolbox.Checked)
                    Dome.UseToolbox = true;
                else
                    Dome.UseToolbox = false;
                if (checkBoxEnableShutter2.Checked)
                    Dome.EnableShutter2 = true;
                else
                    Dome.EnableShutter2 = false;

                UartUninitial();//释放串口资源
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
        }

        private void cmdCancel_Click(object sender, EventArgs e) // Cancel button event handler
        {
            if (!Dome.connectedState)//非连接状态才操作，乙方连接时查看设置串口导致串口冲突
                UartUninitial();
            Close();
        }

        private void comboBoxComPort_SelectedValueChanged(object sender, EventArgs e)
        {
            if (Dome.connectedState)//非连接状态才操作，乙方连接时查看设置串口导致串口冲突
                return;
            if (!FirstTime)//第一次在界面初始化后调用，避免界面打开缓慢
            {
                UartUninitial();
                UartInitial();
            }
        }

        private void textBoxAzimuthOffset_KeyPress(object sender, KeyPressEventArgs e)
        {
            Dome.OnlyEnterInt(sender, e);
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

        private void Display()
        {
            comboBoxComPort.Items.Clear();
            comboBoxComPort.Items.AddRange(System.IO.Ports.SerialPort.GetPortNames());      // use System.IO because it's static
            if (comboBoxComPort.Items.Count > 0)
            {
                if (comboBoxComPort.Items.Contains(Dome.comPort))
                    comboBoxComPort.SelectedItem = Dome.comPort;
                else
                    comboBoxComPort.SelectedIndex = 0;
            }
            textBoxAzimuthOffset.Text = Dome.AzimuthOffset.ToString();
            checkBoxUseToolbox.Checked = Dome.UseToolbox;
            checkBoxEnableShutter2.Checked = Dome.EnableShutter2;
            if (Dome.connectedState)//连接状态不可更改
            {
                comboBoxComPort.Enabled = false;
                checkBoxUseToolbox.Enabled = false;
            }

        }
        public void SendMsg(byte Cmd, int Dat)
        {
            byte[] SendBuf = new byte[7];
            SendBuf[0] = 0xA5;
            SendBuf[1] = 0x5A;
            SendBuf[2] = Cmd;
            if (Cmd == 0x02)
            {
                if (Dat >= 0)
                    SendBuf[3] = 0x2B;
                else
                {
                    SendBuf[3] = 0x2D;
                    Dat = -Dat;
                }
                SendBuf[4] = (byte)(Dat / 256);
                SendBuf[5] = (byte)(Dat % 256);
            }
            else if (Cmd == 0x03)
            {
                SendBuf[3] = (byte)(Dat / 256);
                SendBuf[4] = (byte)(Dat % 256);
                SendBuf[5] = 0;
            }
            else
            {
                SendBuf[3] = 0x00;
                SendBuf[4] = 0x00;
                SendBuf[5] = 0x00;
            }
            SendBuf[6] = (byte)(SendBuf[2] + SendBuf[3] + SendBuf[4] + SendBuf[5]);
            UartSendMsg(SendBuf);
        }
        //初始化串口
        public void UartInitial()
        {
            try
            {
                MySerialPort.PortName = (string)comboBoxComPort.SelectedItem;
                MySerialPort.DataBits = 8;
                MySerialPort.Parity = Parity.None;
                MySerialPort.StopBits = StopBits.One;
                MySerialPort.BaudRate = Dome.baudRate;
                //MySerialPort.NewLine = "\r\n";
                MySerialPort.DataReceived += new SerialDataReceivedEventHandler(UartRecvMsg);
                MySerialPort.Open();

                Dome.m_DeviceOk = false;

                for (byte i = 0; i < 3; i++)
                {
                    ChkState();
                    //Thread.Sleep(300);
                    for (byte j = 0; j < 60; j++)//每个5mS查一次，最长可执行60次（等待300mS）
                    {
                        if (Dome.m_DeviceOk)
                            break;
                        Thread.Sleep(5);
                    }
                    if (Dome.m_DeviceOk)
                        break;
                }
            }
            //catch (IOException ex)
            catch (Exception ex)
            {
                //MessageBox.Show(ex.ToString());
            }
        }
        //释放串口资源
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
            }
        }

        public void UartSendMsg(byte[] Msg)
        {
            try
            {
                //if (!MySerialPort.IsOpen)
                //    MySerialPort.Open();
                MySerialPort.Write(Msg, 0, 7);
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
        private void UartRecvMsg(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            
            try
            {
                byte[] TempBuf = new byte[20];
                byte TempCnt = (byte)MySerialPort.Read(TempBuf, 0, 17);
            
                //MessageBox.Show(TempCnt.ToString ());
                for (byte i = 0; i < TempCnt; i++)
                {
                    RecvCnt++;
                    RecvByte = TempBuf[i];
                    //MessageBox.Show(RecvByte.ToString ("X2"));
                    if ((RecvByte == 0x5A) && (LastByte == 0xA5))//找到协议头则RecvCnt = 2
                    {
                        //RecvBuf[0] = 0xA5;
                        //RecvBuf[1] = 0x5A;
                        RecvCnt = 2;
                        ChkSum = 0;
                        HeadCmd = true;
                        //MessageBox.Show("1");
                    }
                    if (!HeadCmd)//协议头不正确则重新查找，不再往上计数，最多只能到1
                        RecvCnt = 0;
                    if (RecvCnt > 2)//3-17
                    {
                        //RecvBuf[RecvCnt - 1] = RecvByte;
                        if (RecvCnt < 17)//3-16
                            ChkSum += RecvByte;
                        //MessageBox.Show("2");
                    }
                    if (RecvCnt >= 17)
                    {
                        //MessageBox.Show("3");
                        //if ((ChkSum&0x00FF) == RecvBuf[16])//低字节为校验码
                        {
                            Dome.m_DeviceOk = true;
                        }
                        RecvCnt = 0;
                        ChkSum = 0;
                        HeadCmd = false;
                    }
                    LastByte = RecvByte;
                }
            }
            catch (Exception ex)
            {
                //MessageBox.Show(ex.ToString());
            }
        }
        //查询状态
        public void ChkState()
        {
            SendMsg(0x01, 0);
        }       
    }
}