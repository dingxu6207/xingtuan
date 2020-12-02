#ifndef __IODEF_H
#define	__IODEF_H

//#define Focuser_B_DRV8825
#define Focuser_B_TMC2208
//#define Focuser_C_DRV8825
//#define Focuser_C_TMC2208

#include "stm32f10x.h"
/////////////////////////////////////////////////
//Focuser4X4-DRV8825
/////////////////////////////////////////////////

#ifdef Focuser_B_DRV8825

//PFO信号
#define PFO_GPIO_PORT        GPIOB
#define PFO_GPIO_CLK         (RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO)
#define PFO_GPIO_PIN         GPIO_Pin_0
#define PFO_EXTI_LINE        EXTI_Line0
#define PFO_EXTI_IRQ         EXTI0_IRQn
#define PFO_IRQHandler       EXTI0_IRQHandler
#define PFO_EXTI_PORTSOURCE  GPIO_PortSourceGPIOB
#define PFO_EXTI_PINSOURCE   GPIO_PinSource0

//TEMP信号
#define TEMP_GPIO_PORT        GPIOB
#define TEMP_GPIO_CLK         RCC_APB2Periph_GPIOB
#define TEMP_GPIO_PIN         GPIO_Pin_12
//SCLSDA不用
// SCL信号
#define SCL_GPIO_PORT        GPIOB
#define SCL_GPIO_CLK         RCC_APB2Periph_GPIOB
#define SCL_GPIO_PIN         GPIO_Pin_8

// SDA信号
#define SDA_GPIO_PORT        GPIOB
#define SDA_GPIO_CLK         RCC_APB2Periph_GPIOB
#define SDA_GPIO_PIN         GPIO_Pin_9

// SLP信号
#define SLP_GPIO_PORT    		GPIOB
#define SLP_GPIO_CLK 	    	RCC_APB2Periph_GPIOB		
#define SLP_GPIO_PIN		    GPIO_Pin_6  

// FLT信号
#define FLT_GPIO_PORT    		GPIOB
#define FLT_GPIO_CLK 	    	RCC_APB2Periph_GPIOB		
#define FLT_GPIO_PIN		    GPIO_Pin_5  

// DIR信号
#define DIR_GPIO_PORT    		GPIOB
#define DIR_GPIO_CLK 	    	RCC_APB2Periph_GPIOB		
#define DIR_GPIO_PIN		    GPIO_Pin_4                 

// EN信号
#define EN_GPIO_PORT    	  GPIOB			              
#define EN_GPIO_CLK 	      RCC_APB2Periph_GPIOB		
#define EN_GPIO_PIN		    	GPIO_Pin_3		        

//STEP信号 
#define STEP_GPIO_PORT      GPIOA
#define STEP_GPIO_CLK       RCC_APB2Periph_GPIOA
#define STEP_GPIO_PIN       GPIO_Pin_15

//HOME信号 
#define HOME_GPIO_PORT      GPIOA
#define HOME_GPIO_CLK       RCC_APB2Periph_GPIOA
#define HOME_GPIO_PIN       GPIO_Pin_14

//MO,M1,M2不用
//M0信号
#define M0_GPIO_PORT        GPIOB
#define M0_GPIO_CLK         RCC_APB2Periph_GPIOB
#define M0_GPIO_PIN         GPIO_Pin_13

//M1信号 
#define M1_GPIO_PORT        GPIOB
#define M1_GPIO_CLK         RCC_APB2Periph_GPIOB
#define M1_GPIO_PIN         GPIO_Pin_14

//M2信号 
#define M2_GPIO_PORT        GPIOA
#define M2_GPIO_CLK         RCC_APB2Periph_GPIOA
#define M2_GPIO_PIN         GPIO_Pin_15

#endif

//////////////////////////////////////////////////
//Focuser4X4-TMC2208
//////////////////////////////////////////////////

#ifdef Focuser_B_TMC2208

