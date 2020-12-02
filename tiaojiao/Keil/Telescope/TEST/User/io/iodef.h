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

//PFO�ź�
#define PFO_GPIO_PORT        GPIOB
#define PFO_GPIO_CLK         (RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO)
#define PFO_GPIO_PIN         GPIO_Pin_0
#define PFO_EXTI_LINE        EXTI_Line0
#define PFO_EXTI_IRQ         EXTI0_IRQn
#define PFO_IRQHandler       EXTI0_IRQHandler
#define PFO_EXTI_PORTSOURCE  GPIO_PortSourceGPIOB
#define PFO_EXTI_PINSOURCE   GPIO_PinSource0

//TEMP�ź�
#define TEMP_GPIO_PORT        GPIOB
#define TEMP_GPIO_CLK         RCC_APB2Periph_GPIOB
#define TEMP_GPIO_PIN         GPIO_Pin_12
//SCLSDA����
// SCL�ź�
#define SCL_GPIO_PORT        GPIOB
#define SCL_GPIO_CLK         RCC_APB2Periph_GPIOB
#define SCL_GPIO_PIN         GPIO_Pin_8

// SDA�ź�
#define SDA_GPIO_PORT        GPIOB
#define SDA_GPIO_CLK         RCC_APB2Periph_GPIOB
#define SDA_GPIO_PIN         GPIO_Pin_9

// SLP�ź�
#define SLP_GPIO_PORT    		GPIOB
#define SLP_GPIO_CLK 	    	RCC_APB2Periph_GPIOB		
#define SLP_GPIO_PIN		    GPIO_Pin_6  

// FLT�ź�
#define FLT_GPIO_PORT    		GPIOB
#define FLT_GPIO_CLK 	    	RCC_APB2Periph_GPIOB		
#define FLT_GPIO_PIN		    GPIO_Pin_5  

// DIR�ź�
#define DIR_GPIO_PORT    		GPIOB
#define DIR_GPIO_CLK 	    	RCC_APB2Periph_GPIOB		
#define DIR_GPIO_PIN		    GPIO_Pin_4                 

// EN�ź�
#define EN_GPIO_PORT    	  GPIOB			              
#define EN_GPIO_CLK 	      RCC_APB2Periph_GPIOB		
#define EN_GPIO_PIN		    	GPIO_Pin_3		        

//STEP�ź� 
#define STEP_GPIO_PORT      GPIOA
#define STEP_GPIO_CLK       RCC_APB2Periph_GPIOA
#define STEP_GPIO_PIN       GPIO_Pin_15

//HOME�ź� 
#define HOME_GPIO_PORT      GPIOA
#define HOME_GPIO_CLK       RCC_APB2Periph_GPIOA
#define HOME_GPIO_PIN       GPIO_Pin_14

//MO,M1,M2����
//M0�ź�
#define M0_GPIO_PORT        GPIOB
#define M0_GPIO_CLK         RCC_APB2Periph_GPIOB
#define M0_GPIO_PIN         GPIO_Pin_13

//M1�ź� 
#define M1_GPIO_PORT        GPIOB
#define M1_GPIO_CLK         RCC_APB2Periph_GPIOB
#define M1_GPIO_PIN         GPIO_Pin_14

//M2�ź� 
#define M2_GPIO_PORT        GPIOA
#define M2_GPIO_CLK         RCC_APB2Periph_GPIOA
#define M2_GPIO_PIN         GPIO_Pin_15

#endif

//////////////////////////////////////////////////
//Focuser4X4-TMC2208
//////////////////////////////////////////////////

#ifdef Focuser_B_TMC2208

//TEMP�ź�
#define TEMP_GPIO_PORT        GPIOA
#define TEMP_GPIO_CLK         RCC_APB2Periph_GPIOA
#define TEMP_GPIO_PIN         GPIO_Pin_0
/*
// Hand Up�ź�
#define HU_GPIO_PORT        GPIOA
#define HU_GPIO_CLK         RCC_APB2Periph_GPIOA
#define HU_GPIO_PIN         GPIO_Pin_11

// Hand Right�ź�
#define HR_GPIO_PORT        GPIOA
#define HR_GPIO_CLK         RCC_APB2Periph_GPIOA
#define HR_GPIO_PIN         GPIO_Pin_12

// Hand Down�ź�
#define HD_GPIO_PORT        GPIOA
#define HD_GPIO_CLK         RCC_APB2Periph_GPIOA
#define HD_GPIO_PIN         GPIO_Pin_13
*/

