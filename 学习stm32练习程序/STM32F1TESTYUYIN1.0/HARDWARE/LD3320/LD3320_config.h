#ifndef _LD3320_CONFIG_H__
#define _LD3320_CONFIG_H__


#include "stm32f1xx_hal.h"

///ʶ���루�ͻ��޸Ĵ���
#define CODE_LSD	1	 //��ˮ��
#define CODE_SS	  2	 //��˸
#define CODE_AJCF	3	 //��������
#define CODE_QM	  4	 //ȫ��
#define CODE_JT		5  //״̬







///LED������ض���
//#define LED1_PIN					GPIO_Pin_6
//#define LED1_GPIO_PORT				GPIOF
//#define LED1_GPIO_CLK				RCC_APB2Periph_GPIOF

//#define LED2_PIN					GPIO_Pin_7
//#define LED2_GPIO_PORT				GPIOF
//#define LED2_GPIO_CLK				RCC_APB2Periph_GPIOF

//#define LED3_PIN					GPIO_Pin_8
//#define LED3_GPIO_PORT				GPIOF
//#define LED3_GPIO_CLK				RCC_APB2Periph_GPIOF

//#define LED4_PIN					GPIO_Pin_9
//#define LED4_GPIO_PORT				GPIOF
//#define LED4_GPIO_CLK				RCC_APB2Periph_GPIOF

//#define LED1_ON()					GPIO_SetBits(GPIOF,GPIO_Pin_6)
//#define LED2_ON()					GPIO_SetBits(GPIOF,GPIO_Pin_7)
//#define LED3_ON()					GPIO_SetBits(GPIOF,GPIO_Pin_8)
//#define LED4_ON()					GPIO_SetBits(GPIOF,GPIO_Pin_9)

//#define LED1_OFF()					GPIO_ResetBits(GPIOF,GPIO_Pin_6)
//#define LED2_OFF()					GPIO_ResetBits(GPIOF,GPIO_Pin_7)
//#define LED3_OFF()					GPIO_ResetBits(GPIOF,GPIO_Pin_8)
//#define LED4_OFF()					GPIO_ResetBits(GPIOF,GPIO_Pin_9)

///LD3320������ض���
#define LD3320RST_PIN					GPIO_PIN_15		
#define LD3320RST_GPIO_PORT				GPIOB
//#define LD3320RST_GPIO_CLK				RCC_APB2Periph_GPIOB
#define LD_RST_H() 						HAL_GPIO_WritePin(GPIOB, LD3320RST_PIN,SET)
#define LD_RST_L() 						HAL_GPIO_WritePin(GPIOB, LD3320RST_PIN,RESET)

#define LD3320CS_PIN					GPIO_PIN_4		
#define LD3320CS_GPIO_PORT				GPIOA
//#define LD3320CS_GPIO_CLK	    		RCC_APB2Periph_GPIOA
#define LD_CS_H()						HAL_GPIO_WritePin(GPIOA, LD3320CS_PIN,SET)
#define LD_CS_L()						HAL_GPIO_WritePin(GPIOA, LD3320CS_PIN,RESET)
	
//#define LD3320IRQ_GPIO_CLK				RCC_APB2Periph_GPIOB
#define LD3320IRQ_PIN					GPIO_PIN_14
#define LD3320IRQ_GPIO_PORT				GPIOB
//#define LD3320IRQEXIT_PORTSOURCE		GPIO_PortSourceGPIOB
//#define LD3320IRQPINSOURCE				GPIO_PinSource12
//#define LD3320IRQEXITLINE				EXTI_Line12
//#define LD3320IRQN						EXTI15_10_IRQn

#define LD3320WR_PIN					GPIO_PIN_13
#define LD3320WR_GPIO_PORT				GPIOB
//#define LD3320WR_GPIO_CLK				RCC_APB2Periph_GPIOB
#define LD_SPIS_H()  					HAL_GPIO_WritePin(GPIOB, LD3320WR_PIN,SET)
#define LD_SPIS_L()  					HAL_GPIO_WritePin(GPIOB, LD3320WR_PIN,RESET)

//#define	LD3320SPI					SPI1
//#define LD3320SPI_CLK					RCC_APB2Periph_SPI1						

//#define LD3320SPIMISO_PIN				GPIO_PIN_6
//#define LD3320SPIMISO_GPIO_PORT		    GPIOA
//#define LD3320SPIMISO_GPIO_CLK		    RCC_APB2Periph_GPIOA

//#define LD3320SPIMOSI_PIN				GPIO_PIN_7
//#define LD3320SPIMOSI_GPIO_PORT		    GPIOA
//#define LD3320SPIMOSI_GPIO_CLK			RCC_APB2Periph_GPIOA

//#define LD3320SPISCK_PIN				GPIO_PIN_5
//#define LD3320SPISCK_GPIO_PORT			GPIOA
//#define LD3320SPISCK_GPIO_CLK			RCC_APB2Periph_GPIOA

#endif
