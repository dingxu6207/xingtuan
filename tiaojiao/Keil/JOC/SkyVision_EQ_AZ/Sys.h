#include "stdbool.h"

#include <rtl.h>
#include <signal.h>
#include <stdio.h>

//系统常量变量函数定义
//*************************************************
//*************************************************	
//菜单所用常量定义
//按键对应值定义
//	新键盘
#define  KEY_NUM0     0
#define  KEY_NUM1     1
#define  KEY_NUM2     2
#define  KEY_NUM3     3
#define  KEY_NUM4     4
#define  KEY_NUM5     5
#define  KEY_NUM6     6
#define  KEY_NUM7     7
#define  KEY_NUM8     8
#define  KEY_NUM9     9
#define  KEY_XH       10
#define  KEY_WH       11
#define  KEY_MENU     12
#define  KEY_BACK     13
#define  KEY_UP       14
#define  KEY_DOWN     15
#define  KEY_LEFT     16
#define  KEY_RIGHT    17
#define  KEY_ENTER    19
#define  KEY_TORCH    20

#define  KEY_LEFTDOWN	 21					     
#define  KEY_LEFTUP	     22
#define  KEY_RIGHTDOWN	 23
#define  KEY_RIGHTUP	 24



//老键盘
//#define  KEY_NUM0     10
//#define  KEY_NUM1     2
//#define  KEY_NUM2     7
//#define  KEY_NUM3     12
//#define  KEY_NUM4     3
//#define  KEY_NUM5     8
//#define  KEY_NUM6     13
//#define  KEY_NUM7     4
//#define  KEY_NUM8     9
//#define  KEY_NUM9     14
//#define  KEY_XH       5
//#define  KEY_WH       15
//
//#define  KEY_MENU     18
//#define  KEY_BACK     19
//#define  KEY_UP       16
//#define  KEY_DOWN     6
//#define  KEY_LEFT     1
//#define  KEY_RIGHT    11
//#define  KEY_ENTER    17
//#define  KEY_TORCH    100  //老键盘没有这个，只位程序由此
//
//#define  KEY_LEFTDOWN	 21					     
//#define  KEY_LEFTUP	     22
//#define  KEY_RIGHTDOWN	 23
//#define  KEY_RIGHTUP	 24

//*******************************************************
//*******************************************************
//********************
//系统状态定义
#define SYS_MAINSHOW  0	//系统在零状态为主要的待机屏显示状态
#define SYS_MENUSHOW  1 //刚观测过星的显示
#define SYS_NOTELSCOPE  2 //没有望远镜状态
#define SYS_RESET 100//系统出厂状态


#define SYS_F_SELFNUM  101  //进入F陆地目标和天空目标GOTO功能
#define SYS_F_SELFNUM_SEL 102 

//#define SYS_MENU_LANDSKY_OBJECT 200//进入陆地目标和天空自定义功能 
#define SYS_MENU_SKY_OBJECT 201
#define SYS_MENU_LAND_OBJECT 202

#define SYS_MENU_SKY_NAME 203
#define SYS_MENU_SKY_RA 204
#define SYS_MENU_SKY_DEC 205


