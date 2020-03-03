#include <msp430x14x.h>
#include "lcd12864.h"
//#include "Config.h"

#define uchar unsigned char
#define uint  unsigned int
#define N 3
#define buchang 60              //补偿高度值

unsigned int ADC12A0,ADC12A1,ADC12A2;
//unsigned char RDat=0;
//unsigned char RFlag=0;
unsigned char mode=0;          //模式设置
unsigned char counter0=0;
uchar miao;                     //秒
float ek,ek1,ek2,u1,u;         //pid函数过程量
float Kp,Ki=0.05,Kd;           //pid函数参数
float distance,vol;            
 
/**************函数声明***************/
void init(void);                //系统初始化
uchar key_scan(void);
void TA_PWM_init(void);
void serialinit(void);
void ADC12_init(void);
void dis_init(void);
int filter(void);
void PID_Control(float sv,float fy);
void TB_init(void);

void main(void)
{
  float temp;
  unsigned int temp1,pwm,sum;
  unsigned char i,mode;
  init(); 
  ADC12_init();  
  lcd12864_init();
  lcd12864_display_string(1,1,"通道:          ");
  lcd12864_display_string(2,1,"电压:   .   V  ");
  lcd12864_display_string(3,1,"距离:   .   cm ");
  lcd12864_display_string(4,1,"kp:     kd:    ");
  for(i=0;i<7;i++)                              //无刷启动等待
  {
    TACCR1=TACCR1+40;
    delay_ms(500);
  }
  P1DIR &= ~BIT0;
  P2DIR |=  BIT0;
  TA_PWM_init();
//  TB_init();
  while(1)
 {
    dis_init();
    mode=key_scan();
/*    switch(mode)
    {
      case 0:
        break;
        
      case 1:
//        sv=35;
        break;
      
      case 2:
//        sv=10;
        break;
        
      default:
        break;
    }
 */ 
    PID_Control(38,buchang-distance);      //设定为25cm    
    temp=u; 
    temp=temp/100*40;
    TACCR1=(int)temp+1040;
    delay_ms(30);
  }
}
void init(void)
{
  unsigned char iq0;
  WDTCTL = WDTPW + WDTHOLD;     //关闭看门狗
  _DINT();                      //关全局中断
  BCSCTL1 &=~XT2OFF;            //开XT2
  do
  {
    IFG1 &= ~OFIFG;                     // 清除振荡器失效标志
    for (iq0 = 0xFF; iq0 > 0; iq0--);	// 延时，等待XT2起振
  }while ((IFG1 & OFIFG) != 0);		// 判断XT2是否起振
	
  BCSCTL2 =SELM_2 + SELS;               //MCLK,SMCLK时钟为XT2
 
}
uchar key_scan(void)
{
  uchar mode1;
  if(P1IN==BIT0)
    {
      delay_ms(10);
      if(P1IN==BIT0)
      {
        mode1++;
        mode1%=3;        
      }
    }
    return mode1;
}
void TA_PWM_init(void)
{
  TACTL = TASSEL_2 + ID_3 + TACLR;      //根据所确定的系统时钟频率设定定时器A的计数频率                   
  TACCR0  = 20000;                      //设定PWM波的周期初始值，以确定频率
  TACCR1  = 1000;                      //设定PWM波的占空比初始值
  TACCTL1 = OUTMOD_7;                   //PWM波模式  
  P1DIR |= BIT2;
  P1SEL |= BIT2;
//  EN1_OUT_1;                            //0使能有效  
  TACTL |= MC_1;                        //增计数模式 
}

