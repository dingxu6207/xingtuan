/**
  ******************************************************************************
  * @file    main.c
  * @author  HeShouSheng(graycode@qq.com)
  * @version V1.0
  * @date    2017-11-20
  * @brief   SS Focuser
  ******************************************************************************
  */ 
	
#include "stm32f10x.h"
#include "stm32f10x_it.h"
#include "stm32f10x_flash.h"
#include "iodef.h"
#include "pfo.h"
#include "at24c02.h"
#include "bsp_ds18b20.h"
#include "bsp_SysTick.h"
#include "bsp_TiMbase.h"
#include "bsp_usart.h"
#include "bsp_usart_blt.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stdbool.h"
//64K空间，第0页-第31页用于程序存储，第32页-第63页用于数据存储（即0x0800 8000~0x0800 FFFF）
//#define WriteFlashAddress    ((u32)0x0800FC00)//存储到最后一页，地址范围：0x0800 FC00~0x0800 FFFF
typedef union//内部Flash数据格式
{
	struct
	{
		//u8 	IsCurrent; //当前页
		u16 PageWriteTimes;//单页读写次数
		u32 TotalWriteTimes;//总共读写次数
		u8  IsLowPower;
		u8  IsReverse; 		
		u8  SubDivision;
		u8  MotorSpeed;
		u8  MotorSpeedMax;
		u16 DelayCycle;
		//u16 DelayCycle2;
		int	Position;  //上次位置
	}CfgData;
	u32 SaveArray[5];
}UnionData; 
UnionData UD;
/*
typedef union//0-3
{
	int	Position;
	u8 SaveArray[4];
}UnionPos; 

UnionPos UP; 

typedef union//存在最后一页，擦写次数较少
{
    struct
    {
      u8    IsReverse;//4
			u8    SubDivision;//5
			u16   MotorSpeed;//6,7
    } MotorData;
		u8 SaveArray[4];
}UnionMotor; 
UnionMotor UM;
*/

char  *pVersion = "SS~SKY ROVER Focuser~SKY ROVER Co.,Ltd.~www.sky-rover.cn~service@sky-rover.com~0871-64605908";    //判断符号~设备名称型号~网址~电子邮箱~电话
//char  *pVersion = "SS~KC Focuser~KC.ASTRO~www.kctw.cn~ark@kctw.cn~0576-85389533";    

//char  *pBTName = "SSFocuser"; //BT SSID

bool  bIsHome         = 0; 
bool  bIsSlpMode    = true;      //Drv8825是否处于睡眠模式
bool  bIsInitial    = false;     //是否片上存储
bool  bIsLowPower   = true;     //true-低功耗模式
bool  bIsReverse    = false;     //电机是否反向
bool  bIsReverseRcv = false;

u8    uSubdivision = 8;       //步进电机细分
u8    uSubdivisionRcv = 8;    //步进电机细分
u8    uSpeed        = 9;
u8    uSpeedRcv     = 9;
u8    uSpeedMax     = 9;      //不同电机设置不一样
u8  	uSpeedCnt     = 3;
u8    uSpeedCntLim  = 3;
//HandBox
u8    uHandUState   = 0;
u8    uHandRState   = 0;
u8    uHandDState   = 0;
u16   uHandUCountPrv= 0;
u16   uHandRCountPrv= 0;
u16   uHandDCountPrv= 0;

u8    uSCurve[256]={0};       //加速曲线数据数组
u8    uSTot=0;                //加速曲线数据个数
u8    uSCnt=0;

//u8    uMoveState = 0;         //运动状态0-Idle,1-Move,2-Slew out&Slew in,3-Align
u8    uIsMoving   =0;	        //运动状态标志0-stop,1-move up,2-move down
int   iStepCount = 0;         //当前步数
int   iStepStart = 0;         //命令步数
int   iStepStop  = 0;         //命令步数
int   iStepDelt  = 0;					//命令步数
int   iStepTemp  = 0;					//命令步数

//bool  bTempAvail  =false;      //温度是否可用
float fTemperature=-273.15;

u16   uTimerCount=0;
u16   uSecondCount=0;
u16   uDelayCycle=300;//300S不操作进入睡眠模式
u16   uDelayCycle2=0;
u16   uDelayCountPrv=0;
u16   uDelayCountPrv2=0;

char  CmdBuff[32] = {0};     //回复字符串
char  ReplyBuff[128] = {0};  //回复字符串
char  TmpBuff[4] = {0};

u8    uCurrentPage=0;
u16   uPageWriteTimesMax=500;//每页存储500次换下一页
u16   uPageWriteTimes=0;
u32   uTotalWriteTimes=0;//总计读写次数
u32   uStartAdress=0x08008000;
u32   uStopAdress =0x0800FC00;
u32   uCurrentAdress=0x08008000;

unsigned char UART_RxPtr_Prv=0;    //上次读取位置
unsigned char BLTUART_RxPtr_Prv=0; //上次读取位置
unsigned char UART_RxCmd=0;        //未读命令个数
unsigned char BLTUART_RxCmd=0;     //未读命令个数

