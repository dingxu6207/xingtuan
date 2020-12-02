//*******************************************************
//*******************************************
//**********��Զ��������*********************
//**********ŷ��������԰�*******************
//**********���ߣ�����Ǭ           **********
//**********2008������������̨     **********
//**********lgq@ynao.ac.cn         **********
//*******************************************
//*******************************************
//*******************************************************


//*******************************************************
#include <LPC214X.H>   //ϵͳ�ļ�
#include "IOConfig.H"  //ϵͳ�ļ�
#include "config.h"	   //ϵͳ�ļ�
#include "LCD12864.c"  //ϵͳ�ļ�
#include "Disp.c"	   //��ʾ�ļ�
#include "Keys.c"	   //��������ļ�
#include "Interrupt.c" //�жϴ����ļ�
#include "UTR0.c"	   //�����㴦���ļ�
#include "Timers.c"	   //ʱ���ļ�
#include "PowerUp.c"   //ϵͳ��Դ���ļ�
#include "ROM.c"		//���ݴ洢оƬ��д�ļ�
#include "starstructure.c" //�Ǳ����ݻ����ļ�
#include "FAS.c"		//У׼���ļ�
#include "Menu.c"		//ϵͳ�˵��ļ�
#include "ASCOM.c"		//ϵͳSKYMAPͨ���ļ�
//*******************************************************
//��������
 char s1[20];
 char s2[20];
 char s3[20];
 char s4[20];
 char s5[20];
 char s6[20];
 char s7[20];
 char s8[20];

 uint8 data[100];
 double ra;
 double dec; 
 float  lon0,lat0;
 int zone; 
 int d1,f1,m1,d2,f2,m2;

 uint8 dd;
 uint32 tt;

 //uint8 g_mSendToSkymap;//������SKYMAP������Զ��λ�õ�ʱ�� 


 uint8 site[8];
 uint8 Lon[6];
 uint8 Lat[5];
 uint8 Zone[3]; 
 uint8 i;
//*******************************************************
//*******************************************************
//ϵͳ������ʼ
int main(void)
 {
  	 //ϵͳ�ϵ��ʼ��
	 PowerOnInit();
	//***********************************			   
	//�������ʼ��
	 Init_Uart0(UART_BAUD(9600));//�������λ����PC�����ճ���
	 //***********************************
	//����һ��ʼ��
	 Init_Uart1(UART_BAUD(9600)); //�������λ�������������
	 //***********************************
    //��λ�������ϵ�򿪣�����������ֹͣ����ֹ�ֶ�
     FHandPowerTelescope();
	 //***********************************	
	//��λ���ٲ�����ʼ��
	 FSetupPointTrackPara();	
	//***********************************
	//ϵͳ������ʼ��
     FInitPara(); 
	//***********************************
//	//���ñ�����Ϊ��
//	 UART1_SentByte(0x55);
//	 UART1_SentByte(0xAA);
//	 UART1_SentByte(0x01);
//	 UART1_SentByte(3);	
//	 UART1_SentByte(21);
//	 UART1_SentByte(0);
//	 UART1_SentByte(0);
//	 UART1_SentByte(0);
//	 
//	 UART1_SentByte(0x55);
//	 UART1_SentByte(0xAA);
//	 UART1_SentByte(0x01);
//	 UART1_SentByte(3);
//	 UART1_SentByte(53); 
//	 UART1_SentByte(0);
//	 UART1_SentByte(0);
//	 UART1_SentByte(0);	  
//
//	 UART1_SentByte(0x55);
//	 UART1_SentByte(0xAA);
//	 UART1_SentByte(0x01);
//	 UART1_SentByte(3);
//     UART1_SentByte(85);
//	 UART1_SentByte(0);
//	 UART1_SentByte(0);
//	 UART1_SentByte(0);
//
//	 UART1_SentByte(0x55);
//	 UART1_SentByte(0xAA);
//	 UART1_SentByte(0x01);
//	 UART1_SentByte(3);
//	 UART1_SentByte(117);
//	 UART1_SentByte(0);
//	 UART1_SentByte(0);
//	 UART1_SentByte(0);
//	 MenuDelay(100);	//��ʱ
	 //**********************************
	 //��ȡϵͳ����
     ReadFromRom(3531,0,10,data);
	 g_mMenuLangauge=data[0];//ϵͳ�ϴ����õĲ˵����� 
	 if(data[1]==1)	         //���ֿذ��ǲ��ǵ�һ���� 
	 {
	    FSetSysTime();
	    data[1]=0;
	    WriteToRom(3531,0,2,data);
	  }
	//***********************************
//	//ϵͳ����������ʾ
//	   	DispEn(0,3,1,22,"     StarTracker      ");
//		DispEn(0,5,1,22,"   Ver. 0.99 EQ/AZ    ");
//		DispEn(0,7,1,22," (c)2012  MAXVISION   ");
        FShowStart();
	//***********************************
	//*********************************************************
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
	 //***********************************
	 MenuDelay(10);	//��ʱ

	 //***********************************
	 //������Զ��װ�õ�ϵͳ��־
	if(g_mTelescopeConType==1)
	{
       g_mAzEq=1; //���ʽ
	}
	else
	{
       g_mAzEq=0;  //��ƽʽ
	 }
    //***********************************
	//ϵͳ������ʼ��
	  
    g_mEQHn=false;//���ʽ��Զ��Ŀ���Ƿ��ڵ�ƽ��
    g_mTelRABack=0.050;  //�ྭ�ز�	
    g_mTelDecBack=0.045;  //��γ�ز�

	g_mGoto.m_nTescpAPZero=100;
	g_mGoto.m_nTescpEPZero=60;

	GetTelZero(&azi_zero,&alt_zero); //��ȡ��Զ�����

	g_mGoto.m_nTescpAPZero=azi_zero; //��Զ����λ��� ,��λ�Ա���ʼ�㣬��Ϊ��
	g_mGoto.m_nTescpEPZero=alt_zero;//��Զ���߶����  ���߶��Ե�ƽ�㣬����Ϊ��

	g_mGoto.m_nStarAPos0=-180;
	g_mGoto.m_nStarEPos0=90;

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
	     sprintf(g_sysmenu4300sitelonEn,"  Lon:E%03dd%02df ",abs((int)lon0),abs((int)((lon0-(int)lon0)*60)));
		 }
		 else
		 {
		    sprintf(g_sysmenu4300sitelonEn,"  Lon:W%03dd%02df ",abs((int)lon0),abs((int)((lon0-(int)lon0)*60)));
		 }
	  
	   if(lat0>0)
	   {
	       sprintf(g_sysmenu4300sitelatEn,"  Lat:N%02dd%02df ",abs((int)lat0),abs((int)((lat0-(int)lat0)*60)));
		 }
		 else
		 {
		   sprintf(g_sysmenu4300sitelatEn,"  Lat:S%02dd%02df ",abs((int)lat0),abs((int)((lat0-(int)lat0)*60)));
		 }

		 if(zone>0)
		 {
		     sprintf(g_sysmenu4300sitezoneEn," Zone:E%02d",abs(zone));
		 }
		 else
		 {
		   sprintf(g_sysmenu4300sitezoneEn," Zone:W%02d",abs(zone));
		 }
  //***********************************
