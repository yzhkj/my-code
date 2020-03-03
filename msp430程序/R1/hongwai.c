//////////////////////////////////////////////////////////////////////////*
/*****************************************************************
0x45 0x46 0x47
0x44 0x40 0x43
0x07 0x15 0xd9
0x16 0x19 0x0d
0x0c 0x18 0x5e
0x08 0x1c 0x5a
0x42 0x52 0x4a
*****************************************************//////////////////////////////////////////////

/********************************************************************
//DM430-A�Ϳ��������ң����������򣬶�ң������������ʶ��Ȼ�󽫼�ֵ��ʾ���������
//����ң����ΪNEC�����ʽ��38K���ƣ�����ʱֱ�Ӷ�ȡ��ֵ���û���00FF
//���ڲ�ȡ����IO��ƽֱ���жϷ�ʽ��ȡ�����в��ȶ������󣬰���ʱƵ�ʲ�Ҫ����
//���Ի�����EW430 V5.30
//���ߣ����� www.avrgcc.com 

//ʱ�䣺2011.09.19
********************************************************************/

#include <msp430x14x.h>
//#include "delay.h"
#include "Config.h"                  //����������ͷ�ļ�����Ҫ����IO�˿���Ϣ
 
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




typedef unsigned char uchar; 






uchar code_value=0,KEY_VAL,RED_R;
uchar key_code[4]; 



//*************************************************************************
//			ң������ֵ������ֵ�ӳ���
//*************************************************************************
 void Key_Icode(void)
 {
   switch(key_code[2])                    //��3���ֽ������ݣ���4���ֽ��Ƿ���
   {                                      //Ϊ�˸��ȶ������Լ��ϵ�4���ֽ����ݵ��ж�
   case KEY_0:KEY_VAL=0;P2OUT=BIT0;break;
   case KEY_1:KEY_VAL=1;P2OUT=BIT1; break;
   case KEY_2:KEY_VAL=2;P2OUT=BIT2; break;
   case KEY_3:KEY_VAL=3;P2OUT=BIT3; break;
   case KEY_4:KEY_VAL=4; P2OUT=BIT4; break;
   case KEY_5:KEY_VAL=5; P2OUT=BIT5; break;
   case KEY_6:KEY_VAL=6; P2OUT=BIT6; break;
   case KEY_7:KEY_VAL=7; P2OUT=BIT7; break;
   case KEY_8:KEY_VAL=8;P2OUT=BIT0; break;
   case KEY_9:KEY_VAL=9;P2OUT=BIT0; break;
   case KEY11:break;
   case KEY12:break;
   case KEY13:break;
   case KEY14:break;
   case KEY15:break;
   case KEY16:break;
   case KEY17:TACCR1-=100;P2OUT=0XF0;break;
   case KEY18:TACCR1+=100;P2OUT=0X0F;break;
   case KEY19:break;
   case KEY20:break;
   case KEY21:break;
   default:break;
   }

   
 }
 
//*************************************************************************
//	ң���������ӳ���
//*************************************************************************

void Red_Code()
{
uchar i,j,k = 0;

 for(i = 0;i < 19;i++)
{
  delay_us(400);           //��ʱ400us
  if(RED_R)                //9ms���иߵ�ƽ�����ж�Ϊ���ţ��˳��������
  {
      return;
  }
}

while(!RED_R);            //�ȴ�9ms�͵�ƽ��ȥ



for(i=0;i<5;i++)          //�Ƿ�������
{
  delay_us(500);
  if(!RED_R)
   {
     return;
   }
}


while(RED_R);               //�ȴ�4.5ms�ߵ�ƽ��ȥ

for(i = 0;i < 4;i++)        //����4���ֽڵ�����
{
  for(j = 0;j < 8;j++)      //ÿ���ֽڵ�����8λ
  {
   

   while(!RED_R);           //�ȴ���ߵ�ƽ
   while(RED_R)             //����ߵ�ƽʱ��
   {
    delay_us(100);
    k++;
    if(k >22)               //�ߵ�ƽʱ����������˳��������
    {
     return;         
    }
    
   }

   code_value>>=1;          //����һλ����
   if(k >= 7)
   {
    code_value|=0x80;       //�ߵ�ƽʱ�����0.56����Ϊ����1
   }
   k = 0;                  //��ʱ����
  }
  key_code[i]=code_value;  //�ĸ��ֽڵ�����
}

  Key_Icode();             //���ø�ֵ����

 
}

//***********************************************************************
//            ������
//***********************************************************************
/*void main(void)
{    
  WDT_Init();                         //���Ź���ʼ��
  Clock_Init();                       //ʱ�ӳ�ʼ��
  Port_Init();                        //�˿ڳ�ʼ�������ڿ���IO����������
  Close_LED();
  P2DIR=0xff;
    while(1)
 {
    Red_Code();                       //����ң���������ӳ���
 }
} */
