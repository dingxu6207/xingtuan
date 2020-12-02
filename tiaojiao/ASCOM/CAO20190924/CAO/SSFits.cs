using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using System.IO;
using System.Drawing;
using System.Drawing.Imaging;
using System.Windows.Forms;

using nom.tam.fits;
using nom.tam.image;
using nom.tam.util;

namespace CAO
{
    public class SSFits
    {
        public SSFits()
        { 
        }
        public void Dispose()
        {
        }
        public string OpenFile()
        {
            OpenFileDialog file_path = new OpenFileDialog(); //创建选择文件窗口的类

            file_path.Multiselect = true;  //是否允许选择多个文件

            file_path.Title = "请选择文件";  //文件框的标题

            file_path.Filter = "全部文件|*.*";  //设置文件后缀(当前为所有文件)

            if (file_path.ShowDialog() == DialogResult.OK)   //选择对话框中的确定和取消按钮
            {
                return file_path.FileName;  //把选择文件的路径复制给txtbox;
            }
            else
                return "";
        }
        public string FilePath()
        {
            FolderBrowserDialog new_file_path = new FolderBrowserDialog();  //浏览文件夹的方法的类

            new_file_path.Description = "请选择文件存储路径";  //文件框的标题

            if (new_file_path.ShowDialog() == DialogResult.OK)  //如果单机窗口的确定按钮
            {

                return new_file_path.SelectedPath;  //把选定的路径传给txtbox
            }
            else
                return "";
        }
        // Make FITS file
        public void MakeFile(string FileName, byte[][] ImgArray)
        {
            //Create a FITS file from an image:
            Fits f = new Fits();
            //BasicHDU h = FitsFactory.HDUFactory(ImgArray);
            BasicHDU h = Fits.MakeHDU(ImgArray);
            Header hdr = h.Header;
            //添加关键字
            hdr.AddValue("OBS2", "hss", "Observer");
            f.AddHDU(h);
            BufferedDataStream bf = new BufferedDataStream(new FileStream(FileName, FileMode.Create));
            f.Write(bf);
            bf.Flush();
            bf.Close();
        }
        // Make FITS file
        public void MakeFile(string FileName, short[][] ImgArray)
        {
            //Create a FITS file from an image:
            Fits f = new Fits();
            //BasicHDU h = FitsFactory.HDUFactory(ImgArray);
            BasicHDU h = Fits.MakeHDU(ImgArray);
            Header hdr = h.Header;
            //添加关键字
            hdr.AddValue("OBS2", "hss", "Observer");
            f.AddHDU(h);
            BufferedDataStream bf = new BufferedDataStream(new FileStream(FileName, FileMode.Create));
            f.Write(bf);
            bf.Flush();
            bf.Close();
        }
        // Make FITS file
        public void MakeFile(string FileName, int[][] ImgArray)
        {
            //Create a FITS file from an image:
            Fits f = new Fits();
            //BasicHDU h = FitsFactory.HDUFactory(ImgArray);
            BasicHDU h = Fits.MakeHDU(ImgArray);
            Header hdr = h.Header;
            //添加关键字
            hdr.AddValue("OBS2", "hss", "Observer");
            f.AddHDU(h);
            BufferedDataStream bf = new BufferedDataStream(new FileStream(FileName, FileMode.Create));
            f.Write(bf);
            bf.Flush();
            bf.Close();
        }
        // Make FITS file
        public void MakeFile(string FileName, float[][] ImgArray)
        {
            //Create a FITS file from an image:
            Fits f = new Fits();
            //BasicHDU h = FitsFactory.HDUFactory(ImgArray);
            BasicHDU h = Fits.MakeHDU(ImgArray);
            Header hdr = h.Header;
            //添加关键字
            hdr.AddValue("OBS2", "hss", "Observer");
            f.AddHDU(h);
            BufferedDataStream bf = new BufferedDataStream(new FileStream(FileName, FileMode.Create));
            f.Write(bf);
            bf.Flush();
            bf.Close();
        }
        // Make FITS file
        public void MakeFile(string FileName, double[][] ImgArray)
        {
            //Create a FITS file from an image:
            Fits f = new Fits();
            //BasicHDU h = FitsFactory.HDUFactory(ImgArray);
            BasicHDU h = Fits.MakeHDU(ImgArray);
            Header hdr = h.Header;
            //添加关键字
            hdr.AddValue("OBS2", "hss", "Observer");
            f.AddHDU(h);
            BufferedDataStream bf = new BufferedDataStream(new FileStream(FileName, FileMode.Create));
            f.Write(bf);
            bf.Flush();
            bf.Close();
        }
        // Read a FITS file
        public Bitmap ReadFile(string FileName)
        {
            Fits f2 = new Fits(FileName);
            ImageHDU h2 = (ImageHDU)f2.ReadHDU();
            Header hdr2 = h2.Header;
            int BitPixLen = hdr2.GetIntValue("BITPIX");
            int PixelWidth = hdr2.GetIntValue("NAXIS1");
            int PixelHeight = hdr2.GetIntValue("NAXIS2");
            object[] img = (object[])h2.Kernel;
            uint[][] img1 = new uint[PixelHeight][];
            byte[][] img2 = new byte[PixelHeight][];
            //for (int i = 0; i < PixelHeight; i++)
            //    img2[i] = new byte[PixelWidth];

            if (BitPixLen == 32)//int
            {
                //读出来又翻转，注意

                uint MaxPixelValue = 0x00000000;
                uint MinPixelValue = 0xFFFFFFFF;
                for (int i = 0; i < PixelHeight; i++)
                {
                    img1[i] = (uint[])img[i];//img强制赋值给img1
                    img2[i] = new byte[PixelWidth];
                    for (int j = 0; j < PixelWidth; j++)//求最值
                    {
                        if (img1[i][j] > MaxPixelValue)
                            MaxPixelValue = img1[i][j];
                        else if ((img1[i][j] > 0) && (img1[i][j] < MinPixelValue))
                            MinPixelValue = img1[i][j];
                    }
                }
                //转换灰度图系数
                double m = (MaxPixelValue - MinPixelValue) * 1.0 / 255;

                for (int i = 0; i < PixelHeight; i++)
                    for (int j = 0; j < PixelWidth; j++)
                    {
                        if (img1[i][j] > 0)
                        {
                            double tf = (img1[i][j] - MinPixelValue) * 1.0 / m;
                            if (tf >= 255.0)
                                img2[i][j] = 255;
                            else
                                img2[i][j] = Convert.ToByte(tf);
                        }
                    }
            }

            //Bitmap bmp = ToGrayBitmap(img2, PixelWidth, PixelHeight);
            //pictureBox1.Image = bmp;
            return ToGrayBitmap(img2, PixelWidth, PixelHeight);
        }

