
 //系统参数初始化及函数实现
#include "Sys.h"

//系统参数初始化
void InitSysPara()
{
	g_mSysInitGuide=1;//是否打开初始化向导，0不打开，1打开
	

	g_mhelpshow=0;//显示状态，0菜单，1帮助
	g_mKeyBeepOpen=0;//按键蜂鸣开关0,关，1开，按F+0操作


    g_bkeyoperator=false;


//	g_mhumidity=82;//湿度
//	g_mtemperature=25;//温度
//	g_mairpressure=682;//气压


	g_mDaylight=false;//是否采用夏令时,true采用，false不用采


	g_mRaTrackSpeed=0.0;//角秒
	g_mTrackSpeed=0;//跟踪速度0恒星速，1太阳速，2月亮速，3自定义

	g_mPoleAxisEW=0.235;
	g_mPoleAxisNS=0.326;//望远镜的东西和南北倾斜,东和北为正，西和南为负,单位为度


    g_telra=0;//望远镜所指向的赤经
    g_teldec=0;//望远镜所指向的赤纬
	
	g_mObjRa_shi=11;
	g_mObjRa_fen=41;//目标赤经时分秒
	g_mObjRa_miao=12.6;

	g_gObjDec_sign=1; //目标赤纬正负
	g_mObjDec_du=55;
	g_mObjDec_fen=11;//目标赤纬度分秒
	g_mObjDec_miao=1.9;
	
	g_mObjAzi_du=1;
	g_mObjAzi_fen=3;//目标方位度分秒
	g_mObjAzi_miao=5.9;


	g_mObjAlt_du=6;
	g_mObjAlt_fen=3;//目标高度度分秒
	g_mObjAlt_miao=5.8;
	
	g_mTelRa_shi=2;
	g_mTelRa_fen=3;//望远镜赤经时分秒
	g_mTelRa_miao=2.3;

	g_mTelDec_du=5;
	g_mTelDec_fen=2;//望远镜赤纬度分秒
	g_mTelDec_miao=5.6;
	
	g_mTelAzi_du=8;
	g_mTelAzi_fen=2;//望远镜方位度分秒
	g_mTelAzi_miao=5.8;
	g_mTelAlt_du=3;
	g_mTelAlt_fen=6;//望远镜高度度分秒
	g_mTelAlt_miao=2.5;
	
	g_mSitLon_du=12;
	g_mSitLon_fen=7;//观测地经度度分秒
	g_mSitLon_miao=1.3;
	g_mSitLon_WE=1;//东西京，正东经，负西经
	
	g_mSitLat_du=5;
	g_mSitLat_fen=1;//观测地纬度度度分秒
	g_mSitLat_miao=8.9;
	g_mSitLat_SN=1;//南北半球，正北半球，负南半球

	g_mTimeZone=8;//时区,正为东时区，负为西时区
	
//	g_mSitAlt=1863;//海拔
	
	g_mDate_year=2010;
    g_mDate_month=8;
	g_mDate_day=28;//观测日期
	g_mTime_hour=18;
	g_mTime_minute=18;
	g_mTime_second=18;//观测时间



	
	
	g_mSkyLand=0;//观测目标是天空还是陆地，0天空，1陆地
	g_mAzEq=0;//望远镜是地平式还是赤道式，0地平式，1赤道式
	
	g_mGps=0;//是否连接GPS，0没连接，1连接
	g_mHandSpeed=5;//手动速度档,0,1,2,3,4,5,6,7,8,9
	g_mHandSpeed1=0;
	g_mTelStatus=0;//望远镜运行状态，0停止，1指向，2跟踪,3移动状态,100为零位置状态
    g_mTelStatusSet=1; //望远镜暂停状态操作指示

	g_mGotoHandMove=false;//望远镜在跟踪时，是否要手动,true跟踪时有手动，false跟踪时没有手动
	g_mGotoHandMoveOK=false;


	 g_mRaAziGearError=0;//望远镜赤经或方位一次回差 ？角秒
     g_mRaAziGearEvenError=23.8;//望远镜赤经或方位平均回差	？角秒
     g_mRaAziGearErrorNum=0;//望远镜赤经或方位平均回差测量次数 
	 g_mRaAziGearErrorTotal=0;//远镜赤经或方位总次数回差 ？角秒

	 g_mDecAltGearError=0;//望远镜赤纬或方位一次回差 ？角秒
     g_mDecAltGearEvenError=23.8;//望远镜赤纬或方位平均回差	？角秒
     g_mDecAltGearErrorNum=0;//望远镜赤纬或方位平均回差测量次数 
	 g_mDecAltGearErrorTotal=0;//远镜赤纬或方位总次数回差 ？角秒

	g_mGearErrorAlign=false;//望远镜是否正在执行轴的回差校准,true正在执行,false没有


	g_mNowBestObjectNum=0;//当前最佳目标计数器 
	g_mSunSysObjectNum=0;//太阳系目标计数器
	g_mPopularNameObjectNum=0;//俗名星表目标计数器
	g_mMsrObjectNum=0;//M星表目标计数器
	g_mNgcObjectNum=0;//NGCIC星表目标计数器
	g_mIcObjectNum=0;//UGC星表目标计数器
	g_mSh2ObjectNum=0;//MCG星表目标计数器
	g_mBrightObjectNum=0;//Caldwell星表目标计数器
	g_mSaoObjectNum=0;//Abell星表目标计数器
	g_mHershelObjectNum=0;//Hershel星表目标计数器

	g_mCon88ObjectNum=1;//88星座计数器
	g_mCon88StarObjectNum=0;//88星座里星的计数器
  
    g_mFamousStarObjectNum=0;//恒星查找方式计数，0学名，1SAO编号,2HR编号
	g_mFixedStarObjectNum=0;//恒星星表目标计数器

	g_mDoubleStarObjectNum=0;//双星星表目标计数器
	g_mVariableStarObjectNum=0;//变星星表目标计数器



	g_mFindObjectAcc=1;//查找星表的速度档1,2,5,10,20,50,100,200,500,1000;

	g_mCountry=1;
	g_mCity=1;

    g_mGotoPause=false; //望远镜暂停标志

    g_mCurrentObjRa=0;
    g_mCurrentObjDec=0;  //当前目标位置


	g_mRecentTargetNum=0;//最近有几颗观测目标，最大8颗
    g_mTargetType=0;//目标类型，0错误类型，1太阳系天体，2星座，3著名恒星，4messier,5NGC,6IC,7sh2,8bright,9sao,10userstar,11specify,12 Landmark
    g_mTargetnum=0;//目标编号

	


	}

//获取系统时间
void GetSysTime()
{
    uint32  RTCtime;
	uint32  RTCdate;
	RTCtime = RTCtimeRead; // 读取完整时钟寄存器
	RTCdate = RTCdateRead;	// 读取完整日期寄存器
	// 取得年值
     g_mDate_year = (RTCdate>>16)&0xFFF;     
	// 取得月值
	g_mDate_month = (RTCdate>>8)&0x0F;       
	// 取得日值
	g_mDate_day = RTCdate&0x1F;            
	// 显示日值;
	      
	// 取得时的值
	g_mTime_hour = (RTCtime>>16)&0x1F;

	// 取得分的值		
	g_mTime_minute= (RTCtime>>8)&0x3F;	
	// 取得秒的值	
	g_mTime_second = RTCtime&0x3F;

    //取得毫秒
	g_mTime_wMilliseconds=RTCms*10;
	



//	 if((g_mDate_year>3000)||(g_mTime_hour>23))
//	 {
//	   FSetSysTime();
//
//	 }
//	 if((g_mDate_year<2000)||(g_mTime_hour>23))
//	 {
//	   FSetSysTime();
//	 }				
}
