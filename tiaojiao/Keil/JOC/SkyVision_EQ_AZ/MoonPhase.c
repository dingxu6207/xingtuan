#include <stdio.h>

/*****************************************************************************************************
 * MoonPhase.c
 *
 *Idea: First get the year, month of this date, then get the days count in this month, using them to get
 *		the moonphase of a whole month.$
 *
 *Input: A specified year, month.$
 *Output: The moon phase of the specified month.$
 *
 *Usage:You can just call dispMoonPhase() from other program, then you can calculate the lunar phase of current
 *		date, and display on the screen.
 *
 *5		2008-8-25		wcj.		修改了显示的方法，将所有的显示放在了一个方法里来实现，删除了dispPhase0到dispPhase7这些函数；
 *									修改了dispMoonPhase方法，将其中不需要的部分都去掉，并按照日期安排月相显示的位置；
 *									测试了显示月相的方法，可以将一个月的对应的月相都显示在LCD上，不过还需要优化；
 *									旧版本的MoonPhase文件被重命名为MoonPhase1，可以供参考；
 *4		2008-7-20		wcj.		Change the Lunar phase display method, as the same phase just display once.$
 *3		2008-7-8		wcj.		Added the Lunar phase display methods, needed to be tested.	$
 *2		2008-7-7		wcj.		Added into the project.	$
 *1		2008-6-30		wcj.		Original Version.	$
 *****************************************************************************************************/
 /*****************************************************************************************************
  *------------------------该函数调用方法----------------------------------------
  *在使用该文件来计算某个指定月份的月相的时候，只需要调用函数dispMoonPhase(int year,int month)即可。
  *需要输入的参数是：指定的年和月
  *结果：计算指定年月的月相情况，并显示一个月的月相信息在LCD界面上。
  *****************************************************************************************************/

/********************************************************************************************
 *Method: dispPhase
 *Func: Display the lunar phase on the LCD screen, with the specified phase_id.
 *Params:uint8 Lin --- The page number for drawing
 *		 uint8 Col --- The colume number for drawing
 *		 uint8 phase_id --- The if of specified lunar phase, 0 for New, 1 for Waxing Crescent, 
 *							2 for first quarter, 3 for Waxing Gibbous,4 for Full, 5 for Waning Gibbous,
 *							6 for Third quarter, 7 for Waning Crescent.
 *Return: Null
 ********************************************************************************************/
void dispPhase(uint8 Lin,uint8 Col,uint8 phase_id){
	const char phaseBit[8][32] = {0xE0,0x18,0x04,0x02,0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x00,0x02,0x04,0x18,0xE0,0x07,0x18,0x20,0x40,0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x00,0x40,0x20,0x18,0x07,
								   0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x03,0x03,0x07,0x1F,0xFE,0xFE,0xFC,0xF8,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0xC0,0xE0,0xF8,0x7F,0x7F,0x3F,0x1F,0x07,
								   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFE,0xFE,0xFC,0xF8,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0x7F,0x7F,0x3F,0x1F,0x07,
								   0x00,0x00,0x00,0xC0,0xF0,0xFC,0xFE,0xFF,0xFF,0xFF,0xFF,0xFE,0xFE,0xFC,0xF8,0xE0,0x00,0x00,0x00,0x03,0x0F,0x3F,0x7F,0xFF,0xFF,0xFF,0xFF,0x7F,0x7F,0x3F,0x1F,0x07,
								   0xE0,0xF8,0xFC,0xFE,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0xFE,0xFC,0xFC,0xE0,0x07,0x1F,0x3F,0x7F,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x7F,0x3F,0x1F,0x07,
								   0xE0,0xF8,0xFC,0xFE,0xFE,0xFF,0xFF,0xFF,0xFF,0xFE,0xFC,0xF0,0xC0,0x00,0x00,0x00,0x07,0x1F,0x3F,0x7F,0x7F,0xFF,0xFF,0xFF,0xFF,0x7F,0x3F,0x0F,0x03,0x00,0x00,0x00,
								   0xE0,0xF8,0xFC,0xFE,0xFE,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x1F,0x3F,0x7F,0x7F,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
								   0xE0,0xF8,0xFC,0xFE,0xFE,0x1F,0x07,0x03,0x03,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x1F,0x3F,0x7F,0x7F,0xF8,0xE0,0xC0,0xC0,0x80,0x00,0x00,0x00,0x00,0x00,0x00,
								   }	;
	int i;
	LCDWC(0x00 | ((Col-1)*6+2 & 0x0f ) );	// 列号低4bit
	LCDWC(0x10 | ((Col-1)*6+2 & 0xf0 )>>4 );	// 列号高4bit
	LCDWC(0xB0 | ( (Lin-1)&0x0f ) );	// 页号
	for(i=0;i<16;i++){
		LCDWD(phaseBit[phase_id][i]);
	}

	LCDWC(0x00 | ((Col-1)*6+2 & 0x0f ) );	// 列号低4bit
	LCDWC(0x10 | ((Col-1)*6+2 & 0xf0 )>>4 );	// 列号高4bit
	LCDWC(0xB0 | ( (Lin)&0x0f ) );	// 页号
	for(i=0;i<16;i++){
		LCDWD(phaseBit[phase_id][i+16]);
	}
}

