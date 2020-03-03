#ifndef __MATH_H
#define __MATH_H


#include "config.h"

//¿¨¶ûÂüÂË²¨ 
typedef struct 
{
    float x;  /* state */
    float A;  /* x(n)=A*x(n-1)+u(n),u(n)~N(0,q) */
    float H;  /* z(n)=H*x(n)+w(n),w(n)~N(0,r)   */
    float q;  /* process(predict) noise convariance */
    float r;  /* measure noise convariance */
    float p;  /* estimated error convariance */
    float gain;
} kalman1_state;


void ResolveNumBit(u16 num,u16* array,u8* len);
void kalman1_init(kalman1_state *state, float init_x, float init_p);
float kalman1_filter(kalman1_state *state, float z_measure);


#endif

