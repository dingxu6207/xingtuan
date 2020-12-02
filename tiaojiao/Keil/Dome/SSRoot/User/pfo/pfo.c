#include "pfo.h"



 /**
  * @brief  配置嵌套向量中断控制器NVIC
  * @param  无
  * @retval 无
  */
static void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* 配置NVIC为优先级组1 */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  
  /* 配置中断源：按键1 */
  NVIC_InitStructure.NVIC_IRQChannel = PF_EXTI_IRQ;
  /* 配置抢占优先级 */
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  /* 配置子优先级 */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;//1
  /* 使能中断通道 */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

/**
  * @brief  配置 IO为EXTI中断口，并设置中断优先级
  * @param  无
  * @retval 无
  */
void PF_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	EXTI_InitTypeDef EXTI_InitStructure;

	/*开启按键GPIO口的时钟*/
	RCC_APB2PeriphClockCmd(PF_GPIO_CLK,ENABLE);
												
	/* 配置 NVIC 中断*/
	NVIC_Configuration();
	
/*--------------------------MIN配置-----------------------------*/
	/* 选择按键用到的GPIO */	
  GPIO_InitStructure.GPIO_Pin = PF_GPIO_PIN;
  /* 配置为浮空输入 */	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(PF_GPIO_PORT, &GPIO_InitStructure);

	/* 选择EXTI的信号源 */
  GPIO_EXTILineConfig(PF_EXTI_PORTSOURCE, PF_EXTI_PINSOURCE); 
  EXTI_InitStructure.EXTI_Line = PF_EXTI_LINE;
	
	/* EXTI为中断模式 */
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	/* 上升沿中断 */
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  /* 使能中断 */	
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
}





