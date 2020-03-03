#include <msp430x14x.h>
#include "delay.h"

//�жϺ�����������p1.0�����������ж϶�p2.7ȡ��

/**************��������***************/
void init(void);//ϵͳ��ʼ��
void delay(unsigned int x);
void IO_init(void);
//void PORT1_INT(void);

//*******************���߼�*************//
void main(void)
{  
   init();
   IO_init(); 
  while(1)
  {
    
             
  }
}

//*******************�Ӻ���***************//
//01����ʼ������
void init(void)
{
  unsigned char iq0;

  _DINT();//��ȫ���ж�
  BCSCTL1 &=~XT2OFF;  //��XT2
  do
  {
    IFG1 &= ~OFIFG; // �������ʧЧ��־
    for (iq0 = 0xFF; iq0 > 0; iq0--);	// ��ʱ���ȴ�XT2����
  }while ((IFG1 & OFIFG) != 0);		// �ж�XT2�Ƿ�����
	
  BCSCTL2 = SELM_2 + SELS;           //MCLK,SMCLKʱ��ΪXT2

  WDTCTL = WDTPW + WDTHOLD;//�رտ��Ź�
  P2DIR |= BIT0;
  P2OUT &=~BIT0;
  delay_ms(100);
}

void IO_init(void)
{
   P1DIR &=~BIT0;
   P1IES |= BIT0;   //������
   P1IE |= BIT0;
   P2DIR |= BIT7;
   _EINT();           //�����ж�
} 
#pragma vector=PORT1_VECTOR
__interrupt void PORT1_INT()
{ 
    P2OUT ^= BIT7;
    P1IFG &=~BIT0;
    //delay_ms(100);  
}
