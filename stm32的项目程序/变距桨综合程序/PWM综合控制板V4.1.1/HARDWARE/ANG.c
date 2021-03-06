#include "UserData.h"


//////////////////////////////////////////////////////////////////////////////
/// 用途: 这是控制板采集ANG(变距浆角度)的方法集
/// 资源: TIM?
///       引脚:         中断时钟:
/// 方法: PWM捕获初始化   捕获中断数据解析及处理
///
//////////////////////////////////////////////////////////////////////////////

void PWM2_CH1_Cap_Init(u32 arr,u16 psc);


///初始化
void ANG_Int(u32 arr,u16 psc) {
    PWM2_CH1_Cap_Init(arr,psc);
}





/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///PWM2捕获配置  使用定时器4 作为PWM2 的定时器
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TIM_ICInitTypeDef  PWM2_ICInitStructure;

//定时器4通道1输入捕获配置
//arr：自动重装值(TIM2,TIM5是32位的!!)
//psc：时钟预分频数
void PWM2_CH1_Cap_Init(u32 arr,u16 psc)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;


    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);  		//TIM1时钟使能
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE); 		//使能PORTE时钟

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; 					//GPIOE9
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;				//复用功能
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;			//速度100MHz
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;				//推挽复用输出
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; 				//  下拉
    GPIO_Init(GPIOE,&GPIO_InitStructure); 						//初始化PE9

    GPIO_PinAFConfig(GPIOE,GPIO_PinSource9,GPIO_AF_TIM1); 		//PE9复用位定时器1

    TIM_DeInit(TIM1); //重设成默认值
    TIM_TimeBaseStructure.TIM_Prescaler=psc;  					//定时器分频
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 	//向上计数模式
    TIM_TimeBaseStructure.TIM_Period=arr;   					//自动重装载值
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;//时钟分割值

    TIM_TimeBaseStructure.TIM_RepetitionCounter=0; //网上新加的部分
    TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure);//初始化时钟TIM1


    //初始化PWM2输入捕获参数
    PWM2_ICInitStructure.TIM_Channel = TIM_Channel_1; 					//CC1S=01 	选择输入端 IC1映射到TI1上
    PWM2_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;		//上升沿捕获
    PWM2_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; 	//映射到TI1上
    PWM2_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 			//配置输入分频,不分频
    PWM2_ICInitStructure.TIM_ICFilter = 0x00;							//IC1F=0000 配置输入滤波器 不滤波

//    TIM_PWMIConfig(TIM1, &PWM2_ICInitStructure);
//    TIM_SelectInputTrigger(TIM1, TIM_TS_TI1FP1); //选择ic1为始终触发源
//    TIM_SelectSlaveMode(TIM1, TIM_SlaveMode_Reset);//TIM 从模式 触发信号的上升沿重新初始化计数器和触发寄存器的更新事件
//    TIM_SelectMasterSlaveMode(TIM1, TIM_MasterSlaveMode_Enable); //启动定时器被动触发
    TIM_ICInit(TIM1, &PWM2_ICInitStructure);

    TIM_ITConfig(TIM1
                 ,TIM_IT_Update
                 |TIM_IT_CC1
                 ,ENABLE);					//允许更新中断 ,允许CC1IE捕获中断

    // TIM_ClearFlag(TIM1, TIM_IT_Update|TIM_IT_CC1);// 清除中断标志位


    NVIC_InitStructure.NVIC_IRQChannel = TIM1_CC_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;			//抢占优先级4
    NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;				//子优先级1
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					//IRQ通道使能
    NVIC_Init(&NVIC_InitStructure);									//根据指定的参数初始化VIC寄存器�
    TIM_Cmd(TIM1,ENABLE ); 					//使能定时器1
}


//捕获状态
//[7]:0,没有成功的捕获;1,成功捕获到一次.
//[6]:0,还没捕获到低电平;1,已经捕获到低电平了.
//[5:0]:捕获低电平后溢出的次数(对于32位定时器来说,1us计数器加1,溢出时间:4294秒)
u8  PWM2CH1_CAPTURE_STA=0;	//输入捕获状态
u32	PWM2CH1_CAPTURE_VAL;	//输入捕获值(PWM2/TIM5是32位)
u32	PWM2CH1_CAPTURE_VAL_CYC;	//输入捕获值(TIM4/TIM5是32位)

//PWM2  定时器1中断服务程序
void TIM1_CC_IRQHandler(void)
{

    if((PWM2CH1_CAPTURE_STA&0X80)==0)//还未成功捕获
    {
        if(TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)//溢出
        {
            if(PWM2CH1_CAPTURE_STA&0X40)//已经捕获到高电平了
            {
                if((PWM2CH1_CAPTURE_STA&0X3F)==0X3F)//高电平太长了
                {
                    PWM2CH1_CAPTURE_STA|=0X80;		//标记成功捕获了一次
                    PWM2CH1_CAPTURE_VAL=0XFFFFFFFF;
                }

                else
                    PWM2CH1_CAPTURE_STA++;
            }
        }
        if(TIM_GetITStatus(TIM1, TIM_IT_CC1) != RESET)//捕获2发生捕获事件
        {


            if(PWM2CH1_CAPTURE_STA&0X40)		//捕获到一个下降沿
            {
                PWM2CH1_CAPTURE_STA|=0X80;		//标记成功捕获到一次高电平脉宽
                PWM2CH1_CAPTURE_VAL=TIM_GetCapture1(TIM1);//获取当前的捕获值.

                PWM2CH1_CAPTURE_VAL_CYC=TIM_GetCapture2(TIM1);

                TIM_OC1PolarityConfig(TIM1,TIM_ICPolarity_Rising); //CC1P=0 设置为上升沿捕获
            }

            else  								//还未开始,第一次捕获上升沿
            {
                PWM2CH1_CAPTURE_STA=0;			//清空
                PWM2CH1_CAPTURE_VAL=0;
                PWM2CH1_CAPTURE_STA|=0X40;		//标记捕获到了上升沿
                TIM_Cmd(TIM1,DISABLE ); 		//关闭定时器1
                TIM_SetCounter(TIM1,0);
                TIM_OC1PolarityConfig(TIM1,TIM_ICPolarity_Falling);		//CC1P=1 设置为下降沿捕获
                TIM_Cmd(TIM1,ENABLE ); 			//使能定时器1
            }
        }
    }
    TIM_ClearITPendingBit(TIM1, TIM_IT_CC1|TIM_IT_Update); //清除中断标志位
}
