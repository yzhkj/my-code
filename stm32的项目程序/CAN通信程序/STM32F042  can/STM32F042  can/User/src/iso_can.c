	/******************** (C) COPYRIGHT  ���Ƕ��ʽ���������� ********************
 * �ļ���  ��iso_can.c
 * ����    ��STM32F0-CAN       
 * ʵ��ƽ̨��M0-ISO������
 * ��汾  ��V1.3.0
 * ����    ����� QQ:779814207/2366260464
 * ����    ��
 * �Ա�    ��http://shop71177993.taobao.com/
 * �޸�ʱ��: 2014-12-15
**********************************************************************************/	
/**
  ******************************************************************************
  * @file    iso_can.c 
  * @author  Fengchi  Technology Team
  * @version V1.3.0
  * @date    15-December-2014
  * @brief   led
  ******************************************************************************
  * @attention
  * CAN_TX<----->PB9
  * CAN_RX<----->PB8
  ******************************************************************************
  */
#include "iso_can.h"
#include "iso_led.h"
#include "iso_usart1.h"
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;

/* ���жϴ������з��� */
uint8_t Receive_Buffer_Len=0;
uint8_t ReceiveBuffer[255];
uint8_t *pReceiveBuffer=ReceiveBuffer;

volatile TestStatus TestRx;	

/*
 * ��������CAN_NVIC_Configuration
 * ����  ��CAN RX0 �ж����ȼ�����
 * ����  ����
 * ���  : ��
 * ����  ���ڲ�����
 */
static void CAN_NVIC_Configuration(void)
{

	NVIC_InitTypeDef NVIC_InitStructure; 
	
	/* Enable the USART1 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = CEC_CAN_IRQn;	 
	NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

/*
 * ��������CAN_GPIO_onfiguration
 * ����  ��CAN GPIO ��ʱ������
 * ����  ����
 * ���  : ��
 * ����  ���ڲ�����
 */
static void CAN_GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA , ENABLE);	                        											 
	
	/* CAN1 Periph clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN, ENABLE);
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource11,GPIO_AF_4);
  GPIO_PinAFConfig(GPIOA,GPIO_PinSource12,GPIO_AF_4);
	
	/* Configure CAN pin: RX */									               // PB8
	
	GPIO_InitStructure.GPIO_Pin    = CAN_RX;
	GPIO_InitStructure.GPIO_Mode   = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_PuPd   = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/* Configure CAN pin: TX */									               // PB9

	GPIO_InitStructure.GPIO_Pin    = CAN_TX;
	GPIO_InitStructure.GPIO_Mode   = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType  = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed  = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd   = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	

}

/*
 * ��������CAN_Polling
 * ����  ������ CAN �Ĺ���ģʽΪ �ػ�ģʽ
 * ����  ����
 * ���  : -PASSED   �ɹ�
 *         -FAILED   ʧ��
 * ����  ���ڲ�����
 */
