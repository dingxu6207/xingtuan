#include "stdbool.h"

#include <rtl.h>
#include <signal.h>
#include <stdio.h>

//ϵͳ����������������
//*************************************************
//*************************************************	
//�˵����ó�������
//������Ӧֵ����
//	�¼���
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



//�ϼ���
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
//#define  KEY_TORCH    100  //�ϼ���û�������ֻλ�����ɴ�
//
//#define  KEY_LEFTDOWN	 21					     
//#define  KEY_LEFTUP	     22
//#define  KEY_RIGHTDOWN	 23
//#define  KEY_RIGHTUP	 24

//*******************************************************
//*******************************************************
//********************
//ϵͳ״̬����
#define SYS_MAINSHOW  0	//ϵͳ����״̬Ϊ��Ҫ�Ĵ�������ʾ״̬
#define SYS_MENUSHOW  1 //�չ۲���ǵ���ʾ
#define SYS_NOTELSCOPE  2 //û����Զ��״̬
#define SYS_RESET 100//ϵͳ����״̬


#define SYS_F_SELFNUM  101  //����F½��Ŀ������Ŀ��GOTO����
#define SYS_F_SELFNUM_SEL 102 

//#define SYS_MENU_LANDSKY_OBJECT 200//����½��Ŀ�������Զ��幦�� 
#define SYS_MENU_SKY_OBJECT 201
#define SYS_MENU_LAND_OBJECT 202

#define SYS_MENU_SKY_NAME 203
#define SYS_MENU_SKY_RA 204
#define SYS_MENU_SKY_DEC 205


