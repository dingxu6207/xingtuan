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

unsigned char UART_RxPtr_Start=0;//���ʼλ�ü�:λ��
unsigned char BLTUART_RxPtr_Start=0;//���ʼλ�ü�:λ��

extern u8 Next(u8 Prv);
extern void Halt(void);
extern void WriteCfg(void);
extern void SetSpeed(u16 uSetSpeedCur);

extern void TimingDelay_Decrement(void);

//char  ReplyRecv[64] = {0};    //�ظ��ַ���
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
void  BASIC_TIM_IRQHandler (void)//�����Ӽ���
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
		//�����ʱ��
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
			//����
			if((uSpeedCur<uSpeedMax)&&(uSCntCur<uSCurve[0]))
			{
				if((iStepCount-iStepStart)>=iStepDelt)//���߲������ڵ������鲽��
				{
					uSCntCur++;
					uSpeedPrv=uSpeedCur;
					uSpeedCur=uSCurve[uSCntCur*2+1];
					iStepDelt=iStepDelt+uSCurve[uSCntCur*2+2];
					if(uSpeedCur>uSpeedMax)//��֤�ٶȲ���������ٶ�
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
			//����
			if((uSpeedCur<uSpeedMax)&&(uSCntCur<uSCurve[0]))
			{
				if((iStepStart-iStepCount)>=iStepDelt)
				{
					uSCntCur++;
					uSpeedPrv=uSpeedCur;
					uSpeedCur=uSCurve[uSCntCur*2+1];
					iStepDelt=iStepDelt+uSCurve[uSCntCur*2+2];
					if(uSpeedCur>uSpeedMax)//��֤�ٶȲ���������ٶ�
						uSpeedCur=uSpeedMax;
					SetSpeed(uSpeedCur,uSpeedPrv);
				}
			}
		}
		
		TIM_ClearITPendingBit(BASIC_TIM , TIM_FLAG_Update); 
	}		 	
}
*/

void TIM1_UP_IRQHandler(void) //TIM1�жϺ���
{
	if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET) //����Ƿ��ж�
	{
		TIM_ClearFlag(TIM1, TIM_IT_Update ); //����жϱ�־
		uTimerCount++;//������,��ʱ��	
	}
}

// ����1�жϷ�����
void DEBUG_USART_IRQHandler(void)
{
	if(USART_GetITStatus(DEBUG_USARTx,USART_IT_RXNE)!=RESET)
	{
		//ѭ������
		UART_RxBuffer[UART_RxPtr] = USART_ReceiveData(DEBUG_USARTx);
		if(UART_RxBuffer[UART_RxPtr] == 58)//:
		{
			UART_RxPtr_Start=UART_RxPtr;
		}
		if(Next(UART_RxPtr)==UART_RxPtr_Prv)//��������Ͷ���
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
// ����2�жϷ�����
void BLT_USART_IRQHandler(void)
{
  if(USART_GetITStatus(BLT_USARTx, USART_IT_RXNE) != RESET)
	{
		//ѭ������
		BLTUART_RxBuffer[BLTUART_RxPtr] = USART_ReceiveData(BLT_USARTx);
		if(BLTUART_RxBuffer[BLTUART_RxPtr] == 58)//:
		{
			BLTUART_RxPtr_Start=BLTUART_RxPtr;
		}
		if(Next(BLTUART_RxPtr)==BLTUART_RxPtr_Prv)//��������Ͷ���
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

//�����ж�
void PF_IRQHandler(void)
{
  //ȷ���Ƿ������EXTI Line�ж�
	if(EXTI_GetITStatus(PF_EXTI_LINE) != RESET) 
	{
		//���籣������
		WriteCfg();
		printf("%s", ":oPowerOff#\r\n");
    //����жϱ�־λ
		EXTI_ClearITPendingBit(PF_EXTI_LINE);     
	}  
}

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
