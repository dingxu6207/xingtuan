/* 各种测试程序
void LCDtst(void)  // 测试程序，用于main中测试LCD，逐行填黑然后逐行清白。
void KeyTst(void)  // 测试程序，用于main中测试键盘，也可作为编程例子。
void RTCTst(void)  // 测试程序，用于main中测试实时时钟，也可作为编程例子。
*/
/****************************************************************************
* 名称：LCD_tst
* 功能：测试屏幕。
* 入口参数：无
* 出口参数：
****************************************************************************/
//void LCDtst(void)
//{
////	uint32 i,j;
////	LCDWC(0x00);	// 列号低4bit
////	LCDWC(0x10);	// 列号高4bit
////	LCDWC(0xB0);	// 页号
////	for(i=132*8;i!=0;i--){
////		LCDWD(0xFF);
////		for(j=50*1000;j!=0;j--);
////		}
////	LCDWC(0x00);	// 列号低4bit
////	LCDWC(0x10);	// 列号高4bit
////	LCDWC(0xB0);	// 页号
////	for(i=132*8;i!=0;i--){
////		LCDWD(0x00);
////		for(j=50*1000;j!=0;j--);
////		}
//}

//void KeyTst(void)  // 测试程序，用于main中测试键盘，也可作为编程例子。
//{		
////	uint8 Keypad; // 从按键消息队列中获取的按键值
////	char KeyDisp[2];	// 测试程序用于显示键值的字符
//////	DispCn(1,1,4,5,"云南天文台") ;
//////	DispCn(0,2,1,12,"SkyVision控制器") ;
//////	DispCn(0,3,1,12,"键盘测试2008-7-6") ;
////	Keypad=GetKey();
////	if(Keypad&0x20)
////	{
//////		if(Keypad&0x40)DispCn(1,4,3,3,"长按:");
//////		else if(Keypad & 0x80) 	DispCn(1,4,3,3,"已按:");
//////		else DispCn(1,4,3,3,"短按:");
////		Keypad&=0x1f;
////		KeyDisp[1]=(Keypad%10)+0x30;
////		KeyDisp[0]=(Keypad/10)+0x30;
////		DispCn(0,4,8,2,KeyDisp);
////		DoKey();
////	}
////	else DispCn(1,4,1,7,"  无按键  ");
//
//}
//
//
//void RTCTst(void)  // 测试程序，用于main中测试实时时钟，也可作为编程例子。
//{		
////	uint32  RTCtime;
////	uint32  RTCdate;
////	uint32  RTCtmp;
////	char RTCdisp[19];
////	RTCtime = RTCtimeRead; // 读取完整时钟寄存器
////	RTCdate = RTCdateRead;	// 读取完整日期寄存器
////	// 取得年值
////	RTCtmp = (RTCdate>>16)&0xFFF;     
////	// 显示年值
////	RTCdisp[0]= (RTCtmp/1000+0x30);
////	RTCtmp = RTCtmp%1000;
////	RTCdisp[1]= (RTCtmp/100+0x30);
////	RTCtmp = RTCtmp%100;
////	RTCdisp[2]= (RTCtmp/10+0x30);
////	RTCdisp[3]= (RTCtmp%10+0x30);
////	RTCdisp[4]= '-';	// 
////	// 取得月值
////	RTCtmp = (RTCdate>>8)&0x0F;       
////	// 显示月值
////	RTCdisp[5]= (RTCtmp/10+0x30);
////	RTCdisp[6]= (RTCtmp%10+0x30);
////	RTCdisp[7]= '-';	// 
////	// 取得日值
////	RTCtmp = RTCdate&0x1F;            
////	// 显示日值
////	RTCdisp[8]= (RTCtmp/10+0x30);
////	RTCdisp[9]= (RTCtmp%10+0x30);
////	RTCdisp[10]= (0x20);	// ' '
////	// 取得星期值
//////	RTCtmp = (RTCtime>>24)&0x07;      
////	// 取得时的值
////	RTCtmp = (RTCtime>>16)&0x1F;
////	RTCdisp[11]= (RTCtmp/10+0x30);
////	RTCdisp[12]= (RTCtmp%10+0x30);
////	RTCdisp[13]= ':';	//
////	// 取得分的值		
////	RTCtmp = (RTCtime>>8)&0x3F;	
////	RTCdisp[14]= (RTCtmp/10+0x30);
////	RTCdisp[15]= (RTCtmp%10+0x30);
////	RTCdisp[16]= ':';	// ' '
////	// 取得秒的值	
////	RTCtmp = RTCtime&0x3F;			
////	RTCdisp[17]= (RTCtmp/10+0x30);
////	RTCdisp[18]= (RTCtmp%10+0x30);
////	DispEn(0,6,1,20,"KeyPad Testing......") ;
////	DispEn(0,5,1,19,RTCdisp) ;
//}
