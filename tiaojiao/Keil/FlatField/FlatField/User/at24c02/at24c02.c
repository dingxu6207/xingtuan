#include "at24c02.h"
#include "stm32f10x.h" 
//#include "system_config.h" 
//u8 sdata[12]={0,0,0,0,0,0,0,0,0,0,0,0};   
int baseAddr=0;
/*******************************************************************************  
* Function Name  : AT24C02_SDA_IO_SET(uchar io_set) 
* Description    : SDA方向控制 
* Input          : None 
* Output         : None 
* Return         : None  
*******************************************************************************/  
void AT24C02_SDA_IO_SET(unsigned char io_set) {    
	GPIO_InitTypeDef GPIO_InitStructure;    
	if(io_set)   
	{    
		GPIO_InitStructure.GPIO_Pin = SDA_GPIO_PIN ;//SDA设置为输出  
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
		GPIO_Init(GPIOB, &GPIO_InitStructure);   
	}   
	else   
	{    
		GPIO_InitStructure.GPIO_Pin = SDA_GPIO_PIN ;//SDA设置为输入   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   
		GPIO_Init(GPIOB, &GPIO_InitStructure);   
	} 
}   
/*******************************************************************************  
* Function Name  : delay2 
* Description    : 延时函数 
* Input          : None 
* Output         : None
* Return         : None  
*******************************************************************************/   
void delay2(u32 x)   {         
	u32 i;         
	for(i=0;i<x;i++);   
}      
/*******************************************************************************  
* Function Name  : delay_nop 
* Description    : 延时函数 
* Input          : None 
* Output         : None 
* Return         : None  
*******************************************************************************/  
void delay_nop(void) {    
	uint8_t i=10;//1.5us   
	while(i--); 
}   
/*******************************************************************************  
* Function Name  : 24C02_init() 
* Description    : 初始化函数 
* Input          : None 
* Output         : None 
* Return         : None  
*******************************************************************************/  
void I2C_init(void) {    
	//SCL=1  
	SCL_H;    
	delay_nop();   
	//SDA=1   
	SDA_H;   
	delay_nop(); 
}  
/*******************************************************************************  
* Function Name  : I2C_start()
* Description    : 开始信号 
* Input          : None 
* Output         : None 
* Return         : None  
*******************************************************************************/  
void I2C_start(void) {    
	SDA_H;   
	delay_nop();   
	SCL_H;   
	delay_nop();   
	SDA_L;   
	delay_nop();   
	SCL_L;   
	delay_nop(); 
}  
/*******************************************************************************  
* Function Name  : I2C_stop() 
* Description    : 结束信号 
* Input          : None 
* Output         : None 
* Return         : None  
*******************************************************************************/    
void I2C_stop(void) {    
	SDA_L;   
	delay_nop();   
	SCL_H;   
	delay_nop();   
	SDA_H;   
	delay_nop(); 
}  
/*******************************************************************************  
* Function Name  : I2C_write_byte() 
* Description    : 写一字节
* Input          : None 
* Output         : None 
* Return         : None  
*******************************************************************************/
void I2C_write_byte(int j) {    
	int i,temp,temp1;   
	temp=j;    
	//AT24C02_SDA_IO_SET(1);//发送数据   
	for(i=0;i<8;i++)   {      
		temp1=temp&0x80;//高位在前相与   
		temp=temp<<1;      
		SCL_L;//时钟设为低     
		delay_nop();      
		if(temp1==0x80)//发送到SDA线上    
		{        
			SDA_H;       
			delay_nop();     
		}     
		else     
		{        
			SDA_L;       
			delay_nop();     
		}      
		SCL_H;//时钟线设为高，开始传输数据     
		delay_nop();   
	}    
	SCL_L;//一个字节发送完成   
	delay_nop();   
	SDA_H;   
	delay_nop(); 
}  
/*******************************************************************************  
* Function Name  : I2C_read_byte() 
* Description    : 读一字节 
* Input          : None 
* Output         : None 
* Return         : None  
*******************************************************************************/       
u8 I2C_read_byte(void) {    
	u8 i,j,k=0;   
	SCL_L;   
	delay_nop();   
	SDA_H;
	delay_nop();    
	AT24C02_SDA_IO_SET(0);//SDA设置为输入  
	for(i=0;i<8;i++)   {     
		delay_nop();     
		SCL_H;    
		delay_nop();     
		if(GPIO_ReadInputDataBit(SDA_GPIO_PORT,SDA_GPIO_PIN)==1)      
			j=1;    
		else      
			j=0;    
		k=(k<<1)|j;    
		SCL_L;    
		delay_nop();   
	}    
	AT24C02_SDA_IO_SET(1);//SDA设置为输出  
	delay_nop();    
	return(k); 
}   
/*******************************************************************************  
* Function Name  : I2C_reply() 
* Description    : 读取应答信号 
* Input          : None 
* Output         : None 
* Return         : None  
*******************************************************************************/    
void I2C_reply(void) {    
	u16 i=0;    
	AT24C02_SDA_IO_SET(0);//SDA设置为输入  
	SCL_H;   
	delay_nop();    
	while((GPIO_ReadInputDataBit(SDA_GPIO_PORT,SDA_GPIO_PIN)==1)&&(i<5000))     
		i++;   
	SCL_L;   
	delay_nop();    
	AT24C02_SDA_IO_SET(1);//SDA设置为输出
	}  
/*******************************************************************************  
	* Function Name  : I2C_write_addr()
	* Description    : 制定地址写 
	* Input          : None 
	* Output         : None 
	* Return         : None  
	*******************************************************************************/   
void I2C_write_addr(u8 addr,u8 data)  {    
	I2C_start();   
	I2C_write_byte(0xa0);   
	I2C_reply();   
	I2C_write_byte(addr); 
	I2C_reply();    
	I2C_write_byte(data);  
	I2C_reply();  
	I2C_stop();  
	delay2(250); 
}   
/*******************************************************************************  
* Function Name  : I2C_read_addr() 
* Description    : 指定地址读取 
* Input          : None 
* Output         : None 
* Return         : None  
*******************************************************************************/    
//int  I2C_read_addr(int addr)   {  
u8  I2C_read_addr(int addr)   { 
	//int i=0; 
  u8 i=0; 	
	I2C_start();     
	I2C_write_byte(0xa0);    
	I2C_reply();    
	I2C_write_byte(addr);    
	I2C_reply();         
	I2C_start();     
	I2C_write_byte(0xa1);    
	I2C_reply();    
	i=I2C_read_byte();     
	I2C_stop();    
	delay2(250);     
	//return(i);
	return i;
}

void Write_Flash(u8 *buff, u16 staddr,u16 len)
{ 
	u16 i;
	for(i=0;i<len;i++)
	{
		I2C_write_addr(baseAddr+staddr+i,buff[i]);
		delay2(20000);//70000
	} 
}

void Read_Flash(u8 *buff, u16 staddr, u16 len)
{
	u16 i;
	for(i=0;i<len;i++)
	{
		buff[i]=I2C_read_addr(baseAddr+staddr+i);
		delay2(20000);//70000
	} 
}

