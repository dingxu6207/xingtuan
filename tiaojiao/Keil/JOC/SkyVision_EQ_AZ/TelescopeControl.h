#include "stdbool.h"
#include <rtl.h>
#include <signal.h>
#include <stdio.h>
#include <math.h>



//头文件：TelescopeControl.h


//*******************************************
//*******************************************
//**********晶华GOTO望远镜控制函数说明 ******
//**********编者：柳光乾           **********
//**********2008年于云南天文台     **********
//**********lgq@ynao.ac.cn         **********
//*******************************************
//*******************************************


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@                         @@@@@@
//@@@@@@数据结构定义             @@@@@@
//@@@@@@                         @@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


////*******************************************
//系统时间数据结构
typedef struct{
    uint16 wYear;//年
    uint8 wMonth;//月
    uint8 wDay;//日
    uint8 wHour;//时
    uint8 wMinute;//分
    uint8 wSecond;//秒
    uint16 wMilliseconds;//毫秒
} SYSTEMTIME;
//*******************************************


//*******************************************
//观测地的位置数据结构
typedef struct {
	double mLongitude;//经度(-180度到180度)东正西负
	double mAtitude;//纬度(-90度到90度)北正南负
} LOCATION;
//*******************************************

//*******************************************
//观测目标赤道坐标数据结构
typedef struct {
	double mRightAscension;//赤经(0-24小时)
	double mDeclination;//赤纬(-90到90度)
	double mSiderealTime;//地方恒星时(0-24小时)
	double mHourAngle;//时角(0-24小时)
} STARRAD;
//*******************************************

//*******************************************
//观测目标地平坐标数据结构
typedef struct {
	double mASzimuth;//方位，正南为零，东负西正，-180度到180度
	double mANzimuth;//方位，正北为零，东负西正，0度到360度
	double mZenith;//天顶距，天顶为零，地平90度，0度到90度
	double mAtitude;//高度，地平为零，天顶90度，0零到90度
	double mAzimuthSpeed;//方位速度
	double mZenithSpeed;//天顶距速度
	double mAtitudeSpeed;//高度速度
	double mAzimuthAcc;//方位加速度
	double mZenithAcc;//天顶距加速度
} STARAZ;
//*******************************************