#define SYS_MENU_LAND_NAME 206
#define SYS_MENU_LAND_AZI 207
#define SYS_MENU_LAND_ALT 208





 
//********************
//菜单状态一级菜单（主菜单）
#define SYS_MAINMENU1  1000	//系统主菜单第一项值
#define SYS_MAINMENU2  2000	//系统主菜单第二项值
#define SYS_MAINMENU3  3000 //系统主菜单第三项值
#define SYS_MAINMENU4  4000	//系统主菜单第四项值
//子菜单（二级菜单）
//望远镜校正子菜单
#define SYS_SUB1MENU1  1100	//系统子菜单1第一项值
#define SYS_SUB1MENU2  1200	//系统子菜单1第二项值
#define SYS_SUB1MENU3  1300	//系统子菜单1第三项值
#define SYS_SUB1MENU4  1400	//系统子菜单1第四项值
#define SYS_SUB1MENU5  1500	//系统子菜单1第五项值
#define SYS_SUB1MENU6  1600	//系统子菜单1第六项值
#define SYS_SUB1MENU7  1700	//系统子菜单1第七项值
//目标导航子菜单
#define SYS_SUB2MENU1  2100	//系统子菜单2第一项值
#define SYS_SUB2MENU2  2200	//系统子菜单2第二项值
#define SYS_SUB2MENU3  2300	//系统子菜单2第三项值
#define SYS_SUB2MENU4  2400	//系统子菜单2第四项值
#define SYS_SUB2MENU5  2500	//系统子菜单2第五项值
#define SYS_SUB2MENU6  2600	//系统子菜单2第六项值
#define SYS_SUB2MENU7  2700	//系统子菜单2第七项值
#define SYS_SUB2MENU8  2800	//系统子菜单2第八项值
#define SYS_SUB2MENU9  2900	//系统子菜单2第九项值
#define SYS_SUB2MENU11 2110	//系统子菜单2第十项值
#define SYS_SUB2MENU12 2120	//系统子菜单2第十一项值
#define SYS_SUB2MENU13 2130	//系统子菜单2第十二项值
//工具命令子菜单
#define SYS_SUB3MENU1  3100	//系统子菜单3第一项值
#define SYS_SUB3MENU2  3200	//系统子菜单3第二项值
#define SYS_SUB3MENU3  3300	//系统子菜单3第三项值
#define SYS_SUB3MENU4  3400	//系统子菜单3第四项值
#define SYS_SUB3MENU5  3500	//系统子菜单3第五项值
#define SYS_SUB3MENU6  3600	//系统子菜单3第六项值
#define SYS_SUB3MENU7  3700	//系统子菜单3第七项值
#define SYS_SUB3MENU8  3800	//系统子菜单3第八项值
#define SYS_SUB3MENU9  3900	//系统子菜单3第九项值
//参数设置子菜单
#define SYS_SUB4MENU1  4100	//系统子菜单4第一项值
#define SYS_SUB4MENU2  4200	//系统子菜单4第二项值
#define SYS_SUB4MENU3  4300	//系统子菜单4第三项值
#define SYS_SUB4MENU4  4400	//系统子菜单4第四项值
#define SYS_SUB4MENU5  4500	//系统子菜单4第五项值
#define SYS_SUB4MENU6  4600	//系统子菜单4第六项值
#define SYS_SUB4MENU7  4700	//系统子菜单4第七项值
#define SYS_SUB4MENU8  4800	//系统子菜单4第八项值
#define SYS_SUB4MENU9  4900	//系统子菜单4第九项值
//子子菜单（三级菜单）
//望远镜同步
#define SYS_SUB1SUB4MENU1  1401	//进入同步
#define SYS_SUB1SUB4MENU2  1402	//确认同步
#define SYS_SUB1SUB4MENU3  1403 //取消同步
//太阳系子菜单
#define SYS_SUB2SUB2MENU1  2201	//系统子子菜单1第一项值
#define SYS_SUB2SUB2MENU2  2202	//系统子子菜单1第二项值
#define SYS_SUB2SUB2MENU3  2203	//系统子子菜单1第三项值
#define SYS_SUB2SUB2MENU4  2204	//系统子子菜单1第四项值
#define SYS_SUB2SUB2MENU5  2205	//系统子子菜单1第五项值
#define SYS_SUB2SUB2MENU6  2206	//系统子子菜单1第六项值
#define SYS_SUB2SUB2MENU7  2207	//系统子子菜单1第七项值
#define SYS_SUB2SUB2MENU8  2208	//系统子子菜单1第八项值
#define SYS_SUB2SUB2MENU9  2209	//系统子子菜单1第九项值
#define SYS_SUB2SUB2MENU11 22011//系统子子菜单1第十项值
#define SYS_SUB2SUB2MENU12 22012//系统子子菜单1第十一项值
//深空天体子菜单
#define SYS_SUB2SUB3MENU1  2301	//系统子子菜单2第一项值
#define SYS_SUB2SUB3MENU2  2302	//系统子子菜单2第二项值
#define SYS_SUB2SUB3MENU3  2303	//系统子子菜单2第三项值
#define SYS_SUB2SUB3MENU4  2304	//系统子子菜单2第四项值
#define SYS_SUB2SUB3MENU5  2305	//系统子子菜单2第五项值
#define SYS_SUB2SUB3MENU6  2306	//系统子子菜单2第六项值
#define SYS_SUB2SUB3MENU7  2307	//系统子子菜单2第七项值
#define SYS_SUB2SUB3MENU8  2308	//系统子子菜单2第八项值
//恒星子菜单
#define SYS_SUB2SUB5MENU1  2501	//系统子子菜单3第一项值
#define SYS_SUB2SUB5MENU2  2502	//系统子子菜单3第二项值
#define SYS_SUB2SUB5MENU3  2503	//系统子子菜单3第三项值

