////#include "get_pwm.h"
////#include "led.h"
////#include "usart.h"



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////PWM1捕获配置    使用定时器3 作为PWM1 的定时器
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////TIM_ICInitTypeDef  PWM1_ICInitStructure;

//////定时器3通道1输入捕获配置
//////arr：自动重装值(TIM4,TIM5是32位的!!)
//////psc：时钟预分频数
////void PWM1_CH1_Cap_Init(u32 arr,u16 psc)
////{
////    GPIO_InitTypeDef GPIO_InitStructure;
////    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
////    TIM_OCInitTypeDef  TIM_OCInitStructure;
////    NVIC_InitTypeDef NVIC_InitStructure;


////    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  		//TIM3时钟使能
////    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 		//使能PORTA时钟

////    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; 					//GPIOA6
////    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;				//复用功能
////    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;			//速度100MHz
////    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;				//推挽复用输出
////    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; 				//下拉
////    GPIO_Init(GPIOA,&GPIO_InitStructure); 						//初始化PA6

////    GPIO_PinAFConfig(GPIOA,GPIO_PinSource6,GPIO_AF_TIM3); 		//PA6复用位定时器3


////    TIM_TimeBaseStructure.TIM_Prescaler=psc;  					//定时器分频
////    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 	//向上计数模式
////    TIM_TimeBaseStructure.TIM_Period=arr;   					//自动重装载值
////    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;

////    TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);//初始化定时器


////    //初始化PWM1输入捕获参数
////    PWM1_ICInitStructure.TIM_Channel = TIM_Channel_1; 					//CC1S=01 	选择输入端 IC1映射到TI1上
////    PWM1_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;		//上升沿捕获
////    PWM1_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; 	//映射到TI1上
////    PWM1_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 			//配置输入分频,不分频
////    PWM1_ICInitStructure.TIM_ICFilter = 0x00;							//IC1F=0000 配置输入滤波器 不滤波
////    TIM_ICInit(TIM3, &PWM1_ICInitStructure);
////    TIM_ITConfig(TIM3,TIM_IT_Update|TIM_IT_CC1,ENABLE);					//允许更新中断 ,允许CC1IE捕获中断

//////    //初始化TIM14 Channel1 PWM模式
//////    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
//////    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
//////    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性低
//////    TIM_OC1Init(TIM14, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM1 4OC1
//////    TIM_OC1PreloadConfig(TIM14, TIM_OCPreload_Enable);  //使能TIM14在CCR1上的预装载寄存器
//////    TIM_ARRPreloadConfig(TIM14,ENABLE);//ARPE使能


////    TIM_Cmd(TIM3,ENABLE ); 					//使能定时器3


////    //中断配置
////    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
////    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;			//抢占优先级2
////    NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;				//子优先级0
////    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					//IRQ通道使能
////    NVIC_Init(&NVIC_InitStructure);									//根据指定的参数初始化VIC寄存器、


////}


//////捕获状态
//////[7]:0,没有成功的捕获;1,成功捕获到一次.
//////[6]:0,还没捕获到低电平;1,已经捕获到低电平了.
//////[5:0]:捕获低电平后溢出的次数(对于32位定时器来说,1us计数器加1,溢出时间:4294秒)
////u8  PWM1CH1_CAPTURE_STA=0;	//输入捕获状态
////u32	PWM1CH1_CAPTURE_VAL;	//输入捕获值(TIM4/TIM5是32位)
////u32	PWM1CH1_CAPTURE_VAL_CYC;	//输入捕获值(TIM4/TIM5是32位)
////u32 PWM1Data;//我的计数值

//////PWM1 定时器3中断服务程序  PWM1口
////void TIM3_IRQHandler(void)
////{

////    if((PWM1CH1_CAPTURE_STA&0X80)==0)//还未成功捕获
////    {
////        if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)//溢出
////        {
////            if(PWM1CH1_CAPTURE_STA&0X40)//已经捕获到高电平了
////            {
////                if((PWM1CH1_CAPTURE_STA&0X3F)==0X3F)//高电平太长了
////                {
////                    PWM1CH1_CAPTURE_STA|=0X80;		//标记成功捕获了一次
////                    PWM1CH1_CAPTURE_VAL=0XFFFFFFFF;
////                }
////                else {
////                    PWM1CH1_CAPTURE_STA++;
////                }
////            }
////        }
////        if(TIM_GetITStatus(TIM3, TIM_IT_CC1) != RESET)//捕获1发生捕获事件
////        {

////            if(PWM1CH1_CAPTURE_STA&0X40)		//捕获到一个下降沿
////            {
////                PWM1CH1_CAPTURE_STA|=0X80;		//标记成功捕获到一次高电平脉宽
////                PWM1CH1_CAPTURE_VAL=TIM_GetCapture1(TIM3);//获取当前的捕获值.

////                PWM1CH1_CAPTURE_VAL_CYC=TIM_GetCapture2(TIM3);
////                TIM_OC1PolarityConfig(TIM3,TIM_ICPolarity_Rising); //CC1P=0 设置为上升沿捕获    TIM_ICPolarity_Rising
////            }