void delay_us(u32 nTimer)
{
	u32 i=0;
	for(i=0;i<nTimer;i++){
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
	}
}
void delay_ms(u32 nTimer)
{
	u32 i=1000*nTimer;
	delay_us(i);
}
bool wait_ms(u16 nTimer,u16 uStartCount)
{
	u16 uCountTmp=0;
	if(uTimerCount<uStartCount)
		uCountTmp=uTimerCount+65535-uStartCount;
	else
		uCountTmp=uTimerCount-uStartCount;	
	if(uCountTmp>=10*nTimer)
		return true;
	else
		return false;
}
//写Flash，成功返回1，失败返回0
u8 Write_Flash_MCU(u32 Address,u32 *buff, u8 len)
{    
	volatile FLASH_Status FLASHStatus;
	//u32 Address = WriteFlashAddress;
	FLASHStatus = FLASH_COMPLETE;
	FLASH_Unlock();
	FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
	//FLASHStatus = FLASH_ErasePage(WriteFlashAddress);
	FLASHStatus = FLASH_ErasePage(Address);
	if(FLASHStatus == FLASH_COMPLETE)
	{
		u8 k;
		for(k=0;(k<len) && (FLASHStatus == FLASH_COMPLETE);k++)
		{
				FLASHStatus = FLASH_ProgramWord(Address, buff[k]);
				Address = Address + 4;
		}        
		FLASH_Lock();
	}
	else
	{
		return 0;
	}
	if(FLASHStatus == FLASH_COMPLETE)
	{
		return 1;
	}
	return 0;
}

void Read_Flash_MCU(u32 Address,u32 *buff, u8 len)
{
	//u32 Address = WriteFlashAddress;
	u8 k;
	for(k=0;k<len;k++)
	{
		buff[k] =  (*(vu32*) Address);
		Address += 4;     
	}
}

