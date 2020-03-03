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
#include "can.h"

#include "gpio.h"

/* USER CODE BEGIN 0 */



CAN_FilterConfTypeDef  		  sFilterConfig;
static CanTxMsgTypeDef        TxMessage;
static CanRxMsgTypeDef        RxMessage;

/* USER CODE END 0 */

CAN_HandleTypeDef hcan;

/* CAN init function */
void MX_CAN_Init(void)
{

  hcan.Instance = CAN1;
  hcan.Init.Prescaler = 6;
  hcan.Init.Mode =CAN_MODE_NORMAL; //CAN_MODE_NORMAL;
  hcan.Init.SJW = CAN_SJW_1TQ;
  hcan.Init.BS1 = CAN_BS1_5TQ;
  hcan.Init.BS2 = CAN_BS2_6TQ;
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
  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspInit 0 */

  /* USER CODE END CAN1_MspInit 0 */
    /* CAN1 clock enable */
    __HAL_RCC_CAN1_CLK_ENABLE();
  
    /**CAN GPIO Configuration    
    PA11     ------> CAN_RX
    PA12     ------> CAN_TX 
    */
    GPIO_InitStruct.Pin = CAN_RX_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(CAN_RX_GPIO_Port, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = CAN_TX_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(CAN_TX_GPIO_Port, &GPIO_InitStruct);

  /* USER CODE BEGIN CAN1_MspInit 1 */
    __HAL_CAN_ENABLE_IT(&hcan,CAN_IT_FMP0);//FIFO0��Ϣ�����ж�����.	  
    //CAN1->IER|=1<<1;		//FIFO0��Ϣ�����ж�����.	
    HAL_NVIC_SetPriority(CAN1_RX0_IRQn,2,2);    //��ռ���ȼ�1�������ȼ�2
    HAL_NVIC_EnableIRQ(CAN1_RX0_IRQn);          //ʹ���ж� 
	Configure_Filter();	
  /* USER CODE END CAN1_MspInit 1 */
  }
}

void HAL_CAN_MspDeInit(CAN_HandleTypeDef* canHandle)
{

  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspDeInit 0 */

  /* USER CODE END CAN1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_CAN1_CLK_DISABLE();
  
    /**CAN GPIO Configuration    
    PA11     ------> CAN_RX
    PA12     ------> CAN_TX 
    */
    HAL_GPIO_DeInit(GPIOA, CAN_RX_Pin|CAN_TX_Pin);

  /* USER CODE BEGIN CAN1_MspDeInit 1 */

  /* USER CODE END CAN1_MspDeInit 1 */
  }
} 

/* USER CODE BEGIN 1 */

void CAN1_RX0_IRQHandler(void)
{
    HAL_CAN_IRQHandler(&hcan);//�˺��������CAN_Receive_IT()��������
}

//CAN�жϴ������
//�˺����ᱻCAN_Receive_IT()����
//hcan:CAN���
void HAL_CAN_RxCpltCallback(CAN_HandleTypeDef* hcan1)
{
    int i=0;
    //CAN_Receive_IT()������ر�FIFO0��Ϣ�Һ��жϣ����������Ҫ���´�
    __HAL_CAN_ENABLE_IT(&hcan,CAN_IT_FMP0);//���¿���FIF00��Ϣ�Һ��ж�
    printf("Stid:%d\r\n",hcan.pRxMsg->StdId);
	printf("Exid:%d\r\n",hcan.pRxMsg->ExtId);
    printf("ide:%d\r\n",hcan.pRxMsg->IDE);
    printf("rtr:%d\r\n",hcan.pRxMsg->RTR);
    printf("len:%d\r\n",hcan.pRxMsg->DLC);
    for(i=0;i<8;i++)
    printf("rxbuf[%d]:%d\r\n",i,hcan.pRxMsg->Data[i]);
}


//can����һ������(�̶���ʽ:IDΪ0X12,��׼֡,����֡)	
//len:���ݳ���(���Ϊ8)				     
//msg:����ָ��,���Ϊ8���ֽ�.
//����ֵ:0,�ɹ�;
//		 ����,ʧ��;
u8 CAN1_Send_Msg(u8* msg,u8 len)
{	
    u16 i=0;
	hcan.pTxMsg = &TxMessage;
    hcan.pTxMsg->StdId=0X12;        //��׼��ʶ��
    hcan.pTxMsg->ExtId=0x12;        //��չ��ʶ��(29λ)
    hcan.pTxMsg->IDE=CAN_ID_STD;    //ʹ�ñ�׼֡
    hcan.pTxMsg->RTR=CAN_RTR_DATA;  //����֡
    hcan.pTxMsg->DLC=len;                
    for(i=0;i<len;i++)
    hcan.pTxMsg->Data[i]=msg[i];
    if(HAL_CAN_Transmit(&hcan,10)!=HAL_OK) return 1;     //����
    return 0;		
}

//can�ڽ������ݲ�ѯ
//buf:���ݻ�����;	 
//����ֵ:0,�����ݱ��յ�;
//		 ����,���յ����ݳ���;
u8 CAN1_Receive_Msg(u8 *buf)
{		   		   
 	u8 i;
    if(HAL_CAN_Receive(&hcan,CAN_FIFO0,0)!=HAL_OK) return 0;//�������ݣ���ʱʱ������Ϊ0	
    for(i=0;i<hcan.pRxMsg->DLC;i++)
    buf[i]=hcan.pRxMsg->Data[i];
	return hcan.pRxMsg->DLC;	
}

void SendData(void)
{

  hcan.pTxMsg = &TxMessage;
  hcan.pRxMsg = &RxMessage;
  hcan.pTxMsg->StdId = 0x00;//0x1314;
  hcan.pTxMsg->ExtId = 0x1414;
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
 
  if(HAL_CAN_Transmit(&hcan, 10) != HAL_OK)
  {
	  
  }
	
}


void Configure_Filter(void)
{
	sFilterConfig.FilterNumber = 0;                   //������0
  sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK; //�����ڱ�ʶ������λģʽ
  sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;//�˲������32λ	
		//��������ֻ����IDλ0x1314�ķ��ͻ�������
//  sFilterConfig.FilterIdHigh =(((unsigned int)0x1314<<3)&0xFFFF0000)>>16; //Ҫ����id��λ
//  sFilterConfig.FilterIdLow = (((unsigned int)0x1314<<3)|CAN_ID_EXT|CAN_RTR_DATA)&0xFFFF;//����id�ĵ�λ
//  sFilterConfig.FilterMaskIdHigh = 0xffff;
//  sFilterConfig.FilterMaskIdLow = 0xffff;
  sFilterConfig.FilterIdHigh=0X0000;     //32λID
  sFilterConfig.FilterIdLow=0X0000;
  sFilterConfig.FilterMaskIdHigh=0X0000; //32λMASK
  sFilterConfig.FilterMaskIdLow=0X0000;  
  sFilterConfig.FilterFIFOAssignment =CAN_FILTER_FIFO0;//������������FIFO0;
  sFilterConfig.FilterActivation = ENABLE;//ʹ�ܹ�����
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
