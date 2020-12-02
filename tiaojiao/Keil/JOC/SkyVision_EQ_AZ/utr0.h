#define FOSC		11059200//12000000		//晶振频率
#define PLL_M		5				//倍频系数
#define MSEL		(PLL_M-1)
#define PLL_P		2				//分频系数	 P=Fcco/(CCLK×2)

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
//串口零通信数据定义
uint8 rcv_datanum0;	    //当前收到指令的字节数
uint8 rcv_databuf0[10];		// UART0数据接收缓冲区
uint8 rcv_neworder0;		    //收到新指令的示志
uint8 rcv_headernum0;       //收到协议头的个数
uint8 rcv_header0[4];   //通信协议头
uint8 rcv_temp0;		 //零时收到的存放

//串口一通信数据定义
//串口零通信数据定义
uint8 rcv_datanum1;	    //当前收到指令的字节数
uint8 rcv_databuf1[10];		// UART0数据接收缓冲区
uint8 rcv_neworder1;		    //收到新指令的示志
uint8 rcv_headernum1;       //收到协议头的个数
uint8 rcv_header1[4];   //通信协议头
uint8 rcv_temp1;		 //零时收到的存放

//******************************
uint8 g_mTelescopeConType;//0没有望远镜连接，1望远镜为赤道式，2望远镜为地平式，3有望远镜连接

 //*****************************************************************
 //*****************************************************************



 //串口一中断子程序
void __irq IRQ_UART1(void)	 ;


//串口零中断子程序
void __irq IRQ_UART0 (void)	 ;

 //*****************************************************************
 //中断零初始化
void Init_Uart0(unsigned int Baud)	;

//串口零通信
//*****************************************
//获取一个字节
uint8 UART0_GetByte (void) ;


//获取n个字节
void UART0_GetStr (uint8 *s, uint32 n) ;

//发送一个字节
void  UART0_SentByte(unsigned char data)   ;

//发送n个字节,n不指定，但以'\0\结尾的字符串
void  SUART0_SentStr(unsigned char const *str)	 ;

 //*****************************************************************
 //*****************************************************************
 //*****************************************************************
  //中断零初始化
void Init_Uart1(unsigned int Baud)	 ;

uint8 UART1_GetByte (void) ;

//获取n个字节
void UART1_GetStr (uint8 *s, uint32 n)	;


//发送一个字节
void  UART1_SentByte(unsigned char data)  ;


//发送n个字节,n不指定，但以'\0\结尾的字符串
void  UART1_Sent_Str(unsigned char const *str)	 ;

//*****************************************************
//*****************************************************
//延时子程序
void delay (unsigned int i)  ;
