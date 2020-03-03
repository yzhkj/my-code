#include <msp430x14x.h>
//#include "delay.h"
#include "TA.c"
//#include "12864.c"
//#include "12864.h"




/**************函数声明***************/
//void init(void);//系统初始化
//void delay(unsigned int x);
//extern void TA_init(void);
//*******************主逻辑*************//
//void main(void)
/*{
 // init();
  while(1);
  
}*/

//*******************子函数***************//
//01、初始化函数
void init(void)
{
  unsigned char iq0;

  _DINT();//关全局中断
  BCSCTL1 &=~XT2OFF;  //开XT2
  do
  {
    IFG1 &= ~OFIFG; // 清除振荡器失效标志
    for (iq0 = 0xFF; iq0 > 0; iq0--);	// 延时，等待XT2起振
  }while ((IFG1 & OFIFG) != 0);		// 判断XT2是否起振
	
  BCSCTL2 = SELM_2 + SELS;           //MCLK,SMCLK时钟为XT2

  WDTCTL = WDTPW + WDTHOLD;//关闭看门狗
  
  P2DIR |=(BIT0+BIT1+BIT2+BIT3);
//  P2OUT &=~(BIT0+BIT1+BIT2+BIT3);
  TA_init();
}
}
