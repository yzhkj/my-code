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
//DM430-A型开发板红外遥控器解码程序，对遥控器按键进行识别，然后将键值显示到数码管上
//红外遥控器为NEC编码格式，38K调制，解码时直接读取键值，用户码00FF
//由于采取的是IO电平直接判断方式读取，会有不稳定的现象，按键时频率不要过快
//调试环境：EW430 V5.30
//作者：阿迪 www.avrgcc.com 

//时间：2011.09.19
/********************************************************************/

#include <msp430x14x.h>
#include "Config.h"                  //开发板配置头文件，主要配置IO端口信息



uchar code_value=0,KEY_VAL;
uchar key_code[4];
extern float sv;

//*************************************************************************
//			遥控器键值赋功能值子程序
//*************************************************************************
 void Key_Icode(void)
 {
   switch(key_code[2])                    //第3个字节是数据，第4个字节是反码
   {                                      //为了更稳定，可以加上第4个字节数据的判断
   case KEY_0:KEY_VAL=0;sv=30; break;
   case KEY_1:KEY_VAL=1;sv=10; break;
   case KEY_2:KEY_VAL=2; break;
   case KEY_3:KEY_VAL=3; break;
   case KEY_4:KEY_VAL=4;  break;
   case KEY_5:KEY_VAL=5; break;
   case KEY_6:KEY_VAL=6; break;
   case KEY_7:KEY_VAL=7;  break;
   case KEY_8:KEY_VAL=8; break;
   case KEY_9:KEY_VAL=9; break;
   case KEY11:break;
   case KEY12:break;
   case KEY13:break;
   case KEY14:KEY_VAL=14; break;
   case KEY15:break;
   case KEY16:break;
   case KEY17:break;
   case KEY18:break;
   case KEY19:break;
   case KEY20:break;
   case KEY21:break;
   default:break;
   }

   
 }
 
void Red_Code()
{
  uchar i,j,k = 0;
 for(i = 0;i < 19;i++)
{
  delay_us(400);           //延时400us
  if(RED_R)                //9ms内有高电平，则判断为干扰，退出处理程序
  {
      return;
  }
}
while(!RED_R);            //等待9ms低电平过去
for(i=0;i<5;i++)          //是否连发码
{
  delay_us(500);
  if(!RED_R)
   {
     return;
   }
}
while(RED_R);               //等待4.5ms高电平过去

for(i = 0;i < 4;i++)        //接收4个字节的数据
{
  for(j = 0;j < 8;j++)      //每个字节的数据8位
  {
    while(!RED_R);           //等待变高电平
    while(RED_R)             //计算高电平时间
   {
    delay_us(100);
    k++;
    if(k >22)               //高电平时间过长，则退出处理程序
    {
     return;         
    }
    
   }

   code_value>>=1;          //接受一位数据
   if(k >= 7)
   {
    code_value|=0x80;       //高电平时间大于0.56，则为数据1
   }
   k = 0;                  //计时清零
  }
  key_code[i]=code_value;  //四个字节的数据
}
  Key_Icode();             //调用赋值函数 
}

//***********************************************************************
//            主程序
//***********************************************************************
/*
void main(void)
{    
  WDT_Init();                         //看门狗初始化
  Clock_Init();                       //时钟初始化
 // Port_Init();                        //端口初始化，用于控制IO口输入或输出
//  Close_LED();
  P2DIR=0xff;
    while(1) 
 {
    Red_Code();//调用遥控器解码子程序

 }
} 
*/