#define SYS_MENU_LAND_NAME 206
#define SYS_MENU_LAND_AZI 207
#define SYS_MENU_LAND_ALT 208





 
//********************
//�˵�״̬һ���˵������˵���
#define SYS_MAINMENU1  1000	//ϵͳ���˵���һ��ֵ
#define SYS_MAINMENU2  2000	//ϵͳ���˵��ڶ���ֵ
#define SYS_MAINMENU3  3000 //ϵͳ���˵�������ֵ
#define SYS_MAINMENU4  4000	//ϵͳ���˵�������ֵ
//�Ӳ˵��������˵���
//��Զ��У���Ӳ˵�
#define SYS_SUB1MENU1  1100	//ϵͳ�Ӳ˵�1��һ��ֵ
#define SYS_SUB1MENU2  1200	//ϵͳ�Ӳ˵�1�ڶ���ֵ
#define SYS_SUB1MENU3  1300	//ϵͳ�Ӳ˵�1������ֵ
#define SYS_SUB1MENU4  1400	//ϵͳ�Ӳ˵�1������ֵ
#define SYS_SUB1MENU5  1500	//ϵͳ�Ӳ˵�1������ֵ
#define SYS_SUB1MENU6  1600	//ϵͳ�Ӳ˵�1������ֵ
#define SYS_SUB1MENU7  1700	//ϵͳ�Ӳ˵�1������ֵ
//Ŀ�굼���Ӳ˵�
#define SYS_SUB2MENU1  2100	//ϵͳ�Ӳ˵�2��һ��ֵ
#define SYS_SUB2MENU2  2200	//ϵͳ�Ӳ˵�2�ڶ���ֵ
#define SYS_SUB2MENU3  2300	//ϵͳ�Ӳ˵�2������ֵ
#define SYS_SUB2MENU4  2400	//ϵͳ�Ӳ˵�2������ֵ
#define SYS_SUB2MENU5  2500	//ϵͳ�Ӳ˵�2������ֵ
#define SYS_SUB2MENU6  2600	//ϵͳ�Ӳ˵�2������ֵ
#define SYS_SUB2MENU7  2700	//ϵͳ�Ӳ˵�2������ֵ
#define SYS_SUB2MENU8  2800	//ϵͳ�Ӳ˵�2�ڰ���ֵ
#define SYS_SUB2MENU9  2900	//ϵͳ�Ӳ˵�2�ھ���ֵ
#define SYS_SUB2MENU11 2110	//ϵͳ�Ӳ˵�2��ʮ��ֵ
#define SYS_SUB2MENU12 2120	//ϵͳ�Ӳ˵�2��ʮһ��ֵ
#define SYS_SUB2MENU13 2130	//ϵͳ�Ӳ˵�2��ʮ����ֵ
//���������Ӳ˵�
#define SYS_SUB3MENU1  3100	//ϵͳ�Ӳ˵�3��һ��ֵ
#define SYS_SUB3MENU2  3200	//ϵͳ�Ӳ˵�3�ڶ���ֵ
#define SYS_SUB3MENU3  3300	//ϵͳ�Ӳ˵�3������ֵ
#define SYS_SUB3MENU4  3400	//ϵͳ�Ӳ˵�3������ֵ
#define SYS_SUB3MENU5  3500	//ϵͳ�Ӳ˵�3������ֵ
#define SYS_SUB3MENU6  3600	//ϵͳ�Ӳ˵�3������ֵ
#define SYS_SUB3MENU7  3700	//ϵͳ�Ӳ˵�3������ֵ
#define SYS_SUB3MENU8  3800	//ϵͳ�Ӳ˵�3�ڰ���ֵ
#define SYS_SUB3MENU9  3900	//ϵͳ�Ӳ˵�3�ھ���ֵ
//���������Ӳ˵�
#define SYS_SUB4MENU1  4100	//ϵͳ�Ӳ˵�4��һ��ֵ
#define SYS_SUB4MENU2  4200	//ϵͳ�Ӳ˵�4�ڶ���ֵ
#define SYS_SUB4MENU3  4300	//ϵͳ�Ӳ˵�4������ֵ
#define SYS_SUB4MENU4  4400	//ϵͳ�Ӳ˵�4������ֵ
#define SYS_SUB4MENU5  4500	//ϵͳ�Ӳ˵�4������ֵ
#define SYS_SUB4MENU6  4600	//ϵͳ�Ӳ˵�4������ֵ
#define SYS_SUB4MENU7  4700	//ϵͳ�Ӳ˵�4������ֵ
#define SYS_SUB4MENU8  4800	//ϵͳ�Ӳ˵�4�ڰ���ֵ
#define SYS_SUB4MENU9  4900	//ϵͳ�Ӳ˵�4�ھ���ֵ
//���Ӳ˵��������˵���
//��Զ��ͬ��
#define SYS_SUB1SUB4MENU1  1401	//����ͬ��
#define SYS_SUB1SUB4MENU2  1402	//ȷ��ͬ��
#define SYS_SUB1SUB4MENU3  1403 //ȡ��ͬ��
//̫��ϵ�Ӳ˵�
#define SYS_SUB2SUB2MENU1  2201	//ϵͳ���Ӳ˵�1��һ��ֵ
#define SYS_SUB2SUB2MENU2  2202	//ϵͳ���Ӳ˵�1�ڶ���ֵ
#define SYS_SUB2SUB2MENU3  2203	//ϵͳ���Ӳ˵�1������ֵ
#define SYS_SUB2SUB2MENU4  2204	//ϵͳ���Ӳ˵�1������ֵ
#define SYS_SUB2SUB2MENU5  2205	//ϵͳ���Ӳ˵�1������ֵ
#define SYS_SUB2SUB2MENU6  2206	//ϵͳ���Ӳ˵�1������ֵ
#define SYS_SUB2SUB2MENU7  2207	//ϵͳ���Ӳ˵�1������ֵ
#define SYS_SUB2SUB2MENU8  2208	//ϵͳ���Ӳ˵�1�ڰ���ֵ
#define SYS_SUB2SUB2MENU9  2209	//ϵͳ���Ӳ˵�1�ھ���ֵ
#define SYS_SUB2SUB2MENU11 22011//ϵͳ���Ӳ˵�1��ʮ��ֵ
#define SYS_SUB2SUB2MENU12 22012//ϵͳ���Ӳ˵�1��ʮһ��ֵ
//��������Ӳ˵�
#define SYS_SUB2SUB3MENU1  2301	//ϵͳ���Ӳ˵�2��һ��ֵ
#define SYS_SUB2SUB3MENU2  2302	//ϵͳ���Ӳ˵�2�ڶ���ֵ
#define SYS_SUB2SUB3MENU3  2303	//ϵͳ���Ӳ˵�2������ֵ
#define SYS_SUB2SUB3MENU4  2304	//ϵͳ���Ӳ˵�2������ֵ
#define SYS_SUB2SUB3MENU5  2305	//ϵͳ���Ӳ˵�2������ֵ
#define SYS_SUB2SUB3MENU6  2306	//ϵͳ���Ӳ˵�2������ֵ
#define SYS_SUB2SUB3MENU7  2307	//ϵͳ���Ӳ˵�2������ֵ
#define SYS_SUB2SUB3MENU8  2308	//ϵͳ���Ӳ˵�2�ڰ���ֵ
//�����Ӳ˵�
#define SYS_SUB2SUB5MENU1  2501	//ϵͳ���Ӳ˵�3��һ��ֵ
#define SYS_SUB2SUB5MENU2  2502	//ϵͳ���Ӳ˵�3�ڶ���ֵ
#define SYS_SUB2SUB5MENU3  2503	//ϵͳ���Ӳ˵�3������ֵ

//�Զ����Ǳ��Ӳ˵�
#define SYS_SUB2SUB8MENU1  2801	//ϵͳ���Ӳ˵�4��һ��ֵ
#define SYS_SUB2SUB8MENU2  2802	//ϵͳ���Ӳ˵�4�ڶ���ֵ
#define SYS_SUB2SUB8MENU3  2803	//ϵͳ���Ӳ˵�4������ֵ
#define SYS_SUB2SUB8MENU4  2804	//ϵͳ���Ӳ˵�4������ֵ
#define SYS_SUB2SUB8_SET   28001
//½��Ŀ���Ӳ˵�
#define SYS_SUB2SUB11MENU1  21101	//ϵͳ���Ӳ˵�5��һ��ֵ
#define SYS_SUB2SUB11MENU2  21102	//ϵͳ���Ӳ˵�5�ڶ���ֵ
#define SYS_SUB2SUB11MENU3  21103	//ϵͳ���Ӳ˵�5������ֵ
#define SYS_SUB2SUB11_SET   211001	
//Ŀ�������Ӳ˵�
#define SYS_SUB3SUB6MENU1  3601	//ϵͳ���Ӳ˵�8��һ��ֵ
#define SYS_SUB3SUB6MENU2  3602	//ϵͳ���Ӳ˵�8�ڶ���ֵ


