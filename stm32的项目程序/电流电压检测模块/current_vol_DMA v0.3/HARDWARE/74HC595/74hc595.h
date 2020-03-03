#ifndef __74HC595_H__
#define __74HC595_H__

#include "stm32f1xx_hal.h"
#include "main.h"
#include "config.h"

//串行数据输入,74HC595数据接口14
#define	HC595_DATA_PIN    	    GPIO_PIN_7
#define HC595_DATA_GPIO         GPIOA
#define HC595_DATA_GPIO_CLK     RCC_APB2Periph_GPIOA
#define HC595_DATA_H()          GPIOA->BSRR = HC595_DATA_PIN
#define HC595_DATA_L()		    GPIOA->BRR  = HC595_DATA_PIN



//移位,时钟脉冲信号——上升沿有效,74HC595数据接口11
#define	HC595_CLK_PIN    	    GPIO_PIN_5
#define HC595_CLK_GPIO          GPIOA
#define HC595_CLK_GPIO_CLK      RCC_APB2Periph_GPIOA
#define HC595_CLK_H()           GPIOA->BSRR = HC595_CLK_PIN
#define HC595_CLK_L()		    GPIOA->BRR  = HC595_CLK_PIN

//锁存,打入信号————上升沿有效,74HC595数据接口12
#define	HC595_CS_PIN    	    GPIO_PIN_4
#define HC595_CS_GPIO           GPIOA
#define HC595_CS_GPIO_CLK       RCC_APB2Periph_GPIOA
#define HC595_CS_H()            GPIOA->BSRR = HC595_CS_PIN
#define HC595_CS_L()		    GPIOA->BRR  = HC595_CS_PIN


//数码管位置定义  按先后顺序
#define one_pos 	3
#define two_pos 	4
#define three_pos   5
#define four_pos 	6
#define five_pos    0
#define six_pos 	1
#define seven_pos 	2


void HC595Init(void);
void HC595Send(u8 data);
void DispNum(unsigned char * N);


#endif

