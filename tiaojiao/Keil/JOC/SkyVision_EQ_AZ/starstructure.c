//***********************************************************
//***********************************************************
//
//*******************************************
//*******************************************
//*******定义星表里的数据结构及数据读写******
//**********编者：柳光乾           **********
//**********2008年于云南天文台     **********
//**********lgq@ynao.ac.cn         **********
//*******************************************
//*******************************************
//***********************************************************
//33颗校准星
typedef struct  
{
     char ConEn[12]	;  //（星座拉丁名编码）10
     char ConCn[12];  //（星座中文名）10
	 uint32 SaoNo;   // （SAO编码）3
	 char NameEn[14]; //（英文名）12
	 char NameCn[10];  // （中文名)8
	 float Bright;  // （星等）2
	 float Ra ;     // （赤经）3
	 float Dec;     // (赤纬）3
} AlignStar33;
//***********************************************************


uint8 GetAlignStar(uint8 starnum, AlignStar33* star)//从星表获取校准星
 {
     uint16 page;
	 uint16 pageoffset;
	 uint8 data[51]; //51记录长度
     uint8 i;
	 //*****
	 if((starnum==0)&&(starnum>33))	  //33记录总数
	 {
	   return  0;
	 }
	  //*****
	 page=(starnum-1)/10;  //10每页记录数
	 pageoffset=((starnum-1)%10)*51;////10每页记录数，51记录长度
     ReadFromRom(page+0,pageoffset,51,data); //0该类数据的起始页，51每页记录数
	  //*****
	 for(i=0;i<10;i++)
	 {
	    (*star).ConEn[i]=data[i];
	 }
	 (*star).ConEn[10]=0x00;
	 (*star).ConEn[11]=0x00;
	 //*****
	  for(i=10;i<20;i++)
	 {
	    (*star).ConCn[i-10]=data[i];
	 }
	 (*star).ConCn[10]=0x00;
	 (*star).ConCn[11]=0x00;
	  //*****
	
	  (*star).SaoNo=data[20]*10000+data[21]*100+data[22];

	   //*****
	  for(i=23;i<35;i++)
	 {
	    (*star).NameEn[i-22]=data[i];
	 }
	 (*star).NameEn[0]=0x20;
	 (*star).NameEn[13]=0x00;
	   //*****
	  for(i=35;i<43;i++)
	 {
	    (*star).NameCn[i-35]=data[i];
	 }
	  (*star).NameCn[8]=0x00;
	 (*star).NameCn[9]=0x00;
	  //*****
	  if(data[43]>=128)
	  {
	     (*star).Bright=128-data[43]-data[44]/10.0;
	  }
	  else
	  {
	      (*star).Bright=data[43]+data[44]/10.0;
	  }
	  //*****
	  (*star).Ra=data[45]+data[46]/60.0+data[47]/3600.0;
	  //*****
	  if(data[48]>=128)
	  {
	     (*star).Dec=128-data[48]-data[49]/60.0-data[50]/3600.0;
	  }
	  else
	  {
	      (*star).Dec=data[48]+data[49]/60.0+data[50]/3600.0;
	  }
	  //*****


	 return  1;
 }
//***********************************************************


//***********************************************************
//88星座
typedef struct  
{
     char ConEn0[5]	;  //（星座英文名简写）3
	 char ConEn[21]	;  //（星座英文名）19
	 char ConCn[10]	;  //（星座中文名）8
	 float Ra ;     // （赤经）2
	 float Dec;     // 赤纬）2
	 uint16 area;   //面积2
	 uint8  view;   //视角1
	 uint8  starnum; //星体数1
}Con88 ;
//***********************************************************


