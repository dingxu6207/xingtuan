using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Threading;
using ASCOM.Utilities;
using ASCOM.YNUDome;

namespace ASCOM.YNUDome
{
    public partial class Toolbox : Form
    {
        Dome MyDome;// = new Focuser();//graycode
        System.Timers.Timer t;
        public delegate void TimerFunc();

        private static byte i = 0;
        //public bool bUpdate = false;
        //public static byte i=0,j=0;
        //public string TmpWebsite="www.graycode.cn";
        //public bool FirstTime=true;

        string DCtrMode, DAzimuthDeg, DAzimuthSta, DShutter1Sta, DShutter2Sta;

        public Toolbox(Dome f)
        {
            MyDome = f;
            InitializeComponent();

            comboBoxSlewSpeed.SelectedIndex = Dome.SlewSpeed;
            if (!Dome.EnableShutter2)
            {
                buttonShutter2Open.Enabled = false;
                buttonShutter2Close.Enabled = false;
                buttonShutter2Stop.Enabled = false;
            }
            t = new System.Timers.Timer(500);//500毫秒执行一次；
            t.Elapsed += new System.Timers.ElapsedEventHandler(TimerEvent);//到达时间的时候执行事件；
            t.AutoReset = true;//设置是执行一次（false）还是一直执行(true)；
            t.Enabled = true;//是否执行System.Timers.Timer.Elapsed事件；
        }
        
        public void UpdateStatus()
        {
            if (i >= 20) i = 0;else i++;
            if (Dome.TimeCount >= Dome.TimeOut)
            {
                toolStripStatusLabel1.ForeColor = System.Drawing.Color.Red;
                toolStripStatusLabel1.Text = "Communication error! Please check!";
            }
            else
            {
                toolStripStatusLabel1.ForeColor = System.Drawing.Color.Black;
                if (i < 10)
                    toolStripStatusLabel1.Text = "Technical support: Yunnan Observatories, CAS";
                else if (i < 20)
                    toolStripStatusLabel1.Text = "Email: HeShouSheng@ynao.ac.cn";
            }
            if (Dome.CtrMode == 0x2A) DCtrMode = "Remote"; 
            else if (Dome.CtrMode == 0x2D) DCtrMode = "Manual"; 
            else DCtrMode = "No data";
            DAzimuthDeg=Dome.AzimuthDeg.ToString ();
            //DAzimuthOffset=Dome.AzimuthOffset.ToString();
            switch (Dome.AzimuthSta)
            {
                case 0x2A:
                    DAzimuthSta = "Slewing CCW";
                    break;
                case 0x2B:
                    DAzimuthSta = "Slewing CW";
                    break;
                case 0x2F:
                    DAzimuthSta = "Stoped";
                    break;
                default:
                    DAzimuthSta = "No data";
                    break;
            }
            switch (Dome.Shutter1Sta)
            {
                case 0x2A:
                    DShutter1Sta = "Opening";
                    break;
                case 0x2B:
                    DShutter1Sta = "Closing";
                    break;
                case 0x2C:
                    DShutter1Sta = "Opened";
                    break;
                case 0x2D:
                    DShutter1Sta = "Closed";
                    break;
                case 0x2F:
                    DShutter1Sta = "Stoped";
                    break;
                case 0xFF:
                    DShutter1Sta = "Unconnected";
                    break;
                default:
                    DShutter1Sta = "No data";
                    break;
            }
            switch (Dome.Shutter2Sta)
            {
                case 0x2A:
                    DShutter2Sta = "Opening";
                    break;
                case 0x2B:
                    DShutter2Sta = "Closing";
                    break;
                case 0x2C:
                    DShutter2Sta = "Opened";
                    break;
                case 0x2D:
                    DShutter2Sta = "Closed";
                    break;
                case 0x2F:
                    DShutter2Sta = "Stoped";
                    break;
                case 0xFF:
                    DShutter2Sta = "Unconnected";
                    break;
                default:
                    DShutter2Sta = "No data";
                    break;
            }
            textBoxDomeState.Text = "Control Mode:\r\n  " + DCtrMode
                //+ "\r\n\r\nAzimuth offset:\r\n  " + DAzimuthOffset 
                + "\r\n\r\nAzimuth:\r\n  " + DAzimuthDeg
                + "\r\n\r\nAzimuthSta:\r\n  " + DAzimuthSta
                + "\r\n\r\nMainShutter:\r\n  " + DShutter1Sta
                + "\r\n\r\nMiniShutter:\r\n  " + DShutter2Sta;
        }
         
