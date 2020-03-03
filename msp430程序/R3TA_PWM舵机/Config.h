#ifndef __CONFIG_H_
#define __CONFIG_H_
             /*
#define CPU_F ((double)8000000) 
#define delay_us(x) __delay_cycles((long)(CPU_F*(double)x/1000000.0)) 
#define delay_ms(x) __delay_cycles((long)(CPU_F*(double)x/1000.0)) 
             */
#define uchar unsigned char
#define uint  unsigned int
#define ulong unsigned long

/*��BRCLK=CPU_Fʱ������Ĺ�ʽ���Լ��㣬����Ҫ�������ü����Ƶϵ��*/
#define baud           9600                                //���ò����ʵĴ�С
#define baud_setting   (uint)((ulong)CPU_F/((ulong)baud))  //�����ʼ��㹫ʽ
#define baud_h         (uchar)(baud_setting>>8)            //��ȡ��λ
#define baud_l         (uchar)(baud_setting)               //��λ
/*
#define LED8PORT        P2OUT                   //P2��8��LED��
#define LED8SEL         P2SEL                   //P2��8��LED��
#define LED8DIR         P2DIR                   //P2��8��LED��
*/
#define DATAPORT	P4OUT                   //���ݿ����ڶ˿�P4
#define DATASEL         P4SEL                   //���ݿڹ��ܼĴ��������ƹ���ģʽ
#define DATADIR         P4DIR                   //���ݿڷ���Ĵ���

#define CTRPORT	        P6OUT                   //���������ڵĶ˿�P6
#define CTRSEL          P6SEL                   //���ƿڹ��ܼĴ��������ƹ���ģʽ
#define CTRDIR          P6DIR                   //���ƿڷ���Ĵ���

#define DCTR0	        P6OUT &= ~BIT4          //����ܶο���λ�ź��õ�
#define DCTR1           P6OUT |=  BIT4          //����ܶο���λ�ź��ø�
#define WCTR0	        P6OUT &= ~BIT3          //�����λ����λ�ź��õ�
#define WCTR1           P6OUT |=  BIT3          //�����λ����λ�ź��ø�

#define KEYPORT	        P1OUT                   //�������ڵĶ˿�P1
#define KEYSEL          P1SEL                   //���ƿڹ��ܼĴ��������ƹ���ģʽ
#define KEYDIR          P1DIR                   //���ƿڷ���Ĵ���
#define KEYIN           P1IN                    //����ɨ���ж���Ҫ��ȡIO��״ֵ̬

#define DACCS0          P5OUT &= ~BIT4          //DACƬѡ�ź��õ�
#define DACCS1          P5OUT |=  BIT4          //DACƬѡ�ź��ø�
#define DIN0            P3OUT &= ~BIT1          //DAC DIN�ܽ�λ����Ϊ0
#define DIN1            P3OUT |=  BIT1          //DAC DIN�ܽ�λ����Ϊ1
#define DOUT0           P3OUT &= ~BIT2          //DAC DOUT�ܽ�λ����Ϊ0
#define DOUT1           P3OUT |=  BIT2          //DAC DOUT�ܽ�λ����Ϊ0
#define SCLK0           P3OUT &= ~BIT3          //DAC SCLK�ܽ�λ����Ϊ0
#define SCLK1           P3OUT |=  BIT3          //DAC SCLK�ܽ�λ����Ϊ0

#define SOUNDON         P6OUT &= ~BIT2          //������������
#define SOUNDOFF        P6OUT |=  BIT2          //������������

#define RS_CLR	        P6OUT &= ~BIT3           //RS�õ�    
#define RS_SET	        P6OUT |=  BIT3           //RS�ø�

#define RW_CLR	        P6OUT &= ~BIT4           //RW�õ�      
#define RW_SET	        P6OUT |=  BIT4          //RW�ø�

#define EN_CLR	        P6OUT &= ~BIT5           //E�õ�     
#define EN_SET	        P6OUT |=  BIT5           //E�ø�

 #define PSB_CLR	        P6OUT &= ~BIT6           //PSB�õͣ����ڷ�ʽ    ԭΪp50
 #define PSB_SET	        P6OUT |=  BIT6           //PSB�øߣ����ڷ�ʽ

#define RST_CLR	        P5OUT &= ~BIT1            //RST�õ�    ԭΪp51
#define RST_SET	        P5OUT |= BIT1             //RST�ø�

#define DataPort        P2OUT                     

/*12864Ӧ��ָ��*/
#define CLEAR_SCREEN	0x01		          //����ָ�������ACֵΪ00H
#define AC_INIT		0x02		          //��AC����Ϊ00H�����α��Ƶ�ԭ��λ��
#define CURSE_ADD	0x06		          //�趨�α��Ƶ�����ͼ�������ƶ�����Ĭ���α����ƣ�ͼ�����岻����
#define FUN_MODE	0x30		          //����ģʽ��8λ����ָ�
#define DISPLAY_ON	0x0c		          //��ʾ��,��ʾ�α꣬���α�λ�÷���
#define DISPLAY_OFF	0x08		          //��ʾ��
#define CURSE_DIR	0x14		          //�α������ƶ�:AC=AC+1
#define SET_CG_AC	0x40		          //����AC����ΧΪ��00H~3FH
#define SET_DD_AC	0x80                      //����DDRAM AC

