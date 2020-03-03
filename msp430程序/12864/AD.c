#include  <msp430x14x.h>
#include "AD.H"
#define   Num_of_Results   32


static unsigned int results[Num_of_Results];    //保存ADC转换结果的数组                                                     // is not used for anything.
void Trans_val(int Hex_Val); 

unsigned char ADC12A0;
unsigned char ADC12A1;

unsigned char ptr[8];
unsigned char ptr1[8];


/************************主函数****************************/
void adc12_init()
{
  //单片机引脚端口配置
  P6SEL |= BIT0 + BIT1; // 设置AD通道
  
  ADC12CTL0 = ADC12ON + MSC + SHT0_8;     // 打开ADC12, 多次采样控制位设置，采样保持时间
  ADC12CTL1 = SHP + CONSEQ_3;     // 采样保持信号选择采样保持定时器, 多通道多次转换
  ADC12MCTL0 = INCH_0;       // ref+=AVcc, channel = A0
  ADC12MCTL1 = INCH_1+EOS;      // ref+=AVcc, channel = A1
//  ADC12MCTL2 = INCH_2+EOS;   // ref+=AVcc, channel = A2，序列最后的一个
  ADC12IE = BIT1;      // 使能A2转换完成中断
  ADC12CTL0 |= ENC;   // 使能转换
  ADC12CTL0 |= ADC12SC;   // 开始转换
  _EINT();
  
  /*
  P6SEL |= BIT0+BIT1;                            // 使能ADC通道
  ADC12CTL0 = ADC12ON+SHT0_8+MSC;           // 打开ADC，设置采样时间
  ADC12CTL1 = SHP+CONSEQ_2;                 // 使用采样定时器
  ADC12MCTL0 = INCH_0;       // ref+=AVcc, channel = A0
  ADC12MCTL1 = INCH_1+EOS;
  ADC12IE = BIT2;                           // 使能ADC中断
  ADC12CTL0 |= ENC;                         // 使能转换
  ADC12CTL0 |= ADC12SC;                     // 开始转换
  _EINT();
  */
}

/*******************************************
函数名称：ADC12ISR
功    能：ADC中断服务函数，在这里用多次平均的
          计算P6.0口的模拟电压数值
参    数：无       
返回值  ：无
********************************************/
#pragma vector=ADC_VECTOR
__interrupt void ADC12ISR (void)
{
  static unsigned int index = 0;
  index++;
  ADC12A0= ADC12MEM0;// Move results
  ADC12A1= ADC12MEM1;
  if(index == Num_of_Results)
  {
    index=0;
  //  ADC12A0= ADC12MEM0;// Move results
  //  ADC12A1= ADC12MEM1;
     /*   unsigned char i;
        unsigned long sum = 0;

        index = 0;
        for(i = 0; i < Num_of_Results; i++)
        {
            sum += results[i];
        }
        sum >>= 5;                            //除以32
        
        Trans_val(sum);
        Trans_val(ADC12MEM1);
      */
    //    Trans_val(ADC12MEM0);
    //    Trans_val(ADC12MEM1);
  }
  
       /* ADC12CTL0 &=~ADC12SC;
        Trans_val(ADC12MEM0);
        Trans_val(ADC12MEM1);
        ADC12CTL0 &=~ADC12SC;
      */
}

/*******************************************
函数名称：Trans_val
功    能：将16进制ADC转换数据变换成三位10进制
          真实的模拟电压数据，并在液晶上显示
参    数：Hex_Val--16进制数据
          n--变换时的分母等于2的n次方       
返回值  ：无
********************************************/
void Trans_val(    int Hex_val)
{   
  //  unsigned long caltmp;
  //  unsigned int Curr_Volt;
  //  unsigned char t1;//,i
  //  Hex_val=(Hex_val*8)/10;   
  //  ptr[0]=Hex_val/100000 ;
  //  ptr[1]=Hex_val%100000/10000 ;
    ptr[2]=Hex_val%100000%10000/1000 ;
    ptr[3]=Hex_val%100000%10000%1000/100 ;
    ptr[4]=Hex_val%100000%10000%1000%100/10 ;   
    ptr[5]=Hex_val%100000%10000%1000%100%10/1 ;
    
    ptr1[2]=Hex_val%100000%10000/1000 ;
    ptr1[3]=Hex_val%100000%10000%1000/100 ;
    ptr1[4]=Hex_val%100000%10000%1000%100/10 ;   
    ptr1[5]=Hex_val%100000%10000%1000%100%10/1 ;
    //ptr[0] = Hex_val / 1000;   
    //ptr[1] = '.';      
    //ptr[2] = (Hex_val - ptr[0]*1000)/100;
    //ptr[3] = (Hex_val - ptr[0]*1000 - ptr[1]*100)/10;
   // ptr[4] = (Hex_val - ptr[0]*1000 - ptr[1]*100 - ptr[2]*10); 
   // ptr[5] = (Hex_val - ptr[0]*1000 - ptr[1]*100 - ptr[2]*10-ptr[0]);
    
   // caltmp = Hex_val;
   // caltmp = (caltmp << 5) + Hex_val;           //caltmp = Hex_Val * 33
   // caltmp = (caltmp << 3) + (caltmp << 1);     //caltmp = caltmp * 10
   // Curr_Volt = caltmp >> 12;                   //Curr_Volt = caltmp / 2^n
    
    /*

    ptr[0] = Curr_Volt / 100;                   //Hex->Dec变换
    t1 = Curr_Volt - (ptr[0] * 100);
    ptr[2] = t1 / 10;
    ptr[3] = t1 - (ptr[2] * 10);
   
    //ptr[4] = (t1 - ptr[0]*10 - ptr[2]*100-ptr[3]*1000); 
    //ptr[5] = (t1 - ptr[4]*1000 - ptr[3]*100 - ptr[2]*10);
     ptr[1] = '.';  
    //shuzi表中第10位对应符号"."
    */
   // Display(Hex_val);
   /* Display_number(1,0,ptr[0]);
    Display(1,1,".");    
    Display_number(1,2,ptr[1]);
    Display_number(1,3,ptr[2]);
    Display_number(1,4,ptr[3]);
    Display_number(1,5,ptr[4]);
     Display_number(1,6,ptr[5]);
   */
}
