#include "TN9.h"


u8 MISO_I(void)    		//转换函数
{
	return SPI_MISO;
}

u8 WAIT_STAR(void)		//等待数据传送开始
{
	u8 count=0;         //计数
	while(1) 
	{
		if(SPI_CLK)				//采到高电平
		{
			count++;
			HAL_Delay(100);   		 //延时10us
			if(!SPI_CLK) count=0;  //错误，不是spi空闲的高电平 计数清零		 
		}
		if(count>10) return 1;   //根据实际示波器测量来定
					
	}
}
void SCK_D(u8 sclk)
{
	if(1==sclk)
	{
		while(SPI_CLK);       //等待时钟线为高
	}
	else
	{
		while(!SPI_CLK);			//等待时钟线为低
	}
}


u8 SPI_Receiver_Dat(void)
{
	 u8 n,dat,bit_t;
	 for(n=0;n<8;n++)
	 {
			SCK_D(1);
			 dat<<=1;
			if(MISO_I())dat|=0x01;
			else dat&=0xfe;
			SCK_D(0);
	 }
		SCK_D(0);
		return dat;
}
u8* SPI_Receiver_MulDat(void)
{
	u8 data[5];  				//缓存数据
	u8 count=0;
	if(WAIT_STAR())     //等待新数据开始接收
	{
		for(count=0;count<4;count++)
		{
			data[count]=SPI_Receiver_Dat();
		}
	}
	if(count>3)					//采集到4字节数据，返回数据指针 
//		return ((u8 *)(&data));
	return data;
	else return NULL;		//一帧数据采集出错，返回空指针
}

