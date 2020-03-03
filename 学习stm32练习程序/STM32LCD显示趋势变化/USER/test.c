#include "sys.h"
#include "delay.h"  
#include "usart.h"  
#include "led.h"
#include "lcd.h"
#include "adc.h"
#include "timer.h"
#include "UART2.H"	
//ALIENTEK ̽����STM32F407������ ʵ��13
//TFTLCD��ʾʵ��  
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾

#define Xstar 0   //���Ŀ�ʼx����
#define Ystar 30
#define Xend 240
#define Yend 150
const float PowerMax=4096;       //�����
//const float PowerMin=0


//extern u8 Res_Flag;    //�������ݱ�־
//extern u8 Send_Flag;   //���ͱ�־
//extern u8 resive;         //��������
extern u8 HalfSenced;      //ʱ���ʶ


#define a 50     //Ȩֵ

u8 Old_value;    //��һ�μ�Ȩ����ֵ


u8 filter(u8 get_ad)    //һ���ͺ��˲�
{  
	u16 temp;
	u8 new_value;
	float value;          //�м����
  new_value = get_ad;
	temp=(u16)((100-a)*Old_value + a*new_value);
	value=(float)temp;
	Old_value=(u8)(value/100);
	return Old_value;
//   return (100-a)*value + a*new_value; 
}
void TendRange(u16 Power,u8 Xrange) //���ʴ�����ʾ  Power(0->4096)
{
	float temp;
	u8 Y_value;     //y������
	static u8 Y_OldValue=50;   //��һ���y������
	if(Power>PowerMax) Power=PowerMax;   //���ֵ��
	temp=(float)Power;
	temp=(temp/PowerMax)*100;            //������0-100
//	Y_value=(u8)temp;                      //ȡ��
	Y_value=filter((u8)temp);
	if(Y_value>Y_OldValue)
	{
		if((Y_value-3)>Y_OldValue)       //������ϴ�ֱ���
		{
			LCD_DrawLine(Xstar+(Xrange-1)*2,Yend-Y_OldValue, Xstar+Xrange*2, Yend-Y_value);
//			LCD_DrawLine(Xstar+(Xrange-1)*2-1,Yend-Y_OldValue-1, Xstar+Xrange*2-1, Yend-Y_value-1);
			LCD_DrawBPoint(Xstar+Xrange*2,Yend-Y_value);  //����
		}
		else
		{
			LCD_DrawBPoint(Xstar+Xrange*2,Yend-Y_value);  //����
		}
	}
	else 
	{
		if((Y_OldValue-3)>Y_value)       //������ϴ�ֱ���
		{
			LCD_DrawLine(Xstar+(Xrange-1)*2,Yend-Y_OldValue, Xstar+Xrange*2, Yend-Y_value);
//			LCD_DrawLine(Xstar+(Xrange-1)*2-1,Yend-Y_OldValue-1, Xstar+Xrange*2-1, Yend-Y_value-1);
			LCD_DrawBPoint(Xstar+Xrange*2,Yend-Y_value);  //����
		}
		else
		{
			LCD_DrawBPoint(Xstar+Xrange*2,Yend-Y_value);  //����
		}	
	}
	Y_OldValue=Y_value;     //���¾�ֵ
	
	
}
int main(void)
{   
	u16 adcx,adc;
	float temp;
// 	u8 x=0; 
	static u8 count=0;               //��������
	Stm32_Clock_Init(336,8,2,7);//����ʱ��,168Mhz 
	delay_init(168);			//��ʱ��ʼ��  
	uart_init(84,9600);		//��ʼ�����ڲ�����Ϊ115200 
	TIM3_Int_Init(8400-1,5000-1);
	LED_Init();					//��ʼ��LED
 	LCD_Init();
	Adc_Init();         //adc��ʼ��
	POINT_COLOR=RED; 
	LCD_DrawRectangle(Xstar,Ystar, Xend, Yend);	
	LCD_ShowString(Xstar+50,Yend+5,200,16,16,"TEND RANGE");
	POINT_COLOR=BLUE;
//	for(x=0;x<10;x++)
//	{
//		LCD_DrawBPoint(Xstar+x*2,Ystar+x*2);
//	}
//	LCD_DrawLine(Xstar,Ystar+50,Xstar+100,Ystar+50);
//	printf("HIGH:%lld us\r\n","abcde");
	LCD_ShowString(30,200,200,16,16,"ADC1_CH5_VAL:");	      
	LCD_ShowString(30,220,200,16,16,"ADC1_CH5_VOL:0.000V");	 
 	while(1) 
	{
		adc=Get_Adc_Average(ADC_CH5,20);
		adcx=adc;
		LCD_ShowxNum(134,200,adcx,4,16,0);//��ʾADC��ֵ
		temp=(float)adcx*(3.3/4096); 
		adcx=temp;
		LCD_ShowxNum(134,220,adcx,1,16,0);//��ʾ��ѹֵ
		temp-=adcx;
		temp*=1000;
		LCD_ShowxNum(150,220,temp,3,16,0X80);		
//		if(1==Res_Flag)
//		{
//			Res_Flag=0;
//			send(resive);
//		}
		if(1==HalfSenced)  //ʱ���־
		{
			HalfSenced=0;
			LED0=!LED0;	
			count++;
			if(count>120) 
			{
				count=0;
			  LCD_Clear(WHITE);
				POINT_COLOR=RED;
				LCD_DrawRectangle(Xstar,Ystar, Xend, Yend);	
	      LCD_ShowString(Xstar+50,Yend+5,200,16,16,"TEND RANGE");
				POINT_COLOR=BLUE;
				LCD_ShowString(30,200,200,16,16,"ADC1_CH5_VAL:");	      
	      LCD_ShowString(30,220,200,16,16,"ADC1_CH5_VOL:0.000V");
//				LCD_ShowxNum(134,200,adcx,4,16,0);//��ʾADC��ֵ
//		    LCD_ShowxNum(134,220,adcx,1,16,0);//��ʾ��ѹֵ      				
//				LCD_ShowxNum(150,220,temp,3,16,0X80);		                 
//				LCD_Fill((u16)(Xstar-1),(u16)(Ystar-1),(u16)(Xend-1),(u16)(Yend-1),BLACK);  //����Ļ
			}
			TendRange(adc,count);
		}
//		LED2=!LED2;	
//		delay_ms(500);	
	} 
}

