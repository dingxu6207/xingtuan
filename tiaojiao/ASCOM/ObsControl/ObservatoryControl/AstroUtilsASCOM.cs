using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ObservatoryCenter
{
    class AstroUtilsASCOM
    {
        public static double Latitude;
        public static double Longitude;
        public static string ConvertToTimeString(DateTime t)
        {
            return DateTime.Now.ToShortTimeString();
        }
        public static double MoonIllumination()
        {
            return 0;
        }
        public static DateTime NowLAST()
        {
            return DateTime.Now;
        }
        public static double GetJD()
        {
            return 0;
        }
        public static DateTime SunRise(double t)
        {
            return DateTime.Now;
        }
        public static DateTime SunSet()
        {
            return DateTime.Now;
        }
        public static DateTime MoonRise()
        {
            return DateTime.Now;
        }
        public static DateTime MoonSet()
        {
            return DateTime.Now;
        }
        public static DateTime NautTwilightSet()
        {
            return DateTime.Now;
        }
        public static DateTime AstronTwilightSet()
        {
            return DateTime.Now;
        }
        public static DateTime AstronTwilightRise(double t)
        {
            return DateTime.Now;
        }
        public static DateTime NautTwilightRise(double t)
        {
            return DateTime.Now;
        }
    }
}
