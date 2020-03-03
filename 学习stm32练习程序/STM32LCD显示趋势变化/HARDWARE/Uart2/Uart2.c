#include "UART2.h"	



u8 Res_Flag;    //接收数据标志
u8 Send_Flag;   //发送标志
u8 resive;         //接收数据

//实际用usart3  引脚使用pc10->Tx  pc11->Rx

void uart2_init(u32 pclk2,u32 bound)			
{  	 
	float temp;
	u16 mantissa;
	u16 fraction;	   
	temp=(float)(pclk2*1000000)/(bound*16);//得到USARTDIV@OVER8=0
	mantissa=temp;				 //得到整数部分
	fraction=(temp-mantissa)*16; //得到小数部分@OVER8=0 
    mantissa<<=4;
	mantissa+=fraction; 
	RCC->AHB1ENR|=1<<3;   	//使能PORTA口时钟  
	RCC->APB1ENR|=1<<18;  	//使能串口2时钟 
	GPIO_Set(GPIOC,PIN10|PIN11,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_50M,GPIO_PUPD_PU);//PA9,PA10,复用功能,上拉输出
 	GPIO_AF_Set(GPIOC,10,7);	//PA9,AF7
	GPIO_AF_Set(GPIOC,10,7);//PA10,AF7  	   
	//波特率设置
 	USART3->BRR=mantissa; 	//波特率设置	 
	USART3->CR1&=~(1<<15); 	//设置OVER8=0 
	USART3->CR1|=1<<3;  	//串口发送使能 
//#if EN_USART1_RX		  	//如果使能了接收
	//使能接收中断 
	USART3->CR1|=1<<2;  	//串口接收使能
	USART3->CR1|=1<<5;    	//接收缓冲区非空中断使能	    	
	MY_NVIC_Init(3,3,USART3_IRQn,2);//组2，最低优先级 
//#endif
	USART3->CR1|=1<<13;  	//串口使能
}

void send(int ch)
{      
	while((USART3->SR&0X40)==0);//循环发送,直到发送完毕   
	USART3->DR = (u8) ch;  
	if((USART3->SR&0X20)==1)    //判断发送是否完毕
	Send_Flag=1;
//	return ch;
}
void USART3_IRQHandler(void)
{
	
	if(USART3->SR&(1<<5))//接收到数据
	{
		resive=USART2->DR; 
		Res_Flag=1;
	}
}
