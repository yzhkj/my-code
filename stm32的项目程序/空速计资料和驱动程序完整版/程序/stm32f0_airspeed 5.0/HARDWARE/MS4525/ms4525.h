#ifndef _MS4525_H
#define _MS4525_H

#include "main.h"
#include "stm32f0xx_hal.h"
#include "i2c_ee.h"

#define MS4525_ReadAddr  0x51  //4525读地址
#define MS4525_WriteAddr 0x50	 //写地址

#define NumByte		4  				//定义接收数据位数

//卡尔曼滤波 
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




u16 I2C_MS4525_ByteWrite(void);
float calculate_pressure(uint32_t pressure);
float calculate_Temperature(uint32_t Temperature);
float get_air_density( float temperature_celsius);
float calc_indicated_airspeed(float differential_pressure);
float calc_true_airspeed_from_indicated(float speed_indicated,
         	float pressure_ambient, float temperature_celsius);
void kalman1_init(kalman1_state *state, float init_x, float init_p);
float kalman1_filter(kalman1_state *state, float z_measure);
int ftos(float num,char *s,int n);
#endif

