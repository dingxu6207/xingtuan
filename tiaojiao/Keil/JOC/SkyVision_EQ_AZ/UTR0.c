// 修改记录：
// 2008-08-30	fanyufeng	根据新时钟，修改拨特率分频
// 2009-02-05   Heshousheng 添加UART0_SentByteArray(unsigned char const *str)函数
//2013-04-13    HeShouSheng	添加导星数据接收到中断
#include "utr0.h" 

int AGuiderRa,AGuiderDec; 
//int AGuiderRa1,AGuiderDec1; 

 //串口一中断子程序
void __irq IRQ_UART1(void)
{  		 
    rcv_temp1= U1RBR;
	if(g_mTelescopeConType==0)
	{
	  g_mTelescopeConType=3;//望远镜是否连接，是true，不是false
	}
	 
   if(rcv_neworder1==0)
   {
 		
	    switch(	rcv_headernum1)
		{  
		   
		   case 0:
		      if(rcv_header1[0]==rcv_temp1)
			  {
			      rcv_headernum1++; 
				  
			  }
			  break;
		   case 1:
		    if(rcv_header1[1]==rcv_temp1)
			  {
			      rcv_headernum1++;
				  
			  }
			  else
			  {
			      rcv_headernum1=0;
			  }
			   break;
			case 2:	
			 if(rcv_header1[2]==rcv_temp1)
			  {
			      rcv_headernum1++;
				  
			  }
			  else
			  {
			      rcv_headernum1=0;
			  }
			   break;
			case 3:
			    if(rcv_temp1<10)
				{
			       rcv_header1[3]=rcv_temp1; 
				   rcv_headernum1++;
				   
				 }
				 else
				 {
				    rcv_headernum1=0;
				}
			 break;
			case 4:
			  	if(rcv_datanum1<rcv_header1[3])
				{  
				   rcv_databuf1[rcv_datanum1]=rcv_temp1;
				   rcv_datanum1++;
				   if(rcv_datanum1==rcv_header1[3]) 
					{
					   rcv_neworder1=1;
				       rcv_headernum1=0;
				       rcv_datanum1=0;
					   if((g_mTelescopeConType!=1)||(g_mTelescopeConType!=2))
					   {
						   switch(rcv_databuf1[0])
						   {
						      case 4:
							  case 36:
							  g_mTelescopeConType=1;//望远镜为赤道式类型
							  break;
							  case 68:
							  case 100:
							  g_mTelescopeConType=2;//望远镜为地平式类型
							  break;
							  default:
							  break;
							}
						}
						  
					 
					 }
					   
				}  

			break;
			default:
			break;
		}
   	}
	VICVectAddr = 0x00;	// 中断处理结束
}

//串口零中断子程序
void __irq IRQ_UART0 (void)
{ 
   USART_IRQHandler(U0RBR);
	 VICVectAddr = 0x00;	// 中断处理结束
}

//串口零中断子程序
void __irq IRQ_UART0 (void)
{ 
   rcv_temp0= U0RBR;
   if(rcv_neworder0==0)
   {
        		
	    switch(	rcv_headernum0)
		{  
		   
		   case 0:
		      if(rcv_header0[0]==rcv_temp0)
			  {
			      rcv_headernum0++; 
			  
			  }
			  break;
		   case 1:
		    if(rcv_header0[1]==rcv_temp0)
			  {
			      rcv_headernum0++;
				  
			  }
			  else
			  {
			      rcv_headernum0=0;
			  }
			   break;
			case 2:	
			 if(rcv_header0[2]==rcv_temp0)
			  {
			      rcv_headernum0++;
				  
			  }
			  else
			  {
			      rcv_headernum0=0;
			  }
			   break;
			case 3:
			    if(rcv_temp0<10)
				{
			       rcv_header0[3]=rcv_temp0; 
				   rcv_headernum0++;
				   
				 }
				 else
				 {
				    rcv_headernum0=0;
				}
			 break;
			case 4:
			  	if(rcv_datanum0<rcv_header0[3])
				{  
				   rcv_databuf0[rcv_datanum0]=rcv_temp0;
				   rcv_datanum0++;
				   if(rcv_datanum0==rcv_header0[3]) 
					{
					   rcv_neworder0=1;
				       rcv_headernum0=0;
				       rcv_datanum0=0; 
					   //HeShouSheng 20130413
					   switch(rcv_databuf0[0])
					   {
							case 1:
								AGuiderRa=-1;	//EAST
								rcv_neworder0=0;
								break;	
							case 2:
								AGuiderRa=1;  //WEST
								rcv_neworder0=0;
								break;
							case 4:
								AGuiderDec=-1;//NORTH
								rcv_neworder0=0;
								break;
							case 8:
								AGuiderDec=1; //SOUTH
								rcv_neworder0=0;
								break;
							default :
								break;
						}
						//
					 }
					   
				}  

			break;
			default:
			break;
		}
   	}
	VICVectAddr = 0x00;	// 中断处理结束
}
 //*****************************************************************
 //中断零初始化
