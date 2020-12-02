//��Զ������ʵ���ļ�TelescopeControl.c
 
//*******************************************
//*******************************************
//**********��Զ�����ƺ���ʵ�� **************
//**********���ߣ�����Ǭ           **********
//**********2008������������̨     **********
//**********lgq@ynao.ac.cn         **********
//*******************************************
//*******************************************

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
#include "TelescopeControl.h"

union INTPOS{
	long int i;
	unsigned char ub[4];
	}sendpos;

union INTSPD{
	int i;
	unsigned char ub[2	];
	}sendspd,sendspda,sendspde;


//$$$$$$$$$$$$$$$��������(ȫ�ֱ���)
GOTOAZDATA g_mGoto;//��Զ����λ����
TSETTING  g_mTelError;//��Զ��װ�ò��������ϵ

double dg_mApos;//��λ����ʱ������(��Χ����)
double dg_mZpos;//�춥����ʱ������(��Χ����)

double dg_mApos0;//У׼ʱ��λ����ʱ������(��Χ����)
double dg_mZpos0;//У׼ʱ�춥����ʱ������(��Χ����)


double ddg_mApos;//��λ����ʱ��������(��Χ����)
double ddg_mZpos;//�춥����ʱ��������(��Χ����)

int g_mAposModify;//��λ���ٵ��ڴ� 0������1������-1����
int g_mZposModify;//�߶ȸ��ٵ��ڴ�  0������1������-1����


double dg_mApos_syn;//��λ����ʱ��ͬ����ʾ��
double dg_mZpos_syn;//�춥����ʱ��ͬ����ʾ��


double syn_mApos;//��λ����ʱ��ͬ����
double syn_mZpos;//�춥����ʱ��ͬ����

uint8 g_mstartOTAset;//����ʱ������Զ���ĳ�ʼָ��

LOCATION  m_nLocation;//�۲��λ�ã������ƽ������
STARRAD   m_nStarRAD;//�۲�Ŀ��λ�ã������ƽ������
STARAZ    m_nStarAZ;//�۲��ƽ���귵��ֵ�������ƽ������

bool g_mTelGoHome;//��Զ���Ƿ��ڹ���״̬

bool g_mEQHn;//���ʽ��Զ��Ŀ���Ƿ��ڵ�ƽ��

double mtest0;
double mtest1;

double mtesta0,mtestz0; 
double mtesta1,mtestz1; 
double mtesta2,mtestz2; 
double mtesta3,mtestz3;

  
extern uint8 BuzCount,BuzOnTime,BuzOffTime;
extern bool g_mGotoHandMoveOK;//��Զ���Ƿ�����ֶ��ˣ���Զ��Ҫ����λ���С��һ��ʱ�����ֶ�����
extern char RTCms;//10�������ֵ��ÿ10ms���ж���1��ÿ���������ж�����
extern  uint8 g_mTelescopeConType;//0û����Զ�����ӣ�1��Զ��Ϊ���ʽ��2��Զ��Ϊ��ƽʽ��3����Զ������


extern int AGuiderRa,AGuiderDec; 

double g_mTempTelEpos;//��Զ���߶���ʱλ��

bool  g_mGotoBeep;

double g_mgwt;//����ʱΪ��ʱ�ĺ���ʱ
float  g_mTelPeriodErrorA[200];	//��λ�ྭ����������¼
float  g_mTelPeriodErrorE[200];	//�߶ȳ�γ����������¼

float  g_mStarAlign[28]; 
uint8   g_mAlignStarNum;

bool g_mLandMark;//��½Ŀ�껹�����Ŀ��,false���Ŀ�꣬true½��Ŀ��
uint8 g_mgotostarttype;//0���Ŀ�꣬1½��Ŀ��

float g_mLandObjAzi	; //��ƽʽ��Զ��½��Ŀ�귽λ
float g_mLandObjAlt	; //��ƽʽ��Զ��½��Ŀ��߶�


uint8 g_mPointNewStarTracking;//ָ���µ��ǲ�����
bool g_mPointNewStar;//�Ƿ�ָ�����µ�һ���ǣ�trueָ��,ָ�˾ʹ�Ϊ����۲���ǣ�falseû��ָ
float g_RecentRa,g_RecentDec;	 //����۲��ǵĳྭ��γ


float g_mAligndAzi,g_mAligndAlt;//	У׼��

float g_mSidTime ;//�ط�����ʱ

			  
uint8 g_mPauseTrack;//�ǲ�����ֹͣ�𶯵ĸ��� 0,���ǣ�1��

uint8 g_mAlignShow;//У׼�����е���ʾ����


double  g_mTelRABack;  //�ྭ�ز�
double  g_mTelDecBack;  //��γ�ز�

double g_mTelRALastPos;
double g_mTelRANextPos;

double g_mTelDecLastPos;
double g_mTelDecNextPos;

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@��Զ������ʵ��
//@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@




