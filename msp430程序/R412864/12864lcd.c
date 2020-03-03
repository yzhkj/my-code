#include <msp430x14x.h>
#include "12864.c"
#include "init.h"
#include "delay.h"

void main()
{
  init();
  Ini_Lcd();
  while(1)
  {
    Disp_HZ(0x80,hang2,8);
    //lcd12864_display_string(2,1,"123455666");
    
  }
}