using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;

namespace CAO
{
    static class Program
    {
        /// <summary>
        /// 应用程序的主入口点。
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            //Application.Run(new MainForm());

            //禁止开启多个实例
            bool createdNew; 
            System.Threading.Mutex instance = new System.Threading.Mutex(true, "CAO", out createdNew); 
            if (createdNew) 
            {
                Application.Run(new MainForm());
                instance.ReleaseMutex();
            }
            else
            {
                MessageBox.Show("程序已经启动，无需重复开启！", "温馨提示", MessageBoxButtons.OK, MessageBoxIcon.Error);
                Application.Exit();
            } 
        }
    }
}