uint8 GetCon88(uint8 connum, Con88* con)//从星表获取校准星
 {
     uint16 page;
	 uint16 pageoffset;
	 uint8 data[38];
     uint8 i;
	 //*****
	 if((connum==0)&&(connum>33))
	 {
	   return  0;
	 }
	  //*****
	 page=(connum-1)/13;
	 pageoffset=((connum-1)%13)*38;
     ReadFromRom(page+4,pageoffset,38,data);
	  //*****
	 for(i=0;i<3;i++)
	 {
	    (*con).ConEn0[i]=data[i];
	 }
	 (*con).ConEn0[3]=0x20;
	 (*con).ConEn0[4]=0x00;
	 //*****
	  for(i=3;i<22;i++)
	 {
	    (*con).ConEn[i-3]=data[i];
	 }
	 (*con).ConEn[19]=0x20;
	 (*con).ConEn[20]=0x00;
	  //*****
	  for(i=22;i<30;i++)
	 {
	    (*con).ConCn[i-22]=data[i];
	 }
	 (*con).ConCn[8]=0x00;
	 (*con).ConCn[9]=0x00;
	 //**************
	  (*con).Ra=data[30]+data[31]/60.0;
	  //*****
	  if(data[32]>=128)
	  {
	     (*con).Dec=128-data[32]-data[33]/100.0;
	  }
	  else
	  {
	      (*con).Dec=data[32]+data[33]/100.0;
	  }
	  //*****
	   (*con).area=data[34]*100+data[35];
	     //*****
	   (*con).view=data[36];
	     //*****
	   (*con).starnum=data[37];
	  //*****
		

	 return  1;
 }
//***********************************************************

//***********************************************************
//messier110星表
typedef struct  
{
     uint16 NGCNo;     //NGC编号 2
	 float Ra ;     // （赤经）3
	 float Dec;     // 赤纬）3
	 float  view;   //视角2
	 double  dis;   //距离（千光年）4
	 char ConCn[8]	;  //（星座中文名）6
	 char ConEn[16]	;  //（星座英文名）14
	 char TypeCn[12];//中文类型10
	 char TypeEn[26];//英文类型24
	 char NameCn[22];//中文别名24
	 char NameEn[38];//英文别名36

}Messier110 ;
//***********************************************************


uint8 GetMessier110(uint8 starnum, Messier110* star)//从星表获取校准星
 {
     uint16 page;
	 uint16 pageoffset;
	 uint8 data[124];
     uint8 i;
	 //*****
	 if((starnum==0)&&(starnum>110))
	 {
	   return  0;
	 }

	   //*****
	  page=(starnum-1)/4;
	  pageoffset=((starnum-1)%4)*124;
      ReadFromRom(page+11,pageoffset,124,data);
	  //*****
	 (*star).NGCNo=data[0]*100+data[1];
	  //*****
	  (*star).Ra=data[2]+data[3]/60.0+data[4]/3600.0;
	  //*****
	  if(data[5]>=128)
	  {
	     (*star).Dec=128-data[5]-data[6]/60.0-data[7]/3600.0;
	  }
	  else
	  {
	      (*star).Dec=data[5]+data[6]/60.0+data[7]/3600.0;
	  }
	  //*****
	   (*star).view=data[8]+data[9]/10.0;
	  //*****
	  (*star).dis=data[10]*10000.0+data[11]*100.0+data[12]+data[13]/10.0;

	 //*****
	 for(i=14;i<20;i++)
	 {
	    (*star).ConCn[i-14]=data[i];
	 }
	 (*star).ConCn[6]=0x00;
	 (*star).ConCn[7]=0x00;
	  //*****
	  for(i=20;i<34;i++)
	 {
	    (*star).ConEn[i-20]=data[i];
	 }
	 (*star).ConEn[14]=0x20;
	 (*star).ConEn[15]=0x00;
	 //*****


	 for(i=34;i<44;i++)
	 {
	    (*star).TypeCn[i-34]=data[i];
	 }
	 (*star).TypeCn[10]=0x00;
	 (*star).TypeCn[11]=0x00;
	  //*****
	  for(i=44;i<68;i++)
	 {
	    (*star).TypeEn[i-44]=data[i];
	 }
	 (*star).TypeEn[24]=0x20;
	 (*star).TypeEn[25]=0x00;
	 //*****

	 	 //*****
	 for(i=68;i<90;i++)
	 {
	    (*star).NameCn[i-68]=data[i];
	 }
	 (*star).NameCn[22]=0x00;
	 (*star).NameCn[23]=0x00;
	  //*****
	  for(i=90;i<124;i++)
	 {
	    (*star).NameEn[i-90]=data[i];
	 }
	 (*star).NameEn[34]=0x20;
	 (*star).NameEn[35]=0x00;
	 //*****

		
	 return  1;
 }
