
#include "UserData.h"




//////////////////////////////////////////////////////////////////////////////
/// 用途: 这是控制板控制ANG(变距浆角度)TPS(发动机节气门)的方法集
/// 资源: TIM?
///       引脚:         中断时钟:
/// 方法: PWM捕获初始化   捕获中断数据解析及处理
///
//////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///PWM1 输出配置
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
void PWM1_CH1_Out_Init(u32 arr,u32 psc)
{
    //此部分需手动修改IO口设置
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  		//TIM3时钟使能
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 		//使能PORTA时钟

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; 					//GPIOA6
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;				//复用功能
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;			//速度100MHz
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;				//推挽复用输出
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; 				//下拉
    GPIO_Init(GPIOA,&GPIO_InitStructure); 						//初始化PA6

    GPIO_PinAFConfig(GPIOA,GPIO_PinSource6,GPIO_AF_TIM3); 		//PA6复用位定时器3


    TIM_TimeBaseStructure.TIM_Prescaler=psc;  					//定时器分频
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 	//向上计数模式
    TIM_TimeBaseStructure.TIM_Period=arr;   					//自动重装载值
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;

    TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);//初始化定时器


    //初始化TIM12 Channel1 PWM模式
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性低
    TIM_OC1Init(TIM3, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM1 4OC1
    TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM12在CCR1上的预装载寄存器
    TIM_ARRPreloadConfig(TIM3,ENABLE);//ARPE使能

    TIM_Cmd(TIM3, ENABLE);  //使能TIM2
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///PWM3 输出配置
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
void PWM3_CH1_Out_Init(u32 arr,u32 psc)
{
    //此部分需手动修改IO口设置
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);  		//TIM5时钟使能
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 		//使能PORTA时钟

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; 					//GPIOA5
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;				//复用功能
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;			//速度100MHz
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;				//推挽复用输出
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; 				//下拉
    GPIO_Init(GPIOA,&GPIO_InitStructure); 						//初始化pa5

    GPIO_PinAFConfig(GPIOA,GPIO_PinSource5,GPIO_AF_TIM2); 		//Pa5复用位定时器2


    TIM_TimeBaseStructure.TIM_Prescaler=psc;  					//定时器分频
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 	//向上计数模式
    TIM_TimeBaseStructure.TIM_Period=arr;   					//自动重装载值
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
    TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);//初始化定时器2

    //初始化TIM12 Channel1 PWM模式
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性低
    TIM_OC1Init(TIM2, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM1 4OC1

    TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);  //使能TIM12在CCR1上的预装载寄存器

    TIM_ARRPreloadConfig(TIM2,ENABLE);//ARPE使能

    TIM_Cmd(TIM2, ENABLE);  //使能TIM2
}

void KTPSANG_init(void) {
    PWM3_CH1_Out_Init(15015-1,84-1);//pwm 输出口初始化
    PWM1_CH1_Out_Init(15015-1,84-1);//pwm 输出口初始化
}

