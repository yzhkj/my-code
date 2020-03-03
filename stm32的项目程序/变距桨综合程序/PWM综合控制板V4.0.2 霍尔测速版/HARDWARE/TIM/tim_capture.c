#include "tim_capture.h"


#define a 0.85										//滤波系数a（0-1）
#define MaxChangeValue  100 			//限幅
#define Max_Value 			3000
#define Min_Value 			850

uint32_t value=1000;     					//滤波后的值
uint32_t last_value=1000;      		//上一次的滤波值
uint32_t last_Revalue=1000;      	//上一次的采样值
uint32_t new_value;       				//新采样值


//添加递推平均滤波  添加消除抖动
#define Num 						6													//递推平均的深度
//#define UpDownCountMax  4													//上升下降标志的最大计数值
uint16_t value_buff[Num]={0};											//递推平均的队列 FIFO

//uint16_t value_buff2[Num]={0};										//排序滤波队列FIFO

uint16_t filter(uint32_t rec_value)   
{ 
	static uint8_t count=0;													//FIFO的计数变量 数组的环形偏移量
	static uint8_t orig_count=0;											//原始数据计数
	uint16_t i=0,sum=0;
	uint16_t *point=value_buff;											//指向数组
//	uint16_t *point_f=value_buff2;									//原始数据fifo指针
	//转速限位
	if(rec_value>Max_Value)
	{
		rec_value=Max_Value;
	}
	else if(rec_value<Min_Value)
	{
		rec_value=Min_Value;
	}
	else ;
	
	//消抖滤波
	if((rec_value-last_Revalue)>MaxChangeValue ||
		 (last_Revalue-rec_value)>MaxChangeValue)				//限制变化幅度
  {
		new_value=last_Revalue;													//变化超过
	}
  else
	{
		new_value=rec_value;
		last_Revalue=rec_value;
	}	
	
	//高速消抖  求递推队列的最大值
//	point_f[orig_count++]=new_value;								
//	orig_count=orig_count%Num;
//	new_value=SortRank(point_f,Num);
	
	//一阶滞后滤波
	value=(uint16_t)(a*last_value+(1-a)*new_value); //返回与上一次计算数据相关数据 
	last_value=value;																//保存计算数据
	
	//递推平均滤波
	*(point+(count++))=value;													//将最新的数据保存到buff
																										//自动覆盖队列最后一个数据
	count=count%Num;	
	for(i=0;i<Num;i++)															//求和平均
	{
		sum+=*(point+i);
	}
	return (uint16_t)(sum/Num);	
}



TIM_ICInitTypeDef  TIM4_ICInitStructure;

//定时器4通道3输入捕获配置
//arr：自动重装值(TIM2,TIM5是32位的!!)
//psc：时钟预分频数
void TIM4_CH3_Cap_Init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

			
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);  	//TIM5时钟使能    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 	//使能PORTA时钟	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; //GPIOb8
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOB,&GPIO_InitStructure); //初始化PA0
	GPIO_SetBits(GPIOB,GPIO_Pin_8);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource8,GPIO_AF_TIM4); //PA8复用位定时器4
  
	  
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //定时器分频
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseStructure.TIM_Period=arr;   //自动重装载值
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);
    
	TIM_ClearITPendingBit(TIM4, TIM_IT_CC3|TIM_IT_Update);    //清除中断标志位
	
	//初始化TIM5输入捕获参数
	TIM4_ICInitStructure.TIM_Channel = TIM_Channel_3; //CC1S=01 	选择输入端 IC1映射到TI1上
    TIM4_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Falling;	//上升沿捕获
    TIM4_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
    TIM4_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //配置输入分频,不分频 
    TIM4_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 配置输入滤波器 不滤波
    TIM_ICInit(TIM4, &TIM4_ICInitStructure);
		
	TIM_ITConfig(TIM4,TIM_IT_Update|TIM_IT_CC3,ENABLE);//允许更新中断 ,允许CC1IE捕获中断	
	
    TIM_Cmd(TIM4,ENABLE ); 	//使能定时器5
	
    NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器、
	
}
//捕获状态
//[7]:0,没有成功的捕获;1,成功捕获到一次.
//[6]:0,还没捕获到低电平;1,已经捕获到低电平了.
//[5:0]:捕获低电平后溢出的次数(对于32位定时器来说,1us计数器加1,溢出时间:4294秒)
u8  TIM4CH3_CAPTURE_STA=0;	//输入捕获状态		    				
u32	TIM4CH3_CAPTURE_VAL;	//输入捕获值(TIM2/TIM5是32位)
//定时器5中断服务程序	 
void TIM4_IRQHandler(void)
{ 		    
 	if((TIM4CH3_CAPTURE_STA&0X80)==0)//还未成功捕获	
	{
		if(TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)//溢出
		{	     
			if(TIM4CH3_CAPTURE_STA&0X40)//已经捕获到高电平了
			{
				if((TIM4CH3_CAPTURE_STA&0X3F)==0X3F)//高电平太长了
				{
					TIM4CH3_CAPTURE_STA|=0X80;		//标记成功捕获了一次
					TIM4CH3_CAPTURE_VAL=0XFFFFFFFF;
				}else TIM4CH3_CAPTURE_STA++;
			}	 
		}
		if(TIM_GetITStatus(TIM4, TIM_IT_CC3) != RESET)//捕获1发生捕获事件
		{	
			if(TIM4CH3_CAPTURE_STA&0X40)		//捕获到一个下降沿 		
			{	  			
				TIM4CH3_CAPTURE_STA|=0X80;		//标记成功捕获到一次高电平脉宽
				TIM4CH3_CAPTURE_VAL=TIM_GetCapture3(TIM4);//获取当前的捕获值.
	 			TIM_OC3PolarityConfig(TIM4,TIM_ICPolarity_Falling); //CC1P=0 设置为上升沿捕获
			}else  								//还未开始,第一次捕获上升沿
			{
				TIM4CH3_CAPTURE_STA=0;			//清空
				TIM4CH3_CAPTURE_VAL=0;
				TIM4CH3_CAPTURE_STA|=0X40;		//标记捕获到了上升沿
				TIM_Cmd(TIM4,DISABLE ); 	//关闭定时器5
	 			TIM_SetCounter(TIM4,0);
	 			TIM_OC3PolarityConfig(TIM4,TIM_ICPolarity_Falling);		//CC1P=1 设置为下降沿捕获
				TIM_Cmd(TIM4,ENABLE ); 	//使能定时器5
			}		    
		}			     	    					   
 	}
	TIM_ClearITPendingBit(TIM4, TIM_IT_CC3|TIM_IT_Update); //清除中断标志位
}



