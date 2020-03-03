#ifndef _ADS1115_H
#define _ADS1115_H

#include "stm32f4xx_hal.h"
#include "main.h"

#define u32 unsigned int
#define u16 unsigned short int
#define u8 unsigned char

//GPIO 别名区定义  没有作用
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr))
#define BIT_ADDR(addr, bitnum)   MEM_ADDR( BITBAND(addr, bitnum)) 

#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C 
#define GPIOB_ODR_Addr    (GPIOB_BASE+12) //0x40010C0C 
#define GPIOC_ODR_Addr    (GPIOC_BASE+12) //0x4001100C 
#define GPIOD_ODR_Addr    (GPIOD_BASE+12) //0x4001140C 
#define GPIOE_ODR_Addr    (GPIOE_BASE+12) //0x4001180C 

#define GPIOA_IDR_Addr    (GPIOA_BASE+8) //0x40010808 
#define GPIOB_IDR_Addr    (GPIOB_BASE+8) //0x40010C08 
#define GPIOC_IDR_Addr    (GPIOC_BASE+8) //0x40011008 
#define GPIOD_IDR_Addr    (GPIOD_BASE+8) //0x40011408 
#define GPIOE_IDR_Addr    (GPIOE_BASE+8) //0x40011808 

//----------------------------------------------------- 
#define PA0   BIT_ADDR(GPIOA_ODR_Addr, 0)//输入
#define PA1   BIT_ADDR(GPIOA_ODR_Addr, 1)
#define PA2   BIT_ADDR(GPIOA_ODR_Addr, 2)    
#define PA3   BIT_ADDR(GPIOA_ODR_Addr, 3)    
#define PA4   BIT_ADDR(GPIOA_ODR_Addr, 4)    
#define PA5   BIT_ADDR(GPIOA_ODR_Addr, 5)    
#define PA6   BIT_ADDR(GPIOA_ODR_Addr, 6)    
#define PA7   BIT_ADDR(GPIOA_ODR_Addr, 7)    
#define PA8   BIT_ADDR(GPIOA_ODR_Addr, 8)    
#define PA9   BIT_ADDR(GPIOA_ODR_Addr, 9)    
#define PA10  BIT_ADDR(GPIOA_ODR_Addr, 10)   
#define PA11  BIT_ADDR(GPIOA_ODR_Addr, 11)   
#define PA12  BIT_ADDR(GPIOA_ODR_Addr, 12)   
#define PA13  BIT_ADDR(GPIOA_ODR_Addr, 13)   
#define PA14  BIT_ADDR(GPIOA_ODR_Addr, 14)   
#define PA15  BIT_ADDR(GPIOA_ODR_Addr, 15)   

#define PA0in   BIT_ADDR(GPIOA_IDR_Addr, 0) //输出   
#define PA1in   BIT_ADDR(GPIOA_IDR_Addr, 1)    
#define PA2in   BIT_ADDR(GPIOA_IDR_Addr, 2)    
#define PA3in   BIT_ADDR(GPIOA_IDR_Addr, 3)    
#define PA4in   BIT_ADDR(GPIOA_IDR_Addr, 4)    
#define PA5in   BIT_ADDR(GPIOA_IDR_Addr, 5)    
#define PA6in   BIT_ADDR(GPIOA_IDR_Addr, 6)    
#define PA7in   BIT_ADDR(GPIOA_IDR_Addr, 7)    
#define PA8in   BIT_ADDR(GPIOA_IDR_Addr, 8)    
#define PA9in   BIT_ADDR(GPIOA_IDR_Addr, 9)    
#define PA10in  BIT_ADDR(GPIOA_IDR_Addr, 10)   
#define PA11in  BIT_ADDR(GPIOA_IDR_Addr, 11)   
#define PA12in  BIT_ADDR(GPIOA_IDR_Addr, 12)   
#define PA13in  BIT_ADDR(GPIOA_IDR_Addr, 13)   
#define PA14in  BIT_ADDR(GPIOA_IDR_Addr, 14)   
#define PA15in  BIT_ADDR(GPIOA_IDR_Addr, 15)   

