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
 *2	2008-9-3		添加了显示时角的部分程序，可以根据用户输入的时角信息，即时、分、秒对应显示；
 *1	2008-9-3		完成了最初版本的编写及测试，基本上可以显示一个时钟；
 *****************************************************************************************************/
 /*****************************************************************************************************
  *------------------------该函数调用方法----------------------------------------
  *在使用该文件来计算某个指定月份的月相的时候，只需要调用函数dispPole(int t)即可。
  *需要输入的参数是：当前时间对应的北极星的时角t。
  *结果：根据输入的时角，在LCD上显示当前时角对应的指针的位置。由于精度的关系，在这里只显示小时对应的指针
  *		 位置，因为如果要显示分的话就太细微了，实现比较困难。而且在LCD上小时间的差距也不是很明显。
  *****************************************************************************************************/

/********************************************************************************************
 *Method: dispPole
 *Func: 显示当前时间对应的时角信息到LCD上，需要输入指定的时角值。
 *Params:uint8 t -- 当前时间对应的时角的时。
 *		 uint8 m -- 当前时间对应的时角的分。
 *		 uint8 s -- 当前时间对应的时角的秒。
 *Return: Null
// ********************************************************************************************/
//void dispPole(uint8 poletype){
//	char PoleBit[288]= { 0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xC0,0xA0,0x10,0x10,0x08,0x08,0x04,0x04,0x02,
//						  0x02,0x01,0x01,0x01,0x01,0x01,0x01,0x1F,0x1F,0x01,0x01,0x01,0x01,0x01,0x01,0x02,
//						  0x02,0x04,0x04,0x08,0x08,0x10,0x10,0xA0,0xC0,0x80,0x00,0x00,0x00,0x00,0x00,0x00,		//Page1
//						  0x00,0xC0,0x50,0x18,0x06,0x03,0x00,0x01,0x03,0x03,0xC0,0x60,0x30,0x18,0x0C,0x04,			
//						  0x06,0x02,0x03,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x03,0x02,0x06,
//						  0x04,0x0C,0x18,0x30,0x60,0xC0,0x03,0x03,0x01,0x00,0x03,0x06,0x18,0x50,0xC0,0x00,		//Page2
//						  0xFE,0x81,0x80,0x80,0x80,0x00,0x00,0x00,0xFC,0x07,0x00,0x00,0x00,0x00,0x00,0x00,			
//						  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//						  0x00,0x00,0x00,0x00,0x00,0x00,0x07,0xFC,0x00,0x00,0x00,0x80,0x80,0x80,0x81,0xFE,		//Page3
//						  0x7F,0x81,0x01,0x01,0x01,0x00,0x00,0x00,0x3F,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,			
//						  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//						  0x00,0x00,0x00,0x00,0x00,0x00,0xE0,0x3F,0x00,0x00,0x00,0x01,0x01,0x01,0x81,0x7F,		//page4
//						  0x00,0x03,0x0C,0x10,0x60,0x80,0x00,0x80,0xC0,0xC0,0x03,0x06,0x0C,0x18,0x30,0x20,			
//						  0x60,0x40,0xC0,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0xC0,0x40,0x60,
//						  0x20,0x30,0x18,0x0C,0x06,0x03,0xC0,0xC0,0x80,0x00,0x80,0x60,0x10,0x0C,0x03,0x00,		//page5
//						  0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x03,0x05,0x08,0x08,0x10,0x30,0x20,0x60,0x40,
//						  0x40,0x80,0x80,0x80,0x80,0x80,0x80,0xF8,0xF8,0x80,0x80,0x80,0x80,0x80,0x80,0x40,
//						  0x40,0x60,0x20,0x30,0x10,0x08,0x08,0x05,0x03,0x01,0x00,0x00,0x00,0x00,0x00,0x00 		//page6
//						};
//	int i,j;
//	int Col = 1;
//	int Lin = 2; 
//	uint8 t,m,s ;
//	double hourganle ;
//	double stime;
//	
//  	char timeDisp[8]="00:00:00";
//	char *timestr;
//   	   	
//	//*****************************************************
//   //柳光乾在此修改加入时角计算	
//	//计算时角
//	stime=FCalSiderealTime(1,false,g_mGoto.m_nLongitude);
//
//	if(poletype==0)
//	{
//	   hourganle=stime-2.7115; //
//	}
//	else
//	{
//	   hourganle=stime-21.32111; //sigma -Oct 21h 19m 16.02s
//	}
//    while(hourganle>=24)
//	{
//		hourganle=hourganle-24;
//	}
//    while(hourganle<0)
//	{
//		hourganle=hourganle+24;
//	}
//		
//	
//	t=(int)hourganle;//地平坐标方位返回赋值于方位显示
//	m=(int)((hourganle-t)*60.0);
//	s=(int)((hourganle-t-m/60.0)*3600);
//	//*****************************************************
//	/*timeDisp[0] = t/10 +0x30;
//	timeDisp[1] = t%10 +0x30;
//	timeDisp[2] = ':';
//	timeDisp[3] = m/10 +0x30;
//	timeDisp[4] = m%10 +0x30;
//	timeDisp[5] = ':';
//	timeDisp[6] = s/10 +0x30;
//	timeDisp[7] = s%10 +0x30;
//	DispEn(0,3,12,8,timeDisp);*/
//
//	
//	DispEn(0,1,14,10,"HrAngle:");
//	sprintf(timeDisp,"%02d:%02d:%02d",t,m,s);
//	timestr=timeDisp;
//	DispEn(0,3,14,8,timestr);
//
//	DispEn(0,6,14,10,"LclTime:");
//	sprintf(timeDisp,"%02d:%02d:%02d",g_mTime_hour,g_mTime_minute,g_mTime_second);
//	timestr=timeDisp;
//	DispEn(0,8,14,8,timestr);
//	
//
//
//	 
//    hourganle=hourganle+12;
//	if(hourganle>24)
//	{
//	   hourganle=hourganle-24;
//
//	}
//	if(poletype==0)
//	{
//	    hourganle=24-hourganle;
//	}
//
//
//			
//	t=(int)hourganle;//地平坐标方位返回赋值于方位显示
//	m=(int)((hourganle-t)*60.0);
//	s=(int)((hourganle-t-m/60.0)*3600);
//	
//		
//
//	if(m>=45)
//		t+=1;
//
//	switch(t){
//		case 0:	//0点时需要修改的数组的值
//			PoleBit[71] = 0xFD;
//			PoleBit[72] = 0xFD;
//			PoleBit[119] = 0xFF;
//			PoleBit[120] = 0xFF;
//			break;
//		case 1:	//1点时需要修改的数组的值
//			PoleBit[73] = 0xC1;
//			PoleBit[74] = 0xFD;
//			PoleBit[75] = 0x3D;
//			PoleBit[119] = 0xC0;
//			PoleBit[120] = 0xFC;
//			PoleBit[121] = 0x3F;
//			PoleBit[122] = 0x03;
//			break;
//		case 2:	//2点时需要修改的数组的值
//			PoleBit[77] = 0xC1;
//			PoleBit[78] = 0xE3;
//			PoleBit[79] = 0x62;
//			PoleBit[119] = 0x80;
//			PoleBit[120] = 0xE0;
//			PoleBit[121] = 0x70;
//			PoleBit[122] = 0x3C;
//			PoleBit[123] = 0x0F;
//			PoleBit[124] = 0x03;
//			PoleBit[125] = 0x01;
//			break;
//		case 3:	//3点时需要修改的数组的值
//			PoleBit[79] = 0x86;
//			PoleBit[80] = 0xC4;
//			PoleBit[81] = 0xC8;
//			PoleBit[120] = 0xC0;
//			PoleBit[121] = 0xE0;
//			PoleBit[122] = 0x70;
//			PoleBit[123] = 0x38;
//			PoleBit[124] = 0x1C;
//			PoleBit[125] = 0x0E;
//			PoleBit[126] = 0x07;
//			PoleBit[127] = 0x03;
//			PoleBit[128] = 0x01;
//			break;
//		case 4:	//4点时需要修改的数组的值
//			PoleBit[120] = 0x80;
//			PoleBit[121] = 0xC0;
//			PoleBit[122] = 0x40;
//			PoleBit[123] = 0x60;
//			PoleBit[124] = 0x30;
//			PoleBit[125] = 0x30;
//			PoleBit[126] = 0x18;
//			PoleBit[127] = 0x08;
//			PoleBit[128] = 0x0C;
//			PoleBit[129] = 0x06;
//			PoleBit[130] = 0x06;
//			PoleBit[131] = 0x03;
//			break;
//		case 5:	//5点时需要修改的数组的值
//			PoleBit[120] = 0x80;
//			PoleBit[121] = 0x80;
//			PoleBit[122] = 0xC0;
//			PoleBit[123] = 0x40;
//			PoleBit[124] = 0x40;
//			PoleBit[125] = 0x60;
//			PoleBit[126] = 0x60;
//			PoleBit[127] = 0x20;
//			PoleBit[128] = 0x20;
//			PoleBit[129] = 0x30;
//			PoleBit[130] = 0x30;
//			PoleBit[131] = 0x10;
//			break;
//		case 6:	//6点时需要修改的数组的值
//			for(i=0;i<14;i++){
//				PoleBit[120+i] = 0x80;
//			}
//			for(i=0;i<14;i++){
//				PoleBit[168+i] = 0x01;
//			}
//			break;
//		case 7:	//7点时需要修改的数组的值
//			PoleBit[168] = 0x01;
//			PoleBit[169] = 0x01;
//			PoleBit[170] = 0x03;
//			PoleBit[171] = 0x02;
//			PoleBit[172] = 0x02;
//			PoleBit[173] = 0x06;
//			PoleBit[174] = 0x06;
//			PoleBit[175] = 0x04;
//			PoleBit[176] = 0x04;
//			PoleBit[177] = 0x0C;
//			PoleBit[178] = 0x0C;
//			PoleBit[179] = 0x08;
//			break;
//		case 8:	 //8点时需要修改的数组的值
//			PoleBit[168] = 0x01;
//			PoleBit[169] = 0x03;
//			PoleBit[170] = 0x06;
//			PoleBit[171] = 0x06;
//			PoleBit[172] = 0x0C;
//			PoleBit[173] = 0x0C;
//			PoleBit[174] = 0x18;
//			PoleBit[175] = 0x10;
//			PoleBit[176] = 0x30;
//			PoleBit[177] = 0x60;
//			PoleBit[178] = 0x60;
//			PoleBit[179] = 0x40;
//			break;
//		case 9:	//9点时需要修改的数组的值
//			PoleBit[168] = 0x03;
//			PoleBit[169] = 0x07;
//			PoleBit[170] = 0x0E;
//			PoleBit[171] = 0x1C;
//			PoleBit[172] = 0x38;
//			PoleBit[173] = 0x70;
//			PoleBit[174] = 0xE0;
//			PoleBit[175] = 0xC0;
//			PoleBit[176] = 0x80;
//			PoleBit[223] = 0x61;
//			PoleBit[224] = 0x23;
//			PoleBit[225] = 0x33;
//			break;
//		case 10: //10点时需要修改的数组的值
//			PoleBit[168] = 0x03;
//			PoleBit[169] = 0x0E;
//			PoleBit[170] = 0x18;
//			PoleBit[171] = 0x70;
//			PoleBit[172] = 0xC0;
//			PoleBit[220] = 0x81;
//			PoleBit[221] = 0xC7;
//			PoleBit[222] = 0x4C;
//			PoleBit[223] = 0x60;
//			break;
//		case 11: //11点时需要修改的数组的值
//			PoleBit[168] = 0x07;
//			PoleBit[169] = 0x7C;
//			PoleBit[170] = 0xC0;
//			PoleBit[218] = 0x87;
//			PoleBit[219] = 0x9C;
//			break;
//		case 12: //12点时需要修改的数组的值
//			PoleBit[167] = 0xFF;
//			PoleBit[168] = 0xFF;
//			PoleBit[215] = 0xBF;
//			PoleBit[216] = 0xBF;
//			break;
//		case 13:  //13点时需要修改的数组的值
//			PoleBit[165] = 0xC0;
//			PoleBit[166] = 0x7C;
//			PoleBit[167] = 0x07;
//			PoleBit[212] = 0x9C;
//			PoleBit[213] = 0x87;
//			break;
//		case 14: //14点时需要修改的数组的值
//			PoleBit[163] = 0xC0;
//			PoleBit[164] = 0x70;
//			PoleBit[165] = 0x18;
//			PoleBit[166] = 0x0E;
//			PoleBit[167] = 0x03;
//			PoleBit[208] = 0x60;
//			PoleBit[209] = 0x4C;
//			PoleBit[210] = 0xC7;
//			PoleBit[211] = 0x81;
//			break;
//		case 15: //15点时需要修改的数组的值
//			PoleBit[159] = 0x80;
//			PoleBit[160] = 0xC0;
//			PoleBit[161] = 0xE0;
//			PoleBit[162] = 0x70;
//			PoleBit[163] = 0x38;
//			PoleBit[164] = 0x1C;
//			PoleBit[165] = 0x0E;
//			PoleBit[166] = 0x07;
//			PoleBit[167] = 0x03;
//			PoleBit[206] = 0x33;
//			PoleBit[207] = 0x23;
//			PoleBit[208] = 0x61;
//			break;
//		case 16: //16点时需要修改的数组的值
//			PoleBit[156] = 0x40;
//			PoleBit[157] = 0x60;
//			PoleBit[158] = 0x60;
//			PoleBit[159] = 0x30;
//			PoleBit[160] = 0x10;
//			PoleBit[161] = 0x18;
//			PoleBit[162] = 0x0C;
//			PoleBit[163] = 0x0C;
//			PoleBit[164] = 0x06;
//			PoleBit[165] = 0x06;
//			PoleBit[166] = 0x03;
//			PoleBit[167] = 0x01;
//			break;
//		case 17: //17点时需要修改的数组的值
//			PoleBit[156] = 0x08;
//			PoleBit[157] = 0x0C;
//			PoleBit[158] = 0x0C;
//			PoleBit[159] = 0x04;
//			PoleBit[160] = 0x04;
//			PoleBit[161] = 0x06;
//			PoleBit[162] = 0x06;
//			PoleBit[163] = 0x02;
//			PoleBit[164] = 0x02;
//			PoleBit[165] = 0x03;
//			PoleBit[166] = 0x01;
//			PoleBit[167] = 0x01;
//			break;
//		case 18: //18点时需要修改的数组的值
//			for(i=0;i<14;i++){
//				PoleBit[106+i] = 0x80;
//			}
//			for(i=0;i<14;i++){
//				PoleBit[154+i] = 0x01;
//			}
//			break;
//		case 19: //19点时需要修改的数组的值
//			PoleBit[108] = 0x10;
//			PoleBit[109] = 0x30;
//			PoleBit[110] = 0x30;
//			PoleBit[111] = 0x20;
//			PoleBit[112] = 0x20;
//			PoleBit[113] = 0x60;
//			PoleBit[114] = 0x60;
//			PoleBit[115] = 0x40;
//			PoleBit[116] = 0x40;
//			PoleBit[117] = 0xC0;
//			PoleBit[118] = 0x80;
//			PoleBit[119] = 0x80;
//			break;
//		case 20: //20点时需要修改的数组的值
//			PoleBit[108] = 0x03;
//			PoleBit[109] = 0x06;
//			PoleBit[110] = 0x06;
//			PoleBit[111] = 0x0C;
//			PoleBit[112] = 0x08;
//			PoleBit[113] = 0x18;
//			PoleBit[114] = 0x30;
//			PoleBit[115] = 0x30;
//			PoleBit[116] = 0x60;
//			PoleBit[117] = 0x40;
//			PoleBit[118] = 0xC0;
//			PoleBit[119] = 0x80;
//			break;
//		case 21: //21点时需要修改的数组的值
//			PoleBit[62] = 0xCC;
//			PoleBit[63] = 0xC4;
//			PoleBit[64] = 0x86;
//			PoleBit[111] = 0x01;
//			PoleBit[112] = 0x03;
//			PoleBit[113] = 0x07;
//			PoleBit[114] = 0x0E;
//			PoleBit[115] = 0x1C;
//			PoleBit[116] = 0x38;
//			PoleBit[117] = 0x70;
//			PoleBit[118] = 0xE0;
//			PoleBit[119] = 0xC0;
//			break;
//		case 22: //22点时需要修改的数组的值�
//			PoleBit[65] = 0x62;
//			PoleBit[66] = 0xE3;
//			PoleBit[67] = 0xC1;
//			PoleBit[115] = 0x03;
//			PoleBit[116] = 0x0F;
//			PoleBit[117] = 0x3C;
//			PoleBit[118] = 0x70;
//			PoleBit[119] = 0xE0;
//			break;
//		case 23: //23点时需要修改的数组的值
//			PoleBit[68] = 0x3D;
//			PoleBit[69] = 0xE1;
//			PoleBit[117] = 0x03;
//			PoleBit[118] = 0x3F;
//			PoleBit[119] = 0xC0;
//			break;
//		default:
//			break;
//	}
//
//	//逐个显示，总共要显示6页，每页有48个字节，故采用如下的显示方式
//	for(i=0;i<6;i++){
//		LCDWC(0x00 | ((Col+1-1)*6+2 & 0x0f ) );	// 列号低4bit
//		LCDWC(0x10 | ((Col+1-1)*6+2 & 0xf0 )>>4 );	// 列号高4bit
//		LCDWC(0xB0 | ( (Lin+i-1)&0x0f ) );	// 页号
//		for(j=0;j<48;j++){
//			LCDWD(PoleBit[j+i*48]);
//		}
//	}
//
//   //************************************
//	if(poletype==0)
//	{
//		DispEn(0,8,5,2,"00");
//		DispEn(0,7,9,2,"03");
//		DispEn(0,4,11,1,"0");
//		DispEn(0,5,11,1,"6");
//		DispEn(0,2,9,2,"09");
//		
//		DispEn(0,1,5,2,"12");
//		DispEn(0,2,1,2,"15");
//		DispEn(0,4,1,1,"1");
//		DispEn(0,5,1,1,"8");
//		DispEn(0,7,1,2,"21");
//	}
//	else
//	{
//	    DispEn(0,8,5,2,"00");
//		DispEn(0,7,9,2,"21");
//		DispEn(0,4,11,1,"1");
//		DispEn(0,5,11,1,"8");
//		DispEn(0,2,9,2,"15");
//		
//		DispEn(0,1,5,2,"12");
//		DispEn(0,2,1,2,"09");
//		DispEn(0,4,1,1,"0");
//		DispEn(0,5,1,1,"6");
//		DispEn(0,7,1,2,"03");
//	   
//	}
//
//
//}
