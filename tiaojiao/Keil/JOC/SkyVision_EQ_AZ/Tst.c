/* ���ֲ��Գ���
void LCDtst(void)  // ���Գ�������main�в���LCD���������Ȼ��������ס�
void KeyTst(void)  // ���Գ�������main�в��Լ��̣�Ҳ����Ϊ������ӡ�
void RTCTst(void)  // ���Գ�������main�в���ʵʱʱ�ӣ�Ҳ����Ϊ������ӡ�
*/
/****************************************************************************
* ���ƣ�LCD_tst
* ���ܣ�������Ļ��
* ��ڲ�������
* ���ڲ�����
****************************************************************************/
//void LCDtst(void)
//{
////	uint32 i,j;
////	LCDWC(0x00);	// �кŵ�4bit
////	LCDWC(0x10);	// �кŸ�4bit
////	LCDWC(0xB0);	// ҳ��
////	for(i=132*8;i!=0;i--){
////		LCDWD(0xFF);
////		for(j=50*1000;j!=0;j--);
////		}
////	LCDWC(0x00);	// �кŵ�4bit
////	LCDWC(0x10);	// �кŸ�4bit
////	LCDWC(0xB0);	// ҳ��
////	for(i=132*8;i!=0;i--){
////		LCDWD(0x00);
////		for(j=50*1000;j!=0;j--);
////		}
//}

//void KeyTst(void)  // ���Գ�������main�в��Լ��̣�Ҳ����Ϊ������ӡ�
//{		
////	uint8 Keypad; // �Ӱ�����Ϣ�����л�ȡ�İ���ֵ
////	char KeyDisp[2];	// ���Գ���������ʾ��ֵ���ַ�
//////	DispCn(1,1,4,5,"��������̨") ;
//////	DispCn(0,2,1,12,"SkyVision������") ;
//////	DispCn(0,3,1,12,"���̲���2008-7-6") ;
////	Keypad=GetKey();
////	if(Keypad&0x20)
////	{
//////		if(Keypad&0x40)DispCn(1,4,3,3,"����:");
//////		else if(Keypad & 0x80) 	DispCn(1,4,3,3,"�Ѱ�:");
//////		else DispCn(1,4,3,3,"�̰�:");
////		Keypad&=0x1f;
////		KeyDisp[1]=(Keypad%10)+0x30;
////		KeyDisp[0]=(Keypad/10)+0x30;
////		DispCn(0,4,8,2,KeyDisp);
////		DoKey();
////	}
////	else DispCn(1,4,1,7,"  �ް���  ");
//
//}
//
//
//void RTCTst(void)  // ���Գ�������main�в���ʵʱʱ�ӣ�Ҳ����Ϊ������ӡ�
//{		
////	uint32  RTCtime;
////	uint32  RTCdate;
////	uint32  RTCtmp;
////	char RTCdisp[19];
////	RTCtime = RTCtimeRead; // ��ȡ����ʱ�ӼĴ���
////	RTCdate = RTCdateRead;	// ��ȡ�������ڼĴ���
////	// ȡ����ֵ
////	RTCtmp = (RTCdate>>16)&0xFFF;     
////	// ��ʾ��ֵ
////	RTCdisp[0]= (RTCtmp/1000+0x30);
////	RTCtmp = RTCtmp%1000;
////	RTCdisp[1]= (RTCtmp/100+0x30);
////	RTCtmp = RTCtmp%100;
////	RTCdisp[2]= (RTCtmp/10+0x30);
////	RTCdisp[3]= (RTCtmp%10+0x30);
////	RTCdisp[4]= '-';	// 
////	// ȡ����ֵ
////	RTCtmp = (RTCdate>>8)&0x0F;       
////	// ��ʾ��ֵ
////	RTCdisp[5]= (RTCtmp/10+0x30);
////	RTCdisp[6]= (RTCtmp%10+0x30);
////	RTCdisp[7]= '-';	// 
////	// ȡ����ֵ
////	RTCtmp = RTCdate&0x1F;            
////	// ��ʾ��ֵ
////	RTCdisp[8]= (RTCtmp/10+0x30);
////	RTCdisp[9]= (RTCtmp%10+0x30);
////	RTCdisp[10]= (0x20);	// ' '
////	// ȡ������ֵ
//////	RTCtmp = (RTCtime>>24)&0x07;      
////	// ȡ��ʱ��ֵ
////	RTCtmp = (RTCtime>>16)&0x1F;
////	RTCdisp[11]= (RTCtmp/10+0x30);
////	RTCdisp[12]= (RTCtmp%10+0x30);
////	RTCdisp[13]= ':';	//
////	// ȡ�÷ֵ�ֵ		
////	RTCtmp = (RTCtime>>8)&0x3F;	
////	RTCdisp[14]= (RTCtmp/10+0x30);
////	RTCdisp[15]= (RTCtmp%10+0x30);
////	RTCdisp[16]= ':';	// ' '
////	// ȡ�����ֵ	
////	RTCtmp = RTCtime&0x3F;			
////	RTCdisp[17]= (RTCtmp/10+0x30);
////	RTCdisp[18]= (RTCtmp%10+0x30);
////	DispEn(0,6,1,20,"KeyPad Testing......") ;
////	DispEn(0,5,1,19,RTCdisp) ;
//}
