#include <msp430x14x.h>
//#include "delay.h"
#include "TA.c"
//#include "12864.c"
//#include "12864.h"




/**************��������***************/
//void init(void);//ϵͳ��ʼ��
//void delay(unsigned int x);
//extern void TA_init(void);
//*******************���߼�*************//
//void main(void)
/*{
 // init();
  while(1);
  
}*/

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
  
  P2DIR |=(BIT0+BIT1+BIT2+BIT3);
//  P2OUT &=~(BIT0+BIT1+BIT2+BIT3);
  TA_init();
}
}
