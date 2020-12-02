namespace ASCOM.YNUDome
{
    partial class GotoForm
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
            this.buttonGotoOK = new System.Windows.Forms.Button();
            this.buttonGotoCancel = new System.Windows.Forms.Button();
            this.numericUpDownAzimuth = new System.Windows.Forms.NumericUpDown();
            this.numericUpDownAltitude = new System.Windows.Forms.NumericUpDown();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownAzimuth)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownAltitude)).BeginInit();
            this.SuspendLayout();
            // 
            // buttonGotoOK
            // 
            this.buttonGotoOK.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.buttonGotoOK.Location = new System.Drawing.Point(12, 68);
            this.buttonGotoOK.Name = "buttonGotoOK";
            this.buttonGotoOK.Size = new System.Drawing.Size(75, 23);
            this.buttonGotoOK.TabIndex = 2;
            this.buttonGotoOK.Text = "OK";
            this.buttonGotoOK.UseVisualStyleBackColor = true;
            this.buttonGotoOK.Click += new System.EventHandler(this.buttonGotoOK_Click);
            // 
            // buttonGotoCancel
            // 
            this.buttonGotoCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.buttonGotoCancel.Location = new System.Drawing.Point(110, 68);
            this.buttonGotoCancel.Name = "buttonGotoCancel";
            this.buttonGotoCancel.Size = new System.Drawing.Size(75, 23);
            this.buttonGotoCancel.TabIndex = 3;
            this.buttonGotoCancel.Text = "Cancel";
            this.buttonGotoCancel.UseVisualStyleBackColor = true;
            this.buttonGotoCancel.Click += new System.EventHandler(this.buttonGotoCancel_Click);
            // 
            // numericUpDownAzimuth
            // 
            this.numericUpDownAzimuth.Location = new System.Drawing.Point(12, 35);
            this.numericUpDownAzimuth.Maximum = new decimal(new int[] {
            360,
            0,
            0,
            0});
            this.numericUpDownAzimuth.Minimum = new decimal(new int[] {
            360,
            0,
            0,
            -2147483648});
            this.numericUpDownAzimuth.Name = "numericUpDownAzimuth";
            this.numericUpDownAzimuth.Size = new System.Drawing.Size(75, 21);
            this.numericUpDownAzimuth.TabIndex = 4;
            // 
            // numericUpDownAltitude
            // 
            this.numericUpDownAltitude.Location = new System.Drawing.Point(110, 35);
            this.numericUpDownAltitude.Maximum = new decimal(new int[] {
            90,
            0,
            0,
            0});
            this.numericUpDownAltitude.Name = "numericUpDownAltitude";
            this.numericUpDownAltitude.Size = new System.Drawing.Size(75, 21);
            this.numericUpDownAltitude.TabIndex = 5;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 12);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(47, 12);
            this.label1.TabIndex = 6;
            this.label1.Text = "Azimuth";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(111, 12);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(53, 12);
            this.label2.TabIndex = 7;
            this.label2.Text = "Altitude";
            // 
            // GotoForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(196, 102);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.numericUpDownAltitude);
            this.Controls.Add(this.numericUpDownAzimuth);
            this.Controls.Add(this.buttonGotoCancel);
            this.Controls.Add(this.buttonGotoOK);
            this.Name = "GotoForm";
            this.Text = "GotoForm";
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownAzimuth)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownAltitude)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button buttonGotoOK;
        private System.Windows.Forms.Button buttonGotoCancel;
        private System.Windows.Forms.NumericUpDown numericUpDownAzimuth;
        private System.Windows.Forms.NumericUpDown numericUpDownAltitude;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
    }
}