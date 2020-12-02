using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Threading;

using ASCOM;
using ASCOM.Astrometry;
using ASCOM.DriverAccess;
using ASCOM.DeviceInterface;
using ASCOM.Utilities;
using System.IO;
using System.Xml;

using Microsoft.CSharp;
using System.CodeDom.Compiler;
using System.Reflection;

using System.Drawing.Imaging;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters.Binary;
using System.Collections;

namespace CAO
{
    public partial class MainForm : Form
    {
        //DeviceType设备类型
        public enum DeviceType:byte
        {
            Camera = 0,
            Dome = 1,
            FilterWheel = 2,
            Focuser = 3,
            ObservingConditions = 4,
            Rotator=5,
            Switch = 6,
            Telescope = 7,
        }
        public enum FrameType : byte
        {
            Light = 0,
            Bias = 1,
            Dark = 2,
            Flat = 3,
        }
        //DriverID驱动ID，字符串
        public static string[] DriverID = new string[8];
        //DriverType驱动类型，0-ASCOM，1-Serial，3-Socket
        public static byte[] DriverType = new byte[8];
        public static UInt32 ImgNumber = 0;
        public static bool Display = false;
        //连接状态
        public static bool[] DriverConnected = new bool[8];
        public TextBox[] TextBoxDriverID = new TextBox[8];
        public Button[] ButtonConnected = new Button[8];
        public static byte ConnectTimeout = 10;//连接超时时间，单位：秒
        //驱动类   
        public SSDome MyDome;
        public SSTelescope MyTelescope;
        public SSCamera MyCamera;
        public SSFilterWheel MyFilterWheel;
        public SSFocuser MyFocuser;
        public SSObservingConditions MyObsConditions;
        public SSRotator MyRotator;
        public SSSwitch MySwitch;
        public SSVideo MyVideo;
        public SSFits MyFits;

