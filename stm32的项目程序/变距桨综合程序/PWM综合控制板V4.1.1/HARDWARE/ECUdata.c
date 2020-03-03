

//////////////////////////////////////////////////////////////////////////////
/// 用途: 这是控制板与ECU通讯的方法集
/// 资源: 232串口
///       引脚:         串口号:
/// 方法: 串口初始化 串口中断数据接收 数据解析及处理
///
//////////////////////////////////////////////////////////////////////////////

#include "UserData.h"
#include "delay.h"

#if EN_USART3_RX   //如果使能了接收
//串口1中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误
u8 USART3_RX_BUF[USART3_REC_LEN];   //接收缓冲,最大USART_REC_LEN个字节.
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 USART3_RX_STA=0;       //接收状态标记
u16 USART3_flagA=0;       //接收状态标记

//初始化IO 串口3
//bound:波特率
void uart3_init(u32 bound)
{
    //GPIO端口设置
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE); //使能GPIOC时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);//使能USART3时钟

    //串口3对应引脚复用映射
    GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_USART3); //GPIOC10复用为USART3
    GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_USART3); //GPIOC11复用为USART3

    //USART1端口配置
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11; //GPIOC10与GPIOAC11
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
    GPIO_Init(GPIOB,&GPIO_InitStructure); //初始化PC10，PC11

    //USART1 初始化设置
    USART_InitStructure.USART_BaudRate = bound;//波特率设置
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
    USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
    USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
    USART_Init(USART3, &USART_InitStructure); //初始化串口3

    USART_Cmd(USART3, ENABLE);  //使能串口3

    //USART_ClearFlag(USART1, USART_FLAG_TC);

#if EN_USART3_RX
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//开启相关中断

    //Usart1 NVIC 配置
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;//串口3中断通道
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//抢占优先级3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;		//子优先级3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
    NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器、

#endif

}



void USART3_IRQHandler(void)                	//串口1中断服务程序
{
    u8 Res;

    if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
    {
        Res =USART_ReceiveData(USART3);//(USART1->DR);	//读取接收到的数据

        if((USART3_RX_STA&0x8000)==0)//接收未完成
        {
            if(USART3_RX_STA==0&&Res!=0x80) {
                USART3_RX_STA=0;//接收错误
                return;
            }
            if(USART3_RX_STA==1&&Res!=0x8f) {
                USART3_RX_STA=0;//接收错误
                return;
            }
            if(USART3_RX_STA==2&&Res!=0xea) {
                USART3_RX_STA=0;//接收错误
                return;
            }
            if(USART3_RX_STA==3&&Res!=0x16) {
                USART3_RX_STA=0;//接收错误
                return;
            }
            if(USART3_RX_STA==4&&Res!=0x50) {
                USART3_RX_STA=0;//接收错误
                return;
            }
            if(USART3_RX_STA==5&&Res!=0x04) {
                USART3_RX_STA=0;//接收错误
                return;
            }
            USART3_RX_BUF[USART3_RX_STA&0X3FFF]=Res ;
            if(USART3_RX_STA>=25) {
                USART3_RX_STA|=0x8000;	//接收完成了
                return;
            }
            USART3_RX_STA++;
        }
    }
#if SYSTEM_SUPPORT_OS 	//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
    OSIntExit();
#endif
}
#endif

void ECU_init(void ) {
    uart2_init(115200);
    uart3_init(115200);
    delay_ms(500);
    u8 data1[]= {0x80,0x8F,0xEA,0x03,0x20,0x02,0x07,0x25,0x80,0x8F,0xEA,0x01,0x9B,0x95,0x80,0x8F,0xEA,0x01,0xA1,0x9B };
    u8 data2[]= {0x80,0x8F,0xEA,0x03,0x20,0x02,0x07,0x25,0x80,0x8F,0xEA,0x22,0x10,0x82,0x04,0x01,0x02,0x2C,0xF4,0x02,0x2C,0xD2,0x02,0x2F,0x2C,0x01,0x2D,0xA6,0x01,0x2D,0xAC,0x02,0x30,0x41,0x01,0x2C,0xF6,0x02,0x2C,0x8A,0x02,0x2C,0x8C,0x02,0x2C,0xB3,0xC8,0x80
                 ,0x8F,0xEA,0x2E,0x10,0x82,0x01,0x01,0x01,0x2E,0x19,0x02,0x2E,0x55,0x01,0x28,0x6E,0x02,0x28,0x8F,0x02,0x2F,0x0C,0x02,0x2C,0x41,0x02,0x28,0x7D,0x02,0x28,0x65,0x02,0x2F,0x2C,0x02,0x2C,0xF4,0x02,0x2C,0xD0,0x02,0x2C,0x4D,0x01,0x2D,0xAC,0x02,0x30,0x41,0xFF
                };
    for(u8 i=0; i<sizeof(data1); i++) {
        USART_SendData(USART3,data1[i]);
        while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);//等待发送结束
    }
    delay_ms(500);
    for(u8 i=0; i<sizeof(data2); i++) {
        USART_SendData(USART3,data2[i]);
        while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);//等待发送结束
    }

}



#if EN_USART2_RX   //如果使能了接收
//串口2中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误
u8 USART2_RX_BUF[USART2_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 USART2_RX_STA=0;       //接收状态标记

//初始化IO 串口2
//bound:波特率
void uart2_init(u32 bound) {
    //GPIO端口设置
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //使能GPIOA时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);//使能USART2时钟

    //串口2对应引脚复用映射
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2); //GPIOA2复用为USART2
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2); //GPIOA3复用为USART2

    //USART1端口配置
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3; //GPIOA2与GPIOA3
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
    GPIO_Init(GPIOA,&GPIO_InitStructure); //初始化PA2，PA3

    //USART2 初始化设置
    USART_InitStructure.USART_BaudRate = bound;//波特率设置
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
    USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
    USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
    USART_Init(USART2, &USART_InitStructure); //初始化串口2

    USART_Cmd(USART2, ENABLE);  //使能串口2

    //USART_ClearFlag(USART1, USART_FLAG_TC);

#if EN_USART2_RX
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启相关中断

    //Usart1 NVIC 配置
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;//串口2中断通道
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//抢占优先级3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//子优先级3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
    NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器、

#endif

}


void USART2_IRQHandler(void)                	//串口1中断服务程序
{
    u8 Res;

    if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
    {
        Res =USART_ReceiveData(USART2);//(USART1->DR);	//读取接收到的数据

        if((USART2_RX_STA&0x8000)==0)//接收未完成
        {
            if(USART2_RX_STA&0x4000)//接收到了0x0d
            {
                if(Res!=0x0a)USART2_RX_STA=0;//接收错误,重新开始
                else USART2_RX_STA|=0x8000;	//接收完成了
            }
            else //还没收到0X0D
            {
                if(Res==0x0d)USART2_RX_STA|=0x4000;
                else
                {
                    USART2_RX_BUF[USART2_RX_STA&0X3FFF]=Res ;
                    USART2_RX_STA++;
                    if(USART2_RX_STA>(USART2_REC_LEN-1))USART2_RX_STA=0;//接收数据错误,重新开始接收
                }
            }

            //数据验证
            if((USART2_RX_STA==0||USART2_RX_STA==1)&&Res!=0x4f) {//起始位不为0x4f
                USART2_RX_STA=0;//接收数据错误,重新开始接收
            }
        }
    }
}
#endif



//////////////////////////////////////////////////////////////////////////////////
