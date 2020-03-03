#ifndef __GET_PWM__
#define __GET_PWM__

#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////
//   ‰»Î  ‰≥ˆ IO
//////////////////////////////////////////////////////////////////////////////////


//in
void PWM1_CH1_Cap_Init(u32 arr,u16 psc);
void PWM2_CH1_Cap_Init(u32 arr,u16 psc);
void PWM3_CH1_Cap_Init(u32 arr,u16 psc);
void PWM4_CH1_Cap_Init(u32 arr,u16 psc);
void PWM5_CH1_Cap_Init(u32 arr,u16 psc);
//out
void PWM1_CH1_Out_Init(u32 arr,u32 psc);
void PWM2_CH1_Out_Init(u32 arr,u32 psc);
void PWM3_CH1_Out_Init(u32 arr,u32 psc);
void PWM4_CH1_Out_Init(u32 arr,u32 psc);
void PWM5_CH1_Out_Init(u32 arr,u32 psc);
#endif
