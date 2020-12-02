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
//#include "at24c02.h"
//#include "bsp_ds18b20.h"
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
		u16 PageWriteTimes;//单页读写次数
		u32 TotalWriteTimes;//总共读写次数
		u16 dutycycle;
	}CfgData;
	u32 SaveArray[2];
}UnionData; 
UnionData UD;

//char  *pVersion = "SS~SKY ROVER Focuser~SKY ROVER Co.,Ltd.~www.sky-rover.cn~service@sky-rover.com~0871-64605908";    //判断符号~设备名称型号~网址~电子邮箱~电话
char  *pVersion = "SS~KC FlatField Lamp~KC.ASTRO~www.kctw.cn~ark@kctw.cn~0576-85389533";    

//char  *pBTName = "SSFocuser"; //BT SSID
u8 open=0;
u16 dcycle=500;
u16 rcycle=0;

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
		Read_Flash_MCU(uCurrentAdress,UD.SaveArray,2);
		if(UD.CfgData.PageWriteTimes>uPageWriteTimesMax)//65535未初始化的默认值为65535，比最大值uPageWriteTimesMax大说明未初始化
		{
			UD.CfgData.PageWriteTimes=0;
			UD.CfgData.TotalWriteTimes=0;
			UD.CfgData.dutycycle=500;
			Write_Flash_MCU(uCurrentAdress,UD.SaveArray,2);
		}
		else if(UD.CfgData.TotalWriteTimes > TmpTotalWriteTimes)
		{
			TmpTotalWriteTimes=UD.CfgData.TotalWriteTimes;
			uCurrentPage=i;
		}	
	}
	//读取当前页
	uCurrentAdress=uStartAdress+1024*uCurrentPage;
	Read_Flash_MCU(uCurrentAdress,UD.SaveArray,2);
	//赋值给参数
	uPageWriteTimes=UD.CfgData.PageWriteTimes;
	uTotalWriteTimes =UD.CfgData.TotalWriteTimes ;
	dcycle=UD.CfgData.dutycycle;	
}
//将变量写入Flash存储
void WriteCfg(void)
{
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
	
	UD.CfgData.dutycycle=dcycle;

	while(1)
	{
		UD.CfgData.PageWriteTimes =uPageWriteTimes;
		UD.CfgData.TotalWriteTimes =uTotalWriteTimes;
		ret=Write_Flash_MCU(uCurrentAdress,UD.SaveArray,2);
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
	if(CmdBuff[0]=='f')//调焦器命令以F开头
	{
		switch (CmdBuff[1])
		{
			case '?':  //Focuser version
				{
					sprintf(ReplyBuff, ":?%s#\r\n", pVersion);
					SendTo(MyComPort,ReplyBuff);
					break;
				}
			case 'O': 
				{
					if(open!=1)
						open=1;
					sprintf(ReplyBuff, ":O#\r\n");
					SendTo(MyComPort,ReplyBuff);
					break;
				}
			case 'C': 
				{
					open=0;
					GPIO_ResetBits(DIM_GPIO_PORT, DIM_GPIO_PIN);
					sprintf(ReplyBuff, ":C#\r\n");
					SendTo(MyComPort,ReplyBuff);
					break;
				}
			case 'L': 
				{
					rcycle=atoi((char const *)CmdBuff+2);
					if(rcycle<=0)
					{
						open=0;
						GPIO_ResetBits(DIM_GPIO_PORT, DIM_GPIO_PIN);
					}
					else if(rcycle<=999)
					{
						if(open!=1)
							open=1;
						dcycle=rcycle;
					}
					else
					{
						open=2;
						GPIO_SetBits(DIM_GPIO_PORT, DIM_GPIO_PIN);
					}	
					sprintf(ReplyBuff, ":L#\r\n");
					SendTo(MyComPort,ReplyBuff);
					break;
				}
			case 'l': 
				{
					sprintf(ReplyBuff, ":L%d~%d#\r\n",open,dcycle);
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

//主程序
int main()
{	
	SystemInit();
	
	//SysTick_Init();
	
	MY_GPIO_Config();
	
	TIM1_Init(9,71);//100KHz
	
	//TIM2_Init(99,71);//100US定时器，1KHz
	
	//TIM3_Init(9999,7199);//1S定时器，1Hz
	
	PF_Config();
	
	USART_Config();


	//初始化参数
	ReadCfg();


	while(1)
	{	
		//处理串口1数据
		while(UART_RxCmd>0)
		{
			UART_RxCmd--;//命令计数减一
			CmdProcess(0,UART_RxBuffer,&UART_RxPtr_Prv);
		}			
	}
}

/*********************************************END OF FILE**********************/
