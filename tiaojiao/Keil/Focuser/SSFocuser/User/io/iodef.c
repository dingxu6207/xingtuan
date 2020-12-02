#include "iodef.h"   

 /**
  * @brief  ��ʼ������LED��IO
  * @param  ��
  * @retval ��
  */
void MY_GPIO_Config(void)
{		
		/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
		GPIO_InitTypeDef GPIO_InitStructure,GPIO_InitStructureIPU,GPIO_InitStructureIPD;
		//GPIO_InitTypeDef GPIO_InitStructureIPF;

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
		GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);//PB3,PB4,PA13,PA14,PA15ȫ��������GPIO
	  //GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//PB3,PB4,PA15����GPIO,PA13&14����SWD����	
	
		/*��������ģʽΪͨ���������*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
		//GPIO_InitStructureIPF.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //��������
		GPIO_InitStructureIPU.GPIO_Mode = GPIO_Mode_IPU;  //��������
	  GPIO_InitStructureIPD.GPIO_Mode = GPIO_Mode_IPD;  //��������
		/*������������Ϊ50MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

		//GPIO_InitStructure.GPIO_Pin = PFO_GPIO_PIN;	
		//GPIO_Init(PFO_GPIO_PORT, &GPIO_InitStructure);
	
	  //GPIO_InitStructure.GPIO_Pin = TEMP_GPIO_PIN;
		//GPIO_Init(TEMP_GPIO_PORT, &GPIO_InitStructure);
		
		#ifdef Focuser_C_DRV8825
	
		GPIO_InitStructure.GPIO_Pin = BRST_GPIO_PIN;//������ʼ�������Բ�������
		GPIO_Init(BRST_GPIO_PORT, &GPIO_InitStructure);
		
		GPIO_InitStructure.GPIO_Pin = D1_GPIO_PIN;
		GPIO_Init(D1_GPIO_PORT, &GPIO_InitStructure);
		
		GPIO_InitStructure.GPIO_Pin = D2_GPIO_PIN;
		GPIO_Init(D2_GPIO_PORT, &GPIO_InitStructure);
		
		GPIO_InitStructure.GPIO_Pin = D3_GPIO_PIN;
		GPIO_Init(D3_GPIO_PORT, &GPIO_InitStructure);
		
		GPIO_InitStructure.GPIO_Pin = D4_GPIO_PIN;
		GPIO_Init(D4_GPIO_PORT, &GPIO_InitStructure);
		
		#endif
		
		#ifdef Focuser_C_TMC2208
		GPIO_InitStructure.GPIO_Pin = BRST_GPIO_PIN;//������ʼ�������Բ�������
		GPIO_Init(BRST_GPIO_PORT, &GPIO_InitStructure);
		#endif
		
		//Hander
		
		GPIO_InitStructureIPU.GPIO_Pin = HU_GPIO_PIN;	
		GPIO_Init(HU_GPIO_PORT, &GPIO_InitStructureIPU);
	
	  GPIO_InitStructureIPU.GPIO_Pin = HD_GPIO_PIN;
		GPIO_Init(HD_GPIO_PORT, &GPIO_InitStructureIPU);
		
		//AT24C02
		
		GPIO_InitStructure.GPIO_Pin = SCL_GPIO_PIN;
		GPIO_Init(SCL_GPIO_PORT, &GPIO_InitStructure);
		
		GPIO_InitStructure.GPIO_Pin = SDA_GPIO_PIN;
		GPIO_Init(SDA_GPIO_PORT, &GPIO_InitStructure);
		
		//Drv8825

		GPIO_InitStructure.GPIO_Pin = SLP_GPIO_PIN;	
		GPIO_Init(SLP_GPIO_PORT, &GPIO_InitStructure);	

		GPIO_InitStructureIPU.GPIO_Pin = FLT_GPIO_PIN;//�������룬��������͵�ƽ
		GPIO_Init(FLT_GPIO_PORT, &GPIO_InitStructureIPU);

		GPIO_InitStructure.GPIO_Pin = DIR_GPIO_PIN;
		GPIO_Init(DIR_GPIO_PORT, &GPIO_InitStructure);

		GPIO_InitStructure.GPIO_Pin = EN_GPIO_PIN;
		GPIO_Init(EN_GPIO_PORT, &GPIO_InitStructure);
			
		GPIO_InitStructure.GPIO_Pin = STEP_GPIO_PIN;
		GPIO_Init(STEP_GPIO_PORT, &GPIO_InitStructure);
		
		GPIO_InitStructure.GPIO_Pin = M0_GPIO_PIN;
		GPIO_Init(M0_GPIO_PORT, &GPIO_InitStructure);
		
		GPIO_InitStructure.GPIO_Pin = M1_GPIO_PIN;
		GPIO_Init(M1_GPIO_PORT, &GPIO_InitStructure);
		
		GPIO_InitStructure.GPIO_Pin = M2_GPIO_PIN;
		GPIO_Init(M2_GPIO_PORT, &GPIO_InitStructure);
		
		GPIO_InitStructure.GPIO_Pin = HOME_GPIO_PIN;
		GPIO_Init(HOME_GPIO_PORT, &GPIO_InitStructure);

		#ifdef Focuser_B_TMC2208
		
		GPIO_InitStructureIPU.GPIO_Pin = HU_GPIO_PIN;	
		GPIO_Init(HU_GPIO_PORT, &GPIO_InitStructureIPU);
	
	  GPIO_InitStructureIPU.GPIO_Pin = HD_GPIO_PIN;
		GPIO_Init(HD_GPIO_PORT, &GPIO_InitStructureIPU);
		
		GPIO_InitStructureIPU.GPIO_Pin = HR_GPIO_PIN;
		GPIO_Init(HR_GPIO_PORT, &GPIO_InitStructureIPU);
/*		
		GPIO_InitStructure.GPIO_Pin = MS2_GPIO_PIN;
		GPIO_Init(MS2_GPIO_PORT, &GPIO_InitStructure);
		
		GPIO_InitStructure.GPIO_Pin = MS1_GPIO_PIN;
		GPIO_Init(MS1_GPIO_PORT, &GPIO_InitStructure);
*/		
		GPIO_InitStructure.GPIO_Pin = PDN_GPIO_PIN;
		GPIO_Init(PDN_GPIO_PORT, &GPIO_InitStructure);
		
