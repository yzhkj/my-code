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
  U0CTL = CHAR;   //����UAR0Ϊ8λ����
  U0TCTL = 0X31;  //���÷��ͼĴ�����ѡ��smclk
  U0BR1=0X03;    //U0BR0 U0BR1�����ò����ʵ�����λ
  U0BR0=0X41;
  U0MCTL=0X00;    //   UART0��ģʽѡ��
  ME1 |= URXE0;   //   UART0�Ľ���ʹ��
  IE1 |= UTXIE0+URXIE0;   //�����ͺͽ����ж�
  P3SEL |=BIT4 + BIT5;    //����p3.4��p3.5Ϊ���ù���
//  _EINT();         //�����ж�
  
  IFG1 &=~UTXIFG0;     //��������жϱ�־λ
  ME1 &=~UTXE0;  //�ر�TXD
  
}
void TA_init(void)
{
  _DINT();
  TACTL |= TASSEL_2 + ID_3 + TAIE + TACLR;  //TAʱ��Դ����Ƶϵ����ta�жϡ�ta���Ʒ���
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
  RDat=RXBUF0;   //���ջ�����������
  P2OUT=RXBUF0;
  RFlag=1;         //���ձ�־λ
}
#pragma vector=UART0TX_VECTOR
__interrupt void UARTT(void)
{
  P2OUT ^=BIT0;
  RDat=0;
  ME1 &=~UTXE0;//�ر�TXD
}
