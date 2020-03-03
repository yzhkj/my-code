/**
  ******************************************************************************
  * File Name          : TIM.c
  * Description        : This file provides code for the configuration
  *                      of the TIM instances.
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
#include "tim.h"

/* USER CODE BEGIN 0 */
extern uint16_t speed_count;
/* USER CODE END 0 */

//TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim14;

/* TIM3 init function */
//void MX_TIM3_Init(void)
//{
//  TIM_ClockConfigTypeDef sClockSourceConfig;
//  TIM_MasterConfigTypeDef sMasterConfig;

//  htim3.Instance = TIM3;
//  htim3.Init.Prescaler = 0;
//  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
//  htim3.Init.Period = 0;
//  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
//  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
//  {
//    _Error_Handler(__FILE__, __LINE__);
//  }

//  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
//  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
//  {
//    _Error_Handler(__FILE__, __LINE__);
//  }

//  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
//  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
//  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
//  {
//    _Error_Handler(__FILE__, __LINE__);
//  }

//}
/* TIM14 init function */
void MX_TIM14_Init(void)
{
  TIM_OC_InitTypeDef sConfigOC;

  htim14.Instance = TIM14;
  htim14.Init.Prescaler = 840-1;
  htim14.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim14.Init.Period = 200-1;
  htim14.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  if (HAL_TIM_Base_Init(&htim14) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  if (HAL_TIM_PWM_Init(&htim14) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim14, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  HAL_TIM_MspPostInit(&htim14);

}

//void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* tim_baseHandle)
//{

//  if(tim_baseHandle->Instance==TIM3)
//  {
//  /* USER CODE BEGIN TIM3_MspInit 0 */

//  /* USER CODE END TIM3_MspInit 0 */
//    /* TIM3 clock enable */
//    __HAL_RCC_TIM3_CLK_ENABLE();

//    /* TIM3 interrupt Init */
//    HAL_NVIC_SetPriority(TIM3_IRQn, 2, 1);
//    HAL_NVIC_EnableIRQ(TIM3_IRQn);
//  /* USER CODE BEGIN TIM3_MspInit 1 */

//  /* USER CODE END TIM3_MspInit 1 */
//  }
//  else if(tim_baseHandle->Instance==TIM14)
//  {
//  /* USER CODE BEGIN TIM14_MspInit 0 */

//  /* USER CODE END TIM14_MspInit 0 */
//    /* TIM14 clock enable */
//    __HAL_RCC_TIM14_CLK_ENABLE();
//  /* USER CODE BEGIN TIM14_MspInit 1 */

//  /* USER CODE END TIM14_MspInit 1 */
//  }
//}
void HAL_TIM_MspPostInit(TIM_HandleTypeDef* timHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct;
  if(timHandle->Instance==TIM14)
  {
  /* USER CODE BEGIN TIM14_MspPostInit 0 */

  /* USER CODE END TIM14_MspPostInit 0 */
  
    /**TIM14 GPIO Configuration    
    PF9     ------> TIM14_CH1 
    */
    GPIO_InitStruct.Pin = pwm_led0_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_TIM14;
    HAL_GPIO_Init(pwm_led0_GPIO_Port, &GPIO_InitStruct);

  /* USER CODE BEGIN TIM14_MspPostInit 1 */

  /* USER CODE END TIM14_MspPostInit 1 */
  }

}

void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* tim_baseHandle)
{

  if(tim_baseHandle->Instance==TIM3)
  {
  /* USER CODE BEGIN TIM3_MspDeInit 0 */

  /* USER CODE END TIM3_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM3_CLK_DISABLE();

    /* TIM3 interrupt Deinit */
    HAL_NVIC_DisableIRQ(TIM3_IRQn);
  /* USER CODE BEGIN TIM3_MspDeInit 1 */

  /* USER CODE END TIM3_MspDeInit 1 */
  }
  else if(tim_baseHandle->Instance==TIM14)
  {
  /* USER CODE BEGIN TIM14_MspDeInit 0 */

  /* USER CODE END TIM14_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM14_CLK_DISABLE();
  /* USER CODE BEGIN TIM14_MspDeInit 1 */

  /* USER CODE END TIM14_MspDeInit 1 */
  }
} 

/* USER CODE BEGIN 1 */

TIM_HandleTypeDef TIM3_Handler;         //��ʱ��3���

uint8_t  TIM3_CAPTURE_STA=0;	//���벶��״̬		    				
uint32_t	TIM3_CAPTURE_VAL;	//���벶��ֵ(TIM2/TIM5��32λ)


//��ʱ��3��ʱ�ж�  
//arr���Զ���װֵ(TIM2,TIM5��32λ��!!)
//psc��ʱ��Ԥ��Ƶ��
void TIM3_CH1_Cap_Init(uint32_t arr,uint16_t psc)
{  
//    TIM_IC_InitTypeDef TIM3_CH1Config;  
    
    TIM3_Handler.Instance=TIM3;                          //ͨ�ö�ʱ��5
    TIM3_Handler.Init.Prescaler=psc;                     //��Ƶϵ��
    TIM3_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;    //���ϼ�����
    TIM3_Handler.Init.Period=arr;                        //�Զ�װ��ֵ
    TIM3_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;//ʱ�ӷ�Ƶ����
		HAL_TIM_Base_Init(&TIM3_Handler);
//    HAL_TIM_IC_Init(&TIM3_Handler);//��ʼ�����벶��ʱ������
    
//    TIM3_CH1Config.ICPolarity=TIM_ICPOLARITY_RISING;    //�����ز���
//    TIM3_CH1Config.ICSelection=TIM_ICSELECTION_DIRECTTI;//ӳ�䵽TI1��
//    TIM3_CH1Config.ICPrescaler=TIM_ICPSC_DIV1;          //���������Ƶ������Ƶ
//    TIM3_CH1Config.ICFilter=0;                          //���������˲��������˲�
//    HAL_TIM_IC_ConfigChannel(&TIM3_Handler,&TIM3_CH1Config,TIM_CHANNEL_1);//����TIM3ͨ��1
	
//    HAL_TIM_IC_Start_IT(&TIM3_Handler,TIM_CHANNEL_1);   //����TIM5�Ĳ���ͨ��1�����ҿ��������ж�
	HAL_TIM_Base_Start_IT(&TIM3_Handler);
//	__HAL_TIM_ENABLE_IT(&TIM3_Handler,TIM_IT_UPDATE);   //ʹ�ܸ����ж�
}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
    if(htim->Instance==TIM3)
	{
		__HAL_RCC_TIM3_CLK_ENABLE();            //ʹ��TIM3ʱ��
		HAL_NVIC_SetPriority(TIM3_IRQn,2,3);    //�����ж����ȼ�����ռ���ȼ�1�������ȼ�3
		HAL_NVIC_EnableIRQ(TIM3_IRQn);          //����ITM3�ж�   
	}
}

