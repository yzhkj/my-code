#include <msp430x14x.h>
#include "init.c"
#include "12864.c"
#include "Config.h"
#include "hong.c"

void PID_Control(float sv,float fy);
void displayshu();

unsigned char shuzi[20]="0123456789abcdef";
float Ki,Kd,Kp,u;

void main()
{
  
  initf();
  PWM_INIT();
  Ini_Lcd(); 
  while(1)
  {
 //   Red_Code();
    displayshu(); 

  }  
}
void PID_Control(float sv,float fy)
{
  float pError=0,iError=0,dError=0,u1;
  float ek,ek1,ek2;
  ek=sv-fy;
  pError=ek-ek1;		//�������(���ڵ�ǰ����ȥǰһ�ε����)
  iError=ek;				//�������(���ڵ�ǰ���ֵ)
  dError=ek-ek1*2+ek2;	//΢�����(���ڵ�ǰ����ȥǰһ��2������ټ���ǰ���ε����)
	
  ek2=ek1;	//����ǰ���ε����ֵ
  ek1=ek;	//����ǰһ�ε����ֵ	
  u=(float)(Kp*pError+Ki*iError+Kd*dError+u1);	//��ȡPID���ڵ����ֵ
  u1=u;		//����ǰһ�ε����ֵ
}
void displayshu()
{
    unsigned char shi,ge;
    shi=TACCR0/10000;    //TACCR0������ʾ
    ge=TACCR0%10000/1000;
    Disp_SZ(0x80,(shuzi+shi),1);
    Disp_SZ(0x82,(shuzi+ge),1);
    shi=TACCR1/1000;      //TACCR1������ʾ
    ge=TACCR1%1000/100;
    Disp_SZ(0x84,(shuzi+shi),1);
    Disp_SZ(0x86,(shuzi+ge),1);
    shi=TACCR2/1000;    //TACCR2������ʾ
    ge=TACCR2%1000/100;
    Disp_SZ(0x90,(shuzi+shi),1);
    Disp_SZ(0x92,(shuzi+ge),1);

}