//自定义星表子菜单
#define SYS_SUB2SUB8MENU1  2801	//系统子子菜单4第一项值
#define SYS_SUB2SUB8MENU2  2802	//系统子子菜单4第二项值
#define SYS_SUB2SUB8MENU3  2803	//系统子子菜单4第三项值
#define SYS_SUB2SUB8MENU4  2804	//系统子子菜单4第四项值
#define SYS_SUB2SUB8_SET   28001
//陆地目标子菜单
#define SYS_SUB2SUB11MENU1  21101	//系统子子菜单5第一项值
#define SYS_SUB2SUB11MENU2  21102	//系统子子菜单5第二项值
#define SYS_SUB2SUB11MENU3  21103	//系统子子菜单5第三项值
#define SYS_SUB2SUB11_SET   211001	
//目镜计算子菜单
#define SYS_SUB3SUB6MENU1  3601	//系统子子菜单8第一项值
#define SYS_SUB3SUB6MENU2  3602	//系统子子菜单8第二项值


//暗视野照明子菜单
#define SYS_SUB3SUB8MENU1  3801	//系统子子菜单9第一项值
#define SYS_SUB3SUB8MENU2  3802	//系统子子菜单9第二项值
//地点设置子菜单
#define SYS_SUB4SUB3MENU1  4301	//系统子子菜单10第一项值
#define SYS_SUB4SUB3MENU2  4302	//系统子子菜单10第二项值
//望远镜型号子菜单
//#define SYS_SUB4SUB7MENU1  4701	//系统子子菜单12第一项值
//#define SYS_SUB4SUB7MENU2  4702	//系统子子菜单12第二项值
//#define SYS_SUB4SUB7MENU3  4703	//系统子子菜单12第三项值
//#define SYS_SUB4SUB7MENU4  4704	//系统子子菜单12第四项值

//跟踪速度子菜单
#define SYS_SUB4SUB8MENU1  4801	//系统子子菜单13第一项值
#define SYS_SUB4SUB8MENU2  4802	//系统子子菜单13第二项值
#define SYS_SUB4SUB8MENU3  4803	//系统子子菜单13第三项值
#define SYS_SUB4SUB8MENU4  4804	//系统子子菜单13第四项值
//*******************************************
//*******************************************



//菜单最底层实现
//第一层子菜单第一项:望远镜校正
//#define SYS_SUB1SUB1AUTOSTAR_ALIGN  11001 //自动双星校准

#define SYS_SUB1SUB2STAR_ALIGN  12001 //一星校准	 两星校准 三星校准 显示状态




#define SYS_SUB1SUB8POLE_AXIS_ERROR  18001 //望远镜极轴偏差显示



#define SYS_SUB1SUB11RA_GEAR_ERROR 11101 //赤经回差校正
#define SYS_SUB1SUB11RA_GEAR_ERROR_BEGIN 11102//赤经回差校正开始
#define SYS_SUB1SUB11RA_GEAR_ERROR_ALIGN 11103 //赤经回差正在校正
#define SYS_SUB1SUB11RA_GEAR_ERROR_ALIGN_OK  11104//完成一次回差赤经回差校正
#define SYS_SUB1SUB11RA_GEAR_ERROR_ALIGN_END  11105//完成多次赤经回差校正

#define SYS_SUB1SUB12DEC_GEAR_ERROR 11201 //赤纬回差校正
#define SYS_SUB1SUB12DEC_GEAR_ERROR_BEGIN 11202//赤纬回差校正开始
#define SYS_SUB1SUB12DEC_GEAR_ERROR_ALIGN 11203 //赤纬回差正在校正
#define SYS_SUB1SUB12DEC_GEAR_ERROR_ALIGN_OK  11204//完成一次回差赤纬回差校正
#define SYS_SUB1SUB12DEC_GEAR_ERROR_ALIGN_END  11205//完成多次赤纬回差校正

//第一层子菜单第二项：目标导航
#define SYS_SUB2SUB1NOW_OBJECT   21001   //当前最佳目标
#define SYS_SUB2SUN_PLANET   22001	//太阳系统目标
#define SYS_SUB2SUN_PLANET1   22111	//太阳系统目标
#define SYS_SUB2SUN_SUNWARN	  22112	//指向太阳警告

#define SYS_SUB2SUB3PN_OBJECT   23001   //俗名星表目标

#define SYS_SUB2MSR_OBJECT   23002   //M星表目标
#define SYS_SUB2MSR_OBJECT0   23012   //M星表目标
#define SYS_SUB2MSR_OBJECT1   23022   //M星表目标

