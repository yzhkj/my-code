#include <msp430X14x.h>


void initf(void)
{
   unsigned char iq0;
   
   _DINT();
   BCSCTL1 &=~XT2OFF;   //��xt2
   do
   {
     IFG1 &=~OFIFG;
     for(iq0=0XFF;iq0>0;iq0--);
   }
   while((IFG1&OFIFG) != 0);
   BCSCTL2 = SELM_2 + SELS;
   WDTCTL = WDTPW + WDTHOLD;
}
   /*
void PWM_INIT(void)
{
    TBCTL |= TBSSEL_2 + ID_3 + TBCLR;
    TBCCR0 = 20000;
    TBCCR1 = 1500;
    TBCCR2 = 1500;
    TBCCR3 = 1500;
    TBCCR4 = 1500;
    TBCCR5 = 1500;
    TBCCTL1 |= OUTMOD_7;
    TBCCTL2 |= OUTMOD_7;
    TBCCTL3 |= OUTMOD_7;
    TBCCTL4 |= OUTMOD_7;
    TBCCTL5 |= OUTMOD_7;
    
    P4DIR |= BIT1+BIT2+BIT3+BIT4+BIT5;
    P1SEL |=BIT1+BIT2+BIT3+BIT4+BIT5;
   // P1DIR |=BIT3;
   // P1SEL |=BIT3;
    TBCTL |= MC_1; 
    
     
}

   */ 
void PWM_INIT(void)
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
    
     
}
    /*

  TACTL = TASSEL_2 + ID_3 + TACLR;  //������ȷ����ϵͳʱ��Ƶ���趨��ʱ��A�ļ���Ƶ��                   
  TACCR0  = 50000; //�趨PWM�������ڳ�ʼֵ����ȷ��Ƶ��
  TACCR1  = 25000; //�趨PWM����ռ�ձȳ�ʼֵ
  TACCR2 = 10000;
  TACCTL1 = OUTMOD_7;   //PWM��ģʽ
  TACCTL2 = OUTMOD_7;
  
  P1DIR |= BIT2;
  P1SEL |= BIT2;
  P1DIR |= BIT3;
  P1SEL |= BIT3;
  
  TACTL |= MC_1;//������ģʽ */