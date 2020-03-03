	/******************** (C) COPYRIGHT  ���Ƕ��ʽ���������� ********************
 * �ļ���  ��main.c
 * ����    ��STM32F0-LED       
 * ʵ��ƽ̨��M0-ISO������
 * ��汾  ��V1.3.0
 * ����    ����� QQ:779814207/2366260464
 * ����    ��
 * �Ա�    ��http://shop71177993.taobao.com/
 * �޸�ʱ��: 2014-12-15
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
  * @brief  ��ʼ������LED��IO
  * @param  ��
  * @retval ��
  */
void LED_GPIO_Config(void)
{		
		/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
		GPIO_InitTypeDef GPIO_InitStructure;

		/*����GPIOB������ʱ��*/
		RCC_AHBPeriphClockCmd( RCC_AHBPeriph_GPIOB, ENABLE); 
	
		/*ѡ��Ҫ���Ƶ�GPIOB����*/															   
		GPIO_InitStructure.GPIO_Pin = LED1|LED2|LED3;	

	  /*����Ҫ���Ƶ�GPIOB����Ϊ���ģʽ*/	
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
	
		/*������������Ϊ50MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

		/*��������ģʽΪͨ���������*/
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 

	  /*��������ģʽΪ��������*/
		GPIO_InitStructure.GPIO_PuPd   = GPIO_PuPd_NOPULL;  

		/*���ÿ⺯������ʼ��GPIOB*/
		GPIO_Init(LEDPort, &GPIO_InitStructure);		  

		/* �ر�����led��	*/
		GPIO_SetBits(LEDPort, LED1|LED2|LED3);
}

static void LED_Delay(__IO uint32_t nCount)	 //�򵥵���ʱ����
{
	for(; nCount != 0; nCount--);
}

/*----------------------------------------------------------------*/
void LED_Test(void)
{
  
		ISO_LED(LED1,ON);		    // ��
		LED_Delay(0x0FFFFF);
		ISO_LED(LED1,OFF);		  // ��

		ISO_LED(LED2,ON);		    // ��
		LED_Delay(0x0FFFFF);
		ISO_LED(LED2,OFF);		  // ��

		ISO_LED(LED3,ON);		    // ��
		LED_Delay(0x0FFFFF);
		ISO_LED(LED3,OFF);		  // ��  

}


/*********************************************END OF FILE**********************/