//����Ұ�����Ӳ˵�
#define SYS_SUB3SUB8MENU1  3801	//ϵͳ���Ӳ˵�9��һ��ֵ
#define SYS_SUB3SUB8MENU2  3802	//ϵͳ���Ӳ˵�9�ڶ���ֵ
//�ص������Ӳ˵�
#define SYS_SUB4SUB3MENU1  4301	//ϵͳ���Ӳ˵�10��һ��ֵ
#define SYS_SUB4SUB3MENU2  4302	//ϵͳ���Ӳ˵�10�ڶ���ֵ
//��Զ���ͺ��Ӳ˵�
//#define SYS_SUB4SUB7MENU1  4701	//ϵͳ���Ӳ˵�12��һ��ֵ
//#define SYS_SUB4SUB7MENU2  4702	//ϵͳ���Ӳ˵�12�ڶ���ֵ
//#define SYS_SUB4SUB7MENU3  4703	//ϵͳ���Ӳ˵�12������ֵ
//#define SYS_SUB4SUB7MENU4  4704	//ϵͳ���Ӳ˵�12������ֵ

//�����ٶ��Ӳ˵�
#define SYS_SUB4SUB8MENU1  4801	//ϵͳ���Ӳ˵�13��һ��ֵ
#define SYS_SUB4SUB8MENU2  4802	//ϵͳ���Ӳ˵�13�ڶ���ֵ
#define SYS_SUB4SUB8MENU3  4803	//ϵͳ���Ӳ˵�13������ֵ
#define SYS_SUB4SUB8MENU4  4804	//ϵͳ���Ӳ˵�13������ֵ
//*******************************************
//*******************************************



//�˵���ײ�ʵ��
//��һ���Ӳ˵���һ��:��Զ��У��
//#define SYS_SUB1SUB1AUTOSTAR_ALIGN  11001 //�Զ�˫��У׼

#define SYS_SUB1SUB2STAR_ALIGN  12001 //һ��У׼	 ����У׼ ����У׼ ��ʾ״̬




#define SYS_SUB1SUB8POLE_AXIS_ERROR  18001 //��Զ������ƫ����ʾ



#define SYS_SUB1SUB11RA_GEAR_ERROR 11101 //�ྭ�ز�У��
#define SYS_SUB1SUB11RA_GEAR_ERROR_BEGIN 11102//�ྭ�ز�У����ʼ
#define SYS_SUB1SUB11RA_GEAR_ERROR_ALIGN 11103 //�ྭ�ز�����У��
#define SYS_SUB1SUB11RA_GEAR_ERROR_ALIGN_OK  11104//���һ�λز�ྭ�ز�У��
#define SYS_SUB1SUB11RA_GEAR_ERROR_ALIGN_END  11105//��ɶ�γྭ�ز�У��

#define SYS_SUB1SUB12DEC_GEAR_ERROR 11201 //��γ�ز�У��
#define SYS_SUB1SUB12DEC_GEAR_ERROR_BEGIN 11202//��γ�ز�У����ʼ
#define SYS_SUB1SUB12DEC_GEAR_ERROR_ALIGN 11203 //��γ�ز�����У��
#define SYS_SUB1SUB12DEC_GEAR_ERROR_ALIGN_OK  11204//���һ�λز��γ�ز�У��
#define SYS_SUB1SUB12DEC_GEAR_ERROR_ALIGN_END  11205//��ɶ�γ�γ�ز�У��

//��һ���Ӳ˵��ڶ��Ŀ�굼��
#define SYS_SUB2SUB1NOW_OBJECT   21001   //��ǰ���Ŀ��
#define SYS_SUB2SUN_PLANET   22001	//̫��ϵͳĿ��
#define SYS_SUB2SUN_PLANET1   22111	//̫��ϵͳĿ��
#define SYS_SUB2SUN_SUNWARN	  22112	//ָ��̫������

#define SYS_SUB2SUB3PN_OBJECT   23001   //�����Ǳ�Ŀ��

#define SYS_SUB2MSR_OBJECT   23002   //M�Ǳ�Ŀ��
#define SYS_SUB2MSR_OBJECT0   23012   //M�Ǳ�Ŀ��
#define SYS_SUB2MSR_OBJECT1   23022   //M�Ǳ�Ŀ��

#define SYS_SUB2NGC_OBJECT   23003   //NGCIC�Ǳ�Ŀ��
#define SYS_SUB2NGC_OBJECT1   23013   //NGCIC�Ǳ�Ŀ��   

#define SYS_SUB2IC_OBJECT   23004   //UGC�Ǳ�Ŀ��
#define SYS_SUB2IC_OBJECT1   23014   //UGC�Ǳ�Ŀ��

