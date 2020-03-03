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
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//��ʱ�� ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/3
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////   	 

//ͨ�ö�ʱ��3�жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ4M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��3!

void TIM2_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //ʱ��ʹ��
	
	//��ʱ��TIM3��ʼ��
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM3�ж�,��������ж�

	//�ж����ȼ�NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM3�ж�
  NVIC_InitStructure.NVIC_IRQChannelPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���
	TIM_Cmd(TIM2, ENABLE);  //ʹ��TIMx		
	
}
//��ʱ��3�жϷ������
void TIM2_IRQHandler(void)   //TIM3�ж�
{	
	u8 canbuf[10];
	u16 ADC_Value;	
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)  //���TIM3�����жϷ������
		{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  //���TIMx�����жϱ�־ 
	PA1_TOGGLE;
	PA2_TOGGLE;	
	delay_ms(1);
    while((DMA_GetFlagStatus(DMA1_FLAG_TC1)) == RESET ); 	//�ж�ͨ��2�������		
		DMA_ClearFlag(DMA1_FLAG_TC1);//���ͨ��1������ɱ�־
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
			











