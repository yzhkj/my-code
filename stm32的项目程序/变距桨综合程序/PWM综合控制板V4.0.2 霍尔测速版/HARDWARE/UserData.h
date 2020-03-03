
#ifndef __UserData_H
#define __UserData_H
#include "sys.h"
#include "stdio.h"
#include "stm32f4xx_conf.h"


///////////////////////////////////////////////////////////////
//串口2 与发动机通讯接口
#define USART3_REC_LEN  			200  	//定义最大接收字节数 200
#define EN_USART3_RX 			1		//使能（1）/禁止（0）串口1接收

extern u8  USART3_RX_BUF[USART3_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符
extern u16 USART3_RX_STA;         		//接收状态标记
//如果想串口中断接收，请不要注释以下宏定义
void uart3_init(u32 bound);

void ANG_Int(u32 arr,u16 psc);


/////////////////////////////////////////////////////////////
//PWM5 遥控器值输入口   //串口4 力值数据接收口

#define USART6_REC_LEN  			200  	//定义最大接收字节数 200
#define EN_USART6_RX 			1		//使能（1）/禁止（0）串口1接收

extern u8  USART6_RX_BUF[USART6_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符
extern u16 USART6_RX_STA;         		//接收状态标记
//如果想串口中断接收，请不要注释以下宏定义
void uart6_init(u32 bound);
void PWM5_CH1_Cap_Init(u32 arr,u16 psc);
void Pow_init(void);
/////////////////////////////////////////////////////////////
//控制板输出
void KTPSANG_init(void);


/////////////////////////////////////////////////////
/////ECU
void ECU_init(void);


////////////////////////////////////////
#endif