//----------------------------------------------------- 
#define PB0   BIT_ADDR(GPIOB_ODR_Addr, 0)    
#define PB1   BIT_ADDR(GPIOB_ODR_Addr, 1)    
#define PB2   BIT_ADDR(GPIOB_ODR_Addr, 2)    
#define PB3   BIT_ADDR(GPIOB_ODR_Addr, 3)    
#define PB4   BIT_ADDR(GPIOB_ODR_Addr, 4)    
#define PB5   BIT_ADDR(GPIOB_ODR_Addr, 5)    
#define PB6   BIT_ADDR(GPIOB_ODR_Addr, 6)    
#define PB7   BIT_ADDR(GPIOB_ODR_Addr, 7)    
#define PB8   BIT_ADDR(GPIOB_ODR_Addr, 8)    
#define PB9   BIT_ADDR(GPIOB_ODR_Addr, 9)    
#define PB10  BIT_ADDR(GPIOB_ODR_Addr, 10)   
#define PB11  BIT_ADDR(GPIOB_ODR_Addr, 11)   
#define PB12  BIT_ADDR(GPIOB_ODR_Addr, 12)   
#define PB13  BIT_ADDR(GPIOB_ODR_Addr, 13)   
#define PB14  BIT_ADDR(GPIOB_ODR_Addr, 14)   
#define PB15  BIT_ADDR(GPIOB_ODR_Addr, 15)   

#define PB0in   BIT_ADDR(GPIOB_IDR_Addr, 0)    
#define PB1in   BIT_ADDR(GPIOB_IDR_Addr, 1)    
#define PB2in   BIT_ADDR(GPIOB_IDR_Addr, 2)    
#define PB3in   BIT_ADDR(GPIOB_IDR_Addr, 3)    
#define PB4in   BIT_ADDR(GPIOB_IDR_Addr, 4)    
#define PB5in   BIT_ADDR(GPIOB_IDR_Addr, 5)    
#define PB6in   BIT_ADDR(GPIOB_IDR_Addr, 6)    
#define PB7in   BIT_ADDR(GPIOB_IDR_Addr, 7)    
#define PB8in   BIT_ADDR(GPIOB_IDR_Addr, 8)    
#define PB9in   BIT_ADDR(GPIOB_IDR_Addr, 9)    
#define PB10in  BIT_ADDR(GPIOB_IDR_Addr, 10)   
#define PB11in  BIT_ADDR(GPIOB_IDR_Addr, 11)   
#define PB12in  BIT_ADDR(GPIOB_IDR_Addr, 12)   
#define PB13in  BIT_ADDR(GPIOB_IDR_Addr, 13)   
#define PB14in  BIT_ADDR(GPIOB_IDR_Addr, 14)   
#define PB15in  BIT_ADDR(GPIOB_IDR_Addr, 15)   
//---------------------------------------------------- 
#define PC0   BIT_ADDR(GPIOC_ODR_Addr, 0)    
#define PC1   BIT_ADDR(GPIOC_ODR_Addr, 1)    
#define PC2   BIT_ADDR(GPIOC_ODR_Addr, 2)    
#define PC3   BIT_ADDR(GPIOC_ODR_Addr, 3)    
#define PC4   BIT_ADDR(GPIOC_ODR_Addr, 4)    
#define PC5   BIT_ADDR(GPIOC_ODR_Addr, 5)    
#define PC6   BIT_ADDR(GPIOC_ODR_Addr, 6)    
#define PC7   BIT_ADDR(GPIOC_ODR_Addr, 7)    
#define PC8   BIT_ADDR(GPIOC_ODR_Addr, 8)    
#define PC9   BIT_ADDR(GPIOC_ODR_Addr, 9)    
#define PC10  BIT_ADDR(GPIOC_ODR_Addr, 10)   
#define PC11  BIT_ADDR(GPIOC_ODR_Addr, 11)   
#define PC12  BIT_ADDR(GPIOC_ODR_Addr, 12)   
#define PC13  BIT_ADDR(GPIOC_ODR_Addr, 13)   
#define PC14  BIT_ADDR(GPIOC_ODR_Addr, 14)   
#define PC15  BIT_ADDR(GPIOC_ODR_Addr, 15)   

#define PC0in   BIT_ADDR(GPIOC_IDR_Addr, 0)    
#define PC1in   BIT_ADDR(GPIOC_IDR_Addr, 1)    
#define PC2in   BIT_ADDR(GPIOC_IDR_Addr, 2)    
#define PC3in   BIT_ADDR(GPIOC_IDR_Addr, 3)    
#define PC4in   BIT_ADDR(GPIOC_IDR_Addr, 4)    
#define PC5in   BIT_ADDR(GPIOC_IDR_Addr, 5)    
#define PC6in   BIT_ADDR(GPIOC_IDR_Addr, 6)    
#define PC7in   BIT_ADDR(GPIOC_IDR_Addr, 7)    
#define PC8in   BIT_ADDR(GPIOC_IDR_Addr, 8)    
#define PC9in   BIT_ADDR(GPIOC_IDR_Addr, 9)    
#define PC10in  BIT_ADDR(GPIOC_IDR_Addr, 10)   
#define PC11in  BIT_ADDR(GPIOC_IDR_Addr, 11)   
#define PC12in  BIT_ADDR(GPIOC_IDR_Addr, 12)   
#define PC13in  BIT_ADDR(GPIOC_IDR_Addr, 13)   
#define PC14in  BIT_ADDR(GPIOC_IDR_Addr, 14)   
#define PC15in  BIT_ADDR(GPIOC_IDR_Addr, 15)   

