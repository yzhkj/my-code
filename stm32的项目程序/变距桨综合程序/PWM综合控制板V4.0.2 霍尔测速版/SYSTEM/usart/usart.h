//#ifndef __USART_H
//#define __USART_H
//#include "stdio.h"
//#include "stm32f4xx_conf.h"
//#include "sys.h"
////////////////////////////////////////////////////////////////////////////////////


////串口1
//#define USART1_REC_LEN  			200  	//定义最大接收字节数 200
//#define EN_USART1_RX 			1		//使能（1）/禁止（0）串口1接收

//extern u8  USART1_RX_BUF[USART1_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符
//extern u16 USART1_RX_STA;         		//接收状态标记
////如果想串口中断接收，请不要注释以下宏定义
////void uart1_init(u32 bound);

////////////////////////////////////////////////////////////////////////////////////
///////数据处理方法
////////////////////////////////////////////////////////////////////////////////////


////发送数据信息给串口
////void SendDatatoUSART(u8 data[]);

////发送位信息 串口2
//void SendSitetoUSART2(u32 s);
////发送位信息 串口3
//void SendSitetoUSART3(u32 s);
////发送位信息 串口4
//void SendSitetoUSART4(u32 s);


///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////






////串口2
//#define USART2_REC_LEN  			200  	//定义最大接收字节数 200
//#define EN_USART2_RX 			1		//使能（1）/禁止（0）串口1接收

//extern u8  USART2_RX_BUF[USART2_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符
//extern u16 USART2_RX_STA;         		//接收状态标记
////如果想串口中断接收，请不要注释以下宏定义
//void uart2_init(u32 bound);




////串口3
//#define USART3_REC_LEN  			200  	//定义最大接收字节数 200
//#define EN_USART3_RX 			1		//使能（1）/禁止（0）串口1接收

//extern u8  USART3_RX_BUF[USART3_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符
//extern u16 USART3_RX_STA;         		//接收状态标记
////如果想串口中断接收，请不要注释以下宏定义
//void uart3_init(u32 bound);


////串口4
//#define UART4_REC_LEN  			200  	//定义最大接收字节数 200
//#define EN_UART4_RX 			1		//使能（1）/禁止（0）串口1接收

//extern u8  UART4_RX_BUF[UART4_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符
//extern u16 UART4_RX_STA;         		//接收状态标记
////如果想串口中断接收，请不要注释以下宏定义
//void uart4_init(u32 bound);

////串口5
//#define UART5_REC_LEN  			200  	//定义最大接收字节数 200
//#define EN_UART5_RX 			1		//使能（1）/禁止（0）串口1接收

//extern u8  UART5_RX_BUF[UART5_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符
//extern u16 UART5_RX_STA;         		//接收状态标记
////如果想串口中断接收，请不要注释以下宏定义
//void uart5_init(u32 bound);


////串口6
//#define USART6_REC_LEN  			200  	//定义最大接收字节数 200
//#define EN_USART6_RX 			1		//使能（1）/禁止（0）串口1接收

//extern u8  USART6_RX_BUF[USART6_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符
//extern u16 USART6_RX_STA;         		//接收状态标记
////如果想串口中断接收，请不要注释以下宏定义
//void uart6_init(u32 bound);


//#endif


