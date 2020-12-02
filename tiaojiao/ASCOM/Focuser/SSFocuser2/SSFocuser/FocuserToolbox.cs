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
using ASCOM.SSFocuser;

namespace ASCOM.SSFocuser
{
    public partial class Toolbox : Form
    {
        Focuser MyFocuser;// = new Focuser();//graycode
        System.Timers.Timer t;
        public delegate void TimerFunc();
        private static byte SlewStatue = 0;
        //private static byte j = 0;
        public bool bUpdate = false;
        public static byte i=0,j=0;
        //public string TmpWebsite="www.graycode.cn";
        public bool FirstTime=true;

        public Toolbox(Focuser f)
        {
            MyFocuser = f;
            InitializeComponent();
            
            t = new System.Timers.Timer(500);//500毫秒执行一次；
            t.Elapsed += new System.Timers.ElapsedEventHandler(TimerEvent);//到达时间的时候执行事件；
            t.AutoReset = true;//设置是执行一次（false）还是一直执行(true)；
            t.Enabled = true;//是否执行System.Timers.Timer.Elapsed事件；
        }
        public void UpdateStatus()
        {
            if (Focuser.m_IsMoving)
            {
                buttonDefineZero.Enabled = false;
                buttonDefineMax.Enabled = false;
            }
            else
            {
                buttonDefineZero.Enabled = true;
                buttonDefineMax.Enabled = true;
            }
            if (FirstTime)//第一次更新速度在这里执行，避免界面打开缓慢
            {
                if (comboBoxMotorSpeed.Items.Contains(Focuser.m_MotorSpeed.ToString()))
                    comboBoxMotorSpeed.SelectedItem = Focuser.m_MotorSpeed.ToString();
                FirstTime = false;
            }
            if (j < 100)
                j++;
            if ((!bUpdate) && (j>=10))//5秒钟后再更改
            {
                if (comboBoxMotorSpeed.SelectedItem.ToString() != Focuser.m_MotorSpeed.ToString())
                {
                    if (comboBoxMotorSpeed.Items.Contains(Focuser.m_MotorSpeed.ToString()))
                        comboBoxMotorSpeed.SelectedItem = Focuser.m_MotorSpeed.ToString();
                }
            }
            textBoxCurrentPosition.Text = Focuser.m_CurrentPosition.ToString();
            //currentPosition.Text = " Temperature: " + Focuser.m_CurrentTemperature.ToString() + " Speed: " + Focuser.m_MotorSpeed.ToString();
            if (Focuser.ErrorInfo == 1)
            {
                toolStripStatusLabel1.ForeColor = System.Drawing.Color.Red;
                toolStripStatusLabel1.Text = "Communication Error, Please Check !";
            }
            else
            {
                toolStripStatusLabel1.ForeColor = System.Drawing.Color.Black;
                switch (i)
                {
                    case 0:
                        toolStripStatusLabel1.Text = "Temperature: " + Focuser.m_CurrentTemperature.ToString() + " ℃";
                        break;
                    case 4:
                        if (Focuser.m_MotorReverse)
                            toolStripStatusLabel1.Text = "Motor Direction: Reverse";
                        else
                            toolStripStatusLabel1.Text = "Motor Direction: Normal";
                        break;
                    case 8:
                        toolStripStatusLabel1.Text = "Motor Microstep: " + Focuser.m_MotorMicrostep.ToString();
                        break;
                    case 12:
                        if (Focuser.m_LowPower)
                            toolStripStatusLabel1.Text = "Power Waste: Low";
                        else
                            toolStripStatusLabel1.Text = "Power Waste: Normal";
                        break;
                    case 16:
                        toolStripStatusLabel1.Text = "Technical support: " + Focuser.m_Website;
                        break;
                }
            }
        }
        public void TimerEvent(object source, System.Timers.ElapsedEventArgs e)
        {
            if (SlewStatue == 1)
            {
                MyFocuser.SlewOut();
            }
            else if (SlewStatue == 2)
            {
                MyFocuser.SlewIn();
            }
            //查询时间
            //GetPosition-0.5S,GetMovState-1S,GetSpeed-5S,GetReverse()-10S,GetMicrostep-10S,GetTemperature()-10S,GetPowerState-10S
            MyFocuser.GetPosition();
            switch (i)
            {
                case 0:
                    MyFocuser.GetSpeed();
                    MyFocuser.GetReverse();
                    break;
                case 1:
                    MyFocuser.GetMovState();
                    break;
                case 3:
                    MyFocuser.GetMovState();
                    break;
                case 5:
                    MyFocuser.GetMovState();
                    MyFocuser.GetTemperature();
                    break;
                case 7:
                    MyFocuser.GetMovState();
                    break;
                case 9:
                    MyFocuser.GetMovState();
                    break;
                case 10:
                    MyFocuser.GetSpeed();
                    MyFocuser.GetMicrostep();
                    break;
                case 11:
                    MyFocuser.GetMovState();
                    break;
                case 13:
                    MyFocuser.GetMovState();
                    break;
                case 15:
                    MyFocuser.GetMovState();
                    MyFocuser.GetPowerWaste();              
                    break;
                case 17:
                    MyFocuser.GetMovState();
                    break;
                case 19:
                    MyFocuser.GetMovState();
                    break;
            }
            if (i >= 20)
                i = 0;
            else
                i++;
            TimerFunc func = new TimerFunc(UpdateStatus);
            this.Invoke(func, new Object[] { });
        }

