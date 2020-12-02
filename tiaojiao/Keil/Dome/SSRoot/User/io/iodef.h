#ifndef __IODEF_H
#define	__IODEF_H

#include "stm32f10x.h"

//PFO信号
#define PFO_GPIO_PORT        GPIOB
#define PFO_GPIO_CLK         (RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO)
#define PFO_GPIO_PIN         GPIO_Pin_0
#define PFO_EXTI_LINE        EXTI_Line0
#define PFO_EXTI_IRQ         EXTI0_IRQn
#define PFO_IRQHandler       EXTI0_IRQHandler
#define PFO_EXTI_PORTSOURCE  GPIO_PortSourceGPIOB
#define PFO_EXTI_PINSOURCE   GPIO_PinSource0
/*
//PFO信号
#define PFO_GPIO_PORT        GPIOA
#define PFO_GPIO_CLK         (RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO)
#define PFO_GPIO_PIN         GPIO_Pin_14
#define PFO_EXTI_LINE        EXTI_Line14
#define PFO_EXTI_IRQ         EXTI15_10_IRQn
#define PFO_IRQHandler       EXTI15_10_IRQHandler//参考中断分组
#define PFO_EXTI_PORTSOURCE  GPIO_PortSourceGPIOA
#define PFO_EXTI_PINSOURCE   GPIO_PinSource0
*/
//S1
#define S1_GPIO_PORT        GPIOB
#define S1_GPIO_CLK         RCC_APB2Periph_GPIOB
#define S1_GPIO_PIN         GPIO_Pin_0

//S2
#define S2_GPIO_PORT        GPIOA
#define S2_GPIO_CLK         RCC_APB2Periph_GPIOA
#define S2_GPIO_PIN         GPIO_Pin_6

//S3
#define S3_GPIO_PORT        GPIOA
#define S3_GPIO_CLK         RCC_APB2Periph_GPIOA
#define S3_GPIO_PIN         GPIO_Pin_5

//S4
#define S4_GPIO_PORT    		GPIOB
#define S4_GPIO_CLK 	    	RCC_APB2Periph_GPIOB		
#define S4_GPIO_PIN		      GPIO_Pin_11  

//O1
#define O1_GPIO_PORT    		GPIOB
#define O1_GPIO_CLK 	    	RCC_APB2Periph_GPIOB		
#define O1_GPIO_PIN		      GPIO_Pin_10  

//O2
#define O2_GPIO_PORT    		GPIOA
#define O2_GPIO_CLK 	    	RCC_APB2Periph_GPIOA		
#define O2_GPIO_PIN		      GPIO_Pin_4                 

//O3
#define O3_GPIO_PORT    	  GPIOA			              
#define O3_GPIO_CLK 	      RCC_APB2Periph_GPIOA		
#define O3_GPIO_PIN		    	GPIO_Pin_7		        

//O4 
#define O4_GPIO_PORT        GPIOB
#define O4_GPIO_CLK         RCC_APB2Periph_GPIOB
#define O4_GPIO_PIN         GPIO_Pin_1

//R1 
#define R1_GPIO_PORT        GPIOB
#define R1_GPIO_CLK         RCC_APB2Periph_GPIOB
#define R1_GPIO_PIN         GPIO_Pin_4

//R2
#define R2_GPIO_PORT        GPIOB
#define R2_GPIO_CLK         RCC_APB2Periph_GPIOB
#define R2_GPIO_PIN         GPIO_Pin_3

//R3
#define R3_GPIO_PORT        GPIOA
#define R3_GPIO_CLK         RCC_APB2Periph_GPIOA
#define R3_GPIO_PIN         GPIO_Pin_15

//R4
#define R4_GPIO_PORT        GPIOA
#define R4_GPIO_CLK         RCC_APB2Periph_GPIOA
#define R4_GPIO_PIN         GPIO_Pin_14

//L1
#define L1_GPIO_PORT        GPIOB
#define L1_GPIO_CLK         RCC_APB2Periph_GPIOB
#define L1_GPIO_PIN         GPIO_Pin_9

//L2
#define L2_GPIO_PORT        GPIOB
#define L2_GPIO_CLK         RCC_APB2Periph_GPIOB
#define L2_GPIO_PIN         GPIO_Pin_8

//TEMP信号不用，仅为了程序正确运行
#define TEMP_GPIO_PORT        GPIOB
#define TEMP_GPIO_CLK         RCC_APB2Periph_GPIOB
#define TEMP_GPIO_PIN         GPIO_Pin_13

// SCL信号不用，仅为了程序正确运行
#define SCL_GPIO_PORT        GPIOB
#define SCL_GPIO_CLK         RCC_APB2Periph_GPIOB
#define SCL_GPIO_PIN         GPIO_Pin_14

//SDA信号不用，仅为了程序正确运行
#define SDA_GPIO_PORT        GPIOB
#define SDA_GPIO_CLK         RCC_APB2Periph_GPIOB
#define SDA_GPIO_PIN         GPIO_Pin_15




#define ON  0
#define OFF 1

/* 直接操作寄存器的方法控制IO */
#define	digitalHi(p,i)		 {p->BSRR=i;}	 //输出为高电平		
#define digitalLo(p,i)		 {p->BRR=i;}	 //输出低电平
#define digitalToggle(p,i) {p->ODR ^=i;} //输出反转状态

void MY_GPIO_Config(void);
//void PFO_GPIO_Config(void);

#endif 