//PFO�ź�
#define PFO_GPIO_PORT        GPIOB
#define PFO_GPIO_CLK         (RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO)
#define PFO_GPIO_PIN         GPIO_Pin_11
#define PFO_EXTI_LINE        EXTI_Line11
#define PFO_EXTI_IRQ         EXTI15_10_IRQn
#define PFO_IRQHandler       EXTI15_10_IRQHandler//�ο��жϷ���
#define PFO_EXTI_PORTSOURCE  GPIO_PortSourceGPIOB
#define PFO_EXTI_PINSOURCE   GPIO_PinSource0

//DIAG�ź� 
#define DIAG_GPIO_PORT      GPIOC
#define DIAG_GPIO_CLK       RCC_APB2Periph_GPIOC
#define DIAG_GPIO_PIN       GPIO_Pin_14

// EN�ź�
#define EN_GPIO_PORT    	  GPIOB		              
#define EN_GPIO_CLK 	      RCC_APB2Periph_GPIOB		
#define EN_GPIO_PIN		    	GPIO_Pin_9		

//PDN�ź� 
#define PDN_GPIO_PORT      GPIOB
#define PDN_GPIO_CLK       RCC_APB2Periph_GPIOB
#define PDN_GPIO_PIN       GPIO_Pin_6

//STEP�ź� 
#define STEP_GPIO_PORT      GPIOB
#define STEP_GPIO_CLK       RCC_APB2Periph_GPIOB
#define STEP_GPIO_PIN       GPIO_Pin_5

// DIR�ź�
#define DIR_GPIO_PORT    		GPIOB
#define DIR_GPIO_CLK 	    	RCC_APB2Periph_GPIOB		
#define DIR_GPIO_PIN		    GPIO_Pin_4  


/*

//INDEX�ź� 
#define INDEX_GPIO_PORT      GPIOB
#define INDEX_GPIO_CLK       RCC_APB2Periph_GPIOB
#define INDEX_GPIO_PIN       GPIO_Pin_3

//MS1,MS2
//MS2�ź�
#define MS2_GPIO_PORT        GPIOB
#define MS2_GPIO_CLK         RCC_APB2Periph_GPIOB
#define MS2_GPIO_PIN         GPIO_Pin_5
//MS1�ź�
#define MS1_GPIO_PORT        GPIOB
#define MS1_GPIO_CLK         RCC_APB2Periph_GPIOB
#define MS1_GPIO_PIN         GPIO_Pin_6
*/
//SCL�źŲ��ã���Ϊ�˳�����ȷ����
// SCL�ź�
#define SCL_GPIO_PORT        GPIOB
#define SCL_GPIO_CLK         RCC_APB2Periph_GPIOB
#define SCL_GPIO_PIN         GPIO_Pin_8

//SDA�źŲ��ã���Ϊ�˳�����ȷ����
#define SDA_GPIO_PORT        GPIOB
#define SDA_GPIO_CLK         RCC_APB2Periph_GPIOB
#define SDA_GPIO_PIN         GPIO_Pin_7

// SLP�źţ����ﲻ�ã���Ϊ�˳�����ȷ����
#define SLP_GPIO_PORT    		GPIOB
#define SLP_GPIO_CLK 	    	RCC_APB2Periph_GPIOB		
#define SLP_GPIO_PIN		    GPIO_Pin_10  

// FLT�źţ����ﲻ�ã���Ϊ�˳�����ȷ����
#define FLT_GPIO_PORT    		GPIOB
#define FLT_GPIO_CLK 	    	RCC_APB2Periph_GPIOB		
#define FLT_GPIO_PIN		    GPIO_Pin_12   //11       

