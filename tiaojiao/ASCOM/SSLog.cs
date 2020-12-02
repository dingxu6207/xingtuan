using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using System.Threading;
using System.IO;
using System.Text.RegularExpressions;

namespace ObservatoryCenter
{
    /// <summary>
    /// 日志操作类
    /// </summary>
    class SSLog
    {
        #region 属性
        /// <summary>
        /// 日志保存路径
        /// </summary>
        private static string LogPath = "SSLog";
        /// <summary>
        /// 文件锁
        /// </summary>
        private static readonly object FileLock = new object();
        /// <summary>
        /// 是否写日志
        /// </summary>
       // private static Boolean IsWriteLog = true;
        /// <summary>
        /// 计时器
        /// </summary>
        private static int Count = 0;
        #endregion
        #region 枚举
        /// <summary>
        /// Log类型
        /// </summary>
        public enum LogLevel
        {
            Important = 0,
            Activity = 1,
            Trace = 2,
            Debug = 3
        }
        public enum Highlight
        {
            Normal = 0,
            Error = 1,
        }
        #endregion

        #region 结构体
        /// <summary>
        /// 日志结构体
        /// </summary>
        public struct LogData
        {
            /// <summary>
            /// 记录时间
            /// </summary>
            public string Time;
            /// <summary>
            /// Log ID
            /// </summary>
            //public string ID;
            /// <summary>
            /// 日志类型
            /// </summary>
            public LogLevel Level;
            /// <summary>
            /// 信息
            /// </summary>
            public string Message;
        }
        #endregion
        #region 构造器
        /// <summary>
        /// 构造器
        /// </summary>
        static SSLog()
        {
            /*初始化数据*/
            ThreadPool.SetMaxThreads(30, 30);
            ThreadPool.SetMinThreads(1, 1);
            LogPath = AppDomain.CurrentDomain.BaseDirectory + LogPath + "\\";
            if (!Directory.Exists(LogPath)) Directory.CreateDirectory(LogPath);
        }
        #endregion

        #region 方法

        /// <summary>
        /// 记录日志
        /// </summary>
        /// <param name="logData">日志对象</param>
        public static void WriteLog(LogData logData)
        {
            //if (!IsWriteLog) return;
            ThreadPool.QueueUserWorkItem((o) =>
            {
                Thread.CurrentThread.IsBackground = true;
                Run(logData);
            });
        }
        /// <summary>
        /// 记录日志
        /// </summary>
        /// <param name="LogLevel">日志类型</param>
        /// <param name="DataSource">日志源</param>
        /// <param name="ClassName">日志类名</param>
        /// <param name="FunctionName">方法名</param>
        /// <param name="Message">日志信息</param>
        public static void WriteLog(LogLevel LLevel, string LogMessage)
        {
            WriteLog(new LogData
            {
                Level = LLevel,
                Message = LogMessage
            });
        }
        /// <summary>
        /// 记录日志
        /// </summary>
        /// <param name="Message">日志信息</param>
        public static void WriteLog(string LogMessage)
        {
            WriteLog(new LogData
            {
                Level = LogLevel.Trace,
                Message = LogMessage
            });
        }
        /// <summary>
        /// 记录日志
        /// </summary>
        /// <param name="Message">信息</param>
        public static void AddLog(string Message, LogLevel LL, Highlight HL) { WriteLog(LL, Message); }
        /// <summary>
        /// 记录日志
        /// </summary>
        /// <param name="Message">信息</param>
        public static void AddLog(string Message, LogLevel LL) { WriteLog(LL, Message); }
        /// <summary>
        /// 记录日志
        /// </summary>
        /// <param name="Message">信息</param>
        public static void AddLog(string Message) { WriteLog(LogLevel.Trace, Message); }


        /// <summary>
        /// 文件是否存在
        /// </summary>
        /// <param name="FilePath">文件路径</param>
        private static void CreateFile(string FilePath)
        {
            if (!File.Exists(FilePath))
            {
                FileStream fso = File.Create(FilePath);
                fso.Close();
                fso.Dispose();

                StreamWriter SW = File.AppendText(FilePath);
                SW.WriteLine("");
                SW.WriteLine("                   LogFile(" + DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss") + ")");
                SW.WriteLine("");
                SW.Flush();
                SW.Close();
                SW.Dispose();
            }
        }
        /// <summary>
        /// 读取LogID
        /// </summary>
        /// <param name="FilePath">文件路径</param>
        private static UInt32 ReadLogID(string FilePath)
        {
            if (File.Exists(FilePath))
            {
                StreamReader sr = new StreamReader(FilePath);
                string st = string.Empty;
                while (!sr.EndOfStream)
                    st = sr.ReadLine();
                if (string.IsNullOrEmpty(st))
                    return 0;
                else
                    return Convert.ToUInt32(st.Split(' ')[0]);
            }
            else
                return 0;
        }
        /// <summary>
        /// 写日志
        /// </summary>
        /// <param name="logData">日志数据</param>
        /// <param name="logPath">日志路径</param>
        public static void Run(LogData logData, string logPath = null)
        {
            try
            {
                if (string.IsNullOrEmpty(logPath))//默认目录
                    logPath = LogPath;
                else//新建目录
                {
                    LogPath = AppDomain.CurrentDomain.BaseDirectory + LogPath + "\\";
                    if (!Directory.Exists(LogPath)) Directory.CreateDirectory(LogPath);
                }
                Monitor.Enter(FileLock);//锁定
                //创建日志文件
                string FilePath = logPath + "\\" + DateTime.Now.ToString("yyyy-MM-dd") + ".log";
                CreateFile(FilePath);

                //写入日志数据
                StreamWriter sw = File.AppendText(FilePath);
                sw.WriteLine("".PadLeft(70, '-'));
                sw.WriteLine(string.Format("Time : [{0}]  ", DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss.fff")));
                //sw.WriteLine("LogID : " + logData.ID);
                sw.WriteLine("LogLevel : " + logData.Level);
                sw.WriteLine("Message : " + logData.Message);
                //保存日志文件
                sw.Flush();
                sw.Close();
                sw.Dispose();
                Monitor.Exit(FileLock);//解锁
            }
            catch
            {
                if (Interlocked.Increment(ref Count) == 3)
                {
                    Count = 0;
                    return;
                }
                Run(logData);
            }
        }

        #endregion
    }
}
