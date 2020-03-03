	/******************** (C) COPYRIGHT  风驰嵌入式开发工作室 ********************
 * 文件名  ：main.c
 * 描述    ：STM32F0-LED       
 * 实验平台：M0-ISO开发板
 * 库版本  ：V1.3.0
 * 作者    ：风驰 QQ:779814207/2366260464
 * 博客    ：
 * 淘宝    ：http://shop71177993.taobao.com/
 * 修改时间: 2014-12-15
**********************************************************************************/	
/**
  ******************************************************************************
  * @file    iso_led.c 
  * @author  Fengchi  Technology Team
  * @version V1.3.0
  * @date    15-December-2014
  * @brief   led
  ******************************************************************************
  * @attention
  * LED1<----->PB3
  * LED2<----->PB4
	* LED3<----->PB5
  ******************************************************************************
  */
  
#include "iso_led.h"   

 /**
  * @brief  初始化控制LED的IO
  * @param  无
  * @retval 无
  */
void LED_GPIO_Config(void)
{		
		/*定义一个GPIO_InitTypeDef类型的结构体*/
		GPIO_InitTypeDef GPIO_InitStructure;

		/*开启GPIOB的外设时钟*/
		RCC_AHBPeriphClockCmd( RCC_AHBPeriph_GPIOB, ENABLE); 
	
		/*选择要控制的GPIOB引脚*/															   
		GPIO_InitStructure.GPIO_Pin = LED1|LED2|LED3;	

	  /*设置要控制的GPIOB引脚为输出模式*/	
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
	
		/*设置引脚速率为50MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

		/*设置引脚模式为通用推挽输出*/
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 

	  /*设置引脚模式为无上下拉*/
		GPIO_InitStructure.GPIO_PuPd   = GPIO_PuPd_NOPULL;  

		/*调用库函数，初始化GPIOB*/
		GPIO_Init(LEDPort, &GPIO_InitStructure);		  

		/* 关闭所有led灯	*/
		GPIO_SetBits(LEDPort, LED1|LED2|LED3);
}

static void LED_Delay(__IO uint32_t nCount)	 //简单的延时函数
{
	for(; nCount != 0; nCount--);
}

/*----------------------------------------------------------------*/
void LED_Test(void)
{
  
		ISO_LED(LED1,ON);		    // 亮
		LED_Delay(0x0FFFFF);
		ISO_LED(LED1,OFF);		  // 灭

		ISO_LED(LED2,ON);		    // 亮
		LED_Delay(0x0FFFFF);
		ISO_LED(LED2,OFF);		  // 灭

		ISO_LED(LED3,ON);		    // 亮
		LED_Delay(0x0FFFFF);
		ISO_LED(LED3,OFF);		  // 灭  

}


/*********************************************END OF FILE**********************/
