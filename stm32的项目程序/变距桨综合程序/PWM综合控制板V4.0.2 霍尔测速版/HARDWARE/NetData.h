

#include "sys.h"
#include "stdio.h"
#include "stm32f4xx_conf.h"

////////////////////////////////////////////////////////////
//传输数据的结构体
//////////////////////////////////////////////////////////
typedef struct SendData {
    //控制变量
    double KPow;
    double KTps;
    double KAng;
    double KRpm;
    //采集变量
    double Pow;
    double Ang;
    double Tps;
     double Rpm;
    int Error;
} SendData;
////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//串口1 wifi 初始化
#define USART1_REC_LEN  			200  	//定义最大接收字节数 200
#define EN_USART1_RX 			1		//使能（1）/禁止（0）串口1接收

extern u8  USART1_RX_BUF[USART1_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符
extern u16 USART1_RX_STA;         		//接收状态标记
//如果想串口中断接收，请不要注释以下宏定义
void uart1_init(u32 bound);

void Net_Init(void);
/////////////////////////////////////////////////////////////////