////            else  								//还未开始,第一次捕获上升沿
////            {
////                PWM1CH1_CAPTURE_STA=0;			//清空
////                PWM1CH1_CAPTURE_VAL=0;
////                PWM1CH1_CAPTURE_STA|=0X40;		//标记捕获到了上升沿
////                TIM_Cmd(TIM3,DISABLE ); 		//关闭定时器5
////                TIM_SetCounter(TIM3,0);
////                TIM_OC1PolarityConfig(TIM3,TIM_ICPolarity_Falling);		//CC1P=1 设置为下降沿捕获   TIM_ICPolarity_Falling
////                TIM_Cmd(TIM3,ENABLE ); 			//使能定时器5
////            }
////        }
////    }
////    TIM_ClearITPendingBit(TIM3, TIM_IT_CC1|TIM_IT_Update); //清除中断标志位
////}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////PWM2 输出配置
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////PWM输出初始化
//////arr：自动重装值
//////psc：时钟预分频数
////void PWM1_CH1_Out_Init(u32 arr,u32 psc)
////{
////    //此部分需手动修改IO口设置
////    GPIO_InitTypeDef GPIO_InitStructure;
////    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
////    TIM_OCInitTypeDef  TIM_OCInitStructure;

////    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  		//TIM3时钟使能
////    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 		//使能PORTA时钟

////    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; 					//GPIOA6
////    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;				//复用功能
////    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;			//速度100MHz
////    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;				//推挽复用输出
////    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; 				//下拉
////    GPIO_Init(GPIOA,&GPIO_InitStructure); 						//初始化PA6

////    GPIO_PinAFConfig(GPIOA,GPIO_PinSource6,GPIO_AF_TIM3); 		//PA6复用位定时器3


////    TIM_TimeBaseStructure.TIM_Prescaler=psc;  					//定时器分频
////    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 	//向上计数模式
////    TIM_TimeBaseStructure.TIM_Period=arr;   					//自动重装载值
////    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;

////    TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);//初始化定时器


////    //初始化TIM12 Channel1 PWM模式
////    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
////    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
////    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性低
////    TIM_OC1Init(TIM3, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM1 4OC1
////    TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM12在CCR1上的预装载寄存器
////    TIM_ARRPreloadConfig(TIM3,ENABLE);//ARPE使能

////    TIM_Cmd(TIM3, ENABLE);  //使能TIM2
////}





/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////PWM2捕获配置  使用定时器4 作为PWM2 的定时器
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////TIM_ICInitTypeDef  PWM2_ICInitStructure;

//////定时器4通道1输入捕获配置
//////arr：自动重装值(TIM2,TIM5是32位的!!)
//////psc：时钟预分频数
////void PWM2_CH1_Cap_Init(u32 arr,u16 psc)
////{
////    GPIO_InitTypeDef GPIO_InitStructure;
////    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
////    NVIC_InitTypeDef NVIC_InitStructure;


////    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);  		//TIM1时钟使能
////    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE); 		//使能PORTE时钟

////    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; 					//GPIOE9
////    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;				//复用功能
////    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;			//速度100MHz
////    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;				//推挽复用输出
////    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; 				//  下拉
////    GPIO_Init(GPIOE,&GPIO_InitStructure); 						//初始化PE9

////    GPIO_PinAFConfig(GPIOE,GPIO_PinSource9,GPIO_AF_TIM1); 		//PE9复用位定时器1

////    TIM_DeInit(TIM1); //重设成默认值
////    TIM_TimeBaseStructure.TIM_Prescaler=psc;  					//定时器分频
////    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 	//向上计数模式
////    TIM_TimeBaseStructure.TIM_Period=arr;   					//自动重装载值
////    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;//时钟分割值

////    TIM_TimeBaseStructure.TIM_RepetitionCounter=0; //网上新加的部分
////    TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure);//初始化时钟TIM1


////    //初始化PWM2输入捕获参数
////    PWM2_ICInitStructure.TIM_Channel = TIM_Channel_1; 					//CC1S=01 	选择输入端 IC1映射到TI1上
////    PWM2_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;		//上升沿捕获
////    PWM2_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; 	//映射到TI1上
////    PWM2_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 			//配置输入分频,不分频
////    PWM2_ICInitStructure.TIM_ICFilter = 0x00;							//IC1F=0000 配置输入滤波器 不滤波

//////    TIM_PWMIConfig(TIM1, &PWM2_ICInitStructure);
//////    TIM_SelectInputTrigger(TIM1, TIM_TS_TI1FP1); //选择ic1为始终触发源
//////    TIM_SelectSlaveMode(TIM1, TIM_SlaveMode_Reset);//TIM 从模式 触发信号的上升沿重新初始化计数器和触发寄存器的更新事件
//////    TIM_SelectMasterSlaveMode(TIM1, TIM_MasterSlaveMode_Enable); //启动定时器被动触发
////    TIM_ICInit(TIM1, &PWM2_ICInitStructure);

////    TIM_ITConfig(TIM1
////                 ,TIM_IT_Update
////                 |TIM_IT_CC1
////                 ,ENABLE);					//允许更新中断 ,允许CC1IE捕获中断