#define SYS_SUB2SH2_OBJECT   23005   //MCG�Ǳ�Ŀ��
#define SYS_SUB2SH2_OBJECT1   23015   //MCG�Ǳ�Ŀ��

#define SYS_SUB2BRT_OBJECT   23006   //Caldwell�Ǳ�Ŀ��
#define SYS_SUB2BRT_OBJECT1   23016   //Caldwell�Ǳ�Ŀ��

#define SYS_SUB2SAO_OBJECT   23007   //Abell�Ǳ�Ŀ��
#define SYS_SUB2SAO_OBJECT1   23017   //Abell�Ǳ�Ŀ��

#define SYS_SUB2SUB3HER_OBJECT   23008   //Hershel�Ǳ�Ŀ��

#define SYS_SUB2CON_OBJECT   24001   //88�����Ǳ�Ŀ��
#define SYS_SUB2CON_OBJECT1   24002   //88�����Ǳ�Ŀ��

#define SYS_SUB2FS_OBJECT   25001   //�����Ǳ�Ŀ��
#define SYS_SUB2FS_OBJECT1   25002   //�����Ǳ�Ŀ��

#define SYS_SUB2SUB6DS_OBJECT   26001   //˫���Ǳ�Ŀ��
#define SYS_SUB2SUB7VS_OBJECT   27001   //�����Ǳ�Ŀ��


#define SYS_SUB2SUB9RA   29001   //��Զ���ྭ��γ����
#define SYS_SUB2SUB9DEC  29002   //��Զ���ྭ��γ����
//��һ���Ӳ˵��������������
#define SYS_SUB3SUB1NOW_APH   31001   //��������
 #define SYS_SUB3SUB2_STARRISESET  32001 //��������
#define SYS_SUB3SUB3_MOONPHASE 33001	//�����Ѱ״̬
//����ʱ�Ӳ˵�
#define SYS_SUB3SUB4TIMER_INPUT 34001	//��ʱ����
#define SYS_SUB3SUB4TIMER_ONOFF 34002	//��ʱ��/ֹͣ
//��ʱ�����Ӳ˵�
#define SYS_SUB3SUB5ALARM_INPUT  35001	//��������
#define SYS_SUB3SUB5ALARM_ONOFF  35002	//���ӿ���/�ر�
//***************************************************************************************
//Ŀ������.��Ұ
#define SYS_SUB3SUB6SUB1LOV_TELTYPE1 360011 //��Զ���ͺ�ѡ��
#define SYS_SUB3SUB6SUB1LOV_TELTYPE2 360012 //��Զ���ͺ�ѡ��
#define SYS_SUB3SUB6SUB1LOV_TELTYPE3 360013 //��Զ���ͺ�ѡ��

#define SYS_SUB3SUB6SUB1MENU1       360111
#define SYS_SUB3SUB6SUB1MENU2       360112
#define SYS_SUB3SUB6SUB1MENU3       360113

//Ŀ������.����
#define SYS_SUB3SUB6SUB2M_MF 360021       //������������״̬
#define SYS_SUB3SUB6SUB2M_SF 360022     //������������״̬	  
#define SYS_SUB3SUB6SUB2M_Multi 360023 //�Ŵ�����ʾ״̬

#define SYS_SUB3SUB6SUB2M_MF1 370021       //������������״̬
#define SYS_SUB3SUB6SUB2M_SF1 370022     //������������״̬	  
#define SYS_SUB3SUB6SUB2M_MFOV 370023 //�Ŵ�����ʾ״̬

//����Ұ����
#define SYS_SUB3SUB8MENU1Screen 380011