#define SYS_SUB2NGC_OBJECT   23003   //NGCIC星表目标
#define SYS_SUB2NGC_OBJECT1   23013   //NGCIC星表目标   

#define SYS_SUB2IC_OBJECT   23004   //UGC星表目标
#define SYS_SUB2IC_OBJECT1   23014   //UGC星表目标

#define SYS_SUB2SH2_OBJECT   23005   //MCG星表目标
#define SYS_SUB2SH2_OBJECT1   23015   //MCG星表目标

#define SYS_SUB2BRT_OBJECT   23006   //Caldwell星表目标
#define SYS_SUB2BRT_OBJECT1   23016   //Caldwell星表目标

#define SYS_SUB2SAO_OBJECT   23007   //Abell星表目标
#define SYS_SUB2SAO_OBJECT1   23017   //Abell星表目标

#define SYS_SUB2SUB3HER_OBJECT   23008   //Hershel星表目标

#define SYS_SUB2CON_OBJECT   24001   //88星座星表目标
#define SYS_SUB2CON_OBJECT1   24002   //88星座星表目标

#define SYS_SUB2FS_OBJECT   25001   //恒星星表目标
#define SYS_SUB2FS_OBJECT1   25002   //恒星星表目标

#define SYS_SUB2SUB6DS_OBJECT   26001   //双星星表目标
#define SYS_SUB2SUB7VS_OBJECT   27001   //变星星表目标


#define SYS_SUB2SUB9RA   29001   //望远镜赤经赤纬输入
#define SYS_SUB2SUB9DEC  29002   //望远镜赤经赤纬输入
//第一层子菜单第三项：工具命令
#define SYS_SUB3SUB1NOW_APH   31001   //今日天像
 #define SYS_SUB3SUB2_STARRISESET  32001 //星体升落
#define SYS_SUB3SUB3_MOONPHASE 33001	//月相查寻状态
//倒计时子菜单
#define SYS_SUB3SUB4TIMER_INPUT 34001	//定时输入
#define SYS_SUB3SUB4TIMER_ONOFF 34002	//定时起动/停止
//定时闹钟子菜单
#define SYS_SUB3SUB5ALARM_INPUT  35001	//闹钟输入
#define SYS_SUB3SUB5ALARM_ONOFF  35002	//闹钟开启/关闭
//***************************************************************************************
//目镜计算.视野
#define SYS_SUB3SUB6SUB1LOV_TELTYPE1 360011 //望远镜型号选择
#define SYS_SUB3SUB6SUB1LOV_TELTYPE2 360012 //望远镜型号选择
#define SYS_SUB3SUB6SUB1LOV_TELTYPE3 360013 //望远镜型号选择

#define SYS_SUB3SUB6SUB1MENU1       360111
#define SYS_SUB3SUB6SUB1MENU2       360112
#define SYS_SUB3SUB6SUB1MENU3       360113

//目镜计算.倍率
#define SYS_SUB3SUB6SUB2M_MF 360021       //主镜焦距输入状态
#define SYS_SUB3SUB6SUB2M_SF 360022     //副镜焦距输入状态	  
#define SYS_SUB3SUB6SUB2M_Multi 360023 //放大倍数显示状态

#define SYS_SUB3SUB6SUB2M_MF1 370021       //主镜焦距输入状态
#define SYS_SUB3SUB6SUB2M_SF1 370022     //副镜焦距输入状态	  
#define SYS_SUB3SUB6SUB2M_MFOV 370023 //放大倍数显示状态

//暗视野照明
#define SYS_SUB3SUB8MENU1Screen 380011