////    // TIM_ClearFlag(TIM1, TIM_IT_Update|TIM_IT_CC1);// 清除中断标志位


////    NVIC_InitStructure.NVIC_IRQChannel = TIM1_CC_IRQn;
////    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;			//抢占优先级3
////    NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;				//子优先级1
////    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					//IRQ通道使能
////    NVIC_Init(&NVIC_InitStructure);									//根据指定的参数初始化VIC寄存器�
////    TIM_Cmd(TIM1,ENABLE ); 					//使能定时器1
////}


//////捕获状态
//////[7]:0,没有成功的捕获;1,成功捕获到一次.
//////[6]:0,还没捕获到低电平;1,已经捕获到低电平了.
//////[5:0]:捕获低电平后溢出的次数(对于32位定时器来说,1us计数器加1,溢出时间:4294秒)
////u8  PWM2CH1_CAPTURE_STA=0;	//输入捕获状态
////u32	PWM2CH1_CAPTURE_VAL;	//输入捕获值(PWM2/TIM5是32位)
////u32	PWM2CH1_CAPTURE_VAL_CYC;	//输入捕获值(TIM4/TIM5是32位)

//////PWM2  定时器1中断服务程序
////void TIM1_CC_IRQHandler(void)
////{

////    if((PWM2CH1_CAPTURE_STA&0X80)==0)//还未成功捕获
////    {
////        if(TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)//溢出
////        {
////            if(PWM2CH1_CAPTURE_STA&0X40)//已经捕获到高电平了
////            {
////                if((PWM2CH1_CAPTURE_STA&0X3F)==0X3F)//高电平太长了
////                {
////                    PWM2CH1_CAPTURE_STA|=0X80;		//标记成功捕获了一次
////                    PWM2CH1_CAPTURE_VAL=0XFFFFFFFF;
////                }

////                else
////                    PWM2CH1_CAPTURE_STA++;
////            }
////        }
////        if(TIM_GetITStatus(TIM1, TIM_IT_CC1) != RESET)//捕获2发生捕获事件
////        {


////            if(PWM2CH1_CAPTURE_STA&0X40)		//捕获到一个下降沿
////            {
////                PWM2CH1_CAPTURE_STA|=0X80;		//标记成功捕获到一次高电平脉宽
////                PWM2CH1_CAPTURE_VAL=TIM_GetCapture1(TIM1);//获取当前的捕获值.

////                PWM2CH1_CAPTURE_VAL_CYC=TIM_GetCapture2(TIM1);

////                TIM_OC1PolarityConfig(TIM1,TIM_ICPolarity_Rising); //CC1P=0 设置为上升沿捕获
////            }

////            else  								//还未开始,第一次捕获上升沿
////            {
////                PWM2CH1_CAPTURE_STA=0;			//清空
////                PWM2CH1_CAPTURE_VAL=0;
////                PWM2CH1_CAPTURE_STA|=0X40;		//标记捕获到了上升沿
////                TIM_Cmd(TIM1,DISABLE ); 		//关闭定时器1
////                TIM_SetCounter(TIM1,0);
////                TIM_OC1PolarityConfig(TIM1,TIM_ICPolarity_Falling);		//CC1P=1 设置为下降沿捕获
////                TIM_Cmd(TIM1,ENABLE ); 			//使能定时器1
////            }
////        }
////    }
////    TIM_ClearITPendingBit(TIM1, TIM_IT_CC1|TIM_IT_Update); //清除中断标志位
////}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////PWM2 输出配置
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////PWM输出初始化
//////arr：自动重装值
//////psc：时钟预分频数
////void PWM2_CH1_Out_Init(u32 arr,u32 psc)
////{
////    //此部分需手动修改IO口设置
////    GPIO_InitTypeDef GPIO_InitStructure;
////    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
////    TIM_OCInitTypeDef  TIM_OCInitStructure;

////    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);  		//TIM1时钟使能
////    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE); 		//使能PORTE时钟

////    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; 					//GPIOE9
////    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;				//复用功能
////    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;			//速度100MHz
////    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;				//推挽复用输出
////    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; 				//  下拉
////    GPIO_Init(GPIOE,&GPIO_InitStructure); 						//初始化PE9

////    GPIO_PinAFConfig(GPIOE,GPIO_PinSource9,GPIO_AF_TIM1); 		//PE9复用位定时器1

////    TIM_DeInit(TIM1); //重设成默认值
////    TIM_TimeBaseStructure.TIM_Prescaler=psc;  					//定时器分频
////    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 	//向上计数模式
////    TIM_TimeBaseStructure.TIM_Period=arr;   					//自动重装载值
////    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;//时钟分割值

////    // TIM_TimeBaseStructure.TIM_RepetitionCounter=0; //网上新加的部分
////    TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure);//初始化时钟TIM1

////    //初始化TIM12 Channel1 PWM模式
////    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
////    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
////    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性低
////    TIM_OC1Init(TIM1, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM1 4OC1

////    TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);  //使能TIM12在CCR1上的预装载寄存器

////    TIM_ARRPreloadConfig(TIM1,ENABLE);//ARPE使能

