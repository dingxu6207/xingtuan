#include <stdio.h>

/*****************************************************************************************
 *JDTime.c
 *
 *Idea:First get the year,month,day,hour,minute,second value of current time, then calculate
 *	   the Julian Day of current time.
 *
 *Input: The time value, such us: year-month-day hour:min:sec
 *Output: The final Julian Day calculated by this function.
 *
 *Usage: You can use this function by just call getJD() from other program, then you can 
 *		 get the Julian Day value of current time, and use it.
 *
 *1		2008-7-14	wcj.		Original version. Tested on the enviroment of Turbo C,
 *								compiling smoothly, but needed to be tested.																					 
 ****************************************************************************************/

double  getJD(){
	int tai_utc=32;
	int a,b;
	int year,month,day,hour,min,sec;
	long term;
	double currentTime,ymd,jed;
	uint32 RTCtime;
	uint32 RTCdate;					/*获取完整的日期*/
	
	RTCtime = RTCtimeRead; // 读取完整时钟寄存器
	RTCdate = RTCdateRead;	// 读取完整日期寄存器
	//取得年值
	year = (RTCdate>>16)&0xFFF;
	//取得月值
	month = (RTCdate>>8)&0x0F;
	// 取得日值
	day = RTCdate&0x1F;            
	
	// 取得时的值
	hour = (RTCtime>>16)&0x1F;
	// 取得分的值		
	min = (RTCtime>>8)&0x3F;	
	// 取得秒的值	
	sec = RTCtime&0x3F;
	
	currentTime = hour+((double)min/100)+((double)sec/10000);

	if(month==1||month==2){
		year = year-1;
		month = month+12;
	}

	ymd = year + (double)month/100+(double)day/10000;
	if(ymd>=1582.1015){
		a = year/100;
		b = 2-a+(a/4);
	}
	else{
		a = 0;
		b = 0;
	}

	if(year<0)
		term = (long)(365.25*year-0.75);
	else
		term = (long)365.25*year;

	jed = term + (int)(30.6001*(month+1))+day+currentTime/24.0 +  1720994.5 + b +(tai_utc+32.185)/86400.0;
	return jed;
}
