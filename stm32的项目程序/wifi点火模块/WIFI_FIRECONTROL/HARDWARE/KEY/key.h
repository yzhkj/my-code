#ifndef _KEY_H
#define _KEY_H
//#include "sys.h"

#include "stm32f1xx_hal.h"
#include "main.h"

#include "config.h"


//����ķ�ʽ��ͨ��λ��������ʽ��ȡIO
#define KEY0        PAin(10) //һ�Ű���
#define KEY1        PAin(11) //���Ű���
#define KEY2        PAin(9)  //���Ű���
#define KEY3        PBin(14) //�ĺŰ���
#define KEY4        PAin(8)  //��Ű���
#define KEY5        PBin(13) //���Ű���
#define KEY6        PBin(15) //�ߺŰ���
#define KEY7        PBin(12) //�˺Ű���
//����ķ�ʽ��ͨ��ֱ�Ӳ���HAL�⺯����ʽ��ȡIO
//#define KEY0        HAL_GPIO_ReadPin(GPIOH,GPIO_PIN_3)  //KEY0����PH3
//#define KEY1        HAL_GPIO_ReadPin(GPIOH,GPIO_PIN_2)  //KEY1����PH2
//#define KEY2        HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_13) //KEY2����PC13
//#define WK_UP       HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)  //WKUP����PA0


#define NONE_PRES   0x00
#define KEY0_PRES 	0x01
#define KEY1_PRES	0x02
#define KEY2_PRES	0x04
#define KEY3_PRES   0x08
#define KEY4_PRES 	0x10
#define KEY5_PRES	0x20
#define KEY6_PRES	0x40
#define KEY7_PRES   0x80

#define NONE_STATE  0xaa
//void KEY_Init(void);


void Get_Keyval(void);
void Key_filter(void);
u8 KEY_Scan(u8 mode);



#endif


