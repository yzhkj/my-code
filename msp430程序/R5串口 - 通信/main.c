#include <msp430x14x.h>
#include "init.c"
 
void initf();
void serialinit(void);
void TA_init(void);

unsigned char RDat=0;
unsigned char RFlag=0;
unsigned char miao;

void main()
{
  initf();
  serialinit();
  TA_init();
  _EINT();
  P2DIR=0XFF;
  P2OUT=0xff;
  while(1)
  {
    if(RFlag==1)
    {
      RFlag=0;
      TXBUF0=RDat;
      ME1 |=UTXE0;
    }
  }

}
void serialinit(void)
{
  U0CTL = CHAR;   //设置UAR0为8位数据
  U0TCTL = 0X31;  //设置发送寄存器，选择smclk
  U0BR1=0X03;    //U0BR0 U0BR1，设置波特率的整数位
  U0BR0=0X41;
  U0MCTL=0X00;    //   UART0的模式选择
  ME1 |= URXE0;   //   UART0的接收使能
  IE1 |= UTXIE0+URXIE0;   //开发送和接收中断
  P3SEL |=BIT4 + BIT5;    //设置p3.4和p3.5为复用功能
//  _EINT();         //开总中断
  
  IFG1 &=~UTXIFG0;     //清除发送中断标志位
  ME1 &=~UTXE0;  //关闭TXD
  
}
void TA_init(void)
{
  _DINT();
  TACTL |= TASSEL_2 + ID_3 + TAIE + TACLR;  //TA时钟源、分频系数、ta中断、ta控制方向
  TACCTL0 = CCIE;
  TACCR0 = 50000;
//  _EINT();
  TACTL |=MC_1;
}
#pragma vector = TIMERA0_VECTOR
__interrupt void Timer_A0(void)
{
  static unsigned char counter0;
  counter0++;
  if(counter0>50)
  {
    counter0=0;
    miao++;
//    TXBUF0=miao;
    P2OUT^=BIT0;
    if(miao>60)
      miao=0;
  }
}
#pragma vector=UART0RX_VECTOR
__interrupt void UARTR(void)
{
  RDat=RXBUF0;   //接收缓冲区的数据
  P2OUT=RXBUF0;
  RFlag=1;         //接收标志位
}
#pragma vector=UART0TX_VECTOR
__interrupt void UARTT(void)
{
  P2OUT ^=BIT0;
  RDat=0;
  ME1 &=~UTXE0;//关闭TXD
}