        void FocuserToolbox_Shown(object sender, System.EventArgs e)
        {
            Focuser.ToolboxOpened = true;//工具面板打开状态
        }

        private void FocuserToolbox_FormClosing(object sender, FormClosingEventArgs e)
        {
            Focuser.ToolboxOpened = false;//工具面板关闭状态
            t.Close();
            this.Close();
        }

        private void buttonExit_Click(object sender, EventArgs e)
        {
            Focuser.ToolboxOpened = false;//工具面板关闭状态
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
        //下拉列表框按顺序执行如下三个动作
        private void comboBoxMotorSpeed_DropDown(object sender, EventArgs e)
        {
            bUpdate = true;
        }

        private void comboBoxMotorSpeed_DropDownClosed(object sender, EventArgs e)
        {
            
        }
        private void comboBoxMotorSpeed_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (comboBoxMotorSpeed.SelectedItem.ToString() != Focuser.m_MotorSpeed.ToString())
            {
                MyFocuser.SetSpeed(Convert.ToByte(comboBoxMotorSpeed.SelectedItem));
                j = 0;     
            }
            bUpdate = false;
        }

        void buttonSlewOut_MouseDown(object sender, System.Windows.Forms.MouseEventArgs e)
        {
            //MyFocuser.SlewOut();
            SlewStatue = 1;
        }

        void buttonSlewOut_MouseUp(object sender, System.Windows.Forms.MouseEventArgs e)
        {
            SlewStatue = 0;
            MyFocuser.Halt();
        }

        void buttonSlewIn_MouseDown(object sender, System.Windows.Forms.MouseEventArgs e)
        {
            //MyFocuser.SlewIn();
            SlewStatue = 2;
        }

        void buttonSlewIn_MouseUp(object sender, System.Windows.Forms.MouseEventArgs e)
        {
            SlewStatue = 0;
            MyFocuser.Halt();
        }

        private void buttonDefineZero_Click(object sender, EventArgs e)
        {
            MyFocuser.DefinePosition(0);
        }

        private void buttonDefineMax_Click(object sender, EventArgs e)
        {
            //MyFocuser.DefinePosition(Focuser.m_CurrentPosition);
            if (Focuser.m_CurrentPosition < 1000)
            {
                MessageBox.Show("MaxStep cannot be less than 1000 !");
                return;
            }
            Focuser.m_MaxStep = Focuser.m_CurrentPosition;
            Focuser.m_MaxIncrement = Focuser.m_CurrentPosition;
            MyFocuser.WriteProfile();
        }

        private void notifyIcon_Click(object sender, System.EventArgs e)
        {
            notifyIcon.Visible = false;
            WindowState = FormWindowState.Normal;
            ShowInTaskbar = true;
        }

        private void textBoxPosition_KeyPress(object sender, KeyPressEventArgs e)
        {
            Focuser.OnlyEnterInt(sender, e);
        }

        private void statusStrip_ItemClicked(object sender, ToolStripItemClickedEventArgs e)
        {
            if(i>=15)
                System.Diagnostics.Process.Start("http://" + Focuser.m_Website);
        }    
    }
}
