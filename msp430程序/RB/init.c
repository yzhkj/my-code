#include <msp430x14x.h>
#include "init.h"
void init()
{
  unsigned char iq0;
  _DINT();   //关总中断
  BCSCTL1 &= ~XT2OFF;  //开xt2
  do
  {
    IFG1 &=~OFIFG;   //清除振荡器失效标志
    for(iq0=0xff;iq0>0;iq0--); 
  }
  while((IFG1&OFIFG)!=0);   //判断是否启振
  BCSCTL2 = SELM_2 + SELS;   //MCLK  SMCLK为XT2
  WDTCTL = WDTPW + WDTHOLD;  //关看门狗
  //TA_init();
}