//读取Flash并赋值给变量
void ReadCfg(void)
{
	/*
	Read_Flash(UM.SaveArray,4, 4);
	if((UM.MotorData.IsReverse<0)||(UM.MotorData.IsReverse>1))
		SetDefault();
	else
	{
		bIsReverse = UM.MotorData.IsReverse==0?false:true;
		uSubdivision = UM.MotorData.SubDivision;
		uSpeed  = UM.MotorData.MotorSpeed;
		Read_Flash(UP.SaveArray,0, 4);
		iStepCount=UP.Position;
	}
	*/
	//扫描后32页,查找当前页面
	u8 i=0;
	u32 TmpTotalWriteTimes=0;	
	uCurrentPage=0;
	for(i=0;i<32;i++)
	{
		uCurrentAdress=uStartAdress+1024*i;
		Read_Flash_MCU(uCurrentAdress,UD.SaveArray,5);
		if(UD.CfgData.PageWriteTimes>uPageWriteTimesMax)//65535未初始化的默认值为65535，比最大值uPageWriteTimesMax大说明未初始化
		{
			UD.CfgData.PageWriteTimes=0;
			UD.CfgData.TotalWriteTimes=0;
			UD.CfgData.IsLowPower=bIsLowPower;
			UD.CfgData.IsReverse=bIsReverse==false?0:1;
			UD.CfgData.SubDivision=uSubdivision;
			UD.CfgData.MotorSpeed=uSpeed;
			UD.CfgData.MotorSpeedMax=uSpeedMax;
			UD.CfgData.DelayCycle=uDelayCycle;
			//UD.CfgData.DelayCycle2=uDelayCycle2;
			UD.CfgData.Position=iStepCount;
			Write_Flash_MCU(uCurrentAdress,UD.SaveArray,5);
		}
		else if(UD.CfgData.TotalWriteTimes > TmpTotalWriteTimes)
		{
			TmpTotalWriteTimes=UD.CfgData.TotalWriteTimes;
			uCurrentPage=i;
		}	
	}
	//读取当前页
	uCurrentAdress=uStartAdress+1024*uCurrentPage;
	Read_Flash_MCU(uCurrentAdress,UD.SaveArray,5);
	//赋值给参数
	uPageWriteTimes=UD.CfgData.PageWriteTimes;
	uTotalWriteTimes =UD.CfgData.TotalWriteTimes ;
	bIsLowPower=UD.CfgData.IsLowPower;
	bIsReverse=UD.CfgData.IsReverse==0?false:true;
	uSubdivision=UD.CfgData.SubDivision;
	uSpeed=UD.CfgData.MotorSpeed;	
	uSpeedMax=UD.CfgData.MotorSpeedMax;
	uDelayCycle=UD.CfgData.DelayCycle;
	//uDelayCycle2=UD.CfgData.DelayCycle2;
	iStepCount=UD.CfgData.Position;	
}
//将变量写入Flash存储
void WriteCfg(void)
{
	/*
	UP.Position=iStepCount;
	Write_Flash(UP.SaveArray,0,4);
	UM.MotorData.IsReverse=bIsReverse==false?0:1;
	UM.MotorData.SubDivision=uSubdivision;
	UM.MotorData.MotorSpeed=uSpeed;
	Write_Flash(UM.SaveArray,4,4);
	*/
	u8 ret=0;
	uPageWriteTimes++;//设置读写次数+1
	uTotalWriteTimes++;
	if(uPageWriteTimes>uPageWriteTimesMax)
	{
		uPageWriteTimes=1;
		uCurrentAdress=uCurrentAdress+1024;
		if(uCurrentAdress>=uStopAdress)
			uCurrentAdress=uStartAdress;
	}
	
	UD.CfgData.IsLowPower=bIsLowPower;
	UD.CfgData.IsReverse=bIsReverse==false?0:1;
	UD.CfgData.SubDivision=uSubdivision;
	UD.CfgData.MotorSpeed=uSpeed;
	UD.CfgData.MotorSpeedMax=uSpeedMax;
	UD.CfgData.DelayCycle=uDelayCycle;
	//UD.CfgData.DelayCycle2=uDelayCycle2;
	UD.CfgData.Position=iStepCount;

	while(1)
	{
		UD.CfgData.PageWriteTimes =uPageWriteTimes;
		UD.CfgData.TotalWriteTimes =uTotalWriteTimes;
		ret=Write_Flash_MCU(uCurrentAdress,UD.SaveArray,5);
		if(ret==0)//写入失败则写入下一页，知道写入成功
		{
			uPageWriteTimes=1;
			uCurrentAdress=uCurrentAdress+1024;
			if(uCurrentAdress>=uStopAdress)
				uCurrentAdress=uStartAdress;
		}
		else
			break;
	}
}
/*
//读取Flash并赋值给变量
void ReadPosition(void)
{
	Read_Flash(UP.SaveArray,0, 4);
	iStepCount=UP.Position;
}
//将位置写入Flash存储
void WritePosition(void)
{
	UP.Position=iStepCount;
	Write_Flash(UP.SaveArray,0,4);
}
//读取Flash并赋值给变量
void ReadMotorPara(void)
{
	Read_Flash(UM.SaveArray,4, 4);
	bIsReverse = UM.MotorData.IsReverse==0?false:true;
	uSubdivision = UM.MotorData.SubDivision;
	uSpeed  = UM.MotorData.MotorSpeed;
}
//将电机参数写入Flash存储
void WriteMotorPara(void)
{
	UM.MotorData.IsReverse=bIsReverse==false?0:1;
	UM.MotorData.SubDivision=uSubdivision;
	UM.MotorData.MotorSpeed=uSpeed;
	Write_Flash(UM.SaveArray,4,4);
}
*/
float GetTemperature(void)
{
	//if(uMoveState==0)//为避免温度读取调用Systemtick影响PWM，空闲状态才读取温度
	if(uIsMoving==0)//为避免温度读取调用Systemtick影响PWM，空闲状态才读取温度
		fTemperature=DS18B20_Get_Temp();
	return fTemperature;
}
//通过某个串口发送
void SendTo(u8 MyComPort,char MyReplyBuff[])
{
	switch(MyComPort)
	{
		case 0:
			printf("%s", MyReplyBuff);
			break;
		case 1:
			BLTUsart_SendString(USART2,MyReplyBuff);
			break;
	}
	memset(MyReplyBuff,0,128);
}
//设置蓝牙
void SetBluetooth(void)
{
	char  TemBuff[24] = {0};
	sprintf(TemBuff, "AT");
	BLTUsart_SendString(USART2,TemBuff);
	delay_ms(100);
	memset(TemBuff,0,24);
	sprintf(TemBuff, "AT+NAME=%s", CmdBuff+2);
	BLTUsart_SendString(USART2,TemBuff);	
	delay_ms(100);
	memset(TemBuff,0,24);
	sprintf(TemBuff, "AT+RESET");
	BLTUsart_SendString(USART2,TemBuff);
	//硬重启蓝牙模块,硬重启丢失蓝牙名称
	//GPIO_ResetBits(BRST_GPIO_PORT, BRST_GPIO_PIN);
	delay_ms(500);
	//GPIO_SetBits(BRST_GPIO_PORT, BRST_GPIO_PIN);
}
//初始化加速曲线
void InitCurve(void)
{
	uSCurve[0]=19;//uSTot=19;
	uSCurve[1]=200;uSCurve[2]=8;          //6Hz
	uSCurve[3]=160;uSCurve[4]=16;         //8Hz
	uSCurve[5]=125;uSCurve[6]=24;         //10Hz     1
	uSCurve[7]=100;uSCurve[8]=24;         //1Hz
	uSCurve[9]=80;uSCurve[10]=32;         //15Hz
	uSCurve[11]=70;uSCurve[12]=32;        //18Hz
	uSCurve[13]=60;uSCurve[14]=40;        //20Hz     
	uSCurve[15]=50;uSCurve[16]=48;        //25Hz     2
	uSCurve[17]=40;uSCurve[18]=64;        //31Hz
	uSCurve[19]=30;uSCurve[20]=80;        //41Hz
	uSCurve[21]=24;uSCurve[22]=96;        //52Hz     3
	uSCurve[23]=20;uSCurve[24]=120;       //62Hz
	uSCurve[25]=16;uSCurve[26]=144;       //78Hz
	uSCurve[27]=13;uSCurve[28]=160;       //96Hz     4
	uSCurve[29]=10;uSCurve[30]=176;       //125Hz    
	uSCurve[31]=8;uSCurve[32]=192;        //156Hz    5
	uSCurve[33]=6;uSCurve[34]=208;        //208Hz    6
	uSCurve[35]=5;uSCurve[36]=224;        //250Hz    7
	uSCurve[37]=4;uSCurve[48]=240;        //312Hz    8
	uSCurve[39]=3;uSCurve[40]=248;        //416Hz    9
}
//设置电机反向
void SetReverse(void)
{
	bIsReverse = !bIsReverse; 
}