//---------------------------------------------------- 
#define PD0   BIT_ADDR(GPIOD_ODR_Addr, 0)    
#define PD1   BIT_ADDR(GPIOD_ODR_Addr, 1)    
#define PD2   BIT_ADDR(GPIOD_ODR_Addr, 2)    
#define PD3   BIT_ADDR(GPIOD_ODR_Addr, 3)    
#define PD4   BIT_ADDR(GPIOD_ODR_Addr, 4)    
#define PD5   BIT_ADDR(GPIOD_ODR_Addr, 5)    
#define PD6   BIT_ADDR(GPIOD_ODR_Addr, 6)    
#define PD7   BIT_ADDR(GPIOD_ODR_Addr, 7)    
#define PD8   BIT_ADDR(GPIOD_ODR_Addr, 8)    
#define PD9   BIT_ADDR(GPIOD_ODR_Addr, 9)    
#define PD10  BIT_ADDR(GPIOD_ODR_Addr, 10)   
#define PD11  BIT_ADDR(GPIOD_ODR_Addr, 11)   
#define PD12  BIT_ADDR(GPIOD_ODR_Addr, 12)   
#define PD13  BIT_ADDR(GPIOD_ODR_Addr, 13)   
#define PD14  BIT_ADDR(GPIOD_ODR_Addr, 14)   
#define PD15  BIT_ADDR(GPIOD_ODR_Addr, 15)   

#define PD0in   BIT_ADDR(GPIOD_IDR_Addr, 0)    
#define PD1in   BIT_ADDR(GPIOD_IDR_Addr, 1)    
#define PD2in   BIT_ADDR(GPIOD_IDR_Addr, 2)    
#define PD3in   BIT_ADDR(GPIOD_IDR_Addr, 3)    
#define PD4in   BIT_ADDR(GPIOD_IDR_Addr, 4)    
#define PD5in   BIT_ADDR(GPIOD_IDR_Addr, 5)    
#define PD6in   BIT_ADDR(GPIOD_IDR_Addr, 6)    
#define PD7in   BIT_ADDR(GPIOD_IDR_Addr, 7)    
#define PD8in   BIT_ADDR(GPIOD_IDR_Addr, 8)    
#define PD9in   BIT_ADDR(GPIOD_IDR_Addr, 9)    
#define PD10in  BIT_ADDR(GPIOD_IDR_Addr, 10)   
#define PD11in  BIT_ADDR(GPIOD_IDR_Addr, 11)   
#define PD12in  BIT_ADDR(GPIOD_IDR_Addr, 12)   
#define PD13in  BIT_ADDR(GPIOD_IDR_Addr, 13)   
#define PD14in  BIT_ADDR(GPIOD_IDR_Addr, 14)   
#define PD15in  BIT_ADDR(GPIOD_IDR_Addr, 15)   

//---------------------------------------------------- 
#define PE0   BIT_ADDR(GPIOE_ODR_Addr, 0)    
#define PE1   BIT_ADDR(GPIOE_ODR_Addr, 1)    
#define PE2   BIT_ADDR(GPIOE_ODR_Addr, 2)    
#define PE3   BIT_ADDR(GPIOE_ODR_Addr, 3)    
#define PE4   BIT_ADDR(GPIOE_ODR_Addr, 4)    
#define PE5   BIT_ADDR(GPIOE_ODR_Addr, 5)    
#define PE6   BIT_ADDR(GPIOE_ODR_Addr, 6)    
#define PE7   BIT_ADDR(GPIOE_ODR_Addr, 7)    
#define PE8   BIT_ADDR(GPIOE_ODR_Addr, 8)    
#define PE9   BIT_ADDR(GPIOE_ODR_Addr, 9)    
#define PE10  BIT_ADDR(GPIOE_ODR_Addr, 10)   
#define PE11  BIT_ADDR(GPIOE_ODR_Addr, 11)   
#define PE12  BIT_ADDR(GPIOE_ODR_Addr, 12)   
#define PE13  BIT_ADDR(GPIOE_ODR_Addr, 13)   
#define PE14  BIT_ADDR(GPIOE_ODR_Addr, 14)   
#define PE15  BIT_ADDR(GPIOE_ODR_Addr, 15)   

