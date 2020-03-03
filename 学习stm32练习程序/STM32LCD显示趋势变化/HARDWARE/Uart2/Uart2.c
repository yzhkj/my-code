#include "UART2.h"	



u8 Res_Flag;    //�������ݱ�־
u8 Send_Flag;   //���ͱ�־
u8 resive;         //��������

//ʵ����usart3  ����ʹ��pc10->Tx  pc11->Rx

void uart2_init(u32 pclk2,u32 bound)			
{  	 
	float temp;
	u16 mantissa;
	u16 fraction;	   
	temp=(float)(pclk2*1000000)/(bound*16);//�õ�USARTDIV@OVER8=0
	mantissa=temp;				 //�õ���������
	fraction=(temp-mantissa)*16; //�õ�С������@OVER8=0 
    mantissa<<=4;
	mantissa+=fraction; 
	RCC->AHB1ENR|=1<<3;   	//ʹ��PORTA��ʱ��  
	RCC->APB1ENR|=1<<18;  	//ʹ�ܴ���2ʱ�� 
	GPIO_Set(GPIOC,PIN10|PIN11,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_50M,GPIO_PUPD_PU);//PA9,PA10,���ù���,�������
 	GPIO_AF_Set(GPIOC,10,7);	//PA9,AF7
	GPIO_AF_Set(GPIOC,10,7);//PA10,AF7  	   
	//����������
 	USART3->BRR=mantissa; 	//����������	 
	USART3->CR1&=~(1<<15); 	//����OVER8=0 
	USART3->CR1|=1<<3;  	//���ڷ���ʹ�� 
//#if EN_USART1_RX		  	//���ʹ���˽���
	//ʹ�ܽ����ж� 
	USART3->CR1|=1<<2;  	//���ڽ���ʹ��
	USART3->CR1|=1<<5;    	//���ջ������ǿ��ж�ʹ��	    	
	MY_NVIC_Init(3,3,USART3_IRQn,2);//��2��������ȼ� 
//#endif
	USART3->CR1|=1<<13;  	//����ʹ��
}

void send(int ch)
{      
	while((USART3->SR&0X40)==0);//ѭ������,ֱ���������   
	USART3->DR = (u8) ch;  
	if((USART3->SR&0X20)==1)    //�жϷ����Ƿ����
	Send_Flag=1;
//	return ch;
}
void USART3_IRQHandler(void)
{
	
	if(USART3->SR&(1<<5))//���յ�����
	{
		resive=USART2->DR; 
		Res_Flag=1;
	}
}