//		GPIO_InitStructure.GPIO_Pin = INDEX_GPIO_PIN;
//		GPIO_Init(INDEX_GPIO_PORT, &GPIO_InitStructure);
		
		GPIO_InitStructureIPD.GPIO_Pin = DIAG_GPIO_PIN;//�������룬��������ߵ�ƽ
		GPIO_Init(DIAG_GPIO_PORT, &GPIO_InitStructureIPD);

		#endif
		
		#ifdef Focuser_C_TMC2208
		
		GPIO_InitStructure.GPIO_Pin = MS2_GPIO_PIN;
		GPIO_Init(MS2_GPIO_PORT, &GPIO_InitStructure);
		
		GPIO_InitStructure.GPIO_Pin = MS1_GPIO_PIN;
		GPIO_Init(MS1_GPIO_PORT, &GPIO_InitStructure);
		
		GPIO_InitStructure.GPIO_Pin = PDN_GPIO_PIN;
		GPIO_Init(PDN_GPIO_PORT, &GPIO_InitStructure);
		
		GPIO_InitStructure.GPIO_Pin = INDEX_GPIO_PIN;
		GPIO_Init(INDEX_GPIO_PORT, &GPIO_InitStructure);
		
		GPIO_InitStructureIPD.GPIO_Pin = DIAG_GPIO_PIN;//�������룬��������ߵ�ƽ
		GPIO_Init(DIAG_GPIO_PORT, &GPIO_InitStructureIPD);

		#endif
		///////////////////////////////////////////////////		
		
		//Drv8825-2
		#ifdef Focuser_C_DRV8825
		
		GPIO_InitStructure.GPIO_Pin = SLP2_GPIO_PIN;	
		GPIO_Init(SLP2_GPIO_PORT, &GPIO_InitStructure);	
		
		GPIO_InitStructureIPU.GPIO_Pin = FLT2_GPIO_PIN;//�������룬��������͵�ƽ
		GPIO_Init(FLT2_GPIO_PORT, &GPIO_InitStructureIPU);

		GPIO_InitStructure.GPIO_Pin = DIR2_GPIO_PIN;
		GPIO_Init(DIR2_GPIO_PORT, &GPIO_InitStructure);

		GPIO_InitStructure.GPIO_Pin = EN2_GPIO_PIN;
		GPIO_Init(EN2_GPIO_PORT, &GPIO_InitStructure);
			
		GPIO_InitStructure.GPIO_Pin = STEP2_GPIO_PIN;
		GPIO_Init(STEP2_GPIO_PORT, &GPIO_InitStructure);
		
		//GPIO_InitStructure.GPIO_Pin = HOME2_GPIO_PIN;
		//GPIO_Init(HOME2_GPIO_PORT, &GPIO_InitStructure);

		GPIO_InitStructure.GPIO_Pin = M02_GPIO_PIN;
		GPIO_Init(M02_GPIO_PORT, &GPIO_InitStructure);
		
		GPIO_InitStructure.GPIO_Pin = M12_GPIO_PIN;
		GPIO_Init(M12_GPIO_PORT, &GPIO_InitStructure);
		
		GPIO_InitStructure.GPIO_Pin = M22_GPIO_PIN;
		GPIO_Init(M22_GPIO_PORT, &GPIO_InitStructure);
		
		#endif
		
		#ifdef Focuser_C_DRV8825
		
		GPIO_SetBits(BRST_GPIO_PORT, BRST_GPIO_PIN);
		GPIO_ResetBits(D1_GPIO_PORT, D1_GPIO_PIN);
		GPIO_ResetBits(D2_GPIO_PORT, D2_GPIO_PIN);
		GPIO_ResetBits(D3_GPIO_PORT, D3_GPIO_PIN);
		GPIO_ResetBits(D4_GPIO_PORT, D4_GPIO_PIN);
		#endif
		
	  GPIO_ResetBits(SLP_GPIO_PORT, SLP_GPIO_PIN);
		//GPIO_SetBits(FLT_GPIO_PORT, FLT_GPIO_PIN);
		GPIO_ResetBits(DIR_GPIO_PORT, DIR_GPIO_PIN);
		GPIO_ResetBits(EN_GPIO_PORT, EN_GPIO_PIN);
		GPIO_ResetBits(STEP_GPIO_PORT, STEP_GPIO_PIN);
		//GPIO_ResetBits(HOME_GPIO_PORT, HOME_GPIO_PIN);
		GPIO_ResetBits(M0_GPIO_PORT, M0_GPIO_PIN);
		GPIO_ResetBits(M1_GPIO_PORT, M1_GPIO_PIN);
		GPIO_ResetBits(M2_GPIO_PORT, M2_GPIO_PIN);
		
		#ifdef Focuser_B_TMC2208
		
		GPIO_ResetBits(PDN_GPIO_PORT, PDN_GPIO_PIN);
		//GPIO_ResetBits(INDEX_GPIO_PORT, INDEX_GPIO_PIN);
		//GPIO_ResetBits(DIAG_GPIO_PORT, DIAG_GPIO_PIN);
		//8ϸ��
		//GPIO_ResetBits(MS2_GPIO_PORT, MS2_GPIO_PIN);
		//GPIO_ResetBits(MS1_GPIO_PORT, MS1_GPIO_PIN);
		
		#endif
		
		#ifdef Focuser_C_TMC2208
		
		GPIO_SetBits(BRST_GPIO_PORT, BRST_GPIO_PIN);
		
		GPIO_ResetBits(PDN_GPIO_PORT, PDN_GPIO_PIN);
		GPIO_ResetBits(INDEX_GPIO_PORT, INDEX_GPIO_PIN);
		//GPIO_ResetBits(DIAG_GPIO_PORT, DIAG_GPIO_PIN);
		//8ϸ��
		GPIO_ResetBits(MS2_GPIO_PORT, MS2_GPIO_PIN);
		GPIO_ResetBits(MS1_GPIO_PORT, MS1_GPIO_PIN);
		
		#endif

		#ifdef Focuser_C_DRV8825
		GPIO_ResetBits(SLP2_GPIO_PORT, SLP2_GPIO_PIN);
		//GPIO_SetBits(FLT2_GPIO_PORT, FLT2_GPIO_PIN);
		GPIO_ResetBits(DIR2_GPIO_PORT, DIR2_GPIO_PIN);
		GPIO_ResetBits(EN2_GPIO_PORT, EN2_GPIO_PIN);
		GPIO_ResetBits(STEP2_GPIO_PORT, STEP2_GPIO_PIN);
		//GPIO_ResetBits(HOME2_GPIO_PORT, HOME2_GPIO_PIN);
		GPIO_ResetBits(M02_GPIO_PORT, M02_GPIO_PIN);
		GPIO_ResetBits(M12_GPIO_PORT, M12_GPIO_PIN);
		GPIO_ResetBits(M22_GPIO_PORT, M22_GPIO_PIN);	
		#endif
}
/**
  * @brief  ����Ƕ�������жϿ�����NVIC
  * @param  ��
  * @retval ��
  */

/*********************************************END OF FILE**********************/
