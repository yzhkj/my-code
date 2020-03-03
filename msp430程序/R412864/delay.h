#ifndef __DELAY_H__
#define __DELAY_H__

#define MFRE            (8000000) //CPU的主频，参数随MCLK设置改变，调整延时
#define CPU_F           ((double)MFRE) 
#define delay_us(x)     __delay_cycles((long)(CPU_F*(double)x/1000000.0)) 
#define delay_ms(x)     __delay_cycles((long)(CPU_F*(double)x/1000.0)) 


#endif