using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace ASCOM.SSFocuser
{
    public partial class CoverSetting : Form
    {
        public CoverSetting()
        {
            InitializeComponent();
            //textBoxOpenCode.Text = Focuser.m_OpenCoverCode.ToString();
            //textBoxCloseCode.Text = Focuser.m_CloseCoverCode.ToString ();
        }

        private void cmdOK_Click(object sender, EventArgs e)
        {
            UInt16 OpenCode = Convert.ToUInt16(textBoxOpenCode.Text);
            UInt16 CloseCode = Convert.ToUInt16(textBoxCloseCode.Text);
            /*
            if ((OpenCode > 0) && (CloseCode > 0))
            {
                Focuser.m_OpenCoverCode = Convert.ToUInt16(textBoxOpenCode.Text);
                Focuser.m_CloseCoverCode = Convert.ToUInt16(textBoxCloseCode.Text);
            }
            else
                MessageBox.Show("Invalid input data");
             */
        }
    }
}
