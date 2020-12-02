
// 基本定时器TIMx,x[1]定时初始化函数

#include "bsp_TiMbase.h" 
#include "bsp_usart.h"
#include "iodef.h"

void TIM1_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); //使能TIM1
	//初始化TIM1
	TIM_TimeBaseStructure.TIM_Period = arr; 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0; //
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); 
	TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE ); 
	//中断优先级设置
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);	//0	
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; //3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure); 
	TIM_Cmd(TIM1, ENABLE); 
}

/*********************************************END OF FILE**********************/