//����ʱ��
#define SYS_SUB4SUB2MENU1 42001
#define SYS_SUB4SUB2MENU2 42002
//***************************************************************************************
#define SYS_MAINSHOWHELP    500	//ϵͳ����״̬Ϊ��Ҫ�Ĵ�������ʾ״̬
//********************
//�˵�״̬һ���˵������˵���
#define SYS_MAINMENU1HELP  501	//ϵͳ���˵���һ��ֵ
#define SYS_MAINMENU2HELP  502	//ϵͳ���˵��ڶ���ֵ
#define SYS_MAINMENU3HELP  503 //ϵͳ���˵�������ֵ
#define SYS_MAINMENU4HELP  504	//ϵͳ���˵�������ֵ
//�Ӳ˵��������˵���
//��Զ��У���Ӳ˵�
#define SYS_SUB1MENU1HELP  505	//ϵͳ�Ӳ˵�1��һ��ֵ
#define SYS_SUB1MENU2HELP  506	//ϵͳ�Ӳ˵�1�ڶ���ֵ
#define SYS_SUB1MENU3HELP  507	//ϵͳ�Ӳ˵�1������ֵ
#define SYS_SUB1MENU4HELP  508	//ϵͳ�Ӳ˵�1������ֵ
#define SYS_SUB1MENU5HELP  509	//ϵͳ�Ӳ˵�1������ֵ
#define SYS_SUB1MENU6HELP  510	//ϵͳ�Ӳ˵�1������ֵ
#define SYS_SUB1MENU7HELP  511	//ϵͳ�Ӳ˵�1������ֵ
//Ŀ�굼���Ӳ˵�
#define SYS_SUB2MENU1HELP  516	//ϵͳ�Ӳ˵�2��һ��ֵ
#define SYS_SUB2MENU2HELP  517	//ϵͳ�Ӳ˵�2�ڶ���ֵ
#define SYS_SUB2MENU3HELP  518	//ϵͳ�Ӳ˵�2������ֵ
#define SYS_SUB2MENU4HELP  519	//ϵͳ�Ӳ˵�2������ֵ
#define SYS_SUB2MENU5HELP  520	//ϵͳ�Ӳ˵�2������ֵ
#define SYS_SUB2MENU6HELP  521	//ϵͳ�Ӳ˵�2������ֵ
#define SYS_SUB2MENU7HELP  522	//ϵͳ�Ӳ˵�2������ֵ
#define SYS_SUB2MENU8HELP  523	//ϵͳ�Ӳ˵�2�ڰ���ֵ
#define SYS_SUB2MENU9HELP  524	//ϵͳ�Ӳ˵�2�ھ���ֵ
#define SYS_SUB2MENU11HELP 525	//ϵͳ�Ӳ˵�2��ʮ��ֵ
#define SYS_SUB2MENU12HELP 526	//ϵͳ�Ӳ˵�2��ʮһ��ֵ
#define SYS_SUB2MENU13HELP 527	//ϵͳ�Ӳ˵�2��ʮ����ֵ
//���������Ӳ˵�
#define SYS_SUB3MENU1HELP  528	//ϵͳ�Ӳ˵�3��һ��ֵ
#define SYS_SUB3MENU2HELP  529	//ϵͳ�Ӳ˵�3�ڶ���ֵ
#define SYS_SUB3MENU3HELP  530	//ϵͳ�Ӳ˵�3������ֵ
#define SYS_SUB3MENU4HELP  531	//ϵͳ�Ӳ˵�3������ֵ
#define SYS_SUB3MENU5HELP  532	//ϵͳ�Ӳ˵�3������ֵ
#define SYS_SUB3MENU6HELP  533	//ϵͳ�Ӳ˵�3������ֵ
#define SYS_SUB3MENU7HELP  534	//ϵͳ�Ӳ˵�3������ֵ
#define SYS_SUB3MENU8HELP  535	//ϵͳ�Ӳ˵�3�ڰ���ֵ
#define SYS_SUB3MENU9HELP 537	//ϵͳ�Ӳ˵�3��ʮ��ֵ
//���������Ӳ˵�
#define SYS_SUB4MENU1HELP  538	//ϵͳ�Ӳ˵�4��һ��ֵ
#define SYS_SUB4MENU2HELP  539	//ϵͳ�Ӳ˵�4�ڶ���ֵ
#define SYS_SUB4MENU3HELP  540	//ϵͳ�Ӳ˵�4������ֵ
#define SYS_SUB4MENU4HELP  541	//ϵͳ�Ӳ˵�4������ֵ
#define SYS_SUB4MENU5HELP  542	//ϵͳ�Ӳ˵�4������ֵ
#define SYS_SUB4MENU6HELP  543	//ϵͳ�Ӳ˵�4������ֵ
#define SYS_SUB4MENU7HELP  544	//ϵͳ�Ӳ˵�4������ֵ
#define SYS_SUB4MENU8HELP  545	//ϵͳ�Ӳ˵�4�ڰ���ֵ
#define SYS_SUB4MENU9HELP  546	//ϵͳ�Ӳ˵�4�ھ���ֵ

//*******************************************************************************


//��һ���Ӳ˵��������������

#define SYS_SUB4SUB1_SETTIME 41001  //ϵͳʱ������

#define SYS_SUB4SUB3SUN1_CITYSEL  43011	//����ѡ��

#define SYS_SUB4SUB3_SETSITE 43002  //�Զ���ص� 

#define SYS_SUB4SUB3SUB2_SELECT  43021	//�Զ���ص�ѡ��
#define SYS_SUB4SUB3SUB2_ADD  43022	//�Զ���ص�����
#define SYS_SUB4SUB3SUB2_DELETE  43023	//�Զ���ص�ɾ��
#define SYS_SUB4SUB3SUB2_MODIFY  43024	//�Զ���ص��޸�

//#define SYS_SUB4SUB4WEATHER  44001  //�����Ӳ˵�

#define SYS_SUB4SUB5SKY   45001   //�۲�Ŀ�����ģʽѡ��
#define SYS_SUB4SUB5LAND   45002   //�۲�Ŀ��½��ģʽѡ��

#define SYS_SUB4SUB6AZ   46001   //��Զ��װ�õ�ƽʽѡ��
#define SYS_SUB4SUB6EQ   46002   //��Զ��װ�ó��ʽѡ��

//��Զ���ͺ��Ӳ˵�
//#define SYS_SUB4SUB7SUB1_TELSEL   47011	 //ϵͳ���Ӳ˵�12��һ��ֵ
//#define SYS_SUB4SUB7SUB2_TELADD   47021	//ϵͳ���Ӳ˵�12�ڶ���ֵ
//#define SYS_SUB4SUB7SUB3_TELDEL   47031	//ϵͳ���Ӳ˵�12������ֵ
//#define SYS_SUB4SUB7SUB4_TELMOD   47041	//ϵͳ���Ӳ˵�12������ֵ

