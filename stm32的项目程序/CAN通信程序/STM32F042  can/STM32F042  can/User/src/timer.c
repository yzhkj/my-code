#include "timer.h"
#include "led.h"
//#include "lcd.h"
#include "adc.h"
#include "delay.h"
#include "stm32f0xx_tim.h"
 #include "key.h"
  #include "can.h"

static u16  i=0,j=0,l=0,m=0;
static u8  k=0,n=0;



//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//定时器 驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/3
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////   	 

//通用定时器3中断初始化
//这里时钟选择为APB1的2倍，而APB1为4M
//arr：自动重装值。
//psc：时钟预分频数
//这里使用的是定时器3!

void TIM2_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //时钟使能
	
	//定时器TIM3初始化
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE ); //使能指定的TIM3中断,允许更新中断

	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM3中断
  NVIC_InitStructure.NVIC_IRQChannelPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器
	TIM_Cmd(TIM2, ENABLE);  //使能TIMx		
	
}
//定时器3中断服务程序
void TIM2_IRQHandler(void)   //TIM3中断
{	
	u8 canbuf[10];
	u16 ADC_Value;	
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)  //检查TIM3更新中断发生与否
		{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  //清除TIMx更新中断标志 
	PA1_TOGGLE;
	PA2_TOGGLE;	
	delay_ms(1);
    while((DMA_GetFlagStatus(DMA1_FLAG_TC1)) == RESET ); 	//判断通道2传输完成		
		DMA_ClearFlag(DMA1_FLAG_TC1);//清除通道1传输完成标志
		//	 Convert Vref voltage value in mv 
	ADC_Value = Get_Adc_Average(0,10);
	if(ADC_Value<3850&&ADC_Value>3750)
			{	
//			LCD_ShowString(60,170,200,16,16,"Current mode:MODE3");	
			if(i<512)
			i=2*i+1;
		else 
		{
			j=i;
			i=0;
			k++;
		}
		}
		else if(ADC_Value>150&ADC_Value<250)
		{
//			LCD_ShowString(60,170,200,16,16,"Current mode:MODE5");	
			if(l<512)
			l=2*l+1;
			else 
			{
			m=l;
			l=0;
			n++;	
			}
		}
		else if(ADC_Value>3850&i>1)
		{	if(i<512)
			i=2*i;			
		else
			{
   		j=i;  
			i=0;
			k++;
		}
	}
		else if(ADC_Value<150&l>1)
		{
			if(l<512)	
			l=2*l;
			else
			{
			m=l;
			l=0;
			if(m>840)
				n++;
	/*		else if(m==824)
			LCD_ShowString(60,350,200,16,16,"2018/06/26  Blade02");	
			else if(m==832)
			LCD_ShowString(60,350,200,16,16,"2018/06/25  Blade01");*/	
	   }
	}
	canbuf[0] = (u8)ADC_Value; 
	canbuf[1] = (u8)(ADC_Value>>8); 
	canbuf[2] = (u8)j; 
	canbuf[3] = (u8)(j>>8); 
	canbuf[4] = (u8)m; 
	canbuf[5] = (u8)(m>>8); 
	canbuf[6] = (u8)i; 
	canbuf[7] = (u8)(i>>8);
	canbuf[8] = (u8)l; 
	canbuf[9] = (u8)(l>>8);
  Can_Send_Msg(canbuf,10);		
	delay_ms(1);
		}
}
			











