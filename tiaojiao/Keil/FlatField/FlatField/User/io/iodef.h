#ifndef __IODEF_H
#define	__IODEF_H


#include "stm32f10x.h"


//PFO信号
#define PFO_GPIO_PORT        GPIOB
#define PFO_GPIO_CLK         (RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO)
#define PFO_GPIO_PIN         GPIO_Pin_0
#define PFO_EXTI_PORTSOURCE  GPIO_PortSourceGPIOB
#define PFO_EXTI_PINSOURCE   GPIO_PinSource0

//DIM信号
#define DIM_GPIO_PORT        GPIOB
#define DIM_GPIO_CLK         RCC_APB2Periph_GPIOB
#define DIM_GPIO_PIN         GPIO_Pin_5

#define ON  0
#define OFF 1

/* 直接操作寄存器的方法控制IO */
#define	digitalHi(p,i)		 {p->BSRR=i;}	 //输出为高电平		
#define digitalLo(p,i)		 {p->BRR=i;}	 //输出低电平
#define digitalToggle(p,i) {p->ODR ^=i;} //输出反转状态

void MY_GPIO_Config(void);
//void PFO_GPIO_Config(void);

#endif 
