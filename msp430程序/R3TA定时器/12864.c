#include <msp430x14x.h>
#include "12864.h"
#include "delay.h"

#define SetOut_RS                       (P3DIR |= BIT0)
#define RS_Out_1                        (P3OUT |= BIT0)
#define RS_Out_0                        (P3OUT &= ~BIT0)

#define SetOut_RW                       (P3DIR |= BIT1)
#define RW_Out_1                        (P3OUT |= BIT1)
#define RW_Out_0                        (P3OUT &= ~BIT1)

#define SetOut_EN                       (P3DIR |= BIT2)
#define EN_Out_1                        (P3OUT |= BIT2)
#define EN_Out_0                        (P3OUT &= ~BIT2)



void lcd12864_write(unsigned char dat);
void lcd12864_write_command(unsigned char com);
void lcd12864_write_dat(unsigned char dat);


//==����˵����1����ϵͳ�ϵ缴���øó�ʼ�������������ٱ�֤ϵͳ��ѹ�ȶ������øú����м������ӳ�ʱ�䡣
//==             ���������ϵ����밴һ�¸�λ��Һ���Ż�������ʾ��
//==          2����ϵͳ�������ڱȽ϶̣����ʼ��������ʱһ��ʱ����ܵ�����ʾ����
void lcd12864_init(void)
{
  delay_ms(20);//�ϵ���ʱ
  
  SetOut_RS;
  SetOut_RW;
  SetOut_EN;
  
  RS_Out_0;

  lcd12864_write_command(0x30);
  lcd12864_write_command(0x02);
  lcd12864_write_command(0x06);
  lcd12864_write_command(0x0c);
  lcd12864_write_command(0x01);
  lcd12864_write_command(0x80);
  
  delay_ms(1);//��ʼ������ʱ
}

void lcd12864_write(unsigned char dat)
{
  unsigned char i;
 
  for(i=0;i<8;i++)
  {
    if(dat&0x80) RW_Out_1;
      else RW_Out_0;
    EN_Out_0; 
    EN_Out_1;
    dat <<= 1;
  } 
}


void lcd12864_write_command(unsigned char com)
{
 unsigned char ChangeCommand;

  RS_Out_1;
  lcd12864_write(0XF8);//д����ָ��
  ChangeCommand=com;
  ChangeCommand &= 0xf0;//���룬���������ֽڵĸ���λȡ��������λ����
  lcd12864_write(ChangeCommand);
  ChangeCommand=com;
  ChangeCommand<<=4;//���ƣ����������ֽڵĵ���λ�Ƶ�����λ�ϣ�ԭ���ĵ���λ�Զ�����
  lcd12864_write(ChangeCommand);
  RS_Out_0;
}
void lcd12864_write_dat(unsigned char dat)
{
  unsigned char ChangeData;

  RS_Out_1;
  lcd12864_write(0Xfa);//д����ָ��
  ChangeData=dat;
  ChangeData&=0xf0;//���͵ĵڶ�ָ��ĸ���λ����ָ������ݵĸ���λ
  lcd12864_write(ChangeData);
  ChangeData=dat;
  ChangeData<<=4;//����ָ��ĸ���λ����ָ������ݵĵ���λ����֮��һֱ�ĸ���λ��������
  lcd12864_write(ChangeData);
  RS_Out_0;
}

void lcd12864_display_string(unsigned char hang,unsigned char lie,unsigned char *p)
{
 unsigned char DisRow;

 if(hang==1)DisRow=0x80;
 else if(hang==2)DisRow=0x90;
 else if(hang==3)DisRow=0x88;
 else if(hang==4)DisRow=0x98;

 lcd12864_write_command(DisRow+lie-1);
 while(!(*p=='\0'))
 {
  lcd12864_write_dat(*p);
  p++;
 }
}

void lcd12864_display_TwoNum(unsigned char hang,unsigned char lie,unsigned char num)
{  
  unsigned char Addr;
  
  if(hang==1) Addr=0x80;
   else if(hang==2) Addr=0x90;
    else if(hang==3)	Addr=0x88;
	  else if(hang==4) Addr=0x98;

  lcd12864_write_command(Addr+lie-1);
  lcd12864_write_dat(0x30+num/10);
  lcd12864_write_dat(0x30+num%10);
}