        public Util MyUtil = new Util();
        public System.Threading.Thread TCamera, TTelescope, TDome, TFilterWheel, TFocuser, TRotator,TSwitch, TObsConditions,TConnection;
        public string ErrorInfo;
        #region Initialize
        public MainForm()
        {
            InitializeComponent();
            //指定不再捕获对错误线程的调用，可以在线程中更新UI控件
            Control.CheckForIllegalCrossThreadCalls = false;
            for (byte i = 0; i < 8; i++)
            {
                DriverID[i] = null;
                DriverType[i] = 0;
                DriverConnected[i] = false;  
            }
            TextBoxDriverID[0] = textBoxCameraID;
            TextBoxDriverID[1] = textBoxDomeID;
            TextBoxDriverID[2] = textBoxFilterWheelID;
            TextBoxDriverID[3] = textBoxFocuserID;
            TextBoxDriverID[4] = textBoxObsConditionsID;
            //TextBoxDriverID[5] = textBoxRotatorID;
            TextBoxDriverID[6] = textBoxSwitchID;
            TextBoxDriverID[7] = textBoxTelescopeID;

            ButtonConnected[0] = buttonConnectCamera;
            ButtonConnected[1] = buttonConnectDome;
            ButtonConnected[2] = buttonConnectFilterWheel;
            ButtonConnected[3] = buttonConnectFocuser;
            ButtonConnected[4] = buttonConnectObsConditions;
            //ButtonConnected[5] = buttonConnectRotator;
            ButtonConnected[6] = buttonConnectSwitch;
            ButtonConnected[7] = buttonConnectTelescope;

            TConnection = new Thread(this.ConnectionThread);
            TConnection.Start();
        }
        #endregion
        #region TabControl
        private void tabControl1_TabIndexChanged(object sender, EventArgs e)
        {
            if (tabControl1.SelectedTab.Name == "Status")
            {
            }
            else if (tabControl1.SelectedTab.Name == "Camera")
            {
                if (DriverConnected[Convert.ToByte(DeviceType.Camera)])
                {
                    buttonCameraAutoSave.Enabled = true;
                    buttonCameraStartExpose.Enabled = true;
                    buttonCameraStopExpose.Enabled = true;
                    comboBoxFrame.SelectedIndex = 0;
                    comboBoxMode.SelectedIndex = 0;
                    if (DriverConnected[Convert.ToByte(DeviceType.FilterWheel)])
                    {
                        comboBoxFilter.Enabled = true;
                        comboBoxFilter.Items.Clear();
                        comboBoxFilter.Items.AddRange(MyFilterWheel.Names);
                        if (comboBoxFilter.Items.Count > 0)
                        {

                            if (comboBoxFilter.Items.Contains(MyFilterWheel.Names[MyFilterWheel.Position]))
                            {
                                comboBoxFilter.SelectedItem = MyFilterWheel.Names[MyFilterWheel.Position];
                            }
                            else
                                comboBoxFilter.SelectedIndex = 0;

                        }
                    }
                    else
                    {
                        comboBoxFilter.Enabled = false;
                        //comboBoxFilter.Items.Clear();
                        //comboBox1.SelectedIndex = -1;
                        //comboBoxFilter.Text = "";
                    }
                }
                else
                {
                    buttonCameraAutoSave.Enabled = false;
                    buttonCameraStartExpose.Enabled = false;
                    buttonCameraStopExpose.Enabled = false;
                }
            }
            else if (tabControl1.SelectedTab.Name == "Focuser")
            {
                if (DriverConnected[Convert.ToByte(DeviceType.Focuser)])
                {
                    buttonFocuserMoveTo.Enabled = true;
                    buttonFocuserAbort.Enabled = true;
                    buttonFocuserMoveIn.Enabled = true;
                    buttonFocuserMoveOut.Enabled = true;
                    textBoxFocuserPosition.Text = MyFocuser.Position.ToString();
                    textBoxFocuserTemperature.Text = MyFocuser.Temperature.ToString();
                    if (MyFocuser.Absolute)
                        textBoxFocuserType.Text = "Absolute";
                    else
                        textBoxFocuserType.Text = "Relative";
                }
                else
                {
                    buttonFocuserMoveTo.Enabled = false;
                    buttonFocuserAbort.Enabled = false;
                    buttonFocuserMoveIn.Enabled = false;
                    buttonFocuserMoveOut.Enabled = false;
                    textBoxFocuserStatus.Text = "Unconnected";
                }
            }
            else if (tabControl1.SelectedTab.Name == "Telescope")
            {
                if (DriverConnected[Convert.ToByte(DeviceType.Telescope)])
                {
                    buttonTelescopeEastward.Enabled = true;
                    buttonTelescopeWestward.Enabled = true;
                    buttonTelescopeNorthward.Enabled = true;
                    buttonTelescopeSouthward.Enabled = true;
                    buttonTelesocpeStop.Enabled = true;

                    buttonTelescopeHome.Enabled = true;
                    buttonTelescopeGoto.Enabled = true;
                    buttonTelescopeSync.Enabled = true;
                    buttonTelescopePark.Enabled = true;

                    buttonTelescopeCalibrate.Enabled = true;

                    buttonTelescopeSite.Enabled = true;
                    buttonTelescopeLimit.Enabled = true;
                }
                else
                {
                    buttonTelescopeEastward.Enabled = false;
                    buttonTelescopeWestward.Enabled = false;
                    buttonTelescopeNorthward.Enabled = false;
                    buttonTelescopeSouthward.Enabled = false;
                    buttonTelesocpeStop.Enabled = false;

                    buttonTelescopeHome.Enabled = false;
                    buttonTelescopeGoto.Enabled = false;
                    buttonTelescopeSync.Enabled = false;
                    buttonTelescopePark.Enabled = false;

                    buttonTelescopeCalibrate.Enabled = false;

                    buttonTelescopeSite.Enabled = false;
                    buttonTelescopeLimit.Enabled = false;
                }
            }
            else if (tabControl1.SelectedTab.Name == "Dome")
            {
                if (DriverConnected[Convert.ToByte(DeviceType.Dome)])
                {
                    buttonDomeShutterOpen.Enabled = true;
                    buttonDomeShutterClose.Enabled = true;
                    buttonDomeGoto.Enabled = true;
                    buttonDomeAbort.Enabled = true;
                    buttonDomeHome.Enabled = true;
                    buttonDomePark.Enabled = true;
                }
                else
                {
                    buttonDomeShutterOpen.Enabled = false;
                    buttonDomeShutterClose.Enabled = false;
                    buttonDomeGoto.Enabled = false;
                    buttonDomeAbort.Enabled = false;
                    buttonDomeHome.Enabled = false;
                    buttonDomePark.Enabled = false;
                }
            }
            else if (tabControl1.SelectedTab.Name == "Weather")
            {
                if (DriverConnected[Convert.ToByte(DeviceType.ObservingConditions)])
                {
                }
            }
        }

