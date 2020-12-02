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
    public partial class FocuserToolbox : Form
    {
        Focuser MyFocuser;// = new Focuser();//graycode
        System.Timers.Timer t;
        public delegate void TimerFunc();
        private static byte SlewStatue = 0;
        private static byte TimerCount = 0;
        public bool bChanging = false;
        
        public FocuserToolbox(Focuser f)
        {
            MyFocuser = f;
            InitializeComponent();
            //MyFocuser.GetConfig();
            t = new System.Timers.Timer(500);//500毫秒读取一次；
            t.Elapsed += new System.Timers.ElapsedEventHandler(TimerEvent);//到达时间的时候执行事件；
            t.AutoReset = true;//设置是执行一次（false）还是一直执行(true)；
            t.Enabled = true;//是否执行System.Timers.Timer.Elapsed事件；
        }
        public void UpdateStatus()
        {
            if (Focuser.m_IsMoving)
            {
                //buttonSlewIn.Enabled = false;
                //buttonSlewOut.Enabled = false;
                buttonDefineZero.Enabled = false;
                buttonDefineMax.Enabled = false;
            }
            else
            {
                //buttonSlewIn.Enabled = true;
                //buttonSlewOut.Enabled = true;
                buttonDefineZero.Enabled = true;
                buttonDefineMax.Enabled = true;
            }
            if (TimerCount < 100)
                TimerCount++;
            if ((!bChanging) && (TimerCount>5))
            {
                if (checkBoxReverse.Checked != Focuser.m_MotorReverse)
                    checkBoxReverse.Checked = Focuser.m_MotorReverse;
                if (checkBoxLowPower.Checked != Focuser.m_LowPower)
                    checkBoxLowPower.Checked = Focuser.m_LowPower;
                if (comboBoxMotorSpeed.SelectedItem.ToString() != Focuser.m_MotorSpeed.ToString())
                {
                    if (comboBoxMotorSpeed.Items.Contains(Focuser.m_MotorSpeed.ToString()))
                        comboBoxMotorSpeed.SelectedItem = Focuser.m_MotorSpeed.ToString();
                }

            }
            textBoxCurrentPosition.Text = Focuser.m_CurrentPosition.ToString();
            //currentPosition.Text = "Position: " + Focuser.m_CurrentPosition.ToString() + " Reverse: " + ((Focuser.m_MotorReverse==true)?"Yes":"No") + " Speed: " + Focuser.m_MotorSpeed.ToString();
            currentPosition.Text = "Position: " + Focuser.m_CurrentPosition.ToString() + " Speed: " + Focuser.m_MotorSpeed.ToString();
        }
        public void TimerEvent(object source, System.Timers.ElapsedEventArgs e)
        {
            if (SlewStatue == 1)
                MyFocuser.SlewOut();
            else if (SlewStatue == 2)
                MyFocuser.SlewIn();
            TimerFunc func = new TimerFunc(UpdateStatus);
            this.Invoke(func, new Object[] { });
        }

        void FocuserToolbox_Shown(object sender, System.EventArgs e)
        {
            MyRefresh();
        }

        private void FocuserToolbox_FormClosing(object sender, FormClosingEventArgs e)
        {
            t.Close();
            this.Close();
        }

        private void buttonExit_Click(object sender, EventArgs e)
        {
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
                this.ShowInTaskbar = false;//在任务栏不显示
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
            bChanging = true;
        }

        private void comboBoxMotorSpeed_DropDownClosed(object sender, EventArgs e)
        {
            
        }
        private void comboBoxMotorSpeed_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (comboBoxMotorSpeed.SelectedItem.ToString() != Focuser.m_MotorSpeed.ToString())
            {
                MyFocuser.SetSpeed(Convert.ToUInt16(comboBoxMotorSpeed.SelectedItem));
                TimerCount = 0;     
            }
            bChanging = false;
        }
        private void checkBoxReverse_CheckStateChanged(object sender, EventArgs e)
        {
            if (checkBoxReverse.Checked != Focuser.m_MotorReverse)//确保刷新状态下不发送
            {
                bChanging = true;
                DialogResult dr = MessageBox.Show("Are you sure you want to change the direction of the stepper motor?", "Confirmation information", MessageBoxButtons.OKCancel, MessageBoxIcon.Question);
                if (dr == DialogResult.OK)
                {
                    MyFocuser.SetReverse(checkBoxReverse.Checked);
                    TimerCount = 0;
                }
                else
                {
                    //MyFocuser.SetReverse(!checkBoxReverse.Checked);
                    checkBoxReverse.Checked = !checkBoxReverse.Checked;
                }
                bChanging = false;
            }
        }
        
        private void checkBoxLowPower_CheckStateChanged(object sender, EventArgs e)
        {
            if (checkBoxLowPower.Checked != Focuser.m_LowPower)//
            {
                bChanging = true;
                MyFocuser.SetLowPower(checkBoxLowPower.Checked);
                TimerCount = 0;
                bChanging = false;
            }
        }
        private void MyRefresh()
        {
            checkBoxLowPower.Checked = Focuser.m_LowPower;
            checkBoxReverse.Checked = Focuser.m_MotorReverse;
            if (comboBoxMotorSpeed.Items.Contains(Focuser.m_MotorSpeed.ToString()))
                comboBoxMotorSpeed.SelectedItem = Focuser.m_MotorSpeed.ToString();
            textBoxBTName.Text = Focuser.m_BTName;
        }

        private void MySaveData()
        {
            try
            {
                Focuser.m_LowPower = checkBoxLowPower.Checked;
                Focuser.m_MotorReverse = checkBoxReverse.Checked;
                Focuser.m_MotorSpeed = Convert.ToUInt16(comboBoxMotorSpeed.SelectedItem);
                Focuser.m_BTName = textBoxBTName.Text;
            }
            catch
            { }
            MyFocuser.WriteProfile();
        }
        
        private void Halt(object sender, EventArgs e)
        {
            MyFocuser.Halt();
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

        private void buttonSetBT_Click(object sender, EventArgs e)
        {
            if (textBoxBTName.Text == "")
                MessageBox.Show("Bluetooth Name cannot be empty !");
            else if (textBoxBTName.Text.Length > 15)
                MessageBox.Show("Bluetooth Name length is limited to 15 bytes !");
            else
            {
                MyFocuser.SetBluetooth(textBoxBTName.Text);
                MessageBox.Show("Please refresh your Bluetooth device to see if it succeeds !");
            }
        }

        private void textBoxSSID_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar == 35 || e.KeyChar == 58)//禁止输入#和：
            {
                e.Handled = true;
            }
        }

        private void textBoxPWD_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar == 35 || e.KeyChar == 58)//禁止输入#和：
            {
                e.Handled = true;
            }
        }

        private void textBoxDeviceName_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar == 35 || e.KeyChar == 58)//禁止输入#和：
            {
                e.Handled = true;
            }
        }

        private void textBoxSetPos_KeyPress(object sender, KeyPressEventArgs e)
        {
            Focuser.OnlyEnterPlusInt(sender, e);
        }

        private void linkLabel_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            System.Diagnostics.Process.Start("http://www.sky-rover.cn");
        }

        private void textBoxLocalPort_KeyPress(object sender, KeyPressEventArgs e)
        {
            Focuser.OnlyEnterPlusInt(sender, e);
        }

        private void textBoxMaxStep_KeyPress(object sender, KeyPressEventArgs e)
        {
            Focuser.OnlyEnterPlusInt(sender, e);
        }

        private void textBoxMaxIncrement_KeyPress(object sender, KeyPressEventArgs e)
        {
            Focuser.OnlyEnterPlusInt(sender, e);
        }

        private void textBoxStepSize_KeyPress(object sender, KeyPressEventArgs e)
        {
            Focuser.OnlyEnterPlusNumber(sender, e);
        }

        private void textBoxStepPerDeg_KeyPress(object sender, KeyPressEventArgs e)
        {
            Focuser.OnlyEnterPlusNumber(sender, e);
        }

        private void textBoxThreshold_KeyPress(object sender, KeyPressEventArgs e)
        {
            Focuser.OnlyEnterPlusInt(sender, e);
        }

        private void textBoxPosition_KeyPress(object sender, KeyPressEventArgs e)
        {
            Focuser.OnlyEnterInt(sender, e);
        }

        private void checkBoxReservedCAA_CheckStateChanged(object sender, EventArgs e)
        {

        }
        //
        private void MoveToCAA(object sender, EventArgs e)
        {

        }

        private void HaltCAA(object sender, EventArgs e)
        {

        }

        private void buttonSetCover_Click(object sender, EventArgs e)
        {
            using (CoverSetting F = new CoverSetting())
            {
                var result = F.ShowDialog();
                if (result == System.Windows.Forms.DialogResult.OK)
                {
                    MyFocuser.WriteProfile(); // Persist device configuration values to the ASCOM Profile store
                }
            }
        }

        
           
    }
}
