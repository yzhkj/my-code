#include <msp430x14x.h>
#include "lcd12864.h"
#include "lcd12864.c"
//#include "ADC12_some.c"
#include "delay.h"


extern unsigned int ADC12A0,ADC12A1,ADC12A2;

/**************函数声明***************/
void init(void);//系统初始化
extern void ADC12_init(void);
void TA_PWM_init(void);
void TB_PWM_init(void);
void TIAOSU_X(void);
void TIAOSU_Y(void);
void IO_init(void);
void display(void);

//*******************主逻辑*************//
void main(void)
{
  init();
  lcd12864_init();
//  ADC12_init();
//  TA_PWM_init();
//  TB_PWM_init();
  IO_init();
  
  
  lcd12864_display_string(1,1,"通道0:       ");
//  lcd12864_display_string(3,1,"通道1:       ");
  lcd12864_display_string(2,1,"通道1:       ");
  lcd12864_display_string(3,1,"X 轴速度:       ");
  lcd12864_display_string(4,1,"Y 轴速度:       ");

  for(;;)
 {
    display();
    TIAOSU_X();
    TIAOSU_Y();
    //delay_mds(500);
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
	
  BCSCTL2 =SELM_2 + SELS;                      //MCLK,SMCLK时钟为XT2

  WDTCTL = WDTPW + WDTHOLD;//关闭看门狗
  
//  lcd12864_init();
//  ADC12_init();
//  TA_PWM_init();
  
}


void IO_init(void)
{
   P1DIR &=~(BIT0+BIT1+BIT3+BIT4);    
   P1IES |= BIT0+BIT1+BIT3+BIT4;   //上升沿
   P1IE |= BIT0+BIT1+BIT3+BIT4;
  // P5DIR = 0X0F;
   _EINT();           //开总中断
}


#pragma vector=PORT1_VECTOR
__interrupt void PORT1_INT()
{ 
    switch(P1IFG)
    {
      case BIT0:
   //     P5OUT |=BIT0;
        P1IFG &=~BIT0;
        break;
      case BIT1:
   //     P5OUT |=BIT1;
        P1IFG &=~BIT1;
        break;
      case BIT2:
   //     P5OUT |=BIT2;
        P1IFG &=~BIT2;
        break;
      case BIT3:
   //     P5OUT |=BIT3;
        P1IFG &=~BIT3;
        break;
        
    }
   
     
}
void TA_PWM_init(void)
{
  TACTL = TASSEL_2 + ID_3 + TACLR;  //根据所确定的系统时钟频率设定定时器A的计数频率                   
  TACCR0  = 20000; //设定PWM波的周期初始值，以确定频率
  TACCR1  = 5000; //设定PWM波的占空比初始值
  TACCR2 =  5000;
//  TACCTL0 = OUTMOD_7;
  TACCTL1 = OUTMOD_7;   //PWM波模式
//  TACCTL2 = OUTMOD_7;
  
  P1DIR |= BIT2;
  P1SEL |= BIT2;

  

  EN1_OUT_1;  //0使能有效
  
  TACTL |= MC_1;//增计数模式 
}
void TB_PWM_init(void)
{
  TBCTL = TBSSEL_2 + ID_3 + TBCLR;  //根据所确定的系统时钟频率设定定时器A的计数频率                   
  TBCCR0  = 20000; //设定PWM波的周期初始值，以确定频率
  TBCCR1  = 5000; //设定PWM波的占空比初始值
//  TBCCR2 =  5000;
 // TBCCTL0 = OUTMOD_7;
  TBCCTL1 = OUTMOD_7;   //PWM波模式
 // TBCCTL2 = OUTMOD_7;
  
  P4DIR |= BIT1;
  P4SEL |= BIT1;
 /* P4DIR |= BIT1;
  P4SEL |= BIT1;
  P4DIR |= BIT2;
  P4SEL |= BIT2;
 */ 
  
  TBCTL |= MC_1;//增计数模式 
}
void display(void)
{
  lcd12864_display_TwoNum(1,5,ADC12A0%10000/100);
    lcd12864_display_TwoNum(1,6,ADC12A0%10000%100); //模拟通道1
    
 //   lcd12864_display_TwoNum(3,5,ADC12A1%10000/100);
 //   lcd12864_display_TwoNum(3,6,ADC12A1%10000%100);
    
    lcd12864_display_TwoNum(2,5,ADC12A2%10000/100);
    lcd12864_display_TwoNum(2,6,ADC12A2%10000%100);  //模拟通道2
    
    lcd12864_display_TwoNum(3,6,TACCR0%10000/100);    //TACCR0 当前值
    lcd12864_display_TwoNum(4,6,TBCCR0%10000/100);    //TBCCR0 当前值
}
void TIAOSU_X(void)
{
    unsigned char flag=0;
    SETOUT_EN1;
    SETOUT_DIR1;
    if(ADC12A0<2000)
    {
      EN1_OUT_0;
      DIR1_OUT_1;
      flag=0;
      if(ADC12A0<1000)
      {
        flag=1;
        if(ADC12A0<400)
          flag=2;    
      }  
    }     
    if(ADC12A0>2600)
    { 
      EN1_OUT_0;
      DIR1_OUT_0;
      flag=0;
      if(ADC12A0>3300)
      {
        flag=1;
        if(ADC12A0>3500)
          flag=2;
      }  
    }
    switch(flag)
    {
      case 0 : TACCR0  = 8000; //周期
               TACCR1  = 4000; //空比初始值
               break;
      case 1 : TACCR0  = 6000; //周期
               TACCR1  = 3000; //空比初始值
               break;
      case 2 : TACCR0  = 4000; //周期
               TACCR1  = 1000; //空比初始值
               break;
    }   
     
    if(ADC12A0>2000 && ADC12A0 < 2600) 
    {
      EN1_OUT_1;
    }
  
}

void TIAOSU_Y(void)
{
    unsigned char flag=0;
    SETOUT_EN2;
    SETOUT_DIR2;
    if(ADC12A2<2000)
    {
      EN2_OUT_0;
      DIR2_OUT_1;
      flag=0;
      if(ADC12A2<1000)
      {
        flag=1;
        if(ADC12A2<400)
          flag=2;
        
      }  
    }     
    if(ADC12A2>2600)
    { 
      EN2_OUT_0;
      DIR2_OUT_0;
      flag=0;
      if(ADC12A2>3300)
      {
        flag=1;
        if(ADC12A2>4000)
          flag=2;
        
      }  
    }
    if(ADC12A2>2000 && ADC12A2 < 2600) 
    {
      EN2_OUT_1;
    }
    switch(flag)
    {
      case 0 : TBCCR0  = 8000; //周期
               TBCCR1  = 4000; //空比初始值
               break;
      case 1 : TBCCR0  = 6000; //周期
               TBCCR1  = 3000; //空比初始值
               break;
      case 2 : TBCCR0  = 2000; //周期
               TBCCR1  = 1000; //空比初始值
               break;
    }   
    
  
}