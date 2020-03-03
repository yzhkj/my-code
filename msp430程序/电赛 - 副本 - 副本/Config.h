#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "delay.h"

///////////////����ң��
#define RED_IN	        P1DIR &= ~BIT5	//�������룬�������ͷ�ӵ�Ƭ��PE3��
#define RED_OUT	        P1DIR |=  BIT5	//�������
#define RED_L	        P1OUT &= ~BIT5	//�õ͵�ƽ
#define RED_H	        P1OUT |= BIT5   //�øߵ�ƽ
#define RED_R	        (P1IN & BIT5)	//����ƽ

 
//***********************************************************************
//			ң��������
//***********************************************************************

#define KEY_0     0x16                 //��0
#define KEY_1     0x0C                 //��1
#define KEY_2     0x18                 //��2
#define KEY_3     0x5E                 //��3
#define KEY_4     0x08                 //��4
#define KEY_5     0x1C                 //��5
#define KEY_6     0x5A                 //��6
#define KEY_7     0x42                 //��7
#define KEY_8     0x52                 //��8
#define KEY_9     0x4A                 //��9
#define KEY11     0x45                 //  CH-
#define KEY12     0x46                 //  CH
#define KEY13     0x47                 //  CH+
#define KEY14     0x44                 //  |<<
#define KEY15     0x40                 //  >>|
#define KEY16     0x43                 //  >||
#define KEY17     0x07                 //  -
#define KEY18     0x15                 //  +
#define KEY19     0xd9                 //  EQ
#define KEY20     0x19                 //  100+
#define KEY21     0x0d                 //  200+

void Key_Icode(void);
void Red_Code();

#endif














 