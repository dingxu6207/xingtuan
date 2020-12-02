#ifndef __BSP_TIMEBASE_H
#define __BSP_TIMEBASE_H

#include "stm32f10x.h"

void TIM1_Init(u16 arr,u16 psc);
void TIM2_Init(u16 arr,u16 psc);
void TIM3_Init(u16 arr,u16 psc);


#endif	/* __BSP_TIMEBASE_H */

