#include "iodef.h"   

 /**
  * @brief  初始化控制LED的IO
  * @param  无
  * @retval 无
  */
void MY_GPIO_Config(void)
{		
		/*定义一个GPIO_InitTypeDef类型的结构体*/
		GPIO_InitTypeDef GPIO_InitStructureOPP,GPIO_InitStructureIPU,GPIO_InitStructureIPD;
		//GPIO_InitTypeDef GPIO_InitStructureIPF;

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
		GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);//PB3,PB4,PA13,PA14,PA15全都可以做GPIO
	  //GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//PB3,PB4,PA15可做GPIO,PA13&14用于SWD调试	
	
		/*设置引脚模式为通用推挽输出*/
		GPIO_InitStructureOPP.GPIO_Mode = GPIO_Mode_Out_PP;   
		//GPIO_InitStructureIPF.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //悬空输入
		GPIO_InitStructureIPU.GPIO_Mode = GPIO_Mode_IPU;  //上拉输入
	  GPIO_InitStructureIPD.GPIO_Mode = GPIO_Mode_IPD;  //下拉输入
		/*设置引脚速率为50MHz */   
		GPIO_InitStructureOPP.GPIO_Speed = GPIO_Speed_50MHz; 

		//GPIO_InitStructure.GPIO_Pin = PFO_GPIO_PIN;	
		//GPIO_Init(PFO_GPIO_PORT, &GPIO_InitStructure);
	
	  //GPIO_InitStructure.GPIO_Pin = TEMP_GPIO_PIN;
		//GPIO_Init(TEMP_GPIO_PORT, &GPIO_InitStructure);

		GPIO_InitStructureOPP.GPIO_Pin = S1_GPIO_PIN;
		GPIO_Init(S1_GPIO_PORT, &GPIO_InitStructureOPP);
		
		GPIO_InitStructureOPP.GPIO_Pin = S2_GPIO_PIN;
		GPIO_Init(S2_GPIO_PORT, &GPIO_InitStructureOPP);
		
		GPIO_InitStructureOPP.GPIO_Pin = S3_GPIO_PIN;
		GPIO_Init(S3_GPIO_PORT, &GPIO_InitStructureOPP);
		
		GPIO_InitStructureOPP.GPIO_Pin = S4_GPIO_PIN;
		GPIO_Init(S4_GPIO_PORT, &GPIO_InitStructureOPP);
		
		GPIO_InitStructureOPP.GPIO_Pin = O1_GPIO_PIN;
		GPIO_Init(O1_GPIO_PORT, &GPIO_InitStructureOPP);
		
		GPIO_InitStructureOPP.GPIO_Pin = O2_GPIO_PIN;
		GPIO_Init(O2_GPIO_PORT, &GPIO_InitStructureOPP);
		
		GPIO_InitStructureOPP.GPIO_Pin = O3_GPIO_PIN;
		GPIO_Init(O3_GPIO_PORT, &GPIO_InitStructureOPP);
		
		GPIO_InitStructureOPP.GPIO_Pin = O4_GPIO_PIN;
		GPIO_Init(O4_GPIO_PORT, &GPIO_InitStructureOPP);
		
		GPIO_InitStructureOPP.GPIO_Pin = R1_GPIO_PIN;
		GPIO_Init(R1_GPIO_PORT, &GPIO_InitStructureOPP);
		
		GPIO_InitStructureOPP.GPIO_Pin = R2_GPIO_PIN;
		GPIO_Init(R2_GPIO_PORT, &GPIO_InitStructureOPP);
		
		GPIO_InitStructureOPP.GPIO_Pin = R3_GPIO_PIN;
		GPIO_Init(R3_GPIO_PORT, &GPIO_InitStructureOPP);
		
		GPIO_InitStructureOPP.GPIO_Pin = R4_GPIO_PIN;
		GPIO_Init(R4_GPIO_PORT, &GPIO_InitStructureOPP);
		
		GPIO_InitStructureOPP.GPIO_Pin = L1_GPIO_PIN;
		GPIO_Init(L1_GPIO_PORT, &GPIO_InitStructureOPP);
		
		GPIO_InitStructureOPP.GPIO_Pin = L2_GPIO_PIN;
		GPIO_Init(L2_GPIO_PORT, &GPIO_InitStructureOPP);
		
		//关闭全部继电器
		GPIO_SetBits(R1_GPIO_PORT, R1_GPIO_PIN);
		GPIO_SetBits(R2_GPIO_PORT, R2_GPIO_PIN);
		GPIO_SetBits(R3_GPIO_PORT, R3_GPIO_PIN);
		GPIO_SetBits(R4_GPIO_PORT, R4_GPIO_PIN);
		
		GPIO_SetBits(S1_GPIO_PORT, S1_GPIO_PIN);
		GPIO_SetBits(S2_GPIO_PORT, S2_GPIO_PIN);
		GPIO_SetBits(S3_GPIO_PORT, S3_GPIO_PIN);
		GPIO_SetBits(S4_GPIO_PORT, S4_GPIO_PIN);
}
/**
  * @brief  配置嵌套向量中断控制器NVIC
  * @param  无
  * @retval 无
  */

/*********************************************END OF FILE**********************/