        private void tabControl1_DrawItem(object sender, DrawItemEventArgs e)
        {
            Font TabFont;
            Brush BshBack;
            Brush BshFore;
            if (e.Index == this.tabControl1.SelectedIndex)    //当前Tab页的样式
            {
                TabFont = new Font(e.Font, FontStyle.Bold);
                BshBack = new SolidBrush(Color.Blue);
                BshFore = new SolidBrush(Color.Red);
            }
            else    //其余Tab页的样式
            {
                TabFont = e.Font;
                BshBack = new System.Drawing.Drawing2D.LinearGradientBrush(e.Bounds, SystemColors.Control, SystemColors.Control, System.Drawing.Drawing2D.LinearGradientMode.BackwardDiagonal);
                BshFore = Brushes.Black;
            }
            //画样式
            string TabName = this.tabControl1.TabPages[e.Index].Text;
            StringFormat TabSft = new StringFormat();
            TabSft.LineAlignment = StringAlignment.Center;
            TabSft.Alignment = StringAlignment.Center;
            e.Graphics.FillRectangle(BshBack, e.Bounds);
            RectangleF TabRec = (RectangleF)tabControl1.GetTabRect(e.Index);//绘制区域
            e.Graphics.DrawString(TabName, TabFont, BshFore, TabRec, TabSft);

        }
        #endregion
        #region Connection
        //选择设备
        private void ChooseDevice(DeviceType DevType)
        {
            byte MyDeviceType = Convert.ToByte(DevType);//设备类型转换为byte
            if (DriverConnected[MyDeviceType])//已连接就退出不执行
                return;
            using (SetupDialogForm F = new SetupDialogForm(MyDeviceType))
            {
                var result = F.ShowDialog();
                if (result == System.Windows.Forms.DialogResult.OK)
                {
                    TextBoxDriverID[MyDeviceType].Text = DriverID[MyDeviceType];
                    //WriteProfile(); // Persist device configuration values to the ASCOM Profile store
                }
            }
        }
        //连接设备、断开设备
        private void ConnectDevice(DeviceType DevType)
        {
            bool IsConnected = false;
            byte MyDeviceType = Convert.ToByte(DevType);//设备类型转换为byte
            if (DriverConnected[MyDeviceType] == false)
            {
                if (!string.IsNullOrEmpty(DriverID[MyDeviceType]))//DriverID不为空
                {
                    switch (MyDeviceType)
                    {
                        case 0:
                            MyCamera = new SSCamera(DriverID[MyDeviceType], DriverType[MyDeviceType]);
                            MyCamera.Connected = true;
                            for (byte i = 0; i < ConnectTimeout*2; i++)
                            {
                                if (MyCamera.Connected)
                                {
                                    IsConnected = true;
                                    TCamera = new Thread(this.CameraThread);TCamera.Start();
                                    break;
                                }
                                Thread.Sleep(500);
                            }
                            break;
                        case 1:
                            MyDome = new SSDome(DriverID[MyDeviceType], DriverType[MyDeviceType]);
                            MyDome.Connected = true;
                            for (byte i = 0; i < ConnectTimeout * 2; i++)
                            {
                                if (MyDome.Connected)
                                {
                                    IsConnected = true;
                                    TDome = new Thread(this.DomeThread);TDome.Start();
                                    break;
                                }
                                Thread.Sleep(500);
                            }
                            break;
                        case 2:
                            MyFilterWheel = new SSFilterWheel(DriverID[MyDeviceType], DriverType[MyDeviceType]);
                            MyFilterWheel.Connected = true;
                            for (byte i = 0; i < ConnectTimeout * 2; i++)
                            {
                                if (MyFilterWheel.Connected)
                                {
                                    IsConnected = true;
                                    //TFilterWheel = new Thread(this.FilterWheelThread);//TFilterWheel.Start();//由Camera线程调度，不用单开线程
                                    break;
                                }
                                Thread.Sleep(500);
                            }
                            break;
                        case 3:
                            MyFocuser = new SSFocuser(DriverID[MyDeviceType], DriverType[MyDeviceType]);
                            MyFocuser.Connected = true;
                            for (byte i = 0; i < ConnectTimeout * 2; i++)
                            {
                                if (MyFocuser.Connected)
                                {
                                    IsConnected = true;
                                    TFocuser = new Thread(this.FocuserThread);TFocuser.Start();
                                    break;
                                }
                                Thread.Sleep(500);
                            }
                            break;
                        case 4:
                            MyObsConditions = new SSObservingConditions(DriverID[MyDeviceType], DriverType[MyDeviceType]);
                            MyObsConditions.Connected = true;
                            for (byte i = 0; i < ConnectTimeout * 2; i++)
                            {
                                if (MyObsConditions.Connected)
                                {
                                    IsConnected = true;
                                    TObsConditions = new Thread(this.ObsConditionsThread);TObsConditions.Start();
                                    break;
                                }
                                Thread.Sleep(500);
                            }
                            break;
                        case 5:
                            MyRotator = new SSRotator(DriverID[MyDeviceType], DriverType[MyDeviceType]);
                            MyRotator.Connected = true;
                            for (byte i = 0; i < ConnectTimeout * 2; i++)
                            {
                                if (MyRotator.Connected)
                                {
                                    IsConnected = true;
                                    TRotator = new Thread(this.RotatorThread);TRotator.Start();
                                    break;}
                                Thread.Sleep(500);
                            }
                            break;
                        case 6:
                            MySwitch = new SSSwitch(DriverID[MyDeviceType], DriverType[MyDeviceType]);
                            MySwitch.Connected = true;
                            for (byte i = 0; i < ConnectTimeout * 2; i++)
                            {
                                if (MySwitch.Connected){
                                    IsConnected = true;
                                    TSwitch = new Thread(this.SwitchThread);TSwitch.Start();
                                    break;
                                }
                                Thread.Sleep(500);
                            }
                            break;
                        case 7:
                            MyTelescope = new SSTelescope(DriverID[MyDeviceType], DriverType[MyDeviceType]);
                            MyTelescope.Connected = true;
                            for (byte i = 0; i < ConnectTimeout * 2; i++)
                            {
                                if (MyTelescope.Connected)
                                {
                                    IsConnected = true;
                                    TTelescope = new Thread(this.TelescopeThread);TTelescope.Start();
                                    break;
                                }
                                Thread.Sleep(500);
                            }
                            break;
                    }
                    if (IsConnected)
                    {
                        DriverConnected[MyDeviceType] = true;
                        ButtonConnected[MyDeviceType].Text = "Disconnect";
                    }
                    else
                    {
                        DriverConnected[MyDeviceType] = false;
                        ButtonConnected[MyDeviceType].Text = "Connect";
                        MessageBox.Show("Connect failed");
                    }
                }
            }
            else
            {
                switch (MyDeviceType)
                {
                    case 0:
                        MyCamera.Connected = false;//TCamera.Abort();//MyCamera.Dispose();
                        break;
                    case 1:
                        MyDome.Connected = false;//TDome.Abort();//MyDome.Dispose();                        
                        break;
                    case 2:
                        MyFilterWheel.Connected = false;//TFilterWheel.Abort();//MyFilterWheel.Dispose();
                        break;
                    case 3:
                        MyFocuser.Connected = false;//TFocuser.Abort();//MyFocuser.Dispose();
                        break;
                    case 4:
                        MyObsConditions.Connected = false;//TObsConditions.Abort();//MyObsConditions.Dispose();
                        break;
                    case 5:
                        MyRotator.Connected = false;//TRotator.Abort();//MyRotator.Dispose();
                        break;
                    case 6:
                        MySwitch.Connected = false;//TSwitch.Abort();//MySwitch.Dispose();
                        break;
                    case 7:
                        MyTelescope.Connected = false;//TTelescope.Abort();//MyTelescope.Dispose();
                        break;
                }
                DriverConnected[MyDeviceType] = false;
                ButtonConnected[MyDeviceType].Text = "Connect";
            }
        }
        private void ConnectionThread()
        {
            while (true)
            {
                if (DriverConnected[0])
                {
                    try
                    {
                        if (!MyCamera.Connected)
                        {
                            DriverConnected[0] = false;
                            buttonConnectCamera.Text = "Connect";
                        }
                    }
                    catch (Exception ex)
                    {
                        DriverConnected[0] = false;
                        buttonConnectCamera.Text = "Connect";
                        MessageBox.Show("Connection Error");
                        ErrorInfo = ex.ToString();
                    }
                }
                if ((DriverConnected[1]) && (!MyDome.Connected))
                {
                    DriverConnected[1] = false;
                    buttonConnectDome.Text = "Connect";
                }
                if ((DriverConnected[2]) && (!MyFilterWheel.Connected))
                {
                    DriverConnected[2] = false;
                    buttonConnectFilterWheel.Text = "Connect";
                }
                if ((DriverConnected[3]) && (!MyFocuser.Connected))
                {
                    DriverConnected[3] = false;
                    buttonConnectFocuser.Text = "Connect";
                }
                if ((DriverConnected[4]) && (!MyObsConditions.Connected))
                {
                    DriverConnected[4] = false;
                    buttonConnectObsConditions.Text = "Connect";
                }
                if ((DriverConnected[5]) && (!MyRotator.Connected))
                {
                    DriverConnected[5] = false;
                    //buttonConnectRotator.Text = "Connect";
                }
                if ((DriverConnected[6]) && (!MySwitch.Connected))
                {
                    DriverConnected[6] = false;
                    buttonConnectSwitch.Text = "Connect";
                }
                if (DriverConnected[7])
                {
                    try
                    {
                        if (!MyTelescope.Connected)
                        {
                            DriverConnected[7] = false;
                            buttonConnectTelescope.Text = "Connect";
                        }
                    }
                    catch (Exception ex)
                    {
                        DriverConnected[7] = false;
                        buttonConnectTelescope.Text = "Connect";
                        MessageBox.Show("Connection Error");
                        ErrorInfo = ex.ToString();
                    }
                }
                Thread.Sleep(1000);
            }
        }
        #endregion
        #region Camera
        //选择Camera
        private void buttonChooseCamera_Click(object sender, EventArgs e)
        {
            ChooseDevice(DeviceType.Camera);
        }
        //连接Camera
        private void buttonConnectCamera_Click(object sender, EventArgs e)
        {
            ConnectDevice(DeviceType.Camera);
        }
        //开始曝光
        private void buttonStartExpose_Click(object sender, EventArgs e)
        {
            //判断Frame类型，Light，Bias，Dark，Flat
            byte MyFrame = Convert.ToByte(comboBoxFrame.SelectedIndex);
            double MyDuration = Convert.ToDouble(numericUpDownExposeTime.Value);
            if (DriverConnected[Convert.ToByte(DeviceType.FilterWheel)])
            {
                Int16 MyFilter = Convert.ToInt16(comboBoxFilter.SelectedIndex);
                if (MyFrame < 2)
                {
                    if (MyFilterWheel.FilterMove(MyFilter, 300))
                        MyCamera.CameraExpose(MyFrame, MyDuration);
                    else
                        MessageBox.Show("FilterWheel Timeout");
                }
                else
                {
                    MyCamera.CameraExpose(MyFrame, MyDuration);
                }
            }
            else
                MyCamera.CameraExpose(MyFrame, MyDuration);
            Display = false;
        }
        //停止曝光
        private void buttonStopExpose_Click(object sender, EventArgs e)
        {
            MyCamera.AbortExposure();
        }
        //工作线程
        private void CameraThread()
        {
            byte n=0;
            while (true)
            {
                if (DriverConnected[0]) //100mS查一次Camera连接状态
                {
                    try
                    {
                        if (!MyCamera.Connected)//正常断开
                        {
                            DriverConnected[0] = false;
                            buttonConnectCamera.Text = "Connect";
                            textBoxCameraFilterStatus.Text = "Camera Disconnected!";
                            break;
                        }
                    }
                    catch (Exception ex)//异常断开
                    {
                        DriverConnected[0] = false;
                        buttonConnectCamera.Text = "Connect";
                        textBoxCameraFilterStatus.Text = "Camera Connection Error!";
                        ErrorInfo = ex.ToString();
                        break;
                    }
                }
                if (DriverConnected[2])//100mS查一次Filter连接状态，异常不能跳出
                {
                    try
                    {
                        if (!MyFilterWheel.Connected)//正常断开
                        {
                            DriverConnected[2] = false;
                            buttonConnectFilterWheel.Text = "Connect";
                        }
                    }
                    catch (Exception ex)//异常断开
                    {
                        DriverConnected[2] = false;
                        buttonConnectFilterWheel.Text = "Connect";
                        ErrorInfo = ex.ToString();
                    }
                }

                if(n<10)
                    n++;
                else //1000mS执行一次
                {
                    try
                    {
                        if (DriverConnected[2])//滤光片连接,不能用MyFilterWheel.Connected，可能会异常抛出
                        {
                            if (MyFilterWheel.Position < 0)
                                textBoxCameraFilterStatus.Text = Environment.NewLine + "Camera: " + MyCamera.CameraState.ToString() +
                            Environment.NewLine + Environment.NewLine + "Filter: Moving";
                            else
                                textBoxCameraFilterStatus.Text = Environment.NewLine + "Camera: " + MyCamera.CameraState.ToString() +
                            Environment.NewLine + Environment.NewLine + "Filter: " + MyFilterWheel.Names[MyFilterWheel.Position];
                        }
                        else
                        {
                            textBoxCameraFilterStatus.Text = Environment.NewLine + "Camera: " + MyCamera.CameraState.ToString() +
                            Environment.NewLine + Environment.NewLine + "Filter: Disconected";
                        }
                        //图片处理
                        if ((!Display) && (MyCamera.ImageReady))
                        {
                            //MyCameraState += "  ImageReady";
                            int CamNumX = MyCamera.NumX;//ImageArray[NumX][NumY]
                            int CamNumY = MyCamera.NumY;
                            int bitpix = MyCamera.MaxADU;
                            int[,] TemImg = (int[,])MyCamera.ImageArray;
                            //Fits类仅支持交错数组，存储时图像会翻转，需翻转处理
                            //int[][] CurImg = new int[CamNumX][];
                            //for (int i = 0; i < CamNumX; i++)
                            //    CurImg[i] = new int[CamNumY];
                            int[][] CurImg = new int[CamNumY][];
                            for (int i = 0; i < CamNumY; i++)
                                CurImg[i] = new int[CamNumX];

                            for (int i = 0; i < CamNumX; i++)
                                for (int j = 0; j < CamNumY; j++)
                                    CurImg[j][i] = (Int32)TemImg[i, j];//注意翻转
                            pictureBox1.Image = null;
                            ImgNumber++;
                            string ImgPath = "Image" + ImgNumber.ToString() + ".fits";
                            MyFits = new SSFits();
                            MyFits.MakeFile(ImgPath, CurImg);
                            pictureBox1.Image = MyFits.ReadFile(ImgPath);
                            Display = true;
                        }
                    }
                    catch (Exception ex)
                    {
                        ErrorInfo = ex.ToString();
                    }
                    n=0;
                }
                Thread.Sleep(100);
            }
            //Thread.CurrentThread.Abort();
            TCamera.Abort();
        }
        #endregion
        #region Telescope
        //Telescope
        private void buttonChooseTelescope_Click(object sender, EventArgs e)
        {
            ChooseDevice(DeviceType.Telescope);
        }

