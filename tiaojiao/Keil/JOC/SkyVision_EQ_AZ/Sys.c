
 //ϵͳ������ʼ��������ʵ��
#include "Sys.h"

//ϵͳ������ʼ��
void InitSysPara()
{
	g_mSysInitGuide=1;//�Ƿ�򿪳�ʼ���򵼣�0���򿪣�1��
	

	g_mhelpshow=0;//��ʾ״̬��0�˵���1����
	g_mKeyBeepOpen=0;//������������0,�أ�1������F+0����


    g_bkeyoperator=false;


//	g_mhumidity=82;//ʪ��
//	g_mtemperature=25;//�¶�
//	g_mairpressure=682;//��ѹ


	g_mDaylight=false;//�Ƿ��������ʱ,true���ã�false���ò�


	g_mRaTrackSpeed=0.0;//����
	g_mTrackSpeed=0;//�����ٶ�0�����٣�1̫���٣�2�����٣�3�Զ���

	g_mPoleAxisEW=0.235;
	g_mPoleAxisNS=0.326;//��Զ���Ķ������ϱ���б,���ͱ�Ϊ����������Ϊ��,��λΪ��


    g_telra=0;//��Զ����ָ��ĳྭ
    g_teldec=0;//��Զ����ָ��ĳ�γ
	
	g_mObjRa_shi=11;
	g_mObjRa_fen=41;//Ŀ��ྭʱ����
	g_mObjRa_miao=12.6;

	g_gObjDec_sign=1; //Ŀ���γ����
	g_mObjDec_du=55;
	g_mObjDec_fen=11;//Ŀ���γ�ȷ���
	g_mObjDec_miao=1.9;
	
	g_mObjAzi_du=1;
	g_mObjAzi_fen=3;//Ŀ�귽λ�ȷ���
	g_mObjAzi_miao=5.9;


	g_mObjAlt_du=6;
	g_mObjAlt_fen=3;//Ŀ��߶ȶȷ���
	g_mObjAlt_miao=5.8;
	
	g_mTelRa_shi=2;
	g_mTelRa_fen=3;//��Զ���ྭʱ����
	g_mTelRa_miao=2.3;

	g_mTelDec_du=5;
	g_mTelDec_fen=2;//��Զ����γ�ȷ���
	g_mTelDec_miao=5.6;
	
	g_mTelAzi_du=8;
	g_mTelAzi_fen=2;//��Զ����λ�ȷ���
	g_mTelAzi_miao=5.8;
	g_mTelAlt_du=3;
	g_mTelAlt_fen=6;//��Զ���߶ȶȷ���
	g_mTelAlt_miao=2.5;
	
	g_mSitLon_du=12;
	g_mSitLon_fen=7;//�۲�ؾ��ȶȷ���
	g_mSitLon_miao=1.3;
	g_mSitLon_WE=1;//����������������������
	
	g_mSitLat_du=5;
	g_mSitLat_fen=1;//�۲��γ�ȶȶȷ���
	g_mSitLat_miao=8.9;
	g_mSitLat_SN=1;//�ϱ������������򣬸��ϰ���

	g_mTimeZone=8;//ʱ��,��Ϊ��ʱ������Ϊ��ʱ��
	
//	g_mSitAlt=1863;//����
	
	g_mDate_year=2010;
    g_mDate_month=8;
	g_mDate_day=28;//�۲�����
	g_mTime_hour=18;
	g_mTime_minute=18;
	g_mTime_second=18;//�۲�ʱ��



	
	
	g_mSkyLand=0;//�۲�Ŀ������ջ���½�أ�0��գ�1½��
	g_mAzEq=0;//��Զ���ǵ�ƽʽ���ǳ��ʽ��0��ƽʽ��1���ʽ
	
	g_mGps=0;//�Ƿ�����GPS��0û���ӣ�1����
	g_mHandSpeed=5;//�ֶ��ٶȵ�,0,1,2,3,4,5,6,7,8,9
	g_mHandSpeed1=0;
	g_mTelStatus=0;//��Զ������״̬��0ֹͣ��1ָ��2����,3�ƶ�״̬,100Ϊ��λ��״̬
    g_mTelStatusSet=1; //��Զ����ͣ״̬����ָʾ

	g_mGotoHandMove=false;//��Զ���ڸ���ʱ���Ƿ�Ҫ�ֶ�,true����ʱ���ֶ���false����ʱû���ֶ�
	g_mGotoHandMoveOK=false;


	 g_mRaAziGearError=0;//��Զ���ྭ��λһ�λز� ������
     g_mRaAziGearEvenError=23.8;//��Զ���ྭ��λƽ���ز�	������
     g_mRaAziGearErrorNum=0;//��Զ���ྭ��λƽ���ز�������� 
	 g_mRaAziGearErrorTotal=0;//Զ���ྭ��λ�ܴ����ز� ������

	 g_mDecAltGearError=0;//��Զ����γ��λһ�λز� ������
     g_mDecAltGearEvenError=23.8;//��Զ����γ��λƽ���ز�	������
     g_mDecAltGearErrorNum=0;//��Զ����γ��λƽ���ز�������� 
	 g_mDecAltGearErrorTotal=0;//Զ����γ��λ�ܴ����ز� ������

	g_mGearErrorAlign=false;//��Զ���Ƿ�����ִ����Ļز�У׼,true����ִ��,falseû��


	g_mNowBestObjectNum=0;//��ǰ���Ŀ������� 
	g_mSunSysObjectNum=0;//̫��ϵĿ�������
	g_mPopularNameObjectNum=0;//�����Ǳ�Ŀ�������
	g_mMsrObjectNum=0;//M�Ǳ�Ŀ�������
	g_mNgcObjectNum=0;//NGCIC�Ǳ�Ŀ�������
	g_mIcObjectNum=0;//UGC�Ǳ�Ŀ�������
	g_mSh2ObjectNum=0;//MCG�Ǳ�Ŀ�������
	g_mBrightObjectNum=0;//Caldwell�Ǳ�Ŀ�������
	g_mSaoObjectNum=0;//Abell�Ǳ�Ŀ�������
	g_mHershelObjectNum=0;//Hershel�Ǳ�Ŀ�������

	g_mCon88ObjectNum=1;//88����������
	g_mCon88StarObjectNum=0;//88�������ǵļ�����
  
    g_mFamousStarObjectNum=0;//���ǲ��ҷ�ʽ������0ѧ����1SAO���,2HR���
	g_mFixedStarObjectNum=0;//�����Ǳ�Ŀ�������

	g_mDoubleStarObjectNum=0;//˫���Ǳ�Ŀ�������
	g_mVariableStarObjectNum=0;//�����Ǳ�Ŀ�������



	g_mFindObjectAcc=1;//�����Ǳ���ٶȵ�1,2,5,10,20,50,100,200,500,1000;

	g_mCountry=1;
	g_mCity=1;

    g_mGotoPause=false; //��Զ����ͣ��־

    g_mCurrentObjRa=0;
    g_mCurrentObjDec=0;  //��ǰĿ��λ��


	g_mRecentTargetNum=0;//����м��Ź۲�Ŀ�꣬���8��
    g_mTargetType=0;//Ŀ�����ͣ�0�������ͣ�1̫��ϵ���壬2������3�������ǣ�4messier,5NGC,6IC,7sh2,8bright,9sao,10userstar,11specify,12 Landmark
    g_mTargetnum=0;//Ŀ����

	


	}

//��ȡϵͳʱ��
void GetSysTime()
{
    uint32  RTCtime;
	uint32  RTCdate;
	RTCtime = RTCtimeRead; // ��ȡ����ʱ�ӼĴ���
	RTCdate = RTCdateRead;	// ��ȡ�������ڼĴ���
	// ȡ����ֵ
     g_mDate_year = (RTCdate>>16)&0xFFF;     
	// ȡ����ֵ
	g_mDate_month = (RTCdate>>8)&0x0F;       
	// ȡ����ֵ
	g_mDate_day = RTCdate&0x1F;            
	// ��ʾ��ֵ;
	      
	// ȡ��ʱ��ֵ
	g_mTime_hour = (RTCtime>>16)&0x1F;

	// ȡ�÷ֵ�ֵ		
	g_mTime_minute= (RTCtime>>8)&0x3F;	
	// ȡ�����ֵ	
	g_mTime_second = RTCtime&0x3F;

    //ȡ�ú���
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