//夏令时间
#define SYS_SUB4SUB2MENU1 42001
#define SYS_SUB4SUB2MENU2 42002
//***************************************************************************************
#define SYS_MAINSHOWHELP    500	//系统在零状态为主要的待机屏显示状态
//********************
//菜单状态一级菜单（主菜单）
#define SYS_MAINMENU1HELP  501	//系统主菜单第一项值
#define SYS_MAINMENU2HELP  502	//系统主菜单第二项值
#define SYS_MAINMENU3HELP  503 //系统主菜单第三项值
#define SYS_MAINMENU4HELP  504	//系统主菜单第四项值
//子菜单（二级菜单）
//望远镜校正子菜单
#define SYS_SUB1MENU1HELP  505	//系统子菜单1第一项值
#define SYS_SUB1MENU2HELP  506	//系统子菜单1第二项值
#define SYS_SUB1MENU3HELP  507	//系统子菜单1第三项值
#define SYS_SUB1MENU4HELP  508	//系统子菜单1第四项值
#define SYS_SUB1MENU5HELP  509	//系统子菜单1第五项值
#define SYS_SUB1MENU6HELP  510	//系统子菜单1第六项值
#define SYS_SUB1MENU7HELP  511	//系统子菜单1第七项值
//目标导航子菜单
#define SYS_SUB2MENU1HELP  516	//系统子菜单2第一项值
#define SYS_SUB2MENU2HELP  517	//系统子菜单2第二项值
#define SYS_SUB2MENU3HELP  518	//系统子菜单2第三项值
#define SYS_SUB2MENU4HELP  519	//系统子菜单2第四项值
#define SYS_SUB2MENU5HELP  520	//系统子菜单2第五项值
#define SYS_SUB2MENU6HELP  521	//系统子菜单2第六项值
#define SYS_SUB2MENU7HELP  522	//系统子菜单2第七项值
#define SYS_SUB2MENU8HELP  523	//系统子菜单2第八项值
#define SYS_SUB2MENU9HELP  524	//系统子菜单2第九项值
#define SYS_SUB2MENU11HELP 525	//系统子菜单2第十项值
#define SYS_SUB2MENU12HELP 526	//系统子菜单2第十一项值
#define SYS_SUB2MENU13HELP 527	//系统子菜单2第十二项值
//工具命令子菜单
#define SYS_SUB3MENU1HELP  528	//系统子菜单3第一项值
#define SYS_SUB3MENU2HELP  529	//系统子菜单3第二项值
#define SYS_SUB3MENU3HELP  530	//系统子菜单3第三项值
#define SYS_SUB3MENU4HELP  531	//系统子菜单3第四项值
#define SYS_SUB3MENU5HELP  532	//系统子菜单3第五项值
#define SYS_SUB3MENU6HELP  533	//系统子菜单3第六项值
#define SYS_SUB3MENU7HELP  534	//系统子菜单3第七项值
#define SYS_SUB3MENU8HELP  535	//系统子菜单3第八项值
#define SYS_SUB3MENU9HELP 537	//系统子菜单3第十项值
//参数设置子菜单
#define SYS_SUB4MENU1HELP  538	//系统子菜单4第一项值
#define SYS_SUB4MENU2HELP  539	//系统子菜单4第二项值
#define SYS_SUB4MENU3HELP  540	//系统子菜单4第三项值
#define SYS_SUB4MENU4HELP  541	//系统子菜单4第四项值
#define SYS_SUB4MENU5HELP  542	//系统子菜单4第五项值
#define SYS_SUB4MENU6HELP  543	//系统子菜单4第六项值
#define SYS_SUB4MENU7HELP  544	//系统子菜单4第七项值
#define SYS_SUB4MENU8HELP  545	//系统子菜单4第八项值
#define SYS_SUB4MENU9HELP  546	//系统子菜单4第九项值

//*******************************************************************************


//第一层子菜单第四项：参数设置

#define SYS_SUB4SUB1_SETTIME 41001  //系统时间设置

#define SYS_SUB4SUB3SUN1_CITYSEL  43011	//城市选择

#define SYS_SUB4SUB3_SETSITE 43002  //自定义地点 

#define SYS_SUB4SUB3SUB2_SELECT  43021	//自定义地点选择
#define SYS_SUB4SUB3SUB2_ADD  43022	//自定义地点增加
#define SYS_SUB4SUB3SUB2_DELETE  43023	//自定义地点删除
#define SYS_SUB4SUB3SUB2_MODIFY  43024	//自定义地点修改

//#define SYS_SUB4SUB4WEATHER  44001  //气象子菜单

#define SYS_SUB4SUB5SKY   45001   //观测目标天空模式选择
#define SYS_SUB4SUB5LAND   45002   //观测目标陆地模式选择

#define SYS_SUB4SUB6AZ   46001   //望远镜装置地平式选择
#define SYS_SUB4SUB6EQ   46002   //望远镜装置赤道式选择

//望远镜型号子菜单
//#define SYS_SUB4SUB7SUB1_TELSEL   47011	 //系统子子菜单12第一项值
//#define SYS_SUB4SUB7SUB2_TELADD   47021	//系统子子菜单12第二项值
//#define SYS_SUB4SUB7SUB3_TELDEL   47031	//系统子子菜单12第三项值
//#define SYS_SUB4SUB7SUB4_TELMOD   47041	//系统子子菜单12第四项值

