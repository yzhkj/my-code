
#include "UserData.h"

//////////////////////////////////////////////////////////////////////////////
/// 用途: 这是控制板采集POW(变距浆产生力)的方法集
/// 资源: TTL串口
///       引脚:         中断号:
/// 方法: 串口初始化 串口中断数据接收 数据解析及处理
///
//////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///PWM5 输入配置
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TIM_ICInitTypeDef  PWM5_ICInitStructure;
void PWM5_CH1_Cap_Init(u32 arr,u16 psc) {
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;


    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM11,ENABLE);  		//TIM5时钟使能
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 		//使能PORTA时钟

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; 					//GPIOB14
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;				//复用功能
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;			//速度100MHz
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;				//推挽复用输出
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; 				//下拉
    GPIO_Init(GPIOB,&GPIO_InitStructure); 						//初始化PB14

    GPIO_PinAFConfig(GPIOB,GPIO_PinSource9,GPIO_AF_TIM11); 		//PB14复用位定时器4


    TIM_TimeBaseStructure.TIM_Prescaler=psc;  					//定时器分频
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 	//向上计数模式
    TIM_TimeBaseStructure.TIM_Period=arr;   					//自动重装载值
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;

    TIM_TimeBaseInit(TIM11,&TIM_TimeBaseStructure);


    //初始化TIM5输入捕获参数
    PWM5_ICInitStructure.TIM_Channel = TIM_Channel_1; 					//CC1S=01 	选择输入端 IC1映射到TI1上
    PWM5_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;		//上升沿捕获
    PWM5_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; 	//映射到TI1上
    PWM5_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 			//配置输入分频,不分频
    PWM5_ICInitStructure.TIM_ICFilter = 0x00;							//IC1F=0000 配置输入滤波器 不滤波
    TIM_ICInit(TIM11, &PWM5_ICInitStructure);
    TIM_ITConfig(TIM11,TIM_IT_Update|TIM_IT_CC1,ENABLE);					//允许更新中断 ,允许CC1IE捕获中断

    TIM_Cmd(TIM11,ENABLE ); 					//使能定时器5


    NVIC_InitStructure.NVIC_IRQChannel = TIM1_TRG_COM_TIM11_IRQn ;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;			//抢占优先级3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;				//子优先级2
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					//IRQ通道使能
    NVIC_Init(&NVIC_InitStructure);									//根据指定的参数初始化VIC寄存器、
}
//捕获状态
//[7]:0,没有成功的捕获;1,成功捕获到一次.
//[6]:0,还没捕获到低电平;1,已经捕获到低电平了.
//[5:0]:捕获低电平后溢出的次数(对于32位定时器来说,1us计数器加1,溢出时间:4294秒)
u8  PWM5CH1_CAPTURE_STA=0;	//输入捕获状态
u32	PWM5CH1_CAPTURE_VAL;	//输入捕获值(TIM4/TIM5是32位)
u32	PWM5CH1_CAPTURE_VAL_CYC;	//输入捕获值(TIM4/TIM5是32位)
void TIM1_TRG_COM_TIM11_IRQHandler(void) {
    if((PWM5CH1_CAPTURE_STA&0X80)==0)//还未成功捕获
    {
        if(TIM_GetITStatus(TIM11, TIM_IT_Update) != RESET)//溢出
        {
            if(PWM5CH1_CAPTURE_STA&0X40)//已经捕获到高电平了
            {
                if((PWM5CH1_CAPTURE_STA&0X3F)==0X3F)//高电平太长了
                {
                    PWM5CH1_CAPTURE_STA|=0X80;		//标记成功捕获了一次
                    PWM5CH1_CAPTURE_VAL=0XFFFFFFFF;
                }
                else
                    PWM5CH1_CAPTURE_STA++;
            }
        }
        if(TIM_GetITStatus(TIM11, TIM_IT_CC1) != RESET)//捕获1发生捕获事件
        {

            if(PWM5CH1_CAPTURE_STA&0X40)		//捕获到一个下降沿
            {
                PWM5CH1_CAPTURE_STA|=0X80;		//标记成功捕获到一次高电平脉宽
                PWM5CH1_CAPTURE_VAL=TIM_GetCapture1(TIM11);//获取当前的捕获值.

                PWM5CH1_CAPTURE_VAL_CYC=TIM_GetCapture2(TIM11);

                TIM_OC1PolarityConfig(TIM11,TIM_ICPolarity_Rising); //CC1P=0 设置为上升沿捕获//TIM_ICPolarity_Falling
            }

            else  								//还未开始,第一次捕获上升沿
            {
                PWM5CH1_CAPTURE_STA=0;			//清空
                PWM5CH1_CAPTURE_VAL=0;
                PWM5CH1_CAPTURE_STA|=0X40;		//标记捕获到了上升沿
                TIM_Cmd(TIM11,DISABLE); 		//关闭定时器5
                TIM_SetCounter(TIM11,0);
                TIM_OC1PolarityConfig(TIM11,TIM_ICPolarity_Falling);		//CC1P=1 设置为下降沿捕获//TIM_ICPolarity_Rising
                TIM_Cmd(TIM11,ENABLE ); 			//使能定时器5
            }
        }
    }
    TIM_ClearITPendingBit(TIM11, TIM_IT_CC1|TIM_IT_Update); //清除中断标志位
}









