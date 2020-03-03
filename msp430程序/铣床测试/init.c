#include <msp430X14x.h>


void initf(void)
{
   unsigned char iq0;
   
   _DINT();
   BCSCTL1 &=~XT2OFF;   //开xt2
   do
   {
     IFG1 &=~OFIFG;
     for(iq0=0XFF;iq0>0;iq0--);
   }
   while((IFG1&OFIFG) != 0);
   BCSCTL2 = SELM_2 + SELS;
   WDTCTL = WDTPW + WDTHOLD;
}
void PWM_INIT()
{ 
    TACTL |= TASSEL_2 + ID_3 + TACLR;
    TACCR0 = 20000;
    TACCR1 = 500;
    TACCR2 = 500;
    TACCTL1 |= OUTMOD_7;
    TACCTL2 |= OUTMOD_7;
    P1DIR |= BIT2;
    P1SEL |=BIT2;
    P1DIR |=BIT3;
    P1SEL |=BIT3;
    TACTL |= MC_1; 
  //  P2OUT=0XFF;  
}
/*
  TACTL = TASSEL_2 + ID_3 + TACLR;  //根据所确定的系统时钟频率设定定时器A的计数频率                   
  TACCR0  = 50000; //设定PWM波的周期初始值，以确定频率
  TACCR1  = 25000; //设定PWM波的占空比初始值
  TACCR2 = 10000;
  TACCTL1 = OUTMOD_7;   //PWM波模式
  TACCTL2 = OUTMOD_7;
  
  P1DIR |= BIT2;
  P1SEL |= BIT2;
  P1DIR |= BIT3;
  P1SEL |= BIT3;
  
  TACTL |= MC_1;//增计数模式 */