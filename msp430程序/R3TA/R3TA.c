#include <msp430f149.h>
#include "TA.c"
#include "init.c"
#include "delay.h"
//#include "hongwai.c"
//#include "Config.h"


/**************函数声明***************/
void init(void);//系统初始化


//*******************主逻辑*************//
void main(void)
{
  init();
  P2DIR = 0XFF;
  P2OUT &=0XFF;
  while(1)
  {


  }
}