#if EN_USART6_RX   //如果使能了接收
//串口1中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误
u8 USART6_RX_BUF[USART6_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 USART6_RX_STA=0;       //接收状态标记
u16 USART6_flagA=0;       //接收状态标记

//初始化IO 串口6
//bound:波特率
void uart6_init(u32 bound)
{
    //GPIO端口设置
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE); //使能GPIOA时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6,ENABLE);//使能USART1时钟

    //串口1对应引脚复用映射
    GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_USART6); //GPIOA9复用为USART1
    GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_USART6); //GPIOA10复用为USART1

    //USART1端口配置
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7; //GPIOA9与GPIOA10
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
    GPIO_Init(GPIOC,&GPIO_InitStructure); //初始化PA9，PA10

    //USART1 初始化设置
    USART_InitStructure.USART_BaudRate = bound;//波特率设置
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
    USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
    USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
    USART_Init(USART6, &USART_InitStructure); //初始化串口1

    USART_Cmd(USART6, ENABLE);  //使能串口1

    //USART_ClearFlag(USART1, USART_FLAG_TC);

#if EN_USART6_RX
    USART_ITConfig(USART6, USART_IT_RXNE, ENABLE);//开启相关中断

    //Usart1 NVIC 配置
    NVIC_InitStructure.NVIC_IRQChannel = USART6_IRQn;//串口1中断通道
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//抢占优先级3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;		//子优先级3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
    NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器、

#endif

}



void USART6_IRQHandler(void)                	//串口1中断服务程序
{
    u8 Res;

    if(USART_GetITStatus(USART6, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
    {
        Res =USART_ReceiveData(USART6);//(USART1->DR);	//读取接收到的数据

        if((USART6_RX_STA&0x8000)==0)//接收未完成
        {
            if((USART6_RX_STA==0||USART6_RX_STA==1||USART6_RX_STA==2)&&Res!=0xBB) {
                USART6_RX_STA=0;//接收错误
                return;
            }
            if(USART6_RX_STA==4&&Res!=0xA1) {
                USART6_RX_STA=0;//接收错误
                return;
            }
            USART6_RX_BUF[USART6_RX_STA&0X3FFF]=Res ;
            if(USART6_RX_STA>=11) {
                USART6_RX_STA|=0x8000;	//接收完成了
                return;
            }
            USART6_RX_STA++;

        }
    }
}
#endif

///////////////////////////////////////////////////////////////////////////
///


void Pow_init(void) {
    //初始化PWM口
    PWM5_CH1_Cap_Init(10152-1,84-1);
    //初始化串口
    uart6_init(9600);
}

