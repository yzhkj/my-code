/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
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
#include "main.h"
#include "stm32f0xx_hal.h"
#include "can.h"
#include "usart.h"
#include "gpio.h"

/* USER CODE BEGIN Includes */
#include "i2c_ee.h"
#include "ms4525.h"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */
extern CAN_HandleTypeDef hcan;
extern u8 Data_Buf[NumByte];
u8 can_flag[8]={0x01,0x02,0x03,0x04};
/* USER CODE END 0 */

int main(void)
{

  /* USER CODE BEGIN 1 */
//	uint8_t can_flag;
	uint8_t count=0;
	uint32_t temp=0;
	uint32_t pre_temp=0;
	uint32_t pre_temp2=0;
	float Cal_Pre=0.0;
	float Cal_Tep=0.0;
	float Cal_Des=0.0;
	float Cal_Spe=0.0;
	float Cal_Kal=0.0;
	char Send_Buf[10];
	kalman1_state kalman;
  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();							//gpio���ã���Ҫ��ģ��IIc����
  MX_CAN_Init();							//CAN����������Ϊ500k 
  MX_USART2_UART_Init();			//����ʹ��
  /* USER CODE BEGIN 2 */
  I2C_Init();									//�������ټ� 
  kalman1_init(&kalman,0,0);	//���ڿ��ټ����ݿ������˲�
	printf("��ʼ�����ok\r\n"); 
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
		temp=I2C_MS4525_ByteWrite();				//����MS4525���¶�ѹ������
		switch(temp)
		{
			case I2C_TIMEOUT:									//IIC��ʱ 
				printf("I2C_TIMEOUT\r\n");			//f0��PA2���ŷ��͵�����Ϣ
				break;
			case I2C_TM_ERR:
				printf("I2C_TM_ERR\r\n");
				break;
			case I2C_TM_OK:			
				pre_temp=(uint32_t)(Data_Buf[0]<<8+Data_Buf[1]);  //�ϳ�ѹ���ԭʼ����
				Cal_Pre=calculate_pressure(pre_temp);						  //����ʵ��ѹ�λpsi
				pre_temp2=(uint32_t)(Data_Buf[2]<<3);						  //�ϳ��¶�ԭʼ����
				Cal_Tep=calculate_Temperature(pre_temp2);				  //�����¶��¶�
				Cal_Des=get_air_density(Cal_Tep);								  //��������ܶ�
			  Cal_Spe=calc_indicated_airspeed(6894.757*Cal_Pre);//����ָʾ���� ����ѹ�λpa
				Cal_Spe=calc_true_airspeed_from_indicated(Cal_Spe,10100,Cal_Des);    //����ʵ�ʿ���
			  Cal_Kal=kalman1_filter(&kalman,Cal_Spe);					//�������˲�
			  printf("Kalman: \t%.3f \t %.3f Pa \t Temperature: %.3f \t Speed: \t %.3f\r\n",Cal_Kal,6894.757*Cal_Pre,Cal_Tep,Cal_Spe); //��ӡ����1/�˲���Ŀ��� 2/ѹ�λpa 3/�¶� 4/ʵ�ʿ���
				if(ftos(Cal_Kal,Send_Buf,2))                      //�˲�����ת�ַ���
				{
						CAN_Send_Msg(Send_Buf,8);											//ͨ��can���߷��������ַ��� ��λm/s
				}			  
			  
				break;
			default:
				printf("I2C_OTH_ERR\r\n");
				break;
		} 
		count++;
		HAL_Delay(100);
		if(count>10)
		{
			count=0;
//			printf("running\r\n");		
//		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_2);
		}
  
  }
  /* USER CODE END 3 */

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void _Error_Handler(char * file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1) 
  {
  }
  /* USER CODE END Error_Handler_Debug */ 
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