//望远镜零点子菜单
#define SYS_SUB4SUB7_TELAZIALT_ZERO   47011	 //设置方位零点
//#define SYS_SUB4SUB7_TELALT_ZERO   47021	//设置高度零点
//#define SYS_SUB4SUB7_TELZERO_ERROR   47031	//零点设置错误
#define SYS_SUB4SUB7_TELZERO_OK   47041	//零点设置正确



#define SYS_SUB4SUB8MENU4_RASPEED  48001	//望远镜赤经跟踪速度


#define SYS_SUB4SUB9EN   49001   //菜单语言选择
#define SYS_SUB4SUB9GER   49002   //菜单语言选择
#define SYS_SUB4SUB9FRE   49003   //菜单语言选择
#define SYS_SUB4SUB9ITA   49004   //菜单语言选择
#define SYS_SUB4SUB9SPA   49005   //菜单语言选择

//*******************************************
//*******************************************
//帮助状态
#define SYS_MAINHELP  5000//系统帮助状态（主帮助状态)

//*******************************************************
//*******************************************************

char *g_sTelType1;
char *g_sTelType2;
char *g_sTelType3;
char *g_sTelType4;
char *g_sTelType5;
char *g_sTelType6;
char *g_sTelType7;
char *g_sTelType8;


//变量定义	
//系统状态
uint8 g_mhelpshow;//显示状态，0菜单，1帮助
uint8 g_mmainhelpshow;//主菜单显示状态

uint8 g_mKeyBeepOpen;//按键蜂鸣开关0,关，1开，按F+0操作


int g_nAlignStar;//自定义校准星数目最大为3
uint8 g_nSelAlignStarNum;//所选择了自定义校准星是第几颗
uint8 g_nSeledAlignStarNum;//选择了几次星
bool g_nAlignPoint;//望远镜在一星两星三星校正时是调节确认还是选择，false选择星，true校正调节确认

uint32 g_nsysstatus;  //系统状态
bool g_bkeyoperator;//望远镜按下的键是否得到响应
uint8  m_nkeyvalue;//按键值变量

bool g_mDaylight;//是否采用夏令时,true采用，false不用采

double g_mStarRiseTime;//星升起时间
double g_mStarTransitTime;//星中天时间
double g_mStarSetTime;//星下落时间



//系统参数变量
double  g_telra,g_teldec;//望远镜所指向的赤经和赤纬
double g_mRaTrackSpeed;//望远镜赤经的跟踪速度（	恒星速，太阳速，月亮速，自定义，单位角秒)


double  g_mPoleAxisEW,g_mPoleAxisNS	 ;//望远镜的东西和南北倾斜,东和北为正，西和南为负

int g_mObjRa_shi,g_mObjRa_fen;//目标赤经时分秒
float g_mObjRa_miao;
double g_mObjRa;//目标赤经符点表示时
float g_mObjRa1;//目标赤经符点表示时
float g_mObjRa2;//目标赤经符点表示时

int g_mObjHourA_shi,g_mObjHourA_fen;//目标时角时分秒
float g_mObjHourA_miao;
double g_mObjHourA;//目标时角符点表示时
float g_mObjHourA1;//目标时角符点表示时


int g_mObjDec_du,g_mObjDec_fen;//目标赤纬度分秒
float g_mObjDec_miao;
int g_mObjDec_du1,g_mObjDec_fen1;//目标赤纬度分秒
float g_mObjDec_miao1
;
double g_mObjDec;//目标赤纬符点表示度
float g_mObjDec1;//目标赤纬符点表示度
float g_mObjDec2;//目标赤纬符点表示度

int g_mObjAzi_du,g_mObjAzi_fen;//目标方位度分秒
float g_mObjAzi_miao;
double g_mObjAzi ;	//目标方位符点表示度

double g_mTbjRa;//望远镜赤经符点表示时

int g_gObjDec_sign,g_gObjDec_sign1,g_mObjAlt_du,g_mObjAlt_fen;//目标高度正负\度\分\秒
float g_mObjAlt_miao;
double g_mObjAlt ; 	//目标高度符点表示度

double g_mTbjDec;//望远镜赤纬符点表示度


int g_mTelRa_shi,g_mTelRa_fen;//望远镜赤经时分秒
float g_mTelRa_miao;
double g_mTelRa	,g_mTelRaUtr1;

int g_mTelDec_du,g_mTelDec_fen;//望远镜赤纬度分秒
float g_mTelDec_miao;
double g_mTelDec;
double g_mTelDecUtr1;