////    TIM_Cmd(TIM1, ENABLE);  //使能TIM2
////}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////PWM3捕获配置
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////TIM_ICInitTypeDef  PWM3_ICInitStructure;

//////定时器3通道1输入捕获配置
//////arr：自动重装值(TIM4,TIM5是32位的!!)
//////psc：时钟预分频数
////void PWM3_CH1_Cap_Init(u32 arr,u16 psc)
////{
////    GPIO_InitTypeDef GPIO_InitStructure;
////    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
////    NVIC_InitTypeDef NVIC_InitStructure;


////    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12,ENABLE);  		//TIM5时钟使能
////    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 		//使能PORTA时钟

////    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14; 					//GPIOB14
////    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;				//复用功能
////    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;			//速度100MHz
////    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;				//推挽复用输出
////    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; 				//下拉
////    GPIO_Init(GPIOB,&GPIO_InitStructure); 						//初始化PB14

////    GPIO_PinAFConfig(GPIOB,GPIO_PinSource14,GPIO_AF_TIM12); 		//PB14复用位定时器12


////    TIM_TimeBaseStructure.TIM_Prescaler=psc;  					//定时器分频
////    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 	//向上计数模式
////    TIM_TimeBaseStructure.TIM_Period=arr;   					//自动重装载值
////    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;

////    TIM_TimeBaseInit(TIM12,&TIM_TimeBaseStructure);


////    //初始化TIM5输入捕获参数
////    PWM3_ICInitStructure.TIM_Channel = TIM_Channel_1; 					//CC1S=01 	选择输入端 IC1映射到TI1上
////    PWM3_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;		//上升沿捕获
////    PWM3_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; 	//映射到TI1上
////    PWM3_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 			//配置输入分频,不分频
////    PWM3_ICInitStructure.TIM_ICFilter = 0x00;							//IC1F=0000 配置输入滤波器 不滤波
////    TIM_ICInit(TIM12, &PWM3_ICInitStructure);

////    TIM_ITConfig(TIM12,TIM_IT_Update|TIM_IT_CC1,ENABLE);					//允许更新中断 ,允许CC1IE捕获中断

////    TIM_Cmd(TIM12,ENABLE ); 					//使能定时器5


////    NVIC_InitStructure.NVIC_IRQChannel = TIM8_BRK_TIM12_IRQn;
////    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;			//抢占优先级3
////    NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;				//子优先级2
////    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					//IRQ通道使能
////    NVIC_Init(&NVIC_InitStructure);									//根据指定的参数初始化VIC寄存器、


////}


//////捕获状态
//////[7]:0,没有成功的捕获;1,成功捕获到一次.
//////[6]:0,还没捕获到低电平;1,已经捕获到低电平了.
//////[5:0]:捕获低电平后溢出的次数(对于32位定时器来说,1us计数器加1,溢出时间:4294秒)
////u8  PWM3CH1_CAPTURE_STA=0;	//输入捕获状态
////u32	PWM3CH1_CAPTURE_VAL;	//输入捕获值(TIM4/TIM5是32位)
////u32	PWM3CH1_CAPTURE_VAL_CYC;	//输入捕获值(TIM4/TIM5是32位)

//////定时器3中断服务程序
////void TIM8_BRK_TIM12_IRQHandler(void)
////{

////    if((PWM3CH1_CAPTURE_STA&0X80)==0)//还未成功捕获
////    {
////        if(TIM_GetITStatus(TIM12, TIM_IT_Update) != RESET)//溢出
////        {
////            if(PWM3CH1_CAPTURE_STA&0X40)//已经捕获到高电平了
////            {
////                if((PWM3CH1_CAPTURE_STA&0X3F)==0X3F)//高电平太长了
////                {
////                    PWM3CH1_CAPTURE_STA|=0X80;		//标记成功捕获了一次
////                    PWM3CH1_CAPTURE_VAL=0XFFFFFFFF;
////                }

////                else
////                    PWM3CH1_CAPTURE_STA++;
////            }
////        }
////        if(TIM_GetITStatus(TIM12, TIM_IT_CC1) != RESET)//捕获1发生捕获事件
////        {

////            if(PWM3CH1_CAPTURE_STA&0X40)		//捕获到一个下降沿
////            {
////                PWM3CH1_CAPTURE_STA|=0X80;		//标记成功捕获到一次高电平脉宽
////                PWM3CH1_CAPTURE_VAL=TIM_GetCapture1(TIM12);//获取当前的捕获值.

////                PWM3CH1_CAPTURE_VAL_CYC=TIM_GetCapture2(TIM12);

////                TIM_OC1PolarityConfig(TIM12,TIM_ICPolarity_Rising); //CC1P=0 设置为上升沿捕获
////            }