//TEMP信号
#define TEMP_GPIO_PORT        GPIOA
#define TEMP_GPIO_CLK         RCC_APB2Periph_GPIOA
#define TEMP_GPIO_PIN         GPIO_Pin_0
/*
// Hand Up信号
#define HU_GPIO_PORT        GPIOA
#define HU_GPIO_CLK         RCC_APB2Periph_GPIOA
#define HU_GPIO_PIN         GPIO_Pin_11

// Hand Right信号
#define HR_GPIO_PORT        GPIOA
#define HR_GPIO_CLK         RCC_APB2Periph_GPIOA
#define HR_GPIO_PIN         GPIO_Pin_12

// Hand Down信号
#define HD_GPIO_PORT        GPIOA
#define HD_GPIO_CLK         RCC_APB2Periph_GPIOA
#define HD_GPIO_PIN         GPIO_Pin_13
*/

//PFO信号
#define PFO_GPIO_PORT        GPIOB
#define PFO_GPIO_CLK         (RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO)
#define PFO_GPIO_PIN         GPIO_Pin_11
#define PFO_EXTI_LINE        EXTI_Line11
#define PFO_EXTI_IRQ         EXTI15_10_IRQn
#define PFO_IRQHandler       EXTI15_10_IRQHandler//参考中断分组
#define PFO_EXTI_PORTSOURCE  GPIO_PortSourceGPIOB
#define PFO_EXTI_PINSOURCE   GPIO_PinSource0

//DIAG信号 
#define DIAG_GPIO_PORT      GPIOC
#define DIAG_GPIO_CLK       RCC_APB2Periph_GPIOC
#define DIAG_GPIO_PIN       GPIO_Pin_14

// EN信号
#define EN_GPIO_PORT    	  GPIOB		              
#define EN_GPIO_CLK 	      RCC_APB2Periph_GPIOB		
#define EN_GPIO_PIN		    	GPIO_Pin_9		

//PDN信号 
#define PDN_GPIO_PORT      GPIOB
#define PDN_GPIO_CLK       RCC_APB2Periph_GPIOB
#define PDN_GPIO_PIN       GPIO_Pin_6

//STEP信号 
#define STEP_GPIO_PORT      GPIOB
#define STEP_GPIO_CLK       RCC_APB2Periph_GPIOB
#define STEP_GPIO_PIN       GPIO_Pin_5

// DIR信号
#define DIR_GPIO_PORT    		GPIOB
#define DIR_GPIO_CLK 	    	RCC_APB2Periph_GPIOB		
#define DIR_GPIO_PIN		    GPIO_Pin_4  


/*

//INDEX信号 
#define INDEX_GPIO_PORT      GPIOB
#define INDEX_GPIO_CLK       RCC_APB2Periph_GPIOB
#define INDEX_GPIO_PIN       GPIO_Pin_3

//MS1,MS2
//MS2信号
#define MS2_GPIO_PORT        GPIOB
#define MS2_GPIO_CLK         RCC_APB2Periph_GPIOB
#define MS2_GPIO_PIN         GPIO_Pin_5
//MS1信号
#define MS1_GPIO_PORT        GPIOB
#define MS1_GPIO_CLK         RCC_APB2Periph_GPIOB
#define MS1_GPIO_PIN         GPIO_Pin_6
*/
//SCL信号不用，仅为了程序正确运行
// SCL信号
#define SCL_GPIO_PORT        GPIOB
#define SCL_GPIO_CLK         RCC_APB2Periph_GPIOB
#define SCL_GPIO_PIN         GPIO_Pin_8

//SDA信号不用，仅为了程序正确运行
#define SDA_GPIO_PORT        GPIOB
#define SDA_GPIO_CLK         RCC_APB2Periph_GPIOB
#define SDA_GPIO_PIN         GPIO_Pin_7

// SLP信号，这里不用，仅为了程序正确运行
#define SLP_GPIO_PORT    		GPIOB
#define SLP_GPIO_CLK 	    	RCC_APB2Periph_GPIOB		
#define SLP_GPIO_PIN		    GPIO_Pin_10  