///////////////����ң��
#define RED_IN	        P1DIR &= ~BIT5	//�������룬�������ͷ�ӵ�Ƭ��PE3��
#define RED_OUT	        P1DIR |=  BIT5	//�������
#define RED_L	        P1OUT &= ~BIT5	//�õ͵�ƽ
#define RED_H	        P1OUT |= BIT5   //�øߵ�ƽ
#define RED_R	        (P1IN & BIT5)	//����ƽ



/*DS1302�ܽŶ���*/
/*DS1302��λ��*/
#define RESET_CLR	P1OUT &= ~BIT7            //��ƽ�õ�
#define RESET_SET	P1OUT |=  BIT7            //��ƽ�ø�
#define RESET_IN	P1DIR &= ~BIT7            //��������
#define RESET_OUT	P1DIR |=  BIT7            //�������

/*DS1302˫������*/
#define IO_CLR	        P1OUT &= ~BIT6            //��ƽ�õ�
#define IO_SET	        P1OUT |=  BIT6            //��ƽ�ø�
#define IO_R	        P1IN & BIT6               //��ƽ��ȡ
#define IO_IN	        P1DIR &= ~BIT6            //��������
#define IO_OUT	        P1DIR |=  BIT6            //�������

/*DS1302ʱ���ź�*/
#define SCK_CLR	        P1OUT &= ~BIT5            //ʱ���ź�
#define SCK_SET	        P1OUT |=  BIT5            //��ƽ�ø�
#define SCK_IN	        P1DIR &= ~BIT5            //��������
#define SCK_OUT	        P1DIR |=  BIT5            //�������

/*DS1302��������ص�ַ*/
#define DS1302_sec_add		0x80		  //�����ݵ�ַ
#define DS1302_min_add		0x82		  //�����ݵ�ַ
#define DS1302_hr_add		0x84		  //ʱ���ݵ�ַ
#define DS1302_date_add		0x86		  //�����ݵ�ַ
#define DS1302_month_add	0x88		  //�����ݵ�ַ
#define DS1302_day_add		0x8a		  //�������ݵ�ַ
#define DS1302_year_add		0x8c		  //�����ݵ�ַ
#define DS1302_control_add	0x8e		  //�������ݵ�ַ
#define DS1302_charger_add	0x90 					 
#define DS1302_clkburst_add	0xbe




 
//***********************************************************************
//			ң��������
//***********************************************************************

#define KEY_0     0x16                 //��0
#define KEY_1     0x0C                 //��1
#define KEY_2     0x18                 //��2
#define KEY_3     0x5E                 //��3
#define KEY_4     0x08                 //��4
#define KEY_5     0x1C                 //��5
#define KEY_6     0x5A                 //��6
#define KEY_7     0x42                 //��7
#define KEY_8     0x52                 //��8
#define KEY_9     0x4A                 //��9
#define KEY11     0x45                 //  CH-
#define KEY12     0x46                 //  CH
#define KEY13     0x47                 //  CH+
#define KEY14     0x44                 //  |<<
#define KEY15     0x40                 //  >>|
#define KEY16     0x43                 //  >||
#define KEY17     0x07                 //  -
#define KEY18     0x15                 //  +
#define KEY19     0xd9                 //  EQ
#define KEY20     0x19                 //  100+
#define KEY21     0x0d                 //  200+


#endif



//uchar   key=0xFF;                                 //��ֵ����

//***********************************************************************
//			�����������ʾ�Ķ����
//***********************************************************************

 
//***********************************************************************
//                   ϵͳʱ�ӳ�ʼ��
//***********************************************************************
      /*
void Clock_Init()
{
  uchar i;
  BCSCTL1&=~XT2OFF;                 //��XT2����
  BCSCTL2|=SELM1+SELS;              //MCLKΪ8MHZ��SMCLKΪ8MHZ
  do{
    IFG1&=~OFIFG;                   //������������־
    for(i=0;i<100;i++)
       _NOP();
  }
  while((IFG1&OFIFG)!=0);           //�����־λ1�������ѭ���ȴ�
  IFG1&=~OFIFG; 
}
*///**********************************************************************
//               MSP430�ڲ����Ź���ʼ��
//***********************************************************************
       /*
void WDT_Init()
{
   WDTCTL = WDTPW + WDTHOLD;       //�رտ��Ź�
}      */



         /*
void UTR0_Init()
  { //������ 2400
    P3SEL |= 0x30;                            // P3.4,5ѡ��ΪUART�շ��˿�
    ME1 |= UTXE0 + URXE0;                     // ʹ��USART0�շ�  ʹ��
    UCTL0 |= CHAR;                            // 8-bit character
    UTCTL0 |= SSEL0;                          // UCLK = ACLK
    UBR00 = 0x0D;                             // 32k/2400 - 13.65 USART 0 Baud Rate 0 
    UBR10 = 0x00;                             //
    UMCTL0 = 0x6B;                            // Modulation
    UCTL0 &= ~SWRST;                          // ��ʼ��UART0״̬��
    IE1 |= URXIE0;                            // ʹ�ܽ����ж�
    _EINT();
  }
        */

 