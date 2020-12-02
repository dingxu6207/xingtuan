//****************************************************
//****************************************************
//*******************************************
//*******************************************
//**********ϵͳ�˵����ṹʵ�� **************
//**********���ߣ�����Ǭ           **********
//**********2008������������̨     **********
//**********lgq@ynao.ac.cn         **********
//*******************************************
//*******************************************
//****************************************************
//ϵͳͷ�ļ�
#include "stdlib.h"
#include "stdio.h"
#include "Sys.h"
#include "Menu.h"
#include "Sys.c"
#include "TelescopeControl.c"
#include "MoonPhase.c"
//#include "DispPole.c"
#include "Planet.c"	
#include "help.h"	
//****************************************************

////****************************************************
//ϵͳ���ݽṹ
union RA_INTSPD{
	int i;
	unsigned char ub[2	];
	}raspd;

uint8 g_mTelescopeConType;//��Զ���Ƿ����ӣ���true������false
uint8 loopi;//ѭ����

bool g_mKeyHit;//�Ƿ��м����£����ˣ���Ҫ�ӳ�һ�£�ֹͣ���κܿ�İ���

LOCATION  gLocation;
STARRAD   gStarRAD;
STARAZ    gStarAZ;

STARRAD   gTelRAD;
STARAZ    gTelAZ;
//****************************************************
//****************************************************
//****************************************************
//*************************************************************************************************************************
//ϵͳ�˵�ִ��
void  DoMenu() 
{
    //*****************************
	//��ȡϵͳʱ�� 
	GetSysTime();

	//*****************************

	//*****************************
	//�����ӳ�
	if(g_mKeyHit)
	{ 
	  MenuDelay(10);
	  DoKey();
	  if(g_mObjAlarm_open_reset==1)
	  {
	       g_mObjAlarm_open=0;
	 		//BuzCnt=5;
			//BuzMode=1;
			g_mObjAlarm_open_reset=0;//0���Ӳ��ڸ�λ״̬��1�����ڸ�λ״̬
		}
	  
	} 
	//*****************************

	 //*****************************
	//*************************************************************************************************
	//��ȡ����ֵ��������Ӧ����
    m_nkeyvalue=GetKeyValue(); 
   	if(!g_bkeyoperator)
	{
	    if(g_mKeyBeepOpen==1)
		{
		   FBeep1(1);
		 }
     	switch(m_nkeyvalue)
	 	{
	   	 	case KEY_NUM0:
			 		  
			  FKey0();
			
				g_mKeyHit=true;
		    	break;
			case KEY_NUM1:
			   if(((g_mGoto.m_nStartStop)&&(g_mTelStatus==2))||( !g_mGoto.m_nStartStop))
			   {
				FKey1();
				}
				g_mKeyHit=true;
	    		break;
			case KEY_NUM2:
			   if(((g_mGoto.m_nStartStop)&&(g_mTelStatus==2))||( !g_mGoto.m_nStartStop))
			   {
				 FKey2();
				}
				g_mKeyHit=true;
		 		break;
			case KEY_NUM3:
			   if(((g_mGoto.m_nStartStop)&&(g_mTelStatus==2))||( !g_mGoto.m_nStartStop))
			   {
		        	FKey3();
				}
				g_mKeyHit=true;
		    	break;
			case KEY_NUM4:
			  if(((g_mGoto.m_nStartStop)&&(g_mTelStatus==2))||( !g_mGoto.m_nStartStop))
			   {
		    	FKey4();
				}
				g_mKeyHit=true;
	    		break;
			case KEY_NUM5:
			    if(((g_mGoto.m_nStartStop)&&(g_mTelStatus==2))||( !g_mGoto.m_nStartStop))
			   {
		    	FKey5();
				}
	            g_mKeyHit=true;
		 		break;
			case KEY_NUM6:
			   if(((g_mGoto.m_nStartStop)&&(g_mTelStatus==2))||( !g_mGoto.m_nStartStop))
			   {
		    	FKey6();
				}
				g_mKeyHit=true;
		    	break;
			case KEY_NUM7:
		    	FKey7();
				g_mKeyHit=true;
	    		break;
			case KEY_NUM8:
			   if(((g_mGoto.m_nStartStop)&&(g_mTelStatus==2))||( !g_mGoto.m_nStartStop))
			   {
				  FKey8();
				}
				g_mKeyHit=true;
		 		break;
        	case KEY_NUM9:
			    if(((g_mGoto.m_nStartStop)&&(g_mTelStatus==2))||( !g_mGoto.m_nStartStop))
			   {
				  FKey9();
				}
				g_mKeyHit=true;
		    	break;
			case KEY_XH:
		   	 	FKeyXH();
				g_mKeyHit=true;
	    		break;
			case KEY_WH:
		    	FKeyWH();
				g_mKeyHit=true;
		 		break;
			case KEY_MENU:
		    	FKeyMenu( );
				g_mKeyHit=true;
		    	break;
			case KEY_BACK:
		    	FKeyBack();
				g_mKeyHit=true;
	    		break;
			case KEY_UP:
			   
			   if(((g_mGoto.m_nStartStop)&&(g_mTelStatus==2))||( !g_mGoto.m_nStartStop))
			   {
		    	 FKeyUp();
				}
				g_mKeyHit=true;
		 		break;
			case KEY_DOWN:
			  // FBeep(1);
			   if(((g_mGoto.m_nStartStop)&&(g_mTelStatus==2))||( !g_mGoto.m_nStartStop))
			   {
		    	FKeyDown();
				}
				g_mKeyHit=true;
		    	break;
			case KEY_LEFT:
			
			   if(((g_mGoto.m_nStartStop)&&(g_mTelStatus==2))||( !g_mGoto.m_nStartStop))
			   {
		    	FKeyLeft();
				}
				g_mKeyHit=true;
	    		break;
			case KEY_RIGHT:
			   if(((g_mGoto.m_nStartStop)&&(g_mTelStatus==2))||( !g_mGoto.m_nStartStop))
			   {
		   	 	  FKeyRight();
				}
				g_mKeyHit=true;
		 		break;
			case KEY_ENTER:
		    	FKeyEnter();
				g_mKeyHit=true;
		 		break;	
			case KEY_LEFTUP:
			   //FBeep(2);
			   if(((g_mGoto.m_nStartStop)&&(g_mTelStatus==2))||( !g_mGoto.m_nStartStop))
			   {
			     FKeyLeftUp();
				}
				g_mKeyHit=true;
		        break;
			case KEY_LEFTDOWN:
			   if(((g_mGoto.m_nStartStop)&&(g_mTelStatus==2))||( !g_mGoto.m_nStartStop))
			   {
		        FKeyLeftDown();
				}
				g_mKeyHit=true;
		        break;
			case KEY_RIGHTDOWN:
			   if(((g_mGoto.m_nStartStop)&&(g_mTelStatus==2))||( !g_mGoto.m_nStartStop))
			   {
			     FKeyRightDown();
				}
				g_mKeyHit=true;
		        break;
			case KEY_RIGHTUP:
			   if(((g_mGoto.m_nStartStop)&&(g_mTelStatus==2))||( !g_mGoto.m_nStartStop))
			   {
			    FKeyRightUp();
				}
				g_mKeyHit=true;
		        break;	
		    case KEY_TORCH:
			    FKeyTorch();
				g_mKeyHit=true;
				break;					
			default :
			    
				break;	
		}
	  	 g_bkeyoperator=true;
	}
	else							 	
	{	  
	       g_mKeyHit=false;  
		   g_mAposModify=0;
	       g_mZposModify=0;
		   g_mHandSpeedAzi=0; //����Զ������ʱ���ֶ���λ�ٶ�
           g_mHandSpeedAlt=0;  //����Զ������ʱ���ֶ��߶��ٶ�
		   //FBeep(1);
 	}
	//*************************************************************************************************
	
	//*********************************************************
	//��ʾ�Ƿ��Զ��ص���������ҳ��
	if((g_nsysstatus!=SYS_MAINSHOW)&&(g_nsysstatus!=SYS_SUB1SUB2STAR_ALIGN)&&(g_nsysstatus!=SYS_SUB1SUB11RA_GEAR_ERROR_ALIGN)&&(g_nsysstatus!=SYS_SUB1SUB12DEC_GEAR_ERROR_ALIGN)&&(g_nsysstatus!=SYS_SUB1SUB11RA_GEAR_ERROR_BEGIN)&&(g_nsysstatus!=SYS_SUB1SUB12DEC_GEAR_ERROR_BEGIN)&&(!g_mKeyHit))
	{
	   if(!g_mAutoBackMainShow)
	   {
	      g_mAutoBackMainShow=true; 
	      g_mAutoBackMainShownum=0;
		 } 	     
	}
	else
	{
	   g_mAutoBackMainShow=false;  
	}
	//*********************************************************

  if(g_mSysInitGuide==1)
	{
	   if(g_mgetimefirst)
	   {
	    GetSysTime();
	   	sprintf(g_sysmenu4100dateEn,"%04d-%02d-%02d",g_mDate_year,g_mDate_month,g_mDate_day);
      	sprintf(g_sysmenu4100timeEn,"%02d:%02d:%02d",g_mTime_hour,g_mTime_minute,g_mTime_second);
      	sprintf(g_sysmenu4100date,"%04d-%02d-%02d",g_mDate_year,g_mDate_month,g_mDate_day);
      	sprintf(g_sysmenu4100time,"%02d:%02d:%02d",g_mTime_hour,g_mTime_minute,g_mTime_second);
   		g_mgetimefirst=0;
		}
    }

//**********************************
//�˵���ʾ
  if(g_mhelpshow==0)
  {
      FMenuShow();
   }
   else
   {
      FHelpShow();
   }
//**********************************


//*******************************************
//��ʱ����
	if(g_mObjAlarm_open==1)
	{
	 	//��ȡrtcʱ�䲢����������ʱ����бȽ�
	 	if((g_mObjAlarm_shi==g_mTime_hour)&&
			(g_mObjAlarm_fen==g_mTime_minute)&&
			(g_mObjAlarm_miao==g_mTime_second))
		{
		    //g_mObjAlarm_open=0;
	 		//BuzCnt=5;
			//BuzMode=1;
			g_mObjAlarm_open_reset=1;//0���Ӳ��ڸ�λ״̬��1�����ڸ�λ״̬
			//FBeep(10);
		}
	}

	if(g_mObjAlarm_open_reset==1)
	{
	   	FBeep(10);
	}

	
//BuzCnt>0��������
//*******************************************

}
//ϵͳ�˵����
//*************************************************************************************************************************

//****************************************************
//ϵͳ�˵��Ӻ���
///ϵͳ���Դ���
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void FSelMenuLanguage()
{	switch(g_mMenuLangauge)
	{ 
//		case CHANESE://����
//		//ϵͳ�˵�����ѡ��:
//			//***************************************************
//			//һ���˵�
//			     g_sysmenu1000= g_sysmenu1000Cn;
//			     g_sysmenu2000= g_sysmenu2000Cn;
//			     g_sysmenu3000= g_sysmenu3000Cn;
//			     g_sysmenu4000= g_sysmenu4000Cn;
//			//***************************************************
//			//�����˵�
//			//��Զ��У���Ӳ˵�
//			
//			     g_sysmenu1100=g_sysmenu1100Cn;
//			     g_sysmenu1200=g_sysmenu1200Cn;
//			     g_sysmenu1300=g_sysmenu1300Cn;
//			     g_sysmenu1400=g_sysmenu1400Cn;
//			     g_sysmenu1500=g_sysmenu1500Cn;
//			     g_sysmenu1600=g_sysmenu1600Cn;
//			     g_sysmenu1700=g_sysmenu1700Cn;
//			     g_sysmenu1800=g_sysmenu1800Cn;
//			     g_sysmenu1900=g_sysmenu1900Cn;
//			     g_sysmenu1110=g_sysmenu1110Cn;
//			     g_sysmenu1120=g_sysmenu1120Cn;
//			
//			//Ŀ�굼���Ӳ˵�
//			     g_sysmenu2100=g_sysmenu2100Cn;
//			     g_sysmenu2200=g_sysmenu2200Cn;
//			     g_sysmenu2300=g_sysmenu2300Cn;
//			     g_sysmenu2400=g_sysmenu2400Cn;
//			     g_sysmenu2500=g_sysmenu2500Cn;
//			     g_sysmenu2600=g_sysmenu2600Cn;
//			     g_sysmenu2700=g_sysmenu2700Cn;
//			     g_sysmenu2800=g_sysmenu2800Cn;
//			     g_sysmenu2900=g_sysmenu2900Cn;
//			     g_sysmenu2110=g_sysmenu2110Cn;
//				 g_sysmenu2120=g_sysmenu2120Cn;
//				 g_sysmenu2130=g_sysmenu2130Cn;
//			
//			//���������Ӳ˵�
//			     g_sysmenu3100=g_sysmenu3100Cn;
//			     g_sysmenu3200=g_sysmenu3200Cn;
//			     g_sysmenu3300=g_sysmenu3300Cn;
//			     g_sysmenu3400=g_sysmenu3400Cn;
//			     g_sysmenu3500=g_sysmenu3500Cn;
//			     g_sysmenu3600=g_sysmenu3600Cn;
//			     g_sysmenu3700=g_sysmenu3700Cn;
//			     g_sysmenu3800=g_sysmenu3800Cn;
//			     g_sysmenu3900=g_sysmenu3900Cn;
//			     g_sysmenu3110=g_sysmenu3110Cn;
//			//���������Ӳ˵�
//			     g_sysmenu4100=g_sysmenu4100Cn;
//			     g_sysmenu4200=g_sysmenu4200Cn;
//			     g_sysmenu4300=g_sysmenu4300Cn;
//			     g_sysmenu4400=g_sysmenu4400Cn;
//			     g_sysmenu4500=g_sysmenu4500Cn ;
//			     g_sysmenu4600=g_sysmenu4600Cn;
//			     g_sysmenu4700=g_sysmenu4700Cn;
//			     g_sysmenu4800=g_sysmenu4800Cn;
//			     g_sysmenu4900=g_sysmenu4900Cn;
//			     g_sysmenu4110=g_sysmenu4110Cn;
////			     g_sysmenu4120=g_sysmenu4120Cn;
//			//***************************************************
//			
//			//***************************************************
//			//�����˵�
//			//�ڶ���ڶ�����
////			     g_sysmenu2201=g_sysmenu2201Cn;
////			     g_sysmenu2202=g_sysmenu2202Cn;
////			     g_sysmenu2203=g_sysmenu2203Cn;
////			     g_sysmenu2204=g_sysmenu2204Cn;
////			     g_sysmenu2205=g_sysmenu2205Cn;
////			     g_sysmenu2206=g_sysmenu2206Cn;
////			     g_sysmenu2207=g_sysmenu2207Cn;
////			     g_sysmenu2208=g_sysmenu2208Cn;
////			     g_sysmenu2209=g_sysmenu2209Cn;
////			     g_sysmenu22010=g_sysmenu22010Cn;
////			     g_sysmenu22011=g_sysmenu22011Cn;
////			
////			//�ڶ����������
////			     g_sysmenu2301=g_sysmenu2301Cn;
////			     g_sysmenu2302=g_sysmenu2302Cn;
////			     g_sysmenu2303=g_sysmenu2303Cn;
////			     g_sysmenu2304=g_sysmenu2304Cn;
////			     g_sysmenu2305=g_sysmenu2305Cn;
////			     g_sysmenu2306=g_sysmenu2306Cn;
////			     g_sysmenu2307=g_sysmenu2307Cn;
////			     g_sysmenu2308=g_sysmenu2308Cn;
////			
//			//�ڶ����������
////			     g_sysmenu2501=g_sysmenu2501Cn;
////			     g_sysmenu2502=g_sysmenu2502Cn;
////			     g_sysmenu2503=g_sysmenu2503Cn;
//			
//			//�ڶ���ڰ�����
//			     g_sysmenu2801=g_sysmenu2801Cn;
//			     g_sysmenu2802=g_sysmenu2802Cn;
//			     g_sysmenu2803=g_sysmenu2803Cn;
//			     g_sysmenu2804=g_sysmenu2804Cn;
//			
//			//�ڶ����ʮһ����
//			     g_sysmenu21101=g_sysmenu21101Cn;
//			     g_sysmenu21102=g_sysmenu21102Cn;
//			     g_sysmenu21103=g_sysmenu21103Cn;
//			//**********************
//			//�������������
//			     g_sysmenu3601=g_sysmenu3601Cn;
//			     g_sysmenu3602=g_sysmenu3602Cn;
//			
//			//������ڰ�����
//			     g_sysmenu3801=g_sysmenu3801Cn;
//			     g_sysmenu3802=g_sysmenu3802Cn;
//			
//			//***********************
//			//�������������
//			     g_sysmenu4301=g_sysmenu4301Cn;
//			     g_sysmenu4302=g_sysmenu4302Cn;
//			
//			     g_sysmenu43021=g_sysmenu43021Cn;
//			     g_sysmenu43022=g_sysmenu43022Cn;
//			     g_sysmenu43023=g_sysmenu43023Cn;
//			     g_sysmenu43024=g_sysmenu43024Cn;
//			
//			
//			//�������������
//			     g_sysmenu4701=g_sysmenu4701Cn;
//			     g_sysmenu4702=g_sysmenu4702Cn;
//			     g_sysmenu4703=g_sysmenu4703Cn;
//			     g_sysmenu4704=g_sysmenu4704Cn;
//			
//			//������ڰ�����
//			     g_sysmenu4801=g_sysmenu4801Cn;
//			     g_sysmenu4802=g_sysmenu4802Cn;
//			     g_sysmenu4803=g_sysmenu4803Cn;
//			     g_sysmenu4804=g_sysmenu4804Cn;
//			//��ײ�ʵ�֣�
//			//��Զ���Զ�У׼����ʾ:
//			//��Զ��һ����������У׼��ʾ��
//
//			 g_sysmenu1101=g_sysalign1101Cn; 
// 		 	 g_sysmenu1102=g_sysalign1102Cn; 
//			 g_sysmenu1103=g_sysalign1103Cn;
//			 g_sysmenu1104=g_sysalign1104Cn; 
//			 g_sysmenu1105=g_sysalign1105Cn; 
//			 g_sysmenu1106=g_sysalign1106Cn; 
//			 g_sysmenu1107=g_sysalign1107Cn; 
//			 g_sysmenu1108=g_sysalign1108Cn; 
//			 g_sysmenu1109=g_sysalign1109Cn;
//			 //��Զ���ྭ��λ�ز�ⶨ
//			 g_sysmenu11101=g_sysbacklash11101Cn;
//			 g_sysmenu11102=g_sysbacklash11102Cn;
//			 g_sysmenu11103=g_sysbacklash11103Cn;
//			 g_sysmenu11104=g_sysbacklash11104Cn;
//			 g_sysmenu11105=g_sysbacklash11105Cn;
//			 g_sysmenu11205=g_sysbacklash11205Cn;
//			 g_sysmenu11206=g_sysbacklash11206Cn;
//
//			 g_sysmenu11106=g_sysbacklash11106Cn;
//			 g_sysmenu11107=g_sysbacklash11107Cn;
//			 g_sysmenu11108=g_sysbacklash11108Cn;
//			 g_sysmenu11109=g_sysbacklash11109Cn;
//			 g_sysmenu111010=g_sysbacklash111010Cn;
//			 g_sysmenu111011=g_sysbacklash111011Cn;
//			 g_sysmenu111012=g_sysbacklash111012Cn;
//			 g_sysmenu111013=g_sysbacklash111013Cn;
//			 g_sysmenu111014=g_sysbacklash111014Cn;
//			 g_sysmenu111015=g_sysbacklash111015Cn;
//			 g_sysmenu111016=g_sysbacklash111016Cn;
//			 g_sysmenu111017=g_sysbacklash111017Cn;
//			 g_sysmenu111018=g_sysbacklash111018Cn;
//			 g_sysmenu111019=g_sysbacklash111019Cn;
//			 g_sysmenu111020=g_sysbacklash111020Cn;
//
//
//			 //û����Զ����ʾ
//			 g_sysnotel1=g_sysNoTelescopeCn1;
//			 g_sysnotel2=g_sysNoTelescopeCn2;
//			 
//			//***************************************************
			//***************************************************
//		break;
		case ENGLISH://Ӣ��
				//ϵͳ�˵�����ѡ��:
			//***************************************************
			//һ���˵�
			     g_sysmenu1000= g_sysmenu1000En;
			     g_sysmenu2000= g_sysmenu2000En;
			     g_sysmenu3000= g_sysmenu3000En;
			     g_sysmenu4000= g_sysmenu4000En;
			//***************************************************
			//�����˵�
			//��Զ��У���Ӳ˵�
			
			     g_sysmenu1100=g_sysmenu1100En;
			     g_sysmenu1200=g_sysmenu1200En;
			     g_sysmenu1300=g_sysmenu1300En;
			     g_sysmenu1400=g_sysmenu1400En;
			     g_sysmenu1500=g_sysmenu1500En;
			     g_sysmenu1600=g_sysmenu1600En;
			     g_sysmenu1700=g_sysmenu1700En;
			     g_sysmenu1800="                     ";
			     //g_sysmenu1900=g_sysmenu1900En;
			     //g_sysmenu1110=g_sysmenu1110En;
			     //g_sysmenu1120=g_sysmenu1120En;
			
			//Ŀ�굼���Ӳ˵�
			     g_sysmenu2100=g_sysmenu2100En;
			     g_sysmenu2200=g_sysmenu2200En;
			     g_sysmenu2300=g_sysmenu2300En;
			     g_sysmenu2400=g_sysmenu2400En;
			     g_sysmenu2500=g_sysmenu2500En;
			     g_sysmenu2600=g_sysmenu2600En;
			     g_sysmenu2700=g_sysmenu2700En;
			     g_sysmenu2800=g_sysmenu2800En;
			     g_sysmenu2900=g_sysmenu2900En;
			     g_sysmenu2110=g_sysmenu2110En;
				 g_sysmenu2120=g_sysmenu2120En;
				 g_sysmenu2130=g_sysmenu2130En;
			
			//���������Ӳ˵�
			     g_sysmenu3100=g_sysmenu3100En;
			     g_sysmenu3200=g_sysmenu3200En;
			     g_sysmenu3300=g_sysmenu3300En;
			     g_sysmenu3400=g_sysmenu3400En;
			     g_sysmenu3500=g_sysmenu3500En;
			     g_sysmenu3600=g_sysmenu3600En;
			     g_sysmenu3700=g_sysmenu3700En;
			     g_sysmenu3800=g_sysmenu3800En;
			     g_sysmenu3900=g_sysmenu3900En;
//			     g_sysmenu3110=g_sysmenu3110En;
			//���������Ӳ˵�
			     g_sysmenu4100=g_sysmenu4100En;
			     g_sysmenu4200=g_sysmenu4200En;
			     g_sysmenu4300=g_sysmenu4300En;
			     g_sysmenu4400=g_sysmenu4400En;
			     g_sysmenu4500=g_sysmenu4500En ;
			     g_sysmenu4600=g_sysmenu4600En;
			     g_sysmenu4700=g_sysmenu4700En;
			     g_sysmenu4800=g_sysmenu4800En;
			     g_sysmenu4900=g_sysmenu4900En;
//			     g_sysmenu4110=g_sysmenu4110En;
//			     g_sysmenu4120=g_sysmenu4120En;
			//***************************************************
			
			//***************************************************
			//�����˵�
			//�ڶ���ڶ�����
//			     g_sysmenu2201=g_sysmenu2201En;
//			     g_sysmenu2202=g_sysmenu2202En;
//			     g_sysmenu2203=g_sysmenu2203En;
//			     g_sysmenu2204=g_sysmenu2204En;
//			     g_sysmenu2205=g_sysmenu2205En;
//			     g_sysmenu2206=g_sysmenu2206En;
//			     g_sysmenu2207=g_sysmenu2207En;
//			     g_sysmenu2208=g_sysmenu2208En;
//			     g_sysmenu2209=g_sysmenu2209En;
//			     g_sysmenu22010=g_sysmenu22010En;
//			     g_sysmenu22011=g_sysmenu22011En;
			
			//�ڶ����������
//			     g_sysmenu2301=g_sysmenu2301En;
//			     g_sysmenu2302=g_sysmenu2302En;
//			     g_sysmenu2303=g_sysmenu2303En;
//			     g_sysmenu2304=g_sysmenu2304En;
//			     g_sysmenu2305=g_sysmenu2305En;
//			     g_sysmenu2306=g_sysmenu2306En;
//			     g_sysmenu2307=g_sysmenu2307En;
//			     g_sysmenu2308=g_sysmenu2308En;
//			
			//�ڶ����������
			     g_sysmenu2501=g_sysmenu2501En;
			     g_sysmenu2502=g_sysmenu2502En;
			     g_sysmenu2503=g_sysmenu2503En;
			
			//�ڶ���ڰ�����
			     g_sysmenu2801=g_sysmenu2801En;
			     g_sysmenu2802=g_sysmenu2802En;
			     g_sysmenu2803=g_sysmenu2803En;
			     g_sysmenu2804=g_sysmenu2804En;
			
			//�ڶ����ʮһ����
			     g_sysmenu21101=g_sysmenu21101En;
			     g_sysmenu21102=g_sysmenu21102En;
			     g_sysmenu21103=g_sysmenu21103En;
			//**********************
			//�������������
			     g_sysmenu3601=g_sysmenu3601En;
			     g_sysmenu3602=g_sysmenu3602En;
			
			//������ڰ�����
			     g_sysmenu3801=g_sysmenu3801En;
			     g_sysmenu3802=g_sysmenu3802En;
			
			//***********************
			//�������������
			     g_sysmenu4301=g_sysmenu4301En;
			     g_sysmenu4302=g_sysmenu4302En;
			
			     g_sysmenu43021=g_sysmenu43021En;
			     g_sysmenu43022=g_sysmenu43022En;
			     g_sysmenu43023=g_sysmenu43023En;
			     g_sysmenu43024=g_sysmenu43024En;
			
			
			//�������������
			     g_sysmenu4701=g_sysmenu4701En;
			     g_sysmenu4702=g_sysmenu4702En;
			     g_sysmenu4703=g_sysmenu4703En;
			     g_sysmenu4704=g_sysmenu4704En;
			
			//������ڰ�����
			     g_sysmenu4801=g_sysmenu4801En;
			     g_sysmenu4802=g_sysmenu4802En;
			     g_sysmenu4803=g_sysmenu4803En;
			     g_sysmenu4804=g_sysmenu4804En;
		  //��ײ�ʵ�֣�
			//��Զ���Զ�У׼����ʾ:
			//��Զ��һ����������У׼��ʾ��

			 g_sysmenu1101=g_sysalign1101En; 
 		 	 g_sysmenu1102=g_sysalign1102En; 
			 g_sysmenu1103=g_sysalign1103En;
			 g_sysmenu1104=g_sysalign1104En; 
			 g_sysmenu1105=g_sysalign1105En; 
			 g_sysmenu1106=g_sysalign1106En; 
			 g_sysmenu1107=g_sysalign1107En; 
			 g_sysmenu1108=g_sysalign1108En; 
			 g_sysmenu1109=g_sysalign1109En;
			 			 //��Զ���ྭ��λ�ز�ⶨ
			 g_sysmenu11101=g_sysbacklash11101En;
			 g_sysmenu11102=g_sysbacklash11102En;
			 g_sysmenu11103=g_sysbacklash11103En;
			 g_sysmenu11104=g_sysbacklash11104En;
			 g_sysmenu11105=g_sysbacklash11105En;

			 g_sysmenu11106=g_sysbacklash11106En;
			 g_sysmenu11107=g_sysbacklash11107En;
			 g_sysmenu11108=g_sysbacklash11108En;
			 g_sysmenu11109=g_sysbacklash11109En;
			 g_sysmenu111010=g_sysbacklash111010En;
			 g_sysmenu111011=g_sysbacklash111011En;
			 g_sysmenu111012=g_sysbacklash111012En;
			 g_sysmenu111013=g_sysbacklash111013En;
			 g_sysmenu111014=g_sysbacklash111014En;
			 g_sysmenu111015=g_sysbacklash111015En;
			 g_sysmenu111016=g_sysbacklash111016En;
			 g_sysmenu111017=g_sysbacklash111017En;
			 g_sysmenu111018=g_sysbacklash111018En;
			 g_sysmenu111019=g_sysbacklash111019En;
			//g_sysmenu111020=g_sysbacklash111020En;

			 //û����Զ����ʾ
			 g_sysnotel1=g_sysNoTelescopeEn1;
			 g_sysnotel2=g_sysNoTelescopeEn2;
			 g_sysnotel3=g_sysNoTelescopeEn3;
			
			//***************************************************
			//***************************************************
		break;
		case GERMAN://����
		//ϵͳ�˵�����ѡ��:
			//***************************************************
			//һ���˵�
			     g_sysmenu1000= g_sysmenu1000Ger;
			     g_sysmenu2000= g_sysmenu2000Ger;
			     g_sysmenu3000= g_sysmenu3000Ger;
			     g_sysmenu4000= g_sysmenu4000Ger;
			//***************************************************  					
			//�����˵�
			//��Զ��У���Ӳ˵�			
			     g_sysmenu1100=g_sysmenu1100Ger;
			     g_sysmenu1200=g_sysmenu1200Ger;
			     g_sysmenu1300=g_sysmenu1300Ger;
			     g_sysmenu1400=g_sysmenu1400Ger;
			     g_sysmenu1500=g_sysmenu1500Ger;
			     g_sysmenu1600=g_sysmenu1600Ger;
			     g_sysmenu1700=g_sysmenu1700Ger;
//			     g_sysmenu1800=g_sysmenu1800Ger;
//			     g_sysmenu1900=g_sysmenu1900Ger;
//			     g_sysmenu1110=g_sysmenu1110Ger;
//			     g_sysmenu1120=g_sysmenu1120Ger;
			
			//Ŀ�굼���Ӳ˵�
			     g_sysmenu2100=g_sysmenu2100Ger;
			     g_sysmenu2200=g_sysmenu2200Ger;
			     g_sysmenu2300=g_sysmenu2300Ger;
			     g_sysmenu2400=g_sysmenu2400Ger;
			     g_sysmenu2500=g_sysmenu2500Ger;
			     g_sysmenu2600=g_sysmenu2600Ger;
			     g_sysmenu2700=g_sysmenu2700Ger;
			     g_sysmenu2800=g_sysmenu2800Ger;
			     g_sysmenu2900=g_sysmenu2900Ger;
			     g_sysmenu2110=g_sysmenu2110Ger;
				 g_sysmenu2120=g_sysmenu2120Ger;
				 g_sysmenu2130=g_sysmenu2130Ger;
			
			//���������Ӳ˵�
			     g_sysmenu3100=g_sysmenu3100Ger;
			     g_sysmenu3200=g_sysmenu3200Ger;
			     g_sysmenu3300=g_sysmenu3300Ger;
			     g_sysmenu3400=g_sysmenu3400Ger;
			     g_sysmenu3500=g_sysmenu3500Ger;
			     g_sysmenu3600=g_sysmenu3600Ger;
			     g_sysmenu3700=g_sysmenu3700Ger;
			     g_sysmenu3800=g_sysmenu3800Ger;
			     g_sysmenu3900=g_sysmenu3900Ger;
//			     g_sysmenu3110=g_sysmenu3110Ger;
			//���������Ӳ˵�
			     g_sysmenu4100=g_sysmenu4100Ger;
			     g_sysmenu4200=g_sysmenu4200Ger;
			     g_sysmenu4300=g_sysmenu4300Ger;
			     g_sysmenu4400=g_sysmenu4400Ger;
			     g_sysmenu4500=g_sysmenu4500Ger ;
			     g_sysmenu4600=g_sysmenu4600Ger;
			     g_sysmenu4700=g_sysmenu4700Ger;
			     g_sysmenu4800=g_sysmenu4800Ger;
			     g_sysmenu4900=g_sysmenu4900Ger;
//			     g_sysmenu4110=g_sysmenu4110Ger;
//			     g_sysmenu4120=g_sysmenu4120Ger;
			//***************************************************
						
			//***************************************************
			//�����˵�
			//�ڶ���ڶ�����
//			     g_sysmenu2201=g_sysmenu2201En;
//			     g_sysmenu2202=g_sysmenu2202En;
//			     g_sysmenu2203=g_sysmenu2203En;
//			     g_sysmenu2204=g_sysmenu2204En;
//			     g_sysmenu2205=g_sysmenu2205En;
//			     g_sysmenu2206=g_sysmenu2206En;
//			     g_sysmenu2207=g_sysmenu2207En;
//			     g_sysmenu2208=g_sysmenu2208En;
//			     g_sysmenu2209=g_sysmenu2209En;
//			     g_sysmenu22010=g_sysmenu22010En;
//			     g_sysmenu22011=g_sysmenu22011En;
			
			//�ڶ����������
//			     g_sysmenu2301=g_sysmenu2301En;
//			     g_sysmenu2302=g_sysmenu2302En;
//			     g_sysmenu2303=g_sysmenu2303En;
//			     g_sysmenu2304=g_sysmenu2304En;
//			     g_sysmenu2305=g_sysmenu2305En;
//			     g_sysmenu2306=g_sysmenu2306En;
//			     g_sysmenu2307=g_sysmenu2307En;
//			     g_sysmenu2308=g_sysmenu2308En;
//			
			//�ڶ����������
			     g_sysmenu2501=g_sysmenu2501En;
			     g_sysmenu2502=g_sysmenu2502En;
			     g_sysmenu2503=g_sysmenu2503En;
			
			//�ڶ���ڰ�����
			     g_sysmenu2801=g_sysmenu2801En;
			     g_sysmenu2802=g_sysmenu2802En;
			     g_sysmenu2803=g_sysmenu2803En;
			     g_sysmenu2804=g_sysmenu2804En;
			
			//�ڶ����ʮһ����
			     g_sysmenu21101=g_sysmenu21101En;
			     g_sysmenu21102=g_sysmenu21102En;
			     g_sysmenu21103=g_sysmenu21103En;
			//**********************
			//�������������
			     g_sysmenu3601=g_sysmenu3601En;
			     g_sysmenu3602=g_sysmenu3602En;
			
			//������ڰ�����
			     g_sysmenu3801=g_sysmenu3801En;
			     g_sysmenu3802=g_sysmenu3802En;
			
			//***********************
			//�������������
			     g_sysmenu4301=g_sysmenu4301En;
			     g_sysmenu4302=g_sysmenu4302En;
			
			     g_sysmenu43021=g_sysmenu43021En;
			     g_sysmenu43022=g_sysmenu43022En;
			     g_sysmenu43023=g_sysmenu43023En;
			     g_sysmenu43024=g_sysmenu43024En;
			
			
			//�������������
			     g_sysmenu4701=g_sysmenu4701En;
			     g_sysmenu4702=g_sysmenu4702En;
			     g_sysmenu4703=g_sysmenu4703En;
			     g_sysmenu4704=g_sysmenu4704En;
			
			//������ڰ�����
			     g_sysmenu4801=g_sysmenu4801En;
			     g_sysmenu4802=g_sysmenu4802En;
			     g_sysmenu4803=g_sysmenu4803En;
			     g_sysmenu4804=g_sysmenu4804En;
		  //��ײ�ʵ�֣�
			//��Զ���Զ�У׼����ʾ:
			//��Զ��һ����������У׼��ʾ��

			 g_sysmenu1101=g_sysalign1101En; 
 		 	 g_sysmenu1102=g_sysalign1102En; 
			 g_sysmenu1103=g_sysalign1103En;
			 g_sysmenu1104=g_sysalign1104En; 
			 g_sysmenu1105=g_sysalign1105En; 
			 g_sysmenu1106=g_sysalign1106En; 
			 g_sysmenu1107=g_sysalign1107En; 
			 g_sysmenu1108=g_sysalign1108En; 
			 g_sysmenu1109=g_sysalign1109En;
			 			 //��Զ���ྭ��λ�ز�ⶨ
			 g_sysmenu11101=g_sysbacklash11101En;
			 g_sysmenu11102=g_sysbacklash11102En;
			 g_sysmenu11103=g_sysbacklash11103En;
			 g_sysmenu11104=g_sysbacklash11104En;
			 g_sysmenu11105=g_sysbacklash11105En;

			 g_sysmenu11106=g_sysbacklash11106En;
			 g_sysmenu11107=g_sysbacklash11107En;
			 g_sysmenu11108=g_sysbacklash11108En;
			 g_sysmenu11109=g_sysbacklash11109En;
			 g_sysmenu111010=g_sysbacklash111010En;
			 g_sysmenu111011=g_sysbacklash111011En;
			 g_sysmenu111012=g_sysbacklash111012En;
			 g_sysmenu111013=g_sysbacklash111013En;
			 g_sysmenu111014=g_sysbacklash111014En;
			 g_sysmenu111015=g_sysbacklash111015En;
			 g_sysmenu111016=g_sysbacklash111016En;
			 g_sysmenu111017=g_sysbacklash111017En;
			 g_sysmenu111018=g_sysbacklash111018En;
			 g_sysmenu111019=g_sysbacklash111019En;
			//g_sysmenu111020=g_sysbacklash111020En;

			 //û����Զ����ʾ
			 g_sysnotel1=g_sysNoTelescopeEn1;
			 g_sysnotel2=g_sysNoTelescopeEn2;
			 g_sysnotel3=g_sysNoTelescopeEn3;
			
			//***************************************************
			//***************************************************
			break;
		case FRENCH://����
		//ϵͳ�˵�����ѡ��:
			//***************************************************
			//һ���˵�
			     g_sysmenu1000= g_sysmenu1000Fre;
			     g_sysmenu2000= g_sysmenu2000Fre;
			     g_sysmenu3000= g_sysmenu3000Fre;
			     g_sysmenu4000= g_sysmenu4000Fre;
				//***************************************************  					
			//�����˵�
			//��Զ��У���Ӳ˵�			
			     g_sysmenu1100=g_sysmenu1100Fre;
			     g_sysmenu1200=g_sysmenu1200Fre;
			     g_sysmenu1300=g_sysmenu1300Fre;
			     g_sysmenu1400=g_sysmenu1400Fre;
			     g_sysmenu1500=g_sysmenu1500Fre;
			     g_sysmenu1600=g_sysmenu1600Fre;
			     g_sysmenu1700=g_sysmenu1700Fre;
//			     g_sysmenu1800=g_sysmenu1800Fre;
//			     g_sysmenu1900=g_sysmenu1900Fre;
//			     g_sysmenu1110=g_sysmenu1110Fre;
//			     g_sysmenu1120=g_sysmenu1120Fre;
			
			//Ŀ�굼���Ӳ˵�
			     g_sysmenu2100=g_sysmenu2100Fre;
			     g_sysmenu2200=g_sysmenu2200Fre;
			     g_sysmenu2300=g_sysmenu2300Fre;
			     g_sysmenu2400=g_sysmenu2400Fre;
			     g_sysmenu2500=g_sysmenu2500Fre;
			     g_sysmenu2600=g_sysmenu2600Fre;
			     g_sysmenu2700=g_sysmenu2700Fre;
			     g_sysmenu2800=g_sysmenu2800Fre;
			     g_sysmenu2900=g_sysmenu2900Fre;
			     g_sysmenu2110=g_sysmenu2110Fre;
				 g_sysmenu2120=g_sysmenu2120Fre;
				 g_sysmenu2130=g_sysmenu2130Fre;
			
			//���������Ӳ˵�
			     g_sysmenu3100=g_sysmenu3100Fre;
			     g_sysmenu3200=g_sysmenu3200Fre;
			     g_sysmenu3300=g_sysmenu3300Fre;
			     g_sysmenu3400=g_sysmenu3400Fre;
			     g_sysmenu3500=g_sysmenu3500Fre;
			     g_sysmenu3600=g_sysmenu3600Fre;
			     g_sysmenu3700=g_sysmenu3700Fre;
			     g_sysmenu3800=g_sysmenu3800Fre;
			     g_sysmenu3900=g_sysmenu3900Fre;
//			     g_sysmenu3110=g_sysmenu3110Fre;
			//���������Ӳ˵�
			     g_sysmenu4100=g_sysmenu4100Fre;
			     g_sysmenu4200=g_sysmenu4200Fre;
			     g_sysmenu4300=g_sysmenu4300Fre;
			     g_sysmenu4400=g_sysmenu4400Fre;
			     g_sysmenu4500=g_sysmenu4500Fre ;
			     g_sysmenu4600=g_sysmenu4600Fre;
			     g_sysmenu4700=g_sysmenu4700Fre;
			     g_sysmenu4800=g_sysmenu4800Fre;
			     g_sysmenu4900=g_sysmenu4900Fre;
//			     g_sysmenu4110=g_sysmenu4110Fre;
//			     g_sysmenu4120=g_sysmenu4120Fre;
			//***************************************************
						
			//***************************************************
			//�����˵�
			//�ڶ���ڶ�����
//			     g_sysmenu2201=g_sysmenu2201En;
//			     g_sysmenu2202=g_sysmenu2202En;
//			     g_sysmenu2203=g_sysmenu2203En;
//			     g_sysmenu2204=g_sysmenu2204En;
//			     g_sysmenu2205=g_sysmenu2205En;
//			     g_sysmenu2206=g_sysmenu2206En;
//			     g_sysmenu2207=g_sysmenu2207En;
//			     g_sysmenu2208=g_sysmenu2208En;
//			     g_sysmenu2209=g_sysmenu2209En;
//			     g_sysmenu22010=g_sysmenu22010En;
//			     g_sysmenu22011=g_sysmenu22011En;
			
			//�ڶ����������
//			     g_sysmenu2301=g_sysmenu2301En;
//			     g_sysmenu2302=g_sysmenu2302En;
//			     g_sysmenu2303=g_sysmenu2303En;
//			     g_sysmenu2304=g_sysmenu2304En;
//			     g_sysmenu2305=g_sysmenu2305En;
//			     g_sysmenu2306=g_sysmenu2306En;
//			     g_sysmenu2307=g_sysmenu2307En;
//			     g_sysmenu2308=g_sysmenu2308En;
//			
			//�ڶ����������
			     g_sysmenu2501=g_sysmenu2501En;
			     g_sysmenu2502=g_sysmenu2502En;
			     g_sysmenu2503=g_sysmenu2503En;
			
			//�ڶ���ڰ�����
			     g_sysmenu2801=g_sysmenu2801En;
			     g_sysmenu2802=g_sysmenu2802En;
			     g_sysmenu2803=g_sysmenu2803En;
			     g_sysmenu2804=g_sysmenu2804En;
			
			//�ڶ����ʮһ����
			     g_sysmenu21101=g_sysmenu21101En;
			     g_sysmenu21102=g_sysmenu21102En;
			     g_sysmenu21103=g_sysmenu21103En;
			//**********************
			//�������������
			     g_sysmenu3601=g_sysmenu3601En;
			     g_sysmenu3602=g_sysmenu3602En;
			
			//������ڰ�����
			     g_sysmenu3801=g_sysmenu3801En;
			     g_sysmenu3802=g_sysmenu3802En;
			
			//***********************
			//�������������
			     g_sysmenu4301=g_sysmenu4301En;
			     g_sysmenu4302=g_sysmenu4302En;
			
			     g_sysmenu43021=g_sysmenu43021En;
			     g_sysmenu43022=g_sysmenu43022En;
			     g_sysmenu43023=g_sysmenu43023En;
			     g_sysmenu43024=g_sysmenu43024En;
			
			
			//�������������
			     g_sysmenu4701=g_sysmenu4701En;
			     g_sysmenu4702=g_sysmenu4702En;
			     g_sysmenu4703=g_sysmenu4703En;
			     g_sysmenu4704=g_sysmenu4704En;
			
			//������ڰ�����
			     g_sysmenu4801=g_sysmenu4801En;
			     g_sysmenu4802=g_sysmenu4802En;
			     g_sysmenu4803=g_sysmenu4803En;
			     g_sysmenu4804=g_sysmenu4804En;
		  //��ײ�ʵ�֣�
			//��Զ���Զ�У׼����ʾ:
			//��Զ��һ����������У׼��ʾ��

			 g_sysmenu1101=g_sysalign1101En; 
 		 	 g_sysmenu1102=g_sysalign1102En; 
			 g_sysmenu1103=g_sysalign1103En;
			 g_sysmenu1104=g_sysalign1104En; 
			 g_sysmenu1105=g_sysalign1105En; 
			 g_sysmenu1106=g_sysalign1106En; 
			 g_sysmenu1107=g_sysalign1107En; 
			 g_sysmenu1108=g_sysalign1108En; 
			 g_sysmenu1109=g_sysalign1109En;
			 			 //��Զ���ྭ��λ�ز�ⶨ
			 g_sysmenu11101=g_sysbacklash11101En;
			 g_sysmenu11102=g_sysbacklash11102En;
			 g_sysmenu11103=g_sysbacklash11103En;
			 g_sysmenu11104=g_sysbacklash11104En;
			 g_sysmenu11105=g_sysbacklash11105En;

			 g_sysmenu11106=g_sysbacklash11106En;
			 g_sysmenu11107=g_sysbacklash11107En;
			 g_sysmenu11108=g_sysbacklash11108En;
			 g_sysmenu11109=g_sysbacklash11109En;
			 g_sysmenu111010=g_sysbacklash111010En;
			 g_sysmenu111011=g_sysbacklash111011En;
			 g_sysmenu111012=g_sysbacklash111012En;
			 g_sysmenu111013=g_sysbacklash111013En;
			 g_sysmenu111014=g_sysbacklash111014En;
			 g_sysmenu111015=g_sysbacklash111015En;
			 g_sysmenu111016=g_sysbacklash111016En;
			 g_sysmenu111017=g_sysbacklash111017En;
			 g_sysmenu111018=g_sysbacklash111018En;
			 g_sysmenu111019=g_sysbacklash111019En;
			//g_sysmenu111020=g_sysbacklash111020En;

			 //û����Զ����ʾ
			 g_sysnotel1=g_sysNoTelescopeEn1;
			 g_sysnotel2=g_sysNoTelescopeEn2;
			 g_sysnotel3=g_sysNoTelescopeEn3;
			
			//***************************************************
			break;
		 case ITALIAN://�������
		//ϵͳ�˵�����ѡ��:
			//***************************************************
			//һ���˵�
			     g_sysmenu1000= g_sysmenu1000Ita;
			     g_sysmenu2000= g_sysmenu2000Ita;
			     g_sysmenu3000= g_sysmenu3000Ita;
			     g_sysmenu4000= g_sysmenu4000Ita;
				//***************************************************  					
			//�����˵�
			//��Զ��У���Ӳ˵�			
			     g_sysmenu1100=g_sysmenu1100Ita;
			     g_sysmenu1200=g_sysmenu1200Ita;
			     g_sysmenu1300=g_sysmenu1300Ita;
			     g_sysmenu1400=g_sysmenu1400Ita;
			     g_sysmenu1500=g_sysmenu1500Ita;
			     g_sysmenu1600=g_sysmenu1600Ita;
			     g_sysmenu1700=g_sysmenu1700Ita;
//			     g_sysmenu1800=g_sysmenu1800Ita;
//			     g_sysmenu1900=g_sysmenu1900Ita;
//			     g_sysmenu1110=g_sysmenu1110Ita;
//			     g_sysmenu1120=g_sysmenu1120Ita;
			
			//Ŀ�굼���Ӳ˵�
			     g_sysmenu2100=g_sysmenu2100Ita;
			     g_sysmenu2200=g_sysmenu2200Ita;
			     g_sysmenu2300=g_sysmenu2300Ita;
			     g_sysmenu2400=g_sysmenu2400Ita;
			     g_sysmenu2500=g_sysmenu2500Ita;
			     g_sysmenu2600=g_sysmenu2600Ita;
			     g_sysmenu2700=g_sysmenu2700Ita;
			     g_sysmenu2800=g_sysmenu2800Ita;
			     g_sysmenu2900=g_sysmenu2900Ita;
			     g_sysmenu2110=g_sysmenu2110Ita;
				 g_sysmenu2120=g_sysmenu2120Ita;
				 g_sysmenu2130=g_sysmenu2130Ita;
			
			//���������Ӳ˵�
			     g_sysmenu3100=g_sysmenu3100Ita;
			     g_sysmenu3200=g_sysmenu3200Ita;
			     g_sysmenu3300=g_sysmenu3300Ita;
			     g_sysmenu3400=g_sysmenu3400Ita;
			     g_sysmenu3500=g_sysmenu3500Ita;
			     g_sysmenu3600=g_sysmenu3600Ita;
			     g_sysmenu3700=g_sysmenu3700Ita;
			     g_sysmenu3800=g_sysmenu3800Ita;
			     g_sysmenu3900=g_sysmenu3900Ita;
//			     g_sysmenu3110=g_sysmenu3110Ita;
			//���������Ӳ˵�
			     g_sysmenu4100=g_sysmenu4100Ita;
			     g_sysmenu4200=g_sysmenu4200Ita;
			     g_sysmenu4300=g_sysmenu4300Ita;
			     g_sysmenu4400=g_sysmenu4400Ita;
			     g_sysmenu4500=g_sysmenu4500Ita ;
			     g_sysmenu4600=g_sysmenu4600Ita;
			     g_sysmenu4700=g_sysmenu4700Ita;
			     g_sysmenu4800=g_sysmenu4800Ita;
			     g_sysmenu4900=g_sysmenu4900Ita;
//			     g_sysmenu4110=g_sysmenu4110Ita;
//			     g_sysmenu4120=g_sysmenu4120Ita;
			//***************************************************
						
			//***************************************************
			//�����˵�
			//�ڶ���ڶ�����
//			     g_sysmenu2201=g_sysmenu2201En;
//			     g_sysmenu2202=g_sysmenu2202En;
//			     g_sysmenu2203=g_sysmenu2203En;
//			     g_sysmenu2204=g_sysmenu2204En;
//			     g_sysmenu2205=g_sysmenu2205En;
//			     g_sysmenu2206=g_sysmenu2206En;
//			     g_sysmenu2207=g_sysmenu2207En;
//			     g_sysmenu2208=g_sysmenu2208En;
//			     g_sysmenu2209=g_sysmenu2209En;
//			     g_sysmenu22010=g_sysmenu22010En;
//			     g_sysmenu22011=g_sysmenu22011En;
			
			//�ڶ����������
//			     g_sysmenu2301=g_sysmenu2301En;
//			     g_sysmenu2302=g_sysmenu2302En;
//			     g_sysmenu2303=g_sysmenu2303En;
//			     g_sysmenu2304=g_sysmenu2304En;
//			     g_sysmenu2305=g_sysmenu2305En;
//			     g_sysmenu2306=g_sysmenu2306En;
//			     g_sysmenu2307=g_sysmenu2307En;
//			     g_sysmenu2308=g_sysmenu2308En;
//			
			//�ڶ����������
			     g_sysmenu2501=g_sysmenu2501En;
			     g_sysmenu2502=g_sysmenu2502En;
			     g_sysmenu2503=g_sysmenu2503En;
			
			//�ڶ���ڰ�����
			     g_sysmenu2801=g_sysmenu2801En;
			     g_sysmenu2802=g_sysmenu2802En;
			     g_sysmenu2803=g_sysmenu2803En;
			     g_sysmenu2804=g_sysmenu2804En;
			
			//�ڶ����ʮһ����
			     g_sysmenu21101=g_sysmenu21101En;
			     g_sysmenu21102=g_sysmenu21102En;
			     g_sysmenu21103=g_sysmenu21103En;
			//**********************
			//�������������
			     g_sysmenu3601=g_sysmenu3601En;
			     g_sysmenu3602=g_sysmenu3602En;
			
			//������ڰ�����
			     g_sysmenu3801=g_sysmenu3801En;
			     g_sysmenu3802=g_sysmenu3802En;
			
			//***********************
			//�������������
			     g_sysmenu4301=g_sysmenu4301En;
			     g_sysmenu4302=g_sysmenu4302En;
			
			     g_sysmenu43021=g_sysmenu43021En;
			     g_sysmenu43022=g_sysmenu43022En;
			     g_sysmenu43023=g_sysmenu43023En;
			     g_sysmenu43024=g_sysmenu43024En;
			
			
			//�������������
			     g_sysmenu4701=g_sysmenu4701En;
			     g_sysmenu4702=g_sysmenu4702En;
			     g_sysmenu4703=g_sysmenu4703En;
			     g_sysmenu4704=g_sysmenu4704En;
			
			//������ڰ�����
			     g_sysmenu4801=g_sysmenu4801En;
			     g_sysmenu4802=g_sysmenu4802En;
			     g_sysmenu4803=g_sysmenu4803En;
			     g_sysmenu4804=g_sysmenu4804En;
		  //��ײ�ʵ�֣�
			//��Զ���Զ�У׼����ʾ:
			//��Զ��һ����������У׼��ʾ��

			 g_sysmenu1101=g_sysalign1101En; 
 		 	 g_sysmenu1102=g_sysalign1102En; 
			 g_sysmenu1103=g_sysalign1103En;
			 g_sysmenu1104=g_sysalign1104En; 
			 g_sysmenu1105=g_sysalign1105En; 
			 g_sysmenu1106=g_sysalign1106En; 
			 g_sysmenu1107=g_sysalign1107En; 
			 g_sysmenu1108=g_sysalign1108En; 
			 g_sysmenu1109=g_sysalign1109En;
			 			 //��Զ���ྭ��λ�ز�ⶨ
			 g_sysmenu11101=g_sysbacklash11101En;
			 g_sysmenu11102=g_sysbacklash11102En;
			 g_sysmenu11103=g_sysbacklash11103En;
			 g_sysmenu11104=g_sysbacklash11104En;
			 g_sysmenu11105=g_sysbacklash11105En;

			 g_sysmenu11106=g_sysbacklash11106En;
			 g_sysmenu11107=g_sysbacklash11107En;
			 g_sysmenu11108=g_sysbacklash11108En;
			 g_sysmenu11109=g_sysbacklash11109En;
			 g_sysmenu111010=g_sysbacklash111010En;
			 g_sysmenu111011=g_sysbacklash111011En;
			 g_sysmenu111012=g_sysbacklash111012En;
			 g_sysmenu111013=g_sysbacklash111013En;
			 g_sysmenu111014=g_sysbacklash111014En;
			 g_sysmenu111015=g_sysbacklash111015En;
			 g_sysmenu111016=g_sysbacklash111016En;
			 g_sysmenu111017=g_sysbacklash111017En;
			 g_sysmenu111018=g_sysbacklash111018En;
			 g_sysmenu111019=g_sysbacklash111019En;
			//g_sysmenu111020=g_sysbacklash111020En;

			 //û����Զ����ʾ
			 g_sysnotel1=g_sysNoTelescopeEn1;
			 g_sysnotel2=g_sysNoTelescopeEn2;
			 g_sysnotel3=g_sysNoTelescopeEn3;
			
			//***************************************************
			break;
		case SPAIN://��������
		//ϵͳ�˵�����ѡ��:
			//***************************************************
			//һ���˵�
			     g_sysmenu1000= g_sysmenu1000Spa;
			     g_sysmenu2000= g_sysmenu2000Spa;
			     g_sysmenu3000= g_sysmenu3000Spa;
			     g_sysmenu4000= g_sysmenu4000Spa;
			//***************************************************  					
			//�����˵�
			//��Զ��У���Ӳ˵�			
			     g_sysmenu1100=g_sysmenu1100Spa;
			     g_sysmenu1200=g_sysmenu1200Spa;
			     g_sysmenu1300=g_sysmenu1300Spa;
			     g_sysmenu1400=g_sysmenu1400Spa;
			     g_sysmenu1500=g_sysmenu1500Spa;
			     g_sysmenu1600=g_sysmenu1600Spa;
			     g_sysmenu1700=g_sysmenu1700Spa;
//			     g_sysmenu1800=g_sysmenu1800Spa;
//			     g_sysmenu1900=g_sysmenu1900Spa;
//			     g_sysmenu1110=g_sysmenu1110Spa;
//			     g_sysmenu1120=g_sysmenu1120Spa;
			
			//Ŀ�굼���Ӳ˵�
			     g_sysmenu2100=g_sysmenu2100Spa;
			     g_sysmenu2200=g_sysmenu2200Spa;
			     g_sysmenu2300=g_sysmenu2300Spa;
			     g_sysmenu2400=g_sysmenu2400Spa;
			     g_sysmenu2500=g_sysmenu2500Spa;
			     g_sysmenu2600=g_sysmenu2600Spa;
			     g_sysmenu2700=g_sysmenu2700Spa;
			     g_sysmenu2800=g_sysmenu2800Spa;
			     g_sysmenu2900=g_sysmenu2900Spa;
			     g_sysmenu2110=g_sysmenu2110Spa;
				 g_sysmenu2120=g_sysmenu2120Spa;
				 g_sysmenu2130=g_sysmenu2130Spa;
			
			//���������Ӳ˵�
			     g_sysmenu3100=g_sysmenu3100Spa;
			     g_sysmenu3200=g_sysmenu3200Spa;
			     g_sysmenu3300=g_sysmenu3300Spa;
			     g_sysmenu3400=g_sysmenu3400Spa;
			     g_sysmenu3500=g_sysmenu3500Spa;
			     g_sysmenu3600=g_sysmenu3600Spa;
			     g_sysmenu3700=g_sysmenu3700Spa;
			     g_sysmenu3800=g_sysmenu3800Spa;
			     g_sysmenu3900=g_sysmenu3900Spa;
//			     g_sysmenu3110=g_sysmenu3110Spa;
			//���������Ӳ˵�
			     g_sysmenu4100=g_sysmenu4100Spa;
			     g_sysmenu4200=g_sysmenu4200Spa;
			     g_sysmenu4300=g_sysmenu4300Spa;
			     g_sysmenu4400=g_sysmenu4400Spa;
			     g_sysmenu4500=g_sysmenu4500Spa;
			     g_sysmenu4600=g_sysmenu4600Spa;
			     g_sysmenu4700=g_sysmenu4700Spa;
			     g_sysmenu4800=g_sysmenu4800Spa;
			     g_sysmenu4900=g_sysmenu4900Spa;
//			     g_sysmenu4110=g_sysmenu4110Spa;
//			     g_sysmenu4120=g_sysmenu4120Spa;
			//***************************************************
						
			//***************************************************
			//�����˵�
			//�ڶ���ڶ�����
//			     g_sysmenu2201=g_sysmenu2201En;
//			     g_sysmenu2202=g_sysmenu2202En;
//			     g_sysmenu2203=g_sysmenu2203En;
//			     g_sysmenu2204=g_sysmenu2204En;
//			     g_sysmenu2205=g_sysmenu2205En;
//			     g_sysmenu2206=g_sysmenu2206En;
//			     g_sysmenu2207=g_sysmenu2207En;
//			     g_sysmenu2208=g_sysmenu2208En;
//			     g_sysmenu2209=g_sysmenu2209En;
//			     g_sysmenu22010=g_sysmenu22010En;
//			     g_sysmenu22011=g_sysmenu22011En;
			
			//�ڶ����������
//			     g_sysmenu2301=g_sysmenu2301En;
//			     g_sysmenu2302=g_sysmenu2302En;
//			     g_sysmenu2303=g_sysmenu2303En;
//			     g_sysmenu2304=g_sysmenu2304En;
//			     g_sysmenu2305=g_sysmenu2305En;
//			     g_sysmenu2306=g_sysmenu2306En;
//			     g_sysmenu2307=g_sysmenu2307En;
//			     g_sysmenu2308=g_sysmenu2308En;
//			
			//�ڶ����������
			     g_sysmenu2501=g_sysmenu2501En;
			     g_sysmenu2502=g_sysmenu2502En;
			     g_sysmenu2503=g_sysmenu2503En;
			
			//�ڶ���ڰ�����
			     g_sysmenu2801=g_sysmenu2801En;
			     g_sysmenu2802=g_sysmenu2802En;
			     g_sysmenu2803=g_sysmenu2803En;
			     g_sysmenu2804=g_sysmenu2804En;
			
			//�ڶ����ʮһ����
			     g_sysmenu21101=g_sysmenu21101En;
			     g_sysmenu21102=g_sysmenu21102En;
			     g_sysmenu21103=g_sysmenu21103En;
			//**********************
			//�������������
			     g_sysmenu3601=g_sysmenu3601En;
			     g_sysmenu3602=g_sysmenu3602En;
			
			//������ڰ�����
			     g_sysmenu3801=g_sysmenu3801En;
			     g_sysmenu3802=g_sysmenu3802En;
			
			//***********************
			//�������������
			     g_sysmenu4301=g_sysmenu4301En;
			     g_sysmenu4302=g_sysmenu4302En;
			
			     g_sysmenu43021=g_sysmenu43021En;
			     g_sysmenu43022=g_sysmenu43022En;
			     g_sysmenu43023=g_sysmenu43023En;
			     g_sysmenu43024=g_sysmenu43024En;
			
			
			//�������������
			     g_sysmenu4701=g_sysmenu4701En;
			     g_sysmenu4702=g_sysmenu4702En;
			     g_sysmenu4703=g_sysmenu4703En;
			     g_sysmenu4704=g_sysmenu4704En;
			
			//������ڰ�����
			     g_sysmenu4801=g_sysmenu4801En;
			     g_sysmenu4802=g_sysmenu4802En;
			     g_sysmenu4803=g_sysmenu4803En;
			     g_sysmenu4804=g_sysmenu4804En;
		  //��ײ�ʵ�֣�
			//��Զ���Զ�У׼����ʾ:
			//��Զ��һ����������У׼��ʾ��

			 g_sysmenu1101=g_sysalign1101En; 
 		 	 g_sysmenu1102=g_sysalign1102En; 
			 g_sysmenu1103=g_sysalign1103En;
			 g_sysmenu1104=g_sysalign1104En; 
			 g_sysmenu1105=g_sysalign1105En; 
			 g_sysmenu1106=g_sysalign1106En; 
			 g_sysmenu1107=g_sysalign1107En; 
			 g_sysmenu1108=g_sysalign1108En; 
			 g_sysmenu1109=g_sysalign1109En;
			 			 //��Զ���ྭ��λ�ز�ⶨ
			 g_sysmenu11101=g_sysbacklash11101En;
			 g_sysmenu11102=g_sysbacklash11102En;
			 g_sysmenu11103=g_sysbacklash11103En;
			 g_sysmenu11104=g_sysbacklash11104En;
			 g_sysmenu11105=g_sysbacklash11105En;

			 g_sysmenu11106=g_sysbacklash11106En;
			 g_sysmenu11107=g_sysbacklash11107En;
			 g_sysmenu11108=g_sysbacklash11108En;
			 g_sysmenu11109=g_sysbacklash11109En;
			 g_sysmenu111010=g_sysbacklash111010En;
			 g_sysmenu111011=g_sysbacklash111011En;
			 g_sysmenu111012=g_sysbacklash111012En;
			 g_sysmenu111013=g_sysbacklash111013En;
			 g_sysmenu111014=g_sysbacklash111014En;
			 g_sysmenu111015=g_sysbacklash111015En;
			 g_sysmenu111016=g_sysbacklash111016En;
			 g_sysmenu111017=g_sysbacklash111017En;
			 g_sysmenu111018=g_sysbacklash111018En;
			 g_sysmenu111019=g_sysbacklash111019En;
			//g_sysmenu111020=g_sysbacklash111020En;

			 //û����Զ����ʾ
			 g_sysnotel1=g_sysNoTelescopeEn1;
			 g_sysnotel2=g_sysNoTelescopeEn2;
			 g_sysnotel3=g_sysNoTelescopeEn3;
			
			//***************************************************
			break;
		default:
		break;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



//*******************************************
//ϵͳ��ʾʱ���õ�����ѡ��
void FSelShowLanguage()
{
   switch(g_mMenuLangauge)
   {
//       case CHANESE:
//       g_mShowLangauge=CHANESE;
//	   break;
	   case ENGLISH:
       g_mShowLangauge=ENGLISH;
	   break;
	   case GERMAN:
       g_mShowLangauge=2;//GERMAN;
	   break;
	   case FRENCH:
       g_mShowLangauge=2;//FRENCH;
	   break;
	   case ITALIAN:
       g_mShowLangauge=2;//ITALIAN;
	   break;
	   case SPAIN:
       g_mShowLangauge=2;//SPAIN;
	   break;
	   default:
	   break;
	}
 }
 //*******************************************
 
 
 //****************************************************************************************
//��ȡ��Զ���İ���ֵ
uint8 GetKeyValue()
{ 
    uint8  m_ninkeyvalue,m_noutkeyvalue;
	m_ninkeyvalue=GetKey();
	if(m_ninkeyvalue&0x20)
	{
		m_ninkeyvalue&=0x1f;
		DoKey(); 
		g_bkeyoperator=false;//��ʾ��һ�εļ�����
		g_mNoKeyDownNum=0;
	}
	else
	{
       m_ninkeyvalue=100;
	
	}
	//ϵͳ����ƥ��
	switch(m_ninkeyvalue)
	{
		case 1:
		    m_noutkeyvalue=KEY_LEFT;
			break;
		case 2:
		    m_noutkeyvalue=KEY_NUM1;
			break;
		case 3:
		    m_noutkeyvalue=KEY_NUM4;
			break;
		case 4:
		    m_noutkeyvalue=KEY_NUM7;
			break;
		case 5:
		    m_noutkeyvalue=KEY_XH;
			break;
		case 6:
		    m_noutkeyvalue=KEY_DOWN;
			break;
		case 7:
		    m_noutkeyvalue=KEY_NUM2;
			break;
		case 8:
		    m_noutkeyvalue=KEY_NUM5;
			break;
		case 9:
		    m_noutkeyvalue=KEY_NUM8;
			break;
		case 10:
		    m_noutkeyvalue=KEY_NUM0;
			break;
		case 11:
		    m_noutkeyvalue=KEY_RIGHT;
			break;
		case 12:
		    m_noutkeyvalue=KEY_NUM3;
			break;
		case 13:
		    m_noutkeyvalue=KEY_NUM6;
			break;
		case 14:
		    m_noutkeyvalue=KEY_NUM9;
			break;
		case 15:
		    m_noutkeyvalue=KEY_WH;
			break;
		case 16:
		    m_noutkeyvalue=KEY_UP;
			break;
		case 17:
		    m_noutkeyvalue=KEY_ENTER;
			break;
		case 18:
		    m_noutkeyvalue=KEY_MENU;
			break;
		case 19:
		    m_noutkeyvalue=KEY_TORCH;
			break;
		case 20:
		    m_noutkeyvalue=KEY_BACK;
			break;	
	    case 21:
		    m_noutkeyvalue=KEY_LEFTDOWN;
			break;	
		case 22:
		    m_noutkeyvalue=KEY_LEFTUP;
			break;
		case 23:
		    m_noutkeyvalue=KEY_RIGHTDOWN;
			break;
		case 24:
		    m_noutkeyvalue=KEY_RIGHTUP;
			break;
		default :
		  FHandStopTelescope();					 
	    	FHandStopTelescope();
			break;	
	}
	
	return  m_noutkeyvalue ;
}
 //****************************************************************************************





/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//��������

//0��9�ż������������������Զ�����ٶȵ�����
//*******************************************************************
//0�Ű���
void FKey0()
{
 
  switch(g_nsysstatus)
  {
	case SYS_MAINSHOW: //������Զ�����ֶ��ٶ�0��
	if(!g_mLandMark )
	{
       if(g_mAzEq==0)
	   {
		   if(g_mTelStatusSet==0)
		   {
		      g_mTelStatusSet=1;
			  FPauseGoto();
			}
			else
			{
			 g_mTelStatusSet=0;				
			 FCalStarEQPos(g_mTelAzi+dg_mApos0,g_mTelAlt+dg_mZpos0,&g_telra,&g_teldec);		
			 FPointNewStar(g_telra,g_teldec);
			 g_mPauseTrack=1;//�ǲ�����ֹͣ�𶯵ĸ��� 0,���ǣ�1��
			 FContinueGoto();
			}
		}
		else
		{
		    if(g_mTelStatusSet==0)
		   {
		      g_mTelStatusSet=1;
			  FPauseGoto();
			}
			else
			{
				 g_mTelStatusSet=0;
				 g_teldec=g_mTelDec;
				 g_teldec=g_mTelDec-dg_mZpos0;

				 g_telra=FCalSiderealTime(1,false,g_mGoto.m_nLongitude)-g_mTelRa;
				 
				 g_telra=g_telra+dg_mApos0;
				 while(	g_telra>=24)
				 {
				   g_telra=g_telra-24;
				  }
				  while(g_telra<0)
				   {
				    g_telra=g_telra+24;
				   }
				 	
				 FPointNewStar(g_telra,g_teldec);
				 g_mPauseTrack=1;//�ǲ�����ֹͣ�𶯵ĸ��� 0,���ǣ�1��

				 FContinueGoto();
			}
		}
		}
		break;
	case SYS_SUB1SUB11RA_GEAR_ERROR_BEGIN: 	
	case SYS_SUB1SUB12DEC_GEAR_ERROR_BEGIN: 
	case SYS_SUB1SUB11RA_GEAR_ERROR_ALIGN: 	//��Զ��У׼ʱ���ֶ��ٶ�
	case SYS_SUB1SUB12DEC_GEAR_ERROR_ALIGN: 
		if(g_mTelStatusSet==0)
	   {
	      g_mTelStatusSet=1;
		  FPauseGoto();
		}
		else
		{
		  g_mTelStatusSet=0;
		  FContinueGoto();
		}
		break;

    case SYS_SUB1SUB2STAR_ALIGN	:
//	case SYS_SUB1SUB1AUTOSTAR_ALIGN:
	   if(g_mGoto.m_nTelGotoPause==0)
	   {	  		
         g_mGoto.m_nTelGotoPause=1;
		}
		else
		{
		  g_mGoto.m_nTelGotoPause=0;
		}
		break;
    case SYS_F_SELFNUM:
		if(g_mKeyBeepOpen==0)
		{
		  g_mKeyBeepOpen=1;
		}
		else
		{
		   g_mKeyBeepOpen=0;
		}	
	  break;

	case SYS_MAINHELP:
		g_mHandSpeed=0;//������Զ�����ֶ��ٶ�0��
		break;
   case SYS_SUB2SUN_PLANET1: //̫��ϵͳ����1 
   case  SYS_SUB2CON_OBJECT1:
   case  SYS_SUB2FS_OBJECT1: 			   
   case  SYS_SUB2MSR_OBJECT1:
   case  SYS_SUB2NGC_OBJECT1:
   case  SYS_SUB2IC_OBJECT1:
   case  SYS_SUB2SH2_OBJECT1:	
   case  SYS_SUB2BRT_OBJECT1:
   case  SYS_SUB2SAO_OBJECT1:

	    if(g_mOperateStatus==4)
		{
		  FContinueGoto();
		  
		}	
	    if((g_mOperateStatus==1)||(g_mOperateStatus==2))
		{						 
		   g_mOperateStatus=4;
		   FPauseGoto();
		 }		 
		break;					
	
					

	case SYS_SUB2MSR_OBJECT0: //messier�Ǳ���� 
	case SYS_SUB2MSR_OBJECT: 
	       LCDRfrsh();
			   if(((10* g_mInputStarNum+0)<=110)&&((10* g_mInputStarNum+0)>0))
			   {
		          g_mInputStarNum=10* g_mInputStarNum+0; 
		       }
			   if((g_mInputStarNum<=110)&&(g_mInputStarNum>0))
			   {			  
			     g_mMsrObjectNum= g_mInputStarNum;
			   }      
		 break;



	case SYS_SUB2NGC_OBJECT:   //ngc�Ǳ����
               LCDRfrsh();
			   if(((10* g_mInputStarNum+0)<=7840)&&((10* g_mInputStarNum+0)>0))
			   {
		          g_mInputStarNum=10* g_mInputStarNum+0; 
		       }
			   if((g_mInputStarNum<=7840)&&(g_mInputStarNum>0))
			   {			  
			    g_mNgcObjectNum= g_mInputStarNum;
			   }      
		 break;

		case SYS_SUB2IC_OBJECT:  //ic�Ǳ����
		        LCDRfrsh();
			   if(((10* g_mInputStarNum+0)<=5386)&&((10* g_mInputStarNum+0)>0))
			   {
		          g_mInputStarNum=10* g_mInputStarNum+0; 
		       }
			   if((g_mInputStarNum<=5386)&&(g_mInputStarNum>0))
			   {			  
			     g_mIcObjectNum= g_mInputStarNum;
			   }      
		 break;
		 case SYS_SUB2SH2_OBJECT:  //sh2�Ǳ����
			 	 LCDRfrsh();
			   if(((10* g_mInputStarNum+0)<=313)&&((10* g_mInputStarNum+0)>0))
			   {
		          g_mInputStarNum=10* g_mInputStarNum+0; 
		       }
			   if((g_mInputStarNum<=313)&&(g_mInputStarNum>0))
			   {			  
			     g_mSh2ObjectNum= g_mInputStarNum;
			   }      
		 break;

		 case SYS_SUB2BRT_OBJECT:  //bright�Ǳ����
		 		 	 LCDRfrsh();
			   if(((10* g_mInputStarNum+0)<=167)&&((10* g_mInputStarNum+0)>0))
			   {
		          g_mInputStarNum=10* g_mInputStarNum+0; 
		       }
			   if((g_mInputStarNum<=167)&&(g_mInputStarNum>0))
			   {			  
			     g_mBrightObjectNum= g_mInputStarNum;
			   }      
		 break;
	
	     case SYS_SUB2SAO_OBJECT:  //sao�Ǳ����
                LCDRfrsh();
			   if(((10* g_mInputStarNum+0)<=258997)&&((10* g_mInputStarNum+0)>0))
			   {
		          g_mInputStarNum=10* g_mInputStarNum+0; 
		       }
			   if((g_mInputStarNum<=258997)&&(g_mInputStarNum>0))
			   {			  
			     g_mSaoObjectNum= g_mInputStarNum;
			   }      
		 break;


		  
		  

	case  SYS_SUB2SUB9RA:
	case SYS_MENU_SKY_RA:
	  	    g_sysmenu2900ra[g_mShowMenucolumn-1]='0';//�ྭ����
			g_sysmenu2900raEn[g_mShowMenucolumn-1]='0';//�ྭ����
			FRaInputMoveRight();
	        break;
	case SYS_MENU_LAND_AZI:
	  	    g_sysmenu2900ra[g_mShowMenucolumn-1]='0';//�ྭ����
			g_sysmenu2900raEn[g_mShowMenucolumn-1]='0';//�ྭ����
			FDecInputMoveRight();
	        break;
	case SYS_SUB2SUB9DEC:
	case SYS_MENU_SKY_DEC:
	case SYS_MENU_LAND_ALT:
	        if(	g_mShowMenucolumn!=5)
			{
	  	       g_sysmenu2900dec[g_mShowMenucolumn-1]='0';//��γ��������
			   g_sysmenu2900decEn[g_mShowMenucolumn-1]='0';//��γ��������
			}
			else  if(g_sysmenu2900dec[g_mShowMenucolumn-1]=='+'	)
			{
			  g_sysmenu2900dec[g_mShowMenucolumn-1]='-';//��γ������
			  g_sysmenu2900decEn[g_mShowMenucolumn-1]='-';//��γ������
			}
			else
			{
		    	g_sysmenu2900dec[g_mShowMenucolumn-1]='+';//��γ������
				g_sysmenu2900decEn[g_mShowMenucolumn-1]='+';//��γ������

			}
			FDecInputMoveRight();
	        break;

	  case SYS_MENU_SKY_NAME:	
	  case SYS_MENU_LAND_NAME:
	        switch(g_keychar)
			{
			   case '0':
			        g_keychar=' ';
			   break;
			    case ' ':
			         g_keychar='0';
			   break;
			   default:
			       g_keychar='0' ;
			   break;
			}
		   g_sysmenu2900NameEn[g_mShowMenucolumn-1]=g_keychar;	 
		   break;



		

  //�Զ����ٶ�����
	case SYS_SUB4SUB8MENU4_RASPEED :
	     if(g_mShowMenucolumn!=1)
			{
	  	       g_sysmenu4800raspeed[g_mShowMenucolumn-1]='0';	
	           g_sysmenu4800raspeedEn[g_mShowMenucolumn-1]='0';
			}
			else  if(g_sysmenu4800raspeed[g_mShowMenucolumn-1]=='+'	)
			{
                g_sysmenu4800raspeed[g_mShowMenucolumn-1]='-';	
	            g_sysmenu4800raspeedEn[g_mShowMenucolumn-1]='-';
			}
			else
			{
		        g_sysmenu4800raspeed[g_mShowMenucolumn-1]='+';	
	            g_sysmenu4800raspeedEn[g_mShowMenucolumn-1]='+';

			}	
	   FRaTrackSpeedInputMoveRight() ;  //�Զ�������ٶ�����������
	break;

  //ʱ��ʱ������
	case  SYS_SUB4SUB1_SETTIME:
		 
		 if(g_mdatetime==0)
		 {
		        g_sysmenu4100date[g_mShowMenucolumn-1]='0';	
		        g_sysmenu4100dateEn[g_mShowMenucolumn-1]='0';
		}
		else
		{ 
		   		g_sysmenu4100time[g_mShowMenucolumn-1]='0';	
		        g_sysmenu4100timeEn[g_mShowMenucolumn-1]='0';
		}
					
	    FDateTimeInputMoveRight() ;  
	break;

	//�Զ���ص�����
	case SYS_SUB4SUB3_SETSITE : 
		FSiteInput(0);
		break; 

	//��������
	//case SYS_SUB4SUB4WEATHER:				  
	//	FWeatherInput(0);
		break;
	//��Զ���������
	case SYS_SUB4SUB7_TELAZIALT_ZERO:				  
		FTelZeroInput(0);
		break;

//**********************

	case SYS_SUB3SUB4TIMER_INPUT:
	      g_sysmenu3402off[g_mShowMenucolumn-1]='0';
		  g_sysmenu3402offEn[g_mShowMenucolumn-1]='0';
		  FTimerInputMoveRight();
		  break; 
	case SYS_SUB3SUB5ALARM_INPUT:
	      g_sysmenu3500alarm_input[g_mShowMenucolumn-1]='0';
		  g_sysmenu3500alarm_inputEn[g_mShowMenucolumn-1]='0';
		  FAlarmInputMoveRight();
		  break; 
	case SYS_SUB3SUB6SUB2M_MF:
	case SYS_SUB3SUB6SUB2M_MF1:
		  g_sysmenu3602m_mf[g_mShowMenucolumn-1]='0';
		  g_sysmenu3602m_mfEn[g_mShowMenucolumn-1]='0';
	
		  FMfocusInputMoveRight();
		  break;
	case SYS_SUB3SUB6SUB2M_SF:
	case SYS_SUB3SUB6SUB2M_SF1:	 
	 	 g_sysmenu3602m_sf[g_mShowMenucolumn-1]='0';
		 g_sysmenu3602m_sfEn[g_mShowMenucolumn-1]='0';
		 FSfocusInputMoveRight();					   
		 break;
	case SYS_SUB3SUB6SUB2M_MFOV: 
		  g_sysmenu3602m_mfovEn[g_mShowMenucolumn-1]='0';
		 FSFovInputMoveRight();
		  break;
	case SYS_SUB2SUB11_SET:
		F_LandmarkInput(0);
		break;


//*******************		
	default:
	break;
  }
}
//*******************************************************************


//*******************************************************************
//1�Ű���
void FKey1()
{

 switch(g_nsysstatus)
  {
	case SYS_MAINSHOW: //������Զ�����ֶ��ٶ�1��
		g_mHandSpeed=1;
		break;

	case SYS_F_SELFNUM:
	case SYS_MENU_SKY_OBJECT:
    case SYS_MENU_LAND_OBJECT:
		g_mFnum=1;
		break;
	case SYS_MAINHELP:
		g_mHandSpeed=1;//������Զ�����ֶ��ٶ�1��
		break;
  case SYS_SUB1SUB11RA_GEAR_ERROR_BEGIN: 	
	case SYS_SUB1SUB12DEC_GEAR_ERROR_BEGIN: 
	case SYS_SUB1SUB11RA_GEAR_ERROR_ALIGN: 	//��Զ��У׼ʱ���ֶ��ٶ�
	case SYS_SUB1SUB12DEC_GEAR_ERROR_ALIGN: 
	case SYS_SUB1SUB2STAR_ALIGN	:

		g_mHandSpeed=1;
		break;

	case SYS_SUB2MSR_OBJECT0: //messier�Ǳ���� 
	case SYS_SUB2MSR_OBJECT: 
	           LCDRfrsh();
			   if(((10* g_mInputStarNum+1)<=110)&&((10* g_mInputStarNum+1)>0))
			   {
		          g_mInputStarNum=10* g_mInputStarNum+1; 
		       }
			   if((g_mInputStarNum<=110)&&(g_mInputStarNum>0))
			   {			  
			     g_mMsrObjectNum= g_mInputStarNum;
			   }      
		 break;



	case SYS_SUB2NGC_OBJECT:   //ngc�Ǳ����
	            LCDRfrsh();
			   if(((10* g_mInputStarNum+1)<=7840)&&((10* g_mInputStarNum+1)>0))
			   {
		          g_mInputStarNum=10* g_mInputStarNum+1; 
		       }
			   if((g_mInputStarNum<=7840)&&(g_mInputStarNum>0))
			   {			  
			    g_mNgcObjectNum= g_mInputStarNum;
			   }      
		 break;

		case SYS_SUB2IC_OBJECT:  //ic�Ǳ����
		 LCDRfrsh();
			   if(((10* g_mInputStarNum+1)<=5386)&&((10* g_mInputStarNum+1)>0))
			   {
		          g_mInputStarNum=10* g_mInputStarNum+1; 
		       }
			   if((g_mInputStarNum<=5386)&&(g_mInputStarNum>0))
			   {			  
			     g_mIcObjectNum= g_mInputStarNum;
			   }      
		 break;
		 case SYS_SUB2SH2_OBJECT:  //sh2�Ǳ����
		 	        LCDRfrsh();
			   if(((10* g_mInputStarNum+1)<=313)&&((10* g_mInputStarNum+1)>0))
			   {
		          g_mInputStarNum=10* g_mInputStarNum+1; 
		       }
			   if((g_mInputStarNum<=313)&&(g_mInputStarNum>0))
			   {			  
			     g_mSh2ObjectNum= g_mInputStarNum;
			   }      
		 break;

		 case SYS_SUB2BRT_OBJECT:  //bright�Ǳ����
		 		 	 LCDRfrsh();
			   if(((10* g_mInputStarNum+1)<=167)&&((10* g_mInputStarNum+1)>0))
			   {
		          g_mInputStarNum=10* g_mInputStarNum+1; 
		       }
			   if((g_mInputStarNum<=167)&&(g_mInputStarNum>0))
			   {			  
			     g_mBrightObjectNum= g_mInputStarNum;
			   }      
		 break;
	
	     case SYS_SUB2SAO_OBJECT:  //sao�Ǳ����
		 	 	LCDRfrsh();
			   if(((10* g_mInputStarNum+1)<=258997)&&((10* g_mInputStarNum+1)>0))
			   {
		          g_mInputStarNum=10* g_mInputStarNum+1; 
		       }
			   if((g_mInputStarNum<=258997)&&(g_mInputStarNum>0))
			   {			  
			     g_mSaoObjectNum= g_mInputStarNum;
			   }      
		 break;


	case  SYS_SUB2SUB9RA:
	case SYS_MENU_SKY_RA:
	  	    g_sysmenu2900ra[g_mShowMenucolumn-1]='1';//�ྭ����
			g_sysmenu2900raEn[g_mShowMenucolumn-1]='1';//�ྭ����
			FRaInputMoveRight();
	        break;
    case SYS_MENU_LAND_AZI:
	  	    g_sysmenu2900ra[g_mShowMenucolumn-1]='1';//�ྭ����
			g_sysmenu2900raEn[g_mShowMenucolumn-1]='1';//�ྭ����
			FDecInputMoveRight();
	        break;
	case SYS_SUB2SUB9DEC:
	case SYS_MENU_SKY_DEC:
	case SYS_MENU_LAND_ALT:
	  	    if(	g_mShowMenucolumn!=5)
			{
	  	       g_sysmenu2900dec[g_mShowMenucolumn-1]='1';//��γ��������
			   g_sysmenu2900decEn[g_mShowMenucolumn-1]='1';//��γ��������
			}
			else  if(g_sysmenu2900dec[g_mShowMenucolumn-1]=='+'	)
			{
			  g_sysmenu2900dec[g_mShowMenucolumn-1]='-';//��γ������
			  g_sysmenu2900decEn[g_mShowMenucolumn-1]='-';//��γ������
			}
			else
			{
		    	g_sysmenu2900dec[g_mShowMenucolumn-1]='+';//��γ������
				g_sysmenu2900decEn[g_mShowMenucolumn-1]='+';//��γ������
			}
			FDecInputMoveRight();
	        break;

	  case SYS_MENU_SKY_NAME:	
	  case SYS_MENU_LAND_NAME:	
	      	g_keychar='1';
		   g_sysmenu2900NameEn[g_mShowMenucolumn-1]=g_keychar;	 
		   break;





	case SYS_SUB4SUB8MENU4_RASPEED :
	     if(g_mShowMenucolumn!=1)
			{
	  	       g_sysmenu4800raspeed[g_mShowMenucolumn-1]='1';	
	           g_sysmenu4800raspeedEn[g_mShowMenucolumn-1]='1';
			}
			else  if(g_sysmenu4800raspeed[g_mShowMenucolumn-1]=='+'	)
			{
                g_sysmenu4800raspeed[g_mShowMenucolumn-1]='-';	
	            g_sysmenu4800raspeedEn[g_mShowMenucolumn-1]='-';
			}
			else
			{
		        g_sysmenu4800raspeed[g_mShowMenucolumn-1]='+';	
	            g_sysmenu4800raspeedEn[g_mShowMenucolumn-1]='+';

			}	
	   FRaTrackSpeedInputMoveRight() ;  //�Զ�������ٶ�����������
	break;
	  //ʱ��ʱ������
	case  SYS_SUB4SUB1_SETTIME:
		 
		 if(g_mdatetime==0)
		 {
		        g_sysmenu4100date[g_mShowMenucolumn-1]='1';	
		        g_sysmenu4100dateEn[g_mShowMenucolumn-1]='1';
		}
		else
		{ 
		   		g_sysmenu4100time[g_mShowMenucolumn-1]='1';	
		        g_sysmenu4100timeEn[g_mShowMenucolumn-1]='1';
		}
					
	    FDateTimeInputMoveRight() ;
		break;
	//�Զ���ص�����
	case SYS_SUB4SUB3_SETSITE : 
	 FSiteInput(1);
	break;
	 //��Զ���������
	case SYS_SUB4SUB7_TELAZIALT_ZERO:				  
		FTelZeroInput(1);
		break;
//***********************************	FStarInputLeft();
	case SYS_SUB3SUB4TIMER_INPUT:
	      g_sysmenu3402off[g_mShowMenucolumn-1]='1';
		  g_sysmenu3402offEn[g_mShowMenucolumn-1]='1';
		  FTimerInputMoveRight();
		  break;     
	case SYS_SUB3SUB5ALARM_INPUT:
	      g_sysmenu3500alarm_input[g_mShowMenucolumn-1]='1';
		  g_sysmenu3500alarm_inputEn[g_mShowMenucolumn-1]='1';
		  FAlarmInputMoveRight();
		  break; 
	case SYS_SUB3SUB6SUB2M_MF:
	case SYS_SUB3SUB6SUB2M_MF1:
		  g_sysmenu3602m_mf[g_mShowMenucolumn-1]='1';
		  g_sysmenu3602m_mfEn[g_mShowMenucolumn-1]='1';
		  FMfocusInputMoveRight();
		  break;
	case SYS_SUB3SUB6SUB2M_SF:
	case SYS_SUB3SUB6SUB2M_SF1:	 
	 	 g_sysmenu3602m_sf[g_mShowMenucolumn-1]='1';
		 g_sysmenu3602m_sfEn[g_mShowMenucolumn-1]='1';
		 FSfocusInputMoveRight();
		 break;
	case SYS_SUB3SUB6SUB2M_MFOV: 
		  g_sysmenu3602m_mfovEn[g_mShowMenucolumn-1]='1';
		  FSFovInputMoveRight();
		  break;

	case SYS_SUB2SUB11_SET:
		F_LandmarkInput(1);
		break;

		F_SelfdefStarInput(1);
		break;
//***********************************
	default:
	break;
  }
}
//*******************************************************************


//*******************************************************************
//2�Ű���
void FKey2()
{

   switch(g_nsysstatus)
  {
	case SYS_MAINSHOW: //������Զ�����ֶ��ٶ�2��
		g_mHandSpeed=2;
		break;
	case SYS_F_SELFNUM:
	case SYS_MENU_SKY_OBJECT:
    case SYS_MENU_LAND_OBJECT:
		g_mFnum=2;
		break;
	case SYS_MAINHELP:
		g_mHandSpeed=2;//������Զ�����ֶ��ٶ�2��
		break;
	case SYS_SUB1SUB11RA_GEAR_ERROR_BEGIN:	
	case SYS_SUB1SUB12DEC_GEAR_ERROR_BEGIN:
	case SYS_SUB1SUB11RA_GEAR_ERROR_ALIGN: 	//��Զ��У׼ʱ���ֶ��ٶ�
	case SYS_SUB1SUB12DEC_GEAR_ERROR_ALIGN: 
	case SYS_SUB1SUB2STAR_ALIGN	:

		g_mHandSpeed=2;
		break;

	case SYS_SUB2MSR_OBJECT0: //messier�Ǳ���� 
	case SYS_SUB2MSR_OBJECT: 
	          LCDRfrsh();
			   if(((10* g_mInputStarNum+2)<=110)&&((10* g_mInputStarNum+2)>0))
			   {
		          g_mInputStarNum=10* g_mInputStarNum+2; 
		       }
			   if((g_mInputStarNum<=110)&&(g_mInputStarNum>0))
			   {			  
			     g_mMsrObjectNum= g_mInputStarNum;
			   }      
		 break;



	case SYS_SUB2NGC_OBJECT:   //ngc�Ǳ����
	 LCDRfrsh();
			   if(((10* g_mInputStarNum+2)<=7840)&&((10* g_mInputStarNum+2)>0))
			   {
		          g_mInputStarNum=10* g_mInputStarNum+2; 
		       }
			   if((g_mInputStarNum<=7840)&&(g_mInputStarNum>0))
			   {			  
			    g_mNgcObjectNum= g_mInputStarNum;
			   }      
		 break;

		case SYS_SUB2IC_OBJECT:  //ic�Ǳ����
		 LCDRfrsh();
			   if(((10* g_mInputStarNum+2)<=5386)&&((10* g_mInputStarNum+2)>0))
			   {
		          g_mInputStarNum=10* g_mInputStarNum+2; 
		       }
			   if((g_mInputStarNum<=5386)&&(g_mInputStarNum>0))
			   {			  
			     g_mIcObjectNum= g_mInputStarNum;
			   }      
		 break;
		 case SYS_SUB2SH2_OBJECT:  //sh2�Ǳ����
		 	        LCDRfrsh();
			   if(((10* g_mInputStarNum+2)<=313)&&((10* g_mInputStarNum+2)>0))
			   {
		          g_mInputStarNum=10* g_mInputStarNum+2; 
		       }
			   if((g_mInputStarNum<=313)&&(g_mInputStarNum>0))
			   {			  
			     g_mSh2ObjectNum= g_mInputStarNum;
			   }      
		 break;

		 case SYS_SUB2BRT_OBJECT:  //bright�Ǳ����
		 		 	 LCDRfrsh();
			   if(((10* g_mInputStarNum+2)<=167)&&((10* g_mInputStarNum+2)>0))
			   {
		          g_mInputStarNum=10* g_mInputStarNum+2; 
		       }
			   if((g_mInputStarNum<=167)&&(g_mInputStarNum>0))
			   {			  
			     g_mBrightObjectNum= g_mInputStarNum;
			   }      
		 break;
	
	     case SYS_SUB2SAO_OBJECT:  //sao�Ǳ����
		 	 	LCDRfrsh();
			   if(((10* g_mInputStarNum+2)<=258997)&&((10* g_mInputStarNum+2)>0))
			   {
		          g_mInputStarNum=10* g_mInputStarNum+2; 
		       }
			   if((g_mInputStarNum<=258997)&&(g_mInputStarNum>0))
			   {			  
			     g_mSaoObjectNum= g_mInputStarNum;
			   }      
		 break;


	case  SYS_SUB2SUB9RA:
	case SYS_MENU_SKY_RA:
	  	    g_sysmenu2900ra[g_mShowMenucolumn-1]='2';//�ྭ����
			g_sysmenu2900raEn[g_mShowMenucolumn-1]='2';//�ྭ����
			FRaInputMoveRight();
	        break;
	case SYS_MENU_LAND_AZI:
	  	    g_sysmenu2900ra[g_mShowMenucolumn-1]='2';//�ྭ����
			g_sysmenu2900raEn[g_mShowMenucolumn-1]='2';//�ྭ����
			FDecInputMoveRight();
	        break;
	case SYS_SUB2SUB9DEC:
	case SYS_MENU_SKY_DEC:
	case SYS_MENU_LAND_ALT:
	  	    if(	g_mShowMenucolumn!=5)
			{
	  	       g_sysmenu2900dec[g_mShowMenucolumn-1]='2';//��γ��������
			   g_sysmenu2900decEn[g_mShowMenucolumn-1]='2';//��γ��������
			}
			else  if(g_sysmenu2900dec[g_mShowMenucolumn-1]=='+'	)
			{
			  g_sysmenu2900dec[g_mShowMenucolumn-1]='-';//��γ������
			  g_sysmenu2900decEn[g_mShowMenucolumn-1]='-';//��γ������
			}
			else
			{
		    	g_sysmenu2900dec[g_mShowMenucolumn-1]='+';//��γ������
				g_sysmenu2900decEn[g_mShowMenucolumn-1]='+';//��γ������
			}
			FDecInputMoveRight();
	        break;
	  case SYS_MENU_SKY_NAME:	
	  case SYS_MENU_LAND_NAME:		
	        switch(g_keychar)
			{
			   case '2':
			        g_keychar='a';
			   break;
			    case 'a':
			         g_keychar='b';
			   break; 
			    case 'b':
			         g_keychar='c';
			   break;
			     case 'c':
			         g_keychar='A';
			   break;
			     case 'A':
			         g_keychar='B';
			   break;
			   case 'B':
			         g_keychar='C';
			   break;
			   case 'C':
			         g_keychar='2';
			   break;
			   default:
			       g_keychar='2' ;
			   break;
			}
		   g_sysmenu2900NameEn[g_mShowMenucolumn-1]=g_keychar;	 
		   break;


	case SYS_SUB4SUB8MENU4_RASPEED :
	     if(g_mShowMenucolumn!=1)
			{
	  	       g_sysmenu4800raspeed[g_mShowMenucolumn-1]='2';	
	           g_sysmenu4800raspeedEn[g_mShowMenucolumn-1]='2';
			}
			else  if(g_sysmenu4800raspeed[g_mShowMenucolumn-1]=='+'	)
			{
                g_sysmenu4800raspeed[g_mShowMenucolumn-1]='-';	
	            g_sysmenu4800raspeedEn[g_mShowMenucolumn-1]='-';
			}
			else
			{
		        g_sysmenu4800raspeed[g_mShowMenucolumn-1]='+';	
	            g_sysmenu4800raspeedEn[g_mShowMenucolumn-1]='+';

			}	
	   FRaTrackSpeedInputMoveRight() ;  //�Զ�������ٶ�����������
	break;
	  //ʱ��ʱ������
	case  SYS_SUB4SUB1_SETTIME:
		 
		 if(g_mdatetime==0)
		 {
		        g_sysmenu4100date[g_mShowMenucolumn-1]='2';	
		        g_sysmenu4100dateEn[g_mShowMenucolumn-1]='2';
		}
		else
		{ 
		   		g_sysmenu4100time[g_mShowMenucolumn-1]='2';	
		        g_sysmenu4100timeEn[g_mShowMenucolumn-1]='2';
		}
					
	    FDateTimeInputMoveRight() ;
		break;
		//�Զ���ص�����
	case SYS_SUB4SUB3_SETSITE : 
	 FSiteInput(2);
	break;
	 //��Զ���������
	case SYS_SUB4SUB7_TELAZIALT_ZERO:				  
		FTelZeroInput(2);
		break;
//****************************************
	case SYS_SUB3SUB4TIMER_INPUT:
	      g_sysmenu3402off[g_mShowMenucolumn-1]='2';
		  g_sysmenu3402offEn[g_mShowMenucolumn-1]='2';
		  FTimerInputMoveRight();
		  break;     
	case SYS_SUB3SUB5ALARM_INPUT:
	      g_sysmenu3500alarm_input[g_mShowMenucolumn-1]='2';
		  g_sysmenu3500alarm_inputEn[g_mShowMenucolumn-1]='2';
		  FAlarmInputMoveRight();
		  break; 
	case SYS_SUB3SUB6SUB2M_MF:
	case SYS_SUB3SUB6SUB2M_MF1:
		  g_sysmenu3602m_mf[g_mShowMenucolumn-1]='2';
		  g_sysmenu3602m_mfEn[g_mShowMenucolumn-1]='2';
		  FMfocusInputMoveRight();
		  break;
	case SYS_SUB3SUB6SUB2M_SF:
	case SYS_SUB3SUB6SUB2M_SF1:	 
	 	 g_sysmenu3602m_sf[g_mShowMenucolumn-1]='2';
		 g_sysmenu3602m_sfEn[g_mShowMenucolumn-1]='2';
		 FSfocusInputMoveRight();
		 break;
	case SYS_SUB3SUB6SUB2M_MFOV: 
		  g_sysmenu3602m_mfovEn[g_mShowMenucolumn-1]='2';
		  FSFovInputMoveRight();
		  break;
	case SYS_SUB2SUB11_SET:
		F_LandmarkInput(2);
		break;

//***********************************************
	default:
	break;
  }
}

//*******************************************************************


//*******************************************************************
//3�Ű���

void FKey3()
{

 switch(g_nsysstatus)
  {
	case SYS_MAINSHOW: //������Զ�����ֶ��ٶ�3��
		g_mHandSpeed=3;
		break;
	case SYS_F_SELFNUM:
	case SYS_MENU_SKY_OBJECT:
    case SYS_MENU_LAND_OBJECT:
		g_mFnum=3;
		break;
	case SYS_MAINHELP:
		g_mHandSpeed=3;//������Զ�����ֶ��ٶ�3��
		break;
	case SYS_SUB1SUB11RA_GEAR_ERROR_BEGIN: 	
	case SYS_SUB1SUB12DEC_GEAR_ERROR_BEGIN:
	case SYS_SUB1SUB11RA_GEAR_ERROR_ALIGN: 	//��Զ��У׼ʱ���ֶ��ٶ�
	case SYS_SUB1SUB12DEC_GEAR_ERROR_ALIGN: 
	case SYS_SUB1SUB2STAR_ALIGN	:
		g_mHandSpeed=3;
		break;

	case SYS_SUB2MSR_OBJECT0: //messier�Ǳ���� 
	case SYS_SUB2MSR_OBJECT: 
	            LCDRfrsh();
			   if(((10* g_mInputStarNum+3)<=110)&&((10* g_mInputStarNum+3)>0))
			   {
		          g_mInputStarNum=10* g_mInputStarNum+3; 
		       }
			   if((g_mInputStarNum<=110)&&(g_mInputStarNum>0))
			   {			  
			     g_mMsrObjectNum= g_mInputStarNum;
			   }      
		 break;

	case SYS_SUB2NGC_OBJECT:   //ngc�Ǳ����
	 LCDRfrsh();
			   if(((10* g_mInputStarNum+3)<=7840)&&((10* g_mInputStarNum+3)>0))
			   {
		          g_mInputStarNum=10* g_mInputStarNum+3; 
		       }
			   if((g_mInputStarNum<=7840)&&(g_mInputStarNum>0))
			   {			  
			    g_mNgcObjectNum= g_mInputStarNum;
			   }      
		 break;

		case SYS_SUB2IC_OBJECT:  //ic�Ǳ����
		 LCDRfrsh();
			   if(((10* g_mInputStarNum+3)<=5386)&&((10* g_mInputStarNum+3)>0))
			   {
		          g_mInputStarNum=10* g_mInputStarNum+3; 
		       }
			   if((g_mInputStarNum<=5386)&&(g_mInputStarNum>0))
			   {			  
			     g_mIcObjectNum= g_mInputStarNum;
			   }      
		 break;
		 case SYS_SUB2SH2_OBJECT:  //sh2�Ǳ����
		 	        LCDRfrsh();
			   if(((10* g_mInputStarNum+3)<=313)&&((10* g_mInputStarNum+3)>0))
			   {
		          g_mInputStarNum=10* g_mInputStarNum+3; 
		       }
			   if((g_mInputStarNum<=313)&&(g_mInputStarNum>0))
			   {			  
			     g_mSh2ObjectNum= g_mInputStarNum;
			   }      
		 break;

		 case SYS_SUB2BRT_OBJECT:  //bright�Ǳ����
		 		 	 LCDRfrsh();
			   if(((10* g_mInputStarNum+3)<=167)&&((10* g_mInputStarNum+3)>0))
			   {
		          g_mInputStarNum=10* g_mInputStarNum+3; 
		       }
			   if((g_mInputStarNum<=167)&&(g_mInputStarNum>0))
			   {			  
			     g_mBrightObjectNum= g_mInputStarNum;
			   }      
		 break;
	
	     case SYS_SUB2SAO_OBJECT:  //sao�Ǳ����
		 	 	LCDRfrsh();
			   if(((10* g_mInputStarNum+3)<=258997)&&((10* g_mInputStarNum+3)>0))
			   {
		          g_mInputStarNum=10* g_mInputStarNum+3; 
		       }
			   if((g_mInputStarNum<=258997)&&(g_mInputStarNum>0))
			   {			  
			     g_mSaoObjectNum= g_mInputStarNum;
			   }      
		 break;

		case  SYS_SUB2SUB9RA:
	case SYS_MENU_SKY_RA:
	  	    g_sysmenu2900ra[g_mShowMenucolumn-1]='3';//�ྭ����
			g_sysmenu2900raEn[g_mShowMenucolumn-1]='3';//�ྭ����
			FRaInputMoveRight();
	        break;
		case SYS_MENU_LAND_AZI:
	  	    g_sysmenu2900ra[g_mShowMenucolumn-1]='3';//�ྭ����
			g_sysmenu2900raEn[g_mShowMenucolumn-1]='3';//�ྭ����
			FDecInputMoveRight();
	        break;
	case SYS_SUB2SUB9DEC:
	case SYS_MENU_SKY_DEC:
	case SYS_MENU_LAND_ALT:
	  	     if(	g_mShowMenucolumn!=5)
			{
	  	       g_sysmenu2900dec[g_mShowMenucolumn-1]='3';//��γ��������
			   g_sysmenu2900decEn[g_mShowMenucolumn-1]='3';//��γ��������
			}
			else  if(g_sysmenu2900dec[g_mShowMenucolumn-1]=='+'	)
			{
			  g_sysmenu2900dec[g_mShowMenucolumn-1]='-';//��γ������
			  g_sysmenu2900decEn[g_mShowMenucolumn-1]='-';//��γ������
			}
			else
			{
		    	g_sysmenu2900dec[g_mShowMenucolumn-1]='+';//��γ������
				g_sysmenu2900decEn[g_mShowMenucolumn-1]='+';//��γ������
			}
			FDecInputMoveRight();
	        break;


      case SYS_MENU_SKY_NAME:	
	  case SYS_MENU_LAND_NAME:		
	        switch(g_keychar)
			{
			   case '3':
			        g_keychar='d';
			   break;
			    case 'd':
			         g_keychar='e';
			   break; 
			    case 'e':
			         g_keychar='f';
			   break;
			     case 'f':
			         g_keychar='D';
			   break;
			     case 'D':
			         g_keychar='E';
			   break;
			   case 'E':
			         g_keychar='F';
			   break;
			   case 'F':
			         g_keychar='3';
			   break;
			   default:
			       g_keychar='3' ;
			   break;
			}
		   g_sysmenu2900NameEn[g_mShowMenucolumn-1]=g_keychar;	 
		   break;


		case SYS_SUB4SUB8MENU4_RASPEED :
	     if(g_mShowMenucolumn!=1)
			{
	  	       g_sysmenu4800raspeed[g_mShowMenucolumn-1]='3';	
	           g_sysmenu4800raspeedEn[g_mShowMenucolumn-1]='3';
			}
			else  if(g_sysmenu4800raspeed[g_mShowMenucolumn-1]=='+'	)
			{
                g_sysmenu4800raspeed[g_mShowMenucolumn-1]='-';	
	            g_sysmenu4800raspeedEn[g_mShowMenucolumn-1]='-';
			}
			else
			{
		        g_sysmenu4800raspeed[g_mShowMenucolumn-1]='+';	
	            g_sysmenu4800raspeedEn[g_mShowMenucolumn-1]='+';

			}	
	   FRaTrackSpeedInputMoveRight() ;  //�Զ�������ٶ�����������
	break;
	  //ʱ��ʱ������
	case  SYS_SUB4SUB1_SETTIME:
		 
		 if(g_mdatetime==0)
		 {
		        g_sysmenu4100date[g_mShowMenucolumn-1]='3';	
		        g_sysmenu4100dateEn[g_mShowMenucolumn-1]='3';
		}
		else
		{ 
		   		g_sysmenu4100time[g_mShowMenucolumn-1]='3';	
		        g_sysmenu4100timeEn[g_mShowMenucolumn-1]='3';
		}
					
	    FDateTimeInputMoveRight() ;
	break;
		//�Զ���ص�����
	case SYS_SUB4SUB3_SETSITE : 
	 FSiteInput(3);
	break;
	 //��Զ���������
	case SYS_SUB4SUB7_TELAZIALT_ZERO:				  
		FTelZeroInput(3);
		break;
//**************************************

	case SYS_SUB3SUB4TIMER_INPUT:
	      g_sysmenu3402off[g_mShowMenucolumn-1]='3';
		  g_sysmenu3402offEn[g_mShowMenucolumn-1]='3';
		  FTimerInputMoveRight();
		  break;     
	case SYS_SUB3SUB5ALARM_INPUT:
	      g_sysmenu3500alarm_input[g_mShowMenucolumn-1]='3';
		  g_sysmenu3500alarm_inputEn[g_mShowMenucolumn-1]='3';
		  FAlarmInputMoveRight();
		  break; 
		case SYS_SUB3SUB6SUB2M_MF:
	case SYS_SUB3SUB6SUB2M_MF1:
		  g_sysmenu3602m_mf[g_mShowMenucolumn-1]='3';
		  g_sysmenu3602m_mfEn[g_mShowMenucolumn-1]='3';
		  FMfocusInputMoveRight();
		  break;
	case SYS_SUB3SUB6SUB2M_SF:
	case SYS_SUB3SUB6SUB2M_SF1:	 
	 	 g_sysmenu3602m_sf[g_mShowMenucolumn-1]='3';
		 g_sysmenu3602m_sfEn[g_mShowMenucolumn-1]='3';
		 FSfocusInputMoveRight();
		 break;
	case SYS_SUB3SUB6SUB2M_MFOV: 
		  g_sysmenu3602m_mfovEn[g_mShowMenucolumn-1]='3';
		 FSFovInputMoveRight();
		  break;
	case SYS_SUB2SUB11_SET:
		F_LandmarkInput(3);
		break;

//***************************************** 	
	default:
	break;
  }
}
//*******************************************************************


//*******************************************************************
//4�Ű���

void FKey4()
{

 switch(g_nsysstatus)
  {
	case SYS_MAINSHOW: //������Զ�����ֶ��ٶ�4��
		g_mHandSpeed=4;
		break;
	case SYS_F_SELFNUM:
	case SYS_MENU_SKY_OBJECT:
    case SYS_MENU_LAND_OBJECT:
		g_mFnum=4;
		break;
	case SYS_MAINHELP:
		g_mHandSpeed=4;//������Զ�����ֶ��ٶ�4��
		break;
	case SYS_SUB1SUB11RA_GEAR_ERROR_BEGIN: 	
	case SYS_SUB1SUB12DEC_GEAR_ERROR_BEGIN: 
	case SYS_SUB1SUB11RA_GEAR_ERROR_ALIGN: 	//��Զ��У׼ʱ���ֶ��ٶ�
	case SYS_SUB1SUB12DEC_GEAR_ERROR_ALIGN: 
	case SYS_SUB1SUB2STAR_ALIGN	:
		g_mHandSpeed=4;
		break;
	case SYS_SUB2MSR_OBJECT0: //messier�Ǳ���� 
	case SYS_SUB2MSR_OBJECT: 
		            LCDRfrsh();
			   if(((10* g_mInputStarNum+4)<=110)&&((10* g_mInputStarNum+4)>0))
			   {
		          g_mInputStarNum=10* g_mInputStarNum+4; 
		       }
			   if((g_mInputStarNum<=110)&&(g_mInputStarNum>0))
			   {			  
			     g_mMsrObjectNum= g_mInputStarNum;
			   }      
		 break;



	case SYS_SUB2NGC_OBJECT:   //ngc�Ǳ����
	 LCDRfrsh();
			   if(((10* g_mInputStarNum+4)<=7840)&&((10* g_mInputStarNum+4)>0))
			   {
		          g_mInputStarNum=10* g_mInputStarNum+4; 
		       }
			   if((g_mInputStarNum<=7840)&&(g_mInputStarNum>0))
			   {			  
			    g_mNgcObjectNum= g_mInputStarNum;
			   }      
		 break;

		case SYS_SUB2IC_OBJECT:  //ic�Ǳ����
		 LCDRfrsh();
			   if(((10* g_mInputStarNum+4)<=5386)&&((10* g_mInputStarNum+4)>0))
			   {
		          g_mInputStarNum=10* g_mInputStarNum+4; 
		       }
			   if((g_mInputStarNum<=5386)&&(g_mInputStarNum>0))
			   {			  
			     g_mIcObjectNum= g_mInputStarNum;
			   }      
		 break;
		 case SYS_SUB2SH2_OBJECT:  //sh2�Ǳ����
		 	        LCDRfrsh();
			   if(((10* g_mInputStarNum+4)<=313)&&((10* g_mInputStarNum+4)>0))
			   {
		          g_mInputStarNum=10* g_mInputStarNum+4; 
		       }
			   if((g_mInputStarNum<=313)&&(g_mInputStarNum>0))
			   {			  
			     g_mSh2ObjectNum= g_mInputStarNum;
			   }      
		 break;

		 case SYS_SUB2BRT_OBJECT:  //bright�Ǳ����
		 		 	 LCDRfrsh();
			   if(((10* g_mInputStarNum+4)<=167)&&((10* g_mInputStarNum+4)>0))
			   {
		          g_mInputStarNum=10* g_mInputStarNum+4; 
		       }
			   if((g_mInputStarNum<=167)&&(g_mInputStarNum>0))
			   {			  
			     g_mBrightObjectNum= g_mInputStarNum;
			   }      
		 break;
	
	     case SYS_SUB2SAO_OBJECT:  //sao�Ǳ����
		 	 	LCDRfrsh();
			   if(((10* g_mInputStarNum+4)<=258997)&&((10* g_mInputStarNum+4)>0))
			   {
		          g_mInputStarNum=10* g_mInputStarNum+4; 
		       }
			   if((g_mInputStarNum<=258997)&&(g_mInputStarNum>0))
			   {			  
			     g_mSaoObjectNum= g_mInputStarNum;
			   }      
		 break;


		case  SYS_SUB2SUB9RA:
	case SYS_MENU_SKY_RA:
	  	    g_sysmenu2900ra[g_mShowMenucolumn-1]='4';//�ྭ����
			g_sysmenu2900raEn[g_mShowMenucolumn-1]='4';//�ྭ����
			FRaInputMoveRight();
	        break;
		case SYS_MENU_LAND_AZI:
	  	    g_sysmenu2900ra[g_mShowMenucolumn-1]='4';//�ྭ����
			g_sysmenu2900raEn[g_mShowMenucolumn-1]='4';//�ྭ����
			FDecInputMoveRight();
	        break;
	case SYS_SUB2SUB9DEC:
	case SYS_MENU_SKY_DEC:
	case SYS_MENU_LAND_ALT:
	  	    if(	g_mShowMenucolumn!=5)
			{
	  	       g_sysmenu2900dec[g_mShowMenucolumn-1]='4';//��γ��������
			   g_sysmenu2900decEn[g_mShowMenucolumn-1]='4';//��γ��������
			}
			else  if(g_sysmenu2900dec[g_mShowMenucolumn-1]=='+'	)
			{
			  g_sysmenu2900dec[g_mShowMenucolumn-1]='-';//��γ������
			  g_sysmenu2900decEn[g_mShowMenucolumn-1]='-';//��γ������
			}
			else
			{
		    	g_sysmenu2900dec[g_mShowMenucolumn-1]='+';//��γ������
				g_sysmenu2900decEn[g_mShowMenucolumn-1]='+';//��γ������
			}
			FDecInputMoveRight();
	        break;
	  case SYS_MENU_SKY_NAME:	
	  case SYS_MENU_LAND_NAME:	
	        switch(g_keychar)
			{
			   case '4':
			        g_keychar='g';
			   break;
			    case 'g':
			         g_keychar='h';
			   break; 
			    case 'h':
			         g_keychar='i';
			   break;
			     case 'i':
			         g_keychar='G';
			   break;
			     case 'G':
			         g_keychar='H';
			   break;
			   case 'H':
			         g_keychar='I';
			   break;
			   case 'I':
			         g_keychar='4';
			   break;
			   default:
			       g_keychar='4' ;
			   break;
			}
		   g_sysmenu2900NameEn[g_mShowMenucolumn-1]=g_keychar;	 
		   break;
		case SYS_SUB4SUB8MENU4_RASPEED :
	     if(g_mShowMenucolumn!=1)
			{
	  	       g_sysmenu4800raspeed[g_mShowMenucolumn-1]='4';	
	           g_sysmenu4800raspeedEn[g_mShowMenucolumn-1]='4';
			}
			else  if(g_sysmenu4800raspeed[g_mShowMenucolumn-1]=='+'	)
			{
                g_sysmenu4800raspeed[g_mShowMenucolumn-1]='-';	
	            g_sysmenu4800raspeedEn[g_mShowMenucolumn-1]='-';
			}
			else
			{
		        g_sysmenu4800raspeed[g_mShowMenucolumn-1]='+';	
	            g_sysmenu4800raspeedEn[g_mShowMenucolumn-1]='+';

			}	
	   FRaTrackSpeedInputMoveRight() ;  //�Զ�������ٶ�����������
	break;
	  //ʱ��ʱ������
	case  SYS_SUB4SUB1_SETTIME:
		 
		 if(g_mdatetime==0)
		 {
		        g_sysmenu4100date[g_mShowMenucolumn-1]='4';	
		        g_sysmenu4100dateEn[g_mShowMenucolumn-1]='4';
		}
		else
		{ 
		   		g_sysmenu4100time[g_mShowMenucolumn-1]='4';	
		        g_sysmenu4100timeEn[g_mShowMenucolumn-1]='4';
		}
					
	    FDateTimeInputMoveRight() ;
	break;
		//�Զ���ص�����
	case SYS_SUB4SUB3_SETSITE : 
	 FSiteInput(4);
	break;
	 //��Զ���������
	case SYS_SUB4SUB7_TELAZIALT_ZERO:				  
		FTelZeroInput(4);
		break;
//********************************** 
	case SYS_SUB3SUB4TIMER_INPUT:
	      g_sysmenu3402off[g_mShowMenucolumn-1]='4';
		  g_sysmenu3402offEn[g_mShowMenucolumn-1]='4';
		  FTimerInputMoveRight();
		  break;    
	case SYS_SUB3SUB5ALARM_INPUT:
	      g_sysmenu3500alarm_input[g_mShowMenucolumn-1]='4';
		  g_sysmenu3500alarm_inputEn[g_mShowMenucolumn-1]='4';
		  FAlarmInputMoveRight();
		  break;  
	case SYS_SUB3SUB6SUB2M_MF:
	case SYS_SUB3SUB6SUB2M_MF1:
		  g_sysmenu3602m_mf[g_mShowMenucolumn-1]='4';
		  g_sysmenu3602m_mfEn[g_mShowMenucolumn-1]='4';
		  FMfocusInputMoveRight();
		  break;
	case SYS_SUB3SUB6SUB2M_SF:
	case SYS_SUB3SUB6SUB2M_SF1:	 
	 	 g_sysmenu3602m_sf[g_mShowMenucolumn-1]='4';
		 g_sysmenu3602m_sfEn[g_mShowMenucolumn-1]='4';
		 FSfocusInputMoveRight();
		 break;
	case SYS_SUB3SUB6SUB2M_MFOV: 
		  g_sysmenu3602m_mfovEn[g_mShowMenucolumn-1]='4';
		 FSFovInputMoveRight();
		  break;
	case SYS_SUB2SUB11_SET:
		F_LandmarkInput(4);
		break;
//****************************** 
	default:
	break;
  }
}
//*******************************************************************


//*******************************************************************
//5�Ű���

void FKey5()
{

 switch(g_nsysstatus)
  {
	case SYS_MAINSHOW: //������Զ�����ֶ��ٶ�5��
		g_mHandSpeed=5;
	break;
		case SYS_F_SELFNUM:
		case SYS_MENU_SKY_OBJECT:
    case SYS_MENU_LAND_OBJECT:
		g_mFnum=5;
		break;
	case SYS_MAINHELP:
		g_mHandSpeed=5;//������Զ�����ֶ��ٶ�5��
		break;
	case SYS_SUB1SUB11RA_GEAR_ERROR_BEGIN: 	
	case SYS_SUB1SUB12DEC_GEAR_ERROR_BEGIN: 
    case SYS_SUB1SUB11RA_GEAR_ERROR_ALIGN: 	//��Զ��У׼ʱ���ֶ��ٶ�
	case SYS_SUB1SUB12DEC_GEAR_ERROR_ALIGN: 
	case SYS_SUB1SUB2STAR_ALIGN	:
		g_mHandSpeed=5;
		break;
	case SYS_SUB2MSR_OBJECT0: //messier�Ǳ���� 
	case SYS_SUB2MSR_OBJECT: 
		            LCDRfrsh();
			   if(((10* g_mInputStarNum+5)<=110)&&((10* g_mInputStarNum+5)>0))
			   {
		          g_mInputStarNum=10* g_mInputStarNum+5; 
		       }
			   if((g_mInputStarNum<=110)&&(g_mInputStarNum>0))
			   {			  
			     g_mMsrObjectNum= g_mInputStarNum;
			   }      
		 break;



	case SYS_SUB2NGC_OBJECT:   //ngc�Ǳ����
	 LCDRfrsh();
			   if(((10* g_mInputStarNum+5)<=7840)&&((10* g_mInputStarNum+5)>0))
			   {
		          g_mInputStarNum=10* g_mInputStarNum+5; 
		       }
			   if((g_mInputStarNum<=7840)&&(g_mInputStarNum>0))
			   {			  
			    g_mNgcObjectNum= g_mInputStarNum;
			   }      
		 break;

		case SYS_SUB2IC_OBJECT:  //ic�Ǳ����
		 LCDRfrsh();
			   if(((10* g_mInputStarNum+5)<=5386)&&((10* g_mInputStarNum+5)>0))
			   {
		          g_mInputStarNum=10* g_mInputStarNum+5; 
		       }
			   if((g_mInputStarNum<=5386)&&(g_mInputStarNum>0))
			   {			  
			     g_mIcObjectNum= g_mInputStarNum;
			   }      
		 break;
		 case SYS_SUB2SH2_OBJECT:  //sh2�Ǳ����
		 	        LCDRfrsh();
			   if(((10* g_mInputStarNum+5)<=313)&&((10* g_mInputStarNum+5)>0))
			   {
		          g_mInputStarNum=10* g_mInputStarNum+5; 
		       }
			   if((g_mInputStarNum<=313)&&(g_mInputStarNum>0))
			   {			  
			     g_mSh2ObjectNum= g_mInputStarNum;
			   }      
		 break;

		 case SYS_SUB2BRT_OBJECT:  //bright�Ǳ����
		 		 	 LCDRfrsh();
			   if(((10* g_mInputStarNum+5)<=167)&&((10* g_mInputStarNum+5)>0))
			   {
		          g_mInputStarNum=10* g_mInputStarNum+5; 
		       }
			   if((g_mInputStarNum<=167)&&(g_mInputStarNum>0))
			   {			  
			     g_mBrightObjectNum= g_mInputStarNum;
			   }      
		 break;
	
	     case SYS_SUB2SAO_OBJECT:  //sao�Ǳ����
		 	 	LCDRfrsh();
			   if(((10* g_mInputStarNum+5)<=258997)&&((10* g_mInputStarNum+5)>0))
			   {
		          g_mInputStarNum=10* g_mInputStarNum+5; 
		       }
			   if((g_mInputStarNum<=258997)&&(g_mInputStarNum>0))
			   {			  
			     g_mSaoObjectNum= g_mInputStarNum;
			   }      
		 break;


	case  SYS_SUB2SUB9RA:
	case SYS_MENU_SKY_RA:
	  	    g_sysmenu2900ra[g_mShowMenucolumn-1]='5';//�ྭ����
			g_sysmenu2900raEn[g_mShowMenucolumn-1]='5';//�ྭ����
			FRaInputMoveRight();
	        break;
		case SYS_MENU_LAND_AZI:
	  	    g_sysmenu2900ra[g_mShowMenucolumn-1]='5';//�ྭ����
			g_sysmenu2900raEn[g_mShowMenucolumn-1]='5';//�ྭ����
			FDecInputMoveRight();
	        break;
	case SYS_SUB2SUB9DEC:
	case SYS_MENU_SKY_DEC:
	case SYS_MENU_LAND_ALT:
	  	     if(	g_mShowMenucolumn!=5)
			{
	  	       g_sysmenu2900dec[g_mShowMenucolumn-1]='5';//��γ��������
			   g_sysmenu2900decEn[g_mShowMenucolumn-1]='5';//��γ��������
			}
			else  if(g_sysmenu2900dec[g_mShowMenucolumn-1]=='+'	)
			{
			  g_sysmenu2900dec[g_mShowMenucolumn-1]='-';//��γ������
			  g_sysmenu2900decEn[g_mShowMenucolumn-1]='-';//��γ������
			}
			else
			{
		    	g_sysmenu2900dec[g_mShowMenucolumn-1]='+';//��γ������
				g_sysmenu2900decEn[g_mShowMenucolumn-1]='+';//��γ������
			}
			FDecInputMoveRight();
	        break;
		case SYS_MENU_SKY_NAME:	
	   case SYS_MENU_LAND_NAME:	
	        switch(g_keychar)
			{
			   case '5':
			        g_keychar='j';
			   break;
			    case 'j':
			         g_keychar='k';
			   break; 
			    case 'k':
			         g_keychar='l';
			   break;
			     case 'l':
			         g_keychar='J';
			   break;
			     case 'J':
			         g_keychar='K';
			   break;
			   case 'K':
			         g_keychar='L';
			   break;
			   case 'L':
			         g_keychar='5';
			   break;
			   default:
			       g_keychar='5' ;
			   break;
			}
		   g_sysmenu2900NameEn[g_mShowMenucolumn-1]=g_keychar;	 
		   break;
		case SYS_SUB4SUB8MENU4_RASPEED :
	     if(g_mShowMenucolumn!=1)
			{
	  	       g_sysmenu4800raspeed[g_mShowMenucolumn-1]='5';	
	           g_sysmenu4800raspeedEn[g_mShowMenucolumn-1]='5';
			}
			else  if(g_sysmenu4800raspeed[g_mShowMenucolumn-1]=='+'	)
			{
                g_sysmenu4800raspeed[g_mShowMenucolumn-1]='-';	
	            g_sysmenu4800raspeedEn[g_mShowMenucolumn-1]='-';
			}
			else
			{
		        g_sysmenu4800raspeed[g_mShowMenucolumn-1]='+';	
	            g_sysmenu4800raspeedEn[g_mShowMenucolumn-1]='+';

			}	
	   FRaTrackSpeedInputMoveRight() ;  //�Զ�������ٶ�����������
	break;
	  //ʱ��ʱ������
	case  SYS_SUB4SUB1_SETTIME:
		 
		 if(g_mdatetime==0)
		 {
		        g_sysmenu4100date[g_mShowMenucolumn-1]='5';	
		        g_sysmenu4100dateEn[g_mShowMenucolumn-1]='5';
		}
		else
		{ 
		   		g_sysmenu4100time[g_mShowMenucolumn-1]='5';	
		        g_sysmenu4100timeEn[g_mShowMenucolumn-1]='5';
		}
					
	    FDateTimeInputMoveRight() ;
	break;
		//�Զ���ص�����
	case SYS_SUB4SUB3_SETSITE : 
	 FSiteInput(5);
	break;
	 //��Զ���������
	case SYS_SUB4SUB7_TELAZIALT_ZERO:				  
		FTelZeroInput(5);
		break;
//****************************** 
	case SYS_SUB3SUB4TIMER_INPUT:
	      g_sysmenu3402off[g_mShowMenucolumn-1]='5';
		  g_sysmenu3402offEn[g_mShowMenucolumn-1]='5';
		  FTimerInputMoveRight();
		  break;     
	case SYS_SUB3SUB5ALARM_INPUT:
	      g_sysmenu3500alarm_input[g_mShowMenucolumn-1]='5';
		  g_sysmenu3500alarm_inputEn[g_mShowMenucolumn-1]='5';
		  FAlarmInputMoveRight();
		  break; 
		case SYS_SUB3SUB6SUB2M_MF:
	case SYS_SUB3SUB6SUB2M_MF1:
		  g_sysmenu3602m_mf[g_mShowMenucolumn-1]='5';
		  g_sysmenu3602m_mfEn[g_mShowMenucolumn-1]='5';
		  FMfocusInputMoveRight();
		  break;
	case SYS_SUB3SUB6SUB2M_SF:
	case SYS_SUB3SUB6SUB2M_SF1:	 
	 	 g_sysmenu3602m_sf[g_mShowMenucolumn-1]='5';
		 g_sysmenu3602m_sfEn[g_mShowMenucolumn-1]='5';
		 FSfocusInputMoveRight();
		 break;
	case SYS_SUB3SUB6SUB2M_MFOV: 
		  g_sysmenu3602m_mfovEn[g_mShowMenucolumn-1]='5';
		  FSFovInputMoveRight();
		  break;
	case SYS_SUB2SUB11_SET:
		F_LandmarkInput(5);
		break;

//********************************** 
	default:
	break;
  }
}
//*******************************************************************


//*******************************************************************
//6�Ű���
void FKey6 ()
{

 switch(g_nsysstatus)
  {
	case SYS_MAINSHOW: //������Զ�����ֶ��ٶ�6��
		g_mHandSpeed=6;
		break;
		case SYS_F_SELFNUM:
		case SYS_MENU_SKY_OBJECT:
    case SYS_MENU_LAND_OBJECT:
		g_mFnum=6;
		break;
	case SYS_MAINHELP:
		g_mHandSpeed=6;//������Զ�����ֶ��ٶ�6��
		break;
	case SYS_SUB1SUB11RA_GEAR_ERROR_BEGIN: 	
	case SYS_SUB1SUB12DEC_GEAR_ERROR_BEGIN: 
   case SYS_SUB1SUB11RA_GEAR_ERROR_ALIGN: 	//��Զ��У׼ʱ���ֶ��ٶ�
   case SYS_SUB1SUB12DEC_GEAR_ERROR_ALIGN: 
   case SYS_SUB1SUB2STAR_ALIGN	:
		g_mHandSpeed=6;
		break;

    	case SYS_SUB2MSR_OBJECT0: //messier�Ǳ���� 
	    case SYS_SUB2MSR_OBJECT: 
			            LCDRfrsh();
			   if(((10* g_mInputStarNum+6)<=110)&&((10* g_mInputStarNum+6)>0))
			   {
		          g_mInputStarNum=10* g_mInputStarNum+6; 
		       }
			   if((g_mInputStarNum<=110)&&(g_mInputStarNum>0))
			   {			  
			     g_mMsrObjectNum= g_mInputStarNum;
			   }      
		 break;

	case SYS_SUB2NGC_OBJECT:   //ngc�Ǳ����
	 LCDRfrsh();
			   if(((10* g_mInputStarNum+6)<=7840)&&((10* g_mInputStarNum+6)>0))
			   {
		          g_mInputStarNum=10* g_mInputStarNum+6; 
		       }
			   if((g_mInputStarNum<=7840)&&(g_mInputStarNum>0))
			   {			  
			    g_mNgcObjectNum= g_mInputStarNum;
			   }      
		 break;

		case SYS_SUB2IC_OBJECT:  //ic�Ǳ����
		 LCDRfrsh();
			   if(((10* g_mInputStarNum+6)<=5386)&&((10* g_mInputStarNum+6)>0))
			   {
		          g_mInputStarNum=10* g_mInputStarNum+6; 
		       }
			   if((g_mInputStarNum<=5386)&&(g_mInputStarNum>0))
			   {			  
			     g_mIcObjectNum= g_mInputStarNum;
			   }      
		 break;
		 case SYS_SUB2SH2_OBJECT:  //sh2�Ǳ����
		 	        LCDRfrsh();
			   if(((10* g_mInputStarNum+6)<=313)&&((10* g_mInputStarNum+6)>0))
			   {
		          g_mInputStarNum=10* g_mInputStarNum+6; 
		       }
			   if((g_mInputStarNum<=313)&&(g_mInputStarNum>0))
			   {			  
			     g_mSh2ObjectNum= g_mInputStarNum;
			   }      
		 break;

		 case SYS_SUB2BRT_OBJECT:  //bright�Ǳ����
		 		 	 LCDRfrsh();
			   if(((10* g_mInputStarNum+6)<=167)&&((10* g_mInputStarNum+6)>0))
			   {
		          g_mInputStarNum=10* g_mInputStarNum+6; 
		       }
			   if((g_mInputStarNum<=167)&&(g_mInputStarNum>0))
			   {			  
			     g_mBrightObjectNum= g_mInputStarNum;
			   }      
		 break;
	
	     case SYS_SUB2SAO_OBJECT:  //sao�Ǳ����
		 	 	LCDRfrsh();
			   if(((10* g_mInputStarNum+6)<=258997)&&((10* g_mInputStarNum+6)>0))
			   {
		          g_mInputStarNum=10* g_mInputStarNum+6; 
		       }
			   if((g_mInputStarNum<=258997)&&(g_mInputStarNum>0))
			   {			  
			     g_mSaoObjectNum= g_mInputStarNum;
			   }      
		 break;

	case  SYS_SUB2SUB9RA:
	case SYS_MENU_SKY_RA:
	  	    g_sysmenu2900ra[g_mShowMenucolumn-1]='6';//�ྭ����
			g_sysmenu2900raEn[g_mShowMenucolumn-1]='6';//�ྭ����
			FRaInputMoveRight();
	        break;
	case SYS_MENU_LAND_AZI:
	  	    g_sysmenu2900ra[g_mShowMenucolumn-1]='6';//�ྭ����
			g_sysmenu2900raEn[g_mShowMenucolumn-1]='6';//�ྭ����
			FDecInputMoveRight();
	        break;
	case SYS_SUB2SUB9DEC:
	case SYS_MENU_SKY_DEC:
	case SYS_MENU_LAND_ALT:
	  	    if(	g_mShowMenucolumn!=5)
			{
	  	       g_sysmenu2900dec[g_mShowMenucolumn-1]='6';//��γ��������
			   g_sysmenu2900decEn[g_mShowMenucolumn-1]='6';//��γ��������
			}
			else  if(g_sysmenu2900dec[g_mShowMenucolumn-1]=='+'	)
			{
			  g_sysmenu2900dec[g_mShowMenucolumn-1]='-';//��γ������
			  g_sysmenu2900decEn[g_mShowMenucolumn-1]='-';//��γ������
			}
			else
			{
		    	g_sysmenu2900dec[g_mShowMenucolumn-1]='+';//��γ������
				g_sysmenu2900decEn[g_mShowMenucolumn-1]='+';//��γ������
			}
			FDecInputMoveRight();
	        break;
	  	case SYS_MENU_SKY_NAME:	
	     case SYS_MENU_LAND_NAME:	
	        switch(g_keychar)
			{
			   case '6':
			        g_keychar='m';
			   break;
			    case 'm':
			         g_keychar='n';
			   break; 
			    case 'n':
			         g_keychar='o';
			   break;
			     case 'o':
			         g_keychar='M';
			   break;
			     case 'M':
			         g_keychar='N';
			   break;
			   case 'N':
			         g_keychar='O';
			   break;
			   case 'O':
			         g_keychar='6';
			   break;
			   default:
			       g_keychar='6' ;
			   break;
			}
		   g_sysmenu2900NameEn[g_mShowMenucolumn-1]=g_keychar;	 
		   break;

		case SYS_SUB4SUB8MENU4_RASPEED :
	     if(g_mShowMenucolumn!=1)
			{
	  	       g_sysmenu4800raspeed[g_mShowMenucolumn-1]='6';	
	           g_sysmenu4800raspeedEn[g_mShowMenucolumn-1]='6';
			}
			else  if(g_sysmenu4800raspeed[g_mShowMenucolumn-1]=='+'	)
			{
                g_sysmenu4800raspeed[g_mShowMenucolumn-1]='-';	
	            g_sysmenu4800raspeedEn[g_mShowMenucolumn-1]='-';
			}
			else
			{
		        g_sysmenu4800raspeed[g_mShowMenucolumn-1]='+';	
	            g_sysmenu4800raspeedEn[g_mShowMenucolumn-1]='+';

			}	
	   FRaTrackSpeedInputMoveRight() ;  //�Զ�������ٶ�����������
	break;
	  //ʱ��ʱ������
	case  SYS_SUB4SUB1_SETTIME:
		 
		 if(g_mdatetime==0)
		 {
		        g_sysmenu4100date[g_mShowMenucolumn-1]='6';	
		        g_sysmenu4100dateEn[g_mShowMenucolumn-1]='6';
		}
		else
		{ 
		   		g_sysmenu4100time[g_mShowMenucolumn-1]='6';	
		        g_sysmenu4100timeEn[g_mShowMenucolumn-1]='6';
		}
					
	    FDateTimeInputMoveRight() ;
	break;
		//�Զ���ص�����
	case SYS_SUB4SUB3_SETSITE : 
	 FSiteInput(6);
	break;
	 //��Զ���������
	case SYS_SUB4SUB7_TELAZIALT_ZERO:				  
		FTelZeroInput(6);
		break;
//******************************* 
	case SYS_SUB3SUB4TIMER_INPUT:
	      g_sysmenu3402off[g_mShowMenucolumn-1]='6';
		  g_sysmenu3402offEn[g_mShowMenucolumn-1]='6';
		  FTimerInputMoveRight();
		  break; 
	case SYS_SUB3SUB5ALARM_INPUT:
	      g_sysmenu3500alarm_input[g_mShowMenucolumn-1]='6';
		  g_sysmenu3500alarm_inputEn[g_mShowMenucolumn-1]='6';
		  FAlarmInputMoveRight();
		  break;        
		case SYS_SUB3SUB6SUB2M_MF:
	case SYS_SUB3SUB6SUB2M_MF1:
		  g_sysmenu3602m_mf[g_mShowMenucolumn-1]='6';
		  g_sysmenu3602m_mfEn[g_mShowMenucolumn-1]='6';
		  FMfocusInputMoveRight();
		  break;
	case SYS_SUB3SUB6SUB2M_SF:
	case SYS_SUB3SUB6SUB2M_SF1:	 
	 	 g_sysmenu3602m_sf[g_mShowMenucolumn-1]='6';
		 g_sysmenu3602m_sfEn[g_mShowMenucolumn-1]='6';
		 FSfocusInputMoveRight();
		 break;
	case SYS_SUB3SUB6SUB2M_MFOV: 
		  g_sysmenu3602m_mfovEn[g_mShowMenucolumn-1]='6';
		 FSFovInputMoveRight();
		  break;
	case SYS_SUB2SUB11_SET:
		F_LandmarkInput(6);
		break;

//********************************** 
	default:
	break;
  }
}
//*******************************************************************


//*******************************************************************
//7�Ű���

void FKey7()
{

 switch(g_nsysstatus)
  {
	case SYS_MAINSHOW: //������Զ�����ֶ��ٶ�7��
		g_mHandSpeed=7;
		break;
		case SYS_F_SELFNUM:
		case SYS_MENU_SKY_OBJECT:
    case SYS_MENU_LAND_OBJECT:
		g_mFnum=7;
		break;
	case SYS_MAINHELP:
		g_mHandSpeed=7;//������Զ�����ֶ��ٶ�7��
		break;
	case SYS_SUB1SUB11RA_GEAR_ERROR_BEGIN: 	
	case SYS_SUB1SUB12DEC_GEAR_ERROR_BEGIN: 
	case SYS_SUB1SUB11RA_GEAR_ERROR_ALIGN: 	//��Զ��У׼ʱ���ֶ��ٶ�
	case SYS_SUB1SUB12DEC_GEAR_ERROR_ALIGN: 
	case SYS_SUB1SUB2STAR_ALIGN	:
		g_mHandSpeed=7;
		break;

	case SYS_SUB2MSR_OBJECT0: //messier�Ǳ���� 
	case SYS_SUB2MSR_OBJECT: 
		            LCDRfrsh();
			   if(((10* g_mInputStarNum+7)<=110)&&((10* g_mInputStarNum+7)>0))
			   {
		          g_mInputStarNum=10* g_mInputStarNum+7; 
		       }
			   if((g_mInputStarNum<=110)&&(g_mInputStarNum>0))
			   {			  
			     g_mMsrObjectNum= g_mInputStarNum;
			   }      
		 break;

	case SYS_SUB2NGC_OBJECT:   //ngc�Ǳ����
	 LCDRfrsh();
			   if(((10* g_mInputStarNum+7)<=7840)&&((10* g_mInputStarNum+7)>0))
			   {
		          g_mInputStarNum=10* g_mInputStarNum+7; 
		       }
			   if((g_mInputStarNum<=7840)&&(g_mInputStarNum>0))
			   {			  
			    g_mNgcObjectNum= g_mInputStarNum;
			   }      
		 break;

		case SYS_SUB2IC_OBJECT:  //ic�Ǳ����
		 LCDRfrsh();
			   if(((10* g_mInputStarNum+7)<=5386)&&((10* g_mInputStarNum+7)>0))
			   {
		          g_mInputStarNum=10* g_mInputStarNum+7; 
		       }
			   if((g_mInputStarNum<=5386)&&(g_mInputStarNum>0))
			   {			  
			     g_mIcObjectNum= g_mInputStarNum;
			   }      
		 break;
		 case SYS_SUB2SH2_OBJECT:  //sh2�Ǳ����
		 	        LCDRfrsh();
			   if(((10* g_mInputStarNum+7)<=313)&&((10* g_mInputStarNum+7)>0))
			   {
		          g_mInputStarNum=10* g_mInputStarNum+7; 
		       }
			   if((g_mInputStarNum<=313)&&(g_mInputStarNum>0))
			   {			  
			     g_mSh2ObjectNum= g_mInputStarNum;
			   }      
		 break;

		 case SYS_SUB2BRT_OBJECT:  //bright�Ǳ����
		 		 	 LCDRfrsh();
			   if(((10* g_mInputStarNum+7)<=167)&&((10* g_mInputStarNum+7)>0))
			   {
		          g_mInputStarNum=10* g_mInputStarNum+7; 
		       }
			   if((g_mInputStarNum<=167)&&(g_mInputStarNum>0))
			   {			  
			     g_mBrightObjectNum= g_mInputStarNum;
			   }      
		 break;
	
	     case SYS_SUB2SAO_OBJECT:  //sao�Ǳ����
		 	 	LCDRfrsh();
			   if(((10* g_mInputStarNum+7)<=258997)&&((10* g_mInputStarNum+7)>0))
			   {
		          g_mInputStarNum=10* g_mInputStarNum+7; 
		       }
			   if((g_mInputStarNum<=258997)&&(g_mInputStarNum>0))
			   {			  
			     g_mSaoObjectNum= g_mInputStarNum;
			   }      
		 break;

	case  SYS_SUB2SUB9RA:
	case SYS_MENU_SKY_RA:
	  	    g_sysmenu2900ra[g_mShowMenucolumn-1]='7';//�ྭ����
			g_sysmenu2900raEn[g_mShowMenucolumn-1]='7';//�ྭ����
			FRaInputMoveRight();
	        break;
	case SYS_MENU_LAND_AZI:
	  	    g_sysmenu2900ra[g_mShowMenucolumn-1]='7';//�ྭ����
			g_sysmenu2900raEn[g_mShowMenucolumn-1]='7';//�ྭ����
			FDecInputMoveRight();
	        break;
	case SYS_SUB2SUB9DEC:
	case SYS_MENU_SKY_DEC:
	case SYS_MENU_LAND_ALT:
	  	     if(	g_mShowMenucolumn!=5)
			{
	  	       g_sysmenu2900dec[g_mShowMenucolumn-1]='7';//��γ��������
			   g_sysmenu2900decEn[g_mShowMenucolumn-1]='7';//��γ��������
			}
			else  if(g_sysmenu2900dec[g_mShowMenucolumn-1]=='+'	)
			{
			  g_sysmenu2900dec[g_mShowMenucolumn-1]='-';//��γ������
			  g_sysmenu2900decEn[g_mShowMenucolumn-1]='-';//��γ������
			}
			else
			{
		    	g_sysmenu2900dec[g_mShowMenucolumn-1]='-';//��γ������
				g_sysmenu2900decEn[g_mShowMenucolumn-1]='-';//��γ������
			}
			FDecInputMoveRight();
	        break;


    	case SYS_MENU_SKY_NAME:	
	  case SYS_MENU_LAND_NAME:		
	        switch(g_keychar)
			{
			   case '7':
			        g_keychar='p';
			   break;
			    case 'p':
			         g_keychar='q';
			   break; 
			    case 'q':
			         g_keychar='r';
			   break;
			    case 'r':
			         g_keychar='s';
			   break;
			     case 's':
			         g_keychar='P';
			   break;
			     case 'P':
			         g_keychar='Q';
			   break;
			   case 'Q':
			         g_keychar='R';
			   break;
			   case 'R':
			         g_keychar='S';
			   break;
			   case 'S':
			         g_keychar='7';
			   break;
			   default:
			       g_keychar='7' ;
			   break;
			}
		   g_sysmenu2900NameEn[g_mShowMenucolumn-1]=g_keychar;	 
		   break;

		case SYS_SUB4SUB8MENU4_RASPEED :
	     if(g_mShowMenucolumn!=1)
			{
	  	       g_sysmenu4800raspeed[g_mShowMenucolumn-1]='7';	
	           g_sysmenu4800raspeedEn[g_mShowMenucolumn-1]='7';
			}
			else  if(g_sysmenu4800raspeed[g_mShowMenucolumn-1]=='+'	)
			{
                g_sysmenu4800raspeed[g_mShowMenucolumn-1]='-';	
	            g_sysmenu4800raspeedEn[g_mShowMenucolumn-1]='-';
			}
			else
			{
		        g_sysmenu4800raspeed[g_mShowMenucolumn-1]='+';	
	            g_sysmenu4800raspeedEn[g_mShowMenucolumn-1]='+';

			}	
	   FRaTrackSpeedInputMoveRight() ;  //�Զ�������ٶ�����������
	break;
	  //ʱ��ʱ������
	case  SYS_SUB4SUB1_SETTIME:
		 
		 if(g_mdatetime==0)
		 {
		        g_sysmenu4100date[g_mShowMenucolumn-1]='7';	
		        g_sysmenu4100dateEn[g_mShowMenucolumn-1]='7';
		}
		else
		{ 
		   		g_sysmenu4100time[g_mShowMenucolumn-1]='7';	
		        g_sysmenu4100timeEn[g_mShowMenucolumn-1]='7';
		}
					
	    FDateTimeInputMoveRight() ;
	break;
		//�Զ���ص�����
	case SYS_SUB4SUB3_SETSITE : 
	 FSiteInput(7);
	break;
	 //��Զ���������
	case SYS_SUB4SUB7_TELAZIALT_ZERO:				  
		FTelZeroInput(7);
		break;
//******************************** 
	case SYS_SUB3SUB4TIMER_INPUT:
	      g_sysmenu3402off[g_mShowMenucolumn-1]='7';
		  g_sysmenu3402offEn[g_mShowMenucolumn-1]='7';
		  FTimerInputMoveRight();
		  break;    
	case SYS_SUB3SUB5ALARM_INPUT:
	      g_sysmenu3500alarm_input[g_mShowMenucolumn-1]='7';
		  g_sysmenu3500alarm_inputEn[g_mShowMenucolumn-1]='7';
		  FAlarmInputMoveRight();
		  break;  
		case SYS_SUB3SUB6SUB2M_MF:
	case SYS_SUB3SUB6SUB2M_MF1:
		  g_sysmenu3602m_mf[g_mShowMenucolumn-1]='7';
		  g_sysmenu3602m_mfEn[g_mShowMenucolumn-1]='7';
		  FMfocusInputMoveRight();
		  break;
	case SYS_SUB3SUB6SUB2M_SF:
	case SYS_SUB3SUB6SUB2M_SF1:	 
	 	 g_sysmenu3602m_sf[g_mShowMenucolumn-1]='7';
		 g_sysmenu3602m_sfEn[g_mShowMenucolumn-1]='7';
		 FSfocusInputMoveRight();
		 break;
	case SYS_SUB3SUB6SUB2M_MFOV: 
		  g_sysmenu3602m_mfovEn[g_mShowMenucolumn-1]='7';
		 FSFovInputMoveRight();
		  break;
	case SYS_SUB2SUB11_SET:
		F_LandmarkInput(7);
		break;

//*************************************** 
	default:
	break;
  }
}

//*******************************************************************


//*******************************************************************
//8�Ű���
void FKey8()
{

 switch(g_nsysstatus)
  {
	case SYS_MAINSHOW: //������Զ�����ֶ��ٶ�8��
		g_mHandSpeed=8;
		break;
		case SYS_F_SELFNUM:
		case SYS_MENU_SKY_OBJECT:
    case SYS_MENU_LAND_OBJECT:
		g_mFnum=8;
		break;
	case SYS_MAINHELP:
		g_mHandSpeed=8;//������Զ�����ֶ��ٶ�8��
		break;
	case SYS_SUB1SUB11RA_GEAR_ERROR_BEGIN: 	
	case SYS_SUB1SUB12DEC_GEAR_ERROR_BEGIN: 
	case SYS_SUB1SUB11RA_GEAR_ERROR_ALIGN: 	//��Զ��У׼ʱ���ֶ��ٶ�
	case SYS_SUB1SUB12DEC_GEAR_ERROR_ALIGN: 
	case SYS_SUB1SUB2STAR_ALIGN	:
		g_mHandSpeed=8;
		break;

	case SYS_SUB2MSR_OBJECT0: //messier�Ǳ���� 
	case SYS_SUB2MSR_OBJECT: 
		            LCDRfrsh();
			   if(((10* g_mInputStarNum+8)<=110)&&((10* g_mInputStarNum+8)>0))
			   {
		          g_mInputStarNum=10* g_mInputStarNum+8; 
		       }
			   if((g_mInputStarNum<=110)&&(g_mInputStarNum>0))
			   {			  
			     g_mMsrObjectNum= g_mInputStarNum;
			   }      
		 break;



	case SYS_SUB2NGC_OBJECT:   //ngc�Ǳ����
	 LCDRfrsh();
			   if(((10* g_mInputStarNum+8)<=7840)&&((10* g_mInputStarNum+8)>0))
			   {
		          g_mInputStarNum=10* g_mInputStarNum+8; 
		       }
			   if((g_mInputStarNum<=7840)&&(g_mInputStarNum>0))
			   {			  
			    g_mNgcObjectNum= g_mInputStarNum;
			   }      
		 break;

		case SYS_SUB2IC_OBJECT:  //ic�Ǳ����
		 LCDRfrsh();
			   if(((10* g_mInputStarNum+8)<=5386)&&((10* g_mInputStarNum+8)>0))
			   {
		          g_mInputStarNum=10* g_mInputStarNum+8; 
		       }
			   if((g_mInputStarNum<=5386)&&(g_mInputStarNum>0))
			   {			  
			     g_mIcObjectNum= g_mInputStarNum;
			   }      
		 break;
		 case SYS_SUB2SH2_OBJECT:  //sh2�Ǳ����
		 	        LCDRfrsh();
			   if(((10* g_mInputStarNum+8)<=313)&&((10* g_mInputStarNum+8)>0))
			   {
		          g_mInputStarNum=10* g_mInputStarNum+8; 
		       }
			   if((g_mInputStarNum<=313)&&(g_mInputStarNum>0))
			   {			  
			     g_mSh2ObjectNum= g_mInputStarNum;
			   }      
		 break;

		 case SYS_SUB2BRT_OBJECT:  //bright�Ǳ����
		 		 	 LCDRfrsh();
			   if(((10* g_mInputStarNum+8)<=167)&&((10* g_mInputStarNum+8)>0))
			   {
		          g_mInputStarNum=10* g_mInputStarNum+8; 
		       }
			   if((g_mInputStarNum<=167)&&(g_mInputStarNum>0))
			   {			  
			     g_mBrightObjectNum= g_mInputStarNum;
			   }      
		 break;
	
	     case SYS_SUB2SAO_OBJECT:  //sao�Ǳ����
		 	 	LCDRfrsh();
			   if(((10* g_mInputStarNum+8)<=258997)&&((10* g_mInputStarNum+8)>0))
			   {
		          g_mInputStarNum=10* g_mInputStarNum+8; 
		       }
			   if((g_mInputStarNum<=258997)&&(g_mInputStarNum>0))
			   {			  
			     g_mSaoObjectNum= g_mInputStarNum;
			   }      
		 break;

		case  SYS_SUB2SUB9RA:
	case SYS_MENU_SKY_RA:
	  	    g_sysmenu2900ra[g_mShowMenucolumn-1]='8';//�ྭ����
			g_sysmenu2900raEn[g_mShowMenucolumn-1]='8';//�ྭ����
			FRaInputMoveRight();
	        break;
		case SYS_MENU_LAND_AZI:
	  	    g_sysmenu2900ra[g_mShowMenucolumn-1]='8';//�ྭ����
			g_sysmenu2900raEn[g_mShowMenucolumn-1]='8';//�ྭ����
			FDecInputMoveRight();
	        break;
	case SYS_SUB2SUB9DEC:
	case SYS_MENU_SKY_DEC:
	case SYS_MENU_LAND_ALT:
	  	    if(	g_mShowMenucolumn!=5)
			{
	  	       g_sysmenu2900dec[g_mShowMenucolumn-1]='8';//��γ��������
			   g_sysmenu2900decEn[g_mShowMenucolumn-1]='8';//��γ��������
			}
			else  if(g_sysmenu2900dec[g_mShowMenucolumn-1]=='+'	)
			{
			  g_sysmenu2900dec[g_mShowMenucolumn-1]='-';//��γ������
			  g_sysmenu2900decEn[g_mShowMenucolumn-1]='-';//��γ������
			}
			else
			{
		    	g_sysmenu2900dec[g_mShowMenucolumn-1]='+';//��γ������
				g_sysmenu2900decEn[g_mShowMenucolumn-1]='+';//��γ������
			}
			FDecInputMoveRight();
	        break;
		case SYS_MENU_SKY_NAME:	
	    case SYS_MENU_LAND_NAME:		
	        switch(g_keychar)
			{
			   case '8':
			        g_keychar='	t';
			   break;
			    case 't':
			         g_keychar='u';
			   break; 
			    case 'u':
			         g_keychar='v';
			   break;
			     case 'v':
			         g_keychar='T';
			   break;
			     case 'T':
			         g_keychar='U';
			   break;
			   case 'U':
			         g_keychar='V';
			   break;
			   case 'V':
			         g_keychar='8';
			   break;
			   default:
			       g_keychar='8' ;
			   break;
			}
		   g_sysmenu2900NameEn[g_mShowMenucolumn-1]=g_keychar;	 
		   break;

	case SYS_SUB4SUB8MENU4_RASPEED :
	     if(g_mShowMenucolumn!=1)
			{
	  	       g_sysmenu4800raspeed[g_mShowMenucolumn-1]='8';	
	           g_sysmenu4800raspeedEn[g_mShowMenucolumn-1]='8';
			}
			else  if(g_sysmenu4800raspeed[g_mShowMenucolumn-1]=='+'	)
			{
                g_sysmenu4800raspeed[g_mShowMenucolumn-1]='-';	
	            g_sysmenu4800raspeedEn[g_mShowMenucolumn-1]='-';
			}
			else
			{
		        g_sysmenu4800raspeed[g_mShowMenucolumn-1]='+';	
	            g_sysmenu4800raspeedEn[g_mShowMenucolumn-1]='+';

			}	
	   FRaTrackSpeedInputMoveRight() ;  //�Զ�������ٶ�����������
	break;
	  //ʱ��ʱ������
	case  SYS_SUB4SUB1_SETTIME:
		 
		 if(g_mdatetime==0)
		 {
		        g_sysmenu4100date[g_mShowMenucolumn-1]='8';	
		        g_sysmenu4100dateEn[g_mShowMenucolumn-1]='8';
		}
		else
		{ 
		   		g_sysmenu4100time[g_mShowMenucolumn-1]='8';	
		        g_sysmenu4100timeEn[g_mShowMenucolumn-1]='8';
		}
					
	    FDateTimeInputMoveRight() ;
	break;
		//�Զ���ص�����
	case SYS_SUB4SUB3_SETSITE : 
	 FSiteInput(8);
	break;

	 //��Զ���������
	case SYS_SUB4SUB7_TELAZIALT_ZERO:				  
		FTelZeroInput(8);
		break;
//******************************* 
	case SYS_SUB3SUB4TIMER_INPUT:
	      g_sysmenu3402off[g_mShowMenucolumn-1]='8';
		  g_sysmenu3402offEn[g_mShowMenucolumn-1]='8';
		  FTimerInputMoveRight();
			break;     
	case SYS_SUB3SUB5ALARM_INPUT:
	      g_sysmenu3500alarm_input[g_mShowMenucolumn-1]='8';
		  g_sysmenu3500alarm_inputEn[g_mShowMenucolumn-1]='8';
		  FAlarmInputMoveRight();
		  break;  
		case SYS_SUB3SUB6SUB2M_MF:
	case SYS_SUB3SUB6SUB2M_MF1:
		  g_sysmenu3602m_mf[g_mShowMenucolumn-1]='8';
		  g_sysmenu3602m_mfEn[g_mShowMenucolumn-1]='8';
		  FMfocusInputMoveRight();
		  break;
	case SYS_SUB3SUB6SUB2M_SF:
	case SYS_SUB3SUB6SUB2M_SF1:	 
	 	 g_sysmenu3602m_sf[g_mShowMenucolumn-1]='8';
		 g_sysmenu3602m_sfEn[g_mShowMenucolumn-1]='8';
		 FSfocusInputMoveRight();
		 break;
	case SYS_SUB3SUB6SUB2M_MFOV: 
		  g_sysmenu3602m_mfovEn[g_mShowMenucolumn-1]='8';
		  FSFovInputMoveRight();
		  break;
	case SYS_SUB2SUB11_SET:
		F_LandmarkInput(8);
		break;
//********************************** 	
	default:
	break;
  }
}
//*******************************************************************


//*******************************************************************
//9�Ű���
void FKey9()
{

  switch(g_nsysstatus)
  {
	case SYS_MAINSHOW: //������Զ�����ֶ��ٶ�9��
		g_mHandSpeed=9;
		if(g_mTelStatusSet==0)
		 {
		     g_mHandSpeed=8;
	    }
		break;
	case SYS_F_SELFNUM:
	case SYS_MENU_SKY_OBJECT:
    case SYS_MENU_LAND_OBJECT:
		g_mFnum=9;
		break;

	case SYS_MAINHELP:
		g_mHandSpeed=9;//������Զ�����ֶ��ٶ�9��
			if(g_mTelStatusSet==0)
		 {
		     g_mHandSpeed=8;
	    }
		break;
	case SYS_SUB1SUB11RA_GEAR_ERROR_BEGIN: 	
	case SYS_SUB1SUB12DEC_GEAR_ERROR_BEGIN: 
	case SYS_SUB1SUB11RA_GEAR_ERROR_ALIGN: 	//��Զ��У׼ʱ���ֶ��ٶ�
	case SYS_SUB1SUB12DEC_GEAR_ERROR_ALIGN: 
	case SYS_SUB1SUB2STAR_ALIGN	:
		g_mHandSpeed=9;
		if(g_mTelStatusSet==0)
		 {
		     g_mHandSpeed=8;
	    }
		break;
		case SYS_SUB2MSR_OBJECT0: //messier�Ǳ���� 
	case SYS_SUB2MSR_OBJECT: 
		            LCDRfrsh();
			   if(((10* g_mInputStarNum+9)<=110)&&((10* g_mInputStarNum+9)>0))
			   {
		          g_mInputStarNum=10* g_mInputStarNum+9; 
		       }
			   if((g_mInputStarNum<=110)&&(g_mInputStarNum>0))
			   {			  
			     g_mMsrObjectNum= g_mInputStarNum;
			   }      
		 break;

	case SYS_SUB2NGC_OBJECT:   //ngc�Ǳ����
	 LCDRfrsh();
			   if(((10* g_mInputStarNum+9)<=7840)&&((10* g_mInputStarNum+9)>0))
			   {
		          g_mInputStarNum=10* g_mInputStarNum+9; 
		       }
			   if((g_mInputStarNum<=7840)&&(g_mInputStarNum>0))
			   {			  
			    g_mNgcObjectNum= g_mInputStarNum;
			   }      
		 break;

		case SYS_SUB2IC_OBJECT:  //ic�Ǳ����
		 LCDRfrsh();
			   if(((10* g_mInputStarNum+9)<=5386)&&((10* g_mInputStarNum+9)>0))
			   {
		          g_mInputStarNum=10* g_mInputStarNum+9; 
		       }
			   if((g_mInputStarNum<=5386)&&(g_mInputStarNum>0))
			   {			  
			     g_mIcObjectNum= g_mInputStarNum;
			   }      
		 break;
		 case SYS_SUB2SH2_OBJECT:  //sh2�Ǳ����
		 	        LCDRfrsh();
			   if(((10* g_mInputStarNum+9)<=313)&&((10* g_mInputStarNum+9)>0))
			   {
		          g_mInputStarNum=10* g_mInputStarNum+9; 
		       }
			   if((g_mInputStarNum<=313)&&(g_mInputStarNum>0))
			   {			  
			     g_mSh2ObjectNum= g_mInputStarNum;
			   }      
		 break;

		 case SYS_SUB2BRT_OBJECT:  //bright�Ǳ����
		 		 	 LCDRfrsh();
			   if(((10* g_mInputStarNum+9)<=167)&&((10* g_mInputStarNum+9)>0))
			   {
		          g_mInputStarNum=10* g_mInputStarNum+9; 
		       }
			   if((g_mInputStarNum<=167)&&(g_mInputStarNum>0))
			   {			  
			     g_mBrightObjectNum= g_mInputStarNum;
			   }      
		 break;
	
	     case SYS_SUB2SAO_OBJECT:  //sao�Ǳ����
		 	 	LCDRfrsh();
			   if(((10* g_mInputStarNum+9)<=258997)&&((10* g_mInputStarNum+9)>0))
			   {
		          g_mInputStarNum=10* g_mInputStarNum+9; 
		       }
			   if((g_mInputStarNum<=258997)&&(g_mInputStarNum>0))
			   {			  
			     g_mSaoObjectNum= g_mInputStarNum;
			   }      
		 break;

	case  SYS_SUB2SUB9RA:
	case SYS_MENU_SKY_RA:
	  	    g_sysmenu2900ra[g_mShowMenucolumn-1]='9';//�ྭ����
			g_sysmenu2900raEn[g_mShowMenucolumn-1]='9';//�ྭ����
			FRaInputMoveRight();
	        break;
	case SYS_MENU_LAND_AZI:
	  	    g_sysmenu2900ra[g_mShowMenucolumn-1]='9';//�ྭ����
			g_sysmenu2900raEn[g_mShowMenucolumn-1]='9';//�ྭ����
			FDecInputMoveRight();
	        break;
	case SYS_SUB2SUB9DEC:
	case SYS_MENU_SKY_DEC:
	case SYS_MENU_LAND_ALT:
	  	     if(	g_mShowMenucolumn!=5)
			{
	  	       g_sysmenu2900dec[g_mShowMenucolumn-1]='9';//��γ��������
			   g_sysmenu2900decEn[g_mShowMenucolumn-1]='9';//��γ��������
			}
			else  if(g_sysmenu2900dec[g_mShowMenucolumn-1]=='+'	)
			{
			  g_sysmenu2900dec[g_mShowMenucolumn-1]='-';//��γ������
			  g_sysmenu2900decEn[g_mShowMenucolumn-1]='-';//��γ������
			}
			else
			{
		    	g_sysmenu2900dec[g_mShowMenucolumn-1]='+';//��γ������
				g_sysmenu2900decEn[g_mShowMenucolumn-1]='+';//��γ������
			}
			FDecInputMoveRight();
	        break;

		case SYS_MENU_SKY_NAME:	
	    case SYS_MENU_LAND_NAME:	
	        switch(g_keychar)
			{
			   case '9':
			        g_keychar='w';
			   break;
			    case 'w':
			         g_keychar='x';
			   break; 
			    case 'x':
			         g_keychar='y';
			   break;
			     case 'y':
			         g_keychar='z';
			   break;
			     case 'z':
			         g_keychar='W';
			   break;
			   case 'W':
			         g_keychar='X';
			   break;
			   case 'X':
			         g_keychar='Y';
			   break;
			     case 'Y':
			         g_keychar='Z';
			   break;
			     case 'Z':
			         g_keychar='9';
			   break;
			   default:
			       g_keychar='9' ;
			   break;
			}
		   g_sysmenu2900NameEn[g_mShowMenucolumn-1]=g_keychar;	 
		   break;


	case SYS_SUB4SUB8MENU4_RASPEED :
	     if(g_mShowMenucolumn!=1)
			{
	  	       g_sysmenu4800raspeed[g_mShowMenucolumn-1]='9';	
	           g_sysmenu4800raspeedEn[g_mShowMenucolumn-1]='9';
			}
			else  if(g_sysmenu4800raspeed[g_mShowMenucolumn-1]=='+'	)
			{
                g_sysmenu4800raspeed[g_mShowMenucolumn-1]='-';	
	            g_sysmenu4800raspeedEn[g_mShowMenucolumn-1]='-';
			}
			else
			{
		        g_sysmenu4800raspeed[g_mShowMenucolumn-1]='+';	
	            g_sysmenu4800raspeedEn[g_mShowMenucolumn-1]='+';

			}	
	   FRaTrackSpeedInputMoveRight() ;  //�Զ�������ٶ�����������
	break;
	  //ʱ��ʱ������
	case  SYS_SUB4SUB1_SETTIME:
		 
		 if(g_mdatetime==0)
		 {
		        g_sysmenu4100date[g_mShowMenucolumn-1]='9';	
		        g_sysmenu4100dateEn[g_mShowMenucolumn-1]='9';
		}
		else
		{ 
		   		g_sysmenu4100time[g_mShowMenucolumn-1]='9';	
		        g_sysmenu4100timeEn[g_mShowMenucolumn-1]='9';
		}
					
	    FDateTimeInputMoveRight() ;
	break;
		//�Զ���ص�����
	case SYS_SUB4SUB3_SETSITE : 
	  FSiteInput(9);
	break;

	 //��Զ���������
	case SYS_SUB4SUB7_TELAZIALT_ZERO:				  
		FTelZeroInput(9);
		break;
//************************* 
	case SYS_SUB3SUB4TIMER_INPUT:
	      g_sysmenu3402off[g_mShowMenucolumn-1]='9';
		  g_sysmenu3402offEn[g_mShowMenucolumn-1]='9';
		  FTimerInputMoveRight();
		  break;       
	case SYS_SUB3SUB5ALARM_INPUT:
	      g_sysmenu3500alarm_input[g_mShowMenucolumn-1]='9';
		  g_sysmenu3500alarm_inputEn[g_mShowMenucolumn-1]='9';
		  FAlarmInputMoveRight();
		  break; 
	case SYS_SUB3SUB6SUB2M_MF:
	case SYS_SUB3SUB6SUB2M_MF1:
		  g_sysmenu3602m_mf[g_mShowMenucolumn-1]='9';
		  g_sysmenu3602m_mfEn[g_mShowMenucolumn-1]='9';
		  FMfocusInputMoveRight();
		  break;
	case SYS_SUB3SUB6SUB2M_SF:
	case SYS_SUB3SUB6SUB2M_SF1:	 
	 	 g_sysmenu3602m_sf[g_mShowMenucolumn-1]='9';
		 g_sysmenu3602m_sfEn[g_mShowMenucolumn-1]='9';
		 FSfocusInputMoveRight();
		 break;
	case SYS_SUB3SUB6SUB2M_MFOV: 
		  g_sysmenu3602m_mfovEn[g_mShowMenucolumn-1]='9';
		 FSFovInputMoveRight();
		  break;
	case SYS_SUB2SUB11_SET:
		F_LandmarkInput(9);
		break;

//*************************** 
	default:
	break;
  }
}
//*******************************************************************


//*******************************************************************
//*����
//������Զ���ı�����

void FKeyXH()
{
	
 switch(g_nsysstatus)
  {
   case SYS_MAINSHOW :                
        g_nsysstatus=SYS_MAINSHOWHELP;
		g_mhelpshow=1;
		LCDRfrsh();
		g_mmainhelpshow=1;

		break;
		///////////////////////////////////////
	case SYS_MAINMENU1:
		g_nsysstatus=SYS_MAINMENU1HELP;
		g_mhelpshow=1;
		LCDRfrsh();
		break;
	case SYS_MAINMENU2:
		g_nsysstatus=SYS_MAINMENU2HELP;
		g_mhelpshow=1;
		LCDRfrsh();
		break;
	case SYS_MAINMENU3:
		g_nsysstatus=SYS_MAINMENU3HELP;
		g_mhelpshow=1;
		LCDRfrsh();
		break;
	case SYS_MAINMENU4:
		g_nsysstatus=SYS_MAINMENU4HELP;
		g_mhelpshow=1;
		LCDRfrsh();
		break;
	  /////////////////////////////////////////////////////
	 //��Զ��У׼
	case SYS_SUB1MENU1:		    
		g_nsysstatus=SYS_SUB1MENU1HELP;
		g_mhelpshow=1;
		LCDRfrsh();
		break;
	case SYS_SUB1MENU2:
		g_nsysstatus=SYS_SUB1MENU2HELP;
		g_mhelpshow=1;
		LCDRfrsh();
		break;
	case SYS_SUB1MENU3:
		g_nsysstatus=SYS_SUB1MENU3HELP;
		g_mhelpshow=1;
		LCDRfrsh();
		break;
	case SYS_SUB1MENU4:
		g_nsysstatus=SYS_SUB1MENU4HELP;
		g_mhelpshow=1;
		LCDRfrsh();
	    break;	 
	case SYS_SUB1MENU5:
		g_nsysstatus=SYS_SUB1MENU5HELP;
		g_mhelpshow=1;
		LCDRfrsh();
		break;

	case SYS_SUB1MENU6:
		g_nsysstatus=SYS_SUB1MENU6HELP;
		g_mhelpshow=1;
		LCDRfrsh();
		break;
	case SYS_SUB1MENU7:
		g_nsysstatus=SYS_SUB1MENU7HELP;
		g_mhelpshow=1;
		LCDRfrsh();
		break;

	 //Ŀ�굼���Ӳ˵�
	case SYS_SUB2MENU1:
		g_nsysstatus=SYS_SUB2MENU1HELP;
		g_mhelpshow=1;
		LCDRfrsh();
	    break;
	case SYS_SUB2MENU2:	
		g_nsysstatus=SYS_SUB2MENU2HELP;
		g_mhelpshow=1;
		LCDRfrsh();
		break;
	case SYS_SUB2MENU3:
		g_nsysstatus=SYS_SUB2MENU3HELP;
		g_mhelpshow=1;
		LCDRfrsh();
		break;
	case SYS_SUB2MENU4:
		g_nsysstatus=SYS_SUB2MENU4HELP;
		g_mhelpshow=1;
		LCDRfrsh();
		break;
	case SYS_SUB2MENU5:
		g_nsysstatus=SYS_SUB2MENU5HELP;
		g_mhelpshow=1;
		LCDRfrsh();
	    break;
	case SYS_SUB2MENU6:
		g_nsysstatus=SYS_SUB2MENU6HELP;
		g_mhelpshow=1;
		LCDRfrsh();
		break;
	case SYS_SUB2MENU7:
		g_nsysstatus=SYS_SUB2MENU7HELP;
		g_mhelpshow=1;
		LCDRfrsh();
		break;
	case SYS_SUB2MENU8:
		g_nsysstatus=SYS_SUB2MENU8HELP;
		g_mhelpshow=1;
		LCDRfrsh();
		break;
	case SYS_SUB2MENU9:
		g_nsysstatus=SYS_SUB2MENU9HELP;
		g_mhelpshow=1;
		LCDRfrsh();
	    break;
	case SYS_SUB2MENU11:
		g_nsysstatus=SYS_SUB2MENU11HELP;
		g_mhelpshow=1;
		LCDRfrsh();
		break;
	case SYS_SUB2MENU12:
		g_nsysstatus=SYS_SUB2MENU12HELP;
		g_mhelpshow=1;
		LCDRfrsh();
		break;
	case SYS_SUB2MENU13:
		g_nsysstatus=SYS_SUB2MENU13HELP;
		g_mhelpshow=1;
		LCDRfrsh();
		break;

	 //���������Ӳ˵�
	 case SYS_SUB3MENU1:
	    g_nsysstatus=SYS_SUB3MENU1HELP;
		g_mhelpshow=1;
		LCDRfrsh();
	    break;
	case SYS_SUB3MENU2:
		g_nsysstatus=SYS_SUB3MENU2HELP;
		g_mhelpshow=1;
		LCDRfrsh();
		break;
	case SYS_SUB3MENU3:
		g_nsysstatus=SYS_SUB3MENU3HELP;
		g_mhelpshow=1;
		LCDRfrsh();
		break;
	case SYS_SUB3MENU4:
		g_nsysstatus=SYS_SUB3MENU4HELP;
		g_mhelpshow=1;
		LCDRfrsh();
		break;
	case SYS_SUB3MENU5:
		g_nsysstatus=SYS_SUB3MENU5HELP;
		g_mhelpshow=1;
		LCDRfrsh();
	    break;
	case SYS_SUB3MENU6:
		g_nsysstatus=SYS_SUB3MENU6HELP;
		g_mhelpshow=1;
		LCDRfrsh();
		break;
	case SYS_SUB3MENU7:
		g_nsysstatus=SYS_SUB3MENU7HELP;
		g_mhelpshow=1;
		LCDRfrsh();
		break;
	case SYS_SUB3MENU8:
		g_nsysstatus=SYS_SUB3MENU8HELP;
		g_mhelpshow=1;
		LCDRfrsh();
		break;
	case SYS_SUB3MENU9:
		g_nsysstatus=SYS_SUB3MENU9HELP;
		g_mhelpshow=1;
		LCDRfrsh();
		break;

	 //���������Ӳ˵�
	case SYS_SUB4MENU1:
		g_nsysstatus=SYS_SUB4MENU1HELP;
		g_mhelpshow=1;
		LCDRfrsh();
	    break;
	case SYS_SUB4MENU2:
		g_nsysstatus=SYS_SUB4MENU2HELP;
		g_mhelpshow=1;
		LCDRfrsh();
		break;
	case SYS_SUB4MENU3:
		g_nsysstatus=SYS_SUB4MENU3HELP;
		g_mhelpshow=1;
		LCDRfrsh();
		break;

	case SYS_SUB4MENU4:
		g_nsysstatus=SYS_SUB4MENU4HELP;
		g_mhelpshow=1;
		LCDRfrsh();
	    break;
	case SYS_SUB4MENU5:
		g_nsysstatus=SYS_SUB4MENU5HELP;
		g_mhelpshow=1;
		LCDRfrsh();
		break;
	case SYS_SUB4MENU6:
		g_nsysstatus=SYS_SUB4MENU6HELP;
		g_mhelpshow=1;
		LCDRfrsh();
		break;
	case SYS_SUB4MENU7:
		g_nsysstatus=SYS_SUB4MENU7HELP;
		g_mhelpshow=1;
		LCDRfrsh();
		break;
	case SYS_SUB4MENU8:
		g_nsysstatus=SYS_SUB4MENU8HELP;
		g_mhelpshow=1;
		LCDRfrsh();
	    break;
	case SYS_SUB4MENU9:
		g_nsysstatus=SYS_SUB4MENU9HELP;
		g_mhelpshow=1;
		LCDRfrsh();
		break;

	///////////////////////////////////////////////////
	case SYS_MAINSHOWHELP:
        g_nsysstatus=SYS_MAINSHOW ;
		g_mhelpshow=0;
		LCDRfrsh();
		break;
	case SYS_MAINMENU1HELP:
		g_nsysstatus=SYS_MAINMENU1;
		g_mhelpshow=0;
		LCDRfrsh();
		break;
	case SYS_MAINMENU2HELP:
		g_nsysstatus=SYS_MAINMENU2;
		g_mhelpshow=0;
		LCDRfrsh();
		break;
	case SYS_MAINMENU3HELP:
		g_nsysstatus=SYS_MAINMENU3;
		g_mhelpshow=0;
		LCDRfrsh();
		break;
	case SYS_MAINMENU4HELP:
		g_nsysstatus=SYS_MAINMENU4;
		g_mhelpshow=0;
		LCDRfrsh();
		break;
		  /////////////////////////////////////////////////////
	 //��Զ��У׼
	case SYS_SUB1MENU1HELP:		    
		g_nsysstatus=SYS_SUB1MENU1;
		g_mhelpshow=0;
		LCDRfrsh();
		break;
	case SYS_SUB1MENU2HELP:
		g_nsysstatus=SYS_SUB1MENU2;
		g_mhelpshow=0;
		LCDRfrsh();
		break;
	case SYS_SUB1MENU3HELP:
		g_nsysstatus=SYS_SUB1MENU3;
		g_mhelpshow=0;
		LCDRfrsh();
		break;
	case SYS_SUB1MENU4HELP:
		g_nsysstatus=SYS_SUB1MENU4;
		g_mhelpshow=0;
		LCDRfrsh();
	    break;

	case SYS_SUB1MENU5HELP:
		g_nsysstatus=SYS_SUB1MENU5;
		g_mhelpshow=0;
		LCDRfrsh();
		break;

	case SYS_SUB1MENU6HELP:
		g_nsysstatus=SYS_SUB1MENU6;
		g_mhelpshow=0;
		LCDRfrsh();
		break;
	case SYS_SUB1MENU7HELP:
		g_nsysstatus=SYS_SUB1MENU7;
		g_mhelpshow=0;
		LCDRfrsh();
		break;

	 //Ŀ�굼���Ӳ˵�
	case SYS_SUB2MENU1HELP:
		g_nsysstatus=SYS_SUB2MENU1;
		g_mhelpshow=0;
		LCDRfrsh();
	    break;
	case SYS_SUB2MENU2HELP:	
		g_nsysstatus=SYS_SUB2MENU2;
		g_mhelpshow=0;
		LCDRfrsh();
		break;
	case SYS_SUB2MENU3HELP:
		g_nsysstatus=SYS_SUB2MENU3;
		g_mhelpshow=0;
		LCDRfrsh();
		break;
	case SYS_SUB2MENU4HELP:
		g_nsysstatus=SYS_SUB2MENU4;
		g_mhelpshow=0;
		LCDRfrsh();
		break;
	case SYS_SUB2MENU5HELP:
		g_nsysstatus=SYS_SUB2MENU5;
		g_mhelpshow=0;
		LCDRfrsh();
	    break;
	case SYS_SUB2MENU6HELP:
		g_nsysstatus=SYS_SUB2MENU6;
		g_mhelpshow=0;
		LCDRfrsh();
		break;
	case SYS_SUB2MENU7HELP:
		g_nsysstatus=SYS_SUB2MENU7;
		g_mhelpshow=0;
		LCDRfrsh();
		break;
	case SYS_SUB2MENU8HELP:
		g_nsysstatus=SYS_SUB2MENU8;
		g_mhelpshow=0;
		LCDRfrsh();
		break;
	case SYS_SUB2MENU9HELP:
		g_nsysstatus=SYS_SUB2MENU9;
		g_mhelpshow=0;
		LCDRfrsh();
	    break;
	case SYS_SUB2MENU11HELP:
		g_nsysstatus=SYS_SUB2MENU11;
		g_mhelpshow=0;
		LCDRfrsh();
		break;
	case SYS_SUB2MENU12HELP:
		g_nsysstatus=SYS_SUB2MENU12;
		g_mhelpshow=0;
		LCDRfrsh();
		break;
	case SYS_SUB2MENU13HELP:
		g_nsysstatus=SYS_SUB2MENU13;
		g_mhelpshow=0;
		LCDRfrsh();
		break;

	 //���������Ӳ˵�
	 case SYS_SUB3MENU1HELP:
	    g_nsysstatus=SYS_SUB3MENU1;
		g_mhelpshow=0;
		LCDRfrsh();
	    break;
	case SYS_SUB3MENU2HELP:
		g_nsysstatus=SYS_SUB3MENU2;
		g_mhelpshow=0;
		LCDRfrsh();
		break;
	case SYS_SUB3MENU3HELP:
		g_nsysstatus=SYS_SUB3MENU3;
		g_mhelpshow=0;
		LCDRfrsh();
		break;
	case SYS_SUB3MENU4HELP:
		g_nsysstatus=SYS_SUB3MENU4;
		g_mhelpshow=0;
		LCDRfrsh();
		break;
	case SYS_SUB3MENU5HELP:
		g_nsysstatus=SYS_SUB3MENU5;
		g_mhelpshow=0;
		LCDRfrsh();
	    break;
	case SYS_SUB3MENU6HELP:
		g_nsysstatus=SYS_SUB3MENU6;
		g_mhelpshow=0;
		LCDRfrsh();
		break;
	case SYS_SUB3MENU7HELP:
		g_nsysstatus=SYS_SUB3MENU7;
		g_mhelpshow=0;
		LCDRfrsh();
		break;
	case SYS_SUB3MENU8HELP:
		g_nsysstatus=SYS_SUB3MENU8;
		g_mhelpshow=0;
		LCDRfrsh();
		break;
	case SYS_SUB3MENU9HELP:
		g_nsysstatus=SYS_SUB3MENU9;
		g_mhelpshow=0;
		LCDRfrsh();
		break;

	 //���������Ӳ˵�
	case SYS_SUB4MENU1HELP:
		g_nsysstatus=SYS_SUB4MENU1;
		g_mhelpshow=0;
		LCDRfrsh();
	    break;
	case SYS_SUB4MENU2HELP:
		g_nsysstatus=SYS_SUB4MENU2;
		g_mhelpshow=0;
		LCDRfrsh();
		break;
	case SYS_SUB4MENU3HELP:
		g_nsysstatus=SYS_SUB4MENU3;
		g_mhelpshow=0;
		LCDRfrsh();
		break;

	case SYS_SUB4MENU4HELP:
		g_nsysstatus=SYS_SUB4MENU4;
		g_mhelpshow=0;
		LCDRfrsh();
	    break;
	case SYS_SUB4MENU5HELP:
		g_nsysstatus=SYS_SUB4MENU5;
		g_mhelpshow=0;
		LCDRfrsh();
		break;
	case SYS_SUB4MENU6HELP:
		g_nsysstatus=SYS_SUB4MENU6;
		g_mhelpshow=0;
		LCDRfrsh();
		break;
	case SYS_SUB4MENU7HELP:
		g_nsysstatus=SYS_SUB4MENU7;
		g_mhelpshow=0;
		LCDRfrsh();
		break;
	case SYS_SUB4MENU8HELP:
		g_nsysstatus=SYS_SUB4MENU8;
		g_mhelpshow=0;
		LCDRfrsh();
	    break;
	case SYS_SUB4MENU9HELP:
		g_nsysstatus=SYS_SUB4MENU9;
		g_mhelpshow=0;
		LCDRfrsh();
		break;

	}
 	
  
}

//*******************************************************************


//*******************************************************************
//help����
 //��Ҫʵ����Զ���İ�����ʹ��˵��
void FKeyWH()
{  

 switch(g_nsysstatus)
  {
	case SYS_MAINSHOW: //������Զ�����ֶ��ٶ�0��
		g_nsysstatus=SYS_F_SELFNUM;
		g_mFnum=1;	
        g_mFDown=1;
		LCDRfrsh();
		break;

	 	case SYS_SUB2MSR_OBJECT0: //messier�Ǳ���� 
    	case SYS_SUB2MSR_OBJECT: 
	    case SYS_SUB2NGC_OBJECT:   //ngc�Ǳ���� 
		case SYS_SUB2IC_OBJECT:  //ic�Ǳ����  
		 case SYS_SUB2SH2_OBJECT:  //sh2�Ǳ���� 
		 case SYS_SUB2BRT_OBJECT:  //bright�Ǳ����
	     case SYS_SUB2SAO_OBJECT:  //sao�Ǳ����
			    LCDRfrsh();
			   g_mInputStarNum=0;
			   FBeep(1);
		 break;
	}
		  

}


//*******************************************************************


////////////////////////////////////////////////////////////
//�ֵ�����
void FKeyTorch()
{  
    switch(g_mTorch)//��Զ���ֵ�������0�رգ�1һ������2ȫ��
	{
	   case 0:
	   TORCH1OFF();
	   TORCH2OFF();
	   g_mTorch=1;
	   break; 	   
	   case 1:
	   TORCH1OFF();
	   TORCH2ON();
	   g_mTorch=2; 	   
	   break;
	   case 2:
	   TORCH1ON();
	   TORCH2ON();
	   g_mTorch=0;
	   break;
	   default:
	   break;
	  }
}
/////////////////////////////////////////////////////////////////
////*******************************************************************


//*******************************************************************
//left-up��ϰ���		
void FKeyLeftUp()
{
   switch(g_nsysstatus	)
   {
	   case SYS_MAINSHOW:
	   case SYS_SUB2SUN_PLANET1: //̫��ϵͳ����1 
	   case  SYS_SUB2CON_OBJECT1:
	   case  SYS_SUB2FS_OBJECT1: 			   
	   case  SYS_SUB2MSR_OBJECT1:
	   case  SYS_SUB2NGC_OBJECT1:
	   case  SYS_SUB2IC_OBJECT1:
	   case  SYS_SUB2SH2_OBJECT1:	
	   case  SYS_SUB2BRT_OBJECT1:
	   case  SYS_SUB2SAO_OBJECT1:
	   if(!g_mLandMark)
	   {
	     if((g_mGoto.m_nGoto)&&(g_mTelStatusSet!=1))
	    {
		 g_mAposModify=-1;//��λ���ٵ��ڴ�
	   	 g_mZposModify=1;//��λ���ٵ��ڴ�
		 g_mhandtrackAlt=0;//���ָ��ʱ����Զ����Ŀ��λ��һ�£��ֶ����ں󣬾Ͳ�һ����
	    }
		else
		{
		   if(g_mTelescopeConType==1)
		   {
		      FHandControlTelescopeTwo(AXIS_RA,DIRECT_LEFT,g_mHandSpeed,AXIS_DEC,DIRECT_UP,g_mHandSpeed);
	
			}
		   else
		   {
			  FHandControlTelescopeTwo(AXIS_AZI,DIRECT_LEFT,g_mHandSpeed,AXIS_ALT,DIRECT_UP,g_mHandSpeed);
	
		   }
		  }

		}
		else
		{
		  if(g_mTelescopeConType==1)
		   {
		      FHandControlTelescopeTwo(AXIS_RA,DIRECT_LEFT,g_mHandSpeed,AXIS_DEC,DIRECT_UP,g_mHandSpeed);
	
			}
		   else
		   {
			  FHandControlTelescopeTwo(AXIS_AZI,DIRECT_LEFT,g_mHandSpeed,AXIS_ALT,DIRECT_UP,g_mHandSpeed);
	
		   }
		}
	   break;  
	  default:
	  break;
	 } 
}
////*******************************************************************


//*******************************************************************
//left-down��ϰ���
void FKeyLeftDown()
{
   switch(g_nsysstatus	)
   {
	 	   case SYS_MAINSHOW:
	  	   case SYS_SUB2SUN_PLANET1: //̫��ϵͳ����1 
		   case  SYS_SUB2CON_OBJECT1:
		   case  SYS_SUB2FS_OBJECT1: 			   
		   case  SYS_SUB2MSR_OBJECT1:
		   case  SYS_SUB2NGC_OBJECT1:
		   case  SYS_SUB2IC_OBJECT1:
		   case  SYS_SUB2SH2_OBJECT1:	
		   case  SYS_SUB2BRT_OBJECT1:
		   case  SYS_SUB2SAO_OBJECT1:
		 if(!g_mLandMark)
		{
		  if((g_mGoto.m_nGoto)&&(g_mTelStatusSet!=1))
		  {
			 g_mAposModify=-1;//��λ���ٵ��ڴ�
			 g_mZposModify=-1;//��λ���ٵ��ڴ�
			 g_mhandtrackAlt=0;//���ָ��ʱ����Զ����Ŀ��λ��һ�£��ֶ����ں󣬾Ͳ�һ����
			 g_mhandtrackAzi=0;//���ָ��ʱ����Զ����Ŀ��λ��һ�£��ֶ����ں󣬾Ͳ�һ����
	
		    }
			else
			{
			   if(g_mTelescopeConType==1)
			   {
			      FHandControlTelescopeTwo(AXIS_RA,DIRECT_LEFT,g_mHandSpeed,AXIS_DEC,DIRECT_DOWN,g_mHandSpeed);
				}
			   else
			   {
				  FHandControlTelescopeTwo(AXIS_AZI,DIRECT_LEFT,g_mHandSpeed,AXIS_ALT,DIRECT_DOWN,g_mHandSpeed);
			   }
			  }
		  }
		  else
		  {
		    if(g_mTelescopeConType==1)
			   {
			      FHandControlTelescopeTwo(AXIS_RA,DIRECT_LEFT,g_mHandSpeed,AXIS_DEC,DIRECT_DOWN,g_mHandSpeed);
				}
			   else
			   {
				  FHandControlTelescopeTwo(AXIS_AZI,DIRECT_LEFT,g_mHandSpeed,AXIS_ALT,DIRECT_DOWN,g_mHandSpeed);
			   }
		  }
		   break;  
		  default:
		  break;
		 } 
  
}
////*******************************************************************


//*******************************************************************
//right-down��ϰ���				
void FKeyRightDown()
{
   switch(g_nsysstatus	)
   {
	   case SYS_MAINSHOW:
	   case SYS_SUB2SUN_PLANET1: //̫��ϵͳ����1 
	   case  SYS_SUB2CON_OBJECT1:
	   case  SYS_SUB2FS_OBJECT1: 			   
	   case  SYS_SUB2MSR_OBJECT1:
	   case  SYS_SUB2NGC_OBJECT1:
	   case  SYS_SUB2IC_OBJECT1:
	   case  SYS_SUB2SH2_OBJECT1:	
	   case  SYS_SUB2BRT_OBJECT1:
	   case  SYS_SUB2SAO_OBJECT1:
	    if(!g_mLandMark)
	   {
   	  if((g_mGoto.m_nGoto)&&(g_mTelStatusSet!=1))
	  {
		  g_mAposModify=1;//��λ���ٵ��ڴ�
		 g_mZposModify=-1;//��λ���ٵ��ڴ� 
		 g_mhandtrackAlt=0;//���ָ��ʱ����Զ����Ŀ��λ��һ�£��ֶ����ں󣬾Ͳ�һ����
		 g_mhandtrackAzi=0;//���ָ��ʱ����Զ����Ŀ��λ��һ�£��ֶ����ں󣬾Ͳ�һ����
	    }
		else
		{
		   if(g_mTelescopeConType==1)
		   {
		       FHandControlTelescopeTwo(AXIS_RA,DIRECT_RIGHT,g_mHandSpeed,AXIS_DEC,DIRECT_DOWN,g_mHandSpeed);
	
			}
		   else
		   {
			  FHandControlTelescopeTwo(AXIS_AZI,DIRECT_RIGHT,g_mHandSpeed,AXIS_ALT,DIRECT_DOWN,g_mHandSpeed);
		   }
		 }
		 }
		 else
		 {
		  if(g_mTelescopeConType==1)
		   {
		       FHandControlTelescopeTwo(AXIS_RA,DIRECT_RIGHT,g_mHandSpeed,AXIS_DEC,DIRECT_DOWN,g_mHandSpeed);
	
			}
		   else
		   {
			  FHandControlTelescopeTwo(AXIS_AZI,DIRECT_RIGHT,g_mHandSpeed,AXIS_ALT,DIRECT_DOWN,g_mHandSpeed);
		   }
		 }
	   break;  
	  default:
	  break;
	 } 
}
////*******************************************************************


//*******************************************************************
//right-up��ϰ���		
void FKeyRightUp()
{
   switch(g_nsysstatus	)
   {
	   case SYS_MAINSHOW:
	   case SYS_SUB2SUN_PLANET1: //̫��ϵͳ����1 
	   case  SYS_SUB2CON_OBJECT1:
	   case  SYS_SUB2FS_OBJECT1: 			   
	   case  SYS_SUB2MSR_OBJECT1:
	   case  SYS_SUB2NGC_OBJECT1:
	   case  SYS_SUB2IC_OBJECT1:
	   case  SYS_SUB2SH2_OBJECT1:	
	   case  SYS_SUB2BRT_OBJECT1:
	   case  SYS_SUB2SAO_OBJECT1:
	   if(!g_mLandMark)
	  {
   	  if((g_mGoto.m_nGoto)&&(g_mTelStatusSet!=1))
	  {
		    g_mAposModify=1;//��λ���ٵ��ڴ�
			g_mZposModify=1;//��λ���ٵ��ڴ�
			g_mhandtrackAlt=0;//���ָ��ʱ����Զ����Ŀ��λ��һ�£��ֶ����ں󣬾Ͳ�һ����
			g_mhandtrackAzi=0;//���ָ��ʱ����Զ����Ŀ��λ��һ�£��ֶ����ں󣬾Ͳ�һ����
	    }
		else
		{
		   if(g_mTelescopeConType==1)
		   {
		      FHandControlTelescopeTwo(AXIS_RA,DIRECT_RIGHT,g_mHandSpeed,AXIS_DEC,DIRECT_UP,g_mHandSpeed);
			}
		   else
		   {
			  FHandControlTelescopeTwo(AXIS_AZI,DIRECT_RIGHT,g_mHandSpeed,AXIS_ALT,DIRECT_UP,g_mHandSpeed);
		   }
	   }
	   }
	   else
	   {
	      if(g_mTelescopeConType==1)
		   {
		      FHandControlTelescopeTwo(AXIS_RA,DIRECT_RIGHT,g_mHandSpeed,AXIS_DEC,DIRECT_UP,g_mHandSpeed);
			}
		   else
		   {
			  FHandControlTelescopeTwo(AXIS_AZI,DIRECT_RIGHT,g_mHandSpeed,AXIS_ALT,DIRECT_UP,g_mHandSpeed);
		   }
	   }
	   break;  
	  default:
	  break;
	 } 
}
////*******************************************************************


//*******************************************************************
//ϵͳ�˵���

void FKeyMenu()
{
   switch(g_nsysstatus)		 //���뵽��Ѱ�ѹ۲��Ŀ��״̬
	{
	case SYS_MAINSHOW:	
	    LCDRfrsh(); 
		g_nsysstatus=SYS_MENUSHOW;
		g_mUsedStarNum=1;
		g_mShowMenurowEn=1;
		g_mSysMenuShowDirect=true;

		g_mUsedStarNumMax=GetRecentStarInfoNum();
	 	g_mUsedStarNum=0;			
		break;

   

	case SYS_MAINHELP:         
	    g_nsysstatus=SYS_MENUSHOW;
		g_mUsedStarNum=1;
		g_mShowMenurowEn=1;
		g_mSysMenuShowDirect=true;
	default:break;
	}	


} 
//*******************************************************************

//*******************************************************************
//�˵����ذ���
void FKeyBack()
{
    switch(g_nsysstatus)
	{
	case SYS_MENUSHOW:	//����ʾ�չ۲�����ǵ�������ʾ
		g_nsysstatus=SYS_MAINSHOW;
		break;
	case SYS_MAINHELP:	//��������״̬�˳�������ʾ
		g_nsysstatus=SYS_MAINSHOW;
		break;
     case SYS_F_SELFNUM :   //��F½��Ŀ������Ŀ�깦�ܷ��� 
		 	g_nsysstatus=SYS_MAINSHOW;
		break;
	  case SYS_F_SELFNUM_SEL :   //��F½��Ŀ������Ŀ����� 
		 	 g_nsysstatus=SYS_F_SELFNUM;
		break;

	 case SYS_SUB1SUB2STAR_ALIGN:
	    if(g_nAlignPoint)
		{
		  g_mGoto.m_nAlign=true;
		  FPauseGoto();
		  g_mGotoHandMoveOK=false;
		  DispEn(0,1,1,21,"                     ");
		  DispEn(0,2,1,21,"                     ");
		  DispEn(0,3,1,21,"                     ");
		  DispEn(0,4,1,21,"This Align Canceled  ");
		  DispEn(0,5,1,21,"                     ");
		  DispEn(0,6,1,21,"                     ");
		  DispEn(0,7,1,21,"                     ");
		  DispEn(0,8,1,21,"                     ");
		  MenuDelay(1000);
		  FBeep(2);
		  MenuDelay(100);
		  g_nsysstatus=SYS_MAINSHOW;
		 }
		 else
		 {
		     switch(g_nAlignStar)
		    {
		     case 1:
			       g_nsysstatus=SYS_SUB1MENU1;//һ��У������
			       break;
			 case 2:
			       g_nsysstatus=SYS_SUB1MENU2;	//������У������
			       break;
			 case 3:							
			       g_nsysstatus=SYS_SUB1MENU3;	//������У������
			       break;
			 default:
			 break ;
			 }
		 }
	  break;


	//��һ���˵��˳�������ʾ
	case SYS_MAINMENU1:	
		g_nsysstatus=SYS_MAINSHOW;
		break;
	case SYS_MAINMENU2:
		g_nsysstatus=SYS_MAINSHOW;
		break;
	case SYS_MAINMENU3:
		g_nsysstatus=SYS_MAINSHOW;
		break;
	case SYS_MAINMENU4:
		g_nsysstatus=SYS_MAINSHOW;
		break;
	//�Ӷ����˵��˳���һ���˵�
	//����Զ��У���Ӳ˵��˳�����Զ��У��
	case SYS_SUB1MENU1:
		g_nsysstatus=SYS_MAINMENU1;
		break;
	case SYS_SUB1MENU2:
		g_nsysstatus=SYS_MAINMENU1;
		break;
	case SYS_SUB1MENU3:
		g_nsysstatus=SYS_MAINMENU1;
		break;
	case SYS_SUB1MENU4:
		g_nsysstatus=SYS_MAINMENU1;
		break;
	case SYS_SUB1MENU5:
		g_nsysstatus=SYS_MAINMENU1;
		break;
	case SYS_SUB1MENU6:
		g_nsysstatus=SYS_MAINMENU1;
		break;
	case SYS_SUB1MENU7:
		g_nsysstatus=SYS_MAINMENU1;
		break;
	//�Ӷ����˵��˳���һ���˵�
	//��Ŀ�굼���Ӳ˵��˳���Ŀ�굼��
	case SYS_SUB2MENU1:
		g_nsysstatus=SYS_MAINMENU2;
		break;
	case SYS_SUB2MENU2:
		g_nsysstatus=SYS_MAINMENU2;
		break;
	case SYS_SUB2MENU3:
		g_nsysstatus=SYS_MAINMENU2;
		break;
	case SYS_SUB2MENU4:
		g_nsysstatus=SYS_MAINMENU2;
		break;
	case SYS_SUB2MENU5:
		g_nsysstatus=SYS_MAINMENU2;
		break;
	case SYS_SUB2MENU6:
		g_nsysstatus=SYS_MAINMENU2;
		break;
	case SYS_SUB2MENU7:
		g_nsysstatus=SYS_MAINMENU2;
		break;
	case SYS_SUB2MENU8:
		g_nsysstatus=SYS_MAINMENU2;
		break;
	case SYS_SUB2MENU9:
		g_nsysstatus=SYS_MAINMENU2;
		break;
	case SYS_SUB2MENU11:
		g_nsysstatus=SYS_MAINMENU2;
		break;
    case SYS_SUB2MENU12:
		g_nsysstatus=SYS_MAINMENU2;
		break;
	case SYS_SUB2MENU13:
		g_nsysstatus=SYS_MAINMENU2;
		break;



	//�Ӷ����˵��˳���һ���˵�
	//�ӹ��������Ӳ˵��˳�������
	case SYS_SUB3MENU1:
		g_nsysstatus=SYS_MAINMENU3;
		break;
	case SYS_SUB3MENU2:
		g_nsysstatus=SYS_MAINMENU3;
		break;
	case SYS_SUB3MENU3:
		g_nsysstatus=SYS_MAINMENU3;
		break;
	case SYS_SUB3MENU4:
		g_nsysstatus=SYS_MAINMENU3;
		break;
	case SYS_SUB3MENU5:
		g_nsysstatus=SYS_MAINMENU3;
		break;
	case SYS_SUB3MENU6:
		g_nsysstatus=SYS_MAINMENU3;
		break;
	case SYS_SUB3MENU7:
		g_nsysstatus=SYS_MAINMENU3;
		break;
	case SYS_SUB3MENU8:
		g_nsysstatus=SYS_MAINMENU3;
		break;
	case SYS_SUB3MENU9:
		g_nsysstatus=SYS_MAINMENU3;
		break;
	//�Ӷ����˵��˳���һ���˵�
	//�Ӳ��������Ӳ˵��˳�����������
	case SYS_SUB4MENU1:
		g_nsysstatus=SYS_MAINMENU4;
		break;
	case SYS_SUB4MENU2:
		g_nsysstatus=SYS_MAINMENU4;
		break;
	case SYS_SUB4MENU3:
		g_nsysstatus=SYS_MAINMENU4;
		break;
	case SYS_SUB4MENU4:
		g_nsysstatus=SYS_MAINMENU4;
		break;
	case SYS_SUB4MENU5:
		g_nsysstatus=SYS_MAINMENU4;
		break;
	case SYS_SUB4MENU6:
		g_nsysstatus=SYS_MAINMENU4;
		break;
	case SYS_SUB4MENU7:
		g_nsysstatus=SYS_MAINMENU4;
		break;
	case SYS_SUB4MENU8:
		g_nsysstatus=SYS_MAINMENU4;
		break;
	case SYS_SUB4MENU9:
		g_nsysstatus=SYS_MAINMENU4;
		break;

	//�������˵������Ӳ˵����˵������˵����Ӳ˵���

		//��ͬ��Ŀ��˵��˳�
   		case SYS_SUB1SUB4MENU1: 
			m_TcpSynEnable=0;
		case SYS_SUB1SUB4MENU2:
		case SYS_SUB1SUB4MENU3:
		     g_nsysstatus=SYS_SUB1MENU4;
			break;

	//���Զ����Ǳ����Ӳ˵��˵��Զ����Ǳ��Ӳ˵�
	case SYS_SUB2SUB8MENU1:
		g_nsysstatus=SYS_SUB2MENU11;
		break;
	case SYS_SUB2SUB8MENU2:
		g_nsysstatus=SYS_SUB2MENU11;
		break;
	case SYS_SUB2SUB8MENU3:
		g_nsysstatus=SYS_SUB2MENU11;
		break;
	case SYS_SUB2SUB8MENU4:
		g_nsysstatus=SYS_SUB2MENU11;
		break;
	//��½��Ŀ�����Ӳ˵��˵�½��Ŀ���Ӳ˵�
	case SYS_SUB2SUB11MENU1:
		g_nsysstatus=SYS_SUB2MENU13;
		break;
	case SYS_SUB2SUB11MENU2:
		g_nsysstatus=SYS_SUB2MENU13;
		break;
	case SYS_SUB2SUB11MENU3:
		g_nsysstatus=SYS_SUB2MENU13;
		break;
	//�ӵ���ʱ���Ӳ˵��˵�����ʱ�Ӳ˵�
	case SYS_SUB3SUB4TIMER_INPUT:
		g_nsysstatus=SYS_SUB3MENU4;
		break;
	case SYS_SUB3SUB4TIMER_ONOFF:
		g_nsysstatus=SYS_SUB3MENU4;
		break;
	//�Ӷ�ʱ�������Ӳ˵��˵���ʱ�����Ӳ˵�
	case SYS_SUB3SUB5ALARM_INPUT:
		g_nsysstatus=SYS_SUB3MENU5;
		break;
	case SYS_SUB3SUB5ALARM_ONOFF:
		g_nsysstatus=SYS_SUB3MENU5;
		break;
	//��Ŀ���������Ӳ˵��˵�Ŀ�������Ӳ˵�
	case SYS_SUB3SUB6SUB2M_MF:
	case SYS_SUB3SUB6SUB2M_SF:
		g_nsysstatus=SYS_SUB3MENU7;
		break;
	case SYS_SUB3SUB6SUB2M_MF1:
	case SYS_SUB3SUB6SUB2M_SF1:
	case SYS_SUB3SUB6SUB2M_MFOV:
		g_nsysstatus=SYS_SUB3MENU6;
		break;



	case SYS_SUB3SUB6MENU2:
		g_nsysstatus=SYS_SUB3MENU6;
		break;
	//�Ӱ���Ұ�������Ӳ˵��˵�����Ұ�����Ӳ˵�
	case SYS_SUB3SUB8MENU1:
		g_nsysstatus=SYS_SUB3MENU8;
		break;
	case SYS_SUB3SUB8MENU2:
		g_nsysstatus=SYS_SUB3MENU8;
		break;
	//�ӵص��������Ӳ˵��˵��ص������Ӳ˵�
	case SYS_SUB4SUB3MENU1:
	case SYS_SUB4SUB3MENU2:
		  if(g_mSysInitGuide==0)
		 {
		   g_nsysstatus=SYS_SUB4MENU3;
		  }
		  else
		  {
	
		    g_nsysstatus=SYS_SUB4SUB2MENU1;
		  }		
		break;


	//�Ӹ����ٶ����Ӳ˵��˵������ٶ��Ӳ˵�
	case SYS_SUB4SUB8MENU1:
		g_nsysstatus=SYS_SUB4MENU7;
		break;
	case SYS_SUB4SUB8MENU2:
		g_nsysstatus=SYS_SUB4MENU7;
		break;
	case SYS_SUB4SUB8MENU3:
		g_nsysstatus=SYS_SUB4MENU7;
		break;
	case SYS_SUB4SUB8MENU4:
		g_nsysstatus=SYS_SUB4MENU7;
		break;
	//��Զ���ײ�ʵ�ֵ��˳�
	//�۲�Ŀ������/½��ѡ��
	case SYS_SUB4SUB5SKY:
		g_nsysstatus=SYS_SUB4MENU4; 
	    break;
	case SYS_SUB4SUB5LAND:
		g_nsysstatus=SYS_SUB4MENU4;
		break;	 
		 
	//�۲�Ŀ������/½��ѡ��
	case SYS_SUB4SUB6AZ:
		g_nsysstatus=SYS_SUB4MENU5; 
	    break;
	case SYS_SUB4SUB6EQ:
		g_nsysstatus=SYS_SUB4MENU5;
		break;
	

	 		//��Զ������ƫ����ʾ
     	case SYS_SUB1SUB8POLE_AXIS_ERROR:
			g_nsysstatus=SYS_SUB1MENU5;
			break;



	//�˳ྭ�ز�У��
    case SYS_SUB1SUB11RA_GEAR_ERROR_BEGIN: 
		g_nsysstatus=SYS_SUB1MENU6;
		break;

	//�˳ྭ�ز�����У��
    case SYS_SUB1SUB11RA_GEAR_ERROR: 
	    FHandStopTelescope();
		g_nsysstatus=SYS_SUB1SUB11RA_GEAR_ERROR_BEGIN;
		g_mGearErrorAlign=false;//��Զ���Ƿ�����ִ����Ļز�У׼,true����ִ��,falseû��
		break;

   	//�˳���γ�ز�У��
    case SYS_SUB1SUB12DEC_GEAR_ERROR_BEGIN:
		g_nsysstatus=SYS_SUB1MENU7;
		break;

	//�˳���γ�ز�����У��
    case SYS_SUB1SUB12DEC_GEAR_ERROR:  
	    FHandStopTelescope();
		g_nsysstatus=SYS_SUB1SUB12DEC_GEAR_ERROR_BEGIN;
		g_mGearErrorAlign=false;//��Զ���Ƿ�����ִ����Ļز�У׼,true����ִ��,falseû��
		break;



	//��������
	case SYS_SUB3SUB1NOW_APH:
			 g_nsysstatus=SYS_SUB3MENU1;	
			break; 

	
		   case  SYS_SUB2SUB6DS_OBJECT:
		      g_nsysstatus=SYS_SUB2MENU6;
			 break;
	
		  case  SYS_SUB2SUB7VS_OBJECT:
		      g_nsysstatus=SYS_SUB2MENU7;
			 break;
	 	//��̫��ϵ���Ӳ˵��˵�̫��ϵ�Ӳ˵�
	
		//�˳�̫��ϵ���Ӳ˵�
		case SYS_SUB2SUN_PLANET:	 	
			g_nsysstatus=SYS_SUB2MENU1;
			break;	 
		case  SYS_SUB2SUN_PLANET1: 	
		  g_mEQHn=false;//���ʽ��Զ��Ŀ���Ƿ��ڵ�ƽ��    	 
			if((g_mOperateStatus==5)||(g_mOperateStatus==3)) 
			{
			    LCDRfrsh();
			   //g_mGotoHandMoveOK=true;
			   //g_mEQHn=true;//���ʽ��Զ��Ŀ���Ƿ��ڵ�ƽ��
			   g_mGoto.m_nStartStop=false;
         	   g_nsysstatus=SYS_SUB2SUN_PLANET; 
			 }
			 else
			 {
			   g_mOperateStatus=5;
			   FPauseGoto();
			   g_mGotoHandMoveOK=false;
			   FBeep(2);
			  }
		 	break;
		case SYS_SUB2SUN_SUNWARN :
		       g_nsysstatus=SYS_SUB2SUN_PLANET; 
		    break;
 

		//�˳�88����
	   	case  SYS_SUB2CON_OBJECT:  
       	    g_nsysstatus=SYS_SUB2MENU2;
		 	break; 
		case  SYS_SUB2CON_OBJECT1:	
		 g_mEQHn=false;//���ʽ��Զ��Ŀ���Ƿ��ڵ�ƽ��
	      //��ȡ88�����Ǳ�����
		  if((g_mOperateStatus==5)||(g_mOperateStatus==3)) 
			{
			  LCDRfrsh();
			  g_mGoto.m_nStartStop=false;
         	  g_nsysstatus=SYS_SUB2CON_OBJECT;
			 }
			 else
			 {
			   g_mOperateStatus=5;
			   FPauseGoto();
			   g_mGotoHandMoveOK=false;
			   FBeep(2);
			  }
            
		 	break;

		 //�˳����������Ӳ˵�
		case SYS_SUB2FS_OBJECT:	 								 
         	g_nsysstatus=SYS_SUB2MENU3;
			break;
		case  SYS_SUB2FS_OBJECT1:	 
		g_mEQHn=false;//���ʽ��Զ��Ŀ���Ƿ��ڵ�ƽ��
		 if((g_mOperateStatus==5)||(g_mOperateStatus==3)) 
			{
			 LCDRfrsh();
			 g_mGoto.m_nStartStop=false;
         	 g_nsysstatus=SYS_SUB2FS_OBJECT;
			 }
			 else
			 {
			   g_mOperateStatus=5;
			   FPauseGoto();
			   g_mGotoHandMoveOK=false;
			   FBeep(2);
			  }
            
			break;
					
		//�˳�messier�Ǳ�
		case SYS_SUB2MSR_OBJECT0:	
         	g_nsysstatus=SYS_SUB2MENU4;
		 	break;
		case SYS_SUB2MSR_OBJECT:
		    LCDRfrsh();	 
         	g_nsysstatus=SYS_SUB2MSR_OBJECT0;
		 	break;
	   case  SYS_SUB2MSR_OBJECT1:	 
	    g_mEQHn=false;//���ʽ��Զ��Ŀ���Ƿ��ڵ�ƽ��
	    if((g_mOperateStatus==5)||(g_mOperateStatus==3)) 
			{
			  LCDRfrsh();
			  g_mGoto.m_nStartStop=false;
         	   g_nsysstatus=SYS_SUB2MSR_OBJECT;
			 }
			 else
			 {
			   g_mOperateStatus=5;
			   FPauseGoto();
			   g_mGotoHandMoveOK=false;
			   FBeep(2);
			  }
           
			break;

		//�˳�NGC�Ǳ�
	   	case SYS_SUB2NGC_OBJECT:  
         	g_nsysstatus=SYS_SUB2MENU5;
		 	break;
		case  SYS_SUB2NGC_OBJECT1:	  
		 g_mEQHn=false;//���ʽ��Զ��Ŀ���Ƿ��ڵ�ƽ��
		 if((g_mOperateStatus==5)||(g_mOperateStatus==3)) 
			{  LCDRfrsh();
			  g_mGoto.m_nStartStop=false;
         	  g_nsysstatus=SYS_SUB2NGC_OBJECT;
			 }
			 else
			 {
			   g_mOperateStatus=5;
			   FPauseGoto();
			   g_mGotoHandMoveOK=false;
			   FBeep(2);
			  }
            
			break;

	   //�˳�IC�Ǳ�
		case  SYS_SUB2IC_OBJECT: 
         	g_nsysstatus=SYS_SUB2MENU6;
		 	break;
		case  SYS_SUB2IC_OBJECT1:
			g_mEQHn=false;//���ʽ��Զ��Ŀ���Ƿ��ڵ�ƽ��
		 if((g_mOperateStatus==5)||(g_mOperateStatus==3)) 
			{
			 LCDRfrsh();
			 g_mGoto.m_nStartStop=false;
         	  g_nsysstatus=SYS_SUB2IC_OBJECT;
			 }
			 else
			 {
			   g_mOperateStatus=5;
			   FPauseGoto();
			   g_mGotoHandMoveOK=false;
			   FBeep(2);
			  }
            
			break;

	   //�˳�SH2�Ǳ�
	   case  SYS_SUB2SH2_OBJECT:  
         	g_nsysstatus=SYS_SUB2MENU7;	
			break;
		case  SYS_SUB2SH2_OBJECT1:	
		g_mEQHn=false;//���ʽ��Զ��Ŀ���Ƿ��ڵ�ƽ��
		 if((g_mOperateStatus==5)||(g_mOperateStatus==3)) 
			{
			   LCDRfrsh(); 	
			   g_mGoto.m_nStartStop=false;					
         	   g_nsysstatus=SYS_SUB2SH2_OBJECT;
			 }
			 else
			 {
			   g_mOperateStatus=5;
			   FPauseGoto();
			   g_mGotoHandMoveOK=false;
			   FBeep(2);
			  }
           
			break;

		//�˳�Bright�Ǳ�
	   case  SYS_SUB2BRT_OBJECT:  
         	g_nsysstatus=SYS_SUB2MENU8;
		 	break;
	  	case  SYS_SUB2BRT_OBJECT1:	
		 g_mEQHn=false;//���ʽ��Զ��Ŀ���Ƿ��ڵ�ƽ��
		if((g_mOperateStatus==5)||(g_mOperateStatus==3)) 
			{
					 	 LCDRfrsh();
				g_mGoto.m_nStartStop=false;		 
         	   g_nsysstatus=SYS_SUB2BRT_OBJECT;
			 }
			 else
			 {
			   g_mOperateStatus=5;
			   FPauseGoto();
			   g_mGotoHandMoveOK=false;
			   FBeep(2);
			  }
	          
			break;


		 //�˳�Sao�Ǳ�
	     case  SYS_SUB2SAO_OBJECT:
         	g_nsysstatus=SYS_SUB2MENU9;
		 	break;
		 case  SYS_SUB2SAO_OBJECT1:	
		  g_mEQHn=false;//���ʽ��Զ��Ŀ���Ƿ��ڵ�ƽ��
		  if((g_mOperateStatus==5)||(g_mOperateStatus==3)) 
			{ 	 	LCDRfrsh();
			g_mGoto.m_nStartStop=false;
         	  g_nsysstatus=SYS_SUB2SAO_OBJECT;
			 }
			 else
			 {
			   g_mOperateStatus=5;
			   FPauseGoto();
			   g_mGotoHandMoveOK=false;
			   FBeep(2);
			  }
            
			break;	
		 //�˳��Զ����Ǳ����Ӳ˵�
	 	case SYS_MENU_SKY_OBJECT:	
			g_nsysstatus=SYS_SUB2MENU11;
			break;
		case  SYS_MENU_SKY_NAME:
		case  SYS_MENU_SKY_RA:
		case  SYS_MENU_SKY_DEC:
		    g_nsysstatus=SYS_MENU_SKY_OBJECT;
		   break;
	//�ྭ��γ�����˳�
	case SYS_SUB2SUB9RA:
	    if(g_mRaDecMode==0)
		{
		   g_nsysstatus=SYS_SUB2MENU12;
		 }
		 else
		 {
		   g_nsysstatus=SYS_SUB3MENU2;
		  } 
	    break;
	case SYS_SUB2SUB9DEC:
		 if(g_mRaDecMode==0)
		{
		   g_nsysstatus=SYS_SUB2MENU12;
		 }
		 else
		 {
		   g_nsysstatus=SYS_SUB3MENU2;
		  } 
		break;	

		      //�˳�½��Ŀ�����Ӳ˵�	

		case SYS_MENU_LAND_OBJECT:	
			g_nsysstatus=SYS_SUB2MENU13;
			break;
		case  SYS_MENU_LAND_NAME:
		case  SYS_MENU_LAND_AZI:
		case  SYS_MENU_LAND_ALT:  		
		    g_nsysstatus=SYS_MENU_LAND_OBJECT;
		   break;
			break;
	
	case SYS_SUB3SUB6SUB1MENU1:
	    g_nsysstatus=SYS_SUB3SUB6MENU1;
	    break;
	case SYS_SUB3SUB6SUB1MENU2:
	    g_nsysstatus=SYS_SUB3SUB6MENU1;
	    break;
	case SYS_SUB3SUB6SUB1MENU3:
	    g_nsysstatus=SYS_SUB3SUB6MENU1;
	    break;
	
	case SYS_SUB3SUB8MENU1Screen:
		g_nsysstatus=SYS_SUB3MENU8;
		break;

	case SYS_SUB4SUB2MENU1:
	case SYS_SUB4SUB2MENU2:
		  if(g_mSysInitGuide==0)
		 { g_nsysstatus=SYS_SUB4MENU2;
		  
		  }
		  else
		  {
		    GetSysTime();
		    sprintf(g_sysmenu4100dateEn,"%04d-%02d-%02d",g_mDate_year,g_mDate_month,g_mDate_day);
	      	sprintf(g_sysmenu4100timeEn,"%02d:%02d:%02d",g_mTime_hour,g_mTime_minute,g_mTime_second);
	      	sprintf(g_sysmenu4100date,"%04d-%02d-%02d",g_mDate_year,g_mDate_month,g_mDate_day);
	      	sprintf(g_sysmenu4100time,"%02d:%02d:%02d",g_mTime_hour,g_mTime_minute,g_mTime_second);
	      	g_mShowMenucolumn=1;
		  	g_mdatetime=0;
		    g_nsysstatus=SYS_SUB4SUB1_SETTIME;
		  }
		
		break;
	case SYS_SUB2SUB11_SET	:
		switch(g_mMyLandmarkOperator)
		{
			case 0:
		    	g_nsysstatus=SYS_SUB2SUB11MENU1;
				break;
			case 1:
		        g_nsysstatus=SYS_SUB2SUB11MENU2;
				break;
			case 2:
		        g_nsysstatus=SYS_SUB2SUB11MENU3;
				break;
		   	default :
				break;
		}
		break;
	case SYS_SUB2SUB8_SET	:
		switch(g_mMyStarOperator)
		{
			case 0:
		    	g_nsysstatus=SYS_SUB2SUB8MENU1;
				break;
			case 1:
		        g_nsysstatus=SYS_SUB2SUB8MENU2;
				break;
			case 2:
		        g_nsysstatus=SYS_SUB2SUB8MENU3;
				break;
			case 3:
				g_nsysstatus=SYS_SUB2SUB8MENU4;
				break;
		   	default :
				break;
		}
		break; 
	//�˳���Զ������ѡ��״̬
	case SYS_SUB4SUB9EN:  //�˳���Զ������ѡ���Ӳ˵�
	    g_nsysstatus=SYS_SUB4MENU8;
		break;
	case SYS_SUB4SUB9GER:  //�˳���Զ������ѡ���Ӳ˵�
	    g_nsysstatus=SYS_SUB4MENU8;
		break;
	case SYS_SUB4SUB9FRE:  //�˳���Զ������ѡ���Ӳ˵�
	    g_nsysstatus=SYS_SUB4MENU8;
		break;
	case SYS_SUB4SUB9ITA:  //�˳���Զ������ѡ���Ӳ˵�
	    g_nsysstatus=SYS_SUB4MENU8;
		break;
    case SYS_SUB4SUB9SPA:  //�˳���Զ������ѡ���Ӳ˵�
	    g_nsysstatus=SYS_SUB4MENU8;
		break;
	//�˳��Զ����ٶ�����״̬
   	case SYS_SUB4SUB8MENU4_RASPEED:
		g_nsysstatus=SYS_SUB4SUB8MENU4;	 //�Զ���
		break;
	//�˳���Զ����Ұ��ʾ״̬
	case SYS_SUB3SUB6SUB1LOV_TELTYPE1:
	    	g_nsysstatus=SYS_SUB3SUB6MENU1;
	    break;
	 //�˳�ʱ������
	case  SYS_SUB4SUB1_SETTIME:
	     if(g_mSysInitGuide==0)
		 {		  
	       g_nsysstatus=SYS_SUB4MENU1;
		  }
		break;
	//�˳�����ѡ��
    case SYS_SUB4SUB3SUN1_CITYSEL:
		 g_nsysstatus=SYS_SUB4SUB3MENU1;	
	   	break;
    //�˳��Զ���ص�
	case  SYS_SUB4SUB3_SETSITE:
	    g_nsysstatus=SYS_SUB4SUB3MENU2;
		break;

  	case SYS_RESET:	//�˳��ָ�����״̬ 
			 g_nsysstatus=SYS_SUB4MENU9;
		 break;
	
   	//����Զ����������˵���Զ����������Ӳ˵�
	case SYS_SUB4SUB7_TELAZIALT_ZERO:

	      if(g_mSysInitGuide==0)
		 {
		    g_nsysstatus=SYS_SUB4MENU6;
		  }
		  else
		  {
	
		    g_nsysstatus=SYS_SUB4SUB3MENU1;
		  }
		break;
	 case SYS_SUB3SUB2_STARRISESET:
			 g_nsysstatus=SYS_SUB2SUB9RA; //��������������ʾ
	    	break;

		  //�˳������Ѱ
		 case  SYS_SUB3SUB3_MOONPHASE:
		   g_nsysstatus=SYS_SUB3MENU3;
		 break;

	default:
	    FStopGoto();
	    break;
	}



}

////*******************************************************************

//*******************************************************************
//up����
void FKeyUp()
{
  switch(g_nsysstatus)
  {
    case SYS_MENUSHOW:
		
	   	 if(g_mShowMenurowEn==1)
		 {						
		    g_mShowMenurowEn=g_RecentNum;
		 } 
		 else
		 {
		    g_mShowMenurowEn--;
		 }
    	break;

	case SYS_MAINSHOWHELP:	
    	LCDRfrsh();	
         if(g_mmainhelpshow==1)
		 {
		   g_mmainhelpshow=10;
		 }
		 else
		 {
		   g_mmainhelpshow--;
		 }
		break;
   
  //��Զ��һ���˵�����ѭ��
    case SYS_MAINMENU1:
		g_nsysstatus=SYS_MAINMENU4;
		break;
	case SYS_MAINMENU2:
		g_nsysstatus=SYS_MAINMENU1;
		break;
	case SYS_MAINMENU3:
		g_nsysstatus=SYS_MAINMENU2;
		break;
	case SYS_MAINMENU4:
		g_nsysstatus=SYS_MAINMENU3;
		break;
	//��Զ�������˵�����ѭ��
	//��Զ��У���Ӳ˵�����ѭ��
	case SYS_SUB1MENU1:
//	    g_mShowMenurowCn11=4;
//	    g_mShowMenuFtCn11=9;
		g_mShowMenurowUn11=4;
	    g_mShowMenuFtUn11=4;
		g_mShowMenurowEn11=7;
	    g_mShowMenuFtEn11=8;
		g_nsysstatus=SYS_SUB1MENU7;
	    break;
	case SYS_SUB1MENU2:
	   DoMenurowFtCnFtEnAddDec(0,11);
		g_nsysstatus=SYS_SUB1MENU1;
		break;
	case SYS_SUB1MENU3:
	     DoMenurowFtCnFtEnAddDec(0,11);
		g_nsysstatus=SYS_SUB1MENU2;
		break;
	case SYS_SUB1MENU4:
	    DoMenurowFtCnFtEnAddDec(0,11);
		g_nsysstatus=SYS_SUB1MENU3;
	    break;
	case SYS_SUB1MENU5:
	    DoMenurowFtCnFtEnAddDec(0,11);
		g_nsysstatus=SYS_SUB1MENU4;
	    break;
		case SYS_SUB1MENU6:
	    DoMenurowFtCnFtEnAddDec(0,11);
		g_nsysstatus=SYS_SUB1MENU5;
	    break;
   case SYS_SUB1MENU7:
	   DoMenurowFtCnFtEnAddDec(0,11);
		g_nsysstatus=SYS_SUB1MENU6;
		break;

	 //Ŀ�굼���Ӳ˵�����ѭ��
	case SYS_SUB2MENU1:
//	    g_mShowMenurowCn12=4;
//	    g_mShowMenuFtCn12=9;
		g_mShowMenurowUn12=4;
	    g_mShowMenuFtUn12=9;
		g_mShowMenurowEn12=8;
	    g_mShowMenuFtEn12=5;
		g_nsysstatus=SYS_SUB2MENU13;
	    break;
	case SYS_SUB2MENU2:	
		 DoMenurowFtCnFtEnAddDec(0,12);
		g_nsysstatus=SYS_SUB2MENU1;
		break;
	case SYS_SUB2MENU3:
		DoMenurowFtCnFtEnAddDec(0,12);
		g_nsysstatus=SYS_SUB2MENU2;
		break;
	case SYS_SUB2MENU4:
		 DoMenurowFtCnFtEnAddDec(0,12);
		g_nsysstatus=SYS_SUB2MENU3;
		break;
	case SYS_SUB2MENU5:
		 DoMenurowFtCnFtEnAddDec(0,12);
		g_nsysstatus=SYS_SUB2MENU4;
	    break;
	case SYS_SUB2MENU6:
		DoMenurowFtCnFtEnAddDec(0,12);
		g_nsysstatus=SYS_SUB2MENU5;
		break;
	case SYS_SUB2MENU7:
		DoMenurowFtCnFtEnAddDec(0,12);
		g_nsysstatus=SYS_SUB2MENU6;
		break;
	case SYS_SUB2MENU8:
		DoMenurowFtCnFtEnAddDec(0,12);
		g_nsysstatus=SYS_SUB2MENU7;
		break;
	case SYS_SUB2MENU9:
		DoMenurowFtCnFtEnAddDec(0,12);
		g_nsysstatus=SYS_SUB2MENU8;
	    break;
	case SYS_SUB2MENU11:
		 DoMenurowFtCnFtEnAddDec(0,12);
		g_nsysstatus=SYS_SUB2MENU9;
		break;
	case SYS_SUB2MENU12:
		 DoMenurowFtCnFtEnAddDec(0,12);
		g_nsysstatus=SYS_SUB2MENU11;
		break;
	case SYS_SUB2MENU13:
		 DoMenurowFtCnFtEnAddDec(0,12);
		g_nsysstatus=SYS_SUB2MENU12;
		break;

	 //���������Ӳ˵�����ѭ��
	 case SYS_SUB3MENU1:
//	    g_mShowMenurowCn13=4; 		
//		g_mShowMenuFtCn13=7; 
	    g_mShowMenurowUn13=4;
	    g_mShowMenuFtUn13=6;		
		g_mShowMenurowEn13=8;		
		g_mShowMenuFtEn13=2;

		g_nsysstatus=SYS_SUB3MENU9;
	    break;
	case SYS_SUB3MENU2:
	    DoMenurowFtCnFtEnAddDec(0,13);
		g_nsysstatus=SYS_SUB3MENU1;
		break;
	case SYS_SUB3MENU3:
	   DoMenurowFtCnFtEnAddDec(0,13);
		g_nsysstatus=SYS_SUB3MENU2;
		break;
	case SYS_SUB3MENU4:
	   DoMenurowFtCnFtEnAddDec(0,13);
		g_nsysstatus=SYS_SUB3MENU3;
		break;
	case SYS_SUB3MENU5:
	   DoMenurowFtCnFtEnAddDec(0,13);
		g_nsysstatus=SYS_SUB3MENU4;
	    break;
	case SYS_SUB3MENU6:
	   DoMenurowFtCnFtEnAddDec(0,13);
		g_nsysstatus=SYS_SUB3MENU5;
		break;
	case SYS_SUB3MENU7:
	   DoMenurowFtCnFtEnAddDec(0,13);
		g_nsysstatus=SYS_SUB3MENU6;
		break;
	case SYS_SUB3MENU8:
	   DoMenurowFtCnFtEnAddDec(0,13);
		g_nsysstatus=SYS_SUB3MENU7;
		break;
	case SYS_SUB3MENU9:
	   DoMenurowFtCnFtEnAddDec(0,13);
		g_nsysstatus=SYS_SUB3MENU8;
		break;


	 //���������Ӳ˵�����ѭ��
	case SYS_SUB4MENU1:
//	     g_mShowMenurowCn14=4;
//		 g_mShowMenuFtCn14=7;
		 g_mShowMenurowUn14=4;
		 g_mShowMenuFtUn14=6;
		 g_mShowMenurowEn14=8;
		 g_mShowMenuFtEn14=2;
	 
		g_nsysstatus=SYS_SUB4MENU9;
	    break;
	case SYS_SUB4MENU2:
	   DoMenurowFtCnFtEnAddDec(0,14);
		g_nsysstatus=SYS_SUB4MENU1;
		break;
	case SYS_SUB4MENU3:
	    DoMenurowFtCnFtEnAddDec(0,14);
		g_nsysstatus=SYS_SUB4MENU2;
		break;
	case SYS_SUB4MENU4:
	   DoMenurowFtCnFtEnAddDec(0,14);
		g_nsysstatus=SYS_SUB4MENU3;
	    break;
	case SYS_SUB4MENU5:
	  DoMenurowFtCnFtEnAddDec(0,14);
		g_nsysstatus=SYS_SUB4MENU4;
		break;
	case SYS_SUB4MENU6:
	   DoMenurowFtCnFtEnAddDec(0,14);
		g_nsysstatus=SYS_SUB4MENU5;
		break;
	case SYS_SUB4MENU7:
	  DoMenurowFtCnFtEnAddDec(0,14);
		g_nsysstatus=SYS_SUB4MENU6;
		break;
	case SYS_SUB4MENU8:
	   DoMenurowFtCnFtEnAddDec(0,14);
		g_nsysstatus=SYS_SUB4MENU7;
	    break;
	case SYS_SUB4MENU9:
	   DoMenurowFtCnFtEnAddDec(0,14);
		g_nsysstatus=SYS_SUB4MENU8;
	    break;


	 //��Զ�������˵�����ѭ��

		//Ŀ��ͬ��
		case SYS_SUB1SUB4MENU2:
			   g_nsysstatus=SYS_SUB1SUB4MENU3;
			break;
		case SYS_SUB1SUB4MENU3:
		       g_nsysstatus=SYS_SUB1SUB4MENU2;
			  //FBeep(2);
			break;
	
//	case SYS_SUB2SUB2MENU12:
//	    DoMenurowFtCnFtEnAddDec(0,22);
//		g_nsysstatus=SYS_SUB2SUB2MENU11;
//		break;
	 //����������Ӳ˵�����ѭ��
	 case SYS_SUB2SUB3MENU1:
//	    g_mShowMenurowCn23=4;
//	    g_mShowMenuFtCn23=5;
	    g_mShowMenurowEn22=8;
		g_mShowMenuFtEn22=1;
		g_nsysstatus=SYS_SUB2SUB3MENU8;
	    break;
	case SYS_SUB2SUB3MENU2:
	    DoMenurowFtCnFtEnAddDec(0,23);
		g_nsysstatus=SYS_SUB2SUB3MENU1;
		break;
	case SYS_SUB2SUB3MENU3:
	     DoMenurowFtCnFtEnAddDec(0,23);
		g_nsysstatus=SYS_SUB2SUB3MENU2;
		break;
	case SYS_SUB2SUB3MENU4:
	     DoMenurowFtCnFtEnAddDec(0,23);
		g_nsysstatus=SYS_SUB2SUB3MENU3;
		break;
	case SYS_SUB2SUB3MENU5:
	     DoMenurowFtCnFtEnAddDec(0,23);
		g_nsysstatus=SYS_SUB2SUB3MENU4;
	    break;
	case SYS_SUB2SUB3MENU6:
	     DoMenurowFtCnFtEnAddDec(0,23);
		g_nsysstatus=SYS_SUB2SUB3MENU5;
		break;
	case SYS_SUB2SUB3MENU7:
	     DoMenurowFtCnFtEnAddDec(0,23);
		g_nsysstatus=SYS_SUB2SUB3MENU6;
		break;
	case SYS_SUB2SUB3MENU8:
	     DoMenurowFtCnFtEnAddDec(0,23);
		g_nsysstatus=SYS_SUB2SUB3MENU7;
		break;
  	 //�������Ӳ˵�����ѭ��
	case SYS_SUB2SUB5MENU1:
		g_nsysstatus=SYS_SUB2SUB5MENU3;
	    break;
	case SYS_SUB2SUB5MENU2:
		g_nsysstatus=SYS_SUB2SUB5MENU1;
		break;
	case SYS_SUB2SUB5MENU3:
		g_nsysstatus=SYS_SUB2SUB5MENU2;
		break;
	 //�Զ����Ǳ����Ӳ˵�����ѭ��
	 case SYS_SUB2SUB8MENU1:
		g_nsysstatus=SYS_SUB2SUB8MENU4;
	    break;
	case SYS_SUB2SUB8MENU2:
		g_nsysstatus=SYS_SUB2SUB8MENU1;
		break;
	case SYS_SUB2SUB8MENU3:
		g_nsysstatus=SYS_SUB2SUB8MENU2;
		break;
	case SYS_SUB2SUB8MENU4:
		g_nsysstatus=SYS_SUB2SUB8MENU3;
		break;
   //½��Ŀ�����Ӳ˵�����ѭ��
	case SYS_SUB2SUB11MENU1:
		g_nsysstatus=SYS_SUB2SUB11MENU3;
	    break;
	case SYS_SUB2SUB11MENU2:
		g_nsysstatus=SYS_SUB2SUB11MENU1;
		break;
	case SYS_SUB2SUB11MENU3:
		g_nsysstatus=SYS_SUB2SUB11MENU2;
		break;

	 //Ŀ���������Ӳ˵�����ѭ��
	case SYS_SUB3SUB6MENU1:
		g_nsysstatus=SYS_SUB3SUB6MENU2;
	    break;
	case SYS_SUB3SUB6MENU2:
		g_nsysstatus=SYS_SUB3SUB6MENU1;
		break;

	 //����Ұ�������Ӳ˵�����ѭ��
	case SYS_SUB3SUB8MENU1:
		g_nsysstatus=SYS_SUB3SUB8MENU2;
	    break;
	case SYS_SUB3SUB8MENU2:
		g_nsysstatus=SYS_SUB3SUB8MENU1;
		break;
	//�ص��������Ӳ˵�����ѭ��
	case SYS_SUB4SUB3MENU1:
		g_nsysstatus=SYS_SUB4SUB3MENU2;
	    break;
	case SYS_SUB4SUB3MENU2:
		g_nsysstatus=SYS_SUB4SUB3MENU1;
		break;



	//�����ٶ����Ӳ˵�����ѭ��
	case SYS_SUB4SUB8MENU1:
		g_nsysstatus=SYS_SUB4SUB8MENU4;
	    break;
	case SYS_SUB4SUB8MENU2:
		g_nsysstatus=SYS_SUB4SUB8MENU1;
		break;
	case SYS_SUB4SUB8MENU3:
		g_nsysstatus=SYS_SUB4SUB8MENU2;
		break;
	case SYS_SUB4SUB8MENU4:
		g_nsysstatus=SYS_SUB4SUB8MENU3;
		break;
	//*******************************
	//*******************************
	//��Զ���ײ�ʵ�ֵ�ѡ�� 
	case SYS_MAINSHOW:
	case SYS_SUB1SUB11RA_GEAR_ERROR_BEGIN: 	
	case SYS_SUB1SUB12DEC_GEAR_ERROR_BEGIN: 
	case SYS_SUB2SUN_PLANET1: //̫��ϵͳ����1 
    case  SYS_SUB2CON_OBJECT1:
    case  SYS_SUB2FS_OBJECT1: 			   
    case  SYS_SUB2MSR_OBJECT1:
    case  SYS_SUB2NGC_OBJECT1:
    case  SYS_SUB2IC_OBJECT1:
    case  SYS_SUB2SH2_OBJECT1:	
    case  SYS_SUB2BRT_OBJECT1:
    case  SYS_SUB2SAO_OBJECT1:
	 if(!g_mLandMark)
	 {
	 if((g_mGoto.m_nGoto)&&(g_mTelStatusSet!=1))////||((g_mGoto.m_nGoto)&&(g_mTelStatusSet!=1)))//if((g_mGoto.m_nGoto)&&(g_mTelStatusSet!=1))
	{
	     g_mZposModify=1;//�߶ȸ��ٵ��ڴ�
		 g_mhandtrackAlt=0;//���ָ��ʱ����Զ����Ŀ��λ��һ�£��ֶ����ں󣬾Ͳ�һ����
	
      }
	  else
	  {
	       if(g_mTelescopeConType==1)
		   { 		  	
			FHandControlTelescope(AXIS_DEC,DIRECT_UP,g_mHandSpeed);
			 
	
			}
		   else
		   {
			  FHandControlTelescope(AXIS_ALT,DIRECT_UP,g_mHandSpeed);
		   }

	   }
	   }
	   else
	   {
	   
	       if(g_mTelescopeConType==1)
		   { 		  	
			FHandControlTelescope(AXIS_DEC,DIRECT_UP,g_mHandSpeed);
			 
	
			}
		   else
		   {
			  FHandControlTelescope(AXIS_ALT,DIRECT_UP,g_mHandSpeed);
		   }
		  }

	   break;
				//�����γ�ز�����У��
    	case SYS_SUB1SUB12DEC_GEAR_ERROR: 
		    g_mTelAlt0=g_mTelAlt;//��סУ��ǰ��Զ����λ��
			if(g_mTelescopeConType==1)
	   		{
	      		FHandControlTelescope(AXIS_DEC,DIRECT_UP,3);
		  		g_mBackLashAxis=3;
			}
	   		else
	   		{
		  		FHandControlTelescope(AXIS_ALT,DIRECT_UP,3);
		  		g_mBackLashAxis=1;
	   		}
	    	g_mGearErrorAlign=true;//��Զ���Ƿ�����ִ����Ļز�У׼,true����ִ��,falseû��
			g_mTelGearErrorDecAlignDirect=2;//��Զ���ྭ�ز�У��ʱѡ�����еķ���,1��2��
			g_nsysstatus=SYS_SUB1SUB12DEC_GEAR_ERROR_ALIGN;
			break;	


    //��Զ����γ�߶Ȼز�У׼���ֶ�
	case SYS_SUB1SUB12DEC_GEAR_ERROR_ALIGN: 
		 if(g_mTelGearErrorDecAlignDirect==1)
		 {
			  if(g_mTelescopeConType==1)
			   {
			      FHandControlTelescope(AXIS_DEC,DIRECT_UP,3);
				}
			   else
			   {
				  FHandControlTelescope(AXIS_ALT,DIRECT_UP,3);
			   }
		 }
		break;
	  

	//�۲�Ŀ������/½��ѡ��
	case SYS_SUB4SUB5SKY:
		g_nsysstatus=SYS_SUB4SUB5LAND; 
	    break;
	case SYS_SUB4SUB5LAND:
		g_nsysstatus=SYS_SUB4SUB5SKY;
		break;	 
		 
	//�۲�Ŀ������/½��ѡ��
	case SYS_SUB4SUB6AZ:
		g_nsysstatus=SYS_SUB4SUB6EQ; 
	    break;
	case SYS_SUB4SUB6EQ:
		g_nsysstatus=SYS_SUB4SUB6AZ;
		break;
	//�ྭ��γ����
	case SYS_SUB2SUB9RA:
		g_nsysstatus=SYS_SUB2SUB9DEC; 
		g_mShowMenucolumn=5;
	    break;
	case SYS_SUB2SUB9DEC:
		g_nsysstatus=SYS_SUB2SUB9RA;
		g_mShowMenucolumn=6;
		break;	
	//ѭ����Զ������ѡ��״̬
	case SYS_SUB4SUB9EN:  //ѭ����Զ������ѡ���Ӳ˵�
	    g_nsysstatus=SYS_SUB4SUB9SPA;
		break;
	case SYS_SUB4SUB9SPA:  //ѭ����Զ������ѡ���Ӳ˵�
	    g_nsysstatus=SYS_SUB4SUB9ITA;
		break;
	case SYS_SUB4SUB9ITA:  //ѭ����Զ������ѡ���Ӳ˵�
	    g_nsysstatus=SYS_SUB4SUB9FRE;
		break;
	case SYS_SUB4SUB9FRE:  //ѭ����Զ������ѡ���Ӳ˵�
	    g_nsysstatus=SYS_SUB4SUB9GER;
		break;  
	case SYS_SUB4SUB9GER:  //ѭ����Զ������ѡ���Ӳ˵�
	    g_nsysstatus=SYS_SUB4SUB9EN;
		break; 
	//��ǰ���Ŀ�����ϲ�Ѱ
	//case SYS_SUB3SUB1NOW_APH: //ÿ������
    case SYS_SUB2SUB1NOW_OBJECT: //��ǰ���Ŀ��
	    if(g_mNowBestObjectNum==0)
		{
		   g_mNowBestObjectNum=g_mBestStarNum-1;
		 }
		 else
		 {
		   g_mNowBestObjectNum--;
		 }
 	break;  

	 //̫��ϵ���Ӳ˵�����ѭ��
	case SYS_SUB2SUN_PLANET:
	      LCDRfrsh();
	case SYS_SUB3SUB1NOW_APH ://ÿ������
		 
		 if(g_mSunSysObjectNum==0)
		 {
		   g_mSunSysObjectNum=9;
		 }
		 else
		 {
		    g_mSunSysObjectNum--;
		 }
		break;

	  //88�������ϲ���
	 case  SYS_SUB2CON_OBJECT:
	     LCDRfrsh();
	     g_mCon88ObjectNum--;
		  if(g_mCon88ObjectNum==0)
		 {
			g_mCon88ObjectNum=88;
		  }
	
		 break;
	 //�����������ϲ���
	   case  SYS_SUB2FS_OBJECT:
		  LCDRfrsh();
		  g_mFamousStarObjectNum--;
		  if(g_mFamousStarObjectNum==0)
		 {
			g_mFamousStarObjectNum=33;
		  }
		 break;

	   //Messier�Ǳ����ϲ���
	 case SYS_SUB2MSR_OBJECT0: //messier�Ǳ���� 
	 case SYS_SUB2MSR_OBJECT: 
	 	            LCDRfrsh();
	      g_mMsrObjectNum--;
		  if(g_mMsrObjectNum==0)
		 {
			g_mMsrObjectNum=110;
		  }
		 break;
	    //NGC�Ǳ����ϲ���
	   case  SYS_SUB2NGC_OBJECT:
	    LCDRfrsh();
		  g_mNgcObjectNum--;
		  if(g_mNgcObjectNum==0)
		 {
			g_mNgcObjectNum=7840;
		  }
		 break;
	   //IC�Ǳ����ϲ���
	   case  SYS_SUB2IC_OBJECT:
	    LCDRfrsh();
	      g_mIcObjectNum--;
		  if(g_mIcObjectNum==0)
		 {
			g_mIcObjectNum=5386;
		  }
		 break;
	   //SH2�Ǳ����ϲ���
	   case  SYS_SUB2SH2_OBJECT:  
	   	        LCDRfrsh();	     
		  g_mSh2ObjectNum--;
		  if(g_mSh2ObjectNum==0)
		 {
			g_mSh2ObjectNum=313;
		  }
		 break;
	   //Britht�Ǳ����ϲ���
	   case  SYS_SUB2BRT_OBJECT:
	   		 	 LCDRfrsh();
		  g_mBrightObjectNum--;
		  if(g_mBrightObjectNum==0)
		 {
			g_mBrightObjectNum=167;
		  }
		 break;
	   //SAO�Ǳ����ϲ���
	   case  SYS_SUB2SAO_OBJECT:
	   	 	LCDRfrsh();
		 g_mSaoObjectNum--;
		  if(g_mSaoObjectNum==0)
		 {
			g_mSaoObjectNum=258997;
		  }
		 break;

	
		 
		 //�Զ����Ǳ��Ӳ˵�����
	 	case SYS_MENU_SKY_NAME:	
			g_mShowMenucolumn=5;
			g_nsysstatus=SYS_MENU_SKY_DEC;
			break;

		case SYS_MENU_SKY_DEC:	
			g_mShowMenucolumn=6;
			g_nsysstatus=SYS_MENU_SKY_RA;
			break;
		case SYS_MENU_SKY_RA:	
			g_mShowMenucolumn=6;
			g_nsysstatus=SYS_MENU_SKY_NAME;
			break;


	    case  SYS_MENU_SKY_OBJECT:
		case  SYS_MENU_LAND_OBJECT:
		case SYS_F_SELFNUM :
			   switch(g_mFnum)
			   {
			      case 1:
						g_mFnum=7;
						break;
				  case 7:
						g_mFnum=4;
						break;
			   	  case 4:
						g_mFnum=1;
						break;

				  case 2:
						g_mFnum=8;
						break;
				  case 8:
						g_mFnum=5;
						break;
			   	  case 5:
						g_mFnum=2;
						break;

				 case 3:
						g_mFnum=9;
						break;
				  case 9:
						g_mFnum=6;
						break;
			   	  case 6:
						g_mFnum=3;
						break;

			   }
			  break;


	  	     //½��Ŀ���Ӳ˵�����	

		case SYS_MENU_LAND_NAME:
		    g_mShowMenucolumn=5;	
			g_nsysstatus=SYS_MENU_LAND_ALT;
			break;

		case SYS_MENU_LAND_ALT:	
		    g_mShowMenucolumn=5;
			g_nsysstatus=SYS_MENU_LAND_AZI;
			break;
		case SYS_MENU_LAND_AZI:	
		   g_mShowMenucolumn=6;
			g_nsysstatus=SYS_MENU_LAND_NAME;
			break;


  	 //ʱ�����ò������ϲ�˵�
	   case  SYS_SUB4SUB1_SETTIME:
		   if(g_mdatetime==0)
		   {
		       g_mdatetime=1;
		   }
		   else
		   {
		      g_mdatetime=0;
		   }
		   g_mShowMenucolumn=1;
		  break;
	//�Զ���ص�����ѭ��
    case  SYS_SUB4SUB3SUB2_SELECT:
		g_nsysstatus=SYS_SUB4SUB3SUB2_MODIFY;
		break;
	case  SYS_SUB4SUB3SUB2_ADD:
		g_nsysstatus=SYS_SUB4SUB3SUB2_SELECT;
		break;
	case  SYS_SUB4SUB3SUB2_DELETE:
		g_nsysstatus=SYS_SUB4SUB3SUB2_ADD;
		break;
	case  SYS_SUB4SUB3SUB2_MODIFY:
		g_nsysstatus=SYS_SUB4SUB3SUB2_DELETE;
		break;
	case  SYS_SUB4SUB3_SETSITE: 
		
				if(g_mMySiteShowMode==0)
				{
					g_mMySiteShowMode=3;
					g_mShowMenucolumn=7;
				}
				else
				{
					g_mMySiteShowMode--;
					g_mShowMenucolumn=7;
				}
		
		break;
		  

		 case SYS_SUB4SUB7_TELAZIALT_ZERO: //��Զ�����Ӳ˵�

		    g_nsysstatus=SYS_SUB4SUB7_TELAZIALT_ZERO;
	    	if(	g_mTelZeroShowMode>0)
			{
			  g_mTelZeroShowMode--;
			 }
			 else
			 {
			    g_mTelZeroShowMode=1;
			   }
			   if(g_mTelZeroShowMode==0)
			   {
		         g_mShowMenucolumn=5;
				}
				 else
				 {
				 g_mShowMenucolumn=6;
				 }
			break;	

		 //�������
	    case SYS_SUB3SUB3_MOONPHASE	:			  
				g_mMoonPhaseYear--; 
			 break;	  

		case SYS_SUB1SUB2STAR_ALIGN	:
		   if(g_nAlignPoint)
		   {
		      g_mZposModify=1;//�߶ȸ��ٵ��ڴ�
			  g_mhandtrackAlt=0;//���ָ��ʱ����Զ����Ŀ��λ��һ�£��ֶ����ں󣬾Ͳ�һ����
		   }
		   else
		   {
          	if(g_nSelAlignStarNum==1)
			{
			  g_nSelAlignStarNum=g_mAlignStarNum;
			 }
			 else
			 {	
			     g_nSelAlignStarNum--;
			 }
		   }	  

		     break; 

	case SYS_SUB3SUB6SUB2M_MF:   //���ʼ�����������������״̬״̬ת��
	     g_nsysstatus=SYS_SUB3SUB6SUB2M_SF;
		 g_mShowMenucolumn=7;
	    break;
	case SYS_SUB3SUB6SUB2M_SF:   ///���ʼ�����������������״̬ת��
	     g_nsysstatus=SYS_SUB3SUB6SUB2M_MF;
		 g_mShowMenucolumn=7;
	    break; 

   	case SYS_SUB3SUB6SUB2M_MF1:   //���ʼ�����������������״̬״̬ת��
	     g_nsysstatus=SYS_SUB3SUB6SUB2M_MFOV;
		 g_mShowMenucolumn=7;
	    break;
	case SYS_SUB3SUB6SUB2M_MFOV:   ///���ʼ�����������������״̬ת��
	     g_nsysstatus=SYS_SUB3SUB6SUB2M_SF1;
		 g_mShowMenucolumn=7;
	    break; 
	case SYS_SUB3SUB6SUB2M_SF1:   ///���ʼ�����������������״̬ת��
	     g_nsysstatus=SYS_SUB3SUB6SUB2M_MF1;
		 g_mShowMenucolumn=7;
	    break; 

	//��Ұ�Ӳ˵�����ѭ��
	case SYS_SUB3SUB6SUB1MENU1:
	    g_nsysstatus=SYS_SUB3SUB6SUB1MENU3;
	    break;
	case SYS_SUB3SUB6SUB1MENU2:
	    g_nsysstatus=SYS_SUB3SUB6SUB1MENU1;
	    break;
	case SYS_SUB3SUB6SUB1MENU3:
	    g_nsysstatus=SYS_SUB3SUB6SUB1MENU2;
	    break;
	//����Ƶ���
	case SYS_SUB3SUB8MENU1Screen:
		if(g_mVir_BL==0)
		{
			LCDBacklight(63);
			g_mVir_BL=63;
		}
		else if(g_mVir_BL==63)
		{
			LCDBacklight(127);
			g_mVir_BL=127;
		}
		else if(g_mVir_BL==127)
		{
			LCDBacklight(191);
			g_mVir_BL=191;
		}
		else
		{
			LCDBacklight(255);
			g_mVir_BL=255;
		}
		break;
	case SYS_SUB4SUB3SUN1_CITYSEL:
		 	LCDRfrsh();
	     FindCountryDec();
		break;
	case  SYS_SUB2SUB11_SET: 
		switch(g_mMyLandmarkOperator)
		{
			case 0:	//ѡ��			
			case 2:	//ɾ��
				if(CustomLandmarkNum_temp==0)
					CustomLandmarkNum_temp=(CustomLandmarkNum-1);
				else
					CustomLandmarkNum_temp--;			  									
					break;	
			case 1:	//���
				if(g_mMyLandmarkShowMode==0)
				{
					g_mMyLandmarkShowMode=2;
					g_mShowMenucolumn=7;
				}
				else
				{
					g_mMyLandmarkShowMode--;
					g_mShowMenucolumn=7;
				}
			default:
				break;
		}
		break;
	case  SYS_SUB2SUB8_SET: 
		switch(g_mMyStarOperator)
		{
			case 0:	//ѡ��			
			case 2:	 //ɾ��
				if(CustomStarNum_temp==0)
					CustomStarNum_temp=(CustomStarNum-1);
				else
					CustomStarNum_temp--;			  									
					break;	
			case 1:	//���
			case 3:	//�޸�
				if(g_mMyStarShowMode==0)
				{
					g_mMyStarShowMode=2;
					g_mShowMenucolumn=7;
				}
				else
				{
					g_mMyStarShowMode--;
					g_mShowMenucolumn=7;
				}
			default:
				break;
		}
		break;
	   //��������ʱ����
		case SYS_SUB4SUB2MENU1:
		    if(g_mSysInitGuide==1)
			{
			g_nsysstatus=SYS_SUB4SUB2MENU2;
			g_mDaylight=false;
			}
	    	break;
		case SYS_SUB4SUB2MENU2:
			if(g_mSysInitGuide==1)
			{
			g_nsysstatus=SYS_SUB4SUB2MENU1;
			g_mDaylight=true;
			}
	    	break;
	default:
		break ;
	}
}
//*******************************************************************


//*******************************************************************
//down����
void FKeyDown()
{
  switch(g_nsysstatus)
  {
    
	case SYS_MENUSHOW:
	   if(g_mShowMenurowEn==g_RecentNum)
		 {						
		    g_mShowMenurowEn=1;
		 } 
		 else
		 {
		    g_mShowMenurowEn++;
		 }
    	break;
	case SYS_MAINSHOWHELP:	
	     LCDRfrsh();	
         if(g_mmainhelpshow==10)
		 {
		   g_mmainhelpshow=1;
		 }
		 else
		 {
		   g_mmainhelpshow++;
		 }
		break;

   //��Զ��һ���˵�����ѭ��
    case SYS_MAINMENU1:
			g_nsysstatus=SYS_MAINMENU2;
		break;
	case SYS_MAINMENU2:
		g_nsysstatus=SYS_MAINMENU3;
		break;
	case SYS_MAINMENU3:
		g_nsysstatus=SYS_MAINMENU4;
		break;
	case SYS_MAINMENU4:
		g_nsysstatus=SYS_MAINMENU1;
		break;
    //��Զ�������˵�����ѭ��
	//��Զ��У���Ӳ˵�����ѭ��
	case SYS_SUB1MENU1:
	    DoMenurowFtCnFtEnAddDec(1,11);
		g_nsysstatus=SYS_SUB1MENU2;
		break;
	case SYS_SUB1MENU2:
	    DoMenurowFtCnFtEnAddDec(1,11);
		g_nsysstatus=SYS_SUB1MENU3;
		break;
	case SYS_SUB1MENU3:
	    DoMenurowFtCnFtEnAddDec(1,11);
		g_nsysstatus=SYS_SUB1MENU4;
		break;
	case SYS_SUB1MENU4:
	    DoMenurowFtCnFtEnAddDec(1,11);
		g_nsysstatus=SYS_SUB1MENU5;
		break;
	case SYS_SUB1MENU5:
	    DoMenurowFtCnFtEnAddDec(1,11);
		g_nsysstatus=SYS_SUB1MENU6;
		break;
	case SYS_SUB1MENU6:
	    DoMenurowFtCnFtEnAddDec(1,11);
		g_nsysstatus=SYS_SUB1MENU7;
		break;
	case SYS_SUB1MENU7:	
//		  g_mShowMenurowCn11=1;
//		  g_mShowMenuFtCn11=1;
		  g_mShowMenurowUn11=1;
		  g_mShowMenuFtUn11=1;
	      g_mShowMenurowEn11=1;
	      g_mShowMenuFtEn11=1;		 
		  g_nsysstatus=SYS_SUB1MENU1;
		break;


	 //Ŀ�굼���Ӳ˵�����ѭ��
	case SYS_SUB2MENU1:
	   DoMenurowFtCnFtEnAddDec(1,12);
		g_nsysstatus=SYS_SUB2MENU2;
	    break;
	case SYS_SUB2MENU2:
	    DoMenurowFtCnFtEnAddDec(1,12);
		g_nsysstatus=SYS_SUB2MENU3;
		break;
	case SYS_SUB2MENU3:
		DoMenurowFtCnFtEnAddDec(1,12);
		g_nsysstatus=SYS_SUB2MENU4;
		break;
	case SYS_SUB2MENU4:
		 DoMenurowFtCnFtEnAddDec(1,12);
		g_nsysstatus=SYS_SUB2MENU5;
		break;
	case SYS_SUB2MENU5:
		DoMenurowFtCnFtEnAddDec(1,12);
		g_nsysstatus=SYS_SUB2MENU6;
	    break;
	case SYS_SUB2MENU6:
		DoMenurowFtCnFtEnAddDec(1,12);
		g_nsysstatus=SYS_SUB2MENU7;
		break;
	case SYS_SUB2MENU7:
		DoMenurowFtCnFtEnAddDec(1,12);
		g_nsysstatus=SYS_SUB2MENU8;
		break;
	case SYS_SUB2MENU8:
		DoMenurowFtCnFtEnAddDec(1,12);
		g_nsysstatus=SYS_SUB2MENU9;
		break;
	case SYS_SUB2MENU9:
		 DoMenurowFtCnFtEnAddDec(1,12);
		g_nsysstatus=SYS_SUB2MENU11;
	    break;
   case SYS_SUB2MENU11:
		 DoMenurowFtCnFtEnAddDec(1,12);
		g_nsysstatus=SYS_SUB2MENU12;
	    break;
   case SYS_SUB2MENU12:
		 DoMenurowFtCnFtEnAddDec(1,12);
		g_nsysstatus=SYS_SUB2MENU13;
	    break;
	case SYS_SUB2MENU13:	
//		  g_mShowMenurowCn12=1;
//		  g_mShowMenuFtCn12=1;
		  g_mShowMenurowUn12=1;
		  g_mShowMenuFtUn12=1;
	      g_mShowMenurowEn12=1;
	      g_mShowMenuFtEn12=1;		 
		g_nsysstatus=SYS_SUB2MENU1;
		break;

	 //���������Ӳ˵�����ѭ��
	case SYS_SUB3MENU1:
		DoMenurowFtCnFtEnAddDec(1,13);
		g_nsysstatus=SYS_SUB3MENU2;
	    break;
	case SYS_SUB3MENU2:
	   DoMenurowFtCnFtEnAddDec(1,13);
		g_nsysstatus=SYS_SUB3MENU3;
		break;
	case SYS_SUB3MENU3:
	   DoMenurowFtCnFtEnAddDec(1,13);
		g_nsysstatus=SYS_SUB3MENU4;
		break;
	case SYS_SUB3MENU4:
	    DoMenurowFtCnFtEnAddDec(1,13);
		g_nsysstatus=SYS_SUB3MENU5;
		break;
	case SYS_SUB3MENU5:
	   DoMenurowFtCnFtEnAddDec(1,13);
		g_nsysstatus=SYS_SUB3MENU6;
	    break;
	case SYS_SUB3MENU6:
	   DoMenurowFtCnFtEnAddDec(1,13);
		g_nsysstatus=SYS_SUB3MENU7;
		break;
	case SYS_SUB3MENU7:
	   DoMenurowFtCnFtEnAddDec(1,13);
		g_nsysstatus=SYS_SUB3MENU8;
		break;
	case SYS_SUB3MENU8:
	   DoMenurowFtCnFtEnAddDec(1,13);
		g_nsysstatus=SYS_SUB3MENU9;
		break;
	case SYS_SUB3MENU9:
	    
//		  g_mShowMenurowCn13=1;
//	      g_mShowMenuFtCn13=1;
		  g_mShowMenurowUn13=1;
	      g_mShowMenuFtUn13=1;
		  g_mShowMenurowEn13=1;
	      g_mShowMenuFtEn13=1;
	 
		g_nsysstatus=SYS_SUB3MENU1;
		break; 
	 //���������Ӳ˵�����ѭ��
	case SYS_SUB4MENU1:
	    DoMenurowFtCnFtEnAddDec(1,14);
		g_nsysstatus=SYS_SUB4MENU2;
	    break;
	case SYS_SUB4MENU2:
	     DoMenurowFtCnFtEnAddDec(1,14);
		g_nsysstatus=SYS_SUB4MENU3;
		break;
	case SYS_SUB4MENU3:
	    DoMenurowFtCnFtEnAddDec(1,14);
		g_nsysstatus=SYS_SUB4MENU4;
		break;
	case SYS_SUB4MENU4:
	    DoMenurowFtCnFtEnAddDec(1,14);
		g_nsysstatus=SYS_SUB4MENU5;
	    break;
	case SYS_SUB4MENU5:
	     DoMenurowFtCnFtEnAddDec(1,14);
		g_nsysstatus=SYS_SUB4MENU6;
		break;
	case SYS_SUB4MENU6:
	    DoMenurowFtCnFtEnAddDec(1,14);
		g_nsysstatus=SYS_SUB4MENU7;
		break;
	case SYS_SUB4MENU7:
	    DoMenurowFtCnFtEnAddDec(1,14);
		g_nsysstatus=SYS_SUB4MENU8;
		break;	 
	case SYS_SUB4MENU8:
	    DoMenurowFtCnFtEnAddDec(1,14);
		g_nsysstatus=SYS_SUB4MENU9;
		break;	  
	case SYS_SUB4MENU9:
//	    g_mShowMenurowCn14=1;
//	    g_mShowMenuFtCn14=1;
		g_mShowMenurowUn14=1;
	    g_mShowMenuFtUn14=1;
	    g_mShowMenurowEn14=1;
		g_mShowMenuFtEn14=1;
		
		g_nsysstatus=SYS_SUB4MENU1;
		break;
	 //��Զ�������˵�����ѭ��
		 
  	 //��Զ��ͬ��
  		case SYS_SUB1SUB4MENU2:
			  g_nsysstatus=SYS_SUB1SUB4MENU3;
			break;
		case SYS_SUB1SUB4MENU3:
		      g_nsysstatus=SYS_SUB1SUB4MENU2;
			  //FBeep(2);
			break ;



//	case SYS_SUB2SUB2MENU11:
//	 	DoMenurowFtCnFtEnAddDec(1,22);
//		g_nsysstatus=SYS_SUB2SUB2MENU12;
//		break;
	case SYS_SUB2SUB2MENU11:
//	    g_mShowMenurowCn22=1;
//	    g_mShowMenuFtCn22=1;
	    g_mShowMenurowEn22=1;
		g_mShowMenuFtEn22=1;
		g_nsysstatus=SYS_SUB2SUB2MENU1;
		break;
	 //����������Ӳ˵�����ѭ��
	 case SYS_SUB2SUB3MENU1:
	  	DoMenurowFtCnFtEnAddDec(1,23);
		g_nsysstatus=SYS_SUB2SUB3MENU2;
	    break;
	case SYS_SUB2SUB3MENU2:
	 	DoMenurowFtCnFtEnAddDec(1,23);
		g_nsysstatus=SYS_SUB2SUB3MENU3;
		break;
	case SYS_SUB2SUB3MENU3:
	 	DoMenurowFtCnFtEnAddDec(1,23);
		g_nsysstatus=SYS_SUB2SUB3MENU4;
		break;
	case SYS_SUB2SUB3MENU4:
	 	DoMenurowFtCnFtEnAddDec(1,23);
		g_nsysstatus=SYS_SUB2SUB3MENU5;
		break;
	case SYS_SUB2SUB3MENU5:
	 	DoMenurowFtCnFtEnAddDec(1,23);
		g_nsysstatus=SYS_SUB2SUB3MENU6;
	    break;
	case SYS_SUB2SUB3MENU6:
	 	DoMenurowFtCnFtEnAddDec(1,23);
		g_nsysstatus=SYS_SUB2SUB3MENU7;
		break;
	case SYS_SUB2SUB3MENU7:
	 	DoMenurowFtCnFtEnAddDec(1,23);
		g_nsysstatus=SYS_SUB2SUB3MENU8;
		break;
	case SYS_SUB2SUB3MENU8:
//	     g_mShowMenurowCn23=1;
//	    g_mShowMenuFtCn23=1;
	    g_mShowMenurowEn23=1;
		g_mShowMenuFtEn23=1;
		g_nsysstatus=SYS_SUB2SUB3MENU1;
		break;
  	 //�������Ӳ˵�����ѭ��
	case SYS_SUB2SUB5MENU1:
		g_nsysstatus=SYS_SUB2SUB5MENU2;
	    break;
	case SYS_SUB2SUB5MENU2:
		g_nsysstatus=SYS_SUB2SUB5MENU3;
		break;
	case SYS_SUB2SUB5MENU3:
		g_nsysstatus=SYS_SUB2SUB5MENU1;
		break;
	 //�Զ����Ǳ����Ӳ˵�����ѭ��
	 case SYS_SUB2SUB8MENU1:
		g_nsysstatus=SYS_SUB2SUB8MENU2;
	    break;
	case SYS_SUB2SUB8MENU2:
		g_nsysstatus=SYS_SUB2SUB8MENU3;
		break;
	case SYS_SUB2SUB8MENU3:
		g_nsysstatus=SYS_SUB2SUB8MENU4;
		break;
	case SYS_SUB2SUB8MENU4:
		g_nsysstatus=SYS_SUB2SUB8MENU1;
		break;
   //½��Ŀ�����Ӳ˵�����ѭ��
	case SYS_SUB2SUB11MENU1:
		g_nsysstatus=SYS_SUB2SUB11MENU2;
	    break;
	case SYS_SUB2SUB11MENU2:
		g_nsysstatus=SYS_SUB2SUB11MENU3;
		break;
	case SYS_SUB2SUB11MENU3:
		g_nsysstatus=SYS_SUB2SUB11MENU1;
		break;

	 //Ŀ���������Ӳ˵�����ѭ��
	case SYS_SUB3SUB6MENU1:
		g_nsysstatus=SYS_SUB3SUB6MENU2;
	    break;
	case SYS_SUB3SUB6MENU2:
		g_nsysstatus=SYS_SUB3SUB6MENU1;
		break;

	 //����Ұ�������Ӳ˵�����ѭ��
	case SYS_SUB3SUB8MENU1:
		g_nsysstatus=SYS_SUB3SUB8MENU2;
	    break;
	case SYS_SUB3SUB8MENU2:
		g_nsysstatus=SYS_SUB3SUB8MENU1;
		break;
	//�ص��������Ӳ˵�����ѭ��
	case SYS_SUB4SUB3MENU1:
		g_nsysstatus=SYS_SUB4SUB3MENU2;
	    break;
	case SYS_SUB4SUB3MENU2:
		g_nsysstatus=SYS_SUB4SUB3MENU1;
		break;



	//�����ٶ����Ӳ˵�����ѭ��
	case SYS_SUB4SUB8MENU1:
		g_nsysstatus=SYS_SUB4SUB8MENU2;
	    break;
	case SYS_SUB4SUB8MENU2:
		g_nsysstatus=SYS_SUB4SUB8MENU3;
		break;
	case SYS_SUB4SUB8MENU3:
		g_nsysstatus=SYS_SUB4SUB8MENU4;
		break;
	case SYS_SUB4SUB8MENU4:
		g_nsysstatus=SYS_SUB4SUB8MENU1;
		break;
	//*******************************
	//*******************************
	//��Զ���ײ�ʵ�ֵ�ѡ��
	case SYS_MAINSHOW:
	case SYS_SUB1SUB11RA_GEAR_ERROR_BEGIN: 	
	case SYS_SUB1SUB12DEC_GEAR_ERROR_BEGIN: 
//	case SYS_SUB1SUB1AUTOSTAR_ALIGN:
		case SYS_SUB2SUN_PLANET1: //̫��ϵͳ����1 
   case  SYS_SUB2CON_OBJECT1:
   case  SYS_SUB2FS_OBJECT1: 			   
   case  SYS_SUB2MSR_OBJECT1:
   case  SYS_SUB2NGC_OBJECT1:
   case  SYS_SUB2IC_OBJECT1:
   case  SYS_SUB2SH2_OBJECT1:	
   case  SYS_SUB2BRT_OBJECT1:
   case  SYS_SUB2SAO_OBJECT1:
   if(!g_mLandMark)
   {
      if((g_mGoto.m_nGoto)&&(g_mTelStatusSet!=1))////||((g_mGoto.m_nGoto)&&(g_mTelStatusSet!=1)))//if((g_mGoto.m_nGoto)&&(g_mTelStatusSet!=1))
	  {
   	   	   g_mZposModify=-1;//�߶ȸ��ٵ��ڴ�
		   g_mhandtrackAlt=0;//���ָ��ʱ����Զ����Ŀ��λ��һ�£��ֶ����ں󣬾Ͳ�һ����
      }
	  else
	  {
		   if(g_mTelescopeConType==1)
		   {
		      FHandControlTelescope(AXIS_DEC,DIRECT_DOWN,g_mHandSpeed);
			
			}
		   else
		   {
			  FHandControlTelescope(AXIS_ALT,DIRECT_DOWN,g_mHandSpeed);
	       }
	   }
	  }
	  else
	  {
	    if(g_mTelescopeConType==1)
		   {
		      FHandControlTelescope(AXIS_DEC,DIRECT_DOWN,g_mHandSpeed);
			
			}
		   else
		   {
			  FHandControlTelescope(AXIS_ALT,DIRECT_DOWN,g_mHandSpeed);
	       }
	  }
	   break;

			//�����γ�ز�����У��
    	case SYS_SUB1SUB12DEC_GEAR_ERROR: 
		    g_mTelAlt0=g_mTelAlt;//��סУ��ǰ��Զ����λ��
						
			if(g_mTelescopeConType==1)
	   		{
	      		FHandControlTelescope(AXIS_DEC,DIRECT_DOWN,3);
		  		g_mBackLashAxis=3;
			}
	   		else
	   		{
		  		FHandControlTelescope(AXIS_ALT,DIRECT_DOWN,3);
		  		g_mBackLashAxis=1;
	   		}
	    	g_mGearErrorAlign=true;//��Զ���Ƿ�����ִ����Ļز�У׼,true����ִ��,falseû��
			g_mTelGearErrorDecAlignDirect=1;//��Զ���ྭ�ز�У��ʱѡ�����еķ���,1��2��
			g_nsysstatus=SYS_SUB1SUB12DEC_GEAR_ERROR_ALIGN;
			break;	


    //��Զ����γ�߶Ȼز�У׼���ֶ�
	case SYS_SUB1SUB12DEC_GEAR_ERROR_ALIGN: 
		 if(g_mTelGearErrorDecAlignDirect==2)
		 {
			  if(g_mTelescopeConType==1)
			   {
			      FHandControlTelescope(AXIS_DEC,DIRECT_DOWN,3);
				}
			   else
			   {
				  FHandControlTelescope(AXIS_ALT,DIRECT_DOWN,3);
			   }
		 }
		break;



	//�۲�Ŀ������/½��ѡ��
	case SYS_SUB4SUB5SKY:
		g_nsysstatus=SYS_SUB4SUB5LAND; 
	    break;
	case SYS_SUB4SUB5LAND:
		g_nsysstatus=SYS_SUB4SUB5SKY;
		break;	 
		 
	//�۲�Ŀ������/½��ѡ��
	case SYS_SUB4SUB6AZ:
		g_nsysstatus=SYS_SUB4SUB6EQ; 
	    break;
	case SYS_SUB4SUB6EQ:
		g_nsysstatus=SYS_SUB4SUB6AZ;
		break;

	//ѭ����Զ������ѡ��״̬
	case SYS_SUB4SUB9EN:  //ѭ����Զ������ѡ���Ӳ˵�
	    g_nsysstatus=SYS_SUB4SUB9GER;
		break;
	case SYS_SUB4SUB9GER:  //ѭ����Զ������ѡ���Ӳ˵�
	    g_nsysstatus=SYS_SUB4SUB9FRE;
		break;
	case SYS_SUB4SUB9FRE:  //ѭ����Զ������ѡ���Ӳ˵�
	    g_nsysstatus=SYS_SUB4SUB9ITA;
		break;
	case SYS_SUB4SUB9ITA:  //ѭ����Զ������ѡ���Ӳ˵�
	    g_nsysstatus=SYS_SUB4SUB9SPA;
		break; 
	case SYS_SUB4SUB9SPA:  //ѭ����Զ������ѡ���Ӳ˵�
	    g_nsysstatus=SYS_SUB4SUB9EN;
		break; 

	//��ǰ���Ŀ�����²�Ѱ
//	case SYS_SUB3SUB1NOW_APH: //ÿ������
    case SYS_SUB2SUB1NOW_OBJECT: //��ǰ���Ŀ��

	    if(g_mNowBestObjectNum==g_mBestStarNum-1)
		{
		   g_mNowBestObjectNum=0;
		 }
		 else
		 {
		   g_mNowBestObjectNum++;
		 }
 	break; 

	 //�Ǳ����
	case SYS_SUB2SUN_PLANET:
	      LCDRfrsh();
	case SYS_SUB3SUB1NOW_APH:
		 g_mSunSysObjectNum++;
		 if(g_mSunSysObjectNum>9)
		 {
		   g_mSunSysObjectNum=0;
		 }
		break;

	  //88�������²���
	 case  SYS_SUB2CON_OBJECT:
	    LCDRfrsh();
	     g_mCon88ObjectNum++;
		  if(g_mCon88ObjectNum>88)
		 {
			g_mCon88ObjectNum=1;
		  }
	
		 break;
	 //�����������²���
	   case  SYS_SUB2FS_OBJECT:
		  LCDRfrsh();
		  g_mFamousStarObjectNum++;
		  if(g_mFamousStarObjectNum>33)
		 {
			g_mFamousStarObjectNum=1;
		  }
		 break;

	   //Messier�Ǳ����²���
	 case SYS_SUB2MSR_OBJECT0: //messier�Ǳ���� 
     case SYS_SUB2MSR_OBJECT: 
	 	            LCDRfrsh();
	      g_mMsrObjectNum++;
		  if(g_mMsrObjectNum>110)
		 {
			g_mMsrObjectNum=1;
		  }
		 break;
	    //NGC�Ǳ����²���
	   case  SYS_SUB2NGC_OBJECT:
	    LCDRfrsh();
		  g_mNgcObjectNum++;
		  if(g_mNgcObjectNum>7840)
		 {
			g_mNgcObjectNum=1;
		  }
		 break;
	   //IC�Ǳ����²���
	   case  SYS_SUB2IC_OBJECT:
	    LCDRfrsh();
	      g_mIcObjectNum++;
		  if(g_mIcObjectNum>5386)
		 {
			g_mIcObjectNum=1;
		  }
		 break;
	   //SH2�Ǳ����²���
	   case  SYS_SUB2SH2_OBJECT:  

	   	        LCDRfrsh();	     
		  g_mSh2ObjectNum++;
		  if(g_mSh2ObjectNum>313)
		 {
			g_mSh2ObjectNum=1;
		  }
		 break;
	   //Britht�Ǳ����²���
	   case  SYS_SUB2BRT_OBJECT:
	   		 	 LCDRfrsh();
		  g_mBrightObjectNum++;
		  if(g_mBrightObjectNum>167)
		 {
			g_mBrightObjectNum=1;
		  }
		 break;
	   //SAO�Ǳ����²���
	   case  SYS_SUB2SAO_OBJECT:
	   	 	LCDRfrsh();
		 g_mSaoObjectNum++;
		  if(g_mSaoObjectNum>258997)
		 {
			g_mSaoObjectNum=1;
		  }
		 break;	
		 
		 //�Զ����Ǳ��Ӳ˵�����
	 	case SYS_MENU_SKY_NAME:	
			g_mShowMenucolumn=6;
			g_nsysstatus=SYS_MENU_SKY_RA;
			break;

		case SYS_MENU_SKY_RA:	
			g_mShowMenucolumn=5;
			g_nsysstatus=SYS_MENU_SKY_DEC;
			break;
		case SYS_MENU_SKY_DEC:	
			g_mShowMenucolumn=6;
			g_nsysstatus=SYS_MENU_SKY_NAME;
			break;
		 
		case  SYS_MENU_SKY_OBJECT:
		case  SYS_MENU_LAND_OBJECT:
		case SYS_F_SELFNUM :
			   switch(g_mFnum)
			   {
			      case 1:
						g_mFnum=4;
						break;
				  case 4:
						g_mFnum=7;
						break;
			   	  case 7:
						g_mFnum=1;
						break;

				  case 2:
						g_mFnum=5;
						break;
				  case 5:
						g_mFnum=8;
						break;
			   	  case 8:
						g_mFnum=2;
						break;

				 case 3:
						g_mFnum=6;
						break;
				  case 6:
						g_mFnum=9;
						break;
			   	  case 9:
						g_mFnum=3;
						break;

			   }
			  break;

		//�ྭ��γ����
		case SYS_SUB2SUB9RA:
			g_nsysstatus=SYS_SUB2SUB9DEC; 
			g_mShowMenucolumn=5;
		    break;
		case SYS_SUB2SUB9DEC:
			g_nsysstatus=SYS_SUB2SUB9RA;
			g_mShowMenucolumn=6;
			break;	

	   //½��Ŀ���Ӳ˵�����	

		case SYS_MENU_LAND_NAME:
		 g_mShowMenucolumn=5;	
			g_nsysstatus=SYS_MENU_LAND_AZI;
			break;

		case SYS_MENU_LAND_AZI:	
		    g_mShowMenucolumn=5;
			g_nsysstatus=SYS_MENU_LAND_ALT;
			break;
		case SYS_MENU_LAND_ALT:	
		   g_mShowMenucolumn=6;
			g_nsysstatus=SYS_MENU_LAND_NAME;
			break;
		
	 //ʱ�����ò������ϲ�˵�
	   case  SYS_SUB4SUB1_SETTIME:
		   if(g_mdatetime==0)
		   {
		       g_mdatetime=1;
		   }
		   else
		   {
		      g_mdatetime=0;
		   }
		   g_mShowMenucolumn=1;
		  break;	
	 //�Զ���ص�����ѭ��
       
       case  SYS_SUB4SUB3SUB2_SELECT:
		    g_nsysstatus=SYS_SUB4SUB3SUB2_ADD;
		  break;
	   case  SYS_SUB4SUB3SUB2_ADD :
		    g_nsysstatus=SYS_SUB4SUB3SUB2_DELETE;
		  break;
	   case  SYS_SUB4SUB3SUB2_DELETE:
		    g_nsysstatus=SYS_SUB4SUB3SUB2_MODIFY;
		  break;
	   case  SYS_SUB4SUB3SUB2_MODIFY:
		    g_nsysstatus=SYS_SUB4SUB3SUB2_SELECT;
		  break;	
	   case  SYS_SUB4SUB3_SETSITE: 

					if(g_mMySiteShowMode==3)
					{
						g_mMySiteShowMode=0;
						g_mShowMenucolumn=7;
					}
					else
					{
						g_mMySiteShowMode++;
						g_mShowMenucolumn=7;
					}
			
			break;
		case SYS_SUB4SUB7_TELAZIALT_ZERO: //��Զ�����Ӳ˵�
		    g_nsysstatus=SYS_SUB4SUB7_TELAZIALT_ZERO;
	    	if(	g_mTelZeroShowMode<1)
			{
			  g_mTelZeroShowMode++;
			 }
			 else
			 {
			    g_mTelZeroShowMode=0;
			   }
		      if(g_mTelZeroShowMode==0)
			   {
		         g_mShowMenucolumn=5;
				}
				 else
				 {
				 g_mShowMenucolumn=6;
				 }
			break;	
	   //�������
	    case SYS_SUB3SUB3_MOONPHASE	:			  
				 g_mMoonPhaseYear++;
				break;
		
		case SYS_SUB1SUB2STAR_ALIGN	:
		   if(g_nAlignPoint)
		   {
		   	   g_mZposModify=-1;//�߶ȸ��ٵ��ڴ�
			   g_mhandtrackAlt=0;//���ָ��ʱ����Զ����Ŀ��λ��һ�£��ֶ����ں󣬾Ͳ�һ����

		   }
		   else
		   {
          	if(g_nSelAlignStarNum==g_mAlignStarNum)
			{
			  g_nSelAlignStarNum=1;
			 }
			 else
			 {	
			     g_nSelAlignStarNum++;
			 }
			}
			break;	  

	case SYS_SUB3SUB6SUB2M_MF:   //���ʼ�����������������״̬״̬ת��
	    g_nsysstatus=SYS_SUB3SUB6SUB2M_SF;
		g_mShowMenucolumn=7;
	    break;
	case SYS_SUB3SUB6SUB2M_SF:   ///���ʼ�����������������״̬ת��
	    g_nsysstatus=SYS_SUB3SUB6SUB2M_MF;
		g_mShowMenucolumn=7;
	    break;

	  case SYS_SUB3SUB6SUB2M_MF1:   //���ʼ�����������������״̬״̬ת��
	     g_nsysstatus=SYS_SUB3SUB6SUB2M_SF1;
		 g_mShowMenucolumn=7;
	    break;
	case SYS_SUB3SUB6SUB2M_SF1:   ///���ʼ�����������������״̬ת��
	     g_nsysstatus=SYS_SUB3SUB6SUB2M_MFOV;
		 g_mShowMenucolumn=7;
	    break; 
	case SYS_SUB3SUB6SUB2M_MFOV:   ///���ʼ�����������������״̬ת��
	     g_nsysstatus=SYS_SUB3SUB6SUB2M_MF1; 
		 g_mShowMenucolumn=7;
	    break; 

	//��Ұ�Ӳ˵�����ѭ��
	case SYS_SUB3SUB6SUB1MENU1:
	    g_nsysstatus=SYS_SUB3SUB6SUB1MENU2;
	    break;
	case SYS_SUB3SUB6SUB1MENU2:
	    g_nsysstatus=SYS_SUB3SUB6SUB1MENU3;
	    break;
	case SYS_SUB3SUB6SUB1MENU3:
	    g_nsysstatus=SYS_SUB3SUB6SUB1MENU1;
	    break;
	//�������
	case SYS_SUB3SUB8MENU1Screen:
		if(g_mVir_BL==255)
		{
			LCDBacklight(191);
			g_mVir_BL=191;
		}
		else if(g_mVir_BL==191)
		{
			LCDBacklight(127);
			g_mVir_BL=127;
		}
		else if(g_mVir_BL==127)
		{
			LCDBacklight(63);
			g_mVir_BL=63;
		}
		else 
		{
			LCDBacklight(0);
			g_mVir_BL=0;
		}
		break;
	//����ѡ��
	case SYS_SUB4SUB3SUN1_CITYSEL:
		 	LCDRfrsh();
	FindCountryAdd();
		break;
	case  SYS_SUB2SUB11_SET: 
		switch(g_mMyLandmarkOperator)
		{
			case 0:	//ѡ��			
			case 2:	 //ɾ��
				if(CustomLandmarkNum_temp==(CustomLandmarkNum-1))
					CustomLandmarkNum_temp=0;
				else
					CustomLandmarkNum_temp++;				
					break;	
			case 1:	//���
				if(g_mMyLandmarkShowMode==2)
				{
					g_mMyLandmarkShowMode=0;
					g_mShowMenucolumn=7;
				}
				else
				{
					g_mMyLandmarkShowMode++;
					g_mShowMenucolumn=7;
				}
				break;
			default:
				break;

		}
		break;
	case  SYS_SUB2SUB8_SET: 
		switch(g_mMyStarOperator)
		{
			case 0:	//ѡ��			
			case 2:	 //ɾ��
				if(CustomStarNum_temp==(CustomStarNum-1))
					CustomStarNum_temp=0;
				else
					CustomStarNum_temp++;				
					break;	
			case 1:	//���
			case 3:	//�޸�
				if(g_mMyStarShowMode==2)
				{
					g_mMyStarShowMode=0;
					g_mShowMenucolumn=7;
				}
				else
				{
					g_mMyStarShowMode++;
					g_mShowMenucolumn=7;
				}
				break;
			default:
				break;
		}
		break;
		 //��������ʱ����
		case SYS_SUB4SUB2MENU1:
		if(g_mSysInitGuide==1)
			{
			g_nsysstatus=SYS_SUB4SUB2MENU2;
			g_mDaylight=false;
			}
	    	break;
		case SYS_SUB4SUB2MENU2:
		  if(g_mSysInitGuide==1)
			{
			g_nsysstatus=SYS_SUB4SUB2MENU1;
			g_mDaylight=true;
			}
	    	break;
//*****************************************************************************	

	default:
		break ;
	}
}

//*******************************************************************


//*******************************************************************
//down����
void FKeyLeft()
{  
   FFindObjectAccAdd();
   switch(g_nsysstatus	)
   {
     case  SYS_SUB2SUB9RA:	//ϵͳ���ڳྭ����״̬
	 case  SYS_MENU_SKY_RA :
         FRaInputMoveLeft();
	  break;
	  case  SYS_SUB2SUB9DEC:	//ϵͳ���ڳ�γ����״̬
	  case  SYS_MENU_SKY_DEC:
	  case  SYS_MENU_LAND_ALT:
	  case  SYS_MENU_LAND_AZI:
         FDecInputMoveLeft();
	  break;

	  case SYS_MENU_SKY_NAME:
	  case SYS_MENU_LAND_NAME:
	        g_mShowMenucolumn--;
			if(g_mShowMenucolumn<6)
			{
			   g_mShowMenucolumn=13;
			   }
		break;
	  ///**************************************
	  //***************************************
	 
	 case SYS_MAINSHOW:
	 case SYS_SUB1SUB11RA_GEAR_ERROR_BEGIN: 	
     case SYS_SUB1SUB12DEC_GEAR_ERROR_BEGIN: 
	 case SYS_SUB2SUN_PLANET1: //̫��ϵͳ����1 
     case  SYS_SUB2CON_OBJECT1:
     case  SYS_SUB2FS_OBJECT1: 			   
     case  SYS_SUB2MSR_OBJECT1:
     case  SYS_SUB2NGC_OBJECT1:
     case  SYS_SUB2IC_OBJECT1:
     case  SYS_SUB2SH2_OBJECT1:	
     case  SYS_SUB2BRT_OBJECT1:
     case  SYS_SUB2SAO_OBJECT1:
	if(!g_mLandMark)
	{
	 if((g_mGoto.m_nGoto)&&(g_mTelStatusSet!=1))///||((g_mGoto.m_nGoto)&&(g_mTelStatusSet!=1)))//if((g_mGoto.m_nGoto)&&(g_mTelStatusSet!=1))
	 {
           g_mAposModify=-1;//��λ���ٵ��ڴ�
		   g_mhandtrackAzi=0;//���ָ��ʱ����Զ����Ŀ��λ��һ�£��ֶ����ں󣬾Ͳ�һ����
	   }
		else
		{
		   if(g_mTelescopeConType==1)
		   {
		      FHandControlTelescope(AXIS_RA,DIRECT_LEFT,g_mHandSpeed);
			}
		   else
		   {
			  FHandControlTelescope(AXIS_AZI,DIRECT_LEFT,g_mHandSpeed);
		   }
	   }
	   }
	   else
	   { 
	      if(g_mTelescopeConType==1)
		   {
		      FHandControlTelescope(AXIS_RA,DIRECT_LEFT,g_mHandSpeed);
			}
		   else
		   {
			  FHandControlTelescope(AXIS_AZI,DIRECT_LEFT,g_mHandSpeed);
		   }
		 }
	   break;   
	   case SYS_SUB1SUB2STAR_ALIGN:
	   if(g_nAlignPoint)
		  {
	           g_mAposModify=-1;//��λ���ٵ��ڴ�
			   g_mhandtrackAzi=0;//���ָ��ʱ����Զ����Ŀ��λ��һ�£��ֶ����ں󣬾Ͳ�һ����
		  }
		break;
		//����ྭ�ز�����У��
    	case SYS_SUB1SUB11RA_GEAR_ERROR: 
		    g_mTelAzi0=g_mTelAzi;//��סУ��ǰ��Զ����λ��
			if(g_mTelescopeConType==1)
	   		{
	      		FHandControlTelescope(AXIS_RA,DIRECT_LEFT,3);
		  		g_mBackLashAxis=2;
			}
	   		else
	   		{
		  		FHandControlTelescope(AXIS_AZI,DIRECT_LEFT,3);
		  		g_mBackLashAxis=0;
	   		}
	    	g_mGearErrorAlign=true;//��Զ���Ƿ�����ִ����Ļز�У׼,true����ִ��,falseû��
			g_mTelGearErrorRaAlignDirect=2;//��Զ���ྭ�ز�У��ʱѡ�����еķ���,1��2��
			g_nsysstatus=SYS_SUB1SUB11RA_GEAR_ERROR_ALIGN;
			break;	


    //��Զ���ྭ��λ�ز�У׼���ֶ�
	case SYS_SUB1SUB11RA_GEAR_ERROR_ALIGN: 
		 if(g_mTelGearErrorRaAlignDirect==1)
		 {
			  if(g_mTelescopeConType==1)
			   {
			      FHandControlTelescope(AXIS_RA,DIRECT_LEFT,g_mHandSpeed);
				}
			   else
			   {
				  FHandControlTelescope(AXIS_AZI,DIRECT_LEFT,g_mHandSpeed);
			   }
		 }
		   break;
	case SYS_SUB4SUB8MENU4_RASPEED :	
	   FRaTrackSpeedInputMoveLeft() ;  //�Զ�������ٶ�����������
	break;




//ʱ�����ù������
	   case  SYS_SUB4SUB1_SETTIME:
			 FDateTimeInputMoveLeft(); 
		   break;
 //�Զ���ص�������
	case SYS_SUB4SUB3_SETSITE : 
	
				FSiteInputLeft();
				break;

    case  SYS_MENU_SKY_OBJECT:
	case  SYS_MENU_LAND_OBJECT:
	case  SYS_F_SELFNUM :
			   switch(g_mFnum)
			   {
			      case 1:
						g_mFnum=3;
						break;
				  case 3:
						g_mFnum=2;
						break;
			   	  case 2:
						g_mFnum=1;
						break;

				  case 4:
						g_mFnum=6;
						break;
				  case 6:
						g_mFnum=5;
						break;
			   	  case 5:
						g_mFnum=4;
						break;

				 case 7:
						g_mFnum=9;
						break;
				  case 9:
						g_mFnum=8;
						break;
			   	  case 8:
						g_mFnum=7;
						break;

			   }
			  break;


//��Զ���������������
	case SYS_SUB4SUB7_TELAZIALT_ZERO:				  
		FTelZeroInputLeft();
		break;
		 //�����¼�
	    case SYS_SUB3SUB3_MOONPHASE	:			  
				if(g_mMoonPhaseMonth>0)
				{
				   g_mMoonPhaseMonth--;
				   }
				   else
				   {
				     g_mMoonPhaseMonth=12;
			      }
			 break;

   //����ʱ�Ӳ˵�����ѭ��
    case SYS_SUB3SUB4TIMER_INPUT:
	  	FTimerInputMoveLeft();
	  	break;
	   
	//�����Ӳ˵�����ѭ��
	case SYS_SUB3SUB5ALARM_INPUT:
	  	FAlarmInputMoveLeft();
	  	break;
 	//���ʼ����Ӳ˵���ѭ��
	case SYS_SUB3SUB6SUB2M_SF:  
	case SYS_SUB3SUB6SUB2M_SF1: 
	    FSfocusInputMoveLeft();
		break;
	case SYS_SUB3SUB6SUB2M_MFOV: 
		FSFovInputMoveLeft();
	    break;  
	case SYS_SUB3SUB6SUB2M_MF: 
	case SYS_SUB3SUB6SUB2M_MF1:  
		FMfocusInputMoveLeft();
	    break; 
	case SYS_SUB4SUB3SUN1_CITYSEL:
		 	LCDRfrsh();
		 FindCityDec();
    case SYS_SUB2SUB11_SET : 
		switch(g_mMyLandmarkOperator)
		{			
			case 1:	 //����
				FLandmarkInputLeft();		
				break;
			default:  
				break;
		}
		break;
	case SYS_SUB2SUB8_SET : 
		switch(g_mMyStarOperator)
		{			
			case 1:	 //����
			case 3:  //�޸�
				FStarInputLeft();		
				break;
			default:  
				break;
		}
		break;
		 //��������ʱ����
		case SYS_SUB4SUB2MENU1:
		if(g_mSysInitGuide==1)
			{
			g_nsysstatus=SYS_SUB4SUB2MENU2;
			g_mDaylight=false;
			}
	    	break;
		case SYS_SUB4SUB2MENU2:
		   if(g_mSysInitGuide==1)
			{
			  g_nsysstatus=SYS_SUB4SUB2MENU1;
			   g_mDaylight=true;
	     	}
	    	break;
	  default :
	  break;
   }
   
}//*******************************************************************


//*******************************************************************
//down����
void FKeyRight()
{
  
   switch(g_nsysstatus	)
   {
      case  SYS_SUB2SUB9RA:	 //ϵͳ���ڳྭ����״̬
	  case  SYS_MENU_SKY_RA:
         FRaInputMoveRight();
	  break;
	   case  SYS_SUB2SUB9DEC:	 //ϵͳ���ڳ�γ����״̬
	   case  SYS_MENU_SKY_DEC:
	   case  SYS_MENU_LAND_ALT:
	   case  SYS_MENU_LAND_AZI:
         FDecInputMoveRight();
	  break;
	  case SYS_MENU_SKY_NAME:
	  case  SYS_MENU_LAND_NAME:
	        g_mShowMenucolumn++;
			if(g_mShowMenucolumn>13)
			{
			   g_mShowMenucolumn=6;
			   }
		break;
	 //***********************************************
	 //***********************************************
	 
   case  SYS_MAINSHOW:
   case  SYS_SUB1SUB11RA_GEAR_ERROR_BEGIN: 	
   case  SYS_SUB1SUB12DEC_GEAR_ERROR_BEGIN:
   case  SYS_SUB2SUN_PLANET1: //̫��ϵͳ����1 
   case  SYS_SUB2CON_OBJECT1:
   case  SYS_SUB2FS_OBJECT1: 			   
   case  SYS_SUB2MSR_OBJECT1:
   case  SYS_SUB2NGC_OBJECT1:
   case  SYS_SUB2IC_OBJECT1:
   case  SYS_SUB2SH2_OBJECT1:	
   case  SYS_SUB2BRT_OBJECT1:
   case  SYS_SUB2SAO_OBJECT1:
   if(!g_mLandMark)
	{
   	   if((g_mGoto.m_nGoto)&&(g_mTelStatusSet!=1))//&&(!g_mLandMark))////if((g_mOperateStatus==1)||(g_mOperateStatus==2))//||((g_mGoto.m_nGoto)&&(g_mTelStatusSet!=1)))//if((g_mGoto.m_nGoto)&&(g_mTelStatusSet!=1))
	  {
		    g_mAposModify=1;//��λ���ٵ��ڴ�
			g_mhandtrackAzi=0;//���ָ��ʱ����Զ����Ŀ��λ��һ�£��ֶ����ں󣬾Ͳ�һ����

	   }
		else
		{
		   if(g_mTelescopeConType==1)
		   {
		      
		      FHandControlTelescope(AXIS_RA,DIRECT_RIGHT,g_mHandSpeed);
			}
		   else
		   {
		
			  FHandControlTelescope(AXIS_AZI,DIRECT_RIGHT,g_mHandSpeed);
		   }
	   }
	  }
	   else
	   {
	      if(g_mTelescopeConType==1)
		   {
		      
		      FHandControlTelescope(AXIS_RA,DIRECT_RIGHT,g_mHandSpeed);
			}
		   else
		   {
		
			  FHandControlTelescope(AXIS_AZI,DIRECT_RIGHT,g_mHandSpeed);
		   }
	   }
	break;	
	

	case SYS_SUB1SUB2STAR_ALIGN:   
	   if(g_nAlignPoint)
		  {
		    g_mAposModify=1;//��λ���ٵ��ڴ�
			g_mhandtrackAzi=0;//���ָ��ʱ����Զ����Ŀ��λ��һ�£��ֶ����ں󣬾Ͳ�һ����
     	   }
		 break;
			//����ྭ�ز�����У��
	case SYS_SUB1SUB11RA_GEAR_ERROR: 
	    g_mTelAzi0=g_mTelAzi;//��סУ��ǰ��Զ����λ��
		if(g_mTelescopeConType==1)
   		{
      		FHandControlTelescope(AXIS_RA,DIRECT_RIGHT,3);
	  		g_mBackLashAxis=2;
		}						   
   		
   		else
		{
	  		FHandControlTelescope(AXIS_AZI,DIRECT_RIGHT,3);
	  		g_mBackLashAxis=0;
   		}
    	g_mGearErrorAlign=true;//��Զ���Ƿ�����ִ����Ļز�У׼,true����ִ��,falseû��
		g_mTelGearErrorRaAlignDirect=1;//��Զ���ྭ�ز�У��ʱѡ�����еķ���,1��2��

		g_nsysstatus=SYS_SUB1SUB11RA_GEAR_ERROR_ALIGN;
		break;
	
	     //��Զ���ྭ��λ�ز�У׼���ֶ�
	case SYS_SUB1SUB11RA_GEAR_ERROR_ALIGN: 
		 if(g_mTelGearErrorRaAlignDirect==2)
		 {
			  if(g_mTelescopeConType==1)
			   {
			      FHandControlTelescope(AXIS_RA,DIRECT_RIGHT,g_mHandSpeed);
				}
			   else
			   {
				  FHandControlTelescope(AXIS_AZI,DIRECT_RIGHT,g_mHandSpeed);
			   }
		 }

	case SYS_SUB4SUB8MENU4_RASPEED :	
	   FRaTrackSpeedInputMoveRight() ;  //�Զ�������ٶ�����������
	break;


	  //ʱ�����ù������
	   case  SYS_SUB4SUB1_SETTIME:
		 FDateTimeInputMoveRight(); 
		   break;
	 //�Զ���ص�������
	 case SYS_SUB4SUB3_SETSITE : 
			FSiteInputRight();
		break;


	  case  SYS_MENU_SKY_OBJECT:
	  case  SYS_MENU_LAND_OBJECT:
	  case  SYS_F_SELFNUM :
			   switch(g_mFnum)
			   {
			      case 1:
						g_mFnum=2;
						break;
				  case 2:
						g_mFnum=3;
						break;
			   	  case 3:
						g_mFnum=1;
						break;

				  case 4:
						g_mFnum=5;
						break;
				  case 5:
						g_mFnum=6;
						break;
			   	  case 6:
						g_mFnum=4;
						break;

				 case 7:
						g_mFnum=8;
						break;
				  case 8:
						g_mFnum=9;
						break;
			   	  case 9:
						g_mFnum=7;
						break;

			   }
			  break;

	
//��Զ���������������
	case SYS_SUB4SUB7_TELAZIALT_ZERO:				  
		FTelZeroInputRight();
		break;

	 //�����¼�
	    case SYS_SUB3SUB3_MOONPHASE	:			  
				if(g_mMoonPhaseMonth<12)
				{
				   g_mMoonPhaseMonth++;
				   }
				   else
				   {
				     g_mMoonPhaseMonth=0;
			      }
			 break;

   //����ʱ�Ӳ˵�����ѭ��
	case SYS_SUB3SUB4TIMER_INPUT:
	  	FTimerInputMoveRight();
	  	break;
  	//�����Ӳ˵�����ѭ��
	case SYS_SUB3SUB5ALARM_INPUT:
	  	FAlarmInputMoveRight();
	  	break;
 	//���ʼ����Ӳ˵���ѭ��
	case SYS_SUB3SUB6SUB2M_SF:  
	case SYS_SUB3SUB6SUB2M_SF1: 
	
		FSfocusInputMoveRight();
	    break;   
		case SYS_SUB3SUB6SUB2M_MFOV: 
		FSFovInputMoveRight();
		break;
	case SYS_SUB3SUB6SUB2M_MF: 
	case SYS_SUB3SUB6SUB2M_MF1:   
		FMfocusInputMoveRight();
		break; 
   	case SYS_SUB4SUB3SUN1_CITYSEL:
		 	LCDRfrsh();
		FindCityAdd(); 
		break;
		case SYS_SUB2SUB11_SET : 
		switch(g_mMyLandmarkOperator)
		{			
			case 1:	 //����
				FLandmarkInputRight();		
				break;
			default:  
				break;
		}
		break;
	case SYS_SUB2SUB8_SET : 
		switch(g_mMyStarOperator)
		{			
			case 1:	 //����
			case 3:  //�޸�
				FStarInputRight();		
				break;
			default:  
				break;
		}
		break;
		 //��������ʱ����
		case SYS_SUB4SUB2MENU1:
		if(g_mSysInitGuide==1)
			{
			g_nsysstatus=SYS_SUB4SUB2MENU2;
			g_mDaylight=false;
			}
	    	break;
		case SYS_SUB4SUB2MENU2:
		if(g_mSysInitGuide==1)
			{
			g_nsysstatus=SYS_SUB4SUB2MENU1;
			g_mDaylight=true;
			}
	    	break;
	  default:
	  break;

   }
}
//*******************************************************************


//*******************************************************************
//center ϵͳȷ�ϼ�ִ�а���
void FKeyEnter()
{
	switch(g_nsysstatus)
  	{
  		//**************************************
  		//��Զ����SYS_MAINSHOW״̬ʱ��ENTERR����Ҫ�����¹���
  		//1.��Զ��������У��״̬��ȷ�����Ǻ��������У�����

		case SYS_MAINSHOW:
	   		if(!g_mGoto.m_nAlign)
	   		{
	    		FPointAlignStarOk();
	  		}
		    else
			{
			  	g_nsysstatus=SYS_MAINMENU1;//����״̬����һ���˵�
			}	
    		break;

	   case SYS_F_SELFNUM :   //��F½��Ŀ������Ŀ��������� 
	       	  LCDRfrsh();
		 	 g_nsysstatus=SYS_F_SELFNUM_SEL;
		break;
		case  SYS_F_SELFNUM_SEL:
										
		    switch(g_mSkyLand)
				  	{
					  case 0:
						  GetCustomStar(g_mFnum,&CustomStar);
						  if(CustomStar.flag==1)
						  {
							 g_mObjRa=CustomStar.Ra;
				             g_mObjDec=CustomStar.Dec;
							 g_mTelStatus=1;
			                 FPointNewStar(g_mObjRa,g_mObjDec);
							 g_mTargetType=10;
                             g_mTargetnum=g_mFnum;
			                 WriteRecentTarget(g_mTargetType,g_mTargetnum);
		                     FBeep(1);
							 g_nsysstatus=SYS_MAINSHOW;
						 }
						break;
					  case 1:  
						  GetCustomLandTarget(g_mFnum,&LandTarget);
						  g_mLandObjAzi=LandTarget.Azi;
			              g_mLandObjAlt=LandTarget.Alt;
						  if(LandTarget.Alt>=-15)
						  {
							  g_mTelStatus=1;
				              FPointNewStar(g_mObjRa,g_mObjDec);
							  g_mgotostarttype=1;
							  g_mTargetType=12;
	                          g_mTargetnum=g_mFnum;
				              WriteRecentTarget(g_mTargetType,g_mTargetnum);
							  FBeep(1);
							  g_nsysstatus=SYS_MAINSHOW;
						  }
						  else
						  {
						       LCDRfrsh();
		 	                   FBeep(1);
							   DispEn(0,3,1,22," Target Out of Range  ");
		                       DispEn(0,5,1,22,"Altitude < -15 Degree ");
		                       //DispEn(0,7,1,22," (c)2012  MAXVISION   ");
	                           MenuDelay(2000);
                               LCDRfrsh();
							   g_nsysstatus=SYS_F_SELFNUM;
						  }
						break;
					 default:		
						break;
					}
		break;


     	 case SYS_MENUSHOW: 
		         g_RecentNum=GetRecentTarget(g_RecentType,g_Targetnum,g_rdata);

				

				 switch(g_RecentType[g_mShowMenurowEn-1])
				 {
				 	   	 
		     	 	 case 1:
//					      g_mShowMenurowCn12=1;
//					    g_mShowMenuFtCn12=1;
						g_mShowMenurowEn12=1;
					    g_mShowMenuFtEn12=1;

					     g_mSunSysObjectNum=g_Targetnum[g_mShowMenurowEn-1];
						 LCDRfrsh();
			             g_nsysstatus=SYS_SUB2SUN_PLANET; 
				      break;
					 case 2:
//					   g_mShowMenurowCn12=2;
//					    g_mShowMenuFtCn12=1;
						g_mShowMenurowEn12=2;
					    g_mShowMenuFtEn12=1;
					   	g_mCon88ObjectNum=g_Targetnum[g_mShowMenurowEn-1];
						LCDRfrsh();
                       	g_nsysstatus=SYS_SUB2CON_OBJECT;
					 break;
					 case 3:
//					   g_mShowMenurowCn12=3;
//					    g_mShowMenuFtCn12=1;
						g_mShowMenurowEn12=3;
					    g_mShowMenuFtEn12=1;
					    g_mFamousStarObjectNum=g_Targetnum[g_mShowMenurowEn-1];
						LCDRfrsh();
                    	g_nsysstatus=SYS_SUB2FS_OBJECT;
					 break;
					 case 4:
//					   g_mShowMenurowCn12=4;
//					    g_mShowMenuFtCn12=1;
						g_mShowMenurowEn12=4;
					    g_mShowMenuFtEn12=1;
					   g_mMsrObjectNum=g_Targetnum[g_mShowMenurowEn-1];
						g_mInputStarNum=0;
						 LCDRfrsh();
			         	g_nsysstatus=SYS_SUB2MSR_OBJECT0;
					 break;
					 case 5:
//					   g_mShowMenurowCn12=4;
//					    g_mShowMenuFtCn12=2;
						g_mShowMenurowEn12=5;
					    g_mShowMenuFtEn12=1;
					 	g_mNgcObjectNum=g_Targetnum[g_mShowMenurowEn-1];
						g_mInputStarNum=0;
						 LCDRfrsh();
			         	g_nsysstatus=SYS_SUB2NGC_OBJECT;
					 break;
					 case 6:
//					   g_mShowMenurowCn12=4;
//					    g_mShowMenuFtCn12=3;
						g_mShowMenurowEn12=6;
					    g_mShowMenuFtEn12=1;
					 	g_mIcObjectNum=g_Targetnum[g_mShowMenurowEn-1];
						g_mInputStarNum=0;
						 LCDRfrsh();
			         	g_nsysstatus=SYS_SUB2IC_OBJECT;
					 break;
					 case 7:
//					   g_mShowMenurowCn12=4;
//					    g_mShowMenuFtCn12=4;
						g_mShowMenurowEn12=7;
					    g_mShowMenuFtEn12=1;
					    g_mSh2ObjectNum=g_Targetnum[g_mShowMenurowEn-1];
					    g_mInputStarNum=0;
						 LCDRfrsh();
		         	    g_nsysstatus=SYS_SUB2SH2_OBJECT;
					 break;
					 case 8:
//					   g_mShowMenurowCn12=4;
//					    g_mShowMenuFtCn12=5;
						g_mShowMenurowEn12=8;
					    g_mShowMenuFtEn12=1;
						 g_mBrightObjectNum=g_Targetnum[g_mShowMenurowEn-1];
						g_mInputStarNum=0;
						LCDRfrsh();
			         	g_nsysstatus=SYS_SUB2BRT_OBJECT;
					 break;
					 case 9:
//					    g_mShowMenurowCn12=4;
//					    g_mShowMenuFtCn12=6;
						g_mShowMenurowEn12=8;
					    g_mShowMenuFtEn12=2;
					 	g_mSaoObjectNum=g_Targetnum[g_mShowMenurowEn-1];
						g_mInputStarNum=0;
						LCDRfrsh();
			         	g_nsysstatus=SYS_SUB2SAO_OBJECT;
					 break;
					 case 10:
					      if(g_mSkyLand==0)
						  {
					        g_mFnum=g_Targetnum[g_mShowMenurowEn-1];
					         g_nsysstatus=SYS_F_SELFNUM;
						  }
						  else
						  {
						     g_nsysstatus=SYS_MAINSHOW;
						  }

					 break;
					 case 11:
					   GetCustomStar(10,&CustomStar);
						  if(CustomStar.flag==111)
						  {
							 g_mObjRa=CustomStar.Ra;
				             g_mObjDec=CustomStar.Dec;
							 g_mTelStatus=1;
			                 FPointNewStar(g_mObjRa,g_mObjDec);
						   }
						g_nsysstatus=SYS_MAINSHOW;

					 break;
					  case 12:
					    if(g_mSkyLand==1)
						  {
					        g_mFnum=g_Targetnum[g_mShowMenurowEn-1];
					 	   g_nsysstatus=SYS_F_SELFNUM;
						   }
						  else
						  {
						     g_nsysstatus=SYS_MAINSHOW;
						  }

					 break;
					 default :
					   g_nsysstatus=SYS_MAINSHOW;
					 break;
				}


			 //g_nsysstatus=SYS_MAINSHOW;
		   break;


		//********************
    	//�����˵���������˵
    	case SYS_MAINMENU1:	 //������Զ��У���Ӳ˵�
//            g_mShowMenurowCn11=1;	
//		    g_mShowMenuFtCn11=1;
			g_mShowMenurowUn11=1;	
		    g_mShowMenuFtUn11=1;
		    g_mShowMenurowEn11=1;	
		    g_mShowMenuFtEn11=1;

			g_nsysstatus=SYS_SUB1MENU1;
			break;
		case SYS_MAINMENU2:	 //����Ŀ�굼���Ӳ˵�
//		    g_mShowMenurowCn12=1;	
//		    g_mShowMenuFtCn12=1;
			g_mShowMenurowUn12=1;	
		    g_mShowMenuFtUn12=1;
		    g_mShowMenurowEn12=1;	
		    g_mShowMenuFtEn12=1;
			g_nsysstatus=SYS_SUB2MENU1;
			break;
		case SYS_MAINMENU3:	 //���빤�������Ӳ˵�
//		    g_mShowMenurowCn13=1;	
//		    g_mShowMenuFtCn13=1;
			g_mShowMenurowUn13=1;	
		    g_mShowMenuFtUn13=1;
		    g_mShowMenurowEn13=1;	
		    g_mShowMenuFtEn13=1;
			g_nsysstatus=SYS_SUB3MENU1;
			break;
		case SYS_MAINMENU4:	 //������������Ӳ˵�
//		    g_mShowMenurowCn14=1;	
//		    g_mShowMenuFtCn14=1;
			g_mShowMenurowUn14=1;	
		    g_mShowMenuFtUn14=1;
		    g_mShowMenurowEn14=1;	
		    g_mShowMenuFtEn14=1;
			g_nsysstatus=SYS_SUB4MENU1;
			break;
   		//*********************
	 	//�Ӷ����˵����������˵������Ӳ˵�

			case SYS_SUB3MENU6://����Ŀ���������Ӳ˵�
		   g_mShowMenucolumn=7;
			g_nsysstatus=SYS_SUB3SUB6SUB2M_MF1;
			break;

		case SYS_SUB3MENU7://����Ŀ���������Ӳ˵�
		   g_mShowMenucolumn=7;
			g_nsysstatus=SYS_SUB3SUB6SUB2M_MF;
			break;


		case SYS_SUB3MENU8://���밵��Ұ�������Ӳ˵�
			g_nsysstatus=SYS_SUB3SUB8MENU1Screen;
			break;
		case SYS_SUB4MENU3: //����ص��������Ӳ˵�
			g_nsysstatus=SYS_SUB4SUB3MENU1;
			break;


		case SYS_SUB4MENU6: //������Զ������Ӳ˵�
			g_nsysstatus=SYS_SUB4SUB7_TELAZIALT_ZERO;
			g_mTelZeroShowMode=0;
			g_mShowMenucolumn=5;
			tel_zero_error_num=0;//��Զ������
			GetTelZero(&azi_zero,&alt_zero); //��ȡ��Զ�����
	        sprintf(g_sysmenu4700AziZeroEn,"Azi:%03d",(uint16)azi_zero);
 	        sprintf(g_sysmenu4700AltZeroEn,"Alt: %02d",(uint16)alt_zero);
		    sprintf(g_sysmenu4700AziZero,"Azi:%03d",(uint16)azi_zero);
 	        sprintf(g_sysmenu4700AltZero,"Alt: %02d",(uint16)alt_zero);
			break;		
		case SYS_SUB4MENU7: //��������ٶ����Ӳ˵�
			g_nsysstatus=SYS_SUB4SUB8MENU1;
			break;
		//**************************************
		//**************************************
		//������ײ����ʾ����ִ������
    	//��Զ��У��
		//�Զ�У��
//		case SYS_SUB1MENU1: 
//	  		 //FTwoStarAutoAlign();
//	  		//g_nsysstatus=SYS_MAINSHOW;
//			 //g_nAlignStar=2;//�Զ���У׼����Ŀ���Ϊ3
//             //g_nSelAlignStarNum=1;//��ѡ�����Զ���У׼���ǵڼ�
//			 g_nSeledAlignStarNum=1;//ѡ���˼�����
//			 g_nAlignPoint=false;//��Զ����һ����������У��ʱ�ǵ���ȷ�ϻ���ѡ��falseѡ���ǣ�trueУ������ȷ��
//			 //g_mAlignStarNum=FindAlignStar(FCalSiderealTime(1,false,g_mGoto.m_nLongitude),g_mGoto.m_nAtitude,g_mStarAlign,AlignStarName,AlignStarNameCn);		
////	   		  g_mTelStatusSet=0;
//			 g_nsysstatus=SYS_SUB1SUB1AUTOSTAR_ALIGN;
//			break;
//	  case SYS_SUB1SUB1AUTOSTAR_ALIGN:
//	        if(g_mTelStatus==2)
//			{
//				g_nSeledAlignStarNum++;//ѡ���˼����� 
//				//g_mAlignStarNum=FindAlignStar(FCalSiderealTime(1,false,g_mGoto.m_nLongitude),g_mGoto.m_nAtitude,g_mStarAlign,AlignStarName,AlignStarNameCn);					 
//				g_nAlignPoint=false;//��Զ����һ����������У��ʱ�ǵ���ȷ�ϻ���ѡ��falseѡ���ǣ�trueУ������ȷ��
//				FPointAlignStarOk();
//			}
//			g_nsysstatus=SYS_SUB1SUB1AUTOSTAR_ALIGN;
//	        break;


		//һ����У��
		case SYS_SUB1MENU1: 
             g_nAlignStar=1;//�Զ���У׼����Ŀ���Ϊ3
             g_nSelAlignStarNum=1;//��ѡ�����Զ���У׼���ǵڼ�
			 g_nSeledAlignStarNum=1;//ѡ���˼�����
			 g_nAlignPoint=false;//��Զ����һ����������У��ʱ�ǵ���ȷ�ϻ���ѡ��falseѡ���ǣ�trueУ������ȷ��
	         g_mAlignStarNum=FindAlignStar(FCalSiderealTime(1,false,g_mGoto.m_nLongitude),g_mGoto.m_nAtitude,g_mStarAlign,AlignStarName,AlignStarNameCn);		
//	   		  g_mTelStatusSet=0;

			 g_nsysstatus=SYS_SUB1SUB2STAR_ALIGN;
			break;
		//������У��
		case SYS_SUB1MENU2: 
    		 g_nAlignStar=2;//�Զ���У׼����Ŀ���Ϊ3
             g_nSelAlignStarNum=1;//��ѡ�����Զ���У׼���ǵڼ�
			 g_nSeledAlignStarNum=1;//ѡ���˼�����
			 g_nAlignPoint=false;//��Զ����һ����������У��ʱ�ǵ���ȷ�ϻ���ѡ��falseѡ���ǣ�trueУ������ȷ��
			 g_mAlignStarNum=FindAlignStar(FCalSiderealTime(1,false,g_mGoto.m_nLongitude),g_mGoto.m_nAtitude,g_mStarAlign,AlignStarName,AlignStarNameCn);		
//	   		 g_mTelStatusSet=0;
			 g_nsysstatus=SYS_SUB1SUB2STAR_ALIGN;
			 

			break;
		//������У��
		case SYS_SUB1MENU3: 
		     g_nAlignStar=3;//�Զ���У׼����Ŀ���Ϊ3
             g_nSelAlignStarNum=1;//��ѡ�����Զ���У׼���ǵڼ� 
			 g_nSeledAlignStarNum=1;//ѡ���˼�����
			 g_nAlignPoint=false;//��Զ����һ����������У��ʱ�ǵ���ȷ�ϻ���ѡ��falseѡ���ǣ�trueУ������ȷ��
			 g_mAlignStarNum=FindAlignStar(FCalSiderealTime(1,false,g_mGoto.m_nLongitude),g_mGoto.m_nAtitude,g_mStarAlign,AlignStarName,AlignStarNameCn);		
//			 g_mTelStatusSet=0;
			 g_nsysstatus=SYS_SUB1SUB2STAR_ALIGN;
			break;

		case SYS_SUB1SUB2STAR_ALIGN	:
		   g_mAlignShow=0;
		   g_mstartOTAset=1;//����ʱ������Զ���ĳ�ʼָ��
//		   g_mTelStatusSet=0;
		   if(!g_nAlignPoint)//��Զ����һ����������У��ʱ�ǵ���ȷ�ϻ���ѡ��falseѡ���ǣ�trueУ������ȷ��
			{
			   	switch(g_nSeledAlignStarNum)
				{
				    case 1:
					g_mAlignStarNum=FindAlignStar(FCalSiderealTime(1,false,g_mGoto.m_nLongitude),g_mGoto.m_nAtitude,g_mStarAlign,AlignStarName,AlignStarNameCn);		
					g_mGoto.m_nAlignStarRA1=g_mStarAlign[2*( g_nSelAlignStarNum-1)];//�ྭ(0-24Сʱ)
					g_mGoto.m_nAlignStarDec1=g_mStarAlign[2*( g_nSelAlignStarNum-1)+1];//��γ(-90��90��)
					 switch(g_nAlignStar)
					 {
					   case 1:
					     FOneStarAlign();
						break;
					   case 2:
					     FTwoStarAlign();
						break;
					   case 3:
					     FThreeStarAlign();
						break;
					   default:
						break;
				   	}
					g_nSeledAlignStarNum++;
	            	g_nAlignStar--;
					g_nAlignPoint=true;
					g_mTelStatus=0;
					break;
					case 2:
					if(g_mTelStatus==2)
					{
					   g_mAlignStarNum=FindAlignStar(FCalSiderealTime(1,false,g_mGoto.m_nLongitude),g_mGoto.m_nAtitude,g_mStarAlign,AlignStarName,AlignStarNameCn);		
					   g_mGoto.m_nAlignStarRA2=g_mStarAlign[2*( g_nSelAlignStarNum-1)];//�ྭ(0-24Сʱ)
					   g_mGoto.m_nAlignStarDec2=g_mStarAlign[2*( g_nSelAlignStarNum-1)+1];//��γ(-90��90��)
					    if(!g_mGoto.m_nAlign)
				   		{
				    		FPointAlignStarOk();
				  		}
					  g_nSeledAlignStarNum++;
	            	  g_nAlignStar--;
					  g_nAlignPoint=true;
					  g_mTelStatus=0;
					}

					break;
					case 3:
					if(g_mTelStatus==2)
					{
				    	g_mAlignStarNum=FindAlignStar(FCalSiderealTime(1,false,g_mGoto.m_nLongitude),g_mGoto.m_nAtitude,g_mStarAlign,AlignStarName,AlignStarNameCn);		
					   g_mGoto.m_nAlignStarRA3=g_mStarAlign[2*( g_nSelAlignStarNum-1)];//�ྭ(0-24Сʱ)
					   g_mGoto.m_nAlignStarDec3=g_mStarAlign[2*( g_nSelAlignStarNum-1)+1];//��γ(-90��90��)
					    if(!g_mGoto.m_nAlign)
				   		{
				    		FPointAlignStarOk();
				  		}
					    g_nSeledAlignStarNum++;
	            	    g_nAlignStar--;
					    g_nAlignPoint=true;
					    g_mTelStatus=0;
					}
					break;
					default:
					break;
				}

			}
			else
			{
			  
			   //if(g_mTelStatus==2)
			   if((g_mAlignTelStatus==4)||(g_mAlignTelStatus==8))
			   {
			       g_nAlignPoint=false;
			    }
			   //FBeep(1);
			   //delay(20);
			   //FBeep(1)			  
			   
			}


			if(g_nAlignStar==-1)
			{ 
			       //g_nsysstatus=SYS_MAINSHOW;
			 }
			 else
			 {
			       g_nsysstatus=SYS_SUB1SUB2STAR_ALIGN;
			 }			  
//			 g_mTelStatusSet=0;
		     break;


		//Ŀ��ͬ��
   		case SYS_SUB1MENU4: 
		    m_TcpSynFlash=0;//��Զ��ͬ����ʾ��˸
		    if(m_TcpSynEnable==0)
			{  
			   g_nsysstatus=SYS_SUB1SUB4MENU1;
			 }
			 else
			 {
			    g_nsysstatus=SYS_SUB1SUB4MENU2;
			 }
			break;
		case SYS_SUB1SUB4MENU1:
			   m_TcpSynEnable=1;
			  g_nsysstatus=SYS_MAINSHOW;
			   FBeep(2);
		      break;
		case SYS_SUB1SUB4MENU2:
		 	   dg_mApos_syn=dg_mApos;//ͬ����
			   dg_mZpos_syn=-dg_mZpos;//ͬ����
			   	syn_mApos=dg_mApos;//��ʼ������ͬ����
                syn_mZpos=dg_mZpos;//��ʼ������ͬ����

			   g_nsysstatus=SYS_MAINSHOW;
			   m_TcpSynEnable=0;
			   FBeep(2);
			break;
		case SYS_SUB1SUB4MENU3:
		       m_TcpSynEnable=0;
		       g_nsysstatus=SYS_MAINSHOW;
			  //FBeep(2);
			break;




 		//��Զ������ƫ����ʾ
     	case SYS_SUB1MENU5: 
			g_nsysstatus=SYS_SUB1SUB8POLE_AXIS_ERROR;
			break;



		//�ྭ�ز�У����ʼ
    	case SYS_SUB1MENU6: 
			g_nsysstatus=SYS_SUB1SUB11RA_GEAR_ERROR_BEGIN;
			break;
		//�ྭ�ز�У����
	   case SYS_SUB1SUB11RA_GEAR_ERROR_BEGIN: 
			g_nsysstatus=SYS_SUB1SUB11RA_GEAR_ERROR;
			break;
	   	//ִ��һ�γྭ�ز�У��
    	case SYS_SUB1SUB11RA_GEAR_ERROR_ALIGN: 
		    if(fabs(g_mTelAzi-g_mTelAzi0)>5) //�ز���ܴ���5��,���ڣ�����0�����
			{
	    	  g_mRaAziGearError=fabs(3600.0*(g_mTelAzi-g_mTelAzi0-360));
			 }
			 else
			 {
			    g_mRaAziGearError=fabs(3600.0*(g_mTelAzi-g_mTelAzi0));
			 }
			g_mRaAziGearErrorTotal=g_mRaAziGearErrorTotal+g_mRaAziGearError;//Զ���ྭ��λ�ܴ����ز� ������
			g_mRaAziGearErrorNum++;
	    	g_mGearErrorAlign=false;//��Զ���Ƿ�����ִ����Ļز�У׼,true����ִ��,falseû��
			g_nsysstatus=SYS_SUB1SUB11RA_GEAR_ERROR_ALIGN_OK;
			break;
		//��ɳྭ�ز�����У��
    	case SYS_SUB1SUB11RA_GEAR_ERROR: 
		   if(g_mRaAziGearErrorNum!=0)//��Զ���ྭ��λƽ���ز��������
		   {		    
             g_mRaAziGearEvenError=g_mRaAziGearErrorTotal/g_mRaAziGearErrorNum;//��Զ���ྭ��λƽ���ز�	������
            }
			g_mRaAziGearErrorTotal=0; 
			g_mRaAziGearError=0;//��Զ���ྭ��λһ�λز� ������
			g_mRaAziGearErrorNum=0;
			g_nsysstatus=SYS_SUB1SUB11RA_GEAR_ERROR_ALIGN_END;
			break;	
		

	  //��γ�ز�У����ʼ
    	case SYS_SUB1MENU7: 
			g_nsysstatus=SYS_SUB1SUB12DEC_GEAR_ERROR_BEGIN;
			break;
		//��γ�ز�У����
	   case SYS_SUB1SUB12DEC_GEAR_ERROR_BEGIN: 
			g_nsysstatus=SYS_SUB1SUB12DEC_GEAR_ERROR;
			break;
	   	//ִ��һ�γ�γ�ز�У��
    	case SYS_SUB1SUB12DEC_GEAR_ERROR_ALIGN: 
	    	g_mDecAltGearError=fabs(3600.0*(g_mTelAlt-g_mTelAlt0));
			g_mDecAltGearErrorTotal=g_mDecAltGearErrorTotal+g_mDecAltGearError;//Զ����γ��λ�ܴ����ز� ������
			g_mDecAltGearErrorNum++;
	    	g_mGearErrorAlign=false;//��Զ���Ƿ�����ִ����Ļز�У׼,true����ִ��,falseû��
			g_nsysstatus=SYS_SUB1SUB12DEC_GEAR_ERROR_ALIGN_OK;
			break;
		//��ɳ�γ�ز�����У��
    	case SYS_SUB1SUB12DEC_GEAR_ERROR: 
		   if(g_mDecAltGearErrorNum!=0)//��Զ����γ��λƽ���ز��������
		   {		    
             g_mDecAltGearEvenError=g_mDecAltGearErrorTotal/g_mDecAltGearErrorNum;//��Զ����γ��λƽ���ز�	������
            }
			g_mDecAltGearErrorTotal=0; 
			g_mDecAltGearError=0;//��Զ����γ��λһ�λز� ������
			g_mDecAltGearErrorNum=0;
			g_nsysstatus=SYS_SUB1SUB12DEC_GEAR_ERROR_ALIGN_END;
			break;	


	
	   //**************************************************************************

	 	//ִ��̫��ϵͳĿ��ĸ��ٲ����ص�����ʾ
		//����̫��ϵ���Ӳ˵�
		case SYS_SUB2MENU1:	
		    g_mSunSysObjectNum=0;
			LCDRfrsh();
		//	GetPlanetPos();//��������λ��
			g_mEQHn=false;//���ʽ��Զ��Ŀ���Ƿ��ڵ�ƽ��
			g_nsysstatus=SYS_SUB2SUN_PLANET;
			break;

	  	case  SYS_SUB2SUN_PLANET: 
		    if(g_mSunSysObjectNum==8) 
			{
//		     	GetSunSysObject(g_mSunSysObjectNum,&g_mObjRa1,&g_mObjDec1);
//			 	g_mObjRa=g_mObjRa1;
//			 	g_mObjDec=g_mObjDec1;
//				//g_mOperateStatus=1;
//				g_mTelStatus=1;
//	     		FPointNewStar(g_mObjRa,g_mObjDec);
//	
//	            g_mTargetType=1;
//	            g_mTargetnum=g_mSunSysObjectNum;
//				WriteRecentTarget(g_mTargetType,g_mTargetnum);
	             
			    LCDRfrsh();
	         	g_nsysstatus=SYS_SUB2SUN_SUNWARN;
				FBeep(1);
			}
			else
			{
			  	GetSunSysObject(g_mSunSysObjectNum,&g_mObjRa1,&g_mObjDec1);
			 	g_mObjRa=g_mObjRa1;
			 	g_mObjDec=g_mObjDec1;
				//g_mOperateStatus=1;
				g_mTelStatus=1;
	     		FPointNewStar(g_mObjRa,g_mObjDec);
	
	            g_mTargetType=1;
	            g_mTargetnum=g_mSunSysObjectNum;
				WriteRecentTarget(g_mTargetType,g_mTargetnum);
	             
			    LCDRfrsh();
	         	g_nsysstatus=SYS_SUB2SUN_PLANET1;
			
			}
		 	break;
		case  SYS_SUB2SUN_SUNWARN: 
				 GetSunSysObject(g_mSunSysObjectNum,&g_mObjRa1,&g_mObjDec1);
			 	g_mObjRa=g_mObjRa1;
			 	g_mObjDec=g_mObjDec1;
				//g_mOperateStatus=1;
				g_mTelStatus=1;
	     		FPointNewStar(g_mObjRa,g_mObjDec);
	
	            g_mTargetType=1;
	            g_mTargetnum=g_mSunSysObjectNum;
				WriteRecentTarget(g_mTargetType,g_mTargetnum);
	             
			    LCDRfrsh();
	         	g_nsysstatus=SYS_SUB2SUN_PLANET1;
		break;		
			



		//88����
	   	case  SYS_SUB2MENU2:
	     	g_mCon88ObjectNum=1;
			LCDRfrsh();
			g_mEQHn=false;//���ʽ��Զ��Ŀ���Ƿ��ڵ�ƽ��
         	g_nsysstatus=SYS_SUB2CON_OBJECT;
		 	break;
		  //88����
	       case  SYS_SUB2CON_OBJECT:
	      //��ȡ88�����Ǳ�����
             GetCon88(g_mCon88ObjectNum,&con);
		     g_mObjRa=con.Ra;
			g_mObjDec=con.Dec;
			g_mTelStatus=1;
		    FPointNewStar(g_mObjRa,g_mObjDec);
		    g_mTargetType=2;
            g_mTargetnum=g_mCon88ObjectNum;	
			WriteRecentTarget(g_mTargetType,g_mTargetnum);	
			LCDRfrsh();
            g_nsysstatus=SYS_SUB2CON_OBJECT1;
		 	break;


		 //�������������Ӳ˵�
		case SYS_SUB2MENU3:	 
	        g_mFamousStarObjectNum=1;
			LCDRfrsh();
			g_mEQHn=false;//���ʽ��Զ��Ŀ���Ƿ��ڵ�ƽ��
         	g_nsysstatus=SYS_SUB2FS_OBJECT;
			break;

	   	case  SYS_SUB2FS_OBJECT:
			GetAlignStar(g_mFamousStarObjectNum,&AlnStar);
			g_mObjRa=AlnStar.Ra;
			g_mObjDec=AlnStar.Dec;
			g_mTelStatus=1;
		    FPointNewStar(g_mObjRa,g_mObjDec);
		    g_mTargetType=3;
            g_mTargetnum=g_mFamousStarObjectNum;
			WriteRecentTarget(g_mTargetType,g_mTargetnum);
			LCDRfrsh();	
            g_nsysstatus=SYS_SUB2FS_OBJECT1;
			break;

		//����messier�Ǳ�
		case SYS_SUB2MENU4:	 
		    g_mMsrObjectNum=1;
			g_mInputStarNum=0;
			 LCDRfrsh();
			 g_mEQHn=false;//���ʽ��Զ��Ŀ���Ƿ��ڵ�ƽ��
         	g_nsysstatus=SYS_SUB2MSR_OBJECT0;
		 	break;
		case SYS_SUB2MSR_OBJECT0:	 
		    //g_mMsrObjectNum=1;
			//g_mInputStarNum=0;
			 LCDRfrsh();
         	g_nsysstatus=SYS_SUB2MSR_OBJECT;
		 	break;
	   case  SYS_SUB2MSR_OBJECT:
			GetMessier110(g_mMsrObjectNum,&messier);
			g_mObjRa=messier.Ra;
			g_mObjDec=messier.Dec;
			g_mTelStatus=1;
		    FPointNewStar(g_mObjRa,g_mObjDec);
			g_mTargetType=4;
            g_mTargetnum=g_mMsrObjectNum;
			WriteRecentTarget(g_mTargetType,g_mTargetnum);
			 LCDRfrsh();
            g_nsysstatus=SYS_SUB2MSR_OBJECT1;
			break;
		//����NGC�Ǳ�
	   	case SYS_SUB2MENU5:
	     	g_mNgcObjectNum=1;
			g_mInputStarNum=0;
			g_mEQHn=false;//���ʽ��Զ��Ŀ���Ƿ��ڵ�ƽ��
			 LCDRfrsh();
         	g_nsysstatus=SYS_SUB2NGC_OBJECT;
		 	break;
		case  SYS_SUB2NGC_OBJECT:
			 GetNGC7840(g_mNgcObjectNum,&ngc);
			 g_mObjRa=ngc.Ra;
			 g_mObjDec=ngc.Dec;
			g_mTelStatus=1;
		    FPointNewStar(g_mObjRa,g_mObjDec);
			g_mTargetType=5;
            g_mTargetnum=g_mNgcObjectNum;
			WriteRecentTarget(g_mTargetType,g_mTargetnum);
		    LCDRfrsh();
            g_nsysstatus=SYS_SUB2NGC_OBJECT1;
			break;

	   //����IC�Ǳ�
		case  SYS_SUB2MENU6:
	     	g_mIcObjectNum=1;
			g_mInputStarNum=0;
			g_mEQHn=false;//���ʽ��Զ��Ŀ���Ƿ��ڵ�ƽ��
			 LCDRfrsh();
         	g_nsysstatus=SYS_SUB2IC_OBJECT;
		 	break;
		case  SYS_SUB2IC_OBJECT:
		    GetIC5386(g_mIcObjectNum,&ic);
			g_mObjRa=ic.Ra;
			 g_mObjDec=ic.Dec;
			g_mTelStatus=1;
		    FPointNewStar(g_mObjRa,g_mObjDec);
			g_mTargetType=6;
            g_mTargetnum=g_mIcObjectNum;
			WriteRecentTarget(g_mTargetType,g_mTargetnum);
			LCDRfrsh();
            g_nsysstatus=SYS_SUB2IC_OBJECT1;
			break;
	   //����SH2�Ǳ�
	   case  SYS_SUB2MENU7:
	     	g_mSh2ObjectNum=1;
			g_mInputStarNum=0;
			g_mEQHn=false;//���ʽ��Զ��Ŀ���Ƿ��ڵ�ƽ��
			 LCDRfrsh();
         	g_nsysstatus=SYS_SUB2SH2_OBJECT;
		 	break;
	    case  SYS_SUB2SH2_OBJECT:
			GetSh2313(g_mSh2ObjectNum,&sh2);
			g_mObjRa=sh2.Ra;
			g_mObjDec=sh2.Dec;
			g_mTelStatus=1;
		    FPointNewStar(g_mObjRa,g_mObjDec);
			g_mTargetType=7;
            g_mTargetnum=g_mSh2ObjectNum;
			WriteRecentTarget(g_mTargetType,g_mTargetnum);
			LCDRfrsh();
            g_nsysstatus=SYS_SUB2SH2_OBJECT1;
			break;

		//����Bright�Ǳ�
	   case  SYS_SUB2MENU8:
	     	g_mBrightObjectNum=1;
			g_mInputStarNum=0;
			g_mEQHn=false;//���ʽ��Զ��Ŀ���Ƿ��ڵ�ƽ��
			LCDRfrsh();
         	g_nsysstatus=SYS_SUB2BRT_OBJECT;
		 	break;
		case  SYS_SUB2BRT_OBJECT:
		    GetBright167(g_mBrightObjectNum,&bright);
			g_mObjRa=bright.Ra;
			g_mObjDec=bright.Dec;
			g_mTelStatus=1;
		    FPointNewStar(g_mObjRa,g_mObjDec);
			g_mTargetType=8;
            g_mTargetnum=g_mBrightObjectNum;
			WriteRecentTarget(g_mTargetType,g_mTargetnum);
			LCDRfrsh();
            g_nsysstatus=SYS_SUB2BRT_OBJECT1;
			break;

		 //����Sao�Ǳ�
	     case  SYS_SUB2MENU9:
	     	g_mSaoObjectNum=1;
			g_mInputStarNum=0;
			g_mEQHn=false;//���ʽ��Զ��Ŀ���Ƿ��ڵ�ƽ��
				 	LCDRfrsh();
         	g_nsysstatus=SYS_SUB2SAO_OBJECT;
		 	break;
		 case  SYS_SUB2SAO_OBJECT:
		    GetSAO258997(g_mSaoObjectNum,&sao);
			g_mObjRa=sao.Ra;
			g_mObjDec=sao.Dec;
			g_mTelStatus=1;
		    FPointNewStar(g_mObjRa,g_mObjDec);
			g_mTargetType=9;
            g_mTargetnum=g_mSaoObjectNum;
			WriteRecentTarget(g_mTargetType,g_mTargetnum);
			LCDRfrsh();
            g_nsysstatus=SYS_SUB2SAO_OBJECT1;
			break;	
			



		 //�����Զ����Ǳ����Ӳ˵�
	 	case SYS_SUB2MENU11:	
			g_nsysstatus=SYS_MENU_SKY_OBJECT;
			g_mFnum=1;		
			break;

	    case  SYS_MENU_SKY_OBJECT:
			g_mShowMenucolumn=6;
			FRaDecInputShow();
		    g_nsysstatus=SYS_MENU_SKY_NAME;
		   break;
		case  SYS_MENU_SKY_NAME:
		case  SYS_MENU_SKY_RA:
		case  SYS_MENU_SKY_DEC:
		    SaveCStar();
		    g_nsysstatus=SYS_SUB2MENU11;
		   break;



		//ָ��Ŀ��ĳྭ��γ����
	    case SYS_SUB2MENU12:
			g_nsysstatus=SYS_SUB2SUB9RA; //����ྭ��γ����״̬
			g_mShowMenucolumn=6; 	
	    	FRaDecInputShow();
	    	break;
		case SYS_SUB2SUB9RA:
	     	FVerifyRaDecInput(); //ִ�гྭ��γ����
			break;	
		case SYS_SUB2SUB9DEC:
			FVerifyRaDecInput(); //ִ�гྭ��γ����
			break;	 



	    //����½��Ŀ�����Ӳ˵�	

		case SYS_SUB2MENU13:	
			g_nsysstatus=SYS_MENU_LAND_OBJECT;
			g_mFnum=1;
			break;
	    case  SYS_MENU_LAND_OBJECT:
		    FGetTelPos();
		    g_mShowMenucolumn=6;
		    g_nsysstatus=SYS_MENU_LAND_NAME;
		   break;
		case  SYS_MENU_LAND_NAME:
		case  SYS_MENU_LAND_AZI:
		case  SYS_MENU_LAND_ALT:
		    SaveCLand();
		    g_nsysstatus=SYS_SUB2MENU13;
		   break;
			break;



		//���/½��ѡ���ִ��
		case SYS_SUB4MENU4: // �������/½��Ŀ��ѡ��״̬
			g_nsysstatus=SYS_SUB4SUB5SKY;
			break;
		case SYS_SUB4SUB5SKY:
			g_mSkyLand=0; //ִ�����Ŀ��ѡ��
			g_mLandMark=false;
		    g_nsysstatus=SYS_SUB4MENU4; //�˳������½��ѡ���Ӳ˵�
			raspd.i=fabs((int)(6*g_mRaTrackSpeed/15.04));	//����Զ������
	   	    UART1_SentByte(0x55);
			UART1_SentByte(0xAA);
		    UART1_SentByte(0x01);
			UART1_SentByte(0x04);
			UART1_SentByte(65);
			if(g_mRaTrackSpeed>0)
			{
			   UART1_SentByte(1);
			}
			else
			{
			   UART1_SentByte(0);
		 	}
			UART1_SentByte(raspd.ub[1]);
			UART1_SentByte(raspd.ub[0]);

			UART1_SentByte(0x55);
			UART1_SentByte(0xAA);
		    UART1_SentByte(0x01);
			UART1_SentByte(0x04);
			UART1_SentByte(1);
			if(g_mRaTrackSpeed>0)
			{
			   UART1_SentByte(0);
			}
			else
			{
			   UART1_SentByte(1);
			}
			UART1_SentByte(raspd.ub[1]);
			UART1_SentByte(raspd.ub[0]);
			break;
		case SYS_SUB4SUB5LAND:
			g_mSkyLand=1;//ִ�е���Ŀ��ѡ��
			g_mLandMark=true;
		  	//FHandPowerTelescope(); //ֹͣ��Զ���ྭ���˶�
	      	FStopGoto(); //ֹͣ����
		  	g_nsysstatus=SYS_SUB4MENU4;	 //�˳������½��ѡ���Ӳ˵�
			break;
		//��Զ��װ�ó���ʽ/��ƽʽѡ���ִ��
		case SYS_SUB4MENU5: // �������/½��Ŀ��ѡ��״̬
			g_nsysstatus=SYS_SUB4SUB6AZ;
			break;
		case SYS_SUB4SUB6AZ:
		   
			g_mAzEq=0; //ִ�е�ƽʽ��Զ��ѡ��
		
		    g_nsysstatus=SYS_SUB4MENU5; //�˳�����Զ��װ�ó���ʽ/��ƽʽѡ���Ӳ˵�
			break;
		case SYS_SUB4SUB6EQ:
	
		  	 g_mAzEq=1;//ִ�г��ʽ��Զ��ѡ��
		
		  	g_nsysstatus=SYS_SUB4MENU5;	 //�˳�����Զ��װ�ó���ʽ/��ƽʽѡ���Ӳ˵�
			break;
 
		//�˵�����ѡ��
		case SYS_SUB4MENU8 :  //������Զ������ѡ���Ӳ˵�
	    	g_nsysstatus=SYS_SUB4SUB9EN;
			break;
		//ִ������ѡ��,�˵�״̬����
		case SYS_SUB4SUB9EN:  	//ִ������ѡ��
	   		 g_mMenuLangauge=1;
			 ReadFromRom(3531,0,528,g_rdata);	 
	         g_rdata[0]=g_mMenuLangauge;
	         WriteToRom(3531,0,528,g_rdata);	 
	   		 g_nsysstatus=SYS_SUB4MENU8 ;
			break;
		case SYS_SUB4SUB9GER:  	//ִ������ѡ��
	     	 g_mMenuLangauge=2;
			 ReadFromRom(3531,0,528,g_rdata);	 
	         g_rdata[0]=g_mMenuLangauge;
	         WriteToRom(3531,0,528,g_rdata);	 
		 	g_nsysstatus=SYS_SUB4MENU8 ;
			break;
		case SYS_SUB4SUB9FRE:  	//ִ������ѡ��
	    	g_mMenuLangauge=3;
			 ReadFromRom(3531,0,528,g_rdata);	 
	         g_rdata[0]=g_mMenuLangauge;
	         WriteToRom(3531,0,528,g_rdata);	 
		 	g_nsysstatus=SYS_SUB4MENU8 ;
			break;
		case SYS_SUB4SUB9ITA:  	//ִ������ѡ��
	     	g_mMenuLangauge=4;
			 ReadFromRom(3531,0,528,g_rdata);	 
	         g_rdata[0]=g_mMenuLangauge;
	         WriteToRom(3531,0,528,g_rdata);	 
		 	g_nsysstatus=SYS_SUB4MENU8 ;
			break;
		case SYS_SUB4SUB9SPA:  	//ִ������ѡ��
	     	g_mMenuLangauge=5;
			 ReadFromRom(3531,0,528,g_rdata);	 
	         g_rdata[0]=g_mMenuLangauge;
	         WriteToRom(3531,0,528,g_rdata);	 
		 	g_nsysstatus=SYS_SUB4MENU8 ;
			break;




		//�����ٶ�����
		case SYS_SUB4SUB8MENU1:
			g_mRaTrackSpeed=0; //������
			g_mTrackSpeed=0.0;//�����ٶ�0�����٣�1̫���٣�2�����٣�3�Զ���
			FBeep(2);
			g_nsysstatus=SYS_MAINSHOW;
	    	break;
		case SYS_SUB4SUB8MENU2:
			g_mRaTrackSpeed=0.0029014*0.37/3600.0;//̫���� (̫���ྭÿÿ��0.0029014ʱ��,һ��ϵͳ�ջ�������:0.37��)
			g_mTrackSpeed=1;//�����ٶ�0�����٣�1̫���٣�2�����٣�3�Զ���
			FBeep(2);
			g_nsysstatus=SYS_MAINSHOW;
			break;
		case SYS_SUB4SUB8MENU3:
			g_mRaTrackSpeed=0.03667*0.37/3600.0; //������   (�����ྭÿ����0.03667ʱ��,һ��ϵͳ�ջ�������:0.37��)
			g_mTrackSpeed=2;//�����ٶ�0�����٣�1̫���٣�2�����٣�3�Զ���
			FBeep(2);
			g_nsysstatus=SYS_MAINSHOW;
			break;


		//�����Զ����ٶ�
		case SYS_SUB4SUB8MENU4:
	    	g_mShowMenucolumn=1;
		    sprintf(g_sysmenu4800raspeed,"+0%.2f������      ",1.0);	
		    sprintf(g_sysmenu4800raspeedEn,"+0%.2f  starspeed",1.0);

			g_nsysstatus=SYS_SUB4SUB8MENU4_RASPEED;	 //�Զ�������ٶ�  
			break;
		case SYS_SUB4SUB8MENU4_RASPEED:
		    g_mTrackSpeed=3;//�����ٶ�0�����٣�1̫���٣�2�����٣�3�Զ���
			g_mRaTrackSpeed=(1-atof(&g_sysmenu4800raspeed[0]))*0.37/3600.0;
		
			FBeep(2);
			g_nsysstatus=SYS_MAINSHOW;	 //�Զ�������ٶ�
			break;
		case SYS_SUB3MENU9:
	     	FStartGoto();
		 	g_mTelGoHome=true;//��Զ������
			//FBeep(3);
		 	g_nsysstatus=SYS_MAINSHOW;	 //��Զ�����㲢����������
			break; 

		//��������
		case SYS_SUB3MENU1:	     
		   g_mSunSysObjectNum=0;
		   g_nsysstatus=SYS_SUB3SUB1NOW_APH;	
			break; 


		//����ʱ������
	   	case  SYS_SUB4MENU1:
		     GetSysTime();
	   	  	sprintf(g_sysmenu4100dateEn,"%04d-%02d-%02d",g_mDate_year,g_mDate_month,g_mDate_day);
	      	sprintf(g_sysmenu4100timeEn,"%02d:%02d:%02d",g_mTime_hour,g_mTime_minute,g_mTime_second);
	      	sprintf(g_sysmenu4100date,"%04d-%02d-%02d",g_mDate_year,g_mDate_month,g_mDate_day);
	      	sprintf(g_sysmenu4100time,"%02d:%02d:%02d",g_mTime_hour,g_mTime_minute,g_mTime_second);
	      	g_mShowMenucolumn=1;
		  	g_mdatetime=0;
		  	g_nsysstatus=SYS_SUB4SUB1_SETTIME;
		  	break;
	   	//ʱ�����ò������ϲ�˵�
	   	case  SYS_SUB4SUB1_SETTIME:
	      	if(FSetSysTime()==1)
		  	{
			    if(g_mSysInitGuide==1)
				{
				  g_nsysstatus=SYS_SUB4SUB2MENU2;

				 }
				 else
				 {
				   g_nsysstatus=SYS_SUB4MENU1;     
				 }
				FBeep(1);
		  	}
		  	else
		  	{	GetSysTime();
		  		sprintf(g_sysmenu4100dateEn,"%04d-%02d-%02d",g_mDate_year,g_mDate_month,g_mDate_day);
	      		sprintf(g_sysmenu4100timeEn,"%02d:%02d:%02d",g_mTime_hour,g_mTime_minute,g_mTime_second);
	      		sprintf(g_sysmenu4100date,"%04d-%02d-%02d",g_mDate_year,g_mDate_month,g_mDate_day);
	      		sprintf(g_sysmenu4100time,"%02d:%02d:%02d",g_mTime_hour,g_mTime_minute,g_mTime_second);
	      		g_mShowMenucolumn=1;
		  		g_mdatetime=0;
		  		g_nsysstatus=SYS_SUB4SUB1_SETTIME;
		  	}
			break;

     //��������ʱ����
		case SYS_SUB4MENU2:
			if(g_mDaylight==false)
			{
			  g_nsysstatus=SYS_SUB4SUB2MENU2;
			}
			else
			{
			  g_nsysstatus=SYS_SUB4SUB2MENU1;
			 }
			break;				
		 //��������ʱ����
		case SYS_SUB4SUB2MENU1:
		case SYS_SUB4SUB2MENU2:
	       if(g_mSysInitGuide==1)
			{
			   g_nsysstatus=SYS_SUB4SUB3MENU1;
			 }
			 else
			 {
			   FBeep(1);
			   g_nsysstatus=SYS_SUB4MENU2;     
			 }
				   
	    	break;
		//�������ѡ��
    	case SYS_SUB4SUB3MENU1:
		   	Nationnum=1;
			Citynum=0;
		    LCDRfrsh();
			g_nsysstatus=SYS_SUB4SUB3SUN1_CITYSEL;
			break;
		//ִ�г���ѡ���˳��ϲ�˵�
		case SYS_SUB4SUB3SUN1_CITYSEL:
                 GetWorldCity170(Nationnum+Citynum,&city1);
				  g_mSitLon=city1.Lon;
				  g_mSitLat=city1.Lat;
				  g_mTimeZone=city1.Zone;//((int)city1.Lon)%15;
				  g_mGoto.m_nLongitude=g_mSitLon;
		       	  g_mGoto.m_nAtitude=g_mSitLat;
		          g_mGoto.m_nTimeZone=g_mTimeZone;

	        FBeep(2);
			if(g_mSysInitGuide==1)
			{
			    if(g_mTelescopeConType==1)
				{
//			      	LCDRfrsh();
//					//ϵͳ���ڳ�ʼ��
//					//DispEn(0,5,1,22,"   Ver. 0.97 EQ/AZ    ");
//					DispEn(0,4,1,22,"System Initializing...");
//					GetPlanetPos();//��������λ��
//					MenuDelay(1000);  
//					//ϵͳ��ʼ�������					
//					FBeep(1);
//					LCDRfrsh();
//					DispEn(0,4,1,22,"System Initialized    ");
//					MenuDelay(1000);
//					LCDRfrsh();
					g_mcalpalnet=0;

				    g_nsysstatus=SYS_MAINSHOW;
				    g_mSysInitGuide=0;
				 // FBeep(3);
				  
				 }
				 else
				 {
			   	   g_nsysstatus=SYS_SUB4SUB7_TELAZIALT_ZERO; 
				 } 
			 }
			 else
			 {
		
			   g_nsysstatus=SYS_MAINSHOW;     
			 }
		
			break; 
	  	//�Զ���ص�
	    case  SYS_SUB4SUB3MENU2:
		
		  	g_mMySiteOperator=1;
		  	g_mMySiteShowMode=0;
		  	g_mShowMenucolumn=7;
			
		   GetSite(g_sitenametemp,&g_mSitLontemp,&g_mSitLattemp,&g_mTimeZonetemp);
		   g_sysmenu4300sitenameEn[6]=g_sitenametemp[0];
		   g_sysmenu4300sitenameEn[7]=g_sitenametemp[1];
		   g_sysmenu4300sitenameEn[8]=g_sitenametemp[2];
		   g_sysmenu4300sitenameEn[9]=g_sitenametemp[3];
		   g_sysmenu4300sitenameEn[10]=g_sitenametemp[4];
		   g_sysmenu4300sitenameEn[11]=g_sitenametemp[5];
		   g_sysmenu4300sitenameEn[12]=g_sitenametemp[6];
		   g_sysmenu4300sitenameEn[13]=g_sitenametemp[7];
	
	  	   if(g_mSitLontemp>0)
		   {
		     sprintf(g_sysmenu4300sitelonEn,"  Lon:E%03dd%02df ",abs((int)g_mSitLontemp),abs((int)((g_mSitLontemp-(int)g_mSitLontemp)*60)));
			 }
			 else
			 {
			    sprintf(g_sysmenu4300sitelonEn,"  Lon:W%03dd%02df ",abs((int)g_mSitLontemp),abs((int)((g_mSitLontemp-(int)g_mSitLontemp)*60)));
			 }
		  
		   if(g_mSitLattemp>0)
		   {
		       sprintf(g_sysmenu4300sitelatEn,"  Lat:N%02dd%02df ",abs((int)g_mSitLattemp),abs((int)((g_mSitLattemp-(int)g_mSitLattemp)*60)));
			 }
			 else
			 {
			   sprintf(g_sysmenu4300sitelatEn,"  Lat:S%02dd%02df ",abs((int)g_mSitLattemp),abs((int)((g_mSitLattemp-(int)g_mSitLattemp)*60)));
			 }
	
			 if(g_mTimeZonetemp>0)
			 {
			     sprintf(g_sysmenu4300sitezoneEn," Zone:E%02d",abs(g_mTimeZonetemp));
			 }
			 else
			 {
			   sprintf(g_sysmenu4300sitezoneEn," Zone:W%02d",abs(g_mTimeZonetemp));
			 }
	
			  g_nsysstatus=SYS_SUB4SUB3_SETSITE;
	
			  	break;			
		
		//ִ���Զ���ص㲢����
			case SYS_SUB4SUB3_SETSITE:
					FverifyInputSite();
					break;
	
			case SYS_SUB4MENU9:	//�ָ�����״̬ 
				 g_nsysstatus=SYS_RESET;
			     break;
			case SYS_RESET:
			      SysReset();
				  break;
	
		//������Զ��������ȷ�Ӳ˵�
			case SYS_SUB4SUB7_TELAZIALT_ZERO:
				  FverifyInputAziAltZero();
			  	break;
	
	
			//������������ྭ��γ����
			case SYS_SUB3MENU2: 
				g_nsysstatus=SYS_SUB2SUB9RA; //����ྭ��γ����״̬
				g_mShowMenucolumn=6; 	
			    FRaDecInputShow();
				g_mRaDecMode=1;
				break;
			case SYS_SUB3SUB2_STARRISESET:
				g_nsysstatus=SYS_SUB2SUB9RA; //��������������ʾ
		    	break;
			//����������ʾ
			case  SYS_SUB3MENU3:
			 	g_nsysstatus=SYS_SUB3SUB3_MOONPHASE;
			 	GetTime();
			 	break;

   		//����ʱ�Ӳ˵�
		case SYS_SUB3MENU4:
        	if(g_mObjTimer_sec>0)
			{
				g_nsysstatus=SYS_SUB3SUB4TIMER_ONOFF;
				//����ʱ��ʱ״̬	
			}
			else
			{
				g_nsysstatus=SYS_SUB3SUB4TIMER_INPUT;
				g_mShowMenucolumn=1;
				//����ʱ�趨״̬
			}
			break;
		case SYS_SUB3SUB4TIMER_INPUT: //�뵹��ʱ���÷���
			if(g_mMenuLangauge==1)  
			g_mObjTimer_sec=atoi(&g_sysmenu3402offEn[0]);
			else
			g_mObjTimer_sec=atoi(&g_sysmenu3402off[0]);
			if(g_mObjTimer_sec==0)
				g_nsysstatus=SYS_SUB3SUB4TIMER_INPUT;
			else
				g_nsysstatus=SYS_SUB3SUB4TIMER_ONOFF;
			break;
		case SYS_SUB3SUB4TIMER_ONOFF: //�뵹��ʱ���÷���
			g_mObjTimer_sec=0;
			g_nsysstatus=SYS_SUB3SUB4TIMER_INPUT;
			break;
		//���붨ʱ�������Ӳ˵�
		case SYS_SUB3MENU5:
			if(g_mObjAlarm_open==1)
			{
				g_nsysstatus=SYS_SUB3SUB5ALARM_ONOFF;
			}
			else
			{
				g_nsysstatus=SYS_SUB3SUB5ALARM_INPUT;
				g_mShowMenucolumn=1;
			}
			break;
		case SYS_SUB3SUB5ALARM_INPUT://�������ӷ���
	    	FVerifyAlarmInput();
			break;
		case SYS_SUB3SUB5ALARM_ONOFF://�������ӷ���
			g_mObjAlarm_open=0;
			g_nsysstatus=SYS_SUB3SUB5ALARM_INPUT;
			break;
		//������Զ����Ұ��ʾ״̬
		case SYS_SUB3SUB6MENU1:
	    	g_nsysstatus=SYS_SUB3SUB6SUB1LOV_TELTYPE1;
	    	break;


		case SYS_SUB3SUB6SUB2M_MF:   //���뱶�ʼ���������������״̬
		case SYS_SUB3SUB6SUB2M_SF:   ///���뱶�ʼ���������������״̬
	     	

			g_mObjM_MF=1.0*atoi(&g_sysmenu3602m_mfEn[6]);
		 	g_mObjM_SF=1.0*atoi(&g_sysmenu3602m_sfEn[6]);

		 	
			g_mObjM_Multi=g_mObjM_MF/g_mObjM_SF;
			 

			 sprintf(g_sysmenu3602m_dataEn,"Magnification = %.1f         ",g_mObjM_Multi);

			FBeep(1);
			g_mShowMenucolumn=7;
		    g_nsysstatus=SYS_SUB3SUB6SUB2M_MF;
		 	break;


		case SYS_SUB3SUB6SUB2M_MF1:   //���뱶�ʼ���������������״̬
		case SYS_SUB3SUB6SUB2M_SF1:   ///���뱶�ʼ���������������״̬
		case SYS_SUB3SUB6SUB2M_MFOV:   //��Զ�������ӳ�
		     g_mObjM_MF=1.0*atoi(&g_sysmenu3602m_mfEn[6]);
		 	 g_mObjM_SF=1.0*atoi(&g_sysmenu3602m_sfEn[6]);
			 g_mObjM_Mfov=1.0*atoi(&g_sysmenu3602m_mfovEn[6])+0.016666667*atoi(&g_sysmenu3602m_mfovEn[9]);
		 	
			g_mObjM_Multi=g_mObjM_MF/g_mObjM_SF;
			g_mObjM_fov=g_mObjM_Mfov/g_mObjM_Multi;
			 

			 sprintf(g_sysmenu3602m_dataEn1,"         FOV:%0.5f         ",g_mObjM_fov);

			FBeep(1);
			g_mShowMenucolumn=7;
		    g_nsysstatus=SYS_SUB3SUB6SUB2M_MF1;
		break;


		 	case SYS_SUB3SUB6SUB2M_Multi:
		 	g_mObjM_MF=atoi(&g_sysmenu3602m_mf[6]);
		 	g_mObjM_SF=atoi(&g_sysmenu3602m_sf[6]);
		 	g_mObjM_Multi=g_mObjM_MF/g_mObjM_SF;
	     	break;
//		

		//����Ұ��������
		case SYS_SUB3SUB8MENU1:
			g_nsysstatus=SYS_SUB3SUB8MENU1Screen;
	 	   	break;
		case SYS_SUB3SUB8MENU1Screen:
		    FKeyTorch();
			break;
		case SYS_SUB3SUB8MENU2:
			 if(!g_mbacklight)
			{
			    LCDBacklight(255);
				g_mbacklight=true;
			} 
			else
			{	  	
			  LCDBacklight(0);
			  g_mbacklight=false;	      
		    }		
			break;
		
     	default:

		break ;
	}
}


//*******************************************************************


//*******************************************************************
 //�Բ˵�����g_mShowMenuFtEn,g_mShowMenuFtCn��g_mShowMenurowEn,g_mShowMenurowCn ������ר�ú���
void DoMenurowFtCnFtEnAddDec(uint8 nadddec,uint8 CnEn)	//�Բ˵�����g_mShowMenuFtEn,g_mShowMenuFtCn��g_mShowMenurowEn,g_mShowMenurowCn ������ר�ú���
{  
   switch (nadddec )
   {  
        case 0 :
		   switch(CnEn)
		   {
		      case 11:

				 if(g_mShowMenurowUn11>1)
				{
				  g_mShowMenurowUn11--;
				}
				else
				{	
				  g_mShowMenuFtUn11--;
				}


				if(g_mShowMenurowEn11>1)
				{
				  g_mShowMenurowEn11--;
				}
				else
				{	
				  g_mShowMenuFtEn11--;
				}
			  break;
			  case 12:


				 if(g_mShowMenurowUn12>1)
				{
				  g_mShowMenurowUn12--;
				}
				else
				{	
				  g_mShowMenuFtUn12--;
				}


				if(g_mShowMenurowEn12>1)
				{
				  g_mShowMenurowEn12--;
				}
				else
				{	
				  g_mShowMenuFtEn12--;
				}
			  break;
			  case 13:


				 if(g_mShowMenurowUn13>1)
				{
				  g_mShowMenurowUn13--;
				}
				else
				{	
				  g_mShowMenuFtUn13--;
				}


				if(g_mShowMenurowEn13>1)
				{
				  g_mShowMenurowEn13--;
				}
				else
				{	
				  g_mShowMenuFtEn13--;
				}
			break;
			case 14:

				 if(g_mShowMenurowUn14>1)
				{
				  g_mShowMenurowUn14--;
				}
				else
				{	
				  g_mShowMenuFtUn14--;
				}


				if(g_mShowMenurowEn14>1)
				{
				  g_mShowMenurowEn14--;
				}
				else
				{	
				  g_mShowMenuFtEn14--;
				}
			  break;
			case 22:

				if(g_mShowMenurowEn22>1)
				{
				  g_mShowMenurowEn22--;
				}
				else
				{	
				  g_mShowMenuFtEn22--;
				}
			  break;
			case 23:

				if(g_mShowMenurowEn23>1)
				{
				  g_mShowMenurowEn23--;
				}
				else
				{	
				  g_mShowMenuFtEn23--;
				}
			  break;
			 
			  default:break;
		   }
		  break	;
		case 1:
		  switch(CnEn)
		   {
		      case 11:

			   if(g_mShowMenurowUn11<4)
				{
				  g_mShowMenurowUn11++;
				}
				else
				{	
				  g_mShowMenuFtUn11++;
				}


				if(g_mShowMenurowEn11<8)
				{
				  g_mShowMenurowEn11++;
				}
				else
				{	
				  g_mShowMenuFtEn11++;
				}
			  break;
			  case 12:

				if(g_mShowMenurowUn12<4)
				{
				  g_mShowMenurowUn12++;
				}
				else
				{	
				  g_mShowMenuFtUn12++;
				}


				if(g_mShowMenurowEn12<8)
				{
				  g_mShowMenurowEn12++;
				}
				else
				{	
				  g_mShowMenuFtEn12++;
				}
			  break;
			  case 13:

				 if(g_mShowMenurowUn13<4)
				{
				  g_mShowMenurowUn13++;
				}
				else
				{	
				  g_mShowMenuFtUn13++;
				}


				if(g_mShowMenurowEn13<8)
				{
				  g_mShowMenurowEn13++;
				}
				else
				{	
				  g_mShowMenuFtEn13++;
				}
			  break;
			  case 14:
				if(g_mShowMenurowUn14<4)
				{
				  g_mShowMenurowUn14++;
				}
				else
				{	
				  g_mShowMenuFtUn14++;
				}

				if(g_mShowMenurowEn14<8)
				{
				  g_mShowMenurowEn14++;
				}
				else
				{	
				  g_mShowMenuFtEn14++;
				}
			  break;
			case 22:

				if(g_mShowMenurowEn22<8)
				{
				  g_mShowMenurowEn22++;
				}
				else
				{	
				  g_mShowMenuFtEn22++;
				}
			  break;
			case 23:

				if(g_mShowMenurowEn23<8)
				{
				  g_mShowMenurowEn23++;
				}
				else
				{	
				  g_mShowMenuFtEn23++;
				}
			  break;
			  default:break;
		   }
		  break;
		default:break;
   }
} //*************************************************


////************************************************************************************************************************
////��ȡ���Ĳ˵�Ҫ��ʾ�Ķ���
//void GetMenuScreenCn(uint8 menunum,uint8 ScreenFirst)	
//{
//   switch( menunum )
//   {
//       case 11:
//	            switch(	ScreenFirst)
//				{
//				   case 1:
//				   	gstrlineCn1=g_sysmenu1100;				
//					gstrlineCn2=g_sysmenu1200;				
//					gstrlineCn3=g_sysmenu1300;				
//					gstrlineCn4=g_sysmenu1400;				         
//				   break;
//				    case 2:
//				   	gstrlineCn1=g_sysmenu1200;				
//					gstrlineCn2=g_sysmenu1300;				
//					gstrlineCn3=g_sysmenu1400;				
//					gstrlineCn4=g_sysmenu1500;				         
//				   break;
//				   case 3:
//				   	gstrlineCn1=g_sysmenu1300;				
//					gstrlineCn2=g_sysmenu1400;				
//					gstrlineCn3=g_sysmenu1500;				
//					gstrlineCn4=g_sysmenu1600;				         
//				   break;
//				   case 4:
//				   	gstrlineCn1=g_sysmenu1400;				
//					gstrlineCn2=g_sysmenu1500;				
//					gstrlineCn3=g_sysmenu1600;				
//					gstrlineCn4=g_sysmenu1700;				         
//				   break;
//				   case 5:
//				   	gstrlineCn1=g_sysmenu1500;				
//					gstrlineCn2=g_sysmenu1600;				
//					gstrlineCn3=g_sysmenu1700;				
//					gstrlineCn4=g_sysmenu1800; 									         
//				   break;
//				   case 6:
//				   	gstrlineCn1=g_sysmenu1600;				
//					gstrlineCn2=g_sysmenu1700;				
//					gstrlineCn3=g_sysmenu1800;				
//					gstrlineCn4=g_sysmenu1900;				         
//				   break;
//				   case 7:
//				   	gstrlineCn1=g_sysmenu1700;				
//					gstrlineCn2=g_sysmenu1800;				
//					gstrlineCn3=g_sysmenu1900;				
//					gstrlineCn4=g_sysmenu1110;				         
//				   break;
//				   case 8:
//				   	gstrlineCn1=g_sysmenu1800;				
//					gstrlineCn2=g_sysmenu1900;				
//					gstrlineCn3=g_sysmenu1110;				
//					gstrlineCn4=g_sysmenu1120;				         
//				   break;
//				   default:break;
//				}
//	              break;
//			case 12:
//	            switch(	ScreenFirst)
//				{
//				   case 1:
//				   	gstrlineCn1=g_sysmenu2100;				
//					gstrlineCn2=g_sysmenu2200;				
//					gstrlineCn3=g_sysmenu2300;				
//					gstrlineCn4=g_sysmenu2400;				         
//				   break;
//				    case 2:
//				   	gstrlineCn1=g_sysmenu2200;				
//					gstrlineCn2=g_sysmenu2300;				
//					gstrlineCn3=g_sysmenu2400;				
//					gstrlineCn4=g_sysmenu2500;				         
//				   break;
//				   case 3:
//				   	gstrlineCn1=g_sysmenu2300;				
//					gstrlineCn2=g_sysmenu2400;				
//					gstrlineCn3=g_sysmenu2500;				
//					gstrlineCn4=g_sysmenu2600;				         
//				   break;
//				   case 4:
//				   	gstrlineCn1=g_sysmenu2400;				
//					gstrlineCn2=g_sysmenu2500;				
//					gstrlineCn3=g_sysmenu2600;				
//					gstrlineCn4=g_sysmenu2700;				         
//				   break;
//				   case 5:
//				   	gstrlineCn1=g_sysmenu2500;				
//					gstrlineCn2=g_sysmenu2600;				
//					gstrlineCn3=g_sysmenu2700;				
//					gstrlineCn4=g_sysmenu2800; 									         
//				   break;
//				   case 6:
//				   	gstrlineCn1=g_sysmenu2600;				
//					gstrlineCn2=g_sysmenu2700;				
//					gstrlineCn3=g_sysmenu2800;				
//					gstrlineCn4=g_sysmenu2900;				         
//				   break;
//				   case 7:
//				   	gstrlineCn1=g_sysmenu2700;				
//					gstrlineCn2=g_sysmenu2800;				
//					gstrlineCn3=g_sysmenu2900;				
//					gstrlineCn4=g_sysmenu2110;				         
//				   break;
//
//				   case 8:
//				   	gstrlineCn1=g_sysmenu2800;				
//					gstrlineCn2=g_sysmenu2900;				
//					gstrlineCn3=g_sysmenu2110;				
//					gstrlineCn4=g_sysmenu2120;				         
//				   break;
//				   case 9:
//				   	gstrlineCn1=g_sysmenu2900;				
//					gstrlineCn2=g_sysmenu2110;				
//					gstrlineCn3=g_sysmenu2120;				
//					gstrlineCn4=g_sysmenu2130;				         
//				   break;
//
//				   default:break;
//				}
//	              break;
//			 case 13:
//	            switch(	ScreenFirst)
//				{
//				   case 1:
//				   	gstrlineCn1=g_sysmenu3100;				
//					gstrlineCn2=g_sysmenu3200;				
//					gstrlineCn3=g_sysmenu3300;				
//					gstrlineCn4=g_sysmenu3400;				         
//				   break;
//				    case 2:
//				   	gstrlineCn1=g_sysmenu3200;				
//					gstrlineCn2=g_sysmenu3300;				
//					gstrlineCn3=g_sysmenu3400;				
//					gstrlineCn4=g_sysmenu3500;				         
//				   break;
//				   case 3:
//				   	gstrlineCn1=g_sysmenu3300;				
//					gstrlineCn2=g_sysmenu3400;				
//					gstrlineCn3=g_sysmenu3500;				
//					gstrlineCn4=g_sysmenu3600;				         
//				   break;
//				   case 4:
//				   	gstrlineCn1=g_sysmenu3400;				
//					gstrlineCn2=g_sysmenu3500;				
//					gstrlineCn3=g_sysmenu3600;				
//					gstrlineCn4=g_sysmenu3700;				         
//				   break;
//				   case 5:
//				   	gstrlineCn1=g_sysmenu3500;				
//					gstrlineCn2=g_sysmenu3600;				
//					gstrlineCn3=g_sysmenu3700;				
//					gstrlineCn4=g_sysmenu3800; 									         
//				   break;
//				   case 6:
//				   	gstrlineCn1=g_sysmenu3600;				
//					gstrlineCn2=g_sysmenu3700;				
//					gstrlineCn3=g_sysmenu3800;				
//					gstrlineCn4=g_sysmenu3900;				         
//				   break;
//				   case 7:
//				   	gstrlineCn1=g_sysmenu3700;				
//					gstrlineCn2=g_sysmenu3800;				
//					gstrlineCn3=g_sysmenu3900;				
//					gstrlineCn4=g_sysmenu3110;				         
//				   break;
//				   	 default:break;
//				} 
//	              break;
//			 case 14:
//	            switch(	ScreenFirst)
//				{
//				   case 1:
//				   	gstrlineCn1=g_sysmenu4100;				
//					gstrlineCn2=g_sysmenu4200;				
//					gstrlineCn3=g_sysmenu4300;				
//					gstrlineCn4=g_sysmenu4400;				         
//				   break;
//				    case 2:
//				   	gstrlineCn1=g_sysmenu4200;				
//					gstrlineCn2=g_sysmenu4300;				
//					gstrlineCn3=g_sysmenu4400;				
//					gstrlineCn4=g_sysmenu4500;				         
//				   break;
//				   case 3:
//				   	gstrlineCn1=g_sysmenu4300;				
//					gstrlineCn2=g_sysmenu4400;				
//					gstrlineCn3=g_sysmenu4500;				
//					gstrlineCn4=g_sysmenu4600;				         
//				   break;
//				   case 4:
//				   	gstrlineCn1=g_sysmenu4400;				
//					gstrlineCn2=g_sysmenu4500;				
//					gstrlineCn3=g_sysmenu4600;				
//					gstrlineCn4=g_sysmenu4700;				         
//				   break;
//				   case 5:
//				   	gstrlineCn1=g_sysmenu4500;				
//					gstrlineCn2=g_sysmenu4600;				
//					gstrlineCn3=g_sysmenu4700;				
//					gstrlineCn4=g_sysmenu4800; 									         
//				   break;
//				   case 6:
//				   	gstrlineCn1=g_sysmenu4600;				
//					gstrlineCn2=g_sysmenu4700;				
//					gstrlineCn3=g_sysmenu4800;				
//					gstrlineCn4=g_sysmenu4900;				         
//				   break;
//				   case 7:
//				   	gstrlineCn1=g_sysmenu4700;				
//					gstrlineCn2=g_sysmenu4800;				
//					gstrlineCn3=g_sysmenu4900;				
//					gstrlineCn4=g_sysmenu4110;				         
//				   break;
////				   case 8:
////				   	gstrlineCn1=g_sysmenu4800;				
////					gstrlineCn2=g_sysmenu4900;				
////					gstrlineCn3=g_sysmenu4110;				
////					gstrlineCn4=g_sysmenu4120;				         
////				   break;
//				   default:break;
//				}
//				break;
//			 case 22:
//	            switch(	ScreenFirst)
//				{
//				   case 1:
//				   	gstrlineCn1=g_sysmenu2201;				
//					gstrlineCn2=g_sysmenu2202;				
//					gstrlineCn3=g_sysmenu2203;				
//					gstrlineCn4=g_sysmenu2204;				         
//				   break;
//				    case 2:
//				   	gstrlineCn1=g_sysmenu2202;				
//					gstrlineCn2=g_sysmenu2203;				
//					gstrlineCn3=g_sysmenu2204;				
//					gstrlineCn4=g_sysmenu2205;				         
//				   break;
//				   case 3:
//				   	gstrlineCn1=g_sysmenu2203;				
//					gstrlineCn2=g_sysmenu2204;				
//					gstrlineCn3=g_sysmenu2205;				
//					gstrlineCn4=g_sysmenu2206;				         
//				   break;
//				   case 4:
//				   	gstrlineCn1=g_sysmenu2204;				
//					gstrlineCn2=g_sysmenu2205;				
//					gstrlineCn3=g_sysmenu2206;				
//					gstrlineCn4=g_sysmenu2207;				         
//				   break;
//				   case 5:
//				   	gstrlineCn1=g_sysmenu2205;				
//					gstrlineCn2=g_sysmenu2206;				
//					gstrlineCn3=g_sysmenu2207;				
//					gstrlineCn4=g_sysmenu2208; 									         
//				   break;
//				   case 6:
//				   	gstrlineCn1=g_sysmenu2206;				
//					gstrlineCn2=g_sysmenu2207;				
//					gstrlineCn3=g_sysmenu2208;				
//					gstrlineCn4=g_sysmenu2209;				         
//				   break;
//				   case 7:
//				   	gstrlineCn1=g_sysmenu2207;				
//					gstrlineCn2=g_sysmenu2208;				
//					gstrlineCn3=g_sysmenu2209;				
//					gstrlineCn4=g_sysmenu22010;				         
//				   break; 
//				  case 8:
//				   	gstrlineCn1=g_sysmenu2208;				
//					gstrlineCn2=g_sysmenu2209;				
//					gstrlineCn3=g_sysmenu22010;				
//					gstrlineCn4=g_sysmenu22011;				         
//				   break;   				  
//				   default:break;
//				}
//				break;
//
//			 case 23:
//	            switch(	ScreenFirst)
//				{
//				   case 1:
//				   	gstrlineCn1=g_sysmenu2301;				
//					gstrlineCn2=g_sysmenu2302;				
//					gstrlineCn3=g_sysmenu2303;				
//					gstrlineCn4=g_sysmenu2304;				         
//				   break;
//				    case 2:
//				   	gstrlineCn1=g_sysmenu2302;				
//					gstrlineCn2=g_sysmenu2303;				
//					gstrlineCn3=g_sysmenu2304;				
//					gstrlineCn4=g_sysmenu2305;				         
//				   break;
//				   case 3:
//				   	gstrlineCn1=g_sysmenu2303;				
//					gstrlineCn2=g_sysmenu2304;				
//					gstrlineCn3=g_sysmenu2305;				
//					gstrlineCn4=g_sysmenu2306;				         
//				   break;
//				   case 4:
//				   	gstrlineCn1=g_sysmenu2304;				
//					gstrlineCn2=g_sysmenu2305;				
//					gstrlineCn3=g_sysmenu2306;				
//					gstrlineCn4=g_sysmenu2307;				         
//				   break;
//				   case 5:
//				   	gstrlineCn1=g_sysmenu2305;				
//					gstrlineCn2=g_sysmenu2306;				
//					gstrlineCn3=g_sysmenu2307;				
//					gstrlineCn4=g_sysmenu2308; 									         
//				   break;
//				    				  
//				   default:break;
//				}
//	              break;
//
//	    default: break;
//	}
//}
//************************************************************************************************************************

//************************************************************************************************************************
//��ȡ��������������������˵�Ҫ��ʾ�Ķ���
void GetMenuScreenUn(uint8 menunum,uint8 ScreenFirst)	
{
   switch( menunum )
   {
       case 11:
	            switch(	ScreenFirst)
				{
				   case 1:
				   	gstrlineUn1=g_sysmenu1100;				
					gstrlineUn2=g_sysmenu1200;				
					gstrlineUn3=g_sysmenu1300;				
					gstrlineUn4=g_sysmenu1400;				         
				   break;
				    case 2:
				   	gstrlineUn1=g_sysmenu1200;				
					gstrlineUn2=g_sysmenu1300;				
					gstrlineUn3=g_sysmenu1400;				
					gstrlineUn4=g_sysmenu1500;				         
				   break;
				   case 3:
				   	gstrlineUn1=g_sysmenu1300;				
					gstrlineUn2=g_sysmenu1400;				
					gstrlineUn3=g_sysmenu1500;				
					gstrlineUn4=g_sysmenu1600;				         
				   break;
				   case 4:
				   	gstrlineUn1=g_sysmenu1400;				
					gstrlineUn2=g_sysmenu1500;				
					gstrlineUn3=g_sysmenu1600;				
					gstrlineUn4=g_sysmenu1700;				         
				   break;
				   case 5:
				   	gstrlineUn1=g_sysmenu1500;				
					gstrlineUn2=g_sysmenu1600;				
					gstrlineUn3=g_sysmenu1700;				
					gstrlineUn4=g_sysmenu1800; 									         
				   break;
				   case 6:
				   	gstrlineUn1=g_sysmenu1600;				
					gstrlineUn2=g_sysmenu1700;				
					gstrlineUn3=g_sysmenu1800;				
					gstrlineUn4=g_sysmenu1900;				         
				   break;
				   case 7:
				   	gstrlineUn1=g_sysmenu1700;				
					gstrlineUn2=g_sysmenu1800;				
					gstrlineUn3=g_sysmenu1900;				
					gstrlineUn4=g_sysmenu1110;				         
				   break;
				   case 8:
				   	gstrlineUn1=g_sysmenu1800;				
					gstrlineUn2=g_sysmenu1900;				
					gstrlineUn3=g_sysmenu1110;				
					gstrlineUn4=g_sysmenu1120;				         
				   break;
				   default:break;
				}
	              break;
			case 12:
	            switch(	ScreenFirst)
				{
				   case 1:
				   	gstrlineUn1=g_sysmenu2100;				
					gstrlineUn2=g_sysmenu2200;				
					gstrlineUn3=g_sysmenu2300;				
					gstrlineUn4=g_sysmenu2400;				         
				   break;
				    case 2:
				   	gstrlineUn1=g_sysmenu2200;				
					gstrlineUn2=g_sysmenu2300;				
					gstrlineUn3=g_sysmenu2400;				
					gstrlineUn4=g_sysmenu2500;				         
				   break;
				   case 3:
				   	gstrlineUn1=g_sysmenu2300;				
					gstrlineUn2=g_sysmenu2400;				
					gstrlineUn3=g_sysmenu2500;				
					gstrlineUn4=g_sysmenu2600;				         
				   break;
				   case 4:
				   	gstrlineUn1=g_sysmenu2400;				
					gstrlineUn2=g_sysmenu2500;				
					gstrlineUn3=g_sysmenu2600;				
					gstrlineUn4=g_sysmenu2700;				         
				   break;
				   case 5:
				   	gstrlineUn1=g_sysmenu2500;				
					gstrlineUn2=g_sysmenu2600;				
					gstrlineUn3=g_sysmenu2700;				
					gstrlineUn4=g_sysmenu2800; 									         
				   break;
				   case 6:
				   	gstrlineUn1=g_sysmenu2600;				
					gstrlineUn2=g_sysmenu2700;				
					gstrlineUn3=g_sysmenu2800;				
					gstrlineUn4=g_sysmenu2900;				         
				   break;
				   case 7:
				   	gstrlineUn1=g_sysmenu2700;				
					gstrlineUn2=g_sysmenu2800;				
					gstrlineUn3=g_sysmenu2900;				
					gstrlineUn4=g_sysmenu2110;				         
				   break;

				   case 8:
				   	gstrlineUn1=g_sysmenu2800;				
					gstrlineUn2=g_sysmenu2900;				
					gstrlineUn3=g_sysmenu2110;				
					gstrlineUn4=g_sysmenu2120;				         
				   break;
				   case 9:
				   	gstrlineUn1=g_sysmenu2900;				
					gstrlineUn2=g_sysmenu2110;				
					gstrlineUn3=g_sysmenu2120;				
					gstrlineUn4=g_sysmenu2130;				         
				   break;

				   default:break;
				}
	              break;
			 case 13:
	            switch(	ScreenFirst)
				{
				   case 1:
				   	gstrlineUn1=g_sysmenu3100;				
					gstrlineUn2=g_sysmenu3200;				
					gstrlineUn3=g_sysmenu3300;				
					gstrlineUn4=g_sysmenu3400;				         
				   break;
				    case 2:
				   	gstrlineUn1=g_sysmenu3200;				
					gstrlineUn2=g_sysmenu3300;				
					gstrlineUn3=g_sysmenu3400;				
					gstrlineUn4=g_sysmenu3500;				         
				   break;
				   case 3:
				   	gstrlineUn1=g_sysmenu3300;				
					gstrlineUn2=g_sysmenu3400;				
					gstrlineUn3=g_sysmenu3500;				
					gstrlineUn4=g_sysmenu3600;				         
				   break;
				   case 4:
				   	gstrlineUn1=g_sysmenu3400;				
					gstrlineUn2=g_sysmenu3500;				
					gstrlineUn3=g_sysmenu3600;				
					gstrlineUn4=g_sysmenu3700;				         
				   break;
				   case 5:
				   	gstrlineUn1=g_sysmenu3500;				
					gstrlineUn2=g_sysmenu3600;				
					gstrlineUn3=g_sysmenu3700;				
					gstrlineUn4=g_sysmenu3800; 									         
				   break;
				   case 6:
				   	gstrlineUn1=g_sysmenu3600;				
					gstrlineUn2=g_sysmenu3700;				
					gstrlineUn3=g_sysmenu3800;				
					gstrlineUn4=g_sysmenu3900;				         
				   break;
				   case 7:
				   	gstrlineUn1=g_sysmenu3700;				
					gstrlineUn2=g_sysmenu3800;				
					gstrlineUn3=g_sysmenu3900;				
					gstrlineUn4=g_sysmenu3110;				         
				   break;
				   	 default:break;
				} 
	              break;
			 case 14:
	            switch(	ScreenFirst)
				{
				   case 1:
				   	gstrlineUn1=g_sysmenu4100;				
					gstrlineUn2=g_sysmenu4200;				
					gstrlineUn3=g_sysmenu4300;				
					gstrlineUn4=g_sysmenu4400;				         
				   break;
				    case 2:
				   	gstrlineUn1=g_sysmenu4200;				
					gstrlineUn2=g_sysmenu4300;				
					gstrlineUn3=g_sysmenu4400;				
					gstrlineUn4=g_sysmenu4500;				         
				   break;
				   case 3:
				   	gstrlineUn1=g_sysmenu4300;				
					gstrlineUn2=g_sysmenu4400;				
					gstrlineUn3=g_sysmenu4500;				
					gstrlineUn4=g_sysmenu4600;				         
				   break;
				   case 4:
				   	gstrlineUn1=g_sysmenu4400;				
					gstrlineUn2=g_sysmenu4500;				
					gstrlineUn3=g_sysmenu4600;				
					gstrlineUn4=g_sysmenu4700;				         
				   break;
				   case 5:
				   	gstrlineUn1=g_sysmenu4500;				
					gstrlineUn2=g_sysmenu4600;				
					gstrlineUn3=g_sysmenu4700;				
					gstrlineUn4=g_sysmenu4800; 									         
				   break;
				   case 6:
				   	gstrlineUn1=g_sysmenu4600;				
					gstrlineUn2=g_sysmenu4700;				
					gstrlineUn3=g_sysmenu4800;				
					gstrlineUn4=g_sysmenu4900;				         
				   break;
				   case 7:
				   	gstrlineUn1=g_sysmenu4700;				
					gstrlineUn2=g_sysmenu4800;				
					gstrlineUn3=g_sysmenu4900;				
					gstrlineUn4=g_sysmenu4110;				         
				   break;
//				   case 8:
//				   	gstrlineUn1=g_sysmenu4800;				
//					gstrlineUn2=g_sysmenu4900;				
//					gstrlineUn3=g_sysmenu4110;				
//					gstrlineUn4=g_sysmenu4120;				         
//				   break;
				   default:break;
				}
				break;
			 case 22:
	            switch(	ScreenFirst)
				{
				   case 1:
				   	gstrlineUn1=g_sysmenu2201;				
					gstrlineUn2=g_sysmenu2202;				
					gstrlineUn3=g_sysmenu2203;				
					gstrlineUn4=g_sysmenu2204;				         
				   break;
				    case 2:
				   	gstrlineUn1=g_sysmenu2202;				
					gstrlineUn2=g_sysmenu2203;				
					gstrlineUn3=g_sysmenu2204;				
					gstrlineUn4=g_sysmenu2205;				         
				   break;
				   case 3:
				   	gstrlineUn1=g_sysmenu2203;				
					gstrlineUn2=g_sysmenu2204;				
					gstrlineUn3=g_sysmenu2205;				
					gstrlineUn4=g_sysmenu2206;				         
				   break;
				   case 4:
				   	gstrlineUn1=g_sysmenu2204;				
					gstrlineUn2=g_sysmenu2205;				
					gstrlineUn3=g_sysmenu2206;				
					gstrlineUn4=g_sysmenu2207;				         
				   break;
				   case 5:
				   	gstrlineUn1=g_sysmenu2205;				
					gstrlineUn2=g_sysmenu2206;				
					gstrlineUn3=g_sysmenu2207;				
					gstrlineUn4=g_sysmenu2208; 									         
				   break;
				   case 6:
				   	gstrlineUn1=g_sysmenu2206;				
					gstrlineUn2=g_sysmenu2207;				
					gstrlineUn3=g_sysmenu2208;				
					gstrlineUn4=g_sysmenu2209;				         
				   break;
				   case 7:
				   	gstrlineUn1=g_sysmenu2207;				
					gstrlineUn2=g_sysmenu2208;				
					gstrlineUn3=g_sysmenu2209;				
					gstrlineUn4=g_sysmenu22010;				         
				   break; 
				  case 8:
				   	gstrlineUn1=g_sysmenu2208;				
					gstrlineUn2=g_sysmenu2209;				
					gstrlineUn3=g_sysmenu22010;				
					gstrlineUn4=g_sysmenu22011;				         
				   break;   				  
				   default:break;
				}
				break;

			 case 23:
	            switch(	ScreenFirst)
				{
				   case 1:
				   	gstrlineUn1=g_sysmenu2301;				
					gstrlineUn2=g_sysmenu2302;				
					gstrlineUn3=g_sysmenu2303;				
					gstrlineUn4=g_sysmenu2304;				         
				   break;
				    case 2:
				   	gstrlineUn1=g_sysmenu2302;				
					gstrlineUn2=g_sysmenu2303;				
					gstrlineUn3=g_sysmenu2304;				
					gstrlineUn4=g_sysmenu2305;				         
				   break;
				   case 3:
				   	gstrlineUn1=g_sysmenu2303;				
					gstrlineUn2=g_sysmenu2304;				
					gstrlineUn3=g_sysmenu2305;				
					gstrlineUn4=g_sysmenu2306;				         
				   break;
				   case 4:
				   	gstrlineUn1=g_sysmenu2304;				
					gstrlineUn2=g_sysmenu2305;				
					gstrlineUn3=g_sysmenu2306;				
					gstrlineUn4=g_sysmenu2307;				         
				   break;
				   case 5:
				   	gstrlineUn1=g_sysmenu2305;				
					gstrlineUn2=g_sysmenu2306;				
					gstrlineUn3=g_sysmenu2307;				
					gstrlineUn4=g_sysmenu2308; 									         
				   break;
				    				  
				   default:break;
				}
	              break;

	    default: break;
	}
}
//************************************************************************************************************************



//************************************************************************************************************************
//��ȡӢ�Ĳ˵�Ҫ��ʾ�Ķ���
void GetMenuScreenEn(uint8 menunum,uint8 ScreenFirst)											   
{
   switch( menunum )
   {
       case 11:
	            switch(	ScreenFirst)
				{
				   case 1:
				   	gstrlineEn1=g_sysmenu1100;				
					gstrlineEn2=g_sysmenu1200;				
					gstrlineEn3=g_sysmenu1300;				
					gstrlineEn4=g_sysmenu1400;
					gstrlineEn5=g_sysmenu1500;				
					gstrlineEn6=g_sysmenu1600;				
					gstrlineEn7=g_sysmenu1700;				
					gstrlineEn8=g_sysmenu1800;				         
				   break;
				    case 2:
				   	gstrlineEn1=g_sysmenu1200;				
					gstrlineEn2=g_sysmenu1300;				
					gstrlineEn3=g_sysmenu1400;				
					gstrlineEn4=g_sysmenu1500;
					gstrlineEn5=g_sysmenu1600;				
					gstrlineEn6=g_sysmenu1700;				
					gstrlineEn7=g_sysmenu1800;				
					gstrlineEn8=g_sysmenu1900;				         
				   break;
				   case 3:
				   	gstrlineEn1=g_sysmenu1300;				
					gstrlineEn2=g_sysmenu1400;				
					gstrlineEn3=g_sysmenu1500;				
					gstrlineEn4=g_sysmenu1600;
					gstrlineEn5=g_sysmenu1700;				
					gstrlineEn6=g_sysmenu1800;				
					gstrlineEn7=g_sysmenu1900;				
					gstrlineEn8=g_sysmenu1110;		         
				   break;
				   case 4:
				   	gstrlineEn1=g_sysmenu1400;				
					gstrlineEn2=g_sysmenu1500;				
					gstrlineEn3=g_sysmenu1600;				
					gstrlineEn4=g_sysmenu1700;
					gstrlineEn5=g_sysmenu1800;				
					gstrlineEn6=g_sysmenu1900;				
					gstrlineEn7=g_sysmenu1110;				
					gstrlineEn8=g_sysmenu1120;			         
				   break;
				   default:break;
				}
	              break;
		       case 12:
	            switch(	ScreenFirst)
				{
				   case 1:
				   	gstrlineEn1=g_sysmenu2100;				
					gstrlineEn2=g_sysmenu2200;				
					gstrlineEn3=g_sysmenu2300;				
					gstrlineEn4=g_sysmenu2400;
					gstrlineEn5=g_sysmenu2500;				
					gstrlineEn6=g_sysmenu2600;				
					gstrlineEn7=g_sysmenu2700;				
					gstrlineEn8=g_sysmenu2800;				         
				   break;
				    case 2:
				   	gstrlineEn1=g_sysmenu2200;				
					gstrlineEn2=g_sysmenu2300;				
					gstrlineEn3=g_sysmenu2400;				
					gstrlineEn4=g_sysmenu2500;
					gstrlineEn5=g_sysmenu2600;				
					gstrlineEn6=g_sysmenu2700;				
					gstrlineEn7=g_sysmenu2800;				
					gstrlineEn8=g_sysmenu2900;				         
				   break;
				   case 3:
				   	gstrlineEn1=g_sysmenu2300;				
					gstrlineEn2=g_sysmenu2400;				
					gstrlineEn3=g_sysmenu2500;				
					gstrlineEn4=g_sysmenu2600;
					gstrlineEn5=g_sysmenu2700;				
					gstrlineEn6=g_sysmenu2800;				
					gstrlineEn7=g_sysmenu2900;				
					gstrlineEn8=g_sysmenu2110;		         
				   break;

				    case 4:
				   	gstrlineEn1=g_sysmenu2400;				
					gstrlineEn2=g_sysmenu2500;				
					gstrlineEn3=g_sysmenu2600;				
					gstrlineEn4=g_sysmenu2700;
					gstrlineEn5=g_sysmenu2800;				
					gstrlineEn6=g_sysmenu2900;				
					gstrlineEn7=g_sysmenu2110;				
					gstrlineEn8=g_sysmenu2120;		         
				   break;

				   case 5:
				   	gstrlineEn1=g_sysmenu2500;				
					gstrlineEn2=g_sysmenu2600;				
					gstrlineEn3=g_sysmenu2700;				
					gstrlineEn4=g_sysmenu2800;
					gstrlineEn5=g_sysmenu2900;				
					gstrlineEn6=g_sysmenu2110;				
					gstrlineEn7=g_sysmenu2120;				
					gstrlineEn8=g_sysmenu2130;		         
				   break;
			
				   default:break;
				}
	              break;
			   case 13:
	            switch(	ScreenFirst)
				{
				   case 1:
				   	gstrlineEn1=g_sysmenu3100;				
					gstrlineEn2=g_sysmenu3200;				
					gstrlineEn3=g_sysmenu3300;				
					gstrlineEn4=g_sysmenu3400;
					gstrlineEn5=g_sysmenu3500;				
					gstrlineEn6=g_sysmenu3600;				
					gstrlineEn7=g_sysmenu3700;				
					gstrlineEn8=g_sysmenu3800;				         
				   break;
				    case 2:
				   	gstrlineEn1=g_sysmenu3200;				
					gstrlineEn2=g_sysmenu3300;				
					gstrlineEn3=g_sysmenu3400;				
					gstrlineEn4=g_sysmenu3500;
					gstrlineEn5=g_sysmenu3600;				
					gstrlineEn6=g_sysmenu3700;				
					gstrlineEn7=g_sysmenu3800;				
					gstrlineEn8=g_sysmenu3900;				         
				   break;
				   case 3:
				   	gstrlineEn1=g_sysmenu3300;				
					gstrlineEn2=g_sysmenu3400;				
					gstrlineEn3=g_sysmenu3500;				
					gstrlineEn4=g_sysmenu3600;
					gstrlineEn5=g_sysmenu3700;				
					gstrlineEn6=g_sysmenu3800;				
					gstrlineEn7=g_sysmenu3900;				
					gstrlineEn8=g_sysmenu3110;		         
				   break;
				  
				   default:break;
				}
				break;
		       case 14:
	            switch(	ScreenFirst)
				{
				   case 1:
				   	gstrlineEn1=g_sysmenu4100;				
					gstrlineEn2=g_sysmenu4200;				
					gstrlineEn3=g_sysmenu4300;				
					gstrlineEn4=g_sysmenu4400;
					gstrlineEn5=g_sysmenu4500;				
					gstrlineEn6=g_sysmenu4600;				
					gstrlineEn7=g_sysmenu4700;				
					gstrlineEn8=g_sysmenu4800;				         
				   break;
				    case 2:
				   	gstrlineEn1=g_sysmenu4200;				
					gstrlineEn2=g_sysmenu4300;				
					gstrlineEn3=g_sysmenu4400;				
					gstrlineEn4=g_sysmenu4500;
					gstrlineEn5=g_sysmenu4600;				
					gstrlineEn6=g_sysmenu4700;				
					gstrlineEn7=g_sysmenu4800;				
					gstrlineEn8=g_sysmenu4900;				         
				   break;
				   case 3:
				   	gstrlineEn1=g_sysmenu4300;				
					gstrlineEn2=g_sysmenu4400;				
					gstrlineEn3=g_sysmenu4500;				
					gstrlineEn4=g_sysmenu4600;
					gstrlineEn5=g_sysmenu4700;				
					gstrlineEn6=g_sysmenu4800;				
					gstrlineEn7=g_sysmenu4900;				
					gstrlineEn8=g_sysmenu4110;		         
				   break;
//				   case 4:
//				   	gstrlineEn1=g_sysmenu4400;				
//					gstrlineEn2=g_sysmenu4500;				
//					gstrlineEn3=g_sysmenu4600;				
//					gstrlineEn4=g_sysmenu4700;
//					gstrlineEn5=g_sysmenu4800;				
//					gstrlineEn6=g_sysmenu4900;				
//					gstrlineEn7=g_sysmenu4110;				
//					gstrlineEn8=g_sysmenu4120;			         
//				   break;
				   default:break;
				}
				break;
	          case 22:
	            switch(	ScreenFirst)
				{
				   case 1:
				   	gstrlineEn1=g_sysmenu2201;				
					gstrlineEn2=g_sysmenu2202;				
					gstrlineEn3=g_sysmenu2203;				
					gstrlineEn4=g_sysmenu2204;
					gstrlineEn5=g_sysmenu2205;				
					gstrlineEn6=g_sysmenu2206;				
					gstrlineEn7=g_sysmenu2207;				
					gstrlineEn8=g_sysmenu2208;				         
				   break;
				    case 2:
				   	gstrlineEn1=g_sysmenu2202;				
					gstrlineEn2=g_sysmenu2203;				
					gstrlineEn3=g_sysmenu2204;				
					gstrlineEn4=g_sysmenu2205;
					gstrlineEn5=g_sysmenu2206;				
					gstrlineEn6=g_sysmenu2207;				
					gstrlineEn7=g_sysmenu2208;				
					gstrlineEn8=g_sysmenu2209;				         
				   break;
				   case 3:
				   	gstrlineEn1=g_sysmenu2203;				
					gstrlineEn2=g_sysmenu2204;				
					gstrlineEn3=g_sysmenu2205;				
					gstrlineEn4=g_sysmenu2206;
					gstrlineEn5=g_sysmenu2207;				
					gstrlineEn6=g_sysmenu2208;				
					gstrlineEn7=g_sysmenu2209;				
					gstrlineEn8=g_sysmenu22010;		         
				   break;
				   case 4:
				   	gstrlineEn1=g_sysmenu2204;				
					gstrlineEn2=g_sysmenu2205;				
					gstrlineEn3=g_sysmenu2206;				
					gstrlineEn4=g_sysmenu2207;
					gstrlineEn5=g_sysmenu2208;				
					gstrlineEn6=g_sysmenu2209;				
					gstrlineEn7=g_sysmenu22010;				
					gstrlineEn8=g_sysmenu22011;			         
				   break;
				   default:break;
				}
	              break;
			case 23:
	            switch(	ScreenFirst)
				{
				   case 1:
				   	gstrlineEn1=g_sysmenu2301;				
					gstrlineEn2=g_sysmenu2302;				
					gstrlineEn3=g_sysmenu2303;				
					gstrlineEn4=g_sysmenu2304;
					gstrlineEn5=g_sysmenu2305;				
					gstrlineEn6=g_sysmenu2306;				
					gstrlineEn7=g_sysmenu2307;				
					gstrlineEn8=g_sysmenu2308;				         
				   break;
			
				   default:break;
				}
				break;
	          

	    default: break;
	}
}
//************************************************************************************************************************



//************************************************************************************************************************
//��ʾ����
void FMenuShowSet()
{
   uint8 Nation[8],Nation_world[17],City_world[17],Lon[3],Lat[3],Zon[2];
   uint16 *Alt;
   FSelMenuLanguage();

	    	switch(g_nsysstatus)
	     	{
			  case SYS_MAINSHOW:	 //��Զ������ʾ��
			    	FSysMainShowSet();
					g_mShowMenurowEn=10;
					g_mShowLangauge=ENGLISH;	
					break;
			  case SYS_NOTELSCOPE:	   //û����Զ��
			       	gstrlineEn2=g_sysnotel1;
					gstrlineEn4=g_sysnotel2;
					gstrlineEn6=g_sysnotel3;

    			   FSelShowLanguage();
			        break;

				case SYS_F_SELFNUM :   //����F½��Ŀ������Ŀ�깦�� 
				   gstrlineEn1="F1";
				   gstrlineEn2="F2";
				   gstrlineEn3="F3";
				   gstrlineEn4="F4";
				   gstrlineEn5="F5";
				   gstrlineEn6="F6";
				   gstrlineEn7="F7";
				   gstrlineEn8="F8";
				   gstrlineEn9="F9";
				   //��ջ�½��Ŀ����ʾ����
				   switch(g_mSkyLand)
				  	{
					  case 0:
						gstrlineEn10="Select Sky Target No ";
						break;
					  case 1: 
						gstrlineEn10="Select Land Target No";
						break;
					 default:		
						break;
					}
				 break;

				 case SYS_F_SELFNUM_SEL:

				    switch(g_mSkyLand)
				  	{
					  case 0:
						  GetCustomStar(g_mFnum,&CustomStar);
						  //LandTarget.flag=0;
						break;
					  case 1:  
						 GetCustomLandTarget(g_mFnum,&LandTarget);
						 //CustomStar.flag=0;
						break;
					 default:		
						break;
					}



				    if(((LandTarget.flag!=1)&&(g_mSkyLand==1))||((CustomStar.flag!=1)&&(g_mSkyLand==0)))
					{
					 
					    gstrlineEn1="                      ";
						gstrlineEn2="Sorry                 ";
						gstrlineEn3="                      ";
				    	if(g_mSkyLand==0)
						{
						   sprintf(gstrtemp4,"Your Sky F%d is Blank  ",g_mFnum);
						 }
						 if(g_mSkyLand==1)
						{
						   sprintf(gstrtemp4,"Your Land F%d is Blank  ",g_mFnum);
						 }

						gstrlineEn4=gstrtemp4;
						gstrlineEn5="                      ";
						gstrlineEn6="Please Input Data    ";
						gstrlineEn7="                      ";
						gstrlineEn8="                      ";
					}

					else
					{			
					   if(g_mSkyLand==0)
					   {
					        sprintf(gstrtemp1,"My Sky Target %d   ",g_mFnum);
						    gstrlineEn1=gstrtemp1; 
							 
							gstrlineEn2="                      ";
							gstrlineEn3=CustomStar.NameEn;
							gstrlineEn4="                      ";
					  	    gLocation.mLongitude=g_mGoto.m_nLongitude;
						    gLocation.mAtitude=g_mGoto.m_nAtitude;
							gStarRAD.mRightAscension=CustomStar.Ra;
							gStarRAD.mDeclination=CustomStar.Dec;
							g_mObjRa1=CustomStar.Ra;
							g_mObjDec1=CustomStar.Dec;

							FCalStarAEPos(gLocation,gStarRAD,g_mGoto.m_nSysTimeType,g_mGoto.m_nNutation,&gStarAZ);

						  sprintf(gstrtemp5,"OBJ    Azi:%03d %02d %02d                ",(int)gStarAZ.mANzimuth,(int)((gStarAZ.mANzimuth-(int)gStarAZ.mANzimuth)*60),(int)(gStarAZ.mANzimuth*3600)%60);				   
						  
						   if(gStarAZ.mAtitude>=0)
						   {
						     sprintf(gstrtemp6,"Alt:+%02d %02d %02d               ",abs((int)gStarAZ.mAtitude),abs((int)((gStarAZ.mAtitude-(int)gStarAZ.mAtitude)*60)),abs((int)(gStarAZ.mAtitude*3600)%60));			
		          			}
							else
							{
							 sprintf(gstrtemp6,"Alt:-%02d %02d %02d               ",abs((int)gStarAZ.mAtitude),abs((int)((gStarAZ.mAtitude-(int)gStarAZ.mAtitude)*60)),abs((int)(gStarAZ.mAtitude*3600)%60));	
		          			 }
							
		
						   if((int)gStarAZ.mANzimuth <100)
						   {
						     gstrtemp5[11]=' ';
						   }
						   if((int)gStarAZ.mANzimuth <10)
						   {
						     gstrtemp5[12]=' ';
						   }
		
						   if((int)((gStarAZ.mANzimuth-(int)gStarAZ.mANzimuth)*60)<10)
						   {
						     gstrtemp5[15]=' ';
						   }
		
						   if(((int)(gStarAZ.mANzimuth*3600)%60)<10)
						   {
						     gstrtemp5[18]=' ';
						   }
		
		
		
						    if(abs((int)gStarAZ.mAtitude)<10)
						   {
						     gstrtemp6[5]=' ';
						   }
		
						   if(abs((int)((gStarAZ.mAtitude-(int)gStarAZ.mAtitude)*60))<10)
						   {
						     gstrtemp6[8]=' ';
						   }
						   if(abs(((int)(gStarAZ.mAtitude*3600)%60))<10)
						   {
						      gstrtemp6[11]=' ';
						   }
		
							gstrlineEn5=gstrtemp5;
							gstrlineEn6=gstrtemp6;
//		
//						    gstrlineCn5=gstrtemp5;
//							gstrlineCn6=gstrtemp6;
//		
		
					       sprintf(gstrtemp7,"R.a: %02dh%02dm%02ds         ",(int)g_mObjRa1,(int)((g_mObjRa1-(int)g_mObjRa1)*60),(int)(g_mObjRa1*3600)%60);	
					
						   if((int)g_mObjRa1<10)
						   {
						     gstrtemp7[5]=' ';
						   }
		
						   if((int)((g_mObjRa1-(int)g_mObjRa1)*60)<10)
						   {
						     gstrtemp7[8]=' ';
						   }
		
						   if(((int)(g_mObjRa1*3600)%60)<10)
						   {
						     gstrtemp7[11]=' ';
						   }			
							gstrlineEn7=gstrtemp7;
//							gstrlineCn7=gstrtemp7;
		
							 if(g_mObjDec1>=0)
							 {
					            sprintf(gstrtemp8,"Dec:+%02d %02d %02d      ",abs((int)g_mObjDec1),abs((int)((g_mObjDec1-(int)g_mObjDec1)*60)),abs((int)(g_mObjDec1*3600)%60));	
							}
							else
							{
							  sprintf(gstrtemp8,"Dec:-%02d %02d %02d        ",abs((int)g_mObjDec1),abs((int)((g_mObjDec1-(int)g_mObjDec1)*60)),abs((int)(g_mObjDec1*3600)%60));	
							}
		
						   	if(abs((int)g_mObjDec1)<10)
						   {
						     gstrtemp8[5]=' ';
						   }
		
						   if(abs((int)((g_mObjDec1-(int)g_mObjDec1)*60))<10)
						   {
						     gstrtemp8[8]=' ';
						   }
						   if(abs(((int)(g_mObjDec1*3600)%60))<10)
						   {
						      gstrtemp8[11]=' ';
						   }
						    
							gstrlineEn8=gstrtemp8;
//							gstrlineCn8=gstrtemp8;
					}				
	
					   else
					   {
						      sprintf(gstrtemp1,"My Land Target %d",g_mFnum);
						      gstrlineEn1=gstrtemp1;  
							  gstrlineEn2="                      ";
							  gstrlineEn3=LandTarget.NameEn;
							  gstrlineEn4="                      ";
							  gStarAZ.mANzimuth=LandTarget.Azi;
							  gStarAZ.mAtitude=LandTarget.Alt;
	
							  sprintf(gstrtemp5,"OBJ    Azi:%03d %02d %02d                ",(int)gStarAZ.mANzimuth,(int)((gStarAZ.mANzimuth-(int)gStarAZ.mANzimuth)*60),(int)(gStarAZ.mANzimuth*3600)%60);				   
						  
						   if(gStarAZ.mAtitude>=0)
						   {
						     sprintf(gstrtemp6,"Alt:+%02d %02d %02d               ",abs((int)gStarAZ.mAtitude),abs((int)((gStarAZ.mAtitude-(int)gStarAZ.mAtitude)*60)),abs((int)(gStarAZ.mAtitude*3600)%60));			
		          			}
							else
							{
							 sprintf(gstrtemp6,"Alt:-%02d %02d %02d               ",abs((int)gStarAZ.mAtitude),abs((int)((gStarAZ.mAtitude-(int)gStarAZ.mAtitude)*60)),abs((int)(gStarAZ.mAtitude*3600)%60));	
		          			 }
							
		
						   if((int)gStarAZ.mANzimuth <100)
						   {
						     gstrtemp5[11]=' ';
						   }
						   if((int)gStarAZ.mANzimuth <10)
						   {
						     gstrtemp5[12]=' ';
						   }
		
						   if((int)((gStarAZ.mANzimuth-(int)gStarAZ.mANzimuth)*60)<10)
						   {
						     gstrtemp5[15]=' ';
						   }
		
						   if(((int)(gStarAZ.mANzimuth*3600)%60)<10)
						   {
						     gstrtemp5[18]=' ';
						   }
		
		
		
						    if(abs((int)gStarAZ.mAtitude)<10)
						   {
						     gstrtemp6[5]=' ';
						   }
		
						   if(abs((int)((gStarAZ.mAtitude-(int)gStarAZ.mAtitude)*60))<10)
						   {
						     gstrtemp6[8]=' ';
						   }
						   if(abs(((int)(gStarAZ.mAtitude*3600)%60))<10)
						   {
						      gstrtemp6[11]=' ';
						   }
		
							gstrlineEn5=gstrtemp5;
							gstrlineEn6=gstrtemp6;
	
						g_mTelAzi1=g_mTelAzi;
				        g_mTelAlt1=g_mTelAlt;
	
	
				        sprintf(gstrtemp7,"OTA    Azi:%03d %02d %02d                ",(int)g_mTelAzi1,(int)((g_mTelAzi1-(int)g_mTelAzi1)*60),(int)(g_mTelAzi1*3600)%60);				   
					  
					   if(g_mTelAlt1>=0)
					   {
					     sprintf(gstrtemp8,"Alt:+%02d %02d %02d               ",abs((int)g_mTelAlt1),abs((int)((g_mTelAlt1-(int)g_mTelAlt1)*60)),abs((int)(g_mTelAlt1*3600)%60));			
	          			}
						else
						{
						 sprintf(gstrtemp8,"Alt:-%02d %02d %02d               ",abs((int)g_mTelAlt1),abs((int)((g_mTelAlt1-(int)g_mTelAlt1)*60)),abs((int)(g_mTelAlt1*3600)%60));	
	          			 }
						
	
					   if((int)g_mTelAzi1 <100)
					   {
					     gstrtemp7[11]=' ';
					   }
					   if((int)g_mTelAzi1 <10)
					   {
					     gstrtemp7[12]=' ';
					   }
	
					   if((int)((g_mTelAzi1-(int)g_mTelAzi1)*60)<10)
					   {
					     gstrtemp7[15]=' ';
					   }
	
					   if(((int)(g_mTelAzi1*3600)%60)<10)
					   {
					     gstrtemp7[18]=' ';
					   }
	
	
	
					    if(abs((int)g_mTelAlt1)<10)
					   {
					     gstrtemp8[5]=' ';
					   }
	
					   if(abs((int)((g_mTelAlt1-(int)g_mTelAlt1)*60))<10)
					   {
					     gstrtemp8[8]=' ';
					   }
					   if(abs(((int)(g_mTelAlt1*3600)%60))<10)
					   {
					      gstrtemp8[11]=' ';
					   }
	
						gstrlineEn7=gstrtemp7;
						gstrlineEn8=gstrtemp8;

			
	
				 }
	
			   }
	
					 
	
	
					  

					g_mShowMenurowEn=0;
//					g_mShowMenurowCn=0;
					g_mShowLangauge=ENGLISH;	
		     	break; 
			 
				 break;


		      case SYS_MENUSHOW:	 //�չ۲���ǵ���ʾ
	           g_RecentNum=GetRecentTarget(g_RecentType,g_Targetnum,g_rdata);
			   gstrlineEn1="                      ";
			   gstrlineEn2="                      ";
			   gstrlineEn3="                      ";
			   gstrlineEn4="                      ";
			   gstrlineEn5="                      ";
			   gstrlineEn6="                      ";
			   gstrlineEn7="                      ";
			   gstrlineEn8="                      ";  

			   gstrlineEn9="   ";
			   gstrlineEn10="   ";
			   gstrlineEn11="   ";
			   gstrlineEn12="   ";
			   gstrlineEn13="   ";
			   gstrlineEn14="   ";
			   gstrlineEn15="   ";
			   gstrlineEn16="   ";  





				switch(g_RecentNum)
				{
				    case 0:
					    gstrlineEn1="                      ";
						gstrlineEn2="                      ";  
						gstrlineEn3="Sorry                 ";
						gstrlineEn4="                      ";  
						gstrlineEn5="No Recent Target     ";
						gstrlineEn6="                      ";  
						gstrlineEn7="                      ";
						gstrlineEn8="                      ";
					 break;
					 case 8:
					       gstrlineEn16="8: ";
						  g_mTargetType=g_RecentType[7];
						  g_mTargetnum=g_Targetnum[7];

						   GetRectntTarget(g_mTargetType,g_mTargetnum);
						    for(g_mTempstrnum=0;g_mTempstrnum<21;g_mTempstrnum++)
						   {
						      gstrtemp8[g_mTempstrnum]=gstrtemp18[g_mTempstrnum];
							}
						    gstrlineEn8=gstrtemp8;
						  // break;

					  case 7:
					      gstrlineEn15="7: ";
					      g_mTargetType=g_RecentType[6];
						  g_mTargetnum=g_Targetnum[6];

						   GetRectntTarget(g_mTargetType,g_mTargetnum);
						   for(g_mTempstrnum=0;g_mTempstrnum<21;g_mTempstrnum++)
						   {
						      gstrtemp7[g_mTempstrnum]=gstrtemp18[g_mTempstrnum];
							}
						   gstrlineEn7=gstrtemp7;
						    //break;

					 case 6:
							 gstrlineEn14="6: ";
							 g_mTargetType=g_RecentType[5];
						  g_mTargetnum=g_Targetnum[5];

						   GetRectntTarget(g_mTargetType,g_mTargetnum);
						   gstrlineEn6=gstrlineEn18;
						   for(g_mTempstrnum=0;g_mTempstrnum<21;g_mTempstrnum++)
						   {
						      gstrtemp6[g_mTempstrnum]=gstrtemp18[g_mTempstrnum];
							}
						    gstrlineEn6=gstrtemp6;

						   
					 case 5:
							 gstrlineEn13="5: ";
							  g_mTargetType=g_RecentType[4];
						  g_mTargetnum=g_Targetnum[4];

						   GetRectntTarget(g_mTargetType,g_mTargetnum);
						     for(g_mTempstrnum=0;g_mTempstrnum<21;g_mTempstrnum++)
						   {
						      gstrtemp5[g_mTempstrnum]=gstrtemp18[g_mTempstrnum];
							}
						    gstrlineEn5=gstrtemp5;
						   // break;

					 case 4:
					 gstrlineEn12="4: ";
					 g_mTargetType=g_RecentType[3];
						  g_mTargetnum=g_Targetnum[3];

						   GetRectntTarget(g_mTargetType,g_mTargetnum);
						     for(g_mTempstrnum=0;g_mTempstrnum<21;g_mTempstrnum++)
						   {
						      gstrtemp4[g_mTempstrnum]=gstrtemp18[g_mTempstrnum];
							}
						    gstrlineEn4=gstrtemp4;
						   // break;

					 case 3:
					 gstrlineEn11="3: ";
					 g_mTargetType=g_RecentType[2];
						  g_mTargetnum=g_Targetnum[2];

						   GetRectntTarget(g_mTargetType,g_mTargetnum);
						     for(g_mTempstrnum=0;g_mTempstrnum<21;g_mTempstrnum++)
						   {
						      gstrtemp3[g_mTempstrnum]=gstrtemp18[g_mTempstrnum];
							}
						    gstrlineEn3=gstrtemp3;
						   // break;

					 case 2:
					 gstrlineEn10="2: ";
					 g_mTargetType=g_RecentType[1];
						  g_mTargetnum=g_Targetnum[1];

						   GetRectntTarget(g_mTargetType,g_mTargetnum);
						     for(g_mTempstrnum=0;g_mTempstrnum<21;g_mTempstrnum++)
						   {
						      gstrtemp2[g_mTempstrnum]=gstrtemp18[g_mTempstrnum];
							}
						    gstrlineEn2=gstrtemp2;
						   // break;

					 case 1:
					 gstrlineEn9="1: ";
					      g_mTargetType=g_RecentType[0];
						  g_mTargetnum=g_Targetnum[0];
						   GetRectntTarget(g_mTargetType,g_mTargetnum);
						   gstrlineEn1=gstrlineEn18;
						     for(g_mTempstrnum=0;g_mTempstrnum<21;g_mTempstrnum++)
						   {
						      gstrtemp1[g_mTempstrnum]=gstrtemp18[g_mTempstrnum];
							}
						    gstrlineEn1=gstrtemp1;

					break;		 		 
	
				}
				break;

			
				//��Զ��һ���˵���ʾ����
		    	case SYS_MAINMENU1:
					gstrlineEn1=g_sysmenu1000;
					gstrlineEn2="";
					gstrlineEn3=g_sysmenu2000;
					gstrlineEn4="";
					gstrlineEn5=g_sysmenu3000;
					gstrlineEn6="";
					gstrlineEn7=g_sysmenu4000;
					gstrlineEn8="";
					g_mShowMenurowEn=1;

//					gstrlineCn1=g_sysmenu1000;				
//					gstrlineCn2=g_sysmenu2000;				
//					gstrlineCn3=g_sysmenu3000;				
//					gstrlineCn4=g_sysmenu4000;				
//					g_mShowMenurowCn=1;


				    gstrlineUn1=g_sysmenu1000;
					gstrlineUn2=g_sysmenu2000;
					gstrlineUn3=g_sysmenu3000;
					gstrlineUn4=g_sysmenu4000;
				
					g_mShowMenurowUn=1;


					FSelShowLanguage();
			    	break;
				case SYS_MAINMENU2:
					gstrlineEn1=g_sysmenu1000;
					gstrlineEn2="";
					gstrlineEn3=g_sysmenu2000;
					gstrlineEn4="";
					gstrlineEn5=g_sysmenu3000;
					gstrlineEn6="";
					gstrlineEn7=g_sysmenu4000;
					gstrlineEn8="";
					g_mShowMenurowEn=3;

//					gstrlineCn1=g_sysmenu1000;				
//					gstrlineCn2=g_sysmenu2000;				
//					gstrlineCn3=g_sysmenu3000;				
//					gstrlineCn4=g_sysmenu4000;				
//					g_mShowMenurowCn=2;

					gstrlineUn1=g_sysmenu1000;
					gstrlineUn2=g_sysmenu2000;
					gstrlineUn3=g_sysmenu3000;
					gstrlineUn4=g_sysmenu4000;
				
					g_mShowMenurowUn=2;

					FSelShowLanguage();
			    	break;
			 	case SYS_MAINMENU3:
					gstrlineEn1=g_sysmenu1000;
					gstrlineEn2="";
					gstrlineEn3=g_sysmenu2000;
					gstrlineEn4="";
					gstrlineEn5=g_sysmenu3000;
					gstrlineEn6="";
					gstrlineEn7=g_sysmenu4000;
					gstrlineEn8="";
					g_mShowMenurowEn=5;

//					gstrlineCn1=g_sysmenu1000;				
//					gstrlineCn2=g_sysmenu2000;				
//					gstrlineCn3=g_sysmenu3000;				
//					gstrlineCn4=g_sysmenu4000;				
//					g_mShowMenurowCn=3;

					gstrlineUn1=g_sysmenu1000;
					gstrlineUn2=g_sysmenu2000;
					gstrlineUn3=g_sysmenu3000;
					gstrlineUn4=g_sysmenu4000;
				
					g_mShowMenurowUn=3;

					FSelShowLanguage();
		    		break;
			 	case SYS_MAINMENU4:
					gstrlineEn1=g_sysmenu1000;
					gstrlineEn2="";
					gstrlineEn3=g_sysmenu2000;
					gstrlineEn4="";
					gstrlineEn5=g_sysmenu3000;
					gstrlineEn6="";
					gstrlineEn7=g_sysmenu4000;
					gstrlineEn8="";
					g_mShowMenurowEn=7;

//					gstrlineCn1=g_sysmenu1000;				
//					gstrlineCn2=g_sysmenu2000;				
//					gstrlineCn3=g_sysmenu3000;				
//					gstrlineCn4=g_sysmenu4000;				
//					g_mShowMenurowCn=4;

					gstrlineUn1=g_sysmenu1000;
					gstrlineUn2=g_sysmenu2000;
					gstrlineUn3=g_sysmenu3000;
					gstrlineUn4=g_sysmenu4000;
				
					g_mShowMenurowUn=4;

					FSelShowLanguage();
			    	break;
				//��Զ�������˵�
				//��Զ��У���˲˵���ʾ����
				case SYS_SUB1MENU1:	
			 	case SYS_SUB1MENU2:
			 	case SYS_SUB1MENU3:
		    	case SYS_SUB1MENU4:	 
				case SYS_SUB1MENU5:
				case SYS_SUB1MENU6:
				case SYS_SUB1MENU7:
		        	GetMenuScreenEn(11,g_mShowMenuFtEn11);
					g_mShowMenurowEn=g_mShowMenurowEn11; 
//					GetMenuScreenCn(11,g_mShowMenuFtCn11);				
//					g_mShowMenurowCn=g_mShowMenurowCn11; 				   	
					GetMenuScreenUn(11,g_mShowMenuFtUn11);				
					g_mShowMenurowUn=g_mShowMenurowUn11;

					FSelShowLanguage();
			    	break;
		  		//Ŀ�굼���Ӳ˵���ʾ����
		  		case SYS_SUB2MENU1:
				case SYS_SUB2MENU2:
			 	case SYS_SUB2MENU3:
			 	case SYS_SUB2MENU4:
		    	case SYS_SUB2MENU5:
				case SYS_SUB2MENU6:
				case SYS_SUB2MENU7:
				case SYS_SUB2MENU8:
				case SYS_SUB2MENU9:
				case SYS_SUB2MENU11:
				case SYS_SUB2MENU12:
				case SYS_SUB2MENU13:
					GetMenuScreenEn(12,g_mShowMenuFtEn12);
					g_mShowMenurowEn=g_mShowMenurowEn12; 
//					GetMenuScreenCn(12,g_mShowMenuFtCn12);				
//					g_mShowMenurowCn=g_mShowMenurowCn12;
					GetMenuScreenUn(12,g_mShowMenuFtUn12);				
					g_mShowMenurowUn=g_mShowMenurowUn12;

					FSelShowLanguage();
					break;
				//���������Ӳ˵���ʾ����
		  		case SYS_SUB3MENU1:
				case SYS_SUB3MENU2:
				case SYS_SUB3MENU3:
			 	case SYS_SUB3MENU4:
		    	case SYS_SUB3MENU5:
				case SYS_SUB3MENU6:
				case SYS_SUB3MENU7:
				case SYS_SUB3MENU8:
				case SYS_SUB3MENU9:
				    GetMenuScreenEn(13,g_mShowMenuFtEn13);
					g_mShowMenurowEn=g_mShowMenurowEn13; 
//					GetMenuScreenCn(13,g_mShowMenuFtCn13);				
//					g_mShowMenurowCn=g_mShowMenurowCn13;
					GetMenuScreenUn(13,g_mShowMenuFtUn13);				
					g_mShowMenurowUn=g_mShowMenurowUn13;
					FSelShowLanguage();
					break;
				//���������Ӳ˵���ʾ����
		   		case SYS_SUB4MENU1:
				case SYS_SUB4MENU2:
				case SYS_SUB4MENU3:
			    case SYS_SUB4MENU4:
				case SYS_SUB4MENU5:
				case SYS_SUB4MENU6:
				case SYS_SUB4MENU7:
				case SYS_SUB4MENU8:
				case SYS_SUB4MENU9:
				    GetMenuScreenEn(14,g_mShowMenuFtEn14);
					g_mShowMenurowEn=g_mShowMenurowEn14; 
//					GetMenuScreenCn(14,g_mShowMenuFtCn14);				
//					g_mShowMenurowCn=g_mShowMenurowCn14;
					GetMenuScreenUn(14,g_mShowMenuFtUn14);				
					g_mShowMenurowUn=g_mShowMenurowUn14;
					FSelShowLanguage();
				    break;
			

				//̫��ϵ�Ӳ˵���ʾ����
			   	case SYS_SUB2SUB2MENU1:
				case SYS_SUB2SUB2MENU2:
				case SYS_SUB2SUB2MENU3:
				case SYS_SUB2SUB2MENU4:
			    case SYS_SUB2SUB2MENU5:	
				case SYS_SUB2SUB2MENU6:
				case SYS_SUB2SUB2MENU7:
				case SYS_SUB2SUB2MENU8:
				case SYS_SUB2SUB2MENU9:
			    case SYS_SUB2SUB2MENU12:
				    GetMenuScreenEn(22,g_mShowMenuFtEn22);
					g_mShowMenurowEn=g_mShowMenurowEn22; 
//					GetMenuScreenCn(22,g_mShowMenuFtCn22);				
//					g_mShowMenurowCn=g_mShowMenurowCn22;
					//FSelShowLanguage();
					g_mShowLangauge=ENGLISH;
				    break;
				//��������Ӳ˵���ʾ����
			   	case SYS_SUB2SUB3MENU1:
				case SYS_SUB2SUB3MENU2:
				case SYS_SUB2SUB3MENU3:
				case SYS_SUB2SUB3MENU4:
			    case SYS_SUB2SUB3MENU5:
				case SYS_SUB2SUB3MENU6:
				case SYS_SUB2SUB3MENU7:
				case SYS_SUB2SUB3MENU8:
				    GetMenuScreenEn(23,g_mShowMenuFtEn23);
					g_mShowMenurowEn=g_mShowMenurowEn23; 
//					GetMenuScreenCn(23,g_mShowMenuFtCn23);				
//					g_mShowMenurowCn=g_mShowMenurowCn23;
					//FSelShowLanguage();
					g_mShowLangauge=ENGLISH;
					break;
				//�����Ӳ˵���ʾ����
			   	case SYS_SUB2SUB5MENU1:
			        gstrlineEn1=g_sysmenu2501;
					gstrlineEn2="";
					gstrlineEn3=g_sysmenu2502;
					gstrlineEn4="";
					gstrlineEn5=g_sysmenu2503;
					gstrlineEn6="";
					gstrlineEn7="";
					gstrlineEn8="";
					g_mShowMenurowEn=1;
								
//					gstrlineCn1=g_sysmenu2501;				
//					gstrlineCn2=g_sysmenu2502;				
//					gstrlineCn3=g_sysmenu2503;				
//					gstrlineCn4="";				
//					g_mShowMenurowCn=1;


				//	FSelShowLanguage();
				g_mShowLangauge=ENGLISH;
				    break;
				case SYS_SUB2SUB5MENU2:
			        gstrlineEn1=g_sysmenu2501;
					gstrlineEn2="";
					gstrlineEn3=g_sysmenu2502;
					gstrlineEn4="";
					gstrlineEn5=g_sysmenu2503;
					gstrlineEn6="";
					gstrlineEn7="";
					gstrlineEn8="";
					g_mShowMenurowEn=3;
								
//					gstrlineCn1=g_sysmenu2501;				
//					gstrlineCn2=g_sysmenu2502;				
//					gstrlineCn3=g_sysmenu2503;				
//					gstrlineCn4="";				
//					g_mShowMenurowCn=2;


					//FSelShowLanguage();
					g_mShowLangauge=ENGLISH;
				    break;
				case SYS_SUB2SUB5MENU3:
				    gstrlineEn1=g_sysmenu2501;
					gstrlineEn2="";
					gstrlineEn3=g_sysmenu2502;
					gstrlineEn4="";
					gstrlineEn5=g_sysmenu2503;
					gstrlineEn6="";
					gstrlineEn7="";
					gstrlineEn8="";
					g_mShowMenurowEn=5;
								
//					gstrlineCn1=g_sysmenu2501;				
//					gstrlineCn2=g_sysmenu2502;				
//					gstrlineCn3=g_sysmenu2503;				
//					gstrlineCn4="";				
//					g_mShowMenurowCn=3;


					//FSelShowLanguage();
					g_mShowLangauge=ENGLISH;
			    	break;
				//�Զ��������Ӳ˵���ʾ����
			   	case SYS_SUB2SUB8MENU1:
			        gstrlineEn1=g_sysmenu2801;
					gstrlineEn2="";
					gstrlineEn3=g_sysmenu2802;
					gstrlineEn4="";
					gstrlineEn5=g_sysmenu2803;
					gstrlineEn6="";
					gstrlineEn7=g_sysmenu2804;
					gstrlineEn8="";
					g_mShowMenurowEn=1;
								
//					gstrlineCn1=g_sysmenu2801;				
//					gstrlineCn2=g_sysmenu2802;				
//					gstrlineCn3=g_sysmenu2803;				
//					gstrlineCn4=g_sysmenu2804;			
//					g_mShowMenurowCn=1;


					//FSelShowLanguage();
					g_mShowLangauge=ENGLISH;
				    break;
				case SYS_SUB2SUB8MENU2:
			        gstrlineEn1=g_sysmenu2801;
					gstrlineEn2="";
					gstrlineEn3=g_sysmenu2802;
					gstrlineEn4="";
					gstrlineEn5=g_sysmenu2803;
					gstrlineEn6="";
					gstrlineEn7=g_sysmenu2804;
					gstrlineEn8="";
					g_mShowMenurowEn=3;
								
//					gstrlineCn1=g_sysmenu2801;				
//					gstrlineCn2=g_sysmenu2802;				
//					gstrlineCn3=g_sysmenu2803;				
//					gstrlineCn4=g_sysmenu2804;			
//					g_mShowMenurowCn=2;

					g_mShowLangauge=ENGLISH;
					//FSelShowLanguage();
				    break;
				case SYS_SUB2SUB8MENU3:
				    gstrlineEn1=g_sysmenu2801;
					gstrlineEn2="";
					gstrlineEn3=g_sysmenu2802;
					gstrlineEn4="";
					gstrlineEn5=g_sysmenu2803;
					gstrlineEn6="";
					gstrlineEn7=g_sysmenu2804;
					gstrlineEn8="";
					g_mShowMenurowEn=5;
								
//					gstrlineCn1=g_sysmenu2801;				
//					gstrlineCn2=g_sysmenu2802;				
//					gstrlineCn3=g_sysmenu2803;				
//					gstrlineCn4=g_sysmenu2804;			
//					g_mShowMenurowCn=3;

					g_mShowLangauge=ENGLISH;
					//FSelShowLanguage();
			    	break;
				 case SYS_SUB2SUB8MENU4:
			        gstrlineEn1=g_sysmenu2801;
					gstrlineEn2="";
					gstrlineEn3=g_sysmenu2802;
					gstrlineEn4="";
					gstrlineEn5=g_sysmenu2803;
					gstrlineEn6="";
					gstrlineEn7=g_sysmenu2804;
					gstrlineEn8="";
					g_mShowMenurowEn=7;
								
//					gstrlineCn1=g_sysmenu2801;				
//					gstrlineCn2=g_sysmenu2802;				
//					gstrlineCn3=g_sysmenu2803;				
//					gstrlineCn4=g_sysmenu2804;			
//					g_mShowMenurowCn=4;

				   g_mShowLangauge=ENGLISH;
					//FSelShowLanguage();				
				    break;

							//½��Ŀ���Ӳ˵���ʾ����
			   	case SYS_SUB2SUB11MENU1:
			        gstrlineEn1=g_sysmenu21101;
					gstrlineEn2="";
					gstrlineEn3=g_sysmenu21102;
					gstrlineEn4="";
					gstrlineEn5=g_sysmenu21103;
					gstrlineEn6="";
					gstrlineEn7="";
					gstrlineEn8="";
					g_mShowMenurowEn=1;

//					gstrlineCn1=g_sysmenu21101;				
//					gstrlineCn2=g_sysmenu21102;				
//					gstrlineCn3=g_sysmenu21103;				
//					gstrlineCn4="";			
//					g_mShowMenurowCn=1;
					g_mShowLangauge=ENGLISH;
				//	FSelShowLanguage();
				    break;
				case SYS_SUB2SUB11MENU2:
			        gstrlineEn1=g_sysmenu21101;
					gstrlineEn2="";
					gstrlineEn3=g_sysmenu21102;
					gstrlineEn4="";
					gstrlineEn5=g_sysmenu21103;
					gstrlineEn6="";
					gstrlineEn7="";
					gstrlineEn8="";
					g_mShowMenurowEn=3;
					
//					gstrlineCn1=g_sysmenu21101;				
//					gstrlineCn2=g_sysmenu21102;				
//					gstrlineCn3=g_sysmenu21103;				
//					gstrlineCn4="";			
//					g_mShowMenurowCn=2;

					g_mShowLangauge=ENGLISH;
					//FSelShowLanguage();
				    break;
				case SYS_SUB2SUB11MENU3:
				    gstrlineEn1=g_sysmenu21101;
					gstrlineEn2="";
					gstrlineEn3=g_sysmenu21102;
					gstrlineEn4="";
					gstrlineEn5=g_sysmenu21103;
					gstrlineEn6="";
					gstrlineEn7="";
					gstrlineEn8="";
					g_mShowMenurowEn=5;
					
//					gstrlineCn1=g_sysmenu21101;				
//					gstrlineCn2=g_sysmenu21102;				
//					gstrlineCn3=g_sysmenu21103;				
//					gstrlineCn4="";			
//					g_mShowMenurowCn=3;

					g_mShowLangauge=ENGLISH;
					//FSelShowLanguage();
			    	break;
				//Ŀ�������Ӳ˵���ʾ����
			   	case SYS_SUB3SUB6MENU1:
			        gstrlineEn1=g_sysmenu3601;
					gstrlineEn2=g_sysmenu3602;
					gstrlineEn3="";
					gstrlineEn4="";
					gstrlineEn5="";
					gstrlineEn6="";
					gstrlineEn7="";
					gstrlineEn8="";
					g_mShowMenurowEn=1;
					
//					gstrlineCn1=g_sysmenu3601;				
//					gstrlineCn2=g_sysmenu3602;				
//					gstrlineCn3="";				
//					gstrlineCn4="";			
//					g_mShowMenurowCn=1;

					g_mShowLangauge=ENGLISH;
					//FSelShowLanguage();
			    	break;
				    break;
				case SYS_SUB3SUB6MENU2:
			        gstrlineEn1=g_sysmenu3601;
					gstrlineEn2=g_sysmenu3602;
					gstrlineEn3="";
					gstrlineEn4="";
					gstrlineEn5="";
					gstrlineEn6="";
					gstrlineEn7="";
					gstrlineEn8="";
					g_mShowMenurowEn=2;
					
//					gstrlineCn1=g_sysmenu3601;				
//					gstrlineCn2=g_sysmenu3602;				
//					gstrlineCn3="";				
//					gstrlineCn4="";			
//					g_mShowMenurowCn=2;

					g_mShowLangauge=ENGLISH;
					//FSelShowLanguage();
				    break;
				//����Ұ�����Ӳ˵���ʾ����
			   	case SYS_SUB3SUB8MENU1:
			        gstrlineEn1=g_sysmenu3801;
					gstrlineEn2=g_sysmenu3802;
					gstrlineEn3="";
					gstrlineEn4="";
					gstrlineEn5="";
					gstrlineEn6="";
					gstrlineEn7="";
					gstrlineEn8="";
					g_mShowMenurowEn=1;
					
//					gstrlineCn1=g_sysmenu3801;				
//					gstrlineCn2=g_sysmenu3802;				
//					gstrlineCn3="";				
//					gstrlineCn4="";			
//					g_mShowMenurowCn=1;

					g_mShowLangauge=ENGLISH;
					//FSelShowLanguage();
				    break;
				case SYS_SUB3SUB8MENU2:
			        gstrlineEn1=g_sysmenu3801;
					gstrlineEn2=g_sysmenu3802;
					gstrlineEn3="";
					gstrlineEn4="";
					gstrlineEn5="";
					gstrlineEn6="";
					gstrlineEn7="";
					gstrlineEn8="";
					g_mShowMenurowEn=2;
					
//					gstrlineCn1=g_sysmenu3801;				
//					gstrlineCn2=g_sysmenu3802;				
//					gstrlineCn3="";				
//					gstrlineCn4="";			
//					g_mShowMenurowCn=2;

					g_mShowLangauge=ENGLISH;
					//FSelShowLanguage();
				    break;
				 //�ص������Ӳ˵���ʾ����
			   	case SYS_SUB4SUB3MENU1:
			        gstrlineEn1=g_sysmenu4301;
					gstrlineEn3=g_sysmenu4302;
					gstrlineEn2="";
					gstrlineEn4="";
					gstrlineEn5="";
					gstrlineEn6="";
					gstrlineEn7="";
					gstrlineEn8="";
					g_mShowMenurowEn=1;
					
//					gstrlineCn1=g_sysmenu4301;				
//					gstrlineCn2=g_sysmenu4302;				
//					gstrlineCn3="";				
//					gstrlineCn4="";			
//					g_mShowMenurowCn=1;

					//FSelShowLanguage();
					g_mShowLangauge=ENGLISH;
				    break;
				case SYS_SUB4SUB3MENU2:
			        gstrlineEn1=g_sysmenu4301;
					gstrlineEn3=g_sysmenu4302;
					gstrlineEn2="";
					gstrlineEn4="";
					gstrlineEn5="";
					gstrlineEn6="";
					gstrlineEn7="";
					gstrlineEn8="";
					g_mShowMenurowEn=3;
					
//					gstrlineCn1=g_sysmenu4301;				
//					gstrlineCn2=g_sysmenu4302;				
//					gstrlineCn3="";				
//					gstrlineCn4="";			
//					g_mShowMenurowCn=2;

					//FSelShowLanguage();
					g_mShowLangauge=ENGLISH;
				    break;
				 //�Զ���ص�ѡ��
		          case  SYS_SUB4SUB3SUB2_SELECT:
			        gstrlineEn1=g_sysmenu43021;
					gstrlineEn3=g_sysmenu43022;
					gstrlineEn5=g_sysmenu43023;
					gstrlineEn7=g_sysmenu43024;
					gstrlineEn2="";
					gstrlineEn4="";
					gstrlineEn6="";
					gstrlineEn8="";
					g_mShowMenurowEn=1;

//					gstrlineCn1=g_sysmenu43021;				
//					gstrlineCn2=g_sysmenu43022;				
//					gstrlineCn3=g_sysmenu43023;				
//					gstrlineCn4=g_sysmenu43024;			
//					g_mShowMenurowCn=1;

					//FSelShowLanguage();
					g_mShowLangauge=ENGLISH;
				  break;
				  //�Զ���ص�����
			      case  SYS_SUB4SUB3SUB2_ADD:
				    gstrlineEn1=g_sysmenu43021;
					gstrlineEn3=g_sysmenu43022;
					gstrlineEn5=g_sysmenu43023;
					gstrlineEn7=g_sysmenu43024;
					gstrlineEn2="";
					gstrlineEn4="";
					gstrlineEn6="";
					gstrlineEn8="";
					g_mShowMenurowEn=3;

//					gstrlineCn1=g_sysmenu43021;				
//					gstrlineCn2=g_sysmenu43022;				
//					gstrlineCn3=g_sysmenu43023;				
//					gstrlineCn4=g_sysmenu43024;			
//					g_mShowMenurowCn=2;

					//FSelShowLanguage();
					g_mShowLangauge=ENGLISH;
				  break;
				  //�Զ���ص�ɾ��
			      case  SYS_SUB4SUB3SUB2_DELETE:
				    gstrlineEn1=g_sysmenu43021;
					gstrlineEn3=g_sysmenu43022;
					gstrlineEn5=g_sysmenu43023;
					gstrlineEn7=g_sysmenu43024;
					gstrlineEn2="";
					gstrlineEn4="";
					gstrlineEn6="";
					gstrlineEn8="";
					g_mShowMenurowEn=5;

//					gstrlineCn1=g_sysmenu43021;				
//					gstrlineCn2=g_sysmenu43022;				
//					gstrlineCn3=g_sysmenu43023;				
//					gstrlineCn4=g_sysmenu43024;			
//					g_mShowMenurowCn=3;

					//FSelShowLanguage();
					g_mShowLangauge=ENGLISH;
				   break;
				   //�Զ���ص��޸�
			      case  SYS_SUB4SUB3SUB2_MODIFY:
				    gstrlineEn1=g_sysmenu43021;
					gstrlineEn3=g_sysmenu43022;
					gstrlineEn5=g_sysmenu43023;
					gstrlineEn7=g_sysmenu43024;
					gstrlineEn2="";
					gstrlineEn4="";
					gstrlineEn6="";
					gstrlineEn8="";
					g_mShowMenurowEn=7;

//					gstrlineCn1=g_sysmenu43021;				
//					gstrlineCn2=g_sysmenu43022;				
//					gstrlineCn3=g_sysmenu43023;				
//					gstrlineCn4=g_sysmenu43024;			
//					g_mShowMenurowCn=4;

					//FSelShowLanguage();
					g_mShowLangauge=ENGLISH;
				   break;

//				case SYS_SUB4SUB7MENU3:
//				    gstrlineEn1=g_sysmenu4701;
//					gstrlineEn3=g_sysmenu4702;
//					gstrlineEn5=g_sysmenu4703;
//					gstrlineEn7=g_sysmenu4704;
//					gstrlineEn2="";
//					gstrlineEn4="";
//					gstrlineEn6="";
//					gstrlineEn8="";
//					g_mShowMenurowEn=5;
//						
//					gstrlineCn1=g_sysmenu4701;				
//					gstrlineCn2=g_sysmenu4702;				
//					gstrlineCn3=g_sysmenu4703;				
//					gstrlineCn4=g_sysmenu4704;			
//					g_mShowMenurowCn=3;
//
//					FSelShowLanguage();
//			    	break;
//				case SYS_SUB4SUB7MENU4:
//			        gstrlineEn1=g_sysmenu4701;
//					gstrlineEn3=g_sysmenu4702;
//					gstrlineEn5=g_sysmenu4703;
//					gstrlineEn7=g_sysmenu4704;
//					gstrlineEn2="";
//					gstrlineEn4="";
//					gstrlineEn6="";
//					gstrlineEn8="";
//					g_mShowMenurowEn=7;
//						
//					gstrlineCn1=g_sysmenu4701;				
//					gstrlineCn2=g_sysmenu4702;				
//					gstrlineCn3=g_sysmenu4703;				
//					gstrlineCn4=g_sysmenu4704;			
//					g_mShowMenurowCn=4;
//
//					//FSelShowLanguage();
//                  //g_mShowLangauge=ENGLISH;
//					break;


				//�����ٶ��Ӳ˵���ʾ����
			   	case SYS_SUB4SUB8MENU1:
			        gstrlineEn1=g_sysmenu4801;
					gstrlineEn2="";
					gstrlineEn3=g_sysmenu4802;
					gstrlineEn4="";
					gstrlineEn5=g_sysmenu4803;
					gstrlineEn6="";
					gstrlineEn7=g_sysmenu4804;
					gstrlineEn8="";
					g_mShowMenurowEn=1;
						
//					gstrlineCn1=g_sysmenu4801;				
//					gstrlineCn2=g_sysmenu4802;				
//					gstrlineCn3=g_sysmenu4803;				
//					gstrlineCn4=g_sysmenu4804;			
//					g_mShowMenurowCn=1;

					//FSelShowLanguage();
					g_mShowLangauge=ENGLISH;
				    break;
				case SYS_SUB4SUB8MENU2:
			        gstrlineEn1=g_sysmenu4801;
					gstrlineEn2="";
					gstrlineEn3=g_sysmenu4802;
					gstrlineEn4="";
					gstrlineEn5=g_sysmenu4803;
					gstrlineEn6="";
					gstrlineEn7=g_sysmenu4804;
					gstrlineEn8="";
					g_mShowMenurowEn=3;
						
//					gstrlineCn1=g_sysmenu4801;				
//					gstrlineCn2=g_sysmenu4802;				
//					gstrlineCn3=g_sysmenu4803;				
//					gstrlineCn4=g_sysmenu4804;			
//					g_mShowMenurowCn=2;

					//FSelShowLanguage();
					g_mShowLangauge=ENGLISH;
				    break;
				case SYS_SUB4SUB8MENU3:
				    gstrlineEn1=g_sysmenu4801;
					gstrlineEn2="";
					gstrlineEn3=g_sysmenu4802;
					gstrlineEn4="";
					gstrlineEn5=g_sysmenu4803;
					gstrlineEn6="";
					gstrlineEn7=g_sysmenu4804;
					gstrlineEn8="";
					g_mShowMenurowEn=5;
						
//					gstrlineCn1=g_sysmenu4801;				
//					gstrlineCn2=g_sysmenu4802;				
//					gstrlineCn3=g_sysmenu4803;				
//					gstrlineCn4=g_sysmenu4804;			
//					g_mShowMenurowCn=3;

					//FSelShowLanguage();
					g_mShowLangauge=ENGLISH;
			    	break;
				case SYS_SUB4SUB8MENU4:
			        gstrlineEn1=g_sysmenu4801;
					gstrlineEn2="";
					gstrlineEn3=g_sysmenu4802;
					gstrlineEn4="";
					gstrlineEn5=g_sysmenu4803;
					gstrlineEn6="";
					gstrlineEn7=g_sysmenu4804;
					gstrlineEn8="";
					g_mShowMenurowEn=7;
						
//					gstrlineCn1=g_sysmenu4801;				
//					gstrlineCn2=g_sysmenu4802;				
//					gstrlineCn3=g_sysmenu4803;				
//					gstrlineCn4=g_sysmenu4804;			
//					g_mShowMenurowCn=4;

					//FSelShowLanguage();
					g_mShowLangauge=ENGLISH;
					break;

				///*************************************
				///**************************************
				//��ײ����

			//��һ��Ŀ�˵�
			//�����Զ�У׼
//			case SYS_SUB1SUB1AUTOSTAR_ALIGN:	   
//       
//				  g_mAlignStarNum=FindAlignStar(FCalSiderealTime(1,false,g_mGoto.m_nLongitude),g_mGoto.m_nAtitude,g_mStarAlign,AlignStarName,AlignStarNameCn);					 
//		
//				   gLocation.mLongitude=g_mGoto.m_nLongitude;
//			       gLocation.mAtitude=g_mGoto.m_nAtitude; 
//				   if(g_nSeledAlignStarNum==1)
//				   {
//				      gStarRAD.mRightAscension=g_mStarAlign[0];
//				      gStarRAD.mDeclination=g_mStarAlign[1];
//					  sprintf(gstrtemp5,"R.a: %02dh%02dm                ",(int)g_mStarAlign[0],(int)((g_mStarAlign[0]-(int)g_mStarAlign[0])*60));	
//				       if((int)g_mStarAlign[0]<10)
//				       {
//				          gstrtemp5[5]=' ';
//				       }
//
//				       if((int)((g_mStarAlign[0]-(int)g_mStarAlign[0])*60)<10)
//				       {
//				         gstrtemp5[8]=' ';
//				       }
//
//					  
//						if(g_mStarAlign[1]<0)
//					   {
//					     sprintf(gstrtemp6,"Dec:-%02d %02d                 ",abs((int)g_mStarAlign[1]),abs((int)((g_mStarAlign[1]-(int)g_mStarAlign[1])*60)));								   		   	  
//					   	}
//						else
//						{
//						  sprintf(gstrtemp6,"Dec:+%02d %02d                 ",(int)g_mStarAlign[1],abs((int)((g_mStarAlign[1]-(int)g_mStarAlign[1])*60)));								   		   	  
//					 
//					    }
//					   if((int)g_mStarAlign[1]<10)
//				       {
//				          gstrtemp6[5]=' ';
//				       }
//
//				       if((int)((g_mStarAlign[1]-(int)g_mStarAlign[1])*60)<10)
//				       {
//				         gstrtemp6[8]=' ';
//				       }
//				   }
//				   if(g_nSeledAlignStarNum==2)
//				   {
//				      gStarRAD.mRightAscension=g_mStarAlign[2];
//				      gStarRAD.mDeclination=g_mStarAlign[3];
//					  sprintf(gstrtemp5,"R.a:%02dh%02dm                ",(int)g_mStarAlign[2],(int)((g_mStarAlign[2]-(int)g_mStarAlign[2])*60));	
//				        if((int)g_mStarAlign[2]<10)
//				       {
//				          gstrtemp5[5]=' ';
//				       }
//
//				       if((int)((g_mStarAlign[2]-(int)g_mStarAlign[2])*60)<10)
//				       {
//				         gstrtemp5[8]=' ';
//				       }
//					 	if(g_mStarAlign[3]<0)
//					   {
//					      sprintf(gstrtemp6,"Dec:-%02d %02d                 ",abs((int)g_mStarAlign[3]),abs((int)((g_mStarAlign[3]-(int)g_mStarAlign[3])*60)));								   		   	  
//					   	}
//						else
//						{
//						  sprintf(gstrtemp6,"Dec:+%02d %02d                 ",(int)g_mStarAlign[3],abs((int)((g_mStarAlign[3]-(int)g_mStarAlign[3])*60)));								   		   	  
//					 	  }
//					        if((int)g_mStarAlign[3]<10)
//				       {
//				          gstrtemp6[5]=' ';
//				       }
//
//				       if((int)((g_mStarAlign[3]-(int)g_mStarAlign[3])*60)<10)
//				       {
//				         gstrtemp6[8]=' ';
//				       }
//				   }
//				   					
//
//				   if(g_mTelStatus==1)
//					{
//						
//						switch(g_mAzEq)
//						{
//						case 1: 
//						  
//						 g_teldec=g_mTelDec;
//						 g_telra=FCalSiderealTime(1,false,g_mGoto.m_nLongitude)-g_mTelRa;
//						 while(	g_telra>=24)
//						 {
//						   g_telra=g_telra-24;
//						  }
//						  while(g_telra<0)
//						   {
//						    g_telra=g_telra+24;
//						   }
//						   gLocation.mLongitude=g_mGoto.m_nLongitude;
//					       gLocation.mAtitude=g_mGoto.m_nAtitude;
//						   gTelRAD.mRightAscension=g_telra;
//						   gTelRAD.mDeclination=g_teldec;
//						   FCalStarAEPos(gLocation,gTelRAD,g_mGoto.m_nSysTimeType,g_mGoto.m_nNutation,&gTelAZ);
//						   g_mTelAzi1=gTelAZ.mANzimuth;
//						   g_mTelAlt1=gTelAZ.mAtitude;
//
//						   g_mTelAzi_du=(int)g_mTelAzi1;
//						   g_mTelAzi_fen=(int)(60.0*(g_mTelAzi1-g_mTelAzi_du));
//
//						    g_mTelAlt_du=(int)g_mTelAlt1;
//						   g_mTelAlt_fen=(int)(60.0*(g_mTelAlt1-g_mTelAlt_du));
//						   g_mTelAlt_miao=(g_mTelAlt1-g_mTelAlt_du-g_mTelAlt_fen/60.0)*3600;
//				         
//						case 0:	 //��Զ����λ��ʾ����
//							 sprintf(gstrtemp5,"Azi:%03d %02d          ",abs(g_mTelAzi_du),abs(g_mTelAzi_fen));
//							   if(abs(g_mTelAzi_du)<100)
//							   {
//							     gstrtemp5[4]=' ';
//							   }
//							   if(abs(g_mTelAzi_du)<10)
//							   {
//							     gstrtemp5[5]=' ';
//							   }
//							    if(abs(g_mTelAzi_fen)<10)
//							   {
//							     gstrtemp5[8]=' ';
//							     }
//							 //��Զ���߶���ʾ����
//							//if((g_mTelAlt_du==0)&&((g_mTelAlt_fen<0)||(g_mTelAlt_miao<0)))
//							//{
//								//sprintf(gstrtemp6,"Alt:-%02d %02d          ",abs(g_mTelAlt_du),abs(g_mTelAlt_fen));
//							//}
//				            //else
//							//{
//							    sprintf(gstrtemp6,"Alt: %02d %02d          ",abs(g_mTelAlt_du),abs(g_mTelAlt_fen));
//							//}
//							
//							if(abs(g_mTelAlt_du)<10)
//							   {
//							     gstrtemp6[5]=' ';
//							   }
//							    if(abs(g_mTelAlt_fen)<10)
//							   {
//							     gstrtemp6[8]=' ';
//							   }
//							 
//							break;
//
//						default:
//							break;
//						}
//						 
//				   }
//
//
//				   FCalStarAEPos(gLocation,gStarRAD,g_mGoto.m_nSysTimeType,g_mGoto.m_nNutation,&gStarAZ);
//				   sprintf(gstrtemp7,"Azi:%03dd%02dm             ",(int)gStarAZ.mANzimuth,(int)((gStarAZ.mANzimuth-(int)gStarAZ.mANzimuth)*60)); 
//				   sprintf(gstrtemp8,"Alt: %02dd%02dm           ",abs((int)gStarAZ.mAtitude),abs((int)((gStarAZ.mAtitude-(int)gStarAZ.mAtitude)*60)));
//				   if(g_mTelStatus==1)
//				   {
//				     sprintf(gstrtemp7,"Azi:%03d %02d                ",(int)gStarAZ.mANzimuth,(int)((gStarAZ.mANzimuth-(int)gStarAZ.mANzimuth)*60));				   
//				     sprintf(gstrtemp8,"Alt:+%02d %02d               ",abs((int)gStarAZ.mAtitude),abs((int)((gStarAZ.mAtitude-(int)gStarAZ.mAtitude)*60)));
//                   }
//				   				   
//
//				   if((int)gStarAZ.mANzimuth <100)
//				   {
//				     gstrtemp7[4]=' ';
//				   }
//				   if((int)gStarAZ.mANzimuth <10)
//				   {
//				     gstrtemp7[5]=' ';
//				   }
//
//				   if((int)((gStarAZ.mANzimuth-(int)gStarAZ.mANzimuth)*60)<10)
//				   {
//				     gstrtemp7[8]=' ';
//				   }
//				     if(abs((int)gStarAZ.mAtitude)<10)
//				   {
//				     gstrtemp8[5]=' ';
//				   }
//
//				   if(abs((int)((gStarAZ.mAtitude-(int)gStarAZ.mAtitude)*60))<10)
//				   {
//				     gstrtemp8[8]=' ';
//				   }
//
//					     
//				   
//				   gstrlineEn1=g_sysmenu1101;
//				   gstrlineEn2="                     ";
//                   if(g_nSeledAlignStarNum==1)
//				   {
//				      gstrlineEn3=&AlignStarName[0][0];
//				   }
//				   if(g_nSeledAlignStarNum==2)
//				   {
//				      gstrlineEn3=&AlignStarName[1][0];
//				   }	
//				   gstrlineEn4="                        ";	
//				   gstrlineEn5=gstrtemp5;
//				   gstrlineEn6=gstrtemp6;
//				   gstrlineEn7=gstrtemp7;
//				   gstrlineEn8=gstrtemp8;
//					
//								   
//				   if(g_nSeledAlignStarNum==1)
//				   {
////				      gstrlineCn1=&AlignStarNameCn[0][0];
//				   }
//				   if(g_nSeledAlignStarNum==2)
//				   {
////				      gstrlineCn1=&AlignStarNameCn[1][0];
//				   }
//				   
////				   gstrlineCn3=gstrlineEn3;				   
////				   gstrlineCn4="                      ";
////				   gstrlineCn5=gstrtemp5;
////				   gstrlineCn6=gstrtemp6;
////				   gstrlineCn7=gstrtemp7;
////				   gstrlineCn8=gstrtemp8;	
//				   
//				   
//				   g_mShowMenurowEn=0;
//				   //FSelShowLanguage();
//				   g_mShowLangauge=ENGLISH;
//
//
//
//
//			      break;

			//һ����������У׼��ʾ
			case SYS_SUB1SUB2STAR_ALIGN	:
				 
				   g_mAlignStarNum=FindAlignStar(FCalSiderealTime(1,false,g_mGoto.m_nLongitude),g_mGoto.m_nAtitude,g_mStarAlign,AlignStarName,AlignStarNameCn);					 
				
				   sprintf(gstrtemp5,"R.a: %02dh%02dm                ",(int)g_mStarAlign[2*(g_nSelAlignStarNum-1)],(int)((g_mStarAlign[2*(g_nSelAlignStarNum-1)]-(int)g_mStarAlign[2*(g_nSelAlignStarNum-1)])*60));	
				   
				   if((int)g_mStarAlign[2*(g_nSelAlignStarNum-1)]<10)
				   {
				      gstrtemp5[5]=' ';
				   }

				   if((int)((g_mStarAlign[2*(g_nSelAlignStarNum-1)]-(int)g_mStarAlign[2*(g_nSelAlignStarNum-1)])*60)<10)
				   {
				      gstrtemp5[8]=' ';
				   }



				   if(g_mStarAlign[2*(g_nSelAlignStarNum-1)+1]<0)
				   {
				     sprintf(gstrtemp6,"Dec:-%02d %02d                 ",abs((int)g_mStarAlign[2*(g_nSelAlignStarNum-1)+1]),abs((int)((g_mStarAlign[2*(g_nSelAlignStarNum-1)+1]-(int)g_mStarAlign[2*(g_nSelAlignStarNum-1)+1])*60)));								   		   	  
				   	}
					else
					{
					  sprintf(gstrtemp6,"Dec:+%02d %02d                 ",(int)g_mStarAlign[2*(g_nSelAlignStarNum-1)+1],abs((int)((g_mStarAlign[2*(g_nSelAlignStarNum-1)+1]-(int)g_mStarAlign[2*(g_nSelAlignStarNum-1)+1])*60)));								   		   	  
				 
				    }

				 if((int)g_mStarAlign[2*(g_nSelAlignStarNum-1)+1]<10)
				    {
				      gstrtemp6[5]=' ';
				   }

				  if((int)((g_mStarAlign[2*(g_nSelAlignStarNum-1)+1]-(int)g_mStarAlign[2*(g_nSelAlignStarNum-1)]+1)*60)<10)
				   {
				      gstrtemp6[8]=' ';
				   }

				    
					

				 if(g_nAlignPoint)
				 {
						
						switch(g_mAzEq)
						{
						case 1: 
						  
						 g_teldec=g_mTelDec;
						 g_telra=FCalSiderealTime(1,false,g_mGoto.m_nLongitude)-g_mTelRa;
						 while(	g_telra>=24)
						 {
						   g_telra=g_telra-24;
						  }
						  while(g_telra<0)
						   {
						    g_telra=g_telra+24;
						   }
						   gLocation.mLongitude=g_mGoto.m_nLongitude;
					       gLocation.mAtitude=g_mGoto.m_nAtitude;
						   gTelRAD.mRightAscension=g_telra;
						   gTelRAD.mDeclination=g_teldec;
						   FCalStarAEPos(gLocation,gTelRAD,g_mGoto.m_nSysTimeType,g_mGoto.m_nNutation,&gTelAZ);
						   g_mTelAzi1=gTelAZ.mANzimuth;
						   g_mTelAlt1=gTelAZ.mAtitude;

					       g_mTelAzi_du=(int)g_mTelAzi1;
						   g_mTelAzi_fen=(int)(60.0*(g_mTelAzi1-g_mTelAzi_du));

						   g_mTelAlt_du=(int)g_mTelAlt1;
						   g_mTelAlt_fen=(int)(60.0*(g_mTelAlt1-g_mTelAlt_du));
						   g_mTelAlt_miao=(g_mTelAlt1-g_mTelAlt_du-g_mTelAlt_fen/60.0)*3600;

				         
						case 0:	 
						    //��Զ����λ��ʾ����
							   sprintf(gstrtemp5,"Azi:%03d %02d          ",abs(g_mTelAzi_du),abs(g_mTelAzi_fen));
							   if(abs(g_mTelAzi_du)<100)
							   {
							     gstrtemp5[4]=' ';
							   }
							   if(abs(g_mTelAzi_du)<10)
							   {
							     gstrtemp5[5]=' ';
							   }
							    if(abs(g_mTelAzi_fen)<10)
							   {
							     gstrtemp5[8]=' ';
							   }
							 //��Զ���߶���ʾ����
//							if((g_mTelAlt_du<0)||(g_mTelAlt_fen<0)||(g_mTelAlt_miao<0))
//							{
//								sprintf(gstrtemp6,"Alt:-%02d %02d          ",abs(g_mTelAlt_du),abs(g_mTelAlt_fen));
//							}
//				            else
//							{
							   sprintf(gstrtemp6,"Alt: %02d %02d          ",abs(g_mTelAlt_du),abs(g_mTelAlt_fen));
							//}
							
							if(abs(g_mTelAlt_du)<10)
							   {
							     gstrtemp6[5]=' ';
							   }
							    if(abs(g_mTelAlt_fen)<10)
							   {
							     gstrtemp6[8]=' ';
							   }
							  
							break;

						default:
							break;
						}

					}
						
						
				


				   gLocation.mLongitude=g_mGoto.m_nLongitude;
			       gLocation.mAtitude=g_mGoto.m_nAtitude;
				   gStarRAD.mRightAscension=g_mStarAlign[2*(g_nSelAlignStarNum-1)];
				   gStarRAD.mDeclination=g_mStarAlign[2*(g_nSelAlignStarNum-1)+1];
				   FCalStarAEPos(gLocation,gStarRAD,g_mGoto.m_nSysTimeType,g_mGoto.m_nNutation,&gStarAZ);

				   sprintf(gstrtemp7,"Azi:%03d %02d                ",(int)gStarAZ.mANzimuth,(int)((gStarAZ.mANzimuth-(int)gStarAZ.mANzimuth)*60));				   
				   sprintf(gstrtemp8,"Alt:+%02d %02d               ",abs((int)gStarAZ.mAtitude),abs((int)((gStarAZ.mAtitude-(int)gStarAZ.mAtitude)*60)));
        
				   if(g_mTelStatus==1)
				   {
				     sprintf(gstrtemp7,"Azi:%03d %02d                ",(int)gStarAZ.mANzimuth,(int)((gStarAZ.mANzimuth-(int)gStarAZ.mANzimuth)*60));				   
				     sprintf(gstrtemp8,"Alt:+%02d %02d               ",abs((int)gStarAZ.mAtitude),abs((int)((gStarAZ.mAtitude-(int)gStarAZ.mAtitude)*60)));
                   }
				   				   

				   if((int)gStarAZ.mANzimuth <100)
				   {
				     gstrtemp7[4]=' ';
				   }
				   if((int)gStarAZ.mANzimuth <10)
				   {
				     gstrtemp7[5]=' ';
				   }

				   if((int)((gStarAZ.mANzimuth-(int)gStarAZ.mANzimuth)*60)<10)
				   {
				     gstrtemp7[8]=' ';
				   }
				     if(abs((int)gStarAZ.mAtitude)<10)
				   {
				     gstrtemp8[5]=' ';
				   }

				   if(abs((int)((gStarAZ.mAtitude-(int)gStarAZ.mAtitude)*60))<10)
				   {
				     gstrtemp8[8]=' ';
				   }

				   
				   gstrlineEn1=g_sysmenu1101;
				   gstrlineEn2="                     ";
                   gstrlineEn3=&AlignStarName[g_nSelAlignStarNum-1][0];	
				   gstrlineEn4="                        ";	
				   gstrlineEn5=gstrtemp7;
				   gstrlineEn6=gstrtemp8;
				   gstrlineEn7=gstrtemp5;
				   gstrlineEn8=gstrtemp6;
					
								   
//				   gstrlineCn1=&AlignStarNameCn[g_nSelAlignStarNum-1][0];
//				   gstrlineCn3=gstrlineEn3;	
//				   gstrlineCn4="                      ";
//				   gstrlineCn5=gstrtemp7;
//				   gstrlineCn6=gstrtemp8;
//				   gstrlineCn7=gstrtemp5;
//				   gstrlineCn8=gstrtemp6;	
				   
				   
				   g_mShowMenurowEn=0;
				   //FSelShowLanguage();
				   g_mShowLangauge=ENGLISH;
		        break; 
			//�����˵���ʾ����
				//��Զ��ͬ��
	  		    case SYS_SUB1SUB4MENU1:
					gstrlineEn1="";
					gstrlineEn2="Targers Sync. Open?";
					gstrlineEn3="";
					gstrlineEn4="";
					gstrlineEn5="     ENTER:Yes";
					gstrlineEn6="";
					gstrlineEn7="     CANCEL:No";
					gstrlineEn8="";
					g_mShowMenurowEn=0;
			   	    g_mShowLangauge=ENGLISH;
				break;
			    case SYS_SUB1SUB4MENU2:
	                gstrlineEn1="Targers Sync. ensure!";
					gstrlineEn2="";
					gstrlineEn3="Targers Sync. cancel!";
					gstrlineEn4="";
					gstrlineEn5="";
					gstrlineEn6="";
					gstrlineEn7="";
					gstrlineEn8="";
					g_mShowMenurowEn=1;
			   	    g_mShowLangauge=ENGLISH;
				break ;
				case SYS_SUB1SUB4MENU3:
				    gstrlineEn1="Targers Sync. ensure!";
					gstrlineEn2="";
					gstrlineEn3="Targers Sync. cancel!";
					gstrlineEn4="";
					gstrlineEn5="";
					gstrlineEn6="";
					gstrlineEn7="";
					gstrlineEn8="";
					g_mShowMenurowEn=3;
			   	    g_mShowLangauge=ENGLISH;
				break ;
				  //����ƫ��
				case SYS_SUB1SUB8POLE_AXIS_ERROR: 
		    		gstrlineEn1="Pole Axis Dev: ";	
					gstrlineEn2="";
					if(g_mPoleAxisEW>0)
					{
					  sprintf(gstrtemp1,"ToE:%.5f	Degree",fabs(g_mPoleAxisEW));
					 }
					 else
					 {
					   sprintf(gstrtemp1,"ToW:%.5f	Degree",fabs(g_mPoleAxisEW));
					   }
					gstrlineEn3=gstrtemp1;
					if(g_mPoleAxisNS>0)
					{
					  sprintf(gstrtemp2,"ToN:%.5f	Degree",fabs(g_mPoleAxisNS));
					 }
					 else
					 {
					   sprintf(gstrtemp2,"ToS:%.5f	Degree",fabs(g_mPoleAxisNS));
					   }
					gstrlineEn4="";
					gstrlineEn5=gstrtemp2;
					gstrlineEn6="";
					gstrlineEn7="";
					gstrlineEn8="";
			    	g_mShowMenurowEn=0;
					g_mShowLangauge=ENGLISH;
		    	break;		
	
			   	

			//�ྭ�ز�У����ʼ	
			  case SYS_SUB1SUB11RA_GEAR_ERROR_BEGIN: 
			        gstrlineEn1="                      ";
					gstrlineEn2=g_sysmenu11101;
					gstrlineEn3="                      ";
					gstrlineEn4=g_sysmenu11102;
					gstrlineEn5="                      ";
					gstrlineEn6=g_sysmenu11103;
					gstrlineEn7="                      ";
					gstrlineEn8=g_sysmenu11104;

//					gstrlineCn1=g_sysmenu11101;
//					gstrlineCn2=g_sysmenu11102;
//					gstrlineCn3=g_sysmenu11103;
//					gstrlineCn4=g_sysmenu11104;
					g_mShowMenurowEn=0;
				    //FSelShowLanguage();
					g_mShowLangauge=ENGLISH;
					break;
		       case SYS_SUB1SUB11RA_GEAR_ERROR: //�ྭ�ز�У��
								  
			        gstrlineEn1="                      ";
					gstrlineEn2=g_sysmenu11105;
					gstrlineEn3="                      ";
					gstrlineEn4=g_sysmenu11106;
					gstrlineEn5="                      ";
					gstrlineEn6=g_sysmenu11107;
					gstrlineEn7="                      ";
					gstrlineEn8=g_sysmenu11108;

//					gstrlineCn1=g_sysmenu11105;
//					gstrlineCn2=g_sysmenu11106;
//					gstrlineCn3=g_sysmenu11107;
//					gstrlineCn4=g_sysmenu11108;
					g_mShowMenurowEn=0;
				    //FSelShowLanguage();
					g_mShowLangauge=ENGLISH;
					break;
				case SYS_SUB1SUB11RA_GEAR_ERROR_ALIGN: 		 //�ྭ�ز�����У��
								  
			        gstrlineEn1="                      ";
					gstrlineEn2=g_sysmenu11109;
					gstrlineEn3="                      ";
					gstrlineEn4=g_sysmenu111010;
					gstrlineEn5="                      ";
					gstrlineEn6=g_sysmenu111011;
					gstrlineEn7="                      ";
					gstrlineEn8=g_sysmenu111012;

//					gstrlineCn1=g_sysmenu11109;
//					gstrlineCn2=g_sysmenu111010;
//					gstrlineCn3=g_sysmenu111011;
//					gstrlineCn4=g_sysmenu111012;
					g_mShowMenurowEn=0;
				    //FSelShowLanguage();
					g_mShowLangauge=ENGLISH;
					break;
                 //���һ�γྭ�ز�У��
    	          case SYS_SUB1SUB11RA_GEAR_ERROR_ALIGN_OK: 				  
				    sprintf(gstrtemp1,"%.1f",g_mRaAziGearError);

		    	    gstrlineEn1="                      ";
					gstrlineEn2="                      ";
					if(g_mTelGearErrorRaAlignDirect==2)
					{
					  gstrlineEn3=g_sysmenu111013;
					 }
					if(g_mTelGearErrorRaAlignDirect==1)
					{
					  gstrlineEn3=g_sysmenu111014;
					 }
					gstrlineEn4="                      ";
					gstrlineEn5=gstrtemp1;
					gstrlineEn6="                      ";
					gstrlineEn7=g_sysmenu111015;
					gstrlineEn8="                      ";

					
//					gstrlineCn1=gstrtemp1;
//					gstrlineCn2=g_sysmenu111014;
//					gstrlineCn3=g_sysmenu111015;
//					gstrlineCn4=g_sysmenu111016;
					g_mShowMenurowEn=0;
				    //FSelShowLanguage();
				   g_mShowLangauge=ENGLISH;
			       break;	

			  	  //��ɳྭ�ز�У��
    	           case SYS_SUB1SUB11RA_GEAR_ERROR_ALIGN_END: 
				   sprintf(gstrtemp1,"%.1f",g_mRaAziGearEvenError);
		    	    gstrlineEn1="                      ";
					gstrlineEn2="                      ";
					gstrlineEn3=g_sysmenu111016;
					gstrlineEn4="                      ";
					gstrlineEn5=gstrtemp1;
					gstrlineEn6="                      ";
					gstrlineEn7=g_sysmenu111015;
					gstrlineEn8="                      ";

					
///					gstrlineCn1=gstrtemp1;
//					gstrlineCn2=g_sysmenu111018;
//					gstrlineCn3=g_sysmenu111019;
//					gstrlineCn4=g_sysmenu111020;

					g_mShowMenurowEn=0;
				   // FSelShowLanguage();
				   g_mShowLangauge=ENGLISH;
			       break;	

			    	
              //��γ�ز�У����ʼ	
			  case SYS_SUB1SUB12DEC_GEAR_ERROR_BEGIN: 
			        gstrlineEn1="                      ";
					gstrlineEn2=g_sysmenu11101;
					gstrlineEn3="                      ";
					gstrlineEn4=g_sysmenu11102;
					gstrlineEn5="                      ";
					gstrlineEn6=g_sysmenu11103;
					gstrlineEn7="                      ";
					gstrlineEn8=g_sysmenu11104;

//					gstrlineCn1=g_sysmenu11101;
//					gstrlineCn2=g_sysmenu11102;
//					gstrlineCn3=g_sysmenu11103;
//					gstrlineCn4=g_sysmenu11104;
					g_mShowMenurowEn=0;
				    //FSelShowLanguage();
					g_mShowLangauge=ENGLISH;
					break;
		       case SYS_SUB1SUB12DEC_GEAR_ERROR: //��γ�ز�У��
								  
			        gstrlineEn1="                      ";
					gstrlineEn2=g_sysmenu111017;
					gstrlineEn3="                      ";
					gstrlineEn4=g_sysmenu111018;
					gstrlineEn5="                      ";
					gstrlineEn6=g_sysmenu11107;
					gstrlineEn7="                      ";
					gstrlineEn8=g_sysmenu11108;

//					gstrlineCn1=g_sysmenu11205;
//					gstrlineCn2=g_sysmenu11206;
//					gstrlineCn3=g_sysmenu11107;
//					gstrlineCn4=g_sysmenu11108;
					g_mShowMenurowEn=0;
				    //FSelShowLanguage();
					g_mShowLangauge=ENGLISH;
					break;
				case SYS_SUB1SUB12DEC_GEAR_ERROR_ALIGN: 		 //��γ�ز�����У��
								  
			        gstrlineEn1="                      ";
					gstrlineEn2=g_sysmenu11109;
					gstrlineEn3="                      ";
					gstrlineEn4=g_sysmenu111010;
					gstrlineEn5="                      ";
					gstrlineEn6=g_sysmenu111011;
					gstrlineEn7="                      ";
					gstrlineEn8=g_sysmenu111012;
//
//					gstrlineCn1=g_sysmenu11109;
//					gstrlineCn2=g_sysmenu111010;
//					gstrlineCn3=g_sysmenu111011;
//					gstrlineCn4=g_sysmenu111012;
					g_mShowMenurowEn=0;
				    //FSelShowLanguage();
					g_mShowLangauge=ENGLISH;
					break;
                 //���һ�γ�γ�ز�У��
    	          case SYS_SUB1SUB12DEC_GEAR_ERROR_ALIGN_OK: 
		    	    sprintf(gstrtemp1,"%.1f",g_mDecAltGearError);

		    	    gstrlineEn1="                      ";
					gstrlineEn2="                      ";
					if(g_mTelGearErrorDecAlignDirect==2)
					{
					  gstrlineEn3=g_sysmenu111013;
					 }
					if(g_mTelGearErrorDecAlignDirect==1)
					{
					  gstrlineEn3=g_sysmenu111014;
					 }
					gstrlineEn4="                      ";
					gstrlineEn5=gstrtemp1;
					gstrlineEn6="                      ";
					gstrlineEn7=g_sysmenu111015;
					gstrlineEn8="                      ";

					
//					gstrlineCn1=gstrtemp1;
//					gstrlineCn2=g_sysmenu111014;
//					gstrlineCn3=g_sysmenu111015;
//					gstrlineCn4=g_sysmenu111016;
					g_mShowMenurowEn=0;
				    //FSelShowLanguage();
					g_mShowLangauge=ENGLISH;
		
			       break;	

			  	  //��ɳ�γ�ز�У��
    	          case SYS_SUB1SUB12DEC_GEAR_ERROR_ALIGN_END: 
		    	    sprintf(gstrtemp1,"%.1f",g_mDecAltGearEvenError);
		    	    gstrlineEn1="                      ";
					gstrlineEn2="                      ";
					gstrlineEn3=g_sysmenu111016;
					gstrlineEn4="                      ";
					gstrlineEn5=gstrtemp1;
					gstrlineEn6="                      ";
					gstrlineEn7=g_sysmenu111015;
					gstrlineEn8="                      ";

//					;
//					gstrlineCn1=gstrtemp1;
//					gstrlineCn2=g_sysmenu111018;
//					gstrlineCn3=g_sysmenu111019;
//					gstrlineCn4=g_sysmenu111020;

					g_mShowMenurowEn=0;
				    //FSelShowLanguage();
					g_mShowLangauge=ENGLISH;
			       break;	
 

			//�ڶ���Ŀ�˵�
	
				case SYS_SUB2SUN_PLANET: //̫��ϵͳ����
				    GetSunSysObject(g_mSunSysObjectNum,&g_mObjRa1,&g_mObjDec1);	
					gstrlineEn1= g_sysmenu2200object_nameEn; 
//					gstrlineCn1= g_sysmenu2200object_nameCn; 
					gstrlineEn2="                      ";
//					gstrlineCn2="                      ";
//					if(g_mSunSysObjectNum==8)
//					{
//					   gstrlineEn3="Don't Point The Sun !!!";
////					   gstrlineCn3=g_sysmenu22011Cn;
//					}else
//					{
					  gstrlineEn3="                      ";
////					  gstrlineCn3=g_sysmenu22012Cn;
//					}
					gstrlineEn4="                      ";
//					gstrlineCn4="                      ";
					



				   gLocation.mLongitude=g_mGoto.m_nLongitude;
			       gLocation.mAtitude=g_mGoto.m_nAtitude;
				   gStarRAD.mRightAscension=g_mObjRa1;
				   gStarRAD.mDeclination=g_mObjDec1;
				   FCalStarAEPos(gLocation,gStarRAD,g_mGoto.m_nSysTimeType,g_mGoto.m_nNutation,&gStarAZ);



				   sprintf(gstrtemp5,"OBJ    Azi:%03d %02d %02d                ",(int)gStarAZ.mANzimuth,(int)((gStarAZ.mANzimuth-(int)gStarAZ.mANzimuth)*60),(int)(gStarAZ.mANzimuth*3600)%60);				   
				  
				   if(gStarAZ.mAtitude>=0)
				   {
				     sprintf(gstrtemp6,"Alt:+%02d %02d %02d               ",abs((int)gStarAZ.mAtitude),abs((int)((gStarAZ.mAtitude-(int)gStarAZ.mAtitude)*60)),abs((int)(gStarAZ.mAtitude*3600)%60));			
          			}
					else
					{
					 sprintf(gstrtemp6,"Alt:-%02d %02d %02d               ",abs((int)gStarAZ.mAtitude),abs((int)((gStarAZ.mAtitude-(int)gStarAZ.mAtitude)*60)),abs((int)(gStarAZ.mAtitude*3600)%60));	
          			 }
					

				   if((int)gStarAZ.mANzimuth <100)
				   {
				     gstrtemp5[11]=' ';
				   }
				   if((int)gStarAZ.mANzimuth <10)
				   {
				     gstrtemp5[12]=' ';
				   }

				   if((int)((gStarAZ.mANzimuth-(int)gStarAZ.mANzimuth)*60)<10)
				   {
				     gstrtemp5[15]=' ';
				   }

				   if(((int)(gStarAZ.mANzimuth*3600)%60)<10)
				   {
				     gstrtemp5[18]=' ';
				   }



				    if(abs((int)gStarAZ.mAtitude)<10)
				   {
				     gstrtemp6[5]=' ';
				   }

				   if(abs((int)((gStarAZ.mAtitude-(int)gStarAZ.mAtitude)*60))<10)
				   {
				     gstrtemp6[8]=' ';
				   }
				   if(abs(((int)(gStarAZ.mAtitude*3600)%60))<10)
				   {
				      gstrtemp6[11]=' ';
				   }

					gstrlineEn5=gstrtemp5;
					gstrlineEn6=gstrtemp6;

//				    gstrlineCn5=gstrtemp5;
//					gstrlineCn6=gstrtemp6;


			       sprintf(gstrtemp7,"R.a: %02dh%02dm%02ds         ",(int)g_mObjRa1,(int)((g_mObjRa1-(int)g_mObjRa1)*60),(int)(g_mObjRa1*3600)%60);	
			
				   if((int)g_mObjRa1<10)
				   {
				     gstrtemp7[5]=' ';
				   }

				   if((int)((g_mObjRa1-(int)g_mObjRa1)*60)<10)
				   {
				     gstrtemp7[8]=' ';
				   }

				   if(((int)(g_mObjRa1*3600)%60)<10)
				   {
				     gstrtemp7[11]=' ';
				   }			
					gstrlineEn7=gstrtemp7;
//					gstrlineCn7=gstrtemp7;

					 if(g_mObjDec1>=0)
					 {
			            sprintf(gstrtemp8,"Dec:+%02d %02d %02d      ",abs((int)g_mObjDec1),abs((int)((g_mObjDec1-(int)g_mObjDec1)*60)),abs((int)(g_mObjDec1*3600)%60));	
					}
					else
					{
					  sprintf(gstrtemp8,"Dec:-%02d %02d %02d        ",abs((int)g_mObjDec1),abs((int)((g_mObjDec1-(int)g_mObjDec1)*60)),abs((int)(g_mObjDec1*3600)%60));	
					}

				   	if(abs((int)g_mObjDec1)<10)
				   {
				     gstrtemp8[5]=' ';
				   }

				   if(abs((int)((g_mObjDec1-(int)g_mObjDec1)*60))<10)
				   {
				     gstrtemp8[8]=' ';
				   }
				   if(abs(((int)(g_mObjDec1*3600)%60))<10)
				   {
				      gstrtemp8[11]=' ';
				   }
				    
					gstrlineEn8=gstrtemp8;
//					gstrlineCn8=gstrtemp8;				

					g_mShowMenurowEn=0;
//					g_mShowMenurowCn=0;
					//FSelShowLanguage();	
					g_mShowLangauge=ENGLISH;
		     	break; 
			case SYS_SUB2SUN_SUNWARN:
			        gstrlineEn1="                     ";
			        gstrlineEn2="    DO NOT POINT     ";
					gstrlineEn3="the telescope or its "; 
                	gstrlineEn4="viewfinder at or near";
					gstrlineEn5="the Sun!!!           "; 
				    gstrlineEn6="                     "; 					
					gstrlineEn7="ENTER:continue       ";
					gstrlineEn8="    -:return         ";

			      	g_mShowMenurowEn=0;
//					g_mShowMenurowCn=0;
					//FSelShowLanguage();	
					g_mShowLangauge=ENGLISH;

			     break; 
			 
			case SYS_SUB2SUN_PLANET1: //̫��ϵͳ����1
				    GetSunSysObject(g_mSunSysObjectNum,&g_mObjRa1,&g_mObjDec1);	
	
				   gLocation.mLongitude=g_mGoto.m_nLongitude;
			       gLocation.mAtitude=g_mGoto.m_nAtitude;
				   gStarRAD.mRightAscension=g_mObjRa1;
				   gStarRAD.mDeclination=g_mObjDec1;
				   FCalStarAEPos(gLocation,gStarRAD,g_mGoto.m_nSysTimeType,g_mGoto.m_nNutation,&gStarAZ);



				   sprintf(gstrtemp5,"OBJ    Azi:%03d %02d %02d                ",(int)gStarAZ.mANzimuth,(int)((gStarAZ.mANzimuth-(int)gStarAZ.mANzimuth)*60),(int)(gStarAZ.mANzimuth*3600)%60);				   
				  
				   if(gStarAZ.mAtitude>=0)
				   {
				     sprintf(gstrtemp6,"Alt:+%02d %02d %02d               ",abs((int)gStarAZ.mAtitude),abs((int)((gStarAZ.mAtitude-(int)gStarAZ.mAtitude)*60)),abs((int)(gStarAZ.mAtitude*3600)%60));			
          			}
					else
					{
					 sprintf(gstrtemp6,"Alt:-%02d %02d %02d               ",abs((int)gStarAZ.mAtitude),abs((int)((gStarAZ.mAtitude-(int)gStarAZ.mAtitude)*60)),abs((int)(gStarAZ.mAtitude*3600)%60));	
          			  g_mOperateStatus=3;
					 }
					

				   if((int)gStarAZ.mANzimuth <100)
				   {
				     gstrtemp5[11]=' ';
				   }
				   if((int)gStarAZ.mANzimuth <10)
				   {
				     gstrtemp5[12]=' ';
				   }

				   if((int)((gStarAZ.mANzimuth-(int)gStarAZ.mANzimuth)*60)<10)
				   {
				     gstrtemp5[15]=' ';
				   }

				   if(((int)(gStarAZ.mANzimuth*3600)%60)<10)
				   {
				     gstrtemp5[18]=' ';
				   }



				    if(abs((int)gStarAZ.mAtitude)<10)
				   {
				     gstrtemp6[5]=' ';
				   }

				   if(abs((int)((gStarAZ.mAtitude-(int)gStarAZ.mAtitude)*60))<10)
				   {
				     gstrtemp6[8]=' ';
				   }
				   if(abs(((int)(gStarAZ.mAtitude*3600)%60))<10)
				   {
				      gstrtemp6[11]=' ';
				   }

					gstrlineEn5=gstrtemp5;
					gstrlineEn6=gstrtemp6;

//				    gstrlineCn5=gstrtemp5;
//					gstrlineCn6=gstrtemp6;

											 

					g_mTelAzi1=g_mTelAzi;
			        g_mTelAlt1=g_mTelAlt;
					if(g_mAzEq==1)
					{
						 g_teldec=g_mTelDec;
						 g_telra=FCalSiderealTime(1,false,g_mGoto.m_nLongitude)-g_mTelRa;
						 while(	g_telra>=24)
						 {
						   g_telra=g_telra-24;
						  }
						  while(g_telra<0)
						   {
						    g_telra=g_telra+24;
						   }
						   gLocation.mLongitude=g_mGoto.m_nLongitude;
					       gLocation.mAtitude=g_mGoto.m_nAtitude;
						   gTelRAD.mRightAscension=g_telra;
						   gTelRAD.mDeclination=g_teldec;
						   FCalStarAEPos(gLocation,gTelRAD,g_mGoto.m_nSysTimeType,g_mGoto.m_nNutation,&gTelAZ);
						   g_mTelAzi1=gTelAZ.mANzimuth;
						   g_mTelAlt1=gTelAZ.mAtitude;
					}


			       sprintf(gstrtemp7,"OTA    Azi:%03d %02d %02d                ",abs((int)g_mTelAzi1),abs((int)((g_mTelAzi1-(int)g_mTelAzi1)*60)),abs((int)(g_mTelAzi1*3600)%60));				   
				  
				   if(g_mTelAlt1>=0)
				   {
				     sprintf(gstrtemp8,"Alt:+%02d %02d %02d               ",abs((int)g_mTelAlt1),abs((int)((g_mTelAlt1-(int)g_mTelAlt1)*60)),abs((int)(g_mTelAlt1*3600)%60));			
          			}
					else
					{
					 sprintf(gstrtemp8,"Alt:-%02d %02d %02d               ",abs((int)g_mTelAlt1),abs((int)((g_mTelAlt1-(int)g_mTelAlt1)*60)),abs((int)(g_mTelAlt1*3600)%60));	
          			 }
			
			
					

				   if((int)g_mTelAzi1 <100)
				   {
				     gstrtemp7[11]=' ';
				   }
				   if((int)g_mTelAzi1 <10)
				   {
				     gstrtemp7[12]=' ';
				   }

				   if((int)((g_mTelAzi1-(int)g_mTelAzi1)*60)<10)
				   {
				     gstrtemp7[15]=' ';
				   }

				   if(((int)(g_mTelAzi1*3600)%60)<10)
				   {
				     gstrtemp7[18]=' ';
				   }



				    if(abs((int)g_mTelAlt1)<10)
				   {
				     gstrtemp8[5]=' ';
				   }

				   if(abs((int)((g_mTelAlt1-(int)g_mTelAlt1)*60))<10)
				   {
				     gstrtemp8[8]=' ';
				   }
				   if(abs(((int)(g_mTelAlt1*3600)%60))<10)
				   {
				      gstrtemp8[11]=' ';
				   }

					gstrlineEn7=gstrtemp7;
					gstrlineEn8=gstrtemp8;

//				    gstrlineCn7=gstrtemp7;
//					gstrlineCn8=gstrtemp8;	

					if((g_mTelStatus==1)||(g_mTelStatus==2))
					{
				
				       g_mOperateStatus=g_mTelStatus;	
					}

				   	if((gStarAZ.mAtitude<0)&&((g_mOperateStatus==1)||(g_mOperateStatus==2)))
				   {
				      g_mOperateStatus=3;
				   	}
								
	
							//��Զ������״̬			 
				    switch(g_mOperateStatus)
					{
					case 1:
						gstrlineEn1="Slewing to Target       ";
//						gstrlineCn1=g_OperateStatusCn1;
						break;
					case 2:
					    gstrlineEn1="Find Target,Tracking    ";
//						gstrlineCn1=g_OperateStatusCn2;
						break;
					case 3:
						gstrlineEn1="Target Under Horizon    ";
//						gstrlineCn1=g_OperateStatusCn3;
						g_mEQHn=true;//���ʽ��Զ��Ŀ���Ƿ��ڵ�ƽ��
						break;

					case 4:	  
					     gstrlineEn1="Pause                 ";
//						 gstrlineCn1=g_OperateStatusCn4;
					break;
					case 5:	  
					     gstrlineEn1="Cancel Operation          ";
//						 gstrlineCn1=g_OperateStatusCn5;
					break;
						
					default:
						gstrlineEn1="                              ";
						break;
					}
			
				    //sprintf(gstrtemp2,"%d",g_mTelStatus);	
				    //gstrlineEn2=gstrtemp2;							
				   	gstrlineEn2="                              ";


				    gstrlineEn3= g_sysmenu2200object_nameEn; 
//					gstrlineCn3= g_sysmenu2200object_nameCn; 


					gstrlineEn4="                              ";



					g_mShowMenurowEn=0;
//					g_mShowMenurowCn=0;
					//FSelShowLanguage();
					g_mShowLangauge=ENGLISH;	
		     	break; 


				

				   //88����
		      case  SYS_SUB2CON_OBJECT:
		           //��ȡ88�����Ǳ�����
				   GetCon88(g_mCon88ObjectNum,&con);
				   g_mObjRa1=con.Ra;
				   g_mObjDec1=con.Dec;

				   gstrlineEn1=con.ConEn;
//				   gstrlineCn1=con.ConCn;

				   gstrlineEn2="                      "; 
				   sprintf(gstrtemp3,"    Area: %d SQ.Deg               ",con.area);	
				   gstrlineEn3=gstrtemp3;
				   gstrlineEn3[0]=con.ConEn[0];
				   gstrlineEn3[1]=con.ConEn[1];
				   gstrlineEn3[2]=con.ConEn[2];
			
				                               

				   sprintf(gstrtemp4,"Quantity: %d (>6Mag)             ",con.starnum);	
				   gstrlineEn4=gstrtemp4;

				   gLocation.mLongitude=g_mGoto.m_nLongitude;
			       gLocation.mAtitude=g_mGoto.m_nAtitude;
				   	gStarRAD.mRightAscension=g_mObjRa1;
				   gStarRAD.mDeclination=g_mObjDec1;
				 
				   FCalStarAEPos(gLocation,gStarRAD,g_mGoto.m_nSysTimeType,g_mGoto.m_nNutation,&gStarAZ);



				   sprintf(gstrtemp5,"OBJ    Azi:%03d %02d %02d                ",(int)gStarAZ.mANzimuth,(int)((gStarAZ.mANzimuth-(int)gStarAZ.mANzimuth)*60),(int)(gStarAZ.mANzimuth*3600)%60);				   
				  
				   if(gStarAZ.mAtitude>=0)
				   {
				     sprintf(gstrtemp6,"Alt:+%02d %02d %02d               ",abs((int)gStarAZ.mAtitude),abs((int)((gStarAZ.mAtitude-(int)gStarAZ.mAtitude)*60)),abs((int)(gStarAZ.mAtitude*3600)%60));			
          			}
					else
					{
					 sprintf(gstrtemp6,"Alt:-%02d %02d %02d               ",abs((int)gStarAZ.mAtitude),abs((int)((gStarAZ.mAtitude-(int)gStarAZ.mAtitude)*60)),abs((int)(gStarAZ.mAtitude*3600)%60));	
          			 }
					

				   if((int)gStarAZ.mANzimuth <100)
				   {
				     gstrtemp5[11]=' ';
				   }
				   if((int)gStarAZ.mANzimuth <10)
				   {
				     gstrtemp5[12]=' ';
				   }

				   if((int)((gStarAZ.mANzimuth-(int)gStarAZ.mANzimuth)*60)<10)
				   {
				     gstrtemp5[15]=' ';
				   }

				   if(((int)(gStarAZ.mANzimuth*3600)%60)<10)
				   {
				     gstrtemp5[18]=' ';
				   }



				    if(abs((int)gStarAZ.mAtitude)<10)
				   {
				     gstrtemp6[5]=' ';
				   }

				   if(abs((int)((gStarAZ.mAtitude-(int)gStarAZ.mAtitude)*60))<10)
				   {
				     gstrtemp6[8]=' ';
				   }
				   if(abs(((int)(gStarAZ.mAtitude*3600)%60))<10)
				   {
				      gstrtemp6[11]=' ';
				   }

					gstrlineEn5=gstrtemp5;
					gstrlineEn6=gstrtemp6;

//				    gstrlineCn5=gstrtemp5;
//					gstrlineCn6=gstrtemp6;


			       sprintf(gstrtemp7,"R.a: %02dh%02dm%02ds         ",(int)g_mObjRa1,(int)((g_mObjRa1-(int)g_mObjRa1)*60),(int)(g_mObjRa1*3600)%60);	
			
				   if((int)g_mObjRa1<10)
				   {
				     gstrtemp7[5]=' ';
				   }

				   if((int)((g_mObjRa1-(int)g_mObjRa1)*60)<10)
				   {
				     gstrtemp7[8]=' ';
				   }

				   if(((int)(g_mObjRa1*3600)%60)<10)
				   {
				     gstrtemp7[11]=' ';
				   }			
					gstrlineEn7=gstrtemp7;
//					gstrlineCn7=gstrtemp7;

					 if(g_mObjDec1>=0)
					 {
			            sprintf(gstrtemp8,"Dec:+%02d %02d %02d      ",abs((int)g_mObjDec1),abs((int)((g_mObjDec1-(int)g_mObjDec1)*60)),abs((int)(g_mObjDec1*3600)%60));	
					}
					else
					{
					  sprintf(gstrtemp8,"Dec:-%02d %02d %02d        ",abs((int)g_mObjDec1),abs((int)((g_mObjDec1-(int)g_mObjDec1)*60)),abs((int)(g_mObjDec1*3600)%60));	
					}

				   	if(abs((int)g_mObjDec1)<10)
				   {
				     gstrtemp8[5]=' ';
				   }

				   if(abs((int)((g_mObjDec1-(int)g_mObjDec1)*60))<10)
				   {
				     gstrtemp8[8]=' ';
				   }
				   if(abs(((int)(g_mObjDec1*3600)%60))<10)
				   {
				      gstrtemp8[11]=' ';
				   }
				    
					gstrlineEn8=gstrtemp8;
//					gstrlineCn8=gstrtemp8;				

				    g_mShowMenurowEn=0;
//					g_mShowMenurowCn=0;
					//FSelShowLanguage();	
					g_mShowLangauge=ENGLISH;

			    break;

					      //88����1
		      case  SYS_SUB2CON_OBJECT1:
			       GetCon88(g_mCon88ObjectNum,&con);
				   g_mObjRa1=con.Ra;
				   g_mObjDec1=con.Dec;

				 
			      
			       gLocation.mLongitude=g_mGoto.m_nLongitude;
			       gLocation.mAtitude=g_mGoto.m_nAtitude;
				   gStarRAD.mRightAscension=g_mObjRa1;
				   gStarRAD.mDeclination=g_mObjDec1;
				   FCalStarAEPos(gLocation,gStarRAD,g_mGoto.m_nSysTimeType,g_mGoto.m_nNutation,&gStarAZ);



				   sprintf(gstrtemp5,"OBJ    Azi:%03d %02d %02d                ",(int)gStarAZ.mANzimuth,(int)((gStarAZ.mANzimuth-(int)gStarAZ.mANzimuth)*60),(int)(gStarAZ.mANzimuth*3600)%60);				   
				  
				   if(gStarAZ.mAtitude>=0)
				   {
				     sprintf(gstrtemp6,"Alt:+%02d %02d %02d               ",abs((int)gStarAZ.mAtitude),abs((int)((gStarAZ.mAtitude-(int)gStarAZ.mAtitude)*60)),abs((int)(gStarAZ.mAtitude*3600)%60));			
          			}
					else
					{
					 sprintf(gstrtemp6,"Alt:-%02d %02d %02d               ",abs((int)gStarAZ.mAtitude),abs((int)((gStarAZ.mAtitude-(int)gStarAZ.mAtitude)*60)),abs((int)(gStarAZ.mAtitude*3600)%60));	
          			  g_mOperateStatus=3;
					 }
					

				   if((int)gStarAZ.mANzimuth <100)
				   {
				     gstrtemp5[11]=' ';
				   }
				   if((int)gStarAZ.mANzimuth <10)
				   {
				     gstrtemp5[12]=' ';
				   }

				   if((int)((gStarAZ.mANzimuth-(int)gStarAZ.mANzimuth)*60)<10)
				   {
				     gstrtemp5[15]=' ';
				   }

				   if(((int)(gStarAZ.mANzimuth*3600)%60)<10)
				   {
				     gstrtemp5[18]=' ';
				   }



				    if(abs((int)gStarAZ.mAtitude)<10)
				   {
				     gstrtemp6[5]=' ';
				   }

				   if(abs((int)((gStarAZ.mAtitude-(int)gStarAZ.mAtitude)*60))<10)
				   {
				     gstrtemp6[8]=' ';
				   }
				   if(abs(((int)(gStarAZ.mAtitude*3600)%60))<10)
				   {
				      gstrtemp6[11]=' ';
				   }

					gstrlineEn5=gstrtemp5;
					gstrlineEn6=gstrtemp6;

//				    gstrlineCn5=gstrtemp5;
//					gstrlineCn6=gstrtemp6;



					g_mTelAzi1=g_mTelAzi;
			        g_mTelAlt1=g_mTelAlt;  

					if(g_mAzEq==1)
					{
						 g_teldec=g_mTelDec;
						 g_telra=FCalSiderealTime(1,false,g_mGoto.m_nLongitude)-g_mTelRa;
						 while(	g_telra>=24)
						 {
						   g_telra=g_telra-24;
						  }
						  while(g_telra<0)
						   {
						    g_telra=g_telra+24;
						   }
						   gLocation.mLongitude=g_mGoto.m_nLongitude;
					       gLocation.mAtitude=g_mGoto.m_nAtitude;
						   gTelRAD.mRightAscension=g_telra;
						   gTelRAD.mDeclination=g_teldec;
						   FCalStarAEPos(gLocation,gTelRAD,g_mGoto.m_nSysTimeType,g_mGoto.m_nNutation,&gTelAZ);
						   g_mTelAzi1=gTelAZ.mANzimuth;
						   g_mTelAlt1=gTelAZ.mAtitude;
					}



			      sprintf(gstrtemp7,"OTA    Azi:%03d %02d %02d                ",abs((int)g_mTelAzi1),abs((int)((g_mTelAzi1-(int)g_mTelAzi1)*60)),abs((int)(g_mTelAzi1*3600)%60));			   
				  
				   if(g_mTelAlt1>=0)
				   {
				     sprintf(gstrtemp8,"Alt:+%02d %02d %02d               ",abs((int)g_mTelAlt1),abs((int)((g_mTelAlt1-(int)g_mTelAlt1)*60)),abs((int)(g_mTelAlt1*3600)%60));			
          			}
					else
					{
					 sprintf(gstrtemp8,"Alt:-%02d %02d %02d               ",abs((int)g_mTelAlt1),abs((int)((g_mTelAlt1-(int)g_mTelAlt1)*60)),abs((int)(g_mTelAlt1*3600)%60));	
          			 }
					

				   if((int)g_mTelAzi1 <100)
				   {
				     gstrtemp7[11]=' ';
				   }
				   if((int)g_mTelAzi1 <10)
				   {
				     gstrtemp7[12]=' ';
				   }

				   if((int)((g_mTelAzi1-(int)g_mTelAzi1)*60)<10)
				   {
				     gstrtemp7[15]=' ';
				   }

				   if(((int)(g_mTelAzi1*3600)%60)<10)
				   {
				     gstrtemp7[18]=' ';
				   }



				    if(abs((int)g_mTelAlt1)<10)
				   {
				     gstrtemp8[5]=' ';
				   }

				   if(abs((int)((g_mTelAlt1-(int)g_mTelAlt1)*60))<10)
				   {
				     gstrtemp8[8]=' ';
				   }
				   if(abs(((int)(g_mTelAlt1*3600)%60))<10)
				   {
				      gstrtemp8[11]=' ';
				   }

					gstrlineEn7=gstrtemp7;
					gstrlineEn8=gstrtemp8;

//				    gstrlineCn7=gstrtemp7;
//					gstrlineCn8=gstrtemp8;	

					if((g_mTelStatus==1)||(g_mTelStatus==2))
					{
					  g_mOperateStatus=g_mTelStatus;
					}

				   	if((gStarAZ.mAtitude<0)&&((g_mOperateStatus==1)||(g_mOperateStatus==2)))
				   {
				     g_mOperateStatus=3;
				   	}
								
	
							//��Զ������״̬			 
				    switch(g_mOperateStatus)
					{
					case 1:
						gstrlineEn1="Slewing to Target       ";
//						gstrlineCn1=g_OperateStatusCn1;
						break;
					case 2:
					    gstrlineEn1="Find Target,Tracking    ";
//						gstrlineCn1=g_OperateStatusCn2;
						break;
					case 3:
						gstrlineEn1="Target Under Horizon    ";
//						gstrlineCn1=g_OperateStatusCn3;
						g_mEQHn=true;//���ʽ��Զ��Ŀ���Ƿ��ڵ�ƽ��
						break;

					case 4:	  
					     gstrlineEn1="Pause                 ";
//						 gstrlineCn1=g_OperateStatusCn4;
					break;
					case 5:	  
					     gstrlineEn1="Cancel Operation          ";
//						 gstrlineCn1=g_OperateStatusCn5;
					break;
						
					default:
						gstrlineEn1="                              ";
						break;
					}
			
				    //sprintf(gstrtemp2,"%d",g_mOperateStatus);	
				    //gstrlineEn2=gstrtemp2;
				   	gstrlineEn2="                              ";


				    gstrlineEn3=con.ConEn;
//				    gstrlineCn3=con.ConCn;


					gstrlineEn4="                              ";
					g_mShowMenurowEn=0;
//					g_mShowMenurowCn=0;
					//FSelShowLanguage();	
			       g_mShowLangauge=ENGLISH;
			  break;


			  //�������ǣ�Ҳ����У׼��)
		      case  SYS_SUB2FS_OBJECT:
		       //��ȡ�����Ǳ�����
			   GetAlignStar(g_mFamousStarObjectNum,&AlnStar);
			   g_mObjRa1=AlnStar.Ra;
			   g_mObjDec1=AlnStar.Dec;
			   gstrlineEn1=AlnStar.ConEn;
//			   gstrlineCn1=AlnStar.ConCn;

			   gstrlineEn2="                                        ";
			   gstrlineEn3=AlnStar.NameEn;
//			   gstrlineCn3=AlnStar.NameCn;
			   sprintf(gstrtemp4,"SAO:%d  MEG:%.1f",AlnStar.SaoNo,AlnStar.Bright);	
			   gstrlineEn4=gstrtemp4;



			   	   gLocation.mLongitude=g_mGoto.m_nLongitude;
			       gLocation.mAtitude=g_mGoto.m_nAtitude;
				   	gStarRAD.mRightAscension=g_mObjRa1;
				   gStarRAD.mDeclination=g_mObjDec1;
				 
				   FCalStarAEPos(gLocation,gStarRAD,g_mGoto.m_nSysTimeType,g_mGoto.m_nNutation,&gStarAZ);



				   sprintf(gstrtemp5,"OBJ    Azi:%03d %02d %02d                ",(int)gStarAZ.mANzimuth,(int)((gStarAZ.mANzimuth-(int)gStarAZ.mANzimuth)*60),(int)(gStarAZ.mANzimuth*3600)%60);				   
				  
				   if(gStarAZ.mAtitude>=0)
				   {
				     sprintf(gstrtemp6,"Alt:+%02d %02d %02d               ",abs((int)gStarAZ.mAtitude),abs((int)((gStarAZ.mAtitude-(int)gStarAZ.mAtitude)*60)),abs((int)(gStarAZ.mAtitude*3600)%60));			
          			}
					else
					{
					 sprintf(gstrtemp6,"Alt:-%02d %02d %02d               ",abs((int)gStarAZ.mAtitude),abs((int)((gStarAZ.mAtitude-(int)gStarAZ.mAtitude)*60)),abs((int)(gStarAZ.mAtitude*3600)%60));	
          			 }
					

				   if((int)gStarAZ.mANzimuth <100)
				   {
				     gstrtemp5[11]=' ';
				   }
				   if((int)gStarAZ.mANzimuth <10)
				   {
				     gstrtemp5[12]=' ';
				   }

				   if((int)((gStarAZ.mANzimuth-(int)gStarAZ.mANzimuth)*60)<10)
				   {
				     gstrtemp5[15]=' ';
				   }

				   if(((int)(gStarAZ.mANzimuth*3600)%60)<10)
				   {
				     gstrtemp5[18]=' ';
				   }



				    if(abs((int)gStarAZ.mAtitude)<10)
				   {
				     gstrtemp6[5]=' ';
				   }

				   if(abs((int)((gStarAZ.mAtitude-(int)gStarAZ.mAtitude)*60))<10)
				   {
				     gstrtemp6[8]=' ';
				   }
				   if(abs(((int)(gStarAZ.mAtitude*3600)%60))<10)
				   {
				      gstrtemp6[11]=' ';
				   }

					gstrlineEn5=gstrtemp5;
					gstrlineEn6=gstrtemp6;

//				    gstrlineCn5=gstrtemp5;
//					gstrlineCn6=gstrtemp6;


			       sprintf(gstrtemp7,"R.a: %02dh%02dm%02ds         ",(int)g_mObjRa1,(int)((g_mObjRa1-(int)g_mObjRa1)*60),(int)(g_mObjRa1*3600)%60);	
			
				   if((int)g_mObjRa1<10)
				   {
				     gstrtemp7[5]=' ';
				   }

				   if((int)((g_mObjRa1-(int)g_mObjRa1)*60)<10)
				   {
				     gstrtemp7[8]=' ';
				   }

				   if(((int)(g_mObjRa1*3600)%60)<10)
				   {
				     gstrtemp7[11]=' ';
				   }			
					gstrlineEn7=gstrtemp7;
//					gstrlineCn7=gstrtemp7;

					 if(g_mObjDec1>=0)
					 {
			            sprintf(gstrtemp8,"Dec:+%02d %02d %02d      ",abs((int)g_mObjDec1),abs((int)((g_mObjDec1-(int)g_mObjDec1)*60)),abs((int)(g_mObjDec1*3600)%60));	
					}
					else
					{
					  sprintf(gstrtemp8,"Dec:-%02d %02d %02d        ",abs((int)g_mObjDec1),abs((int)((g_mObjDec1-(int)g_mObjDec1)*60)),abs((int)(g_mObjDec1*3600)%60));	
					}

				   	if(abs((int)g_mObjDec1)<10)
				   {
				     gstrtemp8[5]=' ';
				   }

				   if(abs((int)((g_mObjDec1-(int)g_mObjDec1)*60))<10)
				   {
				     gstrtemp8[8]=' ';
				   }
				   if(abs(((int)(g_mObjDec1*3600)%60))<10)
				   {
				      gstrtemp8[11]=' ';
				   }
				    
					gstrlineEn8=gstrtemp8;
//					gstrlineCn8=gstrtemp8;				

				    g_mShowMenurowEn=0;
//					g_mShowMenurowCn=0;
					//FSelShowLanguage();
					g_mShowLangauge=ENGLISH;
		  	   
			    break;

		   //�������ǣ�Ҳ����У׼��)1
		       case  SYS_SUB2FS_OBJECT1:
			   GetAlignStar(g_mFamousStarObjectNum,&AlnStar);
			   g_mObjRa1=AlnStar.Ra;
			   g_mObjDec1=AlnStar.Dec;
			  

			      
			       gLocation.mLongitude=g_mGoto.m_nLongitude;
			       gLocation.mAtitude=g_mGoto.m_nAtitude;
				   gStarRAD.mRightAscension=g_mObjRa1;
				   gStarRAD.mDeclination=g_mObjDec1;
				   FCalStarAEPos(gLocation,gStarRAD,g_mGoto.m_nSysTimeType,g_mGoto.m_nNutation,&gStarAZ);



				   sprintf(gstrtemp5,"OBJ    Azi:%03d %02d %02d                ",(int)gStarAZ.mANzimuth,(int)((gStarAZ.mANzimuth-(int)gStarAZ.mANzimuth)*60),(int)(gStarAZ.mANzimuth*3600)%60);				   
				  
				   if(gStarAZ.mAtitude>=0)
				   {
				     sprintf(gstrtemp6,"Alt:+%02d %02d %02d               ",abs((int)gStarAZ.mAtitude),abs((int)((gStarAZ.mAtitude-(int)gStarAZ.mAtitude)*60)),abs((int)(gStarAZ.mAtitude*3600)%60));			
          			}
					else
					{
					 sprintf(gstrtemp6,"Alt:-%02d %02d %02d               ",abs((int)gStarAZ.mAtitude),abs((int)((gStarAZ.mAtitude-(int)gStarAZ.mAtitude)*60)),abs((int)(gStarAZ.mAtitude*3600)%60));	
          			  g_mOperateStatus=3;
					 }
					

				   if((int)gStarAZ.mANzimuth <100)
				   {
				     gstrtemp5[11]=' ';
				   }
				   if((int)gStarAZ.mANzimuth <10)
				   {
				     gstrtemp5[12]=' ';
				   }

				   if((int)((gStarAZ.mANzimuth-(int)gStarAZ.mANzimuth)*60)<10)
				   {
				     gstrtemp5[15]=' ';
				   }

				   if(((int)(gStarAZ.mANzimuth*3600)%60)<10)
				   {
				     gstrtemp5[18]=' ';
				   }



				    if(abs((int)gStarAZ.mAtitude)<10)
				   {
				     gstrtemp6[5]=' ';
				   }

				   if(abs((int)((gStarAZ.mAtitude-(int)gStarAZ.mAtitude)*60))<10)
				   {
				     gstrtemp6[8]=' ';
				   }
				   if(abs(((int)(gStarAZ.mAtitude*3600)%60))<10)
				   {
				      gstrtemp6[11]=' ';
				   }

					gstrlineEn5=gstrtemp5;
					gstrlineEn6=gstrtemp6;

//				    gstrlineCn5=gstrtemp5;
//					gstrlineCn6=gstrtemp6;



					g_mTelAzi1=g_mTelAzi;
			        g_mTelAlt1=g_mTelAlt;
						if(g_mAzEq==1)
					{
						 g_teldec=g_mTelDec;
						 g_telra=FCalSiderealTime(1,false,g_mGoto.m_nLongitude)-g_mTelRa;
						 while(	g_telra>=24)
						 {
						   g_telra=g_telra-24;
						  }
						  while(g_telra<0)
						   {
						    g_telra=g_telra+24;
						   }
						   gLocation.mLongitude=g_mGoto.m_nLongitude;
					       gLocation.mAtitude=g_mGoto.m_nAtitude;
						   gTelRAD.mRightAscension=g_telra;
						   gTelRAD.mDeclination=g_teldec;
						   FCalStarAEPos(gLocation,gTelRAD,g_mGoto.m_nSysTimeType,g_mGoto.m_nNutation,&gTelAZ);
						   g_mTelAzi1=gTelAZ.mANzimuth;
						   g_mTelAlt1=gTelAZ.mAtitude;
					}


			       sprintf(gstrtemp7,"OTA    Azi:%03d %02d %02d                ",abs((int)g_mTelAzi1),abs((int)((g_mTelAzi1-(int)g_mTelAzi1)*60)),abs((int)(g_mTelAzi1*3600)%60));	  
				   if(g_mTelAlt1>=0)
				   {
				     sprintf(gstrtemp8,"Alt:+%02d %02d %02d               ",abs((int)g_mTelAlt1),abs((int)((g_mTelAlt1-(int)g_mTelAlt1)*60)),abs((int)(g_mTelAlt1*3600)%60));			
          			}
					else
					{
					 sprintf(gstrtemp8,"Alt:-%02d %02d %02d               ",abs((int)g_mTelAlt1),abs((int)((g_mTelAlt1-(int)g_mTelAlt1)*60)),abs((int)(g_mTelAlt1*3600)%60));	
          			 }
					

				   if((int)g_mTelAzi1 <100)
				   {
				     gstrtemp7[11]=' ';
				   }
				   if((int)g_mTelAzi1 <10)
				   {
				     gstrtemp7[12]=' ';
				   }

				   if((int)((g_mTelAzi1-(int)g_mTelAzi1)*60)<10)
				   {
				     gstrtemp7[15]=' ';
				   }

				   if(((int)(g_mTelAzi1*3600)%60)<10)
				   {
				     gstrtemp7[18]=' ';
				   }



				    if(abs((int)g_mTelAlt1)<10)
				   {
				     gstrtemp8[5]=' ';
				   }

				   if(abs((int)((g_mTelAlt1-(int)g_mTelAlt1)*60))<10)
				   {
				     gstrtemp8[8]=' ';
				   }
				   if(abs(((int)(g_mTelAlt1*3600)%60))<10)
				   {
				      gstrtemp8[11]=' ';
				   }

					gstrlineEn7=gstrtemp7;
					gstrlineEn8=gstrtemp8;

//				    gstrlineCn7=gstrtemp7;
//					gstrlineCn8=gstrtemp8;	

					if((g_mTelStatus==1)||(g_mTelStatus==2))
					{
					  g_mOperateStatus=g_mTelStatus;
					}

				   	if((gStarAZ.mAtitude<0)&&((g_mOperateStatus==1)||(g_mOperateStatus==2)))
				   {
				     g_mOperateStatus=3;
				   	}
								
	
							//��Զ������״̬			 
				    switch(g_mOperateStatus)
					{
					case 1:
						gstrlineEn1="Slewing to Target       ";
//						gstrlineCn1=g_OperateStatusCn1;
						break;
					case 2:
					    gstrlineEn1="Find Target,Tracking    ";
//						gstrlineCn1=g_OperateStatusCn2;
						break;
					case 3:
						gstrlineEn1="Target Under Horizon    ";
//						gstrlineCn1=g_OperateStatusCn3;
						g_mEQHn=true;//���ʽ��Զ��Ŀ���Ƿ��ڵ�ƽ��
						break;

					case 4:	  
					     gstrlineEn1="Pause                 ";
//						 gstrlineCn1=g_OperateStatusCn4;
					break;
					case 5:	  
					     gstrlineEn1="Cancel Operation          ";
//						 gstrlineCn1=g_OperateStatusCn5;
					break;
						
					default:
						gstrlineEn1="                              ";
						break;
					}
			

			     sprintf(gstrtemp2,"Sao:%d                  ",AlnStar.SaoNo);	
			     gstrlineEn2=gstrtemp2;
//			     gstrlineCn2=gstrtemp2;

			
			 
				 gstrlineEn3="                                        ";
			  
			  	 gstrlineEn4=AlnStar.NameEn;
//			     gstrlineCn4=AlnStar.NameCn;


					g_mShowMenurowEn=0;
//					g_mShowMenurowCn=0;
					//FSelShowLanguage();	
			       	g_mShowLangauge=ENGLISH;
			  break;
				//messier�Ǳ�
		 case  SYS_SUB2MSR_OBJECT0:
		       GetMessier110(g_mMsrObjectNum,&messier);

    		   sprintf(gstrtemp1,"Messier:%d   NGC:%d                   ",g_mMsrObjectNum,messier.NGCNo);	
			   gstrlineEn1=gstrtemp1;
//			   gstrlineCn1=gstrtemp1;


			   gstrlineEn2=messier.ConEn;
//			   gstrlineCn2=messier.ConCn;

			   gstrlineEn3=messier.TypeEn;
//			   gstrlineCn3=messier.TypeCn;

			    gstrlineEn4=messier.NameEn;
//			   gstrlineCn4=messier.NameCn;


			   gstrlineEn5="                                                   ";
//			   gstrlineCn5="                                                   ";

			   sprintf(gstrtemp6,"Size:%.1f Arc Minute                  ",messier.view);	
			   gstrlineEn6=gstrtemp6;
//			   gstrlineCn6=gstrtemp6;

			    sprintf(gstrtemp7,"Distance:%.1f                         ",messier.dis);	
			   gstrlineEn7=gstrtemp7;
//			   gstrlineCn7=gstrtemp7;

			    gstrlineEn8="         K Light-Years";
//			    gstrlineCn8="          K Light-Years";


				g_mShowMenurowEn=0;
//				g_mShowMenurowCn=0;
				//FSelShowLanguage();
		  	   	g_mShowLangauge=ENGLISH;
			    break;   
				
                

				
		//messier�Ǳ�
		 case  SYS_SUB2MSR_OBJECT:
		       GetMessier110(g_mMsrObjectNum,&messier);
			   g_mObjRa1=messier.Ra;
			   g_mObjDec1=messier.Dec;

			   sprintf(gstrtemp1,"Messier:%d                        ",g_mMsrObjectNum);	
			   gstrlineEn1=gstrtemp1;
//			   gstrlineCn1=gstrtemp1;

			   gstrlineEn2=messier.ConEn;
//			   gstrlineCn2=messier.ConCn;

			   gstrlineEn3=messier.TypeEn;
//			   gstrlineCn3=messier.TypeCn;

			    gstrlineEn4="                                                ";



			   	   gLocation.mLongitude=g_mGoto.m_nLongitude;
			       gLocation.mAtitude=g_mGoto.m_nAtitude;
				   	gStarRAD.mRightAscension=g_mObjRa1;
				   gStarRAD.mDeclination=g_mObjDec1;
				 
				   FCalStarAEPos(gLocation,gStarRAD,g_mGoto.m_nSysTimeType,g_mGoto.m_nNutation,&gStarAZ);



				   sprintf(gstrtemp5,"OBJ    Azi:%03d %02d %02d                ",(int)gStarAZ.mANzimuth,(int)((gStarAZ.mANzimuth-(int)gStarAZ.mANzimuth)*60),(int)(gStarAZ.mANzimuth*3600)%60);				   
				  
				   if(gStarAZ.mAtitude>=0)
				   {
				     sprintf(gstrtemp6,"Alt:+%02d %02d %02d               ",abs((int)gStarAZ.mAtitude),abs((int)((gStarAZ.mAtitude-(int)gStarAZ.mAtitude)*60)),abs((int)(gStarAZ.mAtitude*3600)%60));			
          			}
					else
					{
					 sprintf(gstrtemp6,"Alt:-%02d %02d %02d               ",abs((int)gStarAZ.mAtitude),abs((int)((gStarAZ.mAtitude-(int)gStarAZ.mAtitude)*60)),abs((int)(gStarAZ.mAtitude*3600)%60));	
          			 }
					

				   if((int)gStarAZ.mANzimuth <100)
				   {
				     gstrtemp5[11]=' ';
				   }
				   if((int)gStarAZ.mANzimuth <10)
				   {
				     gstrtemp5[12]=' ';
				   }

				   if((int)((gStarAZ.mANzimuth-(int)gStarAZ.mANzimuth)*60)<10)
				   {
				     gstrtemp5[15]=' ';
				   }

				   if(((int)(gStarAZ.mANzimuth*3600)%60)<10)
				   {
				     gstrtemp5[18]=' ';
				   }



				    if(abs((int)gStarAZ.mAtitude)<10)
				   {
				     gstrtemp6[5]=' ';
				   }

				   if(abs((int)((gStarAZ.mAtitude-(int)gStarAZ.mAtitude)*60))<10)
				   {
				     gstrtemp6[8]=' ';
				   }
				   if(abs(((int)(gStarAZ.mAtitude*3600)%60))<10)
				   {
				      gstrtemp6[11]=' ';
				   }

					gstrlineEn5=gstrtemp5;
					gstrlineEn6=gstrtemp6;

//				    gstrlineCn5=gstrtemp5;
//					gstrlineCn6=gstrtemp6;


			       sprintf(gstrtemp7,"R.a: %02dh%02dm%02ds         ",(int)g_mObjRa1,(int)((g_mObjRa1-(int)g_mObjRa1)*60),(int)(g_mObjRa1*3600)%60);	
			
				   if((int)g_mObjRa1<10)
				   {
				     gstrtemp7[5]=' ';
				   }

				   if((int)((g_mObjRa1-(int)g_mObjRa1)*60)<10)
				   {
				     gstrtemp7[8]=' ';
				   }

				   if(((int)(g_mObjRa1*3600)%60)<10)
				   {
				     gstrtemp7[11]=' ';
				   }			
					gstrlineEn7=gstrtemp7;
//					gstrlineCn7=gstrtemp7;

					 if(g_mObjDec1>=0)
					 {
			            sprintf(gstrtemp8,"Dec:+%02d %02d %02d      ",abs((int)g_mObjDec1),abs((int)((g_mObjDec1-(int)g_mObjDec1)*60)),abs((int)(g_mObjDec1*3600)%60));	
					}
					else
					{
					  sprintf(gstrtemp8,"Dec:-%02d %02d %02d        ",abs((int)g_mObjDec1),abs((int)((g_mObjDec1-(int)g_mObjDec1)*60)),abs((int)(g_mObjDec1*3600)%60));	
					}

				   	if(abs((int)g_mObjDec1)<10)
				   {
				     gstrtemp8[5]=' ';
				   }

				   if(abs((int)((g_mObjDec1-(int)g_mObjDec1)*60))<10)
				   {
				     gstrtemp8[8]=' ';
				   }
				   if(abs(((int)(g_mObjDec1*3600)%60))<10)
				   {
				      gstrtemp8[11]=' ';
				   }
				    
					gstrlineEn8=gstrtemp8;
//					gstrlineCn8=gstrtemp8;				

				    g_mShowMenurowEn=0;
//					g_mShowMenurowCn=0;
					//FSelShowLanguage();
					g_mShowLangauge=ENGLISH;
			break;

			//messier�Ǳ�1
		 case  SYS_SUB2MSR_OBJECT1:
		      GetMessier110(g_mMsrObjectNum,&messier);
			   g_mObjRa1=messier.Ra;
			   g_mObjDec1=messier.Dec;

			   

			      
			       gLocation.mLongitude=g_mGoto.m_nLongitude;
			       gLocation.mAtitude=g_mGoto.m_nAtitude;
				   gStarRAD.mRightAscension=g_mObjRa1;
				   gStarRAD.mDeclination=g_mObjDec1;
				   FCalStarAEPos(gLocation,gStarRAD,g_mGoto.m_nSysTimeType,g_mGoto.m_nNutation,&gStarAZ);



				   sprintf(gstrtemp5,"OBJ    Azi:%03d %02d %02d                ",(int)gStarAZ.mANzimuth,(int)((gStarAZ.mANzimuth-(int)gStarAZ.mANzimuth)*60),(int)(gStarAZ.mANzimuth*3600)%60);				   
				  
				   if(gStarAZ.mAtitude>=0)
				   {
				     sprintf(gstrtemp6,"Alt:+%02d %02d %02d               ",abs((int)gStarAZ.mAtitude),abs((int)((gStarAZ.mAtitude-(int)gStarAZ.mAtitude)*60)),abs((int)(gStarAZ.mAtitude*3600)%60));			
          			}
					else
					{
					 sprintf(gstrtemp6,"Alt:-%02d %02d %02d               ",abs((int)gStarAZ.mAtitude),abs((int)((gStarAZ.mAtitude-(int)gStarAZ.mAtitude)*60)),abs((int)(gStarAZ.mAtitude*3600)%60));	
          			  g_mOperateStatus=3;
					 }
					

				   if((int)gStarAZ.mANzimuth <100)
				   {
				     gstrtemp5[11]=' ';
				   }
				   if((int)gStarAZ.mANzimuth <10)
				   {
				     gstrtemp5[12]=' ';
				   }

				   if((int)((gStarAZ.mANzimuth-(int)gStarAZ.mANzimuth)*60)<10)
				   {
				     gstrtemp5[15]=' ';
				   }

				   if(((int)(gStarAZ.mANzimuth*3600)%60)<10)
				   {
				     gstrtemp5[18]=' ';
				   }



				    if(abs((int)gStarAZ.mAtitude)<10)
				   {
				     gstrtemp6[5]=' ';
				   }

				   if(abs((int)((gStarAZ.mAtitude-(int)gStarAZ.mAtitude)*60))<10)
				   {
				     gstrtemp6[8]=' ';
				   }
				   if(abs(((int)(gStarAZ.mAtitude*3600)%60))<10)
				   {
				      gstrtemp6[11]=' ';
				   }

					gstrlineEn5=gstrtemp5;
					gstrlineEn6=gstrtemp6;

//				    gstrlineCn5=gstrtemp5;
//					gstrlineCn6=gstrtemp6;



					g_mTelAzi1=g_mTelAzi;
			        g_mTelAlt1=g_mTelAlt;
						if(g_mAzEq==1)
					{
						 g_teldec=g_mTelDec;
						 g_telra=FCalSiderealTime(1,false,g_mGoto.m_nLongitude)-g_mTelRa;
						 while(	g_telra>=24)
						 {
						   g_telra=g_telra-24;
						  }
						  while(g_telra<0)
						   {
						    g_telra=g_telra+24;
						   }
						   gLocation.mLongitude=g_mGoto.m_nLongitude;
					       gLocation.mAtitude=g_mGoto.m_nAtitude;
						   gTelRAD.mRightAscension=g_telra;
						   gTelRAD.mDeclination=g_teldec;
						   FCalStarAEPos(gLocation,gTelRAD,g_mGoto.m_nSysTimeType,g_mGoto.m_nNutation,&gTelAZ);
						   g_mTelAzi1=gTelAZ.mANzimuth;
						   g_mTelAlt1=gTelAZ.mAtitude;
					}


			      
				  sprintf(gstrtemp7,"OTA    Azi:%03d %02d %02d                ",abs((int)g_mTelAzi1),abs((int)((g_mTelAzi1-(int)g_mTelAzi1)*60)),abs((int)(g_mTelAzi1*3600)%60));	  
				   if(g_mTelAlt1>=0)
				   {
				     sprintf(gstrtemp8,"Alt:+%02d %02d %02d               ",abs((int)g_mTelAlt1),abs((int)((g_mTelAlt1-(int)g_mTelAlt1)*60)),abs((int)(g_mTelAlt1*3600)%60));			
          			}
					else
					{
					 sprintf(gstrtemp8,"Alt:-%02d %02d %02d               ",abs((int)g_mTelAlt1),abs((int)((g_mTelAlt1-(int)g_mTelAlt1)*60)),abs((int)(g_mTelAlt1*3600)%60));	
          			 }
					

				   if((int)g_mTelAzi1 <100)
				   {
				     gstrtemp7[11]=' ';
				   }
				   if((int)g_mTelAzi1 <10)
				   {
				     gstrtemp7[12]=' ';
				   }

				   if((int)((g_mTelAzi1-(int)g_mTelAzi1)*60)<10)
				   {
				     gstrtemp7[15]=' ';
				   }

				   if(((int)(g_mTelAzi1*3600)%60)<10)
				   {
				     gstrtemp7[18]=' ';
				   }



				    if(abs((int)g_mTelAlt1)<10)
				   {
				     gstrtemp8[5]=' ';
				   }

				   if(abs((int)((g_mTelAlt1-(int)g_mTelAlt1)*60))<10)
				   {
				     gstrtemp8[8]=' ';
				   }
				   if(abs(((int)(g_mTelAlt1*3600)%60))<10)
				   {
				      gstrtemp8[11]=' ';
				   }

					gstrlineEn7=gstrtemp7;
					gstrlineEn8=gstrtemp8;

//				    gstrlineCn7=gstrtemp7;
//					gstrlineCn8=gstrtemp8;	

					if((g_mTelStatus==1)||(g_mTelStatus==2))
					{
					  g_mOperateStatus=g_mTelStatus;
					}

				   	if((gStarAZ.mAtitude<0)&&((g_mOperateStatus==1)||(g_mOperateStatus==2)))
				   {
				     g_mOperateStatus=3;
				   	}
								
	
							//��Զ������״̬			 
				    switch(g_mOperateStatus)
					{
					case 1:
						gstrlineEn1="Slewing to Target       ";
//						gstrlineCn1=g_OperateStatusCn1;
						break;
					case 2:
					    gstrlineEn1="Find Target,Tracking    ";
//						gstrlineCn1=g_OperateStatusCn2;
						g_mEQHn=true;//���ʽ��Զ��Ŀ���Ƿ��ڵ�ƽ��
						break;
					case 3:
						gstrlineEn1="Target Under Horizon    ";
//						gstrlineCn1=g_OperateStatusCn3;
						break;

					case 4:	  
					     gstrlineEn1="Pause                 ";
//						 gstrlineCn1=g_OperateStatusCn4;
					break;
					case 5:	  
					     gstrlineEn1="Cancel Operation          ";
//						 gstrlineCn1=g_OperateStatusCn5;
					break;
						
					default:
						gstrlineEn1="                              ";
						break;
					}
			
			   sprintf(gstrtemp2,"Messier:%d                        ",g_mMsrObjectNum);	
			   gstrlineEn2=gstrtemp2;
//			   gstrlineCn2=gstrtemp2;

			   gstrlineEn3=messier.ConEn;
//			   gstrlineCn3=messier.ConCn;

			   gstrlineEn4=messier.TypeEn;
//			   gstrlineCn4=messier.TypeCn;

					g_mShowMenurowEn=0;
//					g_mShowMenurowCn=0;
					//FSelShowLanguage();
					g_mShowLangauge=ENGLISH;	
		 break;
		//NGC�Ǳ�
		case  SYS_SUB2NGC_OBJECT:
		       GetNGC7840(g_mNgcObjectNum,&ngc);
			   g_mObjRa1=ngc.Ra;
			   g_mObjDec1=ngc.Dec;
			   sprintf(gstrtemp1,"NGC:%d                          ",g_mNgcObjectNum);	
			   gstrlineEn1=gstrtemp1;

			   gstrlineEn2=ngc.ConEn;
		
		       if(ngc.Bright!=0)
			   {
			   sprintf(gstrtemp3,"MEG:%.1f                          ",ngc.Bright);	
			   	gstrlineEn3=gstrtemp3;
				  
				  }
				  else
				  {
					  gstrlineEn3="                                          ";
				  }	
			   
	
			   gstrlineEn4=ngc.TypeEn;



			   	   gLocation.mLongitude=g_mGoto.m_nLongitude;
			       gLocation.mAtitude=g_mGoto.m_nAtitude;
				   	gStarRAD.mRightAscension=g_mObjRa1;
				   gStarRAD.mDeclination=g_mObjDec1;
				 
				   FCalStarAEPos(gLocation,gStarRAD,g_mGoto.m_nSysTimeType,g_mGoto.m_nNutation,&gStarAZ);



				   sprintf(gstrtemp5,"OBJ    Azi:%03d %02d %02d                ",(int)gStarAZ.mANzimuth,(int)((gStarAZ.mANzimuth-(int)gStarAZ.mANzimuth)*60),(int)(gStarAZ.mANzimuth*3600)%60);				   
				  
				   if(gStarAZ.mAtitude>=0)
				   {
				     sprintf(gstrtemp6,"Alt:+%02d %02d %02d               ",abs((int)gStarAZ.mAtitude),abs((int)((gStarAZ.mAtitude-(int)gStarAZ.mAtitude)*60)),abs((int)(gStarAZ.mAtitude*3600)%60));			
          			}
					else
					{
					 sprintf(gstrtemp6,"Alt:-%02d %02d %02d               ",abs((int)gStarAZ.mAtitude),abs((int)((gStarAZ.mAtitude-(int)gStarAZ.mAtitude)*60)),abs((int)(gStarAZ.mAtitude*3600)%60));	
          			 }
					

				   if((int)gStarAZ.mANzimuth <100)
				   {
				     gstrtemp5[11]=' ';
				   }
				   if((int)gStarAZ.mANzimuth <10)
				   {
				     gstrtemp5[12]=' ';
				   }

				   if((int)((gStarAZ.mANzimuth-(int)gStarAZ.mANzimuth)*60)<10)
				   {
				     gstrtemp5[15]=' ';
				   }

				   if(((int)(gStarAZ.mANzimuth*3600)%60)<10)
				   {
				     gstrtemp5[18]=' ';
				   }



				    if(abs((int)gStarAZ.mAtitude)<10)
				   {
				     gstrtemp6[5]=' ';
				   }

				   if(abs((int)((gStarAZ.mAtitude-(int)gStarAZ.mAtitude)*60))<10)
				   {
				     gstrtemp6[8]=' ';
				   }
				   if(abs(((int)(gStarAZ.mAtitude*3600)%60))<10)
				   {
				      gstrtemp6[11]=' ';
				   }

					gstrlineEn5=gstrtemp5;
					gstrlineEn6=gstrtemp6;

//				    gstrlineCn5=gstrtemp5;
//					gstrlineCn6=gstrtemp6;


			       sprintf(gstrtemp7,"R.a: %02dh%02dm%02ds         ",(int)g_mObjRa1,(int)((g_mObjRa1-(int)g_mObjRa1)*60),(int)(g_mObjRa1*3600)%60);	
			
				   if((int)g_mObjRa1<10)
				   {
				     gstrtemp7[5]=' ';
				   }

				   if((int)((g_mObjRa1-(int)g_mObjRa1)*60)<10)
				   {
				     gstrtemp7[8]=' ';
				   }

				   if(((int)(g_mObjRa1*3600)%60)<10)
				   {
				     gstrtemp7[11]=' ';
				   }			
					gstrlineEn7=gstrtemp7;
//					gstrlineCn7=gstrtemp7;

					 if(g_mObjDec1>=0)
					 {
			            sprintf(gstrtemp8,"Dec:+%02d %02d %02d      ",abs((int)g_mObjDec1),abs((int)((g_mObjDec1-(int)g_mObjDec1)*60)),abs((int)(g_mObjDec1*3600)%60));	
					}
					else
					{
					  sprintf(gstrtemp8,"Dec:-%02d %02d %02d        ",abs((int)g_mObjDec1),abs((int)((g_mObjDec1-(int)g_mObjDec1)*60)),abs((int)(g_mObjDec1*3600)%60));	
					}

				   	if(abs((int)g_mObjDec1)<10)
				   {
				     gstrtemp8[5]=' ';
				   }

				   if(abs((int)((g_mObjDec1-(int)g_mObjDec1)*60))<10)
				   {
				     gstrtemp8[8]=' ';
				   }
				   if(abs(((int)(g_mObjDec1*3600)%60))<10)
				   {
				      gstrtemp8[11]=' ';
				   }
				    
					gstrlineEn8=gstrtemp8;
//					gstrlineCn8=gstrtemp8;				

				    g_mShowMenurowEn=0;
//					g_mShowMenurowCn=0;
					g_mShowLangauge=ENGLISH;
			break;

			//NGC�Ǳ�1
		case  SYS_SUB2NGC_OBJECT1:
		       GetNGC7840(g_mNgcObjectNum,&ngc);
			   g_mObjRa1=ngc.Ra;
			   g_mObjDec1=ngc.Dec;
			  
			      
			       gLocation.mLongitude=g_mGoto.m_nLongitude;
			       gLocation.mAtitude=g_mGoto.m_nAtitude;
				   gStarRAD.mRightAscension=g_mObjRa1;
				   gStarRAD.mDeclination=g_mObjDec1;
				   FCalStarAEPos(gLocation,gStarRAD,g_mGoto.m_nSysTimeType,g_mGoto.m_nNutation,&gStarAZ);


		   sprintf(gstrtemp5,"OBJ    Azi:%03d %02d %02d                ",(int)gStarAZ.mANzimuth,(int)((gStarAZ.mANzimuth-(int)gStarAZ.mANzimuth)*60),(int)(gStarAZ.mANzimuth*3600)%60);				   
				  
				   if(gStarAZ.mAtitude>=0)
				   {
				     sprintf(gstrtemp6,"Alt:+%02d %02d %02d               ",abs((int)gStarAZ.mAtitude),abs((int)((gStarAZ.mAtitude-(int)gStarAZ.mAtitude)*60)),abs((int)(gStarAZ.mAtitude*3600)%60));			
          			}
					else
					{
					 sprintf(gstrtemp6,"Alt:-%02d %02d %02d               ",abs((int)gStarAZ.mAtitude),abs((int)((gStarAZ.mAtitude-(int)gStarAZ.mAtitude)*60)),abs((int)(gStarAZ.mAtitude*3600)%60));	
          			  g_mOperateStatus=3;
					 }
					

				   if((int)gStarAZ.mANzimuth <100)
				   {
				     gstrtemp5[11]=' ';
				   }
				   if((int)gStarAZ.mANzimuth <10)
				   {
				     gstrtemp5[12]=' ';
				   }

				   if((int)((gStarAZ.mANzimuth-(int)gStarAZ.mANzimuth)*60)<10)
				   {
				     gstrtemp5[15]=' ';
				   }

				   if(((int)(gStarAZ.mANzimuth*3600)%60)<10)
				   {
				     gstrtemp5[18]=' ';
				   }



				    if(abs((int)gStarAZ.mAtitude)<10)
				   {
				     gstrtemp6[5]=' ';
				   }

				   if(abs((int)((gStarAZ.mAtitude-(int)gStarAZ.mAtitude)*60))<10)
				   {
				     gstrtemp6[8]=' ';
				   }
				   if(abs(((int)(gStarAZ.mAtitude*3600)%60))<10)
				   {
				      gstrtemp6[11]=' ';
				   }

					gstrlineEn5=gstrtemp5;
					gstrlineEn6=gstrtemp6;

//				    gstrlineCn5=gstrtemp5;
//					gstrlineCn6=gstrtemp6;



					g_mTelAzi1=g_mTelAzi;
			        g_mTelAlt1=g_mTelAlt;
						if(g_mAzEq==1)
					{
						 g_teldec=g_mTelDec;
						 g_telra=FCalSiderealTime(1,false,g_mGoto.m_nLongitude)-g_mTelRa;
						 while(	g_telra>=24)
						 {
						   g_telra=g_telra-24;
						  }
						  while(g_telra<0)
						   {
						    g_telra=g_telra+24;
						   }
						   gLocation.mLongitude=g_mGoto.m_nLongitude;
					       gLocation.mAtitude=g_mGoto.m_nAtitude;
						   gTelRAD.mRightAscension=g_telra;
						   gTelRAD.mDeclination=g_teldec;
						   FCalStarAEPos(gLocation,gTelRAD,g_mGoto.m_nSysTimeType,g_mGoto.m_nNutation,&gTelAZ);
						   g_mTelAzi1=gTelAZ.mANzimuth;
						   g_mTelAlt1=gTelAZ.mAtitude;
					}


			     sprintf(gstrtemp7,"OTA    Azi:%03d %02d %02d                ",abs((int)g_mTelAzi1),abs((int)((g_mTelAzi1-(int)g_mTelAzi1)*60)),abs((int)(g_mTelAzi1*3600)%60)); 
				   if(g_mTelAlt1>=0)
				   {
				     sprintf(gstrtemp8,"Alt:+%02d %02d %02d               ",abs((int)g_mTelAlt1),abs((int)((g_mTelAlt1-(int)g_mTelAlt1)*60)),abs((int)(g_mTelAlt1*3600)%60));			
          			}
					else
					{
					 sprintf(gstrtemp8,"Alt:-%02d %02d %02d               ",abs((int)g_mTelAlt1),abs((int)((g_mTelAlt1-(int)g_mTelAlt1)*60)),abs((int)(g_mTelAlt1*3600)%60));	
          			 }
					

				   if((int)g_mTelAzi1 <100)
				   {
				     gstrtemp7[11]=' ';
				   }
				   if((int)g_mTelAzi1 <10)
				   {
				     gstrtemp7[12]=' ';
				   }

				   if((int)((g_mTelAzi1-(int)g_mTelAzi1)*60)<10)
				   {
				     gstrtemp7[15]=' ';
				   }

				   if(((int)(g_mTelAzi1*3600)%60)<10)
				   {
				     gstrtemp7[18]=' ';
				   }



				    if(abs((int)g_mTelAlt1)<10)
				   {
				     gstrtemp8[5]=' ';
				   }

				   if(abs((int)((g_mTelAlt1-(int)g_mTelAlt1)*60))<10)
				   {
				     gstrtemp8[8]=' ';
				   }
				   if(abs(((int)(g_mTelAlt1*3600)%60))<10)
				   {
				      gstrtemp8[11]=' ';
				   }

					gstrlineEn7=gstrtemp7;
					gstrlineEn8=gstrtemp8;

//				    gstrlineCn7=gstrtemp7;
//					gstrlineCn8=gstrtemp8;


					if((g_mTelStatus==1)||(g_mTelStatus==2))
					{
					  g_mOperateStatus=g_mTelStatus;
					}

				   	if((gStarAZ.mAtitude<0)&&((g_mOperateStatus==1)||(g_mOperateStatus==2)))
				   {
				     g_mOperateStatus=3;
				   	}
								
	
							//��Զ������״̬			 
				    switch(g_mOperateStatus)
					{
					case 1:
						gstrlineEn1="Slewing to Target       ";
//						gstrlineCn1=g_OperateStatusCn1;
						break;
					case 2:
					    gstrlineEn1="Find Target,Tracking    ";
//						gstrlineCn1=g_OperateStatusCn2;
						break;
					case 3:
						gstrlineEn1="Target Under Horizon    ";
//						gstrlineCn1=g_OperateStatusCn3;
						g_mEQHn=true;//���ʽ��Զ��Ŀ���Ƿ��ڵ�ƽ��
						break;

					case 4:	  
					     gstrlineEn1="Pause                 ";
//						 gstrlineCn1=g_OperateStatusCn4;
					break;
					case 5:	  
					     gstrlineEn1="Cancel Operation          ";
//						 gstrlineCn1=g_OperateStatusCn5;
					break;
						
					default:
						gstrlineEn1="                     ";
						break;
					}
			
				    sprintf(gstrtemp2,"NGC:%d                          ",g_mNgcObjectNum);	
			      gstrlineEn2=gstrtemp2;

			     gstrlineEn3=ngc.ConEn;
			    
				if(ngc.Bright!=0)
			    {
			     sprintf(gstrtemp4,"MEG:%.1f          ",ngc.Bright);	
			   	  gstrlineEn4=gstrtemp4;
				  
				 }
				  else
				  {
					  gstrlineEn4="                     ";
				  }	
	

					g_mShowMenurowEn=0;
//					g_mShowMenurowCn=0;
					//FSelShowLanguage();	
					g_mShowLangauge=ENGLISH;
		break;


	   //IC�Ǳ�
	
		case  SYS_SUB2IC_OBJECT:
		       GetIC5386(g_mIcObjectNum,&ic);
			   g_mObjRa1=ic.Ra;
			   g_mObjDec1=ic.Dec;
			   sprintf(gstrtemp1,"IC:%d                          ",g_mIcObjectNum);	
			   gstrlineEn1=gstrtemp1;

			   gstrlineEn2=ic.ConEn;
			   if(ic.Bright!=0)
			   {
			    sprintf(gstrtemp3,"MEG:%.1f                          ",ic.Bright);	
			   	gstrlineEn3=gstrtemp3;
				  
				 }
				  else
				  {
					  gstrlineEn3="                                          ";
				  }	
			   
	
			   gstrlineEn4=ic.TypeEn;





			   	   gLocation.mLongitude=g_mGoto.m_nLongitude;
			       gLocation.mAtitude=g_mGoto.m_nAtitude;
				   	gStarRAD.mRightAscension=g_mObjRa1;
				   gStarRAD.mDeclination=g_mObjDec1;
				 
				   FCalStarAEPos(gLocation,gStarRAD,g_mGoto.m_nSysTimeType,g_mGoto.m_nNutation,&gStarAZ);



				   sprintf(gstrtemp5,"OBJ    Azi:%03d %02d %02d                ",(int)gStarAZ.mANzimuth,(int)((gStarAZ.mANzimuth-(int)gStarAZ.mANzimuth)*60),(int)(gStarAZ.mANzimuth*3600)%60);				   
				  
				   if(gStarAZ.mAtitude>=0)
				   {
				     sprintf(gstrtemp6,"Alt:+%02d %02d %02d               ",abs((int)gStarAZ.mAtitude),abs((int)((gStarAZ.mAtitude-(int)gStarAZ.mAtitude)*60)),abs((int)(gStarAZ.mAtitude*3600)%60));			
          			}
					else
					{
					 sprintf(gstrtemp6,"Alt:-%02d %02d %02d               ",abs((int)gStarAZ.mAtitude),abs((int)((gStarAZ.mAtitude-(int)gStarAZ.mAtitude)*60)),abs((int)(gStarAZ.mAtitude*3600)%60));	
          			 }
					

				   if((int)gStarAZ.mANzimuth <100)
				   {
				     gstrtemp5[11]=' ';
				   }
				   if((int)gStarAZ.mANzimuth <10)
				   {
				     gstrtemp5[12]=' ';
				   }

				   if((int)((gStarAZ.mANzimuth-(int)gStarAZ.mANzimuth)*60)<10)
				   {
				     gstrtemp5[15]=' ';
				   }

				   if(((int)(gStarAZ.mANzimuth*3600)%60)<10)
				   {
				     gstrtemp5[18]=' ';
				   }



				    if(abs((int)gStarAZ.mAtitude)<10)
				   {
				     gstrtemp6[5]=' ';
				   }

				   if(abs((int)((gStarAZ.mAtitude-(int)gStarAZ.mAtitude)*60))<10)
				   {
				     gstrtemp6[8]=' ';
				   }
				   if(abs(((int)(gStarAZ.mAtitude*3600)%60))<10)
				   {
				      gstrtemp6[11]=' ';
				   }

					gstrlineEn5=gstrtemp5;
					gstrlineEn6=gstrtemp6;

//				    gstrlineCn5=gstrtemp5;
//					gstrlineCn6=gstrtemp6;


			       sprintf(gstrtemp7,"R.a: %02dh%02dm%02ds         ",(int)g_mObjRa1,(int)((g_mObjRa1-(int)g_mObjRa1)*60),(int)(g_mObjRa1*3600)%60);	
			
				   if((int)g_mObjRa1<10)
				   {
				     gstrtemp7[5]=' ';
				   }

				   if((int)((g_mObjRa1-(int)g_mObjRa1)*60)<10)
				   {
				     gstrtemp7[8]=' ';
				   }

				   if(((int)(g_mObjRa1*3600)%60)<10)
				   {
				     gstrtemp7[11]=' ';
				   }			
					gstrlineEn7=gstrtemp7;
//					gstrlineCn7=gstrtemp7;

					 if(g_mObjDec1>=0)
					 {
			            sprintf(gstrtemp8,"Dec:+%02d %02d %02d      ",abs((int)g_mObjDec1),abs((int)((g_mObjDec1-(int)g_mObjDec1)*60)),abs((int)(g_mObjDec1*3600)%60));	
					}
					else
					{
					  sprintf(gstrtemp8,"Dec:-%02d %02d %02d        ",abs((int)g_mObjDec1),abs((int)((g_mObjDec1-(int)g_mObjDec1)*60)),abs((int)(g_mObjDec1*3600)%60));	
					}

				   	if(abs((int)g_mObjDec1)<10)
				   {
				     gstrtemp8[5]=' ';
				   }

				   if(abs((int)((g_mObjDec1-(int)g_mObjDec1)*60))<10)
				   {
				     gstrtemp8[8]=' ';
				   }
				   if(abs(((int)(g_mObjDec1*3600)%60))<10)
				   {
				      gstrtemp8[11]=' ';
				   }
				    
					gstrlineEn8=gstrtemp8;
//					gstrlineCn8=gstrtemp8;				

				    g_mShowMenurowEn=0;
//					g_mShowMenurowCn=0;
					g_mShowLangauge=ENGLISH;
			break;


	//IC�Ǳ�1
	
		case  SYS_SUB2IC_OBJECT1:
		      GetIC5386(g_mIcObjectNum,&ic);
			   g_mObjRa1=ic.Ra;
			   g_mObjDec1=ic.Dec;
			   
			       gLocation.mLongitude=g_mGoto.m_nLongitude;
			       gLocation.mAtitude=g_mGoto.m_nAtitude;
				   gStarRAD.mRightAscension=g_mObjRa1;
				   gStarRAD.mDeclination=g_mObjDec1;
				   FCalStarAEPos(gLocation,gStarRAD,g_mGoto.m_nSysTimeType,g_mGoto.m_nNutation,&gStarAZ);


				   sprintf(gstrtemp5,"OBJ    Azi:%03d %02d %02d                ",(int)gStarAZ.mANzimuth,(int)((gStarAZ.mANzimuth-(int)gStarAZ.mANzimuth)*60),(int)(gStarAZ.mANzimuth*3600)%60);				   
				  
				   if(gStarAZ.mAtitude>=0)
				   {
				     sprintf(gstrtemp6,"Alt:+%02d %02d %02d               ",abs((int)gStarAZ.mAtitude),abs((int)((gStarAZ.mAtitude-(int)gStarAZ.mAtitude)*60)),abs((int)(gStarAZ.mAtitude*3600)%60));			
          			}
					else
					{
					 sprintf(gstrtemp6,"Alt:-%02d %02d %02d               ",abs((int)gStarAZ.mAtitude),abs((int)((gStarAZ.mAtitude-(int)gStarAZ.mAtitude)*60)),abs((int)(gStarAZ.mAtitude*3600)%60));	
          			  g_mOperateStatus=3;
					 }
					

				   if((int)gStarAZ.mANzimuth <100)
				   {
				     gstrtemp5[11]=' ';
				   }
				   if((int)gStarAZ.mANzimuth <10)
				   {
				     gstrtemp5[12]=' ';
				   }

				   if((int)((gStarAZ.mANzimuth-(int)gStarAZ.mANzimuth)*60)<10)
				   {
				     gstrtemp5[15]=' ';
				   }

				   if(((int)(gStarAZ.mANzimuth*3600)%60)<10)
				   {
				     gstrtemp5[18]=' ';
				   }



				    if(abs((int)gStarAZ.mAtitude)<10)
				   {
				     gstrtemp6[5]=' ';
				   }

				   if(abs((int)((gStarAZ.mAtitude-(int)gStarAZ.mAtitude)*60))<10)
				   {
				     gstrtemp6[8]=' ';
				   }
				   if(abs(((int)(gStarAZ.mAtitude*3600)%60))<10)
				   {
				      gstrtemp6[11]=' ';
				   }

					gstrlineEn5=gstrtemp5;
					gstrlineEn6=gstrtemp6;

//				    gstrlineCn5=gstrtemp5;
//					gstrlineCn6=gstrtemp6;



					g_mTelAzi1=g_mTelAzi;
			        g_mTelAlt1=g_mTelAlt;
					if(g_mAzEq==1)
					{
						 g_teldec=g_mTelDec;
						 g_telra=FCalSiderealTime(1,false,g_mGoto.m_nLongitude)-g_mTelRa;
						 while(	g_telra>=24)
						 {
						   g_telra=g_telra-24;
						  }
						  while(g_telra<0)
						   {
						    g_telra=g_telra+24;
						   }
						   gLocation.mLongitude=g_mGoto.m_nLongitude;
					       gLocation.mAtitude=g_mGoto.m_nAtitude;
						   gTelRAD.mRightAscension=g_telra;
						   gTelRAD.mDeclination=g_teldec;
						   FCalStarAEPos(gLocation,gTelRAD,g_mGoto.m_nSysTimeType,g_mGoto.m_nNutation,&gTelAZ);
						   g_mTelAzi1=gTelAZ.mANzimuth;
						   g_mTelAlt1=gTelAZ.mAtitude;
					}


			     sprintf(gstrtemp7,"OTA    Azi:%03d %02d %02d                ",abs((int)g_mTelAzi1),abs((int)((g_mTelAzi1-(int)g_mTelAzi1)*60)),abs((int)(g_mTelAzi1*3600)%60)); 
				   if(g_mTelAlt1>=0)
				   {
				     sprintf(gstrtemp8,"Alt:+%02d %02d %02d               ",abs((int)g_mTelAlt1),abs((int)((g_mTelAlt1-(int)g_mTelAlt1)*60)),abs((int)(g_mTelAlt1*3600)%60));			
          			}
					else
					{
					 sprintf(gstrtemp8,"Alt:-%02d %02d %02d               ",abs((int)g_mTelAlt1),abs((int)((g_mTelAlt1-(int)g_mTelAlt1)*60)),abs((int)(g_mTelAlt1*3600)%60));	
          			 }
					

				   if((int)g_mTelAzi1 <100)
				   {
				     gstrtemp7[11]=' ';
				   }
				   if((int)g_mTelAzi1 <10)
				   {
				     gstrtemp7[12]=' ';
				   }

				   if((int)((g_mTelAzi1-(int)g_mTelAzi1)*60)<10)
				   {
				     gstrtemp7[15]=' ';
				   }

				   if(((int)(g_mTelAzi1*3600)%60)<10)
				   {
				     gstrtemp7[18]=' ';
				   }



				    if(abs((int)g_mTelAlt1)<10)
				   {
				     gstrtemp8[5]=' ';
				   }

				   if(abs((int)((g_mTelAlt1-(int)g_mTelAlt1)*60))<10)
				   {
				     gstrtemp8[8]=' ';
				   }
				   if(abs(((int)(g_mTelAlt1*3600)%60))<10)
				   {
				      gstrtemp8[11]=' ';
				   }

					gstrlineEn7=gstrtemp7;
					gstrlineEn8=gstrtemp8;

//				    gstrlineCn7=gstrtemp7;
//					gstrlineCn8=gstrtemp8;


					if((g_mTelStatus==1)||(g_mTelStatus==2))
					{
					  g_mOperateStatus=g_mTelStatus;
					}

				   	if((gStarAZ.mAtitude<0)&&((g_mOperateStatus==1)||(g_mOperateStatus==2)))
				   {
				     g_mOperateStatus=3;
				   	}
								
	
							//��Զ������״̬			 
				    switch(g_mOperateStatus)
					{
					case 1:
						gstrlineEn1="Slewing to Target       ";
//						gstrlineCn1=g_OperateStatusCn1;
						break;
					case 2:
					    gstrlineEn1="Find Target,Tracking    ";
//						gstrlineCn1=g_OperateStatusCn2;
						break;
					case 3:
						gstrlineEn1="Target Under Horizon    ";
//						gstrlineCn1=g_OperateStatusCn3;
						g_mEQHn=true;//���ʽ��Զ��Ŀ���Ƿ��ڵ�ƽ��
						break;

					case 4:	  
					     gstrlineEn1="Pause                 ";
//						 gstrlineCn1=g_OperateStatusCn4;
					break;
					case 5:	  
					     gstrlineEn1="Cancel Operation          ";
//						 gstrlineCn1=g_OperateStatusCn5;
					break;
						
					default:
						gstrlineEn1="                     ";
						break;
					}
			
				    sprintf(gstrtemp2,"IC:%d                          ",g_mIcObjectNum);	
			      gstrlineEn2=gstrtemp2;

			     gstrlineEn3=ic.ConEn;
			    
				if(ic.Bright!=0)
			    {
			     sprintf(gstrtemp4,"MEG:%.1f          ",ic.Bright);	
			   	  gstrlineEn4=gstrtemp4;
				  
				 }
				  else
				  {
					  gstrlineEn4="                     ";
				  }	
//			   
//	
			 
			      


					g_mShowMenurowEn=0;
//					g_mShowMenurowCn=0;
				//	FSelShowLanguage();	
				g_mShowLangauge=ENGLISH;
		break;


	   //SH2�Ǳ�

	    case  SYS_SUB2SH2_OBJECT:
		       GetSh2313(g_mSh2ObjectNum,&sh2);
			   g_mObjRa1=sh2.Ra;
			   g_mObjDec1=sh2.Dec;
			   sprintf(gstrtemp1,"Sh2:%d                          ",g_mSh2ObjectNum);	
			   gstrlineEn1=gstrtemp1;

			   gstrlineEn2="                                        ";
			   gstrlineEn3="                                        ";
			   gstrlineEn4="                                        ";



			   	   gLocation.mLongitude=g_mGoto.m_nLongitude;
			       gLocation.mAtitude=g_mGoto.m_nAtitude;
				   	gStarRAD.mRightAscension=g_mObjRa1;
				   gStarRAD.mDeclination=g_mObjDec1;
				 
				   FCalStarAEPos(gLocation,gStarRAD,g_mGoto.m_nSysTimeType,g_mGoto.m_nNutation,&gStarAZ);



				   sprintf(gstrtemp5,"OBJ    Azi:%03d %02d %02d                ",(int)gStarAZ.mANzimuth,(int)((gStarAZ.mANzimuth-(int)gStarAZ.mANzimuth)*60),(int)(gStarAZ.mANzimuth*3600)%60);				   
				  
				   if(gStarAZ.mAtitude>=0)
				   {
				     sprintf(gstrtemp6,"Alt:+%02d %02d %02d               ",abs((int)gStarAZ.mAtitude),abs((int)((gStarAZ.mAtitude-(int)gStarAZ.mAtitude)*60)),abs((int)(gStarAZ.mAtitude*3600)%60));			
          			}
					else
					{
					 sprintf(gstrtemp6,"Alt:-%02d %02d %02d               ",abs((int)gStarAZ.mAtitude),abs((int)((gStarAZ.mAtitude-(int)gStarAZ.mAtitude)*60)),abs((int)(gStarAZ.mAtitude*3600)%60));	
          			 }
					

				   if((int)gStarAZ.mANzimuth <100)
				   {
				     gstrtemp5[11]=' ';
				   }
				   if((int)gStarAZ.mANzimuth <10)
				   {
				     gstrtemp5[12]=' ';
				   }

				   if((int)((gStarAZ.mANzimuth-(int)gStarAZ.mANzimuth)*60)<10)
				   {
				     gstrtemp5[15]=' ';
				   }

				   if(((int)(gStarAZ.mANzimuth*3600)%60)<10)
				   {
				     gstrtemp5[18]=' ';
				   }



				    if(abs((int)gStarAZ.mAtitude)<10)
				   {
				     gstrtemp6[5]=' ';
				   }

				   if(abs((int)((gStarAZ.mAtitude-(int)gStarAZ.mAtitude)*60))<10)
				   {
				     gstrtemp6[8]=' ';
				   }
				   if(abs(((int)(gStarAZ.mAtitude*3600)%60))<10)
				   {
				      gstrtemp6[11]=' ';
				   }

					gstrlineEn5=gstrtemp5;
					gstrlineEn6=gstrtemp6;

//				    gstrlineCn5=gstrtemp5;
//					gstrlineCn6=gstrtemp6;


			       sprintf(gstrtemp7,"R.a: %02dh%02dm%02ds         ",(int)g_mObjRa1,(int)((g_mObjRa1-(int)g_mObjRa1)*60),(int)(g_mObjRa1*3600)%60);	
			
				   if((int)g_mObjRa1<10)
				   {
				     gstrtemp7[5]=' ';
				   }

				   if((int)((g_mObjRa1-(int)g_mObjRa1)*60)<10)
				   {
				     gstrtemp7[8]=' ';
				   }

				   if(((int)(g_mObjRa1*3600)%60)<10)
				   {
				     gstrtemp7[11]=' ';
				   }			
					gstrlineEn7=gstrtemp7;
//					gstrlineCn7=gstrtemp7;

					 if(g_mObjDec1>=0)
					 {
			            sprintf(gstrtemp8,"Dec:+%02d %02d %02d      ",abs((int)g_mObjDec1),abs((int)((g_mObjDec1-(int)g_mObjDec1)*60)),abs((int)(g_mObjDec1*3600)%60));	
					}
					else
					{
					  sprintf(gstrtemp8,"Dec:-%02d %02d %02d        ",abs((int)g_mObjDec1),abs((int)((g_mObjDec1-(int)g_mObjDec1)*60)),abs((int)(g_mObjDec1*3600)%60));	
					}

				   	if(abs((int)g_mObjDec1)<10)
				   {
				     gstrtemp8[5]=' ';
				   }

				   if(abs((int)((g_mObjDec1-(int)g_mObjDec1)*60))<10)
				   {
				     gstrtemp8[8]=' ';
				   }
				   if(abs(((int)(g_mObjDec1*3600)%60))<10)
				   {
				      gstrtemp8[11]=' ';
				   }
				    
					gstrlineEn8=gstrtemp8;
//					gstrlineCn8=gstrtemp8;				

				    g_mShowMenurowEn=0;
//					g_mShowMenurowCn=0;
					g_mShowLangauge=ENGLISH;
			break;

		//SH2�Ǳ�1

	    case  SYS_SUB2SH2_OBJECT1:
		     GetSh2313(g_mSh2ObjectNum,&sh2);
			   g_mObjRa1=sh2.Ra;
			   g_mObjDec1=sh2.Dec;
			  
			      
			       gLocation.mLongitude=g_mGoto.m_nLongitude;
			       gLocation.mAtitude=g_mGoto.m_nAtitude;
				   gStarRAD.mRightAscension=g_mObjRa1;
				   gStarRAD.mDeclination=g_mObjDec1;
				   FCalStarAEPos(gLocation,gStarRAD,g_mGoto.m_nSysTimeType,g_mGoto.m_nNutation,&gStarAZ);



				   sprintf(gstrtemp5,"OBJ    Azi:%03d %02d %02d                ",(int)gStarAZ.mANzimuth,(int)((gStarAZ.mANzimuth-(int)gStarAZ.mANzimuth)*60),(int)(gStarAZ.mANzimuth*3600)%60);				   
				  
				   if(gStarAZ.mAtitude>=0)
				   {
				     sprintf(gstrtemp6,"Alt:+%02d %02d %02d               ",abs((int)gStarAZ.mAtitude),abs((int)((gStarAZ.mAtitude-(int)gStarAZ.mAtitude)*60)),abs((int)(gStarAZ.mAtitude*3600)%60));			
          			}
					else
					{
					 sprintf(gstrtemp6,"Alt:-%02d %02d %02d               ",abs((int)gStarAZ.mAtitude),abs((int)((gStarAZ.mAtitude-(int)gStarAZ.mAtitude)*60)),abs((int)(gStarAZ.mAtitude*3600)%60));	
          			  g_mOperateStatus=3;
					 }
					

				   if((int)gStarAZ.mANzimuth <100)
				   {
				     gstrtemp5[11]=' ';
				   }
				   if((int)gStarAZ.mANzimuth <10)
				   {
				     gstrtemp5[12]=' ';
				   }

				   if((int)((gStarAZ.mANzimuth-(int)gStarAZ.mANzimuth)*60)<10)
				   {
				     gstrtemp5[15]=' ';
				   }

				   if(((int)(gStarAZ.mANzimuth*3600)%60)<10)
				   {
				     gstrtemp5[18]=' ';
				   }



				    if(abs((int)gStarAZ.mAtitude)<10)
				   {
				     gstrtemp6[5]=' ';
				   }

				   if(abs((int)((gStarAZ.mAtitude-(int)gStarAZ.mAtitude)*60))<10)
				   {
				     gstrtemp6[8]=' ';
				   }
				   if(abs(((int)(gStarAZ.mAtitude*3600)%60))<10)
				   {
				      gstrtemp6[11]=' ';
				   }

					gstrlineEn5=gstrtemp5;
					gstrlineEn6=gstrtemp6;

//				    gstrlineCn5=gstrtemp5;
//					gstrlineCn6=gstrtemp6;



					g_mTelAzi1=g_mTelAzi;
			        g_mTelAlt1=g_mTelAlt;
					if(g_mAzEq==1)
					{
						 g_teldec=g_mTelDec;
						 g_telra=FCalSiderealTime(1,false,g_mGoto.m_nLongitude)-g_mTelRa;
						 while(	g_telra>=24)
						 {
						   g_telra=g_telra-24;
						  }
						  while(g_telra<0)
						   {
						    g_telra=g_telra+24;
						   }
						   gLocation.mLongitude=g_mGoto.m_nLongitude;
					       gLocation.mAtitude=g_mGoto.m_nAtitude;
						   gTelRAD.mRightAscension=g_telra;
						   gTelRAD.mDeclination=g_teldec;
						   FCalStarAEPos(gLocation,gTelRAD,g_mGoto.m_nSysTimeType,g_mGoto.m_nNutation,&gTelAZ);
						   g_mTelAzi1=gTelAZ.mANzimuth;
						   g_mTelAlt1=gTelAZ.mAtitude;
					}

				    sprintf(gstrtemp7,"OTA    Azi:%03d %02d %02d                ",abs((int)g_mTelAzi1),abs((int)((g_mTelAzi1-(int)g_mTelAzi1)*60)),abs((int)(g_mTelAzi1*3600)%60));  
				 
				   if(g_mTelAlt1>=0)
				   {
				     sprintf(gstrtemp8,"Alt:+%02d %02d %02d               ",abs((int)g_mTelAlt1),abs((int)((g_mTelAlt1-(int)g_mTelAlt1)*60)),abs((int)(g_mTelAlt1*3600)%60));			
          			}
					else
					{
					 sprintf(gstrtemp8,"Alt:-%02d %02d %02d               ",abs((int)g_mTelAlt1),abs((int)((g_mTelAlt1-(int)g_mTelAlt1)*60)),abs((int)(g_mTelAlt1*3600)%60));	
          			 }
					

				   if((int)g_mTelAzi1 <100)
				   {
				     gstrtemp7[11]=' ';
				   }
				   if((int)g_mTelAzi1 <10)
				   {
				     gstrtemp7[12]=' ';
				   }

				   if((int)((g_mTelAzi1-(int)g_mTelAzi1)*60)<10)
				   {
				     gstrtemp7[15]=' ';
				   }

				   if(((int)(g_mTelAzi1*3600)%60)<10)
				   {
				     gstrtemp7[18]=' ';
				   }



				    if(abs((int)g_mTelAlt1)<10)
				   {
				     gstrtemp8[5]=' ';
				   }

				   if(abs((int)((g_mTelAlt1-(int)g_mTelAlt1)*60))<10)
				   {
				     gstrtemp8[8]=' ';
				   }
				   if(abs(((int)(g_mTelAlt1*3600)%60))<10)
				   {
				      gstrtemp8[11]=' ';
				   }

					gstrlineEn7=gstrtemp7;
					gstrlineEn8=gstrtemp8;

//				    gstrlineCn7=gstrtemp7;
//					gstrlineCn8=gstrtemp8;	

					if((g_mTelStatus==1)||(g_mTelStatus==2))
					{
					  g_mOperateStatus=g_mTelStatus;
					}

				   	if((gStarAZ.mAtitude<0)&&((g_mOperateStatus==1)||(g_mOperateStatus==2)))
				   {
				     g_mOperateStatus=3;
				   	}
								
	
							//��Զ������״̬			 
				    switch(g_mOperateStatus)
					{
					case 1:
						gstrlineEn1="Slewing to Target       ";
//						gstrlineCn1=g_OperateStatusCn1;
						break;
					case 2:
					    gstrlineEn1="Find Target,Tracking    ";
//						gstrlineCn1=g_OperateStatusCn2;
						break;
					case 3:
						gstrlineEn1="Target Under Horizon    ";
//						gstrlineCn1=g_OperateStatusCn3;
						g_mEQHn=true;//���ʽ��Զ��Ŀ���Ƿ��ڵ�ƽ��
						break;

					case 4:	  
					     gstrlineEn1="Pause                 ";
//						 gstrlineCn1=g_OperateStatusCn4;
					break;
					case 5:	  
					     gstrlineEn1="Cancel Operation          ";
//						 gstrlineCn1=g_OperateStatusCn5;
					break;
						
					default:
						gstrlineEn1="                              ";
						break;
					}
			
				    sprintf(gstrtemp3,"Sh2:%d                          ",g_mSh2ObjectNum);	
			        gstrlineEn3=gstrtemp3;

			 
			        gstrlineEn2="                                        ";
			        gstrlineEn4="                                        ";



					g_mShowMenurowEn=0;
//					g_mShowMenurowCn=0;
					//FSelShowLanguage();
					g_mShowLangauge=ENGLISH;	
		break;

		//Bright�Ǳ�

		case  SYS_SUB2BRT_OBJECT:
		       GetBright167(g_mBrightObjectNum,&bright);
			   g_mObjRa1=bright.Ra;
			   g_mObjDec1=bright.Dec;
			  sprintf(gstrtemp1,"Bright:%d                          ",g_mBrightObjectNum);	
			   gstrlineEn1=gstrtemp1;

			   gstrlineEn2=bright.NameEn;
		
		       if(bright.bright!=0)
			   {
			      sprintf(gstrtemp3,"MEG:%.1f                          ",bright.bright); 
				   gstrlineEn3=gstrtemp3;
				  
				  }
				  else
				  {
					  gstrlineEn3="                                          ";
				  }	
			   
	
			   gstrlineEn4="                                          ";



			   	   gLocation.mLongitude=g_mGoto.m_nLongitude;
			       gLocation.mAtitude=g_mGoto.m_nAtitude;
				   	gStarRAD.mRightAscension=g_mObjRa1;
				   gStarRAD.mDeclination=g_mObjDec1;
				 
				   FCalStarAEPos(gLocation,gStarRAD,g_mGoto.m_nSysTimeType,g_mGoto.m_nNutation,&gStarAZ);



				   sprintf(gstrtemp5,"OBJ    Azi:%03d %02d %02d                ",(int)gStarAZ.mANzimuth,(int)((gStarAZ.mANzimuth-(int)gStarAZ.mANzimuth)*60),(int)(gStarAZ.mANzimuth*3600)%60);				   
				  
				   if(gStarAZ.mAtitude>=0)
				   {
				     sprintf(gstrtemp6,"Alt:+%02d %02d %02d               ",abs((int)gStarAZ.mAtitude),abs((int)((gStarAZ.mAtitude-(int)gStarAZ.mAtitude)*60)),abs((int)(gStarAZ.mAtitude*3600)%60));			
          			}
					else
					{
					 sprintf(gstrtemp6,"Alt:-%02d %02d %02d               ",abs((int)gStarAZ.mAtitude),abs((int)((gStarAZ.mAtitude-(int)gStarAZ.mAtitude)*60)),abs((int)(gStarAZ.mAtitude*3600)%60));	
          			 }
					

				   if((int)gStarAZ.mANzimuth <100)
				   {
				     gstrtemp5[11]=' ';
				   }
				   if((int)gStarAZ.mANzimuth <10)
				   {
				     gstrtemp5[12]=' ';
				   }

				   if((int)((gStarAZ.mANzimuth-(int)gStarAZ.mANzimuth)*60)<10)
				   {
				     gstrtemp5[15]=' ';
				   }

				   if(((int)(gStarAZ.mANzimuth*3600)%60)<10)
				   {
				     gstrtemp5[18]=' ';
				   }



				    if(abs((int)gStarAZ.mAtitude)<10)
				   {
				     gstrtemp6[5]=' ';
				   }

				   if(abs((int)((gStarAZ.mAtitude-(int)gStarAZ.mAtitude)*60))<10)
				   {
				     gstrtemp6[8]=' ';
				   }
				   if(abs(((int)(gStarAZ.mAtitude*3600)%60))<10)
				   {
				      gstrtemp6[11]=' ';
				   }

					gstrlineEn5=gstrtemp5;
					gstrlineEn6=gstrtemp6;

//				    gstrlineCn5=gstrtemp5;
//					gstrlineCn6=gstrtemp6;


			       sprintf(gstrtemp7,"R.a: %02dh%02dm%02ds         ",(int)g_mObjRa1,(int)((g_mObjRa1-(int)g_mObjRa1)*60),(int)(g_mObjRa1*3600)%60);	
			
				   if((int)g_mObjRa1<10)
				   {
				     gstrtemp7[5]=' ';
				   }

				   if((int)((g_mObjRa1-(int)g_mObjRa1)*60)<10)
				   {
				     gstrtemp7[8]=' ';
				   }

				   if(((int)(g_mObjRa1*3600)%60)<10)
				   {
				     gstrtemp7[11]=' ';
				   }			
					gstrlineEn7=gstrtemp7;
//					gstrlineCn7=gstrtemp7;

					 if(g_mObjDec1>=0)
					 {
			            sprintf(gstrtemp8,"Dec:+%02d %02d %02d      ",abs((int)g_mObjDec1),abs((int)((g_mObjDec1-(int)g_mObjDec1)*60)),abs((int)(g_mObjDec1*3600)%60));	
					}
					else
					{
					  sprintf(gstrtemp8,"Dec:-%02d %02d %02d        ",abs((int)g_mObjDec1),abs((int)((g_mObjDec1-(int)g_mObjDec1)*60)),abs((int)(g_mObjDec1*3600)%60));	
					}

				   	if(abs((int)g_mObjDec1)<10)
				   {
				     gstrtemp8[5]=' ';
				   }

				   if(abs((int)((g_mObjDec1-(int)g_mObjDec1)*60))<10)
				   {
				     gstrtemp8[8]=' ';
				   }
				   if(abs(((int)(g_mObjDec1*3600)%60))<10)
				   {
				      gstrtemp8[11]=' ';
				   }
				    
					gstrlineEn8=gstrtemp8;
//					gstrlineCn8=gstrtemp8;				

				    g_mShowMenurowEn=0;
//					g_mShowMenurowCn=0;
					g_mShowLangauge=ENGLISH;
			break;
			//Bright�Ǳ�1

		case  SYS_SUB2BRT_OBJECT1:
		          GetBright167(g_mBrightObjectNum,&bright);
			     g_mObjRa1=bright.Ra;
			     g_mObjDec1=bright.Dec;
			 
		
			      
			       gLocation.mLongitude=g_mGoto.m_nLongitude;
			       gLocation.mAtitude=g_mGoto.m_nAtitude;
				   gStarRAD.mRightAscension=g_mObjRa1;
				   gStarRAD.mDeclination=g_mObjDec1;
				   FCalStarAEPos(gLocation,gStarRAD,g_mGoto.m_nSysTimeType,g_mGoto.m_nNutation,&gStarAZ);



				   sprintf(gstrtemp5,"OBJ    Azi:%03d %02d %02d                ",(int)gStarAZ.mANzimuth,(int)((gStarAZ.mANzimuth-(int)gStarAZ.mANzimuth)*60),(int)(gStarAZ.mANzimuth*3600)%60);				   
				  
				   if(gStarAZ.mAtitude>=0)
				   {
				     sprintf(gstrtemp6,"Alt:+%02d %02d %02d               ",abs((int)gStarAZ.mAtitude),abs((int)((gStarAZ.mAtitude-(int)gStarAZ.mAtitude)*60)),abs((int)(gStarAZ.mAtitude*3600)%60));			
          			}
					else
					{
					 sprintf(gstrtemp6,"Alt:-%02d %02d %02d               ",abs((int)gStarAZ.mAtitude),abs((int)((gStarAZ.mAtitude-(int)gStarAZ.mAtitude)*60)),abs((int)(gStarAZ.mAtitude*3600)%60));	
          			  g_mOperateStatus=3;
					 }
					

				   if((int)gStarAZ.mANzimuth <100)
				   {
				     gstrtemp5[11]=' ';
				   }
				   if((int)gStarAZ.mANzimuth <10)
				   {
				     gstrtemp5[12]=' ';
				   }

				   if((int)((gStarAZ.mANzimuth-(int)gStarAZ.mANzimuth)*60)<10)
				   {
				     gstrtemp5[15]=' ';
				   }

				   if(((int)(gStarAZ.mANzimuth*3600)%60)<10)
				   {
				     gstrtemp5[18]=' ';
				   }



				    if(abs((int)gStarAZ.mAtitude)<10)
				   {
				     gstrtemp6[5]=' ';
				   }

				   if(abs((int)((gStarAZ.mAtitude-(int)gStarAZ.mAtitude)*60))<10)
				   {
				     gstrtemp6[8]=' ';
				   }
				   if(abs(((int)(gStarAZ.mAtitude*3600)%60))<10)
				   {
				      gstrtemp6[11]=' ';
				   }

					gstrlineEn5=gstrtemp5;
					gstrlineEn6=gstrtemp6;

//				    gstrlineCn5=gstrtemp5;
//					gstrlineCn6=gstrtemp6;



					g_mTelAzi1=g_mTelAzi;
			        g_mTelAlt1=g_mTelAlt;
						if(g_mAzEq==1)
					{
						 g_teldec=g_mTelDec;
						 g_telra=FCalSiderealTime(1,false,g_mGoto.m_nLongitude)-g_mTelRa;
						 while(	g_telra>=24)
						 {
						   g_telra=g_telra-24;
						  }
						  while(g_telra<0)
						   {
						    g_telra=g_telra+24;
						   }
						   gLocation.mLongitude=g_mGoto.m_nLongitude;
					       gLocation.mAtitude=g_mGoto.m_nAtitude;
						   gTelRAD.mRightAscension=g_telra;
						   gTelRAD.mDeclination=g_teldec;
						   FCalStarAEPos(gLocation,gTelRAD,g_mGoto.m_nSysTimeType,g_mGoto.m_nNutation,&gTelAZ);
						   g_mTelAzi1=gTelAZ.mANzimuth;
						   g_mTelAlt1=gTelAZ.mAtitude;
					}


			       sprintf(gstrtemp7,"OTA    Azi:%03d %02d %02d                ",abs((int)g_mTelAzi1),abs((int)((g_mTelAzi1-(int)g_mTelAzi1)*60)),abs((int)(g_mTelAzi1*3600)%60));
				   if(g_mTelAlt1>=0)
				   {
				     sprintf(gstrtemp8,"Alt:+%02d %02d %02d               ",abs((int)g_mTelAlt1),abs((int)((g_mTelAlt1-(int)g_mTelAlt1)*60)),abs((int)(g_mTelAlt1*3600)%60));			
          			}
					else
					{
					 sprintf(gstrtemp8,"Alt:-%02d %02d %02d               ",abs((int)g_mTelAlt1),abs((int)((g_mTelAlt1-(int)g_mTelAlt1)*60)),abs((int)(g_mTelAlt1*3600)%60));	
          			 }
					

				   if((int)g_mTelAzi1 <100)
				   {
				     gstrtemp7[11]=' ';
				   }
				   if((int)g_mTelAzi1 <10)
				   {
				     gstrtemp7[12]=' ';
				   }

				   if((int)((g_mTelAzi1-(int)g_mTelAzi1)*60)<10)
				   {
				     gstrtemp7[15]=' ';
				   }

				   if(((int)(g_mTelAzi1*3600)%60)<10)
				   {
				     gstrtemp7[18]=' ';
				   }



				    if(abs((int)g_mTelAlt1)<10)
				   {
				     gstrtemp8[5]=' ';
				   }

				   if(abs((int)((g_mTelAlt1-(int)g_mTelAlt1)*60))<10)
				   {
				     gstrtemp8[8]=' ';
				   }
				   if(abs(((int)(g_mTelAlt1*3600)%60))<10)
				   {
				      gstrtemp8[11]=' ';
				   }

					gstrlineEn7=gstrtemp7;
					gstrlineEn8=gstrtemp8;

//				    gstrlineCn7=gstrtemp7;
//					gstrlineCn8=gstrtemp8;	

					if((g_mTelStatus==1)||(g_mTelStatus==2))
					{
					  g_mOperateStatus=g_mTelStatus;
					}

				   	if((gStarAZ.mAtitude<0)&&((g_mOperateStatus==1)||(g_mOperateStatus==2)))
				   {
				     g_mOperateStatus=3;
				   	}
								
	
							//��Զ������״̬			 
				    switch(g_mOperateStatus)
					{
					case 1:
						gstrlineEn1="Slewing to Target       ";
//						gstrlineCn1=g_OperateStatusCn1;
						break;
					case 2:
					    gstrlineEn1="Find Target,Tracking    ";
//						gstrlineCn1=g_OperateStatusCn2;
						break;
					case 3:
						gstrlineEn1="Target Under Horizon    ";
//						gstrlineCn1=g_OperateStatusCn3;
						g_mEQHn=true;//���ʽ��Զ��Ŀ���Ƿ��ڵ�ƽ��
						break;

					case 4:	  
					     gstrlineEn1="Pause                 ";
//						 gstrlineCn1=g_OperateStatusCn4;
					break;
					case 5:	  
					     gstrlineEn1="Cancel Operation          ";
//						 gstrlineCn1=g_OperateStatusCn5;
					break;
						
					default:
						gstrlineEn1="                              ";
						break;
					}
			
				    sprintf(gstrtemp2,"Bright:%d                          ",g_mBrightObjectNum);	
			        gstrlineEn2=gstrtemp2;

			 


				    gstrlineEn3=bright.NameEn;
//				    gstrlineCn3=bright.NameEn;


					gstrlineEn4="                              ";
					g_mShowMenurowEn=0;
//					g_mShowMenurowCn=0;
					//FSelShowLanguage();
					g_mShowLangauge=ENGLISH;	
		break;
		 //Sao�Ǳ�
	     case  SYS_SUB2SAO_OBJECT:

		       GetSAO258997(g_mSaoObjectNum,&sao);
			   g_mObjRa1=sao.Ra;
			   g_mObjDec1=sao.Dec;

			   sprintf(gstrtemp1,"SAO:%d                          ",g_mSaoObjectNum);	
			   gstrlineEn1=gstrtemp1;

			   gstrlineEn2="                                        ";
			   gstrlineEn3="                                        ";
			   gstrlineEn4="                                        ";





			   	   gLocation.mLongitude=g_mGoto.m_nLongitude;
			       gLocation.mAtitude=g_mGoto.m_nAtitude;
				   	gStarRAD.mRightAscension=g_mObjRa1;
				   gStarRAD.mDeclination=g_mObjDec1;
				 
				   FCalStarAEPos(gLocation,gStarRAD,g_mGoto.m_nSysTimeType,g_mGoto.m_nNutation,&gStarAZ);



				   sprintf(gstrtemp5,"OBJ    Azi:%03d %02d %02d                ",(int)gStarAZ.mANzimuth,(int)((gStarAZ.mANzimuth-(int)gStarAZ.mANzimuth)*60),(int)(gStarAZ.mANzimuth*3600)%60);				   
				  
				   if(gStarAZ.mAtitude>=0)
				   {
				     sprintf(gstrtemp6,"Alt:+%02d %02d %02d               ",abs((int)gStarAZ.mAtitude),abs((int)((gStarAZ.mAtitude-(int)gStarAZ.mAtitude)*60)),abs((int)(gStarAZ.mAtitude*3600)%60));			
          			}
					else
					{
					 sprintf(gstrtemp6,"Alt:-%02d %02d %02d               ",abs((int)gStarAZ.mAtitude),abs((int)((gStarAZ.mAtitude-(int)gStarAZ.mAtitude)*60)),abs((int)(gStarAZ.mAtitude*3600)%60));	
          			 }
					

				   if((int)gStarAZ.mANzimuth <100)
				   {
				     gstrtemp5[11]=' ';
				   }
				   if((int)gStarAZ.mANzimuth <10)
				   {
				     gstrtemp5[12]=' ';
				   }

				   if((int)((gStarAZ.mANzimuth-(int)gStarAZ.mANzimuth)*60)<10)
				   {
				     gstrtemp5[15]=' ';
				   }

				   if(((int)(gStarAZ.mANzimuth*3600)%60)<10)
				   {
				     gstrtemp5[18]=' ';
				   }



				    if(abs((int)gStarAZ.mAtitude)<10)
				   {
				     gstrtemp6[5]=' ';
				   }

				   if(abs((int)((gStarAZ.mAtitude-(int)gStarAZ.mAtitude)*60))<10)
				   {
				     gstrtemp6[8]=' ';
				   }
				   if(abs(((int)(gStarAZ.mAtitude*3600)%60))<10)
				   {
				      gstrtemp6[11]=' ';
				   }

					gstrlineEn5=gstrtemp5;
					gstrlineEn6=gstrtemp6;

//				    gstrlineCn5=gstrtemp5;
//					gstrlineCn6=gstrtemp6;


			       sprintf(gstrtemp7,"R.a: %02dh%02dm%02ds         ",(int)g_mObjRa1,(int)((g_mObjRa1-(int)g_mObjRa1)*60),(int)(g_mObjRa1*3600)%60);	
			
				   if((int)g_mObjRa1<10)
				   {
				     gstrtemp7[5]=' ';
				   }

				   if((int)((g_mObjRa1-(int)g_mObjRa1)*60)<10)
				   {
				     gstrtemp7[8]=' ';
				   }

				   if(((int)(g_mObjRa1*3600)%60)<10)
				   {
				     gstrtemp7[11]=' ';
				   }			
					gstrlineEn7=gstrtemp7;
//					gstrlineCn7=gstrtemp7;

					 if(g_mObjDec1>=0)
					 {
			            sprintf(gstrtemp8,"Dec:+%02d %02d %02d      ",abs((int)g_mObjDec1),abs((int)((g_mObjDec1-(int)g_mObjDec1)*60)),abs((int)(g_mObjDec1*3600)%60));	
					}
					else
					{
					  sprintf(gstrtemp8,"Dec:-%02d %02d %02d        ",abs((int)g_mObjDec1),abs((int)((g_mObjDec1-(int)g_mObjDec1)*60)),abs((int)(g_mObjDec1*3600)%60));	
					}

				   	if(abs((int)g_mObjDec1)<10)
				   {
				     gstrtemp8[5]=' ';
				   }

				   if(abs((int)((g_mObjDec1-(int)g_mObjDec1)*60))<10)
				   {
				     gstrtemp8[8]=' ';
				   }
				   if(abs(((int)(g_mObjDec1*3600)%60))<10)
				   {
				      gstrtemp8[11]=' ';
				   }
				    
					gstrlineEn8=gstrtemp8;
//					gstrlineCn8=gstrtemp8;				

				    g_mShowMenurowEn=0;
//					g_mShowMenurowCn=0;
					g_mShowLangauge=ENGLISH;
	     
		 	break;

				 //Sao�Ǳ�1
	     case  SYS_SUB2SAO_OBJECT1:
		       GetSAO258997(g_mSaoObjectNum,&sao);
			   g_mObjRa1=sao.Ra;
			   g_mObjDec1=sao.Dec;

			   

			      
			       gLocation.mLongitude=g_mGoto.m_nLongitude;
			       gLocation.mAtitude=g_mGoto.m_nAtitude;
				   gStarRAD.mRightAscension=g_mObjRa1;
				   gStarRAD.mDeclination=g_mObjDec1;
				   FCalStarAEPos(gLocation,gStarRAD,g_mGoto.m_nSysTimeType,g_mGoto.m_nNutation,&gStarAZ);



				   sprintf(gstrtemp5,"OBJ    Azi:%03d %02d %02d                ",(int)gStarAZ.mANzimuth,(int)((gStarAZ.mANzimuth-(int)gStarAZ.mANzimuth)*60),(int)(gStarAZ.mANzimuth*3600)%60);				   
				  
				   if(gStarAZ.mAtitude>=0)
				   {
				     sprintf(gstrtemp6,"Alt:+%02d %02d %02d               ",abs((int)gStarAZ.mAtitude),abs((int)((gStarAZ.mAtitude-(int)gStarAZ.mAtitude)*60)),abs((int)(gStarAZ.mAtitude*3600)%60));			
          			}
					else
					{
					 sprintf(gstrtemp6,"Alt:-%02d %02d %02d               ",abs((int)gStarAZ.mAtitude),abs((int)((gStarAZ.mAtitude-(int)gStarAZ.mAtitude)*60)),abs((int)(gStarAZ.mAtitude*3600)%60));	
          			  g_mOperateStatus=3;
					 }
					

				   if((int)gStarAZ.mANzimuth <100)
				   {
				     gstrtemp5[11]=' ';
				   }
				   if((int)gStarAZ.mANzimuth <10)
				   {
				     gstrtemp5[12]=' ';
				   }

				   if((int)((gStarAZ.mANzimuth-(int)gStarAZ.mANzimuth)*60)<10)
				   {
				     gstrtemp5[15]=' ';
				   }

				   if(((int)(gStarAZ.mANzimuth*3600)%60)<10)
				   {
				     gstrtemp5[18]=' ';
				   }



				    if(abs((int)gStarAZ.mAtitude)<10)
				   {
				     gstrtemp6[5]=' ';
				   }

				   if(abs((int)((gStarAZ.mAtitude-(int)gStarAZ.mAtitude)*60))<10)
				   {
				     gstrtemp6[8]=' ';
				   }
				   if(abs(((int)(gStarAZ.mAtitude*3600)%60))<10)
				   {
				      gstrtemp6[11]=' ';
				   }

					gstrlineEn5=gstrtemp5;
					gstrlineEn6=gstrtemp6;

//				    gstrlineCn5=gstrtemp5;
//					gstrlineCn6=gstrtemp6;



					g_mTelAzi1=g_mTelAzi;
			        g_mTelAlt1=g_mTelAlt;
						if(g_mAzEq==1)
					{
						 g_teldec=g_mTelDec;
						 g_telra=FCalSiderealTime(1,false,g_mGoto.m_nLongitude)-g_mTelRa;
						 while(	g_telra>=24)
						 {
						   g_telra=g_telra-24;
						  }
						  while(g_telra<0)
						   {
						    g_telra=g_telra+24;
						   }
						   gLocation.mLongitude=g_mGoto.m_nLongitude;
					       gLocation.mAtitude=g_mGoto.m_nAtitude;
						   gTelRAD.mRightAscension=g_telra;
						   gTelRAD.mDeclination=g_teldec;
						   FCalStarAEPos(gLocation,gTelRAD,g_mGoto.m_nSysTimeType,g_mGoto.m_nNutation,&gTelAZ);
						   g_mTelAzi1=gTelAZ.mANzimuth;
						   g_mTelAlt1=gTelAZ.mAtitude;
					}


			     sprintf(gstrtemp7,"OTA    Azi:%03d %02d %02d                ",abs((int)g_mTelAzi1),abs((int)((g_mTelAzi1-(int)g_mTelAzi1)*60)),abs((int)(g_mTelAzi1*3600)%60)); 
				   if(g_mTelAlt1>=0)
				   {
				     sprintf(gstrtemp8,"Alt:+%02d %02d %02d               ",abs((int)g_mTelAlt1),abs((int)((g_mTelAlt1-(int)g_mTelAlt1)*60)),abs((int)(g_mTelAlt1*3600)%60));			
          			}
					else
					{
					 sprintf(gstrtemp8,"Alt:-%02d %02d %02d               ",abs((int)g_mTelAlt1),abs((int)((g_mTelAlt1-(int)g_mTelAlt1)*60)),abs((int)(g_mTelAlt1*3600)%60));	
          			 }
					

				   if((int)g_mTelAzi1 <100)
				   {
				     gstrtemp7[11]=' ';
				   }
				   if((int)g_mTelAzi1 <10)
				   {
				     gstrtemp7[12]=' ';
				   }

				   if((int)((g_mTelAzi1-(int)g_mTelAzi1)*60)<10)
				   {
				     gstrtemp7[15]=' ';
				   }

				   if(((int)(g_mTelAzi1*3600)%60)<10)
				   {
				     gstrtemp7[18]=' ';
				   }



				    if(abs((int)g_mTelAlt1)<10)
				   {
				     gstrtemp8[5]=' ';
				   }

				   if(abs((int)((g_mTelAlt1-(int)g_mTelAlt1)*60))<10)
				   {
				     gstrtemp8[8]=' ';
				   }
				   if(abs(((int)(g_mTelAlt1*3600)%60))<10)
				   {
				      gstrtemp8[11]=' ';
				   }

					gstrlineEn7=gstrtemp7;
					gstrlineEn8=gstrtemp8;

//				    gstrlineCn7=gstrtemp7;
//					gstrlineCn8=gstrtemp8;	

					if((g_mTelStatus==1)||(g_mTelStatus==2))
					{
					  g_mOperateStatus=g_mTelStatus;
					}

				   	if((gStarAZ.mAtitude<0)&&((g_mOperateStatus==1)||(g_mOperateStatus==2)))
				   {
				     g_mOperateStatus=3;
				   	}
								
	
							//��Զ������״̬			 
				    switch(g_mOperateStatus)
					{
					case 1:
						gstrlineEn1="Slewing to Target       ";
//						gstrlineCn1=g_OperateStatusCn1;
						break;
					case 2:
					    gstrlineEn1="Find Target,Tracking    ";
//						gstrlineCn1=g_OperateStatusCn2;
						break;
					case 3:
						gstrlineEn1="Target Under Horizon    ";
//						gstrlineCn1=g_OperateStatusCn3;
						g_mEQHn=true;//���ʽ��Զ��Ŀ���Ƿ��ڵ�ƽ��
						break;

					case 4:	  
					     gstrlineEn1="Pause                 ";
//						 gstrlineCn1=g_OperateStatusCn4;
					break;
					case 5:	  
					     gstrlineEn1="Cancel Operation          ";
//						 gstrlineCn1=g_OperateStatusCn5;
					break;
						
					default:
						gstrlineEn1="                              ";
						break;
					}
			
				    //sprintf(gstrtemp2,"%d",g_mOperateStatus);	
				    //gstrlineEn2=gstrtemp2;
				   	gstrlineEn2="                              ";


				    sprintf(gstrtemp3,"SAO:%d                          ",g_mSaoObjectNum);	
			        gstrlineEn3=gstrtemp3;
//				    gstrlineCn3=gstrtemp3;


					gstrlineEn4="                              ";
					g_mShowMenurowEn=0;
//					g_mShowMenurowCn=0;
					//FSelShowLanguage();
					g_mShowLangauge=ENGLISH;	
		 break;



			//�Զ����Ǳ����
			  case SYS_MENU_SKY_OBJECT:
			       gstrlineEn1="F1";
				   gstrlineEn2="F2";
				   gstrlineEn3="F3";
				   gstrlineEn4="F4";
				   gstrlineEn5="F5";
				   gstrlineEn6="F6";
				   gstrlineEn7="F7";
				   gstrlineEn8="F8";
				   gstrlineEn9="F9";
				   gstrlineEn10="Select F? For Target "	;
				    g_mShowMenurowEn=10;
					g_mShowLangauge=ENGLISH;
				
			  break;
			  case SYS_MENU_SKY_NAME:
			       sprintf(gstrtemp1,"F%d                 ",g_mFnum);	
			       gstrlineEn1=gstrtemp1;
				   gstrlineEn2="                    ";
				    gstrlineEn3="  Please Save Current";
				   gstrlineEn4="Target & Input Target";
				   gstrlineEn5="                    ";
				   gstrlineEn6=g_sysmenu2900NameEn;
				   gstrlineEn7=g_sysmenu2900raEn;
				   gstrlineEn8=g_sysmenu2900decEn;	
				    g_mShowMenurowEn=10;
					g_mShowLangauge=ENGLISH;			  	
			  break;
			 case SYS_MENU_SKY_RA:
			        sprintf(gstrtemp1,"F%d                 ",g_mFnum);	
			       gstrlineEn1=gstrtemp1;
				   gstrlineEn2="                    ";
				   gstrlineEn3="  Please Save Current";
				   gstrlineEn4="Target & Input Target";
				   gstrlineEn5="                    ";
				    gstrlineEn6=g_sysmenu2900NameEn;
				   gstrlineEn7=g_sysmenu2900raEn;
				   gstrlineEn8=g_sysmenu2900decEn;
				   g_mShowMenurowEn=10;
				   g_mShowLangauge=ENGLISH;
				
			  break;
             case SYS_MENU_SKY_DEC:
				    sprintf(gstrtemp1,"F%d                 ",g_mFnum);	
			       gstrlineEn1=gstrtemp1;
				   gstrlineEn2="                    ";
				   gstrlineEn3="  Please Save Current";
				   gstrlineEn4="Target & Input Target";
				   gstrlineEn5="                    ";
				   gstrlineEn6=g_sysmenu2900NameEn;
				   gstrlineEn7=g_sysmenu2900raEn;
				   gstrlineEn8=g_sysmenu2900decEn;
				   g_mShowMenurowEn=10;
					g_mShowLangauge=ENGLISH;
			  break;

	



//		       case SYS_SUB2SUB8_SET:
//			        switch(g_mMyStarOperator)
//					{
//						case 0:
//							gstrlineEn1="Select: ";
//						case 2:
//						    if(g_mMyStarOperator==2)
//			           		gstrlineEn1="Delete: ";
//							GetCustomerStarInfo(CustomStarNum_temp,StarName,&ra_float,&dec_float);
//							ra_byte[0]=(uint8)ra_float;
//							ra_byte[1]=(uint8)((ra_float-ra_byte[0])*60);
//							ra_byte[2]=(uint8)((ra_float-ra_byte[0]-ra_byte[1]/60.0000)*3600);
//							if(dec_float<0)
//							{
//								dec_float=(-dec_float);
//								dec_byte[3]='-';
//							}
//							else
//							{
//								dec_byte[3]='+';
//							}
//							dec_byte[0]=(uint8)dec_float;
//							dec_byte[1]=(uint8)((dec_float-dec_byte[0])*60);
//							dec_byte[2]=(uint8)((dec_float-dec_byte[0]-dec_byte[1]/60.0000)*3600);
//						 sprintf(g_sysmenu2802m_2En,"SName:%s",StarName);
//					
//						  sprintf(g_sysmenu2803m_3En,"SOR.a:%02dh%02dm%02ds",ra_byte[0],ra_byte[1],ra_byte[2]);
//	
//							sprintf(g_sysmenu2804m_4En,"SODec:%c%02dd%02dm%02ds",dec_byte[3],dec_byte[0],dec_byte[1],dec_byte[2]);
//				          	break;
//						case 1:
//			           		gstrlineEn1="Add: ";
//					   		break;
//					   	case 3:
//			           		gstrlineEn1="Modify: ";
//					   		break;
//					   	default :
//					   		break;
//				    }	
//				   		
//					gstrlineEn2=g_sysmenu2802m_2En;
//					gstrlineEn3=g_sysmenu2803m_3En;
//					gstrlineEn4=g_sysmenu2804m_4En;
//					gstrlineEn5="";
//					gstrlineEn6="";
//					gstrlineEn7="";
//					gstrlineEn8="";			  
//					g_mShowMenurowEn=10;
//					g_mShowLangauge=ENGLISH;
//			  		break;

				   //ָ��RA��DEC
				  case SYS_SUB2SUB9RA:
			        gstrlineEn1=g_sysmenu2900titleEn;
					gstrlineEn2="";
					gstrlineEn3=g_sysmenu2900raEn;
					gstrlineEn4="";
					gstrlineEn5=g_sysmenu2900decEn;
					gstrlineEn6="";
					gstrlineEn7="";
					gstrlineEn8="";
					g_mShowMenurowEn=10;
					g_mShowLangauge=ENGLISH;
				    break;
				 case SYS_SUB2SUB9DEC:
			        gstrlineEn1=g_sysmenu2900titleEn;
					gstrlineEn2="";
					gstrlineEn3=g_sysmenu2900raEn;
					gstrlineEn4="";
					gstrlineEn5=g_sysmenu2900decEn;
					gstrlineEn6="";
					gstrlineEn7="";
					gstrlineEn8="";
					g_mShowMenurowEn=10;
					g_mShowLangauge=ENGLISH;
				    break;


			   //½��Ŀ�����
			   case SYS_MENU_LAND_OBJECT:
			       gstrlineEn1="F1";
				   gstrlineEn2="F2";
				   gstrlineEn3="F3";
				   gstrlineEn4="F4";
				   gstrlineEn5="F5";
				   gstrlineEn6="F6";
				   gstrlineEn7="F7";
				   gstrlineEn8="F8";
				   gstrlineEn9="F9";
				   gstrlineEn10="Select F? For Target ";
				   g_mShowMenurowEn=10;
					g_mShowLangauge=ENGLISH;
			   break;
				  case SYS_MENU_LAND_NAME:
			       sprintf(gstrtemp1,"F%d                 ",g_mFnum);	
			       gstrlineEn1=gstrtemp1;
				   gstrlineEn2="                    ";
				    gstrlineEn3="  Please Save Current";
				   gstrlineEn4="Target & Input Target";
				   gstrlineEn5="                    ";
				   gstrlineEn6=g_sysmenu2900NameEn;
				   gstrlineEn7=g_sysmenu2900raEn;
				   gstrlineEn8=g_sysmenu2900decEn;	
				    g_mShowMenurowEn=10;
					g_mShowLangauge=ENGLISH;			  	
			  break;
			 case SYS_MENU_LAND_AZI:
			      sprintf(gstrtemp1,"F%d                 ",g_mFnum);	
			       gstrlineEn1=gstrtemp1;
				   gstrlineEn2="                    ";
				   gstrlineEn3="  Please Save Current";
				   gstrlineEn4="Target & Input Target";
				   gstrlineEn5="                    ";
				    gstrlineEn6=g_sysmenu2900NameEn;
				   gstrlineEn7=g_sysmenu2900raEn;
				   gstrlineEn8=g_sysmenu2900decEn;
				   g_mShowMenurowEn=10;
				   g_mShowLangauge=ENGLISH;
				
			  break;
             case SYS_MENU_LAND_ALT:
			       sprintf(gstrtemp1,"F%d                 ",g_mFnum);	
			       gstrlineEn1=gstrtemp1;
				   gstrlineEn2="                    ";
				   gstrlineEn3="  Please Save Current";
				   gstrlineEn4="Target & Input Target";
				   gstrlineEn5="                    ";
				   gstrlineEn6=g_sysmenu2900NameEn;
				   gstrlineEn7=g_sysmenu2900raEn;
				   gstrlineEn8=g_sysmenu2900decEn;
				   g_mShowMenurowEn=10;
				   g_mShowLangauge=ENGLISH;
			  break;



//		        case SYS_SUB2SUB11_SET :
//			        switch(g_mMyLandmarkOperator)
//					{
//						case 0:
//							gstrlineEn1="Select: ";
//						case 2:
//						    if(g_mMyLandmarkOperator==2)
//			           		gstrlineEn1="Delete: ";
//							GetCustomerLandMarkInfo(CustomLandmarkNum_temp,LandMarkName,&az_float,&alt_float);
//							az_byte[0]=(uint16)az_float;
//							az_byte[1]=(uint16)((az_float-az_byte[0])*60);
//							az_byte[2]=(uint16)((az_float-az_byte[0]-az_byte[1]/60.0)*3600);
//
//							alt_byte[0]=(uint8)alt_float;
//							alt_byte[1]=(uint8)((alt_float-alt_byte[0])*60);
//							alt_byte[2]=(uint8)((alt_float-alt_byte[0]-alt_byte[1]/60.0)*3600);
//							sprintf(g_sysmenu2110m_2En,"LName:%s",LandMarkName);
//					
//							sprintf(g_sysmenu2110m_3En,"LAzmu:%03dd%02dm%02ds",az_byte[0],az_byte[1],az_byte[2]);
//							sprintf(g_sysmenu2110m_4En,"LAlti:%02dd%02dm%02ds",alt_byte[0],alt_byte[1],alt_byte[2]);
//						
//							
//				          	break;
//						case 1:
//			           		gstrlineEn1="Add: ";
//					   		break;
//					   	default :
//					   		break;
//				    }	
//				   	gstrlineEn2=g_sysmenu2110m_2En;
//					gstrlineEn3=g_sysmenu2110m_3En;
//					gstrlineEn4=g_sysmenu2110m_4En;
//					gstrlineEn5="";
//					gstrlineEn6="";
//					gstrlineEn7="";
//					gstrlineEn8="";			  
//					g_mShowMenurowEn=10;
//					g_mShowLangauge=ENGLISH;
//			  		break;
				

				//������˵�

				//ÿ������		   
			   case SYS_SUB3SUB1NOW_APH: 
			        
					GetSunSysObject(g_mSunSysObjectNum,&g_mObjRa1,&g_mObjDec1);	
					
					gstrlineEn1= g_sysmenu2200object_nameEn; 



				   	g_mStarRiseTime=FSRiseSettime(1,g_mObjRa1,g_mObjDec1,g_mGoto.m_nLongitude,g_mGoto.m_nAtitude, g_mGoto.m_nTimeZone);
					g_mStarTransitTime=FSRiseSettime(2,g_mObjRa1,g_mObjDec1,g_mGoto.m_nLongitude,g_mGoto.m_nAtitude, g_mGoto.m_nTimeZone);
					g_mStarSetTime=FSRiseSettime(3,g_mObjRa1,g_mObjDec1,g_mGoto.m_nLongitude,g_mGoto.m_nAtitude, g_mGoto.m_nTimeZone);
  
				
			        sprintf(gstrtemp3,"RiseTime:   %02dh%02dm",(int)g_mStarRiseTime,(int)((g_mStarRiseTime-(int)g_mStarRiseTime)*60));
					gstrlineEn3=gstrtemp3;
					sprintf(gstrtemp5,"TransitTime:%02dh%02dm",(int)g_mStarTransitTime,(int)((g_mStarTransitTime-(int)g_mStarTransitTime)*60));
			        gstrlineEn5=gstrtemp5;
					sprintf(gstrtemp7,"SetTime:    %02dh%02dm",(int)g_mStarSetTime,(int)((g_mStarSetTime-(int)g_mStarSetTime)*60));
			        gstrlineEn7=gstrtemp7;

					gstrlineEn2="                    ";
					gstrlineEn4="                    ";
					gstrlineEn6="                    ";
					gstrlineEn8="                    ";

	
//	               if(g_mSunSysObjectNum==9)
//				   {
//				      	GetSunSysObject(0,&g_mObjRa1,&g_mObjDec1);	   
//				   }
//				   else
//				   {
//				     	GetSunSysObject(g_mSunSysObjectNum+1,&g_mObjRa1,&g_mObjDec1);	   
//				       
//				   }
//	               	gstrlineEn5= g_sysmenu2200object_nameEn; 
//
//					g_mStarRiseTime=FSRiseSettime(1,g_mObjRa2,g_mObjDec2,g_mGoto.m_nLongitude,g_mGoto.m_nAtitude, g_mGoto.m_nTimeZone);
//					g_mStarTransitTime=FSRiseSettime(2,g_mObjRa2,g_mObjDec2,g_mGoto.m_nLongitude,g_mGoto.m_nAtitude, g_mGoto.m_nTimeZone);
//					g_mStarSetTime=FSRiseSettime(3,g_mObjRa2,g_mObjDec2,g_mGoto.m_nLongitude,g_mGoto.m_nAtitude, g_mGoto.m_nTimeZone);
//	
//			
//										   
//			        sprintf(gstrtemp5,"RiseTime:   %02dh%02dm",(int)g_mStarRiseTime,(int)((g_mStarRiseTime-(int)g_mStarRiseTime)*60));
//					gstrlineEn6=gstrtemp5;
//					sprintf(gstrtemp6,"TransitTime:%02dh%02dm",(int)g_mStarTransitTime,(int)((g_mStarTransitTime-(int)g_mStarTransitTime)*60));
//			        gstrlineEn7=gstrtemp6;
//					sprintf(gstrtemp7,"SetTime:    %02dh%02dm",(int)g_mStarSetTime,(int)((g_mStarSetTime-(int)g_mStarSetTime)*60));
//			        gstrlineEn8=gstrtemp7;
//	

					g_mShowMenurowEn=0;	
					g_mShowLangauge=ENGLISH;
		     	break; 
				//��������
				 case SYS_SUB3SUB2_STARRISESET:
					sprintf(gstrtemp1,"RiseTime:   %02dh%02dm",(int)g_mStarRiseTime,(int)((g_mStarRiseTime-(int)g_mStarRiseTime)*60.0));
					gstrlineEn1=gstrtemp1;
			        sprintf(gstrtemp2,"TransitTime:%02dh%02dm",(int)g_mStarTransitTime,(int)((g_mStarTransitTime-(int)g_mStarTransitTime)*60.0));
					gstrlineEn3=gstrtemp2;
			        sprintf(gstrtemp3,"SetTime:    %02dh%02dm",(int)g_mStarSetTime,(int)((g_mStarSetTime-(int)g_mStarSetTime)*60.0));
					gstrlineEn5=gstrtemp3;
					gstrlineEn2="";
					gstrlineEn4="";
					gstrlineEn6="";
					gstrlineEn7="";
					gstrlineEn8="";
					g_mShowMenurowEn=0;
					g_mShowLangauge=ENGLISH;
		    	break;
				
				//��������
			   	case SYS_SUB3SUB3_MOONPHASE	:			  
			      	g_mShowMenurowEn=10;
					g_mShowLangauge=ENGLISH;
				    break;
				//����ʱ�Ӳ˵���ʾ����
			   	case SYS_SUB3SUB4TIMER_ONOFF:
					sprintf(g_sysmenu3403onEn,"%5lds",g_mObjTimer_sec);
			        gstrlineEn1=g_sysmenu3401onEn;
					gstrlineEn2="";
					gstrlineEn3=g_sysmenu3402onEn;
					gstrlineEn4="";
					gstrlineEn5=g_sysmenu3403onEn;
					gstrlineEn6="";
					gstrlineEn8="";
					gstrlineEn7=g_sysmenu3404onEn;
					g_mShowMenurowEn=0;
					g_mShowLangauge=ENGLISH;
				    break;
				case SYS_SUB3SUB4TIMER_INPUT:
			        gstrlineEn1=g_sysmenu3401offEn;
					gstrlineEn2="";
					gstrlineEn3=g_sysmenu3402offEn;
					gstrlineEn4="";
					gstrlineEn5=g_sysmenu3403offEn;
					gstrlineEn6="";
					gstrlineEn7=g_sysmenu3404offEn;	
					gstrlineEn8="";
					g_mShowMenurowEn=10;
					g_mShowLangauge=ENGLISH;
				    break;
					//��ʱ�����Ӳ˵���ʾ����
			   	case SYS_SUB3SUB5ALARM_INPUT:
			        gstrlineEn1=g_sysmenu3500alarm_titleEn;
					gstrlineEn2="";
					gstrlineEn3=g_sysmenu3500alarm_inputEn;
					gstrlineEn4="";
					gstrlineEn5="";
					gstrlineEn6="";
					gstrlineEn8="";
					gstrlineEn7=g_sysmenu3500alarm_onoffEn;			
					g_mShowMenurowEn=10;
					g_mShowLangauge=ENGLISH;
				    break;
				case SYS_SUB3SUB5ALARM_ONOFF:
					gstrlineEn1="";
			        gstrlineEn2=g_sysmenu3500alarm_off1En;
					gstrlineEn3="";
					gstrlineEn4="";
					gstrlineEn5="";
					gstrlineEn6="";
					gstrlineEn8="";
					gstrlineEn7=g_sysmenu3500alarm_off4En;
					g_mShowMenurowEn=0;
					g_mShowLangauge=ENGLISH;
				    break;
				//Ŀ����Ұ��Ѱ��ʾ����
				case SYS_SUB3SUB6SUB1LOV_TELTYPE1:
				    gstrlineEn1=g_sysmenu3601lov_teltype1En;
					gstrlineEn2="";
					gstrlineEn3=g_sysmenu3601lov_data1En;
					gstrlineEn4="";
					gstrlineEn5="";
					gstrlineEn6="";
					gstrlineEn7="";
					gstrlineEn8="";
					g_mShowMenurowEn=0;
					g_mShowLangauge=ENGLISH;
				    break;
				//���ʼ�����ʾ����
				case SYS_SUB3SUB6SUB2M_MF:   
			        gstrlineEn1=g_sysmenu3602m_titleEn;
					gstrlineEn2="";
					gstrlineEn3=g_sysmenu3602m_mfEn;
					gstrlineEn4="";
					gstrlineEn5=g_sysmenu3602m_sfEn;
					gstrlineEn6="";
					gstrlineEn7=g_sysmenu3602m_dataEn;
					gstrlineEn8="";
					g_mShowMenurowEn=10;
					g_mShowLangauge=ENGLISH;
			      break;
			   case SYS_SUB3SUB6SUB2M_SF:   
		            gstrlineEn1=g_sysmenu3602m_titleEn;
					gstrlineEn2="";
					gstrlineEn3=g_sysmenu3602m_mfEn;
					gstrlineEn4="";
					gstrlineEn5=g_sysmenu3602m_sfEn;
					gstrlineEn6="";
					gstrlineEn7=g_sysmenu3602m_dataEn;
					gstrlineEn8="";
					g_mShowMenurowEn=10;
					g_mShowLangauge=ENGLISH;
			      break;	
					case SYS_SUB3SUB6SUB2M_MF1:  
					case SYS_SUB3SUB6SUB2M_SF1: 
					case SYS_SUB3SUB6SUB2M_MFOV:  
			        gstrlineEn1=g_sysmenu3602m_titleEn1;
					gstrlineEn2="";
					gstrlineEn3=g_sysmenu3602m_mfEn;
					gstrlineEn4="";
					gstrlineEn5=g_sysmenu3602m_sfEn;
					gstrlineEn6="";
					gstrlineEn7=g_sysmenu3602m_mfovEn;
					gstrlineEn8=g_sysmenu3602m_dataEn1;
					g_mShowMenurowEn=10;
					g_mShowLangauge=ENGLISH;
			      break;

			   
			   case SYS_SUB3SUB6SUB2M_Multi:	
					sprintf(g_sysmenu3602m_data,"MultiplyM:%d",g_mObjM_Multi);
				    gstrlineEn1=g_sysmenu3602m_titleEn;
					gstrlineEn2="";
					gstrlineEn3=g_sysmenu3602m_mfEn;
					gstrlineEn4="";
					gstrlineEn5=g_sysmenu3602m_sfEn;
					gstrlineEn6="";
					gstrlineEn7=g_sysmenu3602m_dataEn; 
					gstrlineEn8="";
					g_mShowMenurowEn=0;
					g_mShowLangauge=ENGLISH;  
					break;
			   //����Ұ��������
				case SYS_SUB3SUB8MENU1Screen:
					gstrlineEn1=g_sysmenu380011En;
					gstrlineEn2="";
					gstrlineEn3=g_sysmenu380012En;
					gstrlineEn4="";
					gstrlineEn5=g_sysmenu380013En;
					gstrlineEn6="";
					gstrlineEn7=g_sysmenu380014En;
					gstrlineEn8="";
					g_mShowMenurowEn=0;
					g_mShowLangauge=ENGLISH;
				    break;

		
			  //������˵�
			  
			    //ʱ������
		      case  SYS_SUB4SUB1_SETTIME:

			        gstrlineEn1="Date and Time Set: ";
					gstrlineEn2="";
					gstrlineEn3=g_sysmenu4100dateEn;
					gstrlineEn4="           YYYY-MM-DD";
					gstrlineEn5=g_sysmenu4100timeEn;
					gstrlineEn6="         HH:MM:SS";
					gstrlineEn7="";
	                gstrlineEn8="";
					g_mShowMenurowEn=10;
					g_mShowLangauge=ENGLISH;

			   break;
			   
			//����ʱ������
			case SYS_SUB4SUB2MENU1:
				gstrlineEn1=g_sysmenu420011En;   
				gstrlineEn2="";
				gstrlineEn3=g_sysmenu420012En;
				gstrlineEn4="";
				gstrlineEn5=g_sysmenu420013En;
				if(g_mSysInitGuide==1)
				{
				  gstrlineEn6="hit direction key!";
				 }
				 else
				 {
				   gstrlineEn6="Restart & Change!";
				 }
				gstrlineEn7=g_sysmenu420014En;
				gstrlineEn8="";
				g_mShowMenurowEn=0;
				g_mShowLangauge=ENGLISH;
			    break;
			case SYS_SUB4SUB2MENU2:
				gstrlineEn1=g_sysmenu420021En;
				gstrlineEn2="";
				gstrlineEn3=g_sysmenu420022En;
				gstrlineEn4="";
				gstrlineEn5=g_sysmenu420023En;
				if(g_mSysInitGuide==1)
				{
				  gstrlineEn6="hit direction key!";
				 }
				 else
				 {
				   gstrlineEn6="Restart & Change!";
				 }
				gstrlineEn7=g_sysmenu420024En;
				gstrlineEn8="";
				g_mShowMenurowEn=0;
				g_mShowLangauge=ENGLISH;
			    break;
			//����ѡ��
	       case SYS_SUB4SUB3SUN1_CITYSEL:

			      GetWorldCity170(Nationnum+Citynum,&city1);

			   	if(city1.Lon>=0)
				{
			          sprintf(gstrtemp5,"     Lon:E%03d %02d          ",abs((int)city1.Lon),abs((int)((city1.Lon-(int)city1.Lon)*60)));
				}
				else
				{
			     	  sprintf(gstrtemp5,"     Lon:W%03d %02d         ",abs((int)city1.Lon),abs((int)((city1.Lon-(int)city1.Lon)*60)));	
				}
				 if(abs((int)city1.Lon)<100)
				   {
				     gstrtemp5[10]=' ';
				   }
				   	if(abs((int)city1.Lon)<10)
				   {
				     gstrtemp5[11]=' ';
				   }

				   if(abs((int)((city1.Lon-(int)city1.Lon)*60))<10)
				   {
				     gstrtemp5[14]=' ';
				   }
		

				 if(city1.Lat>=0)
				{
			          sprintf(gstrtemp7,"     Lat:N %02d %02d          ",abs((int)city1.Lat),abs((int)((city1.Lat-(int)city1.Lat)*60)));		}
				else
				{
			     	  sprintf(gstrtemp7,"     Lat:S %02d %02d         ",abs((int)city1.Lat),abs((int)((city1.Lat-(int)city1.Lat)*60)));	
				}
				
				   	if(abs((int)city1.Lat)<10)
				   {
				     gstrtemp7[11]=' ';
				   }

				   if(abs((int)((city1.Lat-(int)city1.Lat)*60))<10)
				   {
				     gstrtemp7[14]=' ';
				   }
//				   }
			  
//				 if(g_mShowLangauge==CHANESE)
//				{
//				   sprintf(gstrtemp8,"    Zone:E%d   ",abs(8));
//				 }
//				 else
//				 {
				   	if(city1.Zone>0)
					{
					   sprintf(gstrtemp8,"    Zone:E%d   ",abs(city1.Zone));
					 }
					 else if(city1.Zone	<0)
					{
					   sprintf(gstrtemp8,"    Zone:W%d    ",abs(city1.Zone));
					 }
					 else
					 {
					    sprintf(gstrtemp8,"    Zone:%d    ",abs(city1.Zone));
					 }
//				 }

			

			    gstrlineEn1=city1.CountryEn;

				gstrlineEn2=city1.CityEn;
			    gstrlineEn3=gstrtemp5;
				gstrlineEn4=gstrtemp7;
				gstrlineEn5=gstrtemp8;//"                     ";
				gstrlineEn6="                     ";
				gstrlineEn7="up&down key: country!";
				gstrlineEn8="left&right key: city!";			  
				

//				gstrlineCn1=city.PrvcCn;
//				gstrlineCn2=city.CityCn;
				
				g_mShowMenurowEn=0;
//				g_mShowMenurowCn=0;
				//FSelShowLanguage();
				g_mShowLangauge=ENGLISH;	

			    break;
		
			  //�Զ���ص����
		      case SYS_SUB4SUB3_SETSITE :
			        //	GetCustomerCityInfo(CustomCityNum_temp,Nation,Lon,Lat,Zon,Alt);
//						g_mSitLon=Lon[1]+Lon[2]/60.0;
//						if(Lon[0]=='W')
//						{
//						   g_mSitLon=-1.0*g_mSitLon;
//						 }
//						g_mSitLat=Lat[1]+Lat[2]/60.0;
//					    if(Lat[0]=='S')
//						 {
//						   g_mSitLat=-1.0*g_mSitLat;
//						 }
//						g_mTimeZone=Zon[1];
//	                	if(Zon[0]=='W')
//						{
//						   g_mTimeZone=-1.0*g_mTimeZone;
//						 }
//						 g_mSitAlt=*Alt;  						 			

				  
				           		gstrlineEn1="Please Input Data: ";
								gstrlineEn3=g_sysmenu4300sitenameEn;
								gstrlineEn4=g_sysmenu4300sitelonEn;
								gstrlineEn5=g_sysmenu4300sitelatEn;
								gstrlineEn6=g_sysmenu4300sitezoneEn;
								//gstrlineEn4="";
								gstrlineEn7="";
								gstrlineEn8="";			  
								g_mShowMenurowEn=10;
				
						g_mShowLangauge=ENGLISH;	
			  		break;
	
					//���½��ģʽѡ������
					case SYS_SUB4SUB5SKY:
				        gstrlineEn1="Object Mode:";
						gstrlineEn2="";
						gstrlineEn3=g_sysmenu4500skyEn;
						gstrlineEn4="";
						gstrlineEn5=g_sysmenu4500landEn;
						gstrlineEn6="";
						gstrlineEn7="";
						gstrlineEn8="";
						g_mShowMenurowEn=3;
						g_mShowLangauge=ENGLISH;
					    break;
					case SYS_SUB4SUB5LAND:
				        gstrlineEn1="Object Mode:";
						gstrlineEn2="";
						gstrlineEn3=g_sysmenu4500skyEn;
						gstrlineEn4="";
						gstrlineEn5=g_sysmenu4500landEn;
						gstrlineEn6="";
						gstrlineEn7="";
						gstrlineEn8="";
						g_mShowMenurowEn=5;
						g_mShowLangauge=ENGLISH;
					    break;
						//��Զ��װ��ѡ������
					case SYS_SUB4SUB6AZ:
						gstrlineEn1="Telescope Mount:";
						gstrlineEn2="";
						gstrlineEn3=g_sysmenu4600azEn;
						gstrlineEn4="";
						gstrlineEn5=g_sysmenu4600eqEn;
						gstrlineEn6="";
						gstrlineEn7="";
						gstrlineEn8="";
						g_mShowMenurowEn=3;
						g_mShowLangauge=ENGLISH;
					    break;
					case SYS_SUB4SUB6EQ:
						gstrlineEn1="Telescope Mount:";
						gstrlineEn2="";
						gstrlineEn3=g_sysmenu4600azEn;
						gstrlineEn4="";
						gstrlineEn5=g_sysmenu4600eqEn;
						gstrlineEn6="";
						gstrlineEn7="";
						gstrlineEn8="";
						g_mShowMenurowEn=5;
						g_mShowLangauge=ENGLISH;
					    break;


			      //��Զ����������Ӳ˵�
				   	case SYS_SUB4SUB7_TELAZIALT_ZERO:			 
				        gstrlineEn1=g_sysmenu4700TitleEn;
						gstrlineEn3=g_sysmenu4700AziZeroEn;
						gstrlineEn5=g_sysmenu4700AltZeroEn;
						gstrlineEn4="        Range:0-360";
						gstrlineEn6="        Range:0-90";
						gstrlineEn7="";
						gstrlineEn8="";
                        if(tel_zero_error_num>0)
						{
						   tel_zero_error_num--;
						   gstrlineEn6="                                ";
						   gstrlineEn7=g_sysmenu4700AltZeroErrorEn;
						}
						else
						{
						    gstrlineEn6="                                        ";
						   gstrlineEn7="                                      ";
						}
						gstrlineEn2="                              ";
						gstrlineEn4="          Range:0-360";
						gstrlineEn6="          Range:0-90";
						g_mShowMenurowEn=10;
						g_mShowLangauge=ENGLISH;
					    break;

				 //��Զ�����������ȷ�Ӳ˵�
				   	case SYS_SUB4SUB7_TELZERO_OK:				 
				        gstrlineEn1=g_sysmenu4700TitleEn;
						gstrlineEn3=g_sysmenu4700AziZeroEn;
						gstrlineEn5=g_sysmenu4700AltZeroEn;
						gstrlineEn7=g_sysmenu4700AltZeroOkEn;
						gstrlineEn2="";
						gstrlineEn4="";
						gstrlineEn6="                                                       ";
						gstrlineEn8="";	
						g_mShowMenurowEn=10;
						g_mShowLangauge=ENGLISH;
					    break;


					//�˵�������ʾ����
					case SYS_SUB4SUB9EN:
				        gstrlineEn1=g_sysmenu4900enEn;
						gstrlineEn2=g_sysmenu4900gerEn;
						gstrlineEn3=g_sysmenu4900freEn;
						gstrlineEn4=g_sysmenu4900itaEn;
						gstrlineEn5=g_sysmenu4900spaEn;
						gstrlineEn6="";
						gstrlineEn7="";
						gstrlineEn8="";
						g_mShowMenurowEn=1;
						g_mShowLangauge=ENGLISH;
					    break;									
					case SYS_SUB4SUB9GER:
				        gstrlineEn1=g_sysmenu4900enEn;
						gstrlineEn2=g_sysmenu4900gerEn;
						gstrlineEn3=g_sysmenu4900freEn;
						gstrlineEn4=g_sysmenu4900itaEn;
						gstrlineEn5=g_sysmenu4900spaEn;
						gstrlineEn6="";
						gstrlineEn7="";
						gstrlineEn8="";
						g_mShowMenurowEn=2;
						g_mShowLangauge=ENGLISH;
					    break;
				    case SYS_SUB4SUB9FRE:
				        gstrlineEn1=g_sysmenu4900enEn;
						gstrlineEn2=g_sysmenu4900gerEn;
						gstrlineEn3=g_sysmenu4900freEn;
						gstrlineEn4=g_sysmenu4900itaEn;
						gstrlineEn5=g_sysmenu4900spaEn;
						gstrlineEn6="";
						gstrlineEn7="";
						gstrlineEn8="";
						g_mShowMenurowEn=3;
						g_mShowLangauge=ENGLISH;
					    break;
					case SYS_SUB4SUB9ITA:
				        gstrlineEn1=g_sysmenu4900enEn;
						gstrlineEn2=g_sysmenu4900gerEn;
						gstrlineEn3=g_sysmenu4900freEn;
						gstrlineEn4=g_sysmenu4900itaEn;
						gstrlineEn5=g_sysmenu4900spaEn;
						gstrlineEn6="";
						gstrlineEn7="";
						gstrlineEn8="";
						g_mShowMenurowEn=4;
						g_mShowLangauge=ENGLISH;
					    break;
				  case SYS_SUB4SUB9SPA:
				       gstrlineEn1=g_sysmenu4900enEn;
						gstrlineEn2=g_sysmenu4900gerEn;
						gstrlineEn3=g_sysmenu4900freEn;
						gstrlineEn4=g_sysmenu4900itaEn;
						gstrlineEn5=g_sysmenu4900spaEn;
						gstrlineEn6="";
						gstrlineEn7="";
						gstrlineEn8="";
						g_mShowMenurowEn=5;
						g_mShowLangauge=ENGLISH;
					    break;



					
				 //�Զ����ٶ�������ʾ����
				  case SYS_SUB4SUB8MENU4_RASPEED:
				    gstrlineEn1="Input Treaking Speed:";
					gstrlineEn2="";
					gstrlineEn3="";
					gstrlineEn4=g_sysmenu4800raspeedEn;
					gstrlineEn5="";
					gstrlineEn6="";
					gstrlineEn7="";
					gstrlineEn8="";
					g_mShowMenurowEn=10;
					g_mShowLangauge=ENGLISH;
					break;

			   ///**************************************
			  ///**************************************

				default :
				break;	
				
		 }
}
 //************************************************************************************************************************
//������ʾ����
void FSysMainShowSet()
{
       //double g_mjd;
	  //g_mjd=2454978.81424;

	   	g_mSitLon=g_mGoto.m_nLongitude;
		g_mSitLat=g_mGoto.m_nAtitude;
		g_mTimeZone=g_mGoto.m_nTimeZone;
//		g_mSitAlt=g_mGoto.m_nSiteHigh;

		g_mSitLon_du=(int)g_mSitLon;
		g_mSitLon_fen=(int)((g_mSitLon-g_mSitLon_du)*60);
		g_mSitLon_miao=60.0*(g_mSitLon*60.0-g_mSitLon_du*60.0-g_mSitLon_fen);

		g_mSitLat_du=(int)g_mSitLat;
		g_mSitLat_fen=(int)((g_mSitLat-g_mSitLat_du)*60);
		g_mSitLat_miao=60.0*(g_mSitLat*60.0-g_mSitLat_du*60.0-g_mSitLat_fen);


		//������ʾ����
		sprintf(gstrtemp1,"%04d-%02d-%02d",g_mDate_year,g_mDate_month,g_mDate_day);
        gstrlineEn1=gstrtemp1;
		//ʱ����ʾ���� 
		sprintf(gstrtemp2,"%02d:%02d:%02d",g_mTime_hour,g_mTime_minute,g_mTime_second);
        gstrlineEn2=gstrtemp2;

//		//��������ʾ����
//		sprintf(gstrtemp3,"JD:%.5f",g_mjd);
//        gstrlineEn3=gstrtemp3;
//
//        if(g_mTimeZone>=0)
//		{
//		   sprintf(gstrtemp4,"E%d",abs(g_mTimeZone));
//		 }
//		  else
//		  {
//		    sprintf(gstrtemp4,"W%d",abs(g_mTimeZone));
//		  }
//
//		  gstrlineEn4=gstrtemp4;

	//��ջ�½��Ŀ����ʾ����
	   switch(g_mSkyLand)
	  	{
		  case 0:
			gstrlineEn5="Sky ";
			break;
		  case 1: 
			gstrlineEn5="Land";
			break;
		 default:		
			break;
		}
	//�۲�ص㾭����ʾ����
    	if(g_mSitLon<0)
		{
	
			sprintf(gstrtemp6,"Site:W%03d?%02d'%02d^",abs(g_mSitLon_du),abs(g_mSitLon_fen),(uint8)(abs(g_mSitLon_miao)));
		}
			 
		else
            { 
			sprintf(gstrtemp6,"Site:E%03d?%02d'%02d^",abs(g_mSitLon_du),abs(g_mSitLon_fen),(uint8)(abs(g_mSitLon_miao)));
	
		}
	    gstrlineEn6=gstrtemp6;



	//��Զ��װ�ã���ƽʽ���ʽ����ʾ����
		switch(g_mAzEq)
		{
		case 0:
			gstrlineEn7="AZ";
			break;
		case 1: 
			gstrlineEn7="EQ";
			break;
		default:
			break;
		}  
	//�۲�ص�γ������	
    	if(g_mSitLat<0)
		{
			  sprintf(gstrtemp8,"     S%03d?%02d'%02d^",abs(g_mSitLat_du),abs(g_mSitLat_fen),(uint8)(abs(g_mSitLat_miao)));
		}
		else
		{
			 sprintf(gstrtemp8,"     N%03d?%02d'%02d^",abs(g_mSitLat_du),abs(g_mSitLat_fen),(uint8)(abs(g_mSitLat_miao)));
		} 
	
	    gstrlineEn8=gstrtemp8;




	  //GPS���������ʾ����
		switch(g_mGps)
		{
		case 0:
			gstrlineEn9="    ";
			break;
		case 1: 
			gstrlineEn9="GPS!";
			break;
		default:
			break;
		}

        //����Ŀ��ྭ��λ��ʾ
		switch(g_mAzEq)
		{
		 case 0:  
           sprintf(gstrtemp10," OBJ: %03d?%02d'%02.0f^",abs(g_mObjAzi_du),abs(g_mObjAzi_fen),fabs(g_mObjAzi_miao));
		 break;
    
		 case 1: 
			sprintf(gstrtemp10," OBJ: %03dh%02dm%02ds",g_mObjHourA_shi,g_mObjHourA_fen,(uint8)g_mObjHourA_miao);
			break;
		  default:
			break;
	 	}
		 gstrlineEn10=gstrtemp10;



	//�����ٶ�
      switch(g_mTrackSpeed)
		{
		case 0:
			gstrlineEn11="Cel";
			break;
		case 1: 
			gstrlineEn11="Sun";
			break;
		case 2: 
			gstrlineEn11="Lun";
			break;
		case 3: 
			gstrlineEn11="Def";
			break;
		default:
			break;
		}
	//Ŀ���γ��߶���ʾ����
		switch(g_mAzEq)
		{
		case 0:
		     if(g_mGoto.m_nStarEPos0>90)
			 {
			  sprintf(gstrtemp12,"      -%02d?%02d'%02d^",abs(g_mObjAlt_du),abs(g_mObjAlt_fen),abs(g_mObjAlt_miao));
			  }
			  else
			  {
			    sprintf(gstrtemp12,"      +%02d?%02d'%02d^",abs(g_mObjAlt_du),abs(g_mObjAlt_fen),abs(g_mObjAlt_miao));
			  }
			  
		
			break;																		 
		case 1: 
			if(g_gObjDec_sign1==-1)
			{
				sprintf(gstrtemp12,"      -%02d?%02d'%02d^",abs(g_mObjDec_du1),abs(g_mObjDec_fen1),abs((int)(g_mObjDec_miao1)));
			}
            else
			{
			    sprintf(gstrtemp12,"      +%02d?%02d'%02d^",g_mObjDec_du1,g_mObjDec_fen1,(uint8)(g_mObjDec_miao1));
			}
		
			break;
			
		  default:
			break;
		}
		gstrlineEn12=gstrtemp12;


	//�ֶ��ٶȵ���ʾ����	 
        switch(g_mHandSpeed)
		{
//		case 0:
//			//gstrlineEn13="X0  ";
//			break;
		case 1:
			gstrlineEn13="1X   ";
			break;
		case 2:
			gstrlineEn13="2X   ";
			break;
		case 3:
			gstrlineEn13="8X   ";
			break;
		case 4:
			gstrlineEn13="16X  ";
			break;
		case 5:
			gstrlineEn13="64X  ";
			break;
		case 6:
			gstrlineEn13="128X";
			break;
		case 7:
			gstrlineEn13="256X";
			break;
		case 8:
			gstrlineEn13="512X";
			break;
		case 9:
			gstrlineEn13="Max ";
			break;
		default:break;
		}



	   //��Զ���ྭ��λ��ʾ
	  
		switch(g_mAzEq)
		{
		case 0:
			    sprintf(gstrtemp14," OTA: %03d?%02d'%02d^",abs(g_mTelAzi_du),abs(g_mTelAzi_fen),(uint8)(abs(g_mTelAzi_miao)));
		
			break;
		case 1: 
	
		      sprintf(gstrtemp14," OTA: %03dh%02dm%02ds",g_mTelRa_shi,g_mTelRa_fen,(uint8)(abs(g_mTelRa_miao)));
		
			break;
		default:
			break;
		}
		gstrlineEn14=gstrtemp14;

		 

		switch(g_mAzEq)
		{
		case 0:
		    //if(g_mTelStatus==100)
	        // {			  
			//  sprintf(gstrtemp16,"      +%02d?%02d'%02d^",0,0,0);
			//  g_mTelAlt_miao=0;
			// }
			 //else
			 //{
				//if(g_mGoto.m_nTescpEPos>0) //��ʼ�����ƺ
				if((fabs(g_mGoto.m_nTescpEPos)>90)||(g_mTelAlt<0))//��ʼ�����춥
				{
					sprintf(gstrtemp16,"      -%02d?%02d'%02d^",abs(g_mTelAlt_du),abs(g_mTelAlt_fen),(uint8)(abs(g_mTelAlt_miao)));
				}
	            else
				{
				    sprintf(gstrtemp16,"      +%02d?%02d'%02d^",abs(g_mTelAlt_du),abs(g_mTelAlt_fen),(uint8)(abs(g_mTelAlt_miao)));
				}
		//	}
			break;

	     case 1: 
		 //if(g_mTelStatus==100)
	     //    {
		//	  sprintf(gstrtemp16,"      +%02d?%02d'%02d^",0,0,0);
		//	  g_mTelDec_miao=0;
		//	 }
		//	 else
		//	 {
			    if((g_mTelDec<0))
				{
					sprintf(gstrtemp16,"      -%02d?%02d'%02d      ",abs(g_mTelDec_du),abs(g_mTelDec_fen),(uint8)(abs(g_mTelDec_miao)));
				}
	            else
				{						   
				    sprintf(gstrtemp16,"      +%02d?%02d'%02d      ",abs(g_mTelDec_du),abs(g_mTelDec_fen),(uint8)(abs(g_mTelDec_miao)));
				}
		//	}
			break;	
			
		default:
			break;
		}
		gstrlineEn16=gstrtemp16;

				//��Զ������״̬			 
	    switch(g_mTelStatus)
		{
		case 0:
		case 100:
			gstrlineEn15="Stop";
			break;
		case 1:
			gstrlineEn15="Poin";
			break;
		case 2:
			gstrlineEn15="Trac";
		   
			break;
		case 3:
			gstrlineEn15="UdHn";
			break;
		default:
			gstrlineEn15="Slew";
			break;
		}
		//��Զ����γ��߶���ʾ����
	if((g_mPointNewStarTracking==1)&&(g_mTelStatus==2))//ָ���µ��ǲ�����
	{


	    gstrlineEn14=gstrtemp10;
		gstrlineEn16=gstrtemp12;
		gstrtemp14[1]='O';		
	    gstrtemp14[2]='T';		
		gstrtemp14[3]='A';
		
		gstrlineEn14=gstrtemp14;
		gstrlineEn16=gstrtemp16;
		//FBeep(1);
	}
	


}
	
	
//************************************************************************************************************************

//************************************************************************************************************************
//��Զ����������ʾ
int FSysMainShow()
{
	    
	DispEn(0,1,1,strlen(gstrlineEn1), gstrlineEn1);
	DispEn(0,1,14,strlen(gstrlineEn2), gstrlineEn2);


	if(m_TcpSynEnable==1)
	{
	   if(m_TcpSynFlash==0)//��Զ��ͬ����ʾ��˸
	   {
	     DispEn(0,2,1,22,">>>>synchronizing<<<<");
		 m_TcpSynFlash=1;	
	   }
	   else
	   {
	     DispEn(0,2,1,22,"                      ");
		 m_TcpSynFlash=0;
	   }
	    
	}
	else
	{
	   DispEn(0,2,1,22,"                      ");
	}


//	DispEn(0,2,8,strlen(gstrlineEn3), gstrlineEn3);
//	DispEn(0,2,1,strlen(gstrlineEn4), gstrlineEn4);

	DispEn(0,3,1,strlen(gstrlineEn5), gstrlineEn5);
	DispEn(0,3,6,9, gstrlineEn6);
	DispEn(0,3,16,2, gstrlineEn6+10);
	DispEn(0,3,19,2, gstrlineEn6+13);
	DispCh(0, 3,15,CharD);
	DispCh(0, 3,18,CharM);
	DispCh(0, 3,21,CharS);


	if(abs(g_mSitLon_du)<100)
	{
	  DispEn(0,3,12,1," "); 
	}
	if(abs(g_mSitLon_du)<10)
	{
	  DispEn(0,3,13,1," "); 
	}
	if(abs(g_mSitLon_fen)<10)
	{
	  DispEn(0,3,16,1," "); 
	}
	if(abs(g_mSitLon_miao)<10)
	{
	  DispEn(0,3,19,1," "); 
	}


	DispEn(0,4,1,strlen(gstrlineEn7), gstrlineEn7);
	DispEn(0,4,6,9, gstrlineEn8);
	DispEn(0,4,16,2, gstrlineEn8+10);
	DispEn(0,4,19,2, gstrlineEn8+13);
	DispCh(0, 4,15,CharD);
	DispCh(0, 4,18,CharM);
	DispCh(0, 4,21,CharS);
	if(abs(g_mSitLat_du)<100)
	{
	  DispEn(0,4,12,1," "); 
	}
	if(abs(g_mSitLat_du)<10)
	{
	  DispEn(0,4,13,1," "); 
	}
	if(abs(g_mSitLat_fen)<10)
	{
	  DispEn(0,4,16,1," "); 
	}
	if(abs(g_mSitLat_miao)<10)
	{
	  DispEn(0,4,19,1," "); 
	}


	DispEn(0,5,1,strlen(gstrlineEn9), gstrlineEn9);
	DispEn(0,5,6,9, gstrlineEn10);
	DispEn(0,5,16,2, gstrlineEn10+10);
	DispEn(0,5,19,2, gstrlineEn10+13);
	
	if(g_mAzEq==0)
	{  	
		DispCh(0, 5,15,CharD);
		DispCh(0, 5,18,CharM);
		DispCh(0, 5,21,CharS);
		if(abs(g_mObjAzi_du)<100)
		{
		  DispEn(0,5,12,1," "); 
		}
		if(abs(g_mObjAzi_du)<10)
		{
		  DispEn(0,5,13,1," "); 
		}
		if(abs(g_mObjAzi_fen)<10)
		{
		  DispEn(0,5,16,1," "); 
		}
		if(abs(g_mObjAzi_miao)<10)
		{
		  DispEn(0,5,19,1," "); 
		}
	}
	else
	{
	    DispEn(0, 5,15,1,"h");
		DispEn(0, 5,18,1,"m");
		DispEn(0, 5,21,1,"s");
		if(g_mObjHourA_shi<100)
		{
		  DispEn(0,5,12,1," "); 
		}
		if(g_mObjHourA_shi<10)
		{
		  DispEn(0,5,13,1," "); 
		}
		if(g_mObjHourA_fen<10)
		{
		  DispEn(0,5,16,1," "); 
		}
		if(g_mObjHourA_miao<10)
		{
		  DispEn(0,5,19,1," "); 
		}
		
	}
	


	DispEn(0,6,1,strlen(gstrlineEn11), gstrlineEn11);
	DispEn(0,6,6,9, gstrlineEn12);
	DispEn(0,6,16,2, gstrlineEn12+10);
	DispEn(0,6,19,2, gstrlineEn12+13);
	DispCh(0, 6,15,CharD);
	DispCh(0, 6,18,CharM);
	DispCh(0, 6,21,CharS);
	if(g_mAzEq==0)
	{  	
		
		if(abs(g_mObjAlt_du)<10)
		{
		  DispEn(0,6,13,1," "); 
		}
		if(abs(g_mObjAlt_fen)<10)
		{
		  DispEn(0,6,16,1," "); 
		}
		if(abs(g_mObjAlt_miao)<10)
		{
		  DispEn(0,6,19,1," "); 
		}
	}
	else
	{
	   
		
		if(abs(g_mObjDec_du1)<10)
		{
		  DispEn(0,6,13,1," "); 
		}
		if(abs(g_mObjDec_fen1)<10)
		{
		  DispEn(0,6,16,1," "); 
		}
		if(abs(g_mObjDec_miao1)<10)
		{
		  DispEn(0,6,19,1," "); 
		}
		
	}


	DispEn(0,7,1,strlen(gstrlineEn13), gstrlineEn13);
	DispEn(0,7,6,9, gstrlineEn14);
	DispEn(0,7,16,2, gstrlineEn14+10);
	DispEn(0,7,19,2, gstrlineEn14+13);
 if((g_mPointNewStarTracking==1)&&(g_mTelStatus==2))//ָ���µ��ǲ�����
  {
  	if(g_mAzEq==0)
	{  	
		DispCh(0, 7,15,CharD);
		DispCh(0, 7,18,CharM);
		DispCh(0, 7,21,CharS);
		if(abs(g_mObjAzi_du)<100)
		{
		  DispEn(0,7,12,1," "); 
		}
		if(abs(g_mObjAzi_du)<10)
		{
		  DispEn(0,7,13,1," "); 
		}
		if(abs(g_mObjAzi_fen)<10)
		{
		  DispEn(0,7,16,1," "); 
		}
		if(abs(g_mObjAzi_miao)<10)
		{
		  DispEn(0,7,19,1," "); 
		}
	}
	else
	{
	    DispEn(0, 7,15,1,"h");
		DispEn(0, 7,18,1,"m");
		DispEn(0, 7,21,1,"s");
		if(g_mObjHourA_shi<100)
		{
		  DispEn(0,7,12,1," "); 
		}
		if(g_mObjHourA_shi<10)
		{
		  DispEn(0,7,13,1," "); 
		}
		if(g_mObjHourA_fen<10)
		{
		  DispEn(0,7,16,1," "); 
		}
		if(g_mObjHourA_miao<10)
		{		   
		  DispEn(0,7,19,1," "); 
		}
		
	}
  }
  else
  {
	if(g_mAzEq==0)
	{  	
		DispCh(0, 7,15,CharD);
		DispCh(0, 7,18,CharM);
		DispCh(0, 7,21,CharS);
		if(abs(g_mTelAzi_du)<100)
		{
		  DispEn(0,7,12,1," "); 
		}
		if(abs(g_mTelAzi_du)<10)
		{
		  DispEn(0,7,13,1," "); 
		}
		if(abs(g_mTelAzi_fen)<10)
		{
		  DispEn(0,7,16,1," "); 
		}
		if(abs(g_mTelAzi_miao)<10)
		{
		  DispEn(0,7,19,1," "); 
		}
	}
	else
	{
	    DispEn(0, 7,15,1,"h");
		DispEn(0, 7,18,1,"m");
		DispEn(0, 7,21,1,"s");
		if(g_mTelRa_shi<100)
		{
		  DispEn(0,7,12,1," "); 
		}
		if(g_mTelRa_shi<10)
		{
		  DispEn(0,7,13,1," "); 
		}
		if(g_mTelRa_fen<10)
		{
		  DispEn(0,7,16,1," "); 
		}
		if(g_mTelRa_miao<10)
		{
		  DispEn(0,7,19,1," "); 
		}
	}

	}

	DispEn(0,8,1,strlen(gstrlineEn15), gstrlineEn15);
	DispEn(0,8,6,9, gstrlineEn16);
	DispEn(0,8,16,2, gstrlineEn16+10);
	DispEn(0,8,19,2, gstrlineEn16+13);
	DispCh(0, 8,15,CharD);
	DispCh(0, 8,18,CharM);
	DispCh(0, 8,21,CharS);

  if((g_mPointNewStarTracking==1)&&(g_mTelStatus==2))//ָ���µ��ǲ�����
  {
	if(g_mAzEq==0)
	{  	
		
		if(abs(g_mObjAlt_du)<10)
		{
		  DispEn(0,8,13,1," "); 
		}
		if(abs(g_mObjAlt_fen)<10)
		{
		  DispEn(0,8,16,1," "); 
		}
		if(abs(g_mObjAlt_miao)<10)
		{
		  DispEn(0,8,19,1," "); 
		}
	}
	else
	{
	   
		
		if(abs(g_mObjDec_du1)<10)
		{
		  DispEn(0,8,13,1," "); 
		}
		if(abs(g_mObjDec_fen1)<10)
		{
		  DispEn(0,8,16,1," "); 
		}
		if(abs(g_mObjDec_miao1)<10)
		{
		  DispEn(0,8,19,1," "); 
		}
		
	}

  }
  else
  {
	if(g_mAzEq==0)
	{  	
		
		if(abs(g_mTelAlt_du)<10)
		{
		  DispEn(0,8,13,1," "); 
		}
		if(abs(g_mTelAlt_fen)<10)
		{
		  DispEn(0,8,16,1," "); 
		}
		if(abs(g_mTelAlt_miao)<10)
		{
		  DispEn(0,8,19,1," "); 
		}
	}
	else
	{
	  	
		if(abs(g_mTelDec_du)<10)
		{
		  DispEn(0,8,13,1," "); 
		}
		if(abs(g_mTelDec_fen)<10)
		{
		  DispEn(0,8,16,1," "); 
		}
		if(abs(g_mTelDec_miao)<10)
		{
		  DispEn(0,8,19,1," "); 
		}
		
	}
   }

}

//************************************************************************************************************************

//************************************************************************************************************************

//������ʾ����
void  FHelpShow()
{
   if(g_mshowed1!=g_mshowed2)  //��Զ��״̬����Ͳ�ˢ��,״̬���ˢ��
		{
		       //LCDRfrsh();		     
			  g_mshowed2=g_mshowed1;
		} 

// 	if(g_mMenuLangauge==CHANESE)
//	{
//						
//        switch(g_nsysstatus )
//    	{	 
//	          case SYS_MAINSHOWHELP:
//		      switch(g_mmainhelpshow)
//			  {
//			     case 1:
//				  	  DispUn(0,1,1,144, (uint16*)helpmain1_1CN);
//			          DispUn(0,2,1,144, (uint16*)helpmain1_2CN);
//			          DispUn(0,3,1,144, (uint16*)helpmain1_3CN);
//			          //DispUn(0,4,1,144, (uint16*)helpmain1_4CN);
//					  break;
//                case 2:
//				  	  DispUn(0,1,1,144, (uint16*)helpmain2_1CN);
//			          DispUn(0,2,1,144, (uint16*)helpmain2_2CN);
//			          DispUn(0,3,1,144, (uint16*)helpmain2_3CN);
//			          //DispUn(0,4,1,144, (uint16*)helpmain1_4CN);
//					  break;
//				case 3:
//				  	  DispUn(0,1,1,144, (uint16*)helpmain3_1CN);
//			          DispUn(0,2,1,144, (uint16*)helpmain3_2CN);
//			          //DispUn(0,3,1,144, (uint16*)helpmain1_3CN);
//			          //DispUn(0,4,1,144, (uint16*)helpmain1_4CN);
//					  break;
//				case 4:
//				  	  DispUn(0,1,1,144, (uint16*)helpmain4_1CN);
//			          DispUn(0,2,1,144, (uint16*)helpmain4_2CN);
//			          //DispUn(0,3,1,144, (uint16*)helpmain4_3CN);
//			          //DispUn(0,4,1,144, (uint16*)helpmain1_4CN);
//					  break; 
//				case 5:
//				  	  DispUn(0,1,1,144, (uint16*)helpmain5_1CN);
//			          DispUn(0,2,1,144, (uint16*)helpmain5_2CN);
//			          DispUn(0,3,1,144, (uint16*)helpmain5_3CN);
//			          //DispUn(0,4,1,144, (uint16*)helpmain1_4CN);
//					  break;
//				case 6:
//				  	  DispUn(0,1,1,144, (uint16*)helpmain6_1CN);
//			          DispUn(0,2,1,144, (uint16*)helpmain6_2CN);
//			          DispUn(0,3,1,144, (uint16*)helpmain6_3CN);
//			          //DispUn(0,4,1,144, (uint16*)helpmain1_4CN);
//					  break;
//				case 7:
//				  	  DispUn(0,1,1,144, (uint16*)helpmain7_1CN);
//			          DispUn(0,2,1,144, (uint16*)helpmain7_2CN);
//			          DispUn(0,3,1,144, (uint16*)helpmain7_3CN);
//			          //DispUn(0,4,1,144, (uint16*)helpmain1_4CN);
//					  break;
//				case 8:
//				  	  DispUn(0,1,1,144, (uint16*)helpmain8_1CN);
//			          DispUn(0,2,1,144, (uint16*)helpmain8_2CN);
//			          DispUn(0,3,1,144, (uint16*)helpmain8_3CN);
//			          DispUn(0,4,1,144, (uint16*)helpmain8_4CN);
//					  break;
//				case 9:
//				  	  DispUn(0,1,1,144, (uint16*)helpmain9_1CN);
//			          DispUn(0,2,1,144, (uint16*)helpmain9_2CN);
//			          DispUn(0,3,1,144, (uint16*)helpmain9_3CN);
//			          //DispUn(0,4,1,144, (uint16*)helpmain1_4CN);
//					  break;
//				case 10:
//				  	  DispUn(0,1,1,144, (uint16*)helpmain10_1CN);
//			          DispUn(0,2,1,144, (uint16*)helpmain10_2CN);
//			          //DispUn(0,3,1,144, (uint16*)helpmain1_3CN);
//			          //DispUn(0,4,1,144, (uint16*)helpmain1_4CN);
//					  break;
//
//			  }
//			  break;
//				
//			case SYS_MAINMENU1HELP:
//				  DispCn(0,1,1,108,helpmenu11CN);
//			      DispCn(0,2,1,144,&(helpmenu11CN[12]));
//			      DispCn(0,3,1,144,&(helpmenu11CN[28]));
//			      DispCn(0,4,1,144,&(helpmenu11CN[44]));
//				break;
//			case SYS_MAINMENU2HELP:
//				  DispCn(0,1,1,90,helpmenu12CN);
//			      DispCn(0,2,1,144,&(helpmenu12CN[10]));
//			      DispCn(0,3,1,144,&(helpmenu12CN[26]));
//			      DispCn(0,4,1,144,&(helpmenu12CN[42]));
//				break;
//			case SYS_MAINMENU3HELP:
//				  DispCn(0,1,1,90,helpmenu13CN);
//			      DispCn(0,2,1,144,&(helpmenu13CN[10]));
//			      DispCn(0,3,1,144,&(helpmenu13CN[26]));
//			     //DispCn(0,4,1,144,&(helpmenu13CN[44]));
//				break;
//			case SYS_MAINMENU4HELP:
//				  DispCn(0,1,1,90,helpmenu14CN);
//			      DispCn(0,2,1,144,&(helpmenu14CN[10]));
//			     // DispCn(0,3,1,144, (uint16*)&(helpmenu14CN[28]));
//			      //DispCn(0,4,1,144, (uint16*)&(helpmenu14CN[44]));
//				break;
//					  /////////////////////////////////////////////////////
//			 //��Զ��У׼
//			 case SYS_SUB1MENU1HELP:
//			      DispCn(0,1,1,90,helpmenu211CN);
//			      DispCn(0,2,1,144,&(helpmenu211CN[10]));
//			      DispCn(0,3,1,144,&(helpmenu211CN[26]));
//			      DispCn(0,4,1,144,&(helpmenu211CN[42]));
//			    break;
//			case SYS_SUB1MENU2HELP:		    
//				  DispCn(0,1,1,90,helpmenu212CN);
//			      DispCn(0,2,1,144,&(helpmenu212CN[10]));
//			      DispCn(0,3,1,144,&(helpmenu212CN[26]));
//			      //DispCn(0,4,1,144,&(helpmenu212CN[42]));
//				break;
//			case SYS_SUB1MENU3HELP:
//				 DispCn(0,1,1,90,helpmenu213CN);
//			      DispCn(0,2,1,144,&(helpmenu213CN[10]));
//			      DispCn(0,3,1,144,&(helpmenu213CN[26]));
//			      //DispCn(0,4,1,144,&(helpmenu213CN[42]));
//				break;
//			case SYS_SUB1MENU4HELP:
//				 DispCn(0,1,1,90,helpmenu214CN);
//			      DispCn(0,2,1,144,&(helpmenu214CN[10]));
//			      DispCn(0,3,1,144,&(helpmenu214CN[26]));
//			     // DispCn(0,4,1,144,&(helpmenu214CN[42]));
//				break;
//			case SYS_SUB1MENU5HELP:
//				  DispCn(0,1,1,90,helpmenu215CN);
//			      DispCn(0,2,1,144,&(helpmenu215CN[10]));
//			      DispCn(0,3,1,144,&(helpmenu215CN[26]));
//			      //DispCn(0,4,1,144,&(helpmenu215CN[42]));
//			    break;
//			case SYS_SUB1MENU6HELP:
//				 DispCn(0,1,1,108,helpmenu216CN);
//			      DispCn(0,2,1,144,&(helpmenu216CN[12]));
//			      DispCn(0,3,1,144,&(helpmenu216CN[28]));
//			      //DispCn(0,4,1,144,&(helpmenu216CN[44]));
//				break;
//			case SYS_SUB1MENU7HELP:
//				 DispCn(0,1,1,144,helpmenu217CN);
//			      DispCn(0,2,1,144,&(helpmenu217CN[16]));
//			      DispCn(0,3,1,144,&(helpmenu217CN[32]));
//			      //DispCn(0,4,1,144,&(helpmenu217CN[48]));
//				break;
//			case SYS_SUB1MENU8HELP:
//				 DispCn(0,1,1,126,helpmenu218CN);
//			      DispCn(0,2,1,144,&(helpmenu218CN[14]));
//			      DispCn(0,3,1,144,&(helpmenu218CN[30]));
//			     // DispCn(0,4,1,144,&(helpmenu218CN[46]));
//				break;
//			case SYS_SUB1MENU9HELP:
//				 DispCn(0,1,1,144,helpmenu219CN);
//			      DispCn(0,2,1,144,&(helpmenu219CN[16]));
//			      DispCn(0,3,1,144,&(helpmenu219CN[32]));
//			      DispCn(0,4,1,144,&(helpmenu219CN[48]));
//			    break;
//			case SYS_SUB1MENU11HELP:
//				 DispCn(0,1,1,126,helpmenu2110CN);
//			      DispCn(0,2,1,144,&(helpmenu2110CN[14]));
//			      DispCn(0,3,1,144,&(helpmenu2110CN[30]));
//			      //DispCn(0,4,1,144,&(helpmenu2110CN[46]));
//				break;
//			case SYS_SUB1MENU12HELP:
//				 DispCn(0,1,1,126,helpmenu2111CN);
//			      DispCn(0,2,1,144,&(helpmenu2111CN[14]));
//			      DispCn(0,3,1,144,&(helpmenu2111CN[30]));
//			      //DispCn(0,4,1,144,&(helpmenu2111CN[468]));
//				break;
//		
//			 //Ŀ�굼���Ӳ˵�
//			case SYS_SUB2MENU1HELP:
//				 DispCn(0,1,1,72,helpmenu221CN);
//			      DispCn(0,2,1,144,&(helpmenu221CN[8]));
//			      DispCn(0,3,1,144,&(helpmenu221CN[24]));
//			      //DispCn(0,4,1,144,&(helpmenu221CN[40]));
//			    break;
//			case SYS_SUB2MENU2HELP:	
//				 DispCn(0,1,1,54,helpmenu222CN);
//			      DispCn(0,2,1,144,&(helpmenu222CN[6]));
//			      //DispCn(0,3,1,144,&(helpmenu222CN[22]));
//			      //DispCn(0,4,1,144,&(helpmenu222CN[38]));
//				break;
//			case SYS_SUB2MENU3HELP:
//				 DispCn(0,1,1,90,helpmenu223CN);
//			      DispCn(0,2,1,144,&(helpmenu223CN[10]));
//			      DispCn(0,3,1,144,&(helpmenu223CN[26]));
//			      //DispCn(0,4,1,144,&(helpmenu223CN[42]));
//				break;
//			case SYS_SUB2MENU4HELP:
//				 DispCn(0,1,1,99,helpmenu224CN);
//			      DispCn(0,2,1,135,&(helpmenu224CN[12]));
//			      DispCn(0,3,1,144,&(helpmenu224CN[34]));
//			      //DispCn(0,4,1,144,&(helpmenu224CN[44]));
//				break;
//			case SYS_SUB2MENU5HELP:
//				 DispCn(0,1,1,108,helpmenu225CN);
//			      DispCn(0,2,1,135,&(helpmenu225CN[16]));
//			      DispCn(0,3,1,144,&(helpmenu225CN[34]));
//			      //DispCn(0,4,1,144,&(helpmenu225CN[48]));
//			    break;
//			case SYS_SUB2MENU6HELP:
//				 DispCn(0,1,1,99,helpmenu226CN);
//			      DispCn(0,2,1,144,&(helpmenu226CN[14]));
//			      DispCn(0,3,1,144,&(helpmenu226CN[32]));
//			      //DispCn(0,4,1,144,&(helpmenu226CN[46]));
//				break;
//			case SYS_SUB2MENU7HELP:
//				 DispCn(0,1,1,99,helpmenu227CN);
//			      DispCn(0,2,1,135,&(helpmenu227CN[16]));
//			      DispCn(0,3,1,144,&(helpmenu227CN[34]));
//			      //DispCn(0,4,1,144,&(helpmenu227CN[48]));
//				break;
//			case SYS_SUB2MENU8HELP:
//				 DispCn(0,1,1,99,helpmenu228CN);
//			      DispCn(0,2,1,144,&(helpmenu228CN[18]));
//			      DispCn(0,3,1,144,&(helpmenu228CN[40]));
//			      //DispCn(0,4,1,144,&(helpmenu228CN[50]));
//				break;
//			case SYS_SUB2MENU9HELP:
//				 DispCn(0,1,1,59,helpmenu229CN);
//			      DispCn(0,2,1,135,&(helpmenu229CN[10]));
//			      DispCn(0,3,1,144,&(helpmenu229CN[28]));
//			      //DispCn(0,4,1,144,&(helpmenu229CN[42]));
//			    break;
//			case SYS_SUB2MENU11HELP:
//				  DispCn(0,1,1,144,helpmenu2210CN);
//			      DispCn(0,2,1,144,&(helpmenu2210CN[16]));
//			      DispCn(0,3,1,144,&(helpmenu2210CN[32]));
//			      DispCn(0,4,1,144,&(helpmenu2210CN[48]));
//				break;
//			case SYS_SUB2MENU12HELP:
//				  DispCn(0,1,1,126,helpmenu2211CN);
//			      DispCn(0,2,1,144,&(helpmenu2211CN[14]));
//			      DispCn(0,3,1,144,&(helpmenu2211CN[30]));
//			      //DispCn(0,4,1,144,&(helpmenu2211CN[46]));
//				break;
//			case SYS_SUB2MENU13HELP:
//				  DispCn(0,1,1,144,helpmenu2212CN);
//			      DispCn(0,2,1,144,&(helpmenu2212CN[16]));
//			      DispCn(0,3,1,144,&(helpmenu2212CN[32]));
//			      DispCn(0,4,1,144,&(helpmenu2212CN[48]));
//				break;
//		
//			 //���������Ӳ˵�
//			 case SYS_SUB3MENU1HELP:
//			     DispCn(0,1,1,90,helpmenu231CN);
//			      DispCn(0,2,1,144,&(helpmenu231CN[10]));
//			      DispCn(0,3,1,144,&(helpmenu231CN[26]));
//			      //DispCn(0,4,1,144,&(helpmenu231CN[42]));
//			    break;
//			case SYS_SUB3MENU2HELP:
//				 DispCn(0,1,1,90,helpmenu232CN);
//			      DispCn(0,2,1,144,&(helpmenu232CN[10]));
//			      DispCn(0,3,1,144,&(helpmenu232CN[26]));
//			      DispCn(0,4,1,144,&(helpmenu232CN[42]));
//				break;
//			case SYS_SUB3MENU3HELP:
//				 DispCn(0,1,1,90,helpmenu233CN);
//			      DispCn(0,2,1,144,&(helpmenu233CN[10]));
//			      //DispCn(0,3,1,144,&(helpmenu233CN[26]));
//			      //DispCn(0,4,1,144,&(helpmenu233CN[42]));
//				break;
//			case SYS_SUB3MENU4HELP:
//				 DispCn(0,1,1,72,helpmenu234CN);
//			      DispCn(0,2,1,144,&(helpmenu234CN[8]));
//			      //DispCn(0,3,1,144,&(helpmenu234CN[22]));
//			      //DispCn(0,4,1,144,&(helpmenu234CN[38]));
//				break;
//			case SYS_SUB3MENU5HELP:
//				 DispCn(0,1,1,90,helpmenu235CN);
//			      DispCn(0,2,1,144,&(helpmenu235CN[10]));
//			      //DispCn(0,3,1,144,&(helpmenu235CN[22]));
//			      //DispCn(0,4,1,144,&(helpmenu235CN[38]));
//			    break;
//			case SYS_SUB3MENU6HELP:
//				 DispCn(0,1,1,90,helpmenu236CN);
//			      DispCn(0,2,1,144,&(helpmenu236CN[10]));
//			      //DispCn(0,3,1,144,&(helpmenu236CN[28]));
//			     // DispCn(0,4,1,144,&(helpmenu236CN[44]));
//				break;
//			case SYS_SUB3MENU7HELP:
//				 DispCn(0,1,1,90,helpmenu237CN);
//			      DispCn(0,2,1,144,&(helpmenu237CN[10]));
//			      //DispCn(0,3,1,144,&(helpmenu237CN[28]));
//			      //DispCn(0,4,1,144,&(helpmenu237CN[44]));
//				break;
//			case SYS_SUB3MENU8HELP:
//				 DispCn(0,1,1,108,helpmenu238CN);
//			      DispCn(0,2,1,144,&(helpmenu238CN[12]));
//			      DispCn(0,3,1,144,&(helpmenu238CN[28]));
//			      //DispCn(0,4,1,144,&(helpmenu238CN[44]));
//				break;
//			case SYS_SUB3MENU9HELP:
//				 DispCn(0,1,1,90,helpmenu239CN);
//			      DispCn(0,2,1,144,&(helpmenu239CN[10]));
//			      //DispCn(0,3,1,144,&(helpmenu239CN[28]));
//			      //DispCn(0,4,1,144,&(helpmenu239CN[44]));
//			    break;
//			case SYS_SUB3MENU11HELP:
//				 DispCn(0,1,1,54,helpmenu2310CN);
//			      DispCn(0,2,1,144,&(helpmenu2310CN[6]));
//			      DispCn(0,3,1,144,&(helpmenu2310CN[22]));
//			      //DispCn(0,4,1,144,&(helpmenu2310CN[44]));
//				break;
//		
//			 //���������Ӳ˵�
//			case SYS_SUB4MENU1HELP:
//				 DispCn(0,1,1,90,helpmenu241CN);
//			      DispCn(0,2,1,144,&(helpmenu241CN[10]));
//			      DispCn(0,3,1,144,&(helpmenu241CN[26]));
//			      //DispCn(0,4,1,144,&(helpmenu241CN[44]));
//			    break;
//			case SYS_SUB4MENU2HELP:
//				 DispCn(0,1,1,90,helpmenu242CN);
//			      DispCn(0,2,1,144,&(helpmenu242CN[10]));
//			      //DispCn(0,3,1,144,&(helpmenu242CN[28]));
//			     // DispCn(0,4,1,144,&(helpmenu242CN[44]));
//				break;
//			case SYS_SUB4MENU3HELP:
//				 DispCn(0,1,1,90,helpmenu243CN);
//			      DispCn(0,2,1,144,&(helpmenu243CN[10]));
//			      DispCn(0,3,1,144,&(helpmenu243CN[26]));
//			      //DispCn(0,4,1,144,&(helpmenu243CN[44]));
//				break;
//		//	case SYS_SUB4MENU4HELP:
////		//		 DispCn(0,1,1,108,helpmenu11CN);
////			      DispCn(0,2,1,144,&(helpmenu11CN[12]));
////			      DispCn(0,3,1,144,&(helpmenu11CN[28]));
////			      DispCn(0,4,1,144,&(helpmenu11CN[44]));
////		//		break;
//			case SYS_SUB4MENU5HELP:
//				 DispCn(0,1,1,90,helpmenu244CN);
//			      DispCn(0,2,1,144,&(helpmenu244CN[12]));
//			      DispCn(0,3,1,144,&(helpmenu244CN[28]));
//			      DispCn(0,4,1,144,&(helpmenu244CN[44]));
//			    break;
//			case SYS_SUB4MENU6HELP:
//				 DispCn(0,1,1,126,helpmenu245CN);
//			      DispCn(0,2,1,144,&(helpmenu245CN[16]));
//			      //DispCn(0,3,1,144,&(helpmenu245CN[28]));
//			     // DispCn(0,4,1,144,&(helpmenu245CN[44]));
//				break;
//			case SYS_SUB4MENU7HELP:
//				 DispCn(0,1,1,144,helpmenu246CN);
//			      DispCn(0,2,1,144,&(helpmenu246CN[16]));
//			      DispCn(0,3,1,144,&(helpmenu246CN[32]));
//			      //DispCn(0,4,1,144,&(helpmenu246CN[48]));
//				break;
//			case SYS_SUB4MENU8HELP:
//				 DispCn(0,1,1,90,helpmenu247CN);
//			      DispCn(0,2,1,144,&(helpmenu247CN[10]));
//			      DispCn(0,3,1,144,&(helpmenu247CN[26]));
//			      //DispCn(0,4,1,144,&(helpmenu247CN[42]));
//				break;
//			case SYS_SUB4MENU9HELP:
//				 DispCn(0,1,1,90,helpmenu248CN);
//			      DispCn(0,2,1,144,&(helpmenu248CN[10]));
//			      DispCn(0,3,1,144,&(helpmenu248CN[26]));
//			      //DispCn(0,4,1,144,&(helpmenu248CN[44]));
//			    break;
//			case SYS_SUB4MENU11HELP:
//			       DispCn(0,1,1,108,helpmenu249CN);
//			      DispCn(0,2,1,144,&(helpmenu249CN[12]));
//			      //DispCn(0,3,1,144,&(helpmenu249CN[28]));
//			      //DispCn(0,4,1,144,&(helpmenu249CN[44]));
//				break;
//			case SYS_SUB4MENU12HELP:
//				 DispCn(0,1,1,108,helpmenu2410CN);
//			      DispCn(0,2,1,144,&(helpmenu2410CN[12]));
//			      DispCn(0,3,1,144,&(helpmenu2410CN[28]));
//			      //DispCn(0,4,1,144,&(helpmenu2410CN[44]));
//				break;
//						   	   	  
//	    	}
//		}/////////////////////////////////////////////////////////////////////////////////////////////
//		else
//		{
		   switch(g_nsysstatus )
           {	 
	          case SYS_MAINSHOWHELP:
		      switch(g_mmainhelpshow)
			  {
			     case 1:
				  	  DispEn(0,1,1,21,"*Key:                  ");
			          DispEn(0,3,1,21, "Press the key to cha- ");
			          DispEn(0,5,1,21, "-nge LED illuminance. ");
			          DispEn(0,7,1,21, "                      ");
					  break;
                case 2:
				  	  DispEn(0,1,1,21,"Green Key:             ");
			          DispEn(0,3,1,21, "Press the key to show ");
			          DispEn(0,5,1,21, "and select hitoric    ");
			          DispEn(0,7,1,21, "target quickly.       ");
					  break;
				case 3:
				  	  DispEn(0,1,1,21,"Red Key:               ");
			          DispEn(0,3,1,21, "Show function menu    ");
			          DispEn(0,5,1,21, "or Enter.             ");
			          DispEn(0,7,1,21, "                      ");
					  break;
				case 4:
				  	  DispEn(0,1,1,21,"Yellow Key:            ");
			          DispEn(0,3,1,21, "Press the key to stop ");
			          DispEn(0,5,1,21, "or abandon or quit.   ");
			          DispEn(0,7,1,21, "                      ");
					  break; 
				case 5:
				  	  DispEn(0,1,1,21,"Arrow Keys:            ");
			          DispEn(0,3,1,21, "Slew the telescope    ");
			          DispEn(0,5,1,21, "or Scroll in menu.    ");
			          DispEn(0,7,1,21, "                      ");
					  break;
				case 6:
				  	  DispEn(0,1,1,21,"Number Keys:            ");
			          DispEn(0,3,1,21, "Press to input digits  ");
			          DispEn(0,5,1,21, "0 to 9, input letter   ");
			          DispEn(0,7,1,21, "or Change slew speed.  ");
					  break;
				case 7:
				  	  DispEn(0,1,1,21,"Stop Key:               ");
			          DispEn(0,3,1,21, "Press to pause when    ");
			          DispEn(0,5,1,21, "telescope in tracking, ");
			          DispEn(0,7,1,21, "moving or slewing.     ");
					  break;
				case 8:
				  	  DispEn(0,1,1,21,"Help Key:               ");
			          DispEn(0,3,1,21, "Show help file         ");
			          DispEn(0,5,1,21, "can be used in all     ");
			          DispEn(0,7,1,21, "levels menu.           ");
					  break;
				case 9:
				  	  DispEn(0,1,1,21,"F+(1 to 9):             ");
			          DispEn(0,3,1,21, "Show historic target   ");
			          DispEn(0,5,1,21, "                       ");
			          DispEn(0,7,1,21, "                       ");
					  break;
				case 10:
				  	  DispEn(0,1,1,21,"F+0                     ");
			          DispEn(0,3,1,21, "Open or close key      ");
			          DispEn(0,5,1,21, "beep                   ");
			          DispEn(0,7,1,21, "                       ");
					  break;

			  }
			  break;
				
			case SYS_MAINMENU1HELP:
			      DispEn(0,1,1,21,"Telescope align:      ");
		          DispEn(0,3,1,21, "Align Telescop point ");
		          DispEn(0,5,1,21, "Pole-axis aim and    ");
		          DispEn(0,7,1,21, "correct Backlash.    ");
				break;
			case SYS_MAINMENU2HELP:
				  DispEn(0,1,1,21,"Target navigation:    ");
		          DispEn(0,3,1,21, "Select Target from   ");
		          DispEn(0,5,1,21, "database or input    ");
		          DispEn(0,7,1,21, "data.                ");
				break;
			case SYS_MAINMENU3HELP:
				  DispEn(0,1,1,21,"Utilities Commands:   ");
		          DispEn(0,3,1,21, "Some tools in common ");
		          DispEn(0,5,1,21, "use.                 ");
		          DispEn(0,7,1,21, "                     ");
				break;
			case SYS_MAINMENU4HELP:
				  DispEn(0,1,1,21,"Parameter Setup:      ");
		          DispEn(0,3,1,21, "Setup some parameter ");
		          DispEn(0,5,1,21, "in system.           ");
		          DispEn(0,7,1,21, "                     ");
				break;
					  /////////////////////////////////////////////////////
			case SYS_SUB1MENU1HELP:		    
				  DispEn(0,1,1,21,"One star align:       ");
		          DispEn(0,3,1,21, "Select one star align");
		          DispEn(0,5,1,21, "the telescope point  ");
		          DispEn(0,7,1,21, "by hand.             ");
				break;
			case SYS_SUB1MENU2HELP:
				  DispEn(0,1,1,21,"Two stars align:      ");
		          DispEn(0,3,1,21, "Select two star align");
		          DispEn(0,5,1,21, "the telescope point  ");
		          DispEn(0,7,1,21, "by hand.             ");
				break;
			case SYS_SUB1MENU3HELP:
				  DispEn(0,1,1,21,"Three star align:      ");
		          DispEn(0,3,1,21, "Select three stars    ");
		          DispEn(0,5,1,21, "align the telescope   ");
		          DispEn(0,7,1,21, "point by hand.        ");
				break;
			case SYS_SUB1MENU4HELP:
				  DispEn(0,1,1,21,"Target Sync:           ");
		          DispEn(0,3,1,21, "Synchronizing the     ");
		          DispEn(0,5,1,21, "target parameter with ");
		          DispEn(0,7,1,21, "thetelescope point.   ");
			    break;
								   
			case SYS_SUB1MENU5HELP:
				  DispEn(0,1,1,21,"Pole-Axis Deviation:     ");
		          DispEn(0,3,1,21, "Show the Pole-Axis      ");
		          DispEn(0,5,1,21, "practice Deviation      ");
		          DispEn(0,7,1,21, "through the align.      ");
				break;
			case SYS_SUB1MENU6HELP:
				  DispEn(0,1,1,21,"RA Bklash Correction:     ");
		          DispEn(0,3,1,21, "Correct the backlash     ");
		          DispEn(0,5,1,21, "in RA motor gear.        ");
		          DispEn(0,7,1,21, "                         ");
				break;
			case SYS_SUB1MENU7HELP:
				  DispEn(0,1,1,21,"DEC Bklash Correction:    ");
		          DispEn(0,3,1,21, "Correct the backlash     ");
		          DispEn(0,5,1,21, "in DED motor gear.       ");
		          DispEn(0,7,1,21, "                         ");
				break;
		
			 //Ŀ�굼���Ӳ˵�
			case SYS_SUB2MENU1HELP:
				  DispEn(0,1,1,21,"Solar System:            ");
		          DispEn(0,3,1,21, "Telescope can auto      ");
		          DispEn(0,5,1,21, "point at Planet, Sun,   ");
		          DispEn(0,7,1,21, "Moon.                   ");
			    break;
			case SYS_SUB2MENU2HELP:	
				  DispEn(0,1,1,21, "Constellation:         ");
		          DispEn(0,3,1,21, "Telescope can auto     ");
		          DispEn(0,5,1,21, "point at Constell-     ");
		          DispEn(0,7,1,21, "ation.                  ");
				break;
			case SYS_SUB2MENU3HELP:
				  DispEn(0,1,1,21,"Famous Star:           ");
		          DispEn(0,3,1,21, "Telescope can auto    ");
		          DispEn(0,5,1,21, "point at all famous   ");
		          DispEn(0,7,1,21, "stars.                ");
				break;
			case SYS_SUB2MENU4HELP:
				  DispEn(0,1,1,21,"Messier Catalogue:     ");
		          DispEn(0,3,1,21, "Telescope can auto    ");
		          DispEn(0,5,1,21, "point at all stars in ");
		          DispEn(0,7,1,21, "Messier Catalogue.    ");
				break;
			case SYS_SUB2MENU5HELP:
				 DispEn(0,1,1,21,"NGC Deep Sky:           ");
		          DispEn(0,3,1,21, "Telescope can auto    ");
		          DispEn(0,5,1,21, "point at all stars    ");
		          DispEn(0,7,1,21, "in NGC deep sky.      ");
			    break;
			case SYS_SUB2MENU6HELP:
				  DispEn(0,1,1,21,"IC Deep Sky:           ");
		          DispEn(0,3,1,21, "Telescope can auto    ");
		          DispEn(0,5,1,21, "point at all stars    ");
		          DispEn(0,7,1,21, "in IC deep sky.       ");
				break;
			case SYS_SUB2MENU7HELP:
				  DispEn(0,1,1,21,"Sh2 Deep Sky:          ");
		          DispEn(0,3,1,21, "Telescope can auto    ");
		          DispEn(0,5,1,21, "point at all stars    ");
		          DispEn(0,7,1,21, "in Sh2 Deep Sky.      ");
				break;
			case SYS_SUB2MENU8HELP:
				  DispEn(0,1,1,21,"Bright Stars:         ");
		          DispEn(0,3,1,21, "Telescope can auto   ");
		          DispEn(0,5,1,21, "point at all stars    ");
		          DispEn(0,7,1,21, "in Bright Stars.      ");
				break;
			case SYS_SUB2MENU9HELP:
				  DispEn(0,1,1,21,"SAO Star:              ");
		          DispEn(0,3,1,21, "Telescope can auto   ");
		          DispEn(0,5,1,21, "point at all stars    ");
		          DispEn(0,7,1,21, "in SAO Star.         ");
				  break;
			case SYS_SUB2MENU11HELP:
				  DispEn(0,1,1,21,"User-def Object:        ");
		          DispEn(0,3,1,21, "Input sky target        ");
		          DispEn(0,5,1,21, "parameter and save it.  ");
		          DispEn(0,7,1,21, "                         ");
				break;
			case SYS_SUB2MENU12HELP:
				  DispEn(0,1,1,21,"Specify Ra Dec:           ");
		          DispEn(0,3,1,21, "Input Target R.a and    ");
		          DispEn(0,5,1,21, "Des ,then point to it.   ");
		          DispEn(0,7,1,21, "                         ");
				break;
			case SYS_SUB2MENU13HELP:
				  DispEn(0,1,1,21,"Landmarks:             ");
		          DispEn(0,3,1,21, "Input land target     ");
		          DispEn(0,5,1,21, "parameter and save it. ");
		          DispEn(0,7,1,21, "                       ");
				break;
		
			 //���������Ӳ˵�
			 case SYS_SUB3MENU1HELP:
			      DispEn(0,1,1,21,"Current Objects:      ");
		          DispEn(0,3,1,21, "Give planet's,solar  ");
		          DispEn(0,5,1,21, "and lunar rise,      ");
		          DispEn(0,7,1,21, "transit and set time. ");
			    break;
			case SYS_SUB3MENU2HELP:
				  DispEn(0,1,1,21,"Object Rise/Set:       ");
		          DispEn(0,3,1,21, "calculate star rise,  ");
		          DispEn(0,5,1,21, "transit and set time. ");
		          DispEn(0,7,1,21, "                      ");
				break;
			case SYS_SUB3MENU3HELP:
			      DispEn(0,1,1,21,"Lunar Phase:         ");
		          DispEn(0,3,1,21, "Show the lunar phase ");
		          DispEn(0,5,1,21, "                     ");
		          DispEn(0,7,1,21, "                     ");
				break;
			case SYS_SUB3MENU4HELP:
				  DispEn(0,1,1,21,"Timer:                 ");
		          DispEn(0,3,1,21, "Count down reminder  ");
		          DispEn(0,5,1,21, "                      ");
		          DispEn(0,7,1,21, "                       ");
				break;
			case SYS_SUB3MENU5HELP:
				  DispEn(0,1,1,21,"Alarm:                  ");
		          DispEn(0,3,1,21, "Timeing alarm.         ");
		          DispEn(0,5,1,21, "                       ");
		          DispEn(0,7,1,21, "                       ");
			    break;
			case SYS_SUB3MENU6HELP:
				DispEn(0,1,1,21,"Field Angle Cal:        ");
		          DispEn(0,3,1,21, "Calculate the teles- ");
		          DispEn(0,5,1,21, "cope's field angel.  ");
		          DispEn(0,7,1,21, "                     ");
				break;
			case SYS_SUB3MENU7HELP:
				  DispEn(0,1,1,21,"Magify Power Cal:      ");
		          DispEn(0,3,1,21, "Calculate the teles-  ");
		          DispEn(0,5,1,21, "cope's magify power.  ");
		          DispEn(0,7,1,21, "                      ");
				break;
			case SYS_SUB3MENU8HELP:
				  DispEn(0,1,1,21,"Illumination:          ");
		          DispEn(0,3,1,21, "Set screen illumina-  ");
		          DispEn(0,5,1,21, "tion.                 ");
		          DispEn(0,7,1,21, "                      ");
				break;
			case SYS_SUB3MENU9HELP:
				  DispEn(0,1,1,21,"Parkzen:               ");
		          DispEn(0,3,1,21, "Slew telescope to     ");
		          DispEn(0,5,1,21, "Original Position.    ");
		          DispEn(0,7,1,21, "                      ");
				break;
		
			 //���������Ӳ˵�
			case SYS_SUB4MENU1HELP:
				  DispEn(0,1,1,21,"Time and Date:         ");
		          DispEn(0,3,1,21, "Set local time and   ");
		          DispEn(0,5,1,21, "data for system.      ");
		          DispEn(0,7,1,21, "                      ");
			    break;
			case SYS_SUB4MENU2HELP:
				  DispEn(0,1,1,21,"Daylight Saving:        ");
		          DispEn(0,3,1,21, "Set Daylight Saving.   ");
		          DispEn(0,5,1,21, "                       ");
		          DispEn(0,7,1,21, "                       ");
				break;
			case SYS_SUB4MENU3HELP:
				  DispEn(0,1,1,21,"Site Setting:            ");
		          DispEn(0,3,1,21, "Select local site       ");
		          DispEn(0,5,1,21, "from database or        ");
		          DispEn(0,7,1,21, "input data.             ");
				break;
			case SYS_SUB4MENU4HELP:
		    	  DispEn(0,1,1,21,"Sky/ Land:             ");
		          DispEn(0,3,1,21, "Select sky or land    ");
		          DispEn(0,5,1,21, "mode                  ");
		          DispEn(0,7,1,21, "                      ");
			    break;
			case SYS_SUB4MENU5HELP:
				  DispEn(0,1,1,21,"AZ/EQ:                 ");
		          DispEn(0,3,1,21, "Set mount mode to be  ");
		          DispEn(0,5,1,21, "AZ or EQ mode.        ");
		          DispEn(0,7,1,21, "                      ");
				break;
			case SYS_SUB4MENU6HELP:
			      DispEn(0,1,1,21,"Telescope Zero:        ");
		          DispEn(0,3,1,21, "Set telescope Origin- ");
		          DispEn(0,5,1,21, "al Position.          ");
		          DispEn(0,7,1,21, "                      ");
				break;
			case SYS_SUB4MENU7HELP:
			      DispEn(0,1,1,21,"Tracking Rate:         ");
		          DispEn(0,3,1,21, "Set telescope track   ");
		          DispEn(0,5,1,21, "speed.                ");
		          DispEn(0,7,1,21, "                      ");
				break;
			case SYS_SUB4MENU8HELP:
				  DispEn(0,1,1,21,"Language:             ");
		          DispEn(0,3,1,21, "Select the menu      ");
		          DispEn(0,5,1,21, "language.            ");
		          DispEn(0,7,1,21, "                     ");
			    break;
			case SYS_SUB4MENU9HELP:
			      DispEn(0,1,1,21,"Reset:                ");
		          DispEn(0,3,1,21, "All parameter resume ");
		          DispEn(0,5,1,21, "to the leave factory ");
		          DispEn(0,7,1,21, "state.               ");
			    
				break;
						   	   	  
	    	}
//		}
	

	
			    
}

//���˵���ʾ����
void  FMenuShow()
{
	FMenuShowSet();
	switch(g_mShowLangauge)
	{ 
		case 1://Ӣ��
	    g_mshowed1=g_nsysstatus;
		if(g_mshowed1!=g_mshowed2)  //��Զ��״̬����Ͳ�ˢ��,״̬���ˢ��
		{
		    
		      LCDRfrsh();
			  g_mshowed2=g_mshowed1;
		} 
		
		
		switch(g_nsysstatus )
		{
		       //ϵͳ����������ʾ
			   case SYS_MAINSHOW:
				if(g_mcalpalnet==1)//û��������,���г�ʼ����ʾ
		        {
			     FSysMainShow();
				 }

				break;

			case SYS_MENUSHOW:
			 if(g_RecentNum!=0)
		     {	
			 	
			     switch(g_mShowMenurowEn) 
		        {
		        
			      case 1:
					DispEn(1,1,1,2,gstrlineEn9);
		   		    DispEn(0,2,1,2,gstrlineEn10);
		   		    DispEn(0,3,1,2,gstrlineEn11);
		   		    DispEn(0,4,1,2,gstrlineEn12);
					DispEn(0,5,1,2,gstrlineEn13);
		   		    DispEn(0,6,1,2,gstrlineEn14);
		   		    DispEn(0,7,1,2,gstrlineEn15);
		   		    DispEn(0,8,1,2,gstrlineEn16);

		   		    DispEn(1,1,3,strlen(gstrlineEn1), gstrlineEn1);
		   		    DispEn(0,2,3,strlen(gstrlineEn2), gstrlineEn2);
		   		    DispEn(0,3,3,strlen(gstrlineEn3), gstrlineEn3);
		   		    DispEn(0,4,3,strlen(gstrlineEn4), gstrlineEn4);
					DispEn(0,5,3,strlen(gstrlineEn5), gstrlineEn5);
		   		    DispEn(0,6,3,strlen(gstrlineEn6), gstrlineEn6);
		   		    DispEn(0,7,3,strlen(gstrlineEn7), gstrlineEn7);
		   		    DispEn(0,8,3,strlen(gstrlineEn8), gstrlineEn8);
		   		  break ;
		          case 2:
				    DispEn(0,1,1,2,gstrlineEn9);
		   		    DispEn(1,2,1,2,gstrlineEn10);
		   		    DispEn(0,3,1,2,gstrlineEn11);
		   		    DispEn(0,4,1,2,gstrlineEn12);
					DispEn(0,5,1,2,gstrlineEn13);
		   		    DispEn(0,6,1,2,gstrlineEn14);
		   		    DispEn(0,7,1,2,gstrlineEn15);
		   		    DispEn(0,8,1,2,gstrlineEn16);

		   		    DispEn(0,1,3,strlen(gstrlineEn1), gstrlineEn1);
		   		    DispEn(2,2,3,strlen(gstrlineEn2), gstrlineEn2);
		   		    DispEn(0,3,3,strlen(gstrlineEn3), gstrlineEn3);
		   		    DispEn(0,4,3,strlen(gstrlineEn4), gstrlineEn4);
					DispEn(0,5,3,strlen(gstrlineEn5), gstrlineEn5);
		   		    DispEn(0,6,3,strlen(gstrlineEn6), gstrlineEn6);
		   		    DispEn(0,7,3,strlen(gstrlineEn7), gstrlineEn7);
		   		    DispEn(0,8,3,strlen(gstrlineEn8), gstrlineEn8);
		   		  break ;
			      case 3:
				  DispEn(0,1,1,2,gstrlineEn9);
		   		    DispEn(0,2,1,2,gstrlineEn10);
		   		    DispEn(1,3,1,2,gstrlineEn11);
		   		    DispEn(0,4,1,2,gstrlineEn12);
					DispEn(0,5,1,2,gstrlineEn13);
		   		    DispEn(0,6,1,2,gstrlineEn14);
		   		    DispEn(0,7,1,2,gstrlineEn15);
		   		    DispEn(0,8,1,2,gstrlineEn16);

		   	 	    DispEn(0,1,3,strlen(gstrlineEn1), gstrlineEn1);
		   		    DispEn(0,2,3,strlen(gstrlineEn2), gstrlineEn2);
		   		    DispEn(1,3,3,strlen(gstrlineEn3), gstrlineEn3);
		   		    DispEn(0,4,3,strlen(gstrlineEn4), gstrlineEn4);
					DispEn(0,5,3,strlen(gstrlineEn5), gstrlineEn5);
		   		    DispEn(0,6,3,strlen(gstrlineEn6), gstrlineEn6);
		   		    DispEn(0,7,3,strlen(gstrlineEn7), gstrlineEn7);
		   		    DispEn(0,8,3,strlen(gstrlineEn8), gstrlineEn8);
		   	      break ;
				  case 4:
				    DispEn(0,1,1,2,gstrlineEn9);
		   		    DispEn(0,2,1,2,gstrlineEn10);
		   		    DispEn(0,3,1,2,gstrlineEn11);
		   		    DispEn(1,4,1,2,gstrlineEn12);
					DispEn(0,5,1,2,gstrlineEn13);
		   		    DispEn(0,6,1,2,gstrlineEn14);
		   		    DispEn(0,7,1,2,gstrlineEn15);
		   		    DispEn(0,8,1,2,gstrlineEn16);

		   		    DispEn(0,1,3,strlen(gstrlineEn1), gstrlineEn1);
		   		    DispEn(0,2,3,strlen(gstrlineEn2), gstrlineEn2);
		   		    DispEn(0,3,3,strlen(gstrlineEn3), gstrlineEn3);
		   		    DispEn(1,4,3,strlen(gstrlineEn4), gstrlineEn4);
					DispEn(0,5,3,strlen(gstrlineEn5), gstrlineEn5);
		   		    DispEn(0,6,3,strlen(gstrlineEn6), gstrlineEn6);
		   		    DispEn(0,7,3,strlen(gstrlineEn7), gstrlineEn7);
		   		    DispEn(0,8,3,strlen(gstrlineEn8), gstrlineEn8);
		   		  break ;
			 	 case 5:
				    DispEn(0,1,1,2,gstrlineEn9);
		   		    DispEn(0,2,1,2,gstrlineEn10);
		   		    DispEn(0,3,1,2,gstrlineEn11);
		   		    DispEn(0,4,1,2,gstrlineEn12);
					DispEn(1,5,1,2,gstrlineEn13);
		   		    DispEn(0,6,1,2,gstrlineEn14);
		   		    DispEn(0,7,1,2,gstrlineEn15);
		   		    DispEn(0,8,1,2,gstrlineEn16);

		   		    DispEn(0,1,3,strlen(gstrlineEn1), gstrlineEn1);
		   		    DispEn(0,2,3,strlen(gstrlineEn2), gstrlineEn2);
		   		    DispEn(0,3,3,strlen(gstrlineEn3), gstrlineEn3);
		   		    DispEn(0,4,3,strlen(gstrlineEn4), gstrlineEn4);
					DispEn(1,5,3,strlen(gstrlineEn5), gstrlineEn5);
		   		    DispEn(0,6,3,strlen(gstrlineEn6), gstrlineEn6);
		   		    DispEn(0,7,3,strlen(gstrlineEn7), gstrlineEn7);
		   		    DispEn(0,8,3,strlen(gstrlineEn8), gstrlineEn8);
		   	    	break ;
				case 6:
			    	DispEn(0,1,1,2,gstrlineEn9);
		   		    DispEn(0,2,1,2,gstrlineEn10);
		   		    DispEn(0,3,1,2,gstrlineEn11);
		   		    DispEn(0,4,1,2,gstrlineEn12);
					DispEn(0,5,1,2,gstrlineEn13);
		   		    DispEn(1,6,1,2,gstrlineEn14);
		   		    DispEn(0,7,1,2,gstrlineEn15);
		   		    DispEn(0,8,1,2,gstrlineEn16);

				    DispEn(0,1,3,strlen(gstrlineEn1), gstrlineEn1);
		   		    DispEn(0,2,3,strlen(gstrlineEn2), gstrlineEn2);
		   		    DispEn(0,3,3,strlen(gstrlineEn3), gstrlineEn3);
		   		    DispEn(0,4,3,strlen(gstrlineEn4), gstrlineEn4);
					DispEn(0,5,3,strlen(gstrlineEn5), gstrlineEn5);
		   		    DispEn(1,6,3,strlen(gstrlineEn6), gstrlineEn6);
		   		    DispEn(0,7,3,strlen(gstrlineEn7), gstrlineEn7);
		   		    DispEn(0,8,3,strlen(gstrlineEn8), gstrlineEn8);
				break;
				case 7:
			    	DispEn(0,1,1,2,gstrlineEn9);
		   		    DispEn(0,2,1,2,gstrlineEn10);
		   		    DispEn(0,3,1,2,gstrlineEn11);
		   		    DispEn(0,4,1,2,gstrlineEn12);
					DispEn(0,5,1,2,gstrlineEn13);
		   		    DispEn(0,6,1,2,gstrlineEn14);
		   		    DispEn(1,7,1,2,gstrlineEn15);
		   		    DispEn(0,8,1,2,gstrlineEn16);

				   DispEn(0,1,3,strlen(gstrlineEn1), gstrlineEn1);
		   		    DispEn(0,2,3,strlen(gstrlineEn2), gstrlineEn2);
		   		    DispEn(0,3,3,strlen(gstrlineEn3), gstrlineEn3);
		   		    DispEn(0,4,3,strlen(gstrlineEn4), gstrlineEn4);
					DispEn(0,5,3,strlen(gstrlineEn5), gstrlineEn5);
		   		    DispEn(0,6,3,strlen(gstrlineEn6), gstrlineEn6);
		   		    DispEn(1,7,3,strlen(gstrlineEn7), gstrlineEn7);
		   		    DispEn(0,8,3,strlen(gstrlineEn8), gstrlineEn8);
				break;
				case 8:
			    	DispEn(0,1,1,2,gstrlineEn9);
		   		    DispEn(0,2,1,2,gstrlineEn10);
		   		    DispEn(0,3,1,2,gstrlineEn11);
		   		    DispEn(0,4,1,2,gstrlineEn12);
					DispEn(0,5,1,2,gstrlineEn13);
		   		    DispEn(0,6,1,2,gstrlineEn14);
		   		    DispEn(0,7,1,2,gstrlineEn15);
		   		    DispEn(1,8,1,2,gstrlineEn16);

				    DispEn(0,1,3,strlen(gstrlineEn1), gstrlineEn1);
		   		    DispEn(0,2,3,strlen(gstrlineEn2), gstrlineEn2);
		   		    DispEn(0,3,3,strlen(gstrlineEn3), gstrlineEn3);
		   		    DispEn(0,4,3,strlen(gstrlineEn4), gstrlineEn4);
					DispEn(0,5,3,strlen(gstrlineEn5), gstrlineEn5);
		   		    DispEn(0,6,3,strlen(gstrlineEn6), gstrlineEn6);
		   		    DispEn(0,7,3,strlen(gstrlineEn7), gstrlineEn7);
		   		    DispEn(1,8,3,strlen(gstrlineEn8), gstrlineEn8);
				break;
				   default:break;
		         }
				}
				else
				{   
				    DispEn(0,1,1,2,gstrlineEn9);
		   		    DispEn(0,2,1,2,gstrlineEn10);
		   		    DispEn(0,3,1,2,gstrlineEn11);
		   		    DispEn(0,4,1,2,gstrlineEn12);
					DispEn(0,5,1,2,gstrlineEn13);
		   		    DispEn(0,6,1,2,gstrlineEn14);
		   		    DispEn(0,7,1,2,gstrlineEn15);
		   		    DispEn(0,8,1,2,gstrlineEn16);

				    DispEn(0,1,1,strlen(gstrlineEn1), gstrlineEn1);
		   		    DispEn(0,2,1,strlen(gstrlineEn2), gstrlineEn2);
		   		    DispEn(0,3,1,strlen(gstrlineEn3), gstrlineEn3);
		   		    DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);
					DispEn(0,5,1,strlen(gstrlineEn5), gstrlineEn5);
		   		    DispEn(0,6,1,strlen(gstrlineEn6), gstrlineEn6);
		   		    DispEn(0,7,1,strlen(gstrlineEn7), gstrlineEn7);
		   		    DispEn(0,8,1,strlen(gstrlineEn8), gstrlineEn8);
				}

			   break;
		
	   	   

			case SYS_F_SELFNUM_SEL:
	  		   
          	    if(((LandTarget.flag!=1)&&(g_mSkyLand==1))||((CustomStar.flag!=1)&&(g_mSkyLand==0)))
				{
					  DispEn(0,1,1,strlen(gstrlineEn1), gstrlineEn1);
					  DispEn(0,2,1,strlen(gstrlineEn2), gstrlineEn2);
					  DispEn(0,3,1,strlen(gstrlineEn3), gstrlineEn3);
					  DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);
					  DispEn(0,5,1,strlen(gstrlineEn5), gstrlineEn5);
					  DispEn(0,6,1,strlen(gstrlineEn6), gstrlineEn6);
					  DispEn(0,7,1,strlen(gstrlineEn7), gstrlineEn7);
					  DispEn(0,8,1,strlen(gstrlineEn8), gstrlineEn8);
				  }
				  else
				  {
				     switch(g_mSkyLand)
				  	{
					  case 0:
						    DispEn(0,1,1,strlen(gstrlineEn1),gstrlineEn1);
							DispEn(0,2,1,strlen(gstrlineEn2),gstrlineEn2);             
				   		    DispEn(0,3,1,strlen(gstrlineEn3), gstrlineEn3);									
				   		    DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4); 
			
			
														  
							DispEn(0,5,1,strlen(gstrlineEn5), gstrlineEn5);						
				   		    DispEn(0,6,8,strlen(gstrlineEn6), gstrlineEn6);
				   		    DispEn(0,7,8,strlen(gstrlineEn7), gstrlineEn7);						
				   		    DispEn(0,8,8,strlen(gstrlineEn8), gstrlineEn8);
							DispCh(0, 5,15,CharD);
			  	            DispCh(0, 5,18,CharM);
							DispCh(0, 5,21,CharS);
							DispCh(0, 6,15,CharD);
			  	            DispCh(0, 6,18,CharM);
			            	DispCh(0, 6,21,CharS);
							DispCh(0, 8,15,CharD);
			  	            DispCh(0, 8,18,CharM);
							DispCh(0, 8,21,CharS);
						break;
					  case 1:  
						    DispEn(0,1,1,strlen(gstrlineEn1),gstrlineEn1);
							DispEn(0,2,1,strlen(gstrlineEn2),gstrlineEn2);             
				   		    DispEn(0,3,1,strlen(gstrlineEn3), gstrlineEn3);									
				   		    DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4); 
			
			
														  
							DispEn(0,5,1,strlen(gstrlineEn5), gstrlineEn5);						
				   		    DispEn(0,6,8,strlen(gstrlineEn6), gstrlineEn6);
				   		    DispEn(0,7,1,strlen(gstrlineEn7), gstrlineEn7);						
				   		    DispEn(0,8,8,strlen(gstrlineEn8), gstrlineEn8);
							DispCh(0, 5,15,CharD);
			  	            DispCh(0, 5,18,CharM);
							DispCh(0, 5,21,CharS);
							DispCh(0, 6,15,CharD);
			  	            DispCh(0, 6,18,CharM);
			            	DispCh(0, 6,21,CharS);

							DispCh(0, 7,15,CharD);
			  	            DispCh(0, 7,18,CharM);
			            	DispCh(0, 7,21,CharS);
							DispCh(0, 8,15,CharD);
			  	            DispCh(0, 8,18,CharM);
							DispCh(0, 8,21,CharS);
						break;
		
					}
				   
   		   	   		 }
		     	break; 
			 

				case SYS_NOTELSCOPE:
			
					 DispEn(0,2,1,strlen(gstrlineEn2), gstrlineEn2);
					 DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);
					 DispEn(0,6,1,strlen(gstrlineEn6), gstrlineEn6);

				     FBeep(1);
					 delay(200);
					 FBeep(1);
					 delay(200);
					 FBeep(1);
					 delay(200);
					 g_nsysstatus =SYS_MAINSHOW;
				break;
				

//				case SYS_SUB1SUB1AUTOSTAR_ALIGN:
//				
//				   
//				    if(!g_nAlignPoint)
//					{
//					  switch(g_nSeledAlignStarNum)
//					  {
//					    case 1:
//						case 2:
//						   if(g_mAlignTelStatus!=1)
//						   {
//						       LCDRfrsh();
//						   }
//						   g_mAlignTelStatus=1;
//						gstrlineEn1=g_sysmenu1103;
//						DispEn(0,1,1,strlen(gstrlineEn1), gstrlineEn1);	
//			   		    DispEn(0,2,1,strlen(gstrlineEn2), gstrlineEn2);
//						DispEn(0,3,1,strlen(gstrlineEn3), gstrlineEn3);		
//			   		    DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);	
//												  
//					   	DispEn(0,5,1,4, "OBJ:");
//														  
//							DispEn(0,7,11,strlen(gstrlineEn5), gstrlineEn5);						
//				   		    DispEn(0,8,11,strlen(gstrlineEn6), gstrlineEn6);
//
//				   		    DispEn(0,5,11,strlen(gstrlineEn7), gstrlineEn7);						
//				   		    DispEn(0,6,11,strlen(gstrlineEn8), gstrlineEn8);
//
//							DispCh(0, 5,18,CharD);
//			  	            DispCh(0, 5,21,CharM);
//
//							DispCh(0, 8,18,CharD);
//			  	            DispCh(0, 8,21,CharM);
//
//							DispCh(0, 6,18,CharD);
//			  	            DispCh(0, 6,21,CharM);
//					     	DispEn(0,6,1,6,"       ");
//						  delay(300);
//
//						if(g_nSeledAlignStarNum==1)
//						{
//						   FTwoStarAutoAlign();
//						}
//					    g_nAlignPoint=true;//��Զ����һ����������У��ʱ�ǵ���ȷ�ϻ���ѡ��falseѡ���ǣ�trueУ������ȷ��
//					   break;
//					   case 3:
//						       if(g_mAlignTelStatus!=2)
//						   {
//						       LCDRfrsh();
//						   }
//						   g_mAlignTelStatus=2;
//							FPointAlignStarOk();
//							FBeep(3);
//							gstrlineEn2=g_sysmenu1107;
//							gstrlineEn4=g_sysmenu1108;
//							gstrlineEn6=g_sysmenu1109;
//						   
//						   	DispEn(0,1,1,22,"                       ");
//							DispEn(0,2,1,strlen(gstrlineEn2), gstrlineEn2);
//							DispEn(0,3,1,22,"                       ");
//							DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);
//							DispEn(0,5,1,22,"                       ");
//							DispEn(0,6,1,strlen(gstrlineEn6), gstrlineEn6);
//							DispEn(0,7,1,22,"                       ");
//							DispEn(0,8,1,22,"                       ");
//						   	delay(300);
//						    g_nsysstatus =SYS_MAINSHOW;
//							
//					   break;
//					   default:
//					   break;
//					  }
//					}
//					else
//					{	
//
//						if(g_mTelStatus==1)
//						{
//						   if(g_mAlignTelStatus!=3)
//						   {
//						       LCDRfrsh();
//						   }
//						   g_mAlignTelStatus=3;
//							    gstrlineEn2=g_sysmenu1102;
//								
//								DispEn(0,1,1,22,"                       ");
//
//								if(g_mGoto.m_nTelGotoPause==0)
//								{
//							      DispEn(0,2,1,21,"Slewing to Target   ");
//								}
//								else
//								{
//								  DispEn(0,2,1,21,"Pause                ");
//								}
//
//                                DispEn(0,3,1,22,"                        ");
//								DispEn(0,4,1,22,"                        ");
//
//								DispEn(0,5,1,4, "OBJ:");
//			             		DispEn(0,5,11,strlen(gstrlineEn7), gstrlineEn7);								
//					   		    DispEn(0,6,11,strlen(gstrlineEn8), gstrlineEn8);
//							    DispCh(0, 5,18,CharD);
//				  	            DispCh(0, 5,21,CharM);
//
//
//								DispCh(0, 6,18,CharD);
//				  	            DispCh(0, 6,21,CharM); 
//
//								DispEn(0,6,1,6, "       ");
//
//								DispEn(0,7,1,4, "OTA:");
//					   		    DispEn(0,7,11,strlen(gstrlineEn5), gstrlineEn5);						
//					   		    DispEn(0,8,11,strlen(gstrlineEn6), gstrlineEn6);
////								switch(g_mAzEq)
////								{
////								case 0:
//									 DispCh(0, 7,18,CharD);
//				  	                 DispCh(0, 7,21,CharM);
////									break;
////								case 1: 
////								   DispEn(0, 7,15,1," ");
////								   DispEn(0, 7,18,1,"h");
////				  	               DispEn(0, 7,21,1,"m");
////									break;
////								default:
////									break;
////								}
//								DispCh(0, 8,18,CharD);
//				  	            DispCh(0, 8,21,CharM); 
//								DispEn(0,6,1,6,"      ");
//							  	 
//				
//						}
//						if(g_mTelStatus==2)
//						{
//						   if(g_mAlignTelStatus!=4)
//						   {
//						       LCDRfrsh();
//						   }
//						   g_mAlignTelStatus=4;
//						    gstrlineEn2=g_sysmenu1104;
//							gstrlineEn4=g_sysmenu1105;
//							gstrlineEn6=g_sysmenu1106;								   
//						   	DispEn(0,1,1,22,"                       ");
//							DispEn(0,2,1,strlen(gstrlineEn2),gstrlineEn2);
//							DispEn(0,3,1,22,"                       ");
//							DispEn(0,4,1,strlen(gstrlineEn4),gstrlineEn4);
//							DispEn(0,5,1,22,"                       ");
//							DispEn(0,6,1,strlen(gstrlineEn6),gstrlineEn6);
//							DispEn(0,7,1,22,"                       ");
//							DispEn(0,8,1,22,"                       ");
//						}
//					}
//				break;
//		        
				case SYS_SUB1SUB2STAR_ALIGN	:  //һ������У׼����ʾ����
			
				   	if(!g_nAlignPoint)
					{
					
						if(g_nAlignStar==0)
						{
						  	 if(g_mAlignTelStatus!=5)
						   {
						       LCDRfrsh();
						   }
						   g_mAlignTelStatus=5;
						    FPointAlignStarOk();
							FBeep(3);
						   	gstrlineEn2=g_sysmenu1107;
							gstrlineEn4=g_sysmenu1108;
							gstrlineEn6=g_sysmenu1109;
		
						   
						   	DispEn(0,1,1,22,"                       ");
							DispEn(0,2,1,strlen(gstrlineEn2),gstrlineEn2);
							DispEn(0,3,1,22,"                       ");
							DispEn(0,4,1,strlen(gstrlineEn4),gstrlineEn4);
							DispEn(0,5,1,22,"                       ");
							DispEn(0,6,1,strlen(gstrlineEn6),gstrlineEn6);
							DispEn(0,7,1,22,"                       ");
							DispEn(0,8,1,22,"                       ");
							delay(300);
						   
						    g_nsysstatus =SYS_MAINSHOW;
						}
						else
						{  
						       if(g_mAlignTelStatus!=6)
						   {
						       LCDRfrsh();
						   }
						   g_mAlignTelStatus=6;
						   	DispEn(0,1,1,strlen(gstrlineEn1),gstrlineEn1);
							DispEn(0,2,1,strlen(gstrlineEn2),gstrlineEn2);             
				   		    DispEn(0,3,1,strlen(gstrlineEn3), gstrlineEn3);  							
				   		    DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);
						
							
							DispEn(0,5,1,4, "OBJ:");
														  
							DispEn(0,7,11,strlen(gstrlineEn7), gstrlineEn7);						
				   		    DispEn(0,8,11,strlen(gstrlineEn8), gstrlineEn8);
				   		    DispEn(0,5,11,strlen(gstrlineEn5), gstrlineEn5);						
				   		    DispEn(0,6,11,strlen(gstrlineEn6), gstrlineEn6);

							DispCh(0, 5,18,CharD);
			  	            DispCh(0, 5,21,CharM);
							DispCh(0, 6,18,CharD);
			  	            DispCh(0, 6,21,CharM);
							DispCh(0, 8,18,CharD);
			  	            DispCh(0, 8,21,CharM);
							DispEn(0,6,1,4,"      ");
						}
					}
					else
					{ 	
						//g_mTelStatus=2;
					    if((g_mTelStatus==1)&&(g_mAlignShow==0))
						{
						    if(g_mAlignTelStatus!=7)
						   {
						       LCDRfrsh();
						   }
						   g_mAlignTelStatus=7;
							    gstrlineEn1=g_sysmenu1102;
								gstrlineEn2=g_sysmenu1103;
								if(g_mGoto.m_nTelGotoPause==0)
								{
							      DispEn(0,1,1,21,"Slewing to Target   ");
								}
								else
								{
								  DispEn(0,1,1,21,"Pause                ");
								}
								//DispEn(0,2,1,strlen(gstrlineEn2),gstrlineEn2);
								DispEn(0,2,1,21,"                     ");
                                DispEn(0,3,1,strlen(gstrlineEn3),gstrlineEn3);
								DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);

							    DispEn(0,5,1,4, "OBJ:");
			                	DispEn(0,5,11,strlen(gstrlineEn5), gstrlineEn5);								
					   		    DispEn(0,6,11,strlen(gstrlineEn6), gstrlineEn6);
							    DispCh(0, 5,18,CharD);
				  	            DispCh(0, 5,21,CharM);

								DispCh(0, 6,18,CharD);
				  	            DispCh(0, 6,21,CharM); 

								DispEn(0,6,1,6, "       ");

								DispEn(0,7,1,4, "OTA:");
					   		    DispEn(0,7,11,strlen(gstrlineEn7), gstrlineEn7);						
					   		    DispEn(0,8,11,strlen(gstrlineEn8), gstrlineEn8);
//								switch(g_mAzEq)
//								{
//								case 0:
									 DispCh(0, 7,18,CharD);
				  	                 DispCh(0, 7,21,CharM);
//									break;
//								case 1: 
//								   DispEn(0, 7,15,1," ");
//								   DispEn(0, 7,18,1,"h");
//				  	               DispEn(0, 7,21,1,"m");
//									break;
//								default:
//									break;
//								}
								DispCh(0, 8,18,CharD);
				  	            DispCh(0, 8,21,CharM); 
								DispEn(0,6,1,4,"    ");
							   
				
						}
						else if(g_mAlignShow==1)
						{
						   if(g_mAlignTelStatus!=8)
						   {
						       LCDRfrsh();
						   }
						    g_mAlignTelStatus=8;
						   	gstrlineEn2=g_sysmenu1104;
							gstrlineEn4=g_sysmenu1105;
							gstrlineEn6=g_sysmenu1106;								   
						   	DispEn(0,1,1,22,"                       ");
							DispEn(0,2,1,strlen(gstrlineEn2),gstrlineEn2);
							DispEn(0,3,1,22,"                       ");
							DispEn(0,4,1,strlen(gstrlineEn4),gstrlineEn4);
							DispEn(0,5,1,22,"                       ");
							DispEn(0,6,1,strlen(gstrlineEn6),gstrlineEn6);
							DispEn(0,7,1,22,"                       ");
							DispEn(0,8,1,22,"                       ");
						  
						}
						if(g_mTelStatus==2)
						{
						   g_mAlignShow=1;
						   if(g_mAlignTelStatus!=8)
						   {
						       LCDRfrsh();
						   }

						    g_mAlignTelStatus=8;
						   	gstrlineEn2=g_sysmenu1104;
							gstrlineEn4=g_sysmenu1105;
							gstrlineEn6=g_sysmenu1106;								   
						   	DispEn(0,1,1,22,"                       ");
							DispEn(0,2,1,strlen(gstrlineEn2),gstrlineEn2);
							DispEn(0,3,1,22,"                       ");
							DispEn(0,4,1,strlen(gstrlineEn4),gstrlineEn4);
							DispEn(0,5,1,22,"                       ");
							DispEn(0,6,1,strlen(gstrlineEn6),gstrlineEn6);
							DispEn(0,7,1,22,"                       ");
							DispEn(0,8,1,22,"                       ");
						}
					}

				 break;

			 //�ྭ�ز�У��
			  case SYS_SUB1SUB11RA_GEAR_ERROR_BEGIN:  
			  case SYS_SUB1SUB11RA_GEAR_ERROR: 
			  case SYS_SUB1SUB11RA_GEAR_ERROR_ALIGN: 		      
                   DispEn(0,1,1,strlen(gstrlineEn1),gstrlineEn1);
				   DispEn(0,2,1,strlen(gstrlineEn2),gstrlineEn2);
                   DispEn(0,3,1,strlen(gstrlineEn3),gstrlineEn3);
				   DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);
				   DispEn(0,5,1,strlen(gstrlineEn5),gstrlineEn5);
				   DispEn(0,6,1,strlen(gstrlineEn6),gstrlineEn6);
                   DispEn(0,7,1,strlen(gstrlineEn7),gstrlineEn7);
				   DispEn(0,8,1,strlen(gstrlineEn8), gstrlineEn8);

			   break;
			   case SYS_SUB1SUB11RA_GEAR_ERROR_ALIGN_OK: 			   		     
				   FBeep(1);	
				   DispEn(0,1,1,strlen(gstrlineEn1),gstrlineEn1);
				   DispEn(0,2,1,strlen(gstrlineEn2),gstrlineEn2);
                   DispEn(0,3,1,strlen(gstrlineEn3),gstrlineEn3);
				   DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);
				   DispEn(0,5,8,strlen(gstrlineEn5),gstrlineEn5);
				   DispEn(0,6,1,strlen(gstrlineEn6),gstrlineEn6);
                   DispEn(0,7,1,strlen(gstrlineEn7),gstrlineEn7);
				   DispEn(0,8,1,strlen(gstrlineEn8), gstrlineEn8);
						
				  delay(800);
				  g_nsysstatus =SYS_SUB1SUB11RA_GEAR_ERROR_BEGIN;
			   break;

			   case SYS_SUB1SUB11RA_GEAR_ERROR_ALIGN_END: 			   		     
				  FBeep(3);	
				   DispEn(0,1,1,strlen(gstrlineEn1),gstrlineEn1);
				   DispEn(0,2,1,strlen(gstrlineEn2),gstrlineEn2);
                   DispEn(0,3,1,strlen(gstrlineEn3),gstrlineEn3);
				   DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);
				   DispEn(0,5,8,strlen(gstrlineEn5),gstrlineEn5);
				   DispEn(0,6,1,strlen(gstrlineEn6),gstrlineEn6);
                   DispEn(0,7,1,strlen(gstrlineEn7),gstrlineEn7);
				   DispEn(0,8,1,strlen(gstrlineEn8), gstrlineEn8);					
				  delay(800);
				  g_nsysstatus =SYS_MAINSHOW;
			   break;


			 //��γ�ز�У��
			  case SYS_SUB1SUB12DEC_GEAR_ERROR_BEGIN:  
			  case SYS_SUB1SUB12DEC_GEAR_ERROR: 
			  case SYS_SUB1SUB12DEC_GEAR_ERROR_ALIGN: 		      
                   DispEn(0,1,1,strlen(gstrlineEn1),gstrlineEn1);
				   DispEn(0,2,1,strlen(gstrlineEn2),gstrlineEn2);
                   DispEn(0,3,1,strlen(gstrlineEn3),gstrlineEn3);
				   DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);
				   DispEn(0,5,1,strlen(gstrlineEn5),gstrlineEn5);
				   DispEn(0,6,1,strlen(gstrlineEn6),gstrlineEn6);
                   DispEn(0,7,1,strlen(gstrlineEn7),gstrlineEn7);
				   DispEn(0,8,1,strlen(gstrlineEn8), gstrlineEn8);

			   break;
			   case SYS_SUB1SUB12DEC_GEAR_ERROR_ALIGN_OK: 			   		     
				  FBeep(1);	
				    DispEn(0,1,1,strlen(gstrlineEn1),gstrlineEn1);
				   DispEn(0,2,1,strlen(gstrlineEn2),gstrlineEn2);
                   DispEn(0,3,1,strlen(gstrlineEn3),gstrlineEn3);
				   DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);
				   DispEn(0,5,8,strlen(gstrlineEn5),gstrlineEn5);
				   DispEn(0,6,1,strlen(gstrlineEn6),gstrlineEn6);
                   DispEn(0,7,1,strlen(gstrlineEn7),gstrlineEn7);
				   DispEn(0,8,1,strlen(gstrlineEn8), gstrlineEn8);
					 						
				  delay(800);
				  g_nsysstatus =SYS_SUB1SUB12DEC_GEAR_ERROR_BEGIN;
			   break;

			   case SYS_SUB1SUB12DEC_GEAR_ERROR_ALIGN_END: 			   		     
				  FBeep(3);	
				   DispEn(0,1,1,strlen(gstrlineEn1),gstrlineEn1);
				   DispEn(0,2,1,strlen(gstrlineEn2),gstrlineEn2);
                   DispEn(0,3,1,strlen(gstrlineEn3),gstrlineEn3);
				   DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);
				   DispEn(0,5,8,strlen(gstrlineEn5),gstrlineEn5);
				   DispEn(0,6,1,strlen(gstrlineEn6),gstrlineEn6);
                   DispEn(0,7,1,strlen(gstrlineEn7),gstrlineEn7);
				   DispEn(0,8,1,strlen(gstrlineEn8), gstrlineEn8);					
				  delay(800);
				  g_nsysstatus =SYS_MAINSHOW;
			   break;		  

				//̫��ϵ����
			   case SYS_SUB2SUN_PLANET:
			   case  SYS_SUB2CON_OBJECT:
			   
			   case  SYS_SUB2MSR_OBJECT:
			  
			
		   //SH2�Ǳ�
		    case  SYS_SUB2SH2_OBJECT:	
			//Bright�Ǳ�
			case  SYS_SUB2BRT_OBJECT:
			 //Sao�Ǳ�
			case  SYS_SUB2SAO_OBJECT:
			    			
			   		   	    DispEn(0,1,1,strlen(gstrlineEn1),gstrlineEn1);
							DispEn(0,2,1,strlen(gstrlineEn2),gstrlineEn2);             
				   		    DispEn(0,3,1,strlen(gstrlineEn3), gstrlineEn3);									
				   		    DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4); 


														  
							DispEn(0,5,1,strlen(gstrlineEn5), gstrlineEn5);						
				   		    DispEn(0,6,8,strlen(gstrlineEn6), gstrlineEn6);
				   		    DispEn(0,7,8,strlen(gstrlineEn7), gstrlineEn7);						
				   		    DispEn(0,8,8,strlen(gstrlineEn8), gstrlineEn8);
							DispCh(0, 5,15,CharD);
			  	            DispCh(0, 5,18,CharM);
							DispCh(0, 5,21,CharS);
							DispCh(0, 6,15,CharD);
			  	            DispCh(0, 6,18,CharM);
                        	DispCh(0, 6,21,CharS);
							DispCh(0, 8,15,CharD);
			  	            DispCh(0, 8,18,CharM);
							DispCh(0, 8,21,CharS);

			   break;

			 //NGC�Ǳ�
			case  SYS_SUB2NGC_OBJECT:
		   //IC�Ǳ�	
		   	case  SYS_SUB2IC_OBJECT:
				   	       
			   		   	    DispEn(0,1,1,strlen(gstrlineEn1),gstrlineEn1);
							DispEn(0,2,1,14,"Constellation:");   
							DispEn(0,2,15,strlen(gstrlineEn2),gstrlineEn2);             
				   		    DispEn(0,3,1,strlen(gstrlineEn3), gstrlineEn3);	
							DispEn(0,4,1,5,"Type:"); 								
				   		    DispEn(0,4,6,strlen(gstrlineEn4), gstrlineEn4); 


														  
							DispEn(0,5,1,strlen(gstrlineEn5), gstrlineEn5);						
				   		    DispEn(0,6,8,strlen(gstrlineEn6), gstrlineEn6);
				   		    DispEn(0,7,8,strlen(gstrlineEn7), gstrlineEn7);						
				   		    DispEn(0,8,8,strlen(gstrlineEn8), gstrlineEn8);
							DispCh(0, 5,15,CharD);
			  	            DispCh(0, 5,18,CharM);
							DispCh(0, 5,21,CharS);
							DispCh(0, 6,15,CharD);
			  	            DispCh(0, 6,18,CharM);
                        	DispCh(0, 6,21,CharS);
							DispCh(0, 8,15,CharD);
			  	            DispCh(0, 8,18,CharM);
							DispCh(0, 8,21,CharS);
			 break;

			   case  SYS_SUB2SUN_PLANET1:
			   case  SYS_SUB2CON_OBJECT1:
			   case  SYS_SUB2FS_OBJECT1: 			   
			   case  SYS_SUB2MSR_OBJECT1:
		     
		       case  SYS_SUB2SH2_OBJECT1:	
			   case  SYS_SUB2BRT_OBJECT1:
			   case  SYS_SUB2SAO_OBJECT1:
			   	           
			   		   	    DispEn(0,1,1,strlen(gstrlineEn1),gstrlineEn1);
							DispEn(0,2,1,strlen(gstrlineEn2),gstrlineEn2);             
				   		    DispEn(0,3,1,strlen(gstrlineEn3), gstrlineEn3);									
				   		    DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4); 


														  
							DispEn(0,5,1,strlen(gstrlineEn5), gstrlineEn5);						
				   		    DispEn(0,6,8,strlen(gstrlineEn6), gstrlineEn6);
				   		    DispEn(0,7,1,strlen(gstrlineEn7), gstrlineEn7);						
				   		    DispEn(0,8,8,strlen(gstrlineEn8), gstrlineEn8);
							DispCh(0, 5,15,CharD);
			  	            DispCh(0, 5,18,CharM);
							DispCh(0, 5,21,CharS);
							DispCh(0, 6,15,CharD);
			  	            DispCh(0, 6,18,CharM);
                        	DispCh(0, 6,21,CharS);
						   //if(g_mAzEq==0)
						   //{
							 DispCh(0, 7,15,CharD);
			  	             DispCh(0, 7,18,CharM);
							 DispCh(0, 7,21,CharS);
							//}
//							else
//							{
//							   DispEn(0, 7,15,1,"h");
//			  	               DispEn(0, 7,18,1,"m");
//							   DispEn(0, 7,21,1,"s");
//							}

							
							DispCh(0, 8,15,CharD);
			  	            DispCh(0, 8,18,CharM);
							DispCh(0, 8,21,CharS);
//							if(g_mAzEq==1)
//							{
//							  DispEn(0, 7,8,3,"H.a");
//			  	              DispEn(0, 8,8,3,"Dec");
//							  }
						if(g_mOperateStatus==2)
						{
						    MenuDelay(2000);
						    FBeep(1); 
							MenuDelay(1000);
							FBeep(1); 
							MenuDelay(1000);							  
						    g_nsysstatus=SYS_MAINSHOW;					  			   
						}

			   break;
			   case  SYS_SUB2NGC_OBJECT1:
			   case  SYS_SUB2IC_OBJECT1:
			 
				            LCDRfrsh();
			   		   	    DispEn(0,1,1,strlen(gstrlineEn1),gstrlineEn1);
							DispEn(0,2,1,strlen(gstrlineEn2),gstrlineEn2);  
							DispEn(0,3,1,14,"Constellation:");           
				   		    DispEn(0,3,15,strlen(gstrlineEn3), gstrlineEn3);									
				   		    DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4); 


														  
							DispEn(0,5,1,strlen(gstrlineEn5), gstrlineEn5);						
				   		    DispEn(0,6,8,strlen(gstrlineEn6), gstrlineEn6);
				   		    DispEn(0,7,1,strlen(gstrlineEn7), gstrlineEn7);						
				   		    DispEn(0,8,8,strlen(gstrlineEn8), gstrlineEn8);
							DispCh(0, 5,15,CharD);
			  	            DispCh(0, 5,18,CharM);
							DispCh(0, 5,21,CharS);
							DispCh(0, 6,15,CharD);
			  	            DispCh(0, 6,18,CharM);
                        	DispCh(0, 6,21,CharS);
							//if(g_mAzEq==0)
							//{
							DispCh(0, 7,15,CharD);
			  	            DispCh(0, 7,18,CharM);
							DispCh(0, 7,21,CharS);
//							}
//							else
//							{
//							   DispEn(0, 7,15,1,"h");
//			  	               DispEn(0, 7,18,1,"m");
//							   DispEn(0, 7,21,1,"s");
//							}
							DispCh(0, 8,15,CharD);
			  	            DispCh(0, 8,18,CharM);
							DispCh(0, 8,21,CharS);
//							if(g_mAzEq==1)
//							{
//							  DispEn(0, 7,8,3,"H.a");
//			  	              DispEn(0, 8,8,3,"Dec");
//							 }
				    	if(g_mOperateStatus==2)
						{
						    MenuDelay(2000);
						    FBeep(1); 
							MenuDelay(1000);
							FBeep(1); 
							MenuDelay(1000);							  
						    g_nsysstatus=SYS_MAINSHOW;					  			   
						}

			 break;

		
			   //��������
			  case  SYS_SUB2FS_OBJECT:
			    			
			   		   	    DispUn(0,1,1,64,(uint16*)gstrlineEn1);
							//DispEn(0,2,1,strlen(gstrlineEn2),gstrlineEn2);             
				   		    DispEn(0,3,0,strlen(gstrlineEn3), gstrlineEn3);									
				   		    DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4); 


														  
							DispEn(0,5,1,strlen(gstrlineEn5), gstrlineEn5);						
				   		    DispEn(0,6,8,strlen(gstrlineEn6), gstrlineEn6);
				   		    DispEn(0,7,8,strlen(gstrlineEn7), gstrlineEn7);						
				   		    DispEn(0,8,8,strlen(gstrlineEn8), gstrlineEn8);
							DispCh(0, 5,15,CharD);
			  	            DispCh(0, 5,18,CharM);
							DispCh(0, 5,21,CharS);
							DispCh(0, 6,15,CharD);
			  	            DispCh(0, 6,18,CharM);
                        	DispCh(0, 6,21,CharS);
							DispCh(0, 8,15,CharD);
			  	            DispCh(0, 8,18,CharM);
							DispCh(0, 8,21,CharS);

			   break;

			  case  SYS_SUB2MSR_OBJECT0:
			  		
			   		   	    DispEn(0,1,1,strlen(gstrlineEn1),gstrlineEn1);
							DispEn(0,2,1,strlen(gstrlineEn2),gstrlineEn2);             
				   		    DispEn(0,3,1,strlen(gstrlineEn3), gstrlineEn3);									
				   		    DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4); 														  
							DispEn(0,5,1,strlen(gstrlineEn5), gstrlineEn5);						
				   		    DispEn(0,6,1,strlen(gstrlineEn6), gstrlineEn6);
				   		    DispEn(0,7,1,strlen(gstrlineEn7), gstrlineEn7);						
				   		    DispEn(0,8,1,strlen(gstrlineEn8), gstrlineEn8);
					break;
	
	
			   				
				case  SYS_MENU_SKY_OBJECT: 
				case  SYS_MENU_LAND_OBJECT: 
				case  SYS_F_SELFNUM :
			
				    DispEn(0,1,1,strlen(gstrlineEn10), gstrlineEn10);
					
					switch(g_mFnum)
					{
					   case 1:
					    DispEn(1,3,3,2,gstrlineEn1);
						DispEn(0,3,10,2,gstrlineEn2);
						DispEn(0,3,17,2,gstrlineEn3);
						DispEn(0,5,3,2,gstrlineEn4);
						DispEn(0,5,10,2,gstrlineEn5);
						DispEn(0,5,17,2,gstrlineEn6);
			         	DispEn(0,7,3,2,gstrlineEn7);
						DispEn(0,7,10,2,gstrlineEn8);
						DispEn(0,7,17,2,gstrlineEn9);
						break;
					    case 2:
					    DispEn(0,3,3,2,gstrlineEn1);
						DispEn(1,3,10,2,gstrlineEn2);
						DispEn(0,3,17,2,gstrlineEn3);
						DispEn(0,5,3,2,gstrlineEn4);
						DispEn(0,5,10,2,gstrlineEn5);
						DispEn(0,5,17,2,gstrlineEn6);
			         	DispEn(0,7,3,2,gstrlineEn7);
						DispEn(0,7,10,2,gstrlineEn8);
						DispEn(0,7,17,2,gstrlineEn9);
						break;
						 case 3:
					    DispEn(0,3,3,2,gstrlineEn1);
						DispEn(0,3,10,2,gstrlineEn2);
						DispEn(1,3,17,2,gstrlineEn3);
						DispEn(0,5,3,2,gstrlineEn4);
						DispEn(0,5,10,2,gstrlineEn5);
						DispEn(0,5,17,2,gstrlineEn6);
			         	DispEn(0,7,3,2,gstrlineEn7);
						DispEn(0,7,10,2,gstrlineEn8);
						DispEn(0,7,17,2,gstrlineEn9);
						break;
						 case 4:
					    DispEn(0,3,3,2,gstrlineEn1);
						DispEn(0,3,10,2,gstrlineEn2);
						DispEn(0,3,17,2,gstrlineEn3);
						DispEn(1,5,3,2,gstrlineEn4);
						DispEn(0,5,10,2,gstrlineEn5);
						DispEn(0,5,17,2,gstrlineEn6);
			         	DispEn(0,7,3,2,gstrlineEn7);
						DispEn(0,7,10,2,gstrlineEn8);
						DispEn(0,7,17,2,gstrlineEn9);
						break;
						 case 5:
					    DispEn(0,3,3,2,gstrlineEn1);
						DispEn(0,3,10,2,gstrlineEn2);
						DispEn(0,3,17,2,gstrlineEn3);
						DispEn(0,5,3,2,gstrlineEn4);
						DispEn(1,5,10,2,gstrlineEn5);
						DispEn(0,5,17,2,gstrlineEn6);
			         	DispEn(0,7,3,2,gstrlineEn7);
						DispEn(0,7,10,2,gstrlineEn8);
						DispEn(0,7,17,2,gstrlineEn9);
						break;
						 case 6:
					    DispEn(0,3,3,2,gstrlineEn1);
						DispEn(0,3,10,2,gstrlineEn2);
						DispEn(0,3,17,2,gstrlineEn3);
						DispEn(0,5,3,2,gstrlineEn4);
						DispEn(0,5,10,2,gstrlineEn5);
						DispEn(1,5,17,2,gstrlineEn6);
			         	DispEn(0,7,3,2,gstrlineEn7);
						DispEn(0,7,10,2,gstrlineEn8);
						DispEn(0,7,17,2,gstrlineEn9);
						break;
						 case 7:
					    DispEn(0,3,3,2,gstrlineEn1);
						DispEn(0,3,10,2,gstrlineEn2);
						DispEn(0,3,17,2,gstrlineEn3);
						DispEn(0,5,3,2,gstrlineEn4);
						DispEn(0,5,10,2,gstrlineEn5);
						DispEn(0,5,17,2,gstrlineEn6);
			         	DispEn(1,7,3,2,gstrlineEn7);
						DispEn(0,7,10,2,gstrlineEn8);
						DispEn(0,7,17,2,gstrlineEn9);
						break;
						 case 8:
					    DispEn(0,3,3,2,gstrlineEn1);
						DispEn(0,3,10,2,gstrlineEn2);
						DispEn(0,3,17,2,gstrlineEn3);
						DispEn(0,5,3,2,gstrlineEn4);
						DispEn(0,5,10,2,gstrlineEn5);
						DispEn(0,5,17,2,gstrlineEn6);
			         	DispEn(0,7,3,2,gstrlineEn7);
						DispEn(1,7,10,2,gstrlineEn8);
						DispEn(0,7,17,2,gstrlineEn9);
						break;
						 case 9:
					    DispEn(0,3,3,2,gstrlineEn1);
						DispEn(0,3,10,2,gstrlineEn2);
						DispEn(0,3,17,2,gstrlineEn3);
						DispEn(0,5,3,2,gstrlineEn4);
						DispEn(0,5,10,2,gstrlineEn5);
						DispEn(0,5,17,2,gstrlineEn6);
			         	DispEn(0,7,3,2,gstrlineEn7);
						DispEn(0,7,10,2,gstrlineEn8);
						DispEn(1,7,17,2,gstrlineEn9);
						break;

					}

				break;
				

			
	

			   	 case SYS_MENU_SKY_NAME:
		  	        DispCh(0, 8,8,CharD);
					DispCh(0, 8,11,CharM);
					DispCh(0, 8,16,CharS);


			  	    DispEn(0,1,1,strlen(gstrlineEn1), gstrlineEn1);	//��ʾ�ྭ����
		   		    DispEn(0,2,1,strlen(gstrlineEn2), gstrlineEn2);
					DispEn(0,3,1,strlen(gstrlineEn3), gstrlineEn3);
					DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);
					DispEn(0,5,1,strlen(gstrlineEn5), gstrlineEn5);
					DispEn(0,6,1,13, gstrlineEn6);
		   		    DispEn(0,7,1,16, gstrlineEn7);
					DispEn(0,8,1,16, gstrlineEn8);	//��ʾ�ྭ����	

					DispEn(1,6,g_mShowMenucolumn,1,&gstrlineEn6[g_mShowMenucolumn-1]);//��ǰҪ��������ַ��ӱ���
				    DispCh(0, 8,8,CharD);
					DispCh(0, 8,11,CharM);
					DispCh(0, 8,16,CharS);

			        break;

					 
			 	case SYS_MENU_SKY_RA:
		  	        DispCh(0, 8,8,CharD);
					DispCh(0, 8,11,CharM);
					DispCh(0, 8,16,CharS);

			  	    DispEn(0,1,1,strlen(gstrlineEn1), gstrlineEn1);	//��ʾ�ྭ����
		   		    DispEn(0,2,1,strlen(gstrlineEn2), gstrlineEn2);
					DispEn(0,3,1,strlen(gstrlineEn3), gstrlineEn3);
					DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);
					DispEn(0,5,1,strlen(gstrlineEn5), gstrlineEn5);
					DispEn(0,6,1,13, gstrlineEn6);
		   		    DispEn(0,7,1,16, gstrlineEn7);
					DispEn(0,8,1,16, gstrlineEn8);	//��ʾ�ྭ����	

					DispEn(1,7,g_mShowMenucolumn,1,&gstrlineEn7[g_mShowMenucolumn-1]);//��ǰҪ��������ַ��ӱ���
				    DispCh(0, 8,8,CharD);
					DispCh(0, 8,11,CharM);
					DispCh(0, 8,16,CharS);

			        break;
			  	case SYS_MENU_SKY_DEC:
		            DispCh(0, 8,8,CharD);
					DispCh(0, 8,11,CharM);
					DispCh(0, 8,16,CharS);

			  	    DispEn(0,1,1,strlen(gstrlineEn1), gstrlineEn1);	//��ʾ�ྭ����
		   		    DispEn(0,2,1,strlen(gstrlineEn2), gstrlineEn2);
					DispEn(0,3,1,strlen(gstrlineEn3), gstrlineEn3);
					DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);
					DispEn(0,5,1,strlen(gstrlineEn5), gstrlineEn5);
					DispEn(0,6,1,13, gstrlineEn6);
		   		    DispEn(0,7,1,16, gstrlineEn7);
					DispEn(0,8,1,16, gstrlineEn8);	//��ʾ�ྭ����	

					DispEn(1,8,g_mShowMenucolumn,1,&gstrlineEn8[g_mShowMenucolumn-1]);//��ǰҪ��������ַ��ӱ���
				    DispCh(0, 8,8,CharD);
					DispCh(0, 8,11,CharM);
					DispCh(0, 8,16,CharS);

			        break;
							
			   	  case SYS_MENU_LAND_NAME:
				    DispCh(0, 8,8,CharD);
					DispCh(0, 8,11,CharM);
					DispCh(0, 8,16,CharS);
				    DispCh(0, 7,8,CharD);
					DispCh(0, 7,11,CharM);
					DispCh(0, 7,16,CharS);

			  	    DispEn(0,1,1,strlen(gstrlineEn1), gstrlineEn1);	//��ʾ�ྭ����
		   		    DispEn(0,2,1,strlen(gstrlineEn2), gstrlineEn2);
					DispEn(0,3,1,strlen(gstrlineEn3), gstrlineEn3);
					DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);
					DispEn(0,5,1,strlen(gstrlineEn5), gstrlineEn5);
					DispEn(0,6,1,13, gstrlineEn6);
		   		    DispEn(0,7,1,16, gstrlineEn7);
					DispEn(0,8,1,16, gstrlineEn8);	//��ʾ�ྭ����	

					DispEn(0,7,1,3, "Azi");
					DispEn(0,8,1,3, "Alt");	//��ʾ�ྭ����	

					DispEn(1,6,g_mShowMenucolumn,1,&gstrlineEn6[g_mShowMenucolumn-1]);//��ǰҪ��������ַ��ӱ���
				    DispCh(0, 8,8,CharD);
					DispCh(0, 8,11,CharM);
					DispCh(0, 8,16,CharS);
					DispCh(0, 7,8,CharD);
					DispCh(0, 7,11,CharM);
					DispCh(0, 7,16,CharS);

			        break;
				case SYS_MENU_LAND_AZI:	
				 DispCh(0, 8,8,CharD);
					DispCh(0, 8,11,CharM);
					DispCh(0, 8,16,CharS);
					DispCh(0, 7,8,CharD);
					DispCh(0, 7,11,CharM);
					DispCh(0, 7,16,CharS);

			  	    DispEn(0,1,1,strlen(gstrlineEn1), gstrlineEn1);	//��ʾ�ྭ����
		   		    DispEn(0,2,1,strlen(gstrlineEn2), gstrlineEn2);
					DispEn(0,3,1,strlen(gstrlineEn3), gstrlineEn3);
					DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);
					DispEn(0,5,1,strlen(gstrlineEn5), gstrlineEn5);
					DispEn(0,6,1,13, gstrlineEn6);
		   		    DispEn(0,7,1,16, gstrlineEn7);
					DispEn(0,8,1,16, gstrlineEn8);	//��ʾ�ྭ����
					
					DispEn(0,7,1,3, "Azi");
					DispEn(0,8,1,3, "Alt");	//��ʾ�ྭ����	

					DispEn(1,7,g_mShowMenucolumn,1,&gstrlineEn7[g_mShowMenucolumn-1]);//��ǰҪ��������ַ��ӱ���
				    DispCh(0, 8,8,CharD);
					DispCh(0, 8,11,CharM);
					DispCh(0, 8,16,CharS);
						 DispCh(0, 7,8,CharD);
					DispCh(0, 7,11,CharM);
					DispCh(0, 7,16,CharS);

			        break;	
				case SYS_MENU_LAND_ALT:
				    DispCh(0, 8,8,CharD);
					DispCh(0, 8,11,CharM);
					DispCh(0, 8,16,CharS);
					DispCh(0, 7,8,CharD);
					DispCh(0, 7,11,CharM);
					DispCh(0, 7,16,CharS);

			  	    DispEn(0,1,1,strlen(gstrlineEn1), gstrlineEn1);	//��ʾ�ྭ����
		   		    DispEn(0,2,1,strlen(gstrlineEn2), gstrlineEn2);
					DispEn(0,3,1,strlen(gstrlineEn3), gstrlineEn3);
					DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);
					DispEn(0,5,1,strlen(gstrlineEn5), gstrlineEn5);
					DispEn(0,6,1,13, gstrlineEn6);
		   		    DispEn(0,7,1,16, gstrlineEn7);
					DispEn(0,8,1,16, gstrlineEn8);	//��ʾ�ྭ����
						
				
				   	 DispEn(0,7,1,3, "Azi");
					 DispEn(0,8,1,3, "Alt");	//��ʾ�ྭ����


					DispEn(1,8,g_mShowMenucolumn,1,&gstrlineEn8[g_mShowMenucolumn-1]);//��ǰҪ��������ַ��ӱ���
				    DispCh(0, 8,8,CharD);
					DispCh(0, 8,11,CharM);
					DispCh(0, 8,16,CharS);
					DispCh(0, 7,8,CharD);
					DispCh(0, 7,11,CharM);
					DispCh(0, 7,16,CharS);

			        break;

	
							    
		
		
		      //ϵͳ�ྭ��γ������ʾ
			  case 	SYS_SUB2SUB9RA:
		  	        DispCh(0, 5,8,CharD);
					DispCh(0, 5,11,CharM);
					DispCh(0, 5,16,CharS);

			  	    DispEn(0,1,1,strlen(gstrlineEn1), gstrlineEn1);	//��ʾ�ྭ����
		   		    DispEn(0,2,1,strlen(gstrlineEn2), gstrlineEn2);
		   		    DispEn(0,3,1,16, gstrlineEn3);
		   	    	DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);
					DispEn(0,5,1,16, gstrlineEn5);	//��ʾ�ྭ����
		   		    DispEn(0,6,1,strlen(gstrlineEn6), gstrlineEn6);
		   		    DispEn(0,7,1,strlen(gstrlineEn7), gstrlineEn7);
		   	    	DispEn(0,8,1,strlen(gstrlineEn8), gstrlineEn8);		

					DispEn(1,3,g_mShowMenucolumn,1,&gstrlineEn3[g_mShowMenucolumn-1]);//��ǰҪ��������ַ��ӱ���
				    DispCh(0, 5,8,CharD);
					DispCh(0, 5,11,CharM);
					DispCh(0, 5,16,CharS);

			        break;
			  case SYS_SUB2SUB9DEC:
		            DispCh(0, 5,8,CharD);
					DispCh(0, 5,11,CharM);
					DispCh(0, 5,16,CharS);

				  	DispEn(0,1,1,strlen(gstrlineEn1), gstrlineEn1);	//��ʾ�ྭ����
		   		    DispEn(0,2,1,strlen(gstrlineEn2), gstrlineEn2);
		   		    DispEn(0,3,1,16, gstrlineEn3);
		   	    	DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);
					DispEn(0,5,1,16, gstrlineEn5);	//��ʾ�ྭ����
		   		    DispEn(0,6,1,strlen(gstrlineEn6), gstrlineEn6);
		   		    DispEn(0,7,1,strlen(gstrlineEn7), gstrlineEn7);
		   	    	DispEn(0,8,1,strlen(gstrlineEn8), gstrlineEn8);		


					DispEn(1,5,g_mShowMenucolumn,1,&gstrlineEn5[g_mShowMenucolumn-1]);//��ǰҪ��������ַ��ӱ���
				    DispCh(0, 5,8,CharD);
					DispCh(0, 5,11,CharM);
					DispCh(0, 5,16,CharS);

			        break;

				//�Զ����ٶ�������ʾ����
			 case SYS_SUB4SUB8MENU4_RASPEED:
			       	DispEn(0,1,1,strlen(gstrlineEn1), gstrlineEn1);	//��ʾ�ྭ����
		   		    DispEn(0,2,1,strlen(gstrlineEn2), gstrlineEn2);
		   		    DispEn(0,3,1,strlen(gstrlineEn3), gstrlineEn3);
		   	    	DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);
					DispEn(0,5,1,strlen(gstrlineEn5), gstrlineEn5);
		   		    DispEn(0,6,1,strlen(gstrlineEn6), gstrlineEn6);
		   		    DispEn(0,7,1,strlen(gstrlineEn7), gstrlineEn7);
		   	    	DispEn(0,8,1,strlen(gstrlineEn8), gstrlineEn8);		
					DispEn(1,4,g_mShowMenucolumn,1,&gstrlineEn4[g_mShowMenucolumn-1]);//��ǰҪ��������ַ��ӱ���
	               break ;

			 //ʱ������
	          case  SYS_SUB4SUB1_SETTIME:
			        switch(	g_mdatetime)
					{
					  case 0://��������
				       	DispEn(0,1,1,strlen(gstrlineEn1), gstrlineEn1);	//��ʾ�ྭ����
			   		    DispEn(0,2,1,strlen(gstrlineEn2), gstrlineEn2);
			   		    DispEn(0,3,1,strlen(gstrlineEn3), gstrlineEn3);
			   	    	DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);
						DispEn(0,5,1,strlen(gstrlineEn5), gstrlineEn5);
			   		    DispEn(0,6,1,strlen(gstrlineEn6), gstrlineEn6);
			   		    DispEn(0,7,1,strlen(gstrlineEn7), gstrlineEn7);
			   	    	DispEn(0,8,1,strlen(gstrlineEn8), gstrlineEn8);		
						DispEn(1,3,g_mShowMenucolumn,1,&gstrlineEn3[g_mShowMenucolumn-1]);//��ǰҪ��������ַ��ӱ���
		          	   break;
					   case 1://ʱ������
					   	DispEn(0,1,1,strlen(gstrlineEn1), gstrlineEn1);	//��ʾ�ྭ����
			   		    DispEn(0,2,1,strlen(gstrlineEn2), gstrlineEn2);
			   		    DispEn(0,3,1,strlen(gstrlineEn3), gstrlineEn3);
			   	    	DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);
						DispEn(0,5,1,strlen(gstrlineEn5), gstrlineEn5);
			   		    DispEn(0,6,1,strlen(gstrlineEn6), gstrlineEn6);
			   		    DispEn(0,7,1,strlen(gstrlineEn7), gstrlineEn7);
			   	    	DispEn(0,8,1,strlen(gstrlineEn8), gstrlineEn8);		
						DispEn(1,5,g_mShowMenucolumn,1,&gstrlineEn5[g_mShowMenucolumn-1]);//��ǰҪ��������ַ��ӱ���
		     	   break;
					   default:
					   break;
					 }
			 break;
			 //���ʳ���
			 case SYS_SUB4SUB3SUN1_CITYSEL:
			    
   		   	    DispEn(0,1,1,strlen(gstrlineEn1),gstrlineEn1);
				DispEn(0,2,1,strlen(gstrlineEn2),gstrlineEn2);             
	   		    DispEn(0,3,1,strlen(gstrlineEn3), gstrlineEn3);									
	   		    DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4); 														  
				DispEn(0,5,1,strlen(gstrlineEn5), gstrlineEn5);						
	   		    DispEn(0,6,1,strlen(gstrlineEn6), gstrlineEn6);
	   		    DispEn(0,7,1,strlen(gstrlineEn7), gstrlineEn7);						
	   		    DispEn(0,8,1,strlen(gstrlineEn8), gstrlineEn8);
				DispCh(0, 3,14,CharD);
				DispCh(0, 3,17,CharM);
				DispCh(0, 4,14,CharD);
				DispCh(0, 4,17,CharM);
             break;
			//�Զ���ص����
	        case SYS_SUB4SUB3_SETSITE : 
			    DispCh(0, 4,11,CharD);
				DispCh(0, 4,14,CharM);
				DispCh(0, 5,10,CharD);
				DispCh(0, 5,13,CharM);
		            DispEn(0,1,1,strlen(gstrlineEn1), gstrlineEn1);
		   		    DispEn(0,2,1,strlen(gstrlineEn2), gstrlineEn2);
		   		    DispEn(0,3,1,strlen(gstrlineEn3), gstrlineEn3);
		   	    	DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);
					DispEn(0,5,1,strlen(gstrlineEn5), gstrlineEn5);
		   		    DispEn(0,6,1,strlen(gstrlineEn6), gstrlineEn6);
		   		    DispEn(0,7,1,strlen(gstrlineEn7), gstrlineEn7);
		   	    	DispEn(0,8,1,strlen(gstrlineEn8), gstrlineEn8);
			
					   	switch(g_mMySiteShowMode)
						{
						  case 0:
						  	DispEn(1,3,g_mShowMenucolumn,1,&gstrlineEn3[g_mShowMenucolumn-1]);
						  	break;
						  case 1:
						  	DispEn(1,4,g_mShowMenucolumn,1,&gstrlineEn4[g_mShowMenucolumn-1]);
						  	break;
						  case 2:
						    DispEn(1,5,g_mShowMenucolumn,1,&gstrlineEn5[g_mShowMenucolumn-1]);
						  	break;
						  case 3:
						    DispEn(1,6,g_mShowMenucolumn,1,&gstrlineEn6[g_mShowMenucolumn-1]);
						  	break;
					
						}
			    DispCh(0, 4,11,CharD);
				DispCh(0, 4,14,CharM);
				DispCh(0, 5,10,CharD);
				DispCh(0, 5,13,CharM);
					 break ; 
//				//�����Ӳ˵���ʾ����
//		   	case SYS_SUB4SUB4WEATHER:	
//			        DispEn(0,1,1,strlen(gstrlineEn1), gstrlineEn1);
//		   		    DispEn(0,2,1,strlen(gstrlineEn2), gstrlineEn2);
//		   		    DispEn(0,3,1,strlen(gstrlineEn3), gstrlineEn3);
//		   	    	DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);
//					DispEn(0,5,1,strlen(gstrlineEn5), gstrlineEn5);
//					DispEn(0,6,1,strlen(gstrlineEn7), gstrlineEn6);
//					DispEn(0,7,1,strlen(gstrlineEn7), gstrlineEn7);
//					DispEn(0,8,1,strlen(gstrlineEn8), gstrlineEn8);
//				 	switch(g_mWeatherShowMode)
//						{
//						  case 0:
//						   DispEn(1,1,g_mShowMenucolumn,1,&gstrlineEn1[g_mShowMenucolumn-1]);
//						  break;
//						  case 1:
//						  DispEn(1,3,g_mShowMenucolumn,1,&gstrlineEn3[g_mShowMenucolumn-1]);
//						  break;
//						  case 2:
//						    DispEn(1,5,g_mShowMenucolumn,1,&gstrlineEn5[g_mShowMenucolumn-1]);
//						  break;	
//						  default:
//						  break;
//						}
//
//			    break;


		   //��Զ�������ʾ����
		    case SYS_SUB4SUB7_TELZERO_OK:
		   	case SYS_SUB4SUB7_TELAZIALT_ZERO:	
			        DispEn(0,1,1,strlen(gstrlineEn1), gstrlineEn1);
		   		    DispEn(0,2,1,strlen(gstrlineEn2), gstrlineEn2);
		   		    DispEn(0,3,1,8, gstrlineEn3);
		   	    	DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);


					DispEn(0,5,1,8, gstrlineEn5);
					DispEn(0,6,1,strlen(gstrlineEn7), gstrlineEn6);
					DispEn(0,7,1,strlen(gstrlineEn7), gstrlineEn7);
					DispEn(0,8,1,strlen(gstrlineEn8), gstrlineEn8);
				 	switch(g_mTelZeroShowMode)
						{
						  case 0:
						   DispEn(1,3,g_mShowMenucolumn,1,&gstrlineEn3[g_mShowMenucolumn-1]);
						  break;
						  case 1:
						   DispEn(1,5,g_mShowMenucolumn,1,&gstrlineEn5[g_mShowMenucolumn-1]);
						  break;
						  default:
						  break;
						}
					DispCh(0, 3,8,CharD);
					DispCh(0, 5,8,CharD);

			    break;

			case SYS_RESET:	//�˳��ָ�����״̬ 

			    DispEn(0,1,1,21, "Are you sure reset   ");
				DispEn(0,3,1,21, "System.                ");
				DispEn(0,5,1,21, "Back: Cancel          ");
				DispEn(0,7,1,21, "Enter: Begin Reset      ");

		     break;




		//������ʾ����
		   	case SYS_SUB3SUB3_MOONPHASE	:			  
		        dispMoonphase(g_mMoonPhaseYear,g_mMoonPhaseMonth);
			    break;



//********************************************************************
//����ʱ�趨��ʱ״̬��ʾ
		case SYS_SUB3SUB4TIMER_INPUT:
	  	    DispEn(0,1,1,strlen(gstrlineEn1), gstrlineEn1);	
   		    DispEn(0,2,1,strlen(gstrlineEn2), gstrlineEn2);
   		    DispEn(0,3,1,strlen(gstrlineEn3), gstrlineEn3);
   	    	DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);	
			DispEn(0,5,1,strlen(gstrlineEn5), gstrlineEn5);
			DispEn(0,6,1,strlen(gstrlineEn7), gstrlineEn6);
			DispEn(0,7,1,strlen(gstrlineEn7), gstrlineEn7);
			DispEn(0,8,1,strlen(gstrlineEn8), gstrlineEn8);
			DispEn(1,3,g_mShowMenucolumn,1,&gstrlineEn3[g_mShowMenucolumn-1]);//��ǰҪ��������ַ��ӱ���
	        break;
	//������ʾ
	  case 	SYS_SUB3SUB5ALARM_INPUT:
	  	    DispEn(0,1,1,strlen(gstrlineEn1), gstrlineEn1);
   	    	DispEn(0,2,1,strlen(gstrlineEn2), gstrlineEn2);
   		    DispEn(0,3,1,strlen(gstrlineEn3), gstrlineEn3);
   		    DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);
			DispEn(0,5,1,strlen(gstrlineEn5), gstrlineEn5);
   	    	DispEn(0,6,1,strlen(gstrlineEn6), gstrlineEn6);
   		    DispEn(0,7,1,strlen(gstrlineEn7), gstrlineEn7);
   		    DispEn(0,8,1,strlen(gstrlineEn8), gstrlineEn8);
			DispEn(1,3,g_mShowMenucolumn,1,&gstrlineEn3[g_mShowMenucolumn-1]);//��ǰҪ��������ַ��ӱ���
	        break;

	//���ʼ��㣺
   	case SYS_SUB3SUB6SUB2M_MF:	
        	DispEn(0,1,1,strlen(gstrlineEn1), gstrlineEn1);
   		    DispEn(0,2,1,strlen(gstrlineEn2), gstrlineEn2);
   		    DispEn(0,3,1,strlen(gstrlineEn3), gstrlineEn3);
   		    DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);
			DispEn(0,5,1,strlen(gstrlineEn5), gstrlineEn5);
   		    DispEn(0,6,1,strlen(gstrlineEn6), gstrlineEn6);
   		    DispEn(0,7,1,strlen(gstrlineEn7), gstrlineEn7);
   		    DispEn(0,8,1,strlen(gstrlineEn8), gstrlineEn8);
			DispEn(1,3,g_mShowMenucolumn,1,&gstrlineEn3[g_mShowMenucolumn-1]);//��ǰҪ��������ַ��ӱ���
	       break;	
	case SYS_SUB3SUB6SUB2M_SF:	
        	DispEn(0,1,1,strlen(gstrlineEn1), gstrlineEn1);
   		    DispEn(0,2,1,strlen(gstrlineEn2), gstrlineEn2);
   		    DispEn(0,3,1,strlen(gstrlineEn3), gstrlineEn3);
   		    DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);
			DispEn(0,5,1,strlen(gstrlineEn5), gstrlineEn5);
   		    DispEn(0,6,1,strlen(gstrlineEn6), gstrlineEn6);
   		    DispEn(0,7,1,strlen(gstrlineEn7), gstrlineEn7);
   		    DispEn(0,8,1,strlen(gstrlineEn8), gstrlineEn8);
			DispEn(1,5,g_mShowMenucolumn,1,&gstrlineEn5[g_mShowMenucolumn-1]);//��ǰҪ��������ַ��ӱ���
	       break;	

	   	case SYS_SUB3SUB6SUB2M_MF1:	
        	DispEn(0,1,1,strlen(gstrlineEn1), gstrlineEn1);
   		    DispEn(0,2,1,strlen(gstrlineEn2), gstrlineEn2);
   		    DispEn(0,3,1,strlen(gstrlineEn3), gstrlineEn3);
   		    DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);
			DispEn(0,5,1,strlen(gstrlineEn5), gstrlineEn5);
   		    DispEn(0,6,1,strlen(gstrlineEn6), gstrlineEn6);
   		    DispEn(0,7,1,strlen(gstrlineEn7), gstrlineEn7);
   		    DispEn(0,8,1,strlen(gstrlineEn8), gstrlineEn8);
			DispEn(1,3,g_mShowMenucolumn,1,&gstrlineEn3[g_mShowMenucolumn-1]);//��ǰҪ��������ַ��ӱ���
			DispCh(0,7,10,CharD);
			DispCh(0,7,13,CharM);
			DispCh(0,8,21,CharD);
	       break;	
	case SYS_SUB3SUB6SUB2M_SF1:	
        	DispEn(0,1,1,strlen(gstrlineEn1), gstrlineEn1);
   		    DispEn(0,2,1,strlen(gstrlineEn2), gstrlineEn2);
   		    DispEn(0,3,1,strlen(gstrlineEn3), gstrlineEn3);
   		    DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);
			DispEn(0,5,1,strlen(gstrlineEn5), gstrlineEn5);
   		    DispEn(0,6,1,strlen(gstrlineEn6), gstrlineEn6);
   		    DispEn(0,7,1,strlen(gstrlineEn7), gstrlineEn7);
   		    DispEn(0,8,1,strlen(gstrlineEn8), gstrlineEn8);
			DispEn(1,5,g_mShowMenucolumn,1,&gstrlineEn5[g_mShowMenucolumn-1]);//��ǰҪ��������ַ��ӱ���
			DispCh(0,7,10,CharD);
			DispCh(0,7,13,CharM);
			DispCh(0,8,21,CharD);
	       break;
		case SYS_SUB3SUB6SUB2M_MFOV:	
        	DispEn(0,1,1,strlen(gstrlineEn1), gstrlineEn1);
   		    DispEn(0,2,1,strlen(gstrlineEn2), gstrlineEn2);
   		    DispEn(0,3,1,strlen(gstrlineEn3), gstrlineEn3);
   		    DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);
			DispEn(0,5,1,strlen(gstrlineEn5), gstrlineEn5);
   		    DispEn(0,6,1,strlen(gstrlineEn6), gstrlineEn6);
   		    DispEn(0,7,1,strlen(gstrlineEn7), gstrlineEn7);
   		    DispEn(0,8,1,strlen(gstrlineEn8), gstrlineEn8);
			DispEn(1,7,g_mShowMenucolumn,1,&gstrlineEn7[g_mShowMenucolumn-1]);//��ǰҪ��������ַ��ӱ���
			DispCh(0,7,10,CharD);
			DispCh(0,7,13,CharM);
			DispCh(0,8,21,CharD);
	       break;
	//½��Ŀ��
	      case SYS_SUB2SUB11_SET : 
		            DispEn(0,1,1,strlen(gstrlineEn1), gstrlineEn1);
		   		    DispEn(0,2,1,strlen(gstrlineEn2), gstrlineEn2);
		   		    DispEn(0,3,1,strlen(gstrlineEn3), gstrlineEn3);
		   	    	DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);
					DispEn(0,5,1,strlen(gstrlineEn5), gstrlineEn5);
		   		    DispEn(0,6,1,strlen(gstrlineEn6), gstrlineEn6);
		   		    DispEn(0,7,1,strlen(gstrlineEn7), gstrlineEn7);
		   	    	DispEn(0,8,1,strlen(gstrlineEn8), gstrlineEn8);
					switch(g_mMyLandmarkOperator)
					{
				   		case 1:
							switch(g_mMyLandmarkShowMode)
							{
						 	 case 0:
						  		DispEn(1,2,g_mShowMenucolumn,1,&gstrlineEn2[g_mShowMenucolumn-1]);
						  		break;
						 	 case 1:
						 	 	DispEn(1,3,g_mShowMenucolumn,1,&gstrlineEn3[g_mShowMenucolumn-1]);
						 	 	break;
						 	 case 2:
						 	   DispEn(1,4,g_mShowMenucolumn,1,&gstrlineEn4[g_mShowMenucolumn-1]);
							  	break;
						 	 default:
						  		break;
							}
				 		default :
				  			break;		 
					}
					break;
	//�Զ����Ǳ�
		   case SYS_SUB2SUB8_SET : 
		            DispEn(0,1,1,strlen(gstrlineEn1), gstrlineEn1);
		   		    DispEn(0,2,1,strlen(gstrlineEn2), gstrlineEn2);
		   		    DispEn(0,3,1,strlen(gstrlineEn3), gstrlineEn3);
		   	    	DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);
					DispEn(0,5,1,strlen(gstrlineEn5), gstrlineEn5);
		   		    DispEn(0,6,1,strlen(gstrlineEn6), gstrlineEn6);
		   		    DispEn(0,7,1,strlen(gstrlineEn7), gstrlineEn7);
		   	    	DispEn(0,8,1,strlen(gstrlineEn8), gstrlineEn8);
					switch(g_mMyStarOperator)
					{
				   		case 1:
						case 3:
							switch(g_mMyStarShowMode)
							{
						 	 case 0:
						  		DispEn(1,2,g_mShowMenucolumn,1,&gstrlineEn2[g_mShowMenucolumn-1]);
						  		break;
						 	 case 1:
						 	 	DispEn(1,3,g_mShowMenucolumn,1,&gstrlineEn3[g_mShowMenucolumn-1]);
						 	 	break;
						 	 case 2:
						 	   DispEn(1,4,g_mShowMenucolumn,1,&gstrlineEn4[g_mShowMenucolumn-1]);
							  	break;
						 	 default:
						  		break;
							}
				 		default :
				  			break;		 
					}
					break;

//*****************************************************************************
		
		
		      default: 
			  //ϵͳ�˵���ʾ	      
		        switch(g_mShowMenurowEn) //���˵���ʾ�����Ҫ�������ʾ��g_mShowMenurowEnҪ����6
		        {
		           case 0:
		   		    DispEn(0,1,1,strlen(gstrlineEn1), gstrlineEn1);
		   		    DispEn(0,2,1,strlen(gstrlineEn2), gstrlineEn2);
		   		    DispEn(0,3,1,strlen(gstrlineEn3), gstrlineEn3);
		   		    DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);
					DispEn(0,5,1,strlen(gstrlineEn5), gstrlineEn5);
		   		    DispEn(0,6,1,strlen(gstrlineEn6), gstrlineEn6);
		   		    DispEn(0,7,1,strlen(gstrlineEn7), gstrlineEn7);
		   		    DispEn(0,8,1,strlen(gstrlineEn8), gstrlineEn8);
		   		   break ;
			      case 1:
		   		    DispEn(1,1,1,strlen(gstrlineEn1), gstrlineEn1);
		   		    DispEn(0,2,1,strlen(gstrlineEn2), gstrlineEn2);
		   		    DispEn(0,3,1,strlen(gstrlineEn3), gstrlineEn3);
		   		    DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);
					DispEn(0,5,1,strlen(gstrlineEn5), gstrlineEn5);
		   		    DispEn(0,6,1,strlen(gstrlineEn6), gstrlineEn6);
		   		    DispEn(0,7,1,strlen(gstrlineEn7), gstrlineEn7);
		   		    DispEn(0,8,1,strlen(gstrlineEn8), gstrlineEn8);
		   		  break ;
		          case 2:
		   		    DispEn(0,1,1,strlen(gstrlineEn1), gstrlineEn1);
		   		    DispEn(2,2,1,strlen(gstrlineEn2), gstrlineEn2);
		   		    DispEn(0,3,1,strlen(gstrlineEn3), gstrlineEn3);
		   		    DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);
					DispEn(0,5,1,strlen(gstrlineEn5), gstrlineEn5);
		   		    DispEn(0,6,1,strlen(gstrlineEn6), gstrlineEn6);
		   		    DispEn(0,7,1,strlen(gstrlineEn7), gstrlineEn7);
		   		    DispEn(0,8,1,strlen(gstrlineEn8), gstrlineEn8);
		   		  break ;
			      case 3:
		   	 	    DispEn(0,1,1,strlen(gstrlineEn1), gstrlineEn1);
		   		    DispEn(0,2,1,strlen(gstrlineEn2), gstrlineEn2);
		   		    DispEn(1,3,1,strlen(gstrlineEn3), gstrlineEn3);
		   		    DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);
					DispEn(0,5,1,strlen(gstrlineEn5), gstrlineEn5);
		   		    DispEn(0,6,1,strlen(gstrlineEn6), gstrlineEn6);
		   		    DispEn(0,7,1,strlen(gstrlineEn7), gstrlineEn7);
		   		    DispEn(0,8,1,strlen(gstrlineEn8), gstrlineEn8);
		   	      break ;
				  case 4:
		   		    DispEn(0,1,1,strlen(gstrlineEn1), gstrlineEn1);
		   		    DispEn(0,2,1,strlen(gstrlineEn2), gstrlineEn2);
		   		    DispEn(0,3,1,strlen(gstrlineEn3), gstrlineEn3);
		   		    DispEn(1,4,1,strlen(gstrlineEn4), gstrlineEn4);
					DispEn(0,5,1,strlen(gstrlineEn5), gstrlineEn5);
		   		    DispEn(0,6,1,strlen(gstrlineEn6), gstrlineEn6);
		   		    DispEn(0,7,1,strlen(gstrlineEn7), gstrlineEn7);
		   		    DispEn(0,8,1,strlen(gstrlineEn8), gstrlineEn8);
		   		  break ;
			 	 case 5:
		   		    DispEn(0,1,1,strlen(gstrlineEn1), gstrlineEn1);
		   		    DispEn(0,2,1,strlen(gstrlineEn2), gstrlineEn2);
		   		    DispEn(0,3,1,strlen(gstrlineEn3), gstrlineEn3);
		   		    DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);
					DispEn(1,5,1,strlen(gstrlineEn5), gstrlineEn5);
		   		    DispEn(0,6,1,strlen(gstrlineEn6), gstrlineEn6);
		   		    DispEn(0,7,1,strlen(gstrlineEn7), gstrlineEn7);
		   		    DispEn(0,8,1,strlen(gstrlineEn8), gstrlineEn8);
		   	    	break ;
				case 6:
				    DispEn(0,1,1,strlen(gstrlineEn1), gstrlineEn1);
		   		    DispEn(0,2,1,strlen(gstrlineEn2), gstrlineEn2);
		   		    DispEn(0,3,1,strlen(gstrlineEn3), gstrlineEn3);
		   		    DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);
					DispEn(0,5,1,strlen(gstrlineEn5), gstrlineEn5);
		   		    DispEn(1,6,1,strlen(gstrlineEn6), gstrlineEn6);
		   		    DispEn(0,7,1,strlen(gstrlineEn7), gstrlineEn7);
		   		    DispEn(0,8,1,strlen(gstrlineEn8), gstrlineEn8);
				break;
				case 7:
				   DispEn(0,1,1,strlen(gstrlineEn1), gstrlineEn1);
		   		    DispEn(0,2,1,strlen(gstrlineEn2), gstrlineEn2);
		   		    DispEn(0,3,1,strlen(gstrlineEn3), gstrlineEn3);
		   		    DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);
					DispEn(0,5,1,strlen(gstrlineEn5), gstrlineEn5);
		   		    DispEn(0,6,1,strlen(gstrlineEn6), gstrlineEn6);
		   		    DispEn(1,7,1,strlen(gstrlineEn7), gstrlineEn7);
		   		    DispEn(0,8,1,strlen(gstrlineEn8), gstrlineEn8);
				break;
				case 8:
				    DispEn(0,1,1,strlen(gstrlineEn1), gstrlineEn1);
		   		    DispEn(0,2,1,strlen(gstrlineEn2), gstrlineEn2);
		   		    DispEn(0,3,1,strlen(gstrlineEn3), gstrlineEn3);
		   		    DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);
					DispEn(0,5,1,strlen(gstrlineEn5), gstrlineEn5);
		   		    DispEn(0,6,1,strlen(gstrlineEn6), gstrlineEn6);
		   		    DispEn(0,7,1,strlen(gstrlineEn7), gstrlineEn7);
		   		    DispEn(1,8,1,strlen(gstrlineEn8), gstrlineEn8);
				break;
				   default:break;
		         }
		   break;
		   }
	  break;
	  case 2://����//����//�������//��������
	  	g_mshowed1=g_nsysstatus;
		if(g_mshowed1!=g_mshowed2)  //��Զ��״̬����Ͳ�ˢ��,״̬���ˢ��
		{
		    
		      LCDRfrsh();
			  g_mshowed2=g_mshowed1;
		} 
		
		
		switch(g_nsysstatus )
		{
		       //ϵͳ����������ʾ
			   case SYS_MAINSHOW:
				
			    if(g_mcalpalnet==1)//û��������,���г�ʼ����ʾ
		        {
			     FSysMainShow();
				 }

				break;

			case SYS_MENUSHOW:
			 if(g_RecentNum!=0)
		     {	
			 	
			     switch(g_mShowMenurowEn) 
		        {
		        
			      case 1:
					DispEn(1,1,1,2,gstrlineEn9);
		   		    DispEn(0,2,1,2,gstrlineEn10);
		   		    DispEn(0,3,1,2,gstrlineEn11);
		   		    DispEn(0,4,1,2,gstrlineEn12);
					DispEn(0,5,1,2,gstrlineEn13);
		   		    DispEn(0,6,1,2,gstrlineEn14);
		   		    DispEn(0,7,1,2,gstrlineEn15);
		   		    DispEn(0,8,1,2,gstrlineEn16);

		   		    DispEn(1,1,3,strlen(gstrlineEn1), gstrlineEn1);
		   		    DispEn(0,2,3,strlen(gstrlineEn2), gstrlineEn2);
		   		    DispEn(0,3,3,strlen(gstrlineEn3), gstrlineEn3);
		   		    DispEn(0,4,3,strlen(gstrlineEn4), gstrlineEn4);
					DispEn(0,5,3,strlen(gstrlineEn5), gstrlineEn5);
		   		    DispEn(0,6,3,strlen(gstrlineEn6), gstrlineEn6);
		   		    DispEn(0,7,3,strlen(gstrlineEn7), gstrlineEn7);
		   		    DispEn(0,8,3,strlen(gstrlineEn8), gstrlineEn8);
		   		  break ;
		          case 2:
				    DispEn(0,1,1,2,gstrlineEn9);
		   		    DispEn(1,2,1,2,gstrlineEn10);
		   		    DispEn(0,3,1,2,gstrlineEn11);
		   		    DispEn(0,4,1,2,gstrlineEn12);
					DispEn(0,5,1,2,gstrlineEn13);
		   		    DispEn(0,6,1,2,gstrlineEn14);
		   		    DispEn(0,7,1,2,gstrlineEn15);
		   		    DispEn(0,8,1,2,gstrlineEn16);

		   		    DispEn(0,1,3,strlen(gstrlineEn1), gstrlineEn1);
		   		    DispEn(2,2,3,strlen(gstrlineEn2), gstrlineEn2);
		   		    DispEn(0,3,3,strlen(gstrlineEn3), gstrlineEn3);
		   		    DispEn(0,4,3,strlen(gstrlineEn4), gstrlineEn4);
					DispEn(0,5,3,strlen(gstrlineEn5), gstrlineEn5);
		   		    DispEn(0,6,3,strlen(gstrlineEn6), gstrlineEn6);
		   		    DispEn(0,7,3,strlen(gstrlineEn7), gstrlineEn7);
		   		    DispEn(0,8,3,strlen(gstrlineEn8), gstrlineEn8);
		   		  break ;
			      case 3:
				  DispEn(0,1,1,2,gstrlineEn9);
		   		    DispEn(0,2,1,2,gstrlineEn10);
		   		    DispEn(1,3,1,2,gstrlineEn11);
		   		    DispEn(0,4,1,2,gstrlineEn12);
					DispEn(0,5,1,2,gstrlineEn13);
		   		    DispEn(0,6,1,2,gstrlineEn14);
		   		    DispEn(0,7,1,2,gstrlineEn15);
		   		    DispEn(0,8,1,2,gstrlineEn16);

		   	 	    DispEn(0,1,3,strlen(gstrlineEn1), gstrlineEn1);
		   		    DispEn(0,2,3,strlen(gstrlineEn2), gstrlineEn2);
		   		    DispEn(1,3,3,strlen(gstrlineEn3), gstrlineEn3);
		   		    DispEn(0,4,3,strlen(gstrlineEn4), gstrlineEn4);
					DispEn(0,5,3,strlen(gstrlineEn5), gstrlineEn5);
		   		    DispEn(0,6,3,strlen(gstrlineEn6), gstrlineEn6);
		   		    DispEn(0,7,3,strlen(gstrlineEn7), gstrlineEn7);
		   		    DispEn(0,8,3,strlen(gstrlineEn8), gstrlineEn8);
		   	      break ;
				  case 4:
				    DispEn(0,1,1,2,gstrlineEn9);
		   		    DispEn(0,2,1,2,gstrlineEn10);
		   		    DispEn(0,3,1,2,gstrlineEn11);
		   		    DispEn(1,4,1,2,gstrlineEn12);
					DispEn(0,5,1,2,gstrlineEn13);
		   		    DispEn(0,6,1,2,gstrlineEn14);
		   		    DispEn(0,7,1,2,gstrlineEn15);
		   		    DispEn(0,8,1,2,gstrlineEn16);

		   		    DispEn(0,1,3,strlen(gstrlineEn1), gstrlineEn1);
		   		    DispEn(0,2,3,strlen(gstrlineEn2), gstrlineEn2);
		   		    DispEn(0,3,3,strlen(gstrlineEn3), gstrlineEn3);
		   		    DispEn(1,4,3,strlen(gstrlineEn4), gstrlineEn4);
					DispEn(0,5,3,strlen(gstrlineEn5), gstrlineEn5);
		   		    DispEn(0,6,3,strlen(gstrlineEn6), gstrlineEn6);
		   		    DispEn(0,7,3,strlen(gstrlineEn7), gstrlineEn7);
		   		    DispEn(0,8,3,strlen(gstrlineEn8), gstrlineEn8);
		   		  break ;
			 	 case 5:
				    DispEn(0,1,1,2,gstrlineEn9);
		   		    DispEn(0,2,1,2,gstrlineEn10);
		   		    DispEn(0,3,1,2,gstrlineEn11);
		   		    DispEn(0,4,1,2,gstrlineEn12);
					DispEn(1,5,1,2,gstrlineEn13);
		   		    DispEn(0,6,1,2,gstrlineEn14);
		   		    DispEn(0,7,1,2,gstrlineEn15);
		   		    DispEn(0,8,1,2,gstrlineEn16);

		   		    DispEn(0,1,3,strlen(gstrlineEn1), gstrlineEn1);
		   		    DispEn(0,2,3,strlen(gstrlineEn2), gstrlineEn2);
		   		    DispEn(0,3,3,strlen(gstrlineEn3), gstrlineEn3);
		   		    DispEn(0,4,3,strlen(gstrlineEn4), gstrlineEn4);
					DispEn(1,5,3,strlen(gstrlineEn5), gstrlineEn5);
		   		    DispEn(0,6,3,strlen(gstrlineEn6), gstrlineEn6);
		   		    DispEn(0,7,3,strlen(gstrlineEn7), gstrlineEn7);
		   		    DispEn(0,8,3,strlen(gstrlineEn8), gstrlineEn8);
		   	    	break ;
				case 6:
			    	DispEn(0,1,1,2,gstrlineEn9);
		   		    DispEn(0,2,1,2,gstrlineEn10);
		   		    DispEn(0,3,1,2,gstrlineEn11);
		   		    DispEn(0,4,1,2,gstrlineEn12);
					DispEn(0,5,1,2,gstrlineEn13);
		   		    DispEn(1,6,1,2,gstrlineEn14);
		   		    DispEn(0,7,1,2,gstrlineEn15);
		   		    DispEn(0,8,1,2,gstrlineEn16);

				    DispEn(0,1,3,strlen(gstrlineEn1), gstrlineEn1);
		   		    DispEn(0,2,3,strlen(gstrlineEn2), gstrlineEn2);
		   		    DispEn(0,3,3,strlen(gstrlineEn3), gstrlineEn3);
		   		    DispEn(0,4,3,strlen(gstrlineEn4), gstrlineEn4);
					DispEn(0,5,3,strlen(gstrlineEn5), gstrlineEn5);
		   		    DispEn(1,6,3,strlen(gstrlineEn6), gstrlineEn6);
		   		    DispEn(0,7,3,strlen(gstrlineEn7), gstrlineEn7);
		   		    DispEn(0,8,3,strlen(gstrlineEn8), gstrlineEn8);
				break;
				case 7:
			    	DispEn(0,1,1,2,gstrlineEn9);
		   		    DispEn(0,2,1,2,gstrlineEn10);
		   		    DispEn(0,3,1,2,gstrlineEn11);
		   		    DispEn(0,4,1,2,gstrlineEn12);
					DispEn(0,5,1,2,gstrlineEn13);
		   		    DispEn(0,6,1,2,gstrlineEn14);
		   		    DispEn(1,7,1,2,gstrlineEn15);
		   		    DispEn(0,8,1,2,gstrlineEn16);

				   DispEn(0,1,3,strlen(gstrlineEn1), gstrlineEn1);
		   		    DispEn(0,2,3,strlen(gstrlineEn2), gstrlineEn2);
		   		    DispEn(0,3,3,strlen(gstrlineEn3), gstrlineEn3);
		   		    DispEn(0,4,3,strlen(gstrlineEn4), gstrlineEn4);
					DispEn(0,5,3,strlen(gstrlineEn5), gstrlineEn5);
		   		    DispEn(0,6,3,strlen(gstrlineEn6), gstrlineEn6);
		   		    DispEn(1,7,3,strlen(gstrlineEn7), gstrlineEn7);
		   		    DispEn(0,8,3,strlen(gstrlineEn8), gstrlineEn8);
				break;
				case 8:
			    	DispEn(0,1,1,2,gstrlineEn9);
		   		    DispEn(0,2,1,2,gstrlineEn10);
		   		    DispEn(0,3,1,2,gstrlineEn11);
		   		    DispEn(0,4,1,2,gstrlineEn12);
					DispEn(0,5,1,2,gstrlineEn13);
		   		    DispEn(0,6,1,2,gstrlineEn14);
		   		    DispEn(0,7,1,2,gstrlineEn15);
		   		    DispEn(1,8,1,2,gstrlineEn16);

				    DispEn(0,1,3,strlen(gstrlineEn1), gstrlineEn1);
		   		    DispEn(0,2,3,strlen(gstrlineEn2), gstrlineEn2);
		   		    DispEn(0,3,3,strlen(gstrlineEn3), gstrlineEn3);
		   		    DispEn(0,4,3,strlen(gstrlineEn4), gstrlineEn4);
					DispEn(0,5,3,strlen(gstrlineEn5), gstrlineEn5);
		   		    DispEn(0,6,3,strlen(gstrlineEn6), gstrlineEn6);
		   		    DispEn(0,7,3,strlen(gstrlineEn7), gstrlineEn7);
		   		    DispEn(1,8,3,strlen(gstrlineEn8), gstrlineEn8);
				break;
				   default:break;
		         }
				}
				else
				{   
				    DispEn(0,1,1,2,gstrlineEn9);
		   		    DispEn(0,2,1,2,gstrlineEn10);
		   		    DispEn(0,3,1,2,gstrlineEn11);
		   		    DispEn(0,4,1,2,gstrlineEn12);
					DispEn(0,5,1,2,gstrlineEn13);
		   		    DispEn(0,6,1,2,gstrlineEn14);
		   		    DispEn(0,7,1,2,gstrlineEn15);
		   		    DispEn(0,8,1,2,gstrlineEn16);

				    DispEn(0,1,1,strlen(gstrlineEn1), gstrlineEn1);
		   		    DispEn(0,2,1,strlen(gstrlineEn2), gstrlineEn2);
		   		    DispEn(0,3,1,strlen(gstrlineEn3), gstrlineEn3);
		   		    DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);
					DispEn(0,5,1,strlen(gstrlineEn5), gstrlineEn5);
		   		    DispEn(0,6,1,strlen(gstrlineEn6), gstrlineEn6);
		   		    DispEn(0,7,1,strlen(gstrlineEn7), gstrlineEn7);
		   		    DispEn(0,8,1,strlen(gstrlineEn8), gstrlineEn8);
				}

			   break;
		
	   	   

			case SYS_F_SELFNUM_SEL:
	  		   
          	    if(((LandTarget.flag!=1)&&(g_mSkyLand==1))||((CustomStar.flag!=1)&&(g_mSkyLand==0)))
				{
					  DispEn(0,1,1,strlen(gstrlineEn1), gstrlineEn1);
					  DispEn(0,2,1,strlen(gstrlineEn2), gstrlineEn2);
					  DispEn(0,3,1,strlen(gstrlineEn3), gstrlineEn3);
					  DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);
					  DispEn(0,5,1,strlen(gstrlineEn5), gstrlineEn5);
					  DispEn(0,6,1,strlen(gstrlineEn6), gstrlineEn6);
					  DispEn(0,7,1,strlen(gstrlineEn7), gstrlineEn7);
					  DispEn(0,8,1,strlen(gstrlineEn8), gstrlineEn8);
				  }
				  else
				  {
				     switch(g_mSkyLand)
				  	{
					  case 0:
						    DispEn(0,1,1,strlen(gstrlineEn1),gstrlineEn1);
							DispEn(0,2,1,strlen(gstrlineEn2),gstrlineEn2);             
				   		    DispEn(0,3,1,strlen(gstrlineEn3), gstrlineEn3);									
				   		    DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4); 
			
			
														  
							DispEn(0,5,1,strlen(gstrlineEn5), gstrlineEn5);						
				   		    DispEn(0,6,8,strlen(gstrlineEn6), gstrlineEn6);
				   		    DispEn(0,7,8,strlen(gstrlineEn7), gstrlineEn7);						
				   		    DispEn(0,8,8,strlen(gstrlineEn8), gstrlineEn8);
							DispCh(0, 5,15,CharD);
			  	            DispCh(0, 5,18,CharM);
							DispCh(0, 5,21,CharS);
							DispCh(0, 6,15,CharD);
			  	            DispCh(0, 6,18,CharM);
			            	DispCh(0, 6,21,CharS);
							DispCh(0, 8,15,CharD);
			  	            DispCh(0, 8,18,CharM);
							DispCh(0, 8,21,CharS);
						break;
					  case 1:  
						    DispEn(0,1,1,strlen(gstrlineEn1),gstrlineEn1);
							DispEn(0,2,1,strlen(gstrlineEn2),gstrlineEn2);             
				   		    DispEn(0,3,1,strlen(gstrlineEn3), gstrlineEn3);									
				   		    DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4); 
			
			
														  
							DispEn(0,5,1,strlen(gstrlineEn5), gstrlineEn5);						
				   		    DispEn(0,6,8,strlen(gstrlineEn6), gstrlineEn6);
				   		    DispEn(0,7,1,strlen(gstrlineEn7), gstrlineEn7);						
				   		    DispEn(0,8,8,strlen(gstrlineEn8), gstrlineEn8);
							DispCh(0, 5,15,CharD);
			  	            DispCh(0, 5,18,CharM);
							DispCh(0, 5,21,CharS);
							DispCh(0, 6,15,CharD);
			  	            DispCh(0, 6,18,CharM);
			            	DispCh(0, 6,21,CharS);

							DispCh(0, 7,15,CharD);
			  	            DispCh(0, 7,18,CharM);
			            	DispCh(0, 7,21,CharS);
							DispCh(0, 8,15,CharD);
			  	            DispCh(0, 8,18,CharM);
							DispCh(0, 8,21,CharS);
						break;
		
					}
				   
   		   	   		 }
		     	break; 
			 

				case SYS_NOTELSCOPE:
			
					 DispEn(0,2,1,strlen(gstrlineEn2), gstrlineEn2);
					 DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);
					 DispEn(0,6,1,strlen(gstrlineEn6), gstrlineEn6);

				     FBeep(1);
					 delay(200);
					 FBeep(1);
					 delay(200);
					 FBeep(1);
					 delay(200);
					 g_nsysstatus =SYS_MAINSHOW;
				break;
				

//				case SYS_SUB1SUB1AUTOSTAR_ALIGN:
//				
//				   
//				    if(!g_nAlignPoint)
//					{
//					  switch(g_nSeledAlignStarNum)
//					  {
//					    case 1:
//						case 2:
//						   if(g_mAlignTelStatus!=1)
//						   {
//						       LCDRfrsh();
//						   }
//						   g_mAlignTelStatus=1;
//						gstrlineEn1=g_sysmenu1103;
//						DispEn(0,1,1,strlen(gstrlineEn1), gstrlineEn1);	
//			   		    DispEn(0,2,1,strlen(gstrlineEn2), gstrlineEn2);
//						DispEn(0,3,1,strlen(gstrlineEn3), gstrlineEn3);		
//			   		    DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);	
//												  
//					   	DispEn(0,5,1,4, "OBJ:");
//														  
//							DispEn(0,7,11,strlen(gstrlineEn5), gstrlineEn5);						
//				   		    DispEn(0,8,11,strlen(gstrlineEn6), gstrlineEn6);
//
//				   		    DispEn(0,5,11,strlen(gstrlineEn7), gstrlineEn7);						
//				   		    DispEn(0,6,11,strlen(gstrlineEn8), gstrlineEn8);
//
//							DispCh(0, 5,18,CharD);
//			  	            DispCh(0, 5,21,CharM);
//
//							DispCh(0, 8,18,CharD);
//			  	            DispCh(0, 8,21,CharM);
//
//							DispCh(0, 6,18,CharD);
//			  	            DispCh(0, 6,21,CharM);
//					     	DispEn(0,6,1,6,"       ");
//						  delay(300);
//
//						if(g_nSeledAlignStarNum==1)
//						{
//						   FTwoStarAutoAlign();
//						}
//					    g_nAlignPoint=true;//��Զ����һ����������У��ʱ�ǵ���ȷ�ϻ���ѡ��falseѡ���ǣ�trueУ������ȷ��
//					   break;
//					   case 3:
//						       if(g_mAlignTelStatus!=2)
//						   {
//						       LCDRfrsh();
//						   }
//						   g_mAlignTelStatus=2;
//							FPointAlignStarOk();
//							FBeep(3);
//							gstrlineEn2=g_sysmenu1107;
//							gstrlineEn4=g_sysmenu1108;
//							gstrlineEn6=g_sysmenu1109;
//						   
//						   	DispEn(0,1,1,22,"                       ");
//							DispEn(0,2,1,strlen(gstrlineEn2), gstrlineEn2);
//							DispEn(0,3,1,22,"                       ");
//							DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);
//							DispEn(0,5,1,22,"                       ");
//							DispEn(0,6,1,strlen(gstrlineEn6), gstrlineEn6);
//							DispEn(0,7,1,22,"                       ");
//							DispEn(0,8,1,22,"                       ");
//						   	delay(300);
//						    g_nsysstatus =SYS_MAINSHOW;
//							
//					   break;
//					   default:
//					   break;
//					  }
//					}
//					else
//					{	
//
//						if(g_mTelStatus==1)
//						{
//						   if(g_mAlignTelStatus!=3)
//						   {
//						       LCDRfrsh();
//						   }
//						   g_mAlignTelStatus=3;
//							    gstrlineEn2=g_sysmenu1102;
//								
//								DispEn(0,1,1,22,"                       ");
//
//								if(g_mGoto.m_nTelGotoPause==0)
//								{
//							      DispEn(0,2,1,21,"Slewing to Target   ");
//								}
//								else
//								{
//								  DispEn(0,2,1,21,"Pause                ");
//								}
//
//                                DispEn(0,3,1,22,"                        ");
//								DispEn(0,4,1,22,"                        ");
//
//								DispEn(0,5,1,4, "OBJ:");
//			             		DispEn(0,5,11,strlen(gstrlineEn7), gstrlineEn7);								
//					   		    DispEn(0,6,11,strlen(gstrlineEn8), gstrlineEn8);
//							    DispCh(0, 5,18,CharD);
//				  	            DispCh(0, 5,21,CharM);
//
//
//								DispCh(0, 6,18,CharD);
//				  	            DispCh(0, 6,21,CharM); 
//
//								DispEn(0,6,1,6, "       ");
//
//								DispEn(0,7,1,4, "OTA:");
//					   		    DispEn(0,7,11,strlen(gstrlineEn5), gstrlineEn5);						
//					   		    DispEn(0,8,11,strlen(gstrlineEn6), gstrlineEn6);
////								switch(g_mAzEq)
////								{
////								case 0:
//									 DispCh(0, 7,18,CharD);
//				  	                 DispCh(0, 7,21,CharM);
////									break;
////								case 1: 
////								   DispEn(0, 7,15,1," ");
////								   DispEn(0, 7,18,1,"h");
////				  	               DispEn(0, 7,21,1,"m");
////									break;
////								default:
////									break;
////								}
//								DispCh(0, 8,18,CharD);
//				  	            DispCh(0, 8,21,CharM); 
//								DispEn(0,6,1,6,"      ");
//							  	 
//				
//						}
//						if(g_mTelStatus==2)
//						{
//						   if(g_mAlignTelStatus!=4)
//						   {
//						       LCDRfrsh();
//						   }
//						   g_mAlignTelStatus=4;
//						    gstrlineEn2=g_sysmenu1104;
//							gstrlineEn4=g_sysmenu1105;
//							gstrlineEn6=g_sysmenu1106;								   
//						   	DispEn(0,1,1,22,"                       ");
//							DispEn(0,2,1,strlen(gstrlineEn2),gstrlineEn2);
//							DispEn(0,3,1,22,"                       ");
//							DispEn(0,4,1,strlen(gstrlineEn4),gstrlineEn4);
//							DispEn(0,5,1,22,"                       ");
//							DispEn(0,6,1,strlen(gstrlineEn6),gstrlineEn6);
//							DispEn(0,7,1,22,"                       ");
//							DispEn(0,8,1,22,"                       ");
//						}
//					}
//				break;
//		        
				case SYS_SUB1SUB2STAR_ALIGN	:  //һ������У׼����ʾ����
			
				   	if(!g_nAlignPoint)
					{
					
						if(g_nAlignStar==0)
						{
						  	 if(g_mAlignTelStatus!=5)
						   {
						       LCDRfrsh();
						   }
						   g_mAlignTelStatus=5;
						    FPointAlignStarOk();
							FBeep(3);
						   	gstrlineEn2=g_sysmenu1107;
							gstrlineEn4=g_sysmenu1108;
							gstrlineEn6=g_sysmenu1109;
		
						   
						   	DispEn(0,1,1,22,"                       ");
							DispEn(0,2,1,strlen(gstrlineEn2),gstrlineEn2);
							DispEn(0,3,1,22,"                       ");
							DispEn(0,4,1,strlen(gstrlineEn4),gstrlineEn4);
							DispEn(0,5,1,22,"                       ");
							DispEn(0,6,1,strlen(gstrlineEn6),gstrlineEn6);
							DispEn(0,7,1,22,"                       ");
							DispEn(0,8,1,22,"                       ");
							delay(300);
						   
						    g_nsysstatus =SYS_MAINSHOW;
						}
						else
						{  
						       if(g_mAlignTelStatus!=6)
						   {
						       LCDRfrsh();
						   }
						   g_mAlignTelStatus=6;
						   	DispEn(0,1,1,strlen(gstrlineEn1),gstrlineEn1);
							DispEn(0,2,1,strlen(gstrlineEn2),gstrlineEn2);             
				   		    DispEn(0,3,1,strlen(gstrlineEn3), gstrlineEn3);  							
				   		    DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);
						
							
							DispEn(0,5,1,4, "OBJ:");
														  
							DispEn(0,7,11,strlen(gstrlineEn7), gstrlineEn7);						
				   		    DispEn(0,8,11,strlen(gstrlineEn8), gstrlineEn8);
				   		    DispEn(0,5,11,strlen(gstrlineEn5), gstrlineEn5);						
				   		    DispEn(0,6,11,strlen(gstrlineEn6), gstrlineEn6);

							DispCh(0, 5,18,CharD);
			  	            DispCh(0, 5,21,CharM);
							DispCh(0, 6,18,CharD);
			  	            DispCh(0, 6,21,CharM);
							DispCh(0, 8,18,CharD);
			  	            DispCh(0, 8,21,CharM);
							DispEn(0,6,1,4,"      ");
						}
					}
					else
					{ 	
						//g_mTelStatus=2;
					    if((g_mTelStatus==1)&&(g_mAlignShow==0))
						{
						    if(g_mAlignTelStatus!=7)
						   {
						       LCDRfrsh();
						   }
						   g_mAlignTelStatus=7;
							    gstrlineEn1=g_sysmenu1102;
								gstrlineEn2=g_sysmenu1103;
								if(g_mGoto.m_nTelGotoPause==0)
								{
							      DispEn(0,1,1,21,"Slewing to Target   ");
								}
								else
								{
								  DispEn(0,1,1,21,"Pause                ");
								}
								//DispEn(0,2,1,strlen(gstrlineEn2),gstrlineEn2);
								DispEn(0,2,1,21,"                     ");
                                DispEn(0,3,1,strlen(gstrlineEn3),gstrlineEn3);
								DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);

							    DispEn(0,5,1,4, "OBJ:");
			                	DispEn(0,5,11,strlen(gstrlineEn5), gstrlineEn5);								
					   		    DispEn(0,6,11,strlen(gstrlineEn6), gstrlineEn6);
							    DispCh(0, 5,18,CharD);
				  	            DispCh(0, 5,21,CharM);

								DispCh(0, 6,18,CharD);
				  	            DispCh(0, 6,21,CharM); 

								DispEn(0,6,1,6, "       ");

								DispEn(0,7,1,4, "OTA:");
					   		    DispEn(0,7,11,strlen(gstrlineEn7), gstrlineEn7);						
					   		    DispEn(0,8,11,strlen(gstrlineEn8), gstrlineEn8);
//								switch(g_mAzEq)
//								{
//								case 0:
									 DispCh(0, 7,18,CharD);
				  	                 DispCh(0, 7,21,CharM);
//									break;
//								case 1: 
//								   DispEn(0, 7,15,1," ");
//								   DispEn(0, 7,18,1,"h");
//				  	               DispEn(0, 7,21,1,"m");
//									break;
//								default:
//									break;
//								}
								DispCh(0, 8,18,CharD);
				  	            DispCh(0, 8,21,CharM); 
								DispEn(0,6,1,4,"    ");
							   
				
						}
						else if(g_mAlignShow==1)
						{
						   if(g_mAlignTelStatus!=8)
						   {
						       LCDRfrsh();
						   }
						    g_mAlignTelStatus=8;
						   	gstrlineEn2=g_sysmenu1104;
							gstrlineEn4=g_sysmenu1105;
							gstrlineEn6=g_sysmenu1106;								   
						   	DispEn(0,1,1,22,"                       ");
							DispEn(0,2,1,strlen(gstrlineEn2),gstrlineEn2);
							DispEn(0,3,1,22,"                       ");
							DispEn(0,4,1,strlen(gstrlineEn4),gstrlineEn4);
							DispEn(0,5,1,22,"                       ");
							DispEn(0,6,1,strlen(gstrlineEn6),gstrlineEn6);
							DispEn(0,7,1,22,"                       ");
							DispEn(0,8,1,22,"                       ");
						  
						}
						if(g_mTelStatus==2)
						{
						   g_mAlignShow=1;
						   if(g_mAlignTelStatus!=8)
						   {
						       LCDRfrsh();
						   }

						    g_mAlignTelStatus=8;
						   	gstrlineEn2=g_sysmenu1104;
							gstrlineEn4=g_sysmenu1105;
							gstrlineEn6=g_sysmenu1106;								   
						   	DispEn(0,1,1,22,"                       ");
							DispEn(0,2,1,strlen(gstrlineEn2),gstrlineEn2);
							DispEn(0,3,1,22,"                       ");
							DispEn(0,4,1,strlen(gstrlineEn4),gstrlineEn4);
							DispEn(0,5,1,22,"                       ");
							DispEn(0,6,1,strlen(gstrlineEn6),gstrlineEn6);
							DispEn(0,7,1,22,"                       ");
							DispEn(0,8,1,22,"                       ");
						}
					}


				 break;

			 //�ྭ�ز�У��
			  case SYS_SUB1SUB11RA_GEAR_ERROR_BEGIN:  
			  case SYS_SUB1SUB11RA_GEAR_ERROR: 
			  case SYS_SUB1SUB11RA_GEAR_ERROR_ALIGN: 		      
                   DispEn(0,1,1,strlen(gstrlineEn1),gstrlineEn1);
				   DispEn(0,2,1,strlen(gstrlineEn2),gstrlineEn2);
                   DispEn(0,3,1,strlen(gstrlineEn3),gstrlineEn3);
				   DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);
				   DispEn(0,5,1,strlen(gstrlineEn5),gstrlineEn5);
				   DispEn(0,6,1,strlen(gstrlineEn6),gstrlineEn6);
                   DispEn(0,7,1,strlen(gstrlineEn7),gstrlineEn7);
				   DispEn(0,8,1,strlen(gstrlineEn8), gstrlineEn8);

			   break;
			   case SYS_SUB1SUB11RA_GEAR_ERROR_ALIGN_OK: 			   		     
				   FBeep(1);	
				   DispEn(0,1,1,strlen(gstrlineEn1),gstrlineEn1);
				   DispEn(0,2,1,strlen(gstrlineEn2),gstrlineEn2);
                   DispEn(0,3,1,strlen(gstrlineEn3),gstrlineEn3);
				   DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);
				   DispEn(0,5,8,strlen(gstrlineEn5),gstrlineEn5);
				   DispEn(0,6,1,strlen(gstrlineEn6),gstrlineEn6);
                   DispEn(0,7,1,strlen(gstrlineEn7),gstrlineEn7);
				   DispEn(0,8,1,strlen(gstrlineEn8), gstrlineEn8);
						
				  delay(800);
				  g_nsysstatus =SYS_SUB1SUB11RA_GEAR_ERROR_BEGIN;
			   break;

			   case SYS_SUB1SUB11RA_GEAR_ERROR_ALIGN_END: 			   		     
				  FBeep(3);	
				   DispEn(0,1,1,strlen(gstrlineEn1),gstrlineEn1);
				   DispEn(0,2,1,strlen(gstrlineEn2),gstrlineEn2);
                   DispEn(0,3,1,strlen(gstrlineEn3),gstrlineEn3);
				   DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);
				   DispEn(0,5,8,strlen(gstrlineEn5),gstrlineEn5);
				   DispEn(0,6,1,strlen(gstrlineEn6),gstrlineEn6);
                   DispEn(0,7,1,strlen(gstrlineEn7),gstrlineEn7);
				   DispEn(0,8,1,strlen(gstrlineEn8), gstrlineEn8);					
				  delay(800);
				  g_nsysstatus =SYS_MAINSHOW;
			   break;


			 //��γ�ز�У��
			  case SYS_SUB1SUB12DEC_GEAR_ERROR_BEGIN:  
			  case SYS_SUB1SUB12DEC_GEAR_ERROR: 
			  case SYS_SUB1SUB12DEC_GEAR_ERROR_ALIGN: 		      
                   DispEn(0,1,1,strlen(gstrlineEn1),gstrlineEn1);
				   DispEn(0,2,1,strlen(gstrlineEn2),gstrlineEn2);
                   DispEn(0,3,1,strlen(gstrlineEn3),gstrlineEn3);
				   DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);
				   DispEn(0,5,1,strlen(gstrlineEn5),gstrlineEn5);
				   DispEn(0,6,1,strlen(gstrlineEn6),gstrlineEn6);
                   DispEn(0,7,1,strlen(gstrlineEn7),gstrlineEn7);
				   DispEn(0,8,1,strlen(gstrlineEn8), gstrlineEn8);

			   break;
			   case SYS_SUB1SUB12DEC_GEAR_ERROR_ALIGN_OK: 			   		     
				  FBeep(1);	
				    DispEn(0,1,1,strlen(gstrlineEn1),gstrlineEn1);
				   DispEn(0,2,1,strlen(gstrlineEn2),gstrlineEn2);
                   DispEn(0,3,1,strlen(gstrlineEn3),gstrlineEn3);
				   DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);
				   DispEn(0,5,8,strlen(gstrlineEn5),gstrlineEn5);
				   DispEn(0,6,1,strlen(gstrlineEn6),gstrlineEn6);
                   DispEn(0,7,1,strlen(gstrlineEn7),gstrlineEn7);
				   DispEn(0,8,1,strlen(gstrlineEn8), gstrlineEn8);
					 						
				  delay(800);
				  g_nsysstatus =SYS_SUB1SUB12DEC_GEAR_ERROR_BEGIN;
			   break;

			   case SYS_SUB1SUB12DEC_GEAR_ERROR_ALIGN_END: 			   		     
				  FBeep(3);	
				   DispEn(0,1,1,strlen(gstrlineEn1),gstrlineEn1);
				   DispEn(0,2,1,strlen(gstrlineEn2),gstrlineEn2);
                   DispEn(0,3,1,strlen(gstrlineEn3),gstrlineEn3);
				   DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);
				   DispEn(0,5,8,strlen(gstrlineEn5),gstrlineEn5);
				   DispEn(0,6,1,strlen(gstrlineEn6),gstrlineEn6);
                   DispEn(0,7,1,strlen(gstrlineEn7),gstrlineEn7);
				   DispEn(0,8,1,strlen(gstrlineEn8), gstrlineEn8);					
				  delay(800);
				  g_nsysstatus =SYS_MAINSHOW;
			   break;		  

				//̫��ϵ����
			   case SYS_SUB2SUN_PLANET:
			   case  SYS_SUB2CON_OBJECT:
			   
			   case  SYS_SUB2MSR_OBJECT:
			  
			
		   //SH2�Ǳ�
		    case  SYS_SUB2SH2_OBJECT:	
			//Bright�Ǳ�
			case  SYS_SUB2BRT_OBJECT:
			 //Sao�Ǳ�
			case  SYS_SUB2SAO_OBJECT:
			    			
			   		   	    DispEn(0,1,1,strlen(gstrlineEn1),gstrlineEn1);
							DispEn(0,2,1,strlen(gstrlineEn2),gstrlineEn2);             
				   		    DispEn(0,3,1,strlen(gstrlineEn3), gstrlineEn3);									
				   		    DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4); 


														  
							DispEn(0,5,1,strlen(gstrlineEn5), gstrlineEn5);						
				   		    DispEn(0,6,8,strlen(gstrlineEn6), gstrlineEn6);
				   		    DispEn(0,7,8,strlen(gstrlineEn7), gstrlineEn7);						
				   		    DispEn(0,8,8,strlen(gstrlineEn8), gstrlineEn8);
							DispCh(0, 5,15,CharD);
			  	            DispCh(0, 5,18,CharM);
							DispCh(0, 5,21,CharS);
							DispCh(0, 6,15,CharD);
			  	            DispCh(0, 6,18,CharM);
                        	DispCh(0, 6,21,CharS);
							DispCh(0, 8,15,CharD);
			  	            DispCh(0, 8,18,CharM);
							DispCh(0, 8,21,CharS);

			   break;

			 //NGC�Ǳ�
			case  SYS_SUB2NGC_OBJECT:
		   //IC�Ǳ�	
		   	case  SYS_SUB2IC_OBJECT:
				   	       
			   		   	    DispEn(0,1,1,strlen(gstrlineEn1),gstrlineEn1);
							DispEn(0,2,1,14,"Constellation:");   
							DispEn(0,2,15,strlen(gstrlineEn2),gstrlineEn2);             
				   		    DispEn(0,3,1,strlen(gstrlineEn3), gstrlineEn3);	
							DispEn(0,4,1,5,"Type:"); 								
				   		    DispEn(0,4,6,strlen(gstrlineEn4), gstrlineEn4); 


														  
							DispEn(0,5,1,strlen(gstrlineEn5), gstrlineEn5);						
				   		    DispEn(0,6,8,strlen(gstrlineEn6), gstrlineEn6);
				   		    DispEn(0,7,8,strlen(gstrlineEn7), gstrlineEn7);						
				   		    DispEn(0,8,8,strlen(gstrlineEn8), gstrlineEn8);
							DispCh(0, 5,15,CharD);
			  	            DispCh(0, 5,18,CharM);
							DispCh(0, 5,21,CharS);
							DispCh(0, 6,15,CharD);
			  	            DispCh(0, 6,18,CharM);
                        	DispCh(0, 6,21,CharS);
							DispCh(0, 8,15,CharD);
			  	            DispCh(0, 8,18,CharM);
							DispCh(0, 8,21,CharS);
			 break;

			   case  SYS_SUB2SUN_PLANET1:
			   case  SYS_SUB2CON_OBJECT1:
			   case  SYS_SUB2FS_OBJECT1: 			   
			   case  SYS_SUB2MSR_OBJECT1:
		     
		       case  SYS_SUB2SH2_OBJECT1:	
			   case  SYS_SUB2BRT_OBJECT1:
			   case  SYS_SUB2SAO_OBJECT1:
			   	           
			   		   	    DispEn(0,1,1,strlen(gstrlineEn1),gstrlineEn1);
							DispEn(0,2,1,strlen(gstrlineEn2),gstrlineEn2);             
				   		    DispEn(0,3,1,strlen(gstrlineEn3), gstrlineEn3);									
				   		    DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4); 


														  
							DispEn(0,5,1,strlen(gstrlineEn5), gstrlineEn5);						
				   		    DispEn(0,6,8,strlen(gstrlineEn6), gstrlineEn6);
				   		    DispEn(0,7,1,strlen(gstrlineEn7), gstrlineEn7);						
				   		    DispEn(0,8,8,strlen(gstrlineEn8), gstrlineEn8);
							DispCh(0, 5,15,CharD);
			  	            DispCh(0, 5,18,CharM);
							DispCh(0, 5,21,CharS);
							DispCh(0, 6,15,CharD);
			  	            DispCh(0, 6,18,CharM);
                        	DispCh(0, 6,21,CharS);
						   //if(g_mAzEq==0)
						   //{
							 DispCh(0, 7,15,CharD);
			  	             DispCh(0, 7,18,CharM);
							 DispCh(0, 7,21,CharS);
							//}
//							else
//							{
//							   DispEn(0, 7,15,1,"h");
//			  	               DispEn(0, 7,18,1,"m");
//							   DispEn(0, 7,21,1,"s");
//							}

							
							DispCh(0, 8,15,CharD);
			  	            DispCh(0, 8,18,CharM);
							DispCh(0, 8,21,CharS);
//							if(g_mAzEq==1)
//							{
//							  DispEn(0, 7,8,3,"H.a");
//			  	              DispEn(0, 8,8,3,"Dec");
//							  }
						if(g_mOperateStatus==2)
						{
						    MenuDelay(2000);
						    FBeep(1); 
							MenuDelay(1000);
							FBeep(1); 
							MenuDelay(1000);							  
						    g_nsysstatus=SYS_MAINSHOW;					  			   
						}

			   break;
			   case  SYS_SUB2NGC_OBJECT1:
			   case  SYS_SUB2IC_OBJECT1:
			 
				            LCDRfrsh();
			   		   	    DispEn(0,1,1,strlen(gstrlineEn1),gstrlineEn1);
							DispEn(0,2,1,strlen(gstrlineEn2),gstrlineEn2);  
							DispEn(0,3,1,14,"Constellation:");           
				   		    DispEn(0,3,15,strlen(gstrlineEn3), gstrlineEn3);									
				   		    DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4); 


														  
							DispEn(0,5,1,strlen(gstrlineEn5), gstrlineEn5);						
				   		    DispEn(0,6,8,strlen(gstrlineEn6), gstrlineEn6);
				   		    DispEn(0,7,1,strlen(gstrlineEn7), gstrlineEn7);						
				   		    DispEn(0,8,8,strlen(gstrlineEn8), gstrlineEn8);
							DispCh(0, 5,15,CharD);
			  	            DispCh(0, 5,18,CharM);
							DispCh(0, 5,21,CharS);
							DispCh(0, 6,15,CharD);
			  	            DispCh(0, 6,18,CharM);
                        	DispCh(0, 6,21,CharS);
							//if(g_mAzEq==0)
							//{
							DispCh(0, 7,15,CharD);
			  	            DispCh(0, 7,18,CharM);
							DispCh(0, 7,21,CharS);
//							}
//							else
//							{
//							   DispEn(0, 7,15,1,"h");
//			  	               DispEn(0, 7,18,1,"m");
//							   DispEn(0, 7,21,1,"s");
//							}
							DispCh(0, 8,15,CharD);
			  	            DispCh(0, 8,18,CharM);
							DispCh(0, 8,21,CharS);
//							if(g_mAzEq==1)
//							{
//							  DispEn(0, 7,8,3,"H.a");
//			  	              DispEn(0, 8,8,3,"Dec");
//							 }
				    	if(g_mOperateStatus==2)
						{
						    MenuDelay(2000);
						    FBeep(1); 
							MenuDelay(1000);
							FBeep(1); 
							MenuDelay(1000);							  
						    g_nsysstatus=SYS_MAINSHOW;					  			   
						}

			 break;

		
			   //��������
			  case  SYS_SUB2FS_OBJECT:
			    			
			   		   	    DispUn(0,1,1,64,(uint16*)gstrlineEn1);
							//DispEn(0,2,1,strlen(gstrlineEn2),gstrlineEn2);             
				   		    DispEn(0,3,0,strlen(gstrlineEn3), gstrlineEn3);									
				   		    DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4); 


														  
							DispEn(0,5,1,strlen(gstrlineEn5), gstrlineEn5);						
				   		    DispEn(0,6,8,strlen(gstrlineEn6), gstrlineEn6);
				   		    DispEn(0,7,8,strlen(gstrlineEn7), gstrlineEn7);						
				   		    DispEn(0,8,8,strlen(gstrlineEn8), gstrlineEn8);
							DispCh(0, 5,15,CharD);
			  	            DispCh(0, 5,18,CharM);
							DispCh(0, 5,21,CharS);
							DispCh(0, 6,15,CharD);
			  	            DispCh(0, 6,18,CharM);
                        	DispCh(0, 6,21,CharS);
							DispCh(0, 8,15,CharD);
			  	            DispCh(0, 8,18,CharM);
							DispCh(0, 8,21,CharS);

			   break;

			  case  SYS_SUB2MSR_OBJECT0:
			  		
			   		   	    DispEn(0,1,1,strlen(gstrlineEn1),gstrlineEn1);
							DispEn(0,2,1,strlen(gstrlineEn2),gstrlineEn2);             
				   		    DispEn(0,3,1,strlen(gstrlineEn3), gstrlineEn3);									
				   		    DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4); 														  
							DispEn(0,5,1,strlen(gstrlineEn5), gstrlineEn5);						
				   		    DispEn(0,6,1,strlen(gstrlineEn6), gstrlineEn6);
				   		    DispEn(0,7,1,strlen(gstrlineEn7), gstrlineEn7);						
				   		    DispEn(0,8,1,strlen(gstrlineEn8), gstrlineEn8);
					break;
	
	
			   				
				case  SYS_MENU_SKY_OBJECT: 
				case  SYS_MENU_LAND_OBJECT: 
				case  SYS_F_SELFNUM :
			
				    DispEn(0,1,1,strlen(gstrlineEn10), gstrlineEn10);
					
					switch(g_mFnum)
					{
					   case 1:
					    DispEn(1,3,3,2,gstrlineEn1);
						DispEn(0,3,10,2,gstrlineEn2);
						DispEn(0,3,17,2,gstrlineEn3);
						DispEn(0,5,3,2,gstrlineEn4);
						DispEn(0,5,10,2,gstrlineEn5);
						DispEn(0,5,17,2,gstrlineEn6);
			         	DispEn(0,7,3,2,gstrlineEn7);
						DispEn(0,7,10,2,gstrlineEn8);
						DispEn(0,7,17,2,gstrlineEn9);
						break;
					    case 2:
					    DispEn(0,3,3,2,gstrlineEn1);
						DispEn(1,3,10,2,gstrlineEn2);
						DispEn(0,3,17,2,gstrlineEn3);
						DispEn(0,5,3,2,gstrlineEn4);
						DispEn(0,5,10,2,gstrlineEn5);
						DispEn(0,5,17,2,gstrlineEn6);
			         	DispEn(0,7,3,2,gstrlineEn7);
						DispEn(0,7,10,2,gstrlineEn8);
						DispEn(0,7,17,2,gstrlineEn9);
						break;
						 case 3:
					    DispEn(0,3,3,2,gstrlineEn1);
						DispEn(0,3,10,2,gstrlineEn2);
						DispEn(1,3,17,2,gstrlineEn3);
						DispEn(0,5,3,2,gstrlineEn4);
						DispEn(0,5,10,2,gstrlineEn5);
						DispEn(0,5,17,2,gstrlineEn6);
			         	DispEn(0,7,3,2,gstrlineEn7);
						DispEn(0,7,10,2,gstrlineEn8);
						DispEn(0,7,17,2,gstrlineEn9);
						break;
						 case 4:
					    DispEn(0,3,3,2,gstrlineEn1);
						DispEn(0,3,10,2,gstrlineEn2);
						DispEn(0,3,17,2,gstrlineEn3);
						DispEn(1,5,3,2,gstrlineEn4);
						DispEn(0,5,10,2,gstrlineEn5);
						DispEn(0,5,17,2,gstrlineEn6);
			         	DispEn(0,7,3,2,gstrlineEn7);
						DispEn(0,7,10,2,gstrlineEn8);
						DispEn(0,7,17,2,gstrlineEn9);
						break;
						 case 5:
					    DispEn(0,3,3,2,gstrlineEn1);
						DispEn(0,3,10,2,gstrlineEn2);
						DispEn(0,3,17,2,gstrlineEn3);
						DispEn(0,5,3,2,gstrlineEn4);
						DispEn(1,5,10,2,gstrlineEn5);
						DispEn(0,5,17,2,gstrlineEn6);
			         	DispEn(0,7,3,2,gstrlineEn7);
						DispEn(0,7,10,2,gstrlineEn8);
						DispEn(0,7,17,2,gstrlineEn9);
						break;
						 case 6:
					    DispEn(0,3,3,2,gstrlineEn1);
						DispEn(0,3,10,2,gstrlineEn2);
						DispEn(0,3,17,2,gstrlineEn3);
						DispEn(0,5,3,2,gstrlineEn4);
						DispEn(0,5,10,2,gstrlineEn5);
						DispEn(1,5,17,2,gstrlineEn6);
			         	DispEn(0,7,3,2,gstrlineEn7);
						DispEn(0,7,10,2,gstrlineEn8);
						DispEn(0,7,17,2,gstrlineEn9);
						break;
						 case 7:
					    DispEn(0,3,3,2,gstrlineEn1);
						DispEn(0,3,10,2,gstrlineEn2);
						DispEn(0,3,17,2,gstrlineEn3);
						DispEn(0,5,3,2,gstrlineEn4);
						DispEn(0,5,10,2,gstrlineEn5);
						DispEn(0,5,17,2,gstrlineEn6);
			         	DispEn(1,7,3,2,gstrlineEn7);
						DispEn(0,7,10,2,gstrlineEn8);
						DispEn(0,7,17,2,gstrlineEn9);
						break;
						 case 8:
					    DispEn(0,3,3,2,gstrlineEn1);
						DispEn(0,3,10,2,gstrlineEn2);
						DispEn(0,3,17,2,gstrlineEn3);
						DispEn(0,5,3,2,gstrlineEn4);
						DispEn(0,5,10,2,gstrlineEn5);
						DispEn(0,5,17,2,gstrlineEn6);
			         	DispEn(0,7,3,2,gstrlineEn7);
						DispEn(1,7,10,2,gstrlineEn8);
						DispEn(0,7,17,2,gstrlineEn9);
						break;
						 case 9:
					    DispEn(0,3,3,2,gstrlineEn1);
						DispEn(0,3,10,2,gstrlineEn2);
						DispEn(0,3,17,2,gstrlineEn3);
						DispEn(0,5,3,2,gstrlineEn4);
						DispEn(0,5,10,2,gstrlineEn5);
						DispEn(0,5,17,2,gstrlineEn6);
			         	DispEn(0,7,3,2,gstrlineEn7);
						DispEn(0,7,10,2,gstrlineEn8);
						DispEn(1,7,17,2,gstrlineEn9);
						break;

					}

				break;
				

			
	

			   	 case SYS_MENU_SKY_NAME:
		  	        DispCh(0, 8,8,CharD);
					DispCh(0, 8,11,CharM);
					DispCh(0, 8,16,CharS);


			  	    DispEn(0,1,1,strlen(gstrlineEn1), gstrlineEn1);	//��ʾ�ྭ����
		   		    DispEn(0,2,1,strlen(gstrlineEn2), gstrlineEn2);
					DispEn(0,3,1,strlen(gstrlineEn3), gstrlineEn3);
					DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);
					DispEn(0,5,1,strlen(gstrlineEn5), gstrlineEn5);
					DispEn(0,6,1,13, gstrlineEn6);
		   		    DispEn(0,7,1,16, gstrlineEn7);
					DispEn(0,8,1,16, gstrlineEn8);	//��ʾ�ྭ����	

					DispEn(1,6,g_mShowMenucolumn,1,&gstrlineEn6[g_mShowMenucolumn-1]);//��ǰҪ��������ַ��ӱ���
				    DispCh(0, 8,8,CharD);
					DispCh(0, 8,11,CharM);
					DispCh(0, 8,16,CharS);

			        break;

					 
			 	case SYS_MENU_SKY_RA:
		  	        DispCh(0, 8,8,CharD);
					DispCh(0, 8,11,CharM);
					DispCh(0, 8,16,CharS);

			  	    DispEn(0,1,1,strlen(gstrlineEn1), gstrlineEn1);	//��ʾ�ྭ����
		   		    DispEn(0,2,1,strlen(gstrlineEn2), gstrlineEn2);
					DispEn(0,3,1,strlen(gstrlineEn3), gstrlineEn3);
					DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);
					DispEn(0,5,1,strlen(gstrlineEn5), gstrlineEn5);
					DispEn(0,6,1,13, gstrlineEn6);
		   		    DispEn(0,7,1,16, gstrlineEn7);
					DispEn(0,8,1,16, gstrlineEn8);	//��ʾ�ྭ����	

					DispEn(1,7,g_mShowMenucolumn,1,&gstrlineEn7[g_mShowMenucolumn-1]);//��ǰҪ��������ַ��ӱ���
				    DispCh(0, 8,8,CharD);
					DispCh(0, 8,11,CharM);
					DispCh(0, 8,16,CharS);

			        break;
			  	case SYS_MENU_SKY_DEC:
		            DispCh(0, 8,8,CharD);
					DispCh(0, 8,11,CharM);
					DispCh(0, 8,16,CharS);

			  	    DispEn(0,1,1,strlen(gstrlineEn1), gstrlineEn1);	//��ʾ�ྭ����
		   		    DispEn(0,2,1,strlen(gstrlineEn2), gstrlineEn2);
					DispEn(0,3,1,strlen(gstrlineEn3), gstrlineEn3);
					DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);
					DispEn(0,5,1,strlen(gstrlineEn5), gstrlineEn5);
					DispEn(0,6,1,13, gstrlineEn6);
		   		    DispEn(0,7,1,16, gstrlineEn7);
					DispEn(0,8,1,16, gstrlineEn8);	//��ʾ�ྭ����	

					DispEn(1,8,g_mShowMenucolumn,1,&gstrlineEn8[g_mShowMenucolumn-1]);//��ǰҪ��������ַ��ӱ���
				    DispCh(0, 8,8,CharD);
					DispCh(0, 8,11,CharM);
					DispCh(0, 8,16,CharS);

			        break;
							
			   	  case SYS_MENU_LAND_NAME:
				    DispCh(0, 8,8,CharD);
					DispCh(0, 8,11,CharM);
					DispCh(0, 8,16,CharS);
				    DispCh(0, 7,8,CharD);
					DispCh(0, 7,11,CharM);
					DispCh(0, 7,16,CharS);

			  	    DispEn(0,1,1,strlen(gstrlineEn1), gstrlineEn1);	//��ʾ�ྭ����
		   		    DispEn(0,2,1,strlen(gstrlineEn2), gstrlineEn2);
					DispEn(0,3,1,strlen(gstrlineEn3), gstrlineEn3);
					DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);
					DispEn(0,5,1,strlen(gstrlineEn5), gstrlineEn5);
					DispEn(0,6,1,13, gstrlineEn6);
		   		    DispEn(0,7,1,16, gstrlineEn7);
					DispEn(0,8,1,16, gstrlineEn8);	//��ʾ�ྭ����	

					DispEn(0,7,1,3, "Azi");
					DispEn(0,8,1,3, "Alt");	//��ʾ�ྭ����	

					DispEn(1,6,g_mShowMenucolumn,1,&gstrlineEn6[g_mShowMenucolumn-1]);//��ǰҪ��������ַ��ӱ���
				    DispCh(0, 8,8,CharD);
					DispCh(0, 8,11,CharM);
					DispCh(0, 8,16,CharS);
					DispCh(0, 7,8,CharD);
					DispCh(0, 7,11,CharM);
					DispCh(0, 7,16,CharS);

			        break;
				case SYS_MENU_LAND_AZI:	
				 DispCh(0, 8,8,CharD);
					DispCh(0, 8,11,CharM);
					DispCh(0, 8,16,CharS);
					DispCh(0, 7,8,CharD);
					DispCh(0, 7,11,CharM);
					DispCh(0, 7,16,CharS);

			  	    DispEn(0,1,1,strlen(gstrlineEn1), gstrlineEn1);	//��ʾ�ྭ����
		   		    DispEn(0,2,1,strlen(gstrlineEn2), gstrlineEn2);
					DispEn(0,3,1,strlen(gstrlineEn3), gstrlineEn3);
					DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);
					DispEn(0,5,1,strlen(gstrlineEn5), gstrlineEn5);
					DispEn(0,6,1,13, gstrlineEn6);
		   		    DispEn(0,7,1,16, gstrlineEn7);
					DispEn(0,8,1,16, gstrlineEn8);	//��ʾ�ྭ����
					
					DispEn(0,7,1,3, "Azi");
					DispEn(0,8,1,3, "Alt");	//��ʾ�ྭ����	

					DispEn(1,7,g_mShowMenucolumn,1,&gstrlineEn7[g_mShowMenucolumn-1]);//��ǰҪ��������ַ��ӱ���
				    DispCh(0, 8,8,CharD);
					DispCh(0, 8,11,CharM);
					DispCh(0, 8,16,CharS);
					DispCh(0, 7,8,CharD);
					DispCh(0, 7,11,CharM);
					DispCh(0, 7,16,CharS);

			        break;	
				case SYS_MENU_LAND_ALT:
				    DispCh(0, 8,8,CharD);
					DispCh(0, 8,11,CharM);
					DispCh(0, 8,16,CharS);
					DispCh(0, 7,8,CharD);
					DispCh(0, 7,11,CharM);
					DispCh(0, 7,16,CharS);

			  	    DispEn(0,1,1,strlen(gstrlineEn1), gstrlineEn1);	//��ʾ�ྭ����
		   		    DispEn(0,2,1,strlen(gstrlineEn2), gstrlineEn2);
					DispEn(0,3,1,strlen(gstrlineEn3), gstrlineEn3);
					DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);
					DispEn(0,5,1,strlen(gstrlineEn5), gstrlineEn5);
					DispEn(0,6,1,13, gstrlineEn6);
		   		    DispEn(0,7,1,16, gstrlineEn7);
					DispEn(0,8,1,16, gstrlineEn8);	//��ʾ�ྭ����
						
				
				   	 DispEn(0,7,1,3, "Azi");
					 DispEn(0,8,1,3, "Alt");	//��ʾ�ྭ����


					DispEn(1,8,g_mShowMenucolumn,1,&gstrlineEn8[g_mShowMenucolumn-1]);//��ǰҪ��������ַ��ӱ���
				    DispCh(0, 8,8,CharD);
					DispCh(0, 8,11,CharM);
					DispCh(0, 8,16,CharS);
					DispCh(0, 7,8,CharD);
					DispCh(0, 7,11,CharM);
					DispCh(0, 7,16,CharS);

			        break;

	
							    
		
		
		      //ϵͳ�ྭ��γ������ʾ
			  case 	SYS_SUB2SUB9RA:
		  	        DispCh(0, 5,8,CharD);
					DispCh(0, 5,11,CharM);
					DispCh(0, 5,16,CharS);

			  	    DispEn(0,1,1,strlen(gstrlineEn1), gstrlineEn1);	//��ʾ�ྭ����
		   		    DispEn(0,2,1,strlen(gstrlineEn2), gstrlineEn2);
		   		    DispEn(0,3,1,16, gstrlineEn3);
		   	    	DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);
					DispEn(0,5,1,16, gstrlineEn5);	//��ʾ�ྭ����
		   		    DispEn(0,6,1,strlen(gstrlineEn6), gstrlineEn6);
		   		    DispEn(0,7,1,strlen(gstrlineEn7), gstrlineEn7);
		   	    	DispEn(0,8,1,strlen(gstrlineEn8), gstrlineEn8);		

					DispEn(1,3,g_mShowMenucolumn,1,&gstrlineEn3[g_mShowMenucolumn-1]);//��ǰҪ��������ַ��ӱ���
				    DispCh(0, 5,8,CharD);
					DispCh(0, 5,11,CharM);
					DispCh(0, 5,16,CharS);

			        break;
			  case SYS_SUB2SUB9DEC:
		            DispCh(0, 5,8,CharD);
					DispCh(0, 5,11,CharM);
					DispCh(0, 5,16,CharS);

				  	DispEn(0,1,1,strlen(gstrlineEn1), gstrlineEn1);	//��ʾ�ྭ����
		   		    DispEn(0,2,1,strlen(gstrlineEn2), gstrlineEn2);
		   		    DispEn(0,3,1,16, gstrlineEn3);
		   	    	DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);
					DispEn(0,5,1,16, gstrlineEn5);	//��ʾ�ྭ����
		   		    DispEn(0,6,1,strlen(gstrlineEn6), gstrlineEn6);
		   		    DispEn(0,7,1,strlen(gstrlineEn7), gstrlineEn7);
		   	    	DispEn(0,8,1,strlen(gstrlineEn8), gstrlineEn8);		


					DispEn(1,5,g_mShowMenucolumn,1,&gstrlineEn5[g_mShowMenucolumn-1]);//��ǰҪ��������ַ��ӱ���
				    DispCh(0, 5,8,CharD);
					DispCh(0, 5,11,CharM);
					DispCh(0, 5,16,CharS);

			        break;

				//�Զ����ٶ�������ʾ����
			 case SYS_SUB4SUB8MENU4_RASPEED:
			       	DispEn(0,1,1,strlen(gstrlineEn1), gstrlineEn1);	//��ʾ�ྭ����
		   		    DispEn(0,2,1,strlen(gstrlineEn2), gstrlineEn2);
		   		    DispEn(0,3,1,strlen(gstrlineEn3), gstrlineEn3);
		   	    	DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);
					DispEn(0,5,1,strlen(gstrlineEn5), gstrlineEn5);
		   		    DispEn(0,6,1,strlen(gstrlineEn6), gstrlineEn6);
		   		    DispEn(0,7,1,strlen(gstrlineEn7), gstrlineEn7);
		   	    	DispEn(0,8,1,strlen(gstrlineEn8), gstrlineEn8);		
					DispEn(1,4,g_mShowMenucolumn,1,&gstrlineEn4[g_mShowMenucolumn-1]);//��ǰҪ��������ַ��ӱ���
	               break ;

			 //ʱ������
	          case  SYS_SUB4SUB1_SETTIME:
			        switch(	g_mdatetime)
					{
					  case 0://��������
				       	DispEn(0,1,1,strlen(gstrlineEn1), gstrlineEn1);	//��ʾ�ྭ����
			   		    DispEn(0,2,1,strlen(gstrlineEn2), gstrlineEn2);
			   		    DispEn(0,3,1,strlen(gstrlineEn3), gstrlineEn3);
			   	    	DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);
						DispEn(0,5,1,strlen(gstrlineEn5), gstrlineEn5);
			   		    DispEn(0,6,1,strlen(gstrlineEn6), gstrlineEn6);
			   		    DispEn(0,7,1,strlen(gstrlineEn7), gstrlineEn7);
			   	    	DispEn(0,8,1,strlen(gstrlineEn8), gstrlineEn8);		
						DispEn(1,3,g_mShowMenucolumn,1,&gstrlineEn3[g_mShowMenucolumn-1]);//��ǰҪ��������ַ��ӱ���
		          	   break;
					   case 1://ʱ������
					   	DispEn(0,1,1,strlen(gstrlineEn1), gstrlineEn1);	//��ʾ�ྭ����
			   		    DispEn(0,2,1,strlen(gstrlineEn2), gstrlineEn2);
			   		    DispEn(0,3,1,strlen(gstrlineEn3), gstrlineEn3);
			   	    	DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);
						DispEn(0,5,1,strlen(gstrlineEn5), gstrlineEn5);
			   		    DispEn(0,6,1,strlen(gstrlineEn6), gstrlineEn6);
			   		    DispEn(0,7,1,strlen(gstrlineEn7), gstrlineEn7);
			   	    	DispEn(0,8,1,strlen(gstrlineEn8), gstrlineEn8);		
						DispEn(1,5,g_mShowMenucolumn,1,&gstrlineEn5[g_mShowMenucolumn-1]);//��ǰҪ��������ַ��ӱ���
		     	   break;
					   default:
					   break;
					 }
			 break;
			 //���ʳ���
			 case SYS_SUB4SUB3SUN1_CITYSEL:
			    
   		   	    DispEn(0,1,1,strlen(gstrlineEn1),gstrlineEn1);
				DispEn(0,2,1,strlen(gstrlineEn2),gstrlineEn2);             
	   		    DispEn(0,3,1,strlen(gstrlineEn3), gstrlineEn3);									
	   		    DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4); 														  
				DispEn(0,5,1,strlen(gstrlineEn5), gstrlineEn5);						
	   		    DispEn(0,6,1,strlen(gstrlineEn6), gstrlineEn6);
	   		    DispEn(0,7,1,strlen(gstrlineEn7), gstrlineEn7);						
	   		    DispEn(0,8,1,strlen(gstrlineEn8), gstrlineEn8);
				DispCh(0, 3,14,CharD);
				DispCh(0, 3,17,CharM);
				DispCh(0, 4,14,CharD);
				DispCh(0, 4,17,CharM);
             break;
			//�Զ���ص����
	        case SYS_SUB4SUB3_SETSITE : 
			    DispCh(0, 4,11,CharD);
				DispCh(0, 4,14,CharM);
				DispCh(0, 5,10,CharD);
				DispCh(0, 5,13,CharM);
		            DispEn(0,1,1,strlen(gstrlineEn1), gstrlineEn1);
		   		    DispEn(0,2,1,strlen(gstrlineEn2), gstrlineEn2);
		   		    DispEn(0,3,1,strlen(gstrlineEn3), gstrlineEn3);
		   	    	DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);
					DispEn(0,5,1,strlen(gstrlineEn5), gstrlineEn5);
		   		    DispEn(0,6,1,strlen(gstrlineEn6), gstrlineEn6);
		   		    DispEn(0,7,1,strlen(gstrlineEn7), gstrlineEn7);
		   	    	DispEn(0,8,1,strlen(gstrlineEn8), gstrlineEn8);
			
					   	switch(g_mMySiteShowMode)
						{
						  case 0:
						  	DispEn(1,3,g_mShowMenucolumn,1,&gstrlineEn3[g_mShowMenucolumn-1]);
						  	break;
						  case 1:
						  	DispEn(1,4,g_mShowMenucolumn,1,&gstrlineEn4[g_mShowMenucolumn-1]);
						  	break;
						  case 2:
						    DispEn(1,5,g_mShowMenucolumn,1,&gstrlineEn5[g_mShowMenucolumn-1]);
						  	break;
						  case 3:
						    DispEn(1,6,g_mShowMenucolumn,1,&gstrlineEn6[g_mShowMenucolumn-1]);
						  	break;
					
						}
			    DispCh(0, 4,11,CharD);
				DispCh(0, 4,14,CharM);
				DispCh(0, 5,10,CharD);
				DispCh(0, 5,13,CharM);
					 break ; 
//				//�����Ӳ˵���ʾ����
//		   	case SYS_SUB4SUB4WEATHER:	
//			        DispEn(0,1,1,strlen(gstrlineEn1), gstrlineEn1);
//		   		    DispEn(0,2,1,strlen(gstrlineEn2), gstrlineEn2);
//		   		    DispEn(0,3,1,strlen(gstrlineEn3), gstrlineEn3);
//		   	    	DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);
//					DispEn(0,5,1,strlen(gstrlineEn5), gstrlineEn5);
//					DispEn(0,6,1,strlen(gstrlineEn7), gstrlineEn6);
//					DispEn(0,7,1,strlen(gstrlineEn7), gstrlineEn7);
//					DispEn(0,8,1,strlen(gstrlineEn8), gstrlineEn8);
//				 	switch(g_mWeatherShowMode)
//						{
//						  case 0:
//						   DispEn(1,1,g_mShowMenucolumn,1,&gstrlineEn1[g_mShowMenucolumn-1]);
//						  break;
//						  case 1:
//						  DispEn(1,3,g_mShowMenucolumn,1,&gstrlineEn3[g_mShowMenucolumn-1]);
//						  break;
//						  case 2:
//						    DispEn(1,5,g_mShowMenucolumn,1,&gstrlineEn5[g_mShowMenucolumn-1]);
//						  break;	
//						  default:
//						  break;
//						}
//
//			    break;


		   //��Զ�������ʾ����
		    case SYS_SUB4SUB7_TELZERO_OK:
		   	case SYS_SUB4SUB7_TELAZIALT_ZERO:	
			        DispEn(0,1,1,strlen(gstrlineEn1), gstrlineEn1);
		   		    DispEn(0,2,1,strlen(gstrlineEn2), gstrlineEn2);
		   		    DispEn(0,3,1,8, gstrlineEn3);
		   	    	DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);


					DispEn(0,5,1,8, gstrlineEn5);
					DispEn(0,6,1,strlen(gstrlineEn7), gstrlineEn6);
					DispEn(0,7,1,strlen(gstrlineEn7), gstrlineEn7);
					DispEn(0,8,1,strlen(gstrlineEn8), gstrlineEn8);
				 	switch(g_mTelZeroShowMode)
						{
						  case 0:
						   DispEn(1,3,g_mShowMenucolumn,1,&gstrlineEn3[g_mShowMenucolumn-1]);
						  break;
						  case 1:
						   DispEn(1,5,g_mShowMenucolumn,1,&gstrlineEn5[g_mShowMenucolumn-1]);
						  break;
						  default:
						  break;
						}
					DispCh(0, 3,8,CharD);
					DispCh(0, 5,8,CharD);

			    break;

			case SYS_RESET:	//�˳��ָ�����״̬ 

			    DispEn(0,1,1,21, "Are you sure reset   ");
				DispEn(0,3,1,21, "System.                ");
				DispEn(0,5,1,21, "Back: Cancel          ");
				DispEn(0,7,1,21, "Enter: Begin Reset      ");

		     break;




		//������ʾ����
		   	case SYS_SUB3SUB3_MOONPHASE	:			  
		        dispMoonphase(g_mMoonPhaseYear,g_mMoonPhaseMonth);
			    break;



//********************************************************************

//����ʱ�趨��ʱ״̬��ʾ
		case SYS_SUB3SUB4TIMER_INPUT:
	  	    DispEn(0,1,1,strlen(gstrlineEn1), gstrlineEn1);	
   		    DispEn(0,2,1,strlen(gstrlineEn2), gstrlineEn2);
   		    DispEn(0,3,1,strlen(gstrlineEn3), gstrlineEn3);
   	    	DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);	
			DispEn(0,5,1,strlen(gstrlineEn5), gstrlineEn5);
			DispEn(0,6,1,strlen(gstrlineEn7), gstrlineEn6);
			DispEn(0,7,1,strlen(gstrlineEn7), gstrlineEn7);
			DispEn(0,8,1,strlen(gstrlineEn8), gstrlineEn8);
			DispEn(1,3,g_mShowMenucolumn,1,&gstrlineEn3[g_mShowMenucolumn-1]);//��ǰҪ��������ַ��ӱ���
	        break;
	//������ʾ
	  case 	SYS_SUB3SUB5ALARM_INPUT:
	  	    DispEn(0,1,1,strlen(gstrlineEn1), gstrlineEn1);
   	    	DispEn(0,2,1,strlen(gstrlineEn2), gstrlineEn2);
   		    DispEn(0,3,1,strlen(gstrlineEn3), gstrlineEn3);
   		    DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);
			DispEn(0,5,1,strlen(gstrlineEn5), gstrlineEn5);
   	    	DispEn(0,6,1,strlen(gstrlineEn6), gstrlineEn6);
   		    DispEn(0,7,1,strlen(gstrlineEn7), gstrlineEn7);
   		    DispEn(0,8,1,strlen(gstrlineEn8), gstrlineEn8);
			DispEn(1,3,g_mShowMenucolumn,1,&gstrlineEn3[g_mShowMenucolumn-1]);//��ǰҪ��������ַ��ӱ���
	        break;

	//���ʼ��㣺
   	case SYS_SUB3SUB6SUB2M_MF:	
        	DispEn(0,1,1,strlen(gstrlineEn1), gstrlineEn1);
   		    DispEn(0,2,1,strlen(gstrlineEn2), gstrlineEn2);
   		    DispEn(0,3,1,strlen(gstrlineEn3), gstrlineEn3);
   		    DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);
			DispEn(0,5,1,strlen(gstrlineEn5), gstrlineEn5);
   		    DispEn(0,6,1,strlen(gstrlineEn6), gstrlineEn6);
   		    DispEn(0,7,1,strlen(gstrlineEn7), gstrlineEn7);
   		    DispEn(0,8,1,strlen(gstrlineEn8), gstrlineEn8);
			DispEn(1,3,g_mShowMenucolumn,1,&gstrlineEn3[g_mShowMenucolumn-1]);//��ǰҪ��������ַ��ӱ���
	       break;	
	case SYS_SUB3SUB6SUB2M_SF:	
        	DispEn(0,1,1,strlen(gstrlineEn1), gstrlineEn1);
   		    DispEn(0,2,1,strlen(gstrlineEn2), gstrlineEn2);
   		    DispEn(0,3,1,strlen(gstrlineEn3), gstrlineEn3);
   		    DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);
			DispEn(0,5,1,strlen(gstrlineEn5), gstrlineEn5);
   		    DispEn(0,6,1,strlen(gstrlineEn6), gstrlineEn6);
   		    DispEn(0,7,1,strlen(gstrlineEn7), gstrlineEn7);
   		    DispEn(0,8,1,strlen(gstrlineEn8), gstrlineEn8);
			DispEn(1,5,g_mShowMenucolumn,1,&gstrlineEn5[g_mShowMenucolumn-1]);//��ǰҪ��������ַ��ӱ���
	       break;	

	   	case SYS_SUB3SUB6SUB2M_MF1:	
        	DispEn(0,1,1,strlen(gstrlineEn1), gstrlineEn1);
   		    DispEn(0,2,1,strlen(gstrlineEn2), gstrlineEn2);
   		    DispEn(0,3,1,strlen(gstrlineEn3), gstrlineEn3);
   		    DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);
			DispEn(0,5,1,strlen(gstrlineEn5), gstrlineEn5);
   		    DispEn(0,6,1,strlen(gstrlineEn6), gstrlineEn6);
   		    DispEn(0,7,1,strlen(gstrlineEn7), gstrlineEn7);
   		    DispEn(0,8,1,strlen(gstrlineEn8), gstrlineEn8);
			DispEn(1,3,g_mShowMenucolumn,1,&gstrlineEn3[g_mShowMenucolumn-1]);//��ǰҪ��������ַ��ӱ���
			DispCh(0,7,10,CharD);
			DispCh(0,7,13,CharM);
			DispCh(0,8,21,CharD);
	       break;	
	case SYS_SUB3SUB6SUB2M_SF1:	
        	DispEn(0,1,1,strlen(gstrlineEn1), gstrlineEn1);
   		    DispEn(0,2,1,strlen(gstrlineEn2), gstrlineEn2);
   		    DispEn(0,3,1,strlen(gstrlineEn3), gstrlineEn3);
   		    DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);
			DispEn(0,5,1,strlen(gstrlineEn5), gstrlineEn5);
   		    DispEn(0,6,1,strlen(gstrlineEn6), gstrlineEn6);
   		    DispEn(0,7,1,strlen(gstrlineEn7), gstrlineEn7);
   		    DispEn(0,8,1,strlen(gstrlineEn8), gstrlineEn8);
			DispEn(1,5,g_mShowMenucolumn,1,&gstrlineEn5[g_mShowMenucolumn-1]);//��ǰҪ��������ַ��ӱ���
			DispCh(0,7,10,CharD);
			DispCh(0,7,13,CharM);
			DispCh(0,8,21,CharD);
	       break;
		case SYS_SUB3SUB6SUB2M_MFOV:	
        	DispEn(0,1,1,strlen(gstrlineEn1), gstrlineEn1);
   		    DispEn(0,2,1,strlen(gstrlineEn2), gstrlineEn2);
   		    DispEn(0,3,1,strlen(gstrlineEn3), gstrlineEn3);
   		    DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);
			DispEn(0,5,1,strlen(gstrlineEn5), gstrlineEn5);
   		    DispEn(0,6,1,strlen(gstrlineEn6), gstrlineEn6);
   		    DispEn(0,7,1,strlen(gstrlineEn7), gstrlineEn7);
   		    DispEn(0,8,1,strlen(gstrlineEn8), gstrlineEn8);
			DispEn(1,7,g_mShowMenucolumn,1,&gstrlineEn7[g_mShowMenucolumn-1]);//��ǰҪ��������ַ��ӱ���
			DispCh(0,7,10,CharD);
			DispCh(0,7,13,CharM);
			DispCh(0,8,21,CharD);
	       break;
	//½��Ŀ��
	      case SYS_SUB2SUB11_SET : 
		            DispEn(0,1,1,strlen(gstrlineEn1), gstrlineEn1);
		   		    DispEn(0,2,1,strlen(gstrlineEn2), gstrlineEn2);
		   		    DispEn(0,3,1,strlen(gstrlineEn3), gstrlineEn3);
		   	    	DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);
					DispEn(0,5,1,strlen(gstrlineEn5), gstrlineEn5);
		   		    DispEn(0,6,1,strlen(gstrlineEn6), gstrlineEn6);
		   		    DispEn(0,7,1,strlen(gstrlineEn7), gstrlineEn7);
		   	    	DispEn(0,8,1,strlen(gstrlineEn8), gstrlineEn8);
					switch(g_mMyLandmarkOperator)
					{
				   		case 1:
							switch(g_mMyLandmarkShowMode)
							{
						 	 case 0:
						  		DispEn(1,2,g_mShowMenucolumn,1,&gstrlineEn2[g_mShowMenucolumn-1]);
						  		break;
						 	 case 1:
						 	 	DispEn(1,3,g_mShowMenucolumn,1,&gstrlineEn3[g_mShowMenucolumn-1]);
						 	 	break;
						 	 case 2:
						 	   DispEn(1,4,g_mShowMenucolumn,1,&gstrlineEn4[g_mShowMenucolumn-1]);
							  	break;
						 	 default:
						  		break;
							}
				 		default :
				  			break;		 
					}
					break;
	//�Զ����Ǳ�
		   case SYS_SUB2SUB8_SET : 
		            DispEn(0,1,1,strlen(gstrlineEn1), gstrlineEn1);
		   		    DispEn(0,2,1,strlen(gstrlineEn2), gstrlineEn2);
		   		    DispEn(0,3,1,strlen(gstrlineEn3), gstrlineEn3);
		   	    	DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);
					DispEn(0,5,1,strlen(gstrlineEn5), gstrlineEn5);
		   		    DispEn(0,6,1,strlen(gstrlineEn6), gstrlineEn6);
		   		    DispEn(0,7,1,strlen(gstrlineEn7), gstrlineEn7);
		   	    	DispEn(0,8,1,strlen(gstrlineEn8), gstrlineEn8);
					switch(g_mMyStarOperator)
					{
				   		case 1:
						case 3:
							switch(g_mMyStarShowMode)
							{
						 	 case 0:
						  		DispEn(1,2,g_mShowMenucolumn,1,&gstrlineEn2[g_mShowMenucolumn-1]);
						  		break;
						 	 case 1:
						 	 	DispEn(1,3,g_mShowMenucolumn,1,&gstrlineEn3[g_mShowMenucolumn-1]);
						 	 	break;
						 	 case 2:
						 	   DispEn(1,4,g_mShowMenucolumn,1,&gstrlineEn4[g_mShowMenucolumn-1]);
							  	break;
						 	 default:
						  		break;
							}
				 		default :
				  			break;		 
					}
					break;

			 //**************************************
		      default: 
			  //ϵͳ�˵���ʾ	      
		        switch(g_mShowMenurowUn) //���˵���ʾ�����Ҫ�������ʾ��g_mShowMenurowUnҪ����6
		        {
                 case 0:
		   		    DispUn(0,1,1,136, (uint16*)gstrlineUn1);
		   			DispUn(0,2,1,136, (uint16*)gstrlineUn2);
		   			DispUn(0,3,1,136, (uint16*)gstrlineUn3);
		   		    DispUn(0,4,1,136, (uint16*)gstrlineUn4);
		   		   break ;
			      case 1:
		   		    DispUn(1,1,1,136, (uint16*)gstrlineUn1);
		   		    DispUn(0,2,1,136, (uint16*)gstrlineUn2);
		   		    DispUn(0,3,1,136, (uint16*)gstrlineUn3);
		   		    DispUn(0,4,1,136, (uint16*)gstrlineUn4);
		   		  break ;
		          case 2:
		   		    DispUn(0,1,1,136, (uint16*)gstrlineUn1);
		   	    	DispUn(1,2,1,136, (uint16*)gstrlineUn2);
		   		    DispUn(0,3,1,136, (uint16*)gstrlineUn3);
		   		    DispUn(0,4,1,136, (uint16*)gstrlineUn4);
		   		  break ;
			      case 3:
		   	 	    DispUn(0,1,1,136, (uint16*)gstrlineUn1);
		   			DispUn(0,2,1,136, (uint16*)gstrlineUn2);
		   			DispUn(1,3,1,136, (uint16*)gstrlineUn3);
		   			DispUn(0,4,1,136, (uint16*)gstrlineUn4);
		   	      break ;
				  case 4:
		   			DispUn(0,1,1,136, (uint16*)gstrlineUn1);
		   			DispUn(0,2,1,136, (uint16*)gstrlineUn2);
		   			DispUn(0,3,1,136, (uint16*)gstrlineUn3);
		   			DispUn(1,4,1,136, (uint16*)gstrlineUn4);
		   		  break ;
			 	 case 5:
		   			DispUn(1,1,1,136, (uint16*)gstrlineUn1);
		   			DispUn(1,2,1,136, (uint16*)gstrlineUn2);
		   			DispUn(1,3,1,136, (uint16*)gstrlineUn3);
		   			DispUn(1,4,1,136, (uint16*)gstrlineUn4);
		   	    	break ;
				   default:break;
		         }
			 //**************************************
		   break;
		   }
           
	  break;

	  default:	//����
//		   g_mshowed1=g_nsysstatus;
//		   if(g_mshowed1!=g_mshowed2)  //��Զ��״̬����Ͳ�ˢ��,״̬���ˢ��
//		   {
//		    
//		      LCDRfrsh();
//			  g_mshowed2=g_mshowed1;
//		   } 
//			 	
//		    switch(g_nsysstatus )
//		    {	  
//		        case SYS_NOTELSCOPE:   //��Զ��û������ʾ
//				
//					 
//
//					 DispCn(0,2,0,128,gstrlineCn2);
//					 DispCn(0,3,0,128,gstrlineCn3);
//
//				     FBeep(1);
//					 delay(200);
//					 FBeep(1);
//					 delay(200);
//					 FBeep(1);
//					 delay(200);
//					 g_nsysstatus =SYS_MAINSHOW;
//				break;
//
//		        case SYS_SUB1SUB1AUTOSTAR_ALIGN:   //�����Զ�У׼
//			
//				    if(!g_nAlignPoint)
//					{
//					  switch(g_nSeledAlignStarNum)
//					  {
//					    case 1:
//						case 2:
//						//DispEn(0,1,0,22,"                       ");
//						//DispEn(0,2,0,22,"                       ");					    
//						//DispEn(0,3,0,22,"                       ");
//						//DispEn(0,4,0,22,"                       ");
//						//DispEn(0,5,5,18,"                   ");
//						//DispEn(0,6,12,11,"            ");
//						//DispEn(0,7,12,11,"            ");
//						//DispEn(0,8,12,11,"            ");
//
//						   //g_mAlignTelStatur=0;//��Զ��У׼ʱϵͳ����״̬
//						   if(g_mAlignTelStatus!=1)
//						   {
//						       LCDRfrsh();
//						   }
//						   g_mAlignTelStatus=1;
//
//						    DispCn(0,1,1,128, gstrlineCn1);
//			   		        DispEn(0,3,1,strlen(gstrlineCn3), gstrlineCn3);	
//						    DispEn(0,3,10,12, "            ");
//	
//			   		    	DispEn(0,5,1,4, "OBJ:");
//														  
//							DispEn(0,7,11,strlen(gstrlineEn5), gstrlineEn5);						
//				   		    DispEn(0,8,11,strlen(gstrlineEn6), gstrlineEn6);
//				   		    DispEn(0,5,11,strlen(gstrlineEn7), gstrlineEn7);						
//				   		    DispEn(0,6,11,strlen(gstrlineEn8), gstrlineEn8);
//
//							DispCh(0, 5,18,CharD);
//			  	            DispCh(0, 5,21,CharM);
//							DispCh(0, 6,18,CharD);
//			  	            DispCh(0, 6,21,CharM);
//							DispCh(0, 8,18,CharD);
//			  	            DispCh(0, 8,21,CharM);
//						   delay(300);
//
//						if(g_nSeledAlignStarNum==1)
//						{
//						   FTwoStarAutoAlign();
//						}
//					    g_nAlignPoint=true;//��Զ����һ����������У��ʱ�ǵ���ȷ�ϻ���ѡ��falseѡ���ǣ�trueУ������ȷ��
//					    
//					   break;
//					   case 3: 
//					       if(g_mAlignTelStatus!=2)
//						   {
//						       LCDRfrsh();
//						   }
//						   g_mAlignTelStatus=2;
//
//					        FPointAlignStarOk();
//							FBeep(3);
//						    gstrlineCn1=g_sysmenu1106;
//							gstrlineCn2=g_sysmenu1107;
//							gstrlineCn3=g_sysmenu1108;
//							gstrlineCn4=g_sysmenu1109;
//						   
//						   	DispEn(0,1,0,22,"                       ");
//							DispEn(0,2,0,22,"                       ");
//							DispCn(0,2,0,128,gstrlineCn2);
//							DispCn(0,3,0,128,gstrlineCn3);
//							DispCn(0,4,0,128,gstrlineCn4);
//							DispEn(0,7,0,22,"                       ");
//							DispEn(0,8,0,22,"                       ");
//							
//						    //FBeep(2);
//						    delay(300);
//						    g_nsysstatus =SYS_MAINSHOW;
//					   break;
//					   default:
//					   break;
//					  }
//					}
//					else
//					{	
//						
//						if(g_mTelStatus==1)
//						{
//						   if(g_mAlignTelStatus!=3)
//						   {
//						       LCDRfrsh();
//						   }
//						   g_mAlignTelStatus=3;
//
//
//								gstrlineCn2=g_sysmenu1101;
//								if(g_mGoto.m_nTelGotoPause==0)
//								{
//							   	  DispCn(0,1,1,128,gstrlineCn2);
//								 }
//								 else
//								 {
//								    DispCn(0,1,1,128,g_sysalign1101Pause_Cn);
//								 }
//
//								
//							   	DispCn(0,2,1,128,gstrlineCn1);
//
//					            DispEn(0,5,1,4, "OBJ:");
//			             		DispEn(0,5,11,strlen(gstrlineEn7), gstrlineEn7);								
//					   		    DispEn(0,6,11,strlen(gstrlineEn8), gstrlineEn8);
//								DispCh(0, 5,18,CharD);
//				  	            DispCh(0, 5,21,CharM);
//
//								DispCh(0, 6,18,CharD);
//				  	            DispCh(0, 6,21,CharM); 
//
//								DispEn(0,6,1,6, "        ");
//
//								DispEn(0,7,1,4, "OTA:");
//					   		    DispEn(0,7,11,strlen(gstrlineEn5), gstrlineEn5);						
//					   		    DispEn(0,8,11,strlen(gstrlineEn6), gstrlineEn6);
//							//	switch(g_mAzEq)
//							//	{
//							//	case 0:
//									 DispCh(0, 7,18,CharD);
//				  	                 DispCh(0, 7,21,CharM);
//							//		break;
//							//	case 1: 
//							//	   	DispEn(0, 7,15,1," ");
//							//	   DispEn(0, 7,18,1,"h");
//				  	        //       DispEn(0, 7,21,1,"m");
//							//		break;
//							//	default:
//							//		break;
//							//	}
//								DispCh(0, 8,18,CharD);
//				  	            DispCh(0, 8,21,CharM); 
//								DispEn(0,6,1,6,"      ");
//							  	 
//							
//											  	 
//				
//						}
//						if(g_mTelStatus==2)
//						{
//						   if(g_mAlignTelStatus!=4)
//						   {
//						       LCDRfrsh();
//						   }
//						   g_mAlignTelStatus=4;
//
//						    gstrlineCn1=g_sysmenu1102;
//							gstrlineCn2=g_sysmenu1103;
//							gstrlineCn3=g_sysmenu1104;
//							gstrlineCn4=g_sysmenu1105;
//						   
//						   	DispCn(0,1,0,128,gstrlineCn1);
//							DispCn(0,2,0,128,gstrlineCn2);
//							DispCn(0,3,0,128,gstrlineCn3);
//							DispCn(0,4,0,128,gstrlineCn4);
//
//							//DispEn(0,7,16,6, "   ");
//							//DispEn(0,8,16,6, "   ");
//						
//						}
//					}
//				break;
//		        
//				case SYS_SUB1SUB2STAR_ALIGN	:  //һ������У׼����ʾ����
//			
//				   	if(!g_nAlignPoint)
//					{
//					
//						if(g_nAlignStar==0)
//						{
//						     if(g_mAlignTelStatus!=5)
//						   {
//						       LCDRfrsh();
//						   }
//						   g_mAlignTelStatus=5;
//
//						    FPointAlignStarOk();
//							FBeep(3);
//						   	gstrlineCn1=g_sysmenu1106;
//							gstrlineCn2=g_sysmenu1107;
//							gstrlineCn3=g_sysmenu1108;
//							gstrlineCn4=g_sysmenu1109;
//						   
//						   	DispEn(0,1,0,22,"                       ");
//							DispEn(0,2,0,22,"                       ");
//							DispCn(0,2,0,128,gstrlineCn2);
//							DispCn(0,3,0,128,gstrlineCn3);
//							DispEn(0,7,1,22,"                       ");
//							DispEn(0,8,1,22,"                       ");
//						    //FBeep(2);
//							
//						    delay(300);
//						    g_nsysstatus =SYS_MAINSHOW;
//						}
//						else
//						{  
//						   		//DispEn(0,1,0,22,"                       ");
//								//DispEn(0,2,0,22,"                       ");					    
//								//DispEn(0,3,0,22,"                       ");
//								//DispEn(0,4,0,22,"                       ");
//								//DispEn(0,4,0,22,"                       ");
//								//DispEn(0,5,5,18,"                   ");
//								//DispEn(0,6,12,11,"            ");
//								//DispEn(0,7,12,11,"            ");
//								//DispEn(0,8,12,11,"            ");
//					      if(g_mAlignTelStatus!=6)
//						   {
//						       LCDRfrsh();
//						   }
//						   g_mAlignTelStatus=6;
//
//						   	DispCn(0,1,1,128, gstrlineCn1);
//				   		    DispEn(0,3,1,strlen(gstrlineCn3), gstrlineCn3);	
//							DispEn(0,3,10,12, "            ");
//	
//				   		    DispEn(0,4,0,strlen(gstrlineCn4), gstrlineCn4);	
//							
//													  
//							DispEn(0,5,1,4, "OBJ:");
//														  
//							DispEn(0,7,11,strlen(gstrlineEn7), gstrlineEn7);						
//				   		    DispEn(0,8,11,strlen(gstrlineEn8), gstrlineEn8);
//				   		    DispEn(0,5,11,strlen(gstrlineEn5), gstrlineEn5);						
//				   		    DispEn(0,6,11,strlen(gstrlineEn6), gstrlineEn6);
//
//							DispCh(0, 5,18,CharD);
//			  	            DispCh(0, 5,21,CharM);
//							DispCh(0, 6,18,CharD);
//			  	            DispCh(0, 6,21,CharM);
//							DispCh(0, 8,18,CharD);
//			  	            DispCh(0, 8,21,CharM);
//							DispEn(0,6,1,4,"      ");
//						}
//					}
//					else
//					{ 
//					    if(g_mTelStatus==1)
//						{
//						          
//							if(g_mAlignTelStatus!=7)
//						   {
//						       LCDRfrsh();
//						   }
//						   g_mAlignTelStatus=7;
//
//							    gstrlineCn2=g_sysmenu1101;
//
//							   	if(g_mGoto.m_nTelGotoPause==0)
//								{
//							   	  DispCn(0,1,1,128,gstrlineCn2);
//								 }
//								 else
//								 {
//								    DispCn(0,1,1,128,g_sysalign1101Pause_Cn);
//								 }
//
//
//							   	DispCn(0,2,1,128,gstrlineCn1);
//								DispEn(0,3,20,2, "   ");
//								DispEn(0,4,20,2, "   ");
//		                         
//			                	 DispEn(0,5,1,4, "OBJ:");
//			                	DispEn(0,5,11,strlen(gstrlineEn5), gstrlineEn5);								
//					   		    DispEn(0,6,11,strlen(gstrlineEn6), gstrlineEn6);
//
//								DispCh(0, 5,18,CharD);
//				  	            DispCh(0, 5,21,CharM);
//
//								DispCh(0, 6,18,CharD);
//				  	            DispCh(0, 6,21,CharM); 
//
//								
//
//								DispEn(0,7,1,4, "OTA:")
//								
//								
//
//
//								;
//					   		    DispEn(0,7,11,strlen(gstrlineEn7), gstrlineEn7);						
//					   		    DispEn(0,8,11,strlen(gstrlineEn8), gstrlineEn8);
//							//	switch(g_mAzEq)
//							//	{
//							//	case 0:
//									 DispCh(0, 7,18,CharD);
//				  	                 DispCh(0, 7,21,CharM);
//							//		break;
//							//	case 1: 
//							//	   	DispEn(0, 7,15,1," ");
//							//	   DispEn(0, 7,18,1,"h");
//				  	         //      DispEn(0, 7,21,1,"m");
//							//		break;
//							//	default:
//							//		break;
//							//	}
//								DispCh(0, 8,18,CharD);
//				  	            DispCh(0, 8,21,CharM); 
//								DispEn(0,6,1,4,"      "); 
//
//								
//							  	 
//				
//						}
//						if(g_mTelStatus==2)
//						{
//						 if(g_mAlignTelStatus!=8)
//						   {
//						       LCDRfrsh();
//						   }
//						   g_mAlignTelStatus=8;
//
//						    gstrlineCn1=g_sysmenu1102;
//							gstrlineCn2=g_sysmenu1103;
//							gstrlineCn3=g_sysmenu1104;
//							gstrlineCn4=g_sysmenu1105;
//						   
//						   	DispCn(0,1,0,128,gstrlineCn1);
//							DispCn(0,2,0,128,gstrlineCn2);
//							DispCn(0,3,0,128,gstrlineCn3);
//							DispCn(0,4,0,128,gstrlineCn4);
//							//DispEn(0,7,16,6, "   ");
//							//DispEn(0,8,16,6, "   ");
//						}
//					}
//
//				 break;
//				 //�ྭ�ز�У��
//			  case SYS_SUB1SUB11RA_GEAR_ERROR_BEGIN:  
//			  case SYS_SUB1SUB11RA_GEAR_ERROR: 
//			  case SYS_SUB1SUB11RA_GEAR_ERROR_ALIGN: 		      
//                    DispCn(0,1,0,128, gstrlineCn1);
//		   			DispCn(0,2,0,128, gstrlineCn2);
//		   			DispCn(0,3,0,128, gstrlineCn3);
//		   		    DispCn(0,4,0,128, gstrlineCn4);
//			   break;
//			   case SYS_SUB1SUB11RA_GEAR_ERROR_ALIGN_OK: 			   		     
//				  FBeep(1);	
//				    //DispCn(0,1,0,128, gstrlineCn1);
//					if(g_mTelGearErrorRaAlignDirect==2)
//					{
//		   			  DispCn(0,2,0,128, gstrlineCn2);
//					 }
//					 else
//					 {
//		   			   DispCn(0,2,0,128, gstrlineCn3);
//					 }
//		   		     DispEn(0,6,5,strlen(gstrlineCn1), gstrlineCn1);
//					 	
//					 DispCn(0,4,0,128, gstrlineCn4);					
//				  delay(800);
//				  g_nsysstatus =SYS_SUB1SUB11RA_GEAR_ERROR_BEGIN;
//			   break;
//
//			   case SYS_SUB1SUB11RA_GEAR_ERROR_ALIGN_END: 			   		     
//				  FBeep(3);	
//				   //DispCn(0,1,0,128, gstrlineCn1);
//				
//		   			  DispCn(0,2,0,128, gstrlineCn2);
//					
//		   		     DispEn(0,6,5,strlen(gstrlineCn1), gstrlineCn1);
//					 	
//					 DispCn(0,4,0,128, gstrlineCn4);					
//				  delay(800);
//				  g_nsysstatus =SYS_MAINSHOW;
//			   break;
//
//
//			   			 //��γ�ز�У��
//			  case SYS_SUB1SUB12DEC_GEAR_ERROR_BEGIN:  
//			  case SYS_SUB1SUB12DEC_GEAR_ERROR: 
//			  case SYS_SUB1SUB12DEC_GEAR_ERROR_ALIGN: 		      
//                    DispCn(0,1,0,128, gstrlineCn1);
//		   			DispCn(0,2,0,128, gstrlineCn2);
//		   			DispCn(0,3,0,128, gstrlineCn3);
//		   		    DispCn(0,4,0,128, gstrlineCn4);
//			   break;
//			   case SYS_SUB1SUB12DEC_GEAR_ERROR_ALIGN_OK: 			   		     
//				  FBeep(1);	
//				    //DispCn(0,1,0,128, gstrlineCn1);
//					if(g_mTelGearErrorDecAlignDirect==2)
//					{
//		   			  DispCn(0,2,0,128, gstrlineCn2);
//					 }
//					 else
//					 {
//		   			   DispCn(0,2,0,128, gstrlineCn3);
//					 }
//		   		     DispEn(0,6,5,strlen(gstrlineCn1), gstrlineCn1);
//					 	
//					 DispCn(0,4,0,128, gstrlineCn4);					
//				  delay(800);
//				  g_nsysstatus =SYS_SUB1SUB12DEC_GEAR_ERROR_BEGIN;
//			   break;
//
//			   case SYS_SUB1SUB12DEC_GEAR_ERROR_ALIGN_END: 			   		     
//				  FBeep(3);	
//				   //DispCn(0,1,0,128, gstrlineCn1);
//				
//		   			  DispCn(0,2,0,128, gstrlineCn2);
//					
//		   		     DispEn(0,6,5,strlen(gstrlineCn1), gstrlineCn1);
//					 	
//					 DispCn(0,4,0,128, gstrlineCn4);					
//				  delay(800);
//				  g_nsysstatus =SYS_MAINSHOW;
//			   break;
//
//			   				//̫��ϵ����
//			   case SYS_SUB2SUN_PLANET:
//
//
//			   		   	    DispCn(0,1,0,128,gstrlineCn1);          
//				   		    DispCn(0,2,0,128,gstrlineCn3);								
//				   		    
//														  
//							DispEn(0,5,1,strlen(gstrlineEn5), gstrlineEn5);						
//				   		    DispEn(0,6,8,strlen(gstrlineEn6), gstrlineEn6);
//				   		    DispEn(0,7,8,strlen(gstrlineEn7), gstrlineEn7);						
//				   		    DispEn(0,8,8,strlen(gstrlineEn8), gstrlineEn8);
//							DispCh(0, 5,15,CharD);
//			  	            DispCh(0, 5,18,CharM);
//							DispCh(0, 5,21,CharS);
//							DispCh(0, 6,15,CharD);
//			  	            DispCh(0, 6,18,CharM);
//                        	DispCh(0, 6,21,CharS);
//							DispCh(0, 8,15,CharD);
//			  	            DispCh(0, 8,18,CharM);
//							DispCh(0, 8,21,CharS);
//
//			   break;
//			   case SYS_SUB2SUN_PLANET1:
//			   case  SYS_SUB2CON_OBJECT1:		   
//			  
//			   
//			  
//
//
//			   		   	    DispCn(0,1,0,128,gstrlineCn1);          
//				   		    DispCn(0,2,0,128,gstrlineCn3);								
//				   		    
//														  
//															  
//							DispEn(0,5,1,strlen(gstrlineEn5), gstrlineEn5);						
//				   		    DispEn(0,6,8,strlen(gstrlineEn6), gstrlineEn6);
//				   		    DispEn(0,7,1,strlen(gstrlineEn7), gstrlineEn7);						
//				   		    DispEn(0,8,8,strlen(gstrlineEn8), gstrlineEn8);
//							DispCh(0, 5,15,CharD);
//			  	            DispCh(0, 5,18,CharM);
//							DispCh(0, 5,21,CharS);
//							DispCh(0, 6,15,CharD);
//			  	            DispCh(0, 6,18,CharM);
//                        	DispCh(0, 6,21,CharS);
////							if(g_mAzEq==0)
////							{
//							DispCh(0, 7,15,CharD);
//			  	            DispCh(0, 7,18,CharM);
//							DispCh(0, 7,21,CharS);
////							}
//////							else
//////							{
////							   DispEn(0, 7,15,1,"h");
////			  	               DispEn(0, 7,18,1,"m");
////							   DispEn(0, 7,21,1,"s");
////							}
//							DispCh(0, 8,15,CharD);
//			  	            DispCh(0, 8,18,CharM);
//							DispCh(0, 8,21,CharS);
////							if(g_mAzEq==1)
////							{
////							  DispEn(0, 7,8,3,"H.a");
////			  	              DispEn(0, 8,8,3,"Dec");
////							 }
//						if(g_mOperateStatus==2)
//						{
//						    MenuDelay(2000);
//						    FBeep(1); 
//							MenuDelay(1000);
//							FBeep(1); 
//							MenuDelay(1000);							  
//						    g_nsysstatus=SYS_MAINSHOW;					  			   
//						}
//
//			   break;  
//		
//			   //case  SYS_SUB2NGC_OBJECT1:
//			   //case  SYS_SUB2IC_OBJECT1:
//		       case  SYS_SUB2SH2_OBJECT1:	
//			   //case  SYS_SUB2BRT_OBJECT1:
//			   case  SYS_SUB2SAO_OBJECT1:
//			  
//
//
//			   		   	    DispCn(0,1,0,128,gstrlineCn1);          
//				   		    
//							DispEn(0,3,1,strlen(gstrlineEn3), gstrlineEn3);
//							DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);								
//				   		    
//														  
//															  
//							DispEn(0,5,1,strlen(gstrlineEn5), gstrlineEn5);						
//				   		    DispEn(0,6,8,strlen(gstrlineEn6), gstrlineEn6);
//				   		    DispEn(0,7,1,strlen(gstrlineEn7), gstrlineEn7);						
//				   		    DispEn(0,8,8,strlen(gstrlineEn8), gstrlineEn8);
//							DispCh(0, 5,15,CharD);
//			  	            DispCh(0, 5,18,CharM);
//							DispCh(0, 5,21,CharS);
//							DispCh(0, 6,15,CharD);
//			  	            DispCh(0, 6,18,CharM);
//                        	DispCh(0, 6,21,CharS);
//							//if(g_mAzEq==0)
//						//	{
//							DispCh(0, 7,15,CharD);
//			  	            DispCh(0, 7,18,CharM);
//							DispCh(0, 7,21,CharS);
////						//	}
////							else
////							{
////							   DispEn(0, 7,15,1,"h");
////			  	               DispEn(0, 7,18,1,"m");
////							   DispEn(0, 7,21,1,"s");
////							}
//							DispCh(0, 8,15,CharD);
//			  	            DispCh(0, 8,18,CharM);
//							DispCh(0, 8,21,CharS);
////								if(g_mAzEq==1)
////							{
////							  DispEn(0, 7,8,3,"H.a");
////			  	              DispEn(0, 8,8,3,"Dec");
////							 }
//					if(g_mOperateStatus==2)
//						{
//						    MenuDelay(2000);
//						    FBeep(1); 
//							MenuDelay(1000);
//							FBeep(1); 
//							MenuDelay(1000);							  
//						    g_nsysstatus=SYS_MAINSHOW;					  			   
//						}
//
//			   break;
//			    				//88����
//			  case  SYS_SUB2CON_OBJECT:
//			    		
//
//			   		   	    DispCn(0,1,0,128,gstrlineCn1);          
//				   		    DispEn(0,3,1,strlen(gstrlineEn3), gstrlineEn3);	
//							DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);	
//										  
//							DispEn(0,5,1,strlen(gstrlineEn5), gstrlineEn5);						
//				   		    DispEn(0,6,8,strlen(gstrlineEn6), gstrlineEn6);
//				   		    DispEn(0,7,8,strlen(gstrlineEn7), gstrlineEn7);						
//				   		    DispEn(0,8,8,strlen(gstrlineEn8), gstrlineEn8);
//							DispCh(0, 5,15,CharD);
//			  	            DispCh(0, 5,18,CharM);
//							DispCh(0, 5,21,CharS);
//							DispCh(0, 6,15,CharD);
//			  	            DispCh(0, 6,18,CharM);
//                        	DispCh(0, 6,21,CharS);
//							DispCh(0, 8,15,CharD);
//			  	            DispCh(0, 8,18,CharM);
//							DispCh(0, 8,21,CharS);
//
//			   break;
//
//			  case  SYS_SUB2FS_OBJECT:   //��������
//			  	          
//
//			   		   	    DispCn(0,1,0,72,gstrlineCn1);          
//				   		    DispCn(0,1,72,128,gstrlineCn3);	
//							
//							DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);					  
//							DispEn(0,5,1,strlen(gstrlineEn5), gstrlineEn5);						
//				   		    DispEn(0,6,8,strlen(gstrlineEn6), gstrlineEn6);
//				   		    DispEn(0,7,8,strlen(gstrlineEn7), gstrlineEn7);						
//				   		    DispEn(0,8,8,strlen(gstrlineEn8), gstrlineEn8);
//							DispCh(0, 5,15,CharD);
//			  	            DispCh(0, 5,18,CharM);
//							DispCh(0, 5,21,CharS);
//							DispCh(0, 6,15,CharD);
//			  	            DispCh(0, 6,18,CharM);
//                        	DispCh(0, 6,21,CharS);
//							DispCh(0, 8,15,CharD);
//			  	            DispCh(0, 8,18,CharM);
//							DispCh(0, 8,21,CharS);
//
//			   break;
//
//			  	  case  SYS_SUB2FS_OBJECT1:   //��������
//			  	          
//
//							DispCn(0,1,0,128,gstrlineCn1);  
//			   		   	    DispCn(0,2,0,80,gstrlineCn4);          
//				   		    //DispEn(0,3,81,strlen(gstrlineEn2), gstrlineEn2);		
//							
//										  
//					    	DispEn(0,5,1,strlen(gstrlineEn5), gstrlineEn5);						
//				   		    DispEn(0,6,8,strlen(gstrlineEn6), gstrlineEn6);
//				   		    DispEn(0,7,1,strlen(gstrlineEn7), gstrlineEn7);						
//				   		    DispEn(0,8,8,strlen(gstrlineEn8), gstrlineEn8);
//							DispCh(0, 5,15,CharD);
//			  	            DispCh(0, 5,18,CharM);
//							DispCh(0, 5,21,CharS);
//							DispCh(0, 6,15,CharD);
//			  	            DispCh(0, 6,18,CharM);
//                        	DispCh(0, 6,21,CharS);
//							//if(g_mAzEq==0)
//							//{
//							DispCh(0, 7,15,CharD);
//			  	            DispCh(0, 7,18,CharM);
//							DispCh(0, 7,21,CharS);
////							}
////							else
////							{
////							   DispEn(0, 7,15,1,"h");
////			  	               DispEn(0, 7,18,1,"m");
////							   DispEn(0, 7,21,1,"s");
////							}
//							DispCh(0, 8,15,CharD);
//			  	            DispCh(0, 8,18,CharM);
//							DispCh(0, 8,21,CharS);
////								if(g_mAzEq==1)
////							{
////							  DispEn(0, 7,8,3,"H.a");
////			  	              DispEn(0, 8,8,3,"Dec");
////							 }
//						if(g_mOperateStatus==2)
//						{
//						    MenuDelay(2000);
//						    FBeep(1); 
//							MenuDelay(1000);
//							FBeep(1); 
//							MenuDelay(1000);							  
//						    g_nsysstatus=SYS_MAINSHOW;					  			   
//						}
//
//			   break;
//						   		//messier�Ǳ�
//
//					case  SYS_SUB2MSR_OBJECT1:
//				        
//					        DispCn(0,1,0,128,gstrlineCn1);          
//				   		        
//							DispEn(0,3,1,strlen(gstrlineEn2), gstrlineEn2);
//							DispEn(0,4,1,128,"                                  ");								
//				   		    
//														  
//															  
//							DispEn(0,5,1,strlen(gstrlineEn5), gstrlineEn5);						
//				   		    DispEn(0,6,8,strlen(gstrlineEn6), gstrlineEn6);
//				   		    DispEn(0,7,1,strlen(gstrlineEn7), gstrlineEn7);						
//				   		    DispEn(0,8,8,strlen(gstrlineEn8), gstrlineEn8);
//							DispCh(0, 5,15,CharD);
//			  	            DispCh(0, 5,18,CharM);
//							DispCh(0, 5,21,CharS);
//							DispCh(0, 6,15,CharD);
//			  	            DispCh(0, 6,18,CharM);
//                        	DispCh(0, 6,21,CharS);
//							//if(g_mAzEq==0)
//						//	{
//							DispCh(0, 7,15,CharD);
//			  	            DispCh(0, 7,18,CharM);
//							DispCh(0, 7,21,CharS);
////							}
////							else
////							{
////							   DispEn(0, 7,15,1,"h");
////			  	               DispEn(0, 7,18,1,"m");
////							   DispEn(0, 7,21,1,"s");
////							}
//							DispCh(0, 8,15,CharD);
//			  	            DispCh(0, 8,18,CharM);
//							DispCh(0, 8,21,CharS);
////								if(g_mAzEq==1)
////							{
////							  DispEn(0, 7,8,3,"H.a");
////			  	              DispEn(0, 8,8,3,"Dec");
////							 }
//					if(g_mOperateStatus==2)
//						{
//						    MenuDelay(2000);
//						    FBeep(1); 
//							MenuDelay(1000);
//							FBeep(1); 
//							MenuDelay(1000);							  
//						    g_nsysstatus=SYS_MAINSHOW;					  			   
//						}
//
//					break;
//
//			   case  SYS_SUB2NGC_OBJECT1:
//			   case  SYS_SUB2IC_OBJECT1:
//	
//			   		   	    DispCn(0,1,0,128,gstrlineCn1);          
//				   		    
//							DispEn(0,3,1,strlen(gstrlineEn2), gstrlineEn2);
//							DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);								
//				   		    
//														  
//															  
//							DispEn(0,5,1,strlen(gstrlineEn5), gstrlineEn5);						
//				   		    DispEn(0,6,8,strlen(gstrlineEn6), gstrlineEn6);
//				   		    DispEn(0,7,1,strlen(gstrlineEn7), gstrlineEn7);						
//				   		    DispEn(0,8,8,strlen(gstrlineEn8), gstrlineEn8);
//							DispCh(0, 5,15,CharD);
//			  	            DispCh(0, 5,18,CharM);
//							DispCh(0, 5,21,CharS);
//							DispCh(0, 6,15,CharD);
//			  	            DispCh(0, 6,18,CharM);
//                        	DispCh(0, 6,21,CharS);
//							//if(g_mAzEq==0)
//							//{
//							 DispCh(0, 7,15,CharD);
//			  	             DispCh(0, 7,18,CharM);
//							 DispCh(0, 7,21,CharS);
////							}
////							else
////							{
////							   DispEn(0, 7,15,1,"h");
////			  	               DispEn(0, 7,18,1,"m");
////							   DispEn(0, 7,21,1,"s");
////							}
//							DispCh(0, 8,15,CharD);
//			  	            DispCh(0, 8,18,CharM);
//							DispCh(0, 8,21,CharS);
////								if(g_mAzEq==1)
////							{
////							  DispEn(0, 7,8,3,"H.a");
////			  	              DispEn(0, 8,8,3,"Dec");
////							 }
//							if(g_mOperateStatus==2)
//						{
//						    MenuDelay(2000);
//						    FBeep(1); 
//							MenuDelay(1000);
//							FBeep(1); 
//							MenuDelay(1000);							  
//						    g_nsysstatus=SYS_MAINSHOW;					  			   
//						}
//
//			   break;
//			
//			   case  SYS_SUB2BRT_OBJECT1:
//
//
//			   		   	    DispCn(0,1,0,128,gstrlineCn1);          
//				   		    
//							DispEn(0,3,1,strlen(gstrlineEn2), gstrlineEn2);
//							DispEn(0,4,1,strlen(gstrlineEn3), gstrlineEn3);								
//				   		    
//														  
//															  
//							DispEn(0,5,1,strlen(gstrlineEn5), gstrlineEn5);						
//				   		    DispEn(0,6,8,strlen(gstrlineEn6), gstrlineEn6);
//				   		    DispEn(0,7,1,strlen(gstrlineEn7), gstrlineEn7);						
//				   		    DispEn(0,8,8,strlen(gstrlineEn8), gstrlineEn8);
//							DispCh(0, 5,15,CharD);
//			  	            DispCh(0, 5,18,CharM);
//							DispCh(0, 5,21,CharS);
//							DispCh(0, 6,15,CharD);
//			  	            DispCh(0, 6,18,CharM);
//                        	DispCh(0, 6,21,CharS);
//						//	if(g_mAzEq==0)
//						//	{
//							DispCh(0, 7,15,CharD);
//			  	            DispCh(0, 7,18,CharM);
//							DispCh(0, 7,21,CharS);
////							}
////							else
////							{
////							   DispEn(0, 7,15,1,"h");
////			  	               DispEn(0, 7,18,1,"m");
////							   DispEn(0, 7,21,1,"s");
////							}
//							DispCh(0, 8,15,CharD);
//			  	            DispCh(0, 8,18,CharM);
//							DispCh(0, 8,21,CharS);
////								if(g_mAzEq==1)
////							{
////							  DispEn(0, 7,8,3,"H.a");
////			  	              DispEn(0, 8,8,3,"Dec");
////							 }
//					if(g_mOperateStatus==2)
//						{
//						    MenuDelay(2000);
//						    FBeep(1); 
//							MenuDelay(1000);
//							FBeep(1); 
//							MenuDelay(1000);							  
//						    g_nsysstatus=SYS_MAINSHOW;					  			   
//						}
//
//			   break;
//
//		   case  SYS_SUB2MSR_OBJECT0:
//		                 
//
//			   		   	    DispEn(0,1,1,strlen(gstrlineEn1), gstrlineEn1);	          
//				   		    DispCn(0,2,1,64,gstrlineCn2);
//							DispCn(0,2,64,128,gstrlineCn3);	
//							
//							//DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);					  
//							DispEn(0,5,1,strlen(gstrlineEn5), gstrlineEn5);						
//				   		    DispEn(0,6,1,strlen(gstrlineEn6), gstrlineEn6);
//				   		    DispEn(0,7,1,strlen(gstrlineEn7), gstrlineEn7);						
//				   		    DispEn(0,8,1,strlen(gstrlineEn8), gstrlineEn8);
//	
//
//			   break;
//	
//		   case  SYS_SUB2MSR_OBJECT:
//		                   LCDRfrsh();
//
//			   		   	    DispEn(0,1,1,strlen(gstrlineEn1), gstrlineEn1);	          
//				   		    DispCn(0,2,1,64,gstrlineCn2);
//							DispCn(0,2,64,128,gstrlineCn3);	
//							
//							//DispEn(0,4,1,strlen(gstrlineEn4), gstrlineEn4);					  
//							DispEn(0,5,1,strlen(gstrlineEn5), gstrlineEn5);						
//				   		    DispEn(0,6,8,strlen(gstrlineEn6), gstrlineEn6);
//				   		    DispEn(0,7,8,strlen(gstrlineEn7), gstrlineEn7);						
//				   		    DispEn(0,8,8,strlen(gstrlineEn8), gstrlineEn8);
//							DispCh(0, 5,15,CharD);
//			  	            DispCh(0, 5,18,CharM);
//							DispCh(0, 5,21,CharS);
//							DispCh(0, 6,15,CharD);
//			  	            DispCh(0, 6,18,CharM);
//                        	DispCh(0, 6,21,CharS);
//							DispCh(0, 8,15,CharD);
//			  	            DispCh(0, 8,18,CharM);
//							DispCh(0, 8,21,CharS);
//
//			   break;
//
//			 //���ʳ���
//		 case SYS_SUB4SUB3SUN1_CITYSEL:
//			   
//   		   	    DispCn(0,1,0,128,gstrlineCn1); 
//				DispCn(0,2,0,128,gstrlineCn2); 
//				            
//	   	 														  
//				DispEn(0,5,1,strlen(gstrlineEn5), gstrlineEn5);						
//	   		    DispEn(0,6,1,strlen(gstrlineEn6), gstrlineEn6);
//	   		    DispEn(0,7,1,strlen(gstrlineEn7), gstrlineEn7);						
//	   		    DispEn(0,8,1,strlen(gstrlineEn8), gstrlineEn8);
//				DispCh(0, 5,14,CharD);
//				DispCh(0, 5,17,CharM);
//				DispCh(0, 6,14,CharD);
//				DispCh(0, 6,17,CharM);
//             break;
//		   	case SYS_RESET:	//�˳��ָ�����״̬ 
//
//			    DispEn(0,1,1,21, "Are you sure reset   ");
//				DispEn(0,3,1,21, "System.                ");
//				DispEn(0,5,1,21, "Back: Cancel          ");
//				DispEn(0,7,1,21, "Enter: Begin Reset      ");
//
//		    break;
//
//		   default:	   
//		        switch(g_mShowMenurowCn) //���˵���ʾ�����Ҫ�������ʾ��g_mShowMenurowEnҪ����5
//		        {
//		           case 0:
////		   		    DispCn(0,1,1,strlen(gstrlineCn1)/2, gstrlineCn1);
////		   			DispCn(0,2,1,strlen(gstrlineCn2)/2, gstrlineCn2);
////		   			DispCn(0,3,1,strlen(gstrlineCn3)/2, gstrlineCn3);
////		   		    DispCn(0,4,1,strlen(gstrlineCn4)/2, gstrlineCn4);
//		   		    DispCn(0,1,1,128, gstrlineCn1);
//		   			DispCn(0,2,1,128, gstrlineCn2);
//		   			DispCn(0,3,1,128, gstrlineCn3);
//		   		    DispCn(0,4,1,128, gstrlineCn4);
//		   		   break ;
//			      case 1:
//		   		    DispCn(1,1,1,128, gstrlineCn1);
//		   		    DispCn(0,2,1,128, gstrlineCn2);
//		   		    DispCn(0,3,1,128, gstrlineCn3);
//		   		    DispCn(0,4,1,128, gstrlineCn4);
//		   		  break ;
//		          case 2:
//		   		    DispCn(0,1,1,128, gstrlineCn1);
//		   	    	DispCn(1,2,1,128, gstrlineCn2);
//		   		    DispCn(0,3,1,128, gstrlineCn3);
//		   		    DispCn(0,4,1,128, gstrlineCn4);
//		   		  break ;
//			      case 3:
//		   	 	    DispCn(0,1,1,128, gstrlineCn1);
//		   			DispCn(0,2,1,128, gstrlineCn2);
//		   			DispCn(1,3,1,128, gstrlineCn3);
//		   			DispCn(0,4,1,128, gstrlineCn4);
//		   	      break ;
//				  case 4:
//		   			DispCn(0,1,1,128, gstrlineCn1);
//		   			DispCn(0,2,1,128, gstrlineCn2);
//		   			DispCn(0,3,1,128, gstrlineCn3);
//		   			DispCn(1,4,1,128, gstrlineCn4);
//		   		  break ;
//			 	 case 5:
//		   			DispCn(1,1,1,128, gstrlineCn1);
//		   			DispCn(1,2,1,128, gstrlineCn2);
//		   			DispCn(1,3,1,128, gstrlineCn3);
//		   			DispCn(1,4,1,128, gstrlineCn4);
//		   	    	break ;
//				   default:break;
//		       }
//			   
//		    break;
//		 }
		break;

   }
  
}
//************************************************************************************************************************



//************************************************************
//ϵͳ�˵�������ʼ��
void FInitPara()
{
   InitSysPara();
   g_mShowMenurowEn=0;
   g_mshowed1=0;
   g_mshowed2=1;
   g_mbacklight=false;
   g_mMenuLangauge=1;
   g_mHandControlTelescope=0;//��Զ��û���ֶ�
   g_mHandControlTelescopetwo=0;//��Զ���Ƿ����ֶ�״̬��0û�ϵ�,1�ϵ�

   g_mCapsLock=false;//�ص�������ʱ�Ĵ�Сд���ƣ�falseСд��true��д
   g_mKeyTurn=0;//�ص�������ʱ1-9�ż��������л�

   g_mTelescopeConType=0;//0û����Զ�����ӣ�1��Զ��Ϊ���ʽ��2��Զ��Ϊ��ƽʽ��3����Զ������

    g_mTelGoHome=false;//��Զ����Ҫ���ڹ���״̬	

	g_mUsedStarNumMax=66;//�ѹ۲��ǵ��������
	g_mUsedStarNum=0;//�Ѿ��۲�����ǵ�����
    g_mUsedStarRa=10.6;//�Ѿ��۲�����ǵĳྭ
	g_mUsedStarDec=63.25;//�Ѿ��۲�����ǵĳ�γ
	g_mSysMenuShowDirect=true;//��ʾ�����ѹ۲�Ĳ˵���ʾ����,ture�ӸղŹ۲���ģ��ǺŴ�С������
                          //��ǰ���ң��ǺŴ�ģ���false�෴
	g_mTelGearErrorRaAlignDirect=0;//��Զ���ྭ�ز�У��ʱѡ�����еķ���,1��2��
    g_mTelGearErrorDecAlignDirect=0;//��Զ���ྭ�ز�У��ʱѡ�����еķ���,1�£�2��

	 g_mTorch=0;//��Զ���ֵ�������0�رգ�1һ������2ȫ��

	g_testtemp=0;//�����ð�����ʾһЩ��Ϣ����ʱ

	 
	 tel_zero_error_num=0;//��Զ������

	  g_mFDown=0;

	  g_mAlignTelStatus=0;
	  g_mhmaxspeed1=false;
	  g_mhmaxspeed2=false;

      g_mHandSpeedAzi=0; //����Զ������ʱ���ֶ���λ�ٶ�
      g_mHandSpeedAlt=0;  //����Զ������ʱ���ֶ��߶��ٶ�


	  g_mObjAlarm_open_reset=0;//0���Ӳ��ڸ�λ״̬��1�����ڸ�λ״̬
	  m_TcpSynEnable=0;//��Զ��ͬ���Ƿ��,1�򿪣�0�ر�
	  m_TcpSynFlash=0;//��Զ��ͬ����ʾ��˸
	  g_mgetimefirst=1;
	  g_mcalpalnet=1;

	  dg_mSkyMapAzi=0;  //SKYMAP��λͬ����
      dg_mSkyMapAlt=0;  //SKYMAP�߶�ͬ���� 
	  g_mhandtrackAzi=0;//���ָ��ʱ����Զ����Ŀ��λ��һ�£��ֶ����ں󣬾Ͳ�һ����
	  g_mhandtrackAlt=0;//���ָ��ʱ����Զ����Ŀ��λ��һ�£��ֶ����ں󣬾Ͳ�һ����

	 m_GuiderRa=0;	  //Ϊ1����-1����Ϊ0�������ྭ��絼���ź�
     m_GuiderDec=0; //Ϊ1����-1����Ϊ0����	 ����γ��絼����

 }
 //************************************************************

 //************************************************************
 //�ྭ����������
 void FRaInputMoveLeft()
 {

      switch(g_mShowMenucolumn)
      {
	     case  6:
           g_mShowMenucolumn=15;
		   break;
		 case  15:
           g_mShowMenucolumn=13;
		   break;
		 case  13:
           g_mShowMenucolumn=12;
		   break;
		 case  12:
           g_mShowMenucolumn=10;
		   break;
	     case  10:
           g_mShowMenucolumn=9;
		   break;
		 case  9:
           g_mShowMenucolumn=7;
		   break;
		 case  7:
           g_mShowMenucolumn=6;
		   break;
		 default:
		   break;
      }

}
 //************************************************************

 //************************************************************
//�ྭ����������
void FRaInputMoveRight()
{
    switch(g_mShowMenucolumn)
      {
		 case  6:
           g_mShowMenucolumn=7;
		   break;
		 case  7:
           g_mShowMenucolumn=9;
		   break;
		 case  9:
           g_mShowMenucolumn=10;
		   break;
		 case  10:
           g_mShowMenucolumn=12;
		   break;
	     case  12:
           g_mShowMenucolumn=13;
		   break;
		 case  13:
           g_mShowMenucolumn=15;
		   break;
		 case  15:
           g_mShowMenucolumn=6;
		   break;
		 default:
		   break;
      }

}
 //************************************************************

 //************************************************************
//��γ����������
void FDecInputMoveLeft()
{
    switch(g_mShowMenucolumn)
      {
	     case  5:
           g_mShowMenucolumn=15;
		   break;
		 case  15:
           g_mShowMenucolumn=13;
		   break;
		 case  13:
           g_mShowMenucolumn=12;
		   break;
		 case  12:
           g_mShowMenucolumn=10;
		   break;
	     case  10:
           g_mShowMenucolumn=9;
		   break;
		 case  9:
           g_mShowMenucolumn=7;
		   break;
		 case  7:
           g_mShowMenucolumn=6;
		   break;
		 case  6:
           g_mShowMenucolumn=5;
		   break;
		 default:
		   break;
      }
} 
 //************************************************************

 //************************************************************
//��γ����������
void FDecInputMoveRight()
{
     switch(g_mShowMenucolumn)
      {
	     case  5:
           g_mShowMenucolumn=6;
		   break;
		 case  6:
           g_mShowMenucolumn=7;
		   break;
		 case  7:
           g_mShowMenucolumn=9;
		   break;
		 case  9:
           g_mShowMenucolumn=10;
		   break;
		 case  10:
           g_mShowMenucolumn=12;
		   break;
	     case  12:
           g_mShowMenucolumn=13;
		   break;
		 case  13:
           g_mShowMenucolumn=15;
		   break;
		 case  15:
           g_mShowMenucolumn=5;
		   break;
		 default:
		   break;
      }
}
  //************************************************************

 //************************************************************
 //�жϳྭ��γ�����Ƿ���ȷ
 void FVerifyRaDecInput()
 {
         
    //�˺�����Ҫ�õ�����ʱ����
   //********************************
   //�ྭ��γ�������ʱ�����������ж������Ƿ���ȷ����ȷ�ŷ��أ�����ȷ����������״̬
   int g_mObjRa_shi_temp,g_mObjRa_fen_temp;//Ŀ��ྭʱ����
   float g_mObjRa_miao_temp;
   int g_mObjDec_du_temp,g_mObjDec_fen_temp;//Ŀ���γ�ȷ���
   float g_mObjDec_miao_temp;
   uint8 i;
   //********************************

      //�ѳྭ��γ�ַ����ȡ����������ʱ������
		g_mObjRa_shi_temp= atoi(&g_sysmenu2900ra[5]);
		g_mObjRa_fen_temp= atoi(&g_sysmenu2900ra[8]);
		g_mObjRa_miao_temp= atof(&g_sysmenu2900ra[11]);

		g_mObjDec_du_temp= atoi(&g_sysmenu2900dec[5]);
		g_mObjDec_fen_temp= atoi(&g_sysmenu2900dec[8]);
		g_mObjDec_miao_temp= atof(&g_sysmenu2900dec[11]);
		//������ʱ�����ж��Ƿ�������ȷ��


		if((g_mObjRa_shi_temp>23)||(g_mObjRa_fen_temp>59)||(g_mObjRa_miao_temp>59.99)||(g_mObjDec_du_temp>89)||(g_mObjDec_fen_temp>59)||(g_mObjDec_miao_temp>59.99))
		{
		   if((g_mObjDec_du_temp>89)||(g_mObjDec_fen_temp>59)||(g_mObjDec_miao_temp>59.99))
		   {
		      g_nsysstatus=SYS_SUB2SUB9DEC;	  //��γ���������ȷ��ϵͳ���ص���γ����״̬
			  g_mShowMenucolumn=5;
		   }
		   
		   if((g_mObjRa_shi_temp>23)||(g_mObjRa_fen_temp>59)||(g_mObjRa_miao_temp>59.99))
		   {
		      g_nsysstatus=SYS_SUB2SUB9RA; //�ྭ���������ȷ��ϵͳ���ص��ྭ����״̬
			  g_mShowMenucolumn=6;

			}

		 }
		 else
		 {	    if(g_mRaDecMode==0)
				{
				   	g_nsysstatus=SYS_MAINSHOW;  //����ྭ��γ���붼��ȷ����ִ�гྭ��γ���벢�˳�
					g_mObjRa_shi=g_mObjRa_shi_temp;
				    g_mObjRa_fen=g_mObjRa_fen_temp;
				    g_mObjRa_miao=g_mObjRa_miao_temp;
					if(g_sysmenu2900dec[4]=='-')
					{
					  g_gObjDec_sign=-1;
					 }
					 else
					{
					   g_gObjDec_sign=1;
					 }
					g_mObjDec_du=g_mObjDec_du_temp;
				    g_mObjDec_fen=g_mObjDec_fen_temp;
				    g_mObjDec_miao=g_mObjDec_miao_temp;
		
		        	g_mObjRa=g_mObjRa_shi+g_mObjRa_fen/60.0+g_mObjRa_miao/3600.0;//�ྭ(0-24Сʱ)
		
			        g_mObjDec=g_mObjDec_du+g_mObjDec_fen/60.0+g_mObjDec_miao/3600.0;//��γ(-90��90��)
		            g_mObjDec=g_gObjDec_sign*g_mObjDec;
					g_mTelStatus=1;
						FPointNewStar(g_mObjRa,g_mObjDec);

                  ////////////////////////////////////////////////////
					g_mTargetType=11;
                    g_mTargetnum=10;
			        WriteRecentTarget(g_mTargetType,g_mTargetnum);
					  
					  cstar[0]=111;

					  for(i=1;i<9;i++)
					  {
					    cstar[i]=g_sysmenu2900NameEn[i+4];
						
					  }
			
			
			          cstar[9]=g_sysmenu2900raEn[5]-48;
					  cstar[10]=g_sysmenu2900raEn[6]-48;
					  cstar[11]=g_sysmenu2900raEn[8]-48;
					  cstar[12]=g_sysmenu2900raEn[9]-48;
					  cstar[13]=g_sysmenu2900raEn[11]-48;
					  cstar[14]=g_sysmenu2900raEn[12]-48;
					  cstar[15]=g_sysmenu2900raEn[14]-48;
			
			
					  cstar[16]=g_sysmenu2900decEn[4];
					  cstar[17]=g_sysmenu2900decEn[5]-48;
					  cstar[18]=g_sysmenu2900decEn[6]-48;
					  cstar[19]=g_sysmenu2900decEn[8]-48;
					  cstar[20]=g_sysmenu2900decEn[9]-48;
					  cstar[21]=g_sysmenu2900decEn[11]-48;
					  cstar[22]=g_sysmenu2900decEn[12]-48;
					  cstar[23]=g_sysmenu2900decEn[14]-48;
					  
					  WriteCustomStar(g_mTargetnum,cstar);



				 }
				 else
				 {
				    g_nsysstatus=SYS_SUB3SUB2_STARRISESET;

					g_mObjRa_shi=g_mObjRa_shi_temp;
				    g_mObjRa_fen=g_mObjRa_fen_temp;
				    g_mObjRa_miao=g_mObjRa_miao_temp;
					if(g_sysmenu2900dec[4]=='-')
					{
					  g_gObjDec_sign=-1;
					 }
					 else
					{
					   g_gObjDec_sign=1;
					 }
					g_mObjDec_du=g_mObjDec_du_temp;
				    g_mObjDec_fen=g_mObjDec_fen_temp;
				    g_mObjDec_miao=g_mObjDec_miao_temp;
		
		        	g_mObjRa=g_mObjRa_shi+g_mObjRa_fen/60.0+g_mObjRa_miao/3600.0;//�ྭ(0-24Сʱ)
		
			        g_mObjDec=g_mObjDec_du+g_mObjDec_fen/60.0+g_mObjDec_miao/3600.0;//��γ(-90��90��)
		            g_mObjDec=g_gObjDec_sign*g_mObjDec;
		
					g_mStarRiseTime=FSRiseSettime(1,g_mObjRa,g_mObjDec,g_mGoto.m_nLongitude,g_mGoto.m_nAtitude, g_mGoto.m_nTimeZone);
					g_mStarTransitTime=FSRiseSettime(2,g_mObjRa,g_mObjDec,g_mGoto.m_nLongitude,g_mGoto.m_nAtitude, g_mGoto.m_nTimeZone);
					g_mStarSetTime=FSRiseSettime(3,g_mObjRa,g_mObjDec,g_mGoto.m_nLongitude,g_mGoto.m_nAtitude, g_mGoto.m_nTimeZone);

				  } 
			 
		}

}
 //************************************************************

 //************************************************************
 //�ྭ��γ��������״̬ʱ�ྭ��γ����ת��ΪҪ��ʾ���ַ���
void FRaDecInputShow()
{
		    //FCalStarEQPos(g_mTelAzi,g_mTelAlt,&g_telra,&g_teldec);
				
			if(g_mAzEq==0)
		   {
					
				 FCalStarEQPos(g_mTelAzi,g_mTelAlt,&g_telra,&g_teldec);		
		
			}
			else
			{
		
					 g_teldec=g_mTelDec;
					 g_telra=FCalSiderealTime(1,false,g_mGoto.m_nLongitude)-g_mTelRa;
					 while(	g_telra>=24)
					 {
					   g_telra=g_telra-24;
					  }
					  while(g_telra<0)
					   {
					    g_telra=g_telra+24;
					   }
	
			}
			 
			 
			  
			g_mObjRa=g_telra;//g_mGoto.m_nRightAscension;
			g_mObjRa_shi=(int)g_mObjRa;//��ƽ���귽λ���ظ�ֵ�ڷ�λ��ʾ
			g_mObjRa_fen=(int)((g_mObjRa-g_mObjRa_shi)*60.0);
			g_mObjRa_miao=(g_mObjRa-g_mObjRa_shi-g_mObjRa_fen/60.0)*3600;


			g_mObjDec=fabs(g_teldec);//fabs(g_mGoto.m_nDeclination);							
			g_mObjDec_du=(int)g_mObjDec;//��ƽ����߶ȷ��ظ�ֵ�ڷ�λ��ʾ
			g_mObjDec_fen=(int)((g_mObjDec-g_mObjDec_du)*60.0);
			g_mObjDec_miao=(g_mObjDec-g_mObjDec_du-g_mObjDec_fen/60.0)*3600;
            if(g_teldec>0)//g_mGoto.m_nDeclination>0)
			{
			  g_gObjDec_sign=1;
			}
			else
			{
			  g_gObjDec_sign=-1;
			}


		if(g_mObjRa_miao<10) //������Ƿ������Ƿ����10��С��10Ҫ�ֱ���ʾ
		{
		   sprintf(g_sysmenu2900ra,"R.a: %02dh%02dm0%2.1fs",g_mObjRa_shi,g_mObjRa_fen,g_mObjRa_miao);
		   sprintf(g_sysmenu2900raEn,"R.a: %02dh%02dm0%2.1fs",g_mObjRa_shi,g_mObjRa_fen,g_mObjRa_miao);	
		 }
	    else
		{
		   sprintf(g_sysmenu2900ra,"R.a: %02dh%02dm%3.1fs",g_mObjRa_shi,g_mObjRa_fen,g_mObjRa_miao);
		   sprintf(g_sysmenu2900raEn,"R.a: %02dh%02dm%3.1fs",g_mObjRa_shi,g_mObjRa_fen,g_mObjRa_miao);		
		}
		 		
	 
		if(g_mObjDec_miao<10)//������Ƿ������Ƿ����10��С��10Ҫ�ֱ���ʾ
		{
		    if(g_gObjDec_sign==-1)
	    	{
		       sprintf(g_sysmenu2900dec,"Dec:-%02d %02d 0%2.1f ",g_mObjDec_du,g_mObjDec_fen,g_mObjDec_miao);
			   sprintf(g_sysmenu2900decEn,"Dec:-%02dd%02dm0%2.1fs",g_mObjDec_du,g_mObjDec_fen,g_mObjDec_miao);
		     }
            else
		    {
		       sprintf(g_sysmenu2900dec,"Dec:+%02d %02d 0%2.1f ",g_mObjDec_du,g_mObjDec_fen,g_mObjDec_miao);
			   sprintf(g_sysmenu2900decEn,"Dec:+%02dd%02dm0%2.1fs",g_mObjDec_du,g_mObjDec_fen,g_mObjDec_miao);
	     	}
		}
	   else
		{
		    if(g_gObjDec_sign==-1)
	    	{
		       sprintf(g_sysmenu2900dec,"Dec:-%02d %02d %3.1f ",g_mObjDec_du,g_mObjDec_fen,g_mObjDec_miao);
			   sprintf(g_sysmenu2900decEn,"Dec:-%02dd%02dm%3.1fs",g_mObjDec_du,g_mObjDec_fen,g_mObjDec_miao);
		     }
            else
		    {
		       sprintf(g_sysmenu2900dec,"Dec:+%02d %02d %3.1f ",g_mObjDec_du,g_mObjDec_fen,g_mObjDec_miao);
			   sprintf(g_sysmenu2900decEn,"Dec:+%02dd%02dm%3.1fs",g_mObjDec_du,g_mObjDec_fen,g_mObjDec_miao);
	     	}
		}

		sprintf(g_sysmenu2900NameEn,"Name:Target0%d",0);

}



 //��ǰ����Զ��λ��
void FGetTelPos()	
{

	   
		if(g_mTelAzi_miao<10) //������Ƿ������Ƿ����10��С��10Ҫ�ֱ���ʾ
		{
		   sprintf(g_sysmenu2900raEn,"Azi:%03dh%02dm0%2.1fs",g_mTelAzi_du,g_mTelAzi_fen,g_mTelAzi_miao);
		   sprintf(g_sysmenu2900ra,"Azi:%03dh%02dm0%2.1fs",g_mTelAzi_du,g_mTelAzi_fen,g_mTelAzi_miao);	
		 }
	    else
		{
	
		   sprintf(g_sysmenu2900raEn,"Azi:%03dh%02dm%2.1fs",g_mTelAzi_du,g_mTelAzi_fen,g_mTelAzi_miao);	
		   sprintf(g_sysmenu2900ra,"Azi:%03dh%02dm0%2.1fs",g_mTelAzi_du,g_mTelAzi_fen,g_mTelAzi_miao);	
		}
		 		
	 
		if(g_mTelAlt_miao<10)//������Ƿ������Ƿ����10��С��10Ҫ�ֱ���ʾ
		{
		    if((g_mTelAlt<0))
	    	{
		       sprintf(g_sysmenu2900decEn,"Alt:-%02dd%02dm%2.1fs",abs(g_mTelAlt_du),abs(g_mTelAlt_fen),fabs(g_mTelAlt_miao));
			   sprintf(g_sysmenu2900dec,"Alt:-%02dd%02dm%2.1fs",abs(g_mTelAlt_du),abs(g_mTelAlt_fen),fabs(g_mTelAlt_miao));
		     }
            else
		    {
		      sprintf(g_sysmenu2900decEn,"Alt:+%02dd%02dm0%2.1fs",g_mTelAlt_du,g_mTelAlt_fen,g_mTelAlt_miao);
			  sprintf(g_sysmenu2900dec,"Alt:+%02dd%02dm0%2.1fs",g_mTelAlt_du,g_mTelAlt_fen,g_mTelAlt_miao);	  
	     	}
		}
	    else
		{
		    if((g_mTelAlt<0))
	    	{
		       	   sprintf(g_sysmenu2900decEn,"Alt:-%02dd%02dm%2.1fs",abs(g_mTelAlt_du),abs(g_mTelAlt_fen),fabs(g_mTelAlt_miao));
				   sprintf(g_sysmenu2900dec,"Alt:-%02dd%02dm%2.1fs",abs(g_mTelAlt_du),abs(g_mTelAlt_fen),fabs(g_mTelAlt_miao));	
		     
			 }

            else
		    {
		        sprintf(g_sysmenu2900decEn,"Alt:+%02dd%02dm%2.1fs",g_mTelAlt_du,g_mTelAlt_fen,g_mTelAlt_miao);
				sprintf(g_sysmenu2900dec,"Alt:+%02dd%02dm%2.1fs",g_mTelAlt_du,g_mTelAlt_fen,g_mTelAlt_miao);
	     	}
		}  
		sprintf(g_sysmenu2900NameEn,"Name:Target0%d",0);
	
}

 //************************************************************

 //************************************************************
//��Զ���ֶ�����
void FHandControlTelescope(uint8  faxis,uint8 fdirect,uint8  sfpeed)
{
      
	   
        uint8 sendnum;
	    uint8 g_mDriveOrder[10];
	    uint8 gOrder[10];
		g_mstartOTAset=1;//����ʱ������Զ���ĳ�ʼָ��
	   g_mhandtrackAzi=0;//���ָ��ʱ����Զ����Ŀ��λ��һ�£��ֶ����ں󣬾Ͳ�һ����
	   g_mhandtrackAlt=0;//���ָ��ʱ����Զ����Ŀ��λ��һ�£��ֶ����ں󣬾Ͳ�һ����

				 //ֹͣ��һ�����˶�

			   gOrder[0]=0x55;
			   gOrder[1]=0xAA;
			   gOrder[2]=0x01;
			   gOrder[3]=0x04;
			   switch(faxis)
			   {  
			      case AXIS_RA:
				   gOrder[4]=33;		
				  break;
				  case AXIS_DEC:
				   gOrder[4]=1;
				  break;
				  case AXIS_AZI:
				  gOrder[4]=97;
				  break;
				  case AXIS_ALT:
				  gOrder[4]=65;
				  break;
				  default:
				  break;
				}
			   switch(fdirect)
			   {
			     case DIRECT_LEFT:	
				 case DIRECT_UP:
				  gOrder[5]=0;
				 break;
				 case DIRECT_RIGHT:
				 case DIRECT_DOWN:
				  gOrder[5]=1;
				 break;
				 default:
				 break;
		
		       }
               gOrder[6]=0;
	           gOrder[7]=0;
			   for(sendnum=0;sendnum<8;sendnum++)
			   {
			     UART1_SentByte(gOrder[sendnum]);
				// FBeep(1);
				}



		//��Ҫ���Ƶ���

	   	if(g_mHandControlTelescope==0)
		{
		      g_mHandControlTelescope=1;
			  FHandPowerTelescope();
//		       if(g_mHandControlTelescopetwo==0)
//			   { 
//			     g_mHandControlTelescope=1;
//			     FHandPowerTelescope();
//				}

 			   g_mDriveOrder[0]=0x55;
			   g_mDriveOrder[1]=0xAA;
			   g_mDriveOrder[2]=0x01;
			   g_mDriveOrder[3]=0x04;
			   switch(faxis)
			   {  
			      case AXIS_RA:
				   g_mDriveOrder[4]=1;		
				  break;
				  case AXIS_DEC:
				   g_mDriveOrder[4]=33;
				  break;
				  case AXIS_AZI:
				  g_mDriveOrder[4]=65;
				  break;
				  case AXIS_ALT:
				  g_mDriveOrder[4]=97;
				  break;
				  default:
				  break;
				}
			   switch(fdirect)
			   {
			     case DIRECT_LEFT:	
				 case DIRECT_UP:
				  g_mDriveOrder[5]=0;
				 break;
				 case DIRECT_RIGHT:
				 case DIRECT_DOWN:
				  g_mDriveOrder[5]=1;
				 break;
				 default:
				 break;
				}


		  //if(sfpeed>g_mHandSpeed1)
		  //{
		     //g_mHandSpeed1=g_mHandSpeed1+1;
		  //}

			//���ʽ�ֶ��ٶ��趨
			if(g_mTelescopeConType==1)
			{
				switch(sfpeed)
				{
				   case HAND_SPEED0:
		                 g_mDriveOrder[6]=0x00;
			             g_mDriveOrder[7]=0x00;
						 g_mTelStatus=0;
				   break;
				   case HAND_SPEED1:
		                 g_mDriveOrder[6]=0x00;
			             g_mDriveOrder[7]=0x05;
						 g_mTelStatus=10;
				   break;
				   case HAND_SPEED2:
		                 g_mDriveOrder[6]=0x00;
						 g_mDriveOrder[7]=0x0A;
						  g_mTelStatus=10;
				   break;
				   case HAND_SPEED3:
		                 g_mDriveOrder[6]=0x00;
			             g_mDriveOrder[7]=0x28;
						  g_mTelStatus=10;
				   break;
				   case HAND_SPEED4:
		                 g_mDriveOrder[6]=0x00;
			             g_mDriveOrder[7]=0xA0;
						  g_mTelStatus=10;
				   break;
				   case HAND_SPEED5:
		                 g_mDriveOrder[6]=0x01;
			             g_mDriveOrder[7]=0x40;
						  g_mTelStatus=10;
				   break;
				   case HAND_SPEED6:
		                 g_mDriveOrder[6]=0x02;
			             g_mDriveOrder[7]=0x80;
						  g_mTelStatus=10;
				   break;
				   case HAND_SPEED7:
		                 g_mDriveOrder[6]=0x05;
			             g_mDriveOrder[7]=0x00;
						  g_mTelStatus=10;
				   break;
				   case HAND_SPEED8:
		                 g_mDriveOrder[6]=0x0A;
			             g_mDriveOrder[7]=0x00;
						  g_mTelStatus=10;
				   break;
				   case HAND_SPEED9:
		                  g_mDriveOrder[6]=0x0A;
			              g_mDriveOrder[7]=0x00;
						  hsendspd1.i=2560;
						  g_mhmaxspeed1=true;
						  g_mhmaxspeedaxis1=g_mDriveOrder[4];
						  g_mhmaxspeeddir1=g_mDriveOrder[5];
						  g_mhmaxspeedchangedirect=1;	
						  
				          g_mhmaxspeed2=false;
				          g_mhmaxspeedaxis2=g_mDriveOrder[4];
			          	  g_mhmaxspeeddir2=g_mDriveOrder[5];
			              hsendspd2.i=0;
					
						  g_mTelStatus=10;
				   break;
				 }
				}
			//��ƽʽ�ֶ��ٶ��趨
			if(g_mTelescopeConType==2)
			{
				switch(sfpeed)
				{
				   case HAND_SPEED0:
		                 g_mDriveOrder[6]=0x00;
			             g_mDriveOrder[7]=0x00;
						  g_mTelStatus=0;
				   break;
				   case HAND_SPEED1:
		                 g_mDriveOrder[6]=0x00;
			             g_mDriveOrder[7]=0x06;
						  g_mTelStatus=10;
				   break;
				   case HAND_SPEED2:
		                 g_mDriveOrder[6]=0x00;
						 g_mDriveOrder[7]=0x0C;
						  g_mTelStatus=10;
				   break;
				   case HAND_SPEED3:
		                 g_mDriveOrder[6]=0x00;
			             g_mDriveOrder[7]=0x30;
						  g_mTelStatus=10;
				   break;
				   case HAND_SPEED4:
		                 g_mDriveOrder[6]=0x00;
			             g_mDriveOrder[7]=0x60;
						  g_mTelStatus=10;
				   break;
				   case HAND_SPEED5:
		                 g_mDriveOrder[6]=0x00;
			             g_mDriveOrder[7]=0xC0;
						  g_mTelStatus=10;
				   break;
				   case HAND_SPEED6:
		                 g_mDriveOrder[6]=0x01;
			             g_mDriveOrder[7]=0x80;
						  g_mTelStatus=10;
				   break;
				   case HAND_SPEED7:
		                 g_mDriveOrder[6]=0x02;
			             g_mDriveOrder[7]=0x1C;
						  g_mTelStatus=10;
				   break;
				   case HAND_SPEED8:
		                 g_mDriveOrder[6]=0x03;
			             g_mDriveOrder[7]=0x38;
						  g_mTelStatus=10;
				   break;
				   case HAND_SPEED9:
		                 g_mDriveOrder[6]=0x03;
			             g_mDriveOrder[7]=0xD4;
						 g_mTelStatus=10;
//						 g_mDriveOrder[6]=0x0A;
//			              g_mDriveOrder[7]=0x00;
//						  hsendspd1.i=2560;
//						  g_mhmaxspeed1=true;
//						  g_mhmaxspeedaxis1=g_mDriveOrder[4];
//						  g_mhmaxspeeddir1=g_mDriveOrder[5];
//						  g_mhmaxspeedchangedirect=1;	
//						  
//			   	         g_mhmaxspeed2=false;
//				         g_mhmaxspeedaxis2=g_mDriveOrder[4];
//				         g_mhmaxspeeddir2=g_mDriveOrder[5];
//				         hsendspd2.i=0;
//					
//						  g_mTelStatus=10;
				   break;
				 }
				}
			   
			   for(sendnum=0;sendnum<8;sendnum++)
			   {
			      UART1_SentByte(g_mDriveOrder[sendnum]);
				// FBeep(1);

				}				

		}
	   

	     
   
}
 //************************************************************

 //************************************************************
 //��Զ������һ�𶯺���
void FHandControlTelescopeTwo(uint8  faxis1,uint8 fdirect1,uint8  sfpeed1,uint8  faxis2,uint8 fdirect2,uint8  sfpeed2)
{
	   
	  
       uint8 sendnum;
	   uint8 g_mDriveOrder[10];	
	   g_mstartOTAset=1;//����ʱ������Զ���ĳ�ʼָ��
	   g_mhandtrackAzi=0;//���ָ��ʱ����Զ����Ŀ��λ��һ�£��ֶ����ں󣬾Ͳ�һ����
	   g_mhandtrackAlt=0;//���ָ��ʱ����Զ����Ŀ��λ��һ�£��ֶ����ں󣬾Ͳ�һ����
	    
		//FBeep(1); 
	   	if(g_mHandControlTelescopetwo==1)
		{
		      
		       
			   //FHandPowerTelescope();
			   //FBeep(3);

 			   g_mDriveOrder[0]=0x55;
			   g_mDriveOrder[1]=0xAA;
			   g_mDriveOrder[2]=0x01;
			   g_mDriveOrder[3]=0x04;
			   //��һ��
			   switch(faxis1)
			   {  
			      case AXIS_RA:
				   g_mDriveOrder[4]=1;		
				  break;
				  case AXIS_DEC:
				   g_mDriveOrder[4]=33;
				  break;
				  case AXIS_AZI:
				  g_mDriveOrder[4]=65;
				  break;
				  case AXIS_ALT:
				  g_mDriveOrder[4]=97;
				  break;
				  default:
				  break;
				}
			   switch(fdirect1)
			   {
			     case DIRECT_LEFT:	
				 case DIRECT_UP:
				  g_mDriveOrder[5]=0;
				 break;
				 case DIRECT_RIGHT:
				 case DIRECT_DOWN:
				  g_mDriveOrder[5]=1;
				 break;
				 default:
				 break;
				}
			//���ʽ�ֶ��ٶ��趨
			if(g_mTelescopeConType==1)
			{
				switch(sfpeed1 )
				{
						   case HAND_SPEED0:
		                 g_mDriveOrder[6]=0x00;
			             g_mDriveOrder[7]=0x00;
						 g_mTelStatus=0;
				   break;
				   case HAND_SPEED1:
		                 g_mDriveOrder[6]=0x00;
			             g_mDriveOrder[7]=0x05;
						 g_mTelStatus=10;
				   break;
				   case HAND_SPEED2:
		                 g_mDriveOrder[6]=0x00;
						 g_mDriveOrder[7]=0x0A;
						  g_mTelStatus=10;
				   break;
				   case HAND_SPEED3:
		                 g_mDriveOrder[6]=0x00;
			             g_mDriveOrder[7]=0x28;
						  g_mTelStatus=10;
				   break;
				   case HAND_SPEED4:
		                 g_mDriveOrder[6]=0x00;
			             g_mDriveOrder[7]=0xA0;
						  g_mTelStatus=10;
				   break;
				   case HAND_SPEED5:
		                 g_mDriveOrder[6]=0x01;
			             g_mDriveOrder[7]=0x40;
						  g_mTelStatus=10;
				   break;
				   case HAND_SPEED6:
		                 g_mDriveOrder[6]=0x02;
			             g_mDriveOrder[7]=0x80;
						  g_mTelStatus=10;
				   break;
				   case HAND_SPEED7:
		                 g_mDriveOrder[6]=0x05;
			             g_mDriveOrder[7]=0x00;
						  g_mTelStatus=10;
				   break;
				   case HAND_SPEED8:
		                 g_mDriveOrder[6]=0x0A;
			             g_mDriveOrder[7]=0x00;
						  g_mTelStatus=10;
				   break;
				   case HAND_SPEED9:
		                  g_mDriveOrder[6]=0x0A;
			              g_mDriveOrder[7]=0x00;
//						  hsendspd1.i=2560;
//						  g_mhmaxspeed1=true;
//						  g_mhmaxspeedaxis1=g_mDriveOrder[4];
//						  g_mhmaxspeeddir1=g_mDriveOrder[5];
//						  g_mhmaxspeedchangedirect=1;	
		
						  g_mTelStatus=10;

//		                  g_mDriveOrder[6]=0x0A;
//			              g_mDriveOrder[7]=0x00;
//						  hsendspd1.i=2560;
//						  g_mhmaxspeed1=true;
//						  g_mhmaxspeedaxis1=g_mDriveOrder[4];
//						  g_mhmaxspeeddir1=g_mDriveOrder[5];
//						  g_mhmaxspeedchangedirect=1;	
//						  
//				          g_mhmaxspeed2=false;
//				          g_mhmaxspeedaxis2=g_mDriveOrder[4];
//			          	  g_mhmaxspeeddir2=g_mDriveOrder[5];
//			              hsendspd2.i=0;
//					
//						  g_mTelStatus=10;
				   break;
				 }
				}
			//��ƽʽ�ֶ��ٶ��趨
			if(g_mTelescopeConType==2)
			{
				switch(sfpeed1 )
				{
				   case HAND_SPEED0:
		                 g_mDriveOrder[6]=0x00;
			             g_mDriveOrder[7]=0x00;
						  g_mTelStatus=0;
				   break;
				   case HAND_SPEED1:
		                 g_mDriveOrder[6]=0x00;
			             g_mDriveOrder[7]=0x06;
						  g_mTelStatus=10;
				   break;
				   case HAND_SPEED2:
		                 g_mDriveOrder[6]=0x00;
						 g_mDriveOrder[7]=0x0C;
						  g_mTelStatus=10;
				   break;
				   case HAND_SPEED3:
		                 g_mDriveOrder[6]=0x00;
			             g_mDriveOrder[7]=0x30;
						  g_mTelStatus=10;
				   break;
				   case HAND_SPEED4:
		                 g_mDriveOrder[6]=0x00;
			             g_mDriveOrder[7]=0x60;
						  g_mTelStatus=10;
				   break;
				   case HAND_SPEED5:
		                 g_mDriveOrder[6]=0x00;
			             g_mDriveOrder[7]=0xC0;
						  g_mTelStatus=10;
				   break;
				   case HAND_SPEED6:
		                 g_mDriveOrder[6]=0x01;
			             g_mDriveOrder[7]=0x80;
						  g_mTelStatus=10;
				   break;
				   case HAND_SPEED7:
		                 g_mDriveOrder[6]=0x02;
			             g_mDriveOrder[7]=0x1C;
						  g_mTelStatus=10;
				   break;
				   case HAND_SPEED8:
		                 g_mDriveOrder[6]=0x03;
			             g_mDriveOrder[7]=0x38;
						  g_mTelStatus=10;
				   break;
				   case HAND_SPEED9:
		                  g_mDriveOrder[6]=0x03;
			             g_mDriveOrder[7]=0xD4;
						  g_mTelStatus=10;
				   break;
				 }
				}
			   
			   for(sendnum=0;sendnum<8;sendnum++)
			   {
			     UART1_SentByte(g_mDriveOrder[sendnum]);
				}

				//�ڶ���
			   switch(faxis2)
			   {  
			      case AXIS_RA:
				   g_mDriveOrder[4]=1;		
				  break;
				  case AXIS_DEC:
				   g_mDriveOrder[4]=33;
				  break;
				  case AXIS_AZI:
				  g_mDriveOrder[4]=65;
				  break;
				  case AXIS_ALT:
				  g_mDriveOrder[4]=97;
				  break;
				  default:
				  break;
				}
			   switch(fdirect2)
			   {
			     case DIRECT_LEFT:	
				 case DIRECT_UP:
				  g_mDriveOrder[5]=0;
				 break;
				 case DIRECT_RIGHT:
				 case DIRECT_DOWN:
				  g_mDriveOrder[5]=1;
				 break;
				 default:
				 break;
				}
			//���ʽ�ֶ��ٶ��趨
			if(g_mTelescopeConType==1)
			{
				switch(sfpeed2 )
				{
				   case HAND_SPEED0:
		                 g_mDriveOrder[6]=0x00;
			             g_mDriveOrder[7]=0x00;
						 g_mTelStatus=0;
				   break;
				   case HAND_SPEED1:
		                 g_mDriveOrder[6]=0x00;
			             g_mDriveOrder[7]=0x05;
						 g_mTelStatus=10;
				   break;
				   case HAND_SPEED2:
		                 g_mDriveOrder[6]=0x00;
						 g_mDriveOrder[7]=0x0A;
						  g_mTelStatus=10;
				   break;
				   case HAND_SPEED3:
		                 g_mDriveOrder[6]=0x00;
			             g_mDriveOrder[7]=0x28;
						  g_mTelStatus=10;
				   break;
				   case HAND_SPEED4:
		                 g_mDriveOrder[6]=0x00;
			             g_mDriveOrder[7]=0xA0;
						  g_mTelStatus=10;
				   break;
				   case HAND_SPEED5:
		                 g_mDriveOrder[6]=0x01;
			             g_mDriveOrder[7]=0x40;
						  g_mTelStatus=10;
				   break;
				   case HAND_SPEED6:
		                 g_mDriveOrder[6]=0x02;
			             g_mDriveOrder[7]=0x80;
						  g_mTelStatus=10;
				   break;
				   case HAND_SPEED7:
		                 g_mDriveOrder[6]=0x05;
			             g_mDriveOrder[7]=0x00;
						  g_mTelStatus=10;
				   break;
				   case HAND_SPEED8:
		                 g_mDriveOrder[6]=0x0A;
			             g_mDriveOrder[7]=0x00;
						  g_mTelStatus=10;
				   break;
				   case HAND_SPEED9:
		                  g_mDriveOrder[6]=0x0A;
			              g_mDriveOrder[7]=0x00;
//						  hsendspd2.i=2560;
//						  g_mhmaxspeed2=true;
//						  g_mhmaxspeedaxis2=g_mDriveOrder[4];
//						  g_mhmaxspeeddir2=g_mDriveOrder[5];
//						  g_mhmaxspeedchangedirect=1;
						  g_mTelStatus=10;

//		                  g_mDriveOrder[6]=0x0A;
//			              g_mDriveOrder[7]=0x00;
//						  hsendspd1.i=2560;
//						  g_mhmaxspeed1=true;
//						  g_mhmaxspeedaxis1=g_mDriveOrder[4];
//						  g_mhmaxspeeddir1=g_mDriveOrder[5];
//						  g_mhmaxspeedchangedirect=1;	
//						  
//				          g_mhmaxspeed2=false;
//				          g_mhmaxspeedaxis2=g_mDriveOrder[4];
//			          	  g_mhmaxspeeddir2=g_mDriveOrder[5];
//			              hsendspd2.i=0;
//					
//						  g_mTelStatus=10;
				   break;
				 }
				}
			//��ƽʽ�ֶ��ٶ��趨
			if(g_mTelescopeConType==2)
			{
				switch(sfpeed2)
				{
				   case HAND_SPEED0:
		                 g_mDriveOrder[6]=0x00;
			             g_mDriveOrder[7]=0x00;
						  g_mTelStatus=0;
				   break;
				   case HAND_SPEED1:
		                 g_mDriveOrder[6]=0x00;
			             g_mDriveOrder[7]=0x06;
						  g_mTelStatus=10;
				   break;
				   case HAND_SPEED2:
		                 g_mDriveOrder[6]=0x00;
						 g_mDriveOrder[7]=0x0C;
						  g_mTelStatus=10;
				   break;
				   case HAND_SPEED3:
		                 g_mDriveOrder[6]=0x00;
			             g_mDriveOrder[7]=0x30;
						  g_mTelStatus=10;
				   break;
				   case HAND_SPEED4:
		                 g_mDriveOrder[6]=0x00;
			             g_mDriveOrder[7]=0x60;
						  g_mTelStatus=10;
				   break;
				   case HAND_SPEED5:
		                 g_mDriveOrder[6]=0x00;
			             g_mDriveOrder[7]=0xC0;
						  g_mTelStatus=10;
				   break;
				   case HAND_SPEED6:
		                 g_mDriveOrder[6]=0x01;
			             g_mDriveOrder[7]=0x80;
						  g_mTelStatus=10;
				   break;
				   case HAND_SPEED7:
		                 g_mDriveOrder[6]=0x02;
			             g_mDriveOrder[7]=0x1C;
						  g_mTelStatus=10;
				   break;
				   case HAND_SPEED8:
		                 g_mDriveOrder[6]=0x03;
			             g_mDriveOrder[7]=0x38;
						  g_mTelStatus=10;
				   break;
				   case HAND_SPEED9:
		                 g_mDriveOrder[6]=0x03;
			             g_mDriveOrder[7]=0xD4;
						  g_mTelStatus=10;
				   break;
				 }
				}
			   
			   for(sendnum=0;sendnum<8;sendnum++)
			   {
			     UART1_SentByte(g_mDriveOrder[sendnum]);
				}
		}
		else
		{		  
		   g_mHandControlTelescopetwo=1;
		   if(g_mHandControlTelescope==0)
		   {
		      // FBeep(1);
			   UART1_SentByte(0x55);
			   UART1_SentByte(0xAA);
			   UART1_SentByte(0x01);
			   UART1_SentByte(0x01);
			   UART1_SentByte(0xFF);
		   }
		}
			     

}
  //************************************************************

 //************************************************************
//ֹͣ��Զ���˶�
void FHandStopTelescope()
{
     
     if((g_mHandControlTelescope==1)||(g_mHandControlTelescopetwo==1))
	 {

		if(g_mHandControlTelescopetwo==1)
		{
		   UART1_SentByte(0x55);
	 	   UART1_SentByte(0xAA);
	  	   UART1_SentByte(0x01);
	 	   UART1_SentByte(0x01);
	  	   UART1_SentByte(0x00);
		   g_mTelStatus=0;
		}

		if(g_mHandControlTelescope==1)
		{	if(g_mTelescopeConType==2)
		    {
				   UART1_SentByte(0x55);
			 	   UART1_SentByte(0xAA);
			  	   UART1_SentByte(0x01);
			 	   UART1_SentByte(0x01);
			  	   UART1_SentByte(0x00);
				   g_mTelStatus=0;
			}
			else
			{
				 if(g_mHandSpeed!=9)
				 {
				   
			       UART1_SentByte(0x55);
			 	   UART1_SentByte(0xAA);
			  	   UART1_SentByte(0x01);
			 	   UART1_SentByte(0x01);
			  	   UART1_SentByte(0x00);
				   g_mTelStatus=0;
				  }
				  else
				  {
				   //FBeep(1);
				     //g_mhmaxspeed1=false;
				     //g_mhmaxspeed2=false;
				     if(hsendspd1.i>=4800)
					  { 
					     hsendspd1.i=4700;
					  }
		
				 	 g_mhmaxspeedchangedirect=-4; 
				  }
			  }
		  }


	     if(g_mHandControlTelescope==1)
		 {
	        g_mHandControlTelescope=0;
		  }
		  if(g_mHandControlTelescopetwo==1)
		  {
		    g_mHandControlTelescopetwo=0;
		  }
		  //while(g_mHandSpeed>0)
		  //{
		     //g_mHandSpeed1=g_mHandSpeed1+1;
		  //}
		 // g_mHandSpeed1=0;
		 // FBeep(2);
		// mtest0=g_mHandSpeed
	
	

		

	 }
	 

}
 //************************************************************

 //************************************************************
 //��Զ��������
void FHandPowerTelescope()
{
	  UART1_SentByte(0x55);
	  UART1_SentByte(0xAA);
	  UART1_SentByte(0x01);
	  UART1_SentByte(0x01);
	  UART1_SentByte(0xFF);	 
}

 //************************************************************

 //************************************************************
//��ȡ��Զ��λ��
double FGetTelescopePos(uint8 faxis) 
{	
          int m_npos1;
	 int m_npos2; 
	 uint8 m_npos3;
	 double m_nTelescopePos;
	 uint8 i;

	 rcv_neworder1 =0;
	 UART1_SentByte(0x55);
	 UART1_SentByte(0xAA);
	 UART1_SentByte(0x01);
	 UART1_SentByte(1);
     switch(faxis)
	   {  
	      case AXIS_RA:
	  	   UART1_SentByte(4);		
		  break;
		  case AXIS_DEC:
	  	   UART1_SentByte(36);
		  break;
		  case AXIS_AZI:
	  	   UART1_SentByte(68);
		  break;
		  case AXIS_ALT:
	  	  UART1_SentByte(100);
		  break;
		  default:
		  break;
		}
	  rcv_neworder1 =0;
	  delay(2);	
	  i=20;
	 if(g_mTelescopeConType)
	 {
		 while ((!rcv_neworder1)&&(i>2))
		 {
		    MenuDelay(5);
			i--;	
	     }
	 }
	 
	 	
	if(rcv_neworder1==1)
	{
      switch(faxis)
	   {  
	      case AXIS_RA:
	  	       if(rcv_databuf1[0]==4)
			   {  		      
				  	position.ub[3]=rcv_databuf1[2];
					position.ub[2]=rcv_databuf1[3];
					position.ub[1]=rcv_databuf1[4];
				    m_nTelescopePos=position.i;
				    g_mTelRaUtr1=m_nTelescopePos*RA_RATIO;
					
						
			   }		
		  break;
		  case AXIS_DEC:
	  	      if(rcv_databuf1[0]==36)
			   {  
			     	position.ub[3]=rcv_databuf1[2];
					position.ub[2]=rcv_databuf1[3];
					position.ub[1]=rcv_databuf1[4];
				    m_nTelescopePos=position.i;
				    g_mTelDecUtr1=m_nTelescopePos*DEC_RATIO;
							
			   }		 
		  break;
		  case AXIS_AZI:
	  	      if(rcv_databuf1[0]==68)
			   {
			       	position.ub[3]=rcv_databuf1[2];
					position.ub[2]=rcv_databuf1[3];
					position.ub[1]=rcv_databuf1[4];
				    m_nTelescopePos=position.i;
				    g_mTelAziUtr1=m_nTelescopePos*AZI_RATIO;
					g_mTelAziUtr1=g_mTelAziUtr1;
				 
			   }
		  break;
		  case AXIS_ALT:
	  	      if(rcv_databuf1[0]==100)
			   {
			       	position.ub[3]=rcv_databuf1[2];
					position.ub[2]=rcv_databuf1[3];
					position.ub[1]=rcv_databuf1[4];
				    m_nTelescopePos=position.i;
				    g_mTelAltUtr1=m_nTelescopePos*ALT_RATIO;
				  }
		  break;
		  default:
		  break;
		}	
	    rcv_neworder1=0;
	} 
      
}

 //************************************************************

 //************************************************************
 //��ȡ��絼����Ϣ
void FGetAutoGuider() 
{	

	 uint8 i;
	  //m_GuiderRa=0;	  //Ϊ1����-1����Ϊ0�������ྭ��絼���ź�
	  //m_GuiderDec=0; //Ϊ1����-1����Ϊ0����	 ����γ��絼����

	 rcv_neworder1 =0;

	 UART1_SentByte(0x55);
	 UART1_SentByte(0xAA);
	 UART1_SentByte(0x01);
	 UART1_SentByte(1);  
	 UART1_SentByte(129);
	
	 rcv_neworder1 =0;
	 
	 i=10;
	 while ((!rcv_neworder1)&&(rcv_neworder1==0))
	 {
	    delay(1);
		i--;
	}
	

	if(rcv_neworder1==1)
	{
     
	  	      if(rcv_databuf1[0]==129)
			   {
			       //LCDRfrsh();

					rcv_databuf1[1]=~(rcv_databuf1[1]);

			       
					if((rcv_databuf1[1]&0x01)==1)
					{ 
                      m_GuiderRa=1;	  //Ϊ1����-1����Ϊ0�������ྭ��絼���ź�
					  //DispEn(0,3,1,22,"RA-(W)                  ");

					 // DispEn(0,2,1,1,"W");
					 }
					if((rcv_databuf1[1]&0x08)==8)
					{ 
                      m_GuiderRa=-1;	  //Ϊ1����-1����Ϊ0�������ྭ��絼���ź�
					  //DispEn(0,3,1,22,"RA+(E)                        ");
					  //DispEn(0,2,1,1,"E");
					 }
					 if((rcv_databuf1[1]&0x09)==9)
					{ 
                      //m_GuiderRa=0;	  //Ϊ1����-1����Ϊ0�������ྭ��絼���ź�
					  //DispEn(0,3,1,22,"RA0                        ");
					  //DispEn(0,2,1,1,"0");
					 }



					 if((rcv_databuf1[1]&0x02)==2)
					{ 
                      m_GuiderDec=1;	  //Ϊ1����-1����Ϊ0�������ྭ��絼���ź�
					   //DispEn(0,5,1,22,"Dec-(S)                  ");
					   //DispEn(0,2,2,1,"S");
					 }
					 if((rcv_databuf1[1]&0x04)==4)
					{ 
                      m_GuiderDec=-1;	  //Ϊ1����-1����Ϊ0�������ྭ��絼���ź�
					   //DispEn(0,5,1,22,"Dec+(N)                  ");
					   //DispEn(0,2,2,1,"N");
					 }

					 if((rcv_databuf1[1]&0x06)==6)
					{ 
                      //m_GuiderDec=0;	  //Ϊ1����-1����Ϊ0�������ྭ��絼���ź�
					  // DispEn(0,5,1,22,"Dec0                  ");
					  //DispEn(0,2,2,1,"0");
					 }
              
			   }
			 
			    		 
	
	    rcv_neworder1=0;
	} 
	 
     
} 
  //************************************************************

 //************************************************************
//�Զ�������ٶ�����������
void FRaTrackSpeedInputMoveLeft()
{
    switch(g_mShowMenucolumn)
      {
	     case  1:     
           g_mShowMenucolumn=6;
		   break;
		 case  6:     
           g_mShowMenucolumn=5;
		   break;
		 case  5:
           g_mShowMenucolumn=3;
		   break;
		 case  3:
           g_mShowMenucolumn=2;
		   break;
		 case  2:
           g_mShowMenucolumn=1;
		   break;
		 default:
		   break;
      }
} 
 //************************************************************

 //************************************************************
//�Զ�������ٶ�����������
void FRaTrackSpeedInputMoveRight()
{
     switch(g_mShowMenucolumn)
      {
	     case  1:
           g_mShowMenucolumn=2;
		   break;
		 case  2:
           g_mShowMenucolumn=3;
		   break;
		 case  3:
           g_mShowMenucolumn=5;
		   break;
		 case  5:
           g_mShowMenucolumn=6;
		   break;
		case  6:
           g_mShowMenucolumn=1;
		   break;
//		 case  5:
//           g_mShowMenucolumn=7;
//		   break;
//	     case  7:
//           g_mShowMenucolumn=8;
//		   break;
//		 case  8:
//           g_mShowMenucolumn=1;
//		   break;
//		 case  9:
//           g_mShowMenucolumn=1;
//		   break;
		 default:
		   break;
      }
}
 //************************************************************

 //************************************************************
//�Ǳ���Ҽ��ٶȼ�
void FFindObjectAccAdd() //�����Ǳ���ٶȵ�1,10,100,1000,10000;
{
    switch( g_mFindObjectAcc)
    {
    case 1:
	 g_mFindObjectAcc=10;
	 break;
	case 10:
	 g_mFindObjectAcc=100;
	 break;
	case 100:
	 g_mFindObjectAcc=1000;
	 break;
	case 1000:
	 g_mFindObjectAcc=10000;
	 break;
     default:
	 break;
	 }
}
 //************************************************************

 //************************************************************
//�Ǳ���Ҽ��ٶȼ�
void FFindObjectAccDec() //�����Ǳ���ٶȵ�1,10,100,1000,10000;
{
    switch( g_mFindObjectAcc)
    {
    case 10000:
	 g_mFindObjectAcc=1000;
	 break;
	case 1000:
	 g_mFindObjectAcc=100;
	 break;
	case 100:
	 g_mFindObjectAcc=10;
	 break;
	case 10:
	 g_mFindObjectAcc=1;
	 break;
     default:
	 break;
	 }
}
  //************************************************************

 //************************************************************
//ʱ����������������
void FDateTimeInputMoveRight()
{

       switch(g_mdatetime)
	   {
	       case 0: 
		       switch(g_mShowMenucolumn	)
			   {
			      case 1:
				     g_mShowMenucolumn=2;
				  break;
				  case 2:
				     g_mShowMenucolumn=3;
				  break;
				  case 3:
				     g_mShowMenucolumn=4;
				  break;

				  case 4:
				     g_mShowMenucolumn=6;
				  break;

				  case 6:
				     g_mShowMenucolumn=7;
				  break;
                  
				  case 7:
				     g_mShowMenucolumn=9;
				  break;
				  case 9:
				     g_mShowMenucolumn=10; 
				  break;

				  case 10:
				     g_mShowMenucolumn=1;
				  break;

				  default:
				  break;
			   }
		   break;
		   case 1:
		   switch(g_mShowMenucolumn	)
			   {
			      case 1:
				     g_mShowMenucolumn=2;
				  break;
				  case 2:
				     g_mShowMenucolumn=4;
				  break;
				  case 4:
				     g_mShowMenucolumn=5;
				  break;

				  case 5:
				     g_mShowMenucolumn=7;
				  break;

				  case 7:
				     g_mShowMenucolumn=8;
				  break;
                  
				  case 8:
				     g_mShowMenucolumn=1;
				  break;
				
				  default:
				  break;
			   }
		   break;
		   default:
		   break;
	   }
 }

  //************************************************************

 //************************************************************
 //ʱ����������������
void FDateTimeInputMoveLeft()
{

       switch(g_mdatetime)
	   {
	       case 0: 
		       switch(g_mShowMenucolumn	)
			   {
			      case 1:
				     g_mShowMenucolumn=10;
				  break;
				  case 10:
				     g_mShowMenucolumn=9;
				  break;
				  case 9:
				     g_mShowMenucolumn=7;
				  break;

				  case 7:
				     g_mShowMenucolumn=6;
				  break;

				  case 6:
				     g_mShowMenucolumn=4;
				  break;
                  
				  case 4:
				     g_mShowMenucolumn=3;
				  break;
				  case 3:
				     g_mShowMenucolumn=2; 
				  break;

				  case 2:
				     g_mShowMenucolumn=1;
				  break;

				  default:
				  break;
			   }
		   break;
		   case 1:
		   switch(g_mShowMenucolumn	)
			   {
			      case 1:
				     g_mShowMenucolumn=8;
				  break;
				  case 8:
				     g_mShowMenucolumn=7;
				  break;
				  case 7:
				     g_mShowMenucolumn=5;
				  break;

				  case 5:
				     g_mShowMenucolumn=4;
				  break;

				  case 4:
				     g_mShowMenucolumn=2;
				  break;
                  
				  case 2:
				     g_mShowMenucolumn=1;
				  break;
				
				  default:
				  break;
			   }
		   break;
		   default:
		   break;
	   }
 }
  //************************************************************

 //************************************************************
 //����ϵͳʱ��
 uint8 FSetSysTime()
 {
  uint8 mtemp;
  uint16 myear;
  uint8 mmonth,mday,mhour,mminute,msecond;
   
   mtemp=1;
//   myear=2012;
//   mmonth=12;
//   mday=12;
//   mhour=12;
//   mminute=12;
//   msecond=12;


  myear=atoi(&g_sysmenu4100date[0]);
  mmonth=atoi(&g_sysmenu4100date[5]);
  if((mmonth>12)||( mmonth==0))
  {
    return  0;
  }
  mday=atoi(&g_sysmenu4100date[8]);
  switch (mmonth)
  {
     case 1:
	 case 3:
	 case 5:
	 case 7:
	 case 8:
	 case 10:
	 case 12:
	   if(mday>31)
	   {
	      mtemp=0;
		}
	   break;
	 case 2:
	 if(mday>29)
	   {
	      mtemp=0;
		}
	 break;

	 case 4:
	 case 6:
	 case 9:
	 case 11:
	   if(mday>30)
	   {
	      mtemp=0;
		}
	   break;
	 default :
	 break;
   }
   if(mday<1)
   {
     mtemp=0;
   }
   if(mtemp==0)
   {
     return  0;
   }

  mhour=atoi(&g_sysmenu4100time[0]);
  mminute=atoi(&g_sysmenu4100time[3]);
  msecond=atoi(&g_sysmenu4100time[6]);

   if((mhour>23)||(mminute>59)||(msecond>59))
   {
      return  0;
	}		 

  
	CCR = 0x10;				    // ��ͣRTC
	//MenuDelay(100);
	YEAR = myear;				// ������
	MONTH = mmonth;				    // ������
	DOM = mday;				    // ������
	//DOW = 5;					// ��������
	HOUR = mhour;					// ����Сʱ
	MIN = mminute;					// ���÷���
	SEC = msecond;					// ������
	//MenuDelay(100);
	CCR = 0x11;				    // ����RTC
	return  1;
 }
  //************************************************************

 //************************************************************
 //�ص�����������
 void  FSiteInputRight()
 {
	 switch(g_mMySiteOperator)
				{
				   case 1:
				   case 3:
			 	    switch(g_mMySiteShowMode)
					{
					  case 0:
					       if(g_mShowMenucolumn<14)
						   {
					          g_mShowMenucolumn++;
						   }
						   else
						   {
				   		      g_mShowMenucolumn=7;
				         	}
					  break;
					  case 1:
					        switch(	g_mShowMenucolumn)
							{
							   case 7:
							        g_mShowMenucolumn=8;
									break;
								case 8:
							        g_mShowMenucolumn=9;
									break;
								case 9:
							        g_mShowMenucolumn=10;
									break;
								case 10:
							        g_mShowMenucolumn=12;
									break;
								case 12:
							        g_mShowMenucolumn=13;
									break;
								case 13:
							        g_mShowMenucolumn=7;
									break;
								default:
								break ;
							}
					  break;
					  case 2:
					      switch(g_mShowMenucolumn)
							{
							   case 7:
							        g_mShowMenucolumn=8;
									break;
								case 8:
							        g_mShowMenucolumn=9;
									break;
								case 9:
							        g_mShowMenucolumn=11;
									break;
								case 11:
							        g_mShowMenucolumn=12;
									break;
								case 12:
							        g_mShowMenucolumn=7;
									break;
								default:
								break ;
							}
					     
					  break;
					   case 3:
					      switch(g_mShowMenucolumn)
							{
							   case 7:
							        g_mShowMenucolumn=8;
									break;
								case 8:
							        g_mShowMenucolumn=9;
									break;
								case 9:
							        g_mShowMenucolumn=7;
									break;
								default:
								break ;
							}
					    
					  break;
					  case 4:
					     switch(g_mShowMenucolumn)
							{
							   case 7:
							        g_mShowMenucolumn=8;
									break;
								case 8:
							        g_mShowMenucolumn=9;
									break;
								case 9:
							        g_mShowMenucolumn=10;
									break;
								case 10:
							        g_mShowMenucolumn=7;
									break;
								default:
								break ;
							}
					   
					  break;
					  default:
					  break;
					}
				break;
			default:
			break;
		}
 }
  //************************************************************

 //************************************************************
 //�ص�����������
 void  FSiteInputLeft()
 {
	   switch(g_mMySiteOperator)
				{
				   case 1:
				   case 3:
			 	    switch(g_mMySiteShowMode)
					{
					  case 0:
					       if(g_mShowMenucolumn>7)
						   {
					          g_mShowMenucolumn--;
						   }
						   else
						   {
						      g_mShowMenucolumn=14;
						 	}
					  		break;
					  case 1:
					        switch(	g_mShowMenucolumn)
							{
							   case 7:
							        g_mShowMenucolumn=13;
									break;
								case 13:
							        g_mShowMenucolumn=12;
									break;
								case 12:
							        g_mShowMenucolumn=10;
									break;
								case 10:
							        g_mShowMenucolumn=9;
									break;
								case 9:
							        g_mShowMenucolumn=8;
									break;
								case 8:
							        g_mShowMenucolumn=7;
									break;
								default:
								break ;
							}
					    
					  break;
					  case 2:
					      switch(	g_mShowMenucolumn)
							{
							   case 7:
							        g_mShowMenucolumn=12;
									break;
								case 12:
							        g_mShowMenucolumn=11;
									break;
								case 11:
							        g_mShowMenucolumn=9;
									break;
								case 9:
							        g_mShowMenucolumn=8;
									break;
								case 8:
							        g_mShowMenucolumn=7;
									break;
								default:
								break ;
							}
					     
					  break;
					   case 3:
					     switch(g_mShowMenucolumn)
							{
							   case 7:
							        g_mShowMenucolumn=9;
									break;
								case 9:
							        g_mShowMenucolumn=8;
									break;
								case 8:
							        g_mShowMenucolumn=7;
									break;
								default:
								break ;
							}
					    
					  break;
					  case 4:
					     switch(g_mShowMenucolumn)
							{
							   case 7:
							        g_mShowMenucolumn=10;
									break;
								case 10:
							        g_mShowMenucolumn=9;
									break;
								case 9:
							        g_mShowMenucolumn=8;
									break;
								case 8:
							        g_mShowMenucolumn=7;
									break;
								default:
								break ;
							}
					  break;
					  default:
					  break;
					}
				break;
			default:
			break;
		}
 }
  //************************************************************

 //************************************************************
 //�Զ���ص����뺯��
void  FSiteInput(uint8  num)
{
    char  sc;
	char  ss[10];
	uint8 mtemp;
	if(g_mCapsLock)//�ص�������ʱ�Ĵ�Сд���ƣ�falseСд��true��д
	{
	   mtemp=5;
	}
	else
	{
	   mtemp=0;
	} 
	switch(num)
	{
		case  0:
	    	sc='0';
		   	ss[0]='0';
		   	ss[1]='0';
		   	ss[2]='0';
		   	ss[3]='0';
		   	ss[4]='0';
		   	ss[5]='0';
		   	ss[6]='0';
		   	ss[7]='0';
			ss[8]='0';
		   	ss[9]='0';
	   		break;
	     case  1:
	    	sc='1';
		    ss[0]='1';
		   	ss[1]='1';
		   	ss[2]='1';
		   	ss[3]='1';
		   	ss[4]='1';
		   	ss[5]='1';
		   	ss[6]='1';
		   	ss[7]='1';
			ss[8]='1';
		   	ss[9]='1';
	   		break;
	    case  2:
	       	sc='2';
		   	ss[0]='2';
		   	ss[1]='a';
		   	ss[2]='b';
		   	ss[3]='c';
		   	ss[4]=' ';
		   	ss[5]='2';
		   	ss[6]='A';
		   	ss[7]='B';
			ss[8]='C';
		   	ss[9]=' ';
	   		break;
		case  3:
	        sc='3';
		   	ss[0]='3';
		   	ss[1]='d';
		   	ss[2]='e';
		   	ss[3]='f';
		   	ss[4]=' ';
		   	ss[5]='3';
		   	ss[6]='D';
		   	ss[7]='E';
			ss[8]='F';
		   	ss[9]=' ';
	   		break;
	    case  4:
	       	sc='4';
		   	ss[0]='4';
		   	ss[1]='g';
		   	ss[2]='h';
		   	ss[3]='i';
		   	ss[4]=' ';
		   	ss[5]='4';
		   	ss[6]='G';
		   	ss[7]='H';
			ss[8]='I';
		   	ss[9]=' ';
	    	break;
		case  5:
	       	sc='5';
		   	ss[0]='5';
		   	ss[1]='j';
		   	ss[2]='k';
		   	ss[3]='l';
		   	ss[4]=' ';
		   	ss[5]='5';
		   	ss[6]='J';
		   	ss[7]='K';
			ss[8]='L';
		   	ss[9]=' ';
	   		break;
	   	case  6:
	        sc='6';
		   	ss[0]='6';
		   	ss[1]='m';
		   	ss[2]='n';
		   	ss[3]='o';
		   	ss[4]=' ';
		   	ss[5]='6';
		   	ss[6]='M';
		   	ss[7]='N';
			ss[8]='O';
		   	ss[9]=' ';
	   		break;
	    case  7:
	       	sc='7';
		   	ss[0]='7';
		   	ss[1]='p';
		   	ss[2]='q';
		   	ss[3]='r';
		   	ss[4]='s';
		   	ss[5]='7';
		   	ss[6]='P';
		   	ss[7]='Q';
			ss[8]='R';
		   	ss[9]='S';
	   		break;
	   	case  8:
	       	sc='8';
		   	ss[0]='8';
		   	ss[1]='t';
		   	ss[2]='u';
		   	ss[3]='v';
		   	ss[4]=' ';
		   	ss[5]='8';
		   	ss[6]='T';
		   	ss[7]='U';
			ss[8]='V';
		   	ss[9]=' ';
	   		break;
	   	case  9:
	       	sc='9';
		   	ss[0]='9';
		   	ss[1]='w';
		   	ss[2]='x';
		   	ss[3]='y';
		   	ss[4]='z';
		   	ss[5]='2';
		   	ss[6]='W';
		   	ss[7]='X';
			ss[8]='Y';
		   	ss[9]='Z';
	   		break;
		default:
	   		break;
	}
	switch(g_mMySiteOperator)
	{
		case 1:
		case 3:
		switch(g_mMySiteShowMode)
		{
			case 0:
				g_sysmenu4300sitename[g_mShowMenucolumn-1]=ss[g_mKeyTurn+mtemp];//�ص�������
				g_sysmenu4300sitenameEn[g_mShowMenucolumn-1]=ss[g_mKeyTurn+mtemp];//�ص�������   
				if(g_mKeyTurn<4)
				{
					g_mKeyTurn++;
				}
				else
				{
					g_mKeyTurn=0;
				}

					  break;
					  case 1:
						if(	g_mShowMenucolumn!=7)
						{
				  	       g_sysmenu4300sitelon[g_mShowMenucolumn-1]=sc;//�ص㾭������
						   g_sysmenu4300sitelonEn[g_mShowMenucolumn-1]=sc;//�ص㾭������
						}
						else  if(g_sysmenu4300sitelon[g_mShowMenucolumn-1]=='E'	)
						{
						  g_sysmenu4300sitelon[g_mShowMenucolumn-1]='W';//�ص㾭������
						  g_sysmenu4300sitelonEn[g_mShowMenucolumn-1]='W';//�ص㾭������
						}
						else
						{
					    	g_sysmenu4300sitelon[g_mShowMenucolumn-1]='E';//��γ������
							g_sysmenu4300sitelonEn[g_mShowMenucolumn-1]='E';//��γ������
			
						}
						//������ɺ�������
	                 	FSiteInputRight();		    
					  break;
					  case 2:
					  	if(	g_mShowMenucolumn!=7)
						{
				  	       g_sysmenu4300sitelat[g_mShowMenucolumn-1]=sc;//�ص�γ������
						   g_sysmenu4300sitelatEn[g_mShowMenucolumn-1]=sc;//�ص�γ������
						}
						else  if(g_sysmenu4300sitelat[g_mShowMenucolumn-1]=='N'	)
						{
						  g_sysmenu4300sitelat[g_mShowMenucolumn-1]='S';//�ص�γ������
						  g_sysmenu4300sitelatEn[g_mShowMenucolumn-1]='S';//�ص�γ������
						}
						else
						{
					    	g_sysmenu4300sitelat[g_mShowMenucolumn-1]='N';//��γ������
							g_sysmenu4300sitelatEn[g_mShowMenucolumn-1]='N';//��γ������
			
						}
					    //������ɺ�������
	                 	FSiteInputRight();  				     
					  break;
					  case 3: 
					  if(	g_mShowMenucolumn!=7)
						{
				  	       g_sysmenu4300sitezone[g_mShowMenucolumn-1]=sc;//�ص�ʱ������
						   g_sysmenu4300sitezoneEn[g_mShowMenucolumn-1]=sc;//�ص�ʱ������
						}
						else  if(g_sysmenu4300sitezone[g_mShowMenucolumn-1]=='E'	)
						{
						  g_sysmenu4300sitezone[g_mShowMenucolumn-1]='W';//�ص�ʱ������
						  g_sysmenu4300sitezoneEn[g_mShowMenucolumn-1]='W';//�ص�ʱ������
						}
						else
						{
					    	g_sysmenu4300sitezone[g_mShowMenucolumn-1]='E';//�ص�ʱ������
							g_sysmenu4300sitezoneEn[g_mShowMenucolumn-1]='E';//�ص�ʱ������
			
						}
						//������ɺ�������
	                 	FSiteInputRight();
					  break;

		       	  case 4:
					 
				  	   g_sysmenu4300sitealt[g_mShowMenucolumn-1]=sc;//�ص㺣������
					  g_sysmenu4300sitealtEn[g_mShowMenucolumn-1]=sc;//�ص㺣������
						//������ɺ�������
	                 	FSiteInputRight();
					  break;
					  default:
					  break;
					}
				break;
			default:
			break;
		}	
}
  //************************************************************

 //************************************************************
 //��������������
 void FWeatherInputRight()
 {
//	  switch(g_mWeatherShowMode	)
//	  {
//	     case 0	:
//		     if(g_mShowMenucolumn<8)
//			{
//			  g_mShowMenucolumn++;
//			 }
//			 else
//			 {
//			    g_mShowMenucolumn=6;
//			  }
//		 break;
//		 case 1:
//		 if(g_mShowMenucolumn<7)
//			{
//			  g_mShowMenucolumn++;
//			 }
//			 else
//			 {
//			    g_mShowMenucolumn=6;
//			  }
//		 break;
//		 case 2:
//		  if(g_mShowMenucolumn<9)
//			{
//			  g_mShowMenucolumn++;
//			 }
//			 else
//			 {
//			    g_mShowMenucolumn=6;
//			  }
//		 break;
//		 default :
//		 break;
//	}
 }
 //************************************************************

 //************************************************************
 //��������������
 void FWeatherInputLeft()
 {
//	  switch(g_mWeatherShowMode	)
//	  {
//	     case 0	:
//		     if(g_mShowMenucolumn>6)
//			{
//			  g_mShowMenucolumn--;
//			 }
//			 else
//			 {
//			    g_mShowMenucolumn=8;
//			  }
//		 break;
//		 case 1:
//		  if(g_mShowMenucolumn>6)
//			{
//			  g_mShowMenucolumn--;
//			 }
//			 else
//			 {
//			    g_mShowMenucolumn=7;
//			  }
//		 break;
//		 case 2:
//		   if(g_mShowMenucolumn>6)
//			{
//			  g_mShowMenucolumn--;
//			 }
//			 else
//			 {
//			    g_mShowMenucolumn=9;
//			  }
//		 break;
//		 default :
//		 break;
//	}
 }
  //************************************************************

 //************************************************************
  //�������뺯��
 void  FWeatherInput(uint8  num)
 {
//    char  sc;
//	switch(num)
//	{
//	  case  0:
//	       sc='0';
//		    break;
//	   case  1:
//	       sc='1';
//	        break;
//	    case  2:
//	       sc='2';
//	   break;
//		 case  3:
//	       sc='3';
//	   break;
//	    case  4:
//		   sc='4';
//	    break;
//		case  5:
//	       sc='5';
//	   break;
//	   case  6:
//	       sc='6';
//	   break;
//	    case  7:
//	       sc='7';
//	   break;
//	   case  8:
//	       sc='8';
//	   break;
//	   case  9:
//	       sc='9';
//	   break;
//
//	   default:
//	   break;
//       }
//
// 	    switch(g_mWeatherShowMode)
//		{
//		  case 0:
//		   	if(	g_mShowMenucolumn!=6)
//			{
//	  	       g_sysmenu4400temperatrue[g_mShowMenucolumn-1]=sc;
//			   g_sysmenu4400temperatrueEn[g_mShowMenucolumn-1]=sc;
//			}
//			else  if(g_sysmenu4400temperatrue[g_mShowMenucolumn-1]=='+'	)
//			{
//			  g_sysmenu4400temperatrue[g_mShowMenucolumn-1]='-';
//			  g_sysmenu4400temperatrueEn[g_mShowMenucolumn-1]='-';
//			  FWeatherInputRight();
//			}
//			else
//			{
//		        g_sysmenu4400temperatrue[g_mShowMenucolumn-1]='+';
//				g_sysmenu4400temperatrueEn[g_mShowMenucolumn-1]='+';
//				FWeatherInputRight();
//
//			}
//		
//		  break;
//		  case 1:
//		     g_sysmenu4400humidity[g_mShowMenucolumn-1]=sc;
//		     g_sysmenu4400humidityEn[g_mShowMenucolumn-1]=sc;
//			    
//		  break;
//		  case 2:
//		  	 g_sysmenu4400airpressure[g_mShowMenucolumn-1]=sc;
//			 g_sysmenu4400airpressureEn[g_mShowMenucolumn-1]=sc;			     
//		  break; 
//		  default:
//		  break;
//		}
//
//
//	FWeatherInputRight();
		
}



//************************************************************
 //��Զ���������������
 void FTelZeroInputRight()
 {
	  switch(g_mTelZeroShowMode	)
	  {
	     case 0	:
		     if(g_mShowMenucolumn<7)
			{
			  g_mShowMenucolumn++;
			 }
			 else
			 {
			    g_mShowMenucolumn=5;
			  }
		 break;
		 case 1:
		 if(g_mShowMenucolumn<7)
			{
			  g_mShowMenucolumn++;
			 }
			 else
			 {
			    g_mShowMenucolumn=6;
			  }
		 break;
		 default :
		 break;
	}
 }
 //************************************************************

 //************************************************************
 //��Զ���������������
 void FTelZeroInputLeft()
 {
	  switch(g_mTelZeroShowMode	)
	  {
	     case 0	:
		     if(g_mShowMenucolumn>5)
			{
			  g_mShowMenucolumn--;
			 }
			 else
			 {
			    g_mShowMenucolumn=7;
			  }
		 break;
		 case 1:
		  if(g_mShowMenucolumn>6)
			{
			  g_mShowMenucolumn--;
			 }
			 else
			 {
			    g_mShowMenucolumn=7;
			  }
		 break;
		 default :
		 break;
	}
 }
  //************************************************************

 //************************************************************
  //��Զ��������뺯��
 void  FTelZeroInput(uint8  num)
 {
    char  sc;
	switch(num)
	{
	  case  0:
	       sc='0';
		    break;
	   case  1:
	       sc='1';
	        break;
	    case  2:
	       sc='2';
	   break;
		 case  3:
	       sc='3';
	   break;
	    case  4:
		   sc='4';
	    break;
		case  5:
	       sc='5';
	   break;
	   case  6:
	       sc='6';
	   break;
	    case  7:
	       sc='7';
	   break;
	   case  8:
	       sc='8';
	   break;
	   case  9:
	       sc='9';
	   break;

	   default:
	   break;
       }

 	    switch(g_mTelZeroShowMode)
		{
		  case 0:
		     g_sysmenu4700AziZero[g_mShowMenucolumn-1]=sc;
		     g_sysmenu4700AziZeroEn[g_mShowMenucolumn-1]=sc;
			    
		  break;
		  case 1:
		  	 g_sysmenu4700AltZero[g_mShowMenucolumn-1]=sc;
			 g_sysmenu4700AltZeroEn[g_mShowMenucolumn-1]=sc;			     
		  break; 
		  default:
		  break;
		}


	FTelZeroInputRight();
		
}





  //************************************************************

 //************************************************************

 //��ȡ�۲���������
//void GetNowBestObject(uint8 num,float *fra,float *fdec )
//{
//   	 	
//	*fra=*(g_mNowBestObject+2*num);//��ȡ��ǰ���Ŀ��ĳྭ����
//	*fdec=*(g_mNowBestObject+2*num+1);//��ȡ��ǰ���Ŀ��ĳྭ����    	   
//}

  //************************************************************

 //************************************************************
//����̫��ϵ���������
void SetNowBestObject()
{
    
	double  stime;
	float planetra,planetdec;
	uint8 planetnum,i;
	char tempobjname[10][10] ;
	 char starnamecn[10][22];
	char  Planet_name[9][10]={{'M','o','o','n',' ',' ',' ',' ',' ',0},

							   {'M','e','r','c','u','r','y',' ',' ',0},

							   {'V','e','r','n','u','s',' ',' ',' ',0},
							   	   
							   {'M','a','r','s',' ',' ',' ',' ',' ',0},

							   {'J','u','p','i','t','e','r',' ',' ',0},

							   {'S','a','t','u','r','n',' ',' ',' ',0},

							   {'U','r','a','n','r','s',' ',' ',' ',0},

							   {'N','e','p','t','u','n','e',' ',' ',0},

							   {'S','u','n',' ',' ',' ',' ',' ',' ',0}};
	planetnum=0;

	stime=FCalSiderealTime(1,false,g_mGoto.m_nLongitude);
	g_mBestStarNum=FindAlignStar(stime,g_mGoto.m_nAtitude,g_mStarAlign,tempobjname,starnamecn);		

	GetSunSysObject(8,&planetra,&planetdec);//����ྭ��γ
	if(AdjustPlanetRise(planetra,planetdec,g_mGoto.m_nAtitude,stime)==true)
	{ 
	   planetnum++;
	  g_mNowBestObject[2*(planetnum-1)]=planetra;
	  g_mNowBestObject[2*(planetnum-1)+1]=planetdec;
	  for (i=0;i<10;i++)
	  {
	      BestObjectName[planetnum-1][i]=Planet_name[0][i];
	  }
	}

	GetSunSysObject(0,&planetra,&planetdec);//ˮ�ǳྭ��γ
	if(AdjustPlanetRise(planetra,planetdec,g_mGoto.m_nAtitude,stime)==true)
	{ 
	   planetnum++;
	  g_mNowBestObject[2*(planetnum-1)]=planetra;
	  g_mNowBestObject[2*(planetnum-1)+1]=planetdec;
	  for (i=0;i<10;i++)
	  {
	     BestObjectName[planetnum-1][i]=Planet_name[1][i];
	  }
	}


	GetSunSysObject(1,&planetra,&planetdec);//���ǳྭ��γ
	if(AdjustPlanetRise(planetra,planetdec,g_mGoto.m_nAtitude,stime)==true)
	{ 
	   planetnum++;
	  g_mNowBestObject[2*(planetnum-1)]=planetra;
	  g_mNowBestObject[2*(planetnum-1)+1]=planetdec;
	  for (i=0;i<10;i++)
	  {
	      BestObjectName[planetnum-1][i]=Planet_name[2][i];
	  }
	}


	 GetSunSysObject(2,&planetra,&planetdec);//���ǳྭ��γ
	if(AdjustPlanetRise(planetra,planetdec,g_mGoto.m_nAtitude,stime)==true)
	{ 
	   planetnum++;
	  g_mNowBestObject[2*(planetnum-1)]=planetra;
	  g_mNowBestObject[2*(planetnum-1)+1]=planetdec;
	  for (i=0;i<10;i++)
	  {
	      BestObjectName[planetnum-1][i]=Planet_name[3][i];
	  }
	}


	GetSunSysObject(3,&planetra,&planetdec);//ľ�ǳྭ��γ
	if(AdjustPlanetRise(planetra,planetdec,g_mGoto.m_nAtitude,stime)==true)
	{ 
	   planetnum++;
	  g_mNowBestObject[2*(planetnum-1)]=planetra;
	  g_mNowBestObject[2*(planetnum-1)+1]=planetdec;
	  for (i=0;i<10;i++)
	  {
	      BestObjectName[planetnum-1][i]=Planet_name[4][i];
	  }
	}


   GetSunSysObject(4,&planetra,&planetdec);//���ǳྭ��γ
	if(AdjustPlanetRise(planetra,planetdec,g_mGoto.m_nAtitude,stime)==true)
	{ 
	   planetnum++;
	  g_mNowBestObject[2*(planetnum-1)]=planetra;
	  g_mNowBestObject[2*(planetnum-1)+1]=planetdec;
	  for (i=0;i<10;i++)
	  {
	      BestObjectName[planetnum-1][i]=Planet_name[5][i];
	  }
	}


	GetSunSysObject(5,&planetra,&planetdec);//�����ǳྭ��γ
	if(AdjustPlanetRise(planetra,planetdec,g_mGoto.m_nAtitude,stime)==true)
	{ 
	   planetnum++;
	  g_mNowBestObject[2*(planetnum-1)]=planetra;
	  g_mNowBestObject[2*(planetnum-1)+1]=planetdec;
	  for (i=0;i<10;i++)
	  {
	      BestObjectName[planetnum-1][i]=Planet_name[6][i];
	  }
	}


	GetSunSysObject(6,&planetra,&planetdec);//�����ǳྭ��γ
	if(AdjustPlanetRise(planetra,planetdec,g_mGoto.m_nAtitude,stime)==true)
	{ 
	   planetnum++;
	  g_mNowBestObject[2*(planetnum-1)]=planetra;
	  g_mNowBestObject[2*(planetnum-1)+1]=planetdec;
	  for (i=0;i<10;i++)
	  {
	      BestObjectName[planetnum-1][i]=Planet_name[7][i];
	  }
	}


	GetSunSysObject(7,&planetra,&planetdec);//̫���ྭ��γ
	if(AdjustPlanetRise(planetra,planetdec,g_mGoto.m_nAtitude,stime)==true)
	{ 
	   planetnum++;
	  g_mNowBestObject[2*(planetnum-1)]=planetra;
	  g_mNowBestObject[2*(planetnum-1)+1]=planetdec;
	  for (i=0;i<10;i++)
	  {
	      BestObjectName[planetnum-1][i]=Planet_name[8][i];
	  }
	} 



	for(loopi=0;loopi< g_mBestStarNum;loopi++)
	{
		g_mNowBestObject[2*planetnum+2*loopi]=g_mStarAlign[2*loopi];
		g_mNowBestObject[2*planetnum+2*loopi+1]=g_mStarAlign[2*loopi+1];
		for (i=0;i<10;i++)
		{
		   BestObjectName[planetnum+loopi][i]=tempobjname[loopi][i];
		}										
	}

	g_mBestStarNum=g_mBestStarNum+planetnum;
	

  
}


 //************************************************************

 //************************************************************
//����ÿ����������
void SetSkyPhObject()
{
    
	double  stime;
	float planetra,planetdec;
	uint8 planetnum,i;
	char tempobjname[28][10] ;
	 char starnamecn[28][22];
	char  Planet_name[9][10]={{'M','o','o','n',' ',' ',' ',' ',' ',0},

							   {'M','e','r','c','u','r','y',' ',' ',0},

							   {'V','e','r','n','u','s',' ',' ',' ',0},
							   	   
							   {'M','a','r','s',' ',' ',' ',' ',' ',0},

							   {'J','u','p','i','t','e','r',' ',' ',0},

							   {'S','a','t','u','r','n',' ',' ',' ',0},

							   {'U','r','a','n','r','s',' ',' ',' ',0},

							   {'N','e','p','t','u','n','e',' ',' ',0},

							   {'S','u','n',' ',' ',' ',' ',' ',' ',0}};
	planetnum=0;

	stime=FCalSiderealTime(1,false,g_mGoto.m_nLongitude);
	g_mBestStarNum=FindAlignStar(stime,g_mGoto.m_nAtitude,g_mStarAlign,tempobjname,starnamecn);		

	GetSunSysObject(8,&planetra,&planetdec);//����ྭ��γ
     planetnum++;
	  g_mNowBestObject[2*(planetnum-1)]=planetra;
	  g_mNowBestObject[2*(planetnum-1)+1]=planetdec;
	  for (i=0;i<10;i++)
	  {
	      BestObjectName[planetnum-1][i]=Planet_name[0][i];
	  }


	 GetSunSysObject(0,&planetra,&planetdec);//ˮ�ǳྭ��γ

	   planetnum++;
	  g_mNowBestObject[2*(planetnum-1)]=planetra;
	  g_mNowBestObject[2*(planetnum-1)+1]=planetdec;
	  for (i=0;i<10;i++)
	  {
	     BestObjectName[planetnum-1][i]=Planet_name[1][i];
	  }


	GetSunSysObject(1,&planetra,&planetdec);//���ǳྭ��γ
	 
	   planetnum++;
	  g_mNowBestObject[2*(planetnum-1)]=planetra;
	  g_mNowBestObject[2*(planetnum-1)+1]=planetdec;
	  for (i=0;i<10;i++)
	  {
	      BestObjectName[planetnum-1][i]=Planet_name[2][i];
	  }



	 GetSunSysObject(2,&planetra,&planetdec);//���ǳྭ��γ

	   planetnum++;
	  g_mNowBestObject[2*(planetnum-1)]=planetra;
	  g_mNowBestObject[2*(planetnum-1)+1]=planetdec;
	  for (i=0;i<10;i++)
	  {
	      BestObjectName[planetnum-1][i]=Planet_name[3][i];
	  }



	GetSunSysObject(3,&planetra,&planetdec);//ľ�ǳྭ��γ
      planetnum++;
	  g_mNowBestObject[2*(planetnum-1)]=planetra;
	  g_mNowBestObject[2*(planetnum-1)+1]=planetdec;
	  for (i=0;i<10;i++)
	  {
	      BestObjectName[planetnum-1][i]=Planet_name[4][i];
	  }
	


   GetSunSysObject(4,&planetra,&planetdec);//���ǳྭ��γ
	
	   planetnum++;
	  g_mNowBestObject[2*(planetnum-1)]=planetra;
	  g_mNowBestObject[2*(planetnum-1)+1]=planetdec;
	  for (i=0;i<10;i++)
	  {
	      BestObjectName[planetnum-1][i]=Planet_name[5][i];
	  }
	


	GetSunSysObject(5,&planetra,&planetdec);//�����ǳྭ��γ
 
	   planetnum++;
	  g_mNowBestObject[2*(planetnum-1)]=planetra;
	  g_mNowBestObject[2*(planetnum-1)+1]=planetdec;
	  for (i=0;i<10;i++)
	  {
	      BestObjectName[planetnum-1][i]=Planet_name[6][i];
	  }



	GetSunSysObject(6,&planetra,&planetdec);//�����ǳྭ��γ
 
	   planetnum++;
	  g_mNowBestObject[2*(planetnum-1)]=planetra;
	  g_mNowBestObject[2*(planetnum-1)+1]=planetdec;
	  for (i=0;i<10;i++)
	  {
	      BestObjectName[planetnum-1][i]=Planet_name[7][i];
	  }
	

	  GetSunSysObject(7,&planetra,&planetdec);//̫���ྭ��γ
 
	   planetnum++;
	  g_mNowBestObject[2*(planetnum-1)]=planetra;
	  g_mNowBestObject[2*(planetnum-1)+1]=planetdec;
	  for (i=0;i<10;i++)
	  {
	      BestObjectName[planetnum-1][i]=Planet_name[8][i];
	  }
 



	for(loopi=0;loopi< g_mBestStarNum;loopi++)
	{
		g_mNowBestObject[2*planetnum+2*loopi]=g_mStarAlign[2*loopi];
		g_mNowBestObject[2*planetnum+2*loopi+1]=g_mStarAlign[2*loopi+1];
		for (i=0;i<10;i++)
		{
		   BestObjectName[planetnum+loopi][i]=tempobjname[loopi][i];
		}										
	}

	g_mBestStarNum=g_mBestStarNum+planetnum;
	

  
}

 //************************************************************

// //************************************************************
////��ȡ̫��ϵͳ�ڵ�����
//void GetSunSysObject(uint8 num,float *fra,float *fdec )
//{   
//    uint32 date;
//	double  mra0,mra1,mdec0,mdec1;
//    double  mfday;
//
//	mfday=(g_mTime_hour+g_mTime_minute/60.0+g_mTime_second/3600.0)/24.0; 
//
//	FCalSiderealTime(1,false,g_mGoto.m_nLongitude);
//
//	date=g_mGoto.m_nJday-2454686;//��2008��8��8����������Ϊ:2454686
//
//   	mfday=g_mGoto.m_nJHour;
//		
//	switch(num)
//	{
//	   
//	   case  0:
//	    GetSunMoonPlanetInfo(date,2,&mra0,&mdec0)	;
//		GetSunMoonPlanetInfo(date+1,2,&mra1,&mdec1)	;
//		g_sysmenu2200object_nameEn="Mercury:     ";
//		
//		 break;
//
//	   case  1:
//	     GetSunMoonPlanetInfo(date,3,&mra0,&mdec0)	;
//		GetSunMoonPlanetInfo(date+1,3,&mra1,&mdec1)	;
//		g_sysmenu2200object_nameEn="Venus:      ";
//		
//		 break;
//	   case  2:
//	    GetSunMoonPlanetInfo(date,4,&mra0,&mdec0)	;
//		GetSunMoonPlanetInfo(date+1,4,&mra1,&mdec1)	;
//	    g_sysmenu2200object_nameEn="Mars:      ";
//
//	     break;
//
//	   case  3:
//	     GetSunMoonPlanetInfo(date,5,&mra0,&mdec0)	;
//		GetSunMoonPlanetInfo(date+1,5,&mra1,&mdec1)	;
//		g_sysmenu2200object_nameEn="Jupiter:      ";
//
//		 break;
//
//	   case  4:
//	    GetSunMoonPlanetInfo(date,6,&mra0,&mdec0)	;
//		GetSunMoonPlanetInfo(date+1,6,&mra1,&mdec1)	;
//		 g_sysmenu2200object_nameEn="Saturn:      ";
//		 break;
//	   case  5:
//	     GetSunMoonPlanetInfo(date,7,&mra0,&mdec0)	;
//		GetSunMoonPlanetInfo(date+1,7,&mra1,&mdec1)	; 	
//        g_sysmenu2200object_nameEn="Uranus:       ";
//		 break;
//	   case  6:
//	     GetSunMoonPlanetInfo(date,8,&mra0,&mdec0)	;
//		GetSunMoonPlanetInfo(date+1,8,&mra1,&mdec1)	;
//        g_sysmenu2200object_nameEn="Neptune:          ";
//		 break;
//
//    	case  7:	
//	    GetSunMoonPlanetInfo(date,0,&mra0,&mdec0)	;
//		GetSunMoonPlanetInfo(date+1,0,&mra1,&mdec1)	;
//		g_sysmenu2200object_nameEn="Sun:           ";			 		 
//		break;
//
//	   case 8:	
//	    GetSunMoonPlanetInfo(date,1,&mra0,&mdec0)	;
//		GetSunMoonPlanetInfo(date+1,1,&mra1,&mdec1)	;
//		g_sysmenu2200object_nameEn="Moon:           ";		
//		 break;
//
//	   case  9:
//	     g_sysmenu2200object_name="С���� ";
//		 g_sysmenu2200object_nameEn="Asteroids:           ";
//		
//		 break;
//	   case  10:
//	     g_sysmenu2200object_name="���� ";
//		 g_sysmenu2200object_nameEn="Comets:           ";
//		 
//		 break;
//		default :
//	 break;
//	} 
//
//   	 *fra=mra0+mfday*(mra1-mra0);        //���Բ�ֵ
//     *fdec=mdec0+mfday*(mdec1-mdec0);
//		  
//}
// //************************************************************



  //************************************************************
//��ȡ̫��ϵͳ�ڵ�����
void GetSunSysObject(uint8 num,float *fra,float *fdec )
{   


	switch(num)
	{
	   
	   case  0:
	   	 *fra=Mercury_ra;
         *fdec=Mercury_dec;
		g_sysmenu2200object_nameEn="Mercury                ";
		g_sysmenu2200object_nameCn=g_sysmenu2201Cn;
		 break;

	   case  1:
	     *fra=Venus_ra;
         *fdec=Venus_dec;
		g_sysmenu2200object_nameEn="Venus                    ";
		g_sysmenu2200object_nameCn=g_sysmenu2202Cn;
		 break;
	   case  2:
	     *fra=Mars_ra;
         *fdec=Mars_dec;
	    g_sysmenu2200object_nameEn="Mars                      ";
	    g_sysmenu2200object_nameCn=g_sysmenu2203Cn;
	     break;

	   case  3:
	      *fra=Jupiter_ra;
         *fdec=Jupiter_dec;
		g_sysmenu2200object_nameEn="Jupiter                  ";
	    g_sysmenu2200object_nameCn=g_sysmenu2204Cn;
		 break;

	   case  4:
	    *fra=Saturn_ra;
         *fdec=Saturn_dec;
		 g_sysmenu2200object_nameEn="Saturn                     ";
		 g_sysmenu2200object_nameCn=g_sysmenu2205Cn;
		 break;
	   case  5:
	     *fra=Uranus_ra;
         *fdec=Uranus_dec;
        g_sysmenu2200object_nameEn="Uranus                      ";
		g_sysmenu2200object_nameCn=g_sysmenu2206Cn;
		 break;
	   case  6:
	      *fra=Neptune_ra;
         *fdec=Neptune_dec;
        g_sysmenu2200object_nameEn="Neptune                       ";
		g_sysmenu2200object_nameCn=g_sysmenu2207Cn;
		 break;

    	case  7:	
	     *fra=Pluto_ra;
         *fdec=Pluto_dec;
		g_sysmenu2200object_nameEn="Pluto                      ";	
		g_sysmenu2200object_nameCn=g_sysmenu2208Cn;		 		 
		break;

	   case 8:	
	     *fra=Sun_ra;
         *fdec=Sun_dec;
		g_sysmenu2200object_nameEn="Sun                     ";
		g_sysmenu2200object_nameCn=g_sysmenu2209Cn;		
		 break;

	   case 9:
	     *fra=Moon_ra;
         *fdec=Moon_dec;
		g_sysmenu2200object_nameEn="Moon                       "; 
		g_sysmenu2200object_nameCn=g_sysmenu22010Cn;   	
		 break;
		default :
	 break;
	} 
		  
}
 //************************************************************

 //************************************************************
//��ȡϵͳʱ��
void GetTime()
{
    uint32  RTCtime;
	uint32  RTCdate;
	RTCtime = RTCtimeRead; // ��ȡ����ʱ�ӼĴ���
	RTCdate = RTCdateRead;	// ��ȡ�������ڼĴ���
	// ȡ����ֵ
    // time->wYear = (RTCdate>>16)&0xFFF;  
	 g_mMoonPhaseYear= (RTCdate>>16)&0xFFF; 
	// ȡ����ֵ
//	time->wMonth = (RTCdate>>8)&0x0F; 
	g_mMoonPhaseMonth= (RTCdate>>8)&0x0F;      
	// ȡ����ֵ
	//time->wDay = RTCdate&0x1F;            
	// ��ʾ��ֵ;      
	// ȡ��ʱ��ֵ
//	time->wHour = (RTCtime>>16)&0x1F;
	// ȡ�÷ֵ�ֵ		
//	time->wMinute= (RTCtime>>8)&0x3F;	
	// ȡ�����ֵ	
//	time->wSecond = RTCtime&0x3F;
	//ȡ�ú���
//	time->wMilliseconds=0;
}



 //*****************************************************
//*****************************************************
//��ʱ�ӳ���
void MenuDelay (uint16 i) 
{	                 
	uint16 n;
	while(i>1)
	{
		for(n=10000;n>1;n--);
		i--;
	}
}
//****************************************************************************

void FTimerInputMoveLeft()
{
	switch(g_mShowMenucolumn)
      {
		 case  1:
           g_mShowMenucolumn=5;
		   break;
		 case  2:
           g_mShowMenucolumn=1;
		   break;
		 case  3:
           g_mShowMenucolumn=2;
		   break;
		 case  4:
           g_mShowMenucolumn=3;
		   break;
		 case  5:
           g_mShowMenucolumn=4;
		   break;
		 default:
		   break;
      }
}
void FTimerInputMoveRight()
{
	switch(g_mShowMenucolumn)
      {
	     case  1:
           g_mShowMenucolumn=2;
		   break;
		 case  2:
           g_mShowMenucolumn=3;
		   break;
		 case  3:
           g_mShowMenucolumn=4;
		   break;
		 case  4:
           g_mShowMenucolumn=5;
		   break;
		 case  5:
           g_mShowMenucolumn=1;
		   break;
		 default:
		   break;
      }
}
void FAlarmInputMoveRight()
{
	switch(g_mShowMenucolumn)
      {
		 case  1:
           g_mShowMenucolumn=2;
		   break;
		 case  2:
           g_mShowMenucolumn=4;
		   break;
		 case  4:
           g_mShowMenucolumn=5;
		   break;
		 case  5:
           g_mShowMenucolumn=7;
		   break;
		 case  7:
           g_mShowMenucolumn=8;
		   break;
		 case  8:
           g_mShowMenucolumn=1;
		   break;
		 default:
		   break;
      }
}
void FAlarmInputMoveLeft()
{
	switch(g_mShowMenucolumn)
      {
		 case  1:
           g_mShowMenucolumn=8;
		   break;
		 case  2:
           g_mShowMenucolumn=1;
		   break;
		 case  4:
           g_mShowMenucolumn=2;
		   break;
		 case  5:
           g_mShowMenucolumn=4;
		   break;
		 case  7:
           g_mShowMenucolumn=5;
		   break;
		 case  8:
           g_mShowMenucolumn=7;
		   break;
		 default:
		   break;
      }
}
void FVerifyAlarmInput() 
{
  //�˺�����Ҫ�õ�����ʱ����
   //********************************
   //�ྭ��γ�������ʱ�����������ж������Ƿ���ȷ����ȷ�ŷ��أ�����ȷ����������״̬
   int g_mObjAlarm_shi_temp,g_mObjAlarm_fen_temp;
   int g_mObjAlarm_miao_temp;
   //********************************

      //�ѳྭ��γ�ַ����ȡ����������ʱ������
		g_mObjAlarm_shi_temp= atoi(&g_sysmenu3500alarm_input[0]);
		g_mObjAlarm_fen_temp= atoi(&g_sysmenu3500alarm_input[3]);
		g_mObjAlarm_miao_temp= atoi(&g_sysmenu3500alarm_input[6]);


		if((g_mObjAlarm_shi_temp>23)||(g_mObjAlarm_fen_temp>59)||(g_mObjAlarm_miao_temp>59))
		{

		      g_nsysstatus=SYS_SUB3SUB5ALARM_INPUT;  //��γ���������ȷ��ϵͳ���ص���γ����״̬
			  g_mShowMenucolumn=1;

		}
		else
		{
			g_mObjAlarm_open=1;
		 	g_nsysstatus=SYS_SUB3MENU5;  //����ྭ��γ���붼��ȷ����ִ�гྭ��γ���벢�˳�
			g_mObjAlarm_shi=g_mObjAlarm_shi_temp;
		    g_mObjAlarm_fen=g_mObjAlarm_fen_temp;
		    g_mObjAlarm_miao=g_mObjAlarm_miao_temp;
		}

} 
void FSfocusInputMoveRight()
{
	  switch(g_mShowMenucolumn)
      {
		 case  7:
           g_mShowMenucolumn=8;
		   break;
		 case  8:
           g_mShowMenucolumn=7;
		   break;
		 default:
		   break;
      }
}
void FSfocusInputMoveLeft()
{
	  switch(g_mShowMenucolumn)
      {
		 case  7:
           g_mShowMenucolumn=8;
		   break;
		 case  8:
           g_mShowMenucolumn=7;
		   break;
		 default:
		   break;
      }
}

void FSFovInputMoveRight()
{
	  switch(g_mShowMenucolumn)
      {
		 case  7:
           g_mShowMenucolumn=8;
		   break;
		 case  8:
           g_mShowMenucolumn=9;
		   break;
		 case  9:
           g_mShowMenucolumn=11;
		   break;

		 case  11:
           g_mShowMenucolumn=12;
		   break;
		 case  12:
           g_mShowMenucolumn=7;
		   break;

		 default:
		   break;
      }
}
void FSFovInputMoveLeft()
{
	  switch(g_mShowMenucolumn)
      {
		 case  7:
           g_mShowMenucolumn=12;
		   break;
		 case  12:
           g_mShowMenucolumn=11;
		   break;
		    case  11:
           g_mShowMenucolumn=9;
		   break;
		   case  9:
           g_mShowMenucolumn=8;
		   break;

		 case  8:
           g_mShowMenucolumn=7;
		   break;

		 default:
		   break;
      }
}
void FMfocusInputMoveRight()
{
	  switch(g_mShowMenucolumn)
      {
		 case  7:
           g_mShowMenucolumn=8;
		   break;
		 case  8:
           g_mShowMenucolumn=9;
		   break;
		 case  9:
           g_mShowMenucolumn=10;
		   break;
		 case  10:
           g_mShowMenucolumn=7;
		   break;
		 default:
		   break;
      }
}
void FMfocusInputMoveLeft()
{
	  switch(g_mShowMenucolumn)
      {
		 case  7:
           g_mShowMenucolumn=10;
		   break;
		 case  8:
           g_mShowMenucolumn=7;
		   break;
		 case  9:
           g_mShowMenucolumn=8;
		   break;
		 case  10:
           g_mShowMenucolumn=9;
		   break;
		 default:
		   break;
      }
}
void FverifyInputSite()
{
//�˺�����Ҫ�õ�����ʱ����
    uint8 site[8];
	uint8 Lon[6];
	uint8 Lat[5];
	uint8 Zone[3];

	uint8 i;
      //�ѳྭ��γ�ַ����ȡ����������ʱ������
	for(i=0;i<8;i++)
	{
	 	site[i]=(uint8)g_sysmenu4300sitenameEn[i+6];
	}
	

		Lon[0]=(uint8)g_sysmenu4300sitelonEn[6];
	 	Lon[1]=(uint8)atoi(&g_sysmenu4300sitelonEn[7]);
		Lon[2]=(uint8)atoi(&g_sysmenu4300sitelonEn[11]);

		Lat[0]=(uint8)g_sysmenu4300sitelatEn[6];
		Lat[1]=(uint8)atoi(&g_sysmenu4300sitelatEn[7]);
		Lat[2]=(uint8)atoi(&g_sysmenu4300sitelatEn[10]);

		Zone[0]=(uint8)g_sysmenu4300sitezoneEn[6];
		Zone[1]=(uint8)atoi(&g_sysmenu4300sitezoneEn[7]);


		if((Lon[1]>179)||(Lon[2]>59)||
			(Lat[1]>89)||(Lat[2]>59)||
			(Zone[1]>11))
		{

		      g_nsysstatus=SYS_SUB4SUB3_SETSITE;
		}
		else
		{
			Lon[0]=g_sysmenu4300sitelonEn[6];

			Lon[1]=g_sysmenu4300sitelonEn[7];
			Lon[2]=g_sysmenu4300sitelonEn[8];
			Lon[3]=g_sysmenu4300sitelonEn[9];

			Lon[4]=g_sysmenu4300sitelonEn[11];
			Lon[5]=g_sysmenu4300sitelonEn[12];

			Lat[0]=g_sysmenu4300sitelatEn[6];

			Lat[1]=g_sysmenu4300sitelatEn[7];
			Lat[2]=g_sysmenu4300sitelatEn[8];

			Lat[3]=g_sysmenu4300sitelatEn[10];
			Lat[4]=g_sysmenu4300sitelatEn[11];


			Zone[0]=g_sysmenu4300sitezoneEn[6];
			Zone[1]=g_sysmenu4300sitezoneEn[7];
			Zone[2]=g_sysmenu4300sitezoneEn[8];


			SetSite(site,Lon,Lat,Zone);
   

		
		   GetSite(g_sitenametemp,&g_mSitLontemp,&g_mSitLattemp,&g_mTimeZonetemp);
		     g_mSitLon=g_mSitLontemp;
			 g_mSitLat=g_mSitLattemp;
			 g_mTimeZone=g_mTimeZonetemp;

			g_mGoto.m_nLongitude=g_mSitLon;
		    g_mGoto.m_nAtitude=g_mSitLat;
		    g_mGoto.m_nTimeZone=g_mTimeZone;

			FBeep(2);
		    if(g_mSysInitGuide==1)
			{
			    if(g_mTelescopeConType==1)
				{ 		      	LCDRfrsh();
					//ϵͳ���ڳ�ʼ��
//					//DispEn(0,5,1,22,"   Ver. 0.97 EQ/AZ    ");
//	             	DispEn(0,4,1,22,"System Initializing...");
//
//					GetPlanetPos();//��������λ��
//					MenuDelay(1000);
//
//					//ϵͳ��ʼ�������					
//					FBeep(1);
//					LCDRfrsh();
//					DispEn(0,4,1,22,"System Initialized    ");
//					MenuDelay(1000);
//					LCDRfrsh();
                    g_mcalpalnet=0;

			      g_nsysstatus=SYS_MAINSHOW;
				   g_mSysInitGuide=0;
				  
				 }
				  else
				  {
			   	    g_nsysstatus=SYS_SUB4SUB7_TELAZIALT_ZERO; 
				  } 
			 }
			 else
			 {
		       g_nsysstatus=SYS_MAINSHOW;     
			 }
		}
}
void FverifyInputLandmark()
{
	//�˺�����Ҫ�õ�����ʱ����
	uint8  i;
      //�ѳྭ��γ�ַ����ȡ����������ʱ������
	for(i=0;i<7;i++)
	 	LandMarkName[i]=(uint8)g_sysmenu2110m_2[i+6];
		LandMarkName[7]=0;

		az_byte[0]=(uint16)atoi(&g_sysmenu2110m_3[6]);
	 	az_byte[1]=(uint16)atoi(&g_sysmenu2110m_3[10]);
		az_byte[2]=(uint16)atoi(&g_sysmenu2110m_3[13]);

		alt_byte[0]=(uint8)atoi(&g_sysmenu2110m_4[6]);
		alt_byte[1]=(uint8)atoi(&g_sysmenu2110m_4[9]);
		alt_byte[2]=(uint8)atoi(&g_sysmenu2110m_4[12]);

		if((az_byte[0]>359)||(az_byte[1]>59)||(az_byte[2]>59)||
			(alt_byte[0]>89)||(alt_byte[1]>59)||(alt_byte[2]>59))
		{

		      g_nsysstatus=SYS_SUB2SUB11_SET;
		}
		else
		{
			az_float=(float)az_byte[0]+(float)az_byte[1]/60+(float)az_byte[1]/3600;
			alt_float=(float)alt_byte[0]+(float)alt_byte[1]/60+(float)alt_byte[1]/3600;
			switch(g_mMyLandmarkOperator)
			{
				case 1:	 //����
					AddCustomerLandMarkInfo(LandMarkName,&az_float,&alt_float);
					g_nsysstatus=SYS_SUB2SUB11MENU2;
					break;
				default:
					break;
			}
		}
}
void F_LandmarkInput(uint8 num)
{
    char  sc;
	char  ss[10];
	uint8 mtemp;
	if(g_mCapsLock)//�ص�������ʱ�Ĵ�Сд���ƣ�falseСд��true��д
	{
	   mtemp=5;
	}
	else
	{
	   mtemp=0;
	} 
	switch(num)
	{
		case  0:
	    	sc='0';
		   	ss[0]='0';
		   	ss[1]='0';
		   	ss[2]='0';
		   	ss[3]='0';
		   	ss[4]='0';
		   	ss[5]='0';
		   	ss[6]='0';
		   	ss[7]='0';
			ss[8]='0';
		   	ss[9]='0';
	   		break;
	     case  1:
	    	sc='1';
		    ss[0]='1';
		   	ss[1]='1';
		   	ss[2]='1';
		   	ss[3]='1';
		   	ss[4]='1';
		   	ss[5]='1';
		   	ss[6]='1';
		   	ss[7]='1';
			ss[8]='1';
		   	ss[9]='1';
	   		break;
	    case  2:
	       	sc='2';
		   	ss[0]='2';
		   	ss[1]='a';
		   	ss[2]='b';
		   	ss[3]='c';
		   	ss[4]=' ';
		   	ss[5]='2';
		   	ss[6]='A';
		   	ss[7]='B';
			ss[8]='C';
		   	ss[9]=' ';
	   		break;
		case  3:
	        sc='3';
		   	ss[0]='3';
		   	ss[1]='d';
		   	ss[2]='e';
		   	ss[3]='f';
		   	ss[4]=' ';
		   	ss[5]='3';
		   	ss[6]='D';
		   	ss[7]='E';
			ss[8]='F';
		   	ss[9]=' ';
	   		break;
	    case  4:
	       	sc='4';
		   	ss[0]='4';
		   	ss[1]='g';
		   	ss[2]='h';
		   	ss[3]='i';
		   	ss[4]=' ';
		   	ss[5]='4';
		   	ss[6]='G';
		   	ss[7]='H';
			ss[8]='I';
		   	ss[9]=' ';
	    	break;
		case  5:
	       	sc='5';
		   	ss[0]='5';
		   	ss[1]='j';
		   	ss[2]='k';
		   	ss[3]='l';
		   	ss[4]=' ';
		   	ss[5]='5';
		   	ss[6]='J';
		   	ss[7]='K';
			ss[8]='L';
		   	ss[9]=' ';
	   		break;
	   	case  6:
	        sc='6';
		   	ss[0]='6';
		   	ss[1]='m';
		   	ss[2]='n';
		   	ss[3]='o';
		   	ss[4]=' ';
		   	ss[5]='6';
		   	ss[6]='M';
		   	ss[7]='N';
			ss[8]='O';
		   	ss[9]=' ';
	   		break;
	    case  7:
	       	sc='7';
		   	ss[0]='7';
		   	ss[1]='p';
		   	ss[2]='q';
		   	ss[3]='r';
		   	ss[4]='s';
		   	ss[5]='7';
		   	ss[6]='P';
		   	ss[7]='Q';
			ss[8]='R';
		   	ss[9]='S';
	   		break;
	   	case  8:
	       	sc='8';
		   	ss[0]='8';
		   	ss[1]='t';
		   	ss[2]='u';
		   	ss[3]='v';
		   	ss[4]=' ';
		   	ss[5]='8';
		   	ss[6]='T';
		   	ss[7]='U';
			ss[8]='V';
		   	ss[9]=' ';
	   		break;
	   	case  9:
	       	sc='9';
		   	ss[0]='9';
		   	ss[1]='w';
		   	ss[2]='x';
		   	ss[3]='y';
		   	ss[4]='z';
		   	ss[5]='2';
		   	ss[6]='W';
		   	ss[7]='X';
			ss[8]='Y';
		   	ss[9]='Z';
	   		break;
		default:
	   		break;
	}
	switch(g_mMyLandmarkOperator)
	{
		case 1:
		switch(g_mMyLandmarkShowMode)
		{
			case 0:
				g_sysmenu2110m_2[g_mShowMenucolumn-1]=ss[g_mKeyTurn+mtemp];//½��Ŀ����������
				g_sysmenu2110m_2En[g_mShowMenucolumn-1]=ss[g_mKeyTurn+mtemp];//½��Ŀ��������   
				if(g_mKeyTurn<4)
				{
					g_mKeyTurn++;
				}
				else
				{
					g_mKeyTurn=0;
				}
				break;
			case 1:
				g_sysmenu2110m_3[g_mShowMenucolumn-1]=sc;//��λ����
				g_sysmenu2110m_3En[g_mShowMenucolumn-1]=sc;//��λ����
				//������ɺ�������
	            FLandmarkInputRight();		    
				break;
			case 2:
				g_sysmenu2110m_4[g_mShowMenucolumn-1]=sc;//�߶�����
				g_sysmenu2110m_4En[g_mShowMenucolumn-1]=sc;//�߶�����
				//������ɺ�������
	            FLandmarkInputRight();  				     
				break;
			default:
				break;
		}
			break;
		default:
			break;
	}
}
void FLandmarkInputLeft()
{
 switch(g_mMyLandmarkOperator)
	{
		case 1:
			switch(g_mMyLandmarkShowMode)
			{
				case 0:
					if(g_mShowMenucolumn>7)
					{
						g_mShowMenucolumn--;
					}
					else
					{
					    g_mShowMenucolumn=13;
					}
					break;
				case 1:
					switch(	g_mShowMenucolumn)
					{
						case 7:
							g_mShowMenucolumn=15;
							break;
						case 8:
						    g_mShowMenucolumn=7;
							break;
						case 9:
						    g_mShowMenucolumn=8;
							break;
						case 11:
						    g_mShowMenucolumn=9;
							break;
						case 12:
						    g_mShowMenucolumn=11;
							break;
						case 14:
						    g_mShowMenucolumn=12;
							break;
						case 15:
						    g_mShowMenucolumn=14;
							break;
						default:
							break ;	 						
					}
					break;
				case 2:
					switch(	g_mShowMenucolumn)
					{
						case 7:
							g_mShowMenucolumn=14;
							break;
						case 8:
						    g_mShowMenucolumn=7;
							break;
						case 10:
						    g_mShowMenucolumn=8;
							break;
						case 11:
						    g_mShowMenucolumn=10;
							break;
						case 13:
						    g_mShowMenucolumn=11;
							break;
						case 14:
						    g_mShowMenucolumn=13;
							break;
						default:
							break ;
					}
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}
}
void FLandmarkInputRight()
{
switch(g_mMyLandmarkOperator)
	{
		case 1:
			switch(g_mMyLandmarkShowMode)
			{
				case 0:
					if(g_mShowMenucolumn<13)
					{
						g_mShowMenucolumn++;
					}
					else
					{
					    g_mShowMenucolumn=7;
					}
					break;
				case 1:
					switch(	g_mShowMenucolumn)
					{
						case 7:
							g_mShowMenucolumn=8;
							break;
						case 8:
						    g_mShowMenucolumn=9;
							break;
						case 9:
						    g_mShowMenucolumn=11;
							break;
						case 11:
						    g_mShowMenucolumn=12;
							break;
						case 12:
						    g_mShowMenucolumn=14;
							break;
						case 14:
						    g_mShowMenucolumn=15;
							break;
						case 15:
						    g_mShowMenucolumn=7;
							break;
						default:
							break ;
					}
					break;
				case 2:
					switch(	g_mShowMenucolumn)
					{
						case 7:
							g_mShowMenucolumn=8;
							break;
						case 8:
						    g_mShowMenucolumn=10;
							break;
						case 10:
						    g_mShowMenucolumn=11;
							break;
						case 11:
						    g_mShowMenucolumn=13;
							break;
						case 13:
						    g_mShowMenucolumn=14;
							break;
						case 14:
						    g_mShowMenucolumn=7;
							break;
						default:
							break ;
					}
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}
}




void F_SelfdefStarInput(uint8 num) 
{
    char  sc;
	char  ss[10];
	uint8 mtemp;
	if(g_mCapsLock)//�ص�������ʱ�Ĵ�Сд���ƣ�falseСд��true��д
	{
	   mtemp=5;
	}
	else
	{
	   mtemp=0;
	} 
	switch(num)
	{
		case  0:
	    	sc='0';
		   	ss[0]='0';
		   	ss[1]='0';
		   	ss[2]='0';
		   	ss[3]='0';
		   	ss[4]='0';
		   	ss[5]='0';
		   	ss[6]='0';
		   	ss[7]='0';
			ss[8]='0';
		   	ss[9]='0';
	   		break;
	     case  1:
	    	sc='1';
		    ss[0]='1';
		   	ss[1]='1';
		   	ss[2]='1';
		   	ss[3]='1';
		   	ss[4]='1';
		   	ss[5]='1';
		   	ss[6]='1';
		   	ss[7]='1';
			ss[8]='1';
		   	ss[9]='1';
	   		break;
	    case  2:
	       	sc='2';
		   	ss[0]='2';
		   	ss[1]='a';
		   	ss[2]='b';
		   	ss[3]='c';
		   	ss[4]=' ';
		   	ss[5]='2';
		   	ss[6]='A';
		   	ss[7]='B';
			ss[8]='C';
		   	ss[9]=' ';
	   		break;
		case  3:
	        sc='3';
		   	ss[0]='3';
		   	ss[1]='d';
		   	ss[2]='e';
		   	ss[3]='f';
		   	ss[4]=' ';
		   	ss[5]='3';
		   	ss[6]='D';
		   	ss[7]='E';
			ss[8]='F';
		   	ss[9]=' ';
	   		break;
	    case  4:
	       	sc='4';
		   	ss[0]='4';
		   	ss[1]='g';
		   	ss[2]='h';
		   	ss[3]='i';
		   	ss[4]=' ';
		   	ss[5]='4';
		   	ss[6]='G';
		   	ss[7]='H';
			ss[8]='I';
		   	ss[9]=' ';
	    	break;
		case  5:
	       	sc='5';
		   	ss[0]='5';
		   	ss[1]='j';
		   	ss[2]='k';
		   	ss[3]='l';
		   	ss[4]=' ';
		   	ss[5]='5';
		   	ss[6]='J';
		   	ss[7]='K';
			ss[8]='L';
		   	ss[9]=' ';
	   		break;
	   	case  6:
	        sc='6';
		   	ss[0]='6';
		   	ss[1]='m';
		   	ss[2]='n';
		   	ss[3]='o';
		   	ss[4]=' ';
		   	ss[5]='6';
		   	ss[6]='M';
		   	ss[7]='N';
			ss[8]='O';
		   	ss[9]=' ';
	   		break;
	    case  7:
	       	sc='7';
		   	ss[0]='7';
		   	ss[1]='p';
		   	ss[2]='q';
		   	ss[3]='r';
		   	ss[4]='s';
		   	ss[5]='7';
		   	ss[6]='P';
		   	ss[7]='Q';
			ss[8]='R';
		   	ss[9]='S';
	   		break;
	   	case  8:
	       	sc='8';
		   	ss[0]='8';
		   	ss[1]='t';
		   	ss[2]='u';
		   	ss[3]='v';
		   	ss[4]=' ';
		   	ss[5]='8';
		   	ss[6]='T';
		   	ss[7]='U';
			ss[8]='V';
		   	ss[9]=' ';
	   		break;
	   	case  9:
	       	sc='9';
		   	ss[0]='9';
		   	ss[1]='w';
		   	ss[2]='x';
		   	ss[3]='y';
		   	ss[4]='z';
		   	ss[5]='2';
		   	ss[6]='W';
		   	ss[7]='X';
			ss[8]='Y';
		   	ss[9]='Z';
	   		break;
		default:
	   		break;
	}
	switch(g_mMyStarOperator)
	{
		case 1:
		case 3:
		switch(g_mMyStarShowMode)
		{
			case 0:
				g_sysmenu2802m_2[g_mShowMenucolumn-1]=ss[g_mKeyTurn+mtemp];//�Զ�����������
				g_sysmenu2802m_2En[g_mShowMenucolumn-1]=ss[g_mKeyTurn+mtemp];//�Զ�����������   
				if(g_mKeyTurn<4)
				{
					g_mKeyTurn++;
				}
				else
				{
					g_mKeyTurn=0;
				}
				break;
			case 1:
				g_sysmenu2803m_3[g_mShowMenucolumn-1]=sc;//�ྭ����
				g_sysmenu2803m_3En[g_mShowMenucolumn-1]=sc;//�ྭ����
				//������ɺ�������
	            FStarInputRight();		    
				break;
			case 2:
				if(	g_mShowMenucolumn!=7)
				{
					g_sysmenu2804m_4[g_mShowMenucolumn-1]=sc;//��γ����
					g_sysmenu2804m_4En[g_mShowMenucolumn-1]=sc;//��γ����
				}
				else  if(g_sysmenu2804m_4[g_mShowMenucolumn-1]=='+'	)
				{
					g_sysmenu2804m_4[g_mShowMenucolumn-1]='-';//��γ����
					g_sysmenu2804m_4En[g_mShowMenucolumn-1]='-';//��γ����
				}
				else
				{
					g_sysmenu2804m_4[g_mShowMenucolumn-1]='+';//��γ������
					g_sysmenu2804m_4En[g_mShowMenucolumn-1]='+';//��γ������
				}
				//������ɺ�������
	            FStarInputRight();  				     
				break;
			default:
				break;
		}
			break;
		default:
			break;
	}	
}
void FStarInputLeft() 
{
	switch(g_mMyStarOperator)
	{
		case 1:
		case 3:
			switch(g_mMyStarShowMode)
			{
				case 0:
					if(g_mShowMenucolumn>7)
					{
						g_mShowMenucolumn--;
					}
					else
					{
					    g_mShowMenucolumn=13;
					}
					break;
				case 1:
					switch(	g_mShowMenucolumn)
					{
						case 7:
							g_mShowMenucolumn=14;
							break;
						case 8:
						    g_mShowMenucolumn=7;
							break;
						case 10:
						    g_mShowMenucolumn=8;
							break;
						case 11:
						    g_mShowMenucolumn=10;
							break;
						case 13:
						    g_mShowMenucolumn=11;
							break;
						case 14:
						    g_mShowMenucolumn=13;
							break;
						default:
							break ;
					}
					break;
				case 2:
					switch(	g_mShowMenucolumn)
					{
						case 7:
							g_mShowMenucolumn=15;
							break;
						case 8:
						    g_mShowMenucolumn=7;
							break;
						case 9:
						    g_mShowMenucolumn=8;
							break;
						case 11:
						    g_mShowMenucolumn=9;
							break;
						case 12:
						    g_mShowMenucolumn=11;
							break;
						case 14:
						    g_mShowMenucolumn=12;
							break;
						case 15:
						    g_mShowMenucolumn=14;
							break;
						default:
							break ;
					}
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}
}
void FStarInputRight()
{
switch(g_mMyStarOperator)
	{
		case 1:
		case 3:
			switch(g_mMyStarShowMode)
			{
				case 0:
					if(g_mShowMenucolumn<13)
					{
						g_mShowMenucolumn++;
					}
					else
					{
					    g_mShowMenucolumn=7;
					}
					break;
				case 1:
					switch(	g_mShowMenucolumn)
					{
						case 7:
							g_mShowMenucolumn=8;
							break;
						case 8:
						    g_mShowMenucolumn=10;
							break;
						case 10:
						    g_mShowMenucolumn=11;
							break;
						case 11:
						    g_mShowMenucolumn=13;
							break;
						case 13:
						    g_mShowMenucolumn=14;
							break;
						case 14:
						    g_mShowMenucolumn=7;
							break;
						default:
							break ;
					}
					break;
				case 2:
					switch(	g_mShowMenucolumn)
					{
						case 7:
							g_mShowMenucolumn=8;
							break;
						case 8:
						    g_mShowMenucolumn=9;
							break;
						case 9:
						    g_mShowMenucolumn=11;
							break;
						case 11:
						    g_mShowMenucolumn=12;
							break;
						case 12:
						    g_mShowMenucolumn=14;
							break;
						case 14:
						    g_mShowMenucolumn=15;
							break;
						case 15:
						    g_mShowMenucolumn=7;
							break;
						default:
							break ;
					}
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}
}
void FverifyInputAziAltZero()
{

		azi_zero=(uint16)atoi(&g_sysmenu4700AziZeroEn[4]);
		alt_zero=(uint8)atoi(&g_sysmenu4700AltZeroEn[5]);
		 //FBeep(1);
		if((azi_zero>=0)&&(azi_zero<=360)&&(alt_zero>=0)&&(alt_zero<=90))
		{
			     g_mGoto.m_nTescpAPZero=azi_zero;
			     g_mGoto.m_nTescpEPZero=alt_zero; 
				 SetTelZero((uint16)azi_zero,(uint16)alt_zero);
 				 //FBeep(2);
				if(g_mSysInitGuide==1)
				{

//					LCDRfrsh();
//					//ϵͳ���ڳ�ʼ��
//					//DispEn(0,5,1,22,"   Ver. 0.97 EQ/AZ    ");
//	             	DispEn(0,4,1,22,"System Initializing...");
//
////					GetPlanetPos();//��������λ��
//					MenuDelay(1000);
//
//					//ϵͳ��ʼ�������					
//					FBeep(1);
//					LCDRfrsh();
//					DispEn(0,4,1,22,"System Initialized    ");
//					MenuDelay(1000);
//					LCDRfrsh();
					g_mcalpalnet=0;

				    g_nsysstatus=SYS_MAINSHOW;
				    g_mSysInitGuide=0;


					  
				 }
				 else
				 {
				   //LCDRfrsh();
				  g_nsysstatus=SYS_SUB4SUB7_TELZERO_OK;     
				 }
			  
				 
			   
		}
		else
		{	 
			       g_nsysstatus=SYS_SUB4SUB7_TELAZIALT_ZERO;
				   //azi_zero=0;
				   //alt_zero=0;
				   tel_zero_error_num=20;//��Զ������
		}

		

}

//void FverifyInputStar()
//{
//////�˺�����Ҫ�õ�����ʱ����
////	uint8  i;
////    //�ѳྭ��γ�ַ����ȡ����������ʱ������
////	for(i=0;i<7;i++)
////	 	StarName[i]=(uint8)g_sysmenu2802m_2En[i+6];
////		StarName[7]=0;
////
////		ra_byte[0]=(uint8)atoi(&g_sysmenu2803m_3[6]);
////	 	ra_byte[1]=(uint8)atoi(&g_sysmenu2803m_3[9]);
////		ra_byte[2]=(uint8)atoi(&g_sysmenu2803m_3[12]);
////
////		dec_byte[0]=(uint8)atoi(&g_sysmenu2804m_4[7]);
////		dec_byte[1]=(uint8)atoi(&g_sysmenu2804m_4[10]);
////		dec_byte[2]=(uint8)atoi(&g_sysmenu2804m_4[13]);
////
////		if((ra_byte[0]>23)||(ra_byte[1]>59)||(ra_byte[2]>59)||
////			(dec_byte[0]>89)||(dec_byte[1]>59)||(dec_byte[2]>59))
////		{
////
////		      g_nsysstatus=SYS_SUB2SUB8_SET;
////		}
////		else
////		{
////			ra_float=(float)ra_byte[0]+(float)ra_byte[1]/60.0000+(float)ra_byte[2]/3600.0000;
////			if(g_sysmenu2804m_4[6]=='+')
////				dec_float=(float)dec_byte[0]+(float)dec_byte[1]/60.0000+(float)dec_byte[2]/3600.0000;
////			else
////				dec_float=-((float)dec_byte[0]+(float)dec_byte[1]/60.0000+(float)dec_byte[2]/3600.0000); 
////			switch(g_mMyStarOperator)
////			{
////				case 1:	 //����
////					AddCustomerStarInfo(StarName,&ra_float,&dec_float);
////					g_nsysstatus=SYS_SUB2SUB8MENU2;
////					break;
////				case 3:	 //�޸�
////					g_nsysstatus=SYS_SUB2SUB8MENU4;
////					break;
////				default:
////					break;
////			}
////		}
////
////
//
//
//
//
//}


//�ж����Ƿ�������
bool AdjustPlanetRise(double Ra,double Dec,double Lat,double Fstime) 
{  
	int 	i;
	uint8 	j;
	uint8   k;
	float lat_low;
	float lat_high;
	float lon_low;


	float lon_high;

	if(Fstime>=4||Fstime<=20)
	{
		lon_low=Fstime-4;
		lon_high=Fstime+4;
	}
	else if(Fstime<4)
	{
		lon_low=Fstime+24-4;
		lon_high=Fstime+4;
	}
	else
	{
		lon_low=Fstime-4;
		lon_high=Fstime-24+4;
	}
	if(Lat>=0)
	{
		lat_low=Lat-60;
		lat_high=Lat+60;
		if(lat_high>90)
		lat_high=90;
	}
	else
	{
		lat_low=Lat-60;
		lat_high=Lat+60;
		if(lat_low<(-90))
		lat_low=(-90);
	}
	if((Fstime>=4)||(Fstime<=20))
	{
		if((Ra>=lon_low)&&(Ra<=lon_high))
		{
			if((Dec>=lat_low)&&(Dec<=lat_high))
			return true;			
			
		}
	}
	else if((Fstime<=4)||(Fstime>=20))
	{
		if(((Ra>=lon_low)&&(Ra<=24))||((Ra>=0)&&(Ra<=lon_high)))
		{
			if((Dec>=lat_low)&&(Dec<=lat_high))
			return true;
		}
	}
	else 
		return false;

}




void FindCountryAdd()
{
   Citynum=0;

//  if(g_mMenuLangauge==CHANESE)
//  {
//   switch(Nationnum)
//  { 
//     case  1:
//	         Nationnum=2;
//		   break;
//	 case  2:
//	  Nationnum=3;
//		   break;
//	case  3:
//	  Nationnum=4;
//		   break;
//	case  4:
//	  Nationnum=8;
//		   break;
//	case  8:
//	  Nationnum=9;
//		   break;
//
//	case 9:
//	  Nationnum=10;
//		   break;
//	case  10:
//	  Nationnum=27;
//		   break;
//	case  27:
//	  Nationnum=47;
//		   break;
//	case  47:
//	  Nationnum=69;
//		   break;
//
//	case  69:
//	  Nationnum=82;
//		   break;
//	 case  82:
//	  Nationnum=133;
//		   break;
//
//	 case  133:
//	  Nationnum=149;
//		   break;
//	 case  149:
//	  Nationnum=160;
//		   break;
//
//	 case  160:
//	  Nationnum=166;
//		   break;
//	case  166:
//	  Nationnum=199;
//		   break;
//
//	case  199:
//	  Nationnum=235;
//		   break;
//
//	case  235:
//	  Nationnum=264;
//		   break;
//
//	case  264:
//	  Nationnum=297;
//		   break;
//	case  297:
//	  Nationnum=326;
//		   break;
//
//	case  326:
//	  Nationnum=352;
//		   break;
//
//	case  352:
//	  Nationnum=391;
//		   break;
//
//	case  391:
//	  Nationnum=410;
//		   break;
//
//   case  410:
//	  Nationnum=439;
//		   break;
//
//   case  439:
//	  Nationnum=458;
//		   break;
//
//   case  458:
//	  Nationnum=462;
//		   break;
//
//	case  462:
//	  Nationnum=465;
//		   break;
//
//   case  465:
//	  Nationnum=511;
//		   break;
//
//	case  511:
//	  Nationnum=531;
//		   break;
//
//	case  531:
//	  Nationnum=544;
//		   break;
//	case  544:
//	  Nationnum=574;
//		   break;
//	case  574:
//	  Nationnum=576;
//		   break;
//
//	case  576:
//	  Nationnum=593;
//		   break;
//	 case  593:
//	  Nationnum=608;
//		   break;
//
//	 case  608:
//	  Nationnum=1;
//		   break;
//
//	 }
//  }
//  else
//  {

  switch(Nationnum)
  {
    

     case  1:
	 case  2:
	       Nationnum++;
		   break;
	 case  3:
	       Nationnum=25;
		   break;
	 case  25:
	       Nationnum=26;
		   break;
	case  26:
	       Nationnum=29;
		   break;
	case  29:
	case  30:
	case  31:
	case  32:
	case  33:
	case  34:
	       Nationnum++;
		   break;
    case  35:
	       Nationnum=38;
		   break;
	case  38:
	case  39:
	       Nationnum++;
		   break;
	 case  40:
	       Nationnum=45;
		   break;
	case  45: 
	case  46: 
	case  47: 
	       Nationnum++;
		   break;
	 case  48:
	       Nationnum=53;
		   break;
	case  53: 
    case  54: 
	case  55: 
	case  56: 
	case  57: 
	case  58: 
	case  59: 
	       Nationnum++;
		break;
   case  60: 
	       Nationnum=62;
		   break;
	case  62: 
	case  63: 
	       Nationnum++;
		   break;
	case  64:
	       Nationnum=73;
		   break;
   	case  73: 
	case  74: 
	case  75: 
	case  76: 
	       Nationnum++;
		   break;
   case  77:
	       Nationnum=80;
		   break;
  	case  80: 
	case  81: 
	       Nationnum++;
		   break;
	case  82:
	       Nationnum=89;
		   break;
	case  89:
	       Nationnum=90;
		   break;
	case  90:
	       Nationnum=92;
		   break;
	case  92: 
	case  93: 
	case  94: 
	case  95: 
	case  96: 
	       Nationnum++;
		   break;
    case  97:
	       Nationnum=98;
		   break;
  case  98:
	       Nationnum=99;
		   break;
	case  99:
	       Nationnum=105;
		   break;
    case  105: 
	case  106: 
	case  107: 
	case  108: 
    case  109: 
	case  110: 
	case  111: 
	case  112: 
	case  113: 
	case  114: 
	case  115: 
	case  116: 
	case  117: 
	case  118: 
	       Nationnum++;
		   break;
   case  119:
	       Nationnum=121;
		   break;
    case  121: 
	case  122: 
	case  123: 
	case  124: 
	case  125: 
	case  126: 
	case  127: 
	case  128: 
	case  129: 
	case  130: 
	case  131: 
	case  132: 
	case  133: 
	       Nationnum++;
		   break;
    case  134:
	       Nationnum=143;
		   break;
	case  143: 
	case  144: 
	case  145: 
	case  146: 
	case  147: 
	case  148: 
	case  149: 
	       Nationnum++;
		   break;
   case  150:
	       Nationnum=152;
		   break;
    case  152:
	       Nationnum=154;
		   break;
	  case  154:
	       Nationnum=155;
		   break;
	 case  155:
	       Nationnum=156;
	 case  156:
	       Nationnum=158;
		   break;
	 case  158:
	 case  159:
	 case  160:
	 case  161:
	 case  162:
	 case  163:
	 case  164:
	 case  165:
	 case  166:
	 case  167:
	 case  168:
	 case  169:
	       Nationnum++;
		   break;
	 case  170:
	       Nationnum=1;
		   break;


  }
//  }
}

void FindCountryDec()
{
   Citynum=0;
//   if(g_mMenuLangauge==CHANESE)
//  {
//         switch(Nationnum)
//  { 
//     case  2:
//	         Nationnum=1;
//		   break;
//	 case  3:
//	  Nationnum=2;
//		   break;
//	case  4:
//	  Nationnum=3;
//		   break;
//	case  8:
//	  Nationnum=4;
//		   break;
//	case  9:
//	  Nationnum=8;
//		   break;
//
//	case 10:
//	  Nationnum=9;
//		   break;
//	case  27:
//	  Nationnum=10;
//		   break;
//	case  47:
//	  Nationnum=27;
//		   break;
//	case  69:
//	  Nationnum=47;
//		   break;
//
//	case  82:
//	  Nationnum=69;
//		   break;
//	 case  133:
//	  Nationnum=82;
//		   break;
//
//	 case  149:
//	  Nationnum=133;
//		   break;
//	 case  160:
//	  Nationnum=149;
//		   break;
//
//	 case  166:
//	  Nationnum=160;
//		   break;
//	case  199:
//	  Nationnum=166;
//		   break;
//
//	case  235:
//	  Nationnum=199;
//		   break;
//
//	case  264:
//	  Nationnum=235;
//		   break;
//
//	case  297:
//	  Nationnum=264;
//		   break;
//	case  326:
//	  Nationnum=297;
//		   break;
//
//	case  352:
//	  Nationnum=326;
//		   break;
//
//	case  391:
//	  Nationnum=352;
//		   break;
//
//	case  410:
//	  Nationnum=391;
//		   break;
//
//   case  439:
//	  Nationnum=410;
//		   break;
//
//   case  458:
//	  Nationnum=439;
//		   break;
//
//   case  462:
//	  Nationnum=458;
//		   break;
//
//	case  465:
//	  Nationnum=462;
//		   break;
//
//   case  511:
//	  Nationnum=465;
//		   break;
//
//	case  531:
//	  Nationnum=511;
//		   break;
//
//	case  544:
//	  Nationnum=531;
//		   break;
//	case  574:
//	  Nationnum=544;
//		   break;
//	case  576:
//	  Nationnum=574;
//		   break;
//
//	case  593:
//	  Nationnum=576;
//		   break;
//	 case  608:
//	  Nationnum=593;
//		   break;
//
//	 case  1:
//	  Nationnum=608;
//		   break;
//
//	 }
//  }
//  else
//  {
  switch(Nationnum)
  {
	 case  1:
	       Nationnum=170;
		   break;
     case  2:
	 case  3:
	       Nationnum--;
		   break;
	 case  25:
	       Nationnum=3;
		   break;
	 case  26:
	       Nationnum=25;
		   break;
	case  29:
	       Nationnum=26;
		   break;

	case  30:
	case  31:
	case  32:
	case  33:
	case  34:
	case  35:
	       Nationnum--;
		   break;
    case  38:
	       Nationnum=35;
		   break;
	case  39:
	case  40:
	       Nationnum--;
		   break;
	 case  45:
	       Nationnum=40;
		   break;
	 
	case  46: 
	case  47: 
	case  48:
	       Nationnum--;
		   break;
	 case  53:
	       Nationnum=48;
		   break;
	 
    case  54: 
	case  55: 
	case  56: 
	case  57: 
	case  58: 
	case  59: 
	case  60: 
	       Nationnum--;
		   break;
	case  62:
	       Nationnum=60;
		   break;
	
	case  63: 
	case  64:
	       Nationnum--;
		   break;
	case  73:
	       Nationnum=64;
		   break;
    
	case  74: 
	case  75: 
	case  76: 
	case  77:
	       Nationnum--;
		   break;
   case  80:
	       Nationnum=77;
		   break;
  	case  81: 
	case  82: 
	       Nationnum--;
		   break;
	case  89:
	       Nationnum=82;
		   break;
	case  90:
	       Nationnum=89;
		   break;
	case  92:
	       Nationnum=90;
		   break;
	 
	case  93: 
	case  94: 
	case  95: 
	case  96:
	case  97: 
	       Nationnum--;
		   break;
    case  99:
	       Nationnum=98;
		   break;
	 case  98:
	       Nationnum=97;
		   break;
	case  105:
	       Nationnum=99;
		   break;
    
	case  106: 
	case  107: 
	case  108: 
    case  109: 
	case  110: 
	case  111: 
	case  112: 
	case  113: 
	case  114: 
	case  115: 
	case  116: 
	case  117: 
	case  118: 
	 case  119:
	       Nationnum--;
		   break;
   case  121:
	       Nationnum=119;
		   break;
     
	case  122: 
	case  123: 
	case  124: 
	case  125: 
	case  126: 
	case  127: 
	case  128: 
	case  129: 
	case  130: 
	case  131: 
	case  132: 
	case  133: 
	case  134:
	       Nationnum--;
		   break;
    case  143:
	       Nationnum=134;
		   break;
 
	case  144: 
	case  145: 
	case  146: 
	case  147: 
	case  148: 
	case  149: 
	case  150:
	       Nationnum--;
		   break;
   case  152:
	       Nationnum=150;
		   break;
	case  154:
	       Nationnum=152;
		   break;
    case  155:
	       Nationnum=154;
		   break;
	 case  156:
	       Nationnum=155;
		   break;
	 case  158:
	       Nationnum=156;
		   break;
	
	 case  159:
	 case  160:
	 case  161:
	 case  162:
	 case  163:
	 case  164:
	 case  165:
	 case  166:
	 case  167:
	 case  168:
	 case  169:
	 case  170:
	       Nationnum--;
		   break;


  }
//  }
}

/////////////////////////////
void FindCityAdd()
{
// if(g_mMenuLangauge==CHANESE)
//  {
//      switch(Nationnum)
//  { 
//     case  1:
//	        Citynum=0;
//		   break;
//	 case  2:
//	  Citynum=0;
//		   break;
//	case  3:
//	  Citynum=0;
//		   break;
//	case  4:
//	   Citynum++;
//		  if(Citynum>3)
//		  {
//		    Citynum=0;
//		  }
//		   break;
//	case  8:
//	  Citynum=0;
//		   break;
//
//	case 9:
//	  Citynum=0;
//		   break;
//	case  10:
//	   Citynum++;
//		  if(Citynum>16)
//		  {
//		    Citynum=0;
//		  }
//		   break;
//	case  27:
//	  Citynum++;
//		  if(Citynum>19)
//		  {
//		    Citynum=0;
//		  }
//		   break;
//	case  47:
//	   Citynum++;
//		  if(Citynum>21)
//		  {
//		    Citynum=0;
//		  }
//		   break;
//
//	case  69:
//	   Citynum++;
//		  if(Citynum>12)
//		  {
//		    Citynum=0;
//		  }
//		   break;
//	 case  82:
//	   Citynum++;
//		  if(Citynum>50)
//		  {
//		    Citynum=0;
//		  }
//		   break;
//
//	 case  133:
//	   Citynum++;
//		  if(Citynum>15)
//		  {
//		    Citynum=0;
//		  }
//		   break;
//	 case  149:
//	   Citynum++;
//		  if(Citynum>10)
//		  {
//		    Citynum=0;
//		  }
//		   break;
//
//	 case  160:
//	   Citynum++;
//		  if(Citynum>5)
//		  {
//		    Citynum=0;
//		  }
//		   break;
//	case  166:
//	   Citynum++;
//		  if(Citynum>32)
//		  {
//		    Citynum=0;
//		  }
//		   break;
//
//	case  199:
//	   Citynum++;
//		  if(Citynum>35)
//		  {
//		    Citynum=0;
//		  }
//		   break;
//
//	case  235:
//	   Citynum++;
//		  if(Citynum>28)
//		  {
//		    Citynum=0;
//		  }
//		   break;
//
//	case  264:
//	  Citynum++;
//		  if(Citynum>32)
//		  {
//		    Citynum=0;
//		  }
//		   break;
//	case  297:
//	   Citynum++;
//		  if(Citynum>28)
//		  {
//		    Citynum=0;
//		  }
//		   break;
//
//	case  326:
//	  Citynum++;
//		  if(Citynum>25)
//		  {
//		    Citynum=0;
//		  }
//		   break;
//
//	case  352:
//	  Citynum++;
//		  if(Citynum>38)
//		  {
//		    Citynum=0;
//		  }
//		   break;
//
//	case  391:
//	   Citynum++;
//		  if(Citynum>18)
//		  {
//		    Citynum=0;
//		  }
//		   break;
//
//   case  410:
//	  Citynum++;
//		  if(Citynum>28)
//		  {
//		    Citynum=0;
//		  }
//		   break;
//
//   case  439:
//	  Citynum++;
//		  if(Citynum>18)
//		  {
//		    Citynum=0;
//		  }
//		   break;
//
//   case  458:
//	   Citynum++;
//		  if(Citynum>3)
//		  {
//		    Citynum=0;
//		  }
//		   break;
//
//	case  462:
//	  Citynum++;
//		  if(Citynum>2)
//		  {
//		    Citynum=0;
//		  }
//		   break;
//
//   case  465:
//	   Citynum++;
//		  if(Citynum>45)
//		  {
//		    Citynum=0;
//		  }
//		   break;
//
//	case  511:
//	  Citynum++;
//		  if(Citynum>19)
//		  {
//		    Citynum=0;
//		  }
//		   break;
//
//	case  531:
//	   Citynum++;
//		  if(Citynum>12)
//		  {
//		    Citynum=0;
//		  }
//		   break;
//	case  544:
//	   Citynum++;
//		  if(Citynum>29)
//		  {
//		    Citynum=0;
//		  }
//		   break;
//	case  574:
//	  Citynum++;
//		  if(Citynum>1)
//		  {
//		    Citynum=0;
//		  }
//		   break;
//
//	case  576:
//	  Citynum++;
//		  if(Citynum>16)
//		  {
//		    Citynum=0;
//		  }
//		   break;
//	 case  593:
//	   Citynum++;
//		  if(Citynum>14)
//		  {
//		    Citynum=0;
//		  }
//		   break;
//
//	 case  608:
//	   Citynum++;
//		  if(Citynum>32)
//		  {
//		    Citynum=0;
//		  }
//		   break;
//
//	 break;
//	 }
//  }
//  else
//  {
  switch(Nationnum)
  {
    
	 case  3:  
	   Citynum++;
		  if(Citynum>21)
		  {
		    Citynum=0;
		  }
		  break;
	       
	case  26:
	case  35: 
	case  77:
     	 Citynum++;
	      if(Citynum>2)
		  {
		    Citynum=0;
		  }
		  break;
	 case  40:
	 case  48:
	       Citynum++;
	      if(Citynum>4)
		  {
		    Citynum=0;
		  }
		   break;
      case  60: 
   	 case  90:
	 case  119:
	   case  150:
	   case  152:
	   case  156:
	       Citynum++;
	      if(Citynum>1)
		  {
		    Citynum=0;
		  }
		   break;

	case  64:
	 case  134:
	         Citynum++;
	      if(Citynum>8)
		  {
		    Citynum=0;
		  }
		   break;

	case  82:
	       Citynum++;
	     if(Citynum>6)
		  {
		    Citynum=0;
		  }
		  break;
	case  99:
	       Citynum++;
	     if(Citynum>5)
		  {
		    Citynum=0;
		  }
		  break;
	 default:
	        Citynum=0;
		   break;


  }
 // }
}

/////////////////////////////
void FindCityDec()
{
//  if(g_mMenuLangauge==CHANESE)
//  {
//        switch(Nationnum)
//  { 
//     case  1:
//	        Citynum=0;
//		   break;
//	 case  2:
//	  Citynum=0;
//		   break;
//	case  3:
//	   Citynum=0;
//		   break;
//	case  4:
//	    if(Citynum==0)
//		  {
//		    Citynum=3;
//		  }
//		  else
//		  {
//		     Citynum--;
//		  }
//		   break;
//	case  8:
//	   Citynum=0;
//		   break;
//
//	case 9:
//	  Citynum=0;
//		   break;
//	case  10:
//	     if(Citynum==0)
//		  {
//		    Citynum=16;
//		  }
//		  else
//		  {
//		     Citynum--;
//		  }
//		   break;
//	case  27:
//	    if(Citynum==0)
//		  {
//		    Citynum=19;
//		  }
//		  else
//		  {
//		     Citynum--;
//		  }
//		   break;
//	case  47:
//	    if(Citynum==0)
//		  {
//		    Citynum=21;
//		  }
//		  else
//		  {
//		     Citynum--;
//		  }
//		   break;
//
//	case  69:
//	    if(Citynum==0)
//		  {
//		    Citynum=12;
//		  }
//		  else
//		  {
//		     Citynum--;
//		  }
//		   break;
//	 case  82:
//	     if(Citynum==0)
//		  {
//		    Citynum=50;
//		  }
//		  else
//		  {
//		     Citynum--;
//		  }
//		   break;
//
//	 case  133:
//	     if(Citynum==0)
//		  {
//		    Citynum=15;
//		  }
//		  else
//		  {
//		     Citynum--;
//		  }
//		   break;
//	 case  149:
//	     if(Citynum==0)
//		  {
//		    Citynum=10;
//		  }
//		  else
//		  {
//		     Citynum--;
//		  }
//		   break;
//
//	 case  160:
//	     if(Citynum==0)
//		  {
//		    Citynum=5;
//		  }
//		  else
//		  {
//		     Citynum--;
//		  }
//		   break;
//	case  166:
//	    if(Citynum==0)
//		  {
//		    Citynum=32;
//		  }
//		  else
//		  {
//		     Citynum--;
//		  }
//		   break;
//
//	case  199:
//	    if(Citynum==0)
//		  {
//		    Citynum=35;
//		  }
//		  else
//		  {
//		     Citynum--;
//		  }
//		   break;
//
//	case  235:
//	     if(Citynum==0)
//		  {
//		    Citynum=28;
//		  }
//		  else
//		  {
//		     Citynum--;
//		  }
//		   break;
//
//	case  264:
//	    if(Citynum==0)
//		  {
//		    Citynum=32;
//		  }
//		  else
//		  {
//		     Citynum--;
//		  }
//		   break;
//	case  297:
//	    if(Citynum==0)
//		  {
//		    Citynum=28;
//		  }
//		  else
//		  {
//		     Citynum--;
//		  }
//		   break;
//
//	case  326:
//	     if(Citynum==0)
//		  {
//		    Citynum=25;
//		  }
//		  else
//		  {
//		     Citynum--;
//		  }
//		   break;
//
//	case  352:
//	     if(Citynum==0)
//		  {
//		    Citynum=38;
//		  }
//		  else
//		  {
//		     Citynum--;
//		  }
//		   break;
//
//	case  391:
//	     if(Citynum==0)
//		  {
//		    Citynum=18;
//		  }
//		  else
//		  {
//		     Citynum--;
//		  };
//		   break;
//
//   case  410:
//	     if(Citynum==0)
//		  {
//		    Citynum=28;
//		  }
//		  else
//		  {
//		     Citynum--;
//		  }
//		   break;
//
//   case  439:
//	     if(Citynum==0)
//		  {
//		    Citynum=18;
//		  }
//		  else
//		  {
//		     Citynum--;
//		  }
//		   break;
//
//   case  458:
//	     if(Citynum==0)
//		  {
//		    Citynum=3;
//		  }
//		  else
//		  {
//		     Citynum--;
//		  }
//		   break;
//
//	case  462:
//	    if(Citynum==0)
//		  {
//		    Citynum=2;
//		  }
//		  else
//		  {
//		     Citynum--;
//		  }
//		   break;
//
//   case  465:
//	    if(Citynum==0)
//		  {
//		    Citynum=45;
//		  }
//		  else
//		  {
//		     Citynum--;
//		  };
//		   break;
//
//	case  511:
//	     if(Citynum==0)
//		  {
//		    Citynum=19;
//		  }
//		  else
//		  {
//		     Citynum--;
//		  }
//		   break;
//
//	case  531:
//	    if(Citynum==0)
//		  {
//		    Citynum=12;
//		  }
//		  else
//		  {
//		     Citynum--;
//		  }
//		   break;
//	case  544:
//	     if(Citynum==0)
//		  {
//		    Citynum=29;
//		  }
//		  else
//		  {
//		     Citynum--;
//		  }
//		   break;
//	case  574:
//	     if(Citynum==0)
//		  {
//		    Citynum=1;
//		  }
//		  else
//		  {
//		     Citynum--;
//		  }
//		   break;
//
//	case  576:
//	    if(Citynum==0)
//		  {
//		    Citynum=16;
//		  }
//		  else
//		  {
//		     Citynum--;
//		  }
//		   break;
//	 case  593:
//	     if(Citynum==0)
//		  {
//		    Citynum=14;
//		  }
//		  else
//		  {
//		     Citynum--;
//		  }
//		   break;
//
//	 case  608:
//	    if(Citynum==0)
//		  {
//		    Citynum=32;
//		  }
//		  else
//		  {
//		     Citynum--;
//		  }
//		   break;
//
//	 }
//  }
//  else
//  {
  switch(Nationnum)
  {
    
	 case  3:
	 
	      
		  if(Citynum==0)
		  {
		    Citynum=21;
		  }
		  else
		  {
		     Citynum--;
		  }
		  break;
	      
	case  26:
	case  35:  
	case  77:
     	  if(Citynum==0)
		  {
		    Citynum=2;
		  }
		  else
		  {
		     Citynum--;
		  }
		  break;
	 case  40:
	 case  48:
	       if(Citynum==0)
		  {
		    Citynum=4;
		  }
		  else
		  {
		     Citynum--;
		  }
		   break;
      case  60: 
   	 case  90:
	 case  119:
	   case  150:
	   case  152:
	   case  156:
	       if(Citynum==0)
		  {
		    Citynum=1;
		  }
		  else
		  {
		     Citynum--;
		  }
		   break;

	case  64:
	 case  134:
	       if(Citynum==0)
		  {
		    Citynum=8;
		  }
		  else
		  {
		     Citynum--;
		  }
		   break;

	case  82:
	        if(Citynum==0)
		  {
		    Citynum=6;
		  }
		  else
		  {
		     Citynum--;
		  }
		  break;
	case  99:
	        if(Citynum==0)
		  {
		    Citynum=5;
		  }
		  else
		  {
		     Citynum--;
		  }
		  break;
	 default:
	        Citynum=0;
		   break;


  }
 // }
}

void SaveCStar()//�����Զ�������
{   
       //�˺�����Ҫ�õ�����ʱ����
   //********************************
   //�ྭ��γ�������ʱ�����������ж������Ƿ���ȷ����ȷ�ŷ��أ�����ȷ����������״̬
   int g_mObjRa_shi_temp,g_mObjRa_fen_temp;//Ŀ��ྭʱ����
   float g_mObjRa_miao_temp;
   int g_mObjDec_du_temp,g_mObjDec_fen_temp;//Ŀ���γ�ȷ���
   float g_mObjDec_miao_temp;
   //******************************** 
   uint8 i;

      //�ѳྭ��γ�ַ����ȡ����������ʱ������
		g_mObjRa_shi_temp= atoi(&g_sysmenu2900ra[5]);
		g_mObjRa_fen_temp= atoi(&g_sysmenu2900ra[8]);
		g_mObjRa_miao_temp= atof(&g_sysmenu2900ra[11]);

		g_mObjDec_du_temp= atoi(&g_sysmenu2900dec[5]);
		g_mObjDec_fen_temp= atoi(&g_sysmenu2900dec[8]);
		g_mObjDec_miao_temp= atof(&g_sysmenu2900dec[11]);
		//������ʱ�����ж��Ƿ�������ȷ��


		if((g_mObjRa_shi_temp>23)||(g_mObjRa_fen_temp>59)||(g_mObjRa_miao_temp>59.99)||(g_mObjDec_du_temp>89)||(g_mObjDec_fen_temp>59)||(g_mObjDec_miao_temp>59.99))
		{
		   if((g_mObjDec_du_temp>89)||(g_mObjDec_fen_temp>59)||(g_mObjDec_miao_temp>59.99))
		   {
		      g_nsysstatus=SYS_MENU_SKY_DEC;	  //��γ���������ȷ��ϵͳ���ص���γ����״̬
			  g_mShowMenucolumn=5;
		   }
		   
		   if((g_mObjRa_shi_temp>23)||(g_mObjRa_fen_temp>59)||(g_mObjRa_miao_temp>59.99))
		   {
		      g_nsysstatus=SYS_MENU_SKY_RA; //�ྭ���������ȷ��ϵͳ���ص��ྭ����״̬
			  g_mShowMenucolumn=6;

			}

		 }
		 else
		{
		  cstar[0]=111;

		  for(i=1;i<9;i++)
		  {
		    cstar[i]=g_sysmenu2900NameEn[i+4];
			
		  }


          cstar[9]=g_sysmenu2900raEn[5]-48;
		  cstar[10]=g_sysmenu2900raEn[6]-48;
		  cstar[11]=g_sysmenu2900raEn[8]-48;
		  cstar[12]=g_sysmenu2900raEn[9]-48;
		  cstar[13]=g_sysmenu2900raEn[11]-48;
		  cstar[14]=g_sysmenu2900raEn[12]-48;
		  cstar[15]=g_sysmenu2900raEn[14]-48;


		  cstar[16]=g_sysmenu2900decEn[4];
		  cstar[17]=g_sysmenu2900decEn[5]-48;
		  cstar[18]=g_sysmenu2900decEn[6]-48;
		  cstar[19]=g_sysmenu2900decEn[8]-48;
		  cstar[20]=g_sysmenu2900decEn[9]-48;
		  cstar[21]=g_sysmenu2900decEn[11]-48;
		  cstar[22]=g_sysmenu2900decEn[12]-48;
		  cstar[23]=g_sysmenu2900decEn[14]-48;
		  
		  WriteCustomStar(g_mFnum,cstar);
		  		
		  FBeep(1);	
		 
		     
		}
   
}

void SaveCLand() //�����Զ���½��Ŀ��
{
       //�˺�����Ҫ�õ�����ʱ����
      //********************************
     //�ྭ��γ�������ʱ�����������ж������Ƿ���ȷ����ȷ�ŷ��أ�����ȷ����������״̬
     int g_mObjRa_shi_temp,g_mObjRa_fen_temp;//Ŀ��ྭʱ����
     float g_mObjRa_miao_temp;
     int g_mObjDec_du_temp,g_mObjDec_fen_temp;//Ŀ���γ�ȷ���
     float g_mObjDec_miao_temp;
     //********************************
	 uint8 i;

      //�ѳྭ��γ�ַ����ȡ����������ʱ������
		g_mObjRa_shi_temp= atoi(&g_sysmenu2900ra[4]);
		g_mObjRa_fen_temp= atoi(&g_sysmenu2900ra[8]);
		g_mObjRa_miao_temp= atof(&g_sysmenu2900ra[11]);

		g_mObjDec_du_temp= atoi(&g_sysmenu2900dec[5]);
		g_mObjDec_fen_temp= atoi(&g_sysmenu2900dec[8]);
		g_mObjDec_miao_temp= atof(&g_sysmenu2900dec[11]);
		//������ʱ�����ж��Ƿ�������ȷ��


		if((g_mObjRa_shi_temp>359)||(g_mObjRa_fen_temp>59)||(g_mObjRa_miao_temp>59.99999)||(g_mObjDec_du_temp>89)||(g_mObjDec_fen_temp>59)||(g_mObjDec_miao_temp>59.99999))
		{
		   if((g_mObjDec_du_temp>89)||(g_mObjDec_fen_temp>59)||(g_mObjDec_miao_temp>59.99999))
		   {
		      g_nsysstatus=SYS_MENU_LAND_ALT;	  //��γ���������ȷ��ϵͳ���ص���γ����״̬
			  g_mShowMenucolumn=6;
		   }
		   
		   if((g_mObjRa_shi_temp>359)||(g_mObjRa_fen_temp>59)||(g_mObjRa_miao_temp>59.99999))
		   {
		      g_nsysstatus=SYS_MENU_LAND_AZI; //�ྭ���������ȷ��ϵͳ���ص��ྭ����״̬
			  g_mShowMenucolumn=6;

			}

		 }
		 else
		 {
		    for(i=1;i<9;i++)
		  {
		    cland[i]=g_sysmenu2900NameEn[i+4];
			
		  }
		  cland[9]=g_sysmenu2900raEn[4]-48;
          cland[10]=g_sysmenu2900raEn[5]-48;
		  cland[11]=g_sysmenu2900raEn[6]-48;
		  cland[12]=g_sysmenu2900raEn[8]-48;
		  cland[13]=g_sysmenu2900raEn[9]-48;
		  cland[14]=g_sysmenu2900raEn[11]-48;
		  cland[15]=g_sysmenu2900raEn[12]-48;
		  cland[16]=g_sysmenu2900raEn[14]-48;


		  cland[17]=g_sysmenu2900decEn[4];
		  cland[18]=g_sysmenu2900decEn[5]-48;
		  cland[19]=g_sysmenu2900decEn[6]-48;
		  cland[20]=g_sysmenu2900decEn[8]-48;
		  cland[21]=g_sysmenu2900decEn[9]-48;
		  cland[22]=g_sysmenu2900decEn[11]-48;
		  cland[23]=g_sysmenu2900decEn[12]-48;
		  cland[24]=g_sysmenu2900decEn[14]-48;

		  WriteCustomLandTarget(g_mFnum,cland); 
		   FBeep(1);	
		 }
}

  void GetRectntTarget(uint8 type,uint32 tnum )
   {
	

                  switch(type)
				  {
						      case  1:
							    g_mSunSysObjectNum=tnum;
							   	GetSunSysObject(g_mSunSysObjectNum,&g_mObjRa1,&g_mObjDec1);
							    for(g_mTempstrnum=0;g_mTempstrnum<21;g_mTempstrnum++)
						        {
						           gstrtemp18[g_mTempstrnum]=g_sysmenu2200object_nameEn[g_mTempstrnum];
							    }
								break;
							  case  2: 
							    g_mCon88ObjectNum=tnum;
					             GetCon88(g_mCon88ObjectNum,&con);
								 sprintf(gstrtemp18,"Constellation %d          ",g_mCon88ObjectNum);	
								 break;	
								case 3:	
								g_mFamousStarObjectNum=tnum;						  
								GetAlignStar(g_mFamousStarObjectNum,&AlnStar);
								//sprintf(gstrtemp18,"Famous Star %d          ",g_mFamousStarObjectNum);	
								for(g_mTempstrnum=0;g_mTempstrnum<13;g_mTempstrnum++)
						        {
						           gstrtemp18[g_mTempstrnum]=AlnStar.NameEn[g_mTempstrnum+1];
							    }
								break;
							  case  4: 	
							  g_mMsrObjectNum=tnum;				
								GetMessier110(g_mMsrObjectNum,&messier);
								sprintf(gstrtemp18,"Messier %d                  ",g_mMsrObjectNum);	
								break;
							  case  5: 
							  	g_mNgcObjectNum=tnum;							
								 GetNGC7840(g_mNgcObjectNum,&ngc);
								 sprintf(gstrtemp18,"NGC %d                        ",g_mNgcObjectNum);
								 break;
							  case  6: 	
							  g_mIcObjectNum=tnum;						
							    GetIC5386(g_mIcObjectNum,&ic);
								sprintf(gstrtemp18,"IC %d                         ",g_mIcObjectNum);	
								break;
							  case  7: 	
							  g_mSh2ObjectNum=tnum;						
								GetSh2313(g_mSh2ObjectNum,&sh2);	
								sprintf(gstrtemp18,"Sh %d                           ",g_mSh2ObjectNum);
								break;
							  case  8: 	
							  	g_mBrightObjectNum=tnum;				
							    GetBright167(g_mBrightObjectNum,&bright);
								sprintf(gstrtemp18,"Bright %d                         ",g_mBrightObjectNum);
								break;
							  case  9: 	
							  g_mSaoObjectNum=tnum;				
							    GetSAO258997(g_mSaoObjectNum,&sao);
								sprintf(gstrtemp18,"SAO %d                          ",g_mSaoObjectNum);
								break;
							  case  10: 
						        GetCustomStar(tnum,&CustomStar);
								sprintf(gstrtemp18,"Sky F%d                 ",tnum);
						       break;
							   case  11: 
						        GetCustomStar(tnum,&CustomStar);
								gstrlineEn17="My Input Data                ";
								 for(g_mTempstrnum=0;g_mTempstrnum<21;g_mTempstrnum++)
						        {
						           gstrtemp18[g_mTempstrnum]=gstrlineEn17[g_mTempstrnum];
							    }
						       break;
					           case 12:  
						        GetCustomLandTarget(tnum,&LandTarget);	  
								sprintf(gstrtemp18,"Land F%d                   ",tnum);	
					         	break;	
				}
}


void SysReset()//ϵͳ��λ������״̬
{
   uint16 page;
   uint8 data[528];
   char s1[20];
    float  lon0,lat0;
    int zone;

   LCDRfrsh();		   	
    DispEn(0,4,1,21,"System resetting...    ");

    page=0;
	 for(page=0;page<16;page++)
	 {
	   ReadFromRom(3549+page,0,528,data);

	   WriteToRom(3529+page,0,528,data);
	 }


	 //***********************************	
	//��λ���ٲ�����ʼ��
	 FSetupPointTrackPara();	
	//***********************************
	//ϵͳ������ʼ��
     FInitPara(); 

	 	 //����λ�������ź���ʶ����λ���ǵ�ƽʽ���ǳ��ʽ	
	 
	 UART1_SentByte(0x55);
	 UART1_SentByte(0xAA);
	 UART1_SentByte(0x01);
	 UART1_SentByte(1);	
	 UART1_SentByte(68);
	 
	 UART1_SentByte(0x55);
	 UART1_SentByte(0xAA);
	 UART1_SentByte(0x01);
	 UART1_SentByte(1);
	 UART1_SentByte(100); 	  

	 UART1_SentByte(0x55);
	 UART1_SentByte(0xAA);
	 UART1_SentByte(0x01);
	 UART1_SentByte(1);
     UART1_SentByte(4);

	 UART1_SentByte(0x55);
	 UART1_SentByte(0xAA);
	 UART1_SentByte(0x01);
	 UART1_SentByte(1);
	 UART1_SentByte(36); 

	 MenuDelay(10);	//��ʱ


	 //***********************************
	if(g_mTelescopeConType==1)
	{
       g_mAzEq=1; //���ʽ
	}
	else
	{
       g_mAzEq=0;  //��ƽʽ
	 }
	 //***********************************
	//***********************************


      g_mTelRABack=0.050;  //�ྭ�ز�

      g_mTelDecBack=0.045;  //��γ�ز�



	  GetTelZero(&azi_zero,&alt_zero); //��ȡ��Զ�����

	  g_mGoto.m_nTescpAPZero=azi_zero; //��Զ����λ��� ,��λ�Ա���ʼ�㣬��Ϊ��
	  g_mGoto.m_nTescpEPZero=alt_zero;//��Զ���߶����  ���߶��Ե�ƽ�㣬����Ϊ��

       GetSite(s1,&lon0,&lat0,&zone);

	   g_mGoto.m_nLongitude=lon0;
	   g_mGoto.m_nAtitude=lat0;
	   g_mTimeZone=zone;


	   g_sysmenu4300sitenameEn[6]=s1[0];
	   g_sysmenu4300sitenameEn[7]=s1[1];
	   g_sysmenu4300sitenameEn[8]=s1[2];
	   g_sysmenu4300sitenameEn[9]=s1[3];
	   g_sysmenu4300sitenameEn[10]=s1[4];
	   g_sysmenu4300sitenameEn[11]=s1[5];
	   g_sysmenu4300sitenameEn[12]=s1[6];
	   g_sysmenu4300sitenameEn[13]=s1[7];

	   if(lon0>0)
	   {
	     sprintf(g_sysmenu4300sitelonEn,"  Lon:E%03dd%02df ",(int)lon0,(int)((lon0-(int)lon0)*60));
		 }
		 else
		 {
		    sprintf(g_sysmenu4300sitelonEn,"  Lon:W%03dd%02df ",(int)lon0,(int)((lon0-(int)lon0)*60));
		 }
	  
	   if(lat0>0)
	   {
	       sprintf(g_sysmenu4300sitelatEn,"  Lat:N%02dd%02df ",(int)lat0,(int)((lat0-(int)lat0)*60));
		 }
		 else
		 {
		   sprintf(g_sysmenu4300sitelatEn,"  Lat:S%02dd%02df ",(int)lat0,(int)((lat0-(int)lat0)*60));
		 }

		 if(zone>0)
		 {
		     sprintf(g_sysmenu4300sitezoneEn," Zone:E%02d",zone);
		 }
		 else
		 {
		   sprintf(g_sysmenu4300sitezoneEn," Zone:W%02d",zone);
		 }

	   
	  
	   MenuDelay(2000);	
	   FBeep(2);
	   MenuDelay(100);
	   g_nsysstatus=SYS_MAINSHOW;
}

//*****************************************************************************
 void FShowStart()//������ʾ
 {
 	    //ϵͳ����������ʾ
		char  S1[]="JSDFJJFDFSGGDVV....VYYYCCCFJJJQQQQ'G'GEEEZZZ'Z'ZZ1'1'2.33ZZZOee000000'e'0eOQJTTTErrrQQQr"; //
		char  S2[]="JFDSS'S'AYFEE//NGGYYMMVVVMMC'C'MEM//M'M'REEEEED12.334.5VOO0000O'A'DEEEeEEA'J'rrrrrQQQ'"; //
		char  S3[]="CervvYYv..VVVeVV1'.'V.90133423578DCCDDD004//'/'/3r38445TD0000000D'T'EFDYYMrrrr'r'rQQQ"; //
		char  S4[]="DF'Y'YDSYYYVV'V'VA'E'F444900'9'GGG9577DDCD..D81763SSSVVVV8ZZA0CCD0A'O'AVVVOODMarrrQ'Q'r"; //



	   	//DispEn(0,3,1,22,"  JOC.GOTO  SYSTEM    ");
	  	 DispEn(0,3,4,1,S2+75);
		 DispEn(0,3,5,1,S4+68);
		 DispEn(0,3,6,1,S2+29);
		 DispEn(0,3,7,1,S3+18);
		 DispEn(0,3,8,1,S1+35);
		 DispEn(0,3,9,1,S4+68);
		 DispEn(0,3,10,1,S3+66);
		 DispEn(0,3,11,1,S4+68);

		 DispEn(0,3,14,1,S2+6);
		 DispEn(0,3,15,1,S4+3);
		 DispEn(0,3,16,1,S2+6);
		 DispEn(0,3,17,1,S3+66);
		 DispEn(0,3,18,1,S4+19);
		 DispEn(0,3,19,1,S2+38);

	    //DispEn(0,5,1,22,"   Ver. 1.9 EQ/AZ     ");
	    DispEn(0,5,5,1,S3+20);
		DispEn(0,5,6,1,S1+70);
		DispEn(0,5,7,1,S3+79);
		DispEn(0,5,8,1,S3+18);

		
		DispEn(0,5,10,1,S1+51);
		DispEn(0,5,11,1,S3+18);
		DispEn(0,5,12,1,S4+29);


		DispEn(0,5,14,1,S4+19);
		DispEn(0,5,15,1,S4+84);
		DispEn(0,5,16,1,S3+45);
		DispEn(0,5,17,1,S2+64);
		DispEn(0,5,18,1,S1+45);

		//DispEn(0,7,1,22," (c)2012  MAXVISION   ");
 }
 //*****************************************************************************





