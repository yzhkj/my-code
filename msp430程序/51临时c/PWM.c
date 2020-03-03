/********************************* 深圳市航太电子有限公司 *******************************
* 实 验 名 ：PWM直流电机实验
* 实验说明 ：单击按键s18加速，单击按键s21减速
* 实验平台 ：航太DIY51单片机开发板V1.0
* 连接方式 ：CN16接CN7 MOT5接P04
*            CN10 UP接P34 Left接P35 Right接P36 Down接P37
*            电机两个引脚分别接向CN15的两个引脚，不需要分正负极
* 注    意 ：1.当PWM为1时停止，为0时启动,PWM周期为5ms，脉宽 0%-100%可调
*            2.电机启动时需要加大的电流，所以启动时占空比不可过小，导致电机不转而过热
* 作    者 ：航太电子产品研发部    QQ ：1909197536
* 店    铺 ：http://shop120013844.taobao.com/
****************************************************************************************/

#include <reg52.h>
#include <intrins.h>

#define FOSC 11059200L //晶振设置，默认使用11.0592M Hz
//#define FOSC 12000000L //晶振设置，使用12M Hz
//#define FOSC 24000000L //晶振设置，使用24M Hz

#define MAX_SPEED 950 // 最高占空比
#define MIN_SPEED 50//最低占空比
#define MAX_TIME 950 // 最高占空比
#define MIN_TIME 20//最低占空比
#define SPEED 100

//IO接口定义
sbit PWM=P0^4;
sbit key_inc = P3^2;
sbit key_dec = P3^3;
sbit key_inf = P3^0;
sbit key_def = P3^1;

//全局变量定义
unsigned char timer1,speed,TIME_US=20; //设定定时时间 us ; 

/*******************************************************************************
* 函 数 名 ：Delayms
* 函数功能 ：实现 ms级的延时
* 输    入 ：ms
* 输    出 ：无
*******************************************************************************/
void Delayms(unsigned int ms)
{
	unsigned int i,j;
	for(i=0;i<ms;i++)
	#if FOSC == 11059200L
		for(j=0;j<114;j++);
	#elif FOSC == 12000000L
	  for(j=0;j<123;j++);
	#elif FOSC == 24000000L
		for(j=0;j<249;j++);
	#else
		for(j=0;j<114;j++);
	#endif
}


/*******************************************************************************
* 函 数 名 ：Timer0Init
* 函数功能 ：定时器0初始化
* 输    入 ：无
* 输    出 ：无
*******************************************************************************/
void Timer0Init()
{
	TMOD=0x01; //设置定时器0工作方式为1
	TH0=(65536-(FOSC/12*TIME_US)/1000000)/256;
	TL0=(65536-(FOSC/12*TIME_US)/1000000)%256;
	ET0=1; //开启定时器0中断
	TR0=1;	//开启定时器	
	EA=1;  //打开总中断
}

/*******************************************************************************
* 函 数 名 ：KeyScan
* 函数功能 ：按键扫描
* 输    入 ：无
* 输    出 ：无
*******************************************************************************/
void KeyScan(void)
{
		if(key_inc==0)
		{
			
			Delayms(5);
			if(key_inc==0);
			{	
			    while(key_inc==0);
				speed+=2;
				if(speed > MAX_SPEED)	speed = MAX_SPEED;
			}
		}
			if(key_dec==0)
		{
			Delayms(5);
			if(key_dec==0);
			{
			    while(key_dec==0);
				if(speed <= MIN_SPEED)	speed = MIN_SPEED;
				speed-=2;	
			}
		}
		if(key_inf==0)
		{
			
			Delayms(5);
			if(key_inf==0);
			{	
			    while(key_inf == 0);
				TIME_US +=2;
				if(TIME_US > MAX_TIME)	TIME_US = MAX_TIME;
			}
		}
			if(key_def==0)
		{
			Delayms(5);
			if(key_def==0);
			{
			    while(key_def==0);
				if(TIME_US <= MIN_TIME)	TIME_US = MIN_TIME;
				TIME_US -= 2;	
			}
		}
}

/*******************************************************************************
* 函 数 名 ：main
* 函数功能 ：主函数
* 输    入 ：无
* 输    出 ：无
*******************************************************************************/
void main()
{
	Timer0Init();
	speed = 30;
	while(1)
	{ 
		KeyScan();
	}
}

/*******************************************************************************
* 函 数 名 ：Timer0Int
* 函数功能 ：定时器0中断函数 ， 每隔TIME_US ms进入
* 输    入 ：无
* 输    出 ：无
*******************************************************************************/
void Timer0Int() interrupt 1
{
	TH0=(65536-(FOSC/12*TIME_US)/1000000)/256;
	TL0=(65536-(FOSC/12*TIME_US)/1000000)%256;
	timer1++;  
	if(timer1>1000)  //PWM周期为100*0.05ms
	{
		timer1=0;
	}
	if(timer1 < speed)	//改变30这个值可以改变直流电机的速度
	{
		PWM=1;
	}
	else
	{
		PWM=0;
	}  
}