#define PE0in   BIT_ADDR(GPIOE_IDR_Addr, 0)    
#define PE1in   BIT_ADDR(GPIOE_IDR_Addr, 1)    
#define PE2in   BIT_ADDR(GPIOE_IDR_Addr, 2)    
#define PE3in   BIT_ADDR(GPIOE_IDR_Addr, 3)    
#define PE4in   BIT_ADDR(GPIOE_IDR_Addr, 4)    
#define PE5in   BIT_ADDR(GPIOE_IDR_Addr, 5)    
#define PE6in   BIT_ADDR(GPIOE_IDR_Addr, 6)    
#define PE7in   BIT_ADDR(GPIOE_IDR_Addr, 7)    
#define PE8in   BIT_ADDR(GPIOE_IDR_Addr, 8)    
#define PE9in   BIT_ADDR(GPIOE_IDR_Addr, 9)    
#define PE10in  BIT_ADDR(GPIOE_IDR_Addr, 10)   
#define PE11in  BIT_ADDR(GPIOE_IDR_Addr, 11)   
#define PE12in  BIT_ADDR(GPIOE_IDR_Addr, 12)   
#define PE13in  BIT_ADDR(GPIOE_IDR_Addr, 13)   
#define PE14in  BIT_ADDR(GPIOE_IDR_Addr, 14)   
#define PE15in  BIT_ADDR(GPIOE_IDR_Addr, 15)

#define	 SDA_A1     HAL_GPIO_WritePin(GPIOE,GPIO_PIN_9,GPIO_PIN_SET)//PB11=1   //SDA输出
#define	 SDA_A0     HAL_GPIO_WritePin(GPIOE,GPIO_PIN_9,GPIO_PIN_RESET)//PB11=0
#define	 SDA_AI     HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_9)//PB11=0
#define	 SCL_A1	    HAL_GPIO_WritePin(GPIOE,GPIO_PIN_8,GPIO_PIN_SET)//PB10=1    //SCL
#define	 SCL_A0	    HAL_GPIO_WritePin(GPIOE,GPIO_PIN_8,GPIO_PIN_RESET)//PB10=0
#define	 SDA_AIN	    (GPIOE->MODER &=~(3<<(9*2)))//PB11in   //SDA读入
#define	 SDA_AOUT	    (GPIOE->MODER |= 1<<(9*2))//PB11in   //SDA输出
//#define	 SDA_A1     PE9=1//PB11=1   //SDA输出
//#define	 SDA_A0     PE9=0//PB11=0
//#define	 SCL_A1	    PE8=1//PB10=1    //SCL
//#define	 SCL_A0	    PE8=0//PB10=0
//#define	 SDA_AI	    PE9in//PB11in   //SDA读入


#define	 SDA_B1     PB7=1   //SDA输出
#define	 SDA_B0     PB7=0
#define	 SCL_B1	    PB6=1    //SCL
#define	 SCL_B0	    PB6=0
#define	 SDA_BI	    PB7in   //SDA读入

//I2C地址以及读写设置
#define  WR_REG 0x90
#define  RE_REG 0x91

/***********************************寄存器控制字**********************************************/
#define  DATA_REG  0x00		//转换数据寄存器
#define  CONF_REG  0x01    	//控制字设置寄存器
#define  LOTH_REG  0x02		//最低阀值寄存器
#define  HITH_REG  0x03		//最高阀值寄存器

/***********************控制字申明*************************************************************
*|  OS | MUX2 | MUX1 | MUX0 | PGA2 | PGA1 | PGA0 | MODE  |------HCMD
*|  DR2| DR1  | DR0  | COMP_MODE | COMP_POL | COMP_LAT |  COMP_QUE1 | COMP_QUE0 |-----LCMD
***********************************************************************************************/
#define  HCMD1    0x64   // 入 +-4.096量程  连续模式  01000100b
#define  LCMD1	  0xf0	 //860sps 窗口比较器模式 输出低有效  不锁存信号至读 每周期检测阀值 11110000b

/************************函数申明****************************/
void I2C_Configuration(void);
void ADS1115_Init(void);
void ADS1115Config_A(u8 LCMD,u8 HCMD);
void SetThresHold_A(u16 L_TH,u16 H_TH);
void ADS_1115PointRegister_A(void);

u16 ReadAD_A(void);

//void ADS1115Config_B(u8 LCMD,u8 HCMD);
//void SetThresHold_B(u16 L_TH,u16 H_TH);
//u16 ReadAD_B(void);

static void ADS1115_delay(u16 D);
void delay_nms(u16 ms);
void delay_nus(u16 us);
u16 getad_A(void);



#endif