//设置细分
void SetDivision(u8 uDrvNum,u8 sMode)
{
	if(uDrvNum==0)
	{
		switch(sMode)
		{
			case 1://000
			{
				GPIO_ResetBits(M2_GPIO_PORT, M2_GPIO_PIN);
				GPIO_ResetBits(M1_GPIO_PORT, M1_GPIO_PIN);
				GPIO_ResetBits(M0_GPIO_PORT, M0_GPIO_PIN);
				break;
			}
			case 2://001
			{
				GPIO_ResetBits(M2_GPIO_PORT, M2_GPIO_PIN);
				GPIO_ResetBits(M1_GPIO_PORT, M1_GPIO_PIN);
				GPIO_SetBits(M0_GPIO_PORT, M0_GPIO_PIN);			
				break;
			}
			case 4://010
			{
				GPIO_ResetBits(M2_GPIO_PORT, M2_GPIO_PIN);	
				GPIO_SetBits(M1_GPIO_PORT, M1_GPIO_PIN);
				GPIO_ResetBits(M0_GPIO_PORT, M0_GPIO_PIN);
				break;
			}
			case 8://011
			{   
				GPIO_ResetBits(M2_GPIO_PORT, M2_GPIO_PIN);
				GPIO_SetBits(M1_GPIO_PORT, M1_GPIO_PIN);
				GPIO_SetBits(M0_GPIO_PORT, M0_GPIO_PIN);	
				break;
			}
			case 16://100
			{
				GPIO_SetBits(M2_GPIO_PORT, M2_GPIO_PIN);	   
				GPIO_ResetBits(M1_GPIO_PORT, M1_GPIO_PIN);
				GPIO_ResetBits(M0_GPIO_PORT, M0_GPIO_PIN);		
				break;
			}
			case 32://111
			{
				GPIO_SetBits(M2_GPIO_PORT, M2_GPIO_PIN);  
				GPIO_SetBits(M1_GPIO_PORT, M1_GPIO_PIN);
				GPIO_SetBits(M0_GPIO_PORT, M0_GPIO_PIN);		
				break;
			}
		}
	}
#ifdef Focuser_C_DRV8825
	else if(uDrvNum==1)
	{
		switch(sMode)
		{
			case 1://000
			{
				GPIO_ResetBits(M22_GPIO_PORT, M22_GPIO_PIN);
				GPIO_ResetBits(M12_GPIO_PORT, M12_GPIO_PIN);
				GPIO_ResetBits(M02_GPIO_PORT, M02_GPIO_PIN);
				break;
			}
			case 2://001
			{
				GPIO_ResetBits(M22_GPIO_PORT, M22_GPIO_PIN);
				GPIO_ResetBits(M12_GPIO_PORT, M12_GPIO_PIN);
				GPIO_SetBits(M02_GPIO_PORT, M02_GPIO_PIN);			
				break;
			}
			case 4://010
			{
				GPIO_ResetBits(M22_GPIO_PORT, M22_GPIO_PIN);	
				GPIO_SetBits(M12_GPIO_PORT, M12_GPIO_PIN);
				GPIO_ResetBits(M02_GPIO_PORT, M02_GPIO_PIN);
				break;
			}
			case 8://011
			{   
				GPIO_ResetBits(M22_GPIO_PORT, M22_GPIO_PIN);
				GPIO_SetBits(M12_GPIO_PORT, M12_GPIO_PIN);
				GPIO_SetBits(M02_GPIO_PORT, M02_GPIO_PIN);	
				break;
			}
			case 16://100
			{
				GPIO_SetBits(M22_GPIO_PORT, M22_GPIO_PIN);	   
				GPIO_ResetBits(M12_GPIO_PORT, M12_GPIO_PIN);
				GPIO_ResetBits(M02_GPIO_PORT, M02_GPIO_PIN);		
				break;
			}
			case 32://111
			{
				GPIO_SetBits(M22_GPIO_PORT, M22_GPIO_PIN);  
				GPIO_SetBits(M12_GPIO_PORT, M12_GPIO_PIN);
				GPIO_SetBits(M02_GPIO_PORT, M02_GPIO_PIN);		
				break;
			}
		}
	}
#endif
}
//设置速度
void SetSpeed(u8 uSetSpeed)
{
	if(uSetSpeed>uSpeedMax)
		uSetSpeed=uSpeedMax;
	switch(uSetSpeed)
	{
		case 1:
			uSpeed=1;
			uSpeedCntLim=125;//10Hz
			break;
		case 2:
			uSpeed=2;
			uSpeedCntLim=50;//25Hz
			break;
		case 3:
			uSpeed=3;
			uSpeedCntLim=24;//52Hz
			break;
		case 4:
			uSpeed=4;
			uSpeedCntLim=13;//96Hz
			break;
		case 5:
			uSpeed=5;
			uSpeedCntLim=8;//156Hz
			break;
		case 6:
			uSpeed=6;
			uSpeedCntLim=6;//208Hz
			break;
		case 7:
			uSpeed=7;
			uSpeedCntLim=5;//250Hz
			break;
		case 8:
			uSpeed=8;
			uSpeedCntLim=4;//312Hz
			break;
		case 9:
			uSpeed=9;
			uSpeedCntLim=3;//416Hz
			break;
	}
}
//初始化电机
void InitMotor(void)
{
	uIsMoving = 0;
	SetDivision(0,uSubdivision);
	SetSpeed(uSpeed);
}
//往外转动
void SlewOut(void)//:F+#
{
	//起始速度，用于加速
	uSCnt=0;
	uSpeedCnt=uSCurve[uSCnt*2+1];
	iStepDelt=uSCurve[uSCnt*2+2];
	//设置电机运动方向
	if(bIsReverse)
		GPIO_ResetBits(DIR_GPIO_PORT, DIR_GPIO_PIN);  
	else
		GPIO_SetBits(DIR_GPIO_PORT, DIR_GPIO_PIN);    		
	//使能输出
	//GPIO_ResetBits(EN_GPIO_PORT, EN_GPIO_PIN);
	if(bIsSlpMode)//唤醒睡眠
	{
		GPIO_SetBits(SLP_GPIO_PORT, SLP_GPIO_PIN);
		bIsSlpMode=false;
	}
	delay_ms(100);
	uSecondCount=0;
	uIsMoving = 1;//运动状态标志	
}
//往里转动
void SlewIn(void)//:F-#
{	
	//起始速度，用于加速
	uSCnt=0;
	uSpeedCnt=uSCurve[uSCnt*2+1];
	iStepDelt=uSCurve[uSCnt*2+2];
	//设置电机运动方向
	if(bIsReverse)
		GPIO_SetBits(DIR_GPIO_PORT, DIR_GPIO_PIN);    
	else
		GPIO_ResetBits(DIR_GPIO_PORT, DIR_GPIO_PIN); 
	//使能输出
	//GPIO_ResetBits(EN_GPIO_PORT, EN_GPIO_PIN);
	if(bIsSlpMode)//唤醒睡眠
	{
		GPIO_SetBits(SLP_GPIO_PORT, SLP_GPIO_PIN);
		bIsSlpMode=false;
	}
	delay_ms(100);
	uSecondCount=0;
	uIsMoving = 2;
}
//转动固定步数
void MoveTo()
{ 
	if(iStepStop>iStepStart)
	{
		SlewOut();
	}
	else
	{
		SlewIn();		
	}
}

