#ifndef __IODEF_H
#define	__IODEF_H


#include "stm32f10x.h"

// DCSW1
#define DCSW1_GPIO_PORT    	GPIOA			              /* GPIO�˿� */
#define DCSW1_GPIO_CLK 	    RCC_APB2Periph_GPIOA		/* GPIO�˿�ʱ�� */
#define DCSW1_GPIO_PIN		  GPIO_Pin_15			        /* ���ӵ�SCLʱ���ߵ�GPIO */

// DCSW2
#define DCSW2_GPIO_PORT    	GPIOA/* GPIO�˿� */
#define DCSW2_GPIO_CLK 	    RCC_APB2Periph_GPIOA		/* GPIO�˿�ʱ�� */
#define DCSW2_GPIO_PIN		  GPIO_Pin_14                 /* ���ӵ�SCLʱ���ߵ�GPIO */

// DCSW3
#define DCSW3_GPIO_PORT    	GPIOA			              /* GPIO�˿� */
#define DCSW3_GPIO_CLK 	    RCC_APB2Periph_GPIOA		/* GPIO�˿�ʱ�� */
#define DCSW3_GPIO_PIN		  GPIO_Pin_13			        /* ���ӵ�SCLʱ���ߵ�GPIO */

// DCSW4
#define DCSW4_GPIO_PORT    	GPIOA				              /* GPIO�˿� */
#define DCSW4_GPIO_CLK 	    RCC_APB2Periph_GPIOA		/* GPIO�˿�ʱ�� */
#define DCSW4_GPIO_PIN		  GPIO_Pin_12			        /* ���ӵ�SCLʱ���ߵ�GPIO */

// DCSW5
#define DCSW5_GPIO_PORT    	GPIOA			              
#define DCSW5_GPIO_CLK 	    RCC_APB2Periph_GPIOA		
#define DCSW5_GPIO_PIN		  GPIO_Pin_11		        

// DCSW6
#define DCSW6_GPIO_PORT     GPIOA
#define DCSW6_GPIO_CLK      RCC_APB2Periph_GPIOA
#define DCSW6_GPIO_PIN      GPIO_Pin_8

// USBSW1 
#define USBSW1_GPIO_PORT     GPIOB
#define USBSW1_GPIO_CLK      RCC_APB2Periph_GPIOB
#define USBSW1_GPIO_PIN      GPIO_Pin_7

// USBSW2
#define USBSW2_GPIO_PORT     GPIOB
#define USBSW2_GPIO_CLK      RCC_APB2Periph_GPIOB
#define USBSW2_GPIO_PIN      GPIO_Pin_6

// USBSW3
#define USBSW3_GPIO_PORT     GPIOB
#define USBSW3_GPIO_CLK      RCC_APB2Periph_GPIOB
#define USBSW3_GPIO_PIN      GPIO_Pin_5

// USBSW4
#define USBSW4_GPIO_PORT     GPIOB
#define USBSW4_GPIO_CLK      RCC_APB2Periph_GPIOB
#define USBSW4_GPIO_PIN      GPIO_Pin_4

// USBSW5
#define USBSW5_GPIO_PORT     GPIOB
#define USBSW5_GPIO_CLK      RCC_APB2Periph_GPIOB
#define USBSW5_GPIO_PIN      GPIO_Pin_3

// USBSW6
#define USBSW6_GPIO_PORT     GPIOB
#define USBSW6_GPIO_CLK      RCC_APB2Periph_GPIOB
#define USBSW6_GPIO_PIN      GPIO_Pin_1

// SCL
#define SCL_GPIO_PORT        GPIOB
#define SCL_GPIO_CLK         RCC_APB2Periph_GPIOB
#define SCL_GPIO_PIN         GPIO_Pin_8

// SDA
#define SDA_GPIO_PORT        GPIOB
#define SDA_GPIO_CLK         RCC_APB2Periph_GPIOB
#define SDA_GPIO_PIN         GPIO_Pin_9


#define ON  0
#define OFF 1

/* ֱ�Ӳ����Ĵ����ķ�������IO */
#define	digitalHi(p,i)		 {p->BSRR=i;}	 //���Ϊ�ߵ�ƽ		
#define digitalLo(p,i)		 {p->BRR=i;}	 //����͵�ƽ
#define digitalToggle(p,i) {p->ODR ^=i;} //�����ת״̬

void MY_GPIO_Config(void);

#endif 
