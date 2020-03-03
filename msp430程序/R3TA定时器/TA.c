#include <msp430x14x.h>


void TA_init(void)
{
  TACTL |= TASSEL_2 + ID_3 + TAIE + TACLR;//TAʱ��Դ����Ƶϵ����TA�жϡ�TA���Ʒ���λ
  
  TACCTL0 |= CCIE;//��TACCR0�ж�
  TACCTL1 |= CCIE;
  TACCTL2 |= CCIE;
  TACCR0 = 50000;//��TACCR0��ֵ
  TACCR1 = 10000;            
  TACCR2 = 10000;
  
  _EINT();//�����ж�
  
  TACTL |= MC_1;//TA����ģʽ
}

// TimerA TACCR0 interrupt service routine
#pragma vector=TIMERA0_VECTOR
__interrupt void Timer_A0(void)
{
  static unsigned char counter0=0;
  
  TACCR1 = 10000;            
  TACCR2 = 10000;

  counter0++;
  if(counter0 >= 20)
  {
    P2OUT ^= BIT0;
    counter0 = 0;
  }
}
// Timer TACCR1~TACCR2 TAIFG interrupt service routine
#pragma vector=TIMERA1_VECTOR
__interrupt void Timer_A1(void)
{
  static unsigned char counter1=0;
  static unsigned int counter2=0;
  static unsigned char counter3=0;
  switch( TAIV )
  {
    case  TAIV_TAIFG: 
             counter3++;
             if(counter3 >= 80)
             {
                counter3 = 0;
                P2OUT ^= BIT3;
             }
             break;
    case  TAIV_TACCR1:
             TACCR1 += 10000;
             counter1++;
             if(counter1 >= 200)
             {
                counter1 = 0;
                P2OUT ^= BIT1;
             }
             break;
    case TAIV_TACCR2: 
             TACCR2 += 10000;
             counter2++;
             if(counter2 >= 300)
             {
                counter2 = 0;
                P2OUT ^= BIT2;
             }     
             break;
  }