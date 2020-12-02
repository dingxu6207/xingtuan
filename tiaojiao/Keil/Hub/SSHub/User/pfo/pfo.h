#ifndef __PFO_H
#define __PFO_H

#include "stm32f10x.h"

#define PF_GPIO_PORT         GPIOB
#define PF_GPIO_CLK          (RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO)
#define PF_GPIO_PIN          GPIO_Pin_0
#define PF_EXTI_PORTSOURCE   GPIO_PortSourceGPIOB
#define PF_EXTI_PINSOURCE    GPIO_PinSource0
#define PF_EXTI_LINE         EXTI_Line0
#define PF_EXTI_IRQ          EXTI0_IRQn

#define PF_IRQHandler            EXTI0_IRQHandler

void PF_Config(void);

#endif