//***********************************************************




//***********************************************************
//Bright 167星表
typedef struct  
{
     char NameEn[18];//英文别名16
	 float Ra ;     // （赤经）3
	 float Dec;     // 赤纬）3
	 float bright;   //亮度 2	 
}Bright167 ;
//***********************************************************


uint8 GetBright167(uint8 starnum, Bright167* star)//从星表获取校准星
 {
     uint16 page;
	 uint16 pageoffset;
	 uint8 data[24];
     uint8 i;
	 //*****
	 if((starnum==0)&&(starnum>167))
	 {
	   return  0;
	 }

	   //*****
	  page=(starnum-1)/22;
	  pageoffset=((starnum-1)%22)*24;
      ReadFromRom(page+39,pageoffset,24,data);
	  
	  //*****
	  for(i=0;i<16;i++)
	 {
	    (*star).NameEn[i]=data[i];
	 }
	 (*star).NameEn[16]=0x20;
	 (*star).NameEn[17]=0x00;
	 //*****
	  
	  (*star).Ra=data[16]+data[17]/60.0+data[18]/3600.0;
	  //*****
	  if(data[19]>=128)
	  {
	     (*star).Dec=128-data[19]-data[20]/60.0-data[21]/3600.0;
	  }
	  else
	  {
	      (*star).Dec=data[19]+data[20]/60.0+data[21]/3600.0;
	  }
	  //*****
	  if(data[22]>=128)
	  {
	     (*star).bright=128-data[22]-data[23]/100.0;
	  }
	  else
	  {
	       (*star).bright=data[22]+data[23]/100.0;
	  }
	  
	   //*****

		
	 return  1;
 }
//***********************************************************




//***********************************************************
//Sh2 313星表
typedef struct  
{
	 float Ra ;     // （赤经）3
	 float Dec;     // 赤纬）3
	
}Sh2313 ;
//***********************************************************


uint8 GetSh2313(uint16 starnum, Sh2313* star)//从星表获取校准星
 {
     uint16 page;
	 uint16 pageoffset;
	 uint8 data[6];
	 //*****
	 if((starnum==0)&&(starnum>313))
	 {
	   return  0;
	 }

	   //*****
	  page=(starnum-1)/88;
	  pageoffset=((starnum-1)%88)*6;
      ReadFromRom(page+47,pageoffset,6,data);
	  
	  //*****
		  
	  (*star).Ra=data[0]+data[1]/60.0+data[2]/3600.0;
	  //*****
	  if(data[3]>=128)
	  {
	     (*star).Dec=128-data[3]-data[4]/60.0-data[5]/3600.0;
	  }
	  else
	  {
	      (*star).Dec=data[3]+data[4]/60.0+data[5]/3600.0;
	  }
	  //*****


		
	 return  1;
 }
//***********************************************************


//***********************************************************
//IC5386星表
typedef struct  
{
     char ConEn[5];//星座英文名简写3
	 float Ra ;     // （赤经）3
	 float Dec;     // 赤纬）3
	 float Bright;   //亮度2
	 char TypeEn[10];//类型英文名
	
}IC5386 ;
//***********************************************************


