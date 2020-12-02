//////////////////////////////////
//其中WriteToRom()和ReadFromRom()两个函数基于张涛的底层函数改编优化所得
//公用联合体
// 修改记录  2008-11-17  范玉峰  手柄硬件更新1.04版	 星表芯片(AT45DB161的片选信号改为P1.24，以前0.91版硬件是P0.3)
//           2008-02-04  和寿圣  下载星表串口设置波特率为115200,串口通信协议双向都采用“55AA01”协议，原来向PC机发送信息为裸格式
//			 2008-02-05  和寿圣  添加最近观测目标操作相关函数，调试成功
//#define MXY 0
//#define NGC 1
//#define IC  2
#include <stdio.h>

union
{
	uint16 u16;
	uint8 dat[2];
}u2;
union
{
	uint32 u32;
	float f32;
	uint8 dat[4];
}uf4;
union
{
	double d64;
	uint8 dat[8];
}d8;

//读ROM
void ReadFromRom(uint16 page,uint16 st_add,uint16 num,uint8 data[])
{
	uint16 i=0;
	IO1CLR = XB_CS;
	MSPI_SendData(0XE8);
	MSPI_SendData((unsigned char)(page >> 6));
    MSPI_SendData((unsigned char)(page << 2));
	while(i<st_add+5+num)
	{
		if(i<st_add+5)
			MSPI_SendData(0x00);
		else
			data[i-(st_add+5)] = MSPI_SendData(0x00);
		i++;
	}
	IO1SET = XB_CS;
}

//写ROM
void WriteToRom(uint16 page,uint16 st_add,uint16 num,uint8 data[])
{
	uint16 i;
 	IO1CLR = XB_CS; //片选星表库
//SPI传输命令即地址设定
	MSPI_SendData(0x84);
	MSPI_SendData(0x00);
	MSPI_SendData((unsigned char)(st_add>> 8));   
	MSPI_SendData((unsigned char)st_add);
	for (i=0;i<num;i++)
 	{
 		MSPI_SendData(data[i]);
 	}
	IO1SET = XB_CS;
//buffer到ROM
	IO1CLR = XB_CS; //片选星表库
	if (page<4096)
	{
		MSPI_SendData(0x83);
		MSPI_SendData((unsigned char)(page>>6));
		MSPI_SendData((unsigned char)(page<<2));
		MSPI_SendData(0x00);
	}
	IO1SET = XB_CS;
	delay(5);//soso
}


//写自定义星表
void WriteCustomStar(uint8 num,char *stardata)	 
{
     uint8 data[528];
	 uint8 i;
	 i=0;
	 stardata[0]=1;
	 ReadFromRom(3525,0,528,data);
	 for(i=0;i<24;i++)
	 {
	    data[(num-1)*24+i]=stardata[i]; 
	 }
	 WriteToRom(3525,0,528,data);

     //stardata[0]=111;
	 //WriteToRom(3525,(num-1)*24,24,stardata);

}

//写自定义陆地目标
void WriteCustomLandTarget(uint8 num,char  *targetdata)	 
{
     uint8 data[528];
	 uint8 i;
	 i=0;
	 targetdata[0]=1;
	 ReadFromRom(3526,0,528,data);
	 for(i=0;i<25;i++)
	 {
	    data[(num-1)*25+i]=targetdata[i]; 
	 }
	 WriteToRom(3526,0,528,data);

	
	 //targetdata[0]=111;
	 //WriteToRom(3526,(num-1)*25,25,targetdata);

}


//写最近观测的星
void WriteRecentTarget(uint8 startype,uint32 starnum)	 
{
    uint8 data[57];
	uint8 temp1;
	uint32 temp2;
	ReadFromRom(3527,0,57,data);
	temp1=data[1];//-48;
	temp2=(data[2]-48)*100000+(data[3]-48)*10000+(data[4]-48)*1000+(data[5]-48)*100+(data[6]-48)*10+(data[7]-48);   

    if((startype==temp1)&&(temp2==starnum))
	{
	  temp1=0;
	 }
	else
	{
		data[0]++;
		if(data[0]>8)
		{ 
		  data[0]=8;
		}
		WriteToRom(3527,0,1,data);
		WriteToRom(3527,8,56,&data[1]);
		data[1]=startype;
		WriteToRom(3527,1,1,&data[1]);
		sprintf(data,"%06d",starnum);
		WriteToRom(3527,2,6,data);

	}
}


//功能：获取望远镜的零点
void GetTelZero(float *telazi,float *telalt)
{	
     uint8 data[5];
	 ReadFromRom(3529,0,5,data);
	 *telazi=(data[0]-48)*100.0+(data[1]-48)*10.0+data[2]-48.0;
	 *telalt=(data[3]-48)*10.0+data[4]-48.0;
	
}

