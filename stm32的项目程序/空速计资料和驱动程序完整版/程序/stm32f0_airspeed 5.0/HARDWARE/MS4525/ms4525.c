#include "ms4525.h"
#include "math.h"


#define CONSTANTS_AIR_GAS_CONST             29			//空气平均摩尔质量
#define STATIC_PRESSTURE                    10100		//使用标准大气压，近似计算
#define CONSTANTS_ABSOLUTE_NULL_CELSIUS     273.15  //绝对零度
#define CONSTANTS_AIR_DENSITY_SEA_LEVEL_15C	1.185   //标准空气密度


//#define PressureMax 150
//#define PressureMin 0x333
//#define Range		0x3FFF
u8 Data_Buf[NumByte]={0};														 //IIC获取数据数组

const float P_min = -1.0f;													 //
const float P_max = 1.0f;




/*********************************************************************************
Function: u16 I2C_MS4525_ByteWrite(void) 
Description: MS4525IIC驱动程序
Input:   无
Output:  IIC通信状态标志位
Return:  1、I2C_TM_ERR  IIC错误 
         2、I2C_TIMEOUT IIC超时 
         3、I2C_TM_OK   IIC正常
time:2018年12月21日以前
by：liunian
**********************************************************************************/


u16 I2C_MS4525_ByteWrite(void) 		//读4字节数据 只包含空速
{
	u8* pBuffer=Data_Buf;
	u8 NumByteToRead=NumByte;
	if(I2C_TM_ERR==I2C_Start())		  //I2C启动 超时退出
	{
		return(I2C_TM_ERR);
	}
	I2C_SendByte(MS4525_ReadAddr);
	if(I2C_WaitAck()==I2C_TM_ERR)	  //等待应答 超时退出
	{
		I2C_Stop();
		return(I2C_TM_ERR);
	}
	while(NumByteToRead)
	{
		*pBuffer = I2C_ReceiveByte();
		if(NumByteToRead == 1)		    //最后一位不应答
		{
			I2C_NoAck();
		}
		else
		{
			I2C_Ack();
		}
		pBuffer++;
		NumByteToRead--;
	}	
	I2C_Stop();
	return(I2C_TM_OK);	
}


/*********************************************************************************
Function: float calculate_pressure(uint32_t Pressure)
Description: 换算压差
Input: uint32_t Pressure 从传感器测得原始数据
Output:  压差 单位pa
Return:  
time:2018年12月21日以前
by：liunian
**********************************************************************************/



float calculate_pressure(uint32_t Pressure)
{
	float pre_float=0.0;
//	pre_float=(0.9*Range*Pressure)/(PressureMax-PressureMin)+0.05*Range;
//	pre_float=(Pressure-PressureMin)*0.00202+1;
	pre_float= -((Pressure - 0.1f * 16383) * (P_max - P_min) / (0.8f * 16383) + P_min);
//	if(pre_float<0.018f && pre_float>-0.018f)  pre_float=0;			//去除漂移
//	else if(pre_float>-0.018f)pre_float=0;
	return pre_float;//补偿
}


/*********************************************************************************
Function: float calculate_Temperature(uint32_t Temperature)
Description: 换算环境温度
Input: uint32_t Temperature 从传感器测得原始数据
Output:  温度
Return:  
time:2018年12月21日以前
by：liunian
**********************************************************************************/


float calculate_Temperature(uint32_t Temperature)
{
	float Tem_float=0.0;
	Tem_float=((200.0f * Temperature) / 2047) - 50;
	return Tem_float;
}

/*********************************************************************************
Function: float get_air_density( float temperature_celsius)
Description:计算空气密度
Input: float temperature_celsius 环境温度 单位摄氏度
Output:  空气密度 单位kg/m3
Return:  
time:2018年12月21日以前
by：liunian
**********************************************************************************/


float get_air_density( float temperature_celsius)
{
	return STATIC_PRESSTURE / (CONSTANTS_AIR_GAS_CONST * (temperature_celsius + CONSTANTS_ABSOLUTE_NULL_CELSIUS));
}



/*********************************************************************************
Function: float calc_indicated_airspeed(float differential_pressure)
Description:计算指示空速
Input: float differential_pressure 差压数据 单位pa
Output:  指示空速 单位m/s
Return:  
time:2018年12月21日以前
by：liunian
**********************************************************************************/

