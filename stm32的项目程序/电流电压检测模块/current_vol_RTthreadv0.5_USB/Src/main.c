/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2019 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_hal.h"
#include "adc.h"
#include "can.h"
#include "dma.h"
#include "fatfs.h"
#include "usart.h"
#include "usb_device.h"
#include "gpio.h"

/* USER CODE BEGIN Includes */
#include "config.h"
#include "74hc595.h"
#include "math.h"
#include "rtthread.h"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

#define MAX_CUR 180		//最大电流值
#define MAX_VOL 70		//最大电压值
u8 ERROR_FLG=0;	 		//超最大值报警

u8 Num[8]="        ";			//荧光管显示的字符变量
u8 Init_dis[8]="r  hono";
float CurFlo=0.0;
float CurErr2=0.0;				//电流误差
//float Vol=0.0;
//线程控制块
static struct rt_thread led0_thread;//
static struct rt_thread led1_thread;//
static struct rt_thread CAN_Send_thread;//
ALIGN(RT_ALIGN_SIZE)

//线程堆栈
static rt_uint8_t rt_led0_thread_stack[1024];//???
static rt_uint8_t rt_led1_thread_stack[1024];//???
static rt_uint8_t rt_CAN_Send_thread_stack[1024];//???

//定时器控制块
static struct rt_timer timer1;
static struct rt_timer timer2;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

//uint32_t ADC_Value[100];
//uint8_t i;
//uint32_t ad1,ad2;

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

//重映射串口1到rt_kprintf
//void rt_hw_console_output(const char *str)
//{
//    // /* empty console output */

//    rt_enter_critical();

//    while(*str!='\0')
//    {
//        if(*str=='\n')
//        {
//            USART3->DR = (u8)'\r';
//            while((USART3->SR&0X40)==0);
//        }
//        USART3->DR =*str++;
//        while((USART3->SR&0X40)==0);
//    }

//    rt_exit_critical();
//}



static void timeout1(void* parameter)
{
//rt_kprintf("periodic timer is timeout\n");
	CurErr2=CurFlo;
	printf("periodic timer is timeout\n");
}
u8 Time_flag=0;
static void timeout2(void* parameter)
{
//rt_kprintf("periodic timer is timeout\n");
//	CurErr2=CurFlo;
//	printf("periodic timer is timeout\n");
	Time_flag=1;
}


