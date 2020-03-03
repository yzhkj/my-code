	/******************** (C) COPYRIGHT  风驰嵌入式开发工作室 ********************
 * 文件名  ：iso_dma.c
 * 描述    ：STM32F0-LED       
 * 实验平台：M0-ISO开发板
 * 库版本  ：V1.3.0
 * 作者    ：风驰 QQ:779814207/2366260464
 * 博客    ：
 * 淘宝    ：http://shop71177993.taobao.com/
 * 修改时间: 2014-12-15
**********************************************************************************/	
/**
  ******************************************************************************
  * @file    iso_dma.c 
  * @author  Fengchi  Technology Team
  * @version V1.3.0
  * @date    15-December-2014
  * @brief   led
  ******************************************************************************
  * @attention
  * 
  * 
  ******************************************************************************
  */
#include "iso_dma.h"


void ISO_DMAChannel_Config(DMA_Channel_TypeDef* DMAy_Channelx,u32 PeripheralBaseAddr,\
						u32 MemoryBaseAddr,u32 DMAChannel_Dir, u32 DMAChannel_Mode,u16 BufferSize)
{
	DMA_InitTypeDef  DMA_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

  /*开启DMA时钟*/
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	/*设置DMA源：*/
  DMA_InitStructure.DMA_PeripheralBaseAddr = PeripheralBaseAddr;
	/*内存地址(要传输的变量的指针)*/
  DMA_InitStructure.DMA_MemoryBaseAddr = MemoryBaseAddr;
	/*方向：从内存到外设*/	
  DMA_InitStructure.DMA_DIR = DMAChannel_Dir;
	/*传输大小*/
  DMA_InitStructure.DMA_BufferSize = BufferSize;
	/*外设地址不增*/
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	/*内存地址自增*/
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	/*外设数据单位 8bit*/	
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	/*内存数据单位 8bit*/
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  DMA_InitStructure.DMA_Mode = DMAChannel_Mode;
  DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  DMA_Init(DMAy_Channelx, &DMA_InitStructure);

  /* Enable DMA1 Channelx Transfer Complete interrupt */
  DMA_ITConfig(DMAy_Channelx, DMA_IT_TC, ENABLE);

  /* Enable DMA1 channel2 IRQ Channel */
  NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel2_3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  DMA_Cmd(DMAy_Channelx, DISABLE);
}


