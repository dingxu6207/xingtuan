/**
  ******************************************************************************
  * @file    bsp_usart1.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   HC05串口驱动
  ******************************************************************************
  * @attention
  *
  * 实验平台:秉火 MINI STM32 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 
	
#include "./usart/bsp_usart_blt.h"
#include <stdarg.h>

//中断缓存串口数据
unsigned char BLTUART_RxBuffer[BLTUART_RX_BUFFER_SIZE] = {0};
//串口接收数组指针
unsigned char BLTUART_RxPtr;

/// 配置USART接收中断
static void NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    /* Configure the NVIC Preemption Priority Bits */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);//1

    /* Enable the USARTy Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = BLT_USART_IRQ;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =1;//1
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;//1
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/*
 * 函数名：USARTx_Config
 * 描述  ：USART GPIO 配置,工作模式配置
 * 输入  ：无
 * 输出  : 无
 * 调用  ：外部调用
 */
void BLT_USART_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	/* config USART2 clock */
	BLT_USART_APBxClock_FUN(BLT_USART_CLK, ENABLE); 
	BLT_USART_GPIO_APBxClock_FUN(BLT_USART_GPIO_CLK, ENABLE);

	/* USART2 GPIO config */
	 /* Configure USART2 Tx (PA.02) as alternate function push-pull */
		GPIO_InitStructure.GPIO_Pin = BLT_USART_TX_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(BLT_USART_TX_PORT, &GPIO_InitStructure);
	    
  /* Configure USART2 Rx (PA.03) as input floating */
  GPIO_InitStructure.GPIO_Pin = BLT_USART_RX_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(BLT_USART_RX_PORT, &GPIO_InitStructure);
	  
	/* USART2 mode config */
	USART_InitStructure.USART_BaudRate = BLT_USART_BAUD_RATE;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(BLT_USARTx, &USART_InitStructure); 
	
	/*	配置中断优先级 */
	NVIC_Configuration();
	/* 使能串口2接收中断 */
	USART_ITConfig(BLT_USARTx, USART_IT_RXNE, ENABLE);

	USART_Cmd(BLT_USARTx, ENABLE);
	USART_ClearFlag(BLT_USARTx, USART_FLAG_TC);
}

/***************** 发送一个字符  **********************/
void BLTUsart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch )
{
	/* 发送一个字节数据到USART1 */
	USART_SendData(pUSARTx,ch);
		
	/* 等待发送完毕 */
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}
/*****************  发送指定长度的字符串 **********************/
void BLTUsart_SendStr_length( USART_TypeDef * pUSARTx, uint8_t *str,uint32_t strlen )
{
	unsigned int k=0;
    do 
    {
        BLTUsart_SendByte( pUSARTx, *(str + k) );
        k++;
    } while(k < strlen);
}

/*****************  发送字符串 **********************/
//void BLTUsart_SendString( USART_TypeDef * pUSARTx, uint8_t *str)
void BLTUsart_SendString( USART_TypeDef * pUSARTx, char *str)
{
	unsigned int k=0;
    do 
    {
        BLTUsart_SendByte( pUSARTx, *(str + k) );
        k++;
    } while(*(str + k)!='\0');
}

//获取接收到的数据和长度
char *get_rebuff(uint16_t *len) 
{
    *len = BLTUART_RxPtr;
    return (char *)&BLTUART_RxBuffer;
}

//清空缓冲区
void clean_rebuff(void)
{

    uint16_t i=BLTUART_RX_BUFFER_SIZE+1;
    BLTUART_RxPtr = 0;
	while(i)
		BLTUART_RxBuffer[--i]=0;

}

/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/
