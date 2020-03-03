#include <msp430x14x.h>
#include "init.c"
#include "12864.c"
#include "12864.h"
#include "Config.h"
#include "hong.c"
#include "AD.c"
#include "AD.H"
#include "TA_PWM.H"

unsigned char shuzi[]="0123456789abcdef";
float Ki,Kd,Kp,u;

void main()
{
  
  initf();
  Ini_Lcd();
  PWM_INIT();  
  adc12_init();
  while(1)
  {
    Red_Code();
    displayshu(); 

  }  
}
void displayshu()
{
    unsigned char shi,ge;
    shi=TACCR0/10000;    //TACCR0数字显示
    ge=TACCR0%10000/1000;
    Disp_SZ(0x80,(shuzi+shi),1);
    Disp_SZ(0x81,(shuzi+ge),1);
/*    shi=TACCR1/1000;      //TACCR1数字显示
    ge=TACCR1%1000/100;
    Disp_SZ(0x83,(shuzi+shi),1);
    Disp_SZ(0x84,(shuzi+ge),1);
    shi=TACCR2/1000;    //TACCR2数字显示
    ge=TACCR2%1000/100;
    Disp_SZ(0x86,(shuzi+shi),1);
    Disp_SZ(0x87,(shuzi+ge),1);    */

}
/*

void PID_Control(float sv,float fy)
{
  float pError=0,iError=0,dError=0,u1;
  float ek,ek1,ek2;
  ek=sv-fy;
  pError=ek-ek1;		//比例误差(等于当前误差减去前一次的误差)
  iError=ek;				//积分误差(等于当前误差值)
  dError=ek-ek1*2+ek2;	//微分误差(等于当前误差减去前一次2倍误差再加上前两次的误差)
	
  ek2=ek1;	//储存前两次的误差值
  ek1=ek;	//储存前一次的误差值	
  u=(float)(Kp*pError+Ki*iError+Kd*dError+u1);	//获取PID调节的误差值
  u1=u;		//储存前一次的输出值
}*/