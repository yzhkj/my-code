#ifndef __flydata_H
#define __flydata_H
#include "stm32f4xx.h"
//力油门角度 结构
typedef struct PTAdata {
    u16 Pow;
    u16 Tps;
    u16 Ang;
} PTA;
PTA PatData[45];

#endif