////            else  								//还未开始,第一次捕获上升沿
////            {
////                PWM3CH1_CAPTURE_STA=0;			//清空
////                PWM3CH1_CAPTURE_VAL=0;
////                PWM3CH1_CAPTURE_STA|=0X40;		//标记捕获到了上升沿
////                TIM_Cmd(TIM12,DISABLE ); 		//关闭定时器5
////                TIM_SetCounter(TIM12,0);
////                TIM_OC1PolarityConfig(TIM12,TIM_ICPolarity_Falling);		//CC1P=1 设置为下降沿捕获
////                TIM_Cmd(TIM12,ENABLE ); 			//使能定时器5
////            }
////        }
////    }
////    TIM_ClearITPendingBit(TIM12, TIM_IT_CC1|TIM_IT_Update); //清除中断标志位
////}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////PWM3 输出配置
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////PWM输出初始化
//////arr：自动重装值
//////psc：时钟预分频数
////void PWM3_CH1_Out_Init(u32 arr,u32 psc)
////{
////    //此部分需手动修改IO口设置
////    GPIO_InitTypeDef GPIO_InitStructure;
////    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
////    TIM_OCInitTypeDef  TIM_OCInitStructure;

////    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);  		//TIM5时钟使能
////    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 		//使能PORTA时钟

////    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; 					//GPIOA5
////    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;				//复用功能
////    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;			//速度100MHz
////    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;				//推挽复用输出
////    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; 				//下拉
////    GPIO_Init(GPIOA,&GPIO_InitStructure); 						//初始化pa5

////    GPIO_PinAFConfig(GPIOA,GPIO_PinSource5,GPIO_AF_TIM2); 		//Pa5复用位定时器2


////    TIM_TimeBaseStructure.TIM_Prescaler=psc;  					//定时器分频
////    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 	//向上计数模式
////    TIM_TimeBaseStructure.TIM_Period=arr;   					//自动重装载值
////    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
////    TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);//初始化定时器2

////    //初始化TIM12 Channel1 PWM模式
////    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
////    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
////    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性低
////    TIM_OC1Init(TIM2, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM1 4OC1

////    TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);  //使能TIM12在CCR1上的预装载寄存器

////    TIM_ARRPreloadConfig(TIM2,ENABLE);//ARPE使能

////    TIM_Cmd(TIM2, ENABLE);  //使能TIM2
////}




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////PWM4 输出配置
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////PWM输出初始化
//////arr：自动重装值
//////psc：时钟预分频数
////void PWM4_CH1_Out_Init(u32 arr,u32 psc)
////{
////    //此部分需手动修改IO口设置

////    GPIO_InitTypeDef GPIO_InitStructure;
////    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
////    TIM_OCInitTypeDef  TIM_OCInitStructure;

////    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);  	//TIM2时钟使能
////    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	//使能PORTF时钟

////    GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_TIM2); //GPIOA1复用为定时器2

////    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;           //GPIOA1
////    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
////    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
////    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
////    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
////    GPIO_Init(GPIOA,&GPIO_InitStructure);              //初始化PA0

////    TIM_TimeBaseStructure.TIM_Prescaler=psc;  //定时器分频
////    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
////    TIM_TimeBaseStructure.TIM_Period=arr;   //自动重装载值
////    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;

////    TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);//初始化定时器2

////    //初始化TIM2 Channel1 PWM模式
////    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
////    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
////    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性低
////    TIM_OC1Init(TIM2, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM1 4OC1

////    TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);  //使能TIM2在CCR1上的预装载寄存器

////    TIM_ARRPreloadConfig(TIM2,ENABLE);//ARPE使能

////    TIM_Cmd(TIM2, ENABLE);  //使能TIM2
////}


/////////////////////////////////////////////////
///////PW4 输入配置
/////////////////////////////////////////////////
////TIM_ICInitTypeDef  PWM4_ICInitStructure;
////void PWM4_CH1_Cap_Init(u32 arr,u16 psc)
////{
////    GPIO_InitTypeDef GPIO_InitStructure;
////    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
////    NVIC_InitTypeDef NVIC_InitStructure;


////    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);  		//TIM5时钟使能
////    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); 		//使能PORTA时钟

////    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14; 					//GPIOB14
////    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;				//复用功能
////    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;			//速度100MHz
////    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;				//推挽复用输出
////    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; 				//下拉
////    GPIO_Init(GPIOD,&GPIO_InitStructure); 						//初始化PB14

////    GPIO_PinAFConfig(GPIOD,GPIO_PinSource14,GPIO_AF_TIM4); 		//PB14复用位定时器4


////    TIM_TimeBaseStructure.TIM_Prescaler=psc;  					//定时器分频
////    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 	//向上计数模式
////    TIM_TimeBaseStructure.TIM_Period=arr;   					//自动重装载值
////    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;

////    TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);


////    //初始化TIM5输入捕获参数
////    PWM4_ICInitStructure.TIM_Channel = TIM_Channel_1; 					//CC1S=01 	选择输入端 IC1映射到TI1上
////    PWM4_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;		//上升沿捕获
////    PWM4_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; 	//映射到TI1上
////    PWM4_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 			//配置输入分频,不分频
////    PWM4_ICInitStructure.TIM_ICFilter = 0x00;							//IC1F=0000 配置输入滤波器 不滤波
////    TIM_ICInit(TIM4, &PWM4_ICInitStructure);
////    TIM_ITConfig(TIM4,TIM_IT_Update|TIM_IT_CC1,ENABLE);					//允许更新中断 ,允许CC1IE捕获中断

