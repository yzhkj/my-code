#ifndef __I2C_EE_C
#define __I2C_EE_C
#endif

#include "i2c_ee.h"
/********************************************************************************
* ʹ��I2C1��дAT24C256��LM75
*******************************************************************************/
void I2C_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);
}
//u16 test=0x00e7;

void I2C_delay(void)
{
	u8 i=50;	//��������Ż��ٶȣ���������͵�5����д��
	while(i--);
}

u16 I2C_Start(void)
{
	SDA_H;
	SCL_H;
	I2C_delay();
	if(!SDA_read)return(I2C_TM_ERR);	//SDA��Ϊ�͵�ƽ������æ,�˳�
	SDA_L;
	I2C_delay();
	if(SDA_read) return(I2C_TM_ERR);	//SDA��Ϊ�ߵ�ƽ�����߳���,�˳�
	SCL_L;
	I2C_delay();
	return (I2C_TM_OK);
}

void I2C_Stop(void)
{
	SCL_L;
	I2C_delay();
	SDA_L;
	I2C_delay();
	SCL_H;
	I2C_delay();
	SDA_H;
	I2C_delay();
	SCL_L;
	I2C_delay();
}

void I2C_Ack(void)
{
	SCL_L;
	I2C_delay();
	SDA_L;
	I2C_delay();
	SCL_H;
	I2C_delay();
	SCL_L;
	I2C_delay();
}

void I2C_NoAck(void)
{	
	SCL_L;
	I2C_delay();
	SDA_H;
	I2C_delay();
	SCL_H;
	I2C_delay();
	SCL_L;
	I2C_delay();
}

u16 I2C_WaitAck(void)	//����Ϊ:=1��ACK,=0��ACK
{
	SCL_L;
	I2C_delay();
	SDA_H;
	I2C_delay();
	SCL_H;
	I2C_delay();
	if(SDA_read)
	{
		SCL_L;
		return(I2C_TM_ERR);
	}
	SCL_L;
	return(I2C_TM_OK);
}

void I2C_SendByte(u8 SendByte)	//���ݴӸ�λ����λ//
{
	u8 i=8;
	while(i--)
	{
		SCL_L;
		I2C_delay();
		if(SendByte&0x80)SDA_H;
		else SDA_L;
		SendByte<<=1;
		I2C_delay();
		SCL_H;
		I2C_delay();
	}
	SCL_L;
}

u8 I2C_ReceiveByte(void)	//���ݴӸ�λ����λ//
{ 
	u8 i=8;
	u8 ReceiveByte=0;

	SDA_H;
	while(i--)
	{
		ReceiveByte<<=1;
		SCL_L;
		I2C_delay();
		SCL_H;
		I2C_delay();
		if(SDA_read)
		{
			ReceiveByte|=0x01;
		}
	}
	SCL_L;
	return ReceiveByte;
}

/*******************************************************************************
* Function Name  : I2C_EE_ByteWrite
* Description    : Writes one byte to the I2C EEPROM.
* Input          : - pBuffer : pointer to the buffer  containing the data to be 
*                    written to the EEPROM.
*                  - WriteAddr : EEPROM's internal address to write to.
* Output         : None
* Return         : None
*******************************************************************************/
//u16 I2C_EE_ByteWrite(u8* pBuffer, u16 WriteAddr)
//{
//	if(I2C_Start()==I2C_TM_ERR)return(I2C_TM_ERR);
//	I2C_SendByte(EEPROM_ADDRESS);					//����������ַ
//	if(I2C_WaitAck()==I2C_TM_ERR){I2C_Stop(); return(I2C_TM_ERR);}
//	I2C_SendByte((WriteAddr>>8) & 0x00FF);			//���ø���ʼ��ַ
//	if(I2C_WaitAck()==I2C_TM_ERR){I2C_Stop(); return(I2C_TM_ERR);}
//	I2C_SendByte((u8)(WriteAddr & 0x00FF));			//���õ���ʼ��ַ
//	if(I2C_WaitAck()==I2C_TM_ERR){I2C_Stop(); return(I2C_TM_ERR);}
//	I2C_SendByte(*pBuffer);
//	if(I2C_WaitAck()==I2C_TM_ERR){I2C_Stop(); return(I2C_TM_ERR);}
//	I2C_Stop();
//	//ע�⣺��Ϊ����Ҫ�ȴ�EEPROMд�꣬���Բ��ò�ѯ����ʱ��ʽ(10ms)
//	if(I2C_EE_WaitEepromStandbyState()==I2C_TM_ERR) return(I2C_TM_ERR);
//	return (I2C_TM_OK);
//}

