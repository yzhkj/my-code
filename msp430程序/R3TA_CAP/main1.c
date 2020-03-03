#include <msp430x14x.h>
#include "init.c"
#include "12864.c"
#include "TA_CAP.C"
#include "delay.h"


void initf(void);
extern void TACAP_init(void);
extern long HC_SR04(void);

unsigned char shu[20]="0123456789";

void main()
{
  long distance=0;
  unsigned int xiao=0,qian=0,bai=0,shi=0,ge=0; 
//  float a=0;
  initf();
  TACAP_init();
  Ini_Lcd();
  P2DIR = 0XFF;
  //Disp_SZ(0x90,shu,1);
  while(1)
  {
    distance=HC_SR04();
   // a=distance*0.001;
   // distance=distance/1000;
    qian=distance/100000;
    Disp_SZ(0x80,(shu+qian),1);
    bai=distance%100000/10000;
    Disp_SZ(0x81,(shu+bai),1);
    shi=distance%10000/1000;
    Disp_SZ(0x82,(shu+shi),1);
    ge=distance%1000/100;
    Disp_SZ(0x83,(shu+ge),1);
    xiao=distance%100/10;
    Disp_SZ(0x84,(shu+xiao),1);
    delay_ms(30);
  }
}