//HOME�źţ����ﲻ�ã���Ϊ�˳�����ȷ����
#define HOME_GPIO_PORT      GPIOB
#define HOME_GPIO_CLK       RCC_APB2Periph_GPIOB
#define HOME_GPIO_PIN       GPIO_Pin_12
//MO,M1,M2�����ﲻ�ã���Ϊ�˳�����ȷ����
//M0�ź�
#define M0_GPIO_PORT        GPIOB
#define M0_GPIO_CLK         RCC_APB2Periph_GPIOB
#define M0_GPIO_PIN         GPIO_Pin_13

//M1�ź� 
#define M1_GPIO_PORT        GPIOB
#define M1_GPIO_CLK         RCC_APB2Periph_GPIOB
#define M1_GPIO_PIN         GPIO_Pin_14

//M2�ź�
#define M2_GPIO_PORT        GPIOB
#define M2_GPIO_CLK         RCC_APB2Periph_GPIOB
#define M2_GPIO_PIN         GPIO_Pin_15

#endif
//////////////////////////////////////////////////
//Focuser4X7.8-TMC2208
//////////////////////////////////////////////////

#ifdef Focuser_C_TMC2208

//PFO�ź�
#define PFO_GPIO_PORT        GPIOB
#define PFO_GPIO_CLK         (RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO)
#define PFO_GPIO_PIN         GPIO_Pin_0
#define PFO_EXTI_LINE        EXTI_Line0
#define PFO_EXTI_IRQ         EXTI0_IRQn
#define PFO_IRQHandler       EXTI0_IRQHandler
#define PFO_EXTI_PORTSOURCE  GPIO_PortSourceGPIOB
#define PFO_EXTI_PINSOURCE   GPIO_PinSource0

//TEMP�ź�
#define TEMP_GPIO_PORT        GPIOA
#define TEMP_GPIO_CLK         RCC_APB2Periph_GPIOA
#define TEMP_GPIO_PIN         GPIO_Pin_0

//BRST�ź�
#define BRST_GPIO_PORT        GPIOA
#define BRST_GPIO_CLK         RCC_APB2Periph_GPIOA
#define BRST_GPIO_PIN         GPIO_Pin_1
// EN�ź�
#define EN_GPIO_PORT    	  GPIOB		              
#define EN_GPIO_CLK 	      RCC_APB2Periph_GPIOB		
#define EN_GPIO_PIN		    	GPIO_Pin_7		

//SCL�źŲ��ã���Ϊ�˳�����ȷ����
// SCL�ź�
#define SCL_GPIO_PORT        GPIOB
#define SCL_GPIO_CLK         RCC_APB2Periph_GPIOB
#define SCL_GPIO_PIN         GPIO_Pin_8

//SDA�źŲ��ã���Ϊ�˳�����ȷ����
#define SDA_GPIO_PORT        GPIOB
#define SDA_GPIO_CLK         RCC_APB2Periph_GPIOB
#define SDA_GPIO_PIN         GPIO_Pin_9

// SLP�źţ����ﲻ�ã���Ϊ�˳�����ȷ����
#define SLP_GPIO_PORT    		GPIOB
#define SLP_GPIO_CLK 	    	RCC_APB2Periph_GPIOB		
#define SLP_GPIO_PIN		    GPIO_Pin_10  

// FLT�źţ����ﲻ�ã���Ϊ�˳�����ȷ����
#define FLT_GPIO_PORT    		GPIOB
#define FLT_GPIO_CLK 	    	RCC_APB2Periph_GPIOB		
#define FLT_GPIO_PIN		    GPIO_Pin_11          

// DIR�ź�
#define DIR_GPIO_PORT    		GPIOA
#define DIR_GPIO_CLK 	    	RCC_APB2Periph_GPIOA		
#define DIR_GPIO_PIN		    GPIO_Pin_12                 

//STEP�ź� 
#define STEP_GPIO_PORT      GPIOA
#define STEP_GPIO_CLK       RCC_APB2Periph_GPIOA
#define STEP_GPIO_PIN       GPIO_Pin_13

//PDN�ź� 
#define PDN_GPIO_PORT      GPIOA
#define PDN_GPIO_CLK       RCC_APB2Periph_GPIOA
#define PDN_GPIO_PIN       GPIO_Pin_15

