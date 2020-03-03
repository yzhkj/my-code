#ifndef _LM75AD_H
#define _LM75AD_H

#include "sys.h"
#include "myiic.h"

#define LM75AD_ADDR 0x90   //A0½Óvcc A1 A2½ÓGND

void I2C_WriteByte(u8 mode,u8 config,u8 addr);
u8 *I2C_ReadByte(u8 Rec_mode,u8 addr,u8 time);


void LM75AD_Init(void);

u16 LM75_Temp(void);

#endif