//��Զ������Ӳ˵�
#define SYS_SUB4SUB7_TELAZIALT_ZERO   47011	 //���÷�λ���
//#define SYS_SUB4SUB7_TELALT_ZERO   47021	//���ø߶����
//#define SYS_SUB4SUB7_TELZERO_ERROR   47031	//������ô���
#define SYS_SUB4SUB7_TELZERO_OK   47041	//���������ȷ



#define SYS_SUB4SUB8MENU4_RASPEED  48001	//��Զ���ྭ�����ٶ�


#define SYS_SUB4SUB9EN   49001   //�˵�����ѡ��
#define SYS_SUB4SUB9GER   49002   //�˵�����ѡ��
#define SYS_SUB4SUB9FRE   49003   //�˵�����ѡ��
#define SYS_SUB4SUB9ITA   49004   //�˵�����ѡ��
#define SYS_SUB4SUB9SPA   49005   //�˵�����ѡ��

//*******************************************
//*******************************************
//����״̬
#define SYS_MAINHELP  5000//ϵͳ����״̬��������״̬)

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


//��������	
//ϵͳ״̬
uint8 g_mhelpshow;//��ʾ״̬��0�˵���1����
uint8 g_mmainhelpshow;//���˵���ʾ״̬

uint8 g_mKeyBeepOpen;//������������0,�أ�1������F+0����


int g_nAlignStar;//�Զ���У׼����Ŀ���Ϊ3
uint8 g_nSelAlignStarNum;//��ѡ�����Զ���У׼���ǵڼ���
uint8 g_nSeledAlignStarNum;//ѡ���˼�����
bool g_nAlignPoint;//��Զ����һ����������У��ʱ�ǵ���ȷ�ϻ���ѡ��falseѡ���ǣ�trueУ������ȷ��

uint32 g_nsysstatus;  //ϵͳ״̬
bool g_bkeyoperator;//��Զ�����µļ��Ƿ�õ���Ӧ
uint8  m_nkeyvalue;//����ֵ����

bool g_mDaylight;//�Ƿ��������ʱ,true���ã�false���ò�

double g_mStarRiseTime;//������ʱ��
double g_mStarTransitTime;//������ʱ��
double g_mStarSetTime;//������ʱ��



//ϵͳ��������
double  g_telra,g_teldec;//��Զ����ָ��ĳྭ�ͳ�γ
double g_mRaTrackSpeed;//��Զ���ྭ�ĸ����ٶȣ�	�����٣�̫���٣������٣��Զ��壬��λ����)


double  g_mPoleAxisEW,g_mPoleAxisNS	 ;//��Զ���Ķ������ϱ���б,���ͱ�Ϊ����������Ϊ��

int g_mObjRa_shi,g_mObjRa_fen;//Ŀ��ྭʱ����
float g_mObjRa_miao;
double g_mObjRa;//Ŀ��ྭ�����ʾʱ
float g_mObjRa1;//Ŀ��ྭ�����ʾʱ
float g_mObjRa2;//Ŀ��ྭ�����ʾʱ

int g_mObjHourA_shi,g_mObjHourA_fen;//Ŀ��ʱ��ʱ����
float g_mObjHourA_miao;
double g_mObjHourA;//Ŀ��ʱ�Ƿ����ʾʱ
float g_mObjHourA1;//Ŀ��ʱ�Ƿ����ʾʱ


int g_mObjDec_du,g_mObjDec_fen;//Ŀ���γ�ȷ���
float g_mObjDec_miao;
int g_mObjDec_du1,g_mObjDec_fen1;//Ŀ���γ�ȷ���
float g_mObjDec_miao1
;
double g_mObjDec;//Ŀ���γ�����ʾ��
float g_mObjDec1;//Ŀ���γ�����ʾ��
float g_mObjDec2;//Ŀ���γ�����ʾ��

int g_mObjAzi_du,g_mObjAzi_fen;//Ŀ�귽λ�ȷ���
float g_mObjAzi_miao;
double g_mObjAzi ;	//Ŀ�귽λ�����ʾ��

double g_mTbjRa;//��Զ���ྭ�����ʾʱ

int g_gObjDec_sign,g_gObjDec_sign1,g_mObjAlt_du,g_mObjAlt_fen;//Ŀ��߶�����\��\��\��
float g_mObjAlt_miao;
double g_mObjAlt ; 	//Ŀ��߶ȷ����ʾ��

double g_mTbjDec;//��Զ����γ�����ʾ��


int g_mTelRa_shi,g_mTelRa_fen;//��Զ���ྭʱ����
float g_mTelRa_miao;
double g_mTelRa	,g_mTelRaUtr1;

int g_mTelDec_du,g_mTelDec_fen;//��Զ����γ�ȷ���
float g_mTelDec_miao;
double g_mTelDec;
double g_mTelDecUtr1;

