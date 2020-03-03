#include  <msp430x14x.h>
#define   Num_of_Results   32

static unsigned int results[Num_of_Results];    //����ADCת�����������                                                     // is not used for anything.
void Trans_val(int Hex_Val);           

/************************������****************************/
void adc12_init()
{
  P6SEL |= 0x01;                            // ʹ��ADCͨ��
  ADC12CTL0 = ADC12ON+SHT0_8+MSC;           // ��ADC�����ò���ʱ��
  ADC12CTL1 = SHP+CONSEQ_2;                 // ʹ�ò�����ʱ��
  ADC12IE = 0x01;                           // ʹ��ADC�ж�
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
  static uint index = 0;

  results[index++] = ADC12MEM0;               // Move results
  if(index == Num_of_Results)
  {
        uchar i;
        unsigned long sum = 0;

        index = 0;
        for(i = 0; i < Num_of_Results; i++)
        {
            sum += results[i];
        }
        sum >>= 5;                            //����32
        
        Trans_val(sum);
  }
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
    unsigned long caltmp;
    uint Curr_Volt;
    uchar t1;//,i
    uchar ptr[8];
   Hex_val=(Hex_val*8)/10;
    
    ptr[0]=Hex_val/100000 ;
ptr[1]=Hex_val%100000/10000 ;
ptr[2]=Hex_val%100000%10000/1000 ;
ptr[3]=Hex_val%100000%10000%1000/100 ;
ptr[4]=Hex_val%100000%10000%1000%100/10 ;   
ptr[5]=Hex_val%100000%10000%1000%100%10/1 ;
    //ptr[0] = Hex_val / 1000;   
    //ptr[1] = '.';      
    //ptr[2] = (Hex_val - ptr[0]*1000)/100;
    //ptr[3] = (Hex_val - ptr[0]*1000 - ptr[1]*100)/10;
   // ptr[4] = (Hex_val - ptr[0]*1000 - ptr[1]*100 - ptr[2]*10); 
   // ptr[5] = (Hex_val - ptr[0]*1000 - ptr[1]*100 - ptr[2]*10-ptr[0]);
    
    caltmp = Hex_val;
    caltmp = (caltmp << 5) + Hex_val;           //caltmp = Hex_Val * 33
    caltmp = (caltmp << 3) + (caltmp << 1);     //caltmp = caltmp * 10
    Curr_Volt = caltmp >> 12;                   //Curr_Volt = caltmp / 2^n
    
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
    Display_number(1,0,ptr[0]);
    Display(1,1,".");    
    Display_number(1,2,ptr[1]);
    Display_number(1,3,ptr[2]);
    Display_number(1,4,ptr[3]);
    Display_number(1,5,ptr[4]);
     Display_number(1,6,ptr[5]);
}
