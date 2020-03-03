#include <msp430x14x.h>
#include "lcd12864.h"
#include "lcd12864.c"
#include "ADC12_some.c"
#include "delay.h"



extern unsigned int ADC12A0,ADC12A1,ADC12A2;

/**************��������***************/
void init(void);//ϵͳ��ʼ��
extern void ADC12_init(void);
void TA_PWM_init(void);
void TB_PWM_init(void);
void TIAOSU_X(void);
void TIAOSU_Y(void);
void display(void);
void IO_init(void);
void wdt_init(void);


//*******************���߼�*************//
void main(void)
{

  init(); 
  ADC12_init();
  TA_PWM_init();
  TB_PWM_init();
  lcd12864_init();
  IO_init();
//  wdt_init(); 
  lcd12864_display_string(1,1,"ͨ��0:       ");

  lcd12864_display_string(2,1,"ͨ��1:       ");
  lcd12864_display_string(3,1,"X ���ٶ�:       ");
  lcd12864_display_string(4,1,"Y ���ٶ�:       ");

  for(;;)
 {
    display();
    TIAOSU_X();
    TIAOSU_Y();
 //   delay_ms(500);
//    wdt_clear();

  }
}


//*******************�Ӻ���***************//
//01����ʼ������
void init(void)
{
  unsigned char iq0;
  WDTCTL = WDTPW + WDTHOLD;//�رտ��Ź�
  _DINT();//��ȫ���ж�
  BCSCTL1 &=~XT2OFF;  //��XT2
  do
  {
    IFG1 &= ~OFIFG; // �������ʧЧ��־
    for (iq0 = 0xFF; iq0 > 0; iq0--);	// ��ʱ���ȴ�XT2����
  }while ((IFG1 & OFIFG) != 0);		// �ж�XT2�Ƿ�����
	
  BCSCTL2 =SELM_2 + SELS;                      //MCLK,SMCLKʱ��ΪXT2

  
 // WDTCTL = WDT_MRST_1000;    //1000ms��λ
  
//  lcd12864_init();
//  ADC12_init();
//  TA_PWM_init();
  
}



void TA_PWM_init(void)
{
  TACTL = TASSEL_2 + ID_3 + TACLR;  //������ȷ����ϵͳʱ��Ƶ���趨��ʱ��A�ļ���Ƶ��                   
  TACCR0  = 20000; //�趨PWM�������ڳ�ʼֵ����ȷ��Ƶ��
  TACCR1  = 10000; //�趨PWM����ռ�ձȳ�ʼֵ
//  TACCR2 =  5000;
//  TACCTL0 = OUTMOD_7;
  TACCTL1 = OUTMOD_7;   //PWM��ģʽ
//  TACCTL2 = OUTMOD_7;
  
  P1DIR |= BIT2;
  P1SEL |= BIT2;

  

  EN1_OUT_1;  //0ʹ����Ч
  
  TACTL |= MC_1;//������ģʽ 
}
void TB_PWM_init(void)
{
  TBCTL = TBSSEL_2 + ID_3 + TBCLR;  //������ȷ����ϵͳʱ��Ƶ���趨��ʱ��A�ļ���Ƶ��                   
  TBCCR0  = 20000; //�趨PWM�������ڳ�ʼֵ����ȷ��Ƶ��
  TBCCR1  = 10000; //�趨PWM����ռ�ձȳ�ʼֵ
  TBCCR2 =  10000;
 // TBCCTL0 = OUTMOD_7;
  TBCCTL1 = OUTMOD_7;   //PWM��ģʽ
  TBCCTL2 = OUTMOD_7;
  
  P4DIR |= BIT1;
  P4SEL |= BIT1;
 /* P4DIR |= BIT1;
  P4SEL |= BIT1;
  */
  P4DIR |= BIT2;
  P4SEL |= BIT2;
  
  
  TBCTL |= MC_1;//������ģʽ 
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
      case 0 : TACCR0  = 8000; //����
               TACCR1  = 4000; //�ձȳ�ʼֵ
               break;
      case 1 : TACCR0  = 6000; //����
               TACCR1  = 3000; //�ձȳ�ʼֵ
               break;
      case 2 : TACCR0  =10000; //����
               TACCR1  = 8000; //�ձȳ�ʼֵ
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
      case 0 : TBCCR0  = 8000; //����
               TBCCR1  = 6000; //�ձȳ�ʼֵ
               break;
      case 1 : TBCCR0  = 5000; //����
               TBCCR1  = 3000; //�ձȳ�ʼֵ
           
               break;
      case 2 : TBCCR0  = 2000; //����
               TBCCR1  = 1500; //�ձȳ�ʼֵ
            
               break;
    }   
    
  
}

