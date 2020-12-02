 /****************************************************************************
* 文件名：Timers.c
* 定时器初始化，实时时钟函数
* 不使用全局变量和函数
* FanYF@ynao.ac.cn
* 修改：2008-7-5 范玉峰 完成所有函数
* 		2008-8-25 范玉峰 增加10ms计时，增加秒中断
* 函数说明：
* void  TimerInit(void) // 定时器上电初始化 
****************************************************************************/
//#define Timer0IntRate  100 //定时器0中断（按键扫描，蜂鸣器，LED闪烁计时）频率

// RTC实时时钟寄存器描述
#define	RTCtimeRead	CTIME0;	// 读取完整时钟寄存器，
/*
	(RTCtime>>24)&0x07;      // 取得星期值
	(RTCtime>>16)&0x1F;		// 取得时的值
	(RTCtime>>8)&0x3F;		// 取得分的值
	RTCtime&0x3F;			// 取得秒的值
*/
#define	RTCdateRead	CTIME1;	// 读取完整日期寄存器
/*
	(RTCdate>>16)&0xFFF;     // 取得年值
	(RTCdate>>8)&0x0F;       // 取得月值
	RTCdate&0x1F;            // 取得日值
*/
#define	RTCdayRead	CTIME2;	// 读取完整日期寄存器，365天数

//	设置RTC步骤
/*
	CCR = 0x10;				    // 暂停RTC
	YEAR = 2005;				// 设置年
	MONTH = 6;				    // 设置月
	DOM = 4;				    // 设置日
	DOW = 6;					// 设置星期
	HOUR = 15;					// 设置小时
	MIN = 20;					// 设置分钟
	SEC = 0;					// 设置秒
	CCR = 0x11;				    // 启动RTC
*/


 
void  TimerInit(void)
{
    /* 初始化定时器0，实现50Hz定时。
	   Fcclk=Fosc*4=11.0592MHz*4=44.2368MHz
	   Fpclk=Fcclk/4=44.2368MHz/4=11.0592MHz
	*/
//	时钟修改前
//	T0PR = 99;			    // 设置定时器分频为100分频，得110592Hz
//	T0MCR = 0x03;		    // 匹配通道0匹配中断并复位T0TC
//	T0MR0 = 110592/Timer0IntRate;	    // 比较值
//	T0TCR = 0x03;		    // 启动并复位T0TC
//	T0TCR = 0x01; 
//	
//	/* 设置定时器0中断IRQ */
//	VICIntSelect = 0x00;	// 所有中断通道设置为IRQ中断
//	VICVectCntl0 = 0x24;	// 定时器0中断通道分配最高优先级(向量控制器0)
//	VICVectCntl1 = 0x20 | 0x06;			// UART0分配到IRQ slot0，即最高优先级
//	VICVectCntl2 = 0x20 | 0x07;			// UART1分配到IRQ slot1，即最高优先级
//		
//	VICVectAddr0 = (uint32)Timer0ISR; 	// 设置中断服务程序地址向量
//	 
//
//
//	VICIntEnable = 0x00000010|(1 << 0x06)|(1 << 0x07);				// 使能定时器串口0串口1
//
//
//	//VICIntEnable=(1<<6);
//
// 
////	VICIntSelect = 0x00000000;			// 设置所有的通道为IRQ中断
//
////	VICIntEnable = 1 << 0x06;			// 使能UART0中断  
//
//
//
//
//
//
////	CIIR = 0x01;				    // 设置秒值的增量产生一次中断
//	时钟修改前
//修改后
  
	T0PR = 0;			    // 不分频
	T0MCR = 0x03;		    // 匹配通道0匹配中断并复位T0TC
	T0MR0 = Fpclk/100;		//匹配值为100，产生10ms中断
	T0TCR = 0x03;		    // 启动并复位T0TC
	T0TCR = 0x01; 
	
	/* 设置定时器0中断IRQ */
	VICIntSelect = 0x00;	// 所有中断通道设置为IRQ中断
	VICVectCntl0 = 0x20 | 0x04;	// 定时器0中断通道分配最高优先级(向量控制器0)
	VICVectAddr0 = (uint32)Timer0ISR; 	// 设置中断服务程序地址向量 
	VICIntEnable = (1<<0x04);				// 使能定时器0中断

 	/* 设置RTC秒中断IRQ */
	VICVectCntl3 = 0x20 | 13;	// RTC中断通道分配优先级1(向量控制器1)
	VICVectAddr3 = (uint32)RTC_ISR; 	// 设置中断服务程序地址向量 
	VICIntEnable = (1<<13);				// 使能RTC中断
	CIIR = 0x01;				    // 设置秒值的增量产生一次中断
	ILR = 0x03;				    // 清除中断
	CCR = 0x11;				    // 启动RTC		
	
	/* 设置串口接收中断IRQ */
	VICVectCntl1 = 0x20 | 0x06;			// UART0分配到IRQ slot0，即最高优先级
	VICVectCntl2 = 0x20 | 0x07;			// UART1分配到IRQ slot1，即最高优先级
	VICIntEnable = (1 << 0x07);				// 使能定时器串口0串口1
	VICIntEnable = (1 << 0x06);			// 使能UART0中断  	
	
/*	
	CCR = 0x10;				    // 暂停RTC
	YEAR = 2008;				// 设置年
	MONTH = 7;				    // 设置月
	DOM = 6;				    // 设置日
	DOW = 7;					// 设置星期
	HOUR = 23;					// 设置小时
	MIN = 06;					// 设置分钟
	SEC = 0;					// 设置秒
	CCR = 0x11;				    // 启动RTC
*/


}

