namespace ASCOM.SSFocuser
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
            this.chkTrace = new System.Windows.Forms.CheckBox();
            this.label1 = new System.Windows.Forms.Label();
            this.linkLabel = new System.Windows.Forms.LinkLabel();
            this.comboBoxPortIP = new System.Windows.Forms.ComboBox();
            this.checkboxUseToolbox = new System.Windows.Forms.CheckBox();
            this.comboBoxComPort = new System.Windows.Forms.ComboBox();
            this.groupBox_focuser = new System.Windows.Forms.GroupBox();
            this.label7 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.textBoxMaxStep = new System.Windows.Forms.TextBox();
            this.textBoxStepSize = new System.Windows.Forms.TextBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.groupBox_temperture = new System.Windows.Forms.GroupBox();
            this.label9 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.textBoxThreshold = new System.Windows.Forms.TextBox();
            this.textBoxStepPerDeg = new System.Windows.Forms.TextBox();
            ((System.ComponentModel.ISupportInitialize)(this.picASCOM)).BeginInit();
            this.groupBox_focuser.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.groupBox_temperture.SuspendLayout();
            this.SuspendLayout();
            // 
            // cmdOK
            // 
            this.cmdOK.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.cmdOK.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.cmdOK.Location = new System.Drawing.Point(203, 149);
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
            this.cmdCancel.Location = new System.Drawing.Point(203, 176);
            this.cmdCancel.Name = "cmdCancel";
            this.cmdCancel.Size = new System.Drawing.Size(59, 23);
            this.cmdCancel.TabIndex = 1;
            this.cmdCancel.Text = "Cancel";
            this.cmdCancel.UseVisualStyleBackColor = true;
            this.cmdCancel.Click += new System.EventHandler(this.cmdCancel_Click);
            // 
            // picASCOM
            // 
            this.picASCOM.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.picASCOM.Cursor = System.Windows.Forms.Cursors.Hand;
            this.picASCOM.Image = global::ASCOM.SSFocuser.Properties.Resources.ASCOM;
            this.picASCOM.Location = new System.Drawing.Point(208, 69);
            this.picASCOM.Name = "picASCOM";
            this.picASCOM.Size = new System.Drawing.Size(48, 56);
            this.picASCOM.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize;
            this.picASCOM.TabIndex = 3;
            this.picASCOM.TabStop = false;
            this.picASCOM.Click += new System.EventHandler(this.BrowseToAscom);
            this.picASCOM.DoubleClick += new System.EventHandler(this.BrowseToAscom);
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
            this.label1.Location = new System.Drawing.Point(10, 23);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(70, 15);
            this.label1.TabIndex = 51;
            this.label1.Text = "Com Port";
            // 
            // linkLabel
            // 
            this.linkLabel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.linkLabel.AutoSize = true;
            this.linkLabel.Location = new System.Drawing.Point(149, 217);
            this.linkLabel.Name = "linkLabel";
            this.linkLabel.Size = new System.Drawing.Size(113, 12);
            this.linkLabel.TabIndex = 53;
            this.linkLabel.TabStop = true;
            this.linkLabel.Text = " www.sky-rover.com";
            this.linkLabel.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.linkLabel_LinkClicked);
            // 
            // comboBoxPortIP
            // 
            this.comboBoxPortIP.FormattingEnabled = true;
            this.comboBoxPortIP.Location = new System.Drawing.Point(94, 20);
            this.comboBoxPortIP.Name = "comboBoxPortIP";
            this.comboBoxPortIP.Size = new System.Drawing.Size(140, 20);
            this.comboBoxPortIP.TabIndex = 49;
            // 
            // checkboxUseToolbox
            // 
            this.checkboxUseToolbox.AutoSize = true;
            this.checkboxUseToolbox.Location = new System.Drawing.Point(12, 216);
            this.checkboxUseToolbox.Name = "checkboxUseToolbox";
            this.checkboxUseToolbox.Size = new System.Drawing.Size(90, 16);
            this.checkboxUseToolbox.TabIndex = 52;
            this.checkboxUseToolbox.Text = "Use Toolbox";
            this.checkboxUseToolbox.UseVisualStyleBackColor = true;
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
            // groupBox_focuser
            // 
            this.groupBox_focuser.Controls.Add(this.label7);
            this.groupBox_focuser.Controls.Add(this.label10);
            this.groupBox_focuser.Controls.Add(this.textBoxMaxStep);
            this.groupBox_focuser.Controls.Add(this.textBoxStepSize);
            this.groupBox_focuser.Location = new System.Drawing.Point(12, 56);
            this.groupBox_focuser.Name = "groupBox_focuser";
            this.groupBox_focuser.Size = new System.Drawing.Size(180, 76);
            this.groupBox_focuser.TabIndex = 54;
            this.groupBox_focuser.TabStop = false;
            this.groupBox_focuser.Text = "Focuser ";
            // 
            // label7
            // 
            this.label7.Location = new System.Drawing.Point(10, 48);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(70, 15);
            this.label7.TabIndex = 26;
            this.label7.Text = "Step Size";
            // 
            // label10
            // 
            this.label10.Location = new System.Drawing.Point(10, 23);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(70, 15);
            this.label10.TabIndex = 15;
            this.label10.Text = "Max Step";
            // 
            // textBoxMaxStep
            // 
            this.textBoxMaxStep.Location = new System.Drawing.Point(94, 20);
            this.textBoxMaxStep.Name = "textBoxMaxStep";
            this.textBoxMaxStep.Size = new System.Drawing.Size(70, 21);
            this.textBoxMaxStep.TabIndex = 23;
            this.textBoxMaxStep.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBoxMaxStep_KeyPress);
            // 
            // textBoxStepSize
            // 
            this.textBoxStepSize.Location = new System.Drawing.Point(94, 45);
            this.textBoxStepSize.Name = "textBoxStepSize";
            this.textBoxStepSize.Size = new System.Drawing.Size(70, 21);
            this.textBoxStepSize.TabIndex = 24;
            this.textBoxStepSize.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBoxStepSize_KeyPress);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.comboBoxPortIP);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Location = new System.Drawing.Point(12, 5);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(250, 50);
            this.groupBox1.TabIndex = 55;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Connection";
            // 
            // groupBox_temperture
            // 
            this.groupBox_temperture.Controls.Add(this.label9);
            this.groupBox_temperture.Controls.Add(this.label8);
            this.groupBox_temperture.Controls.Add(this.textBoxThreshold);
            this.groupBox_temperture.Controls.Add(this.textBoxStepPerDeg);
            this.groupBox_temperture.Location = new System.Drawing.Point(12, 133);
            this.groupBox_temperture.Name = "groupBox_temperture";
            this.groupBox_temperture.Size = new System.Drawing.Size(180, 76);
            this.groupBox_temperture.TabIndex = 56;
            this.groupBox_temperture.TabStop = false;
            this.groupBox_temperture.Text = "TempComp";
            // 
            // label9
            // 
            this.label9.Location = new System.Drawing.Point(10, 48);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(70, 15);
            this.label9.TabIndex = 29;
            this.label9.Text = "Threshold";
            // 
            // label8
            // 
            this.label8.Location = new System.Drawing.Point(10, 23);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(70, 15);
            this.label8.TabIndex = 28;
            this.label8.Text = "Steps / ¡æ";
            // 
            // textBoxThreshold
            // 
            this.textBoxThreshold.Location = new System.Drawing.Point(95, 45);
            this.textBoxThreshold.Name = "textBoxThreshold";
            this.textBoxThreshold.Size = new System.Drawing.Size(70, 21);
            this.textBoxThreshold.TabIndex = 22;
            this.textBoxThreshold.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBoxThreshold_KeyPress);
            // 
            // textBoxStepPerDeg
            // 
            this.textBoxStepPerDeg.Location = new System.Drawing.Point(95, 20);
            this.textBoxStepPerDeg.Name = "textBoxStepPerDeg";
            this.textBoxStepPerDeg.Size = new System.Drawing.Size(70, 21);
            this.textBoxStepPerDeg.TabIndex = 20;
            this.textBoxStepPerDeg.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBoxStepPerDeg_KeyPress);
            // 
            // SetupDialogForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(274, 238);
            this.Controls.Add(this.groupBox_temperture);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.groupBox_focuser);
            this.Controls.Add(this.linkLabel);
            this.Controls.Add(this.checkboxUseToolbox);
            this.Controls.Add(this.comboBoxComPort);
            this.Controls.Add(this.chkTrace);
            this.Controls.Add(this.picASCOM);
            this.Controls.Add(this.cmdCancel);
            this.Controls.Add(this.cmdOK);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "SetupDialogForm";
            this.SizeGripStyle = System.Windows.Forms.SizeGripStyle.Hide;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Focuser Setup";
            ((System.ComponentModel.ISupportInitialize)(this.picASCOM)).EndInit();
            this.groupBox_focuser.ResumeLayout(false);
            this.groupBox_focuser.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.groupBox_temperture.ResumeLayout(false);
            this.groupBox_temperture.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button cmdOK;
        private System.Windows.Forms.Button cmdCancel;
        private System.Windows.Forms.PictureBox picASCOM;
        private System.Windows.Forms.CheckBox chkTrace;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.LinkLabel linkLabel;
        private System.Windows.Forms.ComboBox comboBoxPortIP;
        private System.Windows.Forms.CheckBox checkboxUseToolbox;
        private System.Windows.Forms.ComboBox comboBoxComPort;
        private System.Windows.Forms.GroupBox groupBox_focuser;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.TextBox textBoxMaxStep;
        private System.Windows.Forms.TextBox textBoxStepSize;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.GroupBox groupBox_temperture;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.TextBox textBoxThreshold;
        private System.Windows.Forms.TextBox textBoxStepPerDeg;
    }
}