#ifndef __I2C_EE_H
#define __I2C_EE_H
	#ifdef __I2C_EE_C
		#define EXTE_I2C
	#else
		#define EXTE_I2C extern
	#endif
typedef unsigned          char u8;
typedef unsigned short     int u16;
typedef unsigned           int u32;
//#include "stm32f4xx.h"

#include "main.h"
#include "stm32f0xx_hal.h"
//#include "sys.h"
//#include "stm32f0xx_hal_gpio.h"

//外部无上拉电阻，无法开漏配置成双向io 只能先尝试内部上拉		
#define SCL_H	GPIOF->BSRR = GPIO_PIN_1
#define SCL_L	GPIOF->BRR  = GPIO_PIN_1

#define SDA_H	GPIOF->BSRR = GPIO_PIN_0
#define SDA_L	GPIOF->BRR  = GPIO_PIN_0

#define SDA_read	(GPIOF->IDR  & GPIO_PIN_0)

		
//#define SCL_H	HAL_GPIO_WritePin(GPIOF,GPIO_PIN_1,SET)
//#define SCL_L	HAL_GPIO_WritePin(GPIOF,GPIO_PIN_1,RESET)

//#define SDA_H	HAL_GPIO_WritePin(GPIOF,GPIO_PIN_0,SET)
//#define SDA_L	HAL_GPIO_WritePin(GPIOF,GPIO_PIN_0,RESET)

//#define SDA_read	HAL_GPIO_ReadPin(GPIOF,GPIO_PIN_0)

//外部无上拉电阻，无法开漏配置成双向io 只能先尝试内部上拉
#define SDAToRead	(GPIOF->MODER &=~(3<<0) )
#define SDAToWrite	(GPIOF->MODER |=  1<<0  )

//#define I2C_PageSize			64
//#define EEPROM_ADDRESS			0xA0
//#define LM75_ADDRESS			0x92

#define I2C_TIMEOUT				0x00200000
#define I2C_TM_ERR				0x0000FFFF
#define I2C_TM_OK				  0x00000000

void I2C_Init(void);
void I2C_delay(void);
u16 I2C_Start(void);
void I2C_Stop(void);
void I2C_Ack(void);
void I2C_NoAck(void);
u16 I2C_WaitAck(void);
void I2C_SendByte(u8 SendByte);
u8 I2C_ReceiveByte(void);
//EXTE_I2C u8	I_time;

//EXTE_I2C u16  I2C_EE_ByteWrite(u8* pBuffer, u16 WriteAddr);
//EXTE_I2C u16  I2C_EE_PageWrite(u8* pBuffer, u16 WriteAddr, u16 NumByteToWrite);
//EXTE_I2C u16  I2C_EE_BufferWrite(u8* pBuffer, u16 WriteAddr, u16 NumByteToWrite);
//EXTE_I2C u16  I2C_EE_BufferRead(u8* pBuffer, u16 ReadAddr, u16 NumByteToRead);
//EXTE_I2C u16  I2C_EE_WaitEepromStandbyState(void);
//EXTE_I2C u16  I2C_LM75_Read(void);

#endif