//*******************************************
//望远镜GOTOAZ数据结构
typedef struct {
	//**************************************
	//************
    ///系统参数
	int m_nTescpType;//望远镜型号
	double m_nTescpASpeedRatio;//方位传动比,望远镜速度输出码值比例因子，与传动比和码盘线数相关,一个读数值到角秒/秒的转换
	double m_nTescpESpeedRatio;//高度传动比,望远镜速度输出码值比例因子，与传动比和码盘线数相关,一个读数值到角秒/秒的转换
    double m_nTescpAPosRatio;//望远镜位置反馈码值比例因子，与传动比和码盘线数相关,一个读数值到度的转换
	double m_nTescpEPosRatio;//望远镜位置反馈码值比例因子，与传动比和码盘线数相关,一个读数值到度的转换
	
	int m_nSysTimeType;//系统时间类型,1北京时，2世界时
	bool m_nNutation;//计算地方恒星时是否加章动改正
	//************
	//观测地位置
	double m_nLongitude;//经度(-180度到180度)东正西负
	double m_nAtitude;//纬度(-90度到90度)北正南负
	int m_nTimeZone;//观测地时区(-12到12);
	//************
	//观测目标赤经赤纬
	int m_nObjectType;//观测目标类型，1恒星，2太阳，3行量，4彗星，5卫星,6静止目标
	double m_nRightAscension;//赤经(0-24小时)
	double m_nDeclination;//赤纬(-90到90度)
	double m_nHourAngle	;//目标时角
	double  m_nJday;//儒略日
	double  m_nJHour;//当天世界时的几小时换为天,以提供行星小时的插值
	//************
	//观测目标地平坐标
	double m_nStarAPos0;//目标方位理论计算坐标
    double m_nStarEPos0;//目标高度理论计算坐标
	double m_nStarAPosT;//目标方位望远镜坐标系坐标
    double m_nStarEPosT;//目标高度望远镜坐标系坐标 
	double m_nStarAPosTshow;//目标方位望远镜坐标系坐标,用于显示
    double m_nStarEPosTshow;//目标高度望远镜坐标系坐标,用于显示

	double m_nStarAPos;//目标方位望远镜跟踪坐标
    double m_nStarEPos;//目标高度望远镜跟踪坐标
	double m_nStarASpeed;//目标方位运行速度
	double m_nStarESpeed;//目标高度运行速度
    //望远镜运行状态
	double m_nTescpAPZero;// 望远镜的方位零点
	double m_nTescpEPZero;// 望远镜的高度零点
	double m_nTescpAPos;//望远镜的方位坐标
    double m_nTescpEPos;//望远镜的高度坐标
	double m_nAPosError;//星方位与望远镜方位的位置误差
	double m_nEPosError;//星高度与望远镜高度的位置误差
	double m_nAPosEIZero;//望远镜方位误差积分零点
    double m_nEPosEIZero;//望远镜高度误差积分零点
	double m_nTescpASpeed;//望远镜方位跟踪时的运行速度
	double m_nTescpESpeed;//望远镜高度跟踪时的运行速度
    double m_nTescpASpeedMax;//望远镜方位定位时的最大运行速度
	double m_nTescpESpeedMax;//望远镜高度跟踪时的最大运行速度
	double m_nTescpAAcc;//望远镜方位定位时的加速度
	double m_nTescpEAcc;//望远镜高度跟踪时的加速度
    double m_nTAState;//望远镜方位的运行状态,0为起动状态，1为定位状态，2为跟踪状态,3停止状态
	double m_nTEState;//望远镜高度的运行状态,0为起动状态，1为定位状态，2为跟踪状态,3停止状态
    bool m_nTGotoHandSpeed;//望远镜跟踪时，手动调节的速度
	double m_nTAHandMovePos;//望远镜跟踪时方位手动调节量
	double m_nTEHandMovePos;//望远镜跟踪时高度手动调节量
	bool m_nTCrossZeroP;//望远镜在运行时是否有正穿越
	bool m_nTCrossZeroN;//望远镜在运行时是否有负穿越
	int   m_nTPointDirect;//望远镜定位时最近距离的方向判断,0不变向，1望远镜增大方向，-1望远镜减小方向

	int m_nTelGotoPause;//望远镜定位跟踪转动过程中是否暂停,0不暂停，1暂停
	
	//望远镜Goto控制变量
	bool m_nGoto;//望远镜是否在运行Goto状态；true运行在Goto状态,false没有在停止状态
    bool m_nStartStop;//望远镜起停止变量，true;起动Goto,false,停止Goto
	bool m_nUnderhorizon;//星是否在地平线下

    //望远镜自动校准变量：
	int m_nAlignStarNum;//设置几颗星校准
    bool m_nAlign;//望远镜是否已经校过,true校过了，false还没有校准
	bool m_nAlignAdjust;//望远镜是否调节误差了
	int m_nTAlignState;//望远镜是否在校正状态
    int m_nAlignAdjustNum;//望远镜校准时调节次数

	double m_nAlignStarRA1;//赤经(0-24小时)
	double m_nAlignStarDec1;//赤纬(-90到90度)
	double m_nAlignStarRA2;//赤经(0-24小时)
	double m_nAlignStarDec2;//赤纬(-90到90度)
	double m_nAlignStarRA3;//赤经(0-24小时)
	double m_nAlignStarDec3;//赤纬(-90到90度)

	double m_nANzimuth1;//方位，正北为零，东负西正，0度到360度
	double m_nAtitude1;//高度，地平为零，天顶90度，0零到90度
	double m_nAPointEerror1;
	double m_nEPointEerror1;
	double m_nANzimuth2;//方位，正北为零，东负西正，0度到360度
	double m_nAtitude2;//高度，地平为零，天顶90度，0零到90度
	double m_nAPointEerror2;
	double m_nEPointEerror2;
	double m_nANzimuth3;//方位，正北为零，东负西正，0度到360度
	double m_nAtitude3;//高度，地平为零，天顶90度，0零到90度
	double m_nAPointEerror3;
	double m_nEPointEerror3;

	double m_nTSettingNP;//不垂直
	double m_nTSettingLOS;//光轴偏差
	double m_nTSettingNS;//北顷
	double m_nTSettingEW;//东倾
	double m_nTSettingA0;//方位零偏
	double m_nTSettingE0;//高度零偏	 

	double m_nTSettingAA0;//方位零偏备用,
	double m_nTSettingEE0;//方位零偏备用,

	double  m_nGuidMoveRa;//光电导星赤经偏移量
	double m_nGuidMoveDec;//光电导星赤纬偏移量
    
	//计算在气蒙气差
//	double m_nAirP;//大气压mba
//	double m_nAirT;//温度c
//	double m_nSiteHigh;//海拔km
//	double m_nAirR;//大气蒙气差下

} GOTOAZDATA;
//*******************************************


