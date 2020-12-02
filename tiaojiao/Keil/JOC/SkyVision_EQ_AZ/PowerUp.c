 /****************************************************************************
* �ļ�����PowerUp.c
* �ϵ��ʼ��
* ��ʹ��ȫ�ֱ����ͺ���
* FanYF@ynao.ac.cn
* �޸ģ�2008-7-5 ����� ������к���
*		2008-8-30 ����� ����PLL��Ƶ����
* ����˵����
*		void  PowerOnInit(void) // �ϵ��ʼ�� 
****************************************************************************/
// �޸ļ�¼  2008-11-17  �����  �ֱ�Ӳ������1.04��	 P0.2 P0.3 P0.11����ʹ�á���ʼ��SPI �Ǳ�Ƭѡ��
 uint8 BuzCount,BuzOnTime,BuzOffTime;
 void  PowerOnInit(void)
{  
//	Fan YF 20080830, New Time base config
    /* ����ϵͳ������ʱ�� */
    PLL0CON = 1;
#if ((Fcclk / 4) / Fpclk) == 1
    VPBDIV = 0;
#endif

#if ((Fcclk / 4) / Fpclk) == 2
    VPBDIV = 2;
#endif

#if ((Fcclk / 4) / Fpclk) == 4
    VPBDIV = 1;
#endif

#if (Fcco / Fcclk) == 2
    PLL0CFG = ((Fcclk / Fosc) - 1) | (0 << 5);
#endif
#if (Fcco / Fcclk) == 4
    PLL0CFG = ((Fcclk / Fosc) - 1) | (1 << 5);
#endif
#if (Fcco / Fcclk) == 8
    PLL0CFG = ((Fcclk / Fosc) - 1) | (2 << 5);
#endif
#if (Fcco / Fcclk) == 16
    PLL0CFG = ((Fcclk / Fosc) - 1) | (3 << 5);
#endif
    PLL0FEED = 0xaa;
    PLL0FEED = 0x55;
    while((PLL0STAT & (1 << 10)) == 0);
    PLL0CON = 3;
    PLL0FEED = 0xaa;
    PLL0FEED = 0x55;
    
/* ���ô洢������ģ�� */
    MAMCR = 2;
#if Fcclk < 20000000
    MAMTIM = 1;
#else
#if Fcclk < 40000000
    MAMTIM = 2;
#else
    MAMTIM = 3;
#endif
#endif
//	Fan YF 20080830, New Time base config


	// ���ùܽ�
	PINSEL0	= 0x00059505;
	PINSEL1	= 0x800046A8;
	PINSEL2	= 0x00000004;
//	IODIR0	= 0x0000BC8C;	   ԭ�ֱ�Ӳ��0.91��,�°��Ϊ1.24
	IODIR0	= 0x0001B480;		//1.05��Ӳ����P0.2 P0.3 P0.11����ʹ�á�P0.15 Torch2 11011010010000000
	IODIR1	= 0x03Cf0000;		//
	// �رշ�����������
	IOSET1	= BEEP;
	TORCH1OFF();	// 
 	TORCH2OFF();
	// ��ʼ��SPI
 	IO1SET = XB_CS;	   // �޸�ΪIO1
	IO1SET = HZK_CS;
	MSPI_Init();
	// ��ʼ��Һ����
	LCDInit();
	LCDRfrsh();
	LCDContrast(128);
	LCDBacklight(255);
	Key_Ini();//��ʼ�����̳���
	BuzOnTime=16;
	BuzOffTime=16;
	BuzCount = 0;
	TimerInit()	;
}






