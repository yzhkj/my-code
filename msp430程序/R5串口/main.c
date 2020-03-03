#include <msp430x14x.h>
#include "init.c"
 
void initf();
void serialinit(void);

unsigned char RDat=0;
unsigned char RFlag=0;

void main()
{
  initf();
  serialinit();
  P2DIR=0XFF;
  P2OUT=0;
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
  _EINT();         //开总中断
  
  IFG1 &=~UTXIFG0;     //清除发送中断标志位
  ME1 &=~UTXE0;  //关闭TXD
  
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
