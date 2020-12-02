namespace CAO
{
    partial class MainForm
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.Observe = new System.Windows.Forms.TabPage();
            this.Camera = new System.Windows.Forms.TabPage();
            this.groupBox8 = new System.Windows.Forms.GroupBox();
            this.textBoxCameraFilterStatus = new System.Windows.Forms.TextBox();
            this.groupBox7 = new System.Windows.Forms.GroupBox();
            this.buttonCameraAutoSave = new System.Windows.Forms.Button();
            this.label26 = new System.Windows.Forms.Label();
            this.comboBoxMode = new System.Windows.Forms.ComboBox();
            this.comboBoxFilter = new System.Windows.Forms.ComboBox();
            this.numericUpDownExposeTime = new System.Windows.Forms.NumericUpDown();
            this.label21 = new System.Windows.Forms.Label();
            this.label16 = new System.Windows.Forms.Label();
            this.label23 = new System.Windows.Forms.Label();
            this.label22 = new System.Windows.Forms.Label();
            this.comboBoxBinY = new System.Windows.Forms.ComboBox();
            this.comboBoxBinX = new System.Windows.Forms.ComboBox();
            this.buttonCameraStopExpose = new System.Windows.Forms.Button();
            this.label19 = new System.Windows.Forms.Label();
            this.comboBoxFrame = new System.Windows.Forms.ComboBox();
            this.buttonCameraStartExpose = new System.Windows.Forms.Button();
            this.Focuser = new System.Windows.Forms.TabPage();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.label20 = new System.Windows.Forms.Label();
            this.textBoxFocuserBCSteps = new System.Windows.Forms.TextBox();
            this.checkBoxFocuserBCOut = new System.Windows.Forms.CheckBox();
            this.checkBoxFocuserBCEnabled = new System.Windows.Forms.CheckBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.buttonFocuserAbort = new System.Windows.Forms.Button();
            this.buttonFocuserMoveOut = new System.Windows.Forms.Button();
            this.buttonFocuserMoveIn = new System.Windows.Forms.Button();
            this.textBoxFocuserIncrement = new System.Windows.Forms.TextBox();
            this.textBoxFocuserPositionMoveTo = new System.Windows.Forms.TextBox();
            this.buttonFocuserMoveTo = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.textBoxFocuserType = new System.Windows.Forms.TextBox();
            this.label18 = new System.Windows.Forms.Label();
            this.textBoxFocuserTemperature = new System.Windows.Forms.TextBox();
            this.label17 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.textBoxFocuserPosition = new System.Windows.Forms.TextBox();
            this.textBoxFocuserStatus = new System.Windows.Forms.TextBox();
            this.Telescope = new System.Windows.Forms.TabPage();
            this.groupBox12 = new System.Windows.Forms.GroupBox();
            this.textBoxTelescopeStatus = new System.Windows.Forms.TextBox();
            this.groupBox11 = new System.Windows.Forms.GroupBox();
            this.buttonTelescopeLimit = new System.Windows.Forms.Button();
            this.buttonTelescopeSite = new System.Windows.Forms.Button();
            this.groupBox10 = new System.Windows.Forms.GroupBox();
            this.buttonTelescopeHome = new System.Windows.Forms.Button();
            this.buttonTelescopeCalibrate = new System.Windows.Forms.Button();
            this.buttonTelescopePark = new System.Windows.Forms.Button();
            this.buttonTelescopeSync = new System.Windows.Forms.Button();
            this.buttonTelescopeGoto = new System.Windows.Forms.Button();
            this.numericUpDownTelescopeTargetDEC = new System.Windows.Forms.NumericUpDown();
            this.numericUpDownTelescopeTargetRa = new System.Windows.Forms.NumericUpDown();
            this.label25 = new System.Windows.Forms.Label();
            this.label24 = new System.Windows.Forms.Label();
            this.groupBox9 = new System.Windows.Forms.GroupBox();
            this.numericUpDownTelescopeSlewIncrement = new System.Windows.Forms.NumericUpDown();
            this.comboBoxTelescopeSlewUnit = new System.Windows.Forms.ComboBox();
            this.buttonTelesocpeStop = new System.Windows.Forms.Button();
            this.buttonTelescopeWestward = new System.Windows.Forms.Button();
            this.buttonTelescopeEastward = new System.Windows.Forms.Button();
            this.buttonTelescopeSouthward = new System.Windows.Forms.Button();
            this.buttonTelescopeNorthward = new System.Windows.Forms.Button();
            this.Dome = new System.Windows.Forms.TabPage();
            this.groupBox6 = new System.Windows.Forms.GroupBox();
            this.textBoxDomeState = new System.Windows.Forms.TextBox();
            this.groupBox5 = new System.Windows.Forms.GroupBox();
            this.buttonDomeHome = new System.Windows.Forms.Button();
            this.buttonDomePark = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.buttonDomeAbort = new System.Windows.Forms.Button();
            this.textBoxAzimuth = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.checkBoxSlaveDome = new System.Windows.Forms.CheckBox();
            this.textBoxAltitude = new System.Windows.Forms.TextBox();
            this.buttonDomeGoto = new System.Windows.Forms.Button();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.buttonDomeShutterOpen = new System.Windows.Forms.Button();
            this.buttonDomeShutterClose = new System.Windows.Forms.Button();
            this.Weather = new System.Windows.Forms.TabPage();
            this.groupBoxState = new System.Windows.Forms.GroupBox();
            this.textBoxWindSpeed = new System.Windows.Forms.TextBox();
            this.label15 = new System.Windows.Forms.Label();
            this.textBoxWindGust = new System.Windows.Forms.TextBox();
            this.label14 = new System.Windows.Forms.Label();
            this.textBoxWindDirection = new System.Windows.Forms.TextBox();
            this.label13 = new System.Windows.Forms.Label();
            this.textBoxTemperature = new System.Windows.Forms.TextBox();
            this.label12 = new System.Windows.Forms.Label();
            this.textBoxSkyTemperature = new System.Windows.Forms.TextBox();
            this.label11 = new System.Windows.Forms.Label();
            this.textBoxStarFWHM = new System.Windows.Forms.TextBox();
            this.label10 = new System.Windows.Forms.Label();
            this.textBoxSkyQuality = new System.Windows.Forms.TextBox();
            this.label9 = new System.Windows.Forms.Label();
            this.textBoxRainRate = new System.Windows.Forms.TextBox();
            this.label8 = new System.Windows.Forms.Label();
            this.textBoxPressure = new System.Windows.Forms.TextBox();
            this.label7 = new System.Windows.Forms.Label();
            this.textBoxHumidity = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.textBoxDewPoint = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.textBoxCloudCover = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.Setup = new System.Windows.Forms.TabPage();
            this.groupBoxSwitch = new System.Windows.Forms.GroupBox();
            this.textBoxSwitchID = new System.Windows.Forms.TextBox();
            this.buttonConnectSwitch = new System.Windows.Forms.Button();
            this.buttonChooseSwitch = new System.Windows.Forms.Button();
            this.groupBoxWhether = new System.Windows.Forms.GroupBox();
            this.textBoxObsConditionsID = new System.Windows.Forms.TextBox();
            this.buttonConnectObsConditions = new System.Windows.Forms.Button();
            this.buttonChooseObsConditions = new System.Windows.Forms.Button();
            this.groupBoxFilter = new System.Windows.Forms.GroupBox();
            this.textBoxFilterWheelID = new System.Windows.Forms.TextBox();
            this.buttonConnectFilterWheel = new System.Windows.Forms.Button();
            this.buttonChooseFilterWheel = new System.Windows.Forms.Button();
            this.groupBoxFocuser = new System.Windows.Forms.GroupBox();
            this.textBoxFocuserID = new System.Windows.Forms.TextBox();
            this.buttonConnectFocuser = new System.Windows.Forms.Button();
            this.buttonChooseFocuser = new System.Windows.Forms.Button();
            this.groupBoxDome = new System.Windows.Forms.GroupBox();
            this.textBoxDomeID = new System.Windows.Forms.TextBox();
            this.buttonConnectDome = new System.Windows.Forms.Button();
            this.buttonChooseDome = new System.Windows.Forms.Button();
            this.groupBoxTelescope = new System.Windows.Forms.GroupBox();
            this.textBoxTelescopeID = new System.Windows.Forms.TextBox();
            this.buttonConnectTelescope = new System.Windows.Forms.Button();
            this.buttonChooseTelescope = new System.Windows.Forms.Button();
            this.groupBoxCamera = new System.Windows.Forms.GroupBox();
            this.textBoxCameraID = new System.Windows.Forms.TextBox();
            this.buttonConnectCamera = new System.Windows.Forms.Button();
            this.buttonChooseCamera = new System.Windows.Forms.Button();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.label27 = new System.Windows.Forms.Label();
            this.groupBox13 = new System.Windows.Forms.GroupBox();
            this.label28 = new System.Windows.Forms.Label();
            this.button1 = new System.Windows.Forms.Button();
            this.tabControl1.SuspendLayout();
            this.Observe.SuspendLayout();
            this.Camera.SuspendLayout();
            this.groupBox8.SuspendLayout();
            this.groupBox7.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownExposeTime)).BeginInit();
            this.Focuser.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.Telescope.SuspendLayout();
            this.groupBox12.SuspendLayout();
            this.groupBox11.SuspendLayout();
            this.groupBox10.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownTelescopeTargetDEC)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownTelescopeTargetRa)).BeginInit();
            this.groupBox9.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownTelescopeSlewIncrement)).BeginInit();
            this.Dome.SuspendLayout();
            this.groupBox6.SuspendLayout();
            this.groupBox5.SuspendLayout();
            this.groupBox4.SuspendLayout();
            this.Weather.SuspendLayout();
            this.groupBoxState.SuspendLayout();
            this.Setup.SuspendLayout();
            this.groupBoxSwitch.SuspendLayout();
            this.groupBoxWhether.SuspendLayout();
            this.groupBoxFilter.SuspendLayout();
            this.groupBoxFocuser.SuspendLayout();
            this.groupBoxDome.SuspendLayout();
            this.groupBoxTelescope.SuspendLayout();
            this.groupBoxCamera.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.groupBox13.SuspendLayout();
            this.SuspendLayout();
            // 
            // tabControl1
            // 
            this.tabControl1.Alignment = System.Windows.Forms.TabAlignment.Left;
            this.tabControl1.Controls.Add(this.Observe);
            this.tabControl1.Controls.Add(this.Camera);
            this.tabControl1.Controls.Add(this.Focuser);
            this.tabControl1.Controls.Add(this.Telescope);
            this.tabControl1.Controls.Add(this.Dome);
            this.tabControl1.Controls.Add(this.Weather);
            this.tabControl1.Controls.Add(this.Setup);
            this.tabControl1.DrawMode = System.Windows.Forms.TabDrawMode.OwnerDrawFixed;
            this.tabControl1.ItemSize = new System.Drawing.Size(30, 60);
            this.tabControl1.Location = new System.Drawing.Point(0, 0);
            this.tabControl1.Multiline = true;
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(245, 620);
            this.tabControl1.SizeMode = System.Windows.Forms.TabSizeMode.Fixed;
            this.tabControl1.TabIndex = 0;
            this.tabControl1.DrawItem += new System.Windows.Forms.DrawItemEventHandler(this.tabControl1_DrawItem);
            this.tabControl1.SelectedIndexChanged += new System.EventHandler(this.tabControl1_TabIndexChanged);
            this.tabControl1.TabIndexChanged += new System.EventHandler(this.tabControl1_TabIndexChanged);
            // 
            // Observe
            // 
            this.Observe.Controls.Add(this.button1);
            this.Observe.Controls.Add(this.groupBox13);
            this.Observe.Location = new System.Drawing.Point(64, 4);
            this.Observe.Name = "Observe";
            this.Observe.Size = new System.Drawing.Size(177, 612);
            this.Observe.TabIndex = 8;
            this.Observe.Text = "Observe";
            this.Observe.UseVisualStyleBackColor = true;
            // 
            // Camera
            // 
            this.Camera.Controls.Add(this.groupBox8);
            this.Camera.Controls.Add(this.groupBox7);
            this.Camera.Location = new System.Drawing.Point(64, 4);
            this.Camera.Name = "Camera";
            this.Camera.Padding = new System.Windows.Forms.Padding(3);
            this.Camera.Size = new System.Drawing.Size(177, 612);
            this.Camera.TabIndex = 1;
            this.Camera.Text = "Camera";
            this.Camera.UseVisualStyleBackColor = true;
            // 
            // groupBox8
            // 
            this.groupBox8.Controls.Add(this.textBoxCameraFilterStatus);
            this.groupBox8.Location = new System.Drawing.Point(10, 244);
            this.groupBox8.Name = "groupBox8";
            this.groupBox8.Size = new System.Drawing.Size(167, 150);
            this.groupBox8.TabIndex = 2;
            this.groupBox8.TabStop = false;
            this.groupBox8.Text = "Status";
            // 
            // textBoxCameraFilterStatus
            // 
            this.textBoxCameraFilterStatus.Location = new System.Drawing.Point(7, 21);
            this.textBoxCameraFilterStatus.Multiline = true;
            this.textBoxCameraFilterStatus.Name = "textBoxCameraFilterStatus";
            this.textBoxCameraFilterStatus.Size = new System.Drawing.Size(154, 123);
            this.textBoxCameraFilterStatus.TabIndex = 0;
            // 
            // groupBox7
            // 
            this.groupBox7.Controls.Add(this.buttonCameraAutoSave);
            this.groupBox7.Controls.Add(this.label26);
            this.groupBox7.Controls.Add(this.comboBoxMode);
            this.groupBox7.Controls.Add(this.comboBoxFilter);
            this.groupBox7.Controls.Add(this.numericUpDownExposeTime);
            this.groupBox7.Controls.Add(this.label21);
            this.groupBox7.Controls.Add(this.label16);
            this.groupBox7.Controls.Add(this.label23);
            this.groupBox7.Controls.Add(this.label22);
            this.groupBox7.Controls.Add(this.comboBoxBinY);
            this.groupBox7.Controls.Add(this.comboBoxBinX);
            this.groupBox7.Controls.Add(this.buttonCameraStopExpose);
            this.groupBox7.Controls.Add(this.label19);
            this.groupBox7.Controls.Add(this.comboBoxFrame);
            this.groupBox7.Controls.Add(this.buttonCameraStartExpose);
            this.groupBox7.Location = new System.Drawing.Point(10, 10);
            this.groupBox7.Name = "groupBox7";
            this.groupBox7.Size = new System.Drawing.Size(160, 228);
            this.groupBox7.TabIndex = 1;
            this.groupBox7.TabStop = false;
            this.groupBox7.Text = "Expose";
            // 
            // buttonCameraAutoSave
            // 
            this.buttonCameraAutoSave.Location = new System.Drawing.Point(80, 74);
            this.buttonCameraAutoSave.Margin = new System.Windows.Forms.Padding(2);
            this.buttonCameraAutoSave.Name = "buttonCameraAutoSave";
            this.buttonCameraAutoSave.Size = new System.Drawing.Size(65, 23);
            this.buttonCameraAutoSave.TabIndex = 17;
            this.buttonCameraAutoSave.Text = "AutoSave";
            this.buttonCameraAutoSave.UseVisualStyleBackColor = true;
            this.buttonCameraAutoSave.Click += new System.EventHandler(this.buttonCameraAutoSave_Click);
            // 
            // label26
            // 
            this.label26.AutoSize = true;
            this.label26.Location = new System.Drawing.Point(10, 60);
            this.label26.Name = "label26";
            this.label26.Size = new System.Drawing.Size(29, 12);
            this.label26.TabIndex = 16;
            this.label26.Text = "Mode";
            // 
            // comboBoxMode
            // 
            this.comboBoxMode.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxMode.FormattingEnabled = true;
            this.comboBoxMode.Items.AddRange(new object[] {
            "Single",
            "Multi",
            "Focus"});
            this.comboBoxMode.Location = new System.Drawing.Point(10, 75);
            this.comboBoxMode.Name = "comboBoxMode";
            this.comboBoxMode.Size = new System.Drawing.Size(65, 20);
            this.comboBoxMode.TabIndex = 15;
            // 
            // comboBoxFilter
            // 
            this.comboBoxFilter.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxFilter.FormattingEnabled = true;
            this.comboBoxFilter.Location = new System.Drawing.Point(10, 155);
            this.comboBoxFilter.Name = "comboBoxFilter";
            this.comboBoxFilter.Size = new System.Drawing.Size(140, 20);
            this.comboBoxFilter.TabIndex = 3;
            this.comboBoxFilter.SelectedIndexChanged += new System.EventHandler(this.comboBoxFilter_SelectedIndexChanged);
            // 
            // numericUpDownExposeTime
            // 
            this.numericUpDownExposeTime.Location = new System.Drawing.Point(80, 35);
            this.numericUpDownExposeTime.Name = "numericUpDownExposeTime";
            this.numericUpDownExposeTime.Size = new System.Drawing.Size(65, 21);
            this.numericUpDownExposeTime.TabIndex = 14;
            this.numericUpDownExposeTime.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // label21
            // 
            this.label21.AutoSize = true;
            this.label21.Location = new System.Drawing.Point(10, 140);
            this.label21.Name = "label21";
            this.label21.Size = new System.Drawing.Size(41, 12);
            this.label21.TabIndex = 4;
            this.label21.Text = "Filter";
            // 
            // label16
            // 
            this.label16.AutoSize = true;
            this.label16.Location = new System.Drawing.Point(90, 20);
            this.label16.Name = "label16";
            this.label16.Size = new System.Drawing.Size(47, 12);
            this.label16.TabIndex = 13;
            this.label16.Text = "Seconds";
            // 
            // label23
            // 
            this.label23.AutoSize = true;
            this.label23.Location = new System.Drawing.Point(90, 99);
            this.label23.Name = "label23";
            this.label23.Size = new System.Drawing.Size(29, 12);
            this.label23.TabIndex = 12;
            this.label23.Text = "BinY";
            // 
            // label22
            // 
            this.label22.AutoSize = true;
            this.label22.Location = new System.Drawing.Point(10, 100);
            this.label22.Name = "label22";
            this.label22.Size = new System.Drawing.Size(29, 12);
            this.label22.TabIndex = 11;
            this.label22.Text = "BinX";
            // 
            // comboBoxBinY
            // 
            this.comboBoxBinY.FormattingEnabled = true;
            this.comboBoxBinY.Items.AddRange(new object[] {
            "Light",
            "Bias",
            "Dark",
            "Flat"});
            this.comboBoxBinY.Location = new System.Drawing.Point(80, 115);
            this.comboBoxBinY.Name = "comboBoxBinY";
            this.comboBoxBinY.Size = new System.Drawing.Size(65, 20);
            this.comboBoxBinY.TabIndex = 10;
            // 
            // comboBoxBinX
            // 
            this.comboBoxBinX.FormattingEnabled = true;
            this.comboBoxBinX.Items.AddRange(new object[] {
            "Light",
            "Bias",
            "Dark",
            "Flat"});
            this.comboBoxBinX.Location = new System.Drawing.Point(10, 115);
            this.comboBoxBinX.Name = "comboBoxBinX";
            this.comboBoxBinX.Size = new System.Drawing.Size(65, 20);
            this.comboBoxBinX.TabIndex = 9;
            // 
            // buttonCameraStopExpose
            // 
            this.buttonCameraStopExpose.Location = new System.Drawing.Point(90, 185);
            this.buttonCameraStopExpose.Name = "buttonCameraStopExpose";
            this.buttonCameraStopExpose.Size = new System.Drawing.Size(65, 23);
            this.buttonCameraStopExpose.TabIndex = 8;
            this.buttonCameraStopExpose.Text = "Abort";
            this.buttonCameraStopExpose.UseVisualStyleBackColor = true;
            this.buttonCameraStopExpose.Click += new System.EventHandler(this.buttonStopExpose_Click);
            // 
            // label19
            // 
            this.label19.AutoSize = true;
            this.label19.Location = new System.Drawing.Point(10, 20);
            this.label19.Name = "label19";
            this.label19.Size = new System.Drawing.Size(35, 12);
            this.label19.TabIndex = 2;
            this.label19.Text = "Frame";
            // 
            // comboBoxFrame
            // 
            this.comboBoxFrame.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxFrame.FormattingEnabled = true;
            this.comboBoxFrame.Items.AddRange(new object[] {
            "Light",
            "Flat",
            "Bias",
            "Dark"});
            this.comboBoxFrame.Location = new System.Drawing.Point(10, 35);
            this.comboBoxFrame.Name = "comboBoxFrame";
            this.comboBoxFrame.Size = new System.Drawing.Size(65, 20);
            this.comboBoxFrame.TabIndex = 1;
            // 
            // buttonCameraStartExpose
            // 
            this.buttonCameraStartExpose.Location = new System.Drawing.Point(10, 185);
            this.buttonCameraStartExpose.Margin = new System.Windows.Forms.Padding(2);
            this.buttonCameraStartExpose.Name = "buttonCameraStartExpose";
            this.buttonCameraStartExpose.Size = new System.Drawing.Size(65, 23);
            this.buttonCameraStartExpose.TabIndex = 0;
            this.buttonCameraStartExpose.Text = "Start";
            this.buttonCameraStartExpose.UseVisualStyleBackColor = true;
            this.buttonCameraStartExpose.Click += new System.EventHandler(this.buttonStartExpose_Click);
            // 
            // Focuser
            // 
            this.Focuser.Controls.Add(this.groupBox3);
            this.Focuser.Controls.Add(this.groupBox2);
            this.Focuser.Controls.Add(this.groupBox1);
            this.Focuser.Controls.Add(this.textBoxFocuserStatus);
            this.Focuser.Location = new System.Drawing.Point(64, 4);
            this.Focuser.Name = "Focuser";
            this.Focuser.Size = new System.Drawing.Size(177, 612);
            this.Focuser.TabIndex = 2;
            this.Focuser.Text = "Focuser";
            this.Focuser.UseVisualStyleBackColor = true;
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.label20);
            this.groupBox3.Controls.Add(this.textBoxFocuserBCSteps);
            this.groupBox3.Controls.Add(this.checkBoxFocuserBCOut);
            this.groupBox3.Controls.Add(this.checkBoxFocuserBCEnabled);
            this.groupBox3.Location = new System.Drawing.Point(10, 317);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(160, 95);
            this.groupBox3.TabIndex = 7;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Backlash Compensation";
            // 
            // label20
            // 
            this.label20.AutoSize = true;
            this.label20.Location = new System.Drawing.Point(10, 64);
            this.label20.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label20.Name = "label20";
            this.label20.Size = new System.Drawing.Size(35, 12);
            this.label20.TabIndex = 7;
            this.label20.Text = "Steps";
            // 
            // textBoxFocuserBCSteps
            // 
            this.textBoxFocuserBCSteps.Location = new System.Drawing.Point(52, 60);
            this.textBoxFocuserBCSteps.Margin = new System.Windows.Forms.Padding(2);
            this.textBoxFocuserBCSteps.Name = "textBoxFocuserBCSteps";
            this.textBoxFocuserBCSteps.Size = new System.Drawing.Size(78, 21);
            this.textBoxFocuserBCSteps.TabIndex = 11;
            // 
            // checkBoxFocuserBCOut
            // 
            this.checkBoxFocuserBCOut.AutoSize = true;
            this.checkBoxFocuserBCOut.Location = new System.Drawing.Point(10, 40);
            this.checkBoxFocuserBCOut.Name = "checkBoxFocuserBCOut";
            this.checkBoxFocuserBCOut.Size = new System.Drawing.Size(120, 16);
            this.checkBoxFocuserBCOut.TabIndex = 1;
            this.checkBoxFocuserBCOut.Text = "On Outward Moves";
            this.checkBoxFocuserBCOut.UseVisualStyleBackColor = true;
            // 
            // checkBoxFocuserBCEnabled
            // 
            this.checkBoxFocuserBCEnabled.AutoSize = true;
            this.checkBoxFocuserBCEnabled.Location = new System.Drawing.Point(10, 20);
            this.checkBoxFocuserBCEnabled.Name = "checkBoxFocuserBCEnabled";
            this.checkBoxFocuserBCEnabled.Size = new System.Drawing.Size(66, 16);
            this.checkBoxFocuserBCEnabled.TabIndex = 0;
            this.checkBoxFocuserBCEnabled.Text = "Enabled";
            this.checkBoxFocuserBCEnabled.UseVisualStyleBackColor = true;
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.buttonFocuserAbort);
            this.groupBox2.Controls.Add(this.buttonFocuserMoveOut);
            this.groupBox2.Controls.Add(this.buttonFocuserMoveIn);
            this.groupBox2.Controls.Add(this.textBoxFocuserIncrement);
            this.groupBox2.Controls.Add(this.textBoxFocuserPositionMoveTo);
            this.groupBox2.Controls.Add(this.buttonFocuserMoveTo);
            this.groupBox2.Location = new System.Drawing.Point(10, 153);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(160, 141);
            this.groupBox2.TabIndex = 6;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Movement";
            // 
            // buttonFocuserAbort
            // 
            this.buttonFocuserAbort.Location = new System.Drawing.Point(80, 45);
            this.buttonFocuserAbort.Margin = new System.Windows.Forms.Padding(2);
            this.buttonFocuserAbort.Name = "buttonFocuserAbort";
            this.buttonFocuserAbort.Size = new System.Drawing.Size(65, 23);
            this.buttonFocuserAbort.TabIndex = 11;
            this.buttonFocuserAbort.Text = "Abort";
            this.buttonFocuserAbort.UseVisualStyleBackColor = true;
            this.buttonFocuserAbort.Click += new System.EventHandler(this.buttonFocuserAbort_Click);
            // 
            // buttonFocuserMoveOut
            // 
            this.buttonFocuserMoveOut.Location = new System.Drawing.Point(80, 105);
            this.buttonFocuserMoveOut.Margin = new System.Windows.Forms.Padding(2);
            this.buttonFocuserMoveOut.Name = "buttonFocuserMoveOut";
            this.buttonFocuserMoveOut.Size = new System.Drawing.Size(65, 23);
            this.buttonFocuserMoveOut.TabIndex = 10;
            this.buttonFocuserMoveOut.Text = "Move Out";
            this.buttonFocuserMoveOut.UseVisualStyleBackColor = true;
            this.buttonFocuserMoveOut.Click += new System.EventHandler(this.buttonFocuserMoveOut_Click);
            // 
            // buttonFocuserMoveIn
            // 
            this.buttonFocuserMoveIn.Location = new System.Drawing.Point(10, 105);
            this.buttonFocuserMoveIn.Margin = new System.Windows.Forms.Padding(2);
            this.buttonFocuserMoveIn.Name = "buttonFocuserMoveIn";
            this.buttonFocuserMoveIn.Size = new System.Drawing.Size(65, 23);
            this.buttonFocuserMoveIn.TabIndex = 9;
            this.buttonFocuserMoveIn.Text = "Move In";
            this.buttonFocuserMoveIn.UseVisualStyleBackColor = true;
            this.buttonFocuserMoveIn.Click += new System.EventHandler(this.buttonFocuserMoveIn_Click);
            // 
            // textBoxFocuserIncrement
            // 
            this.textBoxFocuserIncrement.Location = new System.Drawing.Point(30, 75);
            this.textBoxFocuserIncrement.Margin = new System.Windows.Forms.Padding(2);
            this.textBoxFocuserIncrement.Name = "textBoxFocuserIncrement";
            this.textBoxFocuserIncrement.Size = new System.Drawing.Size(100, 21);
            this.textBoxFocuserIncrement.TabIndex = 8;
            // 
            // textBoxFocuserPositionMoveTo
            // 
            this.textBoxFocuserPositionMoveTo.Location = new System.Drawing.Point(30, 20);
            this.textBoxFocuserPositionMoveTo.Margin = new System.Windows.Forms.Padding(2);
            this.textBoxFocuserPositionMoveTo.Name = "textBoxFocuserPositionMoveTo";
            this.textBoxFocuserPositionMoveTo.Size = new System.Drawing.Size(100, 21);
            this.textBoxFocuserPositionMoveTo.TabIndex = 7;
            // 
            // buttonFocuserMoveTo
            // 
            this.buttonFocuserMoveTo.Location = new System.Drawing.Point(10, 45);
            this.buttonFocuserMoveTo.Margin = new System.Windows.Forms.Padding(2);
            this.buttonFocuserMoveTo.Name = "buttonFocuserMoveTo";
            this.buttonFocuserMoveTo.Size = new System.Drawing.Size(65, 23);
            this.buttonFocuserMoveTo.TabIndex = 4;
            this.buttonFocuserMoveTo.Text = "Move to";
            this.buttonFocuserMoveTo.UseVisualStyleBackColor = true;
            this.buttonFocuserMoveTo.Click += new System.EventHandler(this.buttonFocuserMoveTo_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.textBoxFocuserType);
            this.groupBox1.Controls.Add(this.label18);
            this.groupBox1.Controls.Add(this.textBoxFocuserTemperature);
            this.groupBox1.Controls.Add(this.label17);
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.Controls.Add(this.textBoxFocuserPosition);
            this.groupBox1.Location = new System.Drawing.Point(6, 3);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(160, 145);
            this.groupBox1.TabIndex = 5;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Focuser Status";
            // 
            // textBoxFocuserType
            // 
            this.textBoxFocuserType.Location = new System.Drawing.Point(10, 115);
            this.textBoxFocuserType.Margin = new System.Windows.Forms.Padding(2);
            this.textBoxFocuserType.Name = "textBoxFocuserType";
            this.textBoxFocuserType.ReadOnly = true;
            this.textBoxFocuserType.Size = new System.Drawing.Size(109, 21);
            this.textBoxFocuserType.TabIndex = 5;
            // 
            // label18
            // 
            this.label18.AutoSize = true;
            this.label18.Location = new System.Drawing.Point(10, 100);
            this.label18.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label18.Name = "label18";
            this.label18.Size = new System.Drawing.Size(77, 12);
            this.label18.TabIndex = 4;
            this.label18.Text = "Focuser Type";
            // 
            // textBoxFocuserTemperature
            // 
            this.textBoxFocuserTemperature.Location = new System.Drawing.Point(10, 75);
            this.textBoxFocuserTemperature.Margin = new System.Windows.Forms.Padding(2);
            this.textBoxFocuserTemperature.Name = "textBoxFocuserTemperature";
            this.textBoxFocuserTemperature.ReadOnly = true;
            this.textBoxFocuserTemperature.Size = new System.Drawing.Size(109, 21);
            this.textBoxFocuserTemperature.TabIndex = 3;
            // 
            // label17
            // 
            this.label17.AutoSize = true;
            this.label17.Location = new System.Drawing.Point(10, 60);
            this.label17.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label17.Name = "label17";
            this.label17.Size = new System.Drawing.Size(71, 12);
            this.label17.TabIndex = 2;
            this.label17.Text = "Temperation";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(10, 20);
            this.label4.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(53, 12);
            this.label4.TabIndex = 0;
            this.label4.Text = "Position";
            // 
            // textBoxFocuserPosition
            // 
            this.textBoxFocuserPosition.Location = new System.Drawing.Point(10, 35);
            this.textBoxFocuserPosition.Margin = new System.Windows.Forms.Padding(2);
            this.textBoxFocuserPosition.Name = "textBoxFocuserPosition";
            this.textBoxFocuserPosition.ReadOnly = true;
            this.textBoxFocuserPosition.Size = new System.Drawing.Size(109, 21);
            this.textBoxFocuserPosition.TabIndex = 1;
            // 
            // textBoxFocuserStatus
            // 
            this.textBoxFocuserStatus.Location = new System.Drawing.Point(10, 416);
            this.textBoxFocuserStatus.Margin = new System.Windows.Forms.Padding(2);
            this.textBoxFocuserStatus.Multiline = true;
            this.textBoxFocuserStatus.Name = "textBoxFocuserStatus";
            this.textBoxFocuserStatus.ReadOnly = true;
            this.textBoxFocuserStatus.Size = new System.Drawing.Size(153, 101);
            this.textBoxFocuserStatus.TabIndex = 3;
            // 
            // Telescope
            // 
            this.Telescope.Controls.Add(this.groupBox12);
            this.Telescope.Controls.Add(this.groupBox11);
            this.Telescope.Controls.Add(this.groupBox10);
            this.Telescope.Controls.Add(this.groupBox9);
            this.Telescope.Location = new System.Drawing.Point(64, 4);
            this.Telescope.Name = "Telescope";
            this.Telescope.Padding = new System.Windows.Forms.Padding(3);
            this.Telescope.Size = new System.Drawing.Size(177, 612);
            this.Telescope.TabIndex = 0;
            this.Telescope.Text = "Telescope";
            this.Telescope.UseVisualStyleBackColor = true;
            // 
            // groupBox12
            // 
            this.groupBox12.Controls.Add(this.textBoxTelescopeStatus);
            this.groupBox12.Location = new System.Drawing.Point(10, 10);
            this.groupBox12.Name = "groupBox12";
            this.groupBox12.Size = new System.Drawing.Size(160, 130);
            this.groupBox12.TabIndex = 3;
            this.groupBox12.TabStop = false;
            this.groupBox12.Text = "Status";
            // 
            // textBoxTelescopeStatus
            // 
            this.textBoxTelescopeStatus.Location = new System.Drawing.Point(10, 20);
            this.textBoxTelescopeStatus.Multiline = true;
            this.textBoxTelescopeStatus.Name = "textBoxTelescopeStatus";
            this.textBoxTelescopeStatus.ReadOnly = true;
            this.textBoxTelescopeStatus.Size = new System.Drawing.Size(140, 100);
            this.textBoxTelescopeStatus.TabIndex = 0;
            // 
            // groupBox11
            // 
            this.groupBox11.Controls.Add(this.buttonTelescopeLimit);
            this.groupBox11.Controls.Add(this.buttonTelescopeSite);
            this.groupBox11.Location = new System.Drawing.Point(10, 500);
            this.groupBox11.Name = "groupBox11";
            this.groupBox11.Size = new System.Drawing.Size(160, 56);
            this.groupBox11.TabIndex = 2;
            this.groupBox11.TabStop = false;
            this.groupBox11.Text = "Configuration";
            // 
            // buttonTelescopeLimit
            // 
            this.buttonTelescopeLimit.Location = new System.Drawing.Point(80, 20);
            this.buttonTelescopeLimit.Name = "buttonTelescopeLimit";
            this.buttonTelescopeLimit.Size = new System.Drawing.Size(60, 23);
            this.buttonTelescopeLimit.TabIndex = 1;
            this.buttonTelescopeLimit.Text = "Limit";
            this.buttonTelescopeLimit.UseVisualStyleBackColor = true;
            this.buttonTelescopeLimit.Click += new System.EventHandler(this.buttonTelescopeLimit_Click);
            // 
            // buttonTelescopeSite
            // 
            this.buttonTelescopeSite.Location = new System.Drawing.Point(10, 20);
            this.buttonTelescopeSite.Name = "buttonTelescopeSite";
            this.buttonTelescopeSite.Size = new System.Drawing.Size(60, 23);
            this.buttonTelescopeSite.TabIndex = 0;
            this.buttonTelescopeSite.Text = "Site";
            this.buttonTelescopeSite.UseVisualStyleBackColor = true;
            this.buttonTelescopeSite.Click += new System.EventHandler(this.buttonTelescopeSite_Click);
            // 
            // groupBox10
            // 
            this.groupBox10.Controls.Add(this.buttonTelescopeHome);
            this.groupBox10.Controls.Add(this.buttonTelescopeCalibrate);
            this.groupBox10.Controls.Add(this.buttonTelescopePark);
            this.groupBox10.Controls.Add(this.buttonTelescopeSync);
            this.groupBox10.Controls.Add(this.buttonTelescopeGoto);
            this.groupBox10.Controls.Add(this.numericUpDownTelescopeTargetDEC);
            this.groupBox10.Controls.Add(this.numericUpDownTelescopeTargetRa);
            this.groupBox10.Controls.Add(this.label25);
            this.groupBox10.Controls.Add(this.label24);
            this.groupBox10.Location = new System.Drawing.Point(10, 320);
            this.groupBox10.Name = "groupBox10";
            this.groupBox10.Size = new System.Drawing.Size(160, 172);
            this.groupBox10.TabIndex = 1;
            this.groupBox10.TabStop = false;
            this.groupBox10.Text = "Target";
            // 
            // buttonTelescopeHome
            // 
            this.buttonTelescopeHome.Location = new System.Drawing.Point(10, 110);
            this.buttonTelescopeHome.Name = "buttonTelescopeHome";
            this.buttonTelescopeHome.Size = new System.Drawing.Size(60, 23);
            this.buttonTelescopeHome.TabIndex = 8;
            this.buttonTelescopeHome.Text = "Home";
            this.buttonTelescopeHome.UseVisualStyleBackColor = true;
            this.buttonTelescopeHome.Click += new System.EventHandler(this.buttonTelescopeHome_Click);
            // 
            // buttonTelescopeCalibrate
            // 
            this.buttonTelescopeCalibrate.Location = new System.Drawing.Point(45, 140);
            this.buttonTelescopeCalibrate.Name = "buttonTelescopeCalibrate";
            this.buttonTelescopeCalibrate.Size = new System.Drawing.Size(75, 23);
            this.buttonTelescopeCalibrate.TabIndex = 7;
            this.buttonTelescopeCalibrate.Text = "Calibrate";
            this.buttonTelescopeCalibrate.UseVisualStyleBackColor = true;
            this.buttonTelescopeCalibrate.Click += new System.EventHandler(this.buttonTelescopeCalibrate_Click);
            // 
            // buttonTelescopePark
            // 
            this.buttonTelescopePark.Location = new System.Drawing.Point(80, 110);
            this.buttonTelescopePark.Name = "buttonTelescopePark";
            this.buttonTelescopePark.Size = new System.Drawing.Size(60, 23);
            this.buttonTelescopePark.TabIndex = 6;
            this.buttonTelescopePark.Text = "Park";
            this.buttonTelescopePark.UseVisualStyleBackColor = true;
            this.buttonTelescopePark.Click += new System.EventHandler(this.buttonTelescopePark_Click);
            // 
            // buttonTelescopeSync
            // 
            this.buttonTelescopeSync.Location = new System.Drawing.Point(80, 80);
            this.buttonTelescopeSync.Name = "buttonTelescopeSync";
            this.buttonTelescopeSync.Size = new System.Drawing.Size(60, 23);
            this.buttonTelescopeSync.TabIndex = 5;
            this.buttonTelescopeSync.Text = "Sync";
            this.buttonTelescopeSync.UseVisualStyleBackColor = true;
            this.buttonTelescopeSync.Click += new System.EventHandler(this.buttonTelescopeSync_Click);
            // 
            // buttonTelescopeGoto
            // 
            this.buttonTelescopeGoto.Location = new System.Drawing.Point(10, 80);
            this.buttonTelescopeGoto.Name = "buttonTelescopeGoto";
            this.buttonTelescopeGoto.Size = new System.Drawing.Size(60, 23);
            this.buttonTelescopeGoto.TabIndex = 4;
            this.buttonTelescopeGoto.Text = "Goto";
            this.buttonTelescopeGoto.UseVisualStyleBackColor = true;
            this.buttonTelescopeGoto.Click += new System.EventHandler(this.buttonTelescopeGoto_Click);
            // 
            // numericUpDownTelescopeTargetDEC
            // 
            this.numericUpDownTelescopeTargetDEC.DecimalPlaces = 4;
            this.numericUpDownTelescopeTargetDEC.Location = new System.Drawing.Point(44, 45);
            this.numericUpDownTelescopeTargetDEC.Maximum = new decimal(new int[] {
            900000,
            0,
            0,
            262144});
            this.numericUpDownTelescopeTargetDEC.Minimum = new decimal(new int[] {
            900000,
            0,
            0,
            -2147221504});
            this.numericUpDownTelescopeTargetDEC.Name = "numericUpDownTelescopeTargetDEC";
            this.numericUpDownTelescopeTargetDEC.Size = new System.Drawing.Size(100, 21);
            this.numericUpDownTelescopeTargetDEC.TabIndex = 3;
            // 
            // numericUpDownTelescopeTargetRa
            // 
            this.numericUpDownTelescopeTargetRa.DecimalPlaces = 4;
            this.numericUpDownTelescopeTargetRa.Location = new System.Drawing.Point(44, 15);
            this.numericUpDownTelescopeTargetRa.Maximum = new decimal(new int[] {
            239999,
            0,
            0,
            262144});
            this.numericUpDownTelescopeTargetRa.Name = "numericUpDownTelescopeTargetRa";
            this.numericUpDownTelescopeTargetRa.Size = new System.Drawing.Size(100, 21);
            this.numericUpDownTelescopeTargetRa.TabIndex = 2;
            // 
            // label25
            // 
            this.label25.AutoSize = true;
            this.label25.Location = new System.Drawing.Point(10, 50);
            this.label25.Name = "label25";
            this.label25.Size = new System.Drawing.Size(23, 12);
            this.label25.TabIndex = 1;
            this.label25.Text = "DEC";
            // 
            // label24
            // 
            this.label24.AutoSize = true;
            this.label24.Location = new System.Drawing.Point(10, 20);
            this.label24.Name = "label24";
            this.label24.Size = new System.Drawing.Size(17, 12);
            this.label24.TabIndex = 0;
            this.label24.Text = "RA";
            // 
            // groupBox9
            // 
            this.groupBox9.Controls.Add(this.numericUpDownTelescopeSlewIncrement);
            this.groupBox9.Controls.Add(this.comboBoxTelescopeSlewUnit);
            this.groupBox9.Controls.Add(this.buttonTelesocpeStop);
            this.groupBox9.Controls.Add(this.buttonTelescopeWestward);
            this.groupBox9.Controls.Add(this.buttonTelescopeEastward);
            this.groupBox9.Controls.Add(this.buttonTelescopeSouthward);
            this.groupBox9.Controls.Add(this.buttonTelescopeNorthward);
            this.groupBox9.Location = new System.Drawing.Point(10, 145);
            this.groupBox9.Name = "groupBox9";
            this.groupBox9.Size = new System.Drawing.Size(160, 172);
            this.groupBox9.TabIndex = 0;
            this.groupBox9.TabStop = false;
            this.groupBox9.Text = "Slew";
            // 
            // numericUpDownTelescopeSlewIncrement
            // 
            this.numericUpDownTelescopeSlewIncrement.Location = new System.Drawing.Point(10, 137);
            this.numericUpDownTelescopeSlewIncrement.Maximum = new decimal(new int[] {
            60,
            0,
            0,
            0});
            this.numericUpDownTelescopeSlewIncrement.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.numericUpDownTelescopeSlewIncrement.Name = "numericUpDownTelescopeSlewIncrement";
            this.numericUpDownTelescopeSlewIncrement.Size = new System.Drawing.Size(78, 21);
            this.numericUpDownTelescopeSlewIncrement.TabIndex = 7;
            this.numericUpDownTelescopeSlewIncrement.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // comboBoxTelescopeSlewUnit
            // 
            this.comboBoxTelescopeSlewUnit.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxTelescopeSlewUnit.FormattingEnabled = true;
            this.comboBoxTelescopeSlewUnit.Items.AddRange(new object[] {
            "Sec",
            "Min",
            "Deg"});
            this.comboBoxTelescopeSlewUnit.Location = new System.Drawing.Point(93, 138);
            this.comboBoxTelescopeSlewUnit.Name = "comboBoxTelescopeSlewUnit";
            this.comboBoxTelescopeSlewUnit.Size = new System.Drawing.Size(56, 20);
            this.comboBoxTelescopeSlewUnit.TabIndex = 6;
            // 
            // buttonTelesocpeStop
            // 
            this.buttonTelesocpeStop.Location = new System.Drawing.Point(59, 55);
            this.buttonTelesocpeStop.Name = "buttonTelesocpeStop";
            this.buttonTelesocpeStop.Size = new System.Drawing.Size(40, 40);
            this.buttonTelesocpeStop.TabIndex = 4;
            this.buttonTelesocpeStop.Text = "Stop";
            this.buttonTelesocpeStop.UseVisualStyleBackColor = true;
            this.buttonTelesocpeStop.Click += new System.EventHandler(this.buttonTelesocpeStop_Click);
            // 
            // buttonTelescopeWestward
            // 
            this.buttonTelescopeWestward.Location = new System.Drawing.Point(105, 60);
            this.buttonTelescopeWestward.Name = "buttonTelescopeWestward";
            this.buttonTelescopeWestward.Size = new System.Drawing.Size(30, 30);
            this.buttonTelescopeWestward.TabIndex = 3;
            this.buttonTelescopeWestward.Text = "W";
            this.buttonTelescopeWestward.UseVisualStyleBackColor = true;
            this.buttonTelescopeWestward.Click += new System.EventHandler(this.buttonTelescopeWestward_Click);
            // 
            // buttonTelescopeEastward
            // 
            this.buttonTelescopeEastward.Location = new System.Drawing.Point(23, 60);
            this.buttonTelescopeEastward.Name = "buttonTelescopeEastward";
            this.buttonTelescopeEastward.Size = new System.Drawing.Size(30, 30);
            this.buttonTelescopeEastward.TabIndex = 2;
            this.buttonTelescopeEastward.Text = "E";
            this.buttonTelescopeEastward.UseVisualStyleBackColor = true;
            this.buttonTelescopeEastward.Click += new System.EventHandler(this.buttonTelescopeEastward_Click);
            // 
            // buttonTelescopeSouthward
            // 
            this.buttonTelescopeSouthward.Location = new System.Drawing.Point(64, 101);
            this.buttonTelescopeSouthward.Name = "buttonTelescopeSouthward";
            this.buttonTelescopeSouthward.Size = new System.Drawing.Size(30, 30);
            this.buttonTelescopeSouthward.TabIndex = 1;
            this.buttonTelescopeSouthward.Text = "S";
            this.buttonTelescopeSouthward.UseVisualStyleBackColor = true;
            this.buttonTelescopeSouthward.Click += new System.EventHandler(this.buttonTelescopeSouthward_Click);
            // 
            // buttonTelescopeNorthward
            // 
            this.buttonTelescopeNorthward.Location = new System.Drawing.Point(64, 20);
            this.buttonTelescopeNorthward.Name = "buttonTelescopeNorthward";
            this.buttonTelescopeNorthward.Size = new System.Drawing.Size(30, 30);
            this.buttonTelescopeNorthward.TabIndex = 0;
            this.buttonTelescopeNorthward.Text = "N";
            this.buttonTelescopeNorthward.UseVisualStyleBackColor = true;
            this.buttonTelescopeNorthward.Click += new System.EventHandler(this.buttonTelescopeNorthward_Click);
            // 
            // Dome
            // 
            this.Dome.Controls.Add(this.groupBox6);
            this.Dome.Controls.Add(this.groupBox5);
            this.Dome.Controls.Add(this.groupBox4);
            this.Dome.Location = new System.Drawing.Point(64, 4);
            this.Dome.Name = "Dome";
            this.Dome.Size = new System.Drawing.Size(177, 612);
            this.Dome.TabIndex = 3;
            this.Dome.Text = "Dome";
            this.Dome.UseVisualStyleBackColor = true;
            // 
            // groupBox6
            // 
            this.groupBox6.Controls.Add(this.textBoxDomeState);
            this.groupBox6.Location = new System.Drawing.Point(10, 10);
            this.groupBox6.Name = "groupBox6";
            this.groupBox6.Size = new System.Drawing.Size(160, 140);
            this.groupBox6.TabIndex = 16;
            this.groupBox6.TabStop = false;
            this.groupBox6.Text = "Status";
            // 
            // textBoxDomeState
            // 
            this.textBoxDomeState.Location = new System.Drawing.Point(10, 20);
            this.textBoxDomeState.Margin = new System.Windows.Forms.Padding(2);
            this.textBoxDomeState.Multiline = true;
            this.textBoxDomeState.Name = "textBoxDomeState";
            this.textBoxDomeState.ReadOnly = true;
            this.textBoxDomeState.Size = new System.Drawing.Size(140, 110);
            this.textBoxDomeState.TabIndex = 13;
            this.textBoxDomeState.Text = "Telescope: Not connected\r\nDome: Parked\r\nShutter: Closed\r\nTarget Altitude:\r\nDome A" +
                "ltitude:\r\nTarget Azimuth: \r\nDome Azimuth:\r\n";
            // 
            // groupBox5
            // 
            this.groupBox5.Controls.Add(this.buttonDomeHome);
            this.groupBox5.Controls.Add(this.buttonDomePark);
            this.groupBox5.Controls.Add(this.label1);
            this.groupBox5.Controls.Add(this.buttonDomeAbort);
            this.groupBox5.Controls.Add(this.textBoxAzimuth);
            this.groupBox5.Controls.Add(this.label2);
            this.groupBox5.Controls.Add(this.checkBoxSlaveDome);
            this.groupBox5.Controls.Add(this.textBoxAltitude);
            this.groupBox5.Controls.Add(this.buttonDomeGoto);
            this.groupBox5.Location = new System.Drawing.Point(10, 215);
            this.groupBox5.Name = "groupBox5";
            this.groupBox5.Size = new System.Drawing.Size(160, 160);
            this.groupBox5.TabIndex = 15;
            this.groupBox5.TabStop = false;
            this.groupBox5.Text = "Dome";
            // 
            // buttonDomeHome
            // 
            this.buttonDomeHome.Location = new System.Drawing.Point(80, 75);
            this.buttonDomeHome.Name = "buttonDomeHome";
            this.buttonDomeHome.Size = new System.Drawing.Size(60, 23);
            this.buttonDomeHome.TabIndex = 14;
            this.buttonDomeHome.Text = "Home";
            this.buttonDomeHome.UseVisualStyleBackColor = true;
            // 
            // buttonDomePark
            // 
            this.buttonDomePark.Location = new System.Drawing.Point(80, 105);
            this.buttonDomePark.Name = "buttonDomePark";
            this.buttonDomePark.Size = new System.Drawing.Size(60, 23);
            this.buttonDomePark.TabIndex = 13;
            this.buttonDomePark.Text = "Park";
            this.buttonDomePark.UseVisualStyleBackColor = true;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(10, 20);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(47, 12);
            this.label1.TabIndex = 11;
            this.label1.Text = "Azimuth";
            // 
            // buttonDomeAbort
            // 
            this.buttonDomeAbort.Location = new System.Drawing.Point(10, 105);
            this.buttonDomeAbort.Name = "buttonDomeAbort";
            this.buttonDomeAbort.Size = new System.Drawing.Size(60, 23);
            this.buttonDomeAbort.TabIndex = 10;
            this.buttonDomeAbort.Text = "Abort";
            this.buttonDomeAbort.UseVisualStyleBackColor = true;
            // 
            // textBoxAzimuth
            // 
            this.textBoxAzimuth.Location = new System.Drawing.Point(65, 15);
            this.textBoxAzimuth.Name = "textBoxAzimuth";
            this.textBoxAzimuth.Size = new System.Drawing.Size(86, 21);
            this.textBoxAzimuth.TabIndex = 8;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(10, 50);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(53, 12);
            this.label2.TabIndex = 12;
            this.label2.Text = "Altitude";
            // 
            // checkBoxSlaveDome
            // 
            this.checkBoxSlaveDome.AutoSize = true;
            this.checkBoxSlaveDome.Location = new System.Drawing.Point(12, 135);
            this.checkBoxSlaveDome.Name = "checkBoxSlaveDome";
            this.checkBoxSlaveDome.Size = new System.Drawing.Size(132, 16);
            this.checkBoxSlaveDome.TabIndex = 7;
            this.checkBoxSlaveDome.Text = "Slave to Telescope";
            this.checkBoxSlaveDome.UseVisualStyleBackColor = true;
            this.checkBoxSlaveDome.CheckedChanged += new System.EventHandler(this.checkBoxSlaveDome_CheckedChanged);
            // 
            // textBoxAltitude
            // 
            this.textBoxAltitude.Location = new System.Drawing.Point(65, 45);
            this.textBoxAltitude.Name = "textBoxAltitude";
            this.textBoxAltitude.Size = new System.Drawing.Size(86, 21);
            this.textBoxAltitude.TabIndex = 9;
            // 
            // buttonDomeGoto
            // 
            this.buttonDomeGoto.Location = new System.Drawing.Point(10, 75);
            this.buttonDomeGoto.Name = "buttonDomeGoto";
            this.buttonDomeGoto.Size = new System.Drawing.Size(60, 23);
            this.buttonDomeGoto.TabIndex = 6;
            this.buttonDomeGoto.Text = "Goto";
            this.buttonDomeGoto.UseVisualStyleBackColor = true;
            this.buttonDomeGoto.Click += new System.EventHandler(this.buttonDomeGoto_Click);
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.buttonDomeShutterOpen);
            this.groupBox4.Controls.Add(this.buttonDomeShutterClose);
            this.groupBox4.Location = new System.Drawing.Point(10, 155);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(160, 55);
            this.groupBox4.TabIndex = 14;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "Shutter";
            // 
            // buttonDomeShutterOpen
            // 
            this.buttonDomeShutterOpen.Location = new System.Drawing.Point(10, 20);
            this.buttonDomeShutterOpen.Name = "buttonDomeShutterOpen";
            this.buttonDomeShutterOpen.Size = new System.Drawing.Size(60, 23);
            this.buttonDomeShutterOpen.TabIndex = 4;
            this.buttonDomeShutterOpen.Text = "Open";
            this.buttonDomeShutterOpen.UseVisualStyleBackColor = true;
            this.buttonDomeShutterOpen.Click += new System.EventHandler(this.buttonDomeShutterOpen_Click);
            // 
            // buttonDomeShutterClose
            // 
            this.buttonDomeShutterClose.Location = new System.Drawing.Point(80, 20);
            this.buttonDomeShutterClose.Name = "buttonDomeShutterClose";
            this.buttonDomeShutterClose.Size = new System.Drawing.Size(60, 23);
            this.buttonDomeShutterClose.TabIndex = 5;
            this.buttonDomeShutterClose.Text = "Close";
            this.buttonDomeShutterClose.UseVisualStyleBackColor = true;
            this.buttonDomeShutterClose.Click += new System.EventHandler(this.buttonDomeShutterClose_Click);
            // 
            // Weather
            // 
            this.Weather.Controls.Add(this.groupBoxState);
            this.Weather.Location = new System.Drawing.Point(64, 4);
            this.Weather.Name = "Weather";
            this.Weather.Size = new System.Drawing.Size(177, 612);
            this.Weather.TabIndex = 4;
            this.Weather.Text = "Weather";
            this.Weather.UseVisualStyleBackColor = true;
            // 
            // groupBoxState
            // 
            this.groupBoxState.Controls.Add(this.textBoxWindSpeed);
            this.groupBoxState.Controls.Add(this.label15);
            this.groupBoxState.Controls.Add(this.textBoxWindGust);
            this.groupBoxState.Controls.Add(this.label14);
            this.groupBoxState.Controls.Add(this.textBoxWindDirection);
            this.groupBoxState.Controls.Add(this.label13);
            this.groupBoxState.Controls.Add(this.textBoxTemperature);
            this.groupBoxState.Controls.Add(this.label12);
            this.groupBoxState.Controls.Add(this.textBoxSkyTemperature);
            this.groupBoxState.Controls.Add(this.label11);
            this.groupBoxState.Controls.Add(this.textBoxStarFWHM);
            this.groupBoxState.Controls.Add(this.label10);
            this.groupBoxState.Controls.Add(this.textBoxSkyQuality);
            this.groupBoxState.Controls.Add(this.label9);
            this.groupBoxState.Controls.Add(this.textBoxRainRate);
            this.groupBoxState.Controls.Add(this.label8);
            this.groupBoxState.Controls.Add(this.textBoxPressure);
            this.groupBoxState.Controls.Add(this.label7);
            this.groupBoxState.Controls.Add(this.textBoxHumidity);
            this.groupBoxState.Controls.Add(this.label6);
            this.groupBoxState.Controls.Add(this.textBoxDewPoint);
            this.groupBoxState.Controls.Add(this.label5);
            this.groupBoxState.Controls.Add(this.textBoxCloudCover);
            this.groupBoxState.Controls.Add(this.label3);
            this.groupBoxState.Location = new System.Drawing.Point(10, 10);
            this.groupBoxState.Name = "groupBoxState";
            this.groupBoxState.Size = new System.Drawing.Size(160, 600);
            this.groupBoxState.TabIndex = 2;
            this.groupBoxState.TabStop = false;
            this.groupBoxState.Text = "Observing condition";
            // 
            // textBoxWindSpeed
            // 
            this.textBoxWindSpeed.BackColor = System.Drawing.SystemColors.Highlight;
            this.textBoxWindSpeed.Location = new System.Drawing.Point(10, 475);
            this.textBoxWindSpeed.Name = "textBoxWindSpeed";
            this.textBoxWindSpeed.ReadOnly = true;
            this.textBoxWindSpeed.Size = new System.Drawing.Size(100, 21);
            this.textBoxWindSpeed.TabIndex = 23;
            // 
            // label15
            // 
            this.label15.AutoSize = true;
            this.label15.Location = new System.Drawing.Point(10, 460);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(59, 12);
            this.label15.TabIndex = 22;
            this.label15.Text = "WindSpeed";
            // 
            // textBoxWindGust
            // 
            this.textBoxWindGust.BackColor = System.Drawing.SystemColors.Highlight;
            this.textBoxWindGust.Location = new System.Drawing.Point(10, 435);
            this.textBoxWindGust.Name = "textBoxWindGust";
            this.textBoxWindGust.ReadOnly = true;
            this.textBoxWindGust.Size = new System.Drawing.Size(100, 21);
            this.textBoxWindGust.TabIndex = 21;
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Location = new System.Drawing.Point(10, 420);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(53, 12);
            this.label14.TabIndex = 20;
            this.label14.Text = "WindGust";
            // 
            // textBoxWindDirection
            // 
            this.textBoxWindDirection.BackColor = System.Drawing.SystemColors.Highlight;
            this.textBoxWindDirection.Location = new System.Drawing.Point(10, 395);
            this.textBoxWindDirection.Name = "textBoxWindDirection";
            this.textBoxWindDirection.ReadOnly = true;
            this.textBoxWindDirection.Size = new System.Drawing.Size(100, 21);
            this.textBoxWindDirection.TabIndex = 19;
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(10, 380);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(83, 12);
            this.label13.TabIndex = 18;
            this.label13.Text = "WindDirection";
            // 
            // textBoxTemperature
            // 
            this.textBoxTemperature.BackColor = System.Drawing.SystemColors.Highlight;
            this.textBoxTemperature.Location = new System.Drawing.Point(10, 355);
            this.textBoxTemperature.Name = "textBoxTemperature";
            this.textBoxTemperature.ReadOnly = true;
            this.textBoxTemperature.Size = new System.Drawing.Size(100, 21);
            this.textBoxTemperature.TabIndex = 17;
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(10, 340);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(71, 12);
            this.label12.TabIndex = 16;
            this.label12.Text = "Temperature";
            // 
            // textBoxSkyTemperature
            // 
            this.textBoxSkyTemperature.BackColor = System.Drawing.SystemColors.Highlight;
            this.textBoxSkyTemperature.Location = new System.Drawing.Point(10, 315);
            this.textBoxSkyTemperature.Name = "textBoxSkyTemperature";
            this.textBoxSkyTemperature.ReadOnly = true;
            this.textBoxSkyTemperature.Size = new System.Drawing.Size(100, 21);
            this.textBoxSkyTemperature.TabIndex = 15;
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(10, 300);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(89, 12);
            this.label11.TabIndex = 14;
            this.label11.Text = "SkyTemperature";
            // 
            // textBoxStarFWHM
            // 
            this.textBoxStarFWHM.BackColor = System.Drawing.SystemColors.Highlight;
            this.textBoxStarFWHM.Location = new System.Drawing.Point(10, 275);
            this.textBoxStarFWHM.Name = "textBoxStarFWHM";
            this.textBoxStarFWHM.ReadOnly = true;
            this.textBoxStarFWHM.Size = new System.Drawing.Size(100, 21);
            this.textBoxStarFWHM.TabIndex = 13;
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(10, 260);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(53, 12);
            this.label10.TabIndex = 12;
            this.label10.Text = "StarFWHM";
            // 
            // textBoxSkyQuality
            // 
            this.textBoxSkyQuality.BackColor = System.Drawing.SystemColors.Highlight;
            this.textBoxSkyQuality.Location = new System.Drawing.Point(10, 235);
            this.textBoxSkyQuality.Name = "textBoxSkyQuality";
            this.textBoxSkyQuality.ReadOnly = true;
            this.textBoxSkyQuality.Size = new System.Drawing.Size(100, 21);
            this.textBoxSkyQuality.TabIndex = 11;
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(10, 220);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(65, 12);
            this.label9.TabIndex = 10;
            this.label9.Text = "SkyQuality";
            // 
            // textBoxRainRate
            // 
            this.textBoxRainRate.BackColor = System.Drawing.SystemColors.Highlight;
            this.textBoxRainRate.Location = new System.Drawing.Point(10, 195);
            this.textBoxRainRate.Name = "textBoxRainRate";
            this.textBoxRainRate.ReadOnly = true;
            this.textBoxRainRate.Size = new System.Drawing.Size(100, 21);
            this.textBoxRainRate.TabIndex = 9;
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(10, 180);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(53, 12);
            this.label8.TabIndex = 8;
            this.label8.Text = "RainRate";
            // 
            // textBoxPressure
            // 
            this.textBoxPressure.BackColor = System.Drawing.SystemColors.Highlight;
            this.textBoxPressure.Location = new System.Drawing.Point(10, 155);
            this.textBoxPressure.Name = "textBoxPressure";
            this.textBoxPressure.ReadOnly = true;
            this.textBoxPressure.Size = new System.Drawing.Size(100, 21);
            this.textBoxPressure.TabIndex = 7;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(10, 140);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(53, 12);
            this.label7.TabIndex = 6;
            this.label7.Text = "Pressure";
            // 
            // textBoxHumidity
            // 
            this.textBoxHumidity.BackColor = System.Drawing.SystemColors.Highlight;
            this.textBoxHumidity.Location = new System.Drawing.Point(10, 115);
            this.textBoxHumidity.Name = "textBoxHumidity";
            this.textBoxHumidity.ReadOnly = true;
            this.textBoxHumidity.Size = new System.Drawing.Size(100, 21);
            this.textBoxHumidity.TabIndex = 5;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(10, 100);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(53, 12);
            this.label6.TabIndex = 4;
            this.label6.Text = "Humidity";
            // 
            // textBoxDewPoint
            // 
            this.textBoxDewPoint.BackColor = System.Drawing.SystemColors.Highlight;
            this.textBoxDewPoint.Location = new System.Drawing.Point(10, 75);
            this.textBoxDewPoint.Name = "textBoxDewPoint";
            this.textBoxDewPoint.ReadOnly = true;
            this.textBoxDewPoint.Size = new System.Drawing.Size(100, 21);
            this.textBoxDewPoint.TabIndex = 3;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(10, 60);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(53, 12);
            this.label5.TabIndex = 2;
            this.label5.Text = "DewPoint";
            // 
            // textBoxCloudCover
            // 
            this.textBoxCloudCover.BackColor = System.Drawing.SystemColors.Highlight;
            this.textBoxCloudCover.Location = new System.Drawing.Point(10, 35);
            this.textBoxCloudCover.Name = "textBoxCloudCover";
            this.textBoxCloudCover.ReadOnly = true;
            this.textBoxCloudCover.Size = new System.Drawing.Size(100, 21);
            this.textBoxCloudCover.TabIndex = 1;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(10, 20);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(65, 12);
            this.label3.TabIndex = 0;
            this.label3.Text = "CloudCover";
            // 
            // Setup
            // 
            this.Setup.Controls.Add(this.groupBoxSwitch);
            this.Setup.Controls.Add(this.groupBoxWhether);
            this.Setup.Controls.Add(this.groupBoxFilter);
            this.Setup.Controls.Add(this.groupBoxFocuser);
            this.Setup.Controls.Add(this.groupBoxDome);
            this.Setup.Controls.Add(this.groupBoxTelescope);
            this.Setup.Controls.Add(this.groupBoxCamera);
            this.Setup.Location = new System.Drawing.Point(64, 4);
            this.Setup.Name = "Setup";
            this.Setup.Size = new System.Drawing.Size(177, 612);
            this.Setup.TabIndex = 7;
            this.Setup.Text = "Setup";
            this.Setup.UseVisualStyleBackColor = true;
            // 
            // groupBoxSwitch
            // 
            this.groupBoxSwitch.Controls.Add(this.textBoxSwitchID);
            this.groupBoxSwitch.Controls.Add(this.buttonConnectSwitch);
            this.groupBoxSwitch.Controls.Add(this.buttonChooseSwitch);
            this.groupBoxSwitch.Location = new System.Drawing.Point(10, 490);
            this.groupBoxSwitch.Name = "groupBoxSwitch";
            this.groupBoxSwitch.Size = new System.Drawing.Size(160, 75);
            this.groupBoxSwitch.TabIndex = 3;
            this.groupBoxSwitch.TabStop = false;
            this.groupBoxSwitch.Text = "Switch";
            // 
            // textBoxSwitchID
            // 
            this.textBoxSwitchID.Location = new System.Drawing.Point(10, 20);
            this.textBoxSwitchID.Name = "textBoxSwitchID";
            this.textBoxSwitchID.ReadOnly = true;
            this.textBoxSwitchID.Size = new System.Drawing.Size(140, 21);
            this.textBoxSwitchID.TabIndex = 2;
            // 
            // buttonConnectSwitch
            // 
            this.buttonConnectSwitch.Location = new System.Drawing.Point(70, 45);
            this.buttonConnectSwitch.Name = "buttonConnectSwitch";
            this.buttonConnectSwitch.Size = new System.Drawing.Size(80, 23);
            this.buttonConnectSwitch.TabIndex = 1;
            this.buttonConnectSwitch.Text = "Connect";
            this.buttonConnectSwitch.UseVisualStyleBackColor = true;
            this.buttonConnectSwitch.Click += new System.EventHandler(this.buttonConnectSwitch_Click);
            // 
            // buttonChooseSwitch
            // 
            this.buttonChooseSwitch.Location = new System.Drawing.Point(10, 45);
            this.buttonChooseSwitch.Name = "buttonChooseSwitch";
            this.buttonChooseSwitch.Size = new System.Drawing.Size(60, 23);
            this.buttonChooseSwitch.TabIndex = 0;
            this.buttonChooseSwitch.Text = "Choose";
            this.buttonChooseSwitch.UseVisualStyleBackColor = true;
            this.buttonChooseSwitch.Click += new System.EventHandler(this.buttonChooseSwitch_Click);
            // 
            // groupBoxWhether
            // 
            this.groupBoxWhether.Controls.Add(this.textBoxObsConditionsID);
            this.groupBoxWhether.Controls.Add(this.buttonConnectObsConditions);
            this.groupBoxWhether.Controls.Add(this.buttonChooseObsConditions);
            this.groupBoxWhether.Location = new System.Drawing.Point(10, 410);
            this.groupBoxWhether.Name = "groupBoxWhether";
            this.groupBoxWhether.Size = new System.Drawing.Size(160, 75);
            this.groupBoxWhether.TabIndex = 5;
            this.groupBoxWhether.TabStop = false;
            this.groupBoxWhether.Text = "Whether";
            // 
            // textBoxObsConditionsID
            // 
            this.textBoxObsConditionsID.Location = new System.Drawing.Point(10, 20);
            this.textBoxObsConditionsID.Name = "textBoxObsConditionsID";
            this.textBoxObsConditionsID.ReadOnly = true;
            this.textBoxObsConditionsID.Size = new System.Drawing.Size(140, 21);
            this.textBoxObsConditionsID.TabIndex = 2;
            // 
            // buttonConnectObsConditions
            // 
            this.buttonConnectObsConditions.Location = new System.Drawing.Point(70, 45);
            this.buttonConnectObsConditions.Name = "buttonConnectObsConditions";
            this.buttonConnectObsConditions.Size = new System.Drawing.Size(80, 23);
            this.buttonConnectObsConditions.TabIndex = 1;
            this.buttonConnectObsConditions.Text = "Connect";
            this.buttonConnectObsConditions.UseVisualStyleBackColor = true;
            this.buttonConnectObsConditions.Click += new System.EventHandler(this.buttonConnectObsConditions_Click);
            // 
            // buttonChooseObsConditions
            // 
            this.buttonChooseObsConditions.Location = new System.Drawing.Point(10, 45);
            this.buttonChooseObsConditions.Name = "buttonChooseObsConditions";
            this.buttonChooseObsConditions.Size = new System.Drawing.Size(60, 23);
            this.buttonChooseObsConditions.TabIndex = 0;
            this.buttonChooseObsConditions.Text = "Choose";
            this.buttonChooseObsConditions.UseVisualStyleBackColor = true;
            this.buttonChooseObsConditions.Click += new System.EventHandler(this.buttonChooseObsConditions_Click);
            // 
            // groupBoxFilter
            // 
            this.groupBoxFilter.Controls.Add(this.textBoxFilterWheelID);
            this.groupBoxFilter.Controls.Add(this.buttonConnectFilterWheel);
            this.groupBoxFilter.Controls.Add(this.buttonChooseFilterWheel);
            this.groupBoxFilter.Location = new System.Drawing.Point(10, 250);
            this.groupBoxFilter.Name = "groupBoxFilter";
            this.groupBoxFilter.Size = new System.Drawing.Size(160, 75);
            this.groupBoxFilter.TabIndex = 4;
            this.groupBoxFilter.TabStop = false;
            this.groupBoxFilter.Text = "Filter";
            // 
            // textBoxFilterWheelID
            // 
            this.textBoxFilterWheelID.Location = new System.Drawing.Point(10, 20);
            this.textBoxFilterWheelID.Name = "textBoxFilterWheelID";
            this.textBoxFilterWheelID.ReadOnly = true;
            this.textBoxFilterWheelID.Size = new System.Drawing.Size(140, 21);
            this.textBoxFilterWheelID.TabIndex = 2;
            // 
            // buttonConnectFilterWheel
            // 
            this.buttonConnectFilterWheel.Location = new System.Drawing.Point(70, 45);
            this.buttonConnectFilterWheel.Name = "buttonConnectFilterWheel";
            this.buttonConnectFilterWheel.Size = new System.Drawing.Size(80, 23);
            this.buttonConnectFilterWheel.TabIndex = 1;
            this.buttonConnectFilterWheel.Text = "Connect";
            this.buttonConnectFilterWheel.UseVisualStyleBackColor = true;
            this.buttonConnectFilterWheel.Click += new System.EventHandler(this.buttonConnectFilterWheel_Click);
            // 
            // buttonChooseFilterWheel
            // 
            this.buttonChooseFilterWheel.Location = new System.Drawing.Point(10, 45);
            this.buttonChooseFilterWheel.Name = "buttonChooseFilterWheel";
            this.buttonChooseFilterWheel.Size = new System.Drawing.Size(60, 23);
            this.buttonChooseFilterWheel.TabIndex = 0;
            this.buttonChooseFilterWheel.Text = "Choose";
            this.buttonChooseFilterWheel.UseVisualStyleBackColor = true;
            this.buttonChooseFilterWheel.Click += new System.EventHandler(this.buttonChooseFilterWheel_Click);
            // 
            // groupBoxFocuser
            // 
            this.groupBoxFocuser.Controls.Add(this.textBoxFocuserID);
            this.groupBoxFocuser.Controls.Add(this.buttonConnectFocuser);
            this.groupBoxFocuser.Controls.Add(this.buttonChooseFocuser);
            this.groupBoxFocuser.Location = new System.Drawing.Point(10, 330);
            this.groupBoxFocuser.Name = "groupBoxFocuser";
            this.groupBoxFocuser.Size = new System.Drawing.Size(160, 75);
            this.groupBoxFocuser.TabIndex = 3;
            this.groupBoxFocuser.TabStop = false;
            this.groupBoxFocuser.Text = "Focuser";
            // 
            // textBoxFocuserID
            // 
            this.textBoxFocuserID.Location = new System.Drawing.Point(10, 20);
            this.textBoxFocuserID.Name = "textBoxFocuserID";
            this.textBoxFocuserID.ReadOnly = true;
            this.textBoxFocuserID.Size = new System.Drawing.Size(140, 21);
            this.textBoxFocuserID.TabIndex = 2;
            // 
            // buttonConnectFocuser
            // 
            this.buttonConnectFocuser.Location = new System.Drawing.Point(70, 45);
            this.buttonConnectFocuser.Name = "buttonConnectFocuser";
            this.buttonConnectFocuser.Size = new System.Drawing.Size(80, 23);
            this.buttonConnectFocuser.TabIndex = 1;
            this.buttonConnectFocuser.Text = "Connect";
            this.buttonConnectFocuser.UseVisualStyleBackColor = true;
            this.buttonConnectFocuser.Click += new System.EventHandler(this.buttonConnectFocuser_Click);
            // 
            // buttonChooseFocuser
            // 
            this.buttonChooseFocuser.Location = new System.Drawing.Point(10, 45);
            this.buttonChooseFocuser.Name = "buttonChooseFocuser";
            this.buttonChooseFocuser.Size = new System.Drawing.Size(60, 23);
            this.buttonChooseFocuser.TabIndex = 0;
            this.buttonChooseFocuser.Text = "Choose";
            this.buttonChooseFocuser.UseVisualStyleBackColor = true;
            this.buttonChooseFocuser.Click += new System.EventHandler(this.buttonChooseFocuser_Click);
            // 
            // groupBoxDome
            // 
            this.groupBoxDome.Controls.Add(this.textBoxDomeID);
            this.groupBoxDome.Controls.Add(this.buttonConnectDome);
            this.groupBoxDome.Controls.Add(this.buttonChooseDome);
            this.groupBoxDome.Location = new System.Drawing.Point(10, 10);
            this.groupBoxDome.Name = "groupBoxDome";
            this.groupBoxDome.Size = new System.Drawing.Size(160, 75);
            this.groupBoxDome.TabIndex = 3;
            this.groupBoxDome.TabStop = false;
            this.groupBoxDome.Text = "Dome";
            // 
            // textBoxDomeID
            // 
            this.textBoxDomeID.Location = new System.Drawing.Point(10, 20);
            this.textBoxDomeID.Name = "textBoxDomeID";
            this.textBoxDomeID.ReadOnly = true;
            this.textBoxDomeID.Size = new System.Drawing.Size(140, 21);
            this.textBoxDomeID.TabIndex = 2;
            // 
            // buttonConnectDome
            // 
            this.buttonConnectDome.Location = new System.Drawing.Point(70, 45);
            this.buttonConnectDome.Name = "buttonConnectDome";
            this.buttonConnectDome.Size = new System.Drawing.Size(80, 23);
            this.buttonConnectDome.TabIndex = 1;
            this.buttonConnectDome.Text = "Connect";
            this.buttonConnectDome.UseVisualStyleBackColor = true;
            this.buttonConnectDome.Click += new System.EventHandler(this.buttonConnectDome_Click);
            // 
            // buttonChooseDome
            // 
            this.buttonChooseDome.Location = new System.Drawing.Point(10, 45);
            this.buttonChooseDome.Name = "buttonChooseDome";
            this.buttonChooseDome.Size = new System.Drawing.Size(60, 23);
            this.buttonChooseDome.TabIndex = 0;
            this.buttonChooseDome.Text = "Choose";
            this.buttonChooseDome.UseVisualStyleBackColor = true;
            this.buttonChooseDome.Click += new System.EventHandler(this.buttonChooseDome_Click);
            // 
            // groupBoxTelescope
            // 
            this.groupBoxTelescope.Controls.Add(this.textBoxTelescopeID);
            this.groupBoxTelescope.Controls.Add(this.buttonConnectTelescope);
            this.groupBoxTelescope.Controls.Add(this.buttonChooseTelescope);
            this.groupBoxTelescope.Location = new System.Drawing.Point(10, 90);
            this.groupBoxTelescope.Name = "groupBoxTelescope";
            this.groupBoxTelescope.Size = new System.Drawing.Size(160, 75);
            this.groupBoxTelescope.TabIndex = 3;
            this.groupBoxTelescope.TabStop = false;
            this.groupBoxTelescope.Text = "Telescope";
            // 
            // textBoxTelescopeID
            // 
            this.textBoxTelescopeID.Location = new System.Drawing.Point(10, 20);
            this.textBoxTelescopeID.Name = "textBoxTelescopeID";
            this.textBoxTelescopeID.ReadOnly = true;
            this.textBoxTelescopeID.Size = new System.Drawing.Size(140, 21);
            this.textBoxTelescopeID.TabIndex = 2;
            // 
            // buttonConnectTelescope
            // 
            this.buttonConnectTelescope.Location = new System.Drawing.Point(70, 45);
            this.buttonConnectTelescope.Name = "buttonConnectTelescope";
            this.buttonConnectTelescope.Size = new System.Drawing.Size(80, 23);
            this.buttonConnectTelescope.TabIndex = 1;
            this.buttonConnectTelescope.Text = "Connect";
            this.buttonConnectTelescope.UseVisualStyleBackColor = true;
            this.buttonConnectTelescope.Click += new System.EventHandler(this.buttonConnectTelescope_Click);
            // 
            // buttonChooseTelescope
            // 
            this.buttonChooseTelescope.Location = new System.Drawing.Point(10, 45);
            this.buttonChooseTelescope.Name = "buttonChooseTelescope";
            this.buttonChooseTelescope.Size = new System.Drawing.Size(60, 23);
            this.buttonChooseTelescope.TabIndex = 0;
            this.buttonChooseTelescope.Text = "Choose";
            this.buttonChooseTelescope.UseVisualStyleBackColor = true;
            this.buttonChooseTelescope.Click += new System.EventHandler(this.buttonChooseTelescope_Click);
            // 
            // groupBoxCamera
            // 
            this.groupBoxCamera.Controls.Add(this.textBoxCameraID);
            this.groupBoxCamera.Controls.Add(this.buttonConnectCamera);
            this.groupBoxCamera.Controls.Add(this.buttonChooseCamera);
            this.groupBoxCamera.Location = new System.Drawing.Point(10, 170);
            this.groupBoxCamera.Name = "groupBoxCamera";
            this.groupBoxCamera.Size = new System.Drawing.Size(160, 75);
            this.groupBoxCamera.TabIndex = 0;
            this.groupBoxCamera.TabStop = false;
            this.groupBoxCamera.Text = "Camera";
            // 
            // textBoxCameraID
            // 
            this.textBoxCameraID.Location = new System.Drawing.Point(10, 20);
            this.textBoxCameraID.Name = "textBoxCameraID";
            this.textBoxCameraID.ReadOnly = true;
            this.textBoxCameraID.Size = new System.Drawing.Size(140, 21);
            this.textBoxCameraID.TabIndex = 2;
            // 
            // buttonConnectCamera
            // 
            this.buttonConnectCamera.Location = new System.Drawing.Point(70, 45);
            this.buttonConnectCamera.Name = "buttonConnectCamera";
            this.buttonConnectCamera.Size = new System.Drawing.Size(80, 23);
            this.buttonConnectCamera.TabIndex = 1;
            this.buttonConnectCamera.Text = "Connect";
            this.buttonConnectCamera.UseVisualStyleBackColor = true;
            this.buttonConnectCamera.Click += new System.EventHandler(this.buttonConnectCamera_Click);
            // 
            // buttonChooseCamera
            // 
            this.buttonChooseCamera.Location = new System.Drawing.Point(10, 45);
            this.buttonChooseCamera.Name = "buttonChooseCamera";
            this.buttonChooseCamera.Size = new System.Drawing.Size(60, 23);
            this.buttonChooseCamera.TabIndex = 0;
            this.buttonChooseCamera.Text = "Choose";
            this.buttonChooseCamera.UseVisualStyleBackColor = true;
            this.buttonChooseCamera.Click += new System.EventHandler(this.buttonChooseCamera_Click);
            // 
            // pictureBox1
            // 
            this.pictureBox1.Location = new System.Drawing.Point(246, 0);
            this.pictureBox1.Margin = new System.Windows.Forms.Padding(2);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(760, 620);
            this.pictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.pictureBox1.TabIndex = 3;
            this.pictureBox1.TabStop = false;
            // 
            // label27
            // 
            this.label27.AutoSize = true;
            this.label27.Location = new System.Drawing.Point(6, 17);
            this.label27.Name = "label27";
            this.label27.Size = new System.Drawing.Size(17, 12);
            this.label27.TabIndex = 4;
            this.label27.Text = "RA";
            // 
            // groupBox13
            // 
            this.groupBox13.Controls.Add(this.label28);
            this.groupBox13.Controls.Add(this.label27);
            this.groupBox13.Location = new System.Drawing.Point(10, 10);
            this.groupBox13.Name = "groupBox13";
            this.groupBox13.Size = new System.Drawing.Size(160, 100);
            this.groupBox13.TabIndex = 0;
            this.groupBox13.TabStop = false;
            this.groupBox13.Text = "Targret";
            // 
            // label28
            // 
            this.label28.AutoSize = true;
            this.label28.Location = new System.Drawing.Point(6, 40);
            this.label28.Name = "label28";
            this.label28.Size = new System.Drawing.Size(23, 12);
            this.label28.TabIndex = 5;
            this.label28.Text = "DEC";
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(46, 196);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 1;
            this.button1.Text = "button1";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1008, 622);
            this.Controls.Add(this.pictureBox1);
            this.Controls.Add(this.tabControl1);
            this.Name = "MainForm";
            this.Text = "CAO Observatory Control Software";
            this.tabControl1.ResumeLayout(false);
            this.Observe.ResumeLayout(false);
            this.Camera.ResumeLayout(false);
            this.groupBox8.ResumeLayout(false);
            this.groupBox8.PerformLayout();
            this.groupBox7.ResumeLayout(false);
            this.groupBox7.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownExposeTime)).EndInit();
            this.Focuser.ResumeLayout(false);
            this.Focuser.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.Telescope.ResumeLayout(false);
            this.groupBox12.ResumeLayout(false);
            this.groupBox12.PerformLayout();
            this.groupBox11.ResumeLayout(false);
            this.groupBox10.ResumeLayout(false);
            this.groupBox10.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownTelescopeTargetDEC)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownTelescopeTargetRa)).EndInit();
            this.groupBox9.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownTelescopeSlewIncrement)).EndInit();
            this.Dome.ResumeLayout(false);
            this.groupBox6.ResumeLayout(false);
            this.groupBox6.PerformLayout();
            this.groupBox5.ResumeLayout(false);
            this.groupBox5.PerformLayout();
            this.groupBox4.ResumeLayout(false);
            this.Weather.ResumeLayout(false);
            this.groupBoxState.ResumeLayout(false);
            this.groupBoxState.PerformLayout();
            this.Setup.ResumeLayout(false);
            this.groupBoxSwitch.ResumeLayout(false);
            this.groupBoxSwitch.PerformLayout();
            this.groupBoxWhether.ResumeLayout(false);
            this.groupBoxWhether.PerformLayout();
            this.groupBoxFilter.ResumeLayout(false);
            this.groupBoxFilter.PerformLayout();
            this.groupBoxFocuser.ResumeLayout(false);
            this.groupBoxFocuser.PerformLayout();
            this.groupBoxDome.ResumeLayout(false);
            this.groupBoxDome.PerformLayout();
            this.groupBoxTelescope.ResumeLayout(false);
            this.groupBoxTelescope.PerformLayout();
            this.groupBoxCamera.ResumeLayout(false);
            this.groupBoxCamera.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.groupBox13.ResumeLayout(false);
            this.groupBox13.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage Telescope;
        private System.Windows.Forms.TabPage Camera;
        private System.Windows.Forms.TabPage Focuser;
        private System.Windows.Forms.TabPage Dome;
        private System.Windows.Forms.TabPage Weather;
        private System.Windows.Forms.Button buttonDomeShutterOpen;
        private System.Windows.Forms.Button buttonDomeShutterClose;
        private System.Windows.Forms.GroupBox groupBoxState;
        private System.Windows.Forms.TabPage Setup;
        private System.Windows.Forms.GroupBox groupBoxCamera;
        private System.Windows.Forms.GroupBox groupBoxSwitch;
        private System.Windows.Forms.TextBox textBoxSwitchID;
        private System.Windows.Forms.Button buttonConnectSwitch;
        private System.Windows.Forms.Button buttonChooseSwitch;
        private System.Windows.Forms.GroupBox groupBoxWhether;
        private System.Windows.Forms.TextBox textBoxObsConditionsID;
        private System.Windows.Forms.Button buttonConnectObsConditions;
        private System.Windows.Forms.Button buttonChooseObsConditions;
        private System.Windows.Forms.GroupBox groupBoxFilter;
        private System.Windows.Forms.TextBox textBoxFilterWheelID;
        private System.Windows.Forms.Button buttonConnectFilterWheel;
        private System.Windows.Forms.Button buttonChooseFilterWheel;
        private System.Windows.Forms.GroupBox groupBoxFocuser;
        private System.Windows.Forms.TextBox textBoxFocuserID;
        private System.Windows.Forms.Button buttonConnectFocuser;
        private System.Windows.Forms.Button buttonChooseFocuser;
        private System.Windows.Forms.GroupBox groupBoxDome;
        private System.Windows.Forms.TextBox textBoxDomeID;
        private System.Windows.Forms.Button buttonConnectDome;
        private System.Windows.Forms.Button buttonChooseDome;
        private System.Windows.Forms.GroupBox groupBoxTelescope;
        private System.Windows.Forms.TextBox textBoxTelescopeID;
        private System.Windows.Forms.Button buttonConnectTelescope;
        private System.Windows.Forms.Button buttonChooseTelescope;
        private System.Windows.Forms.TextBox textBoxCameraID;
        private System.Windows.Forms.Button buttonConnectCamera;
        private System.Windows.Forms.Button buttonChooseCamera;
        private System.Windows.Forms.Button buttonDomeAbort;
        private System.Windows.Forms.TextBox textBoxAltitude;
        private System.Windows.Forms.TextBox textBoxAzimuth;
        private System.Windows.Forms.CheckBox checkBoxSlaveDome;
        private System.Windows.Forms.Button buttonDomeGoto;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox textBoxDomeState;
        private System.Windows.Forms.Button buttonFocuserMoveTo;
        private System.Windows.Forms.TextBox textBoxFocuserStatus;
        private System.Windows.Forms.TextBox textBoxFocuserPosition;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Button buttonCameraStartExpose;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.TabPage Observe;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Button buttonFocuserMoveOut;
        private System.Windows.Forms.Button buttonFocuserMoveIn;
        private System.Windows.Forms.TextBox textBoxFocuserIncrement;
        private System.Windows.Forms.TextBox textBoxFocuserPositionMoveTo;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.TextBox textBoxFocuserType;
        private System.Windows.Forms.Label label18;
        private System.Windows.Forms.TextBox textBoxFocuserTemperature;
        private System.Windows.Forms.Label label17;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.CheckBox checkBoxFocuserBCOut;
        private System.Windows.Forms.CheckBox checkBoxFocuserBCEnabled;
        private System.Windows.Forms.Label label20;
        private System.Windows.Forms.TextBox textBoxFocuserBCSteps;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.GroupBox groupBox6;
        private System.Windows.Forms.GroupBox groupBox5;
        private System.Windows.Forms.Button buttonDomeHome;
        private System.Windows.Forms.Button buttonDomePark;
        private System.Windows.Forms.GroupBox groupBox7;
        private System.Windows.Forms.GroupBox groupBox8;
        private System.Windows.Forms.Label label23;
        private System.Windows.Forms.Label label22;
        private System.Windows.Forms.ComboBox comboBoxBinY;
        private System.Windows.Forms.ComboBox comboBoxBinX;
        private System.Windows.Forms.Button buttonCameraStopExpose;
        private System.Windows.Forms.Label label21;
        private System.Windows.Forms.ComboBox comboBoxFilter;
        private System.Windows.Forms.Label label19;
        private System.Windows.Forms.ComboBox comboBoxFrame;
        private System.Windows.Forms.GroupBox groupBox11;
        private System.Windows.Forms.Button buttonTelescopeLimit;
        private System.Windows.Forms.Button buttonTelescopeSite;
        private System.Windows.Forms.GroupBox groupBox10;
        private System.Windows.Forms.Label label25;
        private System.Windows.Forms.Label label24;
        private System.Windows.Forms.GroupBox groupBox9;
        private System.Windows.Forms.ComboBox comboBoxTelescopeSlewUnit;
        private System.Windows.Forms.Button buttonTelesocpeStop;
        private System.Windows.Forms.Button buttonTelescopeWestward;
        private System.Windows.Forms.Button buttonTelescopeEastward;
        private System.Windows.Forms.Button buttonTelescopeSouthward;
        private System.Windows.Forms.Button buttonTelescopeNorthward;
        private System.Windows.Forms.Button buttonTelescopeSync;
        private System.Windows.Forms.Button buttonTelescopeGoto;
        private System.Windows.Forms.NumericUpDown numericUpDownTelescopeTargetDEC;
        private System.Windows.Forms.NumericUpDown numericUpDownTelescopeTargetRa;
        private System.Windows.Forms.NumericUpDown numericUpDownTelescopeSlewIncrement;
        private System.Windows.Forms.GroupBox groupBox12;
        private System.Windows.Forms.Button buttonTelescopeCalibrate;
        private System.Windows.Forms.Button buttonTelescopePark;
        private System.Windows.Forms.TextBox textBoxCameraFilterStatus;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox textBoxCloudCover;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.TextBox textBoxDewPoint;
        private System.Windows.Forms.TextBox textBoxHumidity;
        private System.Windows.Forms.TextBox textBoxPressure;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.TextBox textBoxRainRate;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.TextBox textBoxSkyQuality;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.TextBox textBoxStarFWHM;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.TextBox textBoxSkyTemperature;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.TextBox textBoxTemperature;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.TextBox textBoxWindDirection;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.TextBox textBoxWindGust;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.TextBox textBoxWindSpeed;
        private System.Windows.Forms.Label label15;
        private System.Windows.Forms.NumericUpDown numericUpDownExposeTime;
        private System.Windows.Forms.Label label16;
        private System.Windows.Forms.ComboBox comboBoxMode;
        private System.Windows.Forms.Label label26;
        private System.Windows.Forms.Button buttonTelescopeHome;
        private System.Windows.Forms.Button buttonCameraAutoSave;
        private System.Windows.Forms.Button buttonFocuserAbort;
        private System.Windows.Forms.TextBox textBoxTelescopeStatus;
        private System.Windows.Forms.GroupBox groupBox13;
        private System.Windows.Forms.Label label28;
        private System.Windows.Forms.Label label27;
        private System.Windows.Forms.Button button1;
    }
}