uint8 GetIC5386(uint16 starnum, IC5386* star)//从星表获取校准星
 {
     uint16 page;
	 uint16 pageoffset;
	 uint8 data[19];
	 uint8 i;
	 //*****
	 if((starnum==0)&&(starnum>5386))
	 {
	   return  0;
	 }

	   //*****
	  page=(starnum-1)/27;
	  pageoffset=((starnum-1)%27)*19;
      ReadFromRom(page+51,pageoffset,19,data);	  
	  //*****
	  for(i=0;i<3;i++)
	 {
	    (*star).ConEn[i]=data[i];
	 }
	 (*star).ConEn[3]=0x20;
	 (*star).ConEn[4]=0x00;
	 //*****


		  
	  (*star).Ra=data[3]+data[4]/60.0+data[5]/3600.0;
	  //*****
	  if(data[6]>=128)
	  {
	     (*star).Dec=128-data[6]-data[7]/60.0-data[8]/3600.0;
	  }
	  else
	  {
	      (*star).Dec=data[6]+data[7]/60.0+data[8]/3600.0;
	  }
	  //*****

	  (*star).Bright=data[9]+data[10]/10.0;

	    //*****
	  for(i=11;i<19;i++)
	 {
	    (*star).TypeEn[i-11]=data[i];
	 }
	 (*star).ConEn[8]=0x20;
	 (*star).ConEn[9]=0x00;
	 //*****


		
	 return  1;
 }
//***********************************************************


//***********************************************************
//NGC7840星表
typedef struct  
{
     char ConEn[5];//星座英文名简写3
	 float Ra ;     // （赤经）3
	 float Dec;     // 赤纬）3
	 float Bright;   //亮度2
	 char TypeEn[10];//类型英文名
	
}NGC7840 ;
//***********************************************************


uint8 GetNGC7840(uint16 starnum, NGC7840* star)//从星表获取校准星
 {
     uint16 page;
	 uint16 pageoffset;
	 uint8 data[19];
	 uint8 i;
	 //*****
	 if((starnum==0)&&(starnum>7840))
	 {
	   return  0;
	 }

	   //*****
	  page=(starnum-1)/27;
	  pageoffset=((starnum-1)%27)*19;
      ReadFromRom(page+251,pageoffset,19,data);	  
	  //*****
	  for(i=0;i<3;i++)
	 {
	    (*star).ConEn[i]=data[i];
	 }
	 (*star).ConEn[3]=0x20;
	 (*star).ConEn[4]=0x00;
	 //*****


		  
	  (*star).Ra=data[3]+data[4]/60.0+data[5]/3600.0;
	  //*****
	  if(data[6]>=128)
	  {
	     (*star).Dec=128-data[6]-data[7]/60.0-data[8]/3600.0;
	  }
	  else
	  {
	      (*star).Dec=data[6]+data[7]/60.0+data[8]/3600.0;
	  }
	  //*****

	  (*star).Bright=data[9]+data[10]/10.0;

	    //*****
	  for(i=11;i<19;i++)
	 {
	    (*star).TypeEn[i-11]=data[i];
	 }
	 (*star).ConEn[8]=0x20;
	 (*star).ConEn[9]=0x00;
	 //*****


		
	 return  1;
 }
//***********************************************************



//***********************************************************
//SAO258997星表
typedef struct  
{
	 float Ra ;     // （赤经）3
	 float Dec;     // 赤纬）3
	
}SAO258997 ;
//***********************************************************


uint8 GetSAO258997(uint32 starnum, SAO258997* star)//从星表获取校准星
 {
     uint16 page;
	 uint16 pageoffset;
	 uint8 data[6];
	 //*****
	 if((starnum==0)&&(starnum>258997))
	 {
	   return  0;
	 }

	   //*****
	  page=(starnum-1)/88;
	  pageoffset=((starnum-1)%88)*6;
      ReadFromRom(page+542,pageoffset,6,data);
	  
	  //*****
		  
	  (*star).Ra=data[0]+data[1]/60.0+data[2]/3600.0;
	  //*****
	  if(data[3]>=128)
	  {
	     (*star).Dec=128-data[3]-data[4]/60.0-data[5]/3600.0;
	  }
	  else
	  {
	      (*star).Dec=data[3]+data[4]/60.0+data[5]/3600.0;
	  }
	  //*****


		
	 return  1;
 }