// FLT信号，这里不用，仅为了程序正确运行
#define FLT_GPIO_PORT    		GPIOB
#define FLT_GPIO_CLK 	    	RCC_APB2Periph_GPIOB		
#define FLT_GPIO_PIN		    GPIO_Pin_12   //11       

//HOME信号，这里不用，仅为了程序正确运行
#define HOME_GPIO_PORT      GPIOB
#define HOME_GPIO_CLK       RCC_APB2Periph_GPIOB
#define HOME_GPIO_PIN       GPIO_Pin_12
//MO,M1,M2，这里不用，仅为了程序正确运行
//M0信号
#define M0_GPIO_PORT        GPIOB
#define M0_GPIO_CLK         RCC_APB2Periph_GPIOB
#define M0_GPIO_PIN         GPIO_Pin_13

//M1信号 
#define M1_GPIO_PORT        GPIOB
#define M1_GPIO_CLK         RCC_APB2Periph_GPIOB
#define M1_GPIO_PIN         GPIO_Pin_14

//M2信号
#define M2_GPIO_PORT        GPIOB
#define M2_GPIO_CLK         RCC_APB2Periph_GPIOB
#define M2_GPIO_PIN         GPIO_Pin_15

#endif
//////////////////////////////////////////////////
//Focuser4X7.8-TMC2208
//////////////////////////////////////////////////

#ifdef Focuser_C_TMC2208

//PFO信号
#define PFO_GPIO_PORT        GPIOB
#define PFO_GPIO_CLK         (RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO)
#define PFO_GPIO_PIN         GPIO_Pin_0
#define PFO_EXTI_LINE        EXTI_Line0
#define PFO_EXTI_IRQ         EXTI0_IRQn
#define PFO_IRQHandler       EXTI0_IRQHandler
#define PFO_EXTI_PORTSOURCE  GPIO_PortSourceGPIOB
#define PFO_EXTI_PINSOURCE   GPIO_PinSource0

//TEMP信号
#define TEMP_GPIO_PORT        GPIOA
#define TEMP_GPIO_CLK         RCC_APB2Periph_GPIOA
#define TEMP_GPIO_PIN         GPIO_Pin_0

//BRST信号
#define BRST_GPIO_PORT        GPIOA
#define BRST_GPIO_CLK         RCC_APB2Periph_GPIOA
#define BRST_GPIO_PIN         GPIO_Pin_1
// EN信号
#define EN_GPIO_PORT    	  GPIOB		              
#define EN_GPIO_CLK 	      RCC_APB2Periph_GPIOB		
#define EN_GPIO_PIN		    	GPIO_Pin_7		

//SCL信号不用，仅为了程序正确运行
// SCL信号
#define SCL_GPIO_PORT        GPIOB
#define SCL_GPIO_CLK         RCC_APB2Periph_GPIOB
#define SCL_GPIO_PIN         GPIO_Pin_8

//SDA信号不用，仅为了程序正确运行
#define SDA_GPIO_PORT        GPIOB
#define SDA_GPIO_CLK         RCC_APB2Periph_GPIOB
#define SDA_GPIO_PIN         GPIO_Pin_9

// SLP信号，这里不用，仅为了程序正确运行
#define SLP_GPIO_PORT    		GPIOB
#define SLP_GPIO_CLK 	    	RCC_APB2Periph_GPIOB		
#define SLP_GPIO_PIN		    GPIO_Pin_10  

// FLT信号，这里不用，仅为了程序正确运行
#define FLT_GPIO_PORT    		GPIOB
#define FLT_GPIO_CLK 	    	RCC_APB2Periph_GPIOB		
#define FLT_GPIO_PIN		    GPIO_Pin_11          

// DIR信号
#define DIR_GPIO_PORT    		GPIOA
#define DIR_GPIO_CLK 	    	RCC_APB2Periph_GPIOA		
#define DIR_GPIO_PIN		    GPIO_Pin_12                 

//STEP信号 
#define STEP_GPIO_PORT      GPIOA
#define STEP_GPIO_CLK       RCC_APB2Periph_GPIOA
#define STEP_GPIO_PIN       GPIO_Pin_13