int g_mTelAzi_du,g_mTelAzi_fen;//��Զ����λ�ȷ���
float g_mTelAzi_miao;
double g_mTelAziUtr1;//��Զ����λ�ö�;
double g_mTelAzi;//��Զ����λ�ö�;
double g_mTelAzi0;//��Զ����λ�ö�; 
double g_mTelAzi1;//��Զ����λ�ö�; 
double g_mTelAzi2;//��Զ����λ�ö�; 

int g_mTelAlt_du,g_mTelAlt_fen;//��Զ���߶ȶȷ���
float g_mTelAlt_miao;
double  g_mTelAltUtr1;//��Զ���߶��ö�;
double  g_mTelAlt;//��Զ���߶��ö�;
double  g_mTelAlt0;//��Զ���߶��ö�;
double  g_mTelAlt1;//��Զ���߶��ö�;
double  g_mTelAlt2;//��Զ���߶��ö�;

int g_mSitLon_du,g_mSitLon_fen;//�۲�ؾ��ȶȷ���
float g_mSitLon_miao;
double g_mSitLon;
float g_mSitLontemp;

int g_mSitLon_WE;//����������������������
int g_mSitLat_du,g_mSitLat_fen;//�۲��γ�ȶȶȷ���
float g_mSitLat_miao;
int g_mSitLat_SN;//�ϱ������������򣬸��ϰ���
double g_mSitLat;
float g_mSitLattemp;

int g_mTimeZone;//ʱ��,��Ϊ��ʱ������Ϊ��ʱ��
int g_mTimeZonetemp;

//uint32 g_mSitAlt;//����
//int    g_mhumidity;//ʪ��
//int    g_mtemperature;//�¶�
//uint16  g_mairpressure;//��ѹ

uint32 g_mDate_year;//�۲���
uint8  g_mDate_month,g_mDate_day;//�۲�����
uint8 g_mTime_hour,g_mTime_minute,g_mTime_second;//�۲�ʱ��
uint16 g_mTime_wMilliseconds;

//double g_mtime0,g_mtim1;
double g_sildtime0,g_sildtime1;	//�ط�����ʱ

uint8 g_mdatetime;//�������û���ʱ�����ã�0�������ã�1ʱ������


uint8 g_mSkyLand;//�۲�Ŀ������ջ���½�أ�0��գ�1½��
uint8 g_mAzEq;//��Զ���ǵ�ƽʽ���ǳ��ʽ��0��ƽʽ��1���ʽ

uint8 g_mGps;//�Ƿ�����GPS��0û���ӣ�1����
uint8 g_mTrackSpeed;//�����ٶ�0�����٣�1̫���٣�2�����٣�3�Զ���


uint8 g_mHandSpeed;//�ֶ��ٶȵ�,0,1,2,3,4,5,6,7,8,9
uint8 g_mHandSpeed1;//�ֶ��ٶȵ�,0,1,2,3,4,5,6,7,8,9
int g_mHandSpeedAzi; //����Զ������ʱ���ֶ���λ�ٶ�
int	g_mHandSpeedAlt;  //����Զ������ʱ���ֶ��߶��ٶ�

uint8 g_mTelStatus;//��Զ������״̬��0ֹͣ��1ָ��2����,3�ƶ�״̬,100Ϊ��λ��״̬
uint8 g_mTelStatusSet; //��Զ����ͣ״̬����ָʾ
uint8 g_mOperateStatus;//��Զ������״̬��1ָ��2����,3Ŀ���ڵ�ƺ����,4��ͣ��5ȡ������

bool g_mGotoHandMove;//��Զ���ڸ���ʱ���Ƿ�Ҫ�ֶ�,true����ʱ���ֶ���false����ʱû���ֶ�
bool g_mGotoHandMoveOK;//��Զ���Ƿ�����ֶ��ˣ���Զ��Ҫ����λ���С��һ��ʱ�����ֶ�����


float g_mRaAziGearError;//��Զ���ྭ��λһ�λز� ������
float g_mRaAziGearErrorTotal;//Զ���ྭ��λ�ܴ����ز� ������
float g_mRaAziGearEvenError;//��Զ���ྭ��λƽ���ز�	������
float g_mRaAziGearErrorNum;//��Զ���ྭ��λƽ���ز�������� 

float g_mDecAltGearError;//��Զ����γ��λһ�λز� ������
float g_mDecAltGearErrorTotal;//Զ����γ��λ�ܴ����ز� ������
float g_mDecAltGearEvenError;//��Զ����γ��λƽ���ز�	������
float g_mDecAltGearErrorNum;//��Զ����γ��λƽ���ز�������� 


int g_mGearErrorAlign;//��Զ���Ƿ�����ִ����Ļز�У׼,1����ִ��,0û��

uint8 g_mNowBestObjectNum;//��ǰ���Ŀ�������
uint8 g_mSunSysObjectNum;//̫��ϵĿ�������
uint16 g_mPopularNameObjectNum;//�������ǣ�33У׼��
uint16 g_mMsrObjectNum;//Messier�Ǳ�Ŀ�������
uint16 g_mNgcObjectNum;//NGC�Ǳ�Ŀ�������
uint16 g_mIcObjectNum;//IC�Ǳ�Ŀ�������
uint16 g_mSh2ObjectNum;//Sh2�Ǳ�Ŀ�������
uint16 g_mBrightObjectNum;//Caldwell�Ǳ�Ŀ�������
uint32 g_mSaoObjectNum;//SAO�Ǳ�Ŀ�������

uint32 g_mInputStarNum;//���Ǳ��������״̬�£�����Ĳ�����


uint16 g_mHershelObjectNum;//Hershel�Ǳ�Ŀ�������

uint8   g_mCon88ObjectNum;//88����������
uint16	g_mCon88StarObjectNum;//88�������ǵļ�����
  
uint8   g_mFamousStarObjectNum;//���ǲ��ҷ�ʽ������0ѧ����1SAO���,2HR���
uint16  g_mFixedStarObjectNum;//�����Ǳ�Ŀ�������

uint16	g_mDoubleStarObjectNum;//˫���Ǳ�Ŀ�������
uint16	g_mVariableStarObjectNum;//�����Ǳ�Ŀ�������


uint16 g_mFindObjectAcc;//�����Ǳ���ٶȵ�1,10,100,1000,10000;

uint8 g_mMySiteOperator;//�Զ���ص����ģʽ��0ѡ��1���ӣ�2 �޸ģ�3ɾ��

uint8 g_mBackLashAxis;//�ز������ᣬ0��λ��1�߶ȣ�2�ྭ��3��γ

uint8 g_mCountry; //���Ҵ���
uint8 g_mCity;	//���д���

 //��Զ����������
float  g_mTelPosA, g_mTelPosAEr,g_mTelPosE,g_mTelPosEEr;
uint16  g_mTelPosAENum,g_mTelPosAENumMax;
uint8 g_mTelAZErrorWtiteflag;//�Ƿ�ʼ������¼��־
bool g_mTelPec;//�Ƿ�����������У����¼��true,�򿪣�false����

bool g_mAutoBackMainShow;//��һ��ʱ��û�������Զ�������������

bool g_mGotoPause; //��Զ����ͣ��־

int  g_mAutoBackMainShownum	;//��������Զ������Ȼ��������

float g_mCurrentTelAzi,	g_mCurrentTelAlt;  //��ǰ��Զ��λ��
float g_mCurrentObjRa,	g_mCurrentObjDec;  //��ǰĿ��λ��


uint8 g_mRecentTargetNum;//����м��Ź۲�Ŀ�꣬���8��
uint8 g_mTargetType;//Ŀ�����ͣ�0�������ͣ�1̫��ϵ���壬2������3�������ǣ�4messier,5NGC,6IC,7sh2,8bright,9sao,10userstar,11specify,12 Landmark
uint32 g_mTargetnum;//Ŀ����


uint8 g_RecentNum;
uint8 g_RecentType[8];
uint32 g_Targetnum[8];
uint8 g_rdata[528];
uint8 g_mTempstrnum;


uint8 g_mSysInitGuide;//�Ƿ�򿪳�ʼ���򵼣�0���򿪣�1��

//�Զ������ݽṹ
//ϵͳʱ�����ݽṹ
/*typedef structure {	;
    uint32 wYear;//��
    uint8 wMonth;//��
    uint8 wDay;//��
    uint8 wHour;//ʱ
    uint8 wMinute;//��
    uint8 wSecond;//��
    uint32 wMilliseconds;//����
} Time;
*/
//***********************************************************************
//***********************************************************************
//ϵͳ����ʵ��

//ϵͳ������ʼ��
void InitSysPara();

//��ȡϵͳʱ��
void GetSysTime();

//��ȡ�����Ǳ�����
void GetPopularNameObject(uint16 num,float *fra,float *fdec )	;
//��ȡM�Ǳ�����
void GetMObject(uint16  num,float *fra,float *fdec )	;
//��NGCIC�Ǳ�����
void GetNgcIcObject(uint16 num,float *fra,float *fdec )	;
//��ȡUGC�Ǳ�����
void GetUgcObject(uint16 num,float *fra,float *fdec )	;
//��ȡMCG�Ǳ�����
void GetMcgObject(uint16 num,float *fra,float *fdec )	;
//��ȡCaldwell�Ǳ�����
void GetCaldwellObject(	uint16 num,float *fra,float *fdec )	;
//��ȡAbell�Ǳ�����
void GetAbellObject(uint16 num,float *fra,float *fdec )	;
//��ȡHershel�Ǳ�����
void GetHershelObject(uint16 num,float *fra,float *fdec )	;


//��ȡ88�����Ǳ�����
void GetConstellationObject(uint8 num,uint8 EName[],float *fra,float *fdec )	;
//��ȡ�����Ǳ�����
void GetFixedStarObject(uint8 num1,uint16 num2,float *fra,float *fdec )	;
//��ȡ˫���Ǳ�����
void GetDoubleStarObject(uint16 num,float *fra,float *fdec )	;
//��ȡ�����Ǳ�����
void GetVariableStarObject(uint16 num,float *fra,float *fdec )	;

//���в���
 void FFindCity(uint8 mcountry,uint8 mcity );
  //��Զ������Ѱ
void FFindTelType(uint16 mteltype) ;