//***********************************************************




//***********************************************************
//ChinaCity640地点
typedef struct  
{
     char PrvcCn[10];//省中文名8
	 char CityCn[10];//省中文名8
	 float Lon ;     // 经度 2
	 float Lat;     // 纬度	2
	
}ChinaCity640 ;
//***********************************************************


uint8 GetChinaCity640(uint16 citynum, ChinaCity640* city)//从星表获取校准星
 {
     uint16 page;
	 uint16 pageoffset;
	 uint8 data[20];
	 uint8 i;
	 //*****
	 if((citynum==0)&&(citynum>640))
	 {
	   return  0;
	 }

	   //*****
	  page=(citynum-1)/26;
	  pageoffset=((citynum-1)%26)*20;
      ReadFromRom(page+3486,pageoffset,20,data);
	  //*****
	  for(i=0;i<8;i++)
	 {
	    (*city).PrvcCn[i-0]=data[i];
	 }
	 (*city).PrvcCn[8]=0x00;
	 (*city).PrvcCn[9]=0x00;
	  //*****

     for(i=8;i<16;i++)
	 {
	    (*city).CityCn[i-8]=data[i];
	 }
	 (*city).CityCn[8]=0x00;
	 (*city).CityCn[9]=0x00;
	  //*****

	  
	  //*****
		  
	  (*city).Lon=data[16]+data[17]/100.0;
	  //*****
	   (*city).Lat=data[18]+data[19]/100.0;
	  //*****


		
	 return  1;
 }
//***********************************************************




//***********************************************************
//WorldCity170地点
typedef struct  
{
     char CountryEn[20];//国家英文名18
	 char CityEn[18];//城市英文名16
	 float Lon ;     // 经度 3
	 float Lat;     // 纬度	2
	 int Zone;     //时区1
	
}WorldCity170 ;
//***********************************************************


uint8 GetWorldCity170(uint16 citynum, WorldCity170* city)//从星表获取校准星
 {
     uint16 page;
	 uint16 pageoffset;
	 uint8 data[40];
	 uint8 i;
	 //*****
	 if((citynum==0)&&(citynum>170))
	 {
	   return  0;
	 }

	   //*****
	  page=(citynum-1)/13;
	  pageoffset=((citynum-1)%13)*40;
      ReadFromRom(page+3511,pageoffset,40,data);
	  //*****
	  for(i=0;i<18;i++)
	 {
	    (*city).CountryEn[i-0]=data[i];
	 }
	 (*city).CountryEn[18]=0x20;
	 (*city).CountryEn[19]=0x00;
	  //*****

     for(i=18;i<34;i++)
	 {
	    (*city).CityEn[i-18]=data[i];
	 }
	 (*city).CityEn[16]=0x20;
	 (*city).CityEn[17]=0x00;
	  //*****

	  
	  //*****
	  if(data[34]>=128)
	  {  
	    (*city).Lon=(128-data[34])*100-data[35]-data[36]/60.0;
		}
		else
		{
		 (*city).Lon=data[34]*100+data[35]+data[36]/60.0;
		}
	  //*****
	  if(data[37]>=128)
	  { 
	     (*city).Lat=128-data[37]-data[38]/60.0;
	  }
	  else
	  { 
	     (*city).Lat=data[37]+data[38]/60.0;
	   }
	  //*****

	  if(data[39]>128)
	  { 
	     (*city).Zone=128-data[39];
	  }
	  else
	  { 
	     (*city).Zone=data[39];
	   }
	  //*****



		
	 return  1;
 }
//***********************************************************




