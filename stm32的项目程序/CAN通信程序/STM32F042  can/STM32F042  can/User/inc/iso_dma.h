#ifndef __ISO_DMA_H
#define	__ISO_DMA_H

#include "stm32f0xx.h"

void ISO_DMAChannel_Config(DMA_Channel_TypeDef* DMAy_Channelx,u32 PeripheralBaseAddr,\
						u32 MemoryBaseAddr,u32 DMAChannel_Dir, u32 DMAChannel_Mode,u16 BufferSize);







#endif 

