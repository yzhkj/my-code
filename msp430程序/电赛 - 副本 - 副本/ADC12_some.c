#include "ADC12.h"

void ADC12_init(void)
{ 
  //��Ƭ�����Ŷ˿�����
  P6SEL |= BIT0 + BIT1 + BIT2;              // ����ADͨ��  
  ADC12CTL0 = ADC12ON + MSC + SHT0_15;     // ��ADC12, ��β�������λ���ã���������ʱ��
  ADC12CTL1 = SHP + CONSEQ_3;              // ���������ź�ѡ��������ֶ�ʱ��, ��ͨ�����ת��
  ADC12MCTL0 = INCH_0;                     // ref+=AVcc, channel = A0
  ADC12MCTL1 = INCH_1;                     // ref+=AVcc, channel = A1
  ADC12MCTL2 = INCH_2+EOS;                 // ref+=AVcc, channel = A2����������һ��
  ADC12IE = BIT2;                           // ʹ��A2ת������ж�
  ADC12CTL0 |= ENC;                         // ʹ��ת��
  ADC12CTL0 |= ADC12SC;                     // ��ʼת��
  _EINT();
}

#pragma vector=ADC_VECTOR
__interrupt void ADC12_ISR (void)
{
  ADC12CTL0 &= ~ADC12SC;                    //��ʱֹͣת��
  
  ADC12A0 = ADC12MEM0;
  ADC12A1 = ADC12MEM1;
  ADC12A2 = ADC12MEM2;

  ADC12CTL0 |= ADC12SC; 
  
}

