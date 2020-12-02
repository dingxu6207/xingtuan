#include "stdbool.h"

/*********************************************************************************************************
** ��������: Timer0ISR
** ��������: �ж��쳣��������û�������Ҫ�Լ��ı����
����������
	BuzOnTime == 0;//�ر�
	BuzOffTime == 0;//����
	BuzOnTime<BuzOffTime;//ѭ�����죨��˸������OnTime/10ms��������OffTime/10msѭ����
   	BuzOnTime>BuzOffTime;//��һ�Σ�����һ�Σ�����OnTime/10ms��رա�
ʹ��ȫ�ֱ���uint8 BuzCount,BuzOnTime,BuzOffTime;
* �޸ģ�2008-7-5 ����� ������к���
* 		2008-8-25 ����� ����10ms��ʱ���������ж�
*			����ȫ�ֱ���	char RTCms;//10�������
*			�������жϺ���// ÿ���жϷ���

   	BuzOnTime<BuzOffTime;//ѭ�����죨��˸������OnTime/32�룬������OffTime/32��ѭ����
   	BuzOnTime>BuzOffTime;//��һ�Σ�����һ�Σ�����OnTime/32���رա�
ʹ��ȫ�ֱ���uint8 BuzCount,BuzOnTime,BuzOffTime;


**-------------------------------------------------------------------------------------------------------
** �޸���: �����
** �ա���: 2008��7��6��		   ���Լ���
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
//****************************************************************************
//�ڴ˼���Ҫʹ�õ�ȫ�ֱ���
//���ڵ���ʱʱ���ӳ���
//�ա���: 2008��8��24��

extern uint32 g_mObjTimer_sec;
extern uint32  BuzCnt;
extern uint8  BuzMode;  
extern uint8   sec_intr_counter; 
//*****************************************************************************
//����Ǭ�����ȫ�ֱ����;ֲ�����
extern uint32 g_nsysstatus;  //ϵͳ״̬
extern bool g_mAutoBackMainShow;//��һ��ʱ��û�������Զ�������������
extern int  g_mAutoBackMainShownum	;//��������Զ������Ȼ��������
//*****************************************************************************

char RTCms;//10�������ֵ��ÿ10ms���ж���1��ÿ���������ж�����

uint8 BuzCount,BuzOnTime,BuzOffTime;
void __irq Timer0ISR(void)
{
	PutKey(); // ɨ�����
	if(!BuzOnTime)	{
		IOSET1 = BEEP;
		BuzCount = 0;
		}
	else if(!BuzOffTime){
		IOCLR1 = BEEP;
		BuzCount = 0;
		}
	else if(BuzCount<=BuzOnTime) {
		IOCLR1 = BEEP;
		BuzCount++;
		}
	else if(BuzCount<=BuzOffTime){
		IOSET1 = BEEP;
		BuzCount++;
		}
	else if(BuzOnTime>=BuzOffTime){
		IOSET1 = BEEP;
		BuzCount = 0;
		BuzOnTime = 0;
		}
	else {
		BuzCount =  0;
		}
	RTCms++;
//****************************************************************************

	if(g_mObjTimer_sec>0)
	{
	    sec_intr_counter--;
		if(sec_intr_counter==0)
		{
			sec_intr_counter=100;
			g_mObjTimer_sec--;
			if(g_mObjTimer_sec==0)
			{
				//BuzCnt=2000000;
				//BuzMode=1;
				  BuzOnTime=5*32;
                  BuzOffTime=BuzOnTime-1;
          
			}
		}
	}

//****************************************************************************
    T0IR = 0x01;	    			            // ����жϱ�־
    VICVectAddr = 0x00;				            // ֪ͨVIC�жϴ������

}


// ÿ���жϷ���
void __irq RTC_ISR(void)
{
	ILR = 0x03;
	RTCms = 0;// 10ms��������
//	�����ã�ÿ�����1��	
//	BuzOnTime=20; // ����
//	BuzOffTime=20; // ����
//	�����ÿ�봦��ĳ���
	  
//	�����ÿ�봦��ĳ���  
	VICVectAddr = 0;
	//*****************************
	//����Ǭ����30�Զ��ش������� ,�� ������ʱ����
/*	if(g_mAutoBackMainShow)
	{ 
	  if(g_mAutoBackMainShownum>30)//30���Զ������Ȼ���
	  {	
	     g_nsysstatus=0;//SYS_MAINSHOW;
		 g_mAutoBackMainShownum=0; 
	  }
	  g_mAutoBackMainShownum++;
	
	}
	else
	{
	  g_mAutoBackMainShownum=0;
	}  */
	//*****************************
}

