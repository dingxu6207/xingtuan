namespace ASCOM.SSFocuser
{
    partial class CoverSetting
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
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.textBoxOpenCode = new System.Windows.Forms.TextBox();
            this.textBoxCloseCode = new System.Windows.Forms.TextBox();
            this.cmdCancel = new System.Windows.Forms.Button();
            this.cmdOK = new System.Windows.Forms.Button();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 21);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(89, 12);
            this.label1.TabIndex = 0;
            this.label1.Text = "OpenPulseWidth";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 48);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(89, 12);
            this.label2.TabIndex = 1;
            this.label2.Text = "ShutPulseWidth";
            // 
            // textBoxOpenCode
            // 
            this.textBoxOpenCode.Location = new System.Drawing.Point(107, 18);
            this.textBoxOpenCode.Name = "textBoxOpenCode";
            this.textBoxOpenCode.Size = new System.Drawing.Size(70, 21);
            this.textBoxOpenCode.TabIndex = 2;
            // 
            // textBoxCloseCode
            // 
            this.textBoxCloseCode.Location = new System.Drawing.Point(107, 45);
            this.textBoxCloseCode.Name = "textBoxCloseCode";
            this.textBoxCloseCode.Size = new System.Drawing.Size(70, 21);
            this.textBoxCloseCode.TabIndex = 3;
            // 
            // cmdCancel
            // 
            this.cmdCancel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.cmdCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.cmdCancel.Location = new System.Drawing.Point(138, 75);
            this.cmdCancel.Name = "cmdCancel";
            this.cmdCancel.Size = new System.Drawing.Size(59, 23);
            this.cmdCancel.TabIndex = 5;
            this.cmdCancel.Text = "Cancel";
            this.cmdCancel.UseVisualStyleBackColor = true;
            // 
            // cmdOK
            // 
            this.cmdOK.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.cmdOK.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.cmdOK.Location = new System.Drawing.Point(42, 75);
            this.cmdOK.Name = "cmdOK";
            this.cmdOK.Size = new System.Drawing.Size(59, 23);
            this.cmdOK.TabIndex = 4;
            this.cmdOK.Text = "OK";
            this.cmdOK.UseVisualStyleBackColor = true;
            this.cmdOK.Click += new System.EventHandler(this.cmdOK_Click);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(186, 21);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(41, 12);
            this.label3.TabIndex = 6;
            this.label3.Text = "*0.1mS";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(186, 48);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(41, 12);
            this.label4.TabIndex = 7;
            this.label4.Text = "*0.1mS";
            // 
            // CoverSetting
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(239, 109);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.cmdCancel);
            this.Controls.Add(this.cmdOK);
            this.Controls.Add(this.textBoxCloseCode);
            this.Controls.Add(this.textBoxOpenCode);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Name = "CoverSetting";
            this.Text = "Cover Setting";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox textBoxOpenCode;
        private System.Windows.Forms.TextBox textBoxCloseCode;
        private System.Windows.Forms.Button cmdCancel;
        private System.Windows.Forms.Button cmdOK;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
    }
}