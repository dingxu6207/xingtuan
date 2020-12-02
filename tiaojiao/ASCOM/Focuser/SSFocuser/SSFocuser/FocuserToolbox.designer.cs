namespace ASCOM.SSFocuser
{
    partial class Toolbox
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Toolbox));
            this.comboBoxMotorSpeed = new System.Windows.Forms.ComboBox();
            this.buttonDefineZero = new System.Windows.Forms.Button();
            this.buttonSlewOut = new System.Windows.Forms.Button();
            this.buttonSlewIn = new System.Windows.Forms.Button();
            this.statusStrip = new System.Windows.Forms.StatusStrip();
            this.currentPosition = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolStripStatusLabel1 = new System.Windows.Forms.ToolStripStatusLabel();
            this.notifyIcon = new System.Windows.Forms.NotifyIcon(this.components);
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.buttonDefineMax = new System.Windows.Forms.Button();
            this.textBoxCurrentPosition = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label13 = new System.Windows.Forms.Label();
            this.statusStrip.SuspendLayout();
            this.groupBox1.SuspendLayout();
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
            "1",
            "2",
            "3",
            "4",
            "5",
            "6",
            "7",
            "8",
            "9"});
            this.comboBoxMotorSpeed.Location = new System.Drawing.Point(120, 44);
            this.comboBoxMotorSpeed.Name = "comboBoxMotorSpeed";
            this.comboBoxMotorSpeed.Size = new System.Drawing.Size(100, 20);
            this.comboBoxMotorSpeed.TabIndex = 1;
            this.comboBoxMotorSpeed.DropDown += new System.EventHandler(this.comboBoxMotorSpeed_DropDown);
            this.comboBoxMotorSpeed.SelectedIndexChanged += new System.EventHandler(this.comboBoxMotorSpeed_SelectedIndexChanged);
            this.comboBoxMotorSpeed.DropDownClosed += new System.EventHandler(this.comboBoxMotorSpeed_DropDownClosed);
            // 
            // buttonDefineZero
            // 
            this.buttonDefineZero.Location = new System.Drawing.Point(9, 108);
            this.buttonDefineZero.Name = "buttonDefineZero";
            this.buttonDefineZero.Size = new System.Drawing.Size(100, 30);
            this.buttonDefineZero.TabIndex = 4;
            this.buttonDefineZero.Text = "Define Zero";
            this.buttonDefineZero.UseVisualStyleBackColor = true;
            this.buttonDefineZero.Click += new System.EventHandler(this.buttonDefineZero_Click);
            // 
            // buttonSlewOut
            // 
            this.buttonSlewOut.Location = new System.Drawing.Point(120, 72);
            this.buttonSlewOut.Name = "buttonSlewOut";
            this.buttonSlewOut.Size = new System.Drawing.Size(100, 30);
            this.buttonSlewOut.TabIndex = 3;
            this.buttonSlewOut.Text = "Slew Out";
            this.buttonSlewOut.UseVisualStyleBackColor = true;
            this.buttonSlewOut.MouseDown += new System.Windows.Forms.MouseEventHandler(this.buttonSlewOut_MouseDown);
            this.buttonSlewOut.MouseUp += new System.Windows.Forms.MouseEventHandler(this.buttonSlewOut_MouseUp);
            // 
            // buttonSlewIn
            // 
            this.buttonSlewIn.Location = new System.Drawing.Point(9, 72);
            this.buttonSlewIn.Name = "buttonSlewIn";
            this.buttonSlewIn.Size = new System.Drawing.Size(100, 30);
            this.buttonSlewIn.TabIndex = 2;
            this.buttonSlewIn.Text = "Slew In";
            this.buttonSlewIn.UseVisualStyleBackColor = true;
            this.buttonSlewIn.MouseDown += new System.Windows.Forms.MouseEventHandler(this.buttonSlewIn_MouseDown);
            this.buttonSlewIn.MouseUp += new System.Windows.Forms.MouseEventHandler(this.buttonSlewIn_MouseUp);
            // 
            // statusStrip
            // 
            this.statusStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.currentPosition,
            this.toolStripStatusLabel1});
            this.statusStrip.Location = new System.Drawing.Point(0, 162);
            this.statusStrip.Name = "statusStrip";
            this.statusStrip.Size = new System.Drawing.Size(255, 22);
            this.statusStrip.TabIndex = 8;
            this.statusStrip.ItemClicked += new System.Windows.Forms.ToolStripItemClickedEventHandler(this.statusStrip_ItemClicked);
            // 
            // currentPosition
            // 
            this.currentPosition.Name = "currentPosition";
            this.currentPosition.Size = new System.Drawing.Size(0, 17);
            // 
            // toolStripStatusLabel1
            // 
            this.toolStripStatusLabel1.BorderSides = ((System.Windows.Forms.ToolStripStatusLabelBorderSides)((((System.Windows.Forms.ToolStripStatusLabelBorderSides.Left | System.Windows.Forms.ToolStripStatusLabelBorderSides.Top)
                        | System.Windows.Forms.ToolStripStatusLabelBorderSides.Right)
                        | System.Windows.Forms.ToolStripStatusLabelBorderSides.Bottom)));
            this.toolStripStatusLabel1.BorderStyle = System.Windows.Forms.Border3DStyle.Sunken;
            this.toolStripStatusLabel1.Name = "toolStripStatusLabel1";
            this.toolStripStatusLabel1.Size = new System.Drawing.Size(240, 17);
            this.toolStripStatusLabel1.Spring = true;
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
            this.groupBox1.Location = new System.Drawing.Point(12, 5);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(230, 148);
            this.groupBox1.TabIndex = 33;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Calibration";
            // 
            // buttonDefineMax
            // 
            this.buttonDefineMax.Location = new System.Drawing.Point(120, 108);
            this.buttonDefineMax.Name = "buttonDefineMax";
            this.buttonDefineMax.Size = new System.Drawing.Size(100, 30);
            this.buttonDefineMax.TabIndex = 5;
            this.buttonDefineMax.Text = "Define MaxStep";
            this.buttonDefineMax.UseVisualStyleBackColor = true;
            this.buttonDefineMax.Click += new System.EventHandler(this.buttonDefineMax_Click);
            // 
            // textBoxCurrentPosition
            // 
            this.textBoxCurrentPosition.Location = new System.Drawing.Point(120, 17);
            this.textBoxCurrentPosition.Name = "textBoxCurrentPosition";
            this.textBoxCurrentPosition.ReadOnly = true;
            this.textBoxCurrentPosition.Size = new System.Drawing.Size(100, 21);
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
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(10, 47);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(89, 12);
            this.label13.TabIndex = 55;
            this.label13.Text = "Rotation Speed";
            // 
            // Toolbox
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(255, 184);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.statusStrip);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.Name = "Toolbox";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Focuser Toolbox";
            this.TopMost = true;
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.FocuserToolbox_FormClosing);
            this.Shown += new System.EventHandler(this.FocuserToolbox_Shown);
            this.Resize += new System.EventHandler(this.FocuserToolbox_Resize);
            this.statusStrip.ResumeLayout(false);
            this.statusStrip.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
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
        private System.Windows.Forms.TextBox textBoxCurrentPosition;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button buttonDefineMax;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel1;
    }
}