// �޸ļ�¼  2008-11-17  �����  �ֱ�Ӳ������1.04��

//#define  XB_CS     1<<3   //�Ǳ�Ƭѡ				 0	   ԭ�ֱ�Ӳ��0.91��,�°��Ϊ1.24
#define  XB_CS     1<<24   //�Ǳ�Ƭѡ				 1	   1.04��Ӳ����	   									ע�⣺0.91��ΪP0��1.04����P1.
#define  HZK_CS    1<<25  //���ֿ�Ƭѡ				 1 
#define  LCD_CS    1<<10  //LCDƬѡ				 0 		
#define  LCD_CD    1<<23  //LCD CD					 1
//#define  LCD_SCK   1<<11  //LCD SCK		  		 0	 	ԭ�ֱ�Ӳ��0.91��,�°��ΪP0.12��	
#define  LCD_SCK   1<<12  //LCD SCK		  		 0	 	 	1.04��Ӳ����	
//#define  LCD_SDA   1<<12  //LCD SDA		  		 0		ԭ�ֱ�Ӳ��0.91��,�°��ΪP0.15��
#define  LCD_SDA   1<<15  //LCD SDA		  		 0			1.04��Ӳ����
#define  TORCH1     1<<13  //TORCH(����1)			 0
#define  TORCH2     1<<16  //TORCH(����2)			 0
#define  ISP_S     1<<14  //ISP����
#define  LED_SD    1<<15  //SD��ָʾ��			 	 0
#define  SD_W_CH    1<<16  //SDд�������			 0
#define  SD_I_CH    1<<20  //SD���뻤���			 1
#define  KEY1       1<<22  //��1					 0
#define  KEY2       1<<25  //��2					 0
#define  KEY3       1<<28  //��3					 0
#define  KEY4       1<<29  //��4					 0
#define  KEY5       1<<30  //��5					 0
#define  LED_ST1       1<<24  //״̬1ָʾ			 1
//#define  LED_ST2       1<<2  //״̬1ָʾ			 0		 ԭ�ֱ�Ӳ��0.91��,�°治��ʹ�á�
#define  KEYA       1<<19  //��Aָʾ				 1
#define  KEYB       1<<18  //��Bָʾ				 1
#define  KEYC       1<<17  //��Cָʾ				 1
#define  KEYD       1<<16  //��Dָʾ				 1
#define  IN_CH       1<<21  //�ⲿ�жϼ��		 1
#define  BEEP       1<<22  //������				 1

#define TORCH1ON() IOCLR0 = TORCH1
#define TORCH1OFF() IOSET0 = TORCH1
#define TORCH2ON() IOSET0 = TORCH2
#define TORCH2OFF() IOCLR0 = TORCH2




