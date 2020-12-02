//望远镜控制实现文件TelescopeControl.c
 
//*******************************************
//*******************************************
//**********望远镜控制函数实现 **************
//**********编者：柳光乾           **********
//**********2008年于云南天文台     **********
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


//$$$$$$$$$$$$$$$变量定义(全局变量)
GOTOAZDATA g_mGoto;//望远镜定位跟踪
TSETTING  g_mTelError;//望远镜装置产生的误差系

double dg_mApos;//方位跟踪时修正量(外围变量)
double dg_mZpos;//天顶跟踪时修正量(外围变量)

double dg_mApos0;//校准时方位跟踪时修正量(外围变量)
double dg_mZpos0;//校准时天顶跟踪时修正量(外围变量)


double ddg_mApos;//方位跟踪时修正增量(外围变量)
double ddg_mZpos;//天顶跟踪时修正增量(外围变量)

int g_mAposModify;//方位跟踪调节打开 0不调，1正调，-1反调
int g_mZposModify;//高度跟踪调节打开  0不调，1正调，-1反调


double dg_mApos_syn;//方位跟踪时的同步显示量
double dg_mZpos_syn;//天顶跟踪时的同步显示量


double syn_mApos;//方位跟踪时的同步量
double syn_mZpos;//天顶跟踪时的同步量

uint8 g_mstartOTAset;//开机时设置望远镜的初始指向

LOCATION  m_nLocation;//观测地位置，计算地平坐标用
STARRAD   m_nStarRAD;//观测目标位置，计算地平坐标用
STARAZ    m_nStarAZ;//观测地平坐标返回值，计算地平坐标用

bool g_mTelGoHome;//望远镜是否在归零状态

bool g_mEQHn;//赤道式望远镜目标是否在地平线

double mtest0;
double mtest1;

double mtesta0,mtestz0; 
double mtesta1,mtestz1; 
double mtesta2,mtestz2; 
double mtesta3,mtestz3;

  
extern uint8 BuzCount,BuzOnTime,BuzOffTime;
extern bool g_mGotoHandMoveOK;//望远镜是否可以手动了，望远镜要到定位误差小到一定时才能手动调节
extern char RTCms;//10毫秒计数值，每10ms由中断增1，每秒钟由秒中断清零
extern  uint8 g_mTelescopeConType;//0没有望远镜连接，1望远镜为赤道式，2望远镜为地平式，3有望远镜连接


extern int AGuiderRa,AGuiderDec; 

double g_mTempTelEpos;//望远镜高度零时位置

bool  g_mGotoBeep;

double g_mgwt;//世界时为零时的恒星时
float  g_mTelPeriodErrorA[200];	//方位赤经周期性误差记录
float  g_mTelPeriodErrorE[200];	//高度赤纬周期性误差记录

float  g_mStarAlign[28]; 
uint8   g_mAlignStarNum;

bool g_mLandMark;//是陆目标还是天空目标,false天空目标，true陆地目标
uint8 g_mgotostarttype;//0天空目标，1陆地目标

float g_mLandObjAzi	; //地平式望远镜陆地目标方位
float g_mLandObjAlt	; //地平式望远镜陆地目标高度


uint8 g_mPointNewStarTracking;//指向新的星并跟踪
bool g_mPointNewStar;//是否指向了新的一颗星，true指了,指了就存为最近观测的星，false没有指
float g_RecentRa,g_RecentDec;	 //最近观测星的赤经赤纬


float g_mAligndAzi,g_mAligndAlt;//	校准量

float g_mSidTime ;//地方恒星时

			  
uint8 g_mPauseTrack;//是不是暂停止起动的跟踪 0,不是，1是

uint8 g_mAlignShow;//校准过程中的显示设置


double  g_mTelRABack;  //赤经回差
double  g_mTelDecBack;  //赤纬回差

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
//@@@@@@@@@@@@@@@@@@望远镜函数实现
//@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@




