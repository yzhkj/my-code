#include "key.h"




#define ON_LEVEL     1
#define KEYOFF_VAL   0x00

uint8_t Cur_Keyval=0; //获取键值
uint8_t Pre_Keyval=0; //上次按键值
uint8_t key_on=0;     //抖动变量  1表示已经抖动


//获取键值
void Get_Keyval(void)
{
    if(KEY0==ON_LEVEL)
        Cur_Keyval|= KEY0_PRES;
    else
        Cur_Keyval&=~KEY0_PRES;

    if(KEY1==ON_LEVEL)
        Cur_Keyval|= KEY1_PRES;
    else
        Cur_Keyval&=~KEY1_PRES;
	
    if(KEY2==ON_LEVEL)
        Cur_Keyval|= KEY2_PRES;
    else
        Cur_Keyval&=~KEY2_PRES;

    if(KEY3==ON_LEVEL)
        Cur_Keyval|= KEY3_PRES;
    else
        Cur_Keyval&=~KEY3_PRES;

    if(KEY4==ON_LEVEL)
        Cur_Keyval|= KEY4_PRES;
    else
        Cur_Keyval&=~KEY4_PRES;

    if(KEY5==ON_LEVEL)
        Cur_Keyval|= KEY5_PRES;
    else
        Cur_Keyval&=~KEY5_PRES;
	
    if(KEY6==ON_LEVEL)
        Cur_Keyval|= KEY6_PRES;
    else
        Cur_Keyval&=~KEY6_PRES;

    if(KEY7==ON_LEVEL)
        Cur_Keyval|= KEY7_PRES;
    else
        Cur_Keyval&=~KEY7_PRES;
}

//按键消除抖动
void Key_filter(void)
{
	HAL_Delay(5);
    if(Cur_Keyval == Pre_Keyval && Cur_Keyval != KEYOFF_VAL)
        {key_on=1;}
    else
        {key_on=0;}

    Pre_Keyval=Cur_Keyval;
}



//按键处理函数
//返回按键值
//mode:0,不支持连续按;1,支持连续按;
//0，没有任何按键按下
//1，WKUP按下 WK_UP
//注意此函数有响应优先级,KEY0>KEY1>KEY2>WK_UP!!

//mode=0有松手检测  mode=1无
u8 KEY_Scan(u8 mode)
{
    static u8 key_up=1;     //按键松开标志
    if(mode==1)key_up=1;    //支持连按
	
	Get_Keyval();
	Key_filter();
	
//    if(key_up&&(KEY0==1||KEY1==1||KEY2==1||KEY3==1||KEY4==1||KEY5==1||KEY6==1||KEY7==1))
    if(key_up && key_on)
	{
//        HAL_Delay(10);
        key_up=0;
        if(Cur_Keyval==KEY0_PRES)       return KEY0_PRES;
        else if(Cur_Keyval==KEY1_PRES)  return KEY1_PRES;
        else if(Cur_Keyval==KEY2_PRES)  return KEY2_PRES;
        else if(Cur_Keyval==KEY3_PRES)  return KEY3_PRES; 
        else if(Cur_Keyval==KEY4_PRES)  return KEY4_PRES;
        else if(Cur_Keyval==KEY5_PRES)  return KEY5_PRES;
        else if(Cur_Keyval==KEY6_PRES)  return KEY6_PRES;	
		else if(Cur_Keyval==KEY7_PRES)  return KEY7_PRES;
		 
    }
//	else if(KEY0==0&&KEY1==0&&KEY2==0&&KEY3==0&&KEY4==0&&KEY5==0&&KEY6==0&&KEY7==0)key_up=1;
    else if(Cur_Keyval==KEYOFF_VAL)
	{
		key_up=1;
	}
	return NONE_PRES;   //无按键按下
}