//PDN信号 
#define PDN_GPIO_PORT      GPIOA
#define PDN_GPIO_CLK       RCC_APB2Periph_GPIOA
#define PDN_GPIO_PIN       GPIO_Pin_15

//INDEX信号 
#define INDEX_GPIO_PORT      GPIOB
#define INDEX_GPIO_CLK       RCC_APB2Periph_GPIOB
#define INDEX_GPIO_PIN       GPIO_Pin_3

//DIAG信号 
#define DIAG_GPIO_PORT      GPIOB
#define DIAG_GPIO_CLK       RCC_APB2Periph_GPIOB
#define DIAG_GPIO_PIN       GPIO_Pin_4

//MS1,MS2
//MS2信号
#define MS2_GPIO_PORT        GPIOB
#define MS2_GPIO_CLK         RCC_APB2Periph_GPIOB
#define MS2_GPIO_PIN         GPIO_Pin_5
//MS1信号
#define MS1_GPIO_PORT        GPIOB
#define MS1_GPIO_CLK         RCC_APB2Periph_GPIOB
#define MS1_GPIO_PIN         GPIO_Pin_6

//HOME信号，这里不用，仅为了程序正确运行
#define HOME_GPIO_PORT      GPIOB
#define HOME_GPIO_CLK       RCC_APB2Periph_GPIOB
#define HOME_GPIO_PIN       GPIO_Pin_1
//MO,M1,M2，这里不用，仅为了程序正确运行
//M0信号
#define M0_GPIO_PORT        GPIOB
#define M0_GPIO_CLK         RCC_APB2Periph_GPIOB
#define M0_GPIO_PIN         GPIO_Pin_13

//M1信号 
#define M1_GPIO_PORT        GPIOA
#define M1_GPIO_CLK         RCC_APB2Periph_GPIOA
#define M1_GPIO_PIN         GPIO_Pin_14

//M2信号，这里不用，仅为了程序正确运行
#define M2_GPIO_PORT        GPIOB
#define M2_GPIO_CLK         RCC_APB2Periph_GPIOB
#define M2_GPIO_PIN         GPIO_Pin_15

#endif
/////////////////////////////////////////////////
//Focuser4X7.8-DRV8825
/////////////////////////////////////////////////

#ifdef Focuser_C_DRV8825

//PFO信号
#define PFO_GPIO_PORT         GPIOB
#define PFO_GPIO_CLK          (RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO)
#define PFO_GPIO_PIN          GPIO_Pin_0
#define PFO_EXTI_LINE         EXTI_Line0
#define PFO_EXTI_IRQ          EXTI0_IRQn
#define PFO_IRQHandler        EXTI0_IRQHandler
#define PFO_EXTI_PORTSOURCE   GPIO_PortSourceGPIOB
#define PFO_EXTI_PINSOURCE    GPIO_PinSource0

//TEMP信号
#define TEMP_GPIO_PORT        GPIOA
#define TEMP_GPIO_CLK         RCC_APB2Periph_GPIOA
#define TEMP_GPIO_PIN         GPIO_Pin_0

//BRST信号
#define BRST_GPIO_PORT        GPIOA
#define BRST_GPIO_CLK         RCC_APB2Periph_GPIOA
#define BRST_GPIO_PIN         GPIO_Pin_1

//D1信号
#define D1_GPIO_PORT          GPIOA
#define D1_GPIO_CLK           RCC_APB2Periph_GPIOA
#define D1_GPIO_PIN           GPIO_Pin_4

//D2信号
#define D2_GPIO_PORT          GPIOA
#define D2_GPIO_CLK           RCC_APB2Periph_GPIOA
#define D2_GPIO_PIN           GPIO_Pin_5

//D3信号
#define D3_GPIO_PORT          GPIOA
#define D3_GPIO_CLK           RCC_APB2Periph_GPIOA
#define D3_GPIO_PIN           GPIO_Pin_6

//D4信号
#define D4_GPIO_PORT          GPIOA
#define D4_GPIO_CLK           RCC_APB2Periph_GPIOA
#define D4_GPIO_PIN           GPIO_Pin_7

// SCL信号
#define SCL_GPIO_PORT        GPIOB
#define SCL_GPIO_CLK         RCC_APB2Periph_GPIOB
#define SCL_GPIO_PIN         GPIO_Pin_10

// SDA信号
#define SDA_GPIO_PORT        GPIOB
#define SDA_GPIO_CLK         RCC_APB2Periph_GPIOB
#define SDA_GPIO_PIN         GPIO_Pin_11

// SLP信号
#define SLP_GPIO_PORT    	   GPIOB
#define SLP_GPIO_CLK 	       RCC_APB2Periph_GPIOB		
#define SLP_GPIO_PIN		     GPIO_Pin_9  

// FLT信号
#define FLT_GPIO_PORT    	   GPIOB
#define FLT_GPIO_CLK 	       RCC_APB2Periph_GPIOB		
#define FLT_GPIO_PIN		     GPIO_Pin_8  

// DIR信号
#define DIR_GPIO_PORT    	  GPIOB
#define DIR_GPIO_CLK 	    	RCC_APB2Periph_GPIOB		
#define DIR_GPIO_PIN		    GPIO_Pin_7                 

// EN信号
#define EN_GPIO_PORT    	  GPIOB			              
#define EN_GPIO_CLK 	      RCC_APB2Periph_GPIOB		
#define EN_GPIO_PIN		    	GPIO_Pin_6		        

//STEP信号 
#define STEP_GPIO_PORT      GPIOB
#define STEP_GPIO_CLK       RCC_APB2Periph_GPIOB
#define STEP_GPIO_PIN       GPIO_Pin_5

//M0信号
#define M0_GPIO_PORT        GPIOB
#define M0_GPIO_CLK         RCC_APB2Periph_GPIOB
#define M0_GPIO_PIN         GPIO_Pin_4

//M1信号 
#define M1_GPIO_PORT        GPIOB
#define M1_GPIO_CLK         RCC_APB2Periph_GPIOB
#define M1_GPIO_PIN         GPIO_Pin_3

//M2信号 
#define M2_GPIO_PORT        GPIOA
#define M2_GPIO_CLK         RCC_APB2Periph_GPIOA
#define M2_GPIO_PIN         GPIO_Pin_15



// SLP2信号
#define SLP2_GPIO_PORT    	  GPIOA
#define SLP2_GPIO_CLK 	      RCC_APB2Periph_GPIOA		
#define SLP2_GPIO_PIN		    GPIO_Pin_14  

// FLT2信号
#define FLT2_GPIO_PORT    	  GPIOA
#define FLT2_GPIO_CLK 	      RCC_APB2Periph_GPIOA		
#define FLT2_GPIO_PIN		    GPIO_Pin_13  

// DIR2信号
#define DIR2_GPIO_PORT    	  GPIOA
#define DIR2_GPIO_CLK 	      RCC_APB2Periph_GPIOA		
#define DIR2_GPIO_PIN		    GPIO_Pin_12                 

// EN2信号
#define EN2_GPIO_PORT    	  GPIOA			              
#define EN2_GPIO_CLK 	      RCC_APB2Periph_GPIOA		
#define EN2_GPIO_PIN		      GPIO_Pin_11		        

//STEP2信号 
#define STEP2_GPIO_PORT      GPIOA
#define STEP2_GPIO_CLK       RCC_APB2Periph_GPIOA
#define STEP2_GPIO_PIN       GPIO_Pin_8

//M02信号
#define M02_GPIO_PORT        GPIOB
#define M02_GPIO_CLK         RCC_APB2Periph_GPIOB
#define M02_GPIO_PIN         GPIO_Pin_15

//M12信号 
#define M12_GPIO_PORT        GPIOB
#define M12_GPIO_CLK         RCC_APB2Periph_GPIOB
#define M12_GPIO_PIN         GPIO_Pin_14

//M22信号 
#define M22_GPIO_PORT        GPIOB
#define M22_GPIO_CLK         RCC_APB2Periph_GPIOB
#define M22_GPIO_PIN         GPIO_Pin_13

#endif

