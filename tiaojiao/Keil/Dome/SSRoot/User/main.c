/**
  ******************************************************************************
  * @file    main.c
  * @author  HeShouSheng(graycode@qq.com)
  * @version V1.0
  * @date    2017-11-20
  * @brief   SS Roof
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

//char  *pVersion = "SS~XJLK Roof~XJLK Co.,Ltd.~www.xjlk.cn~service@xjlk.cn~0871-64605908";    //判断符号~设备名称型号~网址~电子邮箱~电话
char  *pVersion = "SS~SS Roof~Graycode Team~www.graycode.cn~graycode@qq.com~0888-5441222";    

u8 uMode=7;//工作模式：7-00000111支持电脑ASCOM，遥控和手机远程，1-仅支持ASCOM，2-仅支持遥控，4-仅支持手机远程，依次类推，3-支持ASCOM和遥控，
					//5-支持ASCOM和手机远程，6-支持遥控和手机远程，这里仅支持模式1，3 ，5 ，7
u8 uIsMoving=0;
u8 OutPrv=15;
u8 OutTmp=15;
//HandBox
u8    uHandUState   = 0;
u8    uHandDState   = 0;
u16   uHandUCountPrv= 0;
u16   uHandDCountPrv= 0;

u16   uTimerCount=0;
u16   uSecondCount=0;
u16   uDelayCycle=300;//不操作进入睡眠模式时间
u16   uDelayCycle2=0; //自动发送周期
u16   uDelayCountPrv=0;
u16   uDelayCountPrv2=1000;

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
//延迟时间函数---阻塞
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
//延迟时间函数---阻塞
void delay_ms(u32 nTimer)
{
	u32 i=1000*nTimer;
	delay_us(i);
}
//等待时间函数---非阻塞
//如果有其他任务，可能会大于实际设定时间
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
	//扫描后32页,查找当前页面
	u8 i=0;
	u32 TmpTotalWriteTimes=0;	
	uCurrentPage=0;
	for(i=0;i<32;i++)
	{
		uCurrentAdress=uStartAdress+1024*i;
		Read_Flash_MCU(uCurrentAdress,UD.SaveArray,5);
		if(UD.CfgData.PageWriteTimes>uPageWriteTimesMax)//未初始化进行初始化：未初始化的默认值为65535，比最大值uPageWriteTimesMax大说明未初始化
		{
			UD.CfgData.PageWriteTimes=0;
			UD.CfgData.TotalWriteTimes=0;
			//UD.CfgData.IsLowPower=bIsLowPower;
			//UD.CfgData.IsReverse=bIsReverse==false?0:1;
			//UD.CfgData.SubDivision=uSubdivision;
			//UD.CfgData.MotorSpeed=uSpeed;
			//UD.CfgData.MotorSpeedMax=uSpeedMax;
			//UD.CfgData.DelayCycle=uDelayCycle;
			//UD.CfgData.DelayCycle2=uDelayCycle2;
			//UD.CfgData.Position=iStepCount;
			Write_Flash_MCU(uCurrentAdress,UD.SaveArray,5);
		}
		else if(UD.CfgData.TotalWriteTimes > TmpTotalWriteTimes)//查找最大总读写次数，其所在也就是当前记录页
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
	//bIsLowPower=UD.CfgData.IsLowPower;
	//bIsReverse=UD.CfgData.IsReverse==0?false:true;
	//uSubdivision=UD.CfgData.SubDivision;
	//uSpeed=UD.CfgData.MotorSpeed;	
	//uSpeedMax=UD.CfgData.MotorSpeedMax;
	//uDelayCycle=UD.CfgData.DelayCycle;
	//uDelayCycle2=UD.CfgData.DelayCycle2;
	//iStepCount=UD.CfgData.Position;	
}
//将变量写入Flash存储
void WriteCfg(void)
{
	u8 ret=0;
	uPageWriteTimes++;//当前页写次数+1
	uTotalWriteTimes++;//总共写次数+1
	if(uPageWriteTimes>uPageWriteTimesMax)//超过单页写次数则往下一页
	{
		uPageWriteTimes=1;
		uCurrentAdress=uCurrentAdress+1024;
		if(uCurrentAdress>=uStopAdress)
			uCurrentAdress=uStartAdress;
	}
	//赋值
	//UD.CfgData.IsLowPower=bIsLowPower;
	//UD.CfgData.IsReverse=bIsReverse==false?0:1;
	//UD.CfgData.SubDivision=uSubdivision;
	//UD.CfgData.MotorSpeed=uSpeed;
	//UD.CfgData.MotorSpeedMax=uSpeedMax;
	//UD.CfgData.DelayCycle=uDelayCycle;
	//UD.CfgData.DelayCycle2=uDelayCycle2;
	//UD.CfgData.Position=iStepCount;
	//写入，如果写入失败，则往下一页写直到成功
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


//通过某个串口发送字符串，0-默认串口，1-蓝牙串口
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
//发送遥控码
void SendRFCode(char TemBuff[])
{
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
}
//开启继电器
void OpenRelay(u8 RelayNum)
{
	switch(RelayNum)
	{
		case 1:
			GPIO_ResetBits(R1_GPIO_PORT, R1_GPIO_PIN);
			break;
		case 2:
			GPIO_ResetBits(R2_GPIO_PORT, R2_GPIO_PIN);
			break;
		case 4:
			GPIO_ResetBits(R3_GPIO_PORT, R3_GPIO_PIN);
			break;
		case 8:
			GPIO_ResetBits(R4_GPIO_PORT, R4_GPIO_PIN);
			break;
		case 15:
			GPIO_ResetBits(R1_GPIO_PORT, R1_GPIO_PIN);
			GPIO_ResetBits(R2_GPIO_PORT, R2_GPIO_PIN);
			GPIO_ResetBits(R3_GPIO_PORT, R3_GPIO_PIN);
			GPIO_ResetBits(R4_GPIO_PORT, R4_GPIO_PIN);
			break;
	}
}
//关闭继电器
void CloseRelay(u8 RelayNum)
{
	switch(RelayNum)
	{
		case 1:
			GPIO_SetBits(R1_GPIO_PORT, R1_GPIO_PIN);
			break;
		case 2:
			GPIO_SetBits(R2_GPIO_PORT, R2_GPIO_PIN);
			break;
		case 4:
			GPIO_SetBits(R3_GPIO_PORT, R3_GPIO_PIN);
			break;
		case 8:
			GPIO_SetBits(R4_GPIO_PORT, R4_GPIO_PIN);
			break;
		case 15:
			GPIO_SetBits(R1_GPIO_PORT, R1_GPIO_PIN);
			GPIO_SetBits(R2_GPIO_PORT, R2_GPIO_PIN);
			GPIO_SetBits(R3_GPIO_PORT, R3_GPIO_PIN);
			GPIO_SetBits(R4_GPIO_PORT, R4_GPIO_PIN);
			break;
	}
}
//读取PSF-B04输出，低1-4位代表O1-O4状态，如00001010=10代表O2和O4为高电平
u8 ReadPSFOut()
{
	u8 retvalue=0;
	if(GPIO_ReadInputDataBit(O1_GPIO_PORT,O1_GPIO_PIN)==1)
		retvalue+=1;
	if(GPIO_ReadInputDataBit(O2_GPIO_PORT,O2_GPIO_PIN)==1)
		retvalue+=2;
	if(GPIO_ReadInputDataBit(O3_GPIO_PORT,O3_GPIO_PIN)==1)
		retvalue+=4;
	if(GPIO_ReadInputDataBit(O4_GPIO_PORT,O4_GPIO_PIN)==1)
		retvalue+=8;
	return retvalue;
}

//读取Key键盘，低1-4位代表S1-S4状态，如00001010=10代表S2和S4为高电平
//第一版电路没必要读取键盘输入，因为它连接到PSF-B04，跟O1-O4对应
u8 ReadSwitch()
{
	u8 retvalue=0;
	if(GPIO_ReadInputDataBit(S1_GPIO_PORT,S1_GPIO_PIN)==1)
		retvalue+=1;
	if(GPIO_ReadInputDataBit(S2_GPIO_PORT,S2_GPIO_PIN)==1)
		retvalue+=2;
	if(GPIO_ReadInputDataBit(S3_GPIO_PORT,S3_GPIO_PIN)==1)
		retvalue+=4;
	if(GPIO_ReadInputDataBit(S4_GPIO_PORT,S4_GPIO_PIN)==1)
		retvalue+=8;
	return retvalue;
}
//模拟按键操作，大于100mS就起作用
void OperSwitch(u8 SwithcNum)
{
	switch(SwithcNum)
	{
		case 1:
			GPIO_ResetBits(R1_GPIO_PORT, R1_GPIO_PIN);
			delay_ms(250);
			GPIO_SetBits(R1_GPIO_PORT, R1_GPIO_PIN);
			break;
		case 2:
			GPIO_ResetBits(R2_GPIO_PORT, R2_GPIO_PIN);
			delay_ms(250);
			GPIO_SetBits(R2_GPIO_PORT, R2_GPIO_PIN);
			break;
		case 4:
			GPIO_ResetBits(R3_GPIO_PORT, R3_GPIO_PIN);
			delay_ms(250);
			GPIO_SetBits(R3_GPIO_PORT, R3_GPIO_PIN);
			break;
		case 8:
			GPIO_ResetBits(R4_GPIO_PORT, R4_GPIO_PIN);
			delay_ms(250);
			GPIO_SetBits(R4_GPIO_PORT, R4_GPIO_PIN);
			break;
		case 15:
			GPIO_ResetBits(R1_GPIO_PORT, R1_GPIO_PIN);
			GPIO_ResetBits(R2_GPIO_PORT, R2_GPIO_PIN);
			GPIO_ResetBits(R3_GPIO_PORT, R3_GPIO_PIN);
			GPIO_ResetBits(R4_GPIO_PORT, R4_GPIO_PIN);
			delay_ms(250);
			GPIO_SetBits(R1_GPIO_PORT, R1_GPIO_PIN);
			GPIO_SetBits(R2_GPIO_PORT, R2_GPIO_PIN);
			GPIO_SetBits(R3_GPIO_PORT, R3_GPIO_PIN);
			GPIO_SetBits(R4_GPIO_PORT, R4_GPIO_PIN);
			break;
	}
}
//读取限位状态，低1-2位代表限位1和2的状态
u8 ReadLimit()
{
	u8 retvalue=0;
	if(GPIO_ReadInputDataBit(L1_GPIO_PORT,L1_GPIO_PIN)==1)
		retvalue+=1;
	if(GPIO_ReadInputDataBit(L2_GPIO_PORT,L2_GPIO_PIN)==1)
		retvalue+=2;
	return retvalue;
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
	if(CmdBuff[0]=='D')//调焦器命令以F开头
	{
		switch (CmdBuff[1])
		{
			case '?': //查询产品信息
				{
					sprintf(ReplyBuff, ":?%s#\r\n", pVersion);
					SendTo(MyComPort,ReplyBuff);
					break;
				}
			case 'B': //
				{
					sprintf(ReplyBuff,":B%d#\r\n", uIsMoving);
					SendTo(MyComPort,ReplyBuff);
					break;
				}
			case 'O': //
				{
					sprintf(ReplyBuff, ":O#\r\n");
					SendTo(MyComPort,ReplyBuff);
					CloseRelay(2);
					delay_ms(250);
					OpenRelay(1);
					break;
				}
			case 'C': //
				{
					sprintf(ReplyBuff, ":O#\r\n");
					SendTo(MyComPort,ReplyBuff);
					CloseRelay(1);
					delay_ms(250);
					OpenRelay(2);
					break;
				}
			case 'Q': 
				{
					//Halt();
					sprintf(ReplyBuff, ":Q#\r\n");
					SendTo(MyComPort,ReplyBuff);				
					break;
				}
			case 'M':  
				{
					sprintf(ReplyBuff, ":M#\r\n");
					SendTo(MyComPort,ReplyBuff);
					if(uMode != atoi((char const *)CmdBuff+2))
					{
						uMode = atoi((char const *)CmdBuff+2);
					}
					break;
				}
			case 'm': 
				{
					sprintf(ReplyBuff, ":m%d#\r\n",uMode);
					SendTo(MyComPort,ReplyBuff);
					break;
				}
			case 'Z': //设置自动发送周期，掉电不保存 
				{
					sprintf(ReplyBuff, ":Z#\r\n");
					SendTo(MyComPort,ReplyBuff);
					if(uDelayCycle2 != atoi((char const *)CmdBuff+2))
					{
						uDelayCycle2 = atoi((char const *)CmdBuff+2);
					}
					break;
				}
			case 'z': //查询自动发送周期
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
void KeyEvent(void)
{
		;
}
//主程序
int main()
{	
	SystemInit();
	
	//SysTick_Init();
	
	MY_GPIO_Config();
	
	TIM1_Init(99,71);//100US定时器，10KHz
	
	//TIM2_Init(99,71);//100US定时器，10KHz
	
	//TIM3_Init(9999,7199);//1S定时器，1Hz
	
	//PF_Config();

	USART_Config();
	
	BLT_USART_Config();

	//AT24C02
	//I2C_init();	
	
	//初始化温度传感器
	//DS18B20_Init();
	//DS18B20_Get_Temp();//第一次读取返回固定值

	//初始化参数
	ReadCfg();
	OpenRelay(15);
	while(1)
	{	
		//处理ASCOM事件
		while(UART_RxCmd>0)
		{
			UART_RxCmd--;//命令计数减一
			CmdProcess(0,UART_RxBuffer,&UART_RxPtr_Prv);
		}	
		//处理遥控事件
		if((uMode==3)||(uMode==7))
		{
			while(BLTUART_RxCmd>0)
			{ 
				BLTUART_RxCmd--;//命令计数减一
				CmdProcess(1,BLTUART_RxBuffer,&BLTUART_RxPtr_Prv);
			}
		}
		//处理手机事件
		if((uMode==5)||(uMode==7))
		{
			KeyEvent();
		}

		OutTmp=ReadPSFOut();
		if(OutTmp!=OutPrv)
		{
			delay_ms(250);
			if(OutTmp==ReadPSFOut())
			{
				if(OutTmp&0x01)OpenRelay(1);else CloseRelay(1);
				if(OutTmp&0x02)OpenRelay(2);else CloseRelay(2);
				if(OutTmp&0x04)OpenRelay(4);else CloseRelay(4);
				if(OutTmp&0x08)OpenRelay(8);else CloseRelay(8);
				OutPrv=OutTmp;
			}
		}

		//检查驱动错误，出错则停机
		//FaultCheck();
		//主动发送模式

		if(uDelayCycle2>0)//只有大于零才发送回
		{
			if(wait_ms(uDelayCycle2,uDelayCountPrv2))
			{	
				//sprintf(ReplyBuff,":a%d~%d~%.2f~%d~%d~%d~%d~%d#\r\n", iStepCount/uSubdivision,uIsMoving,GetTemperature(),bIsReverse,uSubdivision,uSpeed,bIsLowPower,bIsInitial);
				sprintf(ReplyBuff,":a%d",ReadPSFOut());
				printf("%s", ReplyBuff);
				//BLTUsart_SendString(USART2,ReplyBuff);//蓝牙不支持主动发送
				memset(ReplyBuff,0,128);		
				uDelayCountPrv2=uTimerCount;
			}
		}	

	}
}

/*********************************************END OF FILE**********************/
