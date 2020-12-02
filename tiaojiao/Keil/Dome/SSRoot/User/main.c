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
//64K�ռ䣬��0ҳ-��31ҳ���ڳ���洢����32ҳ-��63ҳ�������ݴ洢����0x0800 8000~0x0800 FFFF��
//#define WriteFlashAddress    ((u32)0x0800FC00)//�洢�����һҳ����ַ��Χ��0x0800 FC00~0x0800 FFFF
typedef union//�ڲ�Flash���ݸ�ʽ
{
	struct
	{
		//u8 	IsCurrent; //��ǰҳ
		u16 PageWriteTimes;//��ҳ��д����
		u32 TotalWriteTimes;//�ܹ���д����
		u8  IsLowPower;
		u8  IsReverse; 		
		u8  SubDivision;
		u8  MotorSpeed;
		u8  MotorSpeedMax;
		u16 DelayCycle;
		//u16 DelayCycle2;
		int	Position;  //�ϴ�λ��
	}CfgData;
	u32 SaveArray[5];
}UnionData; 
UnionData UD;

//char  *pVersion = "SS~XJLK Roof~XJLK Co.,Ltd.~www.xjlk.cn~service@xjlk.cn~0871-64605908";    //�жϷ���~�豸�����ͺ�~��ַ~��������~�绰
char  *pVersion = "SS~SS Roof~Graycode Team~www.graycode.cn~graycode@qq.com~0888-5441222";    

u8 uMode=7;//����ģʽ��7-00000111֧�ֵ���ASCOM��ң�غ��ֻ�Զ�̣�1-��֧��ASCOM��2-��֧��ң�أ�4-��֧���ֻ�Զ�̣��������ƣ�3-֧��ASCOM��ң�أ�
					//5-֧��ASCOM���ֻ�Զ�̣�6-֧��ң�غ��ֻ�Զ�̣������֧��ģʽ1��3 ��5 ��7
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
u16   uDelayCycle=300;//����������˯��ģʽʱ��
u16   uDelayCycle2=0; //�Զ���������
u16   uDelayCountPrv=0;
u16   uDelayCountPrv2=1000;

char  CmdBuff[32] = {0};     //�ظ��ַ���
char  ReplyBuff[128] = {0};  //�ظ��ַ���
char  TmpBuff[4] = {0};

u8    uCurrentPage=0;
u16   uPageWriteTimesMax=500;//ÿҳ�洢500�λ���һҳ
u16   uPageWriteTimes=0;
u32   uTotalWriteTimes=0;//�ܼƶ�д����
u32   uStartAdress=0x08008000;
u32   uStopAdress =0x0800FC00;
u32   uCurrentAdress=0x08008000;

unsigned char UART_RxPtr_Prv=0;    //�ϴζ�ȡλ��
unsigned char BLTUART_RxPtr_Prv=0; //�ϴζ�ȡλ��
unsigned char UART_RxCmd=0;        //δ���������
unsigned char BLTUART_RxCmd=0;     //δ���������
//�ӳ�ʱ�亯��---����
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
//�ӳ�ʱ�亯��---����
void delay_ms(u32 nTimer)
{
	u32 i=1000*nTimer;
	delay_us(i);
}
//�ȴ�ʱ�亯��---������
//������������񣬿��ܻ����ʵ���趨ʱ��
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
//дFlash���ɹ�����1��ʧ�ܷ���0
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

