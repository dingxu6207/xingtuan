// 修改记录  2008-11-17  范玉峰  手柄硬件更新1.04版

//#define  XB_CS     1<<3   //星表片选				 0	   原手柄硬件0.91版,新版改为1.24
#define  XB_CS     1<<24   //星表片选				 1	   1.04版硬件。	   									注意：0.91版为P0，1.04版是P1.
#define  HZK_CS    1<<25  //汉字库片选				 1 
#define  LCD_CS    1<<10  //LCD片选				 0 		
#define  LCD_CD    1<<23  //LCD CD					 1
//#define  LCD_SCK   1<<11  //LCD SCK		  		 0	 	原手柄硬件0.91版,新版改为P0.12。	
#define  LCD_SCK   1<<12  //LCD SCK		  		 0	 	 	1.04版硬件。	
//#define  LCD_SDA   1<<12  //LCD SDA		  		 0		原手柄硬件0.91版,新版改为P0.15。
#define  LCD_SDA   1<<15  //LCD SDA		  		 0			1.04版硬件。
#define  TORCH1     1<<13  //TORCH(照明1)			 0
#define  TORCH2     1<<16  //TORCH(照明2)			 0
#define  ISP_S     1<<14  //ISP开关
#define  LED_SD    1<<15  //SD卡指示灯			 	 0
#define  SD_W_CH    1<<16  //SD写保护检测			 0
#define  SD_I_CH    1<<20  //SD插入护检测			 1
#define  KEY1       1<<22  //键1					 0
#define  KEY2       1<<25  //键2					 0
#define  KEY3       1<<28  //键3					 0
#define  KEY4       1<<29  //键4					 0
#define  KEY5       1<<30  //键5					 0
#define  LED_ST1       1<<24  //状态1指示			 1
//#define  LED_ST2       1<<2  //状态1指示			 0		 原手柄硬件0.91版,新版不再使用。
#define  KEYA       1<<19  //键A指示				 1
#define  KEYB       1<<18  //键B指示				 1
#define  KEYC       1<<17  //键C指示				 1
#define  KEYD       1<<16  //键D指示				 1
#define  IN_CH       1<<21  //外部中断检测		 1
#define  BEEP       1<<22  //蜂鸣器				 1

#define TORCH1ON() IOCLR0 = TORCH1
#define TORCH1OFF() IOSET0 = TORCH1
#define TORCH2ON() IOSET0 = TORCH2
#define TORCH2OFF() IOCLR0 = TORCH2




