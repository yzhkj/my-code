#include "tim_capture.h"
#include "math.h"

#define a 				0.5				//平滑度参数
#define MaxChangeValue  100 			//最大变化幅度
#define Max_Value 		2900			//转速最大值
#define Min_Value 		850				//转速最小值
#define Max_Fangcha		250    			//最大方差
#define Num 			3				//fifo的大小 滤波数组的个数

int value=Min_Value;     			//平滑滤波结果
int last_value=Min_Value;      		//上一次平滑滤波值
int last_Revalue=Min_Value;      	//上一次接实的数据
int new_value;       				//限幅滤波后的新值
int old_value=Min_Value;
//int value_buff[Num]={0};	//平均处理的缓存FIFO										//
int value_buff2[Num]={0};	//原始数据缓存FIFO


int filter(int rec_value)   
{ 
	//static uint8_t count=0;				//平均处理的缓存FIFO下标
	static uint8_t orig_count=0;		//原始数据缓存FIFO下标
//	int num_count=0;
//	int sum=0;						//平均处理求和
//	int *point=value_buff;			//
	int *point_f=value_buff2;
	float DataFangcha=0.0;	
	//缓存原始数据							
	*(point_f+(orig_count++))=rec_value;																														
	orig_count=orig_count%Num;
	//限幅消抖滤波  
	if(rec_value<Max_Value && rec_value>Min_Value)
	{
		DataFangcha=fangcha(point_f,Num);	
	    if(DataFangcha>Max_Fangcha)				
	    {
	    	new_value=old_value;
		}
		else
		{
			new_value=rec_value;
			old_value=rec_value;			
		}
	}
	else
	{
		new_value=old_value;
	}
	//平滑滤波
	value=(uint16_t)(a*last_value+(1-a)*new_value); 
	last_value=value;																
	return value;
//	*(point+(count++))=value;	 //缓存数据FIFO																													
//	count=count%Num;			 //计算下标
	
	//求和平均  消除高频抖动
//	for(num_count=0;num_count<Num;num_count++)														
//	{
//		sum+=*(point+num_count);
//	}
//	return (uint16_t)(sum/Num);	
}
float fangcha(int* x,int n)		//求n个数的数组x的方差
{
 	//S=(<x^2>-<x>)^0.5
 	int i;
 	float xaver=0.0, x2aver=0.0;
 	for(i=0;i<n;++i)
    {
  	xaver+=x[i]; x2aver+=x[i]*x[i];
 	}
    xaver/=n; 
	x2aver/=n; 							
    return sqrt(x2aver-xaver*xaver);
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



