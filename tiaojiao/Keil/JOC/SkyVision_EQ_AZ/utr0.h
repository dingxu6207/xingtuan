#define FOSC		11059200//12000000		//����Ƶ��
#define PLL_M		5				//��Ƶϵ��
#define MSEL		(PLL_M-1)
#define PLL_P		2				//��Ƶϵ��	 P=Fcco/(CCLK��2)

#define PSEL0 		5				//
#define PSEL1 		6

#define PLLE		0
#define PLLC		1

#define PLOCK		10

#define PLL_FEED1	0xAA
#define PLL_FEED2	0x55

#define UART_BAUD(baud) (unsigned  int)((FOSC*PLL_M) / (baud * 16))

 //*****************************************************************
 //*****************************************************************
 //*****************************************************************
//������ͨ�����ݶ���
uint8 rcv_datanum0;	    //��ǰ�յ�ָ����ֽ���
uint8 rcv_databuf0[10];		// UART0���ݽ��ջ�����
uint8 rcv_neworder0;		    //�յ���ָ���ʾ־
uint8 rcv_headernum0;       //�յ�Э��ͷ�ĸ���
uint8 rcv_header0[4];   //ͨ��Э��ͷ
uint8 rcv_temp0;		 //��ʱ�յ��Ĵ��

//����һͨ�����ݶ���
//������ͨ�����ݶ���
uint8 rcv_datanum1;	    //��ǰ�յ�ָ����ֽ���
uint8 rcv_databuf1[10];		// UART0���ݽ��ջ�����
uint8 rcv_neworder1;		    //�յ���ָ���ʾ־
uint8 rcv_headernum1;       //�յ�Э��ͷ�ĸ���
uint8 rcv_header1[4];   //ͨ��Э��ͷ
uint8 rcv_temp1;		 //��ʱ�յ��Ĵ��

//******************************
uint8 g_mTelescopeConType;//0û����Զ�����ӣ�1��Զ��Ϊ���ʽ��2��Զ��Ϊ��ƽʽ��3����Զ������

 //*****************************************************************
 //*****************************************************************



 //����һ�ж��ӳ���
void __irq IRQ_UART1(void)	 ;


//�������ж��ӳ���
void __irq IRQ_UART0 (void)	 ;

 //*****************************************************************
 //�ж����ʼ��
void Init_Uart0(unsigned int Baud)	;

//������ͨ��
//*****************************************
//��ȡһ���ֽ�
uint8 UART0_GetByte (void) ;


//��ȡn���ֽ�
void UART0_GetStr (uint8 *s, uint32 n) ;

//����һ���ֽ�
void  UART0_SentByte(unsigned char data)   ;

//����n���ֽ�,n��ָ��������'\0\��β���ַ���
void  SUART0_SentStr(unsigned char const *str)	 ;

 //*****************************************************************
 //*****************************************************************
 //*****************************************************************
  //�ж����ʼ��
void Init_Uart1(unsigned int Baud)	 ;

uint8 UART1_GetByte (void) ;

//��ȡn���ֽ�
void UART1_GetStr (uint8 *s, uint32 n)	;


//����һ���ֽ�
void  UART1_SentByte(unsigned char data)  ;


//����n���ֽ�,n��ָ��������'\0\��β���ַ���
void  UART1_Sent_Str(unsigned char const *str)	 ;

//*****************************************************
//*****************************************************
//��ʱ�ӳ���
void delay (unsigned int i)  ;
