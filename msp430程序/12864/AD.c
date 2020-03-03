#include  <msp430x14x.h>
#include "AD.H"
#define   Num_of_Results   32


static unsigned int results[Num_of_Results];    //����ADCת�����������                                                     // is not used for anything.
void Trans_val(int Hex_Val); 

unsigned char ADC12A0;
unsigned char ADC12A1;

unsigned char ptr[8];
unsigned char ptr1[8];


/************************������****************************/
void adc12_init()
{
  //��Ƭ�����Ŷ˿�����
  P6SEL |= BIT0 + BIT1; // ����ADͨ��
  
  ADC12CTL0 = ADC12ON + MSC + SHT0_8;     // ��ADC12, ��β�������λ���ã���������ʱ��
  ADC12CTL1 = SHP + CONSEQ_3;     // ���������ź�ѡ��������ֶ�ʱ��, ��ͨ�����ת��
  ADC12MCTL0 = INCH_0;       // ref+=AVcc, channel = A0
  ADC12MCTL1 = INCH_1+EOS;      // ref+=AVcc, channel = A1
//  ADC12MCTL2 = INCH_2+EOS;   // ref+=AVcc, channel = A2����������һ��
  ADC12IE = BIT1;      // ʹ��A2ת������ж�
  ADC12CTL0 |= ENC;   // ʹ��ת��
  ADC12CTL0 |= ADC12SC;   // ��ʼת��
  _EINT();
  
  /*
  P6SEL |= BIT0+BIT1;                            // ʹ��ADCͨ��
  ADC12CTL0 = ADC12ON+SHT0_8+MSC;           // ��ADC�����ò���ʱ��
  ADC12CTL1 = SHP+CONSEQ_2;                 // ʹ�ò�����ʱ��
  ADC12MCTL0 = INCH_0;       // ref+=AVcc, channel = A0
  ADC12MCTL1 = INCH_1+EOS;
  ADC12IE = BIT2;                           // ʹ��ADC�ж�
  ADC12CTL0 |= ENC;                         // ʹ��ת��
  ADC12CTL0 |= ADC12SC;                     // ��ʼת��
  _EINT();
  */
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
        sum >>= 5;                            //����32
        
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
�������ƣ�Trans_val
��    �ܣ���16����ADCת�����ݱ任����λ10����
          ��ʵ��ģ���ѹ���ݣ�����Һ������ʾ
��    ����Hex_Val--16��������
          n--�任ʱ�ķ�ĸ����2��n�η�       
����ֵ  ����
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
   /* Display_number(1,0,ptr[0]);
    Display(1,1,".");    
    Display_number(1,2,ptr[1]);
    Display_number(1,3,ptr[2]);
    Display_number(1,4,ptr[3]);
    Display_number(1,5,ptr[4]);
     Display_number(1,6,ptr[5]);
   */
}
