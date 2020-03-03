/******************** (C) COPYRIGHT  风驰嵌入式开发工作室 ********************
 * 文件名  ：main.c
 * 描述    ：ISO_KEY       
 * 实验平台：M0-ISO开发板
 * 库版本  ：V1.0.0
 * 作者    ：风驰 QQ:779814207/2366260464
 * 博客    ：
 * 淘宝    ：http://shop71177993.taobao.com/
 * 修改时间: 2014-12-15
**********************************************************************************/	
/**
  ******************************************************************************
  * @file    main.c 
  * @author  Fengchi  Technology Team
  * @version V1.0.0
  * @date    15-December-2014
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "iso_usart1.h"
#include "iso_dma.h"
#include "iso_can.h"
/** @addtogroup ISO_KEY_Examples
  * @{
  */

/** @addtogroup ISO_KEY
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f0xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f0xx.c file
     */
	SystemInit ();
	USART1_Config();	
	printf("\r\nFengChi STM32F0 NOTE Board CAN Test...\r\n");
	printf("\r\nTime:%s\r\n", "("__DATE__ " - " __TIME__ ")");
	USART_DMACmd(USART1,USART_DMAReq_Tx | USART_DMAReq_Rx,ENABLE);	
	ISO_DMAChannel_Config(DMA1_Channel2,(u32)&USART1->TDR,(u32)g_DMA_USART_Buffer,\
												DMA_DIR_PeripheralDST,DMA_Mode_Circular,43);
	DMA_Cmd(DMA1_Channel2, ENABLE);
	ISO_DMAChannel_Config(DMA1_Channel3,(u32)&USART1->RDR,(u32)g_DMA_USART_Buffer,\
												DMA_DIR_PeripheralSRC,DMA_Mode_Circular,Max_DMA_USART_Buffer_Len);
	DMA_Cmd(DMA1_Channel3, ENABLE);	
	CAN_Loopback_Test();
  while (1)
  {

  }
}

