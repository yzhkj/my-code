#include <msp430x14x.h>
#include "delay.h"

//中断函数，当按下p1.0按键，触发中断对p2.7取反

/**************函数声明***************/
void init(void);//系统初始化
void delay(unsigned int x);
void IO_init(void);
//void PORT1_INT(void);

//*******************主逻辑*************//
void main(void)
{  
   init();
   IO_init(); 
  while(1)
  {
    
             
  }
}

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
  P2DIR |= BIT0;
  P2OUT &=~BIT0;
  delay_ms(100);
}

void IO_init(void)
{
   P1DIR &=~BIT0;
   P1IES |= BIT0;   //上升沿
   P1IE |= BIT0;
   P2DIR |= BIT7;
   _EINT();           //开总中断
} 
#pragma vector=PORT1_VECTOR
__interrupt void PORT1_INT()
{ 
    P2OUT ^= BIT7;
    P1IFG &=~BIT0;
    //delay_ms(100);  
}
