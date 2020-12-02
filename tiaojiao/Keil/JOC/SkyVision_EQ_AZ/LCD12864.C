/****************************************************************************
* 文件名：LMC12864.c
* 液晶显示程序
* 不使用全局变量和函数
* FanYF@ynao.ac.cn
* 修改：2008-7-1 范玉峰 完成所有函数
* 函数说明：
* 		void LCDRfrsh(void)，清除所有屏幕显示内容。
*		void LCDInit(void)，液晶屏初始化，开机上电时必须执行一次。
*		void LCDBacklight(unsigned char i)，设置背光亮度，0<=i<=255，0为关闭，值越大越亮，255最亮
*		void Eyelight(unsigned char i)，设置极轴镜照明亮度，0<=i<=255，0为关闭，值越大越亮，255最亮
*		void LCDWD(unsigned char LCDdat)  ， 向LCD显示RAM写数据。在程序中一般不单独使用。
*		void LCDWC(unsigned char LCDcmd) ，向LCD写命令。在程序中一般不单独使用。
*		void LCDtst(void)，测试用代码。向LCD左上角显示黑方块。
****************************************************************************/
// 修改记录  2008-11-17  范玉峰  手柄硬件更新1.04版液晶屏换用HOT12864-I(使用S6B0724控制器)，相应程序需要修改
//#define //
//#define //

//unsigned char	LCD_buf[8][128];//显示缓冲区，8页/8bits/128列
//像素排列方式如下[page][line]:bit
//[0][0]:bit0 [0][1]:bit0 [0][2]:bit0 [0][3]:bit0 ...... [0][127]:bit0 
//[0][0]:bit1 [0][1]:bit1 [0][2]:bit1 [0][3]:bit1 ...... [0][127]:bit1 
//...		...		...		...		...
//[0][0]:bit7 [0][1]:bit7 [0][2]:bit7 [0][3]:bit7 ...... [0][127]:bit7 
//[1][0]:bit0 [1][1]:bit0 [1][2]:bit0 [1][3]:bit0 ...... [1][127]:bit0 
//[1][0]:bit1 [1][1]:bit1 [1][2]:bit1 [1][3]:bit1 ...... [1][127]:bit1 
//...		...		...		...		...
//[1][0]:bit7 [1][1]:bit7 [1][2]:bit7 [1][3]:bit7 ...... [1][127]:bit7 
//...		...		...		...		...
//...		...		...		...		...
//...		...		...		...		...
//[7][0]:bit0 [7][1]:bit0 [7][2]:bit0 [7][3]:bit0 ...... [7][127]:bit0 
//[7][0]:bit1 [7][1]:bit1 [7][2]:bit1 [7][3]:bit1 ...... [7][127]:bit1 
//...		...		...		...		...
//[7][0]:bit7 [7][1]:bit7 [7][2]:bit7 [7][3]:bit7 ...... [7][127]:bit7 


/****************************************************************************
* 名称：LCDWR()
* 功能：液晶显示串行方式写数据
****************************************************************************/
void LCDWD(unsigned char LCDdat)   // 写数据
{	unsigned char i;
	IOCLR0 |= LCD_CS;			//片选
	IOSET1 |= LCD_CD;		//发数据
	for(i=0;i<8;i++)			//发送8bits
	{	
		IOCLR0 |= LCD_SCK;		//数据线上升延有效
		if(LCDdat & 0x80) IOSET0 |= LCD_SDA;
			else IOCLR0 |= LCD_SDA;
		LCDdat <<=1;
		IOSET0 |= LCD_SCK;
	}
	IOSET0 |= LCD_CS;			//片选
}

void LCDWC(unsigned char LCDcmd)  // 写命令
{	unsigned char i;
	IOCLR0 |= LCD_CS;			//片选
	IOCLR1 |= LCD_CD;		//发命令
	for(i=0;i<8;i++)			//发送8bits
	{	
		IOCLR0 |= LCD_SCK;		//数据线上升延有效
		if(LCDcmd & 0x80) IOSET0 |= LCD_SDA;
			else IOCLR0 |= LCD_SDA;
		LCDcmd <<=1;
		IOSET0 |= LCD_SCK;
	}
	IOSET0 |= LCD_CS;			//片选
}

/****************************************************************************
* 名称：LCD_Rfrsh()
* 功能：刷新屏幕。
* 入口参数：无
* 出口参数：
****************************************************************************/
void LCDRfrsh(void)
{
	int page,line;
	for(page=0;page<8;page++)
		{
			LCDWC(0xb0 | page);
			LCDWC(0x00);
			LCDWC(0x10);
			for(line=133;line>0;line--)LCDWD(0x00);
		}


}

/****************************************************************************
* 名称：LCDInit()
* 功能：液晶显示初始化程序
****************************************************************************/
void LCDInit(void)
{
// 打开背景光
// 复位 要求RST端最少保持低电平1us
 	LCDWC(0xe2);	// 复位
 	LCDWC(0xa2);	// 设置偏压比
 	LCDWC(0x26);	// 设置分压比
 	LCDWC(0x2f);	// 选择内部电源模式
 	LCDWC(0x81);	// 设置可编程电压调整模式
 	LCDWC(0x80);	// 设置电压编程寄存器
 	LCDWC(0xa6);	// 显示模式（A6正显;A7反显）
 	LCDWC(0xa4);	// 设置全显（A4正常;A5全黑）
 	LCDWC(0xc8);	// 设置输出方向（上下翻转）
 	LCDWC(0xaf);	// 显示开关
	LCDWC(0x60);	// 滚动起始行line32
	LCDRfrsh();		// 清显示内容
//  PWM初始化	
	PWMPR  = 0x00;			// 对pclk进行分频，PWM计数频率为Fpclk的1/10
	PWMMCR = 0x02;			// PWMMR0与PWMTC匹配时复位PWMTC
	PWMPCR = 0x2000;	  	// PWM5单边沿控制
			

	PWMMR0 = Fpclk/1000;			// PWM速率控制/计数初值
	/* 设置双边沿脉冲的脉宽和位置 */

	PWMMR5 =0 ;	// 关闭背光
	PWMMR2 =0 ;	// 关闭极轴镜
	
	 
	PWMLER = 0x21;			// 锁存所有PWM匹配值
	PWMTCR = 0x02;			// 复位PWMTC
	PWMTCR = 0x09;			// 使能PWM
}

/****************************************************************************
* 名称：LCDbACKLIGHT(i)
* 功能：液晶背景光调整PMW
入口参数0<=i<=255,值越大越亮
0表示关闭背景光
255表示全开
****************************************************************************/
void LCDBacklight(unsigned char i)
{
	if(i == 0) 	PWMMR5 = 0;
	else PWMMR5 = PWMMR0*i/255;
	PWMLER = 0x21;			// 锁存所有PWM匹配值

}
/****************************************************************************
* 名称：Eyelight(i)
* 功能：极轴镜照明亮度调整PWM
入口参数0<=i<=255,值越大越亮
0表示关闭背景光
255表示全开
****************************************************************************/
void Eyelight(unsigned char i)
{
	if(i == 0) 	PWMMR5 = 0;
	else PWMMR2 = PWMMR0*i/255;
	PWMLER = 0x21;			// 锁存所有PWM匹配值

}

void LCDContrast(unsigned char i)
{
 	i = (0x50 + i/2);
	LCDWC(0x81);	// 设置可编程电压调整模式
 	LCDWC(i);	// 设置电压编程寄存器
}
