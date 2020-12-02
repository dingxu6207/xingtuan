/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTI
  
  AL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "bsp_usart_blt.h"
#include "bsp_usart.h"
#include "bsp_TiMbase.h"
#include "stdbool.h"
#include "iodef.h"
#include "pfo.h"

extern bool  bIsSlpMode;
extern bool  bIsLowPower; 
extern bool  bIsInitial;
extern u8    uIsMoving;	           

extern int   iStepCount;
extern int   iStepStart;
extern int   iStepStop;
extern int   iStepDelt;				

u8 i=1;       //加速完成
u8 uSpeedCntTmp;
extern u8   uSCnt;//uSTot//加速曲线数据
extern u8   uSCurve[256];
extern u8   uSpeedCntLim,uSpeedCnt;
extern u16  uTimerCount;
extern u16  uDelayCountPrv;

extern unsigned char UART_RxPtr_Prv;
extern unsigned char BLTUART_RxPtr_Prv;

unsigned char UART_RxPtr_Start=0;//命令开始位置即:位置
unsigned char BLTUART_RxPtr_Start=0;//命令开始位置即:位置

extern u8 Next(u8 Prv);
extern void WriteCfg(void);
extern void Halt(void);
//extern void TimingDelay_Decrement(void);



/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */


/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

void SysTick_Handler(void)
{
	//TimingDelay_Decrement();	
}

void TIM1_UP_IRQHandler(void) //TIM1中断函数
{
	if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET) //检查是否中断
	{
		TIM_ClearFlag(TIM1, TIM_IT_Update ); //清除中断标志
		////////////////////////////////////
		uTimerCount++;//计数器,延时用		
		if(uIsMoving==1)//slew out
		{
			if(iStepCount<iStepStop)
			{
				//驱动
				if(i==1)
				{
					GPIO_SetBits(STEP_GPIO_PORT, STEP_GPIO_PIN);
				}
				else if(i==2)
				{
					GPIO_ResetBits(STEP_GPIO_PORT, STEP_GPIO_PIN);
					iStepCount++;	//下降沿计数，保证细分完整
				}
				if(i>=uSpeedCnt)
					i=1;
				else
					i++;	
				//加减速
				if(uSpeedCnt>uSpeedCntLim)//加速
				{
					if((iStepCount-iStepStart)>=iStepDelt)//已走步数大于等于数组步数
					{
						uSCnt++;
						uSpeedCntTmp=uSCurve[uSCnt*2+1];
						if(uSpeedCnt>uSpeedCntTmp)//速度小才执行，速度较大就略过
						{
							iStepDelt=uSCurve[uSCnt*2+2];
							iStepStart=iStepCount;
							/*没有必要
							if(uSpeedCntTmp<uSpeedCntLim)//保证速度不大于最大速度
							{
								uSpeedCntTmp=uSpeedCntLim;
							}
							*/
							uSpeedCnt=uSpeedCntTmp;
						}
					}
				}
				else if(uSpeedCnt<uSpeedCntLim)//减速
				{
					uSpeedCnt=uSpeedCntLim;
					uSCnt=0;//置零保证可以重新加速
				}
			}
			else
			{
				//GPIO_ResetBits(STEP_GPIO_PORT, STEP_GPIO_PIN);
				uDelayCountPrv=uTimerCount;
				uIsMoving=0;
			}
		}			
		else if(uIsMoving==2)//Slew in
		{	
			if(iStepCount>iStepStop)
			{
				//驱动
				if(i==1)
				{
					GPIO_SetBits(STEP_GPIO_PORT, STEP_GPIO_PIN);
				}
				else if(i==2)
				{
					GPIO_ResetBits(STEP_GPIO_PORT, STEP_GPIO_PIN);
					iStepCount--;	//下降沿计数，保证细分完整
				}
				if(i>=uSpeedCnt)
					i=1;
				else
					i++;			
				//加减速
				if(uSpeedCnt>uSpeedCntLim)//加速
				{
					if((iStepStart-iStepCount)>=iStepDelt)
					{
						uSCnt++;
						uSpeedCntTmp=uSCurve[uSCnt*2+1];
						if(uSpeedCnt>uSpeedCntTmp)//速度小才执行，速度较大就略过
						{
							iStepDelt=uSCurve[uSCnt*2+2];
							iStepStart=iStepCount;
							/*
							if(uSpeedCntTmp<uSpeedCntLim)//保证速度不大于最大速度
							{
								uSpeedCntTmp=uSpeedCntLim;
							}
							*/
							uSpeedCnt=uSpeedCntTmp;
						}
					}
				}
				else if(uSpeedCnt<uSpeedCntLim)//减速
				{
					uSpeedCnt=uSpeedCntLim;
					uSCnt=0;
				}
			}
			else
			{
				//GPIO_ResetBits(STEP_GPIO_PORT, STEP_GPIO_PIN);
				uDelayCountPrv=uTimerCount;
				uIsMoving=0;
			}
		}
	}
}

void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)!=RESET)
	{
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
		////////////////////////////////////
		printf("Timer2\r\n");
		
	}
}
void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)!=RESET)
	{
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
		////////////////////////////////////
		printf("Timer3\r\n");
	}
}
// 串口1中断服务函数
void DEBUG_USART_IRQHandler(void)
{
	if(USART_GetITStatus(DEBUG_USARTx,USART_IT_RXNE)!=RESET)
	{
		//循环接收
		UART_RxBuffer[UART_RxPtr] = USART_ReceiveData(DEBUG_USARTx);
		if(UART_RxBuffer[UART_RxPtr] == 58)//:
		{
			UART_RxPtr_Start=UART_RxPtr;
		}
		if(Next(UART_RxPtr)==UART_RxPtr_Prv)//超过缓存就丢弃
		{
			UART_RxPtr_Prv=UART_RxPtr_Start;
			UART_RxCmd=0;
		}
		if(UART_RxBuffer[UART_RxPtr] == 35)//#
		{
			UART_RxCmd++;
		}
		UART_RxPtr=Next(UART_RxPtr);
	}	
}
// 串口2中断服务函数
void BLT_USART_IRQHandler(void)
{
  if(USART_GetITStatus(BLT_USARTx, USART_IT_RXNE) != RESET)
	{
		//循环接收
		BLTUART_RxBuffer[BLTUART_RxPtr] = USART_ReceiveData(BLT_USARTx);
		if(BLTUART_RxBuffer[BLTUART_RxPtr] == 58)//:
		{
			BLTUART_RxPtr_Start=BLTUART_RxPtr;
		}
		if(Next(BLTUART_RxPtr)==BLTUART_RxPtr_Prv)//超过缓存就丢弃
		{
			BLTUART_RxPtr_Prv=BLTUART_RxPtr_Start;
			BLTUART_RxCmd=0;
		}
		if(BLTUART_RxBuffer[BLTUART_RxPtr] == 35)//#	
		{
			BLTUART_RxCmd++;
		}
		BLTUART_RxPtr=Next(BLTUART_RxPtr);
	}	
}

//掉电中断
void PF_IRQHandler(void)
{
  //确保是否产生了EXTI Line中断
	if(EXTI_GetITStatus(PF_EXTI_LINE) != RESET) 
	{
		//掉电保存数据,未初始化说明片上存储，不需要初始化，因此要保存
		if(!bIsInitial)
		{
			WriteCfg();
			printf("%s", ":oPowerOff#\r\n");
		}
    //清除中断标志位
		EXTI_ClearITPendingBit(PF_EXTI_LINE);     
	}  
}

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