        private void buttonConnectTelescope_Click(object sender, EventArgs e)
        {
            ConnectDevice(DeviceType.Telescope);
        }
        private void buttonTelescopeGoto_Click(object sender, EventArgs e)
        {
            MyTelescope.SlewToCoordinates(Convert.ToDouble(numericUpDownTelescopeTargetRa.Value), Convert.ToDouble(numericUpDownTelescopeTargetDEC.Value));
        }

        private void buttonTelescopeSync_Click(object sender, EventArgs e)
        {
            MyTelescope.SyncToCoordinates(Convert.ToDouble(numericUpDownTelescopeTargetRa.Value), Convert.ToDouble(numericUpDownTelescopeTargetDEC.Value));
        }

        private void buttonTelescopeHome_Click(object sender, EventArgs e)
        {
            MyTelescope.FindHome();
        }

        private void buttonTelescopePark_Click(object sender, EventArgs e)
        {
            if (MyTelescope.AtPark)
            {
                MyTelescope.Tracking = true;
                buttonTelescopePark.Text = "Unpark";
            }
            else
            {
                MyTelescope.Park();
                buttonTelescopePark.Text = "Park";
            }
        }

        private void buttonTelescopeCalibrate_Click(object sender, EventArgs e)
        {

        }

        private void buttonTelescopeSite_Click(object sender, EventArgs e)
        {

        }

