using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace CAO
{
    public partial class ObservationTasks : Form
    {
        public ObservationTasks()
        {
            InitializeComponent();
            SSXml XmlObject = new SSXml();
            //XmlObject.CreatXmlFileObsv();
            int count = XmlObject.GetCount();
            tableLayoutPanelObsTasks.ColumnCount = 11;
            tableLayoutPanelObsTasks.RowCount = count;

            
            string[] tmpstr = new string[count];
            tmpstr=XmlObject.GetExposureElement();
            //MessageBox.Show(count.ToString());
            for (int i = 0; i < count; i++)
            {
                TextBox txt0 = new TextBox();
                txt0.Enabled = false;
                txt0.Text = i.ToString() ;
                tableLayoutPanelObsTasks.Controls.Add(txt0, 0, i);
                TextBox txt1 = new TextBox();
                txt1.Text = tmpstr[i * 8 + 0];
                tableLayoutPanelObsTasks.Controls.Add(txt1, 1, i);
                TextBox txt2 = new TextBox();
                txt2.Text = tmpstr[i * 8 + 1];
                tableLayoutPanelObsTasks.Controls.Add(txt2, 2, i);
                TextBox txt3 = new TextBox();
                txt3.Text = tmpstr[i * 8 + 2];
                tableLayoutPanelObsTasks.Controls.Add(txt3, 3, i);
                TextBox txt4 = new TextBox();
                txt4.Text = tmpstr[i * 8 + 3];
                tableLayoutPanelObsTasks.Controls.Add(txt4, 4, i);
                TextBox txt5 = new TextBox();
                txt5.Text = tmpstr[i * 8 + 4];
                tableLayoutPanelObsTasks.Controls.Add(txt5, 5, i); 
                TextBox txt6 = new TextBox();
                txt6.Text = tmpstr[i * 8 + 5];
                tableLayoutPanelObsTasks.Controls.Add(txt6, 6, i);
                TextBox txt7 = new TextBox();
                txt7.Text = tmpstr[i * 8 + 6];
                tableLayoutPanelObsTasks.Controls.Add(txt7, 7, i);
                TextBox txt8 = new TextBox();
                txt8.Text = tmpstr[i * 8 + 7];
                tableLayoutPanelObsTasks.Controls.Add(txt8, 8, i);
                Button btn9 = new Button();
                //btn9.Height = 23;
                btn9.Text = "Edit";
                tableLayoutPanelObsTasks.Controls.Add(btn9, 9, i);
                Button btn10 = new Button();
                //btn10.Height = 23;
                btn10.Text = "Dele";
                tableLayoutPanelObsTasks.Controls.Add(btn10, 10, i);
            }
            XmlObject.Dispose();
        }

        private void button1_Click(object sender, EventArgs e)
        {

        }

        private void button2_Click(object sender, EventArgs e)
        {

        }
    }
}
