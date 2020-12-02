//////////////////////////////////
//ASCOM.c
//////////////////////////////////
//ASCOM��Զ���ӿ�
//��̣�����ʥ
//���䣺graycode@qq.com
//�绰��13388884440
//���ڣ�2013��4��2��
///////////////////////////////////////////////////////////////////
//ʹ��˵������main.c��ֱ�ӵ�������
//*****************************************************************
///////////////////////////////////////////////////////////////////
//��PC��SkyMap��ͨ�Ŵ�����
//����֮ǰ��ע�͵�main.c�ļ��С�uint8 g_mSendToSkymap;//������SKYMAP������Զ��λ�õ�ʱ�䡱һ��
//���޸�ASCOM.c�����º�����
//����Ҫ��skymap�������ڡ�ʱ��͵���λ�ã��޸�SkyMapFlag����6��7����Ӧ���ܺ���
//���skymap�Ͽ�ʱ��Ҫֹͣ���ٵȣ�����SkyMapFlag����2�������Ӧ���ܺ���
//skymap���͵���utcʱ�䣬����Ҫ��Ҫ���ݵ���λ�ú�utcʱ��ת��Ϊ����ʱ��
//���޸�ͬ�����벿������

//Skymap();

///////////////////////////////////////////////////////////////////
//*****************************************************************
//extern int m_GuiderRa;	  //1Ϊ����-1Ϊ����0Ϊ������ֹͣ�����ྭ��絼���ź�
//extern int m_GuiderDec; //1Ϊ�ϣ�-1Ϊ����0Ϊ������ֹͣ�� ����γ��絼���ź�
//extern int m_GuiderSpeed;//�����ٶȵ�λ (1,2,3,4,5,...)����Ŀǰֻ��1����1��������

float CurrentRa,CurrentDec,SkymapRa,SkymapDec,SkymapLon,SkymapLat,SkymapTZ;//skymap���͹���������

//int AGuiderRa,AGuiderDec; //1Ϊ����-1Ϊ����0Ϊ������ֹͣ�����ྭ��絼���ź� //1Ϊ�ϣ�-1Ϊ����0Ϊ������ֹͣ�� ����γ��絼���ź�
//int AGuiderRa1,AGuiderDec1; 
//uint32 m_GuideDuration;//

uint32 SkymapYear;
uint8 SkymapMonth,SkymapDay,SkymapHour,SkymapMin,SkymapSec;

uint8 SkymapFlag;//skymap����״̬��־
uint8 g_mSendToSkymap;//������SKYMAP������Զ��λ�õ�ʱ��

uint8 ASCOM()
{
	if(rcv_neworder0==1)//��ѯ�ж�
	{
		SkymapFlag=rcv_databuf0[0];
		switch(SkymapFlag)	
		{
			case 0x23: //goto
			case 0x24: //sync				
				//��ȡRA
				uf4.dat[0]=rcv_databuf0[1];
				uf4.dat[1]=rcv_databuf0[2];
				uf4.dat[2]=rcv_databuf0[3];
				uf4.dat[3]=rcv_databuf0[4];
				SkymapRa=uf4.f32;	
				//��ȡDec
				uf4.dat[0]=rcv_databuf0[5];
				uf4.dat[1]=rcv_databuf0[6];
				uf4.dat[2]=rcv_databuf0[7];
				uf4.dat[3]=rcv_databuf0[8];
				SkymapDec=uf4.f32;
				break;
			case 0x25://location
				//��ȡ������
				uf4.dat[0]=rcv_databuf0[1];
				uf4.dat[1]=rcv_databuf0[2];
				uf4.dat[2]=rcv_databuf0[3];
				uf4.dat[3]=rcv_databuf0[4];
				SkymapLon=uf4.f32;
				//��ȡ����γ��	
				uf4.dat[0]=rcv_databuf0[5];
				uf4.dat[1]=rcv_databuf0[6];
				uf4.dat[2]=rcv_databuf0[7];
				uf4.dat[3]=rcv_databuf0[8];
				SkymapLat=uf4.f32;
				break;
			case 0x26: //datetime
				//��ȡ����
				SkymapYear =(uint32)(rcv_databuf0[1]*100+rcv_databuf0[2]);
				SkymapMonth=rcv_databuf0[3];
				SkymapDay=rcv_databuf0[4];
				//��ȡʱ��
				SkymapHour=rcv_databuf0[5];
				SkymapMin=rcv_databuf0[6];
				SkymapSec=rcv_databuf0[7];
				//��ȡʱ��
				SkymapTZ=(float)rcv_databuf0[8]-12;
				break;
			default :
				break;
		}
		//��λ�ն˲���
		rcv_neworder0=0;
	}
	return SkymapFlag;
}
//////////////////////////////
//skymap�������
//////////////////////////////