        private void buttonTelescopeLimit_Click(object sender, EventArgs e)
        {

        }
        private double IncrementArcsec()
        {
            double ret = 0;
            switch (comboBoxTelescopeSlewUnit.SelectedIndex)
            {
                case 0://Sec
                    ret = Convert.ToDouble(numericUpDownTelescopeSlewIncrement.Value);
                    break;
                case 1://Min
                    ret = Convert.ToDouble(numericUpDownTelescopeSlewIncrement.Value * 60);
                    break;
                case 2://Deg
                    ret = Convert.ToDouble(numericUpDownTelescopeSlewIncrement.Value * 3600);
                    break;
            }
            return ret;
        }
        private void buttonTelescopeNorthward_Click(object sender, EventArgs e)
        {
            MyTelescope.SlewToCoordinates(MyTelescope.RightAscension, MyTelescope.Declination + IncrementArcsec() / 3600);
        }

        private void buttonTelescopeSouthward_Click(object sender, EventArgs e)
        {
            MyTelescope.SlewToCoordinates(MyTelescope.RightAscension, MyTelescope.Declination - IncrementArcsec() / 3600);
        }

        private void buttonTelescopeEastward_Click(object sender, EventArgs e)
        {
            MyTelescope.SlewToCoordinates(MyTelescope.RightAscension - IncrementArcsec() / 3600 / 15, MyTelescope.Declination);
        }

