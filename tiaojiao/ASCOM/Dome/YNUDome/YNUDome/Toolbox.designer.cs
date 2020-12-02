namespace ASCOM.YNUDome
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
            this.comboBoxSlewSpeed = new System.Windows.Forms.ComboBox();
            this.buttonStop = new System.Windows.Forms.Button();
            this.buttonSlewCCW = new System.Windows.Forms.Button();
            this.buttonSlewCW = new System.Windows.Forms.Button();
            this.statusStrip = new System.Windows.Forms.StatusStrip();
            this.currentPosition = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolStripStatusLabel1 = new System.Windows.Forms.ToolStripStatusLabel();
            this.notifyIcon = new System.Windows.Forms.NotifyIcon(this.components);
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.buttonPark = new System.Windows.Forms.Button();
            this.buttonGoto = new System.Windows.Forms.Button();
            this.buttonShutter1Open = new System.Windows.Forms.Button();
            this.textBoxDomeState = new System.Windows.Forms.TextBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.buttonShutter2Stop = new System.Windows.Forms.Button();
            this.buttonShutter1Stop = new System.Windows.Forms.Button();
            this.buttonShutter2Close = new System.Windows.Forms.Button();
            this.buttonShutter1Close = new System.Windows.Forms.Button();
            this.buttonShutter2Open = new System.Windows.Forms.Button();
            this.statusStrip.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.SuspendLayout();
            // 
            // comboBoxSlewSpeed
            // 
            this.comboBoxSlewSpeed.AutoCompleteCustomSource.AddRange(new string[] {
            "Uart",
            "WiFi"});
            this.comboBoxSlewSpeed.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxSlewSpeed.FormattingEnabled = true;
            this.comboBoxSlewSpeed.Items.AddRange(new object[] {
            "Slow",
            "Fast"});
            this.comboBoxSlewSpeed.Location = new System.Drawing.Point(12, 22);
            this.comboBoxSlewSpeed.Name = "comboBoxSlewSpeed";
            this.comboBoxSlewSpeed.Size = new System.Drawing.Size(80, 20);
            this.comboBoxSlewSpeed.TabIndex = 1;
            this.comboBoxSlewSpeed.SelectedIndexChanged += new System.EventHandler(this.comboBoxSlewSpeed_SelectedIndexChanged);
            // 
            // buttonStop
            // 
            this.buttonStop.Location = new System.Drawing.Point(12, 80);
            this.buttonStop.Name = "buttonStop";
            this.buttonStop.Size = new System.Drawing.Size(80, 25);
            this.buttonStop.TabIndex = 4;
            this.buttonStop.Text = "Stop";
            this.buttonStop.UseVisualStyleBackColor = true;
            this.buttonStop.Click += new System.EventHandler(this.buttonStop_Click);
            // 
            // buttonSlewCCW
            // 
            this.buttonSlewCCW.Location = new System.Drawing.Point(100, 50);
            this.buttonSlewCCW.Name = "buttonSlewCCW";
            this.buttonSlewCCW.Size = new System.Drawing.Size(80, 25);
            this.buttonSlewCCW.TabIndex = 3;
            this.buttonSlewCCW.Text = "Slew(CCW)";
            this.buttonSlewCCW.UseVisualStyleBackColor = true;
            this.buttonSlewCCW.Click += new System.EventHandler(this.buttonSlewCCW_Click);
            // 
            // buttonSlewCW
            // 
            this.buttonSlewCW.Location = new System.Drawing.Point(12, 50);
            this.buttonSlewCW.Name = "buttonSlewCW";
            this.buttonSlewCW.Size = new System.Drawing.Size(80, 25);
            this.buttonSlewCW.TabIndex = 2;
            this.buttonSlewCW.Text = "Slew(CW)";
            this.buttonSlewCW.UseVisualStyleBackColor = true;
            this.buttonSlewCW.Click += new System.EventHandler(this.buttonSlewCW_Click);
            // 
            // statusStrip
            // 
            this.statusStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.currentPosition,
            this.toolStripStatusLabel1});
            this.statusStrip.Location = new System.Drawing.Point(0, 270);
            this.statusStrip.Name = "statusStrip";
            this.statusStrip.Size = new System.Drawing.Size(334, 22);
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
            this.toolStripStatusLabel1.Size = new System.Drawing.Size(319, 17);
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
            this.groupBox1.Controls.Add(this.buttonPark);
            this.groupBox1.Controls.Add(this.buttonGoto);
            this.groupBox1.Controls.Add(this.buttonSlewCCW);
            this.groupBox1.Controls.Add(this.buttonStop);
            this.groupBox1.Controls.Add(this.buttonSlewCW);
            this.groupBox1.Controls.Add(this.comboBoxSlewSpeed);
            this.groupBox1.Location = new System.Drawing.Point(12, 12);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(192, 120);
            this.groupBox1.TabIndex = 33;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Dome";
            // 
            // buttonPark
            // 
            this.buttonPark.Location = new System.Drawing.Point(100, 80);
            this.buttonPark.Name = "buttonPark";
            this.buttonPark.Size = new System.Drawing.Size(80, 25);
            this.buttonPark.TabIndex = 62;
            this.buttonPark.Text = "Park";
            this.buttonPark.UseVisualStyleBackColor = true;
            this.buttonPark.Click += new System.EventHandler(this.buttonPark_Click);
            // 
            // buttonGoto
            // 
            this.buttonGoto.Location = new System.Drawing.Point(100, 20);
            this.buttonGoto.Name = "buttonGoto";
            this.buttonGoto.Size = new System.Drawing.Size(80, 25);
            this.buttonGoto.TabIndex = 5;
            this.buttonGoto.Text = "Goto";
            this.buttonGoto.UseVisualStyleBackColor = true;
            this.buttonGoto.Click += new System.EventHandler(this.buttonGoto_Click);
            // 
            // buttonShutter1Open
            // 
            this.buttonShutter1Open.Location = new System.Drawing.Point(12, 20);
            this.buttonShutter1Open.Name = "buttonShutter1Open";
            this.buttonShutter1Open.Size = new System.Drawing.Size(80, 25);
            this.buttonShutter1Open.TabIndex = 63;
            this.buttonShutter1Open.Text = "Open";
            this.buttonShutter1Open.UseVisualStyleBackColor = true;
            this.buttonShutter1Open.Click += new System.EventHandler(this.buttonShutter1Open_Click);
            // 
            // textBoxDomeState
            // 
            this.textBoxDomeState.Location = new System.Drawing.Point(213, 20);
            this.textBoxDomeState.Multiline = true;
            this.textBoxDomeState.Name = "textBoxDomeState";
            this.textBoxDomeState.ReadOnly = true;
            this.textBoxDomeState.Size = new System.Drawing.Size(109, 238);
            this.textBoxDomeState.TabIndex = 61;
            this.textBoxDomeState.Text = "State";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.buttonShutter2Stop);
            this.groupBox2.Controls.Add(this.buttonShutter1Stop);
            this.groupBox2.Controls.Add(this.buttonShutter2Close);
            this.groupBox2.Controls.Add(this.buttonShutter1Close);
            this.groupBox2.Controls.Add(this.buttonShutter2Open);
            this.groupBox2.Controls.Add(this.buttonShutter1Open);
            this.groupBox2.Location = new System.Drawing.Point(12, 138);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(192, 120);
            this.groupBox2.TabIndex = 34;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "MainShutter     MiniShutter";
            // 
            // buttonShutter2Stop
            // 
            this.buttonShutter2Stop.Location = new System.Drawing.Point(100, 80);
            this.buttonShutter2Stop.Name = "buttonShutter2Stop";
            this.buttonShutter2Stop.Size = new System.Drawing.Size(80, 25);
            this.buttonShutter2Stop.TabIndex = 66;
            this.buttonShutter2Stop.Text = "Stop";
            this.buttonShutter2Stop.UseVisualStyleBackColor = true;
            this.buttonShutter2Stop.Click += new System.EventHandler(this.buttonShutter2Stop_Click);
            // 
            // buttonShutter1Stop
            // 
            this.buttonShutter1Stop.Location = new System.Drawing.Point(12, 80);
            this.buttonShutter1Stop.Name = "buttonShutter1Stop";
            this.buttonShutter1Stop.Size = new System.Drawing.Size(80, 25);
            this.buttonShutter1Stop.TabIndex = 65;
            this.buttonShutter1Stop.Text = "Stop";
            this.buttonShutter1Stop.UseVisualStyleBackColor = true;
            this.buttonShutter1Stop.Click += new System.EventHandler(this.buttonShutter1Stop_Click);
            // 
            // buttonShutter2Close
            // 
            this.buttonShutter2Close.Location = new System.Drawing.Point(100, 50);
            this.buttonShutter2Close.Name = "buttonShutter2Close";
            this.buttonShutter2Close.Size = new System.Drawing.Size(80, 25);
            this.buttonShutter2Close.TabIndex = 65;
            this.buttonShutter2Close.Text = "Close";
            this.buttonShutter2Close.UseVisualStyleBackColor = true;
            this.buttonShutter2Close.Click += new System.EventHandler(this.buttonShutter2Close_Click);
            // 
            // buttonShutter1Close
            // 
            this.buttonShutter1Close.Location = new System.Drawing.Point(12, 50);
            this.buttonShutter1Close.Name = "buttonShutter1Close";
            this.buttonShutter1Close.Size = new System.Drawing.Size(80, 25);
            this.buttonShutter1Close.TabIndex = 64;
            this.buttonShutter1Close.Text = "Close";
            this.buttonShutter1Close.UseVisualStyleBackColor = true;
            this.buttonShutter1Close.Click += new System.EventHandler(this.buttonShutter1Close_Click);
            // 
            // buttonShutter2Open
            // 
            this.buttonShutter2Open.Location = new System.Drawing.Point(100, 20);
            this.buttonShutter2Open.Name = "buttonShutter2Open";
            this.buttonShutter2Open.Size = new System.Drawing.Size(80, 25);
            this.buttonShutter2Open.TabIndex = 64;
            this.buttonShutter2Open.Text = "Open";
            this.buttonShutter2Open.UseVisualStyleBackColor = true;
            this.buttonShutter2Open.Click += new System.EventHandler(this.buttonShutter2Open_Click);
            // 
            // Toolbox
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(334, 292);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.textBoxDomeState);
            this.Controls.Add(this.statusStrip);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.Name = "Toolbox";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Dome Toolbox";
            this.TopMost = true;
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.FocuserToolbox_FormClosing);
            this.Shown += new System.EventHandler(this.FocuserToolbox_Shown);
            this.Resize += new System.EventHandler(this.FocuserToolbox_Resize);
            this.statusStrip.ResumeLayout(false);
            this.statusStrip.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.groupBox2.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        void FocusControl_FormClosing(object sender, System.Windows.Forms.FormClosingEventArgs e)
        {
            e.Cancel = true;
        }

        #endregion

        //private ASCOM.SSFocuser.Focuser MyDome;//graycode
        //private Config Config;
        private System.Windows.Forms.Button buttonStop;
        private System.Windows.Forms.Button buttonSlewCCW;
        private System.Windows.Forms.Button buttonSlewCW;
        private System.Windows.Forms.StatusStrip statusStrip;
        private System.Windows.Forms.NotifyIcon notifyIcon;
        private System.Windows.Forms.ToolStripStatusLabel currentPosition;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.ComboBox comboBoxSlewSpeed;
        private System.Windows.Forms.TextBox textBoxDomeState;
        private System.Windows.Forms.Button buttonGoto;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel1;
        private System.Windows.Forms.Button buttonShutter1Open;
        private System.Windows.Forms.Button buttonPark;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Button buttonShutter1Stop;
        private System.Windows.Forms.Button buttonShutter1Close;
        private System.Windows.Forms.Button buttonShutter2Stop;
        private System.Windows.Forms.Button buttonShutter2Close;
        private System.Windows.Forms.Button buttonShutter2Open;
    }
}