//*******************************************
//望远镜校正星的位置、误差数据结构
typedef struct {
	double mANzimuth1;//方位，正北为零，东负西正，0度到360度
	double mAtitude1;//高度，地平为零，天顶90度，0零到90度
	double mAPointEerror1;//误差(度)
	double mEPointEerror1;//误差(度)
	double mANzimuth2;//方位，正北为零，东负西正，0度到360度
	double mAtitude2;//高度，地平为零，天顶90度，0零到90度
	double mAPointEerror2;//误差(度)
	double mEPointEerror2;//误差(度)
	double mANzimuth3;//方位，正北为零，东负西正，0度到360度
	double mAtitude3;//高度，地平为零，天顶90度，0零到90度
	double mAPointEerror3;//误差(度)
	double mEPointEerror3;//误差(度)
} CALSTARAZ;
//*******************************************


//*******************************************
//望远镜的安装误差数据结构
typedef struct {
	double mTSettingNP;//不垂直(度)
	double mTSettingLOS;//光轴偏差(度)
	double mTSettingNS;//北顷(度)
	double mTSettingEW;//东倾(度)
	double mTSettingA0;//方位零偏(度)
	double mTSettingE0;//高度零偏(度)
} TSETTING;
//*******************************************


//*******************************************
//观测目标校正数据结构
typedef struct {
	double mSAzimuth;//方位，正南为零，东负西正，-180度到180度
	double mSZenith;//天顶距，天顶为零，地平90度，0度到90度
    double mTSAzimuth;//方位，正南为零，东负西正，-180度到180度
	double mTSZenith;//天顶距，天顶为零，地平90度，0度到90度
} ALIGNSTARAZ;
//*******************************************



//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@                         @@@@@@
//@@@@@@函数定义                 @@@@@@
//@@@@@@                         @@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


//******函数功能:赤道式望远镜定位跟踪函数
//*********************************************************************************************
//*********************************************************************************************
//******函数定义                                                                         
void GotoEQ();          
//进出口参数:GOTOAZDATA型全局变量
//影响资源，GOTOAZDATA型全局变量g_mJHGotoAZ
//*********************************************************************************************
//*********************************************************************************************


//******函数功能:地平式望远镜定位跟踪函数
//*********************************************************************************************
//*********************************************************************************************
//******函数定义                                                                         
void GotoAZ();          
//进出口参数:GOTOAZDATA型全局变量
//影响资源，GOTOAZDATA型全局变量g_mJHGotoAZ
//*********************************************************************************************
//*********************************************************************************************


