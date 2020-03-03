#ifndef __function_H
#define __function_H

#include "stm32f4xx_hal.h"
#include "main.h"

//extern typedef struct kalman1_state;

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


int filter(int rec_value);
float fangcha(int* x,int n);
void kalman1_init(kalman1_state *state, float init_x, float init_p);
float kalman1_filter(kalman1_state *state, float z_measure);
uint16_t SortRank(uint16_t* nums,uint16_t NumsSize);

#endif

