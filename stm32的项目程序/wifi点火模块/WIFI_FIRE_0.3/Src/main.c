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
#include "main.h"
#include "stm32f1xx_hal.h"
#include "usart.h"
#include "gpio.h"

/* USER CODE BEGIN Includes */
#include "config.h"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/



u8 temp_hex[2]={0xaa,0xaa};


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */
extern u8  USART_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART_RX_STA;         		//接收状态标记	
/* USER CODE BEGIN 0 */





/* USER CODE END 0 */

int main(void)
{

  /* USER CODE BEGIN 1 */
  
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
  MX_GPIO_Init();
  MX_USART1_UART_Init();

  /* USER CODE BEGIN 2 */
  HAL_Delay(1500);
  printf("AT+CIPSTART=\"UDP\",\"255.255.255.255\",5000,1000,0\r\n");
  HAL_Delay(1500);
  printf("AT+CIPMODE=1\r\n");
  HAL_Delay(800);
  printf("AT+CIPSEND\r\n");
  HAL_Delay(800);  
  
  
  

  HAL_GPIO_WritePin(AH2_GPIO_Port,AH2_Pin,GPIO_PIN_RESET);
//  HAL_GPIO_WritePin(AH4_GPIO_Port,AH4_Pin,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(AH5_GPIO_Port,AH5_Pin,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(AH7_GPIO_Port,AH7_Pin,GPIO_PIN_RESET);
  
  
  HAL_GPIO_WritePin(AH1_GPIO_Port,AH1_Pin,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(AH3_GPIO_Port,AH3_Pin,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(AH6_GPIO_Port,AH6_Pin,GPIO_PIN_RESET);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
	  
	  //如果收到正确数据 就进行处理
	  if(USART_RX_STA&0x8000)
	  {
		  printf("OK\r\n");
		  USART_RX_STA=0;
//		  HAL_UART_Receive_IT(&huart3, (u8 *)aRxBuffer, RXBUFFERSIZE);


		  switch(temp_hex[0]&0x0f)
		  {
			  case KEY1_PRES:
				  HAL_GPIO_WritePin(AH2_GPIO_Port,AH2_Pin,GPIO_PIN_SET);
				  break;
			  case KEY2_PRES:
				  HAL_GPIO_WritePin(AH5_GPIO_Port,AH5_Pin,GPIO_PIN_SET);
				  break;
			  case KEY3_PRES:
				  HAL_GPIO_WritePin(AH7_GPIO_Port,AH7_Pin,GPIO_PIN_SET);
				  break;
			  case KEY4_PRES:
				  HAL_GPIO_WritePin(AH2_GPIO_Port,AH2_Pin,GPIO_PIN_SET);
				  HAL_GPIO_WritePin(AH5_GPIO_Port,AH5_Pin,GPIO_PIN_SET);
				  HAL_GPIO_WritePin(AH7_GPIO_Port,AH7_Pin,GPIO_PIN_SET);
				  break;
			  case NONE_STATE:
				  HAL_GPIO_WritePin(GPIOB, AH2_Pin|AH4_Pin, GPIO_PIN_RESET);
				  HAL_GPIO_WritePin(GPIOA, AH5_Pin|AH7_Pin, GPIO_PIN_RESET);
				  break;
			  default:
				  HAL_GPIO_WritePin(GPIOB, AH2_Pin|AH4_Pin, GPIO_PIN_RESET);
				  HAL_GPIO_WritePin(GPIOA, AH5_Pin|AH7_Pin, GPIO_PIN_RESET);				  
				  break;
		  }
		  //按键4
		  switch(temp_hex[1]&KEY4_PRES)
		  {
			  case KEY4_PRES:
				  HAL_GPIO_WritePin(AH1_GPIO_Port,AH1_Pin,GPIO_PIN_SET);
			      break;
			  case NONE_PRES:
				  HAL_GPIO_WritePin(AH1_GPIO_Port,AH1_Pin,GPIO_PIN_RESET);
			      break;
			  default:
				  HAL_GPIO_WritePin(AH1_GPIO_Port,AH1_Pin,GPIO_PIN_RESET);
			      break;				  
		  }
		  //按键5		  
		  switch(temp_hex[1]&KEY5_PRES)
		  {
			  case KEY5_PRES:
				  HAL_GPIO_WritePin(AH3_GPIO_Port,AH3_Pin,GPIO_PIN_SET);
			      break;
			  case NONE_PRES:
				  HAL_GPIO_WritePin(AH3_GPIO_Port,AH3_Pin,GPIO_PIN_RESET);
			      break;
			  default:
				  HAL_GPIO_WritePin(AH3_GPIO_Port,AH3_Pin,GPIO_PIN_RESET);
			      break;				  
		  }
		  //按键6		  
		  switch(temp_hex[1]&KEY6_PRES)
		  {
			  case KEY6_PRES:
				  HAL_GPIO_WritePin(AH6_GPIO_Port,AH6_Pin,GPIO_PIN_SET);
			      break;
			  case NONE_PRES:
				  HAL_GPIO_WritePin(AH6_GPIO_Port,AH6_Pin,GPIO_PIN_RESET);
			      break;
			  default:
				  HAL_GPIO_WritePin(AH6_GPIO_Port,AH6_Pin,GPIO_PIN_RESET);
			      break;				  
		  }
		  //按键7
		  switch(temp_hex[1]&KEY7_PRES)
		  {
			  case KEY7_PRES:
				  HAL_GPIO_WritePin(AH1_GPIO_Port,AH1_Pin,GPIO_PIN_SET);
			      HAL_GPIO_WritePin(AH3_GPIO_Port,AH3_Pin,GPIO_PIN_SET);
			      HAL_GPIO_WritePin(AH6_GPIO_Port,AH1_Pin,GPIO_PIN_SET);
			      break;
			  case NONE_PRES:
//				  HAL_GPIO_WritePin(AH1_GPIO_Port,AH1_Pin,GPIO_PIN_RESET);
//			      HAL_GPIO_WritePin(AH3_GPIO_Port,AH3_Pin,GPIO_PIN_RESET);
//			      HAL_GPIO_WritePin(AH6_GPIO_Port,AH6_Pin,GPIO_PIN_RESET);
			      break;
			  default:
				  HAL_GPIO_WritePin(AH1_GPIO_Port,AH1_Pin,GPIO_PIN_RESET);
			      HAL_GPIO_WritePin(AH3_GPIO_Port,AH3_Pin,GPIO_PIN_RESET);
			      HAL_GPIO_WritePin(AH6_GPIO_Port,AH6_Pin,GPIO_PIN_RESET);
			      break;				  
		  }
	      USART_RX_BUF[4]=0;
		  USART_RX_BUF[3]=0;
		  USART_RX_BUF[2]=0;
	  }
	  HAL_Delay(10);

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
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
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