        /// <summary>  
        /// 将一个字节数组转换为8bit灰度位图  
        /// </summary>  
        /// <param name="rawValues">显示字节数组</param>  
        /// <param name="width">图像宽度</param>  
        /// <param name="height">图像高度</param>  
        /// <returns>位图</returns>  
        ///
        public static Bitmap ToGrayBitmap(byte[] rawValues, int width, int height)
        {
            //// 申请目标位图的变量，并将其内存区域锁定
            Bitmap bmp = new Bitmap(width, height, PixelFormat.Format8bppIndexed);
            BitmapData bmpData = bmp.LockBits(new Rectangle(0, 0, width, height),
                ImageLockMode.WriteOnly, PixelFormat.Format8bppIndexed);

            //// 获取图像参数
            int stride = bmpData.Stride;  // 扫描线的宽度
            int offset = stride - width;  // 显示宽度与扫描线宽度的间隙
            IntPtr iptr = bmpData.Scan0;  // 获取bmpData的内存起始位置
            int scanBytes = stride * height;   // 用stride宽度，表示这是内存区域的大小

            //// 下面把原始的显示大小字节数组转换为内存中实际存放的字节数组
            int posScan = 0, posReal = 0;   // 分别设置两个位置指针，指向源数组和目标数组
            byte[] pixelValues = new byte[scanBytes];  //为目标数组分配内存
            for (int x = 0; x < height; x++)
            {
                //// 下面的循环节是模拟行扫描
                for (int y = 0; y < width; y++)
                {
                    pixelValues[posScan++] = rawValues[posReal++];
                }
                posScan += offset;  //行扫描结束，要将目标位置指针移过那段“间隙”
            }

            //// 用Marshal的Copy方法，将刚才得到的内存字节数组复制到BitmapData中
            System.Runtime.InteropServices.Marshal.Copy(pixelValues, 0, iptr, scanBytes);
            bmp.UnlockBits(bmpData);  // 解锁内存区域

            //// 下面的代码是为了修改生成位图的索引表，从伪彩修改为灰度
            ColorPalette tempPalette;
            using (Bitmap tempBmp = new Bitmap(1, 1, PixelFormat.Format8bppIndexed))
            {
                tempPalette = tempBmp.Palette;
            }
            for (int i = 0; i < 256; i++)
            {
                tempPalette.Entries[i] = Color.FromArgb(i, i, i);
            }

            bmp.Palette = tempPalette;

            //// 算法到此结束，返回结果
            return bmp;
        }
        public static Bitmap ToGrayBitmap(byte[][] rawValues, int width, int height)
        {
            //// 申请目标位图的变量，并将其内存区域锁定  
            Bitmap bmp = new Bitmap(width, height, PixelFormat.Format8bppIndexed);
            BitmapData bmpData = bmp.LockBits(new Rectangle(0, 0, width, height), ImageLockMode.WriteOnly, PixelFormat.Format8bppIndexed);

            //// 获取图像参数  
            int stride = bmpData.Stride;  // 扫描线的宽度  
            int offset = stride - width;  // 显示宽度与扫描线宽度的间隙  
            IntPtr iptr = bmpData.Scan0;  // 获取bmpData的内存起始位置  
            int scanBytes = stride * height;// 用stride宽度，表示这是内存区域的大小  

            //// 下面把原始的显示大小字节数组转换为内存中实际存放的字节数组  
            //int posScan = 0, posReal = 0;// 分别设置两个位置指针，指向源数组和目标数组  
            int posScan = 0;// 分别设置两个位置指针，指向源数组和目标数组  
            byte[] pixelValues = new byte[scanBytes];  //为目标数组分配内存  
            int x, y;
            for (x = 0; x < height; x++)
            {
                //// 下面的循环节是模拟行扫描  
                for (y = 0; y < width; y++)
                {
                    pixelValues[posScan++] = rawValues[x][y];
                }
                y += offset;  //行扫描结束，要将目标位置指针移过那段“间隙”  
            }

            // 用Marshal的Copy方法，将刚才得到的内存字节数组复制到BitmapData中  
            System.Runtime.InteropServices.Marshal.Copy(pixelValues, 0, iptr, scanBytes);
            bmp.UnlockBits(bmpData);  // 解锁内存区域  

            //// 下面的代码是为了修改生成位图的索引表，从伪彩修改为灰度  
            ColorPalette tempPalette;
            using (Bitmap tempBmp = new Bitmap(1, 1, PixelFormat.Format8bppIndexed))
            {
                tempPalette = tempBmp.Palette;
            }
            for (int i = 0; i < 256; i++)
            {
                tempPalette.Entries[i] = Color.FromArgb(i, i, i);
            }

            bmp.Palette = tempPalette;

            //// 算法到此结束，返回结果  
            return bmp;
        }
    }
}
