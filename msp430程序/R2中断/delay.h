#ifndef __DELAY_H__
#define __DELAY_H__

#define MFRE            (8000000) //CPU����Ƶ��������MCLK���øı䣬������ʱ
#define CPU_F           ((double)MFRE) 
#define delay_us(x)     __delay_cycles((long)(CPU_F*(double)x/1000000.0)) 
#define delay_ms(x)     __delay_cycles((long)(CPU_F*(double)x/1000.0)) 


#endif