//��ʱ�������жϣ�����������жϴ���ص������� �ú�����HAL_TIM_IRQHandler�лᱻ����
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)//�����жϣ����������ʱִ��
{
	if(htim==(&TIM3_Handler))
	{
//		printf("TIM3\r\n");
//		HAL_GPIO_TogglePin(GPIOF,GPIO_PIN_9);
		TIM3_CAPTURE_STA|=0X40;			//��ʱʱ�䵽
		if(speed_count>3)						//����һ��ת�ٿ�ʼ����
		{
			TIM3_CAPTURE_STA|=0X80;
			printf("speed:%d\r\n",speed_count);
		}
		
		speed_count=0;
	}
	
//	if((TIM3_CAPTURE_STA&0X80)==0)//��δ�ɹ�����
//	{
//			if(TIM3_CAPTURE_STA&0X40)//�Ѿ����񵽸ߵ�ƽ��
//			{
//				if((TIM3_CAPTURE_STA&0X3F)==0X3F)//�ߵ�ƽ̫����
//				{
//					TIM3_CAPTURE_STA|=0X80;		//��ǳɹ�������һ��
//					
//				}else TIM3_CAPTURE_STA++;
//			}	 
//	}		
}


void TIM3_IRQHandler(void)
{
  /* USER CODE BEGIN TIM3_IRQn 0 */

  /* USER CODE END TIM3_IRQn 0 */
  HAL_TIM_IRQHandler(&TIM3_Handler);
  /* USER CODE BEGIN TIM3_IRQn 1 */

  /* USER CODE END TIM3_IRQn 1 */
}

/* USER CODE END 1 */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
