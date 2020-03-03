#ifndef _KEY_H
#define _KEY_H
//#include "sys.h"

#include "stm32f1xx_hal.h"
#include "main.h"

#include "config.h"


//下面的方式是通过位带操作方式读取IO
#define KEY0        PAin(10) //一号按键
#define KEY1        PAin(11) //二号按键
#define KEY2        PAin(9)  //三号按键
#define KEY3        PBin(14) //四号按键
#define KEY4        PAin(8)  //五号按键
#define KEY5        PBin(13) //六号按键
#define KEY6        PBin(15) //七号按键
#define KEY7        PBin(12) //八号按键
//下面的方式是通过直接操作HAL库函数方式读取IO
//#define KEY0        HAL_GPIO_ReadPin(GPIOH,GPIO_PIN_3)  //KEY0按键PH3
//#define KEY1        HAL_GPIO_ReadPin(GPIOH,GPIO_PIN_2)  //KEY1按键PH2
//#define KEY2        HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_13) //KEY2按键PC13
//#define WK_UP       HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)  //WKUP按键PA0


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


