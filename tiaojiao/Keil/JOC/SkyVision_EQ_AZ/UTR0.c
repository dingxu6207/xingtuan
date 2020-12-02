// �޸ļ�¼��
// 2008-08-30	fanyufeng	������ʱ�ӣ��޸Ĳ����ʷ�Ƶ
// 2009-02-05   Heshousheng ���UART0_SentByteArray(unsigned char const *str)����
//2013-04-13    HeShouSheng	��ӵ������ݽ��յ��ж�
#include "utr0.h" 

int AGuiderRa,AGuiderDec; 
//int AGuiderRa1,AGuiderDec1; 

 //����һ�ж��ӳ���
void __irq IRQ_UART1(void)
{  		 
    rcv_temp1= U1RBR;
	if(g_mTelescopeConType==0)
	{
	  g_mTelescopeConType=3;//��Զ���Ƿ����ӣ���true������false
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
							  g_mTelescopeConType=1;//��Զ��Ϊ���ʽ����
							  break;
							  case 68:
							  case 100:
							  g_mTelescopeConType=2;//��Զ��Ϊ��ƽʽ����
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
	VICVectAddr = 0x00;	// �жϴ������
}

//�������ж��ӳ���
void __irq IRQ_UART0 (void)
{ 
   USART_IRQHandler(U0RBR);
	 VICVectAddr = 0x00;	// �жϴ������
}

//�������ж��ӳ���
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
	VICVectAddr = 0x00;	// �жϴ������
}
 //*****************************************************************
 //�ж����ʼ��
void Init_Uart0(unsigned int Baud)
 {
  //���������ó�ʼ��
     U0LCR = 0x83;
//	fanyufeng 2008-08-30                   
     U0DLM=0;//(unsigned char)(Baud>>8);
     U0DLL = 72;//(unsigned char)Baud;        11059200/16/9600 = 72            
 //	fanyufeng 2008-08-30                   
 
    U0LCR = 0x03; 	     
	U0FCR = 0x01;						// ʹ��FIFO�������ô�����Ϊ8�ֽ�
	U0IER = 0x01;						// ����RBR�жϣ��������ж�
 	VICVectAddr1 = (uint32)IRQ_UART0;	// ����UART0������ַ

    
  //�����������ʼ��
  	 rcv_datanum0=0;	    //��ǰ�յ�ָ����ֽ���
        		// UART0���ݽ��ջ�����
	 rcv_neworder0=0;		    //�յ���ָ���ʾ־
	 rcv_headernum0=0;       //�յ�Э��ͷ�ĸ���
	 rcv_header0[0]=0x55;   //ͨ��Э��ͷ
	 rcv_header0[1]=0xAA;   //ͨ��Э��ͷ
	 rcv_header0[2]=0x01;   //ͨ��Э��ͷ
	 rcv_header0[3]=0;   //ͨ��Э��ͷ,�յ�ָ��ĳ���
 }

//������ͨ��
//*****************************************
//��ȡһ���ֽ�
uint8 UART0_GetByte (void)
{
	uint8 rcv_dat;

	while ((U0LSR & 0x01) == 0);
	rcv_dat = U0RBR;
	
	return (rcv_dat);	
}

//��ȡn���ֽ�
void UART0_GetStr (uint8 *s, uint32 n)
{
	for ( ; n>0; n--)
	{
		*s++ = UART0_GetByte();
	}
}

//����һ���ֽ�
void  UART0_SentByte(unsigned char data)
{  
	U0THR = data;				    // ��������

   while( (U0LSR&0x40)==0 );	    // �ȴ����ݷ������
}

//����length���ֽڵ�
void  UART0_SentByteArray(uint8 const *str,uint8 length)  
{ 
	while(length--)
	{
      	UART0_SentByte(*str++);	    // ��������
		//delay(5);
	}
}
//����n���ֽ�,n��ָ��������'\0\��β���ַ���
void  SUART0_SentStr(unsigned char const *str)
{ 
  	uint8 i;
  	while(1)
   	{ 
   		if( *str == '\0' ) break;
		for(i=0;i<44;i++)
      		UART0_SentByte(*str++);	    // ��������
  	 }
}

 //*****************************************************************
 //*****************************************************************
 //*****************************************************************
  //�ж����ʼ��
void Init_Uart1(unsigned int Baud)
 {
  //���������ó�ʼ��
     U1LCR = 0x83;                   
     U1DLM=0;//(unsigned char)(Baud>>8);
     U1DLL = 72;//(unsigned char)Baud;        11059200/16/9600 = 72             
  
    U1LCR = 0x03; 	     
	U1FCR = 0x01;						// ʹ��FIFO�������ô�����Ϊ8�ֽ�
	U1IER = 0x01;						// ����RBR�жϣ��������ж�
 	VICVectAddr2 = (uint32)IRQ_UART1;	// ����UART0������ַ
  
   //����һ������ʼ��
  	 rcv_datanum1=0;	    //��ǰ�յ�ָ����ֽ���
        		// UART0���ݽ��ջ�����
	 rcv_neworder1=0;		    //�յ���ָ���ʾ־
	 rcv_headernum1=0;       //�յ�Э��ͷ�ĸ���
	 rcv_header1[0]=0x55;   //ͨ��Э��ͷ
	 rcv_header1[1]=0xAA;   //ͨ��Э��ͷ
	 rcv_header1[2]=0x01;   //ͨ��Э��ͷ
	 rcv_header1[3]=0;   //ͨ��Э��ͷ,�յ�ָ��ĳ���
 }
//����һͨ��
//*****************************************
//��ȡһ���ֽ�
uint8 UART1_GetByte (void)
{
	uint8 rcv_dat;

	while ((U1LSR & 0x01) == 0);
	rcv_dat = U1RBR;
	
	return (rcv_dat);	
}

//��ȡn���ֽ�
void UART1_GetStr (uint8 *s, uint32 n)
{
	for ( ; n>0; n--)
	{
		*s++ = UART1_GetByte();
	}
}

//����һ���ֽ�
void  UART1_SentByte(unsigned char data)
{  
	U1THR = data;				    // ��������

   while( (U1LSR&0x40)==0 );	    // �ȴ����ݷ������
}

//����n���ֽ�,n��ָ��������'\0\��β���ַ���
void  UART1_Sent_Str(unsigned char const *str)
{ 
  uint8 i;
  while(1)
   { if( *str == '\0' ) break;
   
	for(i=0;i<44;i++)

      UART1_SentByte(*str++);	    // ��������
   }
}

 //*****************************************************************
 //*****************************************************************
 //*****************************************************************

 
//*****************************************************
//*****************************************************
//��ʱ�ӳ���
void delay (unsigned int i) {                        /* Delay function */
unsigned int n;
while(i>1)
{
	for(n=65535;n>1;n--);
	i--;
}
}






