//停止
void Halt(void)
{
	//if((iStepStop%uSubdivision)!=0)
	//{
	if(uIsMoving==1)
	{
		iStepStop=(iStepCount/uSubdivision+10)*uSubdivision;//10步后停止
	}
	else if(uIsMoving==2)
	{
		iStepStop=(iStepCount/uSubdivision-10)*uSubdivision;
	}
	//}
	//uMoveState = 0;
	//uIsMoving=0;
	//禁止输出
	//GPIO_SetBits(EN_GPIO_PORT, EN_GPIO_PIN);
	//进入睡眠模式	
	//GPIO_ResetBits(SLP_GPIO_PORT, SLP_GPIO_PIN);
}
void FaultCheck(void)
{
	#ifdef Focuser_B_DRV8825//错误输出低电平
	if(GPIO_ReadInputDataBit(FLT_GPIO_PORT,FLT_GPIO_PIN)==0) 
	{
		Halt();
		printf("%s", ":Driver Fault#\r\n");
	}
	#endif
	#ifdef Focuser_B_TMC2208//错误输出高电平
	if(GPIO_ReadInputDataBit(DIAG_GPIO_PORT,DIAG_GPIO_PIN)==1) 
	{
		Halt();
		printf("%s", ":Driver Fault#\r\n");
	}
	#endif
	#ifdef Focuser_C_DRV8825
	if(GPIO_ReadInputDataBit(FLT_GPIO_PORT,FLT_GPIO_PIN)==0)  
	{
		Halt();
		printf("%s", ":Driver Fault#\r\n");
	}
	#endif
}
//查找下一个
u8 Next(u8 Prv)
{
	if(Prv<255)
		return Prv+1;
	else //255
		return 0;
}
//读取一条命令，去掉头尾:#，指针指向下一条命令
u8 ReadCmd(unsigned char *RxBuffer,unsigned char *Ptr)
{
	u8 Flag=0,i=0;
	memset(CmdBuff,0,32);
	for(;;)
	{
		//下面三条判断的顺序不能调整
		if(RxBuffer[*Ptr]==35)//#结束命令
		{ 
			if(Flag==1)//命令完整
			{
				CmdBuff[i]=NULL;//没有结束符，split函数会出错
				Flag=2;
			}
			else
				Flag=3;
		}
		if(Flag==1)//:后才开始读取命令字符串
		{
			CmdBuff[i]=RxBuffer[*Ptr];
			i++;
		}
		if(RxBuffer[*Ptr]==58)//:
		{
			Flag=1;
			i=0;
		}
		//循环读取串口缓冲区
		*Ptr=Next(*Ptr);
		if(Flag>1)//跳出循环
			break;
	}
	return i;
}
//命令处理
bool CmdProcess(u8 MyComPort,unsigned char *RxBuffer,unsigned char *Ptr)
{
	if(ReadCmd(RxBuffer,Ptr)<1)
		return false;
	memset(ReplyBuff,0,128);
	if(CmdBuff[0]=='F')//调焦器命令以F开头
	{
		switch (CmdBuff[1])
		{
			case '?':  //Focuser version
				{
					sprintf(ReplyBuff, ":?%s#\r\n", pVersion);
					SendTo(MyComPort,ReplyBuff);
					break;
				}
			case '+': 	//Slew Out		 
				{
					iStepStop=(iStepCount/uSubdivision+500)*uSubdivision;//多设置500步保证500mS内不会停掉
					if(uIsMoving == 1)
						;
					else
					{
						sprintf(ReplyBuff, ":+#\r\n");
						SendTo(MyComPort,ReplyBuff);
						Halt();
						while(uIsMoving)//等待完全停止
						{
							delay_ms(100);
						}
						iStepStart=iStepCount;//起始位置，用于加速
						SlewOut();
					}
					break;
				}
			case '-':   //Slew In
				{
					iStepStop=(iStepCount/uSubdivision-500)*uSubdivision;//多设置500步保证500秒内不会停掉
					if(uIsMoving == 2)
						;
					else
					{
						sprintf(ReplyBuff, ":-#\r\n");
						SendTo(MyComPort,ReplyBuff);
						Halt();
						while(uIsMoving)//等待完全停止
						{
							delay_ms(100);
						}
						iStepStart=iStepCount;//起始位置，用于加速
						SlewIn();
					}	
					break;
				}
			case 'a': //  			
				{
					sprintf(ReplyBuff,":a%d~%d~%.2f~%d~%d~%d~%d~%d#\r\n", iStepCount/uSubdivision,uIsMoving,GetTemperature(),bIsReverse,uSubdivision,uSpeed,bIsLowPower,bIsInitial);
					SendTo(MyComPort,ReplyBuff);
					break;
				}
			case 'B': // Busy Status  			
				{
					sprintf(ReplyBuff,":B%d#\r\n", uIsMoving);
					SendTo(MyComPort,ReplyBuff);
					break;
				}
			case 'b': //Bluetooth setting  			
				{
					sprintf(ReplyBuff, ":b#\r\n");
					SendTo(MyComPort,ReplyBuff);
					SetBluetooth();		
					break;
				}
			case 'D':  //Define current position			
				{
					sprintf(ReplyBuff, ":D#\r\n");
					SendTo(MyComPort,ReplyBuff);
					Halt();
					while(uIsMoving)//等待完全停止
					{
						delay_ms(100);
					}
					iStepCount = atoi((char const *)CmdBuff+2)*uSubdivision;
					break;
				}
			case 'I': //		
				{
					sprintf(ReplyBuff, ":I#\r\n");
					SendTo(MyComPort,ReplyBuff);
					if(bIsInitial != (CmdBuff[2] == '1')?true:false)
					{
						bIsInitial = !bIsInitial;							
					}
					break;
				}
			case 'i': //		
				{
					sprintf(ReplyBuff,":i%d#\r\n",bIsInitial);
					SendTo(MyComPort,ReplyBuff);
					break;
				}
			case 'L': //		
				{
					sprintf(ReplyBuff, ":L#\r\n");
					SendTo(MyComPort,ReplyBuff);
					Halt();
					while(uIsMoving)//等待完全停止
					{
						delay_ms(100);
					}
					if(bIsLowPower != (CmdBuff[2] == '1')?true:false)
					{
						bIsLowPower = !bIsLowPower;	
						if(!bIsLowPower)
						{
							GPIO_SetBits(SLP_GPIO_PORT, SLP_GPIO_PIN);
							bIsSlpMode=false;
						}
						else
						{
							GPIO_ResetBits(SLP_GPIO_PORT, SLP_GPIO_PIN);
							bIsSlpMode=true;
						}							
					}
					break;
				}
			case 'l': //		
				{
					sprintf(ReplyBuff,":l%d#\r\n",bIsLowPower);
					SendTo(MyComPort,ReplyBuff);
					break;
				}
			case 'M': //Set Motor subdivision
				{
					sprintf(ReplyBuff, ":M#\r\n");
					SendTo(MyComPort,ReplyBuff);
					//停止运动
					Halt();
					while(uIsMoving)//等待完全停止
					{
						delay_ms(100);
					}
					/*
					//设置细分
					memset(TmpBuff,0,8);
					TmpBuff[0]=CmdBuff[2];TmpBuff[1]=CmdBuff[3];TmpBuff[2]=CmdBuff[4];
					uSubdivisionRcv = atoi((char const *)TmpBuff+0);
					if(uSubdivisionRcv!=uSubdivision)//不同才设置
					{
						switch(uSubdivisionRcv)//判断有效性
						{
							case 1:
							case 2:
							case 4:
							case 8:
							case 16:
							case 32:
							{
								//计算当前细分下的计数值
								iStepCount = (iStepCount *uSubdivisionRcv)/uSubdivision;
								uSubdivision=uSubdivisionRcv;
								SetDivision(0,uSubdivision);
								break;
							}
						}
					}
					*/
					break;
				}
			case 'm': //Get Subdivision		
				{
					sprintf(ReplyBuff,":m%d#\r\n",uSubdivision);
					SendTo(MyComPort,ReplyBuff);
					break;
				}
			case 'P':    //Move command
				{
					sprintf(ReplyBuff, ":P#\r\n");
					SendTo(MyComPort,ReplyBuff);
					Halt();
					while(uIsMoving)//等待完全停止
					{
						delay_ms(100);
					}
					iStepStop = atoi((char const *)CmdBuff+2)*uSubdivision;
					iStepStart=iStepCount;//起始位置，用于加速
					if(iStepStart!=iStepStop)//不相等才执行
					{
						MoveTo();
					}
					break;
				}
			case 'p':  //Get Position
				{
					sprintf(ReplyBuff,":p%d#\r\n", iStepCount/uSubdivision);
					SendTo(MyComPort,ReplyBuff);
					break;
				}
			case 'Q': 	//Halt    
				{
					Halt();
					sprintf(ReplyBuff, ":Q#\r\n");
					SendTo(MyComPort,ReplyBuff);				
					break;
				}
			case 'R': //Reverse			
				{
					sprintf(ReplyBuff, ":R#\r\n");
					SendTo(MyComPort,ReplyBuff);
					Halt();
					while(uIsMoving)//等待完全停止
					{
						delay_ms(100);
					}
					//设置反向
					if(bIsReverse != (CmdBuff[2] == '1')?true:false)
					{
						bIsReverse = !bIsReverse;		
					}
					break;
				}
			case 'r': //		
				{
					sprintf(ReplyBuff,":r%d#\r\n",bIsReverse);
					SendTo(MyComPort,ReplyBuff);
					break;
				}
			case 't':   //Get temperature
				{
					sprintf(ReplyBuff,":t%.2f#\r\n", GetTemperature());//保留2位小数
					SendTo(MyComPort,ReplyBuff);
					break;
				}
			case 'V': //Set Motor Speed
				{
					sprintf(ReplyBuff, ":V#\r\n");
					SendTo(MyComPort,ReplyBuff);
					uSpeedRcv=atoi((char const *)CmdBuff+2);
					SetSpeed(uSpeedRcv);
					break;
				}
			case 'v': //Get Motor Speed		
				{
					sprintf(ReplyBuff,":v%d#\r\n",uSpeed);
					SendTo(MyComPort,ReplyBuff);
					break;
				}
			case 'w':  
			{
				sprintf(ReplyBuff, ":w%d~%d~%d#\r\n",uCurrentPage,uPageWriteTimes,uTotalWriteTimes);
				SendTo(MyComPort,ReplyBuff);
				break;
			}
			case 'X': //Set Motor SpeedMax
				{
					sprintf(ReplyBuff, ":X#\r\n");
					SendTo(MyComPort,ReplyBuff);
					uSpeedRcv=atoi((char const *)CmdBuff+2);
					if((uSpeedRcv>0)&&(uSpeedRcv<10))
					{
						uSpeedMax =uSpeedRcv;
						SetSpeed(uSpeed);//最大值改变后需要重新设置速度，避免速度大于最大值
					}
					break;
				}
			case 'x':  
			{
				sprintf(ReplyBuff, ":x%d#\r\n",uSpeedMax);
				SendTo(MyComPort,ReplyBuff);
				break;
			}
			case 'Y':  
				{
					sprintf(ReplyBuff, ":Y#\r\n");
					SendTo(MyComPort,ReplyBuff);
					if(uDelayCycle != atoi((char const *)CmdBuff+2))
					{
						uDelayCycle = atoi((char const *)CmdBuff+2);
					}
					break;
				}
			case 'y': 
				{
					sprintf(ReplyBuff, ":y%d#\r\n",uDelayCycle);
					SendTo(MyComPort,ReplyBuff);
					break;
				}
			case 'Z':  
				{
					sprintf(ReplyBuff, ":Z#\r\n");
					SendTo(MyComPort,ReplyBuff);
					if(uDelayCycle2 != atoi((char const *)CmdBuff+2))
					{
						uDelayCycle2 = atoi((char const *)CmdBuff+2);
					}
					break;
				}
			case 'z': 
				{
					sprintf(ReplyBuff, ":z%d#\r\n",uDelayCycle2);
					SendTo(MyComPort,ReplyBuff);
					break;
				}
			default://Unknow Command
				{
					sprintf(ReplyBuff, ":U#\r\n");
					SendTo(MyComPort,ReplyBuff);
					break;
				}
		}
	}
	return true;
}
/*
void KeyEvent(void)
{
	#ifdef Focuser_B_TMC2208
		//Up
		if(GPIO_ReadInputDataBit(HU_GPIO_PORT,HU_GPIO_PIN)==0) 
		{
			if(uHandUState==0)
			{
				uHandUCountPrv=uTimerCount;
				uHandUState=1;
			}
			else if(uHandUState==1)
			{
				if(wait_ms(100,uHandUCountPrv))//100mS消除抖动
					uHandUState=2;
			}
			else if(uHandUState==2)
			{
				//if(wait_ms(1000,uDelayCountPrv))
				iStepStop=(iStepCount/uSubdivision+100)*uSubdivision;//多设置500步保证500mS内不会停掉
				if(uIsMoving == 1)
					;
				else
				{
					Halt();
					while(uIsMoving)//等待完全停止
					{
						delay_ms(100);
					}
					iStepStart=iStepCount;//起始位置，用于加速
					SlewOut();
				}
			}
		}
		else if(GPIO_ReadInputDataBit(HU_GPIO_PORT,HU_GPIO_PIN)==1)
		{
			if(uHandUState==2)
				Halt();
			uHandUState=0;
		}
		//Down
		if(GPIO_ReadInputDataBit(HD_GPIO_PORT,HD_GPIO_PIN)==0) 
		{
			if(uHandDState==0)
			{
				uHandDCountPrv=uTimerCount;
				uHandDState=1;
			}
			else if(uHandDState==1)
			{
				if(wait_ms(100,uHandDCountPrv))//100mS消除抖动
					uHandDState=2;
			}
			else if(uHandDState==2)
			{
				iStepStop=(iStepCount/uSubdivision-100)*uSubdivision;//多设置500步保证500mS内不会停掉
				if(uIsMoving == 2)
					;
				else
				{
					Halt();
					while(uIsMoving)//等待完全停止
					{
						delay_ms(100);
					}
					iStepStart=iStepCount;//起始位置，用于加速
					SlewIn();
				}	
			}
		}
		else if(GPIO_ReadInputDataBit(HD_GPIO_PORT,HD_GPIO_PIN)==1) 
		{
			if(uHandDState==2)
				Halt();
			uHandDState=0;
		}
		//Right
		if(GPIO_ReadInputDataBit(HR_GPIO_PORT,HR_GPIO_PIN)==0) 
		{
			if(uHandRState==0)
			{
				uHandRCountPrv=uTimerCount;
				uHandRState=1;
			}
			else if(uHandRState==1)
			{
				if(wait_ms(50,uHandRCountPrv))//50mS消除抖动
					uHandRState=2;
			}
		}
		else if(GPIO_ReadInputDataBit(HR_GPIO_PORT,HR_GPIO_PIN)==1) 
		{
			if(uHandRState==2)
			{
				if(uSpeed>=uSpeedMax)
					uSpeed=1;
				else
					uSpeed++;
				SetSpeed(uSpeed);	
			}
			uHandRState=0;
		}
		#endif
}
*/
//主程序
int main()
{	
	SystemInit();
	
	//SysTick_Init();
	
	MY_GPIO_Config();
	
	TIM1_Init(99,71);//100US定时器，10KHz
	
	//TIM2_Init(99,71);//100US定时器，10KHz
	
	//TIM3_Init(9999,7199);//1S定时器，1Hz
	
	PF_Config();

	USART_Config();
	
	#ifdef Focuser_C_DRV8825
	BLT_USART_Config();
	#endif
	#ifdef Focuser_C_TMC2208
	BLT_USART_Config();
	#endif
	//AT24C02
	//I2C_init();	
	
	//初始化温度传感器
	DS18B20_Init();
	DS18B20_Get_Temp();//第一次读取返回固定值
	delay_ms(1000);

	//初始化参数
	ReadCfg();
	//初始化加减速曲线
	InitCurve();
	//初始化电机
	InitMotor();
	
	if(!bIsLowPower)
	{
		GPIO_SetBits(SLP_GPIO_PORT, SLP_GPIO_PIN);
		bIsSlpMode=false;
	}
	else
	{
		GPIO_ResetBits(SLP_GPIO_PORT, SLP_GPIO_PIN);
		bIsSlpMode=true;
	}

	while(1)
	{	
		//处理串口1数据
		while(UART_RxCmd>0)
		{
			UART_RxCmd--;//命令计数减一
			CmdProcess(0,UART_RxBuffer,&UART_RxPtr_Prv);
		}	
		#ifdef Focuser_C_DRV8825
	  //处理串口2数据	
	  while(BLTUART_RxCmd>0)
	  { 
			BLTUART_RxCmd--;//命令计数减一
			CmdProcess(1,BLTUART_RxBuffer,&BLTUART_RxPtr_Prv);
	  }
		#endif
		#ifdef Focuser_C_TMC2208
	  //处理串口2数据	
	  while(BLTUART_RxCmd>0)
	  { 
			BLTUART_RxCmd--;//命令计数减一
			CmdProcess(1,BLTUART_RxBuffer,&BLTUART_RxPtr_Prv);
	  }
		#endif
		
		//KeyEvent();//五向按键查询
		
		//低功耗模式如果超时不操作则DRV8825进入睡眠
		if((bIsLowPower)&&(!bIsSlpMode)&&(uIsMoving==0))
		{
			if(wait_ms(1000,uDelayCountPrv))
			{
				uSecondCount++;
				uDelayCountPrv=uTimerCount;
			}
			if(uSecondCount>=uDelayCycle)
			{
				GPIO_ResetBits(SLP_GPIO_PORT, SLP_GPIO_PIN);
				bIsSlpMode=true;
			}		
		}
		//检查驱动错误，出错则停机
		//FaultCheck();
		//主动发送模式
		if(uDelayCycle2>0)//只有大于零才发送回
		{
			if(wait_ms(uDelayCycle2,uDelayCountPrv2))
			{	
				sprintf(ReplyBuff,":a%d~%d~%.2f~%d~%d~%d~%d~%d#\r\n", iStepCount/uSubdivision,uIsMoving,GetTemperature(),bIsReverse,uSubdivision,uSpeed,bIsLowPower,bIsInitial);
				printf("%s", ReplyBuff);
				//BLTUsart_SendString(USART2,ReplyBuff);//蓝牙不支持主动发送
				memset(ReplyBuff,0,128);		
				uDelayCountPrv2=uTimerCount;
			}
		}	
	}
}

/*********************************************END OF FILE**********************/
