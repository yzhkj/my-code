#include <msp430x14x.h>
#include "init.h"
void init()
{
  unsigned char iq0;
  _DINT();   //�����ж�
  BCSCTL1 &= ~XT2OFF;  //��xt2
  do
  {
    IFG1 &=~OFIFG;   //�������ʧЧ��־
    for(iq0=0xff;iq0>0;iq0--); 
  }
  while((IFG1&OFIFG)!=0);   //�ж��Ƿ�����
  BCSCTL2 = SELM_2 + SELS;   //MCLK  SMCLKΪXT2
  WDTCTL = WDTPW + WDTHOLD;  //�ؿ��Ź�
  //TA_init();
}