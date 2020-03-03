#include <msp430x14x.h>
#include "init.h"
#include "init.c"
#include "12864.h"
#include "12864.c"
#include "delay.h"
#include "Config.h"
#include "hong.c"



unsigned char shuzi[20]="0123456789abcdef";


void main()
{
  
  initf();
  lcd12864_init();
  PWM_INIT();
  lcd12864_display_TwoNum(2,1,99);
  P2DIR=0XFF;
  P2OUT=0XFF;  
  while(1)
  {
    Red_Code();
    lcd12864_display_TwoNum(1,1,TACCR1/100);
    lcd12864_display_TwoNum(1,4,TACCR2/100);
   // delay_ms(50);
  }  
}
