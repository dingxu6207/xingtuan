namespace ASCOM.SSRoof
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
            this.picASCOM = new System.Windows.Forms.PictureBox();
            this.label2 = new System.Windows.Forms.Label();
            this.comboBoxComPort = new System.Windows.Forms.ComboBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.textBoxStopCode = new System.Windows.Forms.TextBox();
            this.textBoxCloseCode = new System.Windows.Forms.TextBox();
            this.textBoxOpenCode = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.textBoxLockCode = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.chkTrace = new System.Windows.Forms.CheckBox();
            this.textBoxRoofOperTime = new System.Windows.Forms.TextBox();
            this.label7 = new System.Windows.Forms.Label();
            this.linkLabel1 = new System.Windows.Forms.LinkLabel();
            this.label8 = new System.Windows.Forms.Label();
            this.textBoxBrakeTime = new System.Windows.Forms.TextBox();
            this.label9 = new System.Windows.Forms.Label();
            this.textBoxUnlockCode = new System.Windows.Forms.TextBox();
            this.label10 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.picASCOM)).BeginInit();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // cmdOK
            // 
            this.cmdOK.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.cmdOK.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.cmdOK.Location = new System.Drawing.Point(326, 194);
            this.cmdOK.Margin = new System.Windows.Forms.Padding(4);
            this.cmdOK.Name = "cmdOK";
            this.cmdOK.Size = new System.Drawing.Size(88, 33);
            this.cmdOK.TabIndex = 0;
            this.cmdOK.Text = "OK";
            this.cmdOK.UseVisualStyleBackColor = true;
            this.cmdOK.Click += new System.EventHandler(this.cmdOK_Click);
            // 
            // cmdCancel
            // 
            this.cmdCancel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.cmdCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.cmdCancel.Location = new System.Drawing.Point(326, 263);
            this.cmdCancel.Margin = new System.Windows.Forms.Padding(4);
            this.cmdCancel.Name = "cmdCancel";
            this.cmdCancel.Size = new System.Drawing.Size(88, 34);
            this.cmdCancel.TabIndex = 1;
            this.cmdCancel.Text = "Cancel";
            this.cmdCancel.UseVisualStyleBackColor = true;
            this.cmdCancel.Click += new System.EventHandler(this.cmdCancel_Click);
            // 
            // picASCOM
            // 
            this.picASCOM.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.picASCOM.Cursor = System.Windows.Forms.Cursors.Hand;
            this.picASCOM.Image = global::ASCOM.SSRoof.Properties.Resources.ASCOM;
            this.picASCOM.Location = new System.Drawing.Point(350, 33);
            this.picASCOM.Margin = new System.Windows.Forms.Padding(4);
            this.picASCOM.Name = "picASCOM";
            this.picASCOM.Size = new System.Drawing.Size(48, 56);
            this.picASCOM.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize;
            this.picASCOM.TabIndex = 3;
            this.picASCOM.TabStop = false;
            this.picASCOM.Click += new System.EventHandler(this.BrowseToAscom);
            this.picASCOM.DoubleClick += new System.EventHandler(this.BrowseToAscom);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(20, 22);
            this.label2.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(89, 18);
            this.label2.TabIndex = 5;
            this.label2.Text = "Comm Port";
            // 
            // comboBoxComPort
            // 
            this.comboBoxComPort.FormattingEnabled = true;
            this.comboBoxComPort.Location = new System.Drawing.Point(160, 20);
            this.comboBoxComPort.Margin = new System.Windows.Forms.Padding(4);
            this.comboBoxComPort.Name = "comboBoxComPort";
            this.comboBoxComPort.Size = new System.Drawing.Size(133, 26);
            this.comboBoxComPort.TabIndex = 7;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.label10);
            this.groupBox1.Controls.Add(this.textBoxUnlockCode);
            this.groupBox1.Controls.Add(this.textBoxStopCode);
            this.groupBox1.Controls.Add(this.textBoxCloseCode);
            this.groupBox1.Controls.Add(this.textBoxOpenCode);
            this.groupBox1.Controls.Add(this.textBoxLockCode);
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Controls.Add(this.label5);
            this.groupBox1.Location = new System.Drawing.Point(23, 138);
            this.groupBox1.Margin = new System.Windows.Forms.Padding(4);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Padding = new System.Windows.Forms.Padding(4);
            this.groupBox1.Size = new System.Drawing.Size(280, 207);
            this.groupBox1.TabIndex = 11;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "SetCode ";
            // 
            // textBoxStopCode
            // 
            this.textBoxStopCode.Location = new System.Drawing.Point(88, 95);
            this.textBoxStopCode.Margin = new System.Windows.Forms.Padding(4);
            this.textBoxStopCode.Name = "textBoxStopCode";
            this.textBoxStopCode.Size = new System.Drawing.Size(170, 28);
            this.textBoxStopCode.TabIndex = 14;
            this.textBoxStopCode.Text = "FD 7D 9E 92 6B DF";
            // 
            // textBoxCloseCode
            // 
            this.textBoxCloseCode.Location = new System.Drawing.Point(88, 60);
            this.textBoxCloseCode.Margin = new System.Windows.Forms.Padding(4);
            this.textBoxCloseCode.Name = "textBoxCloseCode";
            this.textBoxCloseCode.Size = new System.Drawing.Size(170, 28);
            this.textBoxCloseCode.TabIndex = 13;
            this.textBoxCloseCode.Text = "FD 7D 9E 94 6B DF";
            // 
            // textBoxOpenCode
            // 
            this.textBoxOpenCode.Location = new System.Drawing.Point(88, 25);
            this.textBoxOpenCode.Margin = new System.Windows.Forms.Padding(4);
            this.textBoxOpenCode.Name = "textBoxOpenCode";
            this.textBoxOpenCode.Size = new System.Drawing.Size(170, 28);
            this.textBoxOpenCode.TabIndex = 12;
            this.textBoxOpenCode.Text = "FD 7D 9E 98 6B DF";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(22, 100);
            this.label4.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(44, 18);
            this.label4.TabIndex = 10;
            this.label4.Text = "Stop";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(22, 65);
            this.label3.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(53, 18);
            this.label3.TabIndex = 9;
            this.label3.Text = "Close";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(22, 30);
            this.label1.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(44, 18);
            this.label1.TabIndex = 8;
            this.label1.Text = "Open";
            // 
            // textBoxLockCode
            // 
            this.textBoxLockCode.Location = new System.Drawing.Point(88, 130);
            this.textBoxLockCode.Margin = new System.Windows.Forms.Padding(4);
            this.textBoxLockCode.Name = "textBoxLockCode";
            this.textBoxLockCode.Size = new System.Drawing.Size(170, 28);
            this.textBoxLockCode.TabIndex = 15;
            this.textBoxLockCode.Text = "FD 7D 9E 91 6B DF";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(22, 135);
            this.label5.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(44, 18);
            this.label5.TabIndex = 11;
            this.label5.Text = "Lock";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(20, 64);
            this.label6.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(116, 18);
            this.label6.TabIndex = 17;
            this.label6.Text = "RoofOperTime";
            // 
            // chkTrace
            // 
            this.chkTrace.AutoSize = true;
            this.chkTrace.Location = new System.Drawing.Point(111, 441);
            this.chkTrace.Margin = new System.Windows.Forms.Padding(4);
            this.chkTrace.Name = "chkTrace";
            this.chkTrace.Size = new System.Drawing.Size(106, 22);
            this.chkTrace.TabIndex = 10;
            this.chkTrace.Text = "Trace on";
            this.chkTrace.UseVisualStyleBackColor = true;
            // 
            // textBoxRoofOperTime
            // 
            this.textBoxRoofOperTime.Location = new System.Drawing.Point(160, 61);
            this.textBoxRoofOperTime.Name = "textBoxRoofOperTime";
            this.textBoxRoofOperTime.Size = new System.Drawing.Size(100, 28);
            this.textBoxRoofOperTime.TabIndex = 18;
            this.textBoxRoofOperTime.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBoxRoofOperTime_KeyPress);
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(272, 64);
            this.label7.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(17, 18);
            this.label7.TabIndex = 19;
            this.label7.Text = "S";
            // 
            // linkLabel1
            // 
            this.linkLabel1.AutoSize = true;
            this.linkLabel1.Location = new System.Drawing.Point(20, 361);
            this.linkLabel1.Name = "linkLabel1";
            this.linkLabel1.Size = new System.Drawing.Size(323, 18);
            this.linkLabel1.TabIndex = 20;
            this.linkLabel1.TabStop = true;
            this.linkLabel1.Text = "Technical support: graycode@qq.com ";
            this.linkLabel1.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.linkLabel1_LinkClicked);
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(20, 104);
            this.label8.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(98, 18);
            this.label8.TabIndex = 21;
            this.label8.Text = "Brake Time";
            // 
            // textBoxBrakeTime
            // 
            this.textBoxBrakeTime.Location = new System.Drawing.Point(160, 101);
            this.textBoxBrakeTime.Name = "textBoxBrakeTime";
            this.textBoxBrakeTime.Size = new System.Drawing.Size(100, 28);
            this.textBoxBrakeTime.TabIndex = 22;
            this.textBoxBrakeTime.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBoxBrakeTime_KeyPress);
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(272, 104);
            this.label9.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(17, 18);
            this.label9.TabIndex = 23;
            this.label9.Text = "S";
            // 
            // textBoxUnlockCode
            // 
            this.textBoxUnlockCode.Location = new System.Drawing.Point(88, 165);
            this.textBoxUnlockCode.Margin = new System.Windows.Forms.Padding(4);
            this.textBoxUnlockCode.Name = "textBoxUnlockCode";
            this.textBoxUnlockCode.Size = new System.Drawing.Size(170, 28);
            this.textBoxUnlockCode.TabIndex = 16;
            this.textBoxUnlockCode.Text = "FD 7D 9E 91 6B DF";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(22, 170);
            this.label10.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(62, 18);
            this.label10.TabIndex = 17;
            this.label10.Text = "Unlock";
            // 
            // SetupDialogForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 18F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(440, 396);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.textBoxBrakeTime);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.linkLabel1);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.textBoxRoofOperTime);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.chkTrace);
            this.Controls.Add(this.comboBoxComPort);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.picASCOM);
            this.Controls.Add(this.cmdCancel);
            this.Controls.Add(this.cmdOK);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Margin = new System.Windows.Forms.Padding(4);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "SetupDialogForm";
            this.SizeGripStyle = System.Windows.Forms.SizeGripStyle.Hide;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Roof Setup";
            ((System.ComponentModel.ISupportInitialize)(this.picASCOM)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button cmdOK;
        private System.Windows.Forms.Button cmdCancel;
        private System.Windows.Forms.PictureBox picASCOM;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ComboBox comboBoxComPort;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.TextBox textBoxLockCode;
        private System.Windows.Forms.TextBox textBoxStopCode;
        private System.Windows.Forms.TextBox textBoxCloseCode;
        private System.Windows.Forms.TextBox textBoxOpenCode;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.CheckBox chkTrace;
        private System.Windows.Forms.TextBox textBoxRoofOperTime;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.LinkLabel linkLabel1;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.TextBox textBoxBrakeTime;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.TextBox textBoxUnlockCode;
    }
}