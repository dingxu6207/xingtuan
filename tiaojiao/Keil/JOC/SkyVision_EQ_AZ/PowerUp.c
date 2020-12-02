 /****************************************************************************
* 文件名：PowerUp.c
* 上电初始化
* 不使用全局变量和函数
* FanYF@ynao.ac.cn
* 修改：2008-7-5 范玉峰 完成所有函数
*		2008-8-30 范玉峰 增加PLL倍频设置
* 函数说明：
*		void  PowerOnInit(void) // 上电初始化 
****************************************************************************/
// 修改记录  2008-11-17  范玉峰  手柄硬件更新1.04版	 P0.2 P0.3 P0.11不再使用。初始化SPI 星表片选。
 uint8 BuzCount,BuzOnTime,BuzOffTime;
 void  PowerOnInit(void)
{  
//	Fan YF 20080830, New Time base config
    /* 设置系统各部分时钟 */
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
    
/* 设置存储器加速模块 */
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


	// 配置管脚
	PINSEL0	= 0x00059505;
	PINSEL1	= 0x800046A8;
	PINSEL2	= 0x00000004;
//	IODIR0	= 0x0000BC8C;	   原手柄硬件0.91版,新版改为1.24
	IODIR0	= 0x0001B480;		//1.05版硬件。P0.2 P0.3 P0.11不再使用。P0.15 Torch2 11011010010000000
	IODIR1	= 0x03Cf0000;		//
	// 关闭蜂鸣器和照明
	IOSET1	= BEEP;
	TORCH1OFF();	// 
 	TORCH2OFF();
	// 初始化SPI
 	IO1SET = XB_CS;	   // 修改为IO1
	IO1SET = HZK_CS;
	MSPI_Init();
	// 初始化液晶屏
	LCDInit();
	LCDRfrsh();
	LCDContrast(128);
	LCDBacklight(255);
	Key_Ini();//初始化键盘程序
	BuzOnTime=16;
	BuzOffTime=16;
	BuzCount = 0;
	TimerInit()	;
}






