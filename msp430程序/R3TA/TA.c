#include <msp430x14x.h>

void TA_init(void)
{
  TACTL |= TASSEL_2 + ID_3 + TAIE + TACLR;  //TA时钟源、分频系数、ta中断、ta控制方向
  TACCTL0 = CCIE;
  TACCTL1 = CCIE;
  TACCR0 = 50000;
  TACCR1 = 10000;
  _EINT();
  TACTL |=MC_1;
}
#pragma vector = TIMERA0_VECTOR
__interrupt void Timer_A0(void)
{
  static unsigned char counter0=0;
  
  TACCR1=10000;
  
  
  counter0++;
  if(counter0>=100)
  {
    P2OUT ^= BIT0;
    counter0=0;
  }
}
#pragma vector=TIMERA1_VECTOR
__interrupt void Timer_A1(void)
{
    static unsigned char counter1=0;
    static unsigned char counter2=0;
    switch(TAIV)
    {
      case TAIV_TAIFG:         
           counter1++;
        if(counter1>=100)
          {
            P2OUT ^=BIT1;
            counter1=0;
          }
           break;
  
      case TAIV_TACCR1:
           TACCR1+=10000;
           counter2++;
           if(counter2>=5)
               {
                   P2OUT ^= BIT2;
                   counter2=0;
               }
            break;
    }
}