//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@��Զ������ʵ��
//@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//���ʽ��Զ����λ���ٺ���
void GotoEQ()
{  		//***********************************************
		//��������
		LOCATION  m_nLocation;
		STARRAD   m_nStarRAD;
		STARAZ    m_nStarAZ;
		TSETTING m_ntsetting;
		ALIGNSTARAZ m_nalignstaraz;

		double m_nApout,m_nZpout;
		double m_nTempStarAzimuth;//�������ж��Ƿ���������Խ)

		double m_nSidTime;//�ط�����ʱ 
		double m_nHourAngle	,m_nHourAngle1;//�ǵ�ʱ��
		double m_nDeclination1;	 
		double m_nAzitrackpid;

	   if(g_mGoto.m_nStartStop)
	   { 
	   
	     if(!g_mTelGoHome)
	     { 
			//************************************************
			//���ݴ���
			m_nLocation.mLongitude=g_mGoto.m_nLongitude;
			m_nLocation.mAtitude=g_mGoto.m_nAtitude;
	
			//*************************************************
			//GOTO״̬���
			g_mGoto.m_nGoto=true;
	
			switch(g_mGoto.m_nObjectType)
			{
			case 1:
				g_mGoto.m_nRightAscension=g_mGoto.m_nRightAscension+g_mRaTrackSpeed;
				if(g_mGoto.m_nRightAscension>=24)
				{
				  g_mGoto.m_nRightAscension=g_mGoto.m_nRightAscension-24;
				 }
				 if(g_mGoto.m_nRightAscension<0)
				{
				  g_mGoto.m_nRightAscension=g_mGoto.m_nRightAscension+24;
				 }

				m_nStarRAD.mRightAscension=g_mGoto.m_nRightAscension;
				m_nStarRAD.mDeclination=g_mGoto.m_nDeclination;
				break;
			default:break;
			}

            //************************************************  	 	   
	
		    //����ط�����ʱ  
		      m_nSidTime=FCalSiderealTime(g_mGoto.m_nSysTimeType,g_mGoto.m_nNutation,g_mGoto.m_nLongitude);
			  g_mSidTime= m_nSidTime;
			//***********************************************

			 //*****************************************
			 FCalStarAEPos(m_nLocation,m_nStarRAD,g_mGoto.m_nSysTimeType,g_mGoto.m_nNutation,&m_nStarAZ);
			
			//***********************************************
			//����Ŀ��ʱ��
			m_nHourAngle=m_nSidTime-m_nStarRAD.mRightAscension;

		
	   		while(m_nHourAngle>=24)
			{
				m_nHourAngle=m_nHourAngle-24;
			}
		    while(m_nHourAngle<0)
			{
				m_nHourAngle=m_nHourAngle+24;
			}


			m_nHourAngle1=m_nHourAngle;
			m_nDeclination1=g_mGoto.m_nDeclination;	

		   //**************************************************
			//����ʱ���������
			m_ntsetting.mTSettingA0=g_mTelError.mTSettingA0;
			m_ntsetting.mTSettingE0=g_mTelError.mTSettingE0;
			m_ntsetting.mTSettingLOS=g_mTelError.mTSettingLOS;
			m_ntsetting.mTSettingNP=g_mTelError.mTSettingNP;
			m_ntsetting.mTSettingEW=g_mTelError.mTSettingEW;
			m_ntsetting.mTSettingNS=g_mTelError.mTSettingNS;


			
			mtesta1=m_nHourAngle;
			mtestz1=g_mGoto.m_nDeclination; 
			
			FAlignStarRAPos(m_ntsetting,&mtesta1,&mtestz1);

			m_nHourAngle1=mtesta1;
			m_nDeclination1=mtestz1; 

			//mtest0=m_nHourAngle1-m_nHourAngle;
			//mtest1=m_nDeclination1-g_mGoto.m_nDeclination;

			g_mAligndAzi=m_nHourAngle1-m_nHourAngle;
			g_mAligndAlt=m_nDeclination1-g_mGoto.m_nDeclination;
			//mtest0=g_mAligndAzi;
			//mtest1=g_mAligndAlt;
			if(g_mPauseTrack==1)
			{
			   	m_nHourAngle1=mtesta1-g_mAligndAzi;
		    	m_nDeclination1=mtestz1-g_mAligndAlt; 
			}
			
			//****************************************************  
						 
			g_mGoto.m_nStarAPos0=m_nHourAngle1*15;
			g_mGoto.m_nHourAngle=m_nHourAngle1;

			//g_mGoto.m_nStarAPosTshow=m_nHourAngle1;
			//g_mGoto.m_nStarEPosTshow=m_nDeclination1;

			 g_mGoto.m_nStarAPosTshow=m_nHourAngle;
			 g_mGoto.m_nStarEPosTshow=g_mGoto.m_nDeclination;

			//****************************************************
		  
		    //���ʽ��Զ��
			if(g_mTelescopeConType==1)
			{	
			       if(m_nLocation.mAtitude>=0) //������
					 {
						 
						  if(m_nHourAngle1>=12)
						 {
						   g_mGoto.m_nStarAPos0=g_mGoto.m_nStarAPos0-180.0;
						 }
			
						 g_mGoto.m_nStarAPos0=g_mGoto.m_nStarAPos0-90.0; 
					
					     g_mGoto.m_nStarEPos0=90.0-m_nDeclination1;				
						 if(m_nHourAngle1<12)
						 {
						    g_mGoto.m_nStarEPos0=-1.0*g_mGoto.m_nStarEPos0;
					    }

					}
					else //�ϰ���
					{
					   
						  if(m_nHourAngle1>=12)
						 {
						   g_mGoto.m_nStarAPos0=g_mGoto.m_nStarAPos0-180;
						 }
						 g_mGoto.m_nStarAPos0=90.0-1.0*g_mGoto.m_nStarAPos0;
			
			
					
						 g_mGoto.m_nStarEPos0=-90.0-m_nDeclination1;
			
						 if(m_nHourAngle1<12)
						 {
						    g_mGoto.m_nStarEPos0=-1.0*g_mGoto.m_nStarEPos0;
					     }
	
					}
								  
				 		 	
					g_mGoto.m_nStarASpeed=3.6;
					g_mGoto.m_nStarESpeed=2.1;
				}
		   //*****************************
			//��ƽʽ��Զ�����ʽ�÷�
			  if(g_mTelescopeConType==2)
			  {	
		             
					 if(m_nLocation.mAtitude>=0) //������
					 {

						g_mGoto.m_nStarAPos0=g_mGoto.m_nStarAPos0+180;
						if(g_mGoto.m_nStarAPos0>360)
						{
						   g_mGoto.m_nStarAPos0=g_mGoto.m_nStarAPos0-360;
					    }

						g_mGoto.m_nStarEPos0=90.0-m_nDeclination1;
					}
					else //�ϰ���
					{
					   	g_mGoto.m_nStarAPos0=g_mGoto.m_nStarAPos0+180;
						if(g_mGoto.m_nStarAPos0>360)
						{
						   g_mGoto.m_nStarAPos0=g_mGoto.m_nStarAPos0-360;
					    }
						g_mGoto.m_nStarAPos0=-1.0*g_mGoto.m_nStarAPos0;
						g_mGoto.m_nStarEPos0=90.0+m_nDeclination1;
		
					}
			
								 		 	
					g_mGoto.m_nStarASpeed=3.6;
					g_mGoto.m_nStarESpeed=3.0;
				}

				//*****************************
				//�����ǵ���Զ������ϵͳλ�� 
			    g_mGoto.m_nStarAPosT=g_mGoto.m_nStarAPos0;
			    g_mGoto.m_nStarEPosT=g_mGoto.m_nStarEPos0;				
	
			//**************************************************
			//��Զ���ڸ���ʱ���Ƿ����ֶ�����
			//if(g_mGoto.m_nTAState==2)
			//{
				g_mGoto.m_nTAHandMovePos=dg_mApos;

				
				
		//	}
			
			//if(g_mGoto.m_nTEState==2)
		//	{
				g_mGoto.m_nTEHandMovePos=-1.0*dg_mZpos;
				
		//	}  
		    // mtest0=dg_mApos;//g_mGoto.m_nTEHandMovePos;
			//  mtest1=g_mGoto.m_nTAHandMovePos;
			//**************************************************
	       	//��Զ������ʱ���ֶ�������
			
           
			g_mGoto.m_nStarAPos=g_mGoto.m_nStarAPosT+g_mGoto.m_nTAHandMovePos+g_mGoto.m_nGuidMoveRa;

		    //if(g_mHandSpeed>4)																		  
			//{

//				if((g_mGoto.m_nTEHandMovePos<0)&&(g_mGoto.m_nStarEPosT-g_mGoto.m_nTEHandMovePos>0))
//				{
//				  	g_mGoto.m_nStarEPos=g_mGoto.m_nStarEPosT-g_mGoto.m_nTEHandMovePos;
//				  
//				}
//				else
//				{
//				  	if(g_mGoto.m_nTescpEPos>=0)
//					{
//					    g_mGoto.m_nStarEPos=g_mGoto.m_nStarEPosT+g_mGoto.m_nTEHandMovePos;
//					 }
//					 else
//					 {  
//					    g_mGoto.m_nStarEPos=g_mGoto.m_nStarEPosT-g_mGoto.m_nTEHandMovePos;
//					 }
//				}

				   
				   if(g_mGoto.m_nTescpEPos>=0)
					{
					    g_mGoto.m_nStarEPos=g_mGoto.m_nStarEPosT+g_mGoto.m_nTEHandMovePos+g_mGoto.m_nGuidMoveDec;
					 }
					 else
					 {  
					    g_mGoto.m_nStarEPos=g_mGoto.m_nStarEPosT-g_mGoto.m_nTEHandMovePos-g_mGoto.m_nGuidMoveDec;
					 }


					  //g_mGoto.m_nStarEPos=g_mGoto.m_nStarEPosT+g_mGoto.m_nTEHandMovePos;



			  //mtest1=g_mGoto.m_nStarEPos;
             // mtest0=g_mGoto.m_nTEHandMovePos;


			 //}
			 //else
			 //{
			     //g_mGoto.m_nStarEPos=g_mGoto.m_nStarEPosT-g_mGoto.m_nTEHandMovePos;       
			 //}


		}
		else
		{
		   g_mGoto.m_nStarAPos0=-180;
		   g_mGoto.m_nStarEPos0=90;
		   g_mGoto.m_nStarAPosT=0;
		   g_mGoto.m_nStarEPosT=0;

		   g_mGoto.m_nStarAPos=0;
		   g_mGoto.m_nStarEPos=0;

		   g_mGoto.m_nStarASpeed=3.6;
		   g_mGoto.m_nStarESpeed=3.0;

		  		  	   
		 }

		/*//**************************************************
         //�ж����Ƿ���������Խ
         if(g_mGoto.m_nStarAPos-m_nTempStarAzimuth>180)
		 {
			 g_mGoto.m_nTCrossZeroP=true;//��Զ��������ʱ������Խ
		 }
		 else if(g_mGoto.m_nStarAPos-m_nTempStarAzimuth<-180)
		 {

	         g_mGoto.m_nTCrossZeroN=true;//��Զ��������ʱ�и���Խ
		 }
         //��������Խʱ�����괦��

		 if(g_mGoto.m_nTCrossZeroP)
		 {
			 g_mGoto.m_nStarAPos=g_mGoto.m_nStarAPos-360;
		 }
		 if(g_mGoto.m_nTCrossZeroN)
		 {
			 g_mGoto.m_nStarAPos=g_mGoto.m_nStarAPos+360;
		 }
		//**************************************************
        //��Զ����λʱ�������λ(��λ�ϵ���̾���)�ж�
		 if(g_mGoto.m_nTPointDirect==0)
		 {
		    if(g_mGoto.m_nStarAPos-g_mGoto.m_nTescpAPos>180)
			{
				g_mGoto.m_nTPointDirect=-1;
			}
			else if(g_mGoto.m_nStarAPos-g_mGoto.m_nTescpAPos<-180)
			{
				g_mGoto.m_nTPointDirect=1;
			}

		 }
		 //��������λʱλ�ô���
		 if(g_mGoto.m_nTPointDirect==-1)
		 {
			 g_mGoto.m_nStarAPos=g_mGoto.m_nStarAPos-360;
		 }
		 if(g_mGoto.m_nTPointDirect==1)
		 {
			 g_mGoto.m_nStarAPos=g_mGoto.m_nStarAPos+360;
		 }*/

        //***********************************************
	    //�ж���Զ������Ķ�λ���ٷ���

			
	   /*
		while(g_mGoto.m_nStarAPos-g_mGoto.m_nTescpAPos>180)
		{
			g_mGoto.m_nStarAPos=g_mGoto.m_nStarAPos-360;
		}
		while(g_mGoto.m_nStarAPos-g_mGoto.m_nTescpAPos<-180)
		{
			g_mGoto.m_nStarAPos=g_mGoto.m_nStarAPos+360;
		}
		   */

        //***********************************************
	
		//��ȡ��Զ����λ��
		//FReadTelescopePos(&(g_mGoto.m_nTescpAPos),&(g_mGoto.m_nTescpEPos));//��ȡ��Զ���ķ���λ��	
		//GF_ReadAZPos(); 
		//g_mGoto.m_nTescpAPos=g_mTapos;
		//g_mGoto.m_nTescpEPos=g_mTzpos;
         
		//��Զ����λ���Ѿ��Ӵ����ж����ȡ
		
		
		g_mGoto.m_nAPosError=g_mGoto.m_nStarAPos-g_mGoto.m_nTescpAPos;//��λ�����ǵ�λ��-��Զ��λ��),�Զȱ�ʾ
		g_mGoto.m_nEPosError=g_mGoto.m_nStarEPos-g_mGoto.m_nTescpEPos;//�߶������ǵ�λ��-��Զ��λ��),�Զȱ�ʾ
		
	
		//mtest0=g_mGoto.m_nEPosError;
	

	
				
	  	//************************************************
		//��Զ���ڶ�λ����ʱ�Ĵ���
		if(g_mGoto.m_nTAState==0)
		{
			if(g_mGoto.m_nTescpASpeed>400)
			{
				g_mGoto.m_nTescpASpeed=400+fabs(g_mGoto.m_nStarASpeed);
			}
			else
			{
				g_mGoto.m_nTescpASpeed+=10;
			}
		} 
		
		if(g_mGoto.m_nTEState==0)
		{
			if(g_mGoto.m_nTescpESpeed>400)
			{
				g_mGoto.m_nTescpESpeed=400+fabs(g_mGoto.m_nStarESpeed);
			}
			else
			{
				g_mGoto.m_nTescpESpeed+=10;
			}
		} 
		//***********************************************
		//�жϸ�������Ƿ���󣬹���ʱ���ö�λ���������
		if((fabs(g_mGoto.m_nAPosError)>0.11)&&(g_mGoto.m_nTAState==2))
		{
			g_mGoto.m_nTAState=0;
			if(g_mHandSpeed>6)
			{
			   g_mGotoBeep=true;//����Ƶ�ʸ�
			 }
		}
		
		if((fabs(g_mGoto.m_nEPosError)>0.11)&&(g_mGoto.m_nTEState==2))
		{
			g_mGoto.m_nTEState=0;
			if(g_mHandSpeed>6)
			{
			  g_mGotoBeep=true;	//����Ƶ�ʸ�
			 }
		}

	   //����Ƶ�ʵ�
        if((fabs(g_mGoto.m_nAPosError)>10)||(fabs(g_mGoto.m_nEPosError)>5))
		{
			g_mGotoBeep=true;
		}

		
		//************************************************
		
		
		
		//************************************************
		//����λ������λ�Ƿ�������״̬
		if((fabs(g_mGoto.m_nAPosError)<=15.0)&&((g_mGoto.m_nTAState==0)||(g_mGoto.m_nTAState==1)))//����һ��������
		{  
			g_mGoto.m_nTAState=1;//������Զ����״̬Ϊ����״̬
			//һ�����������ٶȺͼ��ٶ�����
			
			if(g_mGoto.m_nTescpASpeed>180)
			{
			   g_mGoto.m_nTescpASpeed=g_mGoto.m_nTescpASpeed-10;
			 }
			 else
			 {
			   //g_mGoto.m_nTescpASpeed=180;
				if(g_mGoto.m_nTescpASpeed<180)
				{
					g_mGoto.m_nTescpASpeed+=10;
				}
				else
				{
					g_mGoto.m_nTescpASpeed=180;
				}
			 }


			if(fabs(g_mGoto.m_nAPosError)<=10.0)//�������������
			{
				//g_mGoto.m_nTescpASpeed=150+fabs(g_mGoto.m_nStarASpeed);
				if(g_mGoto.m_nTescpASpeed<150)
				{
					g_mGoto.m_nTescpASpeed+=10;
				}
				else
				{
					g_mGoto.m_nTescpASpeed=150+fabs(g_mGoto.m_nStarASpeed);
				}
			}

			if(fabs(g_mGoto.m_nAPosError)<=5.0)//��������������
			{
				
				//g_mGoto.m_nTescpASpeed=120+fabs(g_mGoto.m_nStarASpeed);
				if(g_mGoto.m_nTescpASpeed<120)
				{
					g_mGoto.m_nTescpASpeed+=10;
				}
				else
				{
					g_mGoto.m_nTescpASpeed=120+fabs(g_mGoto.m_nStarASpeed);;
				}

			}
			if(fabs(g_mGoto.m_nAPosError)<=3.0)//�����ļ�������
			{
				//g_mGoto.m_nTescpASpeed=80+fabs(g_mGoto.m_nStarASpeed);
				if(g_mGoto.m_nTescpASpeed<80)
				{
					g_mGoto.m_nTescpASpeed+=10;
				}
				else
				{
					g_mGoto.m_nTescpASpeed=80+fabs(g_mGoto.m_nStarASpeed);;
				}
			}
			
			if(fabs(g_mGoto.m_nAPosError)<=1.0)//�����弶������
			{
				g_mGoto.m_nTescpASpeed=50+fabs(g_mGoto.m_nStarASpeed);
			}
			if(fabs(g_mGoto.m_nAPosError)<=0.1)//����������������
			{
				g_mGoto.m_nTescpASpeed=10+fabs(g_mGoto.m_nStarASpeed);
			}
			if(fabs(g_mGoto.m_nAPosError)<=0.01)//���������
			{
				g_mGoto.m_nTAState=2;///������Զ����λ��״̬Ϊ����
			//	m_tempRAstatus=0;	
			}
		}
		//************************************************
		
		//************************************************
		//���ٸ߶����Ƿ����߶ȼ�����
		if((fabs(g_mGoto.m_nEPosError)<=15.0)&&((g_mGoto.m_nTEState==0)||(g_mGoto.m_nTEState==1)))//����һ��������
		{
			g_mGoto.m_nTEState=1;///������Զ����״̬
			//g_mGoto.m_nTescpESpeed=350+fabs(g_mGoto.m_nStarESpeed);

            if(g_mGoto.m_nTescpESpeed>180)
			{
			   g_mGoto.m_nTescpESpeed=g_mGoto.m_nTescpESpeed-10;
			}
			else
			{
			   //g_mGoto.m_nTescpESpeed=180;
			   	if(g_mGoto.m_nTescpESpeed<180)
				{
					g_mGoto.m_nTescpESpeed+=10;
				}
				else
				{
					g_mGoto.m_nTescpESpeed=180;
				}
			}
		    if(fabs(g_mGoto.m_nEPosError)<=10.0)//�������������
			{
								
				//g_mGoto.m_nTescpESpeed=150+fabs(g_mGoto.m_nStarESpeed);
				if(g_mGoto.m_nTescpESpeed<150)
				{
					g_mGoto.m_nTescpESpeed+=10;
				}
				else
				{
					g_mGoto.m_nTescpESpeed=150+fabs(g_mGoto.m_nStarESpeed);;
				}
			}

			if(fabs(g_mGoto.m_nEPosError)<=5.0)//��������������
			{
			

			  //g_mGoto.m_nTescpESpeed=120+fabs(g_mGoto.m_nStarESpeed);
			    if(g_mGoto.m_nTescpESpeed<120)
				{
					g_mGoto.m_nTescpESpeed+=10;
				}
				else
				{
					g_mGoto.m_nTescpESpeed=120+fabs(g_mGoto.m_nStarESpeed);
				}

			}
			if(fabs(g_mGoto.m_nEPosError)<=3.0)//��������������
			{
							 	
				//g_mGoto.m_nTescpESpeed=80+fabs(g_mGoto.m_nStarESpeed);
				if(g_mGoto.m_nTescpESpeed<80)
				{
					g_mGoto.m_nTescpESpeed+=10;
				}
				else
				{
					g_mGoto.m_nTescpESpeed=80+fabs(g_mGoto.m_nStarESpeed);;
				}

			}
			if(fabs(g_mGoto.m_nEPosError)<=1.0)//�����ļ�������
			{
			
				g_mGoto.m_nTescpESpeed=50+fabs(g_mGoto.m_nStarESpeed);

			}
			if(fabs(g_mGoto.m_nEPosError)<=0.1)//�����弶������
			{
				
				g_mGoto.m_nTescpESpeed=20+fabs(g_mGoto.m_nStarESpeed);

			}

			if(fabs(g_mGoto.m_nEPosError)<=0.05)//�������
			{
				g_mGoto.m_nTEState=2;///������Զ���ĸ߶ȸ���״̬	
			}
		}
	
	
	 if((g_mGoto.m_nTAState==2)&&(g_mGoto.m_nTEState==2))
	   {
	      g_mGotoHandMoveOK=true;
		  if(g_mGotoBeep)
		  {
		      FBeep(1);
		  }
		  g_mGotoBeep=false;
		  g_mTelStatus=2;
	   }
	   else
	   {
	      g_mTelStatus=1;
	  }
		//�˳���Զ������ 
	   if((g_mGoto.m_nTAState==2)&&(g_mGoto.m_nTEState==2)&&g_mTelGoHome)
	   { 
	   	 g_mGoto.m_nStartStop=false;//������Զ����λ�ˣ��˳�
		 g_mGoto.m_nGoto=false;
		 g_mGotoHandMoveOK=false;
	     FBeep(1);
		 g_mTelStatus=100;
	   }
	  	 
		//************************************************
		
		//************************************************
		//��Զ���ķ�λ����
		if(g_mGoto.m_nTAState==2)
		{   
			m_nApout=FPointStarAlgorithm(2,1,g_mGoto.m_nAPosEIZero,g_mGoto.m_nAPosError,g_mGoto.m_nStarASpeed);
		}
		//**********************************************
		
		//**********************************************
		//��Զ���ĸ߶ȸ���
		if(g_mGoto.m_nTEState==2)///ϵͳ�ڸ���״̬�ͼ���λ�û�
		{   
			m_nZpout=FPointStarAlgorithm(g_mGoto.m_nTescpType,2,g_mGoto.m_nEPosEIZero,g_mGoto.m_nEPosError,g_mGoto.m_nStarESpeed);
		}
		//************************************************
		//���Ŀ������
		if(g_mGoto.m_nTAState==2)//����ʱ��������ٵ��ٶ�//�����䶨λ�ٶ�
		{  
		
		   
		   	if(g_mAposModify==0)
			{
			   m_nAzitrackpid=100000.0*m_nApout*m_nApout*m_nApout*m_nApout*m_nApout*m_nApout-0.05;
			   //mtest0=m_nAzitrackpid;
			   g_mGoto.m_nTescpASpeed=fabs(g_mGoto.m_nStarASpeed)/9.5+m_nAzitrackpid;	//��ֵ=0.378���ʽ�����ȶ�9.5
			}
			else
		    {
			   m_nAzitrackpid=100000.0*m_nApout*m_nApout*m_nApout*m_nApout*m_nApout*m_nApout-0.05;
			   g_mGoto.m_nTescpASpeed=fabs(g_mGoto.m_nStarASpeed)/9.5+fabs(m_nAzitrackpid);  
		    }

//		    m_tempRAstatus=m_tempRAstatus+10.0*g_mGoto.m_nAPosError;
//			g_mGoto.m_nTescpASpeed=g_mGoto.m_nTescpASpeed+m_tempRAstatus;

//			g_mGoto.m_nTescpASpeed=g_mGoto.m_nTescpASpeed/30.0;
//            if(fabs(g_mGoto.m_nAPosError)<25.0/3600.0)
//			{
//			    m_tempRAstatus=m_tempRAstatus+1;
//				if(m_tempRAstatus>20)
//				{
//				  m_tempRAstatus=25;
//			      g_mGoto.m_nTescpASpeed=0.377;
//				}
//			}
//		   else
//		   {
//		      if(m_tempRAstatus>21)
//			  {
//			    m_tempRAstatus=m_tempRAstatus-1;
//			   }
//			   else
//			   {
//			    m_tempRAstatus=0;
//			   }
//		   }

		  // mtest0=g_mGoto.m_nTescpASpeed;


			
			if(g_mGoto.m_nTescpASpeed<0)
			{
				g_mGoto.m_nTescpASpeed=0;
			}
		}
    	
		//*************************************************
		if(g_mGoto.m_nTEState==2)//����ʱ��������ٵ��ٶ�//�����䶨λ�ٶ�
		{
		    if(g_mZposModify==0)
			{
			   g_mGoto.m_nTescpESpeed=fabs(g_mGoto.m_nStarESpeed)+m_nZpout;
			 }
			 else
			 {
			   g_mGoto.m_nTescpESpeed=fabs(g_mGoto.m_nStarESpeed)+fabs(m_nZpout);
			 }

			if(g_mGoto.m_nTescpESpeed<0)
			{
				g_mGoto.m_nTescpESpeed=0;
			}
			
		}
		   		
		
		//**********************************************
		//����Զ����������ź�
		//if(m_nStarAZ.mAtitude<0)
		//{
		   //g_mEQHn=true;
		//}

		//if(!g_mEQHn)
		if(m_nStarAZ.mAtitude>=0)
		{
		   //if(m_nStarAZ.mAtitude>0)
		   //{
			   if(!g_mTelGoHome)
			   {
			     FDriveTelescope(g_mGoto.m_nTescpASpeed,g_mGoto.m_nTescpESpeed);
				}
				else
				{
	
	
				  FDriveTelescope(g_mGoto.m_nTescpASpeed,g_mGoto.m_nTescpESpeed);  
				}
			//}
			//else
			//{
			  //FDriveTelescope(0,0);
			  //g_mGoto.m_nTAState=2;
			  //g_mGoto.m_nTEState=2;
			  //g_mTelStatus=3;

			//}


		  // g_mGoto.m_nUnderhorizon=false;//���ڵ�ƽ���µı�־Ϊ��
		  
		}
		else
		{
	    	FDriveTelescope(0,0);
			g_mGoto.m_nStartStop=false;//��Զ���ڵ�ƽ���£�ֹͣ����
			g_mGoto.m_nGoto=false;
            g_mGoto.m_nUnderhorizon=true;//���ڵ�ƽ���µı�־Ϊ��
			g_mTelStatus=3;

			
		}

		 //**********************************************

		  if(!g_mTelGoHome)
		  {
			   if((g_mTempTelEpos==g_mGoto.m_nTescpEPos)&&(g_mGoto.m_nTEState!=2))
			   {
			      FStartGoto();
			   }
			   g_mTempTelEpos=g_mGoto.m_nTescpEPos;
		   }
		   
		   
		   
		   	
		
       }
	   else
	   {  
		   if(g_mGoto.m_nGoto)
		   {
		      FDriveTelescope(0,0);
			  g_mGoto.m_nGoto=false;
		   }
	   }

	  


   }
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//��ƽʽ��Զ����λ���ٺ���
void GotoAZ()
{   
		//***********************************************
		//��������
		LOCATION  m_nLocation;
		STARRAD   m_nStarRAD;
		STARAZ    m_nStarAZ;
		TSETTING m_ntsetting;
		ALIGNSTARAZ m_nalignstaraz;

		double m_nApout,m_nZpout;
		double m_nTempStarAzimuth;//�������ж��Ƿ���������Խ)

		double m_nSidTime;//�ط�����ʱ 
		double m_nHourAngle	;//�ǵ�ʱ��

				
	   if(g_mGoto.m_nStartStop)
	   { 
	   
	     if(!g_mTelGoHome)
	     { 
			//************************************************
			//���ݴ���
			m_nLocation.mLongitude=g_mGoto.m_nLongitude;
			m_nLocation.mAtitude=g_mGoto.m_nAtitude;
	
			//*************************************************
			//GOTO״̬���
			g_mGoto.m_nGoto=true;
	
			switch(g_mGoto.m_nObjectType)
			{
			case 1:
			    g_mGoto.m_nRightAscension=g_mGoto.m_nRightAscension+g_mRaTrackSpeed;
				while(g_mGoto.m_nRightAscension>=24)
				{
				  g_mGoto.m_nRightAscension=g_mGoto.m_nRightAscension-24;
				 }
				 while(g_mGoto.m_nRightAscension<0)
				{
				  g_mGoto.m_nRightAscension=g_mGoto.m_nRightAscension+24;
				 }
				m_nStarRAD.mRightAscension=g_mGoto.m_nRightAscension;
				m_nStarRAD.mDeclination=g_mGoto.m_nDeclination;
				break;
//			case 2:
//				break;
//				break;
//			case 3:
//				break;
//				break;
//			case 4:
//				break;
//				break;
//			case 5:
//				break;
//				break;
//			case 6:
//				break;
			default:break;
			}

           //************************************************
		//************************************************
		
	      		//��λ�ϴε����걣��
				m_nTempStarAzimuth=g_mGoto.m_nStarAPos;
		
		        if(!g_mLandMark)//��½Ŀ�껹�����Ŀ��,false���Ŀ�꣬true½��Ŀ��
				{//************************************************
					  //�����ǵĵ�ƽ����
	
			        FCalStarAEPos(m_nLocation,m_nStarRAD,g_mGoto.m_nSysTimeType,g_mGoto.m_nNutation,&m_nStarAZ);
				
				 		
					g_mGoto.m_nStarAPos0=m_nStarAZ.mASzimuth;
					g_mGoto.m_nStarEPos0=m_nStarAZ.mZenith;

				//	mtesta0=g_mGoto.m_nStarAPos0;
				//	mtestz0=g_mGoto.m_nStarEPos0;
	
				
				   
			        g_mGoto.m_nStarASpeed=m_nStarAZ.mAzimuthSpeed;
				    g_mGoto.m_nStarESpeed=m_nStarAZ.mZenithSpeed;
					
					
				
					//**************************************************
					//�����ǵ�λ�ø���
					m_ntsetting.mTSettingA0=g_mTelError.mTSettingA0;
					m_ntsetting.mTSettingE0=g_mTelError.mTSettingE0;
					m_ntsetting.mTSettingLOS=g_mTelError.mTSettingLOS;
					m_ntsetting.mTSettingNP=g_mTelError.mTSettingNP;
					m_ntsetting.mTSettingEW=g_mTelError.mTSettingEW;
					m_ntsetting.mTSettingNS=g_mTelError.mTSettingNS;
		
					m_nalignstaraz.mSAzimuth=g_mGoto.m_nStarAPos0;
					m_nalignstaraz.mSZenith=g_mGoto.m_nStarEPos0;
			
				 	           	       
		
					FAlignStarAEPos(m_ntsetting,&m_nalignstaraz);

			
			
			        g_mGoto.m_nStarAPosT=m_nalignstaraz.mTSAzimuth;
			        g_mGoto.m_nStarEPosT=m_nalignstaraz.mTSZenith;


					//mtesta1=g_mGoto.m_nStarAPosT;
					//mtestz1=g_mGoto.m_nStarEPosT;
					g_mGoto.m_nStarAPosTshow=g_mGoto.m_nStarAPos0;//g_mGoto.m_nStarAPosT;
					g_mGoto.m_nStarEPosTshow=g_mGoto.m_nStarEPos0;//g_mGoto.m_nStarEPosT;
	
						
					//�����������
					//g_mGoto.m_nAirR=FAirRefraction(g_mGoto.m_nAirT,g_mGoto.m_nAirP,g_mGoto.m_nStarEPos0);					
					//g_mGoto.m_nStarEPosT=g_mGoto.m_nStarEPosT-g_mGoto.m_nAirR;


				//	mtesta2=g_mGoto.m_nStarAPosT;
				//	mtestz2=g_mGoto.m_nStarEPosT;
				}
			
		   
			//��Զ���ڸ���ʱ���Ƿ����ֶ�����
			//if(g_mGoto.m_nTAState==2)
			//{
				g_mGoto.m_nTAHandMovePos=dg_mApos;
				
		//	}
			
			//if(g_mGoto.m_nTEState==2)
		//	{
				g_mGoto.m_nTEHandMovePos=-1.0*dg_mZpos;
				
		//	}
		 // mtest1=g_mGoto.m_nTEHandMovePos;



		   //���������ǽ�����Զ����ʼ���򱱷�,���Ӿ���ָ���춥
		   //g_mGoto.m_nStarAPosT=g_mGoto.m_nStarAPosT+180;
		   //g_mGoto.m_nStarEPosT=g_mGoto.m_nStarEPosT-90;
		   ///////////////////////////////////////////////////////
		   //��������Ϊ����λ�õĳ�ʼ������λ����ôתΪ��Զ��ԭʼ������ֵ

		   g_mGoto.m_nStarAPosT=(g_mGoto.m_nStarAPosT+180)-g_mGoto.m_nTescpAPZero;//��λ-��㣬��180+�Ϸ�λ��-���
		   g_mGoto.m_nStarEPosT=g_mGoto.m_nTescpEPZero-(90-g_mGoto.m_nStarEPosT); //���-�߶ȣ����-��90-�춥�ࣩ



		   	if(g_mLandMark)//��½Ŀ�껹�����Ŀ��,false���Ŀ�꣬true½��Ŀ��
			{
				    g_mGoto.m_nStarASpeed=10;
				    g_mGoto.m_nStarESpeed=10;

					g_mGoto.m_nStarAPosT=g_mLandObjAzi;
			        g_mGoto.m_nStarEPosT=-1.0*g_mLandObjAlt;

				    g_mGoto.m_nStarAPos0=g_mLandObjAzi-180.0;
			        g_mGoto.m_nStarEPos0=90-g_mLandObjAlt;
					g_mGoto.m_nStarEPos=g_mLandObjAlt;

					//FBeep(3);
			}	 
		
			 
			//**************************************************
	       	//��Զ������ʱ���ֶ�������
			
			g_mGoto.m_nStarAPos=g_mGoto.m_nStarAPosT+g_mGoto.m_nTAHandMovePos;
			g_mGoto.m_nStarEPos=g_mGoto.m_nStarEPosT+g_mGoto.m_nTEHandMovePos;


			 //mtest0=g_mGoto.m_nTAHandMovePos;
			 //mtest1=g_mGoto.m_nTEHandMovePos;
	    
		}
		else	  
		{
//		   g_mGoto.m_nStarAPos0=-180;
//		   g_mGoto.m_nStarEPos0=90;
//		   g_mGoto.m_nStarAPosT=0;
//		   g_mGoto.m_nStarEPosT=0;

		   g_mGoto.m_nStarAPos=0;
		   g_mGoto.m_nStarEPos=0;
		   g_mGoto.m_nStarASpeed=10;
		   g_mGoto.m_nStarESpeed=10;
		 }

		 //mtesta3=g_mGoto.m_nStarAPosT;
		 //mtestz3=g_mGoto.m_nStarEPosT;

		/*//**************************************************
         //�ж����Ƿ���������Խ
         if(g_mGoto.m_nStarAPos-m_nTempStarAzimuth>180)
		 {
			 g_mGoto.m_nTCrossZeroP=true;//��Զ��������ʱ������Խ
		 }
		 else if(g_mGoto.m_nStarAPos-m_nTempStarAzimuth<-180)
		 {

	         g_mGoto.m_nTCrossZeroN=true;//��Զ��������ʱ�и���Խ
		 }
         //��������Խʱ�����괦��

		 if(g_mGoto.m_nTCrossZeroP)
		 {
			 g_mGoto.m_nStarAPos=g_mGoto.m_nStarAPos-360;
		 }
		 if(g_mGoto.m_nTCrossZeroN)
		 {
			 g_mGoto.m_nStarAPos=g_mGoto.m_nStarAPos+360;
		 }
		//**************************************************
        //��Զ����λʱ�������λ(��λ�ϵ���̾���)�ж�
		 if(g_mGoto.m_nTPointDirect==0)
		 {
		    if(g_mGoto.m_nStarAPos-g_mGoto.m_nTescpAPos>180)
			{
				g_mGoto.m_nTPointDirect=-1;
			}
			else if(g_mGoto.m_nStarAPos-g_mGoto.m_nTescpAPos<-180)
			{
				g_mGoto.m_nTPointDirect=1;
			}

		 }
		 //��������λʱλ�ô���
		 if(g_mGoto.m_nTPointDirect==-1)
		 {
			 g_mGoto.m_nStarAPos=g_mGoto.m_nStarAPos-360;
		 }
		 if(g_mGoto.m_nTPointDirect==1)
		 {
			 g_mGoto.m_nStarAPos=g_mGoto.m_nStarAPos+360;
		 }*/

        //***********************************************
	    //�ж���Զ������Ķ�λ���ٷ���
    	/*while(g_mGoto.m_nStarAPos-g_mGoto.m_nTescpAPos>180)
		{
			g_mGoto.m_nStarAPos=g_mGoto.m_nStarAPos-360;
		}
		while(g_mGoto.m_nStarAPos-g_mGoto.m_nTescpAPos<-180)
		{
			g_mGoto.m_nStarAPos=g_mGoto.m_nStarAPos+360;
		}*/
        //***********************************************
	
		//��ȡ��Զ����λ��
		//FReadTelescopePos(&(g_mGoto.m_nTescpAPos),&(g_mGoto.m_nTescpEPos));//��ȡ��Զ���ķ���λ��	
		//GF_ReadAZPos(); 
		//g_mGoto.m_nTescpAPos=g_mTapos;
		//g_mGoto.m_nTescpEPos=g_mTzpos;
         
		//��Զ����λ���Ѿ��Ӵ����ж����ȡ
		
		
		g_mGoto.m_nAPosError=g_mGoto.m_nStarAPos-g_mGoto.m_nTescpAPos;//��λ�����ǵ�λ��-��Զ��λ��),�Զȱ�ʾ
		g_mGoto.m_nEPosError=g_mGoto.m_nStarEPos-g_mGoto.m_nTescpEPos;//�߶������ǵ�λ��-��Զ��λ��),�Զȱ�ʾ
		
	//	mtest0=g_mGoto.m_nAPosError*3600.0;//3600.0*(g_mGoto.m_nTescpAPos-mtest1);//g_mGoto.m_nAPosError*3600.0;
		//mtest1=g_mGoto.m_nEPosError*3600.0;//g_mGoto.m_nTescpAPos;//g_mGoto.m_nEPosError*3600.0;
	
		//************************************************
		//��Զ���ڶ�λ����ʱ�Ĵ���
		if(g_mGoto.m_nTAState==0)
		{
			if(g_mGoto.m_nTescpASpeed>g_mGoto.m_nTescpASpeedMax)
			{
				g_mGoto.m_nTescpASpeed=g_mGoto.m_nTescpASpeedMax+fabs(g_mGoto.m_nStarASpeed)/10.0;
			}
			else
			{
				g_mGoto.m_nTescpASpeed+=g_mGoto.m_nTescpAAcc;
			}
		} 
		
		if(g_mGoto.m_nTEState==0)
		{
			if(g_mGoto.m_nTescpESpeed>g_mGoto.m_nTescpESpeedMax)
			{
				g_mGoto.m_nTescpESpeed=g_mGoto.m_nTescpESpeedMax+fabs(g_mGoto.m_nStarESpeed)/10.0;
			}
			else
			{
				g_mGoto.m_nTescpESpeed+=g_mGoto.m_nTescpEAcc;
			}
		} 
		//***********************************************

		//�жϸ�������Ƿ���󣬹���ʱ���ö�λ���������
		if(fabs(g_mGoto.m_nStarASpeed)>100)
		{
				if((fabs(g_mGoto.m_nAPosError)>fabs(g_mGoto.m_nStarASpeed)*0.01)&&(g_mGoto.m_nTAState==2))
				{
					g_mGoto.m_nTAState=0;
					if(g_mHandSpeed>6)
					{
					  g_mGotoBeep=true;	//����Ƶ�ʸ�
					 }
				}
		}
		else
		{
		   if((fabs(g_mGoto.m_nAPosError)>0.1)&&(g_mGoto.m_nTAState==2))
				{
					g_mGoto.m_nTAState=0;
					if(g_mHandSpeed>6)
					{
					  g_mGotoBeep=true;	//����Ƶ�ʸ�
					 }
				}
		}
				
		if((fabs(g_mGoto.m_nEPosError)>0.1)&&(g_mGoto.m_nTEState==2))
		{
			       g_mGoto.m_nTEState=0;
					if(g_mHandSpeed>6)
					{
					  g_mGotoBeep=true;	//����Ƶ�ʸ�
					 }
		}
		 
	   //����Ƶ�ʵ�
        if((fabs(g_mGoto.m_nAPosError)>10)||(fabs(g_mGoto.m_nEPosError)>5))
		{
			g_mGotoBeep=true;
		}



		//************************************************
		
		//************************************************
		//����λ������λ�Ƿ�������״̬
		if((fabs(g_mGoto.m_nAPosError)<=15.0)&&((g_mGoto.m_nTAState==0)||(g_mGoto.m_nTAState==1)))//����һ��������
		{  
			g_mGoto.m_nTAState=1;//������Զ����״̬Ϊ����״̬
			//һ�����������ٶȺͼ��ٶ�����
			g_mGoto.m_nTescpASpeed=300+fabs(g_mGoto.m_nStarASpeed)/10.0;
			if(fabs(g_mGoto.m_nAPosError)<=10.0)//�������������
			{
				g_mGoto.m_nTescpASpeed=200+fabs(g_mGoto.m_nStarASpeed)/10.0;
			}
			if(fabs(g_mGoto.m_nAPosError)<=5.0)//��������������
			{
				
				g_mGoto.m_nTescpASpeed=100+fabs(g_mGoto.m_nStarASpeed)/10.0;
			}
			if(fabs(g_mGoto.m_nAPosError)<=3.0)//�����ļ�������
			{
				g_mGoto.m_nTescpASpeed=50+fabs(g_mGoto.m_nStarASpeed)/10.0;
			}

		    if(fabs(g_mGoto.m_nAPosError)<=1.0)//�����弶������
			{
				g_mGoto.m_nTescpASpeed=10+fabs(g_mGoto.m_nStarASpeed)/10.0;
			}
			if(fabs(g_mGoto.m_nAPosError)<=0.1)//����������������
			{
				g_mGoto.m_nTescpASpeed=5+fabs(g_mGoto.m_nStarASpeed)/10.0;
			}
			if(fabs(g_mGoto.m_nAPosError)<=0.05)//���������
			{
				g_mGoto.m_nTAState=2;///������Զ����λ��״̬Ϊ����	
			}
			if(fabs(g_mGoto.m_nStarASpeed)>50)
			{ 
				 if(fabs(g_mGoto.m_nAPosError)<=0.001*fabs(g_mGoto.m_nStarASpeed))//���������
				{	
					   g_mGoto.m_nTAState=2;///������Զ����λ��״̬Ϊ����
				}
			}
		}
		//************************************************
		
		//************************************************
		//���ٸ߶����Ƿ����߶ȼ�����
		if((fabs(g_mGoto.m_nEPosError)<=15.0)&&((g_mGoto.m_nTEState==0)||(g_mGoto.m_nTEState==1)))//����һ��������
		{
			g_mGoto.m_nTEState=1;///������Զ����״̬
			g_mGoto.m_nTescpESpeed=130+fabs(g_mGoto.m_nStarESpeed);
		
		    if(fabs(g_mGoto.m_nEPosError)<=10.0)//�������������
			{
			
				g_mGoto.m_nTescpESpeed=100+fabs(g_mGoto.m_nStarESpeed);
			}

			if(fabs(g_mGoto.m_nEPosError)<=5.0)//��������������
			{
				
				g_mGoto.m_nTescpESpeed=80+fabs(g_mGoto.m_nStarESpeed);
			}
			if(fabs(g_mGoto.m_nEPosError)<=3.0)//��������������
			{
			
				g_mGoto.m_nTescpESpeed=60+fabs(g_mGoto.m_nStarESpeed);
			}
			if(fabs(g_mGoto.m_nEPosError)<=1.0)//�����ļ�������
			{
				g_mGoto.m_nTescpESpeed=30+fabs(g_mGoto.m_nStarESpeed);

			}
			if(fabs(g_mGoto.m_nEPosError)<=0.1)//�����弶������
			{
				
				g_mGoto.m_nTescpESpeed=10+fabs(g_mGoto.m_nStarESpeed);

			}

			if(fabs(g_mGoto.m_nEPosError)<=0.05)//�������
			{
			    
				g_mGoto.m_nTEState=2;///������Զ���ĸ߶ȸ���״̬
				
			}
		}
	
	  //mtest0=g_mGotoBeep;

	 if((g_mGoto.m_nTAState==2)&&(g_mGoto.m_nTEState==2))
	   {
	      g_mGotoHandMoveOK=true;
		  if(g_mGotoBeep)
		  {
		      FBeep(1);
		  }
		  g_mGotoBeep=false;
		  g_mTelStatus=2;


	   }
	   else
	   {
	      g_mTelStatus=1;
		 }
	  
		//�˳���Զ������ 
	   if((g_mGoto.m_nTAState==2)&&(g_mGoto.m_nTEState==2)&&g_mTelGoHome)
	   { 
	   	  g_mGoto.m_nStartStop=false;//������Զ����λ�ˣ��˳�
		  g_mGotoHandMoveOK=false;
	      FBeep(1);
	   	  g_mTelStatus=100;
	   }
	  
	 
		//************************************************
		
		//************************************************
		//��Զ���ķ�λ����
		if(g_mGoto.m_nTAState==2)
		{   
			m_nApout=FPointStarAlgorithm(g_mGoto.m_nTescpType,1,g_mGoto.m_nAPosEIZero,g_mGoto.m_nAPosError,g_mGoto.m_nStarASpeed);
		}
		//**********************************************
		
		//**********************************************
		//��Զ���ĸ߶ȸ���
		if(g_mGoto.m_nTEState==2)///ϵͳ�ڸ���״̬�ͼ���λ�û�
		{   
			m_nZpout=FPointStarAlgorithm(g_mGoto.m_nTescpType,2,g_mGoto.m_nEPosEIZero,g_mGoto.m_nEPosError,g_mGoto.m_nStarESpeed);
		}
		//************************************************
		//���Ŀ������  
	

		if(g_mGoto.m_nTAState==2)//����ʱ��������ٵ��ٶ�//�����䶨λ�ٶ�
		{  
		    if(fabs(g_mGoto.m_nStarASpeed)>100)
			{
			   g_mGoto.m_nStarASpeed=100+fabs(g_mGoto.m_nStarASpeed)*0.08;
			 }
			 if(fabs(g_mGoto.m_nStarASpeed)>200)
			{
			   g_mGoto.m_nStarASpeed=116+fabs(g_mGoto.m_nStarASpeed)*0.05;
			 }
			  if(fabs(g_mGoto.m_nStarASpeed)>300)
			{
			   g_mGoto.m_nStarASpeed=124+fabs(g_mGoto.m_nStarASpeed)*0.02;
			 }
			 if(fabs(g_mGoto.m_nStarASpeed)>400)
			{
			   g_mGoto.m_nStarASpeed=132+fabs(g_mGoto.m_nStarASpeed)*0.01;
			 }
			 if(fabs(g_mGoto.m_nStarASpeed)>500)
			{
			   g_mGoto.m_nStarASpeed=140+fabs(g_mGoto.m_nStarASpeed)*0.005;
			 }

			g_mGoto.m_nTescpASpeed=fabs(g_mGoto.m_nStarASpeed)+m_nApout;
			
			g_mGoto.m_nTescpASpeed=g_mGoto.m_nTescpASpeed*0.1;
			

			if(g_mGoto.m_nTescpASpeed<0)
			{
				g_mGoto.m_nTescpASpeed=0;
			}
		}	 

		//*************************************************
		if(g_mGoto.m_nTEState==2)//����ʱ��������ٵ��ٶ�//�����䶨λ�ٶ�
		{
		  
			g_mGoto.m_nTescpESpeed=fabs(g_mGoto.m_nStarESpeed)+m_nZpout;
			if(g_mGoto.m_nTescpESpeed<0)
			{
				g_mGoto.m_nTescpESpeed=0;
			}
			
		}
		//))))))))))))))))))))))))))))))))))))))))))))))))))))0000
	   	   //mtest0=g_mGoto.m_nTescpESpeed;
		
		//**********************************************
		//����Զ����������ź�
			if(!g_mTelGoHome)
			{
				if(g_mGoto.m_nStarEPos0<90)
				{
		
				    FDriveTelescope(g_mGoto.m_nTescpASpeed,g_mGoto.m_nTescpESpeed);
	   
		   	       if(g_mLandMark)//��½Ŀ�껹�����Ŀ��,false���Ŀ�꣬true½��Ŀ��
			       {
				     if(g_mGoto.m_nTAState==2)
					 {
					   FDriveTelescope(0,g_mGoto.m_nTescpESpeed);
					 }
					 if(g_mGoto.m_nTEState==2)
					 {
					   FDriveTelescope(g_mGoto.m_nTescpASpeed,0);
					 }

					 if((g_mGoto.m_nTAState==2)&&(g_mGoto.m_nTEState==2))
					 {
					   FDriveTelescope(0,0);
					   g_mGoto.m_nStartStop=false;//������Զ����λ�ˣ��˳�
					   g_mTelStatus=100;
					   g_mGotoHandMoveOK=false;
					   g_mgotostarttype=0;
					 }

					 if(g_mgotostarttype==0)
					 {
					   FDriveTelescope(0,0);
					   g_mGoto.m_nStartStop=false;//������Զ����λ�ˣ��˳�
					   g_mTelStatus=100;
					   g_mGotoHandMoveOK=false;
					 }
		
			       }  
		
				 // FDriveTelescopeNew();
				  // if(!g_mLandMark )
				 //  {
				      g_mGoto.m_nUnderhorizon=false;//���ڵ�ƽ���µı�־Ϊ��
				//	}
				  
				}
				else
				{
					if(!g_mLandMark )
				   {
					g_mGoto.m_nStartStop=false;//��Զ���ڵ�ƽ���£�ֹͣ����
		            g_mGoto.m_nUnderhorizon=true;//���ڵ�ƽ���µı�־Ϊ��
					g_mTelStatus=3;
					}
					else
					{
					  		
					     FDriveTelescope(g_mGoto.m_nTescpASpeed,g_mGoto.m_nTescpESpeed); 	   
			   	      
					     if(g_mGoto.m_nTAState==2)
						 {
						   FDriveTelescope(0,g_mGoto.m_nTescpESpeed);
						 }
						 if(g_mGoto.m_nTEState==2)
						 {
						   FDriveTelescope(g_mGoto.m_nTescpASpeed,0);
						 }
	
						 if((g_mGoto.m_nTAState==2)&&(g_mGoto.m_nTEState==2))
						 {
						   FDriveTelescope(0,0);
						   g_mGoto.m_nStartStop=false;//������Զ����λ�ˣ��˳�
						   g_mTelStatus=100;
						   g_mGotoHandMoveOK=false;
						   g_mgotostarttype=0;
						 }
	
						 g_mGoto.m_nUnderhorizon=false;//���ڵ�ƽ���µı�־Ϊ��
		
			       }  		
			
				}
			}
			else
			{
			       
				   FDriveTelescope(g_mGoto.m_nTescpASpeed,g_mGoto.m_nTescpESpeed);

				  

			}
			 //**********************************************
		
       }
	   else
	   {  
		   if(g_mGoto.m_nGoto)
		   {
		      FDriveTelescope(0,0);
			  g_mGoto.m_nGoto=false;
		   }
	   }

	   

	 //**************************************
	 //���ٱջ�ʱ��
	  /* if((g_mGoto.m_nTAState==2)&&(g_mGoto.m_nTEState==2))
	   {
	      MenuDelay(150);
	   }
	   else
	   {
	     MenuDelay(5);
	 } */
 }



