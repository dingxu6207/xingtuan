namespace ASCOM.SSFC
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
            this.label6 = new System.Windows.Forms.Label();
            this.textBoxLock = new System.Windows.Forms.TextBox();
            this.textBoxStop = new System.Windows.Forms.TextBox();
            this.textBoxShut = new System.Windows.Forms.TextBox();
            this.textBoxOpen = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.chkTrace = new System.Windows.Forms.CheckBox();
            this.comboBoxTime = new System.Windows.Forms.ComboBox();
            ((System.ComponentModel.ISupportInitialize)(this.picASCOM)).BeginInit();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // cmdOK
            // 
            this.cmdOK.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.cmdOK.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.cmdOK.Location = new System.Drawing.Point(215, 124);
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
            this.cmdCancel.Location = new System.Drawing.Point(215, 152);
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
            this.picASCOM.Image = global::ASCOM.SSFC.Properties.Resources.ASCOM;
            this.picASCOM.Location = new System.Drawing.Point(226, 8);
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
            this.label2.Location = new System.Drawing.Point(21, 9);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(59, 12);
            this.label2.TabIndex = 5;
            this.label2.Text = "Comm Port";
            // 
            // comboBoxComPort
            // 
            this.comboBoxComPort.FormattingEnabled = true;
            this.comboBoxComPort.Location = new System.Drawing.Point(85, 6);
            this.comboBoxComPort.Name = "comboBoxComPort";
            this.comboBoxComPort.Size = new System.Drawing.Size(90, 20);
            this.comboBoxComPort.TabIndex = 7;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.comboBoxTime);
            this.groupBox1.Controls.Add(this.label6);
            this.groupBox1.Controls.Add(this.textBoxLock);
            this.groupBox1.Controls.Add(this.textBoxStop);
            this.groupBox1.Controls.Add(this.textBoxShut);
            this.groupBox1.Controls.Add(this.textBoxOpen);
            this.groupBox1.Controls.Add(this.label5);
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Location = new System.Drawing.Point(14, 32);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(187, 142);
            this.groupBox1.TabIndex = 11;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "SetCode ";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(15, 120);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(29, 12);
            this.label6.TabIndex = 17;
            this.label6.Text = "Time";
            // 
            // textBoxLock
            // 
            this.textBoxLock.Location = new System.Drawing.Point(59, 91);
            this.textBoxLock.Name = "textBoxLock";
            this.textBoxLock.Size = new System.Drawing.Size(115, 21);
            this.textBoxLock.TabIndex = 15;
            this.textBoxLock.Text = "FD 7D 9E 91 6B DF";
            // 
            // textBoxStop
            // 
            this.textBoxStop.Location = new System.Drawing.Point(59, 66);
            this.textBoxStop.Name = "textBoxStop";
            this.textBoxStop.Size = new System.Drawing.Size(115, 21);
            this.textBoxStop.TabIndex = 14;
            this.textBoxStop.Text = "FD 7D 9E 92 6B DF";
            // 
            // textBoxShut
            // 
            this.textBoxShut.Location = new System.Drawing.Point(59, 41);
            this.textBoxShut.Name = "textBoxShut";
            this.textBoxShut.Size = new System.Drawing.Size(115, 21);
            this.textBoxShut.TabIndex = 13;
            this.textBoxShut.Text = "FD 7D 9E 94 6B DF";
            // 
            // textBoxOpen
            // 
            this.textBoxOpen.Location = new System.Drawing.Point(59, 17);
            this.textBoxOpen.Name = "textBoxOpen";
            this.textBoxOpen.Size = new System.Drawing.Size(115, 21);
            this.textBoxOpen.TabIndex = 12;
            this.textBoxOpen.Text = "FD 7D 9E 98 6B DF";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(15, 95);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(29, 12);
            this.label5.TabIndex = 11;
            this.label5.Text = "Lock";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(15, 70);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(29, 12);
            this.label4.TabIndex = 10;
            this.label4.Text = "Stop";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(15, 45);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(29, 12);
            this.label3.TabIndex = 9;
            this.label3.Text = "Shut";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(15, 20);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(29, 12);
            this.label1.TabIndex = 8;
            this.label1.Text = "Open";
            // 
            // chkTrace
            // 
            this.chkTrace.AutoSize = true;
            this.chkTrace.Location = new System.Drawing.Point(125, 214);
            this.chkTrace.Name = "chkTrace";
            this.chkTrace.Size = new System.Drawing.Size(72, 16);
            this.chkTrace.TabIndex = 10;
            this.chkTrace.Text = "Trace on";
            this.chkTrace.UseVisualStyleBackColor = true;
            // 
            // comboBoxTime
            // 
            this.comboBoxTime.AutoCompleteCustomSource.AddRange(new string[] {
            "01",
            "02",
            "03",
            "04",
            "05",
            "06",
            "07",
            "08",
            "09",
            "0A"});
            this.comboBoxTime.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxTime.FormattingEnabled = true;
            this.comboBoxTime.Items.AddRange(new object[] {
            "01",
            "02",
            "03",
            "04",
            "05",
            "06",
            "07",
            "08",
            "09",
            "0A",
            "0F",
            "FF"});
            this.comboBoxTime.Location = new System.Drawing.Point(59, 116);
            this.comboBoxTime.Name = "comboBoxTime";
            this.comboBoxTime.Size = new System.Drawing.Size(90, 20);
            this.comboBoxTime.TabIndex = 12;
            // 
            // SetupDialogForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(284, 183);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.chkTrace);
            this.Controls.Add(this.comboBoxComPort);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.picASCOM);
            this.Controls.Add(this.cmdCancel);
            this.Controls.Add(this.cmdOK);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "SetupDialogForm";
            this.SizeGripStyle = System.Windows.Forms.SizeGripStyle.Hide;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "SSFC Setup";
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
        private System.Windows.Forms.TextBox textBoxLock;
        private System.Windows.Forms.TextBox textBoxStop;
        private System.Windows.Forms.TextBox textBoxShut;
        private System.Windows.Forms.TextBox textBoxOpen;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.CheckBox chkTrace;
        private System.Windows.Forms.ComboBox comboBoxTime;
    }
}