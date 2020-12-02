#ifndef __at24c02_H
#define	__at24c02_H

#include "stm32f10x.h"
#include "iodef.h"

#define SCL_H  GPIO_SetBits(SCL_GPIO_PORT,SCL_GPIO_PIN) 
#define SCL_L  GPIO_ResetBits(SCL_GPIO_PORT,SCL_GPIO_PIN)   
#define SDA_H  GPIO_SetBits(SDA_GPIO_PORT,SDA_GPIO_PIN) 
#define SDA_L  GPIO_ResetBits(SDA_GPIO_PORT,SDA_GPIO_PIN)   

void AT24C02_SDA_IO_SET(unsigned char io_set); 
void delay2(u32 x) ; 
void delay_nop(void); 
void I2C_init(void); 
void I2C_start(void); 
void I2C_stop(void);  
void I2C_write_byte(int j); 
u8   I2C_read_byte(void); 
void I2C_reply(void);  
void I2C_write_addr(u8 addr,u8 data) ; 
u8   I2C_read_addr(int addr) ;
void Write_Flash(u8 *buff, u16 staddr, u16 len);
void Read_Flash(u8 *buff, u16 staddr, u16 len);

#endif

