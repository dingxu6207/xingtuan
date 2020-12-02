
// 基本定时器TIMx,x[1]定时初始化函数

#include "bsp_TiMbase.h" 
#include "bsp_usart.h"
#include "iodef.h"

void TIM1_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;	
	NVIC_InitTypeDef NVIC_InitStructure;
	//TIM1配置
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); 
	TIM_TimeBaseStructure.TIM_Period = arr; 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0; 
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); 
	TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE ); 
	//中断优先级设置	
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);	//0	
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure); 
	
	TIM_Cmd(TIM1, ENABLE); 
}

//((1+arr )/72M)*(1+psc )=((1+1999)/72M)*(1+35999)=1?
void TIM2_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	//TIM2配置
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);//TIM_ClearFlag(TIM2,TIM_FLAG_Update);//两者作用相同
	//72M/36000=2000
	TIM_TimeBaseStructure.TIM_Period = arr;
	TIM_TimeBaseStructure.TIM_Prescaler = psc;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	//中断优先级设置
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	TIM_Cmd(TIM2,ENABLE);
}
void TIM3_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	//TIM3配置
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);//TIM_ClearFlag(TIM2,TIM_FLAG_Update);//两者作用相同
	//72M/36000=2000
	TIM_TimeBaseStructure.TIM_Period = arr;
	TIM_TimeBaseStructure.TIM_Prescaler = psc;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	//中断优先级设置
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	TIM_Cmd(TIM3,ENABLE);
}

/*********************************************END OF FILE**********************/
