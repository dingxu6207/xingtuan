#include "stdbool.h"

/*********************************************************************************************************
** 函数名称: Timer0ISR
** 功能描述: 中断异常处理程序，用户根据需要自己改变程序
蜂鸣器控制
	BuzOnTime == 0;//关闭
	BuzOffTime == 0;//常开
	BuzOnTime<BuzOffTime;//循环促响（闪烁），开OnTime/10ms，以周期OffTime/10ms循环。
   	BuzOnTime>BuzOffTime;//响一次（闪亮一次），开OnTime/10ms后关闭。
使用全局变量uint8 BuzCount,BuzOnTime,BuzOffTime;
* 修改：2008-7-5 范玉峰 完成所有函数
* 		2008-8-25 范玉峰 增加10ms计时，增加秒中断
*			增加全局变量	char RTCms;//10毫秒计数
*			增加秒中断函数// 每秒中断服务

   	BuzOnTime<BuzOffTime;//循环促响（闪烁），开OnTime/32秒，以周期OffTime/32秒循环。
   	BuzOnTime>BuzOffTime;//响一次（闪亮一次），开OnTime/32秒后关闭。
使用全局变量uint8 BuzCount,BuzOnTime,BuzOffTime;


**-------------------------------------------------------------------------------------------------------
** 修改人: 范玉峰
** 日　期: 2008年7月6日		   调试键盘
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
//****************************************************************************
//在此加入要使用的全局变量
//用于倒计时时钟子程序
//日　期: 2008年8月24日

extern uint32 g_mObjTimer_sec;
extern uint32  BuzCnt;
extern uint8  BuzMode;  
extern uint8   sec_intr_counter; 
//*****************************************************************************
//柳光乾加入的全局变量和局部变量
extern uint32 g_nsysstatus;  //系统状态
extern bool g_mAutoBackMainShow;//过一定时间没操作，自动回主待机界面
extern int  g_mAutoBackMainShownum	;//多秒可以自动回主等机界面变量
//*****************************************************************************

char RTCms;//10毫秒计数值，每10ms由中断增1，每秒钟由秒中断清零

uint8 BuzCount,BuzOnTime,BuzOffTime;
void __irq Timer0ISR(void)
{
	PutKey(); // 扫描键盘
	if(!BuzOnTime)	{
		IOSET1 = BEEP;
		BuzCount = 0;
		}
	else if(!BuzOffTime){
		IOCLR1 = BEEP;
		BuzCount = 0;
		}
	else if(BuzCount<=BuzOnTime) {
		IOCLR1 = BEEP;
		BuzCount++;
		}
	else if(BuzCount<=BuzOffTime){
		IOSET1 = BEEP;
		BuzCount++;
		}
	else if(BuzOnTime>=BuzOffTime){
		IOSET1 = BEEP;
		BuzCount = 0;
		BuzOnTime = 0;
		}
	else {
		BuzCount =  0;
		}
	RTCms++;
//****************************************************************************

	if(g_mObjTimer_sec>0)
	{
	    sec_intr_counter--;
		if(sec_intr_counter==0)
		{
			sec_intr_counter=100;
			g_mObjTimer_sec--;
			if(g_mObjTimer_sec==0)
			{
				//BuzCnt=2000000;
				//BuzMode=1;
				  BuzOnTime=5*32;
                  BuzOffTime=BuzOnTime-1;
          
			}
		}
	}

//****************************************************************************
    T0IR = 0x01;	    			            // 清除中断标志
    VICVectAddr = 0x00;				            // 通知VIC中断处理结束

}


// 每秒中断服务
void __irq RTC_ISR(void)
{
	ILR = 0x03;
	RTCms = 0;// 10ms计数清零
//	测试用，每秒蜂鸣1次	
//	BuzOnTime=20; // 测试
//	BuzOffTime=20; // 测试
//	添加需每秒处理的程序
	  
//	添加需每秒处理的程序  
	VICVectAddr = 0;
	//*****************************
	//柳光乾加入30自动回待机界面 ,这 部份暂时不加
/*	if(g_mAutoBackMainShow)
	{ 
	  if(g_mAutoBackMainShownum>30)//30秒自动回主等机屏
	  {	
	     g_nsysstatus=0;//SYS_MAINSHOW;
		 g_mAutoBackMainShownum=0; 
	  }
	  g_mAutoBackMainShownum++;
	
	}
	else
	{
	  g_mAutoBackMainShownum=0;
	}  */
	//*****************************
}