//  //GetPlanetPos();//��������λ�� 
   MenuDelay(2000);
   LCDRfrsh();
  //***********************************
  //ϵͳ��ʼ����
   if(g_mSysInitGuide==1)
	{
	    GetSysTime();
	    if(g_mDate_year<2000)
		{
		  g_mDate_year=2000;
 		  g_mDate_month=1;
		  g_mDate_day=1;
		  g_mTime_hour=0;
		  g_mTime_minute=0;
		  g_mTime_second=0;
		 }

	   	sprintf(g_sysmenu4100dateEn,"%04d-%02d-%02d",g_mDate_year,g_mDate_month,g_mDate_day);
      	sprintf(g_sysmenu4100timeEn,"%02d:%02d:%02d",g_mTime_hour,g_mTime_minute,g_mTime_second);
      	sprintf(g_sysmenu4100date,"%04d-%02d-%02d",g_mDate_year,g_mDate_month,g_mDate_day);
      	sprintf(g_sysmenu4100time,"%02d:%02d:%02d",g_mTime_hour,g_mTime_minute,g_mTime_second);
      	
		g_mShowMenucolumn=1;
	  	g_mdatetime=0;
	    g_nsysstatus=SYS_SUB4SUB1_SETTIME;
	 }
	 else
	 {
       g_nsysstatus=SYS_MAINSHOW;
	 }

 //***********************************
 //***********************************
///**************************************************
//����ϵͳ����ģʽ
while(1)
{  	
          //***********************************
		//������Զ����ǰλ��
		g_mCurrentTelAzi=g_mTelAzi;	
		g_mCurrentTelAlt=g_mTelAlt;  //��ǰ��Զ��λ��  
		 
		m_GuiderRa=0;	  //Ϊ1����-1����Ϊ0�������ྭ��絼���ź�
	  m_GuiderDec=0; //Ϊ1����-1����Ϊ0����	 ����γ��絼����
		    
	    //***************************************************************
	   //*****************************************************************
		///////////////////////////////////////////////////////////////////
		//ASCOMͨ�Ŵ�����

		Skymap();

		///////////////////////////////////////////////////////////////////
	   	//*****************************************************************		
		//***************************************************************
		///��Զ��λ�õĻ�ȡ							
	    if(g_mTelescopeConType==1) //���ʽ��Զ��
		 {
			g_mAzEq=1;//����ģʽ�����ʽ��Զ����Զ���ʽ���٣�����ƽʽ��Զ�������ǵ�ƽʽ���٣�Ҳ�����ǳ��ʽ����

			//g_mObjHourA=g_mGoto.m_nStarAPosTshow-8.3333333333e-4;//g_mGoto.m_nHourAngle;
			g_mObjHourA=g_mGoto.m_nRightAscension;//g_mGoto.m_nRightAscension;

			g_mObjHourA_shi=(int)g_mObjHourA;//��ƽ���귽λ���ظ�ֵ�ڷ�λ��ʾ
			g_mObjHourA_fen=(int)((g_mObjHourA-g_mObjHourA_shi)*60.0);
			g_mObjHourA_miao=(g_mObjHourA-g_mObjHourA_shi-g_mObjHourA_fen/60.0)*3600;


			g_mObjDec1=fabs(g_mGoto.m_nStarEPosTshow);//g_mGoto.m_nDeclination);
										
			g_mObjDec_du1=(int)g_mObjDec1;//��ƽ����߶ȷ��ظ�ֵ�ڷ�λ��ʾ
			g_mObjDec_fen1=(int)((g_mObjDec1-g_mObjDec_du1)*60.0);
			g_mObjDec_miao1=(g_mObjDec1-g_mObjDec_du1-g_mObjDec_fen1/60.0)*3600;
            if(g_mGoto.m_nDeclination>=0)
			{
			  g_gObjDec_sign1=1;
			}
			else
			{
			  g_gObjDec_sign1=-1;
			}

	

			FGetTelescopePos(AXIS_RA);
		    g_mGoto.m_nTescpAPos=g_mTelRaUtr1;
			g_mTelRANextPos=g_mTelRaUtr1;

			g_mTelAzi=g_mGoto.m_nTescpAPos;
          	g_mTelRa=g_mTelRaUtr1;

			


			MenuDelay(5);
			FGetTelescopePos(AXIS_DEC);
			g_mGoto.m_nTescpEPos=g_mTelDecUtr1;
			g_mTelDecNextPos=g_mTelDecUtr1;
	    	g_mTelAlt=fabs(g_mGoto.m_nTescpEPos);	
				
			
			g_mTelDec=g_mTelAlt;

		

			 g_mTelDec=fabs(g_mTelDec);
			 while(g_mTelDec>360)
		 	 {			   
			    g_mTelDec=g_mTelDec-360;
			 }
									 	
	            if(g_mGoto.m_nAtitude>=0) //������
			    {	
				 

						//***************
                        if(g_mTelDec>180)
						 {
						    g_mTelDec=g_mTelDec-270;
						  }
						  else
						  {
						    g_mTelDec=90-g_mTelDec;
						  }
						   g_mTelRa=g_mTelRa+90;
						   if(g_mTelDecUtr1>0)
						  {
							 if(g_mTelDecUtr1<180)
							 {
							   g_mTelRa=g_mTelRa+180;
							  }
				           
						  }
						 if(g_mTelDecUtr1<0)
						  {
							 if(g_mTelDecUtr1<-180)
							 {
							   g_mTelRa=g_mTelRa+90;
							  }
				           
						  }
						 while(g_mTelRa>=360)
						 {
						   g_mTelRa=g_mTelRa-360;
						 }
						 while(g_mTelRa<0)
						 {
						   g_mTelRa=g_mTelRa+360;
						 }		 

					 //***************						
				
				}
			 else   //�ϰ���
			   {	

					    //***************
                        if(g_mTelDec>180)
						 {
						    g_mTelDec=270-g_mTelDec;
						  }
						  else
						  {
						    g_mTelDec=g_mTelDec-90;
						  }


						  g_mTelRa=270-g_mTelRa;
						  if(g_mTelDecUtr1>0)
						  {
							 if(g_mTelDecUtr1<180)
							 {
							   g_mTelRa=g_mTelRa-180;
							  }
				           
						  }

						   if(g_mTelDecUtr1<0)
						  {
							 if(g_mTelDecUtr1<-180)
							 {
							   g_mTelRa=g_mTelRa-180;
							  }
				           
						  }
						while(g_mTelRa>=360)
						 {
						   g_mTelRa=g_mTelRa-360;
						 }
						 while(g_mTelRa<0)
						 {
						   g_mTelRa=g_mTelRa+360;
						 }		 
						 //***************	
								
		    	} 

//			g_mTelRa=g_mTelRa/15.0-syn_mApos/15.0;
//			//CurrentRa=g_mTelRa-dg_mSkyMapAzi/15.0;	 //������Զ��λ�ø�SKYMAP
//			CurrentRa=g_mSidTime-(g_mTelRa-dg_mSkyMapAzi/15.0);//������Զ��λ�ø�SKYMAP
//			if(CurrentRa<0)
//			{
//			 CurrentRa=CurrentRa+24;
//			}
//			if(CurrentRa>24)
//			{
//			 CurrentRa=CurrentRa-24;
//			}
//
//			g_mTelRa_shi=(int)g_mTelRa;//��ƽ���귽λ���ظ�ֵ�ڷ�λ��ʾ
//			g_mTelRa_fen=(int)((g_mTelRa-g_mTelRa_shi)*60.0);
//			g_mTelRa_miao=(g_mTelRa-g_mTelRa_shi-g_mTelRa_fen/60.0)*3600;
//			if((g_mhandtrackAzi==1)&&(g_mGoto.m_nTAState==2))//���ָ��ʱ����Զ����Ŀ��λ��һ�£��ֶ����ں󣬾Ͳ�һ����	{
//			{
//			  g_mTelRa_shi=g_mObjRa_shi;
//			  g_mTelRa_fen=g_mObjRa_fen;
//			  g_mTelRa_miao=g_mObjRa_miao;
//
//			}
//
//			g_mTelDec=g_mTelDec-syn_mZpos;			
//			CurrentDec=g_mTelDec-dg_mSkyMapAlt;//������Զ��λ�ø�SKYMAP
//
//			g_mTelDec_du=(int)g_mTelDec;//��ƽ����߶ȷ��ظ�ֵ�ڷ�λ��ʾ
//			g_mTelDec_fen=(int)((g_mTelDec-g_mTelDec_du)*60.0);
//			g_mTelDec_miao=(g_mTelDec-g_mTelDec_du-g_mTelDec_fen/60.0)*3600;
//			if((g_mhandtrackAlt==1)&&(g_mGoto.m_nTEState==2))//���ָ��ʱ����Զ����Ŀ��λ��һ�£��ֶ����ں󣬾Ͳ�һ����	{
//			{
//			  g_mTelDec_du=g_mObjDec_du;
//			  g_mTelDec_fen=g_mObjDec_fen;
//			  g_mTelDec_miao=g_mObjDec_miao;
//
//			}
					g_mTelRa=g_mTelRa/15.0;//-syn_mApos/15.0;
					CurrentRa=g_mSidTime-(g_mTelRa-syn_mApos/15.0-dg_mSkyMapAzi/15.0);//������Զ��λ�ø�SKYMAP
					if(CurrentRa<0)
					{
					 CurrentRa=CurrentRa+24;
					}
					if(CurrentRa>24)
					{
					 CurrentRa=CurrentRa-24;
					}

					g_mTelRa_shi=(int)(g_mTelRa-syn_mApos/15.0+dg_mApos0);//��ƽ���귽λ���ظ�ֵ�ڷ�λ��ʾ
					g_mTelRa_fen=(int)((g_mTelRa-syn_mApos/15.0+dg_mApos0-g_mTelRa_shi)*60.0);
					g_mTelRa_miao=(g_mTelRa-syn_mApos/15.0+dg_mApos0-g_mTelRa_shi-g_mTelRa_fen/60.0)*3600;
		         if((g_mhandtrackAzi==1)&&(g_mGoto.m_nTAState==2))//���ָ��ʱ����Զ����Ŀ��λ��һ�£��ֶ����ں󣬾Ͳ�һ����	{
					{
					  dg_mApos0=g_mObjHourA-g_mTelRa;

					  g_mTelRa_shi=g_mObjHourA_shi;
					  g_mTelRa_fen=g_mObjHourA_fen;
					  g_mTelRa_miao=g_mObjHourA_miao;
		
					}
		
					//g_mTelDec=g_mTelDec-syn_mZpos;					
					CurrentDec=g_mTelDec-syn_mZpos-dg_mSkyMapAlt;//������Զ��λ�ø�SKYMAP


				    g_mTelDec_du=(int)(g_mTelDec-syn_mZpos+dg_mZpos0);//��ƽ����߶ȷ��ظ�ֵ�ڷ�λ��ʾ
					g_mTelDec_fen=(int)((g_mTelDec-syn_mZpos+dg_mZpos0-g_mTelDec_du)*60.0);
					g_mTelDec_miao=(g_mTelDec-syn_mZpos+dg_mZpos0-g_mTelDec_du-g_mTelDec_fen/60.0)*3600;
			   if((g_mhandtrackAlt==1)&&(g_mGoto.m_nTEState==2))//���ָ��ʱ����Զ����Ŀ��λ��һ�£��ֶ����ں󣬾Ͳ�һ����	{
				{
				  dg_mZpos0=g_mObjDec1-g_mTelDec;

				  g_mTelDec_du=g_mObjDec_du1;
				  g_mTelDec_fen=g_mObjDec_fen1;
				  g_mTelDec_miao=g_mObjDec_miao1;
	
				}
			

		 }
		 else if(g_mTelescopeConType==2)  //��ƽʽ��Զ��
		 {	  
            if(g_mAzEq==0)
			{			    
					//g_mObjAzi=g_mGoto.m_nStarAPosT;//��ʼ����
				    //g_mObjAzi=g_mGoto.m_nStarAPosT+180;//��ʼ������
					//g_mObjAzi=g_mGoto.m_nStarAPos0+180;//��ʼ������ֵ����ʾ�ǵ���ԭʼ���꣬�����Ǿ�װ�ø����������

					g_mObjAzi=g_mGoto.m_nStarAPosTshow+180;
		
			 	    g_mObjAzi_du=(int)g_mObjAzi;//��ƽ���귽λ���ظ�ֵ�ڷ�λ��ʾ
				    g_mObjAzi_fen=(int)((g_mObjAzi-g_mObjAzi_du)*60.0);
				    g_mObjAzi_miao=(g_mObjAzi-g_mObjAzi_du-g_mObjAzi_fen/60.0)*3600;
		
				    //g_mObjAlt=g_mGoto.m_nStarEPosT;	//��ʼ�����ƺ
					//g_mObjAlt=90-g_mGoto.m_nStarEPosT; //��ʼ�����춥
					//g_mObjAlt=90-g_mGoto.m_nStarEPos0;//��ʼ������ֵ����ʾ�ǵ���ԭʼ���꣬�����Ǿ�װ�ø����������

					 g_mObjAlt=90-g_mGoto.m_nStarEPosTshow;

			    	g_mObjAlt_du=(int)g_mObjAlt;//��ƽ����߶ȷ��ظ�ֵ�ڸ߶���ʾ
				    g_mObjAlt_fen=(int)((g_mObjAlt-g_mObjAlt_du)*60.0);
				    g_mObjAlt_miao=(g_mObjAlt-g_mObjAlt_du-g_mObjAlt_fen/60.0)*3600;
		
				    FGetTelescopePos(AXIS_AZI);
			    	g_mGoto.m_nTescpAPos=g_mTelAziUtr1;
					g_mTelAzi=g_mGoto.m_nTescpAPos;	

					//g_mTelAzi=g_mTelAzi;//��ʼ����
					//g_mTelAzi=g_mTelAzi+180;//��ʼ������
					if(g_mstartOTAset==0)//����ʱ������Զ���ĳ�ʼָ��
					{
					     g_mTelAzi=g_mGoto.m_nTescpAPZero;//��ʼ��Ϊ����λ��
					 }
					 else
					 {
					    g_mTelAzi=g_mTelAzi+g_mGoto.m_nTescpAPZero;//��ʼ��Ϊ����λ��
					 }

					while(g_mTelAzi>=360)
					{
					    g_mTelAzi=g_mTelAzi-360;
					 }
					while(g_mTelAzi<0)
					{
					    g_mTelAzi=g_mTelAzi+360;
					 } 		
					 
					CurrentRa=g_mTelAzi-dg_mApos_syn-dg_mSkyMapAzi; //������Զ��λ�ø�SKYMAP
					g_mTelAzi_du=(int)(g_mTelAzi-dg_mApos_syn+dg_mApos0);//��ƽ���귽λ���ظ�ֵ�ڸ���ʾ
					g_mTelAzi_fen=(int)((g_mTelAzi-dg_mApos_syn+dg_mApos0-g_mTelAzi_du)*60.0);
					g_mTelAzi_miao=(int)((g_mTelAzi-dg_mApos_syn+dg_mApos0-g_mTelAzi_du-g_mTelAzi_fen/60.0)*3600.0);
					
					if((g_mhandtrackAzi==1)&&(g_mGoto.m_nTAState==2))//���ָ��ʱ����Զ����Ŀ��λ��һ�£��ֶ����ں󣬾Ͳ�һ����	{
					{
					    dg_mApos0=g_mObjAzi-g_mTelAzi;

					  g_mTelAzi_du=g_mObjAzi_du;
					  g_mTelAzi_fen=g_mObjAzi_fen;
					  g_mTelAzi_miao=g_mObjAzi_miao;

					}
		
					MenuDelay(2);
					FGetTelescopePos(AXIS_ALT);
					g_mGoto.m_nTescpEPos=g_mTelAltUtr1;
					g_mTelAlt=g_mGoto.m_nTescpEPos;

		    		//g_mTelAlt=g_mTelAlt; //��ʼ�����ƺ
					//g_mTelAlt=90-g_mTelAlt;//��ʼ�����춥
					if(g_mstartOTAset==0)//����ʱ������Զ���ĳ�ʼָ��
					{
					  g_mTelAlt=g_mGoto.m_nTescpEPZero;//��ʼ��Ϊ����λ��
					 }
					 else
					 {
//					   if((g_mGoto.m_nTescpEPZero-g_mTelAlt)>90)
//					   {
//					      g_mTelAlt=g_mGoto.m_nTescpEPZero-g_mTelAlt;//��ʼ��Ϊ����λ��
//						  g_mTelAlt=180-g_mTelAlt;
//						}
//						else
//						{
						   g_mTelAlt=g_mGoto.m_nTescpEPZero-g_mTelAlt;//��ʼ��Ϊ����λ��
//						 }
					 
					 }
					 if(g_mTelAlt>90)
					 {
					   g_mTelAlt=180-g_mTelAlt;
					 }
						
				
					CurrentDec=g_mTelAlt-dg_mZpos_syn-dg_mSkyMapAlt;//������Զ��λ�ø�SKYMAP	
					g_mTelAlt_du=(int)(g_mTelAlt-dg_mZpos_syn+dg_mZpos0);//��ƽ����߶ȷ��ظ�ֵ����ʾ
					g_mTelAlt_fen=(int)((g_mTelAlt-dg_mZpos_syn+dg_mZpos0-g_mTelAlt_du)*60.0);
					g_mTelAlt_miao=(int)((g_mTelAlt-dg_mZpos_syn+dg_mZpos0-g_mTelAlt_du-g_mTelAlt_fen/60.0)*3600.0);
				    
					if((g_mhandtrackAlt==1)&&(g_mGoto.m_nTEState==2))//���ָ��ʱ����Զ����Ŀ��λ��һ�£��ֶ����ں󣬾Ͳ�һ����
					{

					  dg_mZpos0=g_mObjAlt-g_mTelAlt;


					  g_mTelAlt_du=g_mObjAlt_du;
					  g_mTelAlt_fen=g_mObjAlt_fen;
					  g_mTelAlt_miao=g_mObjAlt_miao;

					 
					}
		
			}
			else //��ƽʽ��Զ��	���ʽ�÷�
			{
				   	g_mObjHourA=g_mGoto.m_nHourAngle;
					g_mObjHourA_shi=(int)g_mObjHourA;//��ƽ���귽λ���ظ�ֵ�ڷ�λ��ʾ
					g_mObjHourA_fen=(int)((g_mObjHourA-g_mObjHourA_shi)*60.0);
					g_mObjHourA_miao=(g_mObjHourA-g_mObjHourA_shi-g_mObjHourA_fen/60.0)*3600;
		
		
					g_mObjDec1=fabs(g_mGoto.m_nDeclination);							
					g_mObjDec_du1=(int)g_mObjDec1;//��ƽ����߶ȷ��ظ�ֵ�ڷ�λ��ʾ
					g_mObjDec_fen1=(int)((g_mObjDec1-g_mObjDec_du1)*60.0);
					g_mObjDec_miao1=(g_mObjDec1-g_mObjDec_du1-g_mObjDec_fen1/60.0)*3600;
		            if(g_mGoto.m_nDeclination>0)
					{
					  g_gObjDec_sign1=1;
					}
					else
					{
					  g_gObjDec_sign1=-1;
					}

					FGetTelescopePos(AXIS_AZI);
			    	g_mGoto.m_nTescpAPos=g_mTelAziUtr1;
					g_mTelAzi=g_mGoto.m_nTescpAPos;
					while(g_mTelAzi>=360)
					{
					    g_mTelAzi=g_mTelAzi-360;
					 }
					while(g_mTelAzi<0)
					{
					    g_mTelAzi=g_mTelAzi+360;
					 } 		
					 g_mTelRa=g_mTelAzi; 				 
				   		
		
					MenuDelay(2);
					FGetTelescopePos(AXIS_ALT);
					g_mGoto.m_nTescpEPos=g_mTelAltUtr1;
					g_mTelAlt=fabs(g_mGoto.m_nTescpEPos);
					g_mTelDec=g_mTelAlt;

					if(g_mGoto.m_nAtitude>=0) //������
					 {
					   	
						if(g_mTelRa>360)
						{
						   g_mTelRa=g_mTelRa+360;
					    }
						g_mTelRa=g_mTelRa-180;
						if(g_mTelRa<0)
						{ 
						   g_mTelRa=g_mTelRa+360;
						}
					

						g_mTelDec=90.0-g_mTelDec;
					}
					else //�ϰ���
					{	
					   g_mTelRa=g_mTelRa-180;
					   if(g_mTelRa<0)
					   {
					      g_mTelRa=-1.0*g_mTelRa;
						}
						else
						{
						   g_mTelRa=360-g_mTelRa;
						}
					    
						g_mTelDec=g_mTelDec-90.0;
							
					}

				


					g_mTelRa=g_mTelRa/15.0;//-syn_mApos/15.0;
					CurrentRa=g_mSidTime-(g_mTelRa-syn_mApos/15.0-dg_mSkyMapAzi/15.0);//������Զ��λ�ø�SKYMAP
					if(CurrentRa<0)
					{
					 CurrentRa=CurrentRa+24;
					}
					if(CurrentRa>24)
					{
					 CurrentRa=CurrentRa-24;
					}

					g_mTelRa_shi=(int)(g_mTelRa-syn_mApos/15.0+dg_mApos0);//��ƽ���귽λ���ظ�ֵ�ڷ�λ��ʾ
					g_mTelRa_fen=(int)((g_mTelRa-syn_mApos/15.0+dg_mApos0-g_mTelRa_shi)*60.0);
					g_mTelRa_miao=(g_mTelRa-syn_mApos/15.0+dg_mApos0-g_mTelRa_shi-g_mTelRa_fen/60.0)*3600;
		         if((g_mhandtrackAzi==1)&&(g_mGoto.m_nTAState==2))//���ָ��ʱ����Զ����Ŀ��λ��һ�£��ֶ����ں󣬾Ͳ�һ����	{
					{
					  dg_mApos0=g_mObjHourA-g_mTelRa;

					  g_mTelRa_shi=g_mObjHourA_shi;
					  g_mTelRa_fen=g_mObjHourA_fen;
					  g_mTelRa_miao=g_mObjHourA_miao;
		
					}
		
					//g_mTelDec=g_mTelDec-syn_mZpos;					
					CurrentDec=g_mTelDec-syn_mZpos-dg_mSkyMapAlt;//������Զ��λ�ø�SKYMAP


				    g_mTelDec_du=(int)(g_mTelDec-syn_mZpos+dg_mZpos0);//��ƽ����߶ȷ��ظ�ֵ�ڷ�λ��ʾ
					g_mTelDec_fen=(int)((g_mTelDec-syn_mZpos+dg_mZpos0-g_mTelDec_du)*60.0);
					g_mTelDec_miao=(g_mTelDec-syn_mZpos+dg_mZpos0-g_mTelDec_du-g_mTelDec_fen/60.0)*3600;
			   if((g_mhandtrackAlt==1)&&(g_mGoto.m_nTEState==2))//���ָ��ʱ����Զ����Ŀ��λ��һ�£��ֶ����ں󣬾Ͳ�һ����	{
				{
				  dg_mZpos0=g_mObjDec1-g_mTelDec;

				  g_mTelDec_du=g_mObjDec_du1;
				  g_mTelDec_fen=g_mObjDec_fen1;
				  g_mTelDec_miao=g_mObjDec_miao1;
	
				}

			}
		
		}
	    //***************************************************************
		///**************************
		//���ò˵�ϵͳ
		if(g_mcalpalnet==0)//û��������
		{
           			LCDRfrsh();
					//ϵͳ���ڳ�ʼ��
					DispEn(0,4,1,22,"System Initializing...");
					GetPlanetPos();//��������λ��
					MenuDelay(1000);  
					//ϵͳ��ʼ�������					
					FBeep(1);
					LCDRfrsh();
					DispEn(0,4,1,22,"System Initialized    ");
					MenuDelay(1000);
					LCDRfrsh();
		            g_mcalpalnet=1;//��������	
		  }
		 DoMenu();
		 ///*************************


		//*********************************
		//��Զ���Զ�У׼
		if(!g_mGoto.m_nAlign)
		{
			FAutoAlign();
			g_mPauseTrack=0;//�ǲ�����ֹͣ�𶯵ĸ��� 0,���ǣ�1��
		}
		//*********************************

//***************************************************************
   //*********************************
		//�����ֶ�
	
		if((g_mhmaxspeed1)&&(hsendspd1.i<=4800))
		{
		   if(hsendspd1.i<4800)
		   {
		     if(g_mhmaxspeedchangedirect==1)
			 {
		       hsendspd1.i+=g_mhmaxspeedchangedirect*100;
			  }
			  else
			  {
			    hsendspd1.i+=g_mhmaxspeedchangedirect*300;
			  }
		   }  
			    
		   if(hsendspd1.i>=2560)
		   {
				if(g_mhmaxspeeddir1==1)
				{
				 	hsendposp.i=(long int)((1080.0* 256.0)/1.0993843447669305189094107299912e-4);
				}
				else
				{
				    hsendposp.i=(long int)((-1080.0* 256.0)/1.0993843447669305189094107299912e-4);
				}
	
			 if(g_mHandControlTelescopetwo!=1)
		      {	       
				UART1_SentByte(0x55);
				UART1_SentByte(0xAA);
				UART1_SentByte(0x01);
				UART1_SentByte(0x06);
				if(g_mhmaxspeedaxis1==1)
				{
				  UART1_SentByte(2);
				 }
				if(g_mhmaxspeedaxis1==33)
				{
				  UART1_SentByte(34);
				 }
				UART1_SentByte(hsendspd1.ub[1]);
				UART1_SentByte(hsendspd1.ub[0]);
				UART1_SentByte(hsendposp.ub[3]);
				UART1_SentByte(hsendposp.ub[2]);
				UART1_SentByte(hsendposp.ub[1]);
				}

			}
			else
			{
			    UART1_SentByte(0x55);
	 	   		UART1_SentByte(0xAA);
	  	   		UART1_SentByte(0x01);
	 	   		UART1_SentByte(0x01);
	  	   		UART1_SentByte(0x00);
		   		g_mTelStatus=0;
		
		     	g_mhmaxspeed1=false;
		     	
			}
  
		}
//*********************************
//��絼�ǵ�����
	//if(g_mSysInitGuide==0)//��������
	if(g_mTelStatus==2)//��Զ���ڸ���״̬���ɵ���
	{
		FGetAutoGuider();
		g_mGoto.m_nGuidMoveRa+=(m_GuiderRa+AGuiderRa)*0.00153;//��絼�ǳྭƫ����
		g_mGoto.m_nGuidMoveDec+=(m_GuiderDec+AGuiderDec)*0.00153;//��絼�ǳ�γƫ����
		//��λASCOM������ǲ���
		AGuiderRa=0;
		AGuiderDec=0;
		//sprintf(s1,"%d:%.5f   %d:%.5f",AGuiderRa,g_mGoto.m_nGuidMoveRa,AGuiderDec,g_mGoto.m_nGuidMoveDec);
		//sprintf(s1,"%d::%d",AGuiderRa,AGuiderDec);
		//DispEn(0,2,1,22,&s1[0]);



		//g_mGoto.m_nGuidMoveRa+=AGuiderRa*0.00153;//��絼�ǳྭƫ����
		//g_mGoto.m_nGuidMoveDec+=AGuiderDec*0.00153;//��絼�ǳ�γƫ����
	}
//*********************************

//��Զ�������ֶ���΢��
   
	 if(g_mTelescopeConType==1)//���ʽ
	 {
  	  if((g_mGoto.m_nGoto)&&(g_mTelStatusSet!=1))//((g_mOperateStatus==1)||(g_mOperateStatus==2)||((g_mGoto.m_nGoto)&&(g_mTelStatusSet!=1))||(g_nAlignPoint))//
	  {
	  
	
	   if(g_nsysstatus!=SYS_SUB1SUB2STAR_ALIGN)
        {
		    switch(g_mHandSpeed)	
	       {
		     case 0:
				 ddg_mApos=0.0;
			     ddg_mZpos=0.0;
				 dg_mApos+=g_mAposModify*ddg_mApos;
			     dg_mZpos+=g_mZposModify*ddg_mZpos;
			   break;
			  case 1:
			     ddg_mApos=0.00153;//0.0013;
			     ddg_mZpos=0.00120;//0.0010;
				 dg_mApos+=g_mAposModify*ddg_mApos;
			     dg_mZpos+=g_mZposModify*ddg_mZpos;
			  break;
			     case 2:
			     ddg_mApos=0.0031;//0.0026;
			     ddg_mZpos=0.0031;//0.0026;
				 dg_mApos+=g_mAposModify*ddg_mApos;
			     dg_mZpos+=g_mZposModify*ddg_mZpos;
			   break;
			   case 3:
			     ddg_mApos=0.0148;//0.0125;
			     ddg_mZpos=0.0148;//0.0125;
				 dg_mApos+=g_mAposModify*ddg_mApos;
			     dg_mZpos+=g_mZposModify*ddg_mZpos;
			   break;
			   case 4:
			     ddg_mApos=0.0602;//0.051;
			     ddg_mZpos=0.0602;//0.051;
				 dg_mApos+=g_mAposModify*ddg_mApos;
			     dg_mZpos+=g_mZposModify*ddg_mZpos;
			   break;
			   case 5:
			   	 ddg_mApos=0.1063;//0.090;
			     ddg_mZpos=0.1063;//0.090;
				 dg_mApos+=g_mAposModify*ddg_mApos;
			     dg_mZpos+=g_mZposModify*ddg_mZpos;
			     break;
			   case 6:
			   	 ddg_mApos=0.370;//0.160;
			     ddg_mZpos=0.160;//0.135;
				 dg_mApos+=g_mAposModify*ddg_mApos;
			     dg_mZpos+=g_mZposModify*ddg_mZpos;
			     break;
			   case 7:
			   	 ddg_mApos=0.461;//0.390;
			     ddg_mZpos=0.461;//0.390;
				 dg_mApos+=g_mAposModify*ddg_mApos;
			     dg_mZpos+=g_mZposModify*ddg_mZpos;
			     break;
			   case 8:
			   	 ddg_mApos=0.745;//0.631;
			     ddg_mZpos=0.745;//0.631;
				 dg_mApos+=g_mAposModify*ddg_mApos;
			     dg_mZpos+=g_mZposModify*ddg_mZpos;
			     break;
			   case 9:
			   	 ddg_mApos=1.560;//1.320;
			     ddg_mZpos=1.560;//1.320;
				 dg_mApos+=g_mAposModify*ddg_mApos;
			     dg_mZpos+=g_mZposModify*ddg_mZpos;
			     break;
	
				default:
			     ddg_mApos=0.0;
			     ddg_mZpos=0.0;
				 dg_mApos+=g_mAposModify*ddg_mApos;
			     dg_mZpos+=g_mZposModify*ddg_mZpos;
			   break;
	
			}
		}
		else
		{
	
		  switch(g_mHandSpeed)	//У׼ʱ����
	       {
		     case 0:
				 ddg_mApos=0.0;
			     ddg_mZpos=0.0;
				 dg_mApos+=g_mAposModify*ddg_mApos;
			     dg_mZpos+=g_mZposModify*ddg_mZpos;
			   break;
			  case 1:
			     ddg_mApos=0.00154;//0.0013;
			     ddg_mZpos=0.00154;//0.0013;
				 dg_mApos+=g_mAposModify*ddg_mApos;
			     dg_mZpos+=g_mZposModify*ddg_mZpos;
			  break;
			     case 2:
			     ddg_mApos=0.0031;//0.0026;
			     ddg_mZpos=0.0031;//0.0026;
				 dg_mApos+=g_mAposModify*ddg_mApos;
			     dg_mZpos+=g_mZposModify*ddg_mZpos;
			   break;
			   case 3:
			     ddg_mApos=0.0260;//0.022;
			     ddg_mZpos=0.0236;//0.020;
				 dg_mApos+=g_mAposModify*ddg_mApos;
			     dg_mZpos+=g_mZposModify*ddg_mZpos;
			   break;
			   case 4:
			     ddg_mApos=0.084;//0.071;
			     ddg_mZpos=0.084;//0.071;
				 dg_mApos+=g_mAposModify*ddg_mApos;
			     dg_mZpos+=g_mZposModify*ddg_mZpos;
			   break;
			   case 5:
			   	 ddg_mApos=0.154;//0.130;
			     ddg_mZpos=0.142;//0.120;
				 dg_mApos+=g_mAposModify*ddg_mApos;
			     dg_mZpos+=g_mZposModify*ddg_mZpos;
			     break;
			   case 6:
			   	 ddg_mApos=0.236;//0.200;
			     ddg_mZpos=0.213;//0.180;
				 dg_mApos+=g_mAposModify*ddg_mApos;
			     dg_mZpos+=g_mZposModify*ddg_mZpos;
			     break;
			   case 7:
			   	 ddg_mApos=0.614;//0.520;
			     ddg_mZpos=0.614;//0.520;
				 dg_mApos+=g_mAposModify*ddg_mApos;
			     dg_mZpos+=g_mZposModify*ddg_mZpos;
			     break;
			   case 8:
			   	 ddg_mApos=1.004;//0.85;
			     ddg_mZpos=1.004;//0.85;
				 dg_mApos+=g_mAposModify*ddg_mApos;
			     dg_mZpos+=g_mZposModify*ddg_mZpos;
			     break;
			   case 9:
			   	 ddg_mApos=2.150;//1.820;
			     ddg_mZpos=2.150;//1.820;
				 dg_mApos+=g_mAposModify*ddg_mApos;
			     dg_mZpos+=g_mZposModify*ddg_mZpos;
			     break;
	
				default:
			     ddg_mApos=0.0;
			     ddg_mZpos=0.0;
				 dg_mApos+=g_mAposModify*ddg_mApos;
			     dg_mZpos+=g_mZposModify*ddg_mZpos;
			   break;
	
			}
		}
	  }
	}
	else  //��ƽʽ
	{  if((g_mGoto.m_nGoto)&&(g_mTelStatusSet!=1))//((g_mOperateStatus==1)||(g_mOperateStatus==2)||((g_mGoto.m_nGoto)&&(g_mTelStatusSet!=1))||(g_nAlignPoint))//
	  {
	   
	    if(g_nsysstatus!=SYS_SUB1SUB2STAR_ALIGN)
        {
		   switch(g_mHandSpeed)	
		   {
		     case 0:
			     ddg_mApos=0.0007;//0.0006;
			     ddg_mZpos=0.0007;//0.0006;
				 dg_mApos+=g_mAposModify*ddg_mApos;
			     dg_mZpos+=g_mZposModify*ddg_mZpos;
			   break;
			  case 1:
			     ddg_mApos=0.0015;//0.0013;
			     ddg_mZpos=0.0015;//0.0013;
				 dg_mApos+=g_mAposModify*ddg_mApos;
			     dg_mZpos+=g_mZposModify*ddg_mZpos;
			  break;
			     case 2:
			     ddg_mApos=0.0083;//0.0070;
			     ddg_mZpos=0.0083;//0.0070;
				 dg_mApos+=g_mAposModify*ddg_mApos;
			     dg_mZpos+=g_mZposModify*ddg_mZpos;
			   break;
			   case 3:
			     ddg_mApos=0.0234;//0.020;
			     ddg_mZpos=0.0235;//0.020;
				 dg_mApos+=g_mAposModify*ddg_mApos;
			     dg_mZpos+=g_mZposModify*ddg_mZpos;
			   break;
			   case 4:
			     ddg_mApos=0.042;//0.035;
			     ddg_mZpos=0.041;//0.035;
				 dg_mApos+=g_mAposModify*ddg_mApos;
			     dg_mZpos+=g_mZposModify*ddg_mZpos;
			   break;
			   case 5:
			   	 ddg_mApos=0.071;//0.060;
			     ddg_mZpos=0.0708;//0.060;
				 dg_mApos+=g_mAposModify*ddg_mApos;
			     dg_mZpos+=g_mZposModify*ddg_mZpos;
			     break;
			   case 6:
			   	 ddg_mApos=0.142;//0.120;
			     ddg_mZpos=0.106;//0.090;
				 dg_mApos+=g_mAposModify*ddg_mApos;
			     dg_mZpos+=g_mZposModify*ddg_mZpos;
			     break;
			   case 7:
			   	 ddg_mApos=0.260;//0.280;//0.320//0.220;
			     ddg_mZpos=0.236;//0.230;//0.250;//0.260;//0.200//0.200;
				 dg_mApos+=g_mAposModify*ddg_mApos;
			     dg_mZpos+=g_mZposModify*ddg_mZpos;
			     break;
			   case 8:
			   	 ddg_mApos=0.634;//0.635;//0.620;//0.700//0.750;//0.680//0.550;
			     ddg_mZpos=0.390;//0.400;//0.430;//0.380//0.450;//0.420//0.320;
				 dg_mApos+=g_mAposModify*ddg_mApos;
			     dg_mZpos+=g_mZposModify*ddg_mZpos;
			     break;
			   case 9:
			   	 ddg_mApos=0.980;//0.990;//0.960;//1.100;//1.200;//0.900//0.700;
			     ddg_mZpos=0.450;//0.460;//0.480;//0.520;//0.580;//0.680;//0.480//0.380;
				 dg_mApos+=g_mAposModify*ddg_mApos;
			     dg_mZpos+=g_mZposModify*ddg_mZpos;
			     break;
	
				default:
			     ddg_mApos=0.0;
			     ddg_mZpos=0.0;
				 dg_mApos+=g_mAposModify*ddg_mApos;
			     dg_mZpos+=g_mZposModify*ddg_mZpos;
			   break;
	
			}
		}
		else
		{
		  	switch(g_mHandSpeed)//У׼ʱ����	
		   {
		     case 0:
			     ddg_mApos=0.0011;//0.0009;
			     ddg_mZpos=0.0007;//0.0006;
				 dg_mApos+=g_mAposModify*ddg_mApos;
			     dg_mZpos+=g_mZposModify*ddg_mZpos;
			   break;
			  case 1:
			     ddg_mApos=0.0024;//0.0020;
			     ddg_mZpos=0.0019;//0.0016;
				 dg_mApos+=g_mAposModify*ddg_mApos;
			     dg_mZpos+=g_mZposModify*ddg_mZpos;
			  break;
			     case 2:
			     ddg_mApos=0.015;//0.0130;
			     ddg_mZpos=0.0076;//0.0065;
				 dg_mApos+=g_mAposModify*ddg_mApos;
			     dg_mZpos+=g_mZposModify*ddg_mZpos;
			   break;
			   case 3:
			     ddg_mApos=0.035;//0.030;
			     ddg_mZpos=0.035;//0.030;
				 dg_mApos+=g_mAposModify*ddg_mApos;
			     dg_mZpos+=g_mZposModify*ddg_mZpos;
			   break;
			   case 4:
			     ddg_mApos=0.062;//0.052;
			     ddg_mZpos=0.060;//0.050;
				 dg_mApos+=g_mAposModify*ddg_mApos;
			     dg_mZpos+=g_mZposModify*ddg_mZpos;
			   break;
			   case 5:
			   	 ddg_mApos=0.093;//0.078;
			     ddg_mZpos=0.090;//0.076;
				 dg_mApos+=g_mAposModify*ddg_mApos;
			     dg_mZpos+=g_mZposModify*ddg_mZpos;
			     break;
			   case 6:
			   	 ddg_mApos=0.178;//0.150;
			     ddg_mZpos=0.130;//0.110;
				 dg_mApos+=g_mAposModify*ddg_mApos;
			     dg_mZpos+=g_mZposModify*ddg_mZpos;
			     break;
			   case 7:
			   	 ddg_mApos=0.335;//0.280;
			     ddg_mZpos=0.300;//0.250;
				 dg_mApos+=g_mAposModify*ddg_mApos;
			     dg_mZpos+=g_mZposModify*ddg_mZpos;
			     break;
			   case 8:
			   	 ddg_mApos=0.805;//0.680;
			     ddg_mZpos=0.485;//0.410;
				 dg_mApos+=g_mAposModify*ddg_mApos;
			     dg_mZpos+=g_mZposModify*ddg_mZpos;
			     break;
			   case 9:
			   	 ddg_mApos=1.005;//0.850;
			     ddg_mZpos=0.69;//0.580;
				 dg_mApos+=g_mAposModify*ddg_mApos;
			     dg_mZpos+=g_mZposModify*ddg_mZpos;
			     break;
	
				default:
			     ddg_mApos=0.0;
			     ddg_mZpos=0.0;
				 dg_mApos+=g_mAposModify*ddg_mApos;
			     dg_mZpos+=g_mZposModify*ddg_mZpos;
			   break;
	
			}
		}
	  }

	}

 if((g_mZposModify!=0)||(g_mAposModify!=0 ))
 {
  g_mPointNewStarTracking=0;//ָ���µ��ǲ�����
 }
		
 //***************************************************************
	  

 //**************************************************
//��Զ���Զ�
	    if(g_mGoto.m_nStartStop)
		  {
			  if(g_mTelescopeConType==0)
			  {
			      g_nsysstatus=SYS_NOTELSCOPE;
				  g_mGoto.m_nStartStop=false;
				  g_mGoto.m_nAlign=true;
			  }
	       	 else
			 {
				 if(g_mAzEq==0)
				{
				     GotoAZ();
				 }
				 else
				 {
				     GotoEQ();
				 }
			 }
		  }
 //**************************************************

//**************************************************
 //��Զ���ز�У׼,true����ִ��,falseû��	
		 if(g_mGearErrorAlign==true)			  
		 { 
		 
		   MenuDelay(3000);

	
		   switch(g_mBackLashAxis)
		   {
		       case 0:					  
		    	    FGetTelescopePos(AXIS_AZI);
			    	g_mGoto.m_nTescpAPos=g_mTelAziUtr1;
					g_mTelAzi=g_mGoto.m_nTescpAPos;

			   break;
			   case 1:
		         FGetTelescopePos(AXIS_ALT);
			     g_mGoto.m_nTescpEPos=g_mTelDecUtr1;
	    	     g_mTelAlt=fabs(g_mGoto.m_nTescpEPos);
			   break;
			   case 2:
			        FGetTelescopePos(AXIS_RA);
			    	g_mGoto.m_nTescpAPos=g_mTelRaUtr1;
					g_mTelAzi=g_mGoto.m_nTescpAPos;
			   break;
			   case 3:
		          FGetTelescopePos(AXIS_DEC);
			      g_mGoto.m_nTescpEPos=g_mTelDecUtr1;
	    	      g_mTelAlt=g_mGoto.m_nTescpEPos;
			   break;
			   default:
			   break;
			}
			  		   	   		 
           FHandStopTelescope();
           MenuDelay(100);
		   switch(g_mBackLashAxis)
		   {
		       case 0:					  
		    	    FGetTelescopePos(AXIS_AZI);
			    	g_mGoto.m_nTescpAPos=g_mTelAziUtr1;
					g_mTelAzi=g_mGoto.m_nTescpAPos;

			   break;
			   case 1:
		         FGetTelescopePos(AXIS_ALT);
			     g_mGoto.m_nTescpEPos=g_mTelDecUtr1;
	    	     g_mTelAlt=fabs(g_mGoto.m_nTescpEPos);
			   break;
			   case 2:
			        FGetTelescopePos(AXIS_RA);
			    	g_mGoto.m_nTescpAPos=g_mTelRaUtr1;
					g_mTelAzi=g_mGoto.m_nTescpAPos;
			   break;
			   case 3:
		          FGetTelescopePos(AXIS_DEC);
			      g_mGoto.m_nTescpEPos=g_mTelDecUtr1;
	    	      g_mTelAlt=g_mGoto.m_nTescpEPos;
			   break;
			   default:
			   break;
			}
		  	

	
		  
		   switch(g_mBackLashAxis)
		    {
		       case 0:
								  
		    	    FGetTelescopePos(AXIS_AZI); 
		        	g_mGoto.m_nTescpAPos=g_mTelAziUtr1;
				    g_mTelAzi=g_mGoto.m_nTescpAPos;

					//g_mTelAzi=g_mTelAzi;//��ʼ����
					//g_mTelAzi=g_mTelAzi+180;//��ʼ������
					g_mTelAzi=g_mTelAzi+g_mGoto.m_nTescpAPZero;//��ʼ��Ϊ����λ��

					while(g_mTelAzi>=360)
					{
						    g_mTelAzi=g_mTelAzi-360;
					 }
					while(g_mTelAzi<0)
					{
					    g_mTelAzi=g_mTelAzi+360;
					 }
					 

				 while( fabs(g_mTelAzi-g_mTelAzi0)>0.0014)
				{	
				  if(g_mTelGearErrorRaAlignDirect==2)
					{
			          FHandControlTelescope(AXIS_AZI,DIRECT_LEFT,1);
					 }
					 if(g_mTelGearErrorRaAlignDirect==1)
					{
			          FHandControlTelescope(AXIS_AZI,DIRECT_RIGHT,1);
					 }
				   	
					MenuDelay(10);
					FGetTelescopePos(AXIS_AZI);
					MenuDelay(10); 
			    	g_mGoto.m_nTescpAPos=g_mTelAziUtr1;
					g_mTelAzi=g_mGoto.m_nTescpAPos;
	
					//g_mTelAzi=g_mTelAzi;//��ʼ����
					//g_mTelAzi=g_mTelAzi+180;//��ʼ������
					g_mTelAzi=g_mTelAzi+g_mGoto.m_nTescpAPZero;//��ʼ��Ϊ����λ��
	
					while(g_mTelAzi>=360)
					{
						    g_mTelAzi=g_mTelAzi-360;
					 }
					while(g_mTelAzi<0)
					{
					    g_mTelAzi=g_mTelAzi+360;
					 } 		

			
				}
			   break;
			   case 1:
		      
					 FGetTelescopePos(AXIS_ALT);
				    g_mGoto.m_nTescpEPos=g_mTelAltUtr1;
					g_mTelAlt=g_mGoto.m_nTescpEPos;
	
					//g_mTelAlt=g_mTelAlt; //��ʼ�����ƺ
					//g_mTelAlt=90-g_mTelAlt;//��ʼ�����춥
					  g_mTelAlt=g_mGoto.m_nTescpEPZero-g_mTelAlt;//��ʼ��Ϊ����λ��

		;		
				  	 // sprintf(s1,"g_mTelAlt0=%f",g_mTelAlt0);
                     // DispEn(0,1,1,128,&s1[0]);


				 while( fabs(g_mTelAlt-g_mTelAlt0)>0.0014)
				{
				   	
				     if(g_mTelGearErrorDecAlignDirect==2)
					{
			          FHandControlTelescope(AXIS_ALT,DIRECT_DOWN,1);
					 }
					 if(g_mTelGearErrorDecAlignDirect==1)
					{
			          FHandControlTelescope(AXIS_ALT,DIRECT_UP,1);
					 }
				 

					 MenuDelay(10);
					  FGetTelescopePos(AXIS_ALT);
					  MenuDelay(10);
				     g_mGoto.m_nTescpEPos=g_mTelAltUtr1;
					 g_mTelAlt=g_mGoto.m_nTescpEPos;
	
					//g_mTelAlt=g_mTelAlt; //��ʼ�����ƺ
					//g_mTelAlt=90-g_mTelAlt;//��ʼ�����춥
					  g_mTelAlt=g_mGoto.m_nTescpEPZero-g_mTelAlt;//��ʼ��Ϊ����λ��
 
			}
			   break;
			   case 2:
			  
				   FGetTelescopePos(AXIS_RA);
			     g_mGoto.m_nTescpAPos=g_mTelRaUtr1;
				 g_mTelAzi=g_mGoto.m_nTescpAPos;	
	

				 while( fabs(g_mTelAzi-g_mTelAzi0)>0.0014)
				{
				   	
					 if(g_mTelGearErrorRaAlignDirect==2)
					{
			          FHandControlTelescope(AXIS_RA,DIRECT_RIGHT,2);
					 }
					 if(g_mTelGearErrorRaAlignDirect==1)
					{
			          FHandControlTelescope(AXIS_RA,DIRECT_LEFT,2);
					  }

				 

					 MenuDelay(10);
					 FGetTelescopePos(AXIS_RA);
					 MenuDelay(10);
			    	 g_mGoto.m_nTescpAPos=g_mTelRaUtr1;
					 g_mTelAzi=g_mGoto.m_nTescpAPos;	

					  
				}

			   break;
			   case 3:
		         
					  
		    	    FGetTelescopePos(AXIS_DEC);
			    	g_mGoto.m_nTescpEPos=g_mTelDecUtr1;
					g_mTelAlt=fabs(g_mGoto.m_nTescpEPos);	
		;

				 while( fabs(g_mTelAlt-g_mTelAlt0)>0.0014)
				{
				   		if(g_mTelGearErrorDecAlignDirect==2)
					{
			          FHandControlTelescope(AXIS_DEC,DIRECT_DOWN,2);
					 }
					 if(g_mTelGearErrorDecAlignDirect==1)
					{
			          FHandControlTelescope(AXIS_DEC,DIRECT_UP,2) ;
					 }
					 MenuDelay(10);
					 FGetTelescopePos(AXIS_DEC);
					  MenuDelay(10);
			    	 g_mGoto.m_nTescpEPos=g_mTelDecUtr1;
					 g_mTelAlt=fabs(g_mGoto.m_nTescpEPos);	

					  
				}
			   break;
			
			}
			
		    FHandStopTelescope();
            MenuDelay(100);
			FBeep(2);
		    g_mGearErrorAlign=false;
		   
		 }
	//��Զ���ز�У׼
	//**************************************************

		
		  //*********************************************	
		  //����ƫ����ʾ����
		  g_mPoleAxisEW=g_mTelError.mTSettingEW;
		  g_mPoleAxisNS=g_mTelError.mTSettingNS;
		  //*********************************************
		 
		  	
 		 //***********************************************
		 MenuDelay(2);
		 //***********************************************


		//************************************************
		//���û����Զ�����ϣ���û��ͨ�ţ���ѭ�����ڼӳ�
		if(!g_mTelescopeConType)
	    {
		   MenuDelay(50);
		}
//		if(calpalnet==0)//û��������
//		{
//            GetPlanetPos();//ʵʱ��������λ��
//		    calpalnet=1;//��������
//		  }
		//MenuDelay(100);
		if(!g_mGoto.m_nStartStop)
		{
		  MenuDelay(100);
		 }
		 //����ѭ���������
		//************************************************
	
		
	} 
	//**************************************************

}
//ϵͳ���������
//*******************************************************