//INDEX�ź� 
#define INDEX_GPIO_PORT      GPIOB
#define INDEX_GPIO_CLK       RCC_APB2Periph_GPIOB
#define INDEX_GPIO_PIN       GPIO_Pin_3

//DIAG�ź� 
#define DIAG_GPIO_PORT      GPIOB
#define DIAG_GPIO_CLK       RCC_APB2Periph_GPIOB
#define DIAG_GPIO_PIN       GPIO_Pin_4

//MS1,MS2
//MS2�ź�
#define MS2_GPIO_PORT        GPIOB
#define MS2_GPIO_CLK         RCC_APB2Periph_GPIOB
#define MS2_GPIO_PIN         GPIO_Pin_5
//MS1�ź�
#define MS1_GPIO_PORT        GPIOB
#define MS1_GPIO_CLK         RCC_APB2Periph_GPIOB
#define MS1_GPIO_PIN         GPIO_Pin_6

//HOME�źţ����ﲻ�ã���Ϊ�˳�����ȷ����
#define HOME_GPIO_PORT      GPIOB
#define HOME_GPIO_CLK       RCC_APB2Periph_GPIOB
#define HOME_GPIO_PIN       GPIO_Pin_1
//MO,M1,M2�����ﲻ�ã���Ϊ�˳�����ȷ����
//M0�ź�
#define M0_GPIO_PORT        GPIOB
#define M0_GPIO_CLK         RCC_APB2Periph_GPIOB
#define M0_GPIO_PIN         GPIO_Pin_13

//M1�ź� 
#define M1_GPIO_PORT        GPIOA
#define M1_GPIO_CLK         RCC_APB2Periph_GPIOA
#define M1_GPIO_PIN         GPIO_Pin_14

//M2�źţ����ﲻ�ã���Ϊ�˳�����ȷ����
#define M2_GPIO_PORT        GPIOB
#define M2_GPIO_CLK         RCC_APB2Periph_GPIOB
#define M2_GPIO_PIN         GPIO_Pin_15

#endif
/////////////////////////////////////////////////
//Focuser4X7.8-DRV8825
/////////////////////////////////////////////////

#ifdef Focuser_C_DRV8825

//PFO�ź�
#define PFO_GPIO_PORT         GPIOB
#define PFO_GPIO_CLK          (RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO)
#define PFO_GPIO_PIN          GPIO_Pin_0
#define PFO_EXTI_LINE         EXTI_Line0
#define PFO_EXTI_IRQ          EXTI0_IRQn
#define PFO_IRQHandler        EXTI0_IRQHandler
#define PFO_EXTI_PORTSOURCE   GPIO_PortSourceGPIOB
#define PFO_EXTI_PINSOURCE    GPIO_PinSource0

//TEMP�ź�
#define TEMP_GPIO_PORT        GPIOA
#define TEMP_GPIO_CLK         RCC_APB2Periph_GPIOA
#define TEMP_GPIO_PIN         GPIO_Pin_0

//BRST�ź�
#define BRST_GPIO_PORT        GPIOA
#define BRST_GPIO_CLK         RCC_APB2Periph_GPIOA
#define BRST_GPIO_PIN         GPIO_Pin_1

//D1�ź�
#define D1_GPIO_PORT          GPIOA
#define D1_GPIO_CLK           RCC_APB2Periph_GPIOA
#define D1_GPIO_PIN           GPIO_Pin_4

//D2�ź�
#define D2_GPIO_PORT          GPIOA
#define D2_GPIO_CLK           RCC_APB2Periph_GPIOA
#define D2_GPIO_PIN           GPIO_Pin_5

//D3�ź�
#define D3_GPIO_PORT          GPIOA
#define D3_GPIO_CLK           RCC_APB2Periph_GPIOA
#define D3_GPIO_PIN           GPIO_Pin_6

//D4�ź�
#define D4_GPIO_PORT          GPIOA
#define D4_GPIO_CLK           RCC_APB2Periph_GPIOA
#define D4_GPIO_PIN           GPIO_Pin_7

