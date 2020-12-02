//////////////////////////////////
//ASCOM.c
//////////////////////////////////
//ASCOM望远镜接口
//编程：和寿圣
//邮箱：graycode@qq.com
//电话：13388884440
//日期：2013年4月2日
///////////////////////////////////////////////////////////////////
//使用说明：在main.c中直接调用如下
//*****************************************************************
///////////////////////////////////////////////////////////////////
//与PC机SkyMap的通信处理函数
//调用之前请注释掉main.c文件中“uint8 g_mSendToSkymap;//控制向SKYMAP发送望远镜位置的时间”一行
//请修改ASCOM.c的如下函数：
//如需要由skymap设置日期、时间和地理位置，修改SkyMapFlag等于6、7处相应功能函数
//如果skymap断开时需要停止跟踪等，请在SkyMapFlag等于2处添加相应功能函数
//skymap发送的是utc时间，如需要需要根据地理位置和utc时间转换为本地时间
//请修改同步代码部分内容

//Skymap();

///////////////////////////////////////////////////////////////////
//*****************************************************************
//extern int m_GuiderRa;	  //1为西，-1为东，0为不导（停止），赤经光电导行信号
//extern int m_GuiderDec; //1为南，-1为北，0为不导（停止） ，赤纬光电导行信号
//extern int m_GuiderSpeed;//导星速度档位 (1,2,3,4,5,...)当，目前只用1档，1倍恒星速

float CurrentRa,CurrentDec,SkymapRa,SkymapDec,SkymapLon,SkymapLat,SkymapTZ;//skymap发送过来的数据

//int AGuiderRa,AGuiderDec; //1为西，-1为东，0为不导（停止），赤经光电导行信号 //1为南，-1为北，0为不导（停止） ，赤纬光电导行信号
//int AGuiderRa1,AGuiderDec1; 
//uint32 m_GuideDuration;//

uint32 SkymapYear;
uint8 SkymapMonth,SkymapDay,SkymapHour,SkymapMin,SkymapSec;

uint8 SkymapFlag;//skymap命令状态标志
uint8 g_mSendToSkymap;//控制向SKYMAP发送望远镜位置的时间

uint8 ASCOM()
{
	if(rcv_neworder0==1)//查询中断
	{
		SkymapFlag=rcv_databuf0[0];
		switch(SkymapFlag)	
		{
			case 0x23: //goto
			case 0x24: //sync				
				//获取RA
				uf4.dat[0]=rcv_databuf0[1];
				uf4.dat[1]=rcv_databuf0[2];
				uf4.dat[2]=rcv_databuf0[3];
				uf4.dat[3]=rcv_databuf0[4];
				SkymapRa=uf4.f32;	
				//获取Dec
				uf4.dat[0]=rcv_databuf0[5];
				uf4.dat[1]=rcv_databuf0[6];
				uf4.dat[2]=rcv_databuf0[7];
				uf4.dat[3]=rcv_databuf0[8];
				SkymapDec=uf4.f32;
				break;
			case 0x25://location
				//获取地理经度
				uf4.dat[0]=rcv_databuf0[1];
				uf4.dat[1]=rcv_databuf0[2];
				uf4.dat[2]=rcv_databuf0[3];
				uf4.dat[3]=rcv_databuf0[4];
				SkymapLon=uf4.f32;
				//获取地理纬度	
				uf4.dat[0]=rcv_databuf0[5];
				uf4.dat[1]=rcv_databuf0[6];
				uf4.dat[2]=rcv_databuf0[7];
				uf4.dat[3]=rcv_databuf0[8];
				SkymapLat=uf4.f32;
				break;
			case 0x26: //datetime
				//获取日期
				SkymapYear =(uint32)(rcv_databuf0[1]*100+rcv_databuf0[2]);
				SkymapMonth=rcv_databuf0[3];
				SkymapDay=rcv_databuf0[4];
				//获取时间
				SkymapHour=rcv_databuf0[5];
				SkymapMin=rcv_databuf0[6];
				SkymapSec=rcv_databuf0[7];
				//获取时区
				SkymapTZ=(float)rcv_databuf0[8]-12;
				break;
			default :
				break;
		}
		//复位终端参数
		rcv_neworder0=0;
	}
	return SkymapFlag;
}
//////////////////////////////
//skymap命令处理函数
//////////////////////////////

void Skymap()
{
	//联合体		
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

	//获取skymap命令状态
	SkymapFlag=ASCOM();
	
	switch(SkymapFlag)
	{
		case 0x21://connect
			if(g_mTelescopeConType==1) //赤道式
	    		SendBuf[4]=0x50; //	 返回赤道式标记"P"--0x50
			else if(g_mTelescopeConType==2)	//地平式
	    		SendBuf[4]=0x41; // 返回地平式标记"A"--0x41
			UART0_SentByteArray(SendBuf,13);
			SkymapFlag=0x00;
			break;
		case 0x22://disconnect
			//添加断开连接代码，如停止跟踪等
			SkymapFlag=0x00;
			break;
		case 0x23://goto
			FPointNewStar(SkymapRa,SkymapDec);	//指向skymap目标 	   	
			dg_mSkyMapAzi=0;  //SKYMAP方位同步量 
			dg_mSkyMapAlt=0;  //SKYMAP高度同步量
			SkymapFlag=0x20;
			break;
		case 0x24://sync 
		    dg_mSkyMapAzi=g_mGoto.m_nTAHandMovePos;  //SKYMAP方位同步量
	        dg_mSkyMapAlt=-g_mGoto.m_nTEHandMovePos;  //SKYMAP高度同步量 
			SkymapFlag=0x20;
			break;
		case 0x25://location	 
		     //FStopGoto(); //停止跟踪
			g_mTelStatusSet=1;
			FPauseGoto();
	
			g_mSitLon=SkymapLon; //地理经度
	        g_mSitLat=SkymapLat; //地理纬度
			g_mGoto.m_nLongitude=SkymapLon; //地理经度
			g_mGoto.m_nAtitude=SkymapLat; //地理纬度
	
	       	SkymapFlag=0x00;
			break;
		case 0x26://datetime
		    //FStopGoto(); //停止跟踪
		    g_mTelStatusSet=1;
			FPauseGoto();
	
			g_mTimeZone=SkymapTZ; //时区
			g_mGoto.m_nTimeZone=SkymapTZ;//时区
	
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

		case 0x20: //moving，返回望远镜位置
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
