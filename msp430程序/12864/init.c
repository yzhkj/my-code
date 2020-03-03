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
void TA_PWM_init(void)
{
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
  
  TACTL |= MC_1;//������ģʽ 
}
