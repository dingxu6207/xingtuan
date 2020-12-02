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
//#include "pfo.h"
//#include "at24c02.h"
//#include "bsp_ds18b20.h"
#include "bsp_SysTick.h"
#include "bsp_TiMbase.h"
#include "bsp_usart.h"
//#include "bsp_usart_blt.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stdbool.h"

//64K空间，第0页-第31页用于程序存储，第32页-第63页用于数据存储（即0x0800 8000~0x0800 FFFF）
//#define WriteFlashAddress    ((u32)0x0800FC00)//存储到最后一页，地址范围：0x0800 FC00~0x0800 FFFF
u8    uCurrentPage=0;
u16   uPageWriteTimesMax=500;//每页存储500次换下一页
u16   uPageWriteTimes=0;
u32   uTotalWriteTimes=0;//总计读写次数
u32   uStartAdress=0x08008000;
u32   uStopAdress =0x0800FC00;
u32   uCurrentAdress=0x08008000;
u8 sdata[12]={1,1,1,1,1,1,1,1,1,1,1,1}; //DC和USB开关状态
typedef union//内部Flash数据格式
{
	struct
	{
		u16 PageWriteTimes;//单页读写次数
		u32 TotalWriteTimes;//总共读写次数
		u8  StateData[12];
	}CfgData;
	u32 SaveArray[5];
}UnionData; 
UnionData UD;

u8 uPort=99,ii=0;

//char  *pVersion = "SSHub-S1.0";    //SE-串口版,BT-蓝牙版,SB-串口蓝牙版,不能在线修改
char  *pVersion = "SS~KC Hub~KC.ASTRO~www.kctw.cn~ark@kctw.cn~0576-85389533"; 

u16   uTimerCount;
u16   uDelayCountPrv;
u16   uDelayCount=0;
u16   uDelayCycle=10000;
u16   uDelayCountTmp=0;

