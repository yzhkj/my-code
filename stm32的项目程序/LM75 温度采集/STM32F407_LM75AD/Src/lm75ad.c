#include "lm75ad.h"

// ////////////////////////////////////////////////////////////////////////////////	 
/*
0x00  Temperature Register      
0x01  Configuration register  ???? ?00????(100ms???????) ?01?ShutDown??
0x02  Hysteresis register
0x03  Over_temperature shutdown register
Temp Register 
MSByte                LSByte
7   6  5  4  3  2  1  0  7  6  5  4 3 2 1 0
D10 D9 D8 D7 D6 D5 D4 D3 D2 D1 D0 X X X X X
D10=0    ?=+(Temp Data×0.125) 	
D10=1    ?=-(Temp Data×0.125)
Address Table
MSB          LSB
1 0 0 1 A2 A1 A0
1 0 0 1 0  0  1 0/1       =0x92
*/
/////////////////////////////////////////////////////////////////////////////////
void I2C_WriteByte(u8 mode,u8 config,u8 addr)
{
	IIC_Send_Byte(addr);
	IIC_Send_Byte(config);
	IIC_Send_Byte(mode);
//	IIC_Send_Byte(config);
}
u16 I2C_ReadByte(u8 Rec_mode,u8 addr,u8 time)
{
	u16 temp[2]={0};
//	u16 re;
//	IIC_Start();
//	IIC_Send_Byte(addr);
//	IIC_Send_Byte(Rec_mode);
//	for(;time>0;time--)
//	{
//		temp[time-1]=IIC_Read_Byte(1);
//	}
	IIC_Start();
	IIC_Send_Byte(0x90);
	IIC_Wait_Ack();
	IIC_Send_Byte(0x00);
	IIC_Wait_Ack();
	IIC_Start();
	IIC_Send_Byte(0x91);
	IIC_Wait_Ack();
	temp[1]=IIC_Read_Byte(1);
	temp[0]=IIC_Read_Byte(0);
	IIC_Stop();
	
	temp[0]=(temp[1]<<8)+temp[0];
	return temp[0];
}

//LM75AD IO³õÊ¼»¯
void LM75AD_Init(void)
{
	I2C_WriteByte(0x01,0x00,LM75AD_ADDR);
}
 
u16 LM75_Temp(void)
{
	float tempture;
	int temp;
	temp=I2C_ReadByte(0x00,LM75AD_ADDR,2);
//	tempture=temp>>5;
//	return tempture*0.125;	
	return temp;
}


