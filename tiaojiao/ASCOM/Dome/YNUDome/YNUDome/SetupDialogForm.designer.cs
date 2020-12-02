namespace ASCOM.YNUDome
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
            this.chkTrace = new System.Windows.Forms.CheckBox();
            this.comboBoxComPort = new System.Windows.Forms.ComboBox();
            this.checkBoxUseToolbox = new System.Windows.Forms.CheckBox();
            this.label1 = new System.Windows.Forms.Label();
            this.checkBoxEnableShutter2 = new System.Windows.Forms.CheckBox();
            this.textBoxAzimuthOffset = new System.Windows.Forms.TextBox();
            ((System.ComponentModel.ISupportInitialize)(this.picASCOM)).BeginInit();
            this.SuspendLayout();
            // 
            // cmdOK
            // 
            this.cmdOK.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.cmdOK.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.cmdOK.Location = new System.Drawing.Point(44, 92);
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
            this.cmdCancel.Location = new System.Drawing.Point(138, 92);
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
            this.picASCOM.Image = global::ASCOM.YNUDome.Properties.Resources.ASCOM;
            this.picASCOM.Location = new System.Drawing.Point(185, 8);
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
            this.label2.Location = new System.Drawing.Point(12, 22);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(59, 12);
            this.label2.TabIndex = 5;
            this.label2.Text = "Comm Port";
            // 
            // chkTrace
            // 
            this.chkTrace.AutoSize = true;
            this.chkTrace.Location = new System.Drawing.Point(77, 340);
            this.chkTrace.Name = "chkTrace";
            this.chkTrace.Size = new System.Drawing.Size(72, 16);
            this.chkTrace.TabIndex = 6;
            this.chkTrace.Text = "Trace on";
            this.chkTrace.UseVisualStyleBackColor = true;
            // 
            // comboBoxComPort
            // 
            this.comboBoxComPort.FormattingEnabled = true;
            this.comboBoxComPort.Location = new System.Drawing.Point(80, 20);
            this.comboBoxComPort.Name = "comboBoxComPort";
            this.comboBoxComPort.Size = new System.Drawing.Size(90, 20);
            this.comboBoxComPort.TabIndex = 7;
            this.comboBoxComPort.SelectedValueChanged += new System.EventHandler(this.comboBoxComPort_SelectedValueChanged);
            // 
            // checkBoxUseToolbox
            // 
            this.checkBoxUseToolbox.AutoSize = true;
            this.checkBoxUseToolbox.Location = new System.Drawing.Point(12, 60);
            this.checkBoxUseToolbox.Name = "checkBoxUseToolbox";
            this.checkBoxUseToolbox.Size = new System.Drawing.Size(66, 16);
            this.checkBoxUseToolbox.TabIndex = 8;
            this.checkBoxUseToolbox.Text = "ToolBox";
            this.checkBoxUseToolbox.UseVisualStyleBackColor = true;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(6, 304);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(65, 12);
            this.label1.TabIndex = 10;
            this.label1.Text = "Azi Offset";
            // 
            // checkBoxEnableShutter2
            // 
            this.checkBoxEnableShutter2.AutoSize = true;
            this.checkBoxEnableShutter2.Location = new System.Drawing.Point(82, 60);
            this.checkBoxEnableShutter2.Name = "checkBoxEnableShutter2";
            this.checkBoxEnableShutter2.Size = new System.Drawing.Size(90, 16);
            this.checkBoxEnableShutter2.TabIndex = 11;
            this.checkBoxEnableShutter2.Text = "MiniShutter";
            this.checkBoxEnableShutter2.UseVisualStyleBackColor = true;
            // 
            // textBoxAzimuthOffset
            // 
            this.textBoxAzimuthOffset.Location = new System.Drawing.Point(77, 301);
            this.textBoxAzimuthOffset.Name = "textBoxAzimuthOffset";
            this.textBoxAzimuthOffset.Size = new System.Drawing.Size(90, 21);
            this.textBoxAzimuthOffset.TabIndex = 9;
            this.textBoxAzimuthOffset.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBoxAzimuthOffset_KeyPress);
            // 
            // SetupDialogForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(243, 127);
            this.Controls.Add(this.checkBoxEnableShutter2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.textBoxAzimuthOffset);
            this.Controls.Add(this.checkBoxUseToolbox);
            this.Controls.Add(this.comboBoxComPort);
            this.Controls.Add(this.chkTrace);
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
            this.Text = "YNUDome Setup";
            ((System.ComponentModel.ISupportInitialize)(this.picASCOM)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button cmdOK;
        private System.Windows.Forms.Button cmdCancel;
        private System.Windows.Forms.PictureBox picASCOM;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.CheckBox chkTrace;
        private System.Windows.Forms.ComboBox comboBoxComPort;
        private System.Windows.Forms.CheckBox checkBoxUseToolbox;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.CheckBox checkBoxEnableShutter2;
        private System.Windows.Forms.TextBox textBoxAzimuthOffset;
    }
}