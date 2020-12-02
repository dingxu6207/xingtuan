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
 *2	2008-9-3		Ìí¼ÓÁËÏÔÊ¾Ê±½ÇµÄ²¿·Ö³ÌÐò£¬¿ÉÒÔ¸ù¾ÝÓÃ»§ÊäÈëµÄÊ±½ÇÐÅÏ¢£¬¼´Ê±¡¢·Ö¡¢Ãë¶ÔÓ¦ÏÔÊ¾£»
 *1	2008-9-3		Íê³ÉÁË×î³õ°æ±¾µÄ±àÐ´¼°²âÊÔ£¬»ù±¾ÉÏ¿ÉÒÔÏÔÊ¾Ò»¸öÊ±ÖÓ£»
 *****************************************************************************************************/
 /*****************************************************************************************************
  *------------------------¸Ãº¯Êýµ÷ÓÃ·½·¨----------------------------------------
  *ÔÚÊ¹ÓÃ¸ÃÎÄ¼þÀ´¼ÆËãÄ³¸öÖ¸¶¨ÔÂ·ÝµÄÔÂÏàµÄÊ±ºò£¬Ö»ÐèÒªµ÷ÓÃº¯ÊýdispPole(int t)¼´¿É¡£
  *ÐèÒªÊäÈëµÄ²ÎÊýÊÇ£ºµ±Ç°Ê±¼ä¶ÔÓ¦µÄ±±¼«ÐÇµÄÊ±½Çt¡£
  *½á¹û£º¸ù¾ÝÊäÈëµÄÊ±½Ç£¬ÔÚLCDÉÏÏÔÊ¾µ±Ç°Ê±½Ç¶ÔÓ¦µÄÖ¸ÕëµÄÎ»ÖÃ¡£ÓÉÓÚ¾«¶ÈµÄ¹ØÏµ£¬ÔÚÕâÀïÖ»ÏÔÊ¾Ð¡Ê±¶ÔÓ¦µÄÖ¸Õë
  *		 Î»ÖÃ£¬ÒòÎªÈç¹ûÒªÏÔÊ¾·ÖµÄ»°¾ÍÌ«Ï¸Î¢ÁË£¬ÊµÏÖ±È½ÏÀ§ÄÑ¡£¶øÇÒÔÚLCDÉÏÐ¡Ê±¼äµÄ²î¾àÒ²²»ÊÇºÜÃ÷ÏÔ¡£
  *****************************************************************************************************/

