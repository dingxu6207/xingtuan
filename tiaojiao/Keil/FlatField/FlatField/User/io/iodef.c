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
		//GPIO_InitTypeDef GPIO_InitStructureIPF;

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
		GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);//PB3,PB4,PA13,PA14,PA15全都可以做GPIO
	  //GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//PB3,PB4,PA15可做GPIO,PA13&14用于SWD调试	
	
		/*设置引脚模式为通用推挽输出*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
		/*设置引脚速率为50MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

		GPIO_InitStructure.GPIO_Pin = DIM_GPIO_PIN;	
		GPIO_Init(DIM_GPIO_PORT, &GPIO_InitStructure);
	 
		GPIO_ResetBits(DIM_GPIO_PORT, DIM_GPIO_PIN);
}
/**
  * @brief  配置嵌套向量中断控制器NVIC
  * @param  无
  * @retval 无
  */

/*********************************************END OF FILE**********************/
