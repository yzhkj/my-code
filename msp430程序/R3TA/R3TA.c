#include <msp430f149.h>
#include "TA.c"
#include "init.c"
#include "delay.h"
//#include "hongwai.c"
//#include "Config.h"


/**************��������***************/
void init(void);//ϵͳ��ʼ��


//*******************���߼�*************//
void main(void)
{
  init();
  P2DIR = 0XFF;
  P2OUT &=0XFF;
  while(1)
  {


  }
}