int g_mTelAzi_du,g_mTelAzi_fen;//望远镜方位度分秒
float g_mTelAzi_miao;
double g_mTelAziUtr1;//望远镜方位置度;
double g_mTelAzi;//望远镜方位置度;
double g_mTelAzi0;//望远镜方位置度; 
double g_mTelAzi1;//望远镜方位置度; 
double g_mTelAzi2;//望远镜方位置度; 

int g_mTelAlt_du,g_mTelAlt_fen;//望远镜高度度分秒
float g_mTelAlt_miao;
double  g_mTelAltUtr1;//望远镜高度置度;
double  g_mTelAlt;//望远镜高度置度;
double  g_mTelAlt0;//望远镜高度置度;
double  g_mTelAlt1;//望远镜高度置度;
double  g_mTelAlt2;//望远镜高度置度;

int g_mSitLon_du,g_mSitLon_fen;//观测地经度度分秒
float g_mSitLon_miao;
double g_mSitLon;
float g_mSitLontemp;

int g_mSitLon_WE;//东西京，正东经，负西经
int g_mSitLat_du,g_mSitLat_fen;//观测地纬度度度分秒
float g_mSitLat_miao;
int g_mSitLat_SN;//南北半球，正北半球，负南半球
double g_mSitLat;
float g_mSitLattemp;

int g_mTimeZone;//时区,正为东时区，负为西时区
int g_mTimeZonetemp;

//uint32 g_mSitAlt;//海拔
//int    g_mhumidity;//湿度
//int    g_mtemperature;//温度
//uint16  g_mairpressure;//气压

uint32 g_mDate_year;//观测年
uint8  g_mDate_month,g_mDate_day;//观测日期
uint8 g_mTime_hour,g_mTime_minute,g_mTime_second;//观测时间
uint16 g_mTime_wMilliseconds;

//double g_mtime0,g_mtim1;
double g_sildtime0,g_sildtime1;	//地方恒星时

uint8 g_mdatetime;//日期设置还是时间设置，0日期设置，1时间设置


uint8 g_mSkyLand;//观测目标是天空还是陆地，0天空，1陆地
uint8 g_mAzEq;//望远镜是地平式还是赤道式，0地平式，1赤道式

uint8 g_mGps;//是否连接GPS，0没连接，1连接
uint8 g_mTrackSpeed;//跟踪速度0恒星速，1太阳速，2月亮速，3自定义


uint8 g_mHandSpeed;//手动速度档,0,1,2,3,4,5,6,7,8,9
uint8 g_mHandSpeed1;//手动速度档,0,1,2,3,4,5,6,7,8,9
int g_mHandSpeedAzi; //给望远镜调节时的手动方位速度
int	g_mHandSpeedAlt;  //给望远镜调节时的手动高度速度

uint8 g_mTelStatus;//望远镜运行状态，0停止，1指向，2跟踪,3移动状态,100为零位置状态
uint8 g_mTelStatusSet; //望远镜暂停状态操作指示
uint8 g_mOperateStatus;//望远镜操作状态，1指向，2跟踪,3目标在地坪线想,4暂停，5取消操作

bool g_mGotoHandMove;//望远镜在跟踪时，是否要手动,true跟踪时有手动，false跟踪时没有手动
bool g_mGotoHandMoveOK;//望远镜是否可以手动了，望远镜要到定位误差小到一定时才能手动调节


float g_mRaAziGearError;//望远镜赤经或方位一次回差 ？角秒
float g_mRaAziGearErrorTotal;//远镜赤经或方位总次数回差 ？角秒
float g_mRaAziGearEvenError;//望远镜赤经或方位平均回差	？角秒
float g_mRaAziGearErrorNum;//望远镜赤经或方位平均回差测量次数 

float g_mDecAltGearError;//望远镜赤纬或方位一次回差 ？角秒
float g_mDecAltGearErrorTotal;//远镜赤纬或方位总次数回差 ？角秒
float g_mDecAltGearEvenError;//望远镜赤纬或方位平均回差	？角秒
float g_mDecAltGearErrorNum;//望远镜赤纬或方位平均回差测量次数 


int g_mGearErrorAlign;//望远镜是否正在执行轴的回差校准,1正在执行,0没有

uint8 g_mNowBestObjectNum;//当前最佳目标计数器
uint8 g_mSunSysObjectNum;//太阳系目标计数器
uint16 g_mPopularNameObjectNum;//著名恒星，33校准星
uint16 g_mMsrObjectNum;//Messier星表目标计数器
uint16 g_mNgcObjectNum;//NGC星表目标计数器
uint16 g_mIcObjectNum;//IC星表目标计数器
uint16 g_mSh2ObjectNum;//Sh2星表目标计数器
uint16 g_mBrightObjectNum;//Caldwell星表目标计数器
uint32 g_mSaoObjectNum;//SAO星表目标计数器