// SCL�ź�
#define SCL_GPIO_PORT        GPIOB
#define SCL_GPIO_CLK         RCC_APB2Periph_GPIOB
#define SCL_GPIO_PIN         GPIO_Pin_10

// SDA�ź�
#define SDA_GPIO_PORT        GPIOB
#define SDA_GPIO_CLK         RCC_APB2Periph_GPIOB
#define SDA_GPIO_PIN         GPIO_Pin_11

// SLP�ź�
#define SLP_GPIO_PORT    	   GPIOB
#define SLP_GPIO_CLK 	       RCC_APB2Periph_GPIOB		
#define SLP_GPIO_PIN		     GPIO_Pin_9  

// FLT�ź�
#define FLT_GPIO_PORT    	   GPIOB
#define FLT_GPIO_CLK 	       RCC_APB2Periph_GPIOB		
#define FLT_GPIO_PIN		     GPIO_Pin_8  

// DIR�ź�
#define DIR_GPIO_PORT    	  GPIOB
#define DIR_GPIO_CLK 	    	RCC_APB2Periph_GPIOB		
#define DIR_GPIO_PIN		    GPIO_Pin_7                 

// EN�ź�
#define EN_GPIO_PORT    	  GPIOB			              
#define EN_GPIO_CLK 	      RCC_APB2Periph_GPIOB		
#define EN_GPIO_PIN		    	GPIO_Pin_6		        

//STEP�ź� 
#define STEP_GPIO_PORT      GPIOB
#define STEP_GPIO_CLK       RCC_APB2Periph_GPIOB
#define STEP_GPIO_PIN       GPIO_Pin_5

//M0�ź�
#define M0_GPIO_PORT        GPIOB
#define M0_GPIO_CLK         RCC_APB2Periph_GPIOB
#define M0_GPIO_PIN         GPIO_Pin_4

//M1�ź� 
#define M1_GPIO_PORT        GPIOB
#define M1_GPIO_CLK         RCC_APB2Periph_GPIOB
#define M1_GPIO_PIN         GPIO_Pin_3

//M2�ź� 
#define M2_GPIO_PORT        GPIOA
#define M2_GPIO_CLK         RCC_APB2Periph_GPIOA
#define M2_GPIO_PIN         GPIO_Pin_15



// SLP2�ź�
#define SLP2_GPIO_PORT    	  GPIOA
#define SLP2_GPIO_CLK 	      RCC_APB2Periph_GPIOA		
#define SLP2_GPIO_PIN		    GPIO_Pin_14  

// FLT2�ź�
#define FLT2_GPIO_PORT    	  GPIOA
#define FLT2_GPIO_CLK 	      RCC_APB2Periph_GPIOA		
#define FLT2_GPIO_PIN		    GPIO_Pin_13  

// DIR2�ź�
#define DIR2_GPIO_PORT    	  GPIOA
#define DIR2_GPIO_CLK 	      RCC_APB2Periph_GPIOA		
#define DIR2_GPIO_PIN		    GPIO_Pin_12                 

// EN2�ź�
#define EN2_GPIO_PORT    	  GPIOA			              
#define EN2_GPIO_CLK 	      RCC_APB2Periph_GPIOA		
#define EN2_GPIO_PIN		      GPIO_Pin_11		        

//STEP2�ź� 
#define STEP2_GPIO_PORT      GPIOA
#define STEP2_GPIO_CLK       RCC_APB2Periph_GPIOA
#define STEP2_GPIO_PIN       GPIO_Pin_8

//M02�ź�
#define M02_GPIO_PORT        GPIOB
#define M02_GPIO_CLK         RCC_APB2Periph_GPIOB
#define M02_GPIO_PIN         GPIO_Pin_15

//M12�ź� 
#define M12_GPIO_PORT        GPIOB
#define M12_GPIO_CLK         RCC_APB2Periph_GPIOB
#define M12_GPIO_PIN         GPIO_Pin_14

//M22�ź� 
#define M22_GPIO_PORT        GPIOB
#define M22_GPIO_CLK         RCC_APB2Periph_GPIOB
#define M22_GPIO_PIN         GPIO_Pin_13

#endif