///*******************************************************************************
//* Function Name  : I2C_EE_PageWrite
//* Description    : Writes more than one byte to the EEPROM with a single WRITE
//*                  cycle. The number of byte can't exceed the EEPROM page size.
//* Input          : - pBuffer : pointer to the buffer containing the data to be 
//*                    written to the EEPROM.
//*                  - WriteAddr : EEPROM's internal address to write to.
//*                  - NumByteToWrite : number of bytes to write to the EEPROM.
//* Output         : None
//* Return         : None
//*******************************************************************************/
//u16 I2C_EE_PageWrite(u8* pBuffer, u16 WriteAddr, u16 NumByteToWrite)
//{
//	if(I2C_Start()==I2C_TM_ERR)return I2C_TM_ERR;
//	I2C_SendByte(EEPROM_ADDRESS);					//����������ַ
//	if(I2C_WaitAck()==I2C_TM_ERR){I2C_Stop(); return(I2C_TM_ERR);}
//	I2C_SendByte((WriteAddr>>8) & 0x00FF);			//���ø���ʼ��ַ
//	if(I2C_WaitAck()==I2C_TM_ERR){I2C_Stop(); return(I2C_TM_ERR);}
//	I2C_SendByte((u8)(WriteAddr & 0x00FF));			//���õ���ʼ��ַ
//	if(I2C_WaitAck()==I2C_TM_ERR){I2C_Stop(); return(I2C_TM_ERR);}

//	while(NumByteToWrite--)
//	{
//		I2C_SendByte(* pBuffer);
//		if(I2C_WaitAck()==I2C_TM_ERR){I2C_Stop(); return(I2C_TM_ERR);}
//		pBuffer++;
//	}
//	I2C_Stop();
//	//ע�⣺��Ϊ����Ҫ�ȴ�EEPROMд�꣬���Բ��ò�ѯ����ʱ��ʽ(10ms)
//	//Systick_Delay_1ms(10);
//	if(I2C_EE_WaitEepromStandbyState()==I2C_TM_ERR) return(I2C_TM_ERR);
//	return(I2C_TM_OK);
//}

///*******************************************************************************
//* Function Name  : I2C_EE_BufferWrite
//* Description    : Writes buffer of data to the I2C EEPROM.
//* Input          : - pBuffer : pointer to the buffer  containing the data to be 
//*                    written to the EEPROM.
//*                  - WriteAddr : EEPROM's internal address to write to.
//*                  - NumByteToWrite : number of bytes to write to the EEPROM.
//* Output         : None
//* Return         : None
//*******************************************************************************/
//u16 I2C_EE_BufferWrite(u8* pBuffer, u16 WriteAddr, u16 NumByteToWrite)
//{
//	u16 NumOfPage = 0, NumOfSingle = 0, Addr = 0, count = 0;

//	Addr = WriteAddr % I2C_PageSize;
//	count = I2C_PageSize - Addr;
//	NumOfPage =  NumByteToWrite / I2C_PageSize;
//	NumOfSingle = NumByteToWrite % I2C_PageSize;

//	/* If WriteAddr is I2C_PageSize aligned  */
//	if(Addr == 0)
//	{
//		/* If NumByteToWrite < I2C_PageSize */
//		if(NumOfPage == 0) 
//		{
//			if(I2C_EE_PageWrite(pBuffer, WriteAddr, NumOfSingle)==I2C_TM_ERR) return(I2C_TM_ERR);
//		}
//		/* If NumByteToWrite > I2C_PageSize */
//		else
//		{
//			while(NumOfPage--)
//			{
//				if(I2C_EE_PageWrite(pBuffer, WriteAddr, I2C_PageSize)==I2C_TM_ERR) return(I2C_TM_ERR); 
//				WriteAddr +=  I2C_PageSize;
//				pBuffer += I2C_PageSize;
//			}
//	
//			if(NumOfSingle!=0)
//			{
//				if(I2C_EE_PageWrite(pBuffer, WriteAddr, NumOfSingle)==I2C_TM_ERR) return(I2C_TM_ERR);
//			}
//		}
//	}
//	/* If WriteAddr is not I2C_PageSize aligned  */
//	else
//	{
//		/* If NumByteToWrite < I2C_PageSize */
//		if(NumOfPage== 0)
//		{
//			if(I2C_EE_PageWrite(pBuffer, WriteAddr, NumOfSingle)==I2C_TM_ERR) return(I2C_TM_ERR);
//		}
//		/* If NumByteToWrite > I2C_PageSize */
//		else
//		{
//			NumByteToWrite -= count;
//			NumOfPage =  NumByteToWrite / I2C_PageSize;
//			NumOfSingle = NumByteToWrite % I2C_PageSize;	

//			if(count != 0)
//			{
//				if(I2C_EE_PageWrite(pBuffer, WriteAddr, count)==I2C_TM_ERR) return(I2C_TM_ERR);
//				WriteAddr += count;
//				pBuffer += count;
//			}

//			while(NumOfPage--)
//			{
//				if(I2C_EE_PageWrite(pBuffer, WriteAddr, I2C_PageSize)==I2C_TM_ERR) return(I2C_TM_ERR);
//				WriteAddr +=  I2C_PageSize;
//				pBuffer += I2C_PageSize;
//			}
//			if(NumOfSingle != 0)
//			{
//				if(I2C_EE_PageWrite(pBuffer, WriteAddr, NumOfSingle)==I2C_TM_ERR) return(I2C_TM_ERR); 
//			}
//		}
//	}
//	return(I2C_TM_OK);
//}