/*
// SLP信号
#define SLP_GPIO_PORT    	  GPIOA
#define SLP_GPIO_CLK 	      RCC_APB2Periph_GPIOA		
#define SLP_GPIO_PIN		    GPIO_Pin_14  

// FLT信号
#define FLT_GPIO_PORT    	  GPIOA
#define FLT_GPIO_CLK 	      RCC_APB2Periph_GPIOA		
#define FLT_GPIO_PIN		    GPIO_Pin_13  

// DIR信号
#define DIR_GPIO_PORT    	  GPIOA
#define DIR_GPIO_CLK 	      RCC_APB2Periph_GPIOA		
#define DIR_GPIO_PIN		    GPIO_Pin_12                 

// EN信号
#define EN_GPIO_PORT    	  GPIOA			              
#define EN_GPIO_CLK 	      RCC_APB2Periph_GPIOA		
#define EN_GPIO_PIN		      GPIO_Pin_11		        

//STEP信号 
#define STEP_GPIO_PORT      GPIOA
#define STEP_GPIO_CLK       RCC_APB2Periph_GPIOA
#define STEP_GPIO_PIN       GPIO_Pin_8

//M0信号
#define M0_GPIO_PORT        GPIOB
#define M0_GPIO_CLK         RCC_APB2Periph_GPIOB
#define M0_GPIO_PIN         GPIO_Pin_15

//M1信号 
#define M1_GPIO_PORT        GPIOB
#define M1_GPIO_CLK         RCC_APB2Periph_GPIOB
#define M1_GPIO_PIN         GPIO_Pin_14

//M2信号 
#define M2_GPIO_PORT        GPIOB
#define M2_GPIO_CLK         RCC_APB2Periph_GPIOB
#define M2_GPIO_PIN         GPIO_Pin_13


// SLP2信号
#define SLP2_GPIO_PORT    	GPIOB
#define SLP2_GPIO_CLK 	    RCC_APB2Periph_GPIOB		
#define SLP2_GPIO_PIN		    GPIO_Pin_9  

// FLT2信号
#define FLT2_GPIO_PORT    	GPIOB
#define FLT2_GPIO_CLK 	    RCC_APB2Periph_GPIOB		
#define FLT2_GPIO_PIN		    GPIO_Pin_8  

// DIR2信号
#define DIR2_GPIO_PORT    	GPIOB
#define DIR2_GPIO_CLK 	    RCC_APB2Periph_GPIOB		
#define DIR2_GPIO_PIN		    GPIO_Pin_7                 

// EN2信号
#define EN2_GPIO_PORT    	  GPIOB			              
#define EN2_GPIO_CLK 	      RCC_APB2Periph_GPIOB		
#define EN2_GPIO_PIN		    GPIO_Pin_6		        

//STEP2信号 
#define STEP2_GPIO_PORT      GPIOB
#define STEP2_GPIO_CLK       RCC_APB2Periph_GPIOB
#define STEP2_GPIO_PIN       GPIO_Pin_5

//M02信号
#define M02_GPIO_PORT        GPIOB
#define M02_GPIO_CLK         RCC_APB2Periph_GPIOB
#define M02_GPIO_PIN         GPIO_Pin_4

//M12信号 
#define M12_GPIO_PORT        GPIOB
#define M12_GPIO_CLK         RCC_APB2Periph_GPIOB
#define M12_GPIO_PIN         GPIO_Pin_3

//M22信号 
#define M22_GPIO_PORT        GPIOA
#define M22_GPIO_CLK         RCC_APB2Periph_GPIOA
#define M22_GPIO_PIN         GPIO_Pin_15
*/
#define ON  0
#define OFF 1

/* 直接操作寄存器的方法控制IO */
#define	digitalHi(p,i)		 {p->BSRR=i;}	 //输出为高电平		
#define digitalLo(p,i)		 {p->BRR=i;}	 //输出低电平
#define digitalToggle(p,i) {p->ODR ^=i;} //输出反转状态

void MY_GPIO_Config(void);
//void PFO_GPIO_Config(void);

#endif 
