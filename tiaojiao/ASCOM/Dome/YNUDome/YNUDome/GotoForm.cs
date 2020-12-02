using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace ASCOM.YNUDome
{
    public partial class GotoForm : Form
    {
        Dome MyDome;// 
        public GotoForm(Dome f)
        {
            MyDome = f;
            InitializeComponent();
            numericUpDownAzimuth.Value = (decimal)MyDome.Azimuth;
            if (MyDome.CanSetAltitude)
                numericUpDownAltitude.Value = (decimal)MyDome.Altitude;
            else
                numericUpDownAltitude.Enabled = false;
        }

        private void buttonGotoOK_Click(object sender, EventArgs e)
        {
            Dome.AzimuthGoto = Convert.ToDouble( numericUpDownAzimuth.Value );
            if(MyDome.CanSetAltitude)
                Dome.AltitudeGoto = Convert.ToDouble(numericUpDownAltitude.Value);
        }

        private void buttonGotoCancel_Click(object sender, EventArgs e)
        {
            Close();
        }
    }
}