//?? LED0
static void led0_thread_entry(void* parameter)
{
	int current=0,voltage=0;
	float temp_float=0.0;
	float VolErr=1.4;			    //电压误差补偿
	float CurErr=0.0;
	float CurTmpFlo=0.0;
	float VolFlo=0.0;
	kalman1_state kalman;
	u16 cur_temp[5]={0};
	u16 vol_temp[5]={0};
	u8 cur_length,vol_length;
	u8 count=0;						//采样计数
	kalman1_init(&kalman,0.8,0.8);	//用于电流数据卡尔曼滤波
	Num[four_pos]='a';
    Num[seven_pos]='u';

	/* 初始化定时器 */
    rt_timer_init(&timer1, "timer1", /* 定时器名字是 timer1 */
				  timeout1, /* 超时时回调的处理函数 */
				  RT_NULL, /* 超时函数的入口参数 */
				  10000, /* 定时长度，以OS Tick为单位，即500个OS Tick */
				  RT_TIMER_FLAG_ONE_SHOT); /* 周期性定时器 */	

	
	count=10;
	while(count--)					    //校准程序
	{
		current+=Get_Adc2(ADC_CHANNEL_9);
		rt_thread_delay(20); 			//延时50毫秒
	}
	CurFlo=(current*0.0732)*0.1-190;
	CurErr=CurFlo;
	current=0;
	
		/* 启动定时器 */
	rt_timer_start(&timer1);	
	while(1)
	{
	   
	   voltage+=Get_Adc1(ADC_CHANNEL_8);
	   current+=Get_Adc2(ADC_CHANNEL_9);
	   count++;
	   if(count>9)									//采样10次
	   {
		   count=0;
		   CurTmpFlo=(current*0.0732)*0.1-190-CurErr;			//量程换算
		   if(CurTmpFlo<0.0)
		   {
			   CurTmpFlo=-CurTmpFlo;
		   }
//		   CurFlo=kalman1_filter(&kalman,CurTmpFlo)*1.163-CurErr2; // 钳表61  显示64
		   CurFlo=kalman1_filter(&kalman,CurTmpFlo)*1.1085-CurErr2;//根据上次校准值得出
//           CurFlo=kalman1_filter(&kalman,CurTmpFlo)*1.0232-CurErr2;		   
		   if(CurFlo<0.0)
		   {
			   CurFlo=-CurFlo;
		   }
		   current=CurFlo;
		   VolFlo=(voltage*80/4095)*0.1+VolErr;
//		   VolFlo=(voltage*77.98/4095)*0.1;
		   if(VolFlo<VolErr+0.1)				//测量电压
		   {
//			   VolFlo=VolFlo-VolErr;
			   VolFlo=(voltage*80/4095)*0.1;
			   if(VolFlo<0) VolFlo=-VolFlo;
		   }
		   voltage=VolFlo;
		   if(current>MAX_CUR || voltage>MAX_VOL)     //设置报警
		   {
			   ERROR_FLG=1;
			   break;
		   }
		   ResolveNumBit(current,cur_temp,&cur_length);	 //取每一位
		   switch(cur_length)
		   {
			   case 0x01:
				   current=CurFlo*100;
			       ResolveNumBit(current,cur_temp,&cur_length);	 //取每一位
				   Num[one_pos]=cur_temp[2]+'.';
				   Num[two_pos]=cur_temp[1];
				   Num[three_pos]=cur_temp[0];	
				   break;
			   case 0x02:
				   current=CurFlo*10;
			       ResolveNumBit(current,cur_temp,&cur_length);	 //取每一位
				   Num[one_pos]=cur_temp[2];
				   Num[two_pos]=cur_temp[1]+'.';
				   Num[three_pos]=cur_temp[0];			   
				   break;
			   case 0x03:
				   Num[one_pos]=cur_temp[2];
				   Num[two_pos]=cur_temp[1];
				   Num[three_pos]=cur_temp[0];			   
				   break;
			   default:
				   Num[one_pos]='-';
				   Num[two_pos]='-';
				   Num[three_pos]='-';
				   break;
		   }
		   cur_temp[2]=0;
		   cur_temp[1]=0;
		   cur_temp[0]=0;
		   ResolveNumBit(voltage,vol_temp,&vol_length);	//取每一位
		   switch(vol_length)
		   {
			   case 1:
				   voltage=VolFlo*100;
			       ResolveNumBit(voltage,vol_temp,&vol_length);	//取每一位 	
				   Num[five_pos]=vol_temp[2]+'.';
			       Num[six_pos]=vol_temp[1];
			       Num[seven_pos]=vol_temp[0];				   
				   break;
			   case 2:
				   voltage=VolFlo*10;
			       ResolveNumBit(voltage,vol_temp,&vol_length);	//取每一位 
				   Num[five_pos]=vol_temp[2];
			       Num[six_pos]=vol_temp[1]+'.';
			       Num[seven_pos]=vol_temp[0];	   
				   break;
			   default:
				   Num[five_pos]='-';
				   Num[six_pos]='-';
				   Num[seven_pos]='u';
				   break;
		   }
		   vol_temp[2]=0;
		   vol_temp[1]=0;
		   printf("cur:\t %.3f \t A \t vol: %.3f V  Err: %.3f\r\n",CurFlo,VolFlo,CurErr);
		   current=0;		//采样清零
		   voltage=0;
	   }	   
	   rt_thread_delay(25); //延时50毫秒
	}
}

