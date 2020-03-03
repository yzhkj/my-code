#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "ws2812b.h"
/************************************************
 ALIENTEK��ӢSTM32������ʵ��1
 �����ʵ��
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/
uint8_t r[][3] = {255,0,0};
uint8_t g[][3] = {0,255,0};
uint8_t b[][3] = {0,0,255};
 int main(void)
 {	
	delay_init();	    //��ʱ������ʼ��	  
	LED_Init();		  	//��ʼ����LED���ӵ�Ӳ���ӿ�
  Timer2_init();
	 
	while(1)
	{
		WS2812_send(r,8);
		delay_ms(1000);
		WS2812_send(g,8);
		delay_ms(1000);
		WS2812_send(b,8);
		delay_ms(1000);
	}
 }



