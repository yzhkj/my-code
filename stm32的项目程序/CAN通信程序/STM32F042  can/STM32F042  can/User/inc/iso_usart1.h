#ifndef __ISO_USART1_H
#define	__ISO_USART1_H

#include "stm32f0xx.h"
#include <stdio.h>
typedef enum
{
  USART1_TX   = GPIO_Pin_9, 
  USART1_RX   = GPIO_Pin_10
}ISO_USART1_TypeDef;

#define Max_DMA_USART_Buffer_Len  128
#define Letter_Len    26
extern u16 g_DMA_CurrDataCount;
extern uint8_t g_DMA_USART_Buffer[Max_DMA_USART_Buffer_Len];
void USART1_Config(void);
void AutoBauRate_StartBitMethod(void);
void NVIC_Configuration(void);
int fputc(int ch, FILE *f);
int fgetc(FILE *f);

#endif /* __ISO_USART1_H */
