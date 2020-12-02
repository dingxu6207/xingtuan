#ifndef __PFO_H
#define __PFO_H

#include "stm32f10x.h"
#include "iodef.h"
//
#define PF_GPIO_PORT         PFO_GPIO_PORT
#define PF_GPIO_CLK          PFO_GPIO_CLK
#define PF_GPIO_PIN          PFO_GPIO_PIN
#define PF_EXTI_PORTSOURCE   PFO_EXTI_PORTSOURCE
#define PF_EXTI_PINSOURCE    PFO_EXTI_PINSOURCE
#define PF_EXTI_LINE         EXTI_Line0
#define PF_EXTI_IRQ          EXTI0_IRQn
#define PF_IRQHandler        EXTI0_IRQHandler

void PF_Config(void);

#endif