void Init_Uart0(unsigned int Baud)
 {
  //串口零设置初始化
     U0LCR = 0x83;
//	fanyufeng 2008-08-30                   
     U0DLM=0;//(unsigned char)(Baud>>8);
     U0DLL = 72;//(unsigned char)Baud;        11059200/16/9600 = 72            
 //	fanyufeng 2008-08-30                   
 
    U0LCR = 0x03; 	     
	U0FCR = 0x01;						// 使能FIFO，并设置触发点为8字节
	U0IER = 0x01;						// 允许RBR中断，即接收中断
 	VICVectAddr1 = (uint32)IRQ_UART0;	// 设置UART0向量地址

    
  //串口零变量初始化
  	 rcv_datanum0=0;	    //当前收到指令的字节数
        		// UART0数据接收缓冲区
	 rcv_neworder0=0;		    //收到新指令的示志
	 rcv_headernum0=0;       //收到协议头的个数
	 rcv_header0[0]=0x55;   //通信协议头
	 rcv_header0[1]=0xAA;   //通信协议头
	 rcv_header0[2]=0x01;   //通信协议头
	 rcv_header0[3]=0;   //通信协议头,收到指令的长度
 }

//串口零通信
//*****************************************
//获取一个字节
uint8 UART0_GetByte (void)
{
	uint8 rcv_dat;

	while ((U0LSR & 0x01) == 0);
	rcv_dat = U0RBR;
	
	return (rcv_dat);	
}

//获取n个字节
void UART0_GetStr (uint8 *s, uint32 n)
{
	for ( ; n>0; n--)
	{
		*s++ = UART0_GetByte();
	}
}

//发送一个字节
void  UART0_SentByte(unsigned char data)
{  
	U0THR = data;				    // 发送数据

   while( (U0LSR&0x40)==0 );	    // 等待数据发送完毕
}

//发送length个字节的
void  UART0_SentByteArray(uint8 const *str,uint8 length)  
{ 
	while(length--)
	{
      	UART0_SentByte(*str++);	    // 发送数据
		//delay(5);
	}
}
//发送n个字节,n不指定，但以'\0\结尾的字符串
void  SUART0_SentStr(unsigned char const *str)
{ 
  	uint8 i;
  	while(1)
   	{ 
   		if( *str == '\0' ) break;
		for(i=0;i<44;i++)
      		UART0_SentByte(*str++);	    // 发送数据
  	 }
}

 //*****************************************************************
 //*****************************************************************
 //*****************************************************************
  //中断零初始化
void Init_Uart1(unsigned int Baud)
 {
  //串口零设置初始化
     U1LCR = 0x83;                   
     U1DLM=0;//(unsigned char)(Baud>>8);
     U1DLL = 72;//(unsigned char)Baud;        11059200/16/9600 = 72             
  
    U1LCR = 0x03; 	     
	U1FCR = 0x01;						// 使能FIFO，并设置触发点为8字节
	U1IER = 0x01;						// 允许RBR中断，即接收中断
 	VICVectAddr2 = (uint32)IRQ_UART1;	// 设置UART0向量地址
  
   //串口一变量初始化
  	 rcv_datanum1=0;	    //当前收到指令的字节数
        		// UART0数据接收缓冲区
	 rcv_neworder1=0;		    //收到新指令的示志
	 rcv_headernum1=0;       //收到协议头的个数
	 rcv_header1[0]=0x55;   //通信协议头
	 rcv_header1[1]=0xAA;   //通信协议头
	 rcv_header1[2]=0x01;   //通信协议头
	 rcv_header1[3]=0;   //通信协议头,收到指令的长度
 }
//串口一通信
//*****************************************
//获取一个字节
uint8 UART1_GetByte (void)
{
	uint8 rcv_dat;

	while ((U1LSR & 0x01) == 0);
	rcv_dat = U1RBR;
	
	return (rcv_dat);	
}

//获取n个字节
void UART1_GetStr (uint8 *s, uint32 n)
{
	for ( ; n>0; n--)
	{
		*s++ = UART1_GetByte();
	}
}

//发送一个字节
void  UART1_SentByte(unsigned char data)
{  
	U1THR = data;				    // 发送数据

   while( (U1LSR&0x40)==0 );	    // 等待数据发送完毕
}

//发送n个字节,n不指定，但以'\0\结尾的字符串
void  UART1_Sent_Str(unsigned char const *str)
{ 
  uint8 i;
  while(1)
   { if( *str == '\0' ) break;
   
	for(i=0;i<44;i++)

      UART1_SentByte(*str++);	    // 发送数据
   }
}

 //*****************************************************************
 //*****************************************************************
 //*****************************************************************

 
//*****************************************************
//*****************************************************
//延时子程序
void delay (unsigned int i) {                        /* Delay function */
unsigned int n;
while(i>1)
{
	for(n=65535;n>1;n--);
	i--;
}
}






























