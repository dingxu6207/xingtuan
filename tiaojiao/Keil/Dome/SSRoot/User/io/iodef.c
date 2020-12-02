#include "iodef.h"   

 /**
  * @brief  ��ʼ������LED��IO
  * @param  ��
  * @retval ��
  */
void MY_GPIO_Config(void)
{		
		/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
		GPIO_InitTypeDef GPIO_InitStructureOPP,GPIO_InitStructureIPU,GPIO_InitStructureIPD;
		//GPIO_InitTypeDef GPIO_InitStructureIPF;

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
		GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);//PB3,PB4,PA13,PA14,PA15ȫ��������GPIO
	  //GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//PB3,PB4,PA15����GPIO,PA13&14����SWD����	
	
		/*��������ģʽΪͨ���������*/
		GPIO_InitStructureOPP.GPIO_Mode = GPIO_Mode_Out_PP;   
		//GPIO_InitStructureIPF.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //��������
		GPIO_InitStructureIPU.GPIO_Mode = GPIO_Mode_IPU;  //��������
	  GPIO_InitStructureIPD.GPIO_Mode = GPIO_Mode_IPD;  //��������
		/*������������Ϊ50MHz */   
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
		
		//�ر�ȫ���̵���
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
  * @brief  ����Ƕ�������жϿ�����NVIC
  * @param  ��
  * @retval ��
  */

/*********************************************END OF FILE**********************/