//线程 LED1
static void led1_thread_entry(void* parameter)
{
	Init_dis[six_pos]=1+'.';
	Init_dis[seven_pos]=0;
	/* 初始化定时器 */
    rt_timer_init(&timer2, "timer2", /* 定时器名字是 timer2 */
				  timeout2, /* 超时时回调的处理函数 */
				  RT_NULL, /* 超时函数的入口参数 */
				  10000, /* 定时长度，以OS Tick为单位，即500个OS Tick */
				  RT_TIMER_FLAG_ONE_SHOT); /* 周期性定时器 */ 
	
	rt_timer_start(&timer2);
//	rt_thread_delay(RT_TICK_PER_SECOND/2); //??
	while(1)
	{
		if(Time_flag==1)    //定时时间到
		{
			DispNum(Num);	//数码管显示
		}
		else				//开机显示
		{
			DispNum(Init_dis);
		}
//		rt_thread_delay(1); //??
	}
}


static void CAN_Send_thread_entry(void* parameter)
{
	
//	rt_thread_delay(RT_TICK_PER_SECOND/2); //??
	u8 num[8]={0,1,2,3,4,5,6,7};
	u8 res=0;
	u8 recive_buff[8]={0};
	while(1)
	{
		res=CAN1_Receive_Msg(recive_buff);
		if(res)
		{
			printf("the length is:%d\r\n",res);
//			for(i=0;i<8;i++)
//			{
//				printf("recive_buff[i]:%d\r\n",recive_buff[i]);
//			}
			
		}
		SendData();
//		CAN1_Send_Msg(num,8);
		rt_thread_delay(500); //??
	}
}

	
   



/* USER CODE END 0 */

int main(void)
{

  /* USER CODE BEGIN 1 */
//  u16 counter=0;
//  u16 tmp;
//  u8 i=0;
  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_CAN_Init();
  MX_USART3_UART_Init();
  MX_ADC1_Init();
  MX_ADC2_Init();
  MX_USB_DEVICE_Init();
  MX_FATFS_Init();

  /* USER CODE BEGIN 2 */
  HC595Init();			//初始化74HC595	 
//  HAL_ADC_Start_DMA(&hadc1, (uint32_t*)&ADC_Value, 100);

  
	// ??????
	rt_thread_init(&led0_thread,     //线程控制块
	"led0",                          //线程名字 在 shell 命令行可以看到
	led0_thread_entry,               //线程入口函数
	RT_NULL,                         //线程入口函数参数
	&rt_led0_thread_stack[0],        //线程起始地址
	sizeof(rt_led0_thread_stack),    //线程栈大小
	3, 								 //线程优先级
	20); 							 //线程时间片
	rt_thread_startup(&led0_thread); //启动线程 led0_thread,开启调度

	
	rt_thread_init(&led1_thread, 	 //线程控制块
	"led1", 						 //线程名字 在 shell 命令行可以看到
	led1_thread_entry, 				 //线程入口函数
	RT_NULL,                         //线程入口函数参数
	&rt_led1_thread_stack[0],        //线程起始地址
	sizeof(rt_led1_thread_stack),    //线程栈大小
	5, 								 //线程优先级
	20);
	rt_thread_startup(&led1_thread); //启动线程 led1_thread,开启调度

	
	rt_thread_init(&CAN_Send_thread, //线程控制块
	"CAN_Send", 					 //线程名字 在 shell 命令行可以看到
	CAN_Send_thread_entry, 			 //线程入口函数
	RT_NULL,                         //线程入口函数参数
	&rt_CAN_Send_thread_stack[0],    //线程起始地址
	sizeof(rt_CAN_Send_thread_stack),//线程栈大小
	4, 								 //线程优先级
	20);
	rt_thread_startup(&CAN_Send_thread); //启动线程 led1_thread,开启调度
	

	rt_system_timer_init();
	rt_system_timer_thread_init();
	//创建一个静态定时器
	
		
	printf("Init Ok\r\n");
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
//  while (1)
//  {
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */

//  }
  /* USER CODE END 3 */

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL3;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC|RCC_PERIPHCLK_USB;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL_DIV1_5;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void _Error_Handler(char * file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1) 
  {
  }
  /* USER CODE END Error_Handler_Debug */ 
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