//***********************************************************
//自定义天空目标最多9个+1颗指定星
typedef struct  
{
     uint8 flag;      //是否有目标标志1
     char NameEn[10];//星英文名8
	 float Ra ;     // 赤经 7
	 float Dec;     // 赤纬	8
	
}CustomStar9 ;
//***********************************************************


uint8 GetCustomStar(uint8 starnum, CustomStar9* star)//获取自定义星
 {
	 uint8 data0[528];
	 uint8 data[24];
	 uint8 i;
	 //*****
	 if((starnum==0)&&(starnum>10))
	 {
	   return  0;
	 }
	  //(*star).flag=0;
	   //*****
     //ReadFromRom(3525,(starnum-1)*24,24,data);
	  ReadFromRom(3525,0,528,data0);
	  for(i=0;i<24;i++)
	  {
	    data[i]=data0[(starnum-1)*24+i];
	  }
	  //*****
	  (*star).flag=data[0]; 
	  for(i=1;i<9;i++)
	 {
	    (*star).NameEn[i-1]=data[i];
	 }


	 (*star).Ra=data[9]*10+data[10]+(data[11]*10+data[12])/60.0+(data[13]*10+data[14]+data[15]/10.0)/3600.0;

	 (*star).Dec=data[17]*10+data[18]+(data[19]*10+data[20])/60.0+(data[21]*10+data[22]+data[23]/10.0)/3600.0;
     if(data[16]=='-')
	 {
	   (*star).Dec=(*star).Dec*(-1.0);
	 }
		
	 return  1;
 }
//***********************************************************




//***********************************************************
//自动天空目标最多9个
typedef struct  
{
     uint8 flag;      //是否有目标标志1
     char NameEn[10];//目标英文名8
	 float Azi ;     // 赤经 8
	 float Alt;     // 赤纬	8
	
}CustomLandTarget9 ;
//***********************************************************


uint8 GetCustomLandTarget(uint8 targetnum, CustomLandTarget9* target)//从获取自定义陆地目标
 {
	 uint8 data0[528];
	 uint8 data[25];
	 uint8 i;
	 //*****
	 if((targetnum==0)&&(targetnum>9))
	 {
	   return  0;
	 }
	  //(*target).flag=0;
	   //*****
      //ReadFromRom(3526,(targetnum-1)*25,25,data);
	  ReadFromRom(3526,0,528,data0);
	  for(i=0;i<25;i++)
	  {
	    data[i]=data0[(targetnum-1)*25+i];
	  }
	  //*****
	  (*target).flag=data[0]; 
	  for(i=1;i<9;i++)
	 {
	    (*target).NameEn[i-1]=data[i];
	 }


	 (*target).Azi=data[9]*100+data[10]*10+data[11]+(data[12]*10+data[13])/60.0+(data[14]*10+data[15]+data[16]/10.0)/3600.0;

	 (*target).Alt=data[18]*10+data[19]+(data[20]*10+data[21])/60.0+(data[22]*10+data[23]+data[24]/10.0)/3600.0;
     if(data[17]=='-')
	 {
	   (*target).Alt=(*target).Alt*(-1.0);
	 }
		
	 return  1;
 }
//***********************************************************

//***********************************************************
//读最近观测的星
uint8 GetRecentTarget(uint8 startype[8],uint32 starno[8],uint8 rdata[57])	 
{

    uint8 data[57];
	uint8 i;
	uint8 starnum;

	ReadFromRom(3527,0,57,data);
	starnum=data[0];
	
	for(i=0;i<starnum;i++)
	{   
	   startype[i]=data[i*7+1];//-48;
	}

	for(i=0;i<starnum;i++)
	{   
	   starno[i]=(data[i*7+2]-48)*100000+(data[i*7+3]-48)*10000+(data[i*7+4]-48)*1000+(data[i*7+5]-48)*100+(data[i*7+6]-48)*10+(data[i*7+7]-48);   
	}
	rdata=data;
	return data[0];

}
//***********************************************************