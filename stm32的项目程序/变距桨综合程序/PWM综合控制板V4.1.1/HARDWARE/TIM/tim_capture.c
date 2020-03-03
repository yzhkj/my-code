#include "tim_capture.h"
#include "math.h"

#define a 				0.5				//ƽ���Ȳ���
#define MaxChangeValue  100 			//���仯����
#define Max_Value 		2900			//ת�����ֵ
#define Min_Value 		850				//ת����Сֵ
#define Max_Fangcha		250    			//��󷽲�
#define Num 			3				//fifo�Ĵ�С �˲�����ĸ���

int value=Min_Value;     			//ƽ���˲����
int last_value=Min_Value;      		//��һ��ƽ���˲�ֵ
int last_Revalue=Min_Value;      	//��һ�ν�ʵ������
int new_value;       				//�޷��˲������ֵ
int old_value=Min_Value;
//int value_buff[Num]={0};	//ƽ������Ļ���FIFO										//
int value_buff2[Num]={0};	//ԭʼ���ݻ���FIFO


int filter(int rec_value)   
{ 
	//static uint8_t count=0;				//ƽ������Ļ���FIFO�±�
	static uint8_t orig_count=0;		//ԭʼ���ݻ���FIFO�±�
//	int num_count=0;
//	int sum=0;						//ƽ���������
//	int *point=value_buff;			//
	int *point_f=value_buff2;
	float DataFangcha=0.0;	
	//����ԭʼ����							
	*(point_f+(orig_count++))=rec_value;																														
	orig_count=orig_count%Num;
	//�޷������˲�  
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
	//ƽ���˲�
	value=(uint16_t)(a*last_value+(1-a)*new_value); 
	last_value=value;																
	return value;
//	*(point+(count++))=value;	 //��������FIFO																													
//	count=count%Num;			 //�����±�
	
	//���ƽ��  ������Ƶ����
//	for(num_count=0;num_count<Num;num_count++)														
//	{
//		sum+=*(point+num_count);
//	}
//	return (uint16_t)(sum/Num);	
}
float fangcha(int* x,int n)		//��n����������x�ķ���
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


TIM_ICInitTypeDef  TIM4_ICInitStructure;

//��ʱ��4ͨ��3���벶������
//arr���Զ���װֵ(TIM2,TIM5��32λ��!!)
//psc��ʱ��Ԥ��Ƶ��
void TIM4_CH3_Cap_Init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

			
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);  	//TIM5ʱ��ʹ��    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 	//ʹ��PORTAʱ��	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; //GPIOb8
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(GPIOB,&GPIO_InitStructure); //��ʼ��PA0
	GPIO_SetBits(GPIOB,GPIO_Pin_8);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource8,GPIO_AF_TIM4); //PA8����λ��ʱ��4
  
	  
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period=arr;   //�Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);
    
	TIM_ClearITPendingBit(TIM4, TIM_IT_CC3|TIM_IT_Update);    //����жϱ�־λ
	
	//��ʼ��TIM5���벶�����
	TIM4_ICInitStructure.TIM_Channel = TIM_Channel_3; //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
    TIM4_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Falling;	//�����ز���
    TIM4_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
    TIM4_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //���������Ƶ,����Ƶ 
    TIM4_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 ���������˲��� ���˲�
    TIM_ICInit(TIM4, &TIM4_ICInitStructure);
		
	TIM_ITConfig(TIM4,TIM_IT_Update|TIM_IT_CC3,ENABLE);//��������ж� ,����CC1IE�����ж�	
	
    TIM_Cmd(TIM4,ENABLE ); 	//ʹ�ܶ�ʱ��5
	
    NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����
	
}
//����״̬
//[7]:0,û�гɹ��Ĳ���;1,�ɹ�����һ��.
//[6]:0,��û���񵽵͵�ƽ;1,�Ѿ����񵽵͵�ƽ��.
//[5:0]:����͵�ƽ������Ĵ���(����32λ��ʱ����˵,1us��������1,���ʱ��:4294��)
u8  TIM4CH3_CAPTURE_STA=0;	//���벶��״̬		    				
u32	TIM4CH3_CAPTURE_VAL;	//���벶��ֵ(TIM2/TIM5��32λ)
//��ʱ��5�жϷ������	 
void TIM4_IRQHandler(void)
{ 		    
 	if((TIM4CH3_CAPTURE_STA&0X80)==0)//��δ�ɹ�����	
	{
		if(TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)//���
		{	     
			if(TIM4CH3_CAPTURE_STA&0X40)//�Ѿ����񵽸ߵ�ƽ��
			{
				if((TIM4CH3_CAPTURE_STA&0X3F)==0X3F)//�ߵ�ƽ̫����
				{
					TIM4CH3_CAPTURE_STA|=0X80;		//��ǳɹ�������һ��
					TIM4CH3_CAPTURE_VAL=0XFFFFFFFF;
				}else TIM4CH3_CAPTURE_STA++;
			}	 
		}
		if(TIM_GetITStatus(TIM4, TIM_IT_CC3) != RESET)//����1���������¼�
		{	
			if(TIM4CH3_CAPTURE_STA&0X40)		//����һ���½��� 		
			{	  			
				TIM4CH3_CAPTURE_STA|=0X80;		//��ǳɹ�����һ�θߵ�ƽ����
				TIM4CH3_CAPTURE_VAL=TIM_GetCapture3(TIM4);//��ȡ��ǰ�Ĳ���ֵ.
	 			TIM_OC3PolarityConfig(TIM4,TIM_ICPolarity_Falling); //CC1P=0 ����Ϊ�����ز���
			}else  								//��δ��ʼ,��һ�β���������
			{
				TIM4CH3_CAPTURE_STA=0;			//���
				TIM4CH3_CAPTURE_VAL=0;
				TIM4CH3_CAPTURE_STA|=0X40;		//��ǲ�����������
				TIM_Cmd(TIM4,DISABLE ); 	//�رն�ʱ��5
	 			TIM_SetCounter(TIM4,0);
	 			TIM_OC3PolarityConfig(TIM4,TIM_ICPolarity_Falling);		//CC1P=1 ����Ϊ�½��ز���
				TIM_Cmd(TIM4,ENABLE ); 	//ʹ�ܶ�ʱ��5
			}		    
		}			     	    					   
 	}
	TIM_ClearITPendingBit(TIM4, TIM_IT_CC3|TIM_IT_Update); //����жϱ�־λ
}



