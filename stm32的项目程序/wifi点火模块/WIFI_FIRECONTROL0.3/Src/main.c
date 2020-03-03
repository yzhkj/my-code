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
#include "key.h"
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

/* USER CODE END 0 */

int main(void)
{

  /* USER CODE BEGIN 1 */
  u8 key_sta1=0;
  u8 key_sta2=0;
  u8 key_old_sta=0;
  u8 old_flg=0;
  u8 Count=0;
  u8 Send_Date1=0;        //µ±Ç°·¢ËÍÊý¾Ý
  u8 Send_Date2=0;
  u8 Send_flag=0;
  u8 key_state=0;
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
  MX_USART3_UART_Init();

  /* USER CODE BEGIN 2 */
  HAL_Delay(3000);
//  HAL_Delay(3000);
  printf("AT+CIPSTART=\"UDP\",\"255.255.255.255\",1000,5000,0\r\n");
  HAL_Delay(1500);
  printf("AT+CIPMODE=1\r\n");
  HAL_Delay(500);
  printf("AT+CIPSEND\r\n");
  HAL_Delay(500);
  
  
  
//  printf("Init ok\r\n");
//  HAL_UART_Receive_IT(&huart3, (u8 *)aRxBuffer, RXBUFFERSIZE);//¸Ãº¯Êý»á¿ªÆô½ÓÊÕÖÐ¶Ï£º±êÖ¾Î»UART_IT_RXNE£¬²¢ÇÒÉèÖÃ½ÓÊÕ»º³åÒÔ¼°½ÓÊÕ»º³å½ÓÊÕ×î´óÊý¾ÝÁ
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
  /* USER CODE END WHILE */
    
  /* USER CODE BEGIN 3 */
	  
	  if(USART_RX_STA&0x8000)
	  {
//		  printf("recive data\r\n");
		  USART_RX_STA=0;
		  if(USART_RX_BUF[0] == 'O' && USART_RX_BUF[1] == 'K')
			  ;
//		  HAL_UART_Receive_IT(&huart3, (u8 *)aRxBuffer, RXBUFFERSIZE);
	  }
	  key_sta1=KEY_Scan_GroupOne(1);     //Ö§³ÖÁ¬Ðø°´¼ü
	  key_sta2=KEY_Scan_GroupTwo(0);     //²»Ö§³ÖÁ¬Ðø°´¼ü
//	  if(key_sta == key_old_sta )  
//	  {
//		  old_flg=1;
//	  }
////      else if(key_sta != key_old_sta || key_sta == NONE_PRES)
//	  else if(key_sta != key_old_sta)
//	  {
//		  old_flg=0;
//	  }	

	  
	  switch(key_sta1)
	  {
		  case NONE_PRES:
			  Send_Date1 = NONE_STATE;
		      break;
		  case KEY0_PRES:
		  case KEY1_PRES:
		  case KEY2_PRES:
		  case KEY3_PRES:
//			  key_old_sta = key_sta1;
//			  printf("0X%x\r\n",key_sta);		//´øËÉÊÖ¼ì²â£¬·¢ËÍÊµÊ±×´Ì¬
		      Send_Date1 = key_sta1;
		      break;
	      default:
			  Send_Date1 = NONE_STATE;
              break;			  
	  }
	  switch(key_sta2)
	  {
		  case NONE_PRES:
//			  if(Send_flag)
//			  {
//				  Send_flag  = 0;
//				  Send_Date2 = NONE_STATE;
//			  }
			  break;
		  case KEY4_PRES:
			  key_state ^= KEY4_PRES;
		      break; 
		  case KEY5_PRES:
			  key_state ^= KEY5_PRES;
		      break; 
		  case KEY6_PRES:
			  key_state ^= KEY6_PRES;
		      break; 
		  case KEY7_PRES:
			  key_state ^= KEY7_PRES;
		      break; 			  

//		      Send_Date2 = key_sta2;
			  break;
			  
		  default:
//			  printf("0X%x\r\n",NONE_STATE);
//			  Send_Date2 = NONE_STATE;
		      break;
			  
	  }
	  
	  HAL_Delay(10);
	  Count++;
	  if(Count>10)
	  {
		  Count=0;
		  Send_flag=1;
		  printf("0X%x%x\r\n",Send_Date1,key_state);
	  }
//	  if(key_sta)
//	  {
//		  printf("0X%d\r\n",key_sta);
////		  HAL_UART_Receive_IT(&huart3, (u8 *)aRxBuffer, RXBUFFERSIZE);
//	  }


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
