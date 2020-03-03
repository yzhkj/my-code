#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "delay.h"

///////////////红外遥控
#define RED_IN	        P1DIR &= ~BIT5	//设置输入，红外接收头接单片机PE3口
#define RED_OUT	        P1DIR |=  BIT5	//设置输出
#define RED_L	        P1OUT &= ~BIT5	//置低电平
#define RED_H	        P1OUT |= BIT5   //置高电平
#define RED_R	        (P1IN & BIT5)	//读电平

 
//***********************************************************************
//			遥控器键码
//***********************************************************************

#define KEY_0     0x16                 //键0
#define KEY_1     0x0C                 //键1
#define KEY_2     0x18                 //键2
#define KEY_3     0x5E                 //键3
#define KEY_4     0x08                 //键4
#define KEY_5     0x1C                 //键5
#define KEY_6     0x5A                 //键6
#define KEY_7     0x42                 //键7
#define KEY_8     0x52                 //键8
#define KEY_9     0x4A                 //键9
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














 