float calc_indicated_airspeed(float differential_pressure)
{
	if (differential_pressure > 0.0f) 
	{
		return sqrtf((2.0f * differential_pressure) / CONSTANTS_AIR_DENSITY_SEA_LEVEL_15C);
	} 
	else 
	{
		return -sqrtf((2.0f * fabsf(differential_pressure)) / CONSTANTS_AIR_DENSITY_SEA_LEVEL_15C);
	}

}






/*********************************************************************************
Function: float calc_true_airspeed_from_indicated(float speed_indicated, float pressure_ambient, float temperature_celsius)
Description:通过指示空速换算实际空速
Input: float speed_indicated 指示空速,float pressure_ambient 环境压力,float temperature_celsius环境温渡 摄氏度
Output:  实际空速 单位m/s
Return:  
time:2018年12月21日以前
by：liunian
**********************************************************************************/

float calc_true_airspeed_from_indicated(float speed_indicated, float pressure_ambient, float temperature_celsius)
{
	return speed_indicated * sqrtf(CONSTANTS_AIR_DENSITY_SEA_LEVEL_15C / get_air_density(temperature_celsius))-10;
}
/*********************************************************************************
Function: void kalman1_init(kalman1_state *state, float init_x, float init_p)
Description:卡尔曼滤波函数初始化
Input: kalman1_state *state卡尔曼结构体指针,float init_x初始测量数据,float init_p初始观测数据
Output:  无
Return:  无
time:2018年12月21日
by：liunian
**********************************************************************************/

void kalman1_init(kalman1_state *state, float init_x, float init_p)
{
    state->x = init_x;
    state->p = init_p;
    state->A = 1;
    state->H = 1;
    state->q = 0.5;//10e-6;  /* predict noise convariance */
    state->r = 50;//10e-5;  /* measure error convariance */
}
/*********************************************************************************
Function: float kalman1_filter(kalman1_state *state, float z_measure)
Description:卡尔曼滤波
Input: kalman1_state *state卡尔曼结构体指针,float z_measure 原始数据
Output:  滤波后的数据
Return: float state->x
time:2018年12月21日
by：liunian
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

/*********************************************************************************
Function: int ftos(float num,char *s,int n)
Description:浮点型转字符串
Input: float num 浮点数,char *s：字符串的存储指针 ,int n 转换的位数
Output: false 表示转换错误  true 表示转换正确
Return: true or false
time:2018年12月22日
by：liunian
**********************************************************************************/
#define true 	  1
#define false 	0

int ftos(float num,char *s,int n)
{
	int temp;
	float t=num;
	int pn=0;
	int flag_s=true;
	int flag_z=false;
	int i=0;	
	for(i=n;i>0;i--)
	{ 
		t=t*10;
	} 
//	printf("%f\n",t);
	temp=t;
//	printf("%d\n",temp);
	if(temp<0)
	{
		 temp=-temp;
		 t=-num;
		 flag_s=false;
	}
	if(temp==0)
	{	
		 if(n>0)
		 {
			for( pn=0;pn<n;pn++)
			{
			 	*(s+pn)='0';
			}
			*(s+pn)='\.';
			++pn;
		 }
		 *(s+pn)='0';
		 ++pn;
		 if(!flag_s)
		 {		
			 *(s+pn)='\-';
			++pn;
		 }
		 *(s+pn)='\0';	
	}
	else
	{
		while(temp>0)
		{
		 	if(pn==n && n>0)
			 {
			
				*(s+pn)='\.';
				++pn;
			 }
			 else
			 {
				 *(s+pn)=(temp%10)+'0';
				temp=temp/10;
				++pn;
			 }
		}
		while(pn<n)
		{
			*(s+pn)='0';
			 ++pn;
		}
		if(pn==n)
		 {	
			*(s+pn)='\.';
			++pn;
			if(flag_s)
			{
				*(s+pn)='0';
				  ++pn;
			}
		 }
		 if(!flag_s)
		 {
			if(t<1.0)
			{
				*(s+pn)='\.';
				++pn;
				*(s+pn)='0';
				 ++pn;
			}
			 *(s+pn)='\-';
			 ++pn;
		 }
		*(s+pn)='\0';
	}
//	int i(0),j(pn-1);
	int j=pn-1;
	i=0;
	while(i<j)
	{
		int temp=*(s+i);
		 *(s+i)=*(s+j);
		*(s+j)=temp;
		++i;
		j--;
	}
 	return true;
}
