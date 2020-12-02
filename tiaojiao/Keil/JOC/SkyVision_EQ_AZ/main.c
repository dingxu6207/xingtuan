//*******************************************************
//*******************************************
//**********望远镜主程序*********************
//**********欧洲五国语言版*******************
//**********编者：柳光乾           **********
//**********2008年于云南天文台     **********
//**********lgq@ynao.ac.cn         **********
//*******************************************
//*******************************************
//*******************************************************


//*******************************************************
#include <LPC214X.H>   //系统文件
#include "IOConfig.H"  //系统文件
#include "config.h"	   //系统文件
#include "LCD12864.c"  //系统文件
#include "Disp.c"	   //显示文件
#include "Keys.c"	   //按键检测文件
#include "Interrupt.c" //中断处理文件
#include "UTR0.c"	   //串口零处理文件
#include "Timers.c"	   //时间文件
#include "PowerUp.c"   //系统电源管文件
#include "ROM.c"		//数据存储芯片读写文件
#include "starstructure.c" //星表数据机构文件
#include "FAS.c"		//校准星文件
#include "Menu.c"		//系统菜单文件
#include "ASCOM.c"		//系统SKYMAP通信文件
//*******************************************************
//函数变量
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

 //uint8 g_mSendToSkymap;//控制向SKYMAP发送望远镜位置的时间 


 uint8 site[8];
 uint8 Lon[6];
 uint8 Lat[5];
 uint8 Zone[3]; 
 uint8 i;
//*******************************************************
//*******************************************************
//系统主程序开始
int main(void)
 {
  	 //系统上电初始化
	 PowerOnInit();
	//***********************************			   
	//串口零初始化
	 Init_Uart0(UART_BAUD(9600));//分配给上位机，PC机，烧程序
	 //***********************************
	//串口一初始化
	 Init_Uart1(UART_BAUD(9600)); //分配给下位机，给轴的驱动
	 //***********************************
    //下位机驱动上电打开，但是所有轴停止并禁止手动
     FHandPowerTelescope();
	 //***********************************	
	//定位跟踪参数初始化
	 FSetupPointTrackPara();	
	//***********************************
	//系统参数初始化
     FInitPara(); 
	//***********************************
//	//设置编码器为零
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
//	 MenuDelay(100);	//延时
	 //**********************************
	 //读取系统参数
     ReadFromRom(3531,0,10,data);
	 g_mMenuLangauge=data[0];//系统上次设置的菜单语言 
	 if(data[1]==1)	         //该手控板是不是第一次用 
	 {
	    FSetSysTime();
	    data[1]=0;
	    WriteToRom(3531,0,2,data);
	  }
	//***********************************
//	//系统开机界面显示
//	   	DispEn(0,3,1,22,"     StarTracker      ");
//		DispEn(0,5,1,22,"   Ver. 0.99 EQ/AZ    ");
//		DispEn(0,7,1,22," (c)2012  MAXVISION   ");
        FShowStart();
	//***********************************
	//*********************************************************
	 //向下位机发送信号以识别下位机是地平式还是赤道式	 
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
	 MenuDelay(10);	//延时

	 //***********************************
	 //设置望远镜装置的系统标志
	if(g_mTelescopeConType==1)
	{
       g_mAzEq=1; //赤道式
	}
	else
	{
       g_mAzEq=0;  //地平式
	 }
    //***********************************
	//系统参数初始化
	  
    g_mEQHn=false;//赤道式望远镜目标是否在地平线
    g_mTelRABack=0.050;  //赤经回差	
    g_mTelDecBack=0.045;  //赤纬回差

	g_mGoto.m_nTescpAPZero=100;
	g_mGoto.m_nTescpEPZero=60;

	GetTelZero(&azi_zero,&alt_zero); //获取望远镜零点

	g_mGoto.m_nTescpAPZero=azi_zero; //望远镜方位零点 ,方位以北开始算，向东为正
	g_mGoto.m_nTescpEPZero=alt_zero;//望远镜高度零点  ，高度以地平算，向上为正

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
//  //GetPlanetPos();//计算行星位置 
   MenuDelay(2000);
   LCDRfrsh();
  //***********************************
  //系统初始化向导
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
//进入系统工作模式
while(1)
{  	
          //***********************************
		//设置望远镜当前位置
		g_mCurrentTelAzi=g_mTelAzi;	
		g_mCurrentTelAlt=g_mTelAlt;  //当前望远镜位置  
		 
		m_GuiderRa=0;	  //为1正向，-1方向，为0不导，赤经光电导行信号
	  m_GuiderDec=0; //为1正向，-1方向，为0不导	 ，赤纬光电导行信
		    
	    //***************************************************************
	   //*****************************************************************
		///////////////////////////////////////////////////////////////////
		//ASCOM通信处理函数

		Skymap();

		///////////////////////////////////////////////////////////////////
	   	//*****************************************************************		
		//***************************************************************
		///望远镜位置的获取							
	    if(g_mTelescopeConType==1) //赤道式望远镜
		 {
			g_mAzEq=1;//跟踪模式，赤道式望远镜永远赤道式跟踪，而地平式望远镜可以是地平式跟踪，也可以是赤道式跟踪

			//g_mObjHourA=g_mGoto.m_nStarAPosTshow-8.3333333333e-4;//g_mGoto.m_nHourAngle;
			g_mObjHourA=g_mGoto.m_nRightAscension;//g_mGoto.m_nRightAscension;

			g_mObjHourA_shi=(int)g_mObjHourA;//地平坐标方位返回赋值于方位显示
			g_mObjHourA_fen=(int)((g_mObjHourA-g_mObjHourA_shi)*60.0);
			g_mObjHourA_miao=(g_mObjHourA-g_mObjHourA_shi-g_mObjHourA_fen/60.0)*3600;


			g_mObjDec1=fabs(g_mGoto.m_nStarEPosTshow);//g_mGoto.m_nDeclination);
										
			g_mObjDec_du1=(int)g_mObjDec1;//地平坐标高度返回赋值于方位显示
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
									 	
	            if(g_mGoto.m_nAtitude>=0) //北半球
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
			 else   //南半球
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
//			//CurrentRa=g_mTelRa-dg_mSkyMapAzi/15.0;	 //返回望远镜位置给SKYMAP
//			CurrentRa=g_mSidTime-(g_mTelRa-dg_mSkyMapAzi/15.0);//返回望远镜位置给SKYMAP
//			if(CurrentRa<0)
//			{
//			 CurrentRa=CurrentRa+24;
//			}
//			if(CurrentRa>24)
//			{
//			 CurrentRa=CurrentRa-24;
//			}
//
//			g_mTelRa_shi=(int)g_mTelRa;//地平坐标方位返回赋值于方位显示
//			g_mTelRa_fen=(int)((g_mTelRa-g_mTelRa_shi)*60.0);
//			g_mTelRa_miao=(g_mTelRa-g_mTelRa_shi-g_mTelRa_fen/60.0)*3600;
//			if((g_mhandtrackAzi==1)&&(g_mGoto.m_nTAState==2))//最初指向时，望远镜与目标位置一致，手动调节后，就不一致了	{
//			{
//			  g_mTelRa_shi=g_mObjRa_shi;
//			  g_mTelRa_fen=g_mObjRa_fen;
//			  g_mTelRa_miao=g_mObjRa_miao;
//
//			}
//
//			g_mTelDec=g_mTelDec-syn_mZpos;			
//			CurrentDec=g_mTelDec-dg_mSkyMapAlt;//返回望远镜位置给SKYMAP
//
//			g_mTelDec_du=(int)g_mTelDec;//地平坐标高度返回赋值于方位显示
//			g_mTelDec_fen=(int)((g_mTelDec-g_mTelDec_du)*60.0);
//			g_mTelDec_miao=(g_mTelDec-g_mTelDec_du-g_mTelDec_fen/60.0)*3600;
//			if((g_mhandtrackAlt==1)&&(g_mGoto.m_nTEState==2))//最初指向时，望远镜与目标位置一致，手动调节后，就不一致了	{
//			{
//			  g_mTelDec_du=g_mObjDec_du;
//			  g_mTelDec_fen=g_mObjDec_fen;
//			  g_mTelDec_miao=g_mObjDec_miao;
//
//			}
					g_mTelRa=g_mTelRa/15.0;//-syn_mApos/15.0;
					CurrentRa=g_mSidTime-(g_mTelRa-syn_mApos/15.0-dg_mSkyMapAzi/15.0);//返回望远镜位置给SKYMAP
					if(CurrentRa<0)
					{
					 CurrentRa=CurrentRa+24;
					}
					if(CurrentRa>24)
					{
					 CurrentRa=CurrentRa-24;
					}

					g_mTelRa_shi=(int)(g_mTelRa-syn_mApos/15.0+dg_mApos0);//地平坐标方位返回赋值于方位显示
					g_mTelRa_fen=(int)((g_mTelRa-syn_mApos/15.0+dg_mApos0-g_mTelRa_shi)*60.0);
					g_mTelRa_miao=(g_mTelRa-syn_mApos/15.0+dg_mApos0-g_mTelRa_shi-g_mTelRa_fen/60.0)*3600;
		         if((g_mhandtrackAzi==1)&&(g_mGoto.m_nTAState==2))//最初指向时，望远镜与目标位置一致，手动调节后，就不一致了	{
					{
					  dg_mApos0=g_mObjHourA-g_mTelRa;

					  g_mTelRa_shi=g_mObjHourA_shi;
					  g_mTelRa_fen=g_mObjHourA_fen;
					  g_mTelRa_miao=g_mObjHourA_miao;
		
					}
		
					//g_mTelDec=g_mTelDec-syn_mZpos;					
					CurrentDec=g_mTelDec-syn_mZpos-dg_mSkyMapAlt;//返回望远镜位置给SKYMAP


				    g_mTelDec_du=(int)(g_mTelDec-syn_mZpos+dg_mZpos0);//地平坐标高度返回赋值于方位显示
					g_mTelDec_fen=(int)((g_mTelDec-syn_mZpos+dg_mZpos0-g_mTelDec_du)*60.0);
					g_mTelDec_miao=(g_mTelDec-syn_mZpos+dg_mZpos0-g_mTelDec_du-g_mTelDec_fen/60.0)*3600;
			   if((g_mhandtrackAlt==1)&&(g_mGoto.m_nTEState==2))//最初指向时，望远镜与目标位置一致，手动调节后，就不一致了	{
				{
				  dg_mZpos0=g_mObjDec1-g_mTelDec;

				  g_mTelDec_du=g_mObjDec_du1;
				  g_mTelDec_fen=g_mObjDec_fen1;
				  g_mTelDec_miao=g_mObjDec_miao1;
	
				}
			

		 }
		 else if(g_mTelescopeConType==2)  //地平式望远镜
		 {	  
            if(g_mAzEq==0)
			{			    
					//g_mObjAzi=g_mGoto.m_nStarAPosT;//初始化向北
				    //g_mObjAzi=g_mGoto.m_nStarAPosT+180;//初始化向南
					//g_mObjAzi=g_mGoto.m_nStarAPos0+180;//初始化任意值，显示星的最原始坐标，而不是经装置改正后的坐标

					g_mObjAzi=g_mGoto.m_nStarAPosTshow+180;
		
			 	    g_mObjAzi_du=(int)g_mObjAzi;//地平坐标方位返回赋值于方位显示
				    g_mObjAzi_fen=(int)((g_mObjAzi-g_mObjAzi_du)*60.0);
				    g_mObjAzi_miao=(g_mObjAzi-g_mObjAzi_du-g_mObjAzi_fen/60.0)*3600;
		
				    //g_mObjAlt=g_mGoto.m_nStarEPosT;	//初始化向地坪
					//g_mObjAlt=90-g_mGoto.m_nStarEPosT; //初始化向天顶
					//g_mObjAlt=90-g_mGoto.m_nStarEPos0;//初始化任意值，显示星的最原始坐标，而不是经装置改正后的坐标

					 g_mObjAlt=90-g_mGoto.m_nStarEPosTshow;

			    	g_mObjAlt_du=(int)g_mObjAlt;//地平坐标高度返回赋值于高度显示
				    g_mObjAlt_fen=(int)((g_mObjAlt-g_mObjAlt_du)*60.0);
				    g_mObjAlt_miao=(g_mObjAlt-g_mObjAlt_du-g_mObjAlt_fen/60.0)*3600;
		
				    FGetTelescopePos(AXIS_AZI);
			    	g_mGoto.m_nTescpAPos=g_mTelAziUtr1;
					g_mTelAzi=g_mGoto.m_nTescpAPos;	

					//g_mTelAzi=g_mTelAzi;//初始化向北
					//g_mTelAzi=g_mTelAzi+180;//初始化向南
					if(g_mstartOTAset==0)//开机时设置望远镜的初始指向
					{
					     g_mTelAzi=g_mGoto.m_nTescpAPZero;//初始化为任意位置
					 }
					 else
					 {
					    g_mTelAzi=g_mTelAzi+g_mGoto.m_nTescpAPZero;//初始化为任意位置
					 }

					while(g_mTelAzi>=360)
					{
					    g_mTelAzi=g_mTelAzi-360;
					 }
					while(g_mTelAzi<0)
					{
					    g_mTelAzi=g_mTelAzi+360;
					 } 		
					 
					CurrentRa=g_mTelAzi-dg_mApos_syn-dg_mSkyMapAzi; //返回望远镜位置给SKYMAP
					g_mTelAzi_du=(int)(g_mTelAzi-dg_mApos_syn+dg_mApos0);//地平坐标方位返回赋值于高显示
					g_mTelAzi_fen=(int)((g_mTelAzi-dg_mApos_syn+dg_mApos0-g_mTelAzi_du)*60.0);
					g_mTelAzi_miao=(int)((g_mTelAzi-dg_mApos_syn+dg_mApos0-g_mTelAzi_du-g_mTelAzi_fen/60.0)*3600.0);
					
					if((g_mhandtrackAzi==1)&&(g_mGoto.m_nTAState==2))//最初指向时，望远镜与目标位置一致，手动调节后，就不一致了	{
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

		    		//g_mTelAlt=g_mTelAlt; //初始化向地坪
					//g_mTelAlt=90-g_mTelAlt;//初始化向天顶
					if(g_mstartOTAset==0)//开机时设置望远镜的初始指向
					{
					  g_mTelAlt=g_mGoto.m_nTescpEPZero;//初始化为任意位置
					 }
					 else
					 {
//					   if((g_mGoto.m_nTescpEPZero-g_mTelAlt)>90)
//					   {
//					      g_mTelAlt=g_mGoto.m_nTescpEPZero-g_mTelAlt;//初始化为任意位置
//						  g_mTelAlt=180-g_mTelAlt;
//						}
//						else
//						{
						   g_mTelAlt=g_mGoto.m_nTescpEPZero-g_mTelAlt;//初始化为任意位置
//						 }
					 
					 }
					 if(g_mTelAlt>90)
					 {
					   g_mTelAlt=180-g_mTelAlt;
					 }
						
				
					CurrentDec=g_mTelAlt-dg_mZpos_syn-dg_mSkyMapAlt;//返回望远镜位置给SKYMAP	
					g_mTelAlt_du=(int)(g_mTelAlt-dg_mZpos_syn+dg_mZpos0);//地平坐标高度返回赋值于显示
					g_mTelAlt_fen=(int)((g_mTelAlt-dg_mZpos_syn+dg_mZpos0-g_mTelAlt_du)*60.0);
					g_mTelAlt_miao=(int)((g_mTelAlt-dg_mZpos_syn+dg_mZpos0-g_mTelAlt_du-g_mTelAlt_fen/60.0)*3600.0);
				    
					if((g_mhandtrackAlt==1)&&(g_mGoto.m_nTEState==2))//最初指向时，望远镜与目标位置一致，手动调节后，就不一致了
					{

					  dg_mZpos0=g_mObjAlt-g_mTelAlt;


					  g_mTelAlt_du=g_mObjAlt_du;
					  g_mTelAlt_fen=g_mObjAlt_fen;
					  g_mTelAlt_miao=g_mObjAlt_miao;

					 
					}
		
			}
			else //地平式望远镜	赤道式用法
			{
				   	g_mObjHourA=g_mGoto.m_nHourAngle;
					g_mObjHourA_shi=(int)g_mObjHourA;//地平坐标方位返回赋值于方位显示
					g_mObjHourA_fen=(int)((g_mObjHourA-g_mObjHourA_shi)*60.0);
					g_mObjHourA_miao=(g_mObjHourA-g_mObjHourA_shi-g_mObjHourA_fen/60.0)*3600;
		
		
					g_mObjDec1=fabs(g_mGoto.m_nDeclination);							
					g_mObjDec_du1=(int)g_mObjDec1;//地平坐标高度返回赋值于方位显示
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

					if(g_mGoto.m_nAtitude>=0) //北半球
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
					else //南半球
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
					CurrentRa=g_mSidTime-(g_mTelRa-syn_mApos/15.0-dg_mSkyMapAzi/15.0);//返回望远镜位置给SKYMAP
					if(CurrentRa<0)
					{
					 CurrentRa=CurrentRa+24;
					}
					if(CurrentRa>24)
					{
					 CurrentRa=CurrentRa-24;
					}

					g_mTelRa_shi=(int)(g_mTelRa-syn_mApos/15.0+dg_mApos0);//地平坐标方位返回赋值于方位显示
					g_mTelRa_fen=(int)((g_mTelRa-syn_mApos/15.0+dg_mApos0-g_mTelRa_shi)*60.0);
					g_mTelRa_miao=(g_mTelRa-syn_mApos/15.0+dg_mApos0-g_mTelRa_shi-g_mTelRa_fen/60.0)*3600;
		         if((g_mhandtrackAzi==1)&&(g_mGoto.m_nTAState==2))//最初指向时，望远镜与目标位置一致，手动调节后，就不一致了	{
					{
					  dg_mApos0=g_mObjHourA-g_mTelRa;

					  g_mTelRa_shi=g_mObjHourA_shi;
					  g_mTelRa_fen=g_mObjHourA_fen;
					  g_mTelRa_miao=g_mObjHourA_miao;
		
					}
		
					//g_mTelDec=g_mTelDec-syn_mZpos;					
					CurrentDec=g_mTelDec-syn_mZpos-dg_mSkyMapAlt;//返回望远镜位置给SKYMAP


				    g_mTelDec_du=(int)(g_mTelDec-syn_mZpos+dg_mZpos0);//地平坐标高度返回赋值于方位显示
					g_mTelDec_fen=(int)((g_mTelDec-syn_mZpos+dg_mZpos0-g_mTelDec_du)*60.0);
					g_mTelDec_miao=(g_mTelDec-syn_mZpos+dg_mZpos0-g_mTelDec_du-g_mTelDec_fen/60.0)*3600;
			   if((g_mhandtrackAlt==1)&&(g_mGoto.m_nTEState==2))//最初指向时，望远镜与目标位置一致，手动调节后，就不一致了	{
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
		//调用菜单系统
		if(g_mcalpalnet==0)//没计算行星
		{
           			LCDRfrsh();
					//系统正在初始化
					DispEn(0,4,1,22,"System Initializing...");
					GetPlanetPos();//计算行星位置
					MenuDelay(1000);  
					//系统初始化化完毕					
					FBeep(1);
					LCDRfrsh();
					DispEn(0,4,1,22,"System Initialized    ");
					MenuDelay(1000);
					LCDRfrsh();
		            g_mcalpalnet=1;//计算行星	
		  }
		 DoMenu();
		 ///*************************


		//*********************************
		//望远镜自动校准
		if(!g_mGoto.m_nAlign)
		{
			FAutoAlign();
			g_mPauseTrack=0;//是不是暂停止起动的跟踪 0,不是，1是
		}
		//*********************************

//***************************************************************
   //*********************************
		//高速手动
	
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
//光电导星调节量
	//if(g_mSysInitGuide==0)//计算行星
	if(g_mTelStatus==2)//望远镜在跟踪状态方可导行
	{
		FGetAutoGuider();
		g_mGoto.m_nGuidMoveRa+=(m_GuiderRa+AGuiderRa)*0.00153;//光电导星赤经偏移量
		g_mGoto.m_nGuidMoveDec+=(m_GuiderDec+AGuiderDec)*0.00153;//光电导星赤纬偏移量
		//复位ASCOM软件导星参数
		AGuiderRa=0;
		AGuiderDec=0;
		//sprintf(s1,"%d:%.5f   %d:%.5f",AGuiderRa,g_mGoto.m_nGuidMoveRa,AGuiderDec,g_mGoto.m_nGuidMoveDec);
		//sprintf(s1,"%d::%d",AGuiderRa,AGuiderDec);
		//DispEn(0,2,1,22,&s1[0]);



		//g_mGoto.m_nGuidMoveRa+=AGuiderRa*0.00153;//光电导星赤经偏移量
		//g_mGoto.m_nGuidMoveDec+=AGuiderDec*0.00153;//光电导星赤纬偏移量
	}
//*********************************

//望远镜低速手动及微调
   
	 if(g_mTelescopeConType==1)//赤道式
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
	
		  switch(g_mHandSpeed)	//校准时调节
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
	else  //地平式
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
		  	switch(g_mHandSpeed)//校准时调节	
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
  g_mPointNewStarTracking=0;//指向新的星并跟踪
 }
		
 //***************************************************************
	  

 //**************************************************
//望远镜自动
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
 //望远镜回差校准,true正在执行,false没有	
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

					//g_mTelAzi=g_mTelAzi;//初始化向北
					//g_mTelAzi=g_mTelAzi+180;//初始化向南
					g_mTelAzi=g_mTelAzi+g_mGoto.m_nTescpAPZero;//初始化为任意位置

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
	
					//g_mTelAzi=g_mTelAzi;//初始化向北
					//g_mTelAzi=g_mTelAzi+180;//初始化向南
					g_mTelAzi=g_mTelAzi+g_mGoto.m_nTescpAPZero;//初始化为任意位置
	
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
	
					//g_mTelAlt=g_mTelAlt; //初始化向地坪
					//g_mTelAlt=90-g_mTelAlt;//初始化向天顶
					  g_mTelAlt=g_mGoto.m_nTescpEPZero-g_mTelAlt;//初始化为任意位置

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
	
					//g_mTelAlt=g_mTelAlt; //初始化向地坪
					//g_mTelAlt=90-g_mTelAlt;//初始化向天顶
					  g_mTelAlt=g_mGoto.m_nTescpEPZero-g_mTelAlt;//初始化为任意位置
 
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
	//望远镜回差校准
	//**************************************************

		
		  //*********************************************	
		  //极轴偏差显示设置
		  g_mPoleAxisEW=g_mTelError.mTSettingEW;
		  g_mPoleAxisNS=g_mTelError.mTSettingNS;
		  //*********************************************
		 
		  	
 		 //***********************************************
		 MenuDelay(2);
		 //***********************************************


		//************************************************
		//如果没有望远镜挂上，即没有通信，则循环周期加长
		if(!g_mTelescopeConType)
	    {
		   MenuDelay(50);
		}
//		if(calpalnet==0)//没计算行星
//		{
//            GetPlanetPos();//实时计算行星位置
//		    calpalnet=1;//计算行星
//		  }
		//MenuDelay(100);
		if(!g_mGoto.m_nStartStop)
		{
		  MenuDelay(100);
		 }
		 //程序循环主体完成
		//************************************************
	
		
	} 
	//**************************************************

}
//系统主程序结束
//*******************************************************