//功能：设置望远镜零点
void SetTelZero(uint16 telazi,uint16 telalt)
{
     uint8 data[5];
	 sprintf(data,"%03d%02d",telazi,telalt);
	 WriteToRom(3529,0,5,data); 

}



//功能：添加一条自定义地点信息记录
void SetSite(char site[8],uint8 lon[6],uint8 lat[5],uint8 zone[3])
{
	 WriteToRom(3530,10,8,site);
	 WriteToRom(3530,18,6,lon);
	 WriteToRom(3530,24,5,lat);
	 WriteToRom(3530,29,3,zone);
}


  //查找自定义地点信息  	     
void GetSite(char site[8],float *lon,float *lat,int *zone) 
{
	uint8 data[22];//每条记录有18个字节
	uint8 i=0;
	ReadFromRom(3530,10,22,data);
    
   for(i=0;i<8;i++)
   {
      site[i]=data[i];
   }


   *lon=(data[9]-48)*100.0+(data[10]-48)*10.0+data[11]-48+((data[12]-48)*10.0+data[13]-48)/60.0;
   if(data[8]=='W')
   {  
      *lon=-1.0*(*lon);
   }
   

   *lat=(data[15]-48)*10.0+data[16]-48+((data[17]-48)*10.0+data[18]-48)/60.0;

    if(data[14]=='S')
   {  
      *lat=-1.0*(*lat);
   }

	*zone=(data[20]-48)*10.0+data[21]-48;
	 if(data[19]=='W')
   {  
      *zone=-1.0*(*zone);
   }


}

 ////////////////////////////////////////////////////////////////////////////
 ///////////////////////////////////////////////////////////////
 //////////////////////////////////////////////////////////////////////
 /////////////////////////////////////////////////////////////////////////
 //跟踪误差操作函数
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
 //功能：修改记录
void Edit(uint16 num,uint16 page,uint16 st_add,uint16 datalength,uint8 data[])
{
	uint8 i=0;
	uint8 tmp[528];
	ReadFromRom(page,0,528,tmp);//取出来先保存到tmp
	for(i=0;i<datalength;i++)
		tmp[st_add+datalength*(num%(528/datalength))+i]=data[i];
	WriteToRom(page,0, 528,tmp);  
}

//功能：设置跟踪误差记录个数
//参数：记录个数（0-500）
//用法：
void SetTrackingErrorInfoNum(uint16 num)	
{
	uint8 tmp[528];
	if(num>500)
		return;
	u2.u16=num;
	ReadFromRom(4095,0,528,tmp);//取出来先保存
	tmp[4]=u2.dat[0];
	tmp[5]=u2.dat[1];
	WriteToRom(4095,0, 528,tmp);  
}
//功能：获取跟踪误差记录个数
//用法
uint16 GetTrackingErrorInfoNum()
{
	ReadFromRom(4095,4,2,u2.dat);
	if(u2.u16>500)
	{
		SetTrackingErrorInfoNum(0);
		return 0;
	}
	return u2.u16;
}
//功能：修改跟踪误差记录
//说明：该函数为内部函数，不是提供给用户使用的
void EditTrackingErrorInfo(uint16 num,uint8 data[])
{
	Edit(num,4062,0,16,data);
}

//功能：获取跟踪误差记录，
//参数：第几条记录（0-499）
//用法：
//uint16 num;
//float Az,Az_Error,Alt,Alt_Error;
//uint8 ret=GetTrackingErrorInfo(num,&Az,&Az_Error,&Alt,&Alt_Error);
//if(ret==0)//Get error
//{}
//else
//{}
uint8 GetTrackingErrorInfo(uint16 num,float *Az,float *Az_Error,float *Alt,float *Alt_Error)
{
	uint8 data[16];
	uint8 i;
	uint16 totalnum=GetTrackingErrorInfoNum();
	if((totalnum==0)||(num>totalnum-1)) //记录数为0或num大于记录数
	{
		return 0;
	}
	else
	{
		ReadFromRom(4062+num/33,16*(num%33),16,data);
		//Get(num,4062,0,16,data);
		for(i=0;i<4;i++)
			uf4.dat[i]=data[i];	
		*Az=uf4.f32;
		for(i=0;i<4;i++)
			uf4.dat[i]=data[i+4];
		*Az_Error=uf4.f32;
		for(i=0;i<4;i++)
			uf4.dat[i]=data[i+8];
		*Alt=uf4.f32;
		for(i=0;i<4;i++)
			uf4.dat[i]=data[i+12];
		*Alt_Error=uf4.f32;
		return 1;
	}
}

