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

extern u16   dcycle;
extern u8 open;

extern unsigned char UART_RxPtr_Prv;
extern unsigned char BLTUART_RxPtr_Prv;

unsigned char UART_RxPtr_Start=0;//���ʼλ�ü�:λ��
unsigned char BLTUART_RxPtr_Start=0;//���ʼλ�ü�:λ��

extern u8 Next(u8 Prv);
extern void WriteCfg(void);

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
static u16 cycle=0;
void TIM1_UP_IRQHandler(void) //TIM1�жϺ���
{
	if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET) //����Ƿ��ж�
	{
		TIM_ClearFlag(TIM1, TIM_IT_Update ); //����жϱ�־
		////////////////////////////////////
		if(open==1)
		{
			cycle++;
			if(cycle>999)
				cycle=0;
			if(cycle==0)
				GPIO_SetBits(DIM_GPIO_PORT, DIM_GPIO_PIN);
			else if(cycle>dcycle)
				GPIO_ResetBits(DIM_GPIO_PORT, DIM_GPIO_PIN);
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
		//���籣������,δ��ʼ��˵��Ƭ�ϴ洢������Ҫ��ʼ�������Ҫ����
		WriteCfg();
		printf("%s", ":oPowerOff#\r\n");
    //����жϱ�־λ
		EXTI_ClearITPendingBit(PF_EXTI_LINE);     
	}  
}

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