/*
// SLP�ź�
#define SLP_GPIO_PORT    	  GPIOA
#define SLP_GPIO_CLK 	      RCC_APB2Periph_GPIOA		
#define SLP_GPIO_PIN		    GPIO_Pin_14  

// FLT�ź�
#define FLT_GPIO_PORT    	  GPIOA
#define FLT_GPIO_CLK 	      RCC_APB2Periph_GPIOA		
#define FLT_GPIO_PIN		    GPIO_Pin_13  

// DIR�ź�
#define DIR_GPIO_PORT    	  GPIOA
#define DIR_GPIO_CLK 	      RCC_APB2Periph_GPIOA		
#define DIR_GPIO_PIN		    GPIO_Pin_12                 

// EN�ź�
#define EN_GPIO_PORT    	  GPIOA			              
#define EN_GPIO_CLK 	      RCC_APB2Periph_GPIOA		
#define EN_GPIO_PIN		      GPIO_Pin_11		        

//STEP�ź� 
#define STEP_GPIO_PORT      GPIOA
#define STEP_GPIO_CLK       RCC_APB2Periph_GPIOA
#define STEP_GPIO_PIN       GPIO_Pin_8

//M0�ź�
#define M0_GPIO_PORT        GPIOB
#define M0_GPIO_CLK         RCC_APB2Periph_GPIOB
#define M0_GPIO_PIN         GPIO_Pin_15

//M1�ź� 
#define M1_GPIO_PORT        GPIOB
#define M1_GPIO_CLK         RCC_APB2Periph_GPIOB
#define M1_GPIO_PIN         GPIO_Pin_14

//M2�ź� 
#define M2_GPIO_PORT        GPIOB
#define M2_GPIO_CLK         RCC_APB2Periph_GPIOB
#define M2_GPIO_PIN         GPIO_Pin_13


// SLP2�ź�
#define SLP2_GPIO_PORT    	GPIOB
#define SLP2_GPIO_CLK 	    RCC_APB2Periph_GPIOB		
#define SLP2_GPIO_PIN		    GPIO_Pin_9  

// FLT2�ź�
#define FLT2_GPIO_PORT    	GPIOB
#define FLT2_GPIO_CLK 	    RCC_APB2Periph_GPIOB		
#define FLT2_GPIO_PIN		    GPIO_Pin_8  

// DIR2�ź�
#define DIR2_GPIO_PORT    	GPIOB
#define DIR2_GPIO_CLK 	    RCC_APB2Periph_GPIOB		
#define DIR2_GPIO_PIN		    GPIO_Pin_7                 

// EN2�ź�
#define EN2_GPIO_PORT    	  GPIOB			              
#define EN2_GPIO_CLK 	      RCC_APB2Periph_GPIOB		
#define EN2_GPIO_PIN		    GPIO_Pin_6		        

//STEP2�ź� 
#define STEP2_GPIO_PORT      GPIOB
#define STEP2_GPIO_CLK       RCC_APB2Periph_GPIOB
#define STEP2_GPIO_PIN       GPIO_Pin_5

//M02�ź�
#define M02_GPIO_PORT        GPIOB
#define M02_GPIO_CLK         RCC_APB2Periph_GPIOB
#define M02_GPIO_PIN         GPIO_Pin_4

//M12�ź� 
#define M12_GPIO_PORT        GPIOB
#define M12_GPIO_CLK         RCC_APB2Periph_GPIOB
#define M12_GPIO_PIN         GPIO_Pin_3

//M22�ź� 
#define M22_GPIO_PORT        GPIOA
#define M22_GPIO_CLK         RCC_APB2Periph_GPIOA
#define M22_GPIO_PIN         GPIO_Pin_15
*/
#define ON  0
#define OFF 1

/* ֱ�Ӳ����Ĵ����ķ�������IO */
#define	digitalHi(p,i)		 {p->BSRR=i;}	 //���Ϊ�ߵ�ƽ		
#define digitalLo(p,i)		 {p->BRR=i;}	 //����͵�ƽ
#define digitalToggle(p,i) {p->ODR ^=i;} //�����ת״̬

void MY_GPIO_Config(void);
//void PFO_GPIO_Config(void);

#endif 