//******函数功能:计算地方恒星时
//*********************************************************************************************
//*********************************************************************************************
//******函数定义                                                                         
double FCalSiderealTime(int fSysTimeType,bool fNutation ,double fLongitude);           
//******                                                                                 
//******
//******入口参数：
//******
//******参数1：fSysTimeType系统时间类型,1北京时，2世界时
//******参数2：fNutation是加章动改，fNutation为假不加章动改正,fNutation为真加章动改正
//******参数3：fLongitude观测地经度，以度表示，东经为正，西经为负,范围（-180度到+180度)
//******
//******出口参数：
//******观测地的地方恒星时，以小时表示，浮点型，范围0-24小时
//*********************************************************************************************
//*********************************************************************************************


//*******************************************
//******函数功能:从赤道坐标到地平坐标
//*********************************************************************************************
//*********************************************************************************************
//******函数定义
void FCalStarAEPos(LOCATION floct,STARRAD fstar,int fSysTimeType,bool fNutation,STARAZ *fstaraz);
//入口参数：
//******参数1：floct,观测地位置，LOCATION型数据
//******参数2：fstar,观测星赤道坐标，STARRAD型数据
//******参数3：fSysTimeType系统时间类型,1北京时，2世界时
//******参数4：fNutation是加章动改，fNutation为假不加章动改正,fNutation为真加章动改正
//******出口参数：
//******星的地平坐标fstaraz，STARAZ指针型
//*********************************************************************************************
//*********************************************************************************************

//*******************************************
//******函数功能:从地平坐标到赤道坐标
//*********************************************************************************************
//*********************************************************************************************
//******函数定义
void FCalStarEQPos(double azi,double alt,double *ra,double *dec);  
//入口参数：
//******参数1：wd 观测的纬度（度）
//******参数2：sidleraltime地方恒星时（时）
//******参数3：azi方位角
//******参数4：alt高度角
//******出口参数：
//******星的赤道坐标ra赤经，dec赤纬
//*********************************************************************************************
//*********************************************************************************************



//*******************************************
//******函数功能://安装误差对星的位置改正计算
//*******************************************
//******函数定义:
void FAlignStarAEPos(TSETTING ftsetting,ALIGNSTARAZ *falignstaraz);
//入口参数：
//******参数1:	ftsetting是TSETTING结构
//******参数2:	falignstaraz是ALIGNSTARAZ数据结构,
//出口参数：
//******参数： falignstaraz是TSETTING
//falignstaraz的前两个参数为入口参数，后两个参数为出口参数.
//*******************************************


//*******************************************
//******函数功能://计算大气蒙气差
//*******************************************
//******函数定义:
//double FAirRefraction(double fAirT,double fAirP,double fzernith);
//入口参数：
//参数1：fAirT空气湿度（摄氏度)
//参数2：fAirP在气压（mbar)
//参数3：fzernith天顶距（度)
//出口参数：
//天顶距变化量
//*******************************************;


//*******************************************
//******函数功能:读取望远镜的位置
//*******************************************
//******函数定义:
void FReadTelescopePos(double *fAZimuth,double *fAltitude);
//入口参数：
//******参数1:	fAZimuth望远镜方位地址
//******参数2:	fAltitude望远镜高度地址
//出口参数：
//******参数1:	*fAZimuth望远镜方位
//******参数2:	*fAltitude望远镜高度
//*******************************************


//*******************************************
//******函数功能:望远镜跟踪误差处理
//*******************************************
//******函数定义:
double FPointStarAlgorithm (int fTescpType,int fAxis,double fPosEIZero,double fPosError,double fObjectSpeed);
//入口参数：
//******参数1:	fTescpType望远镜型号
//******参数2:	fAxis望远镜运行轴，1方位，2高度
//******参数3:	fPosEIZero,积分初值
//******参数4： fPosError跟踪误差
//******参数5： fObjectSpeed目标速度
//出口参数：误差处理后的量
//影响资源：全局变量g_mJHGotoAZ里的m_nAPosEIZero和m_nEPosEIZero//望远镜方位误差积分零点m_nEPosEIZero;//望远镜高度误差积分零点
//*******************************************


//*******************************************
//******函数功能:向望远镜输出控制信号
//*******************************************
//******函数定义:
void FDriveTelescope(double faspeed,double fzspeed);
//入口参数：
//******参数1:	faspeed望远镜方位速度
//******参数2:	fzspeed望远镜高度速度
//*******************************************