//��ȡFlash����ֵ������
void ReadCfg(void)
{
	//ɨ���32ҳ,���ҵ�ǰҳ��
	u8 i=0;
	u32 TmpTotalWriteTimes=0;	
	uCurrentPage=0;
	for(i=0;i<32;i++)
	{
		uCurrentAdress=uStartAdress+1024*i;
		Read_Flash_MCU(uCurrentAdress,UD.SaveArray,5);
		if(UD.CfgData.PageWriteTimes>uPageWriteTimesMax)//δ��ʼ�����г�ʼ����δ��ʼ����Ĭ��ֵΪ65535�������ֵuPageWriteTimesMax��˵��δ��ʼ��
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
		else if(UD.CfgData.TotalWriteTimes > TmpTotalWriteTimes)//��������ܶ�д������������Ҳ���ǵ�ǰ��¼ҳ
		{
			TmpTotalWriteTimes=UD.CfgData.TotalWriteTimes;
			uCurrentPage=i;
		}	
	}
	//��ȡ��ǰҳ
	uCurrentAdress=uStartAdress+1024*uCurrentPage;
	Read_Flash_MCU(uCurrentAdress,UD.SaveArray,5);
	//��ֵ������
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
//������д��Flash�洢
void WriteCfg(void)
{
	u8 ret=0;
	uPageWriteTimes++;//��ǰҳд����+1
	uTotalWriteTimes++;//�ܹ�д����+1
	if(uPageWriteTimes>uPageWriteTimesMax)//������ҳд����������һҳ
	{
		uPageWriteTimes=1;
		uCurrentAdress=uCurrentAdress+1024;
		if(uCurrentAdress>=uStopAdress)
			uCurrentAdress=uStartAdress;
	}
	//��ֵ
	//UD.CfgData.IsLowPower=bIsLowPower;
	//UD.CfgData.IsReverse=bIsReverse==false?0:1;
	//UD.CfgData.SubDivision=uSubdivision;
	//UD.CfgData.MotorSpeed=uSpeed;
	//UD.CfgData.MotorSpeedMax=uSpeedMax;
	//UD.CfgData.DelayCycle=uDelayCycle;
	//UD.CfgData.DelayCycle2=uDelayCycle2;
	//UD.CfgData.Position=iStepCount;
	//д�룬���д��ʧ�ܣ�������һҳдֱ���ɹ�
	while(1)
	{
		UD.CfgData.PageWriteTimes =uPageWriteTimes;
		UD.CfgData.TotalWriteTimes =uTotalWriteTimes;
		ret=Write_Flash_MCU(uCurrentAdress,UD.SaveArray,5);
		if(ret==0)//д��ʧ����д����һҳ��֪��д��ɹ�
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


//ͨ��ĳ�����ڷ����ַ�����0-Ĭ�ϴ��ڣ�1-��������
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
//����ң����
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
//�����̵���
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
//�رռ̵���
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
//��ȡPSF-B04�������1-4λ����O1-O4״̬����00001010=10����O2��O4Ϊ�ߵ�ƽ
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

//��ȡKey���̣���1-4λ����S1-S4״̬����00001010=10����S2��S4Ϊ�ߵ�ƽ
//��һ���·û��Ҫ��ȡ�������룬��Ϊ�����ӵ�PSF-B04����O1-O4��Ӧ
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
//ģ�ⰴ������������100mS��������
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
//��ȡ��λ״̬����1-2λ������λ1��2��״̬
u8 ReadLimit()
{
	u8 retvalue=0;
	if(GPIO_ReadInputDataBit(L1_GPIO_PORT,L1_GPIO_PIN)==1)
		retvalue+=1;
	if(GPIO_ReadInputDataBit(L2_GPIO_PORT,L2_GPIO_PIN)==1)
		retvalue+=2;
	return retvalue;
}
//������һ��
u8 Next(u8 Prv)
{
	if(Prv<255)
		return Prv+1;
	else //255
		return 0;
}
//��ȡһ�����ȥ��ͷβ:#��ָ��ָ����һ������
u8 ReadCmd(unsigned char *RxBuffer,unsigned char *Ptr)
{
	u8 Flag=0,i=0;
	memset(CmdBuff,0,32);
	for(;;)
	{
		//���������жϵ�˳���ܵ���
		if(RxBuffer[*Ptr]==35)//#��������
		{ 
			if(Flag==1)//��������
			{
				CmdBuff[i]=NULL;//û�н�������split���������
				Flag=2;
			}
			else
				Flag=3;
		}
		if(Flag==1)//:��ſ�ʼ��ȡ�����ַ���
		{
			CmdBuff[i]=RxBuffer[*Ptr];
			i++;
		}
		if(RxBuffer[*Ptr]==58)//:
		{
			Flag=1;
			i=0;
		}
		//ѭ����ȡ���ڻ�����
		*Ptr=Next(*Ptr);
		if(Flag>1)//����ѭ��
			break;
	}
	return i;
}
//�����
bool CmdProcess(u8 MyComPort,unsigned char *RxBuffer,unsigned char *Ptr)
{
	if(ReadCmd(RxBuffer,Ptr)<1)
		return false;
	memset(ReplyBuff,0,128);
	if(CmdBuff[0]=='D')//������������F��ͷ
	{
		switch (CmdBuff[1])
		{
			case '?': //��ѯ��Ʒ��Ϣ
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
			case 'Z': //�����Զ��������ڣ����粻���� 
				{
					sprintf(ReplyBuff, ":Z#\r\n");
					SendTo(MyComPort,ReplyBuff);
					if(uDelayCycle2 != atoi((char const *)CmdBuff+2))
					{
						uDelayCycle2 = atoi((char const *)CmdBuff+2);
					}
					break;
				}
			case 'z': //��ѯ�Զ���������
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
//������
int main()
{	
	SystemInit();
	
	//SysTick_Init();
	
	MY_GPIO_Config();
	
	TIM1_Init(99,71);//100US��ʱ����10KHz
	
	//TIM2_Init(99,71);//100US��ʱ����10KHz
	
	//TIM3_Init(9999,7199);//1S��ʱ����1Hz
	
	//PF_Config();

	USART_Config();
	
	BLT_USART_Config();

	//AT24C02
	//I2C_init();	
	
	//��ʼ���¶ȴ�����
	//DS18B20_Init();
	//DS18B20_Get_Temp();//��һ�ζ�ȡ���ع̶�ֵ

	//��ʼ������
	ReadCfg();
	OpenRelay(15);
	while(1)
	{	
		//����ASCOM�¼�
		while(UART_RxCmd>0)
		{
			UART_RxCmd--;//���������һ
			CmdProcess(0,UART_RxBuffer,&UART_RxPtr_Prv);
		}	
		//����ң���¼�
		if((uMode==3)||(uMode==7))
		{
			while(BLTUART_RxCmd>0)
			{ 
				BLTUART_RxCmd--;//���������һ
				CmdProcess(1,BLTUART_RxBuffer,&BLTUART_RxPtr_Prv);
			}
		}
		//�����ֻ��¼�
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

		//����������󣬳�����ͣ��
		//FaultCheck();
		//��������ģʽ

		if(uDelayCycle2>0)//ֻ�д�����ŷ��ͻ�
		{
			if(wait_ms(uDelayCycle2,uDelayCountPrv2))
			{	
				//sprintf(ReplyBuff,":a%d~%d~%.2f~%d~%d~%d~%d~%d#\r\n", iStepCount/uSubdivision,uIsMoving,GetTemperature(),bIsReverse,uSubdivision,uSpeed,bIsLowPower,bIsInitial);
				sprintf(ReplyBuff,":a%d",ReadPSFOut());
				printf("%s", ReplyBuff);
				//BLTUsart_SendString(USART2,ReplyBuff);//������֧����������
				memset(ReplyBuff,0,128);		
				uDelayCountPrv2=uTimerCount;
			}
		}	

	}
}

/*********************************************END OF FILE**********************/