TestStatus CAN_Polling(void)
{
	CAN_InitTypeDef        CAN_InitStructure;
	CAN_FilterInitTypeDef  CAN_FilterInitStructure;
	CanTxMsg TxMessage;
	CanRxMsg RxMessage;
	uint32_t i = 0;
	uint8_t TransmitMailbox = 0;
	
	/* CAN register init */
	CAN_DeInit(CAN);
	CAN_StructInit(&CAN_InitStructure);
	
	/* CAN cell init */
	CAN_InitStructure.CAN_TTCM=DISABLE;						 // ʱ�䴥��ͨ�Ž�ֹ
	CAN_InitStructure.CAN_ABOM=DISABLE;						 // �����˳������ж���λ��0���˳�
	CAN_InitStructure.CAN_AWUM=DISABLE;						 // �Զ�����ģʽ������sleep
	CAN_InitStructure.CAN_NART=DISABLE;						 // �Զ����´��ͱ��ƣ�֪�����ͳɹ�
	CAN_InitStructure.CAN_RFLM=DISABLE;						 // FIFOû���������±��ĸ��Ǿɱ���  
	CAN_InitStructure.CAN_TXFP=DISABLE;						 // ���ͱ������ȼ�ȷ������־��
	CAN_InitStructure.CAN_Mode=CAN_Mode_LoopBack;	 // �ػ�ģʽ
	CAN_InitStructure.CAN_SJW=CAN_SJW_1tq;				 // 1tq��BS1��BS2��ֵ���������й�
	CAN_InitStructure.CAN_BS1=CAN_BS1_8tq;
	CAN_InitStructure.CAN_BS2=CAN_BS2_7tq;
	CAN_InitStructure.CAN_Prescaler=5;             // ��Ƶϵ��Ϊ5
	CAN_Init(CAN, &CAN_InitStructure);            // ��ʼ��CAN1 
	
	/* CAN filter init */
	CAN_FilterInitStructure.CAN_FilterNumber=0;
	CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask;
	CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit;
	CAN_FilterInitStructure.CAN_FilterIdHigh=0x0000;
	CAN_FilterInitStructure.CAN_FilterIdLow=0x0000;
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0000;
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment=0;
	CAN_FilterInitStructure.CAN_FilterActivation=ENABLE;
	CAN_FilterInit(&CAN_FilterInitStructure);
	
	/* transmit */
	TxMessage.StdId=0x11;				// �趨��׼��ʶ����11λ����չ��Ϊ29λ��
	TxMessage.RTR=CAN_RTR_DATA;	// ������Ϣ��֡����Ϊ����֡������Զ��֡��
	TxMessage.IDE=CAN_ID_STD;		// ��Ϣ��־��ʵ���׼��ʶ��
	TxMessage.DLC=2;					  // ������֡��һ֡8λ
	TxMessage.Data[0]=0xCA;			// ��һ֡����
	TxMessage.Data[1]=0xFE;			// �ڶ�֡����
	
	TransmitMailbox=CAN_Transmit(CAN, &TxMessage);
	i = 0;
	// ���ڼ����Ϣ�����Ƿ�����
	while((CAN_TransmitStatus(CAN, TransmitMailbox) != CANTXOK) && (i != 0xFF))
	{
		i++;
	}
	
	i = 0;
	// ��鷵�صĹҺŵ���Ϣ��Ŀ
	while((CAN_MessagePending(CAN, CAN_FIFO0) < 1) && (i != 0xFF))
	{
		i++;
	}
	
	/* receive */
	RxMessage.StdId=0x00;
	RxMessage.IDE=CAN_ID_STD;
	RxMessage.DLC=0;
	RxMessage.Data[0]=0x00;
	RxMessage.Data[1]=0x00;
	CAN_Receive(CAN, CAN_FIFO0, &RxMessage);
	
	
	if (RxMessage.StdId!=0x11)
	{
		return FAILED;  
	}
	
	if (RxMessage.IDE!=CAN_ID_STD)
	{
		return FAILED;
	}
	
	if (RxMessage.DLC!=2)
	{
		return FAILED;  
	}
	
	/* �жϷ��͵���Ϣ�ͽ��յ���Ϣ�Ƿ���� */
	if ((RxMessage.Data[0]<<8|RxMessage.Data[1])!=0xCAFE)
	{
		return FAILED;
	}
	
	printf("receive data:0X%X,0X%X",RxMessage.Data[0], RxMessage.Data[1]);  
	
	return PASSED; /* Test Passed */
}

/**
  * @brief  Configures the CAN, transmit and receive using interrupt.
  * @param  None
  * @retval : PASSED if the reception is well done, FAILED in other case
  */

/*
 * ��������CAN_Interrupt
 * ����  ������ CAN �Ĺ���ģʽΪ �ж�ģʽ
 * ����  ����
 * ���  : -PASSED   �ɹ�
 *         -FAILED   ʧ��
 * ����  ���ڲ�����
 */
