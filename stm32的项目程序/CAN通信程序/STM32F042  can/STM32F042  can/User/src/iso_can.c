	/******************** (C) COPYRIGHT  风驰嵌入式开发工作室 ********************
 * 文件名  ：iso_can.c
 * 描述    ：STM32F0-CAN       
 * 实验平台：M0-ISO开发板
 * 库版本  ：V1.3.0
 * 作者    ：风驰 QQ:779814207/2366260464
 * 博客    ：
 * 淘宝    ：http://shop71177993.taobao.com/
 * 修改时间: 2014-12-15
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

/* 在中断处理函数中返回 */
uint8_t Receive_Buffer_Len=0;
uint8_t ReceiveBuffer[255];
uint8_t *pReceiveBuffer=ReceiveBuffer;

volatile TestStatus TestRx;	

/*
 * 函数名：CAN_NVIC_Configuration
 * 描述  ：CAN RX0 中断优先级配置
 * 输入  ：无
 * 输出  : 无
 * 调用  ：内部调用
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
 * 函数名：CAN_GPIO_onfiguration
 * 描述  ：CAN GPIO 和时钟配置
 * 输入  ：无
 * 输出  : 无
 * 调用  ：内部调用
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
 * 函数名：CAN_Polling
 * 描述  ：配置 CAN 的工作模式为 回环模式
 * 输入  ：无
 * 输出  : -PASSED   成功
 *         -FAILED   失败
 * 调用  ：内部调用
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
	CAN_InitStructure.CAN_TTCM=DISABLE;						 // 时间触发通信禁止
	CAN_InitStructure.CAN_ABOM=DISABLE;						 // 离线退出是在中断置位清0后退出
	CAN_InitStructure.CAN_AWUM=DISABLE;						 // 自动唤醒模式：清零sleep
	CAN_InitStructure.CAN_NART=DISABLE;						 // 自动重新传送豹纹，知道发送成功
	CAN_InitStructure.CAN_RFLM=DISABLE;						 // FIFO没有锁定，新报文覆盖旧报文  
	CAN_InitStructure.CAN_TXFP=DISABLE;						 // 发送报文优先级确定：标志符
	CAN_InitStructure.CAN_Mode=CAN_Mode_LoopBack;	 // 回环模式
	CAN_InitStructure.CAN_SJW=CAN_SJW_1tq;				 // 1tq、BS1、BS2的值跟波特率有关
	CAN_InitStructure.CAN_BS1=CAN_BS1_8tq;
	CAN_InitStructure.CAN_BS2=CAN_BS2_7tq;
	CAN_InitStructure.CAN_Prescaler=5;             // 分频系数为5
	CAN_Init(CAN, &CAN_InitStructure);            // 初始化CAN1 
	
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
	TxMessage.StdId=0x11;				// 设定标准标识符（11位，扩展的为29位）
	TxMessage.RTR=CAN_RTR_DATA;	// 传输消息的帧类型为数据帧（还有远程帧）
	TxMessage.IDE=CAN_ID_STD;		// 消息标志符实验标准标识符
	TxMessage.DLC=2;					  // 发送两帧，一帧8位
	TxMessage.Data[0]=0xCA;			// 第一帧数据
	TxMessage.Data[1]=0xFE;			// 第二帧数据
	
	TransmitMailbox=CAN_Transmit(CAN, &TxMessage);
	i = 0;
	// 用于检查消息传输是否正常
	while((CAN_TransmitStatus(CAN, TransmitMailbox) != CANTXOK) && (i != 0xFF))
	{
		i++;
	}
	
	i = 0;
	// 检查返回的挂号的信息数目
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
	
	/* 判断发送的信息和接收的信息是否相等 */
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
 * 函数名：CAN_Interrupt
 * 描述  ：配置 CAN 的工作模式为 中断模式
 * 输入  ：无
 * 输出  : -PASSED   成功
 *         -FAILED   失败
 * 调用  ：内部调用
 */
static void CAN_InterruptMode_Configuration(void)
{
	CAN_InitTypeDef        CAN_InitStructure;
	CAN_FilterInitTypeDef  CAN_FilterInitStructure;

	/* CAN register init */
	CAN_DeInit(CAN);
	CAN_StructInit(&CAN_InitStructure);
	
	/* CAN cell init */
	CAN_InitStructure.CAN_TTCM=DISABLE;           // 时间触发通信禁止
	CAN_InitStructure.CAN_ABOM=DISABLE;	          // 离线退出是在中断置位清0后退出
	CAN_InitStructure.CAN_AWUM=DISABLE;	          // 自动唤醒模式：清零sleep
	CAN_InitStructure.CAN_NART=DISABLE;	          // 自动重新传送豹纹，知道发送成功
	CAN_InitStructure.CAN_RFLM=DISABLE;	          // FIFO没有锁定，新报文覆盖旧报文
	CAN_InitStructure.CAN_TXFP=DISABLE;           // 发送报文优先级确定：标志符
	CAN_InitStructure.CAN_Mode=CAN_Mode_Normal; // 正常模式
	CAN_InitStructure.CAN_SJW=CAN_SJW_1tq;        // 1tq、BS1、BS2的值跟波特率有关
	CAN_InitStructure.CAN_BS1=CAN_BS1_8tq;
	CAN_InitStructure.CAN_BS2=CAN_BS2_7tq;
	CAN_InitStructure.CAN_Prescaler=1;					  // 分频系数为1
	CAN_Init(CAN, &CAN_InitStructure);						// 初始化CAN1
	
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
	CAN_ITConfig(CAN, CAN_IT_FMP0, ENABLE); //中断使能
	


}

void CAN_Transmit_Buffer(uint8_t* pBuffer,uint16_t NumByteToWrite)
{
	uint8_t NumOfPake=0,NumOfSingle=0,cnt=0;
	CanTxMsg TxMessage;
	NumOfPake=NumByteToWrite/8 ;
	NumOfSingle=NumByteToWrite%8 ;
	TxMessage.StdId=0x00;					 // 标准标识符为0
	TxMessage.ExtId=0x1234;				 // 设置扩展标示符（29位）
	TxMessage.IDE=CAN_ID_EXT;			 // 使用扩展标识符
	TxMessage.RTR=CAN_RTR_DATA;		 // 消息类型为数据帧，一帧8位
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
 * 函数名：CAN_Init
 * 描述  ：CAN初始化，包括端口初始化和中断优先级初始化
 * 输入  ：无
 * 输出  : 无	 
 * 调用  ：外部调用
 */
void USER_CAN_Init(void)
{
	CAN_NVIC_Configuration();
	CAN_GPIO_Configuration();
}

/*
 * 函数名：CAN_Test
 * 描述  ：CAN 回环模式跟中断模式测试
 * 输入  ：无
 * 输出  : 无	 
 * 调用  ：外部调用
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
	
	printf( "\r\n 这个一个CAN（回环模式和中断模式）测试程序...... \r\n" );
	
	USER_CAN_Init();	
	printf( "\r\n CAN 回环测试初始化成功...... \r\n" );
	
	USER_CAN_Test();	

	while (1)
	{
	
	}
}

/*----------------------------------------END OF FILE---------------------------------------------------*/
