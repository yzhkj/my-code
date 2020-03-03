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
	
 
u8 can_flag[4]={0x01,0x02,0x03,0x04};  //测试数组  
/************************************************
 ALIENTEK战舰STM32开发板实验26
 CAN通信实验
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/

static void CAN_NVIC_Configuration(void);
 int main(void)
 {	
	 	u8 count=0;
	u8* flag_point=can_flag;
	u8 mode=CAN_Mode_Normal;//CAN工作模式;CAN_Mode_Normal(0)：普通模式，CAN_Mode_LoopBack(1)：环回模式
	SystemInit ();
	delay_init();	    	 //延时函数初始化	
  CAN_NVIC_Configuration();	 
	LED_Init();		  		//初始化与LED连接的硬件接口	
	Adc_Init();
	TIM2_Int_Init(999,7999); 
  CAN_Mode_Init(CAN_SJW_1tq,CAN_BS2_7tq,CAN_BS1_8tq,9,mode);//CAN初始化环回模式,波特率500Kbps  
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