/******************************************************************************************
 *Method: isLeapYearP
 *Func: Make sure if the specified year is leap year, and return the result.
 *Params: int ---- the specified year
 *Return: int ---- the result, if is leap year return 1, else return 0.
 ******************************************************************************************/
int isLeapYearP(int year){
	if((year%4==0)&&((year%400==0)||(year%100!=0)))
		return 1;
	else
		return 0;
 }

 /**************************************************************************************
   *Method: daysInMonth
   *Func:Returns the number of days in a month given the month and the year.
   *Params:int ---- the specified year
   *			 int ---- the specified month
   *Return:int ---- the days of specified year and month
   **************************************************************************************/
int daysInMonth(int year, int month){
  	int result = 31;							/*Default days: 31*/
  	switch(month){
  		case 4:									/*Days for month 4,6,9,11: 30*/
  		case 6:
  		case 9:
  		case 11:
  			result = 30;
  			break;
  		case 2:									/*Days for month 2: 29 in leap year, 28 others*/
  			if(isLeapYearP(year)==1)
  				result = 29;
  			else
  				result = 28;
  			break;
  	}
  	return result;
	}

/********************************************************************************
 *Method: moonPhase
 *Func: Output the phase of the moon for the given year, month, day.
 * 			The routine calculates the year's epact (the age of the moon on Jan 1.),
 * 			adds this to the number of days in the year, and calculates the phase 
 * 			of the moon for this date.
 *In the algorithm:
 *
 *      diy     Is the day of the year - 1 (i.e., Jan 1 is day 0).
 *
 *      golden  Is the number of the year in the Mentonic cycle, used to
 *              determine the position of the calender moon.
 *
 *      epact   Is the age of the calender moon (in days) at the beginning
 *              of the year.  To calculate epact, two century-based
 *              corrections are applied:
 *              Gregorian:      (3 * cent)/4 - 12
 *                      is the number of years such as 1700, 1800 when
 *                      leap year was not held.
 *              Clavian:        (((8 * cent) + 5) / 25) - 5
 *                      is a correction to the Mentonic cycle of about
 *                      8 days every 2500 years.  Note that this will
 *                      overflow 16 bits in the year 409600.  Beware.
 *
 * The algorithm is accurate for the Gregorian calender only.
 * 
 * The magic numbers used in the phase calculation are as follows:
 *       29.5           The moon's period in days.
 *      177             29.5 scaled by 6
 *       22             (29.5 / 8) scaled by 6 (this gets the phase)
 *       11             ((29.5 / 8) / 2) scaled by 6
 *
 * Theoretically, this should yield a number in the range 0 .. 7.  However,
 * two days per year, things don't work out too well.
 *
 * Epact is calculated by the algorithm given in Knuth vol. 1 (calculation
 * of Easter).  See also the article on Calenders in the Encyclopaedia
 * Britannica and Knuth's algorithm in CACM April 1962, page 209.
 *
 *Params:int ---- the specified year
 *		 int ---- the specified month
 *		 int ---- the specified day
 *Return:int ---- the phase id of specified date
 ********************************************************************************/
