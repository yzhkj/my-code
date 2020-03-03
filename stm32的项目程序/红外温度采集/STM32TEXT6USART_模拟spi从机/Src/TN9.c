#include "TN9.h"


u8 MISO_I(void)    		//ת������
{
	return SPI_MISO;
}

u8 WAIT_STAR(void)		//�ȴ����ݴ��Ϳ�ʼ
{
	u8 count=0;         //����
	while(1) 
	{
		if(SPI_CLK)				//�ɵ��ߵ�ƽ
		{
			count++;
			HAL_Delay(100);   		 //��ʱ10us
			if(!SPI_CLK) count=0;  //���󣬲���spi���еĸߵ�ƽ ��������		 
		}
		if(count>10) return 1;   //����ʵ��ʾ������������
					
	}
}
void SCK_D(u8 sclk)
{
	if(1==sclk)
	{
		while(SPI_CLK);       //�ȴ�ʱ����Ϊ��
	}
	else
	{
		while(!SPI_CLK);			//�ȴ�ʱ����Ϊ��
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
	u8 data[5];  				//��������
	u8 count=0;
	if(WAIT_STAR())     //�ȴ������ݿ�ʼ����
	{
		for(count=0;count<4;count++)
		{
			data[count]=SPI_Receiver_Dat();
		}
	}
	if(count>3)					//�ɼ���4�ֽ����ݣ���������ָ�� 
//		return ((u8 *)(&data));
	return data;
	else return NULL;		//һ֡���ݲɼ��������ؿ�ָ��
}

