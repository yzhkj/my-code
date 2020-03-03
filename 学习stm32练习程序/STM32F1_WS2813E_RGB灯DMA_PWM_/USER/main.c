#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "ws2812b.h"
/************************************************
 ALIENTEK精英STM32开发板实验1
 跑马灯实验
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/
uint8_t r[][3] = {255,0,0};
uint8_t g[][3] = {0,255,0};
uint8_t b[][3] = {0,0,255};
 int main(void)
 {	
	delay_init();	    //延时函数初始化	  
	LED_Init();		  	//初始化与LED连接的硬件接口
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



