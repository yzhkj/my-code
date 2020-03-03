#ifndef _DELAY_H
#define _DELAY_H

#define MFRL               (8000000)   //CPUÖ÷Æµ
#define CPU_F              ((double)MFRL)
#define delay_us(x)        _delay_cycles((long)(CPU_F*(double)x/1000000.0))
#define delay_ms(x)        _delay_cycles((long)(CPU_F*(double)x/1000.0))



#endif