void serialinit(void)
{
  U0CTL = CHAR;         //设置UAR0为8位数据
  U0TCTL = 0X31;        //设置发送寄存器，选择smclk
  U0BR1=0X03;           //U0BR0 U0BR1，设置波特率的整数位
  U0BR0=0X41;
  U0MCTL=0X00;          //   UART0的模式选择
  ME1 |= URXE0;         //   UART0的接收使能
  IE1 |= UTXIE0+URXIE0; //开发送和接收中断
  P3SEL |=BIT4 + BIT5;  //设置p3.4和p3.5为复用功能
  _EINT();              //开总中断
  
  IFG1 &=~UTXIFG0;      //清除发送中断标志位
  ME1 &=~UTXE0;         //关闭TXD
  
}
void ADC12_init(void)
{ 
  //单片机引脚端口配置
  P6SEL |= BIT0 + BIT1 + BIT2;             // 设置AD通道  
  ADC12CTL0 = ADC12ON + MSC + SHT0_15;     // 打开ADC12, 多次采样控制位设置，采样保持时间
  ADC12CTL1 = SHP + CONSEQ_3;              // 采样保持信号选择采样保持定时器, 多通道多次转换
  ADC12MCTL0 = INCH_0;                     // ref+=AVcc, channel = A0
  ADC12MCTL1 = INCH_1;                     // ref+=AVcc, channel = A1
  ADC12MCTL2 = INCH_2+EOS;                 // ref+=AVcc, channel = A2，序列最后的一个
  ADC12IE = BIT2;                           // 使能A2转换完成中断
  ADC12CTL0 |= ENC;                         // 使能转换
  ADC12CTL0 |= ADC12SC;                     // 开始转换
  _EINT();
}
void dis_init(void)
{
    float temp;
    unsigned int temp1;
    temp=ADC12A0;
    Kp=temp/4096*10;
    temp1=(int)(Kp*10);
    lcd12864_display_TwoNum(4,3,temp1%10000%100);

    temp=ADC12A1;
    Kd=temp/4096*10;
    temp1=(int)(Kd*10); 
    lcd12864_display_TwoNum(4,7,temp1%10000%100);
    
    lcd12864_display_TwoNum(1,4,ADC12A2%10000/100);
    lcd12864_display_TwoNum(1,5,ADC12A2%10000%100); //模拟通道1  
    
    temp=ADC12A2;          //滤波
    vol=temp/4096*3.3;      //实际电压
    temp1=(int)(vol*100);
    lcd12864_display_TwoNum(2,4,temp1%10000/100);    //显示电压
    lcd12864_display_TwoNum(2,6,temp1%10000%100);       

    distance=(21423.97/(vol*1000-150.0));            //实际距离
    temp1=(int)(buchang*100-distance*100);
    lcd12864_display_TwoNum(3,4,temp1%10000/100);
    lcd12864_display_TwoNum(3,6,temp1%10000%100); 
}
void dis_init2(void)          //输入采样
{
    float temp;
    unsigned int temp1;
    temp=ADC12A2;          //滤波
    vol=temp/4096*3.3;      //实际电压
    temp1=(int)(vol*100);
    lcd12864_display_TwoNum(2,4,temp1%10000/100);    //显示电压
    lcd12864_display_TwoNum(2,6,temp1%10000%100);       

    distance=(21423.97/(vol*1000-150.0));            //实际距离
    temp1=(int)(buchang*100-distance*100);
    lcd12864_display_TwoNum(3,4,temp1%10000/100);
    lcd12864_display_TwoNum(3,6,temp1%10000%100); 
}
int filter(void)
{
   char count,i,j;
   int value_buf[N],temp;
   int  sum=0;
   for  (count=0;count<N;count++)
   {
      value_buf[count] = ADC12A2;
      delay_ms(40);
   }
   for (j=0;j<N-1;j++)
   {
      for (i=0;i<N-j;i++)
      {
         if ( value_buf[i]>value_buf[i+1] )
         {
            temp = value_buf[i];
            value_buf[i] = value_buf[i+1]; 
             value_buf[i+1] = temp;
         }
      }
   }
   for(count=1;count<N-1;count++)
      sum += value_buf[count];
   return (int)(sum/(N-2));
}
void PID_Control(float sv,float fy)
{
  float pError=0,iError=0,dError=0; 
  ek=sv-fy;
  pError=ek-ek1;		//比例误差(等于当前误差减去前一次的误差)
  iError=ek+ek1+ek2;			//积分误差(等于当前误差值)
  dError=ek-ek1*2+ek2;	        //微分误差(等于当前误差减去前一次2倍误差再加上前两次的误差)	
  ek2=ek1;	                //储存前两次的误差值
  ek1=ek;	                //储存前一次的误差值	
  u=(float)(Kp*pError+Ki*iError+Kd*dError+u1);	//获取PID调节的误差值
//  if(u>30) u=30;
//  if(u<16) u=18;
  if(u>100) u=100;
  u1=u;		                //储存前一次的输出值
}
void TB_init(void)
{
  TBCTL |= TBSSEL_2 + ID_3 + TBIE + TBCLR;  //TA时钟源、分频系数、ta中断、ta控制方向
  TBCCTL0 = CCIE;
  TBCCTL1 = CCIE;
  TBCCR0 = 50000;
  _EINT();
  TBCTL |=MC_1;
}
#pragma vector = TIMERB0_VECTOR
__interrupt void Timer_B0(void)
{  
  counter0++;
  if(counter0>=20)
  {
    counter0=0;
    miao++;
    P2OUT^=BIT0;
//    if(miao>60)
//      miao=0;
  }
}
#pragma vector=ADC_VECTOR
__interrupt void ADC12_ISR (void)
{
  ADC12CTL0 &= ~ADC12SC;                    //暂时停止转换
  
  ADC12A0 = ADC12MEM0;
  ADC12A1 = ADC12MEM1;
  ADC12A2 = ADC12MEM2;

  ADC12CTL0 |= ADC12SC; 
  
}
/*
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

*/



/*
void TB_PWM_init(void)
{
  TBCTL = TBSSEL_2 + ID_3 + TBCLR;  //根据所确定的系统时钟频率设定定时器A的计数频率                   
  TBCCR0  = 20000;                  //设定PWM波的周期初始值，以确定频率
  TBCCR1  = 10000;                  //设定PWM波的占空比初始值
  TBCCR2 =  10000;
 // TBCCTL0 = OUTMOD_7;
  TBCCTL1 = OUTMOD_7;   //PWM波模式
  TBCCTL2 = OUTMOD_7;
  
  P4DIR |= BIT1;
  P4SEL |= BIT1;
 // P4DIR |= BIT1;
 // P4SEL |= BIT1;
  
  P4DIR |= BIT2;
  P4SEL |= BIT2;
  
  
  TBCTL |= MC_1;//增计数模式 
}

*/
/*

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

*/

/*

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

*/
/*

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
*/
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