void display(void)
{
  lcd12864_display_TwoNum(1,5,ADC12A0%10000/100);
    lcd12864_display_TwoNum(1,6,ADC12A0%10000%100); //ģ��ͨ��1
    
 //   lcd12864_display_TwoNum(3,5,ADC12A1%10000/100);
 //   lcd12864_display_TwoNum(3,6,ADC12A1%10000%100);
    
    lcd12864_display_TwoNum(2,5,ADC12A2%10000/100);
    lcd12864_display_TwoNum(2,6,ADC12A2%10000%100);  //ģ��ͨ��2
    
    lcd12864_display_TwoNum(3,6,TACCR0%10000/100);    //TACCR0 ��ǰֵ
    lcd12864_display_TwoNum(3,7,TACCR0%10000%100);    //TACCR0 ��ǰֵ
    lcd12864_display_TwoNum(4,6,TBCCR0%10000/100);    //TBCCR0 ��ǰֵ
    lcd12864_display_TwoNum(4,7,TBCCR0%10000%100);    //TBCCR0 ��ǰֵ
}

void IO_init(void)
{
   P2DIR &=~(BIT0+BIT1);
   P2IES &=~(BIT0+BIT1);     //�½���  ���������ж�
   P2IE |= BIT0+BIT1;
   
   
   P2DIR &=~(BIT4+BIT5+BIT6+BIT7);    
   P2IES |= BIT4+BIT5+BIT6+BIT7;   //������   ��λʹ�õ��ж�io
   P2IE |= BIT4+BIT5+BIT6+BIT7;
 //  P2REN &=~ (BIT4+BIT5+BIT6+BIT7);  //������������ f1ϵ������������
   P2IFG=0X0;
   P5DIR |=BIT5+BIT7;
   P5OUT &=~BIT7;   //p5.6  5.7 ��ʼ�͵�ƽ  �ߵ�ƽ��Ч
   P5OUT |= BIT5;
   _EINT();           //�����ж�
   
}
/*
void wdt_init(void)
{ 
  WDTCTL = WDTPW +  WDTCNTCL + WDTIS0 ;   // ���Ź���ʼ��
  IE1 |= WDTIE;   //�����Ź��ж�
  
}

#pragma vector=PORT2_VECTOR
__interrupt void PORT2_INT()
{ 
    switch(P2IFG)    //��ť�����ж� p2.2����ֱ�����  p2.3�л����
    {
      case BIT0 : 
        delay_ms(5);    //��������
        
        while((P2IN&BIT0)==0X0) ;  //�ȴ������ɿ�
        P5OUT ^= BIT7;
        P2IFG &=~BIT0;
        break;
      case BIT1 :  
        delay_ms(5);    //��������
        
        while((P2IN&BIT1)==0X0) ;    //�ȴ������ɿ�      
        P5OUT ^= BIT5;
        P2IFG &=~BIT1;
        break;
        case BIT4:     //�����ĸ���λ
        EN2_OUT_1;  EN1_OUT_1;  //�رղ���ʹ��
        while((P2IN&BIT4)!=0x0);
        P2IFG &=~BIT4;
        break;
       case BIT5:
        EN2_OUT_1;  EN1_OUT_1;  //�رղ���ʹ��
        while((P2IN&BIT5)!=0x0);
        P2IFG &=~BIT5;
        break;
      case BIT6:
        EN2_OUT_1;  EN1_OUT_1;  //�رղ���ʹ��       
       while((P2IN&BIT6)!=0x0);
        P2IFG &=~BIT6;
        break;
      case BIT7:
        EN2_OUT_1;  EN1_OUT_1;  //�رղ���ʹ��
        while((P2IN&BIT7)!=0x0);
        P2IFG &=~BIT7;
        break; 
    }
}

#pragma vector = WDT_VECTOR
__interrupt void WDT_ISR(void)
{
  WDTCTL |= WDTPW + WDTCNTCL;  //���Ź���λ
}

  */