////    TIM_Cmd(TIM4,ENABLE ); 					//使能定时器5


////    NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn ;
////    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;			//抢占优先级3
////    NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;				//子优先级2
////    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					//IRQ通道使能
////    NVIC_Init(&NVIC_InitStructure);									//根据指定的参数初始化VIC寄存器、
////}

//////捕获状态
//////[7]:0,没有成功的捕获;1,成功捕获到一次.
//////[6]:0,还没捕获到低电平;1,已经捕获到低电平了.
//////[5:0]:捕获低电平后溢出的次数(对于32位定时器来说,1us计数器加1,溢出时间:4294秒)
////u8  PWM4CH1_CAPTURE_STA=0;	//输入捕获状态
////u32	PWM4CH1_CAPTURE_VAL;	//输入捕获值(TIM4/TIM5是32位)
////u32	PWM4CH1_CAPTURE_VAL_CYC;	//输入捕获值(TIM4/TIM5是32位)

////void TIM4_IRQHandler(void) {

////    if((PWM4CH1_CAPTURE_STA&0X80)==0)//还未成功捕获
////    {
////        if(TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)//溢出
////        {
////            if(PWM4CH1_CAPTURE_STA&0X40)//已经捕获到高电平了
////            {
////                if((PWM4CH1_CAPTURE_STA&0X3F)==0X3F)//高电平太长了
////                {
////                    PWM4CH1_CAPTURE_STA|=0X80;		//标记成功捕获了一次
////                    PWM4CH1_CAPTURE_VAL=0XFFFFFFFF;
////                }
////                else
////                    PWM4CH1_CAPTURE_STA++;
////            }
////        }
////        if(TIM_GetITStatus(TIM4, TIM_IT_CC1) != RESET)//捕获1发生捕获事件
////        {

////            if(PWM4CH1_CAPTURE_STA&0X40)		//捕获到一个下降沿
////            {
////                PWM4CH1_CAPTURE_STA|=0X80;		//标记成功捕获到一次高电平脉宽
////                PWM4CH1_CAPTURE_VAL=TIM_GetCapture1(TIM4);//获取当前的捕获值.

////                PWM4CH1_CAPTURE_VAL_CYC=TIM_GetCapture2(TIM4);

////                TIM_OC1PolarityConfig(TIM4,TIM_ICPolarity_Rising); //CC1P=0 设置为上升沿捕获//TIM_ICPolarity_Falling
////            }

////            else  								//还未开始,第一次捕获上升沿
////            {
////                PWM4CH1_CAPTURE_STA=0;			//清空
////                PWM4CH1_CAPTURE_VAL=0;
////                PWM4CH1_CAPTURE_STA|=0X40;		//标记捕获到了上升沿
////                TIM_Cmd(TIM4,DISABLE); 		//关闭定时器5
////                TIM_SetCounter(TIM4,0);
////                TIM_OC1PolarityConfig(TIM4,TIM_ICPolarity_Falling);		//CC1P=1 设置为下降沿捕获//TIM_ICPolarity_Rising
////                TIM_Cmd(TIM4,ENABLE ); 			//使能定时器5
////            }
////        }
////    }
////    TIM_ClearITPendingBit(TIM4, TIM_IT_CC1|TIM_IT_Update); //清除中断标志位
////}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////PWM5 输出配置
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



//////PWM输出初始化
//////arr：自动重装值
//////psc：时钟预分频数
////void PWM5_CH1_Out_Init(u32 arr,u32 psc)
////{
////    //此部分需手动修改IO口设置

////    GPIO_InitTypeDef GPIO_InitStructure;
////    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
////    TIM_OCInitTypeDef  TIM_OCInitStructure;

////    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);  	//TIM2时钟使能
////    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	//使能PORTF时钟

////    GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_TIM5); //GPIOA0复用为定时器5

////    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;           //GPIOA0
////    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
////    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
////    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
////    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
////    GPIO_Init(GPIOA,&GPIO_InitStructure);              //初始化PA0

////    TIM_TimeBaseStructure.TIM_Prescaler=psc;  //定时器分频
////    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
////    TIM_TimeBaseStructure.TIM_Period=arr;   //自动重装载值
////    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;

////    TIM_TimeBaseInit(TIM5,&TIM_TimeBaseStructure);//初始化定时器2

////    //初始化TIM5 Channel1 PWM模式
////    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
////    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
////    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性低
////    TIM_OC1Init(TIM5, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM1 4OC1

////    TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Enable);  //使能TIM2在CCR1上的预装载寄存器

////    TIM_ARRPreloadConfig(TIM5,ENABLE);//ARPE使能

////    TIM_Cmd(TIM5, ENABLE);  //使能TIM2
////}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////PWM5 输出配置
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////TIM_ICInitTypeDef  PWM5_ICInitStructure;
////void PWM5_CH1_Cap_Init(u32 arr,u16 psc) {
////    GPIO_InitTypeDef GPIO_InitStructure;
////    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
////    NVIC_InitTypeDef NVIC_InitStructure;


////    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM11,ENABLE);  		//TIM5时钟使能
////    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 		//使能PORTA时钟

////    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; 					//GPIOB14
////    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;				//复用功能
////    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;			//速度100MHz
////    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;				//推挽复用输出
////    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; 				//下拉
////    GPIO_Init(GPIOB,&GPIO_InitStructure); 						//初始化PB14

////    GPIO_PinAFConfig(GPIOB,GPIO_PinSource9,GPIO_AF_TIM11); 		//PB14复用位定时器4


////    TIM_TimeBaseStructure.TIM_Prescaler=psc;  					//定时器分频
////    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 	//向上计数模式
////    TIM_TimeBaseStructure.TIM_Period=arr;   					//自动重装载值
////    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;

////    TIM_TimeBaseInit(TIM11,&TIM_TimeBaseStructure);


////    //初始化TIM5输入捕获参数
////    PWM5_ICInitStructure.TIM_Channel = TIM_Channel_1; 					//CC1S=01 	选择输入端 IC1映射到TI1上
////    PWM5_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;		//上升沿捕获
////    PWM5_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; 	//映射到TI1上
////    PWM5_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 			//配置输入分频,不分频
////    PWM5_ICInitStructure.TIM_ICFilter = 0x00;							//IC1F=0000 配置输入滤波器 不滤波
////    TIM_ICInit(TIM11, &PWM5_ICInitStructure);
////    TIM_ITConfig(TIM11,TIM_IT_Update|TIM_IT_CC1,ENABLE);					//允许更新中断 ,允许CC1IE捕获中断

////    TIM_Cmd(TIM11,ENABLE ); 					//使能定时器5


////    NVIC_InitStructure.NVIC_IRQChannel = TIM1_TRG_COM_TIM11_IRQn ;
////    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;			//抢占优先级3
////    NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;				//子优先级2
////    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					//IRQ通道使能
////    NVIC_Init(&NVIC_InitStructure);									//根据指定的参数初始化VIC寄存器、
////}
//////捕获状态
//////[7]:0,没有成功的捕获;1,成功捕获到一次.
//////[6]:0,还没捕获到低电平;1,已经捕获到低电平了.
//////[5:0]:捕获低电平后溢出的次数(对于32位定时器来说,1us计数器加1,溢出时间:4294秒)
////u8  PWM5CH1_CAPTURE_STA=0;	//输入捕获状态
////u32	PWM5CH1_CAPTURE_VAL;	//输入捕获值(TIM4/TIM5是32位)
////u32	PWM5CH1_CAPTURE_VAL_CYC;	//输入捕获值(TIM4/TIM5是32位)
////void TIM1_TRG_COM_TIM11_IRQHandler(void) {
////    if((PWM5CH1_CAPTURE_STA&0X80)==0)//还未成功捕获
////    {
////        if(TIM_GetITStatus(TIM11, TIM_IT_Update) != RESET)//溢出
////        {
////            if(PWM5CH1_CAPTURE_STA&0X40)//已经捕获到高电平了
////            {
////                if((PWM5CH1_CAPTURE_STA&0X3F)==0X3F)//高电平太长了
////                {
////                    PWM5CH1_CAPTURE_STA|=0X80;		//标记成功捕获了一次
////                    PWM5CH1_CAPTURE_VAL=0XFFFFFFFF;
////                }
////                else
////                    PWM5CH1_CAPTURE_STA++;
////            }
////        }
////        if(TIM_GetITStatus(TIM11, TIM_IT_CC1) != RESET)//捕获1发生捕获事件
////        {

////            if(PWM5CH1_CAPTURE_STA&0X40)		//捕获到一个下降沿
////            {
////                PWM5CH1_CAPTURE_STA|=0X80;		//标记成功捕获到一次高电平脉宽
////                PWM5CH1_CAPTURE_VAL=TIM_GetCapture1(TIM11);//获取当前的捕获值.

////                PWM5CH1_CAPTURE_VAL_CYC=TIM_GetCapture2(TIM11);

////                TIM_OC1PolarityConfig(TIM11,TIM_ICPolarity_Rising); //CC1P=0 设置为上升沿捕获//TIM_ICPolarity_Falling
////            }

////            else  								//还未开始,第一次捕获上升沿
////            {
////                PWM5CH1_CAPTURE_STA=0;			//清空
////                PWM5CH1_CAPTURE_VAL=0;
////                PWM5CH1_CAPTURE_STA|=0X40;		//标记捕获到了上升沿
////                TIM_Cmd(TIM11,DISABLE); 		//关闭定时器5
////                TIM_SetCounter(TIM11,0);
////                TIM_OC1PolarityConfig(TIM11,TIM_ICPolarity_Falling);		//CC1P=1 设置为下降沿捕获//TIM_ICPolarity_Rising
////                TIM_Cmd(TIM11,ENABLE ); 			//使能定时器5
////            }
////        }
////    }
////    TIM_ClearITPendingBit(TIM11, TIM_IT_CC1|TIM_IT_Update); //清除中断标志位
////}



////// TIM_ICInitTypeDef  TIM5_ICInitStructure;

