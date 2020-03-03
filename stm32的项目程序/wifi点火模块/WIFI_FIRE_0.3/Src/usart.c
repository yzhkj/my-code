/**
  ******************************************************************************
  * File Name          : USART.c
  * Description        : This file provides code for the configuration
  *                      of the USART instances.
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2019 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "usart.h"

#include "gpio.h"

/* USER CODE BEGIN 0 */


u8 USART_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 USART_RX_STA=0;       //接收状态标记	

u8 aRxBuffer[RXBUFFERSIZE];//HAL库使用的串口接收缓冲


extern u8 temp_hex[2];

void Char_to_Hex(u8 Bit_Two,u8 Bit_One);

/* USER CODE END 0 */

UART_HandleTypeDef huart1;

/* USART1 init function */

void MX_USART1_UART_Init(void)
{

  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct;
  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspInit 0 */

  /* USER CODE END USART1_MspInit 0 */
    /* USART1 clock enable */
    __HAL_RCC_USART1_CLK_ENABLE();
  
    /**USART1 GPIO Configuration    
    PB6     ------> USART1_TX
    PB7     ------> USART1_RX 
    */
    GPIO_InitStruct.Pin = USART1_TX_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(USART1_TX_GPIO_Port, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = USART1_RX_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(USART1_RX_GPIO_Port, &GPIO_InitStruct);

    __HAL_AFIO_REMAP_USART1_ENABLE();

  /* USER CODE BEGIN USART1_MspInit 1 */
    HAL_NVIC_SetPriority(USART3_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
	huart1.Instance->CR1 |=(1<<5);
  /* USER CODE END USART1_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspDeInit 0 */

  /* USER CODE END USART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();
  
    /**USART1 GPIO Configuration    
    PB6     ------> USART1_TX
    PB7     ------> USART1_RX 
    */
    HAL_GPIO_DeInit(GPIOB, USART1_TX_Pin|USART1_RX_Pin);

  /* USER CODE BEGIN USART1_MspDeInit 1 */

  /* USER CODE END USART1_MspDeInit 1 */
  }
} 

/* USER CODE BEGIN 1 */

//串口1中断服务程序
void USART1_IRQHandler(void)                	
{ 
	u8 Res;
//#if SYSTEM_SUPPORT_OS	 	//使用OS
//	OSIntEnter();    
//#endif
//	if((__HAL_UART_GET_FLAG(&huart3,UART_FLAG_RXNE)!=RESET))  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
//	{
//        HAL_UART_Receive(&huart3,&Res,1,1000); 
	if(huart1.Instance->SR&(1<<5))	//接收到数据
	{	
//        HAL_UART_Receive_IT(&huart3, (u8 *)aRxBuffer, RXBUFFERSIZE);		
		Res=huart1.Instance->DR; 	
		if((USART_RX_STA&0x8000)==0)//接收未完成
		{
			if(USART_RX_STA&0x4000)//接收到了0x0d
			{
				if(Res!=0x0a)
				{
					USART_RX_STA=0;//接收错误,重新开始
				}
				else 
				{
					USART_RX_STA|=0x8000;	//接收完成了 
					if(USART_RX_BUF[0] == '0' && USART_RX_BUF[1] == 'X') //帧 头检测
					{
						Char_to_Hex(USART_RX_BUF[3],USART_RX_BUF[2]);
					}
					else
					{
						USART_RX_STA=0;//接收错误,重新开始
					}
				}
			}
			else //还没收到0X0D
			{	
				if(Res==0x0d)USART_RX_STA|=0x4000;
				else
				{
					USART_RX_BUF[USART_RX_STA&0X3FFF]=Res ;
					USART_RX_STA++;
					if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;//接收数据错误,重新开始接收	  
				}		 
			}
		}   		 
	}
//	HAL_UART_IRQHandler(&huart3);	
//#if SYSTEM_SUPPORT_OS	 	//使用OS
//	OSIntExit();  											 
//#endif
} 



int fputc(int ch, FILE *f)
{
		/* 发送一个字节数据到USART1 */
//		HAL_UART_Transmit(&huart3, (uint8_t *)&ch, 1, 0xFFFF);
		
		/* 等待发送完毕 */
//		while (USART_GetFlagStatus(TEST_USART, USART_FLAG_TC) == RESET);		
	while((USART1->SR&0X40)==0);//等待上一次串口数据发送完成  
	USART1->DR = (u8) ch;      	//写DR,串口1将发送数据
	return ch;	
//		return (ch);
}



void Char_to_Hex(u8 Bit_Two,u8 Bit_One)
{
	u8 temp=0;
//	if(Bit_Two == 'a' && Bit_One == 'a')
//		return 0xaa;

	
	//第 一位数据处理
	if( Bit_One> '0' && Bit_One < '9' )
	{
//		temp = temp + (Bit_One-'0')*16;
		temp = Bit_One-'0';
		
	}
	else if(Bit_One == 'a')
	{
		temp=NONE_STATE;
//		temp = temp+0xa0; 
	}
	else
	{
		USART_RX_STA=0;//接收错误,重新开始
		temp=NONE_STATE;
	}
	temp_hex[0] = temp;
//	temp_hex[1] = temp;

	
	//第二位数据处理
//	if(Bit_Two != 'A')
	
//	if(   Bit_Two < 'f' && Bit_Two>= '0')
//	if( Bit_Two> 0x30 && Bit_Two < 0x39 )
	if(Bit_Two>= '0' && Bit_Two <= '9' )
	{
	
		temp = Bit_Two-'0';
//		temp_hex[1] = temp;
		
	}
	else if(Bit_Two >= 'a')
	{
		temp=Bit_Two-'a';
	}
	else
	{		
		USART_RX_STA=0;//接收错误,重新开始
		temp=NONE_STATE;
	}
	temp_hex[1] = temp;
	
	//以下代码不用了，谢谢
		
//	if(temp != NONE_STATE && temp != temp_hex)
//	if(temp != NONE_STATE)
//	{
//		temp_hex = temp;
//	}
//	else if(temp == NONE_STATE && (temp_hex ==KEY0_PRES ||
//								   temp_hex ==KEY2_PRES ||
//								   temp_hex ==KEY4_PRES ||
//								   temp_hex ==KEY4_PRES	||
//                                   temp_hex ==NONE_PRES	  )   )
//	{
//		temp_hex = NONE_STATE;
//		
//	}
//	else
//	{
//		USART_RX_STA=0;//接收错误,重新开始
//	}
//	return temp;
}

/* USER CODE END 1 */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