static void CAN_InterruptMode_Configuration(void)
{
	CAN_InitTypeDef        CAN_InitStructure;
	CAN_FilterInitTypeDef  CAN_FilterInitStructure;

	/* CAN register init */
	CAN_DeInit(CAN);
	CAN_StructInit(&CAN_InitStructure);
	
	/* CAN cell init */
	CAN_InitStructure.CAN_TTCM=DISABLE;           // ʱ�䴥��ͨ�Ž�ֹ
	CAN_InitStructure.CAN_ABOM=DISABLE;	          // �����˳������ж���λ��0���˳�
	CAN_InitStructure.CAN_AWUM=DISABLE;	          // �Զ�����ģʽ������sleep
	CAN_InitStructure.CAN_NART=DISABLE;	          // �Զ����´��ͱ��ƣ�֪�����ͳɹ�
	CAN_InitStructure.CAN_RFLM=DISABLE;	          // FIFOû���������±��ĸ��Ǿɱ���
	CAN_InitStructure.CAN_TXFP=DISABLE;           // ���ͱ������ȼ�ȷ������־��
	CAN_InitStructure.CAN_Mode=CAN_Mode_Normal; // ����ģʽ
	CAN_InitStructure.CAN_SJW=CAN_SJW_1tq;        // 1tq��BS1��BS2��ֵ���������й�
	CAN_InitStructure.CAN_BS1=CAN_BS1_8tq;
	CAN_InitStructure.CAN_BS2=CAN_BS2_7tq;
	CAN_InitStructure.CAN_Prescaler=1;					  // ��Ƶϵ��Ϊ1
	CAN_Init(CAN, &CAN_InitStructure);						// ��ʼ��CAN1
	
	/* CAN filter init */
	CAN_FilterInitStructure.CAN_FilterNumber=1;
	CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask;
	CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit;
	CAN_FilterInitStructure.CAN_FilterIdHigh=0x0000;
	CAN_FilterInitStructure.CAN_FilterIdLow=0x0000;
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0000;
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_FIFO0;
	CAN_FilterInitStructure.CAN_FilterActivation=ENABLE;
	CAN_FilterInit(&CAN_FilterInitStructure);
	
	/* CAN FIFO0 message pending interrupt enable */ 
	CAN_ITConfig(CAN, CAN_IT_FMP0, ENABLE); //�ж�ʹ��
	


}

void CAN_Transmit_Buffer(uint8_t* pBuffer,uint16_t NumByteToWrite)
{
	uint8_t NumOfPake=0,NumOfSingle=0,cnt=0;
	CanTxMsg TxMessage;
	NumOfPake=NumByteToWrite/8 ;
	NumOfSingle=NumByteToWrite%8 ;
	TxMessage.StdId=0x00;					 // ��׼��ʶ��Ϊ0
	TxMessage.ExtId=0x1234;				 // ������չ��ʾ����29λ��
	TxMessage.IDE=CAN_ID_EXT;			 // ʹ����չ��ʶ��
	TxMessage.RTR=CAN_RTR_DATA;		 // ��Ϣ����Ϊ����֡��һ֡8λ
	while(NumOfPake--)
	{
				/* transmit 1 message */
			TxMessage.DLC=8;							
			for(cnt=0;cnt<8;cnt++)
			{
				TxMessage.Data[cnt]=* pBuffer;				 
				pBuffer++;
			}
			CAN_Transmit(CAN, &TxMessage);	
	}
	if(NumOfSingle)
	{
		TxMessage.DLC=NumOfSingle;							 
		for(cnt=0;cnt<NumOfSingle;cnt++)
		{
			TxMessage.Data[cnt]=* pBuffer;				 
			pBuffer++;
		}
		CAN_Transmit(CAN, &TxMessage);
	}
	
}


/*
 * ��������CAN_Init
 * ����  ��CAN��ʼ���������˿ڳ�ʼ�����ж����ȼ���ʼ��
 * ����  ����
 * ���  : ��	 
 * ����  ���ⲿ����
 */
void USER_CAN_Init(void)
{
	CAN_NVIC_Configuration();
	CAN_GPIO_Configuration();
}

/*
 * ��������CAN_Test
 * ����  ��CAN �ػ�ģʽ���ж�ģʽ����
 * ����  ����
 * ���  : ��	 
 * ����  ���ⲿ����
 */
void USER_CAN_Test(void)
{
	/* CAN transmit at 100Kb/s and receive by polling in loopback mode */
	TestRx = CAN_Polling();
	
	if (TestRx == FAILED)
	{    
		ISO_LED(LED1,OFF);	// LED1 OFF 		
	}
	else
	{    
		ISO_LED(LED1,ON);	  // LED1 ON;		
	}
	
	/* CAN transmit at 500Kb/s and receive by interrupt in loopback mode */
	CAN_InterruptMode_Configuration();
}


/*-------------------------------------------------------------------------------*/

void CAN_Loopback_Test(void)
{	
	/* LED config */
	LED_GPIO_Config();	
	
	printf( "\r\n ���һ��CAN���ػ�ģʽ���ж�ģʽ�����Գ���...... \r\n" );
	
	USER_CAN_Init();	
	printf( "\r\n CAN �ػ����Գ�ʼ���ɹ�...... \r\n" );
	
	USER_CAN_Test();	

	while (1)
	{
	
	}
}

/*----------------------------------------END OF FILE---------------------------------------------------*/