        public void TimerEvent(object source, System.Timers.ElapsedEventArgs e)
        {
            TimerFunc func = new TimerFunc(UpdateStatus);
            this.Invoke(func, new Object[] { });
        }
       
        void FocuserToolbox_Shown(object sender, System.EventArgs e)
        {
            Dome.ToolboxOpened = true;//工具面板打开状态
        }

        private void FocuserToolbox_FormClosing(object sender, FormClosingEventArgs e)
        {
            Dome.ToolboxOpened = false;//工具面板关闭状态
            t.Close();
            this.Close();
        }

        private void buttonExit_Click(object sender, EventArgs e)
        {
            Dome.ToolboxOpened = false;//工具面板关闭状态
            t.Close();
            this.Close();
            //FocuserToolbox_FormClosing(sender, (EventArgs)e);
        }
        void FocuserToolbox_Resize(object sender, System.EventArgs e)
        {
            if (this.WindowState == FormWindowState.Minimized)
            {
                this.notifyIcon.Visible = true;
                this.notifyIcon.Text = "Focuser Toolbox";
                this.WindowState = FormWindowState.Minimized;
                //this.ShowInTaskbar = false;//在任务栏不显示
                this.ShowInTaskbar = true;//在任务栏显示
            }
        }

        private void notifyIcon_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            this.notifyIcon.Visible = false;
            this.WindowState = FormWindowState.Normal;
            this.ShowInTaskbar = true;
        }
   
        private void notifyIcon_Click(object sender, System.EventArgs e)
        {
            notifyIcon.Visible = false;
            WindowState = FormWindowState.Normal;
            ShowInTaskbar = true;
        }

        private void statusStrip_ItemClicked(object sender, ToolStripItemClickedEventArgs e)
        {
            //if(i>=15)
            //    System.Diagnostics.Process.Start("http://" + Focuser.m_Website);
        }

        private void comboBoxSlewSpeed_SelectedIndexChanged(object sender, EventArgs e)
        {
            Dome.SlewSpeed = (byte)comboBoxSlewSpeed.SelectedIndex;
            MyDome.WriteProfile();
        }

        private void textBoxAzimuth_KeyPress(object sender, KeyPressEventArgs e)
        {
            Dome.OnlyEnterInt(sender, e);
        }

        private void buttonGoto_Click(object sender, EventArgs e)
        {
            MyDome.GotoDialog();
        }

        private void buttonStop_Click(object sender, EventArgs e)
        {
            MyDome.AbortSlew();
        }

        private void buttonPark_Click(object sender, EventArgs e)
        {
            MyDome.Park();
        }

        private void buttonSlewCW_Click(object sender, EventArgs e)
        {
            if (Dome.SlewSpeed > 0)
                MyDome.SlewAzimuthCWFast();
            else
                MyDome.SlewAzimuthCWSlow();
        }

        private void buttonSlewCCW_Click(object sender, EventArgs e)
        {
            if (Dome.SlewSpeed > 0)
                MyDome.SlewAzimuthCCWFast();
            else
                MyDome.SlewAzimuthCCWSlow();
        }

        private void buttonShutter1Open_Click(object sender, EventArgs e)
        {
            MyDome.OpenShutter1();
        }

        private void buttonShutter1Close_Click(object sender, EventArgs e)
        {
            MyDome.CloseShutter1();
        }

        private void buttonShutter1Stop_Click(object sender, EventArgs e)
        {
            MyDome.AbortShutter1();
        }

        private void buttonShutter2Open_Click(object sender, EventArgs e)
        {
            MyDome.OpenShutter2();
        }

        private void buttonShutter2Close_Click(object sender, EventArgs e)
        {
            MyDome.CloseShutter2();
        }

        private void buttonShutter2Stop_Click(object sender, EventArgs e)
        {
            MyDome.AbortShutter2();
        } 
    }
}
