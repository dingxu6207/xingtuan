namespace ASCOM.SSFocuser
{
    partial class FocuserToolbox
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FocuserToolbox));
            this.comboBoxMotorSpeed = new System.Windows.Forms.ComboBox();
            this.buttonDefineZero = new System.Windows.Forms.Button();
            this.buttonSlewOut = new System.Windows.Forms.Button();
            this.buttonSlewIn = new System.Windows.Forms.Button();
            this.statusStrip = new System.Windows.Forms.StatusStrip();
            this.currentPosition = new System.Windows.Forms.ToolStripStatusLabel();
            this.notifyIcon = new System.Windows.Forms.NotifyIcon(this.components);
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.checkBoxLowPower = new System.Windows.Forms.CheckBox();
            this.textBoxCurrentPosition = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.checkBoxReverse = new System.Windows.Forms.CheckBox();
            this.label13 = new System.Windows.Forms.Label();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.textBoxCurrentAngle = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.checkBoxReversedCAA = new System.Windows.Forms.CheckBox();
            this.textBoxAngle = new System.Windows.Forms.TextBox();
            this.buttonCAAHalt = new System.Windows.Forms.Button();
            this.buttonCAAMoveTo = new System.Windows.Forms.Button();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.textBoxBTName = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.buttonSetBT = new System.Windows.Forms.Button();
            this.buttonDefineMax = new System.Windows.Forms.Button();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.statusStrip.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.groupBox4.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.SuspendLayout();
            // 
            // comboBoxMotorSpeed
            // 
            this.comboBoxMotorSpeed.AutoCompleteCustomSource.AddRange(new string[] {
            "Uart",
            "WiFi"});
            this.comboBoxMotorSpeed.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxMotorSpeed.FormattingEnabled = true;
            this.comboBoxMotorSpeed.Items.AddRange(new object[] {
            "64",
            "128",
            "196",
            "256",
            "320",
            "384",
            "448"});
            this.comboBoxMotorSpeed.Location = new System.Drawing.Point(130, 44);
            this.comboBoxMotorSpeed.Name = "comboBoxMotorSpeed";
            this.comboBoxMotorSpeed.Size = new System.Drawing.Size(110, 20);
            this.comboBoxMotorSpeed.TabIndex = 35;
            this.comboBoxMotorSpeed.DropDown += new System.EventHandler(this.comboBoxMotorSpeed_DropDown);
            this.comboBoxMotorSpeed.SelectedIndexChanged += new System.EventHandler(this.comboBoxMotorSpeed_SelectedIndexChanged);
            this.comboBoxMotorSpeed.DropDownClosed += new System.EventHandler(this.comboBoxMotorSpeed_DropDownClosed);
            // 
            // buttonDefineZero
            // 
            this.buttonDefineZero.Location = new System.Drawing.Point(12, 102);
            this.buttonDefineZero.Name = "buttonDefineZero";
            this.buttonDefineZero.Size = new System.Drawing.Size(110, 24);
            this.buttonDefineZero.TabIndex = 1;
            this.buttonDefineZero.Text = "Define Zero";
            this.buttonDefineZero.UseVisualStyleBackColor = true;
            this.buttonDefineZero.Click += new System.EventHandler(this.buttonDefineZero_Click);
            // 
            // buttonSlewOut
            // 
            this.buttonSlewOut.Location = new System.Drawing.Point(130, 72);
            this.buttonSlewOut.Name = "buttonSlewOut";
            this.buttonSlewOut.Size = new System.Drawing.Size(110, 24);
            this.buttonSlewOut.TabIndex = 3;
            this.buttonSlewOut.Text = "Slew Out";
            this.buttonSlewOut.UseVisualStyleBackColor = true;
            this.buttonSlewOut.MouseDown += new System.Windows.Forms.MouseEventHandler(this.buttonSlewOut_MouseDown);
            this.buttonSlewOut.MouseUp += new System.Windows.Forms.MouseEventHandler(this.buttonSlewOut_MouseUp);
            // 
            // buttonSlewIn
            // 
            this.buttonSlewIn.Location = new System.Drawing.Point(12, 72);
            this.buttonSlewIn.Name = "buttonSlewIn";
            this.buttonSlewIn.Size = new System.Drawing.Size(110, 24);
            this.buttonSlewIn.TabIndex = 3;
            this.buttonSlewIn.Text = "Slew In";
            this.buttonSlewIn.UseVisualStyleBackColor = true;
            this.buttonSlewIn.MouseDown += new System.Windows.Forms.MouseEventHandler(this.buttonSlewIn_MouseDown);
            this.buttonSlewIn.MouseUp += new System.Windows.Forms.MouseEventHandler(this.buttonSlewIn_MouseUp);
            // 
            // statusStrip
            // 
            this.statusStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.currentPosition});
            this.statusStrip.Location = new System.Drawing.Point(0, 280);
            this.statusStrip.Name = "statusStrip";
            this.statusStrip.Size = new System.Drawing.Size(275, 22);
            this.statusStrip.TabIndex = 8;
            // 
            // currentPosition
            // 
            this.currentPosition.Name = "currentPosition";
            this.currentPosition.Size = new System.Drawing.Size(0, 17);
            // 
            // notifyIcon
            // 
            this.notifyIcon.Icon = ((System.Drawing.Icon)(resources.GetObject("notifyIcon.Icon")));
            this.notifyIcon.Text = "notifyIcon";
            this.notifyIcon.Click += new System.EventHandler(this.notifyIcon_Click);
            this.notifyIcon.MouseDoubleClick += new System.Windows.Forms.MouseEventHandler(this.notifyIcon_MouseDoubleClick);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.buttonDefineMax);
            this.groupBox1.Controls.Add(this.textBoxCurrentPosition);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.label13);
            this.groupBox1.Controls.Add(this.buttonDefineZero);
            this.groupBox1.Controls.Add(this.comboBoxMotorSpeed);
            this.groupBox1.Controls.Add(this.buttonSlewIn);
            this.groupBox1.Controls.Add(this.buttonSlewOut);
            this.groupBox1.Location = new System.Drawing.Point(12, 2);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(250, 137);
            this.groupBox1.TabIndex = 33;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Alignment";
            // 
            // checkBoxLowPower
            // 
            this.checkBoxLowPower.AutoSize = true;
            this.checkBoxLowPower.Enabled = false;
            this.checkBoxLowPower.Location = new System.Drawing.Point(12, 20);
            this.checkBoxLowPower.Name = "checkBoxLowPower";
            this.checkBoxLowPower.Size = new System.Drawing.Size(78, 16);
            this.checkBoxLowPower.TabIndex = 64;
            this.checkBoxLowPower.Text = "Low Power";
            this.checkBoxLowPower.UseVisualStyleBackColor = true;
            this.checkBoxLowPower.CheckStateChanged += new System.EventHandler(this.checkBoxLowPower_CheckStateChanged);
            // 
            // textBoxCurrentPosition
            // 
            this.textBoxCurrentPosition.Location = new System.Drawing.Point(130, 17);
            this.textBoxCurrentPosition.Name = "textBoxCurrentPosition";
            this.textBoxCurrentPosition.ReadOnly = true;
            this.textBoxCurrentPosition.Size = new System.Drawing.Size(110, 21);
            this.textBoxCurrentPosition.TabIndex = 61;
            this.textBoxCurrentPosition.Text = "0";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(10, 20);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(101, 12);
            this.label2.TabIndex = 60;
            this.label2.Text = "Current Position";
            // 
            // checkBoxReverse
            // 
            this.checkBoxReverse.AutoSize = true;
            this.checkBoxReverse.Enabled = false;
            this.checkBoxReverse.Location = new System.Drawing.Point(130, 20);
            this.checkBoxReverse.Name = "checkBoxReverse";
            this.checkBoxReverse.Size = new System.Drawing.Size(66, 16);
            this.checkBoxReverse.TabIndex = 55;
            this.checkBoxReverse.Text = "Reverse";
            this.checkBoxReverse.UseVisualStyleBackColor = true;
            this.checkBoxReverse.CheckStateChanged += new System.EventHandler(this.checkBoxReverse_CheckStateChanged);
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(10, 47);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(89, 12);
            this.label13.TabIndex = 55;
            this.label13.Text = "Rotation Speed";
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.textBoxCurrentAngle);
            this.groupBox4.Controls.Add(this.label1);
            this.groupBox4.Controls.Add(this.checkBoxReversedCAA);
            this.groupBox4.Controls.Add(this.textBoxAngle);
            this.groupBox4.Controls.Add(this.buttonCAAHalt);
            this.groupBox4.Controls.Add(this.buttonCAAMoveTo);
            this.groupBox4.Location = new System.Drawing.Point(580, 139);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(250, 109);
            this.groupBox4.TabIndex = 32;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "Camera Angle Adjust";
            this.groupBox4.Visible = false;
            // 
            // textBoxCurrentAngle
            // 
            this.textBoxCurrentAngle.Location = new System.Drawing.Point(130, 20);
            this.textBoxCurrentAngle.Name = "textBoxCurrentAngle";
            this.textBoxCurrentAngle.ReadOnly = true;
            this.textBoxCurrentAngle.Size = new System.Drawing.Size(110, 21);
            this.textBoxCurrentAngle.TabIndex = 59;
            this.textBoxCurrentAngle.Text = "0";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(10, 24);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(83, 12);
            this.label1.TabIndex = 58;
            this.label1.Text = "Current Angle";
            // 
            // checkBoxReversedCAA
            // 
            this.checkBoxReversedCAA.AutoSize = true;
            this.checkBoxReversedCAA.Location = new System.Drawing.Point(11, 52);
            this.checkBoxReversedCAA.Name = "checkBoxReversedCAA";
            this.checkBoxReversedCAA.Size = new System.Drawing.Size(72, 16);
            this.checkBoxReversedCAA.TabIndex = 58;
            this.checkBoxReversedCAA.Text = "Reversed";
            this.checkBoxReversedCAA.UseVisualStyleBackColor = true;
            this.checkBoxReversedCAA.CheckStateChanged += new System.EventHandler(this.checkBoxReservedCAA_CheckStateChanged);
            // 
            // textBoxAngle
            // 
            this.textBoxAngle.Location = new System.Drawing.Point(11, 79);
            this.textBoxAngle.Name = "textBoxAngle";
            this.textBoxAngle.Size = new System.Drawing.Size(70, 21);
            this.textBoxAngle.TabIndex = 30;
            this.textBoxAngle.Text = "0";
            // 
            // buttonCAAHalt
            // 
            this.buttonCAAHalt.Location = new System.Drawing.Point(170, 77);
            this.buttonCAAHalt.Name = "buttonCAAHalt";
            this.buttonCAAHalt.Size = new System.Drawing.Size(70, 24);
            this.buttonCAAHalt.TabIndex = 2;
            this.buttonCAAHalt.Text = "Halt";
            this.buttonCAAHalt.UseVisualStyleBackColor = true;
            this.buttonCAAHalt.Click += new System.EventHandler(this.HaltCAA);
            // 
            // buttonCAAMoveTo
            // 
            this.buttonCAAMoveTo.Location = new System.Drawing.Point(87, 78);
            this.buttonCAAMoveTo.Name = "buttonCAAMoveTo";
            this.buttonCAAMoveTo.Size = new System.Drawing.Size(70, 24);
            this.buttonCAAMoveTo.TabIndex = 1;
            this.buttonCAAMoveTo.Text = "Move To";
            this.buttonCAAMoveTo.UseVisualStyleBackColor = true;
            this.buttonCAAMoveTo.Click += new System.EventHandler(this.MoveToCAA);
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.textBoxBTName);
            this.groupBox3.Controls.Add(this.label4);
            this.groupBox3.Controls.Add(this.buttonSetBT);
            this.groupBox3.Location = new System.Drawing.Point(12, 140);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(250, 80);
            this.groupBox3.TabIndex = 63;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Bluetooth";
            // 
            // textBoxBTName
            // 
            this.textBoxBTName.Location = new System.Drawing.Point(130, 18);
            this.textBoxBTName.Name = "textBoxBTName";
            this.textBoxBTName.Size = new System.Drawing.Size(110, 21);
            this.textBoxBTName.TabIndex = 63;
            this.textBoxBTName.Text = "SkyRoverFocuser";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(10, 22);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(89, 12);
            this.label4.TabIndex = 62;
            this.label4.Text = "Bluetooth Name";
            // 
            // buttonSetBT
            // 
            this.buttonSetBT.Location = new System.Drawing.Point(72, 46);
            this.buttonSetBT.Name = "buttonSetBT";
            this.buttonSetBT.Size = new System.Drawing.Size(110, 24);
            this.buttonSetBT.TabIndex = 5;
            this.buttonSetBT.Text = "Set Bluetooth";
            this.buttonSetBT.UseVisualStyleBackColor = true;
            this.buttonSetBT.Click += new System.EventHandler(this.buttonSetBT_Click);
            // 
            // buttonDefineMax
            // 
            this.buttonDefineMax.Location = new System.Drawing.Point(130, 102);
            this.buttonDefineMax.Name = "buttonDefineMax";
            this.buttonDefineMax.Size = new System.Drawing.Size(110, 24);
            this.buttonDefineMax.TabIndex = 65;
            this.buttonDefineMax.Text = "Define MaxStep";
            this.buttonDefineMax.UseVisualStyleBackColor = true;
            this.buttonDefineMax.Click += new System.EventHandler(this.buttonDefineMax_Click);
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.checkBoxLowPower);
            this.groupBox2.Controls.Add(this.checkBoxReverse);
            this.groupBox2.Location = new System.Drawing.Point(12, 221);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(250, 48);
            this.groupBox2.TabIndex = 65;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Advanced";
            // 
            // FocuserToolbox
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(275, 302);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.groupBox4);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.statusStrip);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.Name = "FocuserToolbox";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "Focuser Toolbox";
            this.TopMost = true;
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.FocuserToolbox_FormClosing);
            this.Shown += new System.EventHandler(this.FocuserToolbox_Shown);
            this.Resize += new System.EventHandler(this.FocuserToolbox_Resize);
            this.statusStrip.ResumeLayout(false);
            this.statusStrip.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox4.ResumeLayout(false);
            this.groupBox4.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        void FocusControl_FormClosing(object sender, System.Windows.Forms.FormClosingEventArgs e)
        {
            e.Cancel = true;
        }

        #endregion

        //private ASCOM.SSFocuser.Focuser MyFocuser;//graycode
        //private Config Config;
        private System.Windows.Forms.Button buttonDefineZero;
        private System.Windows.Forms.Button buttonSlewOut;
        private System.Windows.Forms.Button buttonSlewIn;
        private System.Windows.Forms.StatusStrip statusStrip;
        private System.Windows.Forms.NotifyIcon notifyIcon;
        private System.Windows.Forms.ToolStripStatusLabel currentPosition;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.ComboBox comboBoxMotorSpeed;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.CheckBox checkBoxReverse;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.TextBox textBoxAngle;
        private System.Windows.Forms.Button buttonCAAHalt;
        private System.Windows.Forms.Button buttonCAAMoveTo;
        private System.Windows.Forms.TextBox textBoxCurrentAngle;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.CheckBox checkBoxReversedCAA;
        private System.Windows.Forms.TextBox textBoxCurrentPosition;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.TextBox textBoxBTName;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Button buttonSetBT;
        private System.Windows.Forms.CheckBox checkBoxLowPower;
        private System.Windows.Forms.Button buttonDefineMax;
        private System.Windows.Forms.GroupBox groupBox2;
    }
}