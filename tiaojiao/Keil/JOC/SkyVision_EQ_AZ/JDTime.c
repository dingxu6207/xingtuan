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
	uint32 RTCdate;					/*��ȡ����������*/
	
	RTCtime = RTCtimeRead; // ��ȡ����ʱ�ӼĴ���
	RTCdate = RTCdateRead;	// ��ȡ�������ڼĴ���
	//ȡ����ֵ
	year = (RTCdate>>16)&0xFFF;
	//ȡ����ֵ
	month = (RTCdate>>8)&0x0F;
	// ȡ����ֵ
	day = RTCdate&0x1F;            
	
	// ȡ��ʱ��ֵ
	hour = (RTCtime>>16)&0x1F;
	// ȡ�÷ֵ�ֵ		
	min = (RTCtime>>8)&0x3F;	
	// ȡ�����ֵ	
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
