#include "ADC12.h"

void ADC12_init(void)
{ 
  //单片机引脚端口配置
  P6SEL |= BIT0 + BIT1 + BIT2;              // 设置AD通道  
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

#pragma vector=ADC_VECTOR
__interrupt void ADC12_ISR (void)
{
  ADC12CTL0 &= ~ADC12SC;                    //暂时停止转换
  
  ADC12A0 = ADC12MEM0;
  ADC12A1 = ADC12MEM1;
  ADC12A2 = ADC12MEM2;

  ADC12CTL0 |= ADC12SC; 
  
}

