#include "led.h"
 #include "delay.h"
 #include "key.h"
 #include "sys.h"
// #include "lcd.h"
 #include "usart.h"	 
 #include "can.h"
  #include "timer.h"
	#include "adc.h"
	#include "iso_usart1.h"
	
 
u8 can_flag[4]={0x01,0x02,0x03,0x04};  //��������  
/************************************************
 ALIENTEKս��STM32������ʵ��26
 CANͨ��ʵ��
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/

static void CAN_NVIC_Configuration(void);
 int main(void)
 {	
	 	u8 count=0;
	u8* flag_point=can_flag;
	u8 mode=CAN_Mode_Normal;//CAN����ģʽ;CAN_Mode_Normal(0)����ͨģʽ��CAN_Mode_LoopBack(1)������ģʽ
	SystemInit ();
	delay_init();	    	 //��ʱ������ʼ��	
  CAN_NVIC_Configuration();	 
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�	
	Adc_Init();
	TIM2_Int_Init(999,7999); 
  CAN_Mode_Init(CAN_SJW_1tq,CAN_BS2_7tq,CAN_BS1_8tq,9,mode);//CAN��ʼ������ģʽ,������500Kbps  
 	while (1)
{	
		Can_Send_Msg(flag_point+count,1);
		count++;
		count=count%4;
		delay_ms(100);
	
//		LED1_TOGGLE;
//		delay_ms(20);
//	LED1_TOGGLE;
//		delay_ms(20);
	}
}
 
static void CAN_NVIC_Configuration(void)
{

	NVIC_InitTypeDef NVIC_InitStructure; 
	
	/* Enable the USART1 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = CEC_CAN_IRQn;	 
	NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

