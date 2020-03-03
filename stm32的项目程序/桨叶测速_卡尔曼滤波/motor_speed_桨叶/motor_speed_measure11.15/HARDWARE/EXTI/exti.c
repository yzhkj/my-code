#include "exti.h"


uint16_t speed_count=0;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == GPIO_PIN_0)
	{
	/* Toggle LED1 */
		speed_count++;
//		printf("EXTI0");
//		HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
//	BSP_LED_Toggle(LED1);
	}
}

void EXTI0_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI0_IRQn 0 */

  /* USER CODE END EXTI0_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
  /* USER CODE BEGIN EXTI0_IRQn 1 */

  /* USER CODE END EXTI0_IRQn 1 */
}

