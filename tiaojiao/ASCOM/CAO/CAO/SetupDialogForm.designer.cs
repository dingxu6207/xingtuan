namespace CAO
{
    partial class SetupDialogForm
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
            this.cmdOK = new System.Windows.Forms.Button();
            this.cmdCancel = new System.Windows.Forms.Button();
            this.chkTrace = new System.Windows.Forms.CheckBox();
            this.label1 = new System.Windows.Forms.Label();
            this.linkLabel = new System.Windows.Forms.LinkLabel();
            this.comboBoxPort = new System.Windows.Forms.ComboBox();
            this.comboBoxComPort = new System.Windows.Forms.ComboBox();
            this.comboBoxLocalIP = new System.Windows.Forms.ComboBox();
            this.textBoxRemotePort = new System.Windows.Forms.TextBox();
            this.textBoxRemoteIP = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.textBoxLocalPort = new System.Windows.Forms.TextBox();
            this.comboBoxBaudRate = new System.Windows.Forms.ComboBox();
            this.label2 = new System.Windows.Forms.Label();
            this.tabControlProtocol = new System.Windows.Forms.TabControl();
            this.tabPageASCOM = new System.Windows.Forms.TabPage();
            this.textBoxASCOMDriverID = new System.Windows.Forms.TextBox();
            this.buttonASCOMChooser = new System.Windows.Forms.Button();
            this.tabPageSerial = new System.Windows.Forms.TabPage();
            this.tabPageSocket = new System.Windows.Forms.TabPage();
            this.label4 = new System.Windows.Forms.Label();
            this.tabControlProtocol.SuspendLayout();
            this.tabPageASCOM.SuspendLayout();
            this.tabPageSerial.SuspendLayout();
            this.tabPageSocket.SuspendLayout();
            this.SuspendLayout();
            // 
            // cmdOK
            // 
            this.cmdOK.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.cmdOK.Location = new System.Drawing.Point(105, 106);
            this.cmdOK.Name = "cmdOK";
            this.cmdOK.Size = new System.Drawing.Size(59, 22);
            this.cmdOK.TabIndex = 0;
            this.cmdOK.Text = "OK";
            this.cmdOK.UseVisualStyleBackColor = true;
            this.cmdOK.Click += new System.EventHandler(this.cmdOK_Click);
            // 
            // cmdCancel
            // 
            this.cmdCancel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.cmdCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.cmdCancel.Location = new System.Drawing.Point(216, 106);
            this.cmdCancel.Name = "cmdCancel";
            this.cmdCancel.Size = new System.Drawing.Size(59, 23);
            this.cmdCancel.TabIndex = 1;
            this.cmdCancel.Text = "Cancel";
            this.cmdCancel.UseVisualStyleBackColor = true;
            this.cmdCancel.Click += new System.EventHandler(this.cmdCancel_Click);
            // 
            // chkTrace
            // 
            this.chkTrace.AutoSize = true;
            this.chkTrace.Location = new System.Drawing.Point(11, 360);
            this.chkTrace.Name = "chkTrace";
            this.chkTrace.Size = new System.Drawing.Size(72, 16);
            this.chkTrace.TabIndex = 6;
            this.chkTrace.Text = "Trace on";
            this.chkTrace.UseVisualStyleBackColor = true;
            this.chkTrace.Visible = false;
            // 
            // label1
            // 
            this.label1.Location = new System.Drawing.Point(10, 10);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(59, 15);
            this.label1.TabIndex = 51;
            this.label1.Text = "ComPort";
            // 
            // linkLabel
            // 
            this.linkLabel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.linkLabel.AutoSize = true;
            this.linkLabel.Location = new System.Drawing.Point(292, 111);
            this.linkLabel.Name = "linkLabel";
            this.linkLabel.Size = new System.Drawing.Size(83, 12);
            this.linkLabel.TabIndex = 53;
            this.linkLabel.TabStop = true;
            this.linkLabel.Text = " www.fhxy.com";
            this.linkLabel.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.linkLabel_LinkClicked);
            // 
            // comboBoxPort
            // 
            this.comboBoxPort.FormattingEnabled = true;
            this.comboBoxPort.Location = new System.Drawing.Point(70, 7);
            this.comboBoxPort.Name = "comboBoxPort";
            this.comboBoxPort.Size = new System.Drawing.Size(112, 20);
            this.comboBoxPort.TabIndex = 49;
            // 
            // comboBoxComPort
            // 
            this.comboBoxComPort.FormattingEnabled = true;
            this.comboBoxComPort.Location = new System.Drawing.Point(-1, 334);
            this.comboBoxComPort.Name = "comboBoxComPort";
            this.comboBoxComPort.Size = new System.Drawing.Size(90, 20);
            this.comboBoxComPort.TabIndex = 7;
            this.comboBoxComPort.Visible = false;
            // 
            // comboBoxLocalIP
            // 
            this.comboBoxLocalIP.FormattingEnabled = true;
            this.comboBoxLocalIP.Location = new System.Drawing.Point(75, 32);
            this.comboBoxLocalIP.Margin = new System.Windows.Forms.Padding(2);
            this.comboBoxLocalIP.Name = "comboBoxLocalIP";
            this.comboBoxLocalIP.Size = new System.Drawing.Size(116, 20);
            this.comboBoxLocalIP.TabIndex = 31;
            // 
            // textBoxRemotePort
            // 
            this.textBoxRemotePort.Location = new System.Drawing.Point(267, 7);
            this.textBoxRemotePort.Name = "textBoxRemotePort";
            this.textBoxRemotePort.Size = new System.Drawing.Size(70, 21);
            this.textBoxRemotePort.TabIndex = 30;
            this.textBoxRemotePort.Text = "8086";
            // 
            // textBoxRemoteIP
            // 
            this.textBoxRemoteIP.Location = new System.Drawing.Point(75, 7);
            this.textBoxRemoteIP.Name = "textBoxRemoteIP";
            this.textBoxRemoteIP.Size = new System.Drawing.Size(115, 21);
            this.textBoxRemoteIP.TabIndex = 29;
            // 
            // label3
            // 
            this.label3.Location = new System.Drawing.Point(10, 35);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(59, 15);
            this.label3.TabIndex = 27;
            this.label3.Text = "Local IP";
            // 
            // label7
            // 
            this.label7.Location = new System.Drawing.Point(200, 10);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(70, 15);
            this.label7.TabIndex = 26;
            this.label7.Text = "DevicePort";
            // 
            // label10
            // 
            this.label10.Location = new System.Drawing.Point(10, 10);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(70, 15);
            this.label10.TabIndex = 15;
            this.label10.Text = "Device IP";
            // 
            // textBoxLocalPort
            // 
            this.textBoxLocalPort.Location = new System.Drawing.Point(267, 32);
            this.textBoxLocalPort.Name = "textBoxLocalPort";
            this.textBoxLocalPort.Size = new System.Drawing.Size(70, 21);
            this.textBoxLocalPort.TabIndex = 24;
            this.textBoxLocalPort.Text = "8088";
            this.textBoxLocalPort.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBoxStepSize_KeyPress);
            // 
            // comboBoxBaudRate
            // 
            this.comboBoxBaudRate.AutoCompleteCustomSource.AddRange(new string[] {
            "4800",
            "9600",
            "19200",
            "38400",
            "57600",
            "74880",
            "115200",
            "230400",
            "460800",
            "576000",
            ""});
            this.comboBoxBaudRate.FormattingEnabled = true;
            this.comboBoxBaudRate.Location = new System.Drawing.Point(70, 32);
            this.comboBoxBaudRate.Name = "comboBoxBaudRate";
            this.comboBoxBaudRate.Size = new System.Drawing.Size(112, 20);
            this.comboBoxBaudRate.TabIndex = 53;
            // 
            // label2
            // 
            this.label2.Location = new System.Drawing.Point(10, 35);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(70, 15);
            this.label2.TabIndex = 52;
            this.label2.Text = "BaudRate";
            // 
            // tabControlProtocol
            // 
            this.tabControlProtocol.Controls.Add(this.tabPageASCOM);
            this.tabControlProtocol.Controls.Add(this.tabPageSerial);
            this.tabControlProtocol.Controls.Add(this.tabPageSocket);
            this.tabControlProtocol.Location = new System.Drawing.Point(12, 12);
            this.tabControlProtocol.Name = "tabControlProtocol";
            this.tabControlProtocol.SelectedIndex = 0;
            this.tabControlProtocol.Size = new System.Drawing.Size(366, 86);
            this.tabControlProtocol.TabIndex = 57;
            // 
            // tabPageASCOM
            // 
            this.tabPageASCOM.Controls.Add(this.textBoxASCOMDriverID);
            this.tabPageASCOM.Controls.Add(this.buttonASCOMChooser);
            this.tabPageASCOM.Location = new System.Drawing.Point(4, 22);
            this.tabPageASCOM.Name = "tabPageASCOM";
            this.tabPageASCOM.Padding = new System.Windows.Forms.Padding(3);
            this.tabPageASCOM.Size = new System.Drawing.Size(358, 60);
            this.tabPageASCOM.TabIndex = 0;
            this.tabPageASCOM.Text = "ASCOM";
            this.tabPageASCOM.UseVisualStyleBackColor = true;
            // 
            // textBoxASCOMDriverID
            // 
            this.textBoxASCOMDriverID.Location = new System.Drawing.Point(89, 21);
            this.textBoxASCOMDriverID.Margin = new System.Windows.Forms.Padding(2);
            this.textBoxASCOMDriverID.Name = "textBoxASCOMDriverID";
            this.textBoxASCOMDriverID.ReadOnly = true;
            this.textBoxASCOMDriverID.Size = new System.Drawing.Size(264, 21);
            this.textBoxASCOMDriverID.TabIndex = 1;
            // 
            // buttonASCOMChooser
            // 
            this.buttonASCOMChooser.Location = new System.Drawing.Point(10, 20);
            this.buttonASCOMChooser.Margin = new System.Windows.Forms.Padding(2);
            this.buttonASCOMChooser.Name = "buttonASCOMChooser";
            this.buttonASCOMChooser.Size = new System.Drawing.Size(70, 22);
            this.buttonASCOMChooser.TabIndex = 0;
            this.buttonASCOMChooser.Text = "Choose";
            this.buttonASCOMChooser.UseVisualStyleBackColor = true;
            this.buttonASCOMChooser.Click += new System.EventHandler(this.buttonASCOMChooser_Click);
            // 
            // tabPageSerial
            // 
            this.tabPageSerial.Controls.Add(this.comboBoxBaudRate);
            this.tabPageSerial.Controls.Add(this.label1);
            this.tabPageSerial.Controls.Add(this.label2);
            this.tabPageSerial.Controls.Add(this.comboBoxPort);
            this.tabPageSerial.Location = new System.Drawing.Point(4, 22);
            this.tabPageSerial.Name = "tabPageSerial";
            this.tabPageSerial.Padding = new System.Windows.Forms.Padding(3);
            this.tabPageSerial.Size = new System.Drawing.Size(358, 60);
            this.tabPageSerial.TabIndex = 1;
            this.tabPageSerial.Text = "Serial";
            this.tabPageSerial.UseVisualStyleBackColor = true;
            // 
            // tabPageSocket
            // 
            this.tabPageSocket.Controls.Add(this.textBoxRemotePort);
            this.tabPageSocket.Controls.Add(this.textBoxLocalPort);
            this.tabPageSocket.Controls.Add(this.label4);
            this.tabPageSocket.Controls.Add(this.comboBoxLocalIP);
            this.tabPageSocket.Controls.Add(this.label3);
            this.tabPageSocket.Controls.Add(this.textBoxRemoteIP);
            this.tabPageSocket.Controls.Add(this.label7);
            this.tabPageSocket.Controls.Add(this.label10);
            this.tabPageSocket.Location = new System.Drawing.Point(4, 22);
            this.tabPageSocket.Name = "tabPageSocket";
            this.tabPageSocket.Size = new System.Drawing.Size(358, 60);
            this.tabPageSocket.TabIndex = 2;
            this.tabPageSocket.Text = "Socket";
            this.tabPageSocket.UseVisualStyleBackColor = true;
            // 
            // label4
            // 
            this.label4.Location = new System.Drawing.Point(200, 35);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(70, 15);
            this.label4.TabIndex = 28;
            this.label4.Text = "LocalPort";
            // 
            // SetupDialogForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(387, 136);
            this.Controls.Add(this.tabControlProtocol);
            this.Controls.Add(this.linkLabel);
            this.Controls.Add(this.comboBoxComPort);
            this.Controls.Add(this.chkTrace);
            this.Controls.Add(this.cmdCancel);
            this.Controls.Add(this.cmdOK);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "SetupDialogForm";
            this.SizeGripStyle = System.Windows.Forms.SizeGripStyle.Hide;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Setup Dialog";
            this.tabControlProtocol.ResumeLayout(false);
            this.tabPageASCOM.ResumeLayout(false);
            this.tabPageASCOM.PerformLayout();
            this.tabPageSerial.ResumeLayout(false);
            this.tabPageSocket.ResumeLayout(false);
            this.tabPageSocket.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button cmdOK;
        private System.Windows.Forms.Button cmdCancel;
        private System.Windows.Forms.CheckBox chkTrace;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.LinkLabel linkLabel;
        private System.Windows.Forms.ComboBox comboBoxPort;
        private System.Windows.Forms.ComboBox comboBoxComPort;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.TextBox textBoxLocalPort;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TabControl tabControlProtocol;
        private System.Windows.Forms.TabPage tabPageASCOM;
        private System.Windows.Forms.TabPage tabPageSerial;
        private System.Windows.Forms.TabPage tabPageSocket;
        private System.Windows.Forms.TextBox textBoxRemotePort;
        private System.Windows.Forms.TextBox textBoxRemoteIP;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.ComboBox comboBoxBaudRate;
        private System.Windows.Forms.ComboBox comboBoxLocalIP;
        private System.Windows.Forms.TextBox textBoxASCOMDriverID;
        private System.Windows.Forms.Button buttonASCOMChooser;
        private System.Windows.Forms.Label label4;
    }
}