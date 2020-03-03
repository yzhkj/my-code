#include <msp430x14x.h>
#include "lcd12864.h"
#include "lcd12864.c"
#include "ADC12_some.c"
#include "delay.h"



extern unsigned int ADC12A0,ADC12A1,ADC12A2;

/**************函数声明***************/
void init(void);//系统初始化
extern void ADC12_init(void);
void TA_PWM_init(void);
void TB_PWM_init(void);
void TIAOSU_X(void);
void TIAOSU_Y(void);
void display(void);
void IO_init(void);
void wdt_init(void);


//*******************主逻辑*************//
void main(void)
{

  init(); 
  ADC12_init();
  TA_PWM_init();
  TB_PWM_init();
  lcd12864_init();
  IO_init();
//  wdt_init(); 
  lcd12864_display_string(1,1,"通道0:       ");

  lcd12864_display_string(2,1,"通道1:       ");
  lcd12864_display_string(3,1,"X 轴速度:       ");
  lcd12864_display_string(4,1,"Y 轴速度:       ");

  for(;;)
 {
    display();
    TIAOSU_X();
    TIAOSU_Y();
 //   delay_ms(500);
//    wdt_clear();

  }
}


//*******************子函数***************//
//01、初始化函数
void init(void)
{
  unsigned char iq0;
  WDTCTL = WDTPW + WDTHOLD;//关闭看门狗
  _DINT();//关全局中断
  BCSCTL1 &=~XT2OFF;  //开XT2
  do
  {
    IFG1 &= ~OFIFG; // 清除振荡器失效标志
    for (iq0 = 0xFF; iq0 > 0; iq0--);	// 延时，等待XT2起振
  }while ((IFG1 & OFIFG) != 0);		// 判断XT2是否起振
	
  BCSCTL2 =SELM_2 + SELS;                      //MCLK,SMCLK时钟为XT2

  
 // WDTCTL = WDT_MRST_1000;    //1000ms复位
  
//  lcd12864_init();
//  ADC12_init();
//  TA_PWM_init();
  
}



void TA_PWM_init(void)
{
  TACTL = TASSEL_2 + ID_3 + TACLR;  //根据所确定的系统时钟频率设定定时器A的计数频率                   
  TACCR0  = 20000; //设定PWM波的周期初始值，以确定频率
  TACCR1  = 10000; //设定PWM波的占空比初始值
//  TACCR2 =  5000;
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
  TBCCR1  = 10000; //设定PWM波的占空比初始值
  TBCCR2 =  10000;
 // TBCCTL0 = OUTMOD_7;
  TBCCTL1 = OUTMOD_7;   //PWM波模式
  TBCCTL2 = OUTMOD_7;
  
  P4DIR |= BIT1;
  P4SEL |= BIT1;
 /* P4DIR |= BIT1;
  P4SEL |= BIT1;
  */
  P4DIR |= BIT2;
  P4SEL |= BIT2;
  
  
  TBCTL |= MC_1;//增计数模式 
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
      case 2 : TACCR0  =10000; //周期
               TACCR1  = 8000; //空比初始值
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
               TBCCR1  = 6000; //空比初始值
               break;
      case 1 : TBCCR0  = 5000; //周期
               TBCCR1  = 3000; //空比初始值
           
               break;
      case 2 : TBCCR0  = 2000; //周期
               TBCCR1  = 1500; //空比初始值
            
               break;
    }   
    
  
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
    lcd12864_display_TwoNum(3,7,TACCR0%10000%100);    //TACCR0 当前值
    lcd12864_display_TwoNum(4,6,TBCCR0%10000/100);    //TBCCR0 当前值
    lcd12864_display_TwoNum(4,7,TBCCR0%10000%100);    //TBCCR0 当前值
}

void IO_init(void)
{
   P2DIR &=~(BIT0+BIT1);
   P2IES &=~(BIT0+BIT1);     //下降沿  按键开关中断
   P2IE |= BIT0+BIT1;
   
   
   P2DIR &=~(BIT4+BIT5+BIT6+BIT7);    
   P2IES |= BIT4+BIT5+BIT6+BIT7;   //上升沿   限位使用的中断io
   P2IE |= BIT4+BIT5+BIT6+BIT7;
 //  P2REN &=~ (BIT4+BIT5+BIT6+BIT7);  //加上下拉电阻 f1系列无上拉电阻
   P2IFG=0X0;
   P5DIR |=BIT5+BIT7;
   P5OUT &=~BIT7;   //p5.6  5.7 初始低电平  高电平有效
   P5OUT |= BIT5;
   _EINT();           //开总中断
   
}
/*
void wdt_init(void)
{ 
  WDTCTL = WDTPW +  WDTCNTCL + WDTIS0 ;   // 看门狗初始化
  IE1 |= WDTIE;   //开看门狗中断
  
}

#pragma vector=PORT2_VECTOR
__interrupt void PORT2_INT()
{ 
    switch(P2IFG)    //按钮进入中断 p2.2开启直流电机  p2.3切换电机
    {
      case BIT0 : 
        delay_ms(5);    //消除抖动
        
        while((P2IN&BIT0)==0X0) ;  //等待按键松开
        P5OUT ^= BIT7;
        P2IFG &=~BIT0;
        break;
      case BIT1 :  
        delay_ms(5);    //消除抖动
        
        while((P2IN&BIT1)==0X0) ;    //等待按键松开      
        P5OUT ^= BIT5;
        P2IFG &=~BIT1;
        break;
        case BIT4:     //以下四个限位
        EN2_OUT_1;  EN1_OUT_1;  //关闭步进使能
        while((P2IN&BIT4)!=0x0);
        P2IFG &=~BIT4;
        break;
       case BIT5:
        EN2_OUT_1;  EN1_OUT_1;  //关闭步进使能
        while((P2IN&BIT5)!=0x0);
        P2IFG &=~BIT5;
        break;
      case BIT6:
        EN2_OUT_1;  EN1_OUT_1;  //关闭步进使能       
       while((P2IN&BIT6)!=0x0);
        P2IFG &=~BIT6;
        break;
      case BIT7:
        EN2_OUT_1;  EN1_OUT_1;  //关闭步进使能
        while((P2IN&BIT7)!=0x0);
        P2IFG &=~BIT7;
        break; 
    }
}

#pragma vector = WDT_VECTOR
__interrupt void WDT_ISR(void)
{
  WDTCTL |= WDTPW + WDTCNTCL;  //看门狗复位
}

  */