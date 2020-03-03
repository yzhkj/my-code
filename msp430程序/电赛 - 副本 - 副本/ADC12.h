#ifndef __ADC12_H__
#define __ADC12_H__

#include <msp430x14x.h>

unsigned int ADC12A0=0,ADC12A1=0,ADC12A2=0;
__interrupt void ADC12_ISR (void);
void ADC12_init(void);

#endif