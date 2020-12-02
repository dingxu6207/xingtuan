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

extern u16  uTimerCount;
extern u16  uDelayCountPrv;

extern unsigned char UART_RxPtr_Prv;
extern unsigned char BLTUART_RxPtr_Prv;

unsigned char UART_RxPtr_Start=0;//命令开始位置即:位置
unsigned char BLTUART_RxPtr_Start=0;//命令开始位置即:位置

extern u8 Next(u8 Prv);
extern void Halt(void);
extern void WriteCfg(void);
extern void SetSpeed(u16 uSetSpeedCur);

extern void TimingDelay_Decrement(void);

//char  ReplyRecv[64] = {0};    //回复字符串
//unsigned char p,p1,p2,p3;
//unsigned char UART_FLAG=0;



/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

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
	TimingDelay_Decrement();	
}
/*
void  BASIC_TIM_IRQHandler (void)//不带加减速
{
	if ( TIM_GetITStatus( BASIC_TIM, TIM_IT_Update) != RESET ) 
	{	
		if ((bIsMoving) && (bIncreCount) )
		{
			iStepCount++;	
			if((uMoveState==1)&&(iStepStop<=iStepCount))
				Halt();
		}								
		else if ((bIsMoving) && (!bIncreCount))
		{
			iStepCount--;
			if((uMoveState==1)&&(iStepStop>=iStepCount))
				Halt();
		}
		TIM_ClearITPendingBit(BASIC_TIM , TIM_FLAG_Update); 
	}		 	
}
*/
/*
void  BASIC_TIM_IRQHandler3 (void)
{
	if ( TIM_GetITStatus( BASIC_TIM, TIM_IT_Update) != RESET ) 
	{	
		//毫秒计时器
		if(uDelayCount>=1000)
		{
			uDelayCount=0;
			printf("%s", "1S");
		}
		else
			uDelayCount++;
		
		if ((bIsMoving) && (bIncreCount) )
		{
			iStepCount++;	
			if(uMoveState==1)
			{
				if(iStepStop<=iStepCount)
					Halt();
			}
			//加速
			if((uSpeedCur<uSpeedMax)&&(uSCntCur<uSCurve[0]))
			{
				if((iStepCount-iStepStart)>=iStepDelt)//已走步数大于等于数组步数
				{
					uSCntCur++;
					uSpeedPrv=uSpeedCur;
					uSpeedCur=uSCurve[uSCntCur*2+1];
					iStepDelt=iStepDelt+uSCurve[uSCntCur*2+2];
					if(uSpeedCur>uSpeedMax)//保证速度不大于最大速度
						uSpeedCur=uSpeedMax;
					//sprintf(ReplyRecv, ":z%d,%d#\r\n",uSpeedCur,iStepCount-iStepStart);
					//printf("%s", ReplyRecv);
					SetSpeed(uSpeedCur,uSpeedPrv);
				}
			}
		}							
		else if ((bIsMoving) && (!bIncreCount))
		{
			iStepCount--;
			if(uMoveState==1)
			{
				if(iStepStop>=iStepCount)
					Halt();
			}
			//加速
			if((uSpeedCur<uSpeedMax)&&(uSCntCur<uSCurve[0]))
			{
				if((iStepStart-iStepCount)>=iStepDelt)
				{
					uSCntCur++;
					uSpeedPrv=uSpeedCur;
					uSpeedCur=uSCurve[uSCntCur*2+1];
					iStepDelt=iStepDelt+uSCurve[uSCntCur*2+2];
					if(uSpeedCur>uSpeedMax)//保证速度不大于最大速度
						uSpeedCur=uSpeedMax;
					SetSpeed(uSpeedCur,uSpeedPrv);
				}
			}
		}
		
		TIM_ClearITPendingBit(BASIC_TIM , TIM_FLAG_Update); 
	}		 	
}
*/

void TIM1_UP_IRQHandler(void) //TIM1中断函数
{
	if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET) //检查是否中断
	{
		TIM_ClearFlag(TIM1, TIM_IT_Update ); //清除中断标志
		uTimerCount++;//计数器,延时用	
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
		//掉电保存数据
		WriteCfg();
		printf("%s", ":oPowerOff#\r\n");
    //清除中断标志位
		EXTI_ClearITPendingBit(PF_EXTI_LINE);     
	}  
}

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