///*******************************************************************************
//* Function Name  : I2C_EE_BufferRead
//* Description    : Reads a block of data from the EEPROM.
//* Input          : - pBuffer : pointer to the buffer that receives the data read 
//*                    from the EEPROM.
//*                  - ReadAddr : EEPROM's internal address to read from.
//*                  - NumByteToRead : number of bytes to read from the EEPROM.
//* Output         : None
//* Return         : None
//*******************************************************************************/
//u16 I2C_EE_BufferRead(u8* pBuffer, u16 ReadAddr, u16 NumByteToRead)
//{
//	if(I2C_Start()==I2C_TM_ERR)return(I2C_TM_ERR);
//	I2C_SendByte(EEPROM_ADDRESS);					//����������ַ
//	if(I2C_WaitAck()==I2C_TM_ERR){I2C_Stop(); return(I2C_TM_ERR);}
//	I2C_SendByte((ReadAddr>>8) & 0x00FF);			//���ø���ʼ��ַ
//	if(I2C_WaitAck()==I2C_TM_ERR){I2C_Stop(); return(I2C_TM_ERR);}
//	I2C_SendByte((u8)(ReadAddr & 0x00FF));   		//���õ���ʼ��ַ
//	if(I2C_WaitAck()==I2C_TM_ERR){I2C_Stop(); return(I2C_TM_ERR);}
//	if(I2C_Start()==I2C_TM_ERR)return(I2C_TM_ERR);
//	I2C_SendByte(EEPROM_ADDRESS | 0x0001);
//	if(I2C_WaitAck()==I2C_TM_ERR){I2C_Stop(); return(I2C_TM_ERR);}
//	while(NumByteToRead)
//	{
//		*pBuffer = I2C_ReceiveByte();
//		if(NumByteToRead == 1)I2C_NoAck();
//		else I2C_Ack();
//		pBuffer++;
//		NumByteToRead--;
//	}
//	I2C_Stop();

//	return(I2C_TM_OK);
//}

///*******************************************************************************
//* Function Name  : I2C_EE_WaitEepromStandbyState
//* Description    : Wait for EEPROM Standby state
//* Input          : None
//* Output         : None
//* Return         : None
//*******************************************************************************/
//u16 I2C_EE_WaitEepromStandbyState(void)
//{
//	u32 tmout=I2C_TIMEOUT;

//	do
//	{
//		if(I2C_Start()==I2C_TM_ERR)return I2C_TM_ERR;
//		I2C_SendByte(EEPROM_ADDRESS);					//����������ַ
//		if(I2C_WaitAck()==I2C_TM_OK){I2C_Stop(); return(I2C_TM_OK);}
//		tmout--;
//	}while(tmout>0);

//	//ֹͣλ
//	I2C_Stop();
//	return(I2C_TM_ERR);
//}

///*******************************************************************************
//* Function Name  : I2C_LM75_Read
//* Description    : Reads Temperature data from the LM75.
//* Input          : None
//* Output         : 0xFFFF -- Error
//*					0x0000 ~ 0x01FF -- Valid data
//*					Temp	Binary 					Hex
//*					+125	0111 1101 0xxx xxxx 	0FAh
//*					+25		0001 1001 0xxx xxxx 	032h
//*					+0.5	0000 0000 1xxx xxxx 	001h
//*					0		0000 0000 0xxx xxxx		000h
//*					-0.5	1111 1111 1xxx xxxx 	1FFh
//*					-25		1110 0111 0xxx xxxx 	1CEh
//*					-55		1100 1001 0xxx xxxx 	192h
//* Return         : None
//*******************************************************************************/
//u16 I2C_LM75_Read(void)
//{
//	vu16 TempH,TempL;

//	if(I2C_Start()==I2C_TM_ERR)return(I2C_TM_ERR);
//	I2C_SendByte(LM75_ADDRESS);						//����������ַ
//	if(I2C_WaitAck()==I2C_TM_ERR){I2C_Stop(); return(I2C_TM_ERR);}
//	I2C_SendByte(0x00);								//�����¶ȼĴ�����ַ
//	if(I2C_WaitAck()==I2C_TM_ERR){I2C_Stop(); return(I2C_TM_ERR);}

//	if(I2C_Start()==I2C_TM_ERR)return(I2C_TM_ERR);

//	I2C_SendByte(LM75_ADDRESS | 0x01);			//����������ַ 
//	if(I2C_WaitAck()==I2C_TM_ERR){I2C_Stop(); return(I2C_TM_ERR);}

//	TempH = I2C_ReceiveByte();
//	I2C_Ack();
//	TempL = I2C_ReceiveByte();
//	I2C_NoAck();
//	I2C_Stop();

////	if(TempH==0xFF && TempL==0xFF) return I2C_TM_ERR;
////	TempH = (TempH<<8) | (TempL&0x80);
////	TempH = test;
//	return(TempH);
//}