uint8 AddTrackingErrorInfo(uint8 *flag,float Az,float Az_Error,float Alt,float Alt_Error)
{
	uint8 data[16];
	uint8 i;
	uint16 totalnum=GetTrackingErrorInfoNum();
	if(*flag==0)
	{
		if(totalnum!=0)
		{
			SetTrackingErrorInfoNum(0);
			totalnum=0;
		}
		*flag=1;
	}	
	if(totalnum>=500)
		return 0; 
	uf4.f32=Az;
	for(i=0;i<4;i++)
		data[i]=uf4.dat[i];	
	uf4.f32=Az_Error;
	for(i=0;i<4;i++)
		data[i+4]=uf4.dat[i];
	uf4.f32=Alt;
	for(i=0;i<4;i++)
		data[i+8]=uf4.dat[i];
	uf4.f32=Alt_Error;
	for(i=0;i<4;i++)
		data[i+12]=uf4.dat[i];
	EditTrackingErrorInfo(totalnum,data);
	SetTrackingErrorInfoNum(totalnum+1);
	return 1;
}




//功能：添加一条自定义陆地目标信息记录
//void AddCustomerCityInfo(uint8 data[])
uint8 AddCustomerLandMarkInfo(uint8 name[],float *Az,float *Alt)
{
//	uint8 i=0;
//	uint8 data[16];
//	uint8 totalnum=GetCustomerLandMarkInfoNum();
//	if(totalnum>=10)
//		return 0;  
//	for(i=0;i<7;i++)
//		data[i]=name[i];
//	data[7]=0;
//	uf4.f32=*Az;
//	for(i=0;i<4;i++)
//		data[i+8]=uf4.dat[i];
//	uf4.f32=*Alt;
//	for(i=0;i<4;i++)
//		data[i+12]=uf4.dat[i];
//	EditCustomerLandMarkInfo(totalnum,data);
//	SetCustomerLandMarkInfoNum(totalnum+1);
//	return 1;
}




////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
//最近观测目标操作函数
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////

//功能：设置最近观测目标记录个数，4095页存储城市记录和自定义星表记录个数等信息
//参数：
//用法：
void SetRecentStarInfoNum(uint16 num)	
{
	uint8 tmp[528];
	if(num>66)
		return;
	u2.u16=num;
	ReadFromRom(4095,0,528,tmp);//取出来先保存
	tmp[8]=u2.dat[0];
	tmp[9]=u2.dat[1];
	WriteToRom(4095,0, 528,tmp);  
}

//功能：获取最近观测目标记录个数
//用法
uint16 GetRecentStarInfoNum()
{
	ReadFromRom(4095,8,2,u2.dat);
	if(u2.u16>66)
	{
		SetRecentStarInfoNum(0);
		return 0;
	}
	else
		return u2.u16;
}
//功能：设置最近观测目标最新的一条记录位置
void SetLatestRecentStarInfoNum(uint16 num)	
{
	uint8 tmp[528];
	if(num>65)
		return;
	u2.u16=num;
	ReadFromRom(4095,0,528,tmp);//取出来先保存
	tmp[10]=u2.dat[0];
	tmp[11]=u2.dat[1];
	WriteToRom(4095,0, 528,tmp);  
}

//功能：获取最近观测目标最新的一条记录位置
//用法
uint16 GetLatestRecentStarInfoNum()
{
	ReadFromRom(4095,10,2,u2.dat);
	if(u2.u16>65)
	{
		SetLatestRecentStarInfoNum(0);
		return 0;
	}
	else
		return u2.u16;
}
//功能：修改自定义星表记录
void EditRecentStarInfo(uint16 num,uint8 data[])
{						   
	Edit(num,0,0,8,data);
}
//功能：获取一条最近观测目标记录，成功返回1，否则返回0
uint8 GetRecentStarInfo(uint16 num,float *RA,float *DEC)
{
	uint8 i;
	uint8 data[8];
	uint16 totalnum=GetRecentStarInfoNum();
	uint16 LatestNum=GetLatestRecentStarInfoNum();
	if((totalnum==0)||(num>totalnum-1)) //记录数为0或num大于记录数
		return 0;	
	else
	{
		if(LatestNum<num)
			//LatestNum=66+LatestNum-num;
			num=66+LatestNum-num;
		else
			//LatestNum-=num;
			num=LatestNum-num;
		ReadFromRom(0+num/66,8*(num%66),8,data);
		//Get(num,0,0,8,data);
		for(i=0;i<4;i++)
			uf4.dat[i]=data[i];
		*RA=uf4.f32;
		for(i=0;i<4;i++)
			uf4.dat[i]=data[i+4];
		*DEC=uf4.f32;
		return 1;
	}	 	
}

 
