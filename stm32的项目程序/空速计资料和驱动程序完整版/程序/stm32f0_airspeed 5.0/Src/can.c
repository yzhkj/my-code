/**
  ******************************************************************************
  * File Name          : CAN.c
  * Description        : This file provides code for the configuration
  *                      of the CAN instances.
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
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
#include "can.h"

#include "gpio.h"

/* USER CODE BEGIN 0 */
#include "usart.h"
CAN_FilterConfTypeDef  				sFilterConfig;
static CanTxMsgTypeDef        TxMessage;
static CanRxMsgTypeDef        RxMessage;
/* USER CODE END 0 */

CAN_HandleTypeDef hcan;

/* CAN init function */
void MX_CAN_Init(void)
{

  hcan.Instance = CAN;
	hcan.pTxMsg=&TxMessage;     				//发送消息
	hcan.pRxMsg=&RxMessage;     				//接收消息
  hcan.Init.Prescaler = 1;					  //CAN_MODE_LOOPBACK
  hcan.Init.Mode = CAN_MODE_NORMAL; //CAN_MODE_NORMAL  
  hcan.Init.SJW = CAN_SJW_1TQ;
  hcan.Init.BS1 = CAN_BS1_8TQ;
  hcan.Init.BS2 = CAN_BS2_7TQ;
  hcan.Init.TTCM = DISABLE;
  hcan.Init.ABOM = DISABLE;
  hcan.Init.AWUM = DISABLE;
  hcan.Init.NART = DISABLE;
  hcan.Init.RFLM = DISABLE;
  hcan.Init.TXFP = DISABLE;
  if (HAL_CAN_Init(&hcan) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

void HAL_CAN_MspInit(CAN_HandleTypeDef* canHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct;
  if(canHandle->Instance==CAN)
  {
  /* USER CODE BEGIN CAN_MspInit 0 */

  /* USER CODE END CAN_MspInit 0 */
    /* CAN clock enable */
    __HAL_RCC_CAN1_CLK_ENABLE();
  
    /**CAN GPIO Configuration    
    PA11     ------> CAN_RX
    PA12     ------> CAN_TX 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF4_CAN;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF4_CAN;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    /* CAN interrupt Init */
    __HAL_CAN_ENABLE_IT(&hcan,CAN_IT_FMP0);//FIFO0消息挂起中断允许.	 
	  HAL_NVIC_SetPriority(CEC_CAN_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(CEC_CAN_IRQn);
  /* USER CODE BEGIN CAN_MspInit 1 */
		Configure_Filter();		 
  /* USER CODE END CAN_MspInit 1 */
  }
}

void HAL_CAN_MspDeInit(CAN_HandleTypeDef* canHandle)
{

  if(canHandle->Instance==CAN)
  {
  /* USER CODE BEGIN CAN_MspDeInit 0 */

  /* USER CODE END CAN_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_CAN1_CLK_DISABLE();
  
    /**CAN GPIO Configuration    
    PA11     ------> CAN_RX
    PA12     ------> CAN_TX 
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_11|GPIO_PIN_12);

    /* CAN interrupt Deinit */
    HAL_NVIC_DisableIRQ(CEC_CAN_IRQn);
  /* USER CODE BEGIN CAN_MspDeInit 1 */

  /* USER CODE END CAN_MspDeInit 1 */
  }
} 

/* USER CODE BEGIN 1 */


/*********************************************************************************
Function: void HAL_CAN_RxCpltCallback(CAN_HandleTypeDef* hcan1)
Description: CAN接收中断回调函数 接收数据后由串口打印
Input:   CAN外设句柄
Output:  无
Return:  
time:2018年12月21日以前
by：liunian
**********************************************************************************/



void HAL_CAN_RxCpltCallback(CAN_HandleTypeDef* hcan1)
{
    int i=0;
    //CAN_Receive_IT()函数会关闭FIFO0消息挂号中断，因此我们需要重新打开
    __HAL_CAN_ENABLE_IT(&hcan,CAN_IT_FMP0);//重新开启FIF00消息挂号中断
    printf("Stid:%d\r\n",hcan.pRxMsg->StdId);
	  printf("Exid:0x%x\r\n",hcan.pRxMsg->ExtId);
    printf("ide:%d\r\n",hcan.pRxMsg->IDE);
    printf("rtr:%d\r\n",hcan.pRxMsg->RTR);
    printf("len:%d\r\n",hcan.pRxMsg->DLC);
    for(i=0;i<8;i++)											//中断接收函数，多余位为255
    printf("rxbuf[%d]:%d\r\n",i,hcan.pRxMsg->Data[i]);
}


/*********************************************************************************
Function: u8 CAN_Send_Msg(u8* msg,u8 len)
Description: CAN发送函数 标准id 0x01  扩展id 0x1314
Input:   u8* msg 发送消息指针, u8 len 发送长度
Output:  发送函数状态标识
Return:  0 ：发送失败  1：发送成功
time:2018年12月21日以前
by：
**********************************************************************************/

//ID设置必须参考接收机的ID滤波器，不然无法接收
u8 CAN_Send_Msg(u8* msg,u8 len)
{	
		
    u16 i=0;
		hcan.pTxMsg = &TxMessage;
    hcan.pTxMsg->StdId=0x01;        //标准标识符
    hcan.pTxMsg->ExtId=0x1314;        //扩展标识符(29位)
    hcan.pTxMsg->IDE=CAN_ID_STD;    //使用标准帧
    hcan.pTxMsg->RTR=CAN_RTR_DATA;  //数据帧
    hcan.pTxMsg->DLC=len;                
    for(i=0;i<len;i++)
	  {
			hcan.pTxMsg->Data[i]=msg[i];
		}
    if(HAL_CAN_Transmit(&hcan,100)!=HAL_OK) return 1;     //发送
    return 0;		
}


/*********************************************************************************
Function: void SendData(void)
Description: CAN测试发送程序
Input:   无
Output:  无
Return:  
time:2018年12月21日以前
by：
**********************************************************************************/


void SendData(void)
{

  hcan.pTxMsg = &TxMessage;
  hcan.pRxMsg = &RxMessage;
  hcan.pTxMsg->StdId = 0x00;//0x1314;
	hcan.pTxMsg->ExtId = 0x1314;
  hcan.pTxMsg->RTR = CAN_RTR_DATA;
  hcan.pTxMsg->IDE = CAN_ID_EXT;
  hcan.pTxMsg->DLC = 8;
  hcan.pTxMsg->Data[0] = 'C';
  hcan.pTxMsg->Data[1] = 'A';
  hcan.pTxMsg->Data[2] = 'N';
  hcan.pTxMsg->Data[3] = ' ';
  hcan.pTxMsg->Data[4] = 'T';
  hcan.pTxMsg->Data[5] = 'e';
  hcan.pTxMsg->Data[6] = 's';
  hcan.pTxMsg->Data[7] = 'c';
 
	if(HAL_CAN_Transmit(&hcan, 100) != HAL_OK)
	{
	}
	
}

/*********************************************************************************
Function: void Configure_Filter(void)
Description: CAN配置接收过滤器 无id滤波作用
Input:   无
Output:  无
Return:  
time:2018年12月21日以前
by：
**********************************************************************************/


void Configure_Filter(void)
{
	sFilterConfig.FilterNumber = 0;                   //过滤器0
  sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK; //工作在标识符屏蔽位模式
  sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;//滤波器宽度32位	
		//以下设置只接收ID位0x1314的发送机的数据
//  sFilterConfig.FilterIdHigh =(((unsigned int)0x1314<<3)&0xFFFF0000)>>16; //要过滤id高位
//  sFilterConfig.FilterIdLow = (((unsigned int)0x1314<<3)|CAN_ID_EXT|CAN_RTR_DATA)&0xFFFF;//过滤id的地位
//  sFilterConfig.FilterMaskIdHigh = 0xffff;
//  sFilterConfig.FilterMaskIdLow = 0xffff;
  sFilterConfig.FilterIdHigh=0X0000;     //32位ID
  sFilterConfig.FilterIdLow=0X0000;
  sFilterConfig.FilterMaskIdHigh=0X0000; //32位MASK
  sFilterConfig.FilterMaskIdLow=0X0000;  
  sFilterConfig.FilterFIFOAssignment =CAN_FILTER_FIFO0;//过滤器被关联FIFO0;
  sFilterConfig.FilterActivation = ENABLE;//使能过滤器
  sFilterConfig.BankNumber = 14;
  HAL_CAN_ConfigFilter(&hcan, &sFilterConfig);
}

/* USER CODE END 1 */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
