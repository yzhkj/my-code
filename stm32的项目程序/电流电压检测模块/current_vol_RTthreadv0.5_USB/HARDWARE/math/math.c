#include "math.h"


void ResolveNumBit(u16 num,u16* array,u8* len)
{
	u8 i=0;
	u16 n=num;
	u16* a=array;
	do
	{
			
		a[i]=n%10;
				
		n=n/10;
				
		i++;
		
	}while(n>0);

	*len=i;
	
}


/*********************************************************************************
Function: void kalman1_init(kalman1_state *state, float init_x, float init_p)
Description:�������˲�������ʼ��
Input: kalman1_state *state�������ṹ��ָ��,float init_x��ʼ��������,float init_p��ʼ�۲�����
Output:  ��
Return:  ��
time:2018��12��21��
by��liunian
**********************************************************************************/

void kalman1_init(kalman1_state *state, float init_x, float init_p)
{
    state->x = init_x;
    state->p = init_p;
    state->A = 1;
    state->H = 1;
    state->q = 1;     //10e-6;  /* predict noise convariance */
    state->r = 20;      //10e-5;  /* measure error convariance */
}
/*********************************************************************************
Function: float kalman1_filter(kalman1_state *state, float z_measure)
Description:�������˲�
Input: kalman1_state *state�������ṹ��ָ��,float z_measure ԭʼ����
Output:  �˲��������
Return: float state->x
time:2018��12��21��
by��liunian
**********************************************************************************/

float kalman1_filter(kalman1_state *state, float z_measure)
{
    /* Predict */
    state->x = state->A * state->x;
    state->p = state->A * state->A * state->p + state->q;  /* p(n|n-1)=A^2*p(n-1|n-1)+q */

    /* Measurement */
    state->gain = state->p * state->H / (state->p * state->H * state->H + state->r);
    state->x = state->x + state->gain * (z_measure - state->H * state->x);
    state->p = (1 - state->gain * state->H) * state->p;

    return state->x;
}