uint32 g_mInputStarNum;//在星表输入查找状态下，输入的查找数


uint16 g_mHershelObjectNum;//Hershel星表目标计数器

uint8   g_mCon88ObjectNum;//88星座计数器
uint16	g_mCon88StarObjectNum;//88星座里星的计数器
  
uint8   g_mFamousStarObjectNum;//恒星查找方式计数，0学名，1SAO编号,2HR编号
uint16  g_mFixedStarObjectNum;//恒星星表目标计数器

uint16	g_mDoubleStarObjectNum;//双星星表目标计数器
uint16	g_mVariableStarObjectNum;//变星星表目标计数器


uint16 g_mFindObjectAcc;//查找星表的速度档1,10,100,1000,10000;

uint8 g_mMySiteOperator;//自定义地点操作模式，0选择，1增加，2 修改，3删除

uint8 g_mBackLashAxis;//回差样正轴，0方位，1高度，2赤经，3赤纬

uint8 g_mCountry; //国家代号
uint8 g_mCity;	//城市代号

 //望远镜周期误差度
float  g_mTelPosA, g_mTelPosAEr,g_mTelPosE,g_mTelPosEEr;
uint16  g_mTelPosAENum,g_mTelPosAENumMax;
uint8 g_mTelAZErrorWtiteflag;//是否开始新误差记录标志
bool g_mTelPec;//是否打开周期性误差校正记录，true,打开，false不打开

bool g_mAutoBackMainShow;//过一定时间没操作，自动回主待机界面

bool g_mGotoPause; //望远镜暂停标志

int  g_mAutoBackMainShownum	;//多秒可以自动回主等机界面变量

float g_mCurrentTelAzi,	g_mCurrentTelAlt;  //当前望远镜位置
float g_mCurrentObjRa,	g_mCurrentObjDec;  //当前目标位置


uint8 g_mRecentTargetNum;//最近有几颗观测目标，最大8颗
uint8 g_mTargetType;//目标类型，0错误类型，1太阳系天体，2星座，3著名恒星，4messier,5NGC,6IC,7sh2,8bright,9sao,10userstar,11specify,12 Landmark
uint32 g_mTargetnum;//目标编号


uint8 g_RecentNum;
uint8 g_RecentType[8];
uint32 g_Targetnum[8];
uint8 g_rdata[528];
uint8 g_mTempstrnum;


uint8 g_mSysInitGuide;//是否打开初始化向导，0不打开，1打开

//自定义数据结构
//系统时间数据结构
/*typedef structure {	;
    uint32 wYear;//年
    uint8 wMonth;//月
    uint8 wDay;//日
    uint8 wHour;//时
    uint8 wMinute;//分
    uint8 wSecond;//秒
    uint32 wMilliseconds;//毫秒
} Time;
*/
//***********************************************************************
//***********************************************************************
//系统函数实现

//系统参数初始化
void InitSysPara();

//获取系统时间
void GetSysTime();

//获取俗名星表天体
void GetPopularNameObject(uint16 num,float *fra,float *fdec )	;
//获取M星表天体
void GetMObject(uint16  num,float *fra,float *fdec )	;
//获NGCIC星表天体
void GetNgcIcObject(uint16 num,float *fra,float *fdec )	;
//获取UGC星表天体
void GetUgcObject(uint16 num,float *fra,float *fdec )	;
//获取MCG星表天体
void GetMcgObject(uint16 num,float *fra,float *fdec )	;
//获取Caldwell星表天体
void GetCaldwellObject(	uint16 num,float *fra,float *fdec )	;
//获取Abell星表天体
void GetAbellObject(uint16 num,float *fra,float *fdec )	;
//获取Hershel星表天体
void GetHershelObject(uint16 num,float *fra,float *fdec )	;


//获取88星座星表天体
void GetConstellationObject(uint8 num,uint8 EName[],float *fra,float *fdec )	;
//获取恒星星表天体
void GetFixedStarObject(uint8 num1,uint16 num2,float *fra,float *fdec )	;
//获取双星星表天体
void GetDoubleStarObject(uint16 num,float *fra,float *fdec )	;
//获取变星星表天体
void GetVariableStarObject(uint16 num,float *fra,float *fdec )	;

//城市查找
 void FFindCity(uint8 mcountry,uint8 mcity );
  //望远镜型杳寻
void FFindTelType(uint16 mteltype) ;

