#include <msp430x14x.h>
//#include "hongwai.c"
#include "delay.h"



/**************��������***************/
void init(void);//ϵͳ��ʼ��
//void delay(unsigned int x);

//*******************���߼�*************//
void main(void)
{
  //unsigned int a;
  init();
  P2DIR = 0XFF;
//  delay_ms(100);
  P1DIR=0X0;
  
  while(1)
  {
    P2OUT &=~(BIT0+BIT2);   
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

}