char  CmdBuff[32] = {0};     //回复字符串
char  ReplyBuff[128] = {0};  //回复字符串
char  TmpBuff[4] = {0};

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
//延迟函数,非阻塞
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
	u8 i=0,j=0;
	u32 TmpTotalWriteTimes=0;	
	uCurrentPage=0;
	for(i=0;i<32;i++)
	{
		uCurrentAdress=uStartAdress+1024*i;
		Read_Flash_MCU(uCurrentAdress,UD.SaveArray,5);
		if(UD.CfgData.PageWriteTimes>uPageWriteTimesMax)//未初始化则初始化：未初始化的默认值为65535，比最大值uPageWriteTimesMax大说明未初始化
		{
			UD.CfgData.PageWriteTimes=0;
			UD.CfgData.TotalWriteTimes=0;
			for(j=0;j<12;j++)
				UD.CfgData.StateData[j]=1;
			Write_Flash_MCU(uCurrentAdress,UD.SaveArray,5);
		}
		else if(UD.CfgData.TotalWriteTimes > TmpTotalWriteTimes)//找最大总写入次数
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
	for(j=0;j<12;j++)
		sdata[j]=UD.CfgData.StateData[j];
}
//将变量写入Flash存储
void WriteCfg(void)
{
	u8 ret=0,j=0;
	uPageWriteTimes++;//设置读写次数+1
	uTotalWriteTimes++;
	if(uPageWriteTimes>uPageWriteTimesMax)
	{
		uPageWriteTimes=1;
		uCurrentAdress=uCurrentAdress+1024;
		if(uCurrentAdress>=uStopAdress)
			uCurrentAdress=uStartAdress;
	}
	for(j=0;j<12;j++)
		UD.CfgData.StateData[j]=sdata[j];
	//写入直到成功
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

void OpenDCPort(u8 Port)
{
	switch(Port)
	{
		case 0:
			GPIO_SetBits(DCSW1_GPIO_PORT, DCSW1_GPIO_PIN);
			GPIO_SetBits(DCSW2_GPIO_PORT, DCSW2_GPIO_PIN);
			GPIO_SetBits(DCSW3_GPIO_PORT, DCSW3_GPIO_PIN);
			GPIO_SetBits(DCSW4_GPIO_PORT, DCSW4_GPIO_PIN);
			GPIO_SetBits(DCSW5_GPIO_PORT, DCSW5_GPIO_PIN);
			GPIO_SetBits(DCSW6_GPIO_PORT, DCSW6_GPIO_PIN);
		  break;
		case 1:
			GPIO_SetBits(DCSW1_GPIO_PORT, DCSW1_GPIO_PIN);
			break;
		case 2:
			GPIO_SetBits(DCSW2_GPIO_PORT, DCSW2_GPIO_PIN);
			break;
		case 3:
			GPIO_SetBits(DCSW3_GPIO_PORT, DCSW3_GPIO_PIN);
			break;
		case 4:
			GPIO_SetBits(DCSW4_GPIO_PORT, DCSW4_GPIO_PIN);
			break;
		case 5:
			GPIO_SetBits(DCSW5_GPIO_PORT, DCSW5_GPIO_PIN);
			break;
		case 6:
			GPIO_SetBits(DCSW6_GPIO_PORT, DCSW6_GPIO_PIN);
			break;
	}
}
void CloseDCPort(u8 Port)
{
	switch(Port)
	{
		case 0:
			GPIO_ResetBits(DCSW1_GPIO_PORT, DCSW1_GPIO_PIN);
			GPIO_ResetBits(DCSW2_GPIO_PORT, DCSW2_GPIO_PIN);
			GPIO_ResetBits(DCSW3_GPIO_PORT, DCSW3_GPIO_PIN);
			GPIO_ResetBits(DCSW4_GPIO_PORT, DCSW4_GPIO_PIN);
			GPIO_ResetBits(DCSW5_GPIO_PORT, DCSW5_GPIO_PIN);
			GPIO_ResetBits(DCSW6_GPIO_PORT, DCSW6_GPIO_PIN);
		  break;
		case 1:
			GPIO_ResetBits(DCSW1_GPIO_PORT, DCSW1_GPIO_PIN);
			break;
		case 2:
			GPIO_ResetBits(DCSW2_GPIO_PORT, DCSW2_GPIO_PIN);
			break;
		case 3:
			GPIO_ResetBits(DCSW3_GPIO_PORT, DCSW3_GPIO_PIN);
			break;
		case 4:
			GPIO_ResetBits(DCSW4_GPIO_PORT, DCSW4_GPIO_PIN);
			break;
		case 5:
			GPIO_ResetBits(DCSW5_GPIO_PORT, DCSW5_GPIO_PIN);
			break;
		case 6:
			GPIO_ResetBits(DCSW6_GPIO_PORT, DCSW6_GPIO_PIN);
			break;
	}
}
void OpenUSBPort(u8 Port)
{
	switch(Port)
	{
		case 0:
			GPIO_SetBits(USBSW1_GPIO_PORT, USBSW1_GPIO_PIN);
			GPIO_SetBits(USBSW2_GPIO_PORT, USBSW2_GPIO_PIN);
			GPIO_SetBits(USBSW3_GPIO_PORT, USBSW3_GPIO_PIN);
			GPIO_SetBits(USBSW4_GPIO_PORT, USBSW4_GPIO_PIN);
			GPIO_SetBits(USBSW5_GPIO_PORT, USBSW5_GPIO_PIN);
			GPIO_SetBits(USBSW6_GPIO_PORT, USBSW6_GPIO_PIN);
		  break;
		case 1:
			GPIO_SetBits(USBSW1_GPIO_PORT, USBSW1_GPIO_PIN);
		  break;
		case 2:
			GPIO_SetBits(USBSW2_GPIO_PORT, USBSW2_GPIO_PIN);
			break;
		case 3:
			GPIO_SetBits(USBSW3_GPIO_PORT, USBSW3_GPIO_PIN);
			break;
		case 4:
			GPIO_SetBits(USBSW4_GPIO_PORT, USBSW4_GPIO_PIN);
			break;
		case 5:
			GPIO_SetBits(USBSW5_GPIO_PORT, USBSW5_GPIO_PIN);
			break;
		case 6:
			GPIO_SetBits(USBSW6_GPIO_PORT, USBSW6_GPIO_PIN);
			break;
	}
}
void CloseUSBPort(u8 Port)
{
	switch(Port)
	{
		case 0:
			GPIO_ResetBits(USBSW1_GPIO_PORT, USBSW1_GPIO_PIN);
			GPIO_ResetBits(USBSW2_GPIO_PORT, USBSW2_GPIO_PIN);
			GPIO_ResetBits(USBSW3_GPIO_PORT, USBSW3_GPIO_PIN);
			GPIO_ResetBits(USBSW4_GPIO_PORT, USBSW4_GPIO_PIN);
		  GPIO_ResetBits(USBSW5_GPIO_PORT, USBSW5_GPIO_PIN);
		  GPIO_ResetBits(USBSW6_GPIO_PORT, USBSW6_GPIO_PIN);
		  break;
		case 1:
			GPIO_ResetBits(USBSW1_GPIO_PORT, USBSW1_GPIO_PIN);
			break;
		case 2:
			GPIO_ResetBits(USBSW2_GPIO_PORT, USBSW2_GPIO_PIN);
			break;
		case 3:
			GPIO_ResetBits(USBSW3_GPIO_PORT, USBSW3_GPIO_PIN);
			break;
		case 4:
			GPIO_ResetBits(USBSW4_GPIO_PORT, USBSW4_GPIO_PIN);
			break;
		case 5:
			GPIO_ResetBits(USBSW5_GPIO_PORT, USBSW5_GPIO_PIN);
			break;
		case 6:
			GPIO_ResetBits(USBSW6_GPIO_PORT, USBSW6_GPIO_PIN);
			break;
	}
}
/*
//读取Flash并赋值给变量
void ReadCfg(void)
{
	u8 i,j;
	Read_Flash(sdata,0, 8);
	for(i=0;i<8;i++)
	{
		if((sdata[i]<0)||(sdata[i]>1))
		{
			for(j=0;j<8;j++)
				sdata[j]=1;				
			//Write_Flash(sdata,0,8);
			break;
		}
	}
	for(i=0;i<4;i++)
	{
		if(sdata[i]==1)
			OpenDCPort((char)(i+1));
		else
			CloseDCPort((char)(i+1));
	}
	for(i=4;i<8;i++)
	{
		if(sdata[i]==1)
			OpenUSBPort((char)(i-3));
		else
			CloseUSBPort((char)(i-3));
	}
}
//将变量写入Flash存储
void WriteCfg(void)
{
	Write_Flash(sdata,0,8);
}
void GetState()
{
	Read_Flash(sdata,0, 8);
}
*/
//通过某个串口发送
void SendTo(u8 MyComPort,char MyReplyBuff[])
{
	switch(MyComPort)
	{
		case 0:
			printf("%s", MyReplyBuff);
			break;
		case 1:
			//BLTUsart_SendString(USART2,MyReplyBuff);
			break;
	}
	memset(MyReplyBuff,0,128);
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
	{
		memset(CmdBuff,0,32);
		return false;
	}
	if(CmdBuff[0]=='H')
	{
		switch (CmdBuff[1])//O-open C-Close R-Reset
		{
			case 'O':    //Open
				{
					uPort=(u8)CmdBuff[3]-48;
					sprintf(ReplyBuff,":O#\n");
					if(uPort<=6)
					{
						if (CmdBuff[2] == 'D')//DC
						{
							OpenDCPort(uPort);
							if(uPort==0)
							{
								for(ii=0;ii<6;ii++)
									sdata[ii]=1;
							}
							else
								sdata[uPort-1]=1;
						}
						else if(CmdBuff[2] == 'U')//USB
						{
							OpenUSBPort(uPort);
							if(uPort==0)
							{
								for(ii=6;ii<12;ii++)
									sdata[ii]=1;
							}
							else
								sdata[uPort+5]=1;
						}
					}
					break;
				}
			case 'C':   //Close
				{
					uPort=(u8)CmdBuff[3]-48;
					sprintf(ReplyBuff,":C#\n");
					if(uPort<=6)
					{
						if (CmdBuff[2] == 'D')//DC
						{
							
							CloseDCPort(uPort);
							if(uPort==0)
							{
								for(ii=0;ii<6;ii++)
									sdata[ii]=0;
							}
							else
								sdata[uPort-1]=0;
						}
						else if(CmdBuff[2] == 'U')//USB
						{
							CloseUSBPort(uPort);
							if(uPort==0)
							{
								for(ii=6;ii<12;ii++)
									sdata[ii]=0;
							}
							else
								sdata[uPort+5]=0;
						}
					}
					break;
				}
			case 'R':   //Reboot
				{
					uPort=(u8)CmdBuff[3]-48;
					sprintf(ReplyBuff,":R#\n");
					if(uPort<=6)
					{
						if (CmdBuff[2] == 'D')//DC
						{
							CloseDCPort(uPort);
							delay_ms(5000);//5S
							OpenDCPort(uPort);
						}
						else if(CmdBuff[2] == 'U')//USB
						{
							CloseUSBPort(uPort);
							delay_ms(5000);//5S
							OpenUSBPort(uPort);
						}
					}
					break;							
				}
			case 'S':   //Query
				{
					sprintf(ReplyBuff,":S#\n");WriteCfg();
					break;							
				}
			case 'Q':   //Query
				{     
					//GetState();       
					sprintf(ReplyBuff,":Q%d%d%d%d%d%d%d%d%d%d%d%d#\n",sdata[0],sdata[1],sdata[2],sdata[3],sdata[4],sdata[5],sdata[6],sdata[7],sdata[8],sdata[9],sdata[10],sdata[11]);
					break;							
				}
			case '?':  //ACK , return version
				{
					sprintf(ReplyBuff, ":?%s#\n", pVersion);
					break;
				}
			default://Unknow Command
				{
					sprintf(ReplyBuff, ":U#\n");
					break;
				}
		}
		SendTo(MyComPort,ReplyBuff);
		memset(CmdBuff,0,32);
	}
	return true;
}

//主程序
int main()
{	
	SystemInit();
	
	//SysTick_Init();
	
	MY_GPIO_Config();
	
	TIM1_Init(99,71);//100US定时器，10KHz
	
	USART_Config();
	
	//BLT_USART_Config();
	
	//I2C_init();	//AT24C02
	
	//初始化参数
	ReadCfg();
	for(ii=0;ii<6;ii++)
	{
		if(sdata[ii]==1)
			OpenDCPort(ii+1);
		else if(sdata[ii]==0)
			CloseDCPort(ii+1);
	}
	for(ii=6;ii<12;ii++)
	{
		if(sdata[ii]==1)
			OpenUSBPort(ii-5);
		else if(sdata[ii]==0)
			CloseUSBPort(ii-5);
	}
	while(1)
	{	
		//处理串口1数据
		while(UART_RxCmd>0)
		{
			UART_RxCmd--;//命令计数减一
			CmdProcess(0,UART_RxBuffer,&UART_RxPtr_Prv);
		}	
		/*
	  //处理串口2数据	
	  while(BLTUART_RxCmd>0)
	  { 
			BLTUART_RxCmd--;//命令计数减一
			CmdProcess(1,BLTUART_RxBuffer,&BLTUART_RxPtr_Prv);
	  }
		*/
	}
}

/*********************************************END OF FILE**********************/
