#include "ms4525.h"
#include "math.h"


#define CONSTANTS_AIR_GAS_CONST             29			//����ƽ��Ħ������
#define STATIC_PRESSTURE                    10100		//ʹ�ñ�׼����ѹ�����Ƽ���
#define CONSTANTS_ABSOLUTE_NULL_CELSIUS     273.15  //�������
#define CONSTANTS_AIR_DENSITY_SEA_LEVEL_15C	1.185   //��׼�����ܶ�


//#define PressureMax 150
//#define PressureMin 0x333
//#define Range		0x3FFF
u8 Data_Buf[NumByte]={0};														 //IIC��ȡ��������

const float P_min = -1.0f;													 //
const float P_max = 1.0f;




/*********************************************************************************
Function: u16 I2C_MS4525_ByteWrite(void) 
Description: MS4525IIC��������
Input:   ��
Output:  IICͨ��״̬��־λ
Return:  1��I2C_TM_ERR  IIC���� 
         2��I2C_TIMEOUT IIC��ʱ 
         3��I2C_TM_OK   IIC����
time:2018��12��21����ǰ
by��liunian
**********************************************************************************/


u16 I2C_MS4525_ByteWrite(void) 		//��4�ֽ����� ֻ��������
{
	u8* pBuffer=Data_Buf;
	u8 NumByteToRead=NumByte;
	if(I2C_TM_ERR==I2C_Start())		  //I2C���� ��ʱ�˳�
	{
		return(I2C_TM_ERR);
	}
	I2C_SendByte(MS4525_ReadAddr);
	if(I2C_WaitAck()==I2C_TM_ERR)	  //�ȴ�Ӧ�� ��ʱ�˳�
	{
		I2C_Stop();
		return(I2C_TM_ERR);
	}
	while(NumByteToRead)
	{
		*pBuffer = I2C_ReceiveByte();
		if(NumByteToRead == 1)		    //���һλ��Ӧ��
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
Description: ����ѹ��
Input: uint32_t Pressure �Ӵ��������ԭʼ����
Output:  ѹ�� ��λpa
Return:  
time:2018��12��21����ǰ
by��liunian
**********************************************************************************/



float calculate_pressure(uint32_t Pressure)
{
	float pre_float=0.0;
//	pre_float=(0.9*Range*Pressure)/(PressureMax-PressureMin)+0.05*Range;
//	pre_float=(Pressure-PressureMin)*0.00202+1;
	pre_float= -((Pressure - 0.1f * 16383) * (P_max - P_min) / (0.8f * 16383) + P_min);
//	if(pre_float<0.018f && pre_float>-0.018f)  pre_float=0;			//ȥ��Ư��
//	else if(pre_float>-0.018f)pre_float=0;
	return pre_float;//����
}


/*********************************************************************************
Function: float calculate_Temperature(uint32_t Temperature)
Description: ���㻷���¶�
Input: uint32_t Temperature �Ӵ��������ԭʼ����
Output:  �¶�
Return:  
time:2018��12��21����ǰ
by��liunian
**********************************************************************************/


float calculate_Temperature(uint32_t Temperature)
{
	float Tem_float=0.0;
	Tem_float=((200.0f * Temperature) / 2047) - 50;
	return Tem_float;
}

/*********************************************************************************
Function: float get_air_density( float temperature_celsius)
Description:��������ܶ�
Input: float temperature_celsius �����¶� ��λ���϶�
Output:  �����ܶ� ��λkg/m3
Return:  
time:2018��12��21����ǰ
by��liunian
**********************************************************************************/


float get_air_density( float temperature_celsius)
{
	return STATIC_PRESSTURE / (CONSTANTS_AIR_GAS_CONST * (temperature_celsius + CONSTANTS_ABSOLUTE_NULL_CELSIUS));
}



/*********************************************************************************
Function: float calc_indicated_airspeed(float differential_pressure)
Description:����ָʾ����
Input: float differential_pressure ��ѹ���� ��λpa
Output:  ָʾ���� ��λm/s
Return:  
time:2018��12��21����ǰ
by��liunian
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
Description:ͨ��ָʾ���ٻ���ʵ�ʿ���
Input: float speed_indicated ָʾ����,float pressure_ambient ����ѹ��,float temperature_celsius�����¶� ���϶�
Output:  ʵ�ʿ��� ��λm/s
Return:  
time:2018��12��21����ǰ
by��liunian
**********************************************************************************/

float calc_true_airspeed_from_indicated(float speed_indicated, float pressure_ambient, float temperature_celsius)
{
	return speed_indicated * sqrtf(CONSTANTS_AIR_DENSITY_SEA_LEVEL_15C / get_air_density(temperature_celsius))-10;
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
    state->q = 0.5;//10e-6;  /* predict noise convariance */
    state->r = 50;//10e-5;  /* measure error convariance */
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

/*********************************************************************************
Function: int ftos(float num,char *s,int n)
Description:������ת�ַ���
Input: float num ������,char *s���ַ����Ĵ洢ָ�� ,int n ת����λ��
Output: false ��ʾת������  true ��ʾת����ȷ
Return: true or false
time:2018��12��22��
by��liunian
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