int moonPhase(int year,int month,int day){
    int phase;			/*The moon phase number*/
    int cent;				/*The century number, cent(1979) = 20;*/
    int epact;			/*Age of the moon on Jan. 1*/
    int diy;				/*Day in the year*/
    int golden;			/*Moon's golden number*/
    /*day_year - gives the day of the year for the first day of each month -1. 
    i.e. 1st January is the 0th day of the year, 1st February is the 31st etc. Used by 'moonPhase'.*/
	static int day_year[] = {-1,-1,30,58,89,119,150,180,211,241,272,303,333};				

    if(month<0 || month>12)	month = 0;
    diy = day+day_year[month];												/*Day in the year*/
    if((month>2)&&((year%4==0)&&((year%400==0)||(year%100!=0))))
			diy++;																															/*Leapyear fixup*/
    cent = (year/100) + 1;													/*Century number*/
    golden = (year % 19) + 1;												/*Golden number*/
    epact = ((11*golden)+20													/*Golden number*/
    				+(((8*cent)+5)/25)-5									/*400 year cycle*/
    				-(((3*cent)/4)-12))%30;									/*Leap year correction*/
    if(epact <=0)
			epact += 30;																												/*Age range is 1 .. 30*/
    if(epact == 25 && golden > 11 || epact == 24)
			epact ++;

    /*Calculate the phase, using the magic numbers defined above.Note that (phase and 7) is equivalent to
    (phase mod 8) and is needed on two days per year (when the algorithm yields 8).*/
    phase = (((((diy + epact)*6)+11)%177)/22) & 7;			/*Calculate the phase value*/

    return phase;
  }


/**********************************************************************************************************
 *Method: dispMoonPhase
 *Func: Display the lunar phase of specified year-month, display a month's lunar phase on the LCD Screen.
 *Params:int year -- the specified year
 *		 int month -- the specified month
 *Return:Null
 **********************************************************************************************************/
void dispMoonphase(int year,int month){
  	int day;						/*日*/
  	int phase_id;					/*记录特定日期的月相的编号*/
	int old_phase = -1;				/*记录上一次的Phase的ID号，从而在下面进行判断，不用重复显示*/
	int lin = 2;					/*月相显示的页号*/
	int col = 1;					/*月相显示的列号*/
	char daysCount[31][2] = {'0','1','0','2','0','3','0','4','0','5','0','6','0','7','0','8','0','9','1','0','1','1','1','2','1','3','1','4','1','5','1','6','1','7','1','8','1','9','2','0','2','1','2','2','2','3','2','4','2','5','2','6','2','7','2','8','2','9','3','0','3','1'};		/*用来根据具体的日期在LCD屏幕上显示对应日期*/
	
	char dateDisp[7];						//用来显示当前的日期
	dateDisp[0] = (year/1000)+0x30;		 	//年的最高位
	dateDisp[1] = (year%1000)/100+0x30;		//年的第二位
	dateDisp[2] = (year%100)/10+0x30;		//年的第三位
	dateDisp[3] = (year%100)%10+0x30;		//年的第四位
	dateDisp[4] = '-';
	dateDisp[5] = (month/10)+0x30;			//月的最高位
	dateDisp[6] = (month%10)+0x30;			//月的第二位
	DispEn(0,1,8,7,dateDisp);		/*显示年月信息，需要修改*/

	for(day=1;day<=daysInMonth(year,month);day++){
		/*由年、月、日计算得到当前日期的月相编号，并在LCD上显示*/
	  	phase_id = moonPhase(year,month,day);
		if(phase_id == old_phase){	//判断得到的月相编号与上一次的是否相同，如果相同就跳出到下一次循环，否则就显示新的月相
			continue;
		}
		else{
			old_phase = phase_id;					  //记录当前显示的月相的编号
			dispPhase(lin,col,phase_id);			  //调用显示月相的函数
			DispEn(0,lin+2,col,2,daysCount[day-1]);	  //显示该月相对应的起始日期
			col += 4;								  //月相的列间隔取4，即两个月相的显示之间相差4列
			if(col>20){								  //如果显示已经到了当前页的最后，那么就换页
				col -= 20;							  //列号-20
				lin += 3;							  //页号加3，因为月相会占2页，还有日期数字也占一页，故两行月相之间间隔3页
			}
		}
	}
}
