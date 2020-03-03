#ifndef __LED_H
#define __LED_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//LED��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/2
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 


void LED_Init(void);//��ʼ��

#define CtrlGPIOToggle(GPIO_Port,i)	{GPIO_Port->ODR ^=i;}			//�����ת״̬


/* �������IO�ĺ� */
#define LED1_TOGGLE		CtrlGPIOToggle(GPIOB,GPIO_Pin_1)
#define PA1_TOGGLE		CtrlGPIOToggle(GPIOA,GPIO_Pin_1)
#define PA2_TOGGLE		CtrlGPIOToggle(GPIOA,GPIO_Pin_2)
		 				    
#endif