/********************************************************************************************
 *Method: dispPole
 *Func: ÏÔÊ¾µ±Ç°Ê±¼ä¶ÔÓ¦µÄÊ±½ÇÐÅÏ¢µ½LCDÉÏ£¬ÐèÒªÊäÈëÖ¸¶¨µÄÊ±½ÇÖµ¡£
 *Params:uint8 t -- µ±Ç°Ê±¼ä¶ÔÓ¦µÄÊ±½ÇµÄÊ±¡£
 *		 uint8 m -- µ±Ç°Ê±¼ä¶ÔÓ¦µÄÊ±½ÇµÄ·Ö¡£
 *		 uint8 s -- µ±Ç°Ê±¼ä¶ÔÓ¦µÄÊ±½ÇµÄÃë¡£
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
//   //Áø¹âÇ¬ÔÚ´ËÐÞ¸Ä¼ÓÈëÊ±½Ç¼ÆËã	
//	//¼ÆËãÊ±½Ç
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
//	t=(int)hourganle;//µØÆ½×ø±ê·½Î»·µ»Ø¸³ÖµÓÚ·½Î»ÏÔÊ¾
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
//	t=(int)hourganle;//µØÆ½×ø±ê·½Î»·µ»Ø¸³ÖµÓÚ·½Î»ÏÔÊ¾
//	m=(int)((hourganle-t)*60.0);
//	s=(int)((hourganle-t-m/60.0)*3600);
//	
//		
//
//	if(m>=45)
//		t+=1;
//
//	switch(t){
//		case 0:	//0µãÊ±ÐèÒªÐÞ¸ÄµÄÊý×éµÄÖµ
//			PoleBit[71] = 0xFD;
//			PoleBit[72] = 0xFD;
//			PoleBit[119] = 0xFF;
//			PoleBit[120] = 0xFF;
//			break;
//		case 1:	//1µãÊ±ÐèÒªÐÞ¸ÄµÄÊý×éµÄÖµ
//			PoleBit[73] = 0xC1;
//			PoleBit[74] = 0xFD;
//			PoleBit[75] = 0x3D;
//			PoleBit[119] = 0xC0;
//			PoleBit[120] = 0xFC;
//			PoleBit[121] = 0x3F;
//			PoleBit[122] = 0x03;
//			break;
//		case 2:	//2µãÊ±ÐèÒªÐÞ¸ÄµÄÊý×éµÄÖµ
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
//		case 3:	//3µãÊ±ÐèÒªÐÞ¸ÄµÄÊý×éµÄÖµ
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
//		case 4:	//4µãÊ±ÐèÒªÐÞ¸ÄµÄÊý×éµÄÖµ
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
//		case 5:	//5µãÊ±ÐèÒªÐÞ¸ÄµÄÊý×éµÄÖµ
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
//		case 6:	//6µãÊ±ÐèÒªÐÞ¸ÄµÄÊý×éµÄÖµ
//			for(i=0;i<14;i++){
//				PoleBit[120+i] = 0x80;
//			}
//			for(i=0;i<14;i++){
//				PoleBit[168+i] = 0x01;
//			}
//			break;
//		case 7:	//7µãÊ±ÐèÒªÐÞ¸ÄµÄÊý×éµÄÖµ
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
//		case 8:	 //8µãÊ±ÐèÒªÐÞ¸ÄµÄÊý×éµÄÖµ
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
//		case 9:	//9µãÊ±ÐèÒªÐÞ¸ÄµÄÊý×éµÄÖµ
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
//		case 10: //10µãÊ±ÐèÒªÐÞ¸ÄµÄÊý×éµÄÖµ
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
//		case 11: //11µãÊ±ÐèÒªÐÞ¸ÄµÄÊý×éµÄÖµ
//			PoleBit[168] = 0x07;
//			PoleBit[169] = 0x7C;
//			PoleBit[170] = 0xC0;
//			PoleBit[218] = 0x87;
//			PoleBit[219] = 0x9C;
//			break;
//		case 12: //12µãÊ±ÐèÒªÐÞ¸ÄµÄÊý×éµÄÖµ
//			PoleBit[167] = 0xFF;
//			PoleBit[168] = 0xFF;
//			PoleBit[215] = 0xBF;
//			PoleBit[216] = 0xBF;
//			break;
//		case 13:  //13µãÊ±ÐèÒªÐÞ¸ÄµÄÊý×éµÄÖµ
//			PoleBit[165] = 0xC0;
//			PoleBit[166] = 0x7C;
//			PoleBit[167] = 0x07;
//			PoleBit[212] = 0x9C;
//			PoleBit[213] = 0x87;
//			break;
//		case 14: //14µãÊ±ÐèÒªÐÞ¸ÄµÄÊý×éµÄÖµ
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
//		case 15: //15µãÊ±ÐèÒªÐÞ¸ÄµÄÊý×éµÄÖµ
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
//		case 16: //16µãÊ±ÐèÒªÐÞ¸ÄµÄÊý×éµÄÖµ
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
//		case 17: //17µãÊ±ÐèÒªÐÞ¸ÄµÄÊý×éµÄÖµ
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
//		case 18: //18µãÊ±ÐèÒªÐÞ¸ÄµÄÊý×éµÄÖµ
//			for(i=0;i<14;i++){
//				PoleBit[106+i] = 0x80;
//			}
//			for(i=0;i<14;i++){
//				PoleBit[154+i] = 0x01;
//			}
//			break;
//		case 19: //19µãÊ±ÐèÒªÐÞ¸ÄµÄÊý×éµÄÖµ
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
//		case 20: //20µãÊ±ÐèÒªÐÞ¸ÄµÄÊý×éµÄÖµ
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
//		case 21: //21µãÊ±ÐèÒªÐÞ¸ÄµÄÊý×éµÄÖµ
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
//		case 22: //22µãÊ±ÐèÒªÐÞ¸ÄµÄÊý×éµÄÖµµ
//			PoleBit[65] = 0x62;
//			PoleBit[66] = 0xE3;
//			PoleBit[67] = 0xC1;
//			PoleBit[115] = 0x03;
//			PoleBit[116] = 0x0F;
//			PoleBit[117] = 0x3C;
//			PoleBit[118] = 0x70;
//			PoleBit[119] = 0xE0;
//			break;
//		case 23: //23µãÊ±ÐèÒªÐÞ¸ÄµÄÊý×éµÄÖµ
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
//	//Öð¸öÏÔÊ¾£¬×Ü¹²ÒªÏÔÊ¾6Ò³£¬Ã¿Ò³ÓÐ48¸ö×Ö½Ú£¬¹Ê²ÉÓÃÈçÏÂµÄÏÔÊ¾·½Ê½
//	for(i=0;i<6;i++){
//		LCDWC(0x00 | ((Col+1-1)*6+2 & 0x0f ) );	// ÁÐºÅµÍ4bit
//		LCDWC(0x10 | ((Col+1-1)*6+2 & 0xf0 )>>4 );	// ÁÐºÅ¸ß4bit
//		LCDWC(0xB0 | ( (Lin+i-1)&0x0f ) );	// Ò³ºÅ
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
