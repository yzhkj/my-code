#include "msp430x14x.h"
#include "delay.h"
//引脚定义
#define SetOut_TRIG                             (P6DIR |= BIT0) //触发信号
#define TRIG_Out_1                              (P6OUT |= BIT0)
#define TRIG_Out_0                              (P6OUT &= ~BIT0)

#define SetIn_ECHO                              (P1DIR &= ~BIT1) 
#define ECHO_Status                             (P1IN&BIT1)

unsigned int data=0;
unsigned char flag=0; 

void TACAP_init(void)
{
  SetOut_TRIG;
  SetIn_ECHO;
  
  TRIG_Out_0;
  
  P1DIR &= ~BIT1;
  P1SEL |= BIT1;                             // Set P1.5 to TA0
  TACTL = TASSEL_2 + ID_3 + TACLR;
  TACCTL0 |= CM_3 + CCIS_0 + SCS + CAP + CCIE; 
  
  _EINT();
}

long HC_SR04(void)
{ 
  TRIG_Out_1;
  flag = 0;
  TACTL |= MC_2;
  delay_ms(1);
  TRIG_Out_0;
  
  while(!(flag == 2));
  TACTL |= MC_0; 
  TAR=0;

  return(data * 21.5 + 0.5);
}

#pragma v
ector=TIMERA0_VECTOR
__interrupt void TimerA0(void)
{
  if(flag == 0)
  {
    data = TACCR0;
    flag = 1;
  }
  else if(flag == 1)
  {
    data = TACCR0 - data;
    flag = 2;
  }
}