//*******************************************
//******函数功能:起动望远镜GOTO
//*******************************************
//******函数定义:
void FStartGoto();
//*******************************************

//*******************************************
//******函数功能:停止望远镜GOTO
//*******************************************
//******函数定义:
void FStopGoto();
//*******************************************

//*******************************************
//望远镜暂停GOTO
void FPauseGoto();
//*******************************************

//*******************************************
//望远镜继续GOTO
void FContinueGoto();
//*******************************************

//*******************************************
//******函数功能://指向新目标
//*******************************************
//******函数定义:
void FPointNewStar(double fRightAscension,double fDeclination);
//入口参数：
//参数1：新目标星的赤经
//参数2：新目标星的赤纬
//*******************************************


//*******************************************
//******函数功能://安装误差计算
//*******************************************
//******函数定义:
void FStarCal(int fstarnum,CALSTARAZ fStarsPos,TSETTING *fTSetting);
//入口参数：
//******参数1:	fstarnum校准星的数目：1，一颗星，2两颗星，3三颗星
//******参数2:	fStarsPos是CALSTARAZ数据结构
//出口参数：
//******参数1： fTSetting是TSETTING
//*******************************************


//*******************************************
//******函数功能:望远镜自动校准
//*******************************************
//******函数定义:
void FAutoAlign();
//*******************************************

//*******************************************
//******函数功能:望远镜自动校准对星有没有对准
//*******************************************
//******函数定义:
void FPointAlignStarOk();
//*******************************************


//*******************************************
//******函数功能:起动望远镜GOTO
//*******************************************
//******函数定义:
void FStartGoto();
//*******************************************

//*******************************************
//******函数功能:停止望远镜GOTO
//*******************************************
//******函数定义:
void FStopGoto();
//*******************************************


//*******************************************
//******函数功能://指向新目标
//*******************************************
//******函数定义:
void FPointNewStar(double fRightAscension,double fDeclination);
//入口参数：
//参数1：新目标星的赤经
//参数2：新目标星的赤纬
//*******************************************
//两颗星自动校准
void FTwoStarAutoAlign();

//******函数功能://一颗星自动校准
//*******************************************
//******函数定义:
void FOneStarAlign();
//******************************************

//******函数功能://两颗星自动校准
//*******************************************
//******函数定义:
void FTwoStarAlign();
//******************************************

//******函数功能://三颗星自动校准
//*******************************************
//******函数定义:
void FThreeStarAlign();
//******************************************



//******函数功能://获取系统时间
//*******************************************
//******函数定义:
void GetLocalTime(SYSTEMTIME *time);
//入口参数：
//******参数1:	YSTIME型指针变量
//出口参数：
//******参数1： YSTIME型数据里面年月日时分秒毫秒
//*******************************************


//*************函数功能://望远镜控制参数初始化
void FSetupPointTrackPara();
//*******************************************


//*************函数功能://手柄蜂鸣
void FBeep(uint8 fsceond);
void FBeep1(uint8 fsceond);
//*******************************************

 //两颗星校准计算
void FTowStarCal(CALSTARAZ fStarsPos,TSETTING *fTSetting) ;

//一颗星校准计算
void FOneStarCal(CALSTARAZ fStarsPos,TSETTING *fTSetting) ;
//三颗星校准计算
void FThreeStarCal(CALSTARAZ fStarsPos,TSETTING *fTSetting);

  //计算星体升落时间
//selectnum=1:升起, =2:中天, =3:下落
double FSiseSettime(int selectnum)	;
//定位跟踪驱动输出
void FDriveTelescopeNew() ;

//计算星校准后的赤道位置
void FAlignStarRAPos(TSETTING ftsetting,double *m_HUOR,double *m_Dec);

//查找校准星
//uint8 FindAlignStar(float fstime,float flat,float* fraddec,char Align_Star_Name[10][10],char Align_Star_NameCnn[10][22]);



