#include "iodef.h"   

 /**
  * @brief  初始化控制LED的IO
  * @param  无
  * @retval 无
  */
void MY_GPIO_Config(void)
{		
		/*定义一个GPIO_InitTypeDef类型的结构体*/
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
		GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);//PB3,PB4,PA13,PA14,PA15全都可以做GPIO
	  //GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//PB3,PB4,PA15可做GPIO,PA13&14用于SWD调试	
	
		/*设置引脚模式为通用推挽输出*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
		/*设置引脚速率为50MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

		/*调用库函数，初始化GPIO*/
		GPIO_InitStructure.GPIO_Pin = DCSW1_GPIO_PIN;	
		GPIO_Init(DCSW1_GPIO_PORT, &GPIO_InitStructure);	
		
		GPIO_InitStructure.GPIO_Pin = DCSW2_GPIO_PIN;
		GPIO_Init(DCSW2_GPIO_PORT, &GPIO_InitStructure);
		
		GPIO_InitStructure.GPIO_Pin = DCSW3_GPIO_PIN;
		GPIO_Init(DCSW3_GPIO_PORT, &GPIO_InitStructure);

		GPIO_InitStructure.GPIO_Pin = DCSW4_GPIO_PIN;
		GPIO_Init(DCSW4_GPIO_PORT, &GPIO_InitStructure);

		GPIO_InitStructure.GPIO_Pin = DCSW5_GPIO_PIN;
		GPIO_Init(DCSW5_GPIO_PORT, &GPIO_InitStructure);

		GPIO_InitStructure.GPIO_Pin = DCSW6_GPIO_PIN;
		GPIO_Init(DCSW6_GPIO_PORT, &GPIO_InitStructure);
		
		GPIO_InitStructure.GPIO_Pin = USBSW1_GPIO_PIN;
		GPIO_Init(USBSW1_GPIO_PORT, &GPIO_InitStructure);
		
		GPIO_InitStructure.GPIO_Pin = USBSW2_GPIO_PIN;
		GPIO_Init(USBSW2_GPIO_PORT, &GPIO_InitStructure);

		GPIO_InitStructure.GPIO_Pin = USBSW3_GPIO_PIN;
		GPIO_Init(USBSW3_GPIO_PORT, &GPIO_InitStructure);
		
		GPIO_InitStructure.GPIO_Pin = USBSW4_GPIO_PIN;
		GPIO_Init(USBSW4_GPIO_PORT, &GPIO_InitStructure);
		
		GPIO_InitStructure.GPIO_Pin = USBSW5_GPIO_PIN;
		GPIO_Init(USBSW5_GPIO_PORT, &GPIO_InitStructure);
		
		GPIO_InitStructure.GPIO_Pin = USBSW6_GPIO_PIN;
		GPIO_Init(USBSW6_GPIO_PORT, &GPIO_InitStructure);

		GPIO_InitStructure.GPIO_Pin = SCL_GPIO_PIN;
		GPIO_Init(SCL_GPIO_PORT, &GPIO_InitStructure);
		
		GPIO_InitStructure.GPIO_Pin = SDA_GPIO_PIN;; 
		GPIO_Init(SDA_GPIO_PORT, &GPIO_InitStructure);
/*
	  GPIO_ResetBits(DCSW1_GPIO_PORT, DCSW1_GPIO_PIN);
		GPIO_ResetBits(DCSW2_GPIO_PORT, DCSW2_GPIO_PIN);
		GPIO_ResetBits(DCSW3_GPIO_PORT, DCSW3_GPIO_PIN);
		GPIO_ResetBits(DCSW4_GPIO_PORT, DCSW4_GPIO_PIN);
		GPIO_ResetBits(DCSW5_GPIO_PORT, DCSW5_GPIO_PIN);
		GPIO_ResetBits(DCSW6_GPIO_PORT, DCSW6_GPIO_PIN);
		
		GPIO_ResetBits(USBSW1_GPIO_PORT, USBSW1_GPIO_PIN);
		GPIO_ResetBits(USBSW2_GPIO_PORT, USBSW2_GPIO_PIN);
		GPIO_ResetBits(USBSW3_GPIO_PORT, USBSW3_GPIO_PIN);
		GPIO_ResetBits(USBSW4_GPIO_PORT, USBSW4_GPIO_PIN);
		GPIO_ResetBits(USBSW5_GPIO_PORT, USBSW5_GPIO_PIN);
		GPIO_ResetBits(USBSW6_GPIO_PORT, USBSW6_GPIO_PIN);
*/	  
}
/*********************************************END OF FILE**********************/
