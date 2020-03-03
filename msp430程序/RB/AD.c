#include  <msp430x14x.h>
#include "AD.H"           
unsigned char table[20]="0123456789abcdedfV";
unsigned char ptr[8];
unsigned char ptr1[8];
unsigned char flag=0;
unsigned char flag1=0;
/************************������****************************/

  
void adc12_init()
{
  P6SEL |= BIT0 + BIT1;                            // ʹ��ADCͨ��
  ADC12CTL0 = ADC12ON+SHT0_8+MSC;           // ��ADC�����ò���ʱ��
  ADC12CTL1 = SHP+CONSEQ_3; // ʹ�ò�����ʱ��
  ADC12MCTL0=INCH_0;
  ADC12MCTL1=INCH_1+EOS;
  ADC12IE |= BIT1;                           // ʹ��ADC�ж�
  ADC12CTL0 |= ENC;                         // ʹ��ת��
  ADC12CTL0 |= ADC12SC;                     // ��ʼת��
  _EINT();
}

/*******************************************
�������ƣ�ADC12ISR
��    �ܣ�ADC�жϷ��������������ö��ƽ����
          ����P6.0�ڵ�ģ���ѹ��ֵ
��    ������       
����ֵ  ����
********************************************/


     
#pragma vector=ADC_VECTOR
__interrupt void ADC12ISR (void)
{
  static unsigned int index = 0;
  static unsigned int index1 = 0;
  
  
  ADC12CTL0 &=~ADC12SC;    //��ͣת��

  results[index++] = ADC12MEM0;               // Move results
  results1[index1++] = ADC12MEM1;
  if(index == Num_of_Results)
  {
        unsigned char i;
        unsigned long sum = 0;
       // unsigned long sum1 = 0;
        index = 0;
      //  index1 = 0;
        for(i = 0; i < Num_of_Results; i++)
        {
            sum += results[i];
       //     sum1 += results1[i];
        }
        sum >>= 5;                            //����32
   //     sum1 >>= 5;
        Trans_val(sum);
        flag=1;
        Trans_val(ADC12MEM1);
        
          
  }
  flag1=1;
  ADC12CTL0 |= ADC12SC; 
}
            



             
/*******************************************
�������ƣ�Trans_val
��    �ܣ���16����ADCת�����ݱ任����λ10����
          ��ʵ��ģ���ѹ���ݣ�����Һ������ʾ
��    ����Hex_Val--16��������
          n--�任ʱ�ķ�ĸ����2��n�η�       
����ֵ  ����
********************************************/
void Trans_val(int Hex_val)
{
    unsigned long caltmp;
    unsigned int Curr_Volt;
    unsigned char t1,couter=0;//,i
  //  Hex_val=(Hex_val*8)/10;
    if(flag==0)
    {
      ptr[0]=Hex_val/1000 ;
      ptr[1]=Hex_val%1000/100 ;
      ptr[2]=Hex_val%1000%100/10 ;
      ptr[3]=Hex_val%1000%100%10/1;
    }
    else
    {
      ptr1[0]=Hex_val/1000 ;
      ptr1[1]=Hex_val%1000/100 ;
      ptr1[2]=Hex_val%1000%100/10 ;
      ptr1[3]=Hex_val%1000%100%10/1;
      flag=0;
    }
    // ptr[4]=Hex_val%100000%10000%1000%100/10 ;   
   // ptr[5]=Hex_val%100000%10000%1000%100%10/1 ;
    //ptr[0] = Hex_val / 1000;   
    //ptr[1] = '.';      
    //ptr[2] = (Hex_val - ptr[0]*1000)/100;
    //ptr[3] = (Hex_val - ptr[0]*1000 - ptr[1]*100)/10;
   // ptr[4] = (Hex_val - ptr[0]*1000 - ptr[1]*100 - ptr[2]*10); 
   // ptr[5] = (Hex_val - ptr[0]*1000 - ptr[1]*100 - ptr[2]*10-ptr[0]);
    
  /*  caltmp = Hex_val;
    caltmp = (caltmp << 5) + Hex_val;           //caltmp = Hex_Val * 33
    caltmp = (caltmp << 3) + (caltmp << 1);     //caltmp = caltmp * 10
    Curr_Volt = caltmp >> 12;                   //Curr_Volt = caltmp / 2^n
    
    

    ptr[0] = Curr_Volt / 100;                   //Hex->Dec�任
    t1 = Curr_Volt - (ptr[0] * 100);
    ptr[2] = t1 / 10;
    ptr[3] = t1 - (ptr[2] * 10);
   
    //ptr[4] = (t1 - ptr[0]*10 - ptr[2]*100-ptr[3]*1000); 
    //ptr[5] = (t1 - ptr[4]*1000 - ptr[3]*100 - ptr[2]*10);
     ptr[1] = '.';  
    //shuzi���е�10λ��Ӧ����"."
    */
   // Display(Hex_val);
 /*   Display_number(1,0,ptr[0]);
    Display(1,1,".");    
    Display_number(1,2,ptr[1]);
    Display_number(1,3,ptr[2]);
    Display_number(1,4,ptr[3]);
    Display_number(1,5,ptr[4]);
    Display_number(1,6,ptr[5]);*/
   // for(couter=0;couter<=5;couter++)
    //Disp_HZ(0x80+couter,table+ptr[couter],1);
   // Disp_HZ(0x80,(ptr+1),8);
}


   /*
void adc12_init(void)
{ 
  //��Ƭ�����Ŷ˿�����
  P6SEL |= BIT0 + BIT1 + BIT2; // ����ADͨ��
  
  ADC12CTL0 = ADC12ON + MSC + SHT0_15;     // ��ADC12, ��β�������λ���ã���������ʱ��
  ADC12CTL1 = SHP + CONSEQ_3;     // ���������ź�ѡ��������ֶ�ʱ��, ��ͨ�����ת��
  ADC12MCTL0 = INCH_0;       // ref+=AVcc, channel = A0
  ADC12MCTL1 = INCH_1;      // ref+=AVcc, channel = A1
  ADC12MCTL2 = INCH_2+EOS;   // ref+=AVcc, channel = A2����������һ��
  ADC12IE = BIT2;      // ʹ��A2ת������ж�
  ADC12CTL0 |= ENC;   // ʹ��ת��
  ADC12CTL0 |= ADC12SC;   // ��ʼת��
  _EINT();
}

//02��ADC12�жϷ����ӳ���
#pragma vector=ADC_VECTOR
__interrupt void ADC12_ISR (void)
{
  ADC12CTL0 &= ~ADC12SC;//��ʱֹͣת��
  
  ADC12A0 = ADC12MEM0;
  ADC12A1 = ADC12MEM1;
  ADC12A2 = ADC12MEM2;

  ADC12CTL0 |= ADC12SC; 
  
}
      */