//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@望远镜函数实现
//@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//赤道式望远镜定位跟踪函数
void GotoEQ()
{  		//***********************************************
		//变量定义
		LOCATION  m_nLocation;
		STARRAD   m_nStarRAD;
		STARAZ    m_nStarAZ;
		TSETTING m_ntsetting;
		ALIGNSTARAZ m_nalignstaraz;

		double m_nApout,m_nZpout;
		double m_nTempStarAzimuth;//（用来判断是否有正负穿越)

		double m_nSidTime;//地方恒星时 
		double m_nHourAngle	,m_nHourAngle1;//星的时角
		double m_nDeclination1;	 
		double m_nAzitrackpid;

	   if(g_mGoto.m_nStartStop)
	   { 
	   
	     if(!g_mTelGoHome)
	     { 
			//************************************************
			//数据传递
			m_nLocation.mLongitude=g_mGoto.m_nLongitude;
			m_nLocation.mAtitude=g_mGoto.m_nAtitude;
	
			//*************************************************
			//GOTO状态标记
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
	
		    //计算地方恒星时  
		      m_nSidTime=FCalSiderealTime(g_mGoto.m_nSysTimeType,g_mGoto.m_nNutation,g_mGoto.m_nLongitude);
			  g_mSidTime= m_nSidTime;
			//***********************************************

			 //*****************************************
			 FCalStarAEPos(m_nLocation,m_nStarRAD,g_mGoto.m_nSysTimeType,g_mGoto.m_nNutation,&m_nStarAZ);
			
			//***********************************************
			//计算目标时角
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
			//计算时角坐标改正
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
		  
		    //赤道式望远镜
			if(g_mTelescopeConType==1)
			{	
			       if(m_nLocation.mAtitude>=0) //北半球
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
					else //南半球
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
			//地平式望远镜赤道式用法
			  if(g_mTelescopeConType==2)
			  {	
		             
					 if(m_nLocation.mAtitude>=0) //北半球
					 {

						g_mGoto.m_nStarAPos0=g_mGoto.m_nStarAPos0+180;
						if(g_mGoto.m_nStarAPos0>360)
						{
						   g_mGoto.m_nStarAPos0=g_mGoto.m_nStarAPos0-360;
					    }

						g_mGoto.m_nStarEPos0=90.0-m_nDeclination1;
					}
					else //南半球
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
				//计算星的望远镜坐标系统位置 
			    g_mGoto.m_nStarAPosT=g_mGoto.m_nStarAPos0;
			    g_mGoto.m_nStarEPosT=g_mGoto.m_nStarEPos0;				
	
			//**************************************************
			//望远镜在跟踪时，是否有手动调节
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
	       	//望远镜跟踪时的手动调节量
			
           
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
         //判断星是否有正负穿越
         if(g_mGoto.m_nStarAPos-m_nTempStarAzimuth>180)
		 {
			 g_mGoto.m_nTCrossZeroP=true;//望远镜在运行时有正穿越
		 }
		 else if(g_mGoto.m_nStarAPos-m_nTempStarAzimuth<-180)
		 {

	         g_mGoto.m_nTCrossZeroN=true;//望远镜在运行时有负穿越
		 }
         //正负穿超越时的坐标处理

		 if(g_mGoto.m_nTCrossZeroP)
		 {
			 g_mGoto.m_nStarAPos=g_mGoto.m_nStarAPos-360;
		 }
		 if(g_mGoto.m_nTCrossZeroN)
		 {
			 g_mGoto.m_nStarAPos=g_mGoto.m_nStarAPos+360;
		 }
		//**************************************************
        //望远镜定位时的最近方位(方位上的最短距离)判断
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
		 //正负方向定位时位置处理
		 if(g_mGoto.m_nTPointDirect==-1)
		 {
			 g_mGoto.m_nStarAPos=g_mGoto.m_nStarAPos-360;
		 }
		 if(g_mGoto.m_nTPointDirect==1)
		 {
			 g_mGoto.m_nStarAPos=g_mGoto.m_nStarAPos+360;
		 }*/

        //***********************************************
	    //判断望远镜最近的定位跟踪方向

			
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
	
		//读取望远镜的位置
		//FReadTelescopePos(&(g_mGoto.m_nTescpAPos),&(g_mGoto.m_nTescpEPos));//读取望远镜的反馈位置	
		//GF_ReadAZPos(); 
		//g_mGoto.m_nTescpAPos=g_mTapos;
		//g_mGoto.m_nTescpEPos=g_mTzpos;
         
		//望远镜的位置已经从串口中断零获取
		
		
		g_mGoto.m_nAPosError=g_mGoto.m_nStarAPos-g_mGoto.m_nTescpAPos;//方位置误差（星的位置-望远镜位置),以度表示
		g_mGoto.m_nEPosError=g_mGoto.m_nStarEPos-g_mGoto.m_nTescpEPos;//高度置误差（星的位置-望远镜位置),以度表示
		
	
		//mtest0=g_mGoto.m_nEPosError;
	

	
				
	  	//************************************************
		//望远镜在定位加速时的处理
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
		//判断跟踪误差是否过大，过大时，用定位来处理跟踪
		if((fabs(g_mGoto.m_nAPosError)>0.11)&&(g_mGoto.m_nTAState==2))
		{
			g_mGoto.m_nTAState=0;
			if(g_mHandSpeed>6)
			{
			   g_mGotoBeep=true;//蜂鸣频率高
			 }
		}
		
		if((fabs(g_mGoto.m_nEPosError)>0.11)&&(g_mGoto.m_nTEState==2))
		{
			g_mGoto.m_nTEState=0;
			if(g_mHandSpeed>6)
			{
			  g_mGotoBeep=true;	//蜂鸣频率高
			 }
		}

	   //蜂鸣频率低
        if((fabs(g_mGoto.m_nAPosError)>10)||(fabs(g_mGoto.m_nEPosError)>5))
		{
			g_mGotoBeep=true;
		}

		
		//************************************************
		
		
		
		//************************************************
		//根据位置误差，方位是否进入减速状态
		if((fabs(g_mGoto.m_nAPosError)<=15.0)&&((g_mGoto.m_nTAState==0)||(g_mGoto.m_nTAState==1)))//进入一级减速区
		{  
			g_mGoto.m_nTAState=1;//设置望远镜的状态为减速状态
			//一级减速区的速度和加速度设置
			
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


			if(fabs(g_mGoto.m_nAPosError)<=10.0)//进入二级减速区
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

			if(fabs(g_mGoto.m_nAPosError)<=5.0)//进入三级减速区
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
			if(fabs(g_mGoto.m_nAPosError)<=3.0)//进入四级减速区
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
			
			if(fabs(g_mGoto.m_nAPosError)<=1.0)//进入五级减速区
			{
				g_mGoto.m_nTescpASpeed=50+fabs(g_mGoto.m_nStarASpeed);
			}
			if(fabs(g_mGoto.m_nAPosError)<=0.1)//进入六级级减速区
			{
				g_mGoto.m_nTescpASpeed=10+fabs(g_mGoto.m_nStarASpeed);
			}
			if(fabs(g_mGoto.m_nAPosError)<=0.01)//进入跟踪区
			{
				g_mGoto.m_nTAState=2;///设置望远镜方位的状态为跟踪
			//	m_tempRAstatus=0;	
			}
		}
		//************************************************
		
		//************************************************
		//跟踪高度误差，是否进入高度减速区
		if((fabs(g_mGoto.m_nEPosError)<=15.0)&&((g_mGoto.m_nTEState==0)||(g_mGoto.m_nTEState==1)))//进入一级减速区
		{
			g_mGoto.m_nTEState=1;///设置望远镜的状态
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
		    if(fabs(g_mGoto.m_nEPosError)<=10.0)//进入二级减速区
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

			if(fabs(g_mGoto.m_nEPosError)<=5.0)//进入三级减速区
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
			if(fabs(g_mGoto.m_nEPosError)<=3.0)//进入三级减速区
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
			if(fabs(g_mGoto.m_nEPosError)<=1.0)//进入四级减速区
			{
			
				g_mGoto.m_nTescpESpeed=50+fabs(g_mGoto.m_nStarESpeed);

			}
			if(fabs(g_mGoto.m_nEPosError)<=0.1)//进入五级减速区
			{
				
				g_mGoto.m_nTescpESpeed=20+fabs(g_mGoto.m_nStarESpeed);

			}

			if(fabs(g_mGoto.m_nEPosError)<=0.05)//进入跟踪
			{
				g_mGoto.m_nTEState=2;///设置望远镜的高度跟踪状态	
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
		//退出望远镜归零 
	   if((g_mGoto.m_nTAState==2)&&(g_mGoto.m_nTEState==2)&&g_mTelGoHome)
	   { 
	   	 g_mGoto.m_nStartStop=false;//表明望远镜归位了，退出
		 g_mGoto.m_nGoto=false;
		 g_mGotoHandMoveOK=false;
	     FBeep(1);
		 g_mTelStatus=100;
	   }
	  	 
		//************************************************
		
		//************************************************
		//望远镜的方位跟踪
		if(g_mGoto.m_nTAState==2)
		{   
			m_nApout=FPointStarAlgorithm(2,1,g_mGoto.m_nAPosEIZero,g_mGoto.m_nAPosError,g_mGoto.m_nStarASpeed);
		}
		//**********************************************
		
		//**********************************************
		//望远镜的高度跟踪
		if(g_mGoto.m_nTEState==2)///系统在跟踪状态就加入位置环
		{   
			m_nZpout=FPointStarAlgorithm(g_mGoto.m_nTescpType,2,g_mGoto.m_nEPosEIZero,g_mGoto.m_nEPosError,g_mGoto.m_nStarESpeed);
		}
		//************************************************
		//最后的控制输出
		if(g_mGoto.m_nTAState==2)//跟踪时，输出跟踪的速度//否则输定位速度
		{  
		
		   
		   	if(g_mAposModify==0)
			{
			   m_nAzitrackpid=100000.0*m_nApout*m_nApout*m_nApout*m_nApout*m_nApout*m_nApout-0.05;
			   //mtest0=m_nAzitrackpid;
			   g_mGoto.m_nTescpASpeed=fabs(g_mGoto.m_nStarASpeed)/9.5+m_nAzitrackpid;	//该值=0.378赤道式跟踪稳定9.5
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
		if(g_mGoto.m_nTEState==2)//跟踪时，输出跟踪的速度//否则输定位速度
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
		//向望远镜输出控制信号
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


		  // g_mGoto.m_nUnderhorizon=false;//置在地平线下的标志为假
		  
		}
		else
		{
	    	FDriveTelescope(0,0);
			g_mGoto.m_nStartStop=false;//望远镜在地平线下，停止跟踪
			g_mGoto.m_nGoto=false;
            g_mGoto.m_nUnderhorizon=true;//置在地平线下的标志为假
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
//地平式望远镜定位跟踪函数
void GotoAZ()
{   
		//***********************************************
		//变量定义
		LOCATION  m_nLocation;
		STARRAD   m_nStarRAD;
		STARAZ    m_nStarAZ;
		TSETTING m_ntsetting;
		ALIGNSTARAZ m_nalignstaraz;

		double m_nApout,m_nZpout;
		double m_nTempStarAzimuth;//（用来判断是否有正负穿越)

		double m_nSidTime;//地方恒星时 
		double m_nHourAngle	;//星的时角

				
	   if(g_mGoto.m_nStartStop)
	   { 
	   
	     if(!g_mTelGoHome)
	     { 
			//************************************************
			//数据传递
			m_nLocation.mLongitude=g_mGoto.m_nLongitude;
			m_nLocation.mAtitude=g_mGoto.m_nAtitude;
	
			//*************************************************
			//GOTO状态标记
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
		
	      		//方位上次的坐标保存
				m_nTempStarAzimuth=g_mGoto.m_nStarAPos;
		
		        if(!g_mLandMark)//是陆目标还是天空目标,false天空目标，true陆地目标
				{//************************************************
					  //计算星的地平坐标
	
			        FCalStarAEPos(m_nLocation,m_nStarRAD,g_mGoto.m_nSysTimeType,g_mGoto.m_nNutation,&m_nStarAZ);
				
				 		
					g_mGoto.m_nStarAPos0=m_nStarAZ.mASzimuth;
					g_mGoto.m_nStarEPos0=m_nStarAZ.mZenith;

				//	mtesta0=g_mGoto.m_nStarAPos0;
				//	mtestz0=g_mGoto.m_nStarEPos0;
	
				
				   
			        g_mGoto.m_nStarASpeed=m_nStarAZ.mAzimuthSpeed;
				    g_mGoto.m_nStarESpeed=m_nStarAZ.mZenithSpeed;
					
					
				
					//**************************************************
					//计算星的位置改正
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
	
						
					//计算大气折射
					//g_mGoto.m_nAirR=FAirRefraction(g_mGoto.m_nAirT,g_mGoto.m_nAirP,g_mGoto.m_nStarEPos0);					
					//g_mGoto.m_nStarEPosT=g_mGoto.m_nStarEPosT-g_mGoto.m_nAirR;


				//	mtesta2=g_mGoto.m_nStarAPosT;
				//	mtestz2=g_mGoto.m_nStarEPosT;
				}
			
		   
			//望远镜在跟踪时，是否有手动调节
			//if(g_mGoto.m_nTAState==2)
			//{
				g_mGoto.m_nTAHandMovePos=dg_mApos;
				
		//	}
			
			//if(g_mGoto.m_nTEState==2)
		//	{
				g_mGoto.m_nTEHandMovePos=-1.0*dg_mZpos;
				
		//	}
		 // mtest1=g_mGoto.m_nTEHandMovePos;



		   //以下两句是将其望远镜初始化向北方,不加就是指向天顶
		   //g_mGoto.m_nStarAPosT=g_mGoto.m_nStarAPosT+180;
		   //g_mGoto.m_nStarEPosT=g_mGoto.m_nStarEPosT-90;
		   ///////////////////////////////////////////////////////
		   //以下两句为任意位置的初始化，星位置怎么转为望远镜原始的坐标值

		   g_mGoto.m_nStarAPosT=(g_mGoto.m_nStarAPosT+180)-g_mGoto.m_nTescpAPZero;//方位-零点，（180+南方位）-零点
		   g_mGoto.m_nStarEPosT=g_mGoto.m_nTescpEPZero-(90-g_mGoto.m_nStarEPosT); //零点-高度，零点-（90-天顶距）



		   	if(g_mLandMark)//是陆目标还是天空目标,false天空目标，true陆地目标
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
	       	//望远镜跟踪时的手动调节量
			
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
         //判断星是否有正负穿越
         if(g_mGoto.m_nStarAPos-m_nTempStarAzimuth>180)
		 {
			 g_mGoto.m_nTCrossZeroP=true;//望远镜在运行时有正穿越
		 }
		 else if(g_mGoto.m_nStarAPos-m_nTempStarAzimuth<-180)
		 {

	         g_mGoto.m_nTCrossZeroN=true;//望远镜在运行时有负穿越
		 }
         //正负穿超越时的坐标处理

		 if(g_mGoto.m_nTCrossZeroP)
		 {
			 g_mGoto.m_nStarAPos=g_mGoto.m_nStarAPos-360;
		 }
		 if(g_mGoto.m_nTCrossZeroN)
		 {
			 g_mGoto.m_nStarAPos=g_mGoto.m_nStarAPos+360;
		 }
		//**************************************************
        //望远镜定位时的最近方位(方位上的最短距离)判断
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
		 //正负方向定位时位置处理
		 if(g_mGoto.m_nTPointDirect==-1)
		 {
			 g_mGoto.m_nStarAPos=g_mGoto.m_nStarAPos-360;
		 }
		 if(g_mGoto.m_nTPointDirect==1)
		 {
			 g_mGoto.m_nStarAPos=g_mGoto.m_nStarAPos+360;
		 }*/

        //***********************************************
	    //判断望远镜最近的定位跟踪方向
    	/*while(g_mGoto.m_nStarAPos-g_mGoto.m_nTescpAPos>180)
		{
			g_mGoto.m_nStarAPos=g_mGoto.m_nStarAPos-360;
		}
		while(g_mGoto.m_nStarAPos-g_mGoto.m_nTescpAPos<-180)
		{
			g_mGoto.m_nStarAPos=g_mGoto.m_nStarAPos+360;
		}*/
        //***********************************************
	
		//读取望远镜的位置
		//FReadTelescopePos(&(g_mGoto.m_nTescpAPos),&(g_mGoto.m_nTescpEPos));//读取望远镜的反馈位置	
		//GF_ReadAZPos(); 
		//g_mGoto.m_nTescpAPos=g_mTapos;
		//g_mGoto.m_nTescpEPos=g_mTzpos;
         
		//望远镜的位置已经从串口中断零获取
		
		
		g_mGoto.m_nAPosError=g_mGoto.m_nStarAPos-g_mGoto.m_nTescpAPos;//方位置误差（星的位置-望远镜位置),以度表示
		g_mGoto.m_nEPosError=g_mGoto.m_nStarEPos-g_mGoto.m_nTescpEPos;//高度置误差（星的位置-望远镜位置),以度表示
		
	//	mtest0=g_mGoto.m_nAPosError*3600.0;//3600.0*(g_mGoto.m_nTescpAPos-mtest1);//g_mGoto.m_nAPosError*3600.0;
		//mtest1=g_mGoto.m_nEPosError*3600.0;//g_mGoto.m_nTescpAPos;//g_mGoto.m_nEPosError*3600.0;
	
		//************************************************
		//望远镜在定位加速时的处理
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

		//判断跟踪误差是否过大，过大时，用定位来处理跟踪
		if(fabs(g_mGoto.m_nStarASpeed)>100)
		{
				if((fabs(g_mGoto.m_nAPosError)>fabs(g_mGoto.m_nStarASpeed)*0.01)&&(g_mGoto.m_nTAState==2))
				{
					g_mGoto.m_nTAState=0;
					if(g_mHandSpeed>6)
					{
					  g_mGotoBeep=true;	//蜂鸣频率高
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
					  g_mGotoBeep=true;	//蜂鸣频率高
					 }
				}
		}
				
		if((fabs(g_mGoto.m_nEPosError)>0.1)&&(g_mGoto.m_nTEState==2))
		{
			       g_mGoto.m_nTEState=0;
					if(g_mHandSpeed>6)
					{
					  g_mGotoBeep=true;	//蜂鸣频率高
					 }
		}
		 
	   //蜂鸣频率低
        if((fabs(g_mGoto.m_nAPosError)>10)||(fabs(g_mGoto.m_nEPosError)>5))
		{
			g_mGotoBeep=true;
		}



		//************************************************
		
		//************************************************
		//根据位置误差，方位是否进入减速状态
		if((fabs(g_mGoto.m_nAPosError)<=15.0)&&((g_mGoto.m_nTAState==0)||(g_mGoto.m_nTAState==1)))//进入一级减速区
		{  
			g_mGoto.m_nTAState=1;//设置望远镜的状态为减速状态
			//一级减速区的速度和加速度设置
			g_mGoto.m_nTescpASpeed=300+fabs(g_mGoto.m_nStarASpeed)/10.0;
			if(fabs(g_mGoto.m_nAPosError)<=10.0)//进入二级减速区
			{
				g_mGoto.m_nTescpASpeed=200+fabs(g_mGoto.m_nStarASpeed)/10.0;
			}
			if(fabs(g_mGoto.m_nAPosError)<=5.0)//进入三级减速区
			{
				
				g_mGoto.m_nTescpASpeed=100+fabs(g_mGoto.m_nStarASpeed)/10.0;
			}
			if(fabs(g_mGoto.m_nAPosError)<=3.0)//进入四级减速区
			{
				g_mGoto.m_nTescpASpeed=50+fabs(g_mGoto.m_nStarASpeed)/10.0;
			}

		    if(fabs(g_mGoto.m_nAPosError)<=1.0)//进入五级减速区
			{
				g_mGoto.m_nTescpASpeed=10+fabs(g_mGoto.m_nStarASpeed)/10.0;
			}
			if(fabs(g_mGoto.m_nAPosError)<=0.1)//进入六级级减速区
			{
				g_mGoto.m_nTescpASpeed=5+fabs(g_mGoto.m_nStarASpeed)/10.0;
			}
			if(fabs(g_mGoto.m_nAPosError)<=0.05)//进入跟踪区
			{
				g_mGoto.m_nTAState=2;///设置望远镜方位的状态为跟踪	
			}
			if(fabs(g_mGoto.m_nStarASpeed)>50)
			{ 
				 if(fabs(g_mGoto.m_nAPosError)<=0.001*fabs(g_mGoto.m_nStarASpeed))//进入跟踪区
				{	
					   g_mGoto.m_nTAState=2;///设置望远镜方位的状态为跟踪
				}
			}
		}
		//************************************************
		
		//************************************************
		//跟踪高度误差，是否进入高度减速区
		if((fabs(g_mGoto.m_nEPosError)<=15.0)&&((g_mGoto.m_nTEState==0)||(g_mGoto.m_nTEState==1)))//进入一级减速区
		{
			g_mGoto.m_nTEState=1;///设置望远镜的状态
			g_mGoto.m_nTescpESpeed=130+fabs(g_mGoto.m_nStarESpeed);
		
		    if(fabs(g_mGoto.m_nEPosError)<=10.0)//进入二级减速区
			{
			
				g_mGoto.m_nTescpESpeed=100+fabs(g_mGoto.m_nStarESpeed);
			}

			if(fabs(g_mGoto.m_nEPosError)<=5.0)//进入三级减速区
			{
				
				g_mGoto.m_nTescpESpeed=80+fabs(g_mGoto.m_nStarESpeed);
			}
			if(fabs(g_mGoto.m_nEPosError)<=3.0)//进入三级减速区
			{
			
				g_mGoto.m_nTescpESpeed=60+fabs(g_mGoto.m_nStarESpeed);
			}
			if(fabs(g_mGoto.m_nEPosError)<=1.0)//进入四级减速区
			{
				g_mGoto.m_nTescpESpeed=30+fabs(g_mGoto.m_nStarESpeed);

			}
			if(fabs(g_mGoto.m_nEPosError)<=0.1)//进入五级减速区
			{
				
				g_mGoto.m_nTescpESpeed=10+fabs(g_mGoto.m_nStarESpeed);

			}

			if(fabs(g_mGoto.m_nEPosError)<=0.05)//进入跟踪
			{
			    
				g_mGoto.m_nTEState=2;///设置望远镜的高度跟踪状态
				
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
	  
		//退出望远镜归零 
	   if((g_mGoto.m_nTAState==2)&&(g_mGoto.m_nTEState==2)&&g_mTelGoHome)
	   { 
	   	  g_mGoto.m_nStartStop=false;//表明望远镜归位了，退出
		  g_mGotoHandMoveOK=false;
	      FBeep(1);
	   	  g_mTelStatus=100;
	   }
	  
	 
		//************************************************
		
		//************************************************
		//望远镜的方位跟踪
		if(g_mGoto.m_nTAState==2)
		{   
			m_nApout=FPointStarAlgorithm(g_mGoto.m_nTescpType,1,g_mGoto.m_nAPosEIZero,g_mGoto.m_nAPosError,g_mGoto.m_nStarASpeed);
		}
		//**********************************************
		
		//**********************************************
		//望远镜的高度跟踪
		if(g_mGoto.m_nTEState==2)///系统在跟踪状态就加入位置环
		{   
			m_nZpout=FPointStarAlgorithm(g_mGoto.m_nTescpType,2,g_mGoto.m_nEPosEIZero,g_mGoto.m_nEPosError,g_mGoto.m_nStarESpeed);
		}
		//************************************************
		//最后的控制输出  
	

		if(g_mGoto.m_nTAState==2)//跟踪时，输出跟踪的速度//否则输定位速度
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
		if(g_mGoto.m_nTEState==2)//跟踪时，输出跟踪的速度//否则输定位速度
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
		//向望远镜输出控制信号
			if(!g_mTelGoHome)
			{
				if(g_mGoto.m_nStarEPos0<90)
				{
		
				    FDriveTelescope(g_mGoto.m_nTescpASpeed,g_mGoto.m_nTescpESpeed);
	   
		   	       if(g_mLandMark)//是陆目标还是天空目标,false天空目标，true陆地目标
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
					   g_mGoto.m_nStartStop=false;//表明望远镜归位了，退出
					   g_mTelStatus=100;
					   g_mGotoHandMoveOK=false;
					   g_mgotostarttype=0;
					 }

					 if(g_mgotostarttype==0)
					 {
					   FDriveTelescope(0,0);
					   g_mGoto.m_nStartStop=false;//表明望远镜归位了，退出
					   g_mTelStatus=100;
					   g_mGotoHandMoveOK=false;
					 }
		
			       }  
		
				 // FDriveTelescopeNew();
				  // if(!g_mLandMark )
				 //  {
				      g_mGoto.m_nUnderhorizon=false;//置在地平线下的标志为假
				//	}
				  
				}
				else
				{
					if(!g_mLandMark )
				   {
					g_mGoto.m_nStartStop=false;//望远镜在地平线下，停止跟踪
		            g_mGoto.m_nUnderhorizon=true;//置在地平线下的标志为真
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
						   g_mGoto.m_nStartStop=false;//表明望远镜归位了，退出
						   g_mTelStatus=100;
						   g_mGotoHandMoveOK=false;
						   g_mgotostarttype=0;
						 }
	
						 g_mGoto.m_nUnderhorizon=false;//置在地平线下的标志为假
		
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
	 //跟踪闭环时间
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
//获取系统时间
void GetLocalTime(SYSTEMTIME *time)
{
    uint32  RTCtime;
	uint32  RTCdate;
	RTCtime = RTCtimeRead; // 读取完整时钟寄存器
	RTCdate = RTCdateRead;	// 读取完整日期寄存器
	// 取得年值
     time->wYear = (RTCdate>>16)&0xFFF; 	 
	// 取得月值
	time->wMonth = (RTCdate>>8)&0x0F;  
	// 取得日值
	time->wDay = RTCdate&0x1F;            
	// 显示日值;      
	// 取得时的值
	time->wHour = (RTCtime>>16)&0x1F;
	// 取得分的值		
	time->wMinute= (RTCtime>>8)&0x3F;	
	// 取得秒的值	
	time->wSecond = RTCtime&0x3F;
	//取得毫秒
	time->wMilliseconds=RTCms*10;

   if(g_mDaylight)//是否采用夏令时,true采用，false不用采
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
//计算地方恒星时
double FCalSiderealTime(int fSysTimeType,bool fNutation ,double fLongitude)
{
	///*************************************************
	//数据变量定义
	//double PI=3.14159265359;
	double m_njd;//儒略日
	double m_ncn;//世纪数
	double m_nUTST;//系统当前世界时下的恒星时
	double m_nSidTime;//计算地方恒星时
	
	SYSTEMTIME m_nSysTime;//系统时间
	SYSTEMTIME m_nBJTime;//北京时间
	SYSTEMTIME m_nUTime;//世界时
	//临时变量
	double m_ntempa;
	double m_ntempb;
	double m_ntempc;

	double tempe0,tempe;//度
	//*********************
		double tempq;//度
		double templm,templs;//度 	
		double tempf;//度 	
		double tempdd;//度 	
		double tempdtaf,tempdtae;//角秒
	double PI;
	PI=3.1415927;
	///*************************************************
	
	///*************************************************
	//获取系统时间
	GetLocalTime(&m_nSysTime);
	///*************************************************
	switch(fSysTimeType)
	{
	case 1://如果系统时间为北京时间
		///*************************************************
		//得到北京时间
		m_nBJTime=m_nSysTime;
		///*************************************************
		
		///*************************************************
		//把北京时转化为世界时
		m_nUTime=m_nBJTime;
		if ((m_nBJTime.wHour-g_mGoto.m_nTimeZone)<0)  //东半球
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
		else if((m_nBJTime.wHour-g_mGoto.m_nTimeZone)>24) //西半球
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
	case 2://如果系统时间为世界时
		m_nUTime=m_nSysTime;
		break;
	default:break;
	}
		
	///*******************************************************
    //计算儒略日
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
    //返回儒略日，以找行星
	g_mGoto.m_nJday=m_njd;
	///*******************************************************
	//********************************************************
    //计算从J2000年来的世纪数,2000 January 1.5 TD(世界时)
	m_ncn=(m_njd-2451545)/36525.0;
	 
	//*********************************************************
	//*******************************************************
	//计算任意世界时的地方平恒星时	
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
	//计算零度恒星时
	m_njd=(int)(365.25*(m_nUTime.wYear+4716))+(int)(30.6001*(m_nUTime.wMonth+1))+m_nUTime.wDay+m_ntempb-1524.5;
	//返回儒略日，以找行星
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
//    //加章动改正
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
//		tempdtae=tempdtae/3600.0;//度
//		tempe0=23.43929111111-46.8150*m_ncn/3600.0-0.00059*m_ncn*m_ncn/3600.0+0.001813*m_ncn*m_ncn*m_ncn/3600.0;
//		tempe=tempe0+tempdtae;//度
//		tempdtae=tempdtaf*cos(tempe*PI/180.0)/15.0;//角秒
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
    //计算地方恒星时
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
	//计算目标时角
	
   //***********************************************************
		
	return m_nSidTime;
}


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//计算星的地平坐标
void FCalStarAEPos(LOCATION floct,STARRAD fstar,int fSysTimeType,bool fNutation,STARAZ *fstaraz)
{
	
	//***********************************************
	//变量定义
	double PI=3.14159265359;
	double m_nLongitude;//观测地经度,以度表示
    double m_nAtitude;//观测地纬度，以度表示
	double m_nRightAscension;//观测目标赤经,以时表示
	double m_nDeclination;//观测目标赤纬,以度表示
	double m_nHourAngle;//目标时角,以时表示
    double m_nSidTime;//地方恒星时,以时表示
	//临时参数
	double m_ntempzz,m_ntempaa;
	double m_ntempAspd,m_ntempZspd;
	double m_nAacc,m_nZacc;
	//***********************************************
	TSETTING m_ntsetting1;
	ALIGNSTARAZ m_nalignstaraz1;
	
	//************************************************
	//参数传递
    m_nLongitude=floct.mLongitude;
	m_nAtitude=floct.mAtitude;
    m_nRightAscension=fstar.mRightAscension;
    m_nDeclination=fstar.mDeclination;
	
	//************************************************
	//***********************************************
    //计算地方恒星时
    m_nSidTime=FCalSiderealTime(fSysTimeType,fNutation,m_nLongitude);
	//***********************************************
	
	//***********************************************
	//计算目标时角
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
	//参数转化为弧度表示
	m_nHourAngle=m_nHourAngle*PI*15.0/180.0;//（时角坐标，以弧度表示）
	m_nAtitude=m_nAtitude*PI/180.0;
	m_nDeclination=m_nDeclination*PI/180.0;
	//***********************************************
	
    //***********************************************
	//计算地平坐标

	m_ntempzz=acos(sin(m_nAtitude)*sin(m_nDeclination)+cos(m_nAtitude)*cos(m_nDeclination)*cos(m_nHourAngle));

	m_ntempaa=acos((sin(m_nAtitude)*cos(m_nDeclination)*cos(m_nHourAngle)-cos(m_nAtitude)*sin(m_nDeclination))/sin(m_ntempzz));

	if(m_nHourAngle>PI)
	{
		m_ntempaa=-1.0*m_ntempaa;
	}

	m_ntempAspd=15.04*((sin(m_nAtitude)*sin(m_ntempzz)+cos(m_ntempzz)*cos(m_ntempaa)*cos(m_nAtitude))/sin(m_ntempzz));
	   
	m_ntempZspd=15.04*cos(m_nAtitude)*sin(m_ntempaa); 
      
	//*************************************************
	///返回参数	
	fstaraz->mASzimuth=m_ntempaa*57.295779513082320876798154814105;
	fstaraz->mANzimuth=180.0+m_ntempaa*57.295779513082320876798154814105;
	fstaraz->mAzimuthSpeed=m_ntempAspd;
	fstaraz->mZenith=m_ntempzz*57.295779513082320876798154814105;
	fstaraz->mAtitude=90.0-m_ntempzz*57.295779513082320876798154814105;
	fstaraz->mZenithSpeed=m_ntempZspd;
	fstaraz->mAtitudeSpeed=-m_ntempZspd;  
	//****************************************
   //望远镜校准后的坐标改正
   	
	//**************************************************
	//计算星的位置改正
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
//计算赤道坐标
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

//计算星校准后的地平位置
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
//计算星校准后的赤道位置
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
//计算大气蒙气差
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
//   // R=c*1.02/tan((h+10.3/(h+5.11))*kpi);//角分
//	R=0.017*c/tan((h+10.3/(h+5.11))*kpi);//度
//    //dR=-0.06*sin((14.7*R/60+3)*kpi)*60
//	return R;
//}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

void FReadTelescopePos(double *fAZimuth,double *fAltitude)//读取望远镜的反馈位置
{

	 *fAZimuth=g_mGoto.m_nStarAPosT-0.0028;
	 *fAltitude=g_mGoto.m_nStarEPosT-0.0028;
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//望远镜控制PID算法
double FPointStarAlgorithm (int fTescpType,int fAxis,double fPosEIZero,double fPosError,double fObjectSpeed)
   {
	   //***************************************
	   //变量定义
	   double m_nPIOut,m_nPOut,m_nIOut;//PI输出
	   double m_nAp,m_nZp;//误差比例系数
	   double m_nApi,m_nZpi;//误差积分系数
	   //***************************************
	   
	   
	   //***************************************
	   //根据望远镜类型设置PI参数
	   switch(fTescpType)
	   {
	   case 1://云台164
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
	   //选望远镜的轴，1方位轴，2 高度轴
	   switch(fAxis)
	   {
	   case 1:
		   //********************
		   //方位误差比例
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
		   /*if((g_mGoto.m_nAPosError*Ai)<0)//根据误差和积分，让积分反相
		   {
		   Ai=0.0;
		   }
		   
			 Ai=Ai+Api*g_mGoto.m_nAPosError; //计算位置误差积分
			 if(Ai>10)           //积分饱和限制
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
		   m_nPOut=fPosError*m_nZp;//计算比例，
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
		   
		   /*if((g_mGoto.m_nEPosError*Zi)<0)//根据误差和积分，让积分反相
		   {
		   Zi=0.0;
		   }
		   Zi=Zi+Zpi*g_mGoto.m_nEPosError; //计算位置误差积分
		   if(Zi>10.0)           //积分饱和限制
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
	   //返回结果
	   m_nPIOut=m_nPOut+m_nIOut;
	   return m_nPIOut;
	   //************************************************************
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//望远镜起动GOTO
void FStartGoto()
{   
   
    FHandPowerTelescope();
    g_mGoto.m_nStartStop=true;
	g_mTelGoHome=false;//望远镜不要处在归零状态
	g_mGotoHandMoveOK=false; //望远镜不一开始不可以进入手动状态
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
//望远镜停止GOTO
void FStopGoto()
{
	g_mGoto.m_nStartStop=false;
	g_mTempTelEpos=10000.0;//望远镜高度零时位置
}

//望远镜暂停GOTO
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

//望远镜继续GOTO
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
	  g_mHandSpeed=3;	//默认跟踪时手动调节速度为3档	
 
 	  g_mhandtrackAzi=1;//最初指向时，望远镜与目标位置一致，手动调节后，就不一致了
	  g_mhandtrackAlt=1;//最初指向时，望远镜与目标位置一致，手动调节后，就不一致了

}


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//指向新目标
void FPointNewStar(double fRightAscension,double fDeclination)
{
	g_mGoto.m_nRightAscension=fRightAscension;//赤经(0-24小时)
	g_mGoto.m_nDeclination=fDeclination;//赤纬(-90到90度)

	g_mPointNewStar=true;//是否指向了新的一颗星，true指了,指了就存为最近观测的星，false没有指
    
  	g_RecentRa=fRightAscension;//最近观测星的赤经
	g_RecentDec=fDeclination;//最近观测星的赤纬

   	g_mPointNewStarTracking=1;//指向新的星并跟踪
	g_mstartOTAset=1;//开机时设置望远镜的初始指向

	g_mGoto.m_nTCrossZeroP=false;//望远镜在运行时是否有正穿越
	g_mGoto.m_nTCrossZeroN=false;//望远镜在运行时是否有负穿越
	g_mGoto.m_nTPointDirect=0;//望远镜定位不变向

	//dg_mApos=dg_mApos_syn;
    //dg_mZpos=-dg_mZpos_syn;

	dg_mApos=syn_mApos;//初始化等于同步量
    dg_mZpos=syn_mZpos;//初始化等于同步量

	
//
//	syn_mApos=0;//方位跟踪时的同步量
//  syn_mZpos=0;//天顶跟踪时的同步量

	//g_mLandMark=false;

	//g_mLandObjAzi=0;
	//g_mLandObjAlt=0;
	
	g_mGotoBeep=true;
	g_mgotostarttype=0;
	FStartGoto();//起动望远镜


    g_mPauseTrack=0;//是不是暂停止起动的跟踪 0,不是，1是
	g_mHandSpeed=3;	//默认跟踪时手动调节速度为3档

	 g_mhandtrackAzi=1;//最初指向时，望远镜与目标位置一致，手动调节后，就不一致了
	 g_mhandtrackAlt=1;//最初指向时，望远镜与目标位置一致，手动调节后，就不一致了


	 g_mGoto.m_nGuidMoveRa=0;//上次导行赤经偏差置0
	 g_mGoto.m_nGuidMoveDec=0;//上次导行赤纬偏差置0

}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//设置观测地理位置
void FSetLocation(double fLongitude,double fAtitude)
{
	g_mGoto.m_nLongitude=fLongitude;

    g_mGoto.m_nAtitude=fAtitude;
}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//望远镜自动校准对星
void FAutoAlign()
{   
	int m_nstarnum;
    CALSTARAZ StarsPos;
    TSETTING TSetting;
	m_nstarnum=0;
	
	if(g_mGoto.m_nAlignAdjustNum<g_mGoto.m_nAlignStarNum)
	{   
		g_mGoto.m_nTCrossZeroP=false;//望远镜在运行时是否有正穿越
		g_mGoto.m_nTCrossZeroN=false;//望远镜在运行时是否有负穿越
		g_mGoto.m_nTPointDirect=0;//望远镜定位不变向
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
		StarsPos.mANzimuth1=g_mGoto.m_nANzimuth1;//方位，正北为零，东负西正，0度到360度
		StarsPos.mAtitude1=g_mGoto.m_nAtitude1;//高度，地平为零，天顶90度，0零到90度
		StarsPos.mAPointEerror1=g_mGoto.m_nAPointEerror1;
		StarsPos.mEPointEerror1=g_mGoto.m_nEPointEerror1;
		StarsPos.mANzimuth2=g_mGoto.m_nANzimuth2;//方位，正北为零，东负西正，0度到360度
		StarsPos.mAtitude2=g_mGoto.m_nAtitude2;//高度，地平为零，天顶90度，0零到90度
		StarsPos.mAPointEerror2=g_mGoto.m_nAPointEerror2;
		StarsPos.mEPointEerror2=g_mGoto.m_nEPointEerror2;
		StarsPos.mANzimuth3=g_mGoto.m_nANzimuth3;//方位，正北为零，东负西正，0度到360度
		StarsPos.mAtitude3=g_mGoto.m_nAtitude3;//高度，地平为零，天顶90度，0零到90度
		StarsPos.mAPointEerror3=g_mGoto.m_nAPointEerror3;
		StarsPos.mEPointEerror3=g_mGoto.m_nEPointEerror3;

        //校准计算
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
		
		//置位已经校准标志
		g_mGoto.m_nAlign=true;
	  
	  // if(g_mAzEq==0)  //地平式清零，赤道式不清零
	   //{	


	   	 //dg_mApos0=2.0*dg_mApos; //记录校准后的调节量
		 //dg_mApos0=2.0*dg_mZpos;  //记录校准后的调节量

		 dg_mApos=0;//手动调节量清零
		 dg_mZpos=0;//手动调节量清零
	

		 	syn_mApos=0;//方位跟踪时的同步量
            syn_mZpos=0;//天顶跟踪时的同步量

			g_mhandtrackAzi=1;//最初指向时，望远镜与目标位置一致，手动调节后，就不一致了
			g_mhandtrackAlt=1;//最初指向时，望远镜与目标位置一致，手动调节后，就不一致了


	//	}
		//手动调节量清零现在是清下列两个变量
	
	//	FBeep(3);
	}
}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//望远镜自动校准对星有没有对准
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

						//考虑回差

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

						//考虑回差

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

						//考虑回差


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
//两颗星自动校准
void FTwoStarAutoAlign()
{	
   char starname[28][10];
   char starnamecn[28][22];
	g_mGoto.m_nAlignStarNum=2;//设置几颗星校准
    g_mGoto.m_nAlign=false;//望远镜是否已经校过,true校过了，false还没有校准
    g_mGoto.m_nAlignAdjustNum=0;//望远镜校准时调节次数

	
	
	g_mAlignStarNum=FindAlignStar(FCalSiderealTime(1,false,g_mGoto.m_nLongitude),g_mGoto.m_nAtitude,g_mStarAlign,starname,starnamecn);			
	g_mGoto.m_nAlignStarRA1=g_mStarAlign[0];//赤经(0-24小时)
	g_mGoto.m_nAlignStarDec1=g_mStarAlign[1];//赤纬(-90到90度)
	g_mGoto.m_nAlignStarRA2=g_mStarAlign[2];//2*(g_mAlignStarNum-1)];//赤经(0-24小时)
	g_mGoto.m_nAlignStarDec2=g_mStarAlign[3];//2*(g_mAlignStarNum-1)+1];//赤纬(-90到90度)
    
	dg_mApos=0;
	dg_mZpos=0;
	dg_mApos_syn=0;
	dg_mZpos_syn=0;

	g_mTelError.mTSettingNP=0;//不垂直
	g_mTelError.mTSettingLOS=0;//光轴偏差
	g_mTelError.mTSettingNS=0;//北顷
	g_mTelError.mTSettingEW=0;//东倾
	g_mTelError.mTSettingA0=0;//方位零偏
	g_mTelError.mTSettingE0=0;//高度零偏 

	g_mTelRALastPos=g_mTelRANextPos;
	g_mTelDecLastPos=g_mTelDecNextPos;


	FStartGoto();

}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//一颗星校准
void FOneStarAlign()
{
 
	g_mGoto.m_nAlignStarNum=1;//设置几颗星校准
    g_mGoto.m_nAlign=false;//望远镜是否已经校过,true校过了，false还没有校准
    g_mGoto.m_nAlignAdjustNum=0;//望远镜校准时调节次数

	//g_mAlignStarNum=FindAlignStar(FCalSiderealTime(1,false,g_mGoto.m_nLongitude),g_mGoto.m_nAtitude,g_mStarAlign);		
	//g_mGoto.m_nAlignStarRA1=g_mStarAlign[0];//赤经(0-24小时)
	//g_mGoto.m_nAlignStarDec1=g_mStarAlign[1];//赤纬(-90到90度)


	dg_mApos=0;
	dg_mZpos=0;
	dg_mApos_syn=0;
	dg_mZpos_syn=0;

    g_mTelError.mTSettingNP=0;//不垂直
	g_mTelError.mTSettingLOS=0;//光轴偏差
	g_mTelError.mTSettingNS=0;//北顷
	g_mTelError.mTSettingEW=0;//东倾
	g_mTelError.mTSettingA0=0;//方位零偏
	g_mTelError.mTSettingE0=0;//高度零偏 

	g_mTelRALastPos=g_mTelRANextPos;
	g_mTelDecLastPos=g_mTelDecNextPos;

	FStartGoto();

}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//两颗星校准
void FTwoStarAlign()
{	

	g_mGoto.m_nAlignStarNum=2;//设置几颗星校准
    g_mGoto.m_nAlign=false;//望远镜是否已经校过,true校过了，false还没有校准
    g_mGoto.m_nAlignAdjustNum=0;//望远镜校准时调节次数
	
	//g_mAlignStarNum=FindAlignStar(FCalSiderealTime(1,false,g_mGoto.m_nLongitude),g_mGoto.m_nAtitude,g_mStarAlign);		

	
	//g_mGoto.m_nAlignStarRA1=g_mStarAlign[0];//赤经(0-24小时)
	//g_mGoto.m_nAlignStarDec1=g_mStarAlign[1];//赤纬(-90到90度)
	//g_mGoto.m_nAlignStarRA2=g_mStarAlign[2];//赤经(0-24小时)
	//g_mGoto.m_nAlignStarDec2=g_mStarAlign[3];//赤纬(-90到90度)
    
	dg_mApos=0;
	dg_mZpos=0;
	dg_mApos_syn=0;
	dg_mZpos_syn=0;

    g_mTelError.mTSettingNP=0;//不垂直
	g_mTelError.mTSettingLOS=0;//光轴偏差
	g_mTelError.mTSettingNS=0;//北顷
	g_mTelError.mTSettingEW=0;//东倾
	g_mTelError.mTSettingA0=0;//方位零偏
	g_mTelError.mTSettingE0=0;//高度零偏 

	g_mTelRALastPos=g_mTelRANextPos;
	g_mTelDecLastPos=g_mTelDecNextPos;

	FStartGoto();

}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//三颗星校准
void FThreeStarAlign()
{

	g_mGoto.m_nAlignStarNum=3;//设置几颗星校准
    g_mGoto.m_nAlign=false;//望远镜是否已经校过,true校过了，false还没有校准
    g_mGoto.m_nAlignAdjustNum=0;//望远镜校准时调节次数

	//g_mAlignStarNum=FindAlignStar(FCalSiderealTime(1,false,g_mGoto.m_nLongitude),g_mGoto.m_nAtitude,g_mStarAlign);		
	//g_mGoto.m_nAlignStarRA1=g_mStarAlign[0];//赤经(0-24小时)
	//g_mGoto.m_nAlignStarDec1=g_mStarAlign[1];//赤纬(-90到90度)
	//g_mGoto.m_nAlignStarRA2=g_mStarAlign[2];//赤经(0-24小时)
	//g_mGoto.m_nAlignStarDec2=g_mStarAlign[3];//赤纬(-90到90度)
	//g_mGoto.m_nAlignStarRA3=g_mStarAlign[4];//赤经(0-24小时)
	//g_mGoto.m_nAlignStarDec3=g_mStarAlign[5];//赤纬(-90到90度)


	dg_mApos=0;
	dg_mZpos=0;
	dg_mApos_syn=0;
	dg_mZpos_syn=0;

    g_mTelError.mTSettingNP=0;//不垂直
	g_mTelError.mTSettingLOS=0;//光轴偏差
	g_mTelError.mTSettingNS=0;//北顷
	g_mTelError.mTSettingEW=0;//东倾
	g_mTelError.mTSettingA0=0;//方位零偏
	g_mTelError.mTSettingE0=0;//高度零偏 


	g_mTelRALastPos=g_mTelRANextPos;
	g_mTelDecLastPos=g_mTelDecNextPos;

	FStartGoto();
}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//校准计算
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
		
		//方程建立
		//方位第一颗星方程系数
		ca11=1;

      // mtest0=cos(E1);
	  
	   mtest0=fStarsPos.mANzimuth1*ee;
	   mtest=cos(fStarsPos.mANzimuth1*ee);

	   //mtest=mtest0/mtest;

		ca12=sin(A1)*sin(E1)/cos(E1);
		ca13=cos(A1)*sin(E1)/cos(E1);
		
		//方位第二颗星方程系数
		ca21=1;
		ca22=sin(A2)*sin(E2)/cos(E2);
		ca23=cos(A2)*sin(E2)/cos(E2);
		
		//高度第一颗星方程系数
		ce11=1;
		ce12=cos(A1);
		ce13=-1.0*sin(A1);
		
		//高度第二颗星方程系数
		ce21=1;
		ce22=cos(A2);
		ce23=-1.0*sin(A2);
		//*************************************** 
		//求解方程
		//中间消元
		a=dta2-dta1;
		a1=ca22-ca12;
		a2=ca23-ca13;
		
		e=dte2-dte1;
		e1=ce22-ce12;
		e2=ce23-ce13;
		//****************************************
		
		we=(a*e2-a2*e)/(e2*a1-e1*a2);//东西倾斜
		ns=(a*e1-a1*e)/(e1*a2-e2*a1);//南北倾斜
		
		da0=dta1-ca12*we-ca13*ns;//方位零点偏移
		de0=dte1-ce12*we-ce13*ns;//高度零点偏移
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
		
		//方程系统
		//第一颗星方位方程系数
		ca11=1;
		ca13=-1.0/cos(E1);
		ca14=tan(E1);
		ca15=tan(E1)*sin(A1);
		ca16=tan(E1)*cos(A1);
		
		//第二颗星方位方程系数
		ca21=1;
		ca23=-1.0/cos(E2);
		ca24=tan(E2);
		ca25=tan(E2)*sin(A2);
		ca26=tan(E2)*cos(A2);
		
		//第三颗星方位方程系数
		ca31=1;
		ca33=-1.0/cos(E3);
		ca34=tan(E3);
		ca35=tan(E3)*sin(A3);
		ca36=tan(E3)*cos(A3);
		
		//第一颗星高度方程系数
		ce11=1;
		ce15=cos(A1);
		ce16=-sin(A1);
		
		//第二颗星高度方程系数
		ce21=1;
		ce25=cos(A2);
		ce26=-sin(A2);
		
		//第三颗星高度方程系数
		ce31=1;
		ce35=cos(A3);
		ce36=-sin(A3);
		//***************************************
		
		//求解方程
		//通过高度的三个方程求角高度零点de0,北倾ns,东倾we;
		//***********
		//消de0
		dde1=dte2-dte1;   
		dce15=ce25-ce15;
		dce16=ce26-ce16;
		
		dde2=dte3-dte1;
		dce25=ce35-ce15;
		dce26=ce36-ce16;
		//**************
		//求we,ns
		we=(dde1*dce26-dce16*dde2)/(dce26*dce15-dce25*dce16);//东西倾斜
		ns=(dde1*dce25-dce15*dde2)/(dce25*dce16-dce26*dce15);//南北倾斜
		//求de0
		de0=dte1-ce15*we-ce16*ns;
		//*************************
		//求方位零偏da0,光轴gam,不垂直snta
		switch(nogma)
		{
		case 1:
            gam=0;//不考虑光轴,//不考虑不垂直
            snta=0;
			da0=(dta1-ca15*we-ca16*ns+dta2-ca25*we-ca26*ns+dta3-ca35*we-ca36*ns)/3;
			break;
		case 2:
            gam=0;//不考虑光轴
            //消da0
            dda1=dta2-ca25*we-ca26*ns-dta1+ca15*we+ca16*ns;
            dca14=ca24-ca14;
            
            dda2=dta3-ca35*we-ca36*ns-dta1+ca15*we+ca16*ns;
            dca24=ca34-ca14;
            
            snta=(dda2-dda1)/(dca24-dca14);
            da0=(dta1-ca14*snta-ca15*we-ca16*ns+dta2-ca24*snta-ca25*we-ca26*ns+dta3-ca34*snta-ca35*we-ca36*ns)/3;
			
			break;
		case 3:
            snta=0;//不考虑不垂直
            //消da0
            dda1=dta2-ca25*we-ca26*ns-dta1+ca15*we+ca16*ns ;
            dca13=ca23-ca13;
            
            dda2=dta3-ca35*we-ca36*ns-dta1+ca15*we+ca16*ns;
            dca23=ca33-ca13;
            
            gam=(dda2-dda1)/(dca23-dca13);
            da0=(dta1-ca13*gam-ca15*we-ca16*ns+dta2-ca23*gam-ca25*we-ca26*ns+dta3-ca33*gam-ca35*we-ca36*ns)/3;
			break;
		case 4:
            //消da0
            dda1=dta2-ca25*we-ca26*ns-dta1+ca15*we+ca16*ns;  
            dca13=ca23-ca13;
            dca14=ca24-ca14;
			
            dda2=dta3-ca35*we-ca36*ns-dta1+ca15*we+ca16*ns;
			dca23=ca33-ca13;
            dca24=ca34-ca14;
            //**************
            //求gam,snta
            gam=(dda1*dca24-dca14*dda2)/(dca24*dca13-dca23*dca14);//光轴
            snta=(dda1*dca23-dca13*dda2)/(dca23*dca14-dca24*dca13);//不垂直
            //求da0
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
//一颗星校准计算
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

//两颗星校准计算
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
	
		
		//方程建立
		//方位第一颗星方程系数
		ca11=1;

		ca12=sin(mA1)*sin(mE1)/cos(mE1);
		ca13=cos(mA1)*sin(mE1)/cos(mE1);
		
		//方位第二颗星方程系数
		ca21=1;
		ca22=sin(mA2)*sin(mE2)/cos(mE2);
		ca23=cos(mA2)*sin(mE2)/cos(mE2);
		
		//高度第一颗星方程系数
		ce11=1;
		ce12=cos(mA1);
		ce13=-1.0*sin(mA1);
		
		//高度第二颗星方程系数
		ce21=1;
		ce22=cos(mA2);
		ce23=-1.0*sin(mA2);
		//*************************************** 
		//求解方程
		//中间消元
		a=dta2-dta1;
		a1=ca22-ca12;
		a2=ca23-ca13;
		
		e=dte2-dte1;
		e1=ce22-ce12;
		e2=ce23-ce13;
		//****************************************
		
//		we=(a*e2-a2*e)/(e2*a1-e1*a2);//东西倾斜
//		ns=(a*e1-a1*e)/(e1*a2-e2*a1);//南北倾斜
//		
//		da0=dta1-ca12*we-ca13*ns;//方位零点偏移
//		de0=dte1-ce12*we-ce13*ns;//高度零点偏移

		we=(a*e1-a1*e)/(e1*a2-e2*a1);//东西倾斜
		ns=(a*e2-a2*e)/(e2*a1-e1*a2);//南北倾斜
		
		da0=dta1-ca12*ns-ca13*we;//方位零点偏移
		de0=dte1-ce12*ns-ce13*we;//高度零点偏移

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
//三颗星校准计算
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
	
		
		//方程建立
		//方位第一颗星方程系数
		ca11=1;

		ca12=sin(mA1)*sin(mE1)/cos(mE1);
		ca13=cos(mA1)*sin(mE1)/cos(mE1);
		
		//方位第二颗星方程系数
		ca21=1;
		ca22=sin(mA2)*sin(mE2)/cos(mE2);
		ca23=cos(mA2)*sin(mE2)/cos(mE2);
		
		//高度第一颗星方程系数
		ce11=1;
		ce12=cos(mA1);
		ce13=-1.0*sin(mA1);
		
		//高度第二颗星方程系数
		ce21=1;
		ce22=cos(mA2);
		ce23=-1.0*sin(mA2);
		//*************************************** 
		//求解方程
		//中间消元
		a=dta2-dta1;
		a1=ca22-ca12;
		a2=ca23-ca13;
		
		e=dte2-dte1;
		e1=ce22-ce12;
		e2=ce23-ce13;
		//****************************************
		
//		we=(a*e2-a2*e)/(e2*a1-e1*a2);//东西倾斜
//		ns=(a*e1-a1*e)/(e1*a2-e2*a1);//南北倾斜
//		
//		da0=dta1-ca12*we-ca13*ns;//方位零点偏移
//		de0=dte1-ce12*we-ce13*ns;//高度零点偏移

		we=(a*e1-a1*e)/(e1*a2-e2*a1);//东西倾斜
		ns=(a*e2-a2*e)/(e2*a1-e1*a2);//南北倾斜
		
		da0=dta1-ca12*ns-ca13*we;//方位零点偏移
		de0=dte1-ce12*ns-ce13*we;//高度零点偏移

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
//		//方程系统
//		//第一颗星方位方程系数
//		ca11=1;
//		ca13=-1.0/cos(mE1);
//		ca14=sin(mE1)/cos(mE1);
//
//		ca15=ca14*sin(mA1);
//		ca16=ca14*cos(mA1);
//		
//		//第二颗星方位方程系数
//		ca21=1;
//		ca23=-1.0/cos(mE2);
//		ca24=sin(mE2)/cos(mE2);
//		ca25=ca24*sin(mA2);
//		ca26=ca24*cos(mA2);
//		
//		//第三颗星方位方程系数
//		ca31=1;
//		ca33=-1.0/cos(mE3);
//		ca34=sin(mE3)/cos(mE3);
//		ca35=ca34*sin(mA3);
//		ca36=ca34*cos(mA3);	
//		
//		//第一颗星高度方程系数
//		ce11=1;
//		ce15=cos(mA1);
//		ce16=-1.0*sin(mA1);
//		
//		//第二颗星高度方程系数
//		ce21=1;
//		ce25=cos(mA2);
//		ce26=-sin(mA2);
//		
//		//第三颗星高度方程系数
//		ce31=1;
//		ce35=cos(mA3);
//		ce36=-1.0*sin(mA3);
//		//***************************************
//		
//		//求解方程
//		//通过高度的三个方程求角高度零点de0,北倾ns,东倾we;
//		//***********
//		//消de0
//		dde1=dte2-dte1;   
//		dce15=ce25-ce15;
//		dce16=ce26-ce16;
//		
//		dde2=dte3-dte1;
//		dce25=ce35-ce15;
//		dce26=ce36-ce16;
//		//**************
//		//求we,ns										 
//		we=(dde1*dce25-dce15*dde2)/(dce25*dce16-dce26*dce15);//东西倾斜
//		ns=(dde1*dce26-dce16*dde2)/(dce26*dce15-dce25*dce16);//南北倾斜
//		//求de0
//		de0=dte1-ce15*ns-ce16*we;
//		//*************************
//		//求方位零偏da0,光轴gam,不垂直snta
//		switch(nogma)
//		{
//		case 1:
//            gam=0;//不考虑光轴,//不考虑不垂直
//            snta=0;
//			da0=(dta1-ca15*ns-ca16*we+dta2-ca25*ns-ca26*we+dta3-ca35*ns-ca36*we)/3.0;
//			break;
//		case 2:
//            gam=0;//不考虑光轴,考虑不垂直
//            //消da0
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
//			//不考虑光轴，考虑不垂直，但是方位和高度联合求北倾，和西倾。
//                gam=0;//不考虑光轴,考虑不垂直
//
//			  	//消de0
//				dde1=dte2-dte1;   
//				dce15=ce25-ce15;
//				dce16=ce26-ce16;
//				
//				dde2=dte3-dte1;
//				dce25=ce35-ce15;
//				dce26=ce36-ce16;
//				//消去da0和snta得：
//				dda1=(dta3-dta1)*(ca24-ca14)-(dta2-dta1)*(ca34-ca14);
//				dca15=(ca35-ca15)*(ca24-ca14)-(ca25-ca15)*(ca34-ca14);
//				dca16=(ca36-ca16)*(ca24-ca14)-(ca26-ca16)*(ca34-ca14);
//
//				//一次求ns,we
//		
//				 //we=(dde2*dca15-dda1*dce25)/(dce26*dca15-dca16*dce25);
//				 //ns=(dde2*dca16-dda1*dce26)/(dce25*dca16-dca15*dce26);
//
//				 //两次求ns,we
//		
//				 //we=(dde1*dca15-dda1*dce15)/(dce16*dca15-dca16*dce15)+(dde2*dca15-dda1*dce25)/(dce26*dca15-dca16*dce25);
//				 //we=we/2.0;
//				 //ns=(dde1*dca16-dda1*dce16)/(dce15*dca16-dca15*dce16)+(dde2*dca16-dda1*dce26)/(dce25*dca16-dca15*dce26);
//				// ns=ns/2.0;
//
//				 //三次求ns,we												 		
//				 we1=(dde1*dca15-dda1*dce15)/(dce16*dca15-dca16*dce15);
//				 we2=(dde2*dca15-dda1*dce25)/(dce26*dca15-dca16*dce25);
//				 we3=(dde1*dce25-dce15*dde2)/(dce25*dce16-dce26*dce15); //东西倾斜
//
//				 we=(we1+we2+we3)/3;
//				 
//				 ns1=(dde1*dca16-dda1*dce16)/(dce15*dca16-dca15*dce16);
//				 ns2=(dde2*dca16-dda1*dce26)/(dce25*dca16-dca15*dce26);
//				 ns3=(dde1*dce26-dce16*dde2)/(dce26*dce15-dce25*dce16); //南北倾斜
//
//				 ns=(ns1+ns2+ns3)/3;
//				 
//
//				 //求不垂直
//				 snta=((dta3-dta1)-(ca35-ca15)*ns-(ca36-ca16)*we)/(ca34-ca14);
//				 //求方位零偏
//				 da0=dta3-ca34*snta-ca35*ns-ca36*we;
//				 //求高度零偏
//				 de0=dte3-ce35*ns-ce36*we;	*/
//
//			break;
//		case 3:
//            snta=0;//不考虑不垂直,考虑光轴
//            //消da0
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
//            //消da0
//            dda1=dta2-ca25*ns-ca26*we-dta1+ca15*ns+ca16*we;  
//            dca13=ca23-ca13;
//            dca14=ca24-ca14;
//			
//            dda2=dta3-ca35*ns-ca36*we-dta1+ca15*ns+ca16*we;
//			dca23=ca33-ca13;
//            dca24=ca34-ca14;
//            //**************
//            //求gam,snta
//            gam=(dda1*dca24-dca14*dda2)/(dca24*dca13-dca23*dca14);//光轴
//            snta=(dda1*dca23-dca13*dda2)/(dca23*dca14-dca24*dca13);//不垂直
//            //求da0
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
//系统参数初始化
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void FSetupPointTrackPara()
{ 
	//系统参数
    g_mGoto.m_nTescpType=1;//望远镜型号
	g_mGoto.m_nSysTimeType=1;//系统时间类型,1北京时，2世界时
	g_mGoto.m_nNutation=false;//计算地方恒星时是否加章动改正
	
	g_mGoto.m_nTescpASpeedRatio=0.22701751051996061392472493380255;/*meade改*///0.20870217144665865116076517155392(单臂）;//方位传动比,望远镜速度输出码值比例因子，与传动比和码盘线数相关,一个读数值到角秒/秒的转换
	g_mGoto.m_nTescpESpeedRatio=0.16521502345690755559422189482536;/*meade改*///0.20870217144665865116076517155392(单臂）;//高度传动比,望远镜速度输出码值比例因子，与传动比和码盘线数相关,一个读数值到角秒/秒的转换
    
   

	g_mGoto.m_nTescpAPosRatio=3.3046489801853247148087930100065e-4;/*meade改*///0.0003038036213391663628630453275003(单臂）;//望远镜位置反馈码值比例因子，与传动比和码盘线数相关,一个读数值到度的转换
	g_mGoto.m_nTescpEPosRatio=2.4050024050024050024050024050024e-4;/*meade改*///0.0003038036213391663628630453275003(单臂）;///望远镜位置反馈码值比例因子，与传动比和码盘线数相关,一个读数值到度的转换



   //************
	//观测地位置
	g_mGoto.m_nLongitude=102.7944;//经度(-180度到180度)东正西负
	g_mGoto.m_nAtitude=25.027777;//纬度(-90度到90度)北正南负
	g_mGoto.m_nTimeZone=8;//观测地时区(-12到12);
//	g_mGoto.m_nSiteHigh=1568;//海拔km
	//************
	//观测目标赤经赤纬
	g_mGoto.m_nObjectType=1;//观测目标类型，1恒星，2太阳，3行量，4彗星，5卫星,6静止目标
	g_mGoto.m_nRightAscension=4.4993833;;//赤经(0-24小时)
	g_mGoto.m_nDeclination=-26.453416667;//赤纬(-90到90度)
	//************
	//观测目标地平坐标
	//	g_mGoto.m_nStarAPos;//目标方位
	//   g_mGoto.m_nStarEPos;//目标高度
	//	g_mGoto.m_nStarASpeed;//目标方位运行速度
	//	g_mGoto.m_nStarESpeed;//目标高度运行速度
    //望远镜运行状态
	//g_mGoto.m_nTescpAPos;//望远镜的方位坐标
    //g_mGoto.m_nTescpEPos;//望远镜的高度坐标
	//g_mGoto.m_nAPosError;//星方位与望远镜方位的位置误差
	//g_mGoto.m_nEPosError;//星高度与望远镜高度的位置误差
	g_mGoto.m_nAPosEIZero=0;//望远镜方位误差积分零点
    g_mGoto.m_nEPosEIZero=0;//望远镜高度误差积分零点
	//	g_mGoto.m_nTescpASpeed;//望远镜方位跟踪时的运行速度
	//	g_mGoto.m_nTescpESpeed;//望远镜高度跟踪时的运行速度
    g_mGoto.m_nTescpASpeedMax=500;//望远镜方位定位时的最大运行速度
	g_mGoto.m_nTescpESpeedMax=160;//望远镜高度跟踪时的最大运行速度
	g_mGoto.m_nTescpAAcc=100;//望远镜方位定位时的加速度
	g_mGoto.m_nTescpEAcc=50;//望远镜高度跟踪时的加速度

    g_mGoto.m_nTAState=0;//望远镜方位的运行状态,0为起动状态，1为定位状态，2为跟踪状态,3停止状态
	g_mGoto.m_nTEState=0;//望远镜高度的运行状态,0为起动状态，1为定位状态，2为跟踪状态,3停止状态
	
	g_mGoto.m_nGoto=false;//望远镜初始状态为没有运行在GOTO状态
	g_mGoto.m_nStartStop=false;//false停止GOTO
	g_mGoto.m_nUnderhorizon=false;//星初始化为不在地平线下

	g_mGoto.m_nTCrossZeroP=false;//望远镜在运行时是否有正穿越
	g_mGoto.m_nTCrossZeroN=false;//望远镜在运行时是否有负穿越
	g_mGoto.m_nTPointDirect=0;//望远镜定位不变向

	g_mGoto.m_nTelGotoPause=0;//望远镜定位跟踪转动过程中是否暂停,0不暂停，1暂停


	//望远镜自动校准变量：
	g_mGoto.m_nAlignStarNum=0;//设置几颗星校准
    g_mGoto.m_nAlign=true;//望远镜是否已经校过,true校过了，false还没有校准
	g_mGoto.m_nAlignAdjust=false;//望远镜是否调节误差了
	g_mGoto.m_nTAlignState=0;//望远镜是否在校正状态
    g_mGoto.m_nAlignAdjustNum=0;//望远镜校准时调节次数

	g_mGoto.m_nAlignStarRA1=12.0;//赤经(0-24小时)
	g_mGoto.m_nAlignStarDec1=-16.0;//赤纬(-90到90度)
	g_mGoto.m_nAlignStarRA2=10.0;//赤经(0-24小时)
	g_mGoto.m_nAlignStarDec2=0.0;//赤纬(-90到90度)
	g_mGoto.m_nAlignStarRA3=16.0;//赤经(0-24小时)
	g_mGoto.m_nAlignStarDec3=10.0;//赤纬(-90到90度)


	g_mGoto.m_nTSettingNP=0;//不垂直
	g_mGoto.m_nTSettingLOS=0;//光轴偏差
	g_mGoto.m_nTSettingNS=0;//北顷
	g_mGoto.m_nTSettingEW=0;//东倾
	g_mGoto.m_nTSettingA0=10;//方位零偏
	g_mGoto.m_nTSettingE0=0;//高度零偏 

    g_mGoto.m_nTSettingAA0=0;//方位零偏备用
	g_mGoto.m_nTSettingEE0=0;//高度零偏备用

	g_mGoto.m_nStarAPosTshow=0;//目标方位望远镜坐标系坐标,用于显示
    g_mGoto.m_nStarEPosTshow=0;//目标高度望远镜坐标系坐标,用于显示

	
	//计算在气蒙气差
//	g_mGoto.m_nAirP=880;//大气压mba
//	g_mGoto.m_nAirT=20;//温度c
	


	 g_mLandMark=false;//是陆目标还是天空目标,false天空目标，true陆地目标


	g_mTelError.mTSettingA0=0;//TSetting.mTSettingA0;
	g_mTelError.mTSettingE0=0;//TSetting.mTSettingE0;
	g_mTelError.mTSettingLOS=0;//TSetting.mTSettingLOS;
	g_mTelError.mTSettingNP=0;//TSetting.mTSettingNP;
	g_mTelError.mTSettingEW=0;//TSetting.mTSettingEW;
	g_mTelError.mTSettingNS=0;//TSetting.mTSettingNS;

   	g_mPointNewStar=false;//是否指向了新的一颗星，true指了,指了就存为最近观测的星，false没有指

	dg_mApos=0;
	dg_mZpos=0;


	dg_mApos0=0;
	dg_mZpos0=0;

	//ddg_mApos=0;
	//ddg_mZpos=0;

	syn_mApos=0;//方位跟踪时的同步量
    syn_mZpos=0;//天顶跟踪时的同步量

	g_mAlignShow=0;//校准过程中的显示设置

	g_mPointNewStarTracking=0;
	g_mstartOTAset=0;//开机时设置望远镜的初始指向

	g_mGoto.m_nGuidMoveRa=0;//光电导星赤经偏移量
	g_mGoto.m_nGuidMoveDec=0;//光电导星赤纬偏移量
}


//*************函数功能://手柄蜂鸣
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
 //计算星体升落时间
 //入口参数
//selectnum=1:升起, =2:中天, =3:下落
//g_mochj赤经
//g_mochw赤纬
//g_mpjd经度
//g_mpwd纬度
//g_mzone时区


//出口参数
//  返回观测点观测目标升起、中天、下落的北京时间
 
double FSRiseSettime(int selectnum,double g_mochj,double g_mochw,double g_mpjd,double g_mpwd,uint8 g_mzone)
{
        double BjTime,LocalTime;                    //    北京时、地方平时
		double LocalStarTime,LocalStarTime0;      //    地方恒星时、地方平时0h的地方恒星时
		double v;         //     单位换算系数
		double v0;
		double t;         //     恒星升、没的时角
        
		g_mochj=g_mochj*15.0;		 
	    v=1.0/366.2422;
		v0=1.0/365.2422;	
 		t=fabs(acos((cos(1.58068652588953)-sin(g_mpwd*0.01745329251994)*sin(g_mochw*0.01745329251994))/(cos(g_mpwd*0.01745329251994)*cos(g_mochw*0.01745329251994))))*3.81971863420549;
		
		if(1==selectnum)
		    {
		        LocalStarTime=g_mochj/15.0-t;         //恒星升起的地方恒星时  
		    }
		if(2==selectnum)
		    {
		        LocalStarTime=g_mochj/15.0;           //恒星中天的地方恒星时
		    }
		if(3==selectnum)
		    {
		        LocalStarTime=g_mochj/15.0+t;         //恒星落下的地方恒星时
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
    //  返回观测点观测目标升起、中天、下落的北京时间
 	return BjTime;
}


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//定位跟踪驱动输出
void FDriveTelescope(double faspeed,double fzspeed)
{	
	
	if(g_mTelescopeConType==1)
	{
         	//2011年5月30发现此传动比快了
			//g_mGoto.m_nTescpASpeedRatio=0.075736993550978891820580474933707;//方位传动比,望远镜速度输出码值比例因子，与传动比和码盘线数相关,一个读数值到角秒/秒的转换
			//g_mGoto.m_nTescpESpeedRatio=0.075736993550978891820580474933707;//高度传动比,望远镜速度输出码值比例因子，与传动比和码盘线数相关,一个读数值到角秒/秒的转换
		    
		
			//g_mGoto.m_nTescpAPosRatio=1.0993843447669305189094107299912e-4;//望远镜位置反馈码值比例因子，与传动比和码盘线数相关,一个读数值到度的转换
			//g_mGoto.m_nTescpEPosRatio=1.0993843447669305189094107299912e-4;//望远镜位置反馈码值比例因子，与传动比和码盘线数相关,一个读数值到度的转换
	
	
	       //2011年5月30发现以上传动比快了，理论算改正为 
		   //1传动比为6810.810811
		  	//g_mGoto.m_nTescpASpeedRatio=0.084290465121894868032328317156678;//方位传动比,望远镜速度输出码值比例因子，与传动比和码盘线数相关,一个读数值到角秒/秒的转换
			//g_mGoto.m_nTescpESpeedRatio=0.084290465121894868032328317156678;//高度传动比,望远镜速度输出码值比例因子，与传动比和码盘线数相关,一个读数值到角秒/秒的转换
		    		
			//g_mGoto.m_nTescpAPosRatio=1.2235449735109861845982398017506e-4;//望远镜位置反馈码值比例因子，与传动比和码盘线数相关,一个读数值到度的转换
			//g_mGoto.m_nTescpEPosRatio=1.2235449735109861845982398017506e-4;//望远镜位置反馈码值比例因子，与传动比和码盘线数相关,一个读数值到度的转换
			//2传动比为7611.428571
		  	g_mGoto.m_nTescpASpeedRatio=0.075424265729001741688945293262234;//方位传动比,望远镜速度输出码值比例因子，与传动比和码盘线数相关,一个读数值到角秒/秒的转换
			g_mGoto.m_nTescpESpeedRatio=0.075424265729001741688945293262234;//高度传动比,望远镜速度输出码值比例因子，与传动比和码盘线数相关,一个读数值到角秒/秒的转换
		    		
			g_mGoto.m_nTescpAPosRatio=1.0948448449064915140400301778426e-4;//望远镜位置反馈码值比例因子，与传动比和码盘线数相关,一个读数值到度的转换
			g_mGoto.m_nTescpEPosRatio=1.0948448449064915140400301778426e-4;//望远镜位置反馈码值比例因子，与传动比和码盘线数相关,一个读数值到度的转换
	
	
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
			    if(g_mGoto.m_nTAState==2)//跟踪时，输出跟踪的速度//否则输定位速度
		         { 		   
		   	        if(g_mAposModify==0)
					{
						sendspd.i=5;
					 }
				    if((m_GuiderRa!=0)||(AGuiderRa))//自动导星时，输出导星速度
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
						       g_mHandSpeedAzi=sendspd.i; //给望远镜调节时的手动方位速度
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
						       g_mHandSpeedAzi=sendspd.i; //给望远镜调节时的手动方位速度
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
						       g_mHandSpeedAzi=sendspd.i; //给望远镜调节时的手动方位速度
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
//						       g_mHandSpeedAzi=sendspd.i; //给望远镜调节时的手动方位速度
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
//						       g_mHandSpeedAzi=sendspd.i; //给望远镜调节时的手动方位速度
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
//						       g_mHandSpeedAzi=sendspd.i; //给望远镜调节时的手动方位速度
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
						       g_mHandSpeedAlt=sendspd.i; //给望远镜调节时的手动方位速度
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
						       g_mHandSpeedAlt=sendspd.i; //给望远镜调节时的手动方位速度
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
						       g_mHandSpeedAlt=sendspd.i; //给望远镜调节时的手动方位速度
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
//						       g_mHandSpeedAlt=sendspd.i; //给望远镜调节时的手动方位速度
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
//						       g_mHandSpeedAlt=sendspd.i; //给望远镜调节时的手动方位速度
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
//						       g_mHandSpeedAlt=sendspd.i; //给望远镜调节时的手动方位速度
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
//定位跟踪驱动输出
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
//			g_mGoto.m_nTescpASpeedRatio=0.075736993550978891820580474933707;//方位传动比,望远镜速度输出码值比例因子，与传动比和码盘线数相关,一个读数值到角秒/秒的转换
//			g_mGoto.m_nTescpESpeedRatio=0.075736993550978891820580474933707;//高度传动比,望远镜速度输出码值比例因子，与传动比和码盘线数相关,一个读数值到角秒/秒的转换
//		    
//		
//			g_mGoto.m_nTescpAPosRatio=1.09938e-4;//望远镜位置反馈码值比例因子，与传动比和码盘线数相关,一个读数值到度的转换
//			g_mGoto.m_nTescpEPosRatio=1.09938e-4;//望远镜位置反馈码值比例因子，与传动比和码盘线数相关,一个读数值到度的转换
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
//函数名称: FindAlignStar
//功能描述: 导入校准星表，找出当前时刻可用于校准的星
//   参数说明：fstime : 当前恒星时
//			 flat：   当前纬度
//			 fraddec：指针，用于存储可用于校准星的赤经和赤纬*fraddec=第一颗星赤经
//			           										*（fraddec+1）=第一颗星赤纬
//															*（fraddec+2）=第二颗星赤经
//															*（fraddec+3）=第二颗星赤纬
//															....
//   返回值：返回当前可用于校准星的颗数
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