        private void buttonTelescopeWestward_Click(object sender, EventArgs e)
        {
            MyTelescope.SlewToCoordinates(MyTelescope.RightAscension + IncrementArcsec() / 3600 / 15, MyTelescope.Declination);
        }

        private void buttonTelesocpeStop_Click(object sender, EventArgs e)
        {
            MyTelescope.AbortSlew();
        }
        private void TelescopeThread()
        {
            //byte RAH, RAM, RAS, DECD, DECM, DECS;
            //double TempRA, TempDEC;
            while (DriverConnected[Convert.ToByte(DeviceType.Telescope)])
            {

                //TempRA = MyTelescope.RightAscension;
                //TempDEC = MyTelescope.Declination;
                //RAH = Convert.ToByte(TempRA);
                //RAM = Convert.ToByte(TempRA * 60 % 60);
                //RAS = Convert.ToByte(TempRA * 60 % 60);
                //textBoxTelescopeStatus.Text = "RA: " + RAH.ToString("D2") + RAM.ToString("D2") + RAS.ToString("D2") +
                //textBoxTelescopeStatus.Text = "RA: " +MyUtil.HoursToHMS(MyTelescope.RightAscension)+
                //     Environment.NewLine + "DEC: " + MyUtil.DegreesToDMS(MyTelescope.Declination);
                Thread.Sleep(250);
            }
            TTelescope.Abort();
        }
        #endregion
        #region Dome
        //Dome
        private void buttonChooseDome_Click(object sender, EventArgs e)
        {
            ChooseDevice(DeviceType.Dome);
        }

