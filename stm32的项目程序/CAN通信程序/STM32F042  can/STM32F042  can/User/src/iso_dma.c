	/******************** (C) COPYRIGHT  ���Ƕ��ʽ���������� ********************
 * �ļ���  ��iso_dma.c
 * ����    ��STM32F0-LED       
 * ʵ��ƽ̨��M0-ISO������
 * ��汾  ��V1.3.0
 * ����    ����� QQ:779814207/2366260464
 * ����    ��
 * �Ա�    ��http://shop71177993.taobao.com/
 * �޸�ʱ��: 2014-12-15
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

  /*����DMAʱ��*/
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	/*����DMAԴ��*/
  DMA_InitStructure.DMA_PeripheralBaseAddr = PeripheralBaseAddr;
	/*�ڴ��ַ(Ҫ����ı�����ָ��)*/
  DMA_InitStructure.DMA_MemoryBaseAddr = MemoryBaseAddr;
	/*���򣺴��ڴ浽����*/	
  DMA_InitStructure.DMA_DIR = DMAChannel_Dir;
	/*�����С*/
  DMA_InitStructure.DMA_BufferSize = BufferSize;
	/*�����ַ����*/
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	/*�ڴ��ַ����*/
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	/*�������ݵ�λ 8bit*/	
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	/*�ڴ����ݵ�λ 8bit*/
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