void Skymap()
{
	//������		
	union
	{
		float f32;
		uint8 dat[4];
	}SendRa;
	union
	{
		float f32;
		uint8 dat[4];
	}SendDec;

	uint8 SendBuf[13];
	SendBuf[0]=0x55;SendBuf[1]=0xAA; SendBuf[2]=0x01; SendBuf[3]=0x09;	

	//��ȡskymap����״̬
	SkymapFlag=ASCOM();
	
	switch(SkymapFlag)
	{
		case 0x21://connect
			if(g_mTelescopeConType==1) //���ʽ
	    		SendBuf[4]=0x50; //	 ���س��ʽ���"P"--0x50
			else if(g_mTelescopeConType==2)	//��ƽʽ
	    		SendBuf[4]=0x41; // ���ص�ƽʽ���"A"--0x41
			UART0_SentByteArray(SendBuf,13);
			SkymapFlag=0x00;
			break;
		case 0x22://disconnect
			//��ӶϿ����Ӵ��룬��ֹͣ���ٵ�
			SkymapFlag=0x00;
			break;
		case 0x23://goto
			FPointNewStar(SkymapRa,SkymapDec);	//ָ��skymapĿ�� 	   	
			dg_mSkyMapAzi=0;  //SKYMAP��λͬ���� 
			dg_mSkyMapAlt=0;  //SKYMAP�߶�ͬ����
			SkymapFlag=0x20;
			break;
		case 0x24://sync 
		    dg_mSkyMapAzi=g_mGoto.m_nTAHandMovePos;  //SKYMAP��λͬ����
	        dg_mSkyMapAlt=-g_mGoto.m_nTEHandMovePos;  //SKYMAP�߶�ͬ���� 
			SkymapFlag=0x20;
			break;
		case 0x25://location	 
		     //FStopGoto(); //ֹͣ����
			g_mTelStatusSet=1;
			FPauseGoto();
	
			g_mSitLon=SkymapLon; //������
	        g_mSitLat=SkymapLat; //����γ��
			g_mGoto.m_nLongitude=SkymapLon; //������
			g_mGoto.m_nAtitude=SkymapLat; //����γ��
	
	       	SkymapFlag=0x00;
			break;
		case 0x26://datetime
		    //FStopGoto(); //ֹͣ����
		    g_mTelStatusSet=1;
			FPauseGoto();
	
			g_mTimeZone=SkymapTZ; //ʱ��
			g_mGoto.m_nTimeZone=SkymapTZ;//ʱ��
	
			CCR = 0x10;				    
	
		  	YEAR =SkymapYear;	
			MONTH =SkymapMonth;    
			DOM = SkymapDay;    
	
			HOUR =SkymapHour; 
			MIN = SkymapMin;	
			SEC = SkymapSec;
	
			CCR = 0x11;	
		   
		    SkymapFlag=0x00;
			break;

		case 0x20: //moving��������Զ��λ��
			if(g_mSendToSkymap>2) 
			{
				SendRa.f32=CurrentRa;
				SendDec.f32=CurrentDec;
	
				SendBuf[4]=0xFF;
				SendBuf[5]=SendRa.dat[0];
				SendBuf[6]=SendRa.dat[1];	
				SendBuf[7]=SendRa.dat[2];
				SendBuf[8]=SendRa.dat[3];	
				
				SendBuf[9]=SendDec.dat[0];
				SendBuf[10]=SendDec.dat[1];
				SendBuf[11]=SendDec.dat[2];
				SendBuf[12]=SendDec.dat[3];	
	
				UART0_SentByteArray(SendBuf,13);
	
		   		g_mSendToSkymap=0;
			}
			else
			{
		  		 g_mSendToSkymap++;
			}
			break;	
		default :
			break;	
	}
}