        private void buttonConnectDome_Click(object sender, EventArgs e)
        {
            ConnectDevice(DeviceType.Dome);
        }
        private void buttonDomeShutterOpen_Click(object sender, EventArgs e)
        {
            if (DriverConnected[Convert.ToByte(DeviceType.Dome)])
                MyDome.OpenShutter();
        }

        private void buttonDomeShutterClose_Click(object sender, EventArgs e)
        {
            if (DriverConnected[Convert.ToByte(DeviceType.Dome)])
                MyDome.CloseShutter();
        }
        private void buttonDomeGoto_Click(object sender, EventArgs e)
        {
            try
            {
                if (!DriverConnected[Convert.ToByte(DeviceType.Dome)])
                    return;
                if (MyDome.ShutterStatus != ShutterState.shutterOpen)
                    MyDome.OpenShutter();
                for (byte i = 0; i < 100; i++)
                {
                    System.Threading.Thread.Sleep(100);
                    if (MyDome.ShutterStatus == ShutterState.shutterOpen)
                        break;
                }
                MyDome.SlewToAltitude(45);
                MyDome.SlewToAzimuth(90.0);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
        }
        private void checkBoxSlaveDome_CheckedChanged(object sender, EventArgs e)
        {

        }
        private void DomeThread()
        {
            while (DriverConnected[Convert.ToByte(DeviceType.Dome)])
            {

                if (MyDome.ShutterStatus == ShutterState.shutterOpen)//天窗打开才能操作
                {
                    if (MyDome.Slewing)//正在转动
                    {
                        this.textBoxDomeState.Text = "Device: Connected" +
                            Environment.NewLine + "CurAzimuth: Slewing";
                    }
                    else
                    {
                        this.textBoxDomeState.Text = "Device: Connected" +
                            Environment.NewLine + "Azimuth:" + MyDome.Azimuth.ToString() +
                        Environment.NewLine + "Altitude:" + MyDome.Altitude.ToString();
                    }
                }
                Thread.Sleep(250);
            }
            TDome.Abort();
        }
        #endregion
        #region Focuser
        //Focuser
        private void buttonChooseFocuser_Click(object sender, EventArgs e)
        {
            ChooseDevice(DeviceType.Focuser);
        }

        private void buttonConnectFocuser_Click(object sender, EventArgs e)
        {
            ConnectDevice(DeviceType.Focuser);
        }
        private void buttonFocuserMoveTo_Click(object sender, EventArgs e)
        {
            if (MyFocuser.Absolute)
                MyFocuser.Move(int.Parse(textBoxFocuserPositionMoveTo.Text));
            else
                MessageBox.Show("Relative Focuser don't support Move to");
        }

        private void buttonFocuserAbort_Click(object sender, EventArgs e)
        {
            MyFocuser.Halt();
        }

        private void buttonFocuserMoveIn_Click(object sender, EventArgs e)
        {
            int MoveToPosition = MyFocuser.Position - int.Parse(textBoxFocuserIncrement.Text);
            if (MoveToPosition >= 0)
                MyFocuser.Move(MoveToPosition);
            else
                MyFocuser.Move(0);
        }

        private void buttonFocuserMoveOut_Click(object sender, EventArgs e)
        {
            int MoveToPosition = MyFocuser.Position + int.Parse(textBoxFocuserIncrement.Text);
            if (MoveToPosition <= MyFocuser.MaxStep)
                MyFocuser.Move(MoveToPosition);
            else
                MyFocuser.Move(MyFocuser.MaxStep);
        }
        private void FocuserThread()
        {
            int LastPosition = 0;
            double LastTemperature = 0;
            while (DriverConnected[Convert.ToByte(DeviceType.Focuser)])
            {
                if (MyFocuser.Position != LastPosition)
                {
                    if (MyFocuser.Absolute)
                    {
                        LastPosition = MyFocuser.Position;
                        textBoxFocuserPosition.Text = LastPosition.ToString();
                    }
                    else
                    {
                        textBoxFocuserPosition.Text = "Unknown";
                    }
                }
                if (MyFocuser.Temperature != LastTemperature)
                {
                    LastTemperature = MyFocuser.Temperature;
                    textBoxFocuserTemperature.Text = LastTemperature.ToString();
                }
                Thread.Sleep(250);
            }
            TFocuser.Abort();
        }
        #endregion
        #region FilterWheel
        //FilterWheel
        private void buttonChooseFilterWheel_Click(object sender, EventArgs e)
        {
            ChooseDevice(DeviceType.FilterWheel);
        }

        private void buttonConnectFilterWheel_Click(object sender, EventArgs e)
        {
            ConnectDevice(DeviceType.FilterWheel);
        }
        private void comboBoxFilter_SelectedIndexChanged(object sender, EventArgs e)
        {
            MyFilterWheel.Position = Convert.ToInt16(comboBoxFilter.SelectedIndex);
        }
        private void FilterWheelThread()
        {
            while (DriverConnected[Convert.ToByte(DeviceType.FilterWheel)])
            {
                Thread.Sleep(1000);
            }

            TFilterWheel.Abort();
        }
        #endregion
        #region ObsConditions
        //ObsConditions
        private void buttonChooseObsConditions_Click(object sender, EventArgs e)
        {
            ChooseDevice(DeviceType.ObservingConditions);
        }

        private void buttonConnectObsConditions_Click(object sender, EventArgs e)
        {
            ConnectDevice(DeviceType.ObservingConditions);
        }
        private void ObsConditionsThread()
        {
            while (DriverConnected[Convert.ToByte(DeviceType.ObservingConditions)])
            {
                textBoxCloudCover.Text = MyObsConditions.CloudCover.ToString();
                textBoxDewPoint.Text = MyObsConditions.DewPoint.ToString();
                textBoxHumidity.Text = MyObsConditions.Humidity.ToString();
                textBoxPressure.Text = MyObsConditions.Pressure.ToString();
                textBoxRainRate.Text = MyObsConditions.RainRate.ToString();
                textBoxSkyQuality.Text = MyObsConditions.SkyQuality.ToString();
                textBoxStarFWHM.Text = MyObsConditions.StarFWHM.ToString();
                textBoxSkyTemperature.Text = MyObsConditions.SkyTemperature.ToString();
                textBoxTemperature.Text = MyObsConditions.Temperature.ToString();
                textBoxWindDirection.Text = MyObsConditions.WindDirection.ToString();
                textBoxWindGust.Text = MyObsConditions.WindGust.ToString();
                textBoxWindSpeed.Text = MyObsConditions.WindSpeed.ToString();
                Thread.Sleep(5000);
            }
            TObsConditions.Abort();
        }
        #endregion
        #region Rotator
        private void RotatorThread()
        {
            while (DriverConnected[Convert.ToByte(DeviceType.Rotator)])
            {

                Thread.Sleep(250);
            }
            TRotator.Abort();
        }
        #endregion
        #region Switch
        //Switch
        private void buttonChooseSwitch_Click(object sender, EventArgs e)
        {
            ChooseDevice(DeviceType.Switch);
        }

        private void buttonConnectSwitch_Click(object sender, EventArgs e)
        {
            ConnectDevice(DeviceType.Switch);
        }

        private void SwitchThread()
        {
            while (DriverConnected[Convert.ToByte(DeviceType.Switch)])
            {
                Thread.Sleep(250);
            }
            buttonConnectFilterWheel.Text = "Connect";
            TSwitch.Abort();
        }
        #endregion
    }
}