////// //定时器5通道1输入捕获配置
////// //arr：自动重装值(TIM4,TIM5是32位的!!)
////// //psc：时钟预分频数
////// void TIM5_CH1_Cap_Init(u32 arr,u16 psc)
////// {
////// 	GPIO_InitTypeDef GPIO_InitStructure;
////// 	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
////// 	NVIC_InitTypeDef NVIC_InitStructure;


////// 	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);  		//TIM5时钟使能
////// 	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 		//使能PORTA时钟

////// 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; 					//GPIOA0
////// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;				//复用功能
////// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;			//速度100MHz
////// 	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;				//推挽复用输出
////// 	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; 				//下拉
////// 	GPIO_Init(GPIOA,&GPIO_InitStructure); 						//初始化PA0

////// 	GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_TIM5); 		//PA0复用位定时器5


////// 	TIM_TimeBaseStructure.TIM_Prescaler=psc;  					//定时器分频
////// 	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 	//向上计数模式
////// 	TIM_TimeBaseStructure.TIM_Period=arr;   					//自动重装载值
////// 	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;

////// 	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseStructure);


////// 	//初始化TIM5输入捕获参数
////// 	TIM5_ICInitStructure.TIM_Channel = TIM_Channel_1; 					//CC1S=01 	选择输入端 IC1映射到TI1上
////// 	TIM5_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;		//上升沿捕获
////// 	TIM5_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; 	//映射到TI1上
////// 	TIM5_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 			//配置输入分频,不分频
////// 	TIM5_ICInitStructure.TIM_ICFilter = 0x00;							//IC1F=0000 配置输入滤波器 不滤波
////// 	TIM_ICInit(TIM5, &TIM5_ICInitStructure);

////// 	TIM_ITConfig(TIM5,TIM_IT_Update|TIM_IT_CC1,ENABLE);					//允许更新中断 ,允许CC1IE捕获中断

////// 	TIM_Cmd(TIM5,ENABLE ); 					//使能定时器5


////// 	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;
////// 	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;			//抢占优先级3
////// 	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;				//子优先级3
////// 	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					//IRQ通道使能
////// 	NVIC_Init(&NVIC_InitStructure);									//根据指定的参数初始化VIC寄存器、


////// }


////// //捕获状态
////// //[7]:0,没有成功的捕获;1,成功捕获到一次.
////// //[6]:0,还没捕获到低电平;1,已经捕获到低电平了.
////// //[5:0]:捕获低电平后溢出的次数(对于32位定时器来说,1us计数器加1,溢出时间:4294秒)
////// u8  TIM5CH1_CAPTURE_STA=0;	//输入捕获状态
////// u32	TIM5CH1_CAPTURE_VAL;	//输入捕获值(TIM4/TIM5是32位)
////// u32	TIM5CH1_CAPTURE_VAL_CYC;	//输入捕获值(TIM4/TIM5是32位)

////// //定时器5中断服务程序
////// void TIM5_IRQHandler(void)
////// {

//////  	if((TIM5CH1_CAPTURE_STA&0X80)==0)//还未成功捕获
////// 	{
////// 		if(TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)//溢出
////// 		{
////// 			if(TIM5CH1_CAPTURE_STA&0X40)//已经捕获到高电平了
////// 			{
////// 				if((TIM5CH1_CAPTURE_STA&0X3F)==0X3F)//高电平太长了
////// 				{
////// 					TIM5CH1_CAPTURE_STA|=0X80;		//标记成功捕获了一次
////// 					TIM5CH1_CAPTURE_VAL=0XFFFFFFFF;
////// 				}

////// 				else
////// 					TIM5CH1_CAPTURE_STA++;
////// 			}
////// 		}
////// 		if(TIM_GetITStatus(TIM5, TIM_IT_CC1) != RESET)//捕获1发生捕获事件
////// 		{

////// 			if(TIM5CH1_CAPTURE_STA&0X40)		//捕获到一个下降沿
////// 			{
////// 				TIM5CH1_CAPTURE_STA|=0X80;		//标记成功捕获到一次高电平脉宽
////// 				TIM5CH1_CAPTURE_VAL=TIM_GetCapture1(TIM5);//获取当前的捕获值.

////// 				TIM5CH1_CAPTURE_VAL_CYC=TIM_GetCapture2(TIM5);

////// 	 			TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Rising); //CC1P=0 设置为上升沿捕获
////// 			}

////// 			else  								//还未开始,第一次捕获上升沿
////// 			{
////// 				TIM5CH1_CAPTURE_STA=0;			//清空
////// 				TIM5CH1_CAPTURE_VAL=0;
////// 				TIM5CH1_CAPTURE_STA|=0X40;		//标记捕获到了上升沿
////// 				TIM_Cmd(TIM5,DISABLE ); 		//关闭定时器5
////// 	 			TIM_SetCounter(TIM5,0);
////// 	 			TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Falling);		//CC1P=1 设置为下降沿捕获
////// 				TIM_Cmd(TIM5,ENABLE ); 			//使能定时器5
////// 			}
////// 		}
//////  	}
////// 	TIM_ClearITPendingBit(TIM5, TIM_IT_CC1|TIM_IT_Update); //清除中断标志位
////// }

