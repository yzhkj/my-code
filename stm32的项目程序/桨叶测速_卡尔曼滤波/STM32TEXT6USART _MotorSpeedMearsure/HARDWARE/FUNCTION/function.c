#include "function.h"
#include "math.h"

#define a 				0.5				//平滑度参数
#define MaxChangeValue  100 			//最大变化幅度
#define Max_Value 		2900			//转速最大值
#define Min_Value 		850				//转速最小值
#define Max_Fangcha		250    			//最大方差
#define Num 			3				//fifo的大小 滤波数组的个数

int value=Min_Value;     			//平滑滤波结果
int last_value=Min_Value;      		//上一次平滑滤波值
int last_Revalue=Min_Value;      	//上一次接实的数据
int new_value;       				//限幅滤波后的新值
int old_value=Min_Value;
//int value_buff[Num]={0};	//平均处理的缓存FIFO										//
int value_buff2[Num]={0};	//原始数据缓存FIFO


int filter(int rec_value)   
{ 
	//static uint8_t count=0;				//平均处理的缓存FIFO下标
	static uint8_t orig_count=0;		//原始数据缓存FIFO下标
//	int num_count=0;
//	int sum=0;						//平均处理求和
//	int *point=value_buff;			//
	int *point_f=value_buff2;
	float DataFangcha=0.0;	
	//缓存原始数据							
	*(point_f+(orig_count++))=rec_value;																														
	orig_count=orig_count%Num;
	//限幅消抖滤波  
	if(rec_value<Max_Value && rec_value>Min_Value)
	{
		DataFangcha=fangcha(point_f,Num);	
	    if(DataFangcha>Max_Fangcha)				
	    {
	    	new_value=old_value;
		}
		else
		{
			new_value=rec_value;
			old_value=rec_value;			
		}
	}
	else
	{
		new_value=old_value;
	}
	//平滑滤波
	value=(uint16_t)(a*last_value+(1-a)*new_value); 
	last_value=value;																
	return value;
//	*(point+(count++))=value;	 //缓存数据FIFO																													
//	count=count%Num;			 //计算下标
	
	//求和平均  消除高频抖动
//	for(num_count=0;num_count<Num;num_count++)														
//	{
//		sum+=*(point+num_count);
//	}
//	return (uint16_t)(sum/Num);	
}
float fangcha(int* x,int n)		//求n个数的数组x的方差
{
 	//S=(<x^2>-<x>)^0.5
 	int i;
 	float xaver=0.0, x2aver=0.0;
 	for(i=0;i<n;++i)
    {
  	xaver+=x[i]; x2aver+=x[i]*x[i];
 	}
    xaver/=n; 
	x2aver/=n; 							
    return sqrt(x2aver-xaver*xaver);
}





void kalman1_init(kalman1_state *state, float init_x, float init_p)
{
    state->x = init_x;
    state->p = init_p;
    state->A = 1;
    state->H = 1;
    state->q = 5;//10e-6;  /* predict noise convariance */
    state->r = 2000;//10e-5;  /* measure error convariance */
}


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








//插入排序求最大值（红外测速方案）
//霍尔测速不用此函数
uint16_t SortRank(uint16_t* nums,uint16_t NumsSize)
{
    uint16_t i,j;    
		uint16_t key;
    for(j=1;j<NumsSize;j++)
    {
    	key=nums[j];
        for(i=j-1;((i>0)&&(nums[i]>key));)
        {
					nums[i+1]=nums[i];
					i=i-1;            
        }
        nums[i+1]=key;
    }
    return nums[NumsSize-1]; //返回最大值

}