//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//��ȡϵͳʱ��
void GetLocalTime(SYSTEMTIME *time)
{
    uint32  RTCtime;
	uint32  RTCdate;
	RTCtime = RTCtimeRead; // ��ȡ����ʱ�ӼĴ���
	RTCdate = RTCdateRead;	// ��ȡ�������ڼĴ���
	// ȡ����ֵ
     time->wYear = (RTCdate>>16)&0xFFF; 	 
	// ȡ����ֵ
	time->wMonth = (RTCdate>>8)&0x0F;  
	// ȡ����ֵ
	time->wDay = RTCdate&0x1F;            
	// ��ʾ��ֵ;      
	// ȡ��ʱ��ֵ
	time->wHour = (RTCtime>>16)&0x1F;
	// ȡ�÷ֵ�ֵ		
	time->wMinute= (RTCtime>>8)&0x3F;	
	// ȡ�����ֵ	
	time->wSecond = RTCtime&0x3F;
	//ȡ�ú���
	time->wMilliseconds=RTCms*10;

   if(g_mDaylight)//�Ƿ��������ʱ,true���ã�false���ò�
	{
	   if(time->wHour>=1)
	   {
	     time->wHour=time->wHour-1;
		}
		else
		{
		  time->wHour=23; 
		  time->wDay=time->wDay-1;
		  if(time->wDay==0)
		 {
		    switch(time->wMonth)
			{
			    case  1:
					time->wDay=31;
				   break;
			     case  2:
					time->wDay=31;
				   break;
				case  3:
					time->wDay=28;
				   break;
				case  4:
					time->wDay=31;
				   break;
				case  5:
					time->wDay=30;
				   break;
				case  6:
					time->wDay=31;
				   break;
				case  7:
					time->wDay=30;
				   break;
				case  8:
					time->wDay=31;
				   break;
				case  9:
					time->wDay=31;
				   break;
				case  10:
					time->wDay=30;
				   break;
				case  11:
					time->wDay=31;
				  break;
				 case  12:
					time->wDay=30;
				   break;
				 default:
				 break;
		     }

			time->wMonth=time->wMonth-1;
			if(time->wMonth==0)
			{
			   time->wMonth=time->wMonth+12;
			   time->wYear=time->wYear-1;
			 }

		 }
		}

 }

}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//����ط�����ʱ
double FCalSiderealTime(int fSysTimeType,bool fNutation ,double fLongitude)
{
	///*************************************************
	//���ݱ�������
	//double PI=3.14159265359;
	double m_njd;//������
	double m_ncn;//������
	double m_nUTST;//ϵͳ��ǰ����ʱ�µĺ���ʱ
	double m_nSidTime;//����ط�����ʱ
	
	SYSTEMTIME m_nSysTime;//ϵͳʱ��
	SYSTEMTIME m_nBJTime;//����ʱ��
	SYSTEMTIME m_nUTime;//����ʱ
	//��ʱ����
	double m_ntempa;
	double m_ntempb;
	double m_ntempc;

	double tempe0,tempe;//��
	//*********************
		double tempq;//��
		double templm,templs;//�� 	
		double tempf;//�� 	
		double tempdd;//�� 	
		double tempdtaf,tempdtae;//����
	double PI;
	PI=3.1415927;
	///*************************************************
	
	///*************************************************
	//��ȡϵͳʱ��
	GetLocalTime(&m_nSysTime);
	///*************************************************
	switch(fSysTimeType)
	{
	case 1://���ϵͳʱ��Ϊ����ʱ��
		///*************************************************
		//�õ�����ʱ��
		m_nBJTime=m_nSysTime;
		///*************************************************
		
		///*************************************************
		//�ѱ���ʱת��Ϊ����ʱ
		m_nUTime=m_nBJTime;
		if ((m_nBJTime.wHour-g_mGoto.m_nTimeZone)<0)  //������
		{
			m_nUTime.wHour=m_nUTime.wHour-g_mGoto.m_nTimeZone+24;
			m_nUTime.wDay=m_nUTime.wDay-1;
				
			if(m_nUTime.wDay<1)
			{
				switch (m_nUTime.wMonth)
				{
				case 1:
					m_nUTime.wDay=31;
					m_nUTime.wMonth=12;
					m_nUTime.wYear=m_nUTime.wYear-1;
					break;
				case 2: 
					m_nUTime.wDay=31;
					m_nUTime.wMonth=1;
					break;
				case 3: 
					m_nUTime.wDay=28;
					m_nUTime.wMonth=2;
					break;
				case 4:
					m_nUTime.wDay=31;
					m_nUTime.wMonth=3;  
					break;
				case 5: 
					m_nUTime.wDay=30;
					m_nUTime.wMonth=4; 
					break;
				case 6 :
					m_nUTime.wDay=31;
					m_nUTime.wMonth=5;  
					break;
				case 7: 
					m_nUTime.wDay=30;
					m_nUTime.wMonth=6;   
					break;
				case 8: 
					m_nUTime.wDay=31;
					m_nUTime.wMonth=7;  
					break;
				case 9:
					m_nUTime.wDay=31;
					m_nUTime.wMonth=8;
				case 10: 
					m_nUTime.wDay=30;
					m_nUTime.wMonth=9;
					break;
				case 11: 
					m_nUTime.wDay=31;
					m_nUTime.wMonth=10;
					break;
				case 12: 
					m_nUTime.wDay=30;
					m_nUTime.wMonth=11;
					break;
				default:break;
				}
			  }
		}
		else if((m_nBJTime.wHour-g_mGoto.m_nTimeZone)>24) //������
		{
		    m_nUTime.wHour=m_nUTime.wHour-g_mGoto.m_nTimeZone-24;
			m_nUTime.wDay=m_nUTime.wDay+1;
	    	switch (m_nUTime.wMonth)
				{
				case 1:	 
					if(m_nUTime.wDay>31)
					{ 
					  m_nUTime.wDay=1;
					  m_nUTime.wMonth=2;
					}
					break;
				case 2: 
					if(m_nUTime.wDay>28)
					{ 
					  m_nUTime.wDay=1;
					  m_nUTime.wMonth=3;
					}
				case 3: 
					if(m_nUTime.wDay>31)
					{ 
					  m_nUTime.wDay=1;
					  m_nUTime.wMonth=4;
					}
				case 4:
					if(m_nUTime.wDay>30)
					{ 
					  m_nUTime.wDay=1;
					  m_nUTime.wMonth=5;
					}
					break;
				case 5: 
					if(m_nUTime.wDay>31)
					{ 
					  m_nUTime.wDay=1;
					  m_nUTime.wMonth=6;
					}; 
					break;
				case 6 :
					if(m_nUTime.wDay>30)
					{ 
					  m_nUTime.wDay=1;
					  m_nUTime.wMonth=7;
					}  
					break;
				case 7: 
					if(m_nUTime.wDay>31)
					{ 
					  m_nUTime.wDay=1;
					  m_nUTime.wMonth=8;
					}   
					break;
				case 8: 
				if(m_nUTime.wDay>31)
					{ 
					  m_nUTime.wDay=1;
					  m_nUTime.wMonth=9;
					}  
					break;
				case 9:
				  if(m_nUTime.wDay>30)
					{ 
					  m_nUTime.wDay=1;
					  m_nUTime.wMonth=10;
					}
				case 10: 
					if(m_nUTime.wDay>31)
					{ 
					  m_nUTime.wDay=1;
					  m_nUTime.wMonth=11;
					}
					break;
				case 11: 
				   if(m_nUTime.wDay>30)
					{ 
					  m_nUTime.wDay=1;
					  m_nUTime.wMonth=12;
					}
					break;
				case 12: 
					if(m_nUTime.wDay>31)
					{ 
					  m_nUTime.wDay=1;
					  m_nUTime.wMonth=1;
					  m_nUTime.wYear=m_nUTime.wYear+1;
					}
					break;
				default:break;
				}
		}
		else
		{
			m_nUTime.wHour=m_nBJTime.wHour-g_mGoto.m_nTimeZone;
		}

		///*******************************************************
		break;
	case 2://���ϵͳʱ��Ϊ����ʱ
		m_nUTime=m_nSysTime;
		break;
	default:break;
	}
		
	///*******************************************************
    //����������
	if(m_nUTime.wMonth<3)
	{
		m_nUTime.wYear=m_nUTime.wYear-1;
		m_nUTime.wMonth=m_nUTime.wMonth+12;
	} 
	
	m_ntempa=(int)(m_nUTime.wYear*1.0/100.0); 

    m_ntempb=2-m_ntempa+(int)(m_ntempa*1.0/4.0);
	

	m_ntempc=(m_nUTime.wHour+m_nUTime.wMinute/60.0+m_nUTime.wSecond/3600.0+m_nUTime.wMilliseconds/3600000.0)/24.0;	
   	g_mGoto.m_nJHour=m_ntempc;

	m_njd=(int)(365.25*(m_nUTime.wYear+4716))+(int)(30.6001*(m_nUTime.wMonth+1))+m_nUTime.wDay+m_ntempc+m_ntempb-1524.5;
    //���������գ���������
	g_mGoto.m_nJday=m_njd;
	///*******************************************************
	//********************************************************
    //�����J2000������������,2000 January 1.5 TD(����ʱ)
	m_ncn=(m_njd-2451545)/36525.0;
	 
	//*********************************************************
	//*******************************************************
	//������������ʱ�ĵط�ƽ����ʱ	
	//m_nUTST=100.46061837+36000.770053608*m_ncn+0.000387993*m_ncn*m_ncn-m_ncn*m_ncn*m_ncn/38710000.0;
	m_nUTST=280.46061837+360.98564736629*(m_njd-2451545.0)+0.000387993*m_ncn*m_ncn-m_ncn*m_ncn*m_ncn/38710000.0;
	while (m_nUTST>360)
	{
		m_nUTST=m_nUTST-360;
	}
	while (m_nUTST<0)
	{
		m_nUTST=m_nUTST+360;
	}
	//������Ⱥ���ʱ
	m_njd=(int)(365.25*(m_nUTime.wYear+4716))+(int)(30.6001*(m_nUTime.wMonth+1))+m_nUTime.wDay+m_ntempb-1524.5;
	//���������գ���������
	//g_mGoto.m_nJday=m_njd;
	m_ncn=(m_njd-2451545)/36525.0;
	g_mgwt=280.46061837+360.98564736629*(m_njd-2451545.0)+0.000387993*m_ncn*m_ncn-m_ncn*m_ncn*m_ncn/38710000.0;
   	while (g_mgwt>360)
	{
		g_mgwt=g_mgwt-360;
	}
	while (g_mgwt<0)
	{
		g_mgwt=g_mgwt+360;
	}
	g_mgwt=g_mgwt/15;
   	//***********************************************************
	
//	//***********************************************************
//    //���¶�����
//	if(fNutation)
//	{
//		
//		//*********************
//	
//		//tempq is longitude of the ascending node of the Moon's mean orbit on the ecliptic measured from the mean equinox of the date
//		tempq=125.04452-1934.136261*m_ncn+0.0020708*m_ncn*m_ncn+m_ncn*m_ncn*m_ncn/450000.0; 
//		while (tempq>360)
//		{
//			tempq=tempq-360;
//		}
//		while(tempq<0)
//		{
//			tempq=tempq+360;
//		}
//		//*********************
//	
//		//templm is the mean anomaly of the Moon
//		templm=134.96298+477198.867398*m_ncn+0.0086972*m_ncn*m_ncn+m_ncn*m_ncn*m_ncn/56250.0;
//		while (templm>360)
//		{
//			templm=templm-360;
//		}
//		while (templm<0)
//		{
//			templm=templm+360;
//		}
//		//**********************
//	
//		//templs is the mean anomaly of the Sun(Earth)
//		templs=357.52772+35999.050340*m_ncn-0.0001603*m_ncn*m_ncn-m_ncn*m_ncn*m_ncn/300000.0;
//		while (templs>360)
//		{
//			templs=templs-360;
//		}
//		while (templs<0)
//		{
//			templs=templs+360;
//		}
//		//***********************
//	
//	       //tempf is the difference L-q ,where L is the mean longitude  of the Moon,or Moon's argument of latitude
//		tempf=93.271791+483202.017538*m_ncn-0.00036825*m_ncn*m_ncn+m_ncn*m_ncn*m_ncn/327270.0;
//		while (tempf>360)
//		{
//			tempf=tempf-360;
//		}	
//		while (tempf<0)
//		{
//			tempf=tempf+360;
//		}
//		//***********************	  
//
//		//tempdd is the mean elongation of the Moon from the Sun
//		tempdd=297.85036+445267.111480*m_ncn-0.0019142*m_ncn*m_ncn+m_ncn*m_ncn*m_ncn/189474.0;
//		while (tempdd>360)
//		{
//			tempdd=tempdd-360;
//		}
//		while (tempdd<0)
//		{
//			tempdd=tempdd+360;
//		}
//		//**************************************
//
//		tempdtaf=(-17.2289-0.017450*m_ncn)*sin(tempq*PI/180.0)-(1.4006+0.00008*m_ncn)*sin(tempq*PI/90.0)+(0.0242+0.00003*m_ncn)*sin(templm*PI/180.0)+0.0031*sin(templm*PI/90.0)+(0.0707-0.00017*m_ncn)*sin(templs*PI/180.0)+0.0005*sin(templs*PI/90.0)-(1.6341+0.00013*m_ncn)*sin(tempf*PI/90.0)+0.0002*sin(tempf*PI/45.0)+0.0008*sin(tempdd*PI/180.0)+(1.3346+0.00007*m_ncn)*sin(tempdd*PI/90.0)-0.0002*sin(tempdd*PI/45.0);
//		tempdtae=(9.2179+0.00089*m_ncn)*cos(tempq*PI/180.0)+(0.6076-0.00035*m_ncn)*cos(tempq*PI/90.0)+(0.0105-0.00001*m_ncn)*cos(templm*PI/180.0)-0.0010*cos(templm*PI/90.0)+0.0001*cos(templm*PI/60.0)+(0.02-0.00004*m_ncn)*cos(templs*PI/180.0)+0.0008*cos(templs*PI/90.0)+(0.7104-0.0004*m_ncn)*cos(tempf*PI/90.0)-0.0001*cos(tempdd*PI/180.0)+(0.5852-0.00034*m_ncn)*cos(tempdd*PI/90.0)+0.0002*cos(tempdd*PI/45.0);
//		tempdtae=tempdtae/3600.0;//��
//		tempe0=23.43929111111-46.8150*m_ncn/3600.0-0.00059*m_ncn*m_ncn/3600.0+0.001813*m_ncn*m_ncn*m_ncn/3600.0;
//		tempe=tempe0+tempdtae;//��
//		tempdtae=tempdtaf*cos(tempe*PI/180.0)/15.0;//����
//		//************************************
//		m_nUTST=m_nUTST+tempdtae/3600.0;
//		while (m_nUTST>360)
//		{
//			m_nUTST=m_nUTST-360;
//		}
//		while (m_nUTST<0)
//		{
//			m_nUTST=m_nUTST+360;
//		}
//		//***********************************************************
//	}
    
	//***********************************************************
    //����ط�����ʱ
	m_nSidTime=fLongitude+m_nUTST;
	while (m_nSidTime>360)
	{
		m_nSidTime=m_nSidTime-360;
	}
	while (m_nSidTime<0)
	{
		m_nSidTime=m_nSidTime+360;
	}
	m_nSidTime=m_nSidTime/15.0;
	//***********************************************************
	//����Ŀ��ʱ��
	
   //***********************************************************
		
	return m_nSidTime;
}


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//�����ǵĵ�ƽ����
void FCalStarAEPos(LOCATION floct,STARRAD fstar,int fSysTimeType,bool fNutation,STARAZ *fstaraz)
{
	
	//***********************************************
	//��������
	double PI=3.14159265359;
	double m_nLongitude;//�۲�ؾ���,�Զȱ�ʾ
    double m_nAtitude;//�۲��γ�ȣ��Զȱ�ʾ
	double m_nRightAscension;//�۲�Ŀ��ྭ,��ʱ��ʾ
	double m_nDeclination;//�۲�Ŀ���γ,�Զȱ�ʾ
	double m_nHourAngle;//Ŀ��ʱ��,��ʱ��ʾ
    double m_nSidTime;//�ط�����ʱ,��ʱ��ʾ
	//��ʱ����
	double m_ntempzz,m_ntempaa;
	double m_ntempAspd,m_ntempZspd;
	double m_nAacc,m_nZacc;
	//***********************************************
	TSETTING m_ntsetting1;
	ALIGNSTARAZ m_nalignstaraz1;
	
	//************************************************
	//��������
    m_nLongitude=floct.mLongitude;
	m_nAtitude=floct.mAtitude;
    m_nRightAscension=fstar.mRightAscension;
    m_nDeclination=fstar.mDeclination;
	
	//************************************************
	//***********************************************
    //����ط�����ʱ
    m_nSidTime=FCalSiderealTime(fSysTimeType,fNutation,m_nLongitude);
	//***********************************************
	
	//***********************************************
	//����Ŀ��ʱ��
	m_nHourAngle=m_nSidTime-m_nRightAscension;
	while(m_nHourAngle>=24)
	{
		m_nHourAngle=m_nHourAngle-24;
	}
    while(m_nHourAngle<0)
	{
		m_nHourAngle=m_nHourAngle+24;
	}
	//***********************************************
	
	
	//***********************************************
	//����ת��Ϊ���ȱ�ʾ
	m_nHourAngle=m_nHourAngle*PI*15.0/180.0;//��ʱ�����꣬�Ի��ȱ�ʾ��
	m_nAtitude=m_nAtitude*PI/180.0;
	m_nDeclination=m_nDeclination*PI/180.0;
	//***********************************************
	
    //***********************************************
	//�����ƽ����

	m_ntempzz=acos(sin(m_nAtitude)*sin(m_nDeclination)+cos(m_nAtitude)*cos(m_nDeclination)*cos(m_nHourAngle));

	m_ntempaa=acos((sin(m_nAtitude)*cos(m_nDeclination)*cos(m_nHourAngle)-cos(m_nAtitude)*sin(m_nDeclination))/sin(m_ntempzz));

	if(m_nHourAngle>PI)
	{
		m_ntempaa=-1.0*m_ntempaa;
	}

	m_ntempAspd=15.04*((sin(m_nAtitude)*sin(m_ntempzz)+cos(m_ntempzz)*cos(m_ntempaa)*cos(m_nAtitude))/sin(m_ntempzz));
	   
	m_ntempZspd=15.04*cos(m_nAtitude)*sin(m_ntempaa); 
      
	//*************************************************
	///���ز���	
	fstaraz->mASzimuth=m_ntempaa*57.295779513082320876798154814105;
	fstaraz->mANzimuth=180.0+m_ntempaa*57.295779513082320876798154814105;
	fstaraz->mAzimuthSpeed=m_ntempAspd;
	fstaraz->mZenith=m_ntempzz*57.295779513082320876798154814105;
	fstaraz->mAtitude=90.0-m_ntempzz*57.295779513082320876798154814105;
	fstaraz->mZenithSpeed=m_ntempZspd;
	fstaraz->mAtitudeSpeed=-m_ntempZspd;  
	//****************************************
   //��Զ��У׼����������
   	
	//**************************************************
	//�����ǵ�λ�ø���
//	m_ntsetting1.mTSettingA0=g_mTelError.mTSettingA0;
//	m_ntsetting1.mTSettingE0=g_mTelError.mTSettingE0;
//	m_ntsetting1.mTSettingLOS=g_mTelError.mTSettingLOS;
//	m_ntsetting1.mTSettingNP=g_mTelError.mTSettingNP;
//	m_ntsetting1.mTSettingEW=g_mTelError.mTSettingEW;
//	m_ntsetting1.mTSettingNS=g_mTelError.mTSettingNS;
//
//	m_nalignstaraz1.mSAzimuth=fstaraz->mASzimuth;
//	m_nalignstaraz1.mSZenith=fstaraz->mZenith;	           	       
//
//	FAlignStarAEPos(m_ntsetting1,&m_nalignstaraz1);
//
//    fstaraz->mANzimuth=m_nalignstaraz1.mTSAzimuth+180.0;
//    fstaraz->mAtitude=90.0-m_nalignstaraz1.mTSZenith;

	
}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//����������
void FCalStarEQPos(double azi,double alt,double *ra,double *dec)	
{
   double pik=3.14159265359/180.0;
   double temph;
   double  sidleraltime;
   double wd;  

   
   if(azi<0.0003)
   {
     azi=0.0003;
   }
    if(alt<0.0003)
   {
     alt=0.0003;
   }
   


   sidleraltime=FCalSiderealTime(1,false,g_mGoto.m_nLongitude);
   wd=g_mGoto.m_nAtitude;

  
   
   azi=azi-180;
   temph=atan(sin(azi*pik)/(cos(azi*pik)*sin(wd*pik)+tan(alt*pik)*cos(wd*pik)));
  

   temph=(temph/pik)/15.0;	
   if(alt>wd)
   {
      if(temph<0)
	  {
        temph=24+temph;
	  }
	  else
	  {
	    temph=temph;
	   }
   }
   else
   {
      if(temph<0)
	  {
	    if(azi<0)
		{
		  temph=temph+24;
	    }
	    else
	    {
	      temph=temph+12;
	    }
	  }
	  else
	  {
	     if(azi<0)
		 {
		   temph=temph+12;
		 }
		 else
		 {
		   temph=temph;
		 }
	  }

   }   

   *ra=sidleraltime-temph;

   if(*ra>24)
   {
     *ra=*ra-24;
	 }
	if(*ra<0)
   {
     *ra=*ra+24;
	 }

   
   *dec=asin(sin(wd*pik)*sin(alt*pik)-cos(wd*pik)*cos(alt*pik)*cos(azi*pik));
   *dec=(*dec/pik);
    
    
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

//������У׼��ĵ�ƽλ��
void FAlignStarAEPos(TSETTING ftsetting,ALIGNSTARAZ *falignstaraz)
{
    double m_ntempa,m_ntempz;
	double m_ntemppi;
	double dta1,dte1;
    double dtA0,dtE0,gam0,snta0,we0,ns0;
	
    m_ntemppi=3.1415926/180.0;
	m_ntempa=(falignstaraz->mSAzimuth+180)*m_ntemppi;
    m_ntempz=(90-falignstaraz->mSZenith)*m_ntemppi;
	
	dtA0=ftsetting.mTSettingA0;
	dtE0=ftsetting.mTSettingE0;
	gam0=ftsetting.mTSettingLOS;
	snta0=ftsetting.mTSettingNP;
	we0=ftsetting.mTSettingEW;
	ns0=ftsetting.mTSettingNS;
	


    dta1=dtA0-gam0/cos(m_ntempz)+snta0*tan(m_ntempz)+ns0*tan(m_ntempz)*sin(m_ntempa)+we0*tan(m_ntempz)*cos(m_ntempa);
    dte1=dtE0+ns0*cos(m_ntempa)-we0*sin(m_ntempa);

  	 
	falignstaraz->mTSAzimuth=falignstaraz->mSAzimuth+dta1;
	falignstaraz->mTSZenith=falignstaraz->mSZenith-dte1;

}
//������У׼��ĳ��λ��
void FAlignStarRAPos(TSETTING ftsetting,double *m_HUOR,double *m_Dec)
{
    double m_ntempa,m_ntempz;
	double m_ntemppi;
	double dta1,dte1;
    double dtA0,dtE0,gam0,snta0,we0,ns0;
	
    m_ntemppi=3.1415926/180.0;

	m_ntempa=180+15*(*m_HUOR);
	if (m_ntempa>360)
	{
	  	m_ntempa=m_ntempa-360; 
	}
	m_ntempa=m_ntempa*m_ntemppi;
    m_ntempz=(*m_Dec)*m_ntemppi;
	
	dtA0=ftsetting.mTSettingA0;
	dtE0=ftsetting.mTSettingE0;
	gam0=ftsetting.mTSettingLOS;
	snta0=ftsetting.mTSettingNP;
	we0=ftsetting.mTSettingEW;
	ns0=ftsetting.mTSettingNS;
	


    dta1=dtA0-gam0/cos(m_ntempz)+snta0*tan(m_ntempz)+ns0*tan(m_ntempz)*sin(m_ntempa)+we0*tan(m_ntempz)*cos(m_ntempa);
    dte1=dtE0+ns0*cos(m_ntempa)-we0*sin(m_ntempa);

   // mtesta2=dta1;     
	//mtestz2=dte1;  


	*m_HUOR=(*m_HUOR)+dta1/15.0;
	while(	*m_HUOR>24)
	{
	  *m_HUOR=*m_HUOR-24;
	}
	while(	*m_HUOR<0)
	{
	  *m_HUOR=*m_HUOR+24;
	}
	*m_Dec=*m_Dec+dte1;
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//�������������
//double FAirRefraction(double fAirT,double fAirP,double fzernith)
//{
//   double kpi;
//   double p;
//   double T;
//   double h;
//   double c;
//   double R,dR;
//
//   kpi=3.1415926/180;
//
//    //sh=1875  
//    //p0=1010  %mba
//    //p=(0.88*h/1000)*p0
//
//    T=fAirT;
//    p=fAirP;
//    h=90-fzernith;
//    c=p*283.0/(1010.0*(273+T));
//
//   // R=c*1.02/tan((h+10.3/(h+5.11))*kpi);//�Ƿ�
//	R=0.017*c/tan((h+10.3/(h+5.11))*kpi);//��
//    //dR=-0.06*sin((14.7*R/60+3)*kpi)*60
//	return R;
//}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

void FReadTelescopePos(double *fAZimuth,double *fAltitude)//��ȡ��Զ���ķ���λ��
{

	 *fAZimuth=g_mGoto.m_nStarAPosT-0.0028;
	 *fAltitude=g_mGoto.m_nStarEPosT-0.0028;
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//��Զ������PID�㷨
double FPointStarAlgorithm (int fTescpType,int fAxis,double fPosEIZero,double fPosError,double fObjectSpeed)
   {
	   //***************************************
	   //��������
	   double m_nPIOut,m_nPOut,m_nIOut;//PI���
	   double m_nAp,m_nZp;//������ϵ��
	   double m_nApi,m_nZpi;//������ϵ��
	   //***************************************
	   
	   
	   //***************************************
	   //������Զ����������PI����
	   switch(fTescpType)
	   {
	   case 1://��̨164
		   m_nAp=6.0;
		   m_nZp=18.0;
		   m_nApi=6.0;
		   m_nZpi=9.0;
		   break;
	   case 2:
	       m_nAp=2.0;
		   m_nZp=1.0;
		   m_nApi=6.0;
		   m_nZpi=9.0;
		   break;
	   case 3:
		   break;
	   default:break;
	   }
	   //***************************************
	   
	   //***************************************
	   //ѡ��Զ�����ᣬ1��λ�ᣬ2 �߶���
	   switch(fAxis)
	   {
	   case 1:
		   //********************
		   //��λ������
		   m_nPOut=fPosError*m_nAp;
		   //********************
		   if(fObjectSpeed<0)
		   {
			   m_nPOut=m_nPOut*(-1.0);
		   }
		   if(m_nPOut>10.0)   
		   {
			   m_nPOut=10.0;
		   }
		   if(m_nPOut<-10.0)
		   {
			   m_nPOut=-10.0;
		   }
		   //*********************
		   
		   m_nIOut=fPosEIZero;
		   /*if((g_mGoto.m_nAPosError*Ai)<0)//�������ͻ��֣��û��ַ���
		   {
		   Ai=0.0;
		   }
		   
			 Ai=Ai+Api*g_mGoto.m_nAPosError; //����λ��������
			 if(Ai>10)           //���ֱ�������
			 {
			 Ai=10;
			 }
			 if(Ai<-10)
			 {
			 Ai=-10;
	   }*/
		   g_mGoto.m_nAPosEIZero=m_nIOut;
		   break;
	   case 2:
		   m_nPOut=fPosError*m_nZp;//���������
		   if(fObjectSpeed<0)
		   {
			   m_nPOut=m_nPOut*(-1.0);
		   }
		   if(m_nPOut>10.0)       
		   {
			   m_nPOut=10.0;
		   }
		   if(m_nPOut<-10.0)
		   {
			   m_nPOut=-10.0;
		   }
		   m_nIOut=fPosEIZero;
		   
		   /*if((g_mGoto.m_nEPosError*Zi)<0)//�������ͻ��֣��û��ַ���
		   {
		   Zi=0.0;
		   }
		   Zi=Zi+Zpi*g_mGoto.m_nEPosError; //����λ��������
		   if(Zi>10.0)           //���ֱ�������
		   {
		   Zi=10.0;
		   }
		   if(Zi<-10.0)
		   {
		   Zi=-10.0;
	   }*/
		   g_mGoto.m_nEPosEIZero=m_nIOut;
		   break;
		   
	   default:break;
	   } 
	   //************************************************************
	   //************************************************************
	   //���ؽ��
	   m_nPIOut=m_nPOut+m_nIOut;
	   return m_nPIOut;
	   //************************************************************
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//��Զ����GOTO
void FStartGoto()
{   
   
    FHandPowerTelescope();
    g_mGoto.m_nStartStop=true;
	g_mTelGoHome=false;//��Զ����Ҫ���ڹ���״̬
	g_mGotoHandMoveOK=false; //��Զ����һ��ʼ�����Խ����ֶ�״̬
	//g_mGotoBeep=true;
	g_mGoto.m_nTEState=0;
	g_mGoto.m_nTAState=0;
	g_mGoto.m_nTelGotoPause=0;

	  g_mGoto.m_nTescpESpeed=0;
	  g_mGoto.m_nTescpASpeed=0;	
	  
	  g_mTelStatusSet=0;

}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//��Զ��ֹͣGOTO
void FStopGoto()
{
	g_mGoto.m_nStartStop=false;
	g_mTempTelEpos=10000.0;//��Զ���߶���ʱλ��
}

//��Զ����ͣGOTO
void FPauseGoto()
{
	g_mGoto.m_nStartStop=false;
	g_mGoto.m_nTEState=0;
	g_mGoto.m_nTAState=0;
	g_mTelStatus=0;

	UART1_SentByte(0x55);
	UART1_SentByte(0xAA);
	UART1_SentByte(0x01);
	UART1_SentByte(0x01);
	UART1_SentByte(0x00);

	g_mGoto.m_nTelGotoPause=1;	

	g_mGoto.m_nTescpESpeed=0;
	g_mGoto.m_nTescpASpeed=0;	


}

//��Զ������GOTO
void FContinueGoto()
{
	 g_mGoto.m_nStartStop=true;
	  UART1_SentByte(0x55);
	  UART1_SentByte(0xAA);
	  UART1_SentByte(0x01);
	  UART1_SentByte(0x01);
	  UART1_SentByte(0xFF);
	  g_mGoto.m_nTelGotoPause=0;
	 
	 
	  g_mGoto.m_nTescpESpeed=0;
	  g_mGoto.m_nTescpASpeed=0;
	  g_mHandSpeed=3;	//Ĭ�ϸ���ʱ�ֶ������ٶ�Ϊ3��	
 
 	  g_mhandtrackAzi=1;//���ָ��ʱ����Զ����Ŀ��λ��һ�£��ֶ����ں󣬾Ͳ�һ����
	  g_mhandtrackAlt=1;//���ָ��ʱ����Զ����Ŀ��λ��һ�£��ֶ����ں󣬾Ͳ�һ����

}


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//ָ����Ŀ��
void FPointNewStar(double fRightAscension,double fDeclination)
{
	g_mGoto.m_nRightAscension=fRightAscension;//�ྭ(0-24Сʱ)
	g_mGoto.m_nDeclination=fDeclination;//��γ(-90��90��)

	g_mPointNewStar=true;//�Ƿ�ָ�����µ�һ���ǣ�trueָ��,ָ�˾ʹ�Ϊ����۲���ǣ�falseû��ָ
    
  	g_RecentRa=fRightAscension;//����۲��ǵĳྭ
	g_RecentDec=fDeclination;//����۲��ǵĳ�γ

   	g_mPointNewStarTracking=1;//ָ���µ��ǲ�����
	g_mstartOTAset=1;//����ʱ������Զ���ĳ�ʼָ��

	g_mGoto.m_nTCrossZeroP=false;//��Զ��������ʱ�Ƿ�������Խ
	g_mGoto.m_nTCrossZeroN=false;//��Զ��������ʱ�Ƿ��и���Խ
	g_mGoto.m_nTPointDirect=0;//��Զ����λ������

	//dg_mApos=dg_mApos_syn;
    //dg_mZpos=-dg_mZpos_syn;

	dg_mApos=syn_mApos;//��ʼ������ͬ����
    dg_mZpos=syn_mZpos;//��ʼ������ͬ����

	
//
//	syn_mApos=0;//��λ����ʱ��ͬ����
//  syn_mZpos=0;//�춥����ʱ��ͬ����

	//g_mLandMark=false;

	//g_mLandObjAzi=0;
	//g_mLandObjAlt=0;
	
	g_mGotoBeep=true;
	g_mgotostarttype=0;
	FStartGoto();//����Զ��


    g_mPauseTrack=0;//�ǲ�����ֹͣ�𶯵ĸ��� 0,���ǣ�1��
	g_mHandSpeed=3;	//Ĭ�ϸ���ʱ�ֶ������ٶ�Ϊ3��

	 g_mhandtrackAzi=1;//���ָ��ʱ����Զ����Ŀ��λ��һ�£��ֶ����ں󣬾Ͳ�һ����
	 g_mhandtrackAlt=1;//���ָ��ʱ����Զ����Ŀ��λ��һ�£��ֶ����ں󣬾Ͳ�һ����


	 g_mGoto.m_nGuidMoveRa=0;//�ϴε��гྭƫ����0
	 g_mGoto.m_nGuidMoveDec=0;//�ϴε��г�γƫ����0

}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//���ù۲����λ��
void FSetLocation(double fLongitude,double fAtitude)
{
	g_mGoto.m_nLongitude=fLongitude;

    g_mGoto.m_nAtitude=fAtitude;
}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//��Զ���Զ�У׼����
void FAutoAlign()
{   
	int m_nstarnum;
    CALSTARAZ StarsPos;
    TSETTING TSetting;
	m_nstarnum=0;
	
	if(g_mGoto.m_nAlignAdjustNum<g_mGoto.m_nAlignStarNum)
	{   
		g_mGoto.m_nTCrossZeroP=false;//��Զ��������ʱ�Ƿ�������Խ
		g_mGoto.m_nTCrossZeroN=false;//��Զ��������ʱ�Ƿ��и���Խ
		g_mGoto.m_nTPointDirect=0;//��Զ����λ������
		switch(g_mGoto.m_nAlignAdjustNum)
		{
		case 0:
			 g_mGoto.m_nRightAscension=g_mGoto.m_nAlignStarRA1;
			 g_mGoto.m_nDeclination=g_mGoto.m_nAlignStarDec1;
			break;
		case 1:
			 g_mGoto.m_nRightAscension=g_mGoto.m_nAlignStarRA2;
			 g_mGoto.m_nDeclination=g_mGoto.m_nAlignStarDec2;
			break;
		case 2:
			 g_mGoto.m_nRightAscension=g_mGoto.m_nAlignStarRA3;
			 g_mGoto.m_nDeclination=g_mGoto.m_nAlignStarDec3;
			break;
		default:break;
		}
	}
	else
	{
		m_nstarnum=g_mGoto.m_nAlignStarNum;
		StarsPos.mANzimuth1=g_mGoto.m_nANzimuth1;//��λ������Ϊ�㣬����������0�ȵ�360��
		StarsPos.mAtitude1=g_mGoto.m_nAtitude1;//�߶ȣ���ƽΪ�㣬�춥90�ȣ�0�㵽90��
		StarsPos.mAPointEerror1=g_mGoto.m_nAPointEerror1;
		StarsPos.mEPointEerror1=g_mGoto.m_nEPointEerror1;
		StarsPos.mANzimuth2=g_mGoto.m_nANzimuth2;//��λ������Ϊ�㣬����������0�ȵ�360��
		StarsPos.mAtitude2=g_mGoto.m_nAtitude2;//�߶ȣ���ƽΪ�㣬�춥90�ȣ�0�㵽90��
		StarsPos.mAPointEerror2=g_mGoto.m_nAPointEerror2;
		StarsPos.mEPointEerror2=g_mGoto.m_nEPointEerror2;
		StarsPos.mANzimuth3=g_mGoto.m_nANzimuth3;//��λ������Ϊ�㣬����������0�ȵ�360��
		StarsPos.mAtitude3=g_mGoto.m_nAtitude3;//�߶ȣ���ƽΪ�㣬�춥90�ȣ�0�㵽90��
		StarsPos.mAPointEerror3=g_mGoto.m_nAPointEerror3;
		StarsPos.mEPointEerror3=g_mGoto.m_nEPointEerror3;

        //У׼����
		switch(m_nstarnum)
		{
		   case  1:
		   FOneStarCal(StarsPos,&TSetting);
		   break;
		    case  2:
		   FTowStarCal(StarsPos,&TSetting);
		   break;
		   case  3:
		   FThreeStarCal(StarsPos,&TSetting);
		   break;
		   default :
		   break;
		 }

        g_mTelError.mTSettingA0=TSetting.mTSettingA0;
		g_mTelError.mTSettingE0=TSetting.mTSettingE0;
		g_mTelError.mTSettingLOS=TSetting.mTSettingLOS;
		g_mTelError.mTSettingNP=TSetting.mTSettingNP;
		g_mTelError.mTSettingEW=TSetting.mTSettingEW;
		g_mTelError.mTSettingNS=TSetting.mTSettingNS;
		
		//��λ�Ѿ�У׼��־
		g_mGoto.m_nAlign=true;
	  
	  // if(g_mAzEq==0)  //��ƽʽ���㣬���ʽ������
	   //{	


	   	 //dg_mApos0=2.0*dg_mApos; //��¼У׼��ĵ�����
		 //dg_mApos0=2.0*dg_mZpos;  //��¼У׼��ĵ�����

		 dg_mApos=0;//�ֶ�����������
		 dg_mZpos=0;//�ֶ�����������
	

		 	syn_mApos=0;//��λ����ʱ��ͬ����
            syn_mZpos=0;//�춥����ʱ��ͬ����

			g_mhandtrackAzi=1;//���ָ��ʱ����Զ����Ŀ��λ��һ�£��ֶ����ں󣬾Ͳ�һ����
			g_mhandtrackAlt=1;//���ָ��ʱ����Զ����Ŀ��λ��һ�£��ֶ����ں󣬾Ͳ�һ����


	//	}
		//�ֶ�������������������������������
	
	//	FBeep(3);
	}
}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//��Զ���Զ�У׼������û�ж�׼
void FPointAlignStarOk()
{  
	
	if(!g_mGoto.m_nAlign)
	{  	
		
	 	
		if((g_mGoto.m_nTAState==2)&&(g_mGoto.m_nTEState==2))
		{   
			g_mGoto.m_nAlignAdjustNum++;

			   if(g_mAzEq==0)
			   {
				switch(g_mGoto.m_nAlignAdjustNum)
				{
					case 1:
						g_mGoto.m_nANzimuth1=180+g_mGoto.m_nStarAPos0;
						g_mGoto.m_nAtitude1=90-g_mGoto.m_nStarEPos0;
						g_mGoto.m_nAPointEerror1=g_mGoto.m_nTAHandMovePos;
						g_mGoto.m_nEPointEerror1=-1.0*g_mGoto.m_nTEHandMovePos;
						//g_mGoto.m_nAPointEerror1=g_mGoto.m_nTescpAPos-g_mGoto.m_nStarAPos0;
						//g_mGoto.m_nEPointEerror1=g_mGoto.m_nStarEPos0-g_mGoto.m_nTescpEPos;
						
						 break;
					case 2:
				        g_mGoto.m_nANzimuth2=180+g_mGoto.m_nStarAPos0;
						g_mGoto.m_nAtitude2=90-g_mGoto.m_nStarEPos0;
						g_mGoto.m_nAPointEerror2=g_mGoto.m_nTAHandMovePos;
					    g_mGoto.m_nEPointEerror2=-1.0*g_mGoto.m_nTEHandMovePos;
					//	g_mGoto.m_nAPointEerror1=g_mGoto.m_nTescpAPos-g_mGoto.m_nStarAPos0;
					//	g_mGoto.m_nEPointEerror1=g_mGoto.m_nStarEPos0-g_mGoto.m_nTescpEPos;
						break;
					case 3:
				    	g_mGoto.m_nANzimuth3=180+g_mGoto.m_nStarAPos0;
						g_mGoto.m_nAtitude3=90-g_mGoto.m_nStarEPos0;
						g_mGoto.m_nAPointEerror3=g_mGoto.m_nTAHandMovePos;
						g_mGoto.m_nEPointEerror3=-1.0*g_mGoto.m_nTEHandMovePos;
						//g_mGoto.m_nAPointEerror1=g_mGoto.m_nTescpAPos-g_mGoto.m_nStarAPos0;
					//	g_mGoto.m_nEPointEerror1=g_mGoto.m_nStarEPos0-g_mGoto.m_nTescpEPos;
						break;
				default:break;
				}
			  }
			  else
			  {	 
			     switch(g_mGoto.m_nAlignAdjustNum)
				{
					case 1:
						g_mGoto.m_nANzimuth1=180+15*g_mGoto.m_nHourAngle;
						if (g_mGoto.m_nANzimuth1>360)
						{
						   g_mGoto.m_nANzimuth1=g_mGoto.m_nANzimuth1-360; 
						}
						g_mGoto.m_nAtitude1=g_mGoto.m_nDeclination;

						g_mGoto.m_nAPointEerror1=g_mGoto.m_nTAHandMovePos;
						g_mGoto.m_nEPointEerror1=-1.0*g_mGoto.m_nTEHandMovePos;

						//���ǻز�

//						if(g_mGoto.m_nTAHandMovePos<0)
//						{
//						   g_mGoto.m_nAPointEerror1=g_mGoto.m_nTAHandMovePos+g_mTelRABack;
//						}
//						else
//						{
//						  g_mGoto.m_nAPointEerror1=g_mGoto.m_nTAHandMovePos;
//
//						 }						  
//						
//						g_mGoto.m_nEPointEerror1=g_mGoto.m_nTEHandMovePos;
//					    if((g_mTelDecNextPos>0)&&(g_mGoto.m_nEPointEerror1>0))
//						{
//						}
//						else if((g_mTelDecNextPos>0)&&(g_mGoto.m_nEPointEerror1<0))
//						{
//						    g_mGoto.m_nEPointEerror1=g_mGoto.m_nEPointEerror1+g_mTelDecBack;
//						}
//						else if((g_mTelDecNextPos<0)&&(g_mGoto.m_nEPointEerror1<0))
//						{
//						    
//						}
//						else if((g_mTelDecNextPos<0)&&(g_mGoto.m_nEPointEerror1>0))
//						{
//					    	g_mGoto.m_nEPointEerror1=g_mGoto.m_nEPointEerror1-g_mTelDecBack;
//						}
//
//						if(g_mGoto.m_nHourAngle>12)
//						{
//						  g_mGoto.m_nEPointEerror1=-1.0*g_mGoto.m_nEPointEerror1;
//						}

						//*****************
//						g_mTelRALastPos=g_mTelRANextPos;
//	                    g_mTelDecLastPos=g_mTelDecNextPos;
//
//						dg_mApos=0;
//	                    dg_mZpos=0;

						break;
					case 2:
				        g_mGoto.m_nANzimuth2=180+15*g_mGoto.m_nHourAngle;
						if (g_mGoto.m_nANzimuth2>360)
						{
						   g_mGoto.m_nANzimuth2=g_mGoto.m_nANzimuth2-360; 
						}
						g_mGoto.m_nAtitude2=g_mGoto.m_nDeclination;

						g_mGoto.m_nAPointEerror2=g_mGoto.m_nTAHandMovePos;
						g_mGoto.m_nEPointEerror2=-1.0*g_mGoto.m_nTEHandMovePos;

						//���ǻز�

//
//
//						if(g_mGoto.m_nTAHandMovePos<0)
//						{
//						   g_mGoto.m_nAPointEerror2=g_mGoto.m_nTAHandMovePos+g_mTelRABack;
//						}
//						else
//						{
//						  g_mGoto.m_nAPointEerror2=g_mGoto.m_nTAHandMovePos;
//
//						 }
//
//						g_mGoto.m_nEPointEerror2=g_mGoto.m_nTEHandMovePos;
//					     
//					 	if((g_mTelDecNextPos>g_mTelDecLastPos)&&(g_mGoto.m_nEPointEerror2>0))
//						{
//						}
//						else if((g_mTelDecNextPos>g_mTelDecLastPos)&&(g_mGoto.m_nEPointEerror2<0))
//						{
//						    g_mGoto.m_nEPointEerror2=g_mGoto.m_nEPointEerror2+g_mTelDecBack;
//						}
//						else if((g_mTelDecNextPos<g_mTelDecLastPos)&&(g_mGoto.m_nEPointEerror2<0))
//						{
//						    
//						}
//						else if((g_mTelDecNextPos<g_mTelDecLastPos)&&(g_mGoto.m_nEPointEerror2>0))
//						{
//					    	g_mGoto.m_nEPointEerror2=g_mGoto.m_nEPointEerror2-g_mTelDecBack;
//						}
//					
//
//
//
//						if(g_mGoto.m_nHourAngle>12)
//						{
//						  g_mGoto.m_nEPointEerror2=-1.0*g_mGoto.m_nEPointEerror2;
//						}

						//*****************
//						g_mTelRALastPos=g_mTelRANextPos;
//	                    g_mTelDecLastPos=g_mTelDecNextPos;
//						dg_mApos=0;
//	                    dg_mZpos=0;
						break;
					case 3:
				    	g_mGoto.m_nANzimuth3=180+15*g_mGoto.m_nHourAngle;
						if (g_mGoto.m_nANzimuth3>360)
						{
						   g_mGoto.m_nANzimuth3=g_mGoto.m_nANzimuth3-360; 
						}
						g_mGoto.m_nAtitude3=g_mGoto.m_nDeclination;

						g_mGoto.m_nAPointEerror3=g_mGoto.m_nTAHandMovePos;
						g_mGoto.m_nEPointEerror3=-1.0*g_mGoto.m_nTEHandMovePos;

						//���ǻز�


//						if(g_mGoto.m_nTAHandMovePos<0)
//						{
//						   g_mGoto.m_nAPointEerror3=g_mGoto.m_nTAHandMovePos+g_mTelRABack;
//						}
//						else
//						{
//						  g_mGoto.m_nAPointEerror3=g_mGoto.m_nTAHandMovePos;
//
//						 }
//
//						g_mGoto.m_nEPointEerror3=g_mGoto.m_nTEHandMovePos;
//						if((g_mTelDecNextPos>g_mTelDecLastPos)&&(g_mGoto.m_nEPointEerror3>0))
//						{
//						}
//						else if((g_mTelDecNextPos>g_mTelDecLastPos)&&(g_mGoto.m_nEPointEerror3<0))
//						{
//						    g_mGoto.m_nEPointEerror3=g_mGoto.m_nEPointEerror3+g_mTelDecBack;
//						}
//						else if((g_mTelDecNextPos<g_mTelDecLastPos)&&(g_mGoto.m_nEPointEerror3<0))
//						{
//						    
//						}
//						else if((g_mTelDecNextPos<g_mTelDecLastPos)&&(g_mGoto.m_nEPointEerror3>0))
//						{
//					    	g_mGoto.m_nEPointEerror3=g_mGoto.m_nEPointEerror3-g_mTelDecBack;
//						}
//
//
//						if(g_mGoto.m_nHourAngle>12)
//						{
//						  g_mGoto.m_nEPointEerror3=-1.0*g_mGoto.m_nEPointEerror3;
//						}
            		break;
				 default:break;
			    }
			} 
		}
         
	}
}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//�������Զ�У׼
void FTwoStarAutoAlign()
{	
   char starname[28][10];
   char starnamecn[28][22];
	g_mGoto.m_nAlignStarNum=2;//���ü�����У׼
    g_mGoto.m_nAlign=false;//��Զ���Ƿ��Ѿ�У��,trueУ���ˣ�false��û��У׼
    g_mGoto.m_nAlignAdjustNum=0;//��Զ��У׼ʱ���ڴ���

	
	
	g_mAlignStarNum=FindAlignStar(FCalSiderealTime(1,false,g_mGoto.m_nLongitude),g_mGoto.m_nAtitude,g_mStarAlign,starname,starnamecn);			
	g_mGoto.m_nAlignStarRA1=g_mStarAlign[0];//�ྭ(0-24Сʱ)
	g_mGoto.m_nAlignStarDec1=g_mStarAlign[1];//��γ(-90��90��)
	g_mGoto.m_nAlignStarRA2=g_mStarAlign[2];//2*(g_mAlignStarNum-1)];//�ྭ(0-24Сʱ)
	g_mGoto.m_nAlignStarDec2=g_mStarAlign[3];//2*(g_mAlignStarNum-1)+1];//��γ(-90��90��)
    
	dg_mApos=0;
	dg_mZpos=0;
	dg_mApos_syn=0;
	dg_mZpos_syn=0;

	g_mTelError.mTSettingNP=0;//����ֱ
	g_mTelError.mTSettingLOS=0;//����ƫ��
	g_mTelError.mTSettingNS=0;//����
	g_mTelError.mTSettingEW=0;//����
	g_mTelError.mTSettingA0=0;//��λ��ƫ
	g_mTelError.mTSettingE0=0;//�߶���ƫ 

	g_mTelRALastPos=g_mTelRANextPos;
	g_mTelDecLastPos=g_mTelDecNextPos;


	FStartGoto();

}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//һ����У׼
void FOneStarAlign()
{
 
	g_mGoto.m_nAlignStarNum=1;//���ü�����У׼
    g_mGoto.m_nAlign=false;//��Զ���Ƿ��Ѿ�У��,trueУ���ˣ�false��û��У׼
    g_mGoto.m_nAlignAdjustNum=0;//��Զ��У׼ʱ���ڴ���

	//g_mAlignStarNum=FindAlignStar(FCalSiderealTime(1,false,g_mGoto.m_nLongitude),g_mGoto.m_nAtitude,g_mStarAlign);		
	//g_mGoto.m_nAlignStarRA1=g_mStarAlign[0];//�ྭ(0-24Сʱ)
	//g_mGoto.m_nAlignStarDec1=g_mStarAlign[1];//��γ(-90��90��)


	dg_mApos=0;
	dg_mZpos=0;
	dg_mApos_syn=0;
	dg_mZpos_syn=0;

    g_mTelError.mTSettingNP=0;//����ֱ
	g_mTelError.mTSettingLOS=0;//����ƫ��
	g_mTelError.mTSettingNS=0;//����
	g_mTelError.mTSettingEW=0;//����
	g_mTelError.mTSettingA0=0;//��λ��ƫ
	g_mTelError.mTSettingE0=0;//�߶���ƫ 

	g_mTelRALastPos=g_mTelRANextPos;
	g_mTelDecLastPos=g_mTelDecNextPos;

	FStartGoto();

}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//������У׼
void FTwoStarAlign()
{	

	g_mGoto.m_nAlignStarNum=2;//���ü�����У׼
    g_mGoto.m_nAlign=false;//��Զ���Ƿ��Ѿ�У��,trueУ���ˣ�false��û��У׼
    g_mGoto.m_nAlignAdjustNum=0;//��Զ��У׼ʱ���ڴ���
	
	//g_mAlignStarNum=FindAlignStar(FCalSiderealTime(1,false,g_mGoto.m_nLongitude),g_mGoto.m_nAtitude,g_mStarAlign);		

	
	//g_mGoto.m_nAlignStarRA1=g_mStarAlign[0];//�ྭ(0-24Сʱ)
	//g_mGoto.m_nAlignStarDec1=g_mStarAlign[1];//��γ(-90��90��)
	//g_mGoto.m_nAlignStarRA2=g_mStarAlign[2];//�ྭ(0-24Сʱ)
	//g_mGoto.m_nAlignStarDec2=g_mStarAlign[3];//��γ(-90��90��)
    
	dg_mApos=0;
	dg_mZpos=0;
	dg_mApos_syn=0;
	dg_mZpos_syn=0;

    g_mTelError.mTSettingNP=0;//����ֱ
	g_mTelError.mTSettingLOS=0;//����ƫ��
	g_mTelError.mTSettingNS=0;//����
	g_mTelError.mTSettingEW=0;//����
	g_mTelError.mTSettingA0=0;//��λ��ƫ
	g_mTelError.mTSettingE0=0;//�߶���ƫ 

	g_mTelRALastPos=g_mTelRANextPos;
	g_mTelDecLastPos=g_mTelDecNextPos;

	FStartGoto();

}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//������У׼
void FThreeStarAlign()
{

	g_mGoto.m_nAlignStarNum=3;//���ü�����У׼
    g_mGoto.m_nAlign=false;//��Զ���Ƿ��Ѿ�У��,trueУ���ˣ�false��û��У׼
    g_mGoto.m_nAlignAdjustNum=0;//��Զ��У׼ʱ���ڴ���

	//g_mAlignStarNum=FindAlignStar(FCalSiderealTime(1,false,g_mGoto.m_nLongitude),g_mGoto.m_nAtitude,g_mStarAlign);		
	//g_mGoto.m_nAlignStarRA1=g_mStarAlign[0];//�ྭ(0-24Сʱ)
	//g_mGoto.m_nAlignStarDec1=g_mStarAlign[1];//��γ(-90��90��)
	//g_mGoto.m_nAlignStarRA2=g_mStarAlign[2];//�ྭ(0-24Сʱ)
	//g_mGoto.m_nAlignStarDec2=g_mStarAlign[3];//��γ(-90��90��)
	//g_mGoto.m_nAlignStarRA3=g_mStarAlign[4];//�ྭ(0-24Сʱ)
	//g_mGoto.m_nAlignStarDec3=g_mStarAlign[5];//��γ(-90��90��)


	dg_mApos=0;
	dg_mZpos=0;
	dg_mApos_syn=0;
	dg_mZpos_syn=0;

    g_mTelError.mTSettingNP=0;//����ֱ
	g_mTelError.mTSettingLOS=0;//����ƫ��
	g_mTelError.mTSettingNS=0;//����
	g_mTelError.mTSettingEW=0;//����
	g_mTelError.mTSettingA0=0;//��λ��ƫ
	g_mTelError.mTSettingE0=0;//�߶���ƫ 


	g_mTelRALastPos=g_mTelRANextPos;
	g_mTelDecLastPos=g_mTelDecNextPos;

	FStartGoto();
}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//У׼����
void FStarCal(int fstarnum,CALSTARAZ fStarsPos,TSETTING *fTSetting)
{
/*	
	double ee;
	
	double A1,E1,A2,E2,A3,E3;
    double dta1,dte1,dta2,dte2,dta3,dte3;
	double ca11,ca12,ca13,ca14,ca15,ca16,ca21,ca22,ca23,ca24,ca25,ca26,ca31,ca32,ca33,ca34,ca35,ca36;
    double ce11,ce12,ce13,ce14,ce15,ce16,ce21,ce22,ce23,ce24,ce25,ce26,ce31,ce32,ce33,ce34,ce35,ce36;
    double a,a1,a2,e,e1,e2;
	
	double dde1,dce15,dce16,dde2,dce25,dce26; 
	double dda1,dda2,dca13,dca23,dca14,dca24;
	
	
	double da0,de0,we,ns,gam,snta;
	
    int nogma;
	nogma=1;
	
	ee=0.01745329252;
	
	switch(fstarnum)
	{
	case 1:
        A1=fStarsPos.mANzimuth1*ee;
		E1=fStarsPos.mAtitude1*ee;
		A2=0;
		E2=0;
		A3=0;
		E3=0;
		
		dta1=fStarsPos.mAPointEerror1;
		dta2=0;
		dta3=0;
		dte1=fStarsPos.mEPointEerror1;
		dte2=0;
		dte3=0;
		
        fTSetting->mTSettingA0=fStarsPos.mAPointEerror1;
		fTSetting->mTSettingE0=fStarsPos.mEPointEerror1;
		fTSetting->mTSettingEW=0;
		fTSetting->mTSettingNS=0;
		fTSetting->mTSettingLOS=0;
		fTSetting->mTSettingNP=0; 
		break;
	case 2:
		A1=fStarsPos.mANzimuth1*ee;
		E1=fStarsPos.mAtitude1*ee;
		A2=fStarsPos.mANzimuth2*ee;
		E2=fStarsPos.mAtitude2*ee;
		A3=0;
		E3=0;
		
		dta1=fStarsPos.mAPointEerror1;
		dta2=fStarsPos.mAPointEerror2;
		dta3=0;
		dte1=fStarsPos.mEPointEerror1;
		dte2=fStarsPos.mEPointEerror2;
		dte3=0;
		
		//���̽���
		//��λ��һ���Ƿ���ϵ��
		ca11=1;

      // mtest0=cos(E1);
	  
	   mtest0=fStarsPos.mANzimuth1*ee;
	   mtest=cos(fStarsPos.mANzimuth1*ee);

	   //mtest=mtest0/mtest;

		ca12=sin(A1)*sin(E1)/cos(E1);
		ca13=cos(A1)*sin(E1)/cos(E1);
		
		//��λ�ڶ����Ƿ���ϵ��
		ca21=1;
		ca22=sin(A2)*sin(E2)/cos(E2);
		ca23=cos(A2)*sin(E2)/cos(E2);
		
		//�߶ȵ�һ���Ƿ���ϵ��
		ce11=1;
		ce12=cos(A1);
		ce13=-1.0*sin(A1);
		
		//�߶ȵڶ����Ƿ���ϵ��
		ce21=1;
		ce22=cos(A2);
		ce23=-1.0*sin(A2);
		//*************************************** 
		//��ⷽ��
		//�м���Ԫ
		a=dta2-dta1;
		a1=ca22-ca12;
		a2=ca23-ca13;
		
		e=dte2-dte1;
		e1=ce22-ce12;
		e2=ce23-ce13;
		//****************************************
		
		we=(a*e2-a2*e)/(e2*a1-e1*a2);//������б
		ns=(a*e1-a1*e)/(e1*a2-e2*a1);//�ϱ���б
		
		da0=dta1-ca12*we-ca13*ns;//��λ���ƫ��
		de0=dte1-ce12*we-ce13*ns;//�߶����ƫ��
		//*****************************************
		
		fTSetting->mTSettingA0=da0;
		fTSetting->mTSettingE0=de0;
		fTSetting->mTSettingEW=we;
		fTSetting->mTSettingNS=ns;
		fTSetting->mTSettingLOS=0;
		fTSetting->mTSettingNP=0;
		//*****************************************	 
		break;
    case 3:
		A1=fStarsPos.mANzimuth1*ee;
		E1=fStarsPos.mAtitude1*ee;
		A2=fStarsPos.mANzimuth2*ee;
		E2=fStarsPos.mAtitude2*ee;
		A3=fStarsPos.mANzimuth3*ee;
		E3=fStarsPos.mAtitude3*ee;
		
		dta1=fStarsPos.mAPointEerror1;
		dta2=fStarsPos.mAPointEerror2;
		dta3=fStarsPos.mAPointEerror3;
		dte1=fStarsPos.mEPointEerror1;
		dte2=fStarsPos.mEPointEerror2;
		dte3=fStarsPos.mEPointEerror3;
		//***************************************
		
		//����ϵͳ
		//��һ���Ƿ�λ����ϵ��
		ca11=1;
		ca13=-1.0/cos(E1);
		ca14=tan(E1);
		ca15=tan(E1)*sin(A1);
		ca16=tan(E1)*cos(A1);
		
		//�ڶ����Ƿ�λ����ϵ��
		ca21=1;
		ca23=-1.0/cos(E2);
		ca24=tan(E2);
		ca25=tan(E2)*sin(A2);
		ca26=tan(E2)*cos(A2);
		
		//�������Ƿ�λ����ϵ��
		ca31=1;
		ca33=-1.0/cos(E3);
		ca34=tan(E3);
		ca35=tan(E3)*sin(A3);
		ca36=tan(E3)*cos(A3);
		
		//��һ���Ǹ߶ȷ���ϵ��
		ce11=1;
		ce15=cos(A1);
		ce16=-sin(A1);
		
		//�ڶ����Ǹ߶ȷ���ϵ��
		ce21=1;
		ce25=cos(A2);
		ce26=-sin(A2);
		
		//�������Ǹ߶ȷ���ϵ��
		ce31=1;
		ce35=cos(A3);
		ce36=-sin(A3);
		//***************************************
		
		//��ⷽ��
		//ͨ���߶ȵ�����������Ǹ߶����de0,����ns,����we;
		//***********
		//��de0
		dde1=dte2-dte1;   
		dce15=ce25-ce15;
		dce16=ce26-ce16;
		
		dde2=dte3-dte1;
		dce25=ce35-ce15;
		dce26=ce36-ce16;
		//**************
		//��we,ns
		we=(dde1*dce26-dce16*dde2)/(dce26*dce15-dce25*dce16);//������б
		ns=(dde1*dce25-dce15*dde2)/(dce25*dce16-dce26*dce15);//�ϱ���б
		//��de0
		de0=dte1-ce15*we-ce16*ns;
		//*************************
		//��λ��ƫda0,����gam,����ֱsnta
		switch(nogma)
		{
		case 1:
            gam=0;//�����ǹ���,//�����ǲ���ֱ
            snta=0;
			da0=(dta1-ca15*we-ca16*ns+dta2-ca25*we-ca26*ns+dta3-ca35*we-ca36*ns)/3;
			break;
		case 2:
            gam=0;//�����ǹ���
            //��da0
            dda1=dta2-ca25*we-ca26*ns-dta1+ca15*we+ca16*ns;
            dca14=ca24-ca14;
            
            dda2=dta3-ca35*we-ca36*ns-dta1+ca15*we+ca16*ns;
            dca24=ca34-ca14;
            
            snta=(dda2-dda1)/(dca24-dca14);
            da0=(dta1-ca14*snta-ca15*we-ca16*ns+dta2-ca24*snta-ca25*we-ca26*ns+dta3-ca34*snta-ca35*we-ca36*ns)/3;
			
			break;
		case 3:
            snta=0;//�����ǲ���ֱ
            //��da0
            dda1=dta2-ca25*we-ca26*ns-dta1+ca15*we+ca16*ns ;
            dca13=ca23-ca13;
            
            dda2=dta3-ca35*we-ca36*ns-dta1+ca15*we+ca16*ns;
            dca23=ca33-ca13;
            
            gam=(dda2-dda1)/(dca23-dca13);
            da0=(dta1-ca13*gam-ca15*we-ca16*ns+dta2-ca23*gam-ca25*we-ca26*ns+dta3-ca33*gam-ca35*we-ca36*ns)/3;
			break;
		case 4:
            //��da0
            dda1=dta2-ca25*we-ca26*ns-dta1+ca15*we+ca16*ns;  
            dca13=ca23-ca13;
            dca14=ca24-ca14;
			
            dda2=dta3-ca35*we-ca36*ns-dta1+ca15*we+ca16*ns;
			dca23=ca33-ca13;
            dca24=ca34-ca14;
            //**************
            //��gam,snta
            gam=(dda1*dca24-dca14*dda2)/(dca24*dca13-dca23*dca14);//����
            snta=(dda1*dca23-dca13*dda2)/(dca23*dca14-dca24*dca13);//����ֱ
            //��da0
            da0=dta1-ca13*gam-ca14*snta-ca15*we-ca16*ns;
			break;
			
		default:break;
			
		}
		//*****************************************
		
		fTSetting->mTSettingA0=da0;
		fTSetting->mTSettingE0=de0;
		fTSetting->mTSettingEW=we;
		fTSetting->mTSettingNS=ns;
		fTSetting->mTSettingLOS=gam;
		fTSetting->mTSettingNP=snta;
		//*****************************************
		break;
		default:break;
	} */
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//һ����У׼����
void FOneStarCal(CALSTARAZ fStarsPos,TSETTING *fTSetting)
{
        fTSetting->mTSettingA0=fStarsPos.mAPointEerror1;
		fTSetting->mTSettingE0=fStarsPos.mEPointEerror1;
		fTSetting->mTSettingEW=0;
		fTSetting->mTSettingNS=0;
		fTSetting->mTSettingLOS=0;
		fTSetting->mTSettingNP=0; 
}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

//������У׼����
void FTowStarCal(CALSTARAZ fStarsPos,TSETTING *fTSetting)
{
	
	double ee;
	
	double mA1,mE1,mA2,mE2,mA3,mE3;
    double dta1,dte1,dta2,dte2;
	double ca11,ca12,ca13,ca21,ca22,ca23 ;
    double ce11,ce12,ce13,ce21,ce22,ce23;
    double a,a1,a2,e,e1,e2;
	
		
	double da0,de0,we,ns;
	
	
	  ee=0.01745329252;
	
		mA1=fStarsPos.mANzimuth1*ee;
		mE1=fStarsPos.mAtitude1*ee;
	
		mA2=fStarsPos.mANzimuth2*ee;
		mE2=fStarsPos.mAtitude2*ee;
		
		
		dta1=fStarsPos.mAPointEerror1;
		dta2=fStarsPos.mAPointEerror2;
	
		dte1=fStarsPos.mEPointEerror1;
		dte2=fStarsPos.mEPointEerror2;
	
		
		//���̽���
		//��λ��һ���Ƿ���ϵ��
		ca11=1;

		ca12=sin(mA1)*sin(mE1)/cos(mE1);
		ca13=cos(mA1)*sin(mE1)/cos(mE1);
		
		//��λ�ڶ����Ƿ���ϵ��
		ca21=1;
		ca22=sin(mA2)*sin(mE2)/cos(mE2);
		ca23=cos(mA2)*sin(mE2)/cos(mE2);
		
		//�߶ȵ�һ���Ƿ���ϵ��
		ce11=1;
		ce12=cos(mA1);
		ce13=-1.0*sin(mA1);
		
		//�߶ȵڶ����Ƿ���ϵ��
		ce21=1;
		ce22=cos(mA2);
		ce23=-1.0*sin(mA2);
		//*************************************** 
		//��ⷽ��
		//�м���Ԫ
		a=dta2-dta1;
		a1=ca22-ca12;
		a2=ca23-ca13;
		
		e=dte2-dte1;
		e1=ce22-ce12;
		e2=ce23-ce13;
		//****************************************
		
//		we=(a*e2-a2*e)/(e2*a1-e1*a2);//������б
//		ns=(a*e1-a1*e)/(e1*a2-e2*a1);//�ϱ���б
//		
//		da0=dta1-ca12*we-ca13*ns;//��λ���ƫ��
//		de0=dte1-ce12*we-ce13*ns;//�߶����ƫ��

		we=(a*e1-a1*e)/(e1*a2-e2*a1);//������б
		ns=(a*e2-a2*e)/(e2*a1-e1*a2);//�ϱ���б
		
		da0=dta1-ca12*ns-ca13*we;//��λ���ƫ��
		de0=dte1-ce12*ns-ce13*we;//�߶����ƫ��

		//*****************************************
		
		fTSetting->mTSettingA0=da0;
		fTSetting->mTSettingE0=de0;
		fTSetting->mTSettingEW=we;
		fTSetting->mTSettingNS=ns;
		fTSetting->mTSettingLOS=0;
		fTSetting->mTSettingNP=0;



}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//������У׼����
void FThreeStarCal(CALSTARAZ fStarsPos,TSETTING *fTSetting)
{
	
 	double ee;
	
	double mA1,mE1,mA2,mE2,mA3,mE3;
    double dta1,dte1,dta2,dte2;
	double ca11,ca12,ca13,ca21,ca22,ca23 ;
    double ce11,ce12,ce13,ce21,ce22,ce23;
    double a,a1,a2,e,e1,e2;
	
		
	double da0,de0,we,ns;
	
	
	  ee=0.01745329252;
	
		mA1=fStarsPos.mANzimuth2*ee;
		mE1=fStarsPos.mAtitude2*ee;
	
		mA2=fStarsPos.mANzimuth3*ee;
		mE2=fStarsPos.mAtitude3*ee;
		
		
		dta1=fStarsPos.mAPointEerror2;
		dta2=fStarsPos.mAPointEerror3;
	
		dte1=fStarsPos.mEPointEerror2;
		dte2=fStarsPos.mEPointEerror3;
	
		
		//���̽���
		//��λ��һ���Ƿ���ϵ��
		ca11=1;

		ca12=sin(mA1)*sin(mE1)/cos(mE1);
		ca13=cos(mA1)*sin(mE1)/cos(mE1);
		
		//��λ�ڶ����Ƿ���ϵ��
		ca21=1;
		ca22=sin(mA2)*sin(mE2)/cos(mE2);
		ca23=cos(mA2)*sin(mE2)/cos(mE2);
		
		//�߶ȵ�һ���Ƿ���ϵ��
		ce11=1;
		ce12=cos(mA1);
		ce13=-1.0*sin(mA1);
		
		//�߶ȵڶ����Ƿ���ϵ��
		ce21=1;
		ce22=cos(mA2);
		ce23=-1.0*sin(mA2);
		//*************************************** 
		//��ⷽ��
		//�м���Ԫ
		a=dta2-dta1;
		a1=ca22-ca12;
		a2=ca23-ca13;
		
		e=dte2-dte1;
		e1=ce22-ce12;
		e2=ce23-ce13;
		//****************************************
		
//		we=(a*e2-a2*e)/(e2*a1-e1*a2);//������б
//		ns=(a*e1-a1*e)/(e1*a2-e2*a1);//�ϱ���б
//		
//		da0=dta1-ca12*we-ca13*ns;//��λ���ƫ��
//		de0=dte1-ce12*we-ce13*ns;//�߶����ƫ��

		we=(a*e1-a1*e)/(e1*a2-e2*a1);//������б
		ns=(a*e2-a2*e)/(e2*a1-e1*a2);//�ϱ���б
		
		da0=dta1-ca12*ns-ca13*we;//��λ���ƫ��
		de0=dte1-ce12*ns-ce13*we;//�߶����ƫ��

		//*****************************************
		
		fTSetting->mTSettingA0=da0;
		fTSetting->mTSettingE0=de0;
		fTSetting->mTSettingEW=we;
		fTSetting->mTSettingNS=ns;
		fTSetting->mTSettingLOS=0;
		fTSetting->mTSettingNP=0;



//	double dta1,dte1,dta2,dte2,dta3,dte3;
//	double ca11,ca12,ca13,ca14,ca15,ca16;
//	double ca21,ca22,ca23,ca24,ca25,ca26;
//	double ca31,ca32,ca33,ca34,ca35,ca36;
//    double ce11,ce12,ce13,ce14,ce15,ce16;
//	double ce21,ce22,ce23,ce24,ce25,ce26;
//	double ce31,ce32,ce33,ce34,ce35,ce36;
//    double a,a1,a2,e,e1,e2;
//	double ee;
//	
//	double mA1;
//	double mE1;
//	double mA2;
//	double mE2;
//	double mA3;
//	double mE3;
// 
//	
//	double dde1,dce15,dce16,dde2,dce25,dce26; 
//	double dda1,dda2,dca13,dca23,dca14,dca24;
////	double dca15,dca16;
//	
//	
//	double da0,de0,we,ns,gam,snta;
//
////	double we1,we2,we3,ns1,ns2,ns3;
//	
//    int nogma;
//	nogma=2;
//	
//	ee=0.01745329252;
//
//		mA1=fStarsPos.mANzimuth1*ee;
//		mE1=fStarsPos.mAtitude1*ee;
//		mA2=fStarsPos.mANzimuth2*ee;
//		mE2=fStarsPos.mAtitude2*ee;
//		mA3=fStarsPos.mANzimuth3*ee;
//		mE3=fStarsPos.mAtitude3*ee;
//		
//		dta1=fStarsPos.mAPointEerror1;
//		dta2=fStarsPos.mAPointEerror2;
//		dta3=fStarsPos.mAPointEerror3;
//		dte1=fStarsPos.mEPointEerror1;
//		dte2=fStarsPos.mEPointEerror2;
//		dte3=fStarsPos.mEPointEerror3;
//		//***************************************
//		
//		//����ϵͳ
//		//��һ���Ƿ�λ����ϵ��
//		ca11=1;
//		ca13=-1.0/cos(mE1);
//		ca14=sin(mE1)/cos(mE1);
//
//		ca15=ca14*sin(mA1);
//		ca16=ca14*cos(mA1);
//		
//		//�ڶ����Ƿ�λ����ϵ��
//		ca21=1;
//		ca23=-1.0/cos(mE2);
//		ca24=sin(mE2)/cos(mE2);
//		ca25=ca24*sin(mA2);
//		ca26=ca24*cos(mA2);
//		
//		//�������Ƿ�λ����ϵ��
//		ca31=1;
//		ca33=-1.0/cos(mE3);
//		ca34=sin(mE3)/cos(mE3);
//		ca35=ca34*sin(mA3);
//		ca36=ca34*cos(mA3);	
//		
//		//��һ���Ǹ߶ȷ���ϵ��
//		ce11=1;
//		ce15=cos(mA1);
//		ce16=-1.0*sin(mA1);
//		
//		//�ڶ����Ǹ߶ȷ���ϵ��
//		ce21=1;
//		ce25=cos(mA2);
//		ce26=-sin(mA2);
//		
//		//�������Ǹ߶ȷ���ϵ��
//		ce31=1;
//		ce35=cos(mA3);
//		ce36=-1.0*sin(mA3);
//		//***************************************
//		
//		//��ⷽ��
//		//ͨ���߶ȵ�����������Ǹ߶����de0,����ns,����we;
//		//***********
//		//��de0
//		dde1=dte2-dte1;   
//		dce15=ce25-ce15;
//		dce16=ce26-ce16;
//		
//		dde2=dte3-dte1;
//		dce25=ce35-ce15;
//		dce26=ce36-ce16;
//		//**************
//		//��we,ns										 
//		we=(dde1*dce25-dce15*dde2)/(dce25*dce16-dce26*dce15);//������б
//		ns=(dde1*dce26-dce16*dde2)/(dce26*dce15-dce25*dce16);//�ϱ���б
//		//��de0
//		de0=dte1-ce15*ns-ce16*we;
//		//*************************
//		//��λ��ƫda0,����gam,����ֱsnta
//		switch(nogma)
//		{
//		case 1:
//            gam=0;//�����ǹ���,//�����ǲ���ֱ
//            snta=0;
//			da0=(dta1-ca15*ns-ca16*we+dta2-ca25*ns-ca26*we+dta3-ca35*ns-ca36*we)/3.0;
//			break;
//		case 2:
//            gam=0;//�����ǹ���,���ǲ���ֱ
//            //��da0
//            dda1=dta2-ca25*ns-ca26*we-dta1+ca15*ns+ca16*we;
//            dca14=ca24-ca14;
//            
//            dda2=dta3-ca35*ns-ca36*we-dta1+ca15*ns+ca16*we;
//            dca24=ca34-ca14;
//            
//            //snta=(dda2-dda1)/(dca24-dca14);
//
//			snta=(dda1/dca14+dda2/dca24+(dta3-ca35*ns-ca36*we-dta2+ca25*ns+ca26*we)/(ca34-ca24))/3;
//            da0=dta3-ca34*snta-ca35*ns-ca36*we;
//
//			//da0=(dta1-ca14*snta-ca15*ns-ca16*we+dta2-ca24*snta-ca25*ns-ca26*we+dta3-ca34*snta-ca35*ns-ca36*we)/3;
//			
//		   /*
//			//�����ǹ��ᣬ���ǲ���ֱ�����Ƿ�λ�͸߶��������㣬�����㡣
//                gam=0;//�����ǹ���,���ǲ���ֱ
//
//			  	//��de0
//				dde1=dte2-dte1;   
//				dce15=ce25-ce15;
//				dce16=ce26-ce16;
//				
//				dde2=dte3-dte1;
//				dce25=ce35-ce15;
//				dce26=ce36-ce16;
//				//��ȥda0��snta�ã�
//				dda1=(dta3-dta1)*(ca24-ca14)-(dta2-dta1)*(ca34-ca14);
//				dca15=(ca35-ca15)*(ca24-ca14)-(ca25-ca15)*(ca34-ca14);
//				dca16=(ca36-ca16)*(ca24-ca14)-(ca26-ca16)*(ca34-ca14);
//
//				//һ����ns,we
//		
//				 //we=(dde2*dca15-dda1*dce25)/(dce26*dca15-dca16*dce25);
//				 //ns=(dde2*dca16-dda1*dce26)/(dce25*dca16-dca15*dce26);
//
//				 //������ns,we
//		
//				 //we=(dde1*dca15-dda1*dce15)/(dce16*dca15-dca16*dce15)+(dde2*dca15-dda1*dce25)/(dce26*dca15-dca16*dce25);
//				 //we=we/2.0;
//				 //ns=(dde1*dca16-dda1*dce16)/(dce15*dca16-dca15*dce16)+(dde2*dca16-dda1*dce26)/(dce25*dca16-dca15*dce26);
//				// ns=ns/2.0;
//
//				 //������ns,we												 		
//				 we1=(dde1*dca15-dda1*dce15)/(dce16*dca15-dca16*dce15);
//				 we2=(dde2*dca15-dda1*dce25)/(dce26*dca15-dca16*dce25);
//				 we3=(dde1*dce25-dce15*dde2)/(dce25*dce16-dce26*dce15); //������б
//
//				 we=(we1+we2+we3)/3;
//				 
//				 ns1=(dde1*dca16-dda1*dce16)/(dce15*dca16-dca15*dce16);
//				 ns2=(dde2*dca16-dda1*dce26)/(dce25*dca16-dca15*dce26);
//				 ns3=(dde1*dce26-dce16*dde2)/(dce26*dce15-dce25*dce16); //�ϱ���б
//
//				 ns=(ns1+ns2+ns3)/3;
//				 
//
//				 //�󲻴�ֱ
//				 snta=((dta3-dta1)-(ca35-ca15)*ns-(ca36-ca16)*we)/(ca34-ca14);
//				 //��λ��ƫ
//				 da0=dta3-ca34*snta-ca35*ns-ca36*we;
//				 //��߶���ƫ
//				 de0=dte3-ce35*ns-ce36*we;	*/
//
//			break;
//		case 3:
//            snta=0;//�����ǲ���ֱ,���ǹ���
//            //��da0
//            dda1=dta2-ca25*ns-ca26*we-dta1+ca15*ns+ca16*we ;
//            dca13=ca23-ca13;
//            
//            dda2=dta3-ca35*ns-ca36*we-dta1+ca15*ns+ca16*we;
//            dca23=ca33-ca13;
//            
//            gam=(dda2-dda1)/(dca23-dca13);
//            da0=(dta1-ca13*gam-ca15*ns-ca16*we+dta2-ca23*gam-ca25*ns-ca26*we+dta3-ca33*gam-ca35*ns-ca36*we)/3;
//			break;
//		case 4:
//            //��da0
//            dda1=dta2-ca25*ns-ca26*we-dta1+ca15*ns+ca16*we;  
//            dca13=ca23-ca13;
//            dca14=ca24-ca14;
//			
//            dda2=dta3-ca35*ns-ca36*we-dta1+ca15*ns+ca16*we;
//			dca23=ca33-ca13;
//            dca24=ca34-ca14;
//            //**************
//            //��gam,snta
//            gam=(dda1*dca24-dca14*dda2)/(dca24*dca13-dca23*dca14);//����
//            snta=(dda1*dca23-dca13*dda2)/(dca23*dca14-dca24*dca13);//����ֱ
//            //��da0
//            da0=dta1-ca13*gam-ca14*snta-ca15*ns-ca16*we;
//			break;
//		default:break;
//			
//		}
//		//*****************************************
//		
//		fTSetting->mTSettingA0=da0;
//		fTSetting->mTSettingE0=de0;
//		fTSetting->mTSettingNS=ns;
//		fTSetting->mTSettingEW=we;
//		fTSetting->mTSettingLOS=gam;
//		fTSetting->mTSettingNP=snta;
//		//****************************************
}


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//ϵͳ������ʼ��
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void FSetupPointTrackPara()
{ 
	//ϵͳ����
    g_mGoto.m_nTescpType=1;//��Զ���ͺ�
	g_mGoto.m_nSysTimeType=1;//ϵͳʱ������,1����ʱ��2����ʱ
	g_mGoto.m_nNutation=false;//����ط�����ʱ�Ƿ���¶�����
	
	g_mGoto.m_nTescpASpeedRatio=0.22701751051996061392472493380255;/*meade��*///0.20870217144665865116076517155392(���ۣ�;//��λ������,��Զ���ٶ������ֵ�������ӣ��봫���Ⱥ������������,һ������ֵ������/���ת��
	g_mGoto.m_nTescpESpeedRatio=0.16521502345690755559422189482536;/*meade��*///0.20870217144665865116076517155392(���ۣ�;//�߶ȴ�����,��Զ���ٶ������ֵ�������ӣ��봫���Ⱥ������������,һ������ֵ������/���ת��
    
   

	g_mGoto.m_nTescpAPosRatio=3.3046489801853247148087930100065e-4;/*meade��*///0.0003038036213391663628630453275003(���ۣ�;//��Զ��λ�÷�����ֵ�������ӣ��봫���Ⱥ������������,һ������ֵ���ȵ�ת��
	g_mGoto.m_nTescpEPosRatio=2.4050024050024050024050024050024e-4;/*meade��*///0.0003038036213391663628630453275003(���ۣ�;///��Զ��λ�÷�����ֵ�������ӣ��봫���Ⱥ������������,һ������ֵ���ȵ�ת��



   //************
	//�۲��λ��
	g_mGoto.m_nLongitude=102.7944;//����(-180�ȵ�180��)��������
	g_mGoto.m_nAtitude=25.027777;//γ��(-90�ȵ�90��)�����ϸ�
	g_mGoto.m_nTimeZone=8;//�۲��ʱ��(-12��12);
//	g_mGoto.m_nSiteHigh=1568;//����km
	//************
	//�۲�Ŀ��ྭ��γ
	g_mGoto.m_nObjectType=1;//�۲�Ŀ�����ͣ�1���ǣ�2̫����3������4���ǣ�5����,6��ֹĿ��
	g_mGoto.m_nRightAscension=4.4993833;;//�ྭ(0-24Сʱ)
	g_mGoto.m_nDeclination=-26.453416667;//��γ(-90��90��)
	//************
	//�۲�Ŀ���ƽ����
	//	g_mGoto.m_nStarAPos;//Ŀ�귽λ
	//   g_mGoto.m_nStarEPos;//Ŀ��߶�
	//	g_mGoto.m_nStarASpeed;//Ŀ�귽λ�����ٶ�
	//	g_mGoto.m_nStarESpeed;//Ŀ��߶������ٶ�
    //��Զ������״̬
	//g_mGoto.m_nTescpAPos;//��Զ���ķ�λ����
    //g_mGoto.m_nTescpEPos;//��Զ���ĸ߶�����
	//g_mGoto.m_nAPosError;//�Ƿ�λ����Զ����λ��λ�����
	//g_mGoto.m_nEPosError;//�Ǹ߶�����Զ���߶ȵ�λ�����
	g_mGoto.m_nAPosEIZero=0;//��Զ����λ���������
    g_mGoto.m_nEPosEIZero=0;//��Զ���߶����������
	//	g_mGoto.m_nTescpASpeed;//��Զ����λ����ʱ�������ٶ�
	//	g_mGoto.m_nTescpESpeed;//��Զ���߶ȸ���ʱ�������ٶ�
    g_mGoto.m_nTescpASpeedMax=500;//��Զ����λ��λʱ����������ٶ�
	g_mGoto.m_nTescpESpeedMax=160;//��Զ���߶ȸ���ʱ����������ٶ�
	g_mGoto.m_nTescpAAcc=100;//��Զ����λ��λʱ�ļ��ٶ�
	g_mGoto.m_nTescpEAcc=50;//��Զ���߶ȸ���ʱ�ļ��ٶ�

    g_mGoto.m_nTAState=0;//��Զ����λ������״̬,0Ϊ��״̬��1Ϊ��λ״̬��2Ϊ����״̬,3ֹͣ״̬
	g_mGoto.m_nTEState=0;//��Զ���߶ȵ�����״̬,0Ϊ��״̬��1Ϊ��λ״̬��2Ϊ����״̬,3ֹͣ״̬
	
	g_mGoto.m_nGoto=false;//��Զ����ʼ״̬Ϊû��������GOTO״̬
	g_mGoto.m_nStartStop=false;//falseֹͣGOTO
	g_mGoto.m_nUnderhorizon=false;//�ǳ�ʼ��Ϊ���ڵ�ƽ����

	g_mGoto.m_nTCrossZeroP=false;//��Զ��������ʱ�Ƿ�������Խ
	g_mGoto.m_nTCrossZeroN=false;//��Զ��������ʱ�Ƿ��и���Խ
	g_mGoto.m_nTPointDirect=0;//��Զ����λ������

	g_mGoto.m_nTelGotoPause=0;//��Զ����λ����ת���������Ƿ���ͣ,0����ͣ��1��ͣ


	//��Զ���Զ�У׼������
	g_mGoto.m_nAlignStarNum=0;//���ü�����У׼
    g_mGoto.m_nAlign=true;//��Զ���Ƿ��Ѿ�У��,trueУ���ˣ�false��û��У׼
	g_mGoto.m_nAlignAdjust=false;//��Զ���Ƿ���������
	g_mGoto.m_nTAlignState=0;//��Զ���Ƿ���У��״̬
    g_mGoto.m_nAlignAdjustNum=0;//��Զ��У׼ʱ���ڴ���

	g_mGoto.m_nAlignStarRA1=12.0;//�ྭ(0-24Сʱ)
	g_mGoto.m_nAlignStarDec1=-16.0;//��γ(-90��90��)
	g_mGoto.m_nAlignStarRA2=10.0;//�ྭ(0-24Сʱ)
	g_mGoto.m_nAlignStarDec2=0.0;//��γ(-90��90��)
	g_mGoto.m_nAlignStarRA3=16.0;//�ྭ(0-24Сʱ)
	g_mGoto.m_nAlignStarDec3=10.0;//��γ(-90��90��)


	g_mGoto.m_nTSettingNP=0;//����ֱ
	g_mGoto.m_nTSettingLOS=0;//����ƫ��
	g_mGoto.m_nTSettingNS=0;//����
	g_mGoto.m_nTSettingEW=0;//����
	g_mGoto.m_nTSettingA0=10;//��λ��ƫ
	g_mGoto.m_nTSettingE0=0;//�߶���ƫ 

    g_mGoto.m_nTSettingAA0=0;//��λ��ƫ����
	g_mGoto.m_nTSettingEE0=0;//�߶���ƫ����

	g_mGoto.m_nStarAPosTshow=0;//Ŀ�귽λ��Զ������ϵ����,������ʾ
    g_mGoto.m_nStarEPosTshow=0;//Ŀ��߶���Զ������ϵ����,������ʾ

	
	//��������������
//	g_mGoto.m_nAirP=880;//����ѹmba
//	g_mGoto.m_nAirT=20;//�¶�c
	


	 g_mLandMark=false;//��½Ŀ�껹�����Ŀ��,false���Ŀ�꣬true½��Ŀ��


	g_mTelError.mTSettingA0=0;//TSetting.mTSettingA0;
	g_mTelError.mTSettingE0=0;//TSetting.mTSettingE0;
	g_mTelError.mTSettingLOS=0;//TSetting.mTSettingLOS;
	g_mTelError.mTSettingNP=0;//TSetting.mTSettingNP;
	g_mTelError.mTSettingEW=0;//TSetting.mTSettingEW;
	g_mTelError.mTSettingNS=0;//TSetting.mTSettingNS;

   	g_mPointNewStar=false;//�Ƿ�ָ�����µ�һ���ǣ�trueָ��,ָ�˾ʹ�Ϊ����۲���ǣ�falseû��ָ

	dg_mApos=0;
	dg_mZpos=0;


	dg_mApos0=0;
	dg_mZpos0=0;

	//ddg_mApos=0;
	//ddg_mZpos=0;

	syn_mApos=0;//��λ����ʱ��ͬ����
    syn_mZpos=0;//�춥����ʱ��ͬ����

	g_mAlignShow=0;//У׼�����е���ʾ����

	g_mPointNewStarTracking=0;
	g_mstartOTAset=0;//����ʱ������Զ���ĳ�ʼָ��

	g_mGoto.m_nGuidMoveRa=0;//��絼�ǳྭƫ����
	g_mGoto.m_nGuidMoveDec=0;//��絼�ǳ�γƫ����
}


//*************��������://�ֱ�����
void FBeep(uint8 fsceond)
{
   
   BuzOnTime=fsceond*32;
   BuzOffTime=BuzOnTime-1;
}
void FBeep1(uint8 fsceond)
{
   
   BuzOnTime=fsceond*2;
   BuzOffTime=BuzOnTime-1;
}


//*******************************************
 //������������ʱ��
 //��ڲ���
//selectnum=1:����, =2:����, =3:����
//g_mochj�ྭ
//g_mochw��γ
//g_mpjd����
//g_mpwdγ��
//g_mzoneʱ��


//���ڲ���
//  ���ع۲��۲�Ŀ���������졢����ı���ʱ��
 
double FSRiseSettime(int selectnum,double g_mochj,double g_mochw,double g_mpjd,double g_mpwd,uint8 g_mzone)
{
        double BjTime,LocalTime;                    //    ����ʱ���ط�ƽʱ
		double LocalStarTime,LocalStarTime0;      //    �ط�����ʱ���ط�ƽʱ0h�ĵط�����ʱ
		double v;         //     ��λ����ϵ��
		double v0;
		double t;         //     ��������û��ʱ��
        
		g_mochj=g_mochj*15.0;		 
	    v=1.0/366.2422;
		v0=1.0/365.2422;	
 		t=fabs(acos((cos(1.58068652588953)-sin(g_mpwd*0.01745329251994)*sin(g_mochw*0.01745329251994))/(cos(g_mpwd*0.01745329251994)*cos(g_mochw*0.01745329251994))))*3.81971863420549;
		
		if(1==selectnum)
		    {
		        LocalStarTime=g_mochj/15.0-t;         //��������ĵط�����ʱ  
		    }
		if(2==selectnum)
		    {
		        LocalStarTime=g_mochj/15.0;           //��������ĵط�����ʱ
		    }
		if(3==selectnum)
		    {
		        LocalStarTime=g_mochj/15.0+t;         //�������µĵط�����ʱ
		    }

    LocalStarTime0=g_mgwt-g_mpjd/15.0*v0;

	while((LocalStarTime-LocalStarTime0)<0.0)
		LocalStarTime=LocalStarTime+24.0;
	while((LocalStarTime-LocalStarTime0)>24.0)
		LocalStarTime=LocalStarTime-24.0;
	

    LocalTime=(LocalStarTime-LocalStarTime0)*(1.0-v);
		BjTime=LocalTime+(g_mGoto.m_nTimeZone-g_mpjd/15.0);             


	while(BjTime<=0.0)
	{
		BjTime+=24.0;
	}
	while(BjTime>=24.0)
	{
		BjTime-=24.0;
	}
    //  ���ع۲��۲�Ŀ���������졢����ı���ʱ��
 	return BjTime;
}


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//��λ�����������
void FDriveTelescope(double faspeed,double fzspeed)
{	
	
	if(g_mTelescopeConType==1)
	{
         	//2011��5��30���ִ˴����ȿ���
			//g_mGoto.m_nTescpASpeedRatio=0.075736993550978891820580474933707;//��λ������,��Զ���ٶ������ֵ�������ӣ��봫���Ⱥ������������,һ������ֵ������/���ת��
			//g_mGoto.m_nTescpESpeedRatio=0.075736993550978891820580474933707;//�߶ȴ�����,��Զ���ٶ������ֵ�������ӣ��봫���Ⱥ������������,һ������ֵ������/���ת��
		    
		
			//g_mGoto.m_nTescpAPosRatio=1.0993843447669305189094107299912e-4;//��Զ��λ�÷�����ֵ�������ӣ��봫���Ⱥ������������,һ������ֵ���ȵ�ת��
			//g_mGoto.m_nTescpEPosRatio=1.0993843447669305189094107299912e-4;//��Զ��λ�÷�����ֵ�������ӣ��봫���Ⱥ������������,һ������ֵ���ȵ�ת��
	
	
	       //2011��5��30�������ϴ����ȿ��ˣ����������Ϊ 
		   //1������Ϊ6810.810811
		  	//g_mGoto.m_nTescpASpeedRatio=0.084290465121894868032328317156678;//��λ������,��Զ���ٶ������ֵ�������ӣ��봫���Ⱥ������������,һ������ֵ������/���ת��
			//g_mGoto.m_nTescpESpeedRatio=0.084290465121894868032328317156678;//�߶ȴ�����,��Զ���ٶ������ֵ�������ӣ��봫���Ⱥ������������,һ������ֵ������/���ת��
		    		
			//g_mGoto.m_nTescpAPosRatio=1.2235449735109861845982398017506e-4;//��Զ��λ�÷�����ֵ�������ӣ��봫���Ⱥ������������,һ������ֵ���ȵ�ת��
			//g_mGoto.m_nTescpEPosRatio=1.2235449735109861845982398017506e-4;//��Զ��λ�÷�����ֵ�������ӣ��봫���Ⱥ������������,һ������ֵ���ȵ�ת��
			//2������Ϊ7611.428571
		  	g_mGoto.m_nTescpASpeedRatio=0.075424265729001741688945293262234;//��λ������,��Զ���ٶ������ֵ�������ӣ��봫���Ⱥ������������,һ������ֵ������/���ת��
			g_mGoto.m_nTescpESpeedRatio=0.075424265729001741688945293262234;//�߶ȴ�����,��Զ���ٶ������ֵ�������ӣ��봫���Ⱥ������������,һ������ֵ������/���ת��
		    		
			g_mGoto.m_nTescpAPosRatio=1.0948448449064915140400301778426e-4;//��Զ��λ�÷�����ֵ�������ӣ��봫���Ⱥ������������,һ������ֵ���ȵ�ת��
			g_mGoto.m_nTescpEPosRatio=1.0948448449064915140400301778426e-4;//��Զ��λ�÷�����ֵ�������ӣ��봫���Ⱥ������������,һ������ֵ���ȵ�ת��
	
	
	 }
	  		
	   
	   if(!g_mGotoHandMove)
	   {
		   if(((g_mGoto.m_nStarASpeed>0)&&((g_mGoto.m_nTescpAPos-g_mGoto.m_nStarAPos)>0.005))||((g_mGoto.m_nStarASpeed<0)&&((g_mGoto.m_nTescpAPos-g_mGoto.m_nStarAPos)<-0.005)))
		   {
			  if(g_mTelescopeConType==1)
			  {
			   sendpos.i=(long int)((g_mGoto.m_nStarAPos-0.0*g_mGoto.m_nStarASpeed/3600.0)*(256.0)/g_mGoto.m_nTescpAPosRatio);
			   
			  }
			  else
			  {
			    sendpos.i=(long int)((g_mGoto.m_nStarAPos-0.6*g_mGoto.m_nStarASpeed/3600.0)*(256.0)/g_mGoto.m_nTescpAPosRatio);
			  }
			   sendspd.i=(int)(1.0*faspeed/g_mGoto.m_nTescpASpeedRatio);
		   }
		   else
		   {
			   
			  if(g_mTelescopeConType==1)
			  {
			   sendpos.i=(long int)((g_mGoto.m_nStarAPos+0.0*g_mGoto.m_nStarASpeed/3600.0)*(256.0)/g_mGoto.m_nTescpAPosRatio);
			   }
			   else
			   {
				 sendpos.i=(long int)((g_mGoto.m_nStarAPos+0.6*g_mGoto.m_nStarASpeed/3600.0)*(256.0)/g_mGoto.m_nTescpAPosRatio);
			   }
			   sendspd.i=(int)(1.0*faspeed/g_mGoto.m_nTescpASpeedRatio);
		   }
			 
		
		
			 
			  if(g_mTelescopeConType==2)
	          {
			   if(sendspd.i>980)
			   {
			       sendspd.i=980;
				 }
			  }
			  else
			  {
			    if(sendspd.i>2000)
			   {
			       sendspd.i=2000;
				}
			  }



				 if(g_mGoto.m_nTelGotoPause==1)
				 {
				    sendspd.i=0;
				 }

		      if(g_mTelescopeConType==1)
			  {
			    if(g_mGoto.m_nTAState==2)//����ʱ��������ٵ��ٶ�//�����䶨λ�ٶ�
		         { 		   
		   	        if(g_mAposModify==0)
					{
						sendspd.i=5;
					 }
				    if((m_GuiderRa!=0)||(AGuiderRa))//�Զ�����ʱ����������ٶ�
				    {
					 
				        sendspd.i=6+2*(m_GuiderRa+3*AGuiderRa);
					   
				    }
					
				}

				if(g_mAposModify!=0)
				{
				    switch(g_mHandSpeed)	
					{
                         case 1:
						    sendspd.i=6+2*g_mAposModify;
						    break;
						 case 2:
						    sendspd.i=16;
						 	break;
						 case 3:
						    sendspd.i=60;
							break;
						  case 4:
							sendspd.i=240;
							break;
					     case 5:
						    sendspd.i=460;
						    break;
						 case 6:
						    sendspd.i=640;
						 	break;
						 case 7:
						    sendspd.i=2000;
							if(g_mHandSpeedAzi>=sendspd.i)
							{
						       g_mHandSpeedAzi=sendspd.i; //����Զ������ʱ���ֶ���λ�ٶ�
							}
							else
							{
							   g_mHandSpeedAzi+=400;
							}
							sendspd.i=g_mHandSpeedAzi;    
							break;
						  case 8:
						    sendspd.i=3200;
							if(g_mHandSpeedAzi>=sendspd.i)
							{
						       g_mHandSpeedAzi=sendspd.i; //����Զ������ʱ���ֶ���λ�ٶ�
							}
							else
							{
							   g_mHandSpeedAzi+=640;
							}
							sendspd.i=g_mHandSpeedAzi;
						 	break;

						  case 9:
	                    	sendspd.i=4800;
							if(g_mHandSpeedAzi>=sendspd.i)
							{
						       g_mHandSpeedAzi=sendspd.i; //����Զ������ʱ���ֶ���λ�ٶ�
							}
							else
							{
							   g_mHandSpeedAzi+=800;
							}
							sendspd.i=g_mHandSpeedAzi;
						 	break;

					 }
					 
				}


				
			   //mtest1=sendspd.i;	 
		 	   //mtest0=g_mAposModify;

				UART1_SentByte(0x55);
				UART1_SentByte(0xAA);
			    UART1_SentByte(0x01);
				UART1_SentByte(0x06);
				UART1_SentByte(2);
				UART1_SentByte(sendspd.ub[1]);
				UART1_SentByte(sendspd.ub[0]);
				UART1_SentByte(sendpos.ub[3]);
				UART1_SentByte(sendpos.ub[2]);
				UART1_SentByte(sendpos.ub[1]);


				
							
			  }
			  else
			  {
			    if(g_mAposModify!=0)
				{
				    switch(g_mHandSpeed)	
					{
                         case 1:
						    sendspd.i=8;
						    break;
						 case 2:
						    sendspd.i=16;
						 	break;
						 case 3:
						    sendspd.i=32;
							break;
						  case 4:
							sendspd.i=64;
							break;
					     case 5:
						    sendspd.i=100;
						    break;
						 case 6:
						    sendspd.i=200;
						 	break;
						 case 7:
						    sendspd.i=400;
//							if(g_mHandSpeedAzi>=sendspd.i)
//							{
//						       g_mHandSpeedAzi=sendspd.i; //����Զ������ʱ���ֶ���λ�ٶ�
//							}
//							else
//							{
//							   g_mHandSpeedAzi+=320;
//							}
//							sendspd.i=g_mHandSpeedAzi;    
							break;
						  case 8:
						    sendspd.i=600;
//							if(g_mHandSpeedAzi>=sendspd.i)
//							{
//						       g_mHandSpeedAzi=sendspd.i; //����Զ������ʱ���ֶ���λ�ٶ�
//							}
//							else
//							{
//							   g_mHandSpeedAzi+=320;
//							}
//							sendspd.i=g_mHandSpeedAzi;
//						 	break;

						  case 9:
	                    	sendspd.i=980;
//							if(g_mHandSpeedAzi>=sendspd.i)
//							{
//						       g_mHandSpeedAzi=sendspd.i; //����Զ������ʱ���ֶ���λ�ٶ�
//							}
//							else
//							{
//							   g_mHandSpeedAzi+=320;
//							}
//							sendspd.i=g_mHandSpeedAzi;
						 	break;

					 }
				}
				if(sendspd.i>980)
			    {
			       sendspd.i=980;
				 }

			   	UART1_SentByte(0x55);
				UART1_SentByte(0xAA);
			    UART1_SentByte(0x01);
				UART1_SentByte(0x06);
				UART1_SentByte(66);
				UART1_SentByte(sendspd.ub[1]);
				UART1_SentByte(sendspd.ub[0]);
				UART1_SentByte(sendpos.ub[3]);
				UART1_SentByte(sendpos.ub[2]);
				UART1_SentByte(sendpos.ub[1]);
			
				}
			
			   if(g_mTelescopeConType==1)
		       {		 
		         sendpos.i=(long int)((g_mGoto.m_nStarEPos+0.0*g_mGoto.m_nStarESpeed/3600.0)*(256.0)/g_mGoto.m_nTescpEPosRatio);
				}
				else
				{
				  sendpos.i=(long int)((g_mGoto.m_nStarEPos+1.0*g_mGoto.m_nStarESpeed/3600.0)*(256.0)/g_mGoto.m_nTescpEPosRatio);
				}


		       sendspd.i=(int)(1.0*fzspeed/g_mGoto.m_nTescpESpeedRatio);

			   if(g_mTelescopeConType==2)
	          {
			   if(sendspd.i>980)
			   {
			       sendspd.i=980;
				 }
			  }
			   else
			  {
			     if(sendspd.i>2000)
			   {
			       sendspd.i=2000;
				 }
			  }

			  	 if(g_mGoto.m_nTelGotoPause==1)
				 {
				    sendspd.i=0;
				 }


			  
		     MenuDelay(20);
		

		    if(g_mTelescopeConType==1)
			  {
			    if(g_mZposModify!=0)
				{
                    switch(g_mHandSpeed)	
					{
                         case 1:
						    sendspd.i=4;
						    break;
						 case 2:
						    sendspd.i=16;
						 	break;
						 case 3:
						    sendspd.i=60;
							break;
						  case 4:
							sendspd.i=240;
							break;
					     case 5:
						    sendspd.i=460;
						    break;
						 case 6:
						    sendspd.i=640;
						 	break;
						case 7:
						    sendspd.i=2000;
							if(g_mHandSpeedAlt>=sendspd.i)
							{
						       g_mHandSpeedAlt=sendspd.i; //����Զ������ʱ���ֶ���λ�ٶ�
							}
							else
							{
							   g_mHandSpeedAlt+=400;
							}
							sendspd.i=g_mHandSpeedAlt;    
							break;
						  case 8:
						    sendspd.i=3200;
							if(g_mHandSpeedAlt>=sendspd.i)
							{
						       g_mHandSpeedAlt=sendspd.i; //����Զ������ʱ���ֶ���λ�ٶ�
							}
							else
							{
							   g_mHandSpeedAlt+=640;
							}
							sendspd.i=g_mHandSpeedAlt;
						 	break;

						  case 9:
	                    	sendspd.i=4800;
							if(g_mHandSpeedAlt>=sendspd.i)
							{
						       g_mHandSpeedAlt=sendspd.i; //����Զ������ʱ���ֶ���λ�ٶ�
							}
							else
							{
							   g_mHandSpeedAlt+=800;
							}
							sendspd.i=g_mHandSpeedAlt;
						 	break;

					 }
				}
				

			    UART1_SentByte(0x55);
				UART1_SentByte(0xAA);
			    UART1_SentByte(0x01);
				UART1_SentByte(0x06);
				UART1_SentByte(34);
				UART1_SentByte(sendspd.ub[1]);
				UART1_SentByte(sendspd.ub[0]);
				UART1_SentByte(sendpos.ub[3]);
				UART1_SentByte(sendpos.ub[2]);
				UART1_SentByte(sendpos.ub[1]);
						   
				
			  }

			  else
			  {
			  	if(g_mZposModify!=0)
				{
                    switch(g_mHandSpeed)	
					{
                         case 1:
						    sendspd.i=5;
						    break;
						 case 2:
						    sendspd.i=13;
						 	break;
						 case 3:
						    sendspd.i=50;
							break;
						  case 4:
							sendspd.i=85;
							break;
					     case 5:
						    sendspd.i=150;
						    break;
						 case 6:
						    sendspd.i=220;
						 	break;
						case 7:
						    sendspd.i=500;
//							if(g_mHandSpeedAlt>=sendspd.i)
//							{
//						       g_mHandSpeedAlt=sendspd.i; //����Զ������ʱ���ֶ���λ�ٶ�
//							}
//							else
//							{
//							   g_mHandSpeedAlt+=320;
//							}
//							sendspd.i=g_mHandSpeedAlt;    
							break;
						  case 8:
						    sendspd.i=800;
//							if(g_mHandSpeedAlt>=sendspd.i)
//							{
//						       g_mHandSpeedAlt=sendspd.i; //����Զ������ʱ���ֶ���λ�ٶ�
//							}
//							else
//							{
//							   g_mHandSpeedAlt+=320;
//							}
//							sendspd.i=g_mHandSpeedAlt;
						 	break;

						  case 9:
	                    	sendspd.i=980;
//							if(g_mHandSpeedAlt>=sendspd.i)
//							{
//						       g_mHandSpeedAlt=sendspd.i; //����Զ������ʱ���ֶ���λ�ٶ�
//							}
//							else
//							{
//							   g_mHandSpeedAlt+=320;
//							}
//							sendspd.i=g_mHandSpeedAlt;
						 	break;

					 }
				}
				if(sendspd.i>980)
			    {
			       sendspd.i=980;
				 }

				UART1_SentByte(0x55);
				UART1_SentByte(0xAA);
			    UART1_SentByte(0x01);
				UART1_SentByte(0x06);
				UART1_SentByte(98);
				UART1_SentByte(sendspd.ub[1]);
				UART1_SentByte(sendspd.ub[0]);
				UART1_SentByte(sendpos.ub[3]);
				UART1_SentByte(sendpos.ub[2]);
				UART1_SentByte(sendpos.ub[1]);

					
			 }
			 MenuDelay(10);
		    
		}	 


}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//��λ�����������
void FDriveTelescopeNew()
{	
//   	 
//	union POS{
//		long int i;
//		unsigned char ub[4];
//		}msendpos;
//	
//	union SPD{
//		int i;
//		unsigned char ub[2	];
//		}msendspd,msendspda,msendspde;
//
//	 
//   	double m_nDriveAStarPos,m_nDriveEStarPos;
//   	double m_nDriveAStarSpeed,m_nDriveEStarSpeed;	 
//
//   	double m_nDriveATelPos,m_nDriveETelPos;
//   	double m_nDriveATelSpeed,m_nDriveETelSpeed;
//
//
//	m_nDriveAStarPos=g_mGoto.m_nStarAPos;
//    m_nDriveEStarPos=g_mGoto.m_nStarEPos;
//	m_nDriveAStarSpeed=g_mGoto.m_nStarASpeed;
//    m_nDriveEStarSpeed=g_mGoto.m_nStarESpeed;
//	
//	m_nDriveATelPos=g_mGoto.m_nTescpAPos;
//    m_nDriveETelPos=g_mGoto.m_nTescpEPos;
//	m_nDriveATelSpeed=g_mGoto.m_nTescpASpeed;
//    m_nDriveETelSpeed=g_mGoto.m_nTescpESpeed;
//
//
//
//
//	if(g_mTelescopeConType==1)
//	{
//			g_mGoto.m_nTescpASpeedRatio=0.075736993550978891820580474933707;//��λ������,��Զ���ٶ������ֵ�������ӣ��봫���Ⱥ������������,һ������ֵ������/���ת��
//			g_mGoto.m_nTescpESpeedRatio=0.075736993550978891820580474933707;//�߶ȴ�����,��Զ���ٶ������ֵ�������ӣ��봫���Ⱥ������������,һ������ֵ������/���ת��
//		    
//		
//			g_mGoto.m_nTescpAPosRatio=1.09938e-4;//��Զ��λ�÷�����ֵ�������ӣ��봫���Ⱥ������������,һ������ֵ���ȵ�ת��
//			g_mGoto.m_nTescpEPosRatio=1.09938e-4;//��Զ��λ�÷�����ֵ�������ӣ��봫���Ⱥ������������,һ������ֵ���ȵ�ת��
//	 }
//
//	   if(!g_mGotoHandMove)
//	   {
//		   if(((m_nDriveAStarSpeed>0)&&((m_nDriveATelPos-m_nDriveAStarPos)>0.005))||((	m_nDriveAStarSpeed<0)&&((m_nDriveATelPos-m_nDriveAStarPos)<-0.005)))
//		   {
//			   
//			   msendpos.i=(long int)((m_nDriveAStarPos-2.0*m_nDriveAStarSpeed*3600.0)*(256.0)/g_mGoto.m_nTescpAPosRatio);
//			   msendspd.i=(int)(1.0*m_nDriveATelSpeed/g_mGoto.m_nTescpASpeedRatio);
//		   }
//		   else
//		   {
//			   
//			   msendpos.i=(long int)((m_nDriveAStarPos+2.0*m_nDriveAStarSpeed/3600.0)*(256.0)/g_mGoto.m_nTescpAPosRatio);
//			   msendspd.i=(int)(1.0*m_nDriveATelSpeed/g_mGoto.m_nTescpASpeedRatio);
//		   }
//		 
//		      if(g_mTelescopeConType==1)
//			  {
//			  	UART1_SentByte(0x55);
//				UART1_SentByte(0xAA);
//			    UART1_SentByte(0x01);
//				UART1_SentByte(0x06);
//				UART1_SentByte(2);
//				UART1_SentByte(msendspd.ub[1]);
//				UART1_SentByte(msendspd.ub[0]);
//				UART1_SentByte(msendpos.ub[3]);
//				UART1_SentByte(msendpos.ub[2]);
//				UART1_SentByte(msendpos.ub[1]);
//			
//			  }
//			  else
//			  {
//			   	UART1_SentByte(0x55);
//				UART1_SentByte(0xAA);
//			    UART1_SentByte(0x01);
//				UART1_SentByte(0x06);
//				UART1_SentByte(66);
//				UART1_SentByte(msendspd.ub[1]);
//				UART1_SentByte(msendspd.ub[0]);
//				UART1_SentByte(msendpos.ub[3]);
//				UART1_SentByte(msendpos.ub[2]);
//				UART1_SentByte(msendpos.ub[1]);
//			
//				}
//			  
//					 
//		       msendpos.i=(long int)(( m_nDriveEStarPos+2*m_nDriveEStarSpeed/3600.0)*(256.0)/g_mGoto.m_nTescpEPosRatio);
//		       msendspd.i=(int)(m_nDriveETelSpeed/g_mGoto.m_nTescpESpeedRatio);
//		 	  
//		 
//		
//
//		    if(g_mTelescopeConType==1)
//			  {
//			    UART1_SentByte(0x55);
//				UART1_SentByte(0xAA);
//			    UART1_SentByte(0x01);
//				UART1_SentByte(0x06);
//				UART1_SentByte(34);
//				UART1_SentByte(msendspd.ub[1]);
//				UART1_SentByte(msendspd.ub[0]);
//				UART1_SentByte(msendpos.ub[3]);
//				UART1_SentByte(msendpos.ub[2]);
//				UART1_SentByte(msendpos.ub[1]);
//						   
//				
//			  }
//
//			  else
//			  {
//				UART1_SentByte(0x55);
//				UART1_SentByte(0xAA);
//			    UART1_SentByte(0x01);
//				UART1_SentByte(0x06);
//				UART1_SentByte(98);
//				UART1_SentByte(msendspd.ub[1]);
//				UART1_SentByte(msendspd.ub[0]);
//				UART1_SentByte(msendpos.ub[3]);
//				UART1_SentByte(msendpos.ub[2]);
//				UART1_SentByte(msendpos.ub[1]);
//			 					
//			 }
//		    
//		}	 

}

///*************************************************************************************
//��������: FindAlignStar
//��������: ����У׼�Ǳ��ҳ���ǰʱ�̿�����У׼����
//   ����˵����fstime : ��ǰ����ʱ
//			 flat��   ��ǰγ��
//			 fraddec��ָ�룬���ڴ洢������У׼�ǵĳྭ�ͳ�γ*fraddec=��һ���ǳྭ
//			           										*��fraddec+1��=��һ���ǳ�γ
//															*��fraddec+2��=�ڶ����ǳྭ
//															*��fraddec+3��=�ڶ����ǳ�γ
//															....
//   ����ֵ�����ص�ǰ������У׼�ǵĿ���
//*************************************************************************************/
//
// 																					   
//
//uint8 FindAlignStar(float fstime,float flat,float* fraddec,char Align_Star_Name[28][10],char Align_Star_NameCnn[28][22])		
//{
//
//  char Align_Star_NameEn[28][10]={{'S','i','r','i','u','s',' ',' ',' ',0},
//							 {'C','a','n','o','p','u','s',' ',' ',0},
//							 {'V','e','g','a',' ',' ',' ',' ',' ',0},	   
//							 {'A','l','p','h','a',' ','C','e','n',0},
//							 {'A','r','c','t','u','r','u','s',' ',0},
//							 {'C','a','p','e','l','l','a',' ',' ',0},
//							 {'R','i','g','e','l',' ',' ',' ',' ',0},
//							 {'P','r','o','c','y','o','n',' ',' ',0},
//							 {'A','c','h','e','r','n','a','r',' ',0}, 
//							 {'B','e','t','e','l','g','e','u','s',0},
//							 {'A','l','t','a','i','r',' ',' ',' ',0},
//							 {'A','l','d','e','b','a','r','a','n',0},
//							 {'S','p','i','c','a',' ',' ',' ',' ',0},
//							 {'A','n','t','a','r','e','s',' ',' ',0},
//							 {'F','o','m','a','l','h','a','u','t',0},
//							 {'D','e','n','e','b',' ',' ',' ',' ',0},
//							 {'R','e','g','u','l','u','s',' ',' ',0},
//							 {'M','i','r','f','a','k',' ',' ',' ',0},
//							 {'C','a','s','t','o','r',' ',' ',' ',0},
//							 {'A','l','p','h','a','r','d',' ',' ',0},
//							 {'P','o','l','a','r','i','s',' ',' ',0},
//							 {'A','l','p','h','e','r','a','t','z',0},
//  						     {'R','a','s','a','l','h','a','g','u',0},
//							 {'D','e','n','e','b','o','l','a',' ',0},
//							 {'N','a','v','i',' ',' ',' ',' ',' ',0},
//							 {'S','u','h','a','i','l',' ',' ',' ',0},
//							 {'M','i','z','a','r',' ',' ',' ',' ',0},
//							 {'A','l','b','i','r','e','o',' ',' ',0}};
//
//   char  Align_Star_NameCn[28][22]={{0x29,0x59,0xFC,0x72,0x20,0x00,0x27,0x59,0xAC,0x72,0xA7,0x5E,0xB1,0x03,0x20,0x00,0x20,0x00,0x20,0x00,0x00,0x00},
//								 {0x01,0x80,0xBA,0x4E,0x1F,0x66,0x20,0x00,0x39,0x82,0x95,0x5E,0xA7,0x5E,0xA7,0x5E,0xB1,0x03,0x20,0x00,0x00,0x00},
//								 {0xC7,0x7E,0x73,0x59,0x00,0x4E,0x20,0x00,0x20,0x00,0x29,0x59,0x34,0x74,0xA7,0x5E,0xB1,0x03,0x20,0x00,0x00,0x00},	   
//								 {0x4A,0x53,0xBA,0x4E,0x6C,0x9A,0xA7,0x5E,0xA7,0x5E,0xB1,0x03,0x20,0x00,0x20,0x00,0x20,0x00,0x20,0x00,0x00,0x00},
//							     {0x27,0x59,0xD2,0x89,0x20,0x00,0x67,0x72,0x2B,0x59,0xA7,0x5E,0xB1,0x03,0x20,0x00,0x20,0x00,0x20,0x00,0x00,0x00},
//							  	 {0x94,0x4E,0x66,0x8F,0x8C,0x4E,0x20,0x00,0xA1,0x5F,0x2B,0x59,0xA7,0x5E,0xB1,0x03,0x20,0x00,0x20,0x00,0x00,0x00},
//								 {0xC2,0x53,0xBF,0x5B,0x03,0x4E,0x20,0x00,0x0E,0x73,0x37,0x62,0xA7,0x5E,0xB2,0x03,0x20,0x00,0x20,0x00,0x00,0x00},
//								 {0x57,0x53,0xB3,0x6C,0x09,0x4E,0x20,0x00,0x0F,0x5C,0xAC,0x72,0xA7,0x5E,0xB1,0x03,0x20,0x00,0x20,0x00,0x00,0x00},
//								 {0x34,0x6C,0xD4,0x59,0x00,0x4E,0x20,0x00,0xE2,0x6C,0x5F,0x6C,0xA7,0x5E,0xA7,0x5E,0xB1,0x03,0x20,0x00,0x00,0x00}, 
//								 {0xC2,0x53,0xBF,0x5B,0xDB,0x56,0x20,0x00,0x0E,0x73,0x37,0x62,0xA7,0x5E,0xB1,0x03,0x20,0x00,0x20,0x00,0x00,0x00},
//								 {0xB3,0x6C,0x13,0x9F,0x8C,0x4E,0x20,0x00,0x29,0x59,0x70,0x9E,0xA7,0x5E,0xB1,0x03,0x20,0x00,0x20,0x00,0x00,0x00},
//								 {0xD5,0x6B,0xBF,0x5B,0x94,0x4E,0x20,0x00,0xD1,0x91,0x5B,0x72,0xA7,0x5E,0xB1,0x03,0x20,0x00,0x20,0x00,0x00,0x00},
//								 {0xD2,0x89,0xBF,0x5B,0x00,0x4E,0x20,0x00,0xA4,0x5B,0x73,0x59,0xA7,0x5E,0xB1,0x03,0x20,0x00,0x20,0x00,0x00,0x00},
//								 {0xC3,0x5F,0x27,0x59,0x1F,0x66,0x20,0x00,0x29,0x59,0x4E,0x87,0xA7,0x5E,0xB1,0x03,0x20,0x00,0x20,0x00,0x00,0x00},
//								 {0x17,0x53,0x3D,0x84,0x08,0x5E,0xE8,0x95,0x20,0x00,0x20,0x00,0x57,0x53,0x7C,0x9C,0xA7,0x5E,0xB1,0x03,0x00,0x00},
//								 {0x29,0x59,0x25,0x6D,0xDB,0x56,0x20,0x00,0x29,0x59,0x45,0x9E,0xA7,0x5E,0xB1,0x03,0x20,0x00,0x20,0x00,0x00,0x00},
//								 {0x69,0x8F,0x95,0x8F,0x41,0x53,0xDB,0x56,0xEE,0x72,0x50,0x5B,0xA7,0x5E,0xB1,0x03,0x20,0x00,0x20,0x00,0x00,0x00},
//								 {0x29,0x59,0x39,0x82,0x09,0x4E,0x20,0x00,0xF1,0x82,0xD9,0x4E,0xA7,0x5E,0xB1,0x03,0x20,0x00,0x20,0x00,0x00,0x00},
//								 {0x17,0x53,0xB3,0x6C,0x8C,0x4E,0x20,0x00,0xCC,0x53,0x50,0x5B,0xA7,0x5E,0xB1,0x03,0x20,0x00,0x20,0x00,0x00,0x00},
//								 {0x1F,0x66,0xBF,0x5B,0x00,0x4E,0x20,0x00,0x7F,0x95,0xC7,0x86,0xA7,0x5E,0xB1,0x03,0x20,0x00,0x20,0x00,0x00,0x00},
//								 {0x0F,0x5C,0x8A,0x71,0xA7,0x5E,0xA7,0x5E,0xB1,0x03,0x20,0x00,0x20,0x00,0x20,0x00,0x20,0x00,0x20,0x00,0x00,0x00},
//								 {0xC1,0x58,0xBF,0x5B,0x8C,0x4E,0x20,0x00,0xD9,0x4E,0x73,0x59,0xA7,0x5E,0xB1,0x03,0x20,0x00,0x20,0x00,0x00,0x00},
//	  						     {0xAF,0x4F,0x20,0x00,0xC7,0x86,0x2B,0x59,0xA7,0x5E,0xB1,0x03,0x20,0x00,0x20,0x00,0x20,0x00,0x20,0x00,0x00,0x00},
//								 {0x94,0x4E,0x1D,0x5E,0xA7,0x5E,0x00,0x4E,0xEE,0x72,0x50,0x5B,0xA7,0x5E,0xB2,0x03,0x20,0x00,0x20,0x00,0x00,0x00},
//								 {0xD9,0x4E,0x0E,0x54,0xA7,0x5E,0xB3,0x03,0x20,0x00,0x20,0x00,0x20,0x00,0x20,0x00,0x20,0x00,0x20,0x00,0x00,0x00},
//								 {0x01,0x80,0xBA,0x4E,0x1F,0x66,0x20,0x00,0x39,0x82,0x06,0x5E,0xA7,0x5E,0xBB,0x03,0x20,0x00,0x20,0x00,0x00,0x00},
//								 {0x00,0x5F,0x33,0x96,0x20,0x00,0x27,0x59,0x8A,0x71,0XA7,0X5E,0xB6,0x03,0x20,0x00,0x20,0x00,0x20,0x00,0x00,0x00},
//								 {0x87,0x8F,0x53,0x90,0x9E,0x58,0x03,0x4E,0x29,0x59,0x45,0x9E,0xA7,0x5E,0xB2,0x03,0x20,0x00,0x20,0x00,0x00,0x00}};
//	float Star_arr_ra[28];
//	float Star_arr_dec[28]; 
//	
//	char   arra[28];
//	int 	i;
//	uint8 	j;
//	uint8   k;
//	uint8   n;
//	float lat_low;
//	float lat_high;
//	float lon_low;
//	float lon_high;
//	LOCATION  m_nLocation;
//	STARRAD   m_nStarRAD;
//	STARAZ    m_nStarAZ;
//
// 	Star_arr_ra[0]=6.7585;
//	Star_arr_dec[0]=-16.72630555;
//	Star_arr_ra[1]=6.40180278;
//	Star_arr_dec[1]=-52.6982499;
//	Star_arr_ra[2]=18.620930;
//	Star_arr_dec[2]=38.790943;
//	Star_arr_ra[3]=14.670347;
//	Star_arr_dec[3]=-60.875278;
//	Star_arr_ra[4]=14.267856;
//	Star_arr_dec[4]=19.138472;
//	Star_arr_ra[5]=5.288405;
//	Star_arr_dec[5]=46.006638;
//	Star_arr_ra[6]=5.248961;
//	Star_arr_dec[6]=-8.189528;
//	Star_arr_ra[7]=7.662292;
//	Star_arr_dec[7]=5.204333;
//	Star_arr_ra[8]=1.633978;
//	Star_arr_dec[8]=-57.187054;
//	Star_arr_ra[9]=5.093711;
//	Star_arr_dec[9]=7.410167;
//	Star_arr_ra[10]=19.853836;
//	Star_arr_dec[10]=8.890472;
//	Star_arr_ra[11]=4.606700;
//	Star_arr_dec[11]=16.527527;
//	Star_arr_ra[12]=13.427614;
//	Star_arr_dec[12]=-11.207945;
//	Star_arr_ra[13]=16.499397;
//	Star_arr_dec[13]=-26.453333;
//	Star_arr_ra[14]=22.969114;
//	Star_arr_dec[14]=-29.573389;
//	Star_arr_ra[15]=20.695877;
//	Star_arr_dec[15]=45.308834;
//	Star_arr_ra[16]=10.147056;
//	Star_arr_dec[16]=11.926416;	
//	Star_arr_ra[17]=3.415389;
//	Star_arr_dec[17]=49.890057;
//	Star_arr_ra[18]=7.585497;
//	Star_arr_dec[18]=31.871056;
//	Star_arr_ra[19]=9.466641;
//	Star_arr_dec[19]=-8.695806;
//	Star_arr_ra[20]=2.679011;
//	Star_arr_dec[20]=89.298111;
//	Star_arr_ra[21]=0.147342;
//	Star_arr_dec[21]=29.136417;
//	Star_arr_ra[22]=17.589369;
//	Star_arr_dec[22]=12.553306;
//	Star_arr_ra[23]=11.825017;
//	Star_arr_dec[23]=14.525111;
//	Star_arr_ra[24]=0.953800;
//	Star_arr_dec[24]=60.759693;
//	Star_arr_ra[25]=9.138127;
//	Star_arr_dec[25]=-43.468777;
//	Star_arr_ra[26]=13.404866;
//	Star_arr_dec[26]=54.884029;
//	Star_arr_ra[27]=19.518867;
//	Star_arr_dec[27]=27.982250;
//
//	if(fstime>=4||fstime<=20)
//	{
//		lon_low=fstime-4;
//		lon_high=fstime+4;
//	}
//	else if(fstime<4)
//	{
//		lon_low=fstime+24-4;
//		lon_high=fstime+4;
//	}
//	else
//	{
//		lon_low=fstime-4;
//		lon_high=fstime-24+4;
//	}
//	if(flat>=0)
//	{
//		lat_low=flat-60;
//		lat_high=flat+60;
//		if(lat_high>90)
//		lat_high=90;
//	}
//	else
//	{
//		lat_low=flat-60;
//		lat_high=flat+60;
//		if(lat_low<(-90))
//		lat_low=(-90);
//	}
//	for(i=0,j=0;i<28;i++)
//	{
//		if((fstime>=4)||(fstime<=20))
//		{
//			if((Star_arr_ra[i]>=lon_low)&&(Star_arr_ra[i]<=lon_high))
//			{
//				if((Star_arr_dec[i]>=lat_low)&&(Star_arr_dec[i]<=lat_high))
//				{
//					arra[j]=i;
//					j++;
//				}
//			}
//		}
//		else if((fstime<=4)||(fstime>=20))
//		{
//			if(((Star_arr_ra[i]>=lon_low)&&(Star_arr_ra[i]<=24))||((Star_arr_ra[i]>=0)&&(Star_arr_ra[i]<=lon_high)))
//			{
//				if((Star_arr_dec[i]>=lat_low)&&(Star_arr_dec[i]<=lat_high))
//				{
//					arra[j]=i;
//					j++;
//				}
//			}
//		}
//	}
//	if(j>0)
//	{
//		for(i=0;i<=(j-1);i++)
//		{
//			*(fraddec+2*i)=Star_arr_ra[arra[i]];
//			*(fraddec+2*i+1)=Star_arr_dec[arra[i]];
//			for(k=0;k<10;k++) 					
//			  Align_Star_Name[i][k]=Align_Star_NameEn[arra[i]][k];
//	    	for(n=0;n<22;n++)  
//			  Align_Star_NameCnn[i][n]=Align_Star_NameCn[arra[i]][n];
//			
//			
//			
//		}
//	}
//	return (j-1);
//
//
//}

