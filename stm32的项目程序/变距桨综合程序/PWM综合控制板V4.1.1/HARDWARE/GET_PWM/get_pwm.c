////#include "get_pwm.h"
////#include "led.h"
////#include "usart.h"



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////PWM1��������    ʹ�ö�ʱ��3 ��ΪPWM1 �Ķ�ʱ��
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////TIM_ICInitTypeDef  PWM1_ICInitStructure;

//////��ʱ��3ͨ��1���벶������
//////arr���Զ���װֵ(TIM4,TIM5��32λ��!!)
//////psc��ʱ��Ԥ��Ƶ��
////void PWM1_CH1_Cap_Init(u32 arr,u16 psc)
////{
////    GPIO_InitTypeDef GPIO_InitStructure;
////    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
////    TIM_OCInitTypeDef  TIM_OCInitStructure;
////    NVIC_InitTypeDef NVIC_InitStructure;


////    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  		//TIM3ʱ��ʹ��
////    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 		//ʹ��PORTAʱ��

////    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; 					//GPIOA6
////    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;				//���ù���
////    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;			//�ٶ�100MHz
////    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;				//���츴�����
////    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; 				//����
////    GPIO_Init(GPIOA,&GPIO_InitStructure); 						//��ʼ��PA6

////    GPIO_PinAFConfig(GPIOA,GPIO_PinSource6,GPIO_AF_TIM3); 		//PA6����λ��ʱ��3


////    TIM_TimeBaseStructure.TIM_Prescaler=psc;  					//��ʱ����Ƶ
////    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 	//���ϼ���ģʽ
////    TIM_TimeBaseStructure.TIM_Period=arr;   					//�Զ���װ��ֵ
////    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;

////    TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);//��ʼ����ʱ��


////    //��ʼ��PWM1���벶�����
////    PWM1_ICInitStructure.TIM_Channel = TIM_Channel_1; 					//CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
////    PWM1_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;		//�����ز���
////    PWM1_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; 	//ӳ�䵽TI1��
////    PWM1_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 			//���������Ƶ,����Ƶ
////    PWM1_ICInitStructure.TIM_ICFilter = 0x00;							//IC1F=0000 ���������˲��� ���˲�
////    TIM_ICInit(TIM3, &PWM1_ICInitStructure);
////    TIM_ITConfig(TIM3,TIM_IT_Update|TIM_IT_CC1,ENABLE);					//��������ж� ,����CC1IE�����ж�

//////    //��ʼ��TIM14 Channel1 PWMģʽ
//////    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
//////    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
//////    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //�������:TIM����Ƚϼ��Ե�
//////    TIM_OC1Init(TIM14, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM1 4OC1
//////    TIM_OC1PreloadConfig(TIM14, TIM_OCPreload_Enable);  //ʹ��TIM14��CCR1�ϵ�Ԥװ�ؼĴ���
//////    TIM_ARRPreloadConfig(TIM14,ENABLE);//ARPEʹ��


////    TIM_Cmd(TIM3,ENABLE ); 					//ʹ�ܶ�ʱ��3


////    //�ж�����
////    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
////    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;			//��ռ���ȼ�2
////    NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;				//�����ȼ�0
////    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					//IRQͨ��ʹ��
////    NVIC_Init(&NVIC_InitStructure);									//����ָ���Ĳ�����ʼ��VIC�Ĵ�����


////}


//////����״̬
//////[7]:0,û�гɹ��Ĳ���;1,�ɹ�����һ��.
//////[6]:0,��û���񵽵͵�ƽ;1,�Ѿ����񵽵͵�ƽ��.
//////[5:0]:����͵�ƽ������Ĵ���(����32λ��ʱ����˵,1us��������1,���ʱ��:4294��)
////u8  PWM1CH1_CAPTURE_STA=0;	//���벶��״̬
////u32	PWM1CH1_CAPTURE_VAL;	//���벶��ֵ(TIM4/TIM5��32λ)
////u32	PWM1CH1_CAPTURE_VAL_CYC;	//���벶��ֵ(TIM4/TIM5��32λ)
////u32 PWM1Data;//�ҵļ���ֵ

//////PWM1 ��ʱ��3�жϷ������  PWM1��
////void TIM3_IRQHandler(void)
////{

////    if((PWM1CH1_CAPTURE_STA&0X80)==0)//��δ�ɹ�����
////    {
////        if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)//���
////        {
////            if(PWM1CH1_CAPTURE_STA&0X40)//�Ѿ����񵽸ߵ�ƽ��
////            {
////                if((PWM1CH1_CAPTURE_STA&0X3F)==0X3F)//�ߵ�ƽ̫����
////                {
////                    PWM1CH1_CAPTURE_STA|=0X80;		//��ǳɹ�������һ��
////                    PWM1CH1_CAPTURE_VAL=0XFFFFFFFF;
////                }
////                else {
////                    PWM1CH1_CAPTURE_STA++;
////                }
////            }
////        }
////        if(TIM_GetITStatus(TIM3, TIM_IT_CC1) != RESET)//����1���������¼�
////        {

////            if(PWM1CH1_CAPTURE_STA&0X40)		//����һ���½���
////            {
////                PWM1CH1_CAPTURE_STA|=0X80;		//��ǳɹ�����һ�θߵ�ƽ����
////                PWM1CH1_CAPTURE_VAL=TIM_GetCapture1(TIM3);//��ȡ��ǰ�Ĳ���ֵ.

////                PWM1CH1_CAPTURE_VAL_CYC=TIM_GetCapture2(TIM3);
////                TIM_OC1PolarityConfig(TIM3,TIM_ICPolarity_Rising); //CC1P=0 ����Ϊ�����ز���    TIM_ICPolarity_Rising
////            }

////            else  								//��δ��ʼ,��һ�β���������
////            {
////                PWM1CH1_CAPTURE_STA=0;			//���
////                PWM1CH1_CAPTURE_VAL=0;
////                PWM1CH1_CAPTURE_STA|=0X40;		//��ǲ�����������
////                TIM_Cmd(TIM3,DISABLE ); 		//�رն�ʱ��5
////                TIM_SetCounter(TIM3,0);
////                TIM_OC1PolarityConfig(TIM3,TIM_ICPolarity_Falling);		//CC1P=1 ����Ϊ�½��ز���   TIM_ICPolarity_Falling
////                TIM_Cmd(TIM3,ENABLE ); 			//ʹ�ܶ�ʱ��5
////            }
////        }
////    }
////    TIM_ClearITPendingBit(TIM3, TIM_IT_CC1|TIM_IT_Update); //����жϱ�־λ
////}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////PWM2 �������
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////PWM�����ʼ��
//////arr���Զ���װֵ
//////psc��ʱ��Ԥ��Ƶ��
////void PWM1_CH1_Out_Init(u32 arr,u32 psc)
////{
////    //�˲������ֶ��޸�IO������
////    GPIO_InitTypeDef GPIO_InitStructure;
////    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
////    TIM_OCInitTypeDef  TIM_OCInitStructure;

////    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  		//TIM3ʱ��ʹ��
////    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 		//ʹ��PORTAʱ��

////    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; 					//GPIOA6
////    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;				//���ù���
////    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;			//�ٶ�100MHz
////    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;				//���츴�����
////    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; 				//����
////    GPIO_Init(GPIOA,&GPIO_InitStructure); 						//��ʼ��PA6

////    GPIO_PinAFConfig(GPIOA,GPIO_PinSource6,GPIO_AF_TIM3); 		//PA6����λ��ʱ��3


////    TIM_TimeBaseStructure.TIM_Prescaler=psc;  					//��ʱ����Ƶ
////    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 	//���ϼ���ģʽ
////    TIM_TimeBaseStructure.TIM_Period=arr;   					//�Զ���װ��ֵ
////    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;

////    TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);//��ʼ����ʱ��


////    //��ʼ��TIM12 Channel1 PWMģʽ
////    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
////    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
////    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //�������:TIM����Ƚϼ��Ե�
////    TIM_OC1Init(TIM3, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM1 4OC1
////    TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);  //ʹ��TIM12��CCR1�ϵ�Ԥװ�ؼĴ���
////    TIM_ARRPreloadConfig(TIM3,ENABLE);//ARPEʹ��

////    TIM_Cmd(TIM3, ENABLE);  //ʹ��TIM2
////}





/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////PWM2��������  ʹ�ö�ʱ��4 ��ΪPWM2 �Ķ�ʱ��
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////TIM_ICInitTypeDef  PWM2_ICInitStructure;

//////��ʱ��4ͨ��1���벶������
//////arr���Զ���װֵ(TIM2,TIM5��32λ��!!)
//////psc��ʱ��Ԥ��Ƶ��
////void PWM2_CH1_Cap_Init(u32 arr,u16 psc)
////{
////    GPIO_InitTypeDef GPIO_InitStructure;
////    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
////    NVIC_InitTypeDef NVIC_InitStructure;


////    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);  		//TIM1ʱ��ʹ��
////    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE); 		//ʹ��PORTEʱ��

////    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; 					//GPIOE9
////    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;				//���ù���
////    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;			//�ٶ�100MHz
////    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;				//���츴�����
////    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; 				//  ����
////    GPIO_Init(GPIOE,&GPIO_InitStructure); 						//��ʼ��PE9

////    GPIO_PinAFConfig(GPIOE,GPIO_PinSource9,GPIO_AF_TIM1); 		//PE9����λ��ʱ��1

////    TIM_DeInit(TIM1); //�����Ĭ��ֵ
////    TIM_TimeBaseStructure.TIM_Prescaler=psc;  					//��ʱ����Ƶ
////    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 	//���ϼ���ģʽ
////    TIM_TimeBaseStructure.TIM_Period=arr;   					//�Զ���װ��ֵ
////    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;//ʱ�ӷָ�ֵ

////    TIM_TimeBaseStructure.TIM_RepetitionCounter=0; //�����¼ӵĲ���
////    TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure);//��ʼ��ʱ��TIM1


////    //��ʼ��PWM2���벶�����
////    PWM2_ICInitStructure.TIM_Channel = TIM_Channel_1; 					//CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
////    PWM2_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;		//�����ز���
////    PWM2_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; 	//ӳ�䵽TI1��
////    PWM2_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 			//���������Ƶ,����Ƶ
////    PWM2_ICInitStructure.TIM_ICFilter = 0x00;							//IC1F=0000 ���������˲��� ���˲�

//////    TIM_PWMIConfig(TIM1, &PWM2_ICInitStructure);
//////    TIM_SelectInputTrigger(TIM1, TIM_TS_TI1FP1); //ѡ��ic1Ϊʼ�մ���Դ
//////    TIM_SelectSlaveMode(TIM1, TIM_SlaveMode_Reset);//TIM ��ģʽ �����źŵ����������³�ʼ���������ʹ����Ĵ����ĸ����¼�
//////    TIM_SelectMasterSlaveMode(TIM1, TIM_MasterSlaveMode_Enable); //������ʱ����������
////    TIM_ICInit(TIM1, &PWM2_ICInitStructure);

////    TIM_ITConfig(TIM1
////                 ,TIM_IT_Update
////                 |TIM_IT_CC1
////                 ,ENABLE);					//��������ж� ,����CC1IE�����ж�

////    // TIM_ClearFlag(TIM1, TIM_IT_Update|TIM_IT_CC1);// ����жϱ�־λ


////    NVIC_InitStructure.NVIC_IRQChannel = TIM1_CC_IRQn;
////    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;			//��ռ���ȼ�3
////    NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;				//�����ȼ�1
////    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					//IRQͨ��ʹ��
////    NVIC_Init(&NVIC_InitStructure);									//����ָ���Ĳ�����ʼ��VIC�Ĵ����
////    TIM_Cmd(TIM1,ENABLE ); 					//ʹ�ܶ�ʱ��1
////}


//////����״̬
//////[7]:0,û�гɹ��Ĳ���;1,�ɹ�����һ��.
//////[6]:0,��û���񵽵͵�ƽ;1,�Ѿ����񵽵͵�ƽ��.
//////[5:0]:����͵�ƽ������Ĵ���(����32λ��ʱ����˵,1us��������1,���ʱ��:4294��)
////u8  PWM2CH1_CAPTURE_STA=0;	//���벶��״̬
////u32	PWM2CH1_CAPTURE_VAL;	//���벶��ֵ(PWM2/TIM5��32λ)
////u32	PWM2CH1_CAPTURE_VAL_CYC;	//���벶��ֵ(TIM4/TIM5��32λ)

//////PWM2  ��ʱ��1�жϷ������
////void TIM1_CC_IRQHandler(void)
////{

////    if((PWM2CH1_CAPTURE_STA&0X80)==0)//��δ�ɹ�����
////    {
////        if(TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)//���
////        {
////            if(PWM2CH1_CAPTURE_STA&0X40)//�Ѿ����񵽸ߵ�ƽ��
////            {
////                if((PWM2CH1_CAPTURE_STA&0X3F)==0X3F)//�ߵ�ƽ̫����
////                {
////                    PWM2CH1_CAPTURE_STA|=0X80;		//��ǳɹ�������һ��
////                    PWM2CH1_CAPTURE_VAL=0XFFFFFFFF;
////                }

////                else
////                    PWM2CH1_CAPTURE_STA++;
////            }
////        }
////        if(TIM_GetITStatus(TIM1, TIM_IT_CC1) != RESET)//����2���������¼�
////        {


////            if(PWM2CH1_CAPTURE_STA&0X40)		//����һ���½���
////            {
////                PWM2CH1_CAPTURE_STA|=0X80;		//��ǳɹ�����һ�θߵ�ƽ����
////                PWM2CH1_CAPTURE_VAL=TIM_GetCapture1(TIM1);//��ȡ��ǰ�Ĳ���ֵ.

////                PWM2CH1_CAPTURE_VAL_CYC=TIM_GetCapture2(TIM1);

////                TIM_OC1PolarityConfig(TIM1,TIM_ICPolarity_Rising); //CC1P=0 ����Ϊ�����ز���
////            }

////            else  								//��δ��ʼ,��һ�β���������
////            {
////                PWM2CH1_CAPTURE_STA=0;			//���
////                PWM2CH1_CAPTURE_VAL=0;
////                PWM2CH1_CAPTURE_STA|=0X40;		//��ǲ�����������
////                TIM_Cmd(TIM1,DISABLE ); 		//�رն�ʱ��1
////                TIM_SetCounter(TIM1,0);
////                TIM_OC1PolarityConfig(TIM1,TIM_ICPolarity_Falling);		//CC1P=1 ����Ϊ�½��ز���
////                TIM_Cmd(TIM1,ENABLE ); 			//ʹ�ܶ�ʱ��1
////            }
////        }
////    }
////    TIM_ClearITPendingBit(TIM1, TIM_IT_CC1|TIM_IT_Update); //����жϱ�־λ
////}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////PWM2 �������
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////PWM�����ʼ��
//////arr���Զ���װֵ
//////psc��ʱ��Ԥ��Ƶ��
////void PWM2_CH1_Out_Init(u32 arr,u32 psc)
////{
////    //�˲������ֶ��޸�IO������
////    GPIO_InitTypeDef GPIO_InitStructure;
////    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
////    TIM_OCInitTypeDef  TIM_OCInitStructure;

////    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);  		//TIM1ʱ��ʹ��
////    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE); 		//ʹ��PORTEʱ��

////    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; 					//GPIOE9
////    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;				//���ù���
////    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;			//�ٶ�100MHz
////    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;				//���츴�����
////    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; 				//  ����
////    GPIO_Init(GPIOE,&GPIO_InitStructure); 						//��ʼ��PE9

////    GPIO_PinAFConfig(GPIOE,GPIO_PinSource9,GPIO_AF_TIM1); 		//PE9����λ��ʱ��1

////    TIM_DeInit(TIM1); //�����Ĭ��ֵ
////    TIM_TimeBaseStructure.TIM_Prescaler=psc;  					//��ʱ����Ƶ
////    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 	//���ϼ���ģʽ
////    TIM_TimeBaseStructure.TIM_Period=arr;   					//�Զ���װ��ֵ
////    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;//ʱ�ӷָ�ֵ

////    // TIM_TimeBaseStructure.TIM_RepetitionCounter=0; //�����¼ӵĲ���
////    TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure);//��ʼ��ʱ��TIM1

////    //��ʼ��TIM12 Channel1 PWMģʽ
////    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
////    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
////    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //�������:TIM����Ƚϼ��Ե�
////    TIM_OC1Init(TIM1, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM1 4OC1

////    TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);  //ʹ��TIM12��CCR1�ϵ�Ԥװ�ؼĴ���

////    TIM_ARRPreloadConfig(TIM1,ENABLE);//ARPEʹ��

////    TIM_Cmd(TIM1, ENABLE);  //ʹ��TIM2
////}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////PWM3��������
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////TIM_ICInitTypeDef  PWM3_ICInitStructure;

//////��ʱ��3ͨ��1���벶������
//////arr���Զ���װֵ(TIM4,TIM5��32λ��!!)
//////psc��ʱ��Ԥ��Ƶ��
////void PWM3_CH1_Cap_Init(u32 arr,u16 psc)
////{
////    GPIO_InitTypeDef GPIO_InitStructure;
////    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
////    NVIC_InitTypeDef NVIC_InitStructure;


////    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12,ENABLE);  		//TIM5ʱ��ʹ��
////    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 		//ʹ��PORTAʱ��

////    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14; 					//GPIOB14
////    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;				//���ù���
////    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;			//�ٶ�100MHz
////    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;				//���츴�����
////    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; 				//����
////    GPIO_Init(GPIOB,&GPIO_InitStructure); 						//��ʼ��PB14

////    GPIO_PinAFConfig(GPIOB,GPIO_PinSource14,GPIO_AF_TIM12); 		//PB14����λ��ʱ��12


////    TIM_TimeBaseStructure.TIM_Prescaler=psc;  					//��ʱ����Ƶ
////    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 	//���ϼ���ģʽ
////    TIM_TimeBaseStructure.TIM_Period=arr;   					//�Զ���װ��ֵ
////    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;

////    TIM_TimeBaseInit(TIM12,&TIM_TimeBaseStructure);


////    //��ʼ��TIM5���벶�����
////    PWM3_ICInitStructure.TIM_Channel = TIM_Channel_1; 					//CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
////    PWM3_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;		//�����ز���
////    PWM3_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; 	//ӳ�䵽TI1��
////    PWM3_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 			//���������Ƶ,����Ƶ
////    PWM3_ICInitStructure.TIM_ICFilter = 0x00;							//IC1F=0000 ���������˲��� ���˲�
////    TIM_ICInit(TIM12, &PWM3_ICInitStructure);

////    TIM_ITConfig(TIM12,TIM_IT_Update|TIM_IT_CC1,ENABLE);					//��������ж� ,����CC1IE�����ж�

////    TIM_Cmd(TIM12,ENABLE ); 					//ʹ�ܶ�ʱ��5


////    NVIC_InitStructure.NVIC_IRQChannel = TIM8_BRK_TIM12_IRQn;
////    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;			//��ռ���ȼ�3
////    NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;				//�����ȼ�2
////    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					//IRQͨ��ʹ��
////    NVIC_Init(&NVIC_InitStructure);									//����ָ���Ĳ�����ʼ��VIC�Ĵ�����


////}


//////����״̬
//////[7]:0,û�гɹ��Ĳ���;1,�ɹ�����һ��.
//////[6]:0,��û���񵽵͵�ƽ;1,�Ѿ����񵽵͵�ƽ��.
//////[5:0]:����͵�ƽ������Ĵ���(����32λ��ʱ����˵,1us��������1,���ʱ��:4294��)
////u8  PWM3CH1_CAPTURE_STA=0;	//���벶��״̬
////u32	PWM3CH1_CAPTURE_VAL;	//���벶��ֵ(TIM4/TIM5��32λ)
////u32	PWM3CH1_CAPTURE_VAL_CYC;	//���벶��ֵ(TIM4/TIM5��32λ)

//////��ʱ��3�жϷ������
////void TIM8_BRK_TIM12_IRQHandler(void)
////{

////    if((PWM3CH1_CAPTURE_STA&0X80)==0)//��δ�ɹ�����
////    {
////        if(TIM_GetITStatus(TIM12, TIM_IT_Update) != RESET)//���
////        {
////            if(PWM3CH1_CAPTURE_STA&0X40)//�Ѿ����񵽸ߵ�ƽ��
////            {
////                if((PWM3CH1_CAPTURE_STA&0X3F)==0X3F)//�ߵ�ƽ̫����
////                {
////                    PWM3CH1_CAPTURE_STA|=0X80;		//��ǳɹ�������һ��
////                    PWM3CH1_CAPTURE_VAL=0XFFFFFFFF;
////                }

////                else
////                    PWM3CH1_CAPTURE_STA++;
////            }
////        }
////        if(TIM_GetITStatus(TIM12, TIM_IT_CC1) != RESET)//����1���������¼�
////        {

////            if(PWM3CH1_CAPTURE_STA&0X40)		//����һ���½���
////            {
////                PWM3CH1_CAPTURE_STA|=0X80;		//��ǳɹ�����һ�θߵ�ƽ����
////                PWM3CH1_CAPTURE_VAL=TIM_GetCapture1(TIM12);//��ȡ��ǰ�Ĳ���ֵ.

////                PWM3CH1_CAPTURE_VAL_CYC=TIM_GetCapture2(TIM12);

////                TIM_OC1PolarityConfig(TIM12,TIM_ICPolarity_Rising); //CC1P=0 ����Ϊ�����ز���
////            }

////            else  								//��δ��ʼ,��һ�β���������
////            {
////                PWM3CH1_CAPTURE_STA=0;			//���
////                PWM3CH1_CAPTURE_VAL=0;
////                PWM3CH1_CAPTURE_STA|=0X40;		//��ǲ�����������
////                TIM_Cmd(TIM12,DISABLE ); 		//�رն�ʱ��5
////                TIM_SetCounter(TIM12,0);
////                TIM_OC1PolarityConfig(TIM12,TIM_ICPolarity_Falling);		//CC1P=1 ����Ϊ�½��ز���
////                TIM_Cmd(TIM12,ENABLE ); 			//ʹ�ܶ�ʱ��5
////            }
////        }
////    }
////    TIM_ClearITPendingBit(TIM12, TIM_IT_CC1|TIM_IT_Update); //����жϱ�־λ
////}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////PWM3 �������
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////PWM�����ʼ��
//////arr���Զ���װֵ
//////psc��ʱ��Ԥ��Ƶ��
////void PWM3_CH1_Out_Init(u32 arr,u32 psc)
////{
////    //�˲������ֶ��޸�IO������
////    GPIO_InitTypeDef GPIO_InitStructure;
////    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
////    TIM_OCInitTypeDef  TIM_OCInitStructure;

////    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);  		//TIM5ʱ��ʹ��
////    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 		//ʹ��PORTAʱ��

////    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; 					//GPIOA5
////    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;				//���ù���
////    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;			//�ٶ�100MHz
////    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;				//���츴�����
////    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; 				//����
////    GPIO_Init(GPIOA,&GPIO_InitStructure); 						//��ʼ��pa5

////    GPIO_PinAFConfig(GPIOA,GPIO_PinSource5,GPIO_AF_TIM2); 		//Pa5����λ��ʱ��2


////    TIM_TimeBaseStructure.TIM_Prescaler=psc;  					//��ʱ����Ƶ
////    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 	//���ϼ���ģʽ
////    TIM_TimeBaseStructure.TIM_Period=arr;   					//�Զ���װ��ֵ
////    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
////    TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);//��ʼ����ʱ��2

////    //��ʼ��TIM12 Channel1 PWMģʽ
////    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
////    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
////    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //�������:TIM����Ƚϼ��Ե�
////    TIM_OC1Init(TIM2, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM1 4OC1

////    TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);  //ʹ��TIM12��CCR1�ϵ�Ԥװ�ؼĴ���

////    TIM_ARRPreloadConfig(TIM2,ENABLE);//ARPEʹ��

////    TIM_Cmd(TIM2, ENABLE);  //ʹ��TIM2
////}




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////PWM4 �������
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////PWM�����ʼ��
//////arr���Զ���װֵ
//////psc��ʱ��Ԥ��Ƶ��
////void PWM4_CH1_Out_Init(u32 arr,u32 psc)
////{
////    //�˲������ֶ��޸�IO������

////    GPIO_InitTypeDef GPIO_InitStructure;
////    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
////    TIM_OCInitTypeDef  TIM_OCInitStructure;

////    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);  	//TIM2ʱ��ʹ��
////    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	//ʹ��PORTFʱ��

////    GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_TIM2); //GPIOA1����Ϊ��ʱ��2

////    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;           //GPIOA1
////    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //���ù���
////    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
////    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
////    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����
////    GPIO_Init(GPIOA,&GPIO_InitStructure);              //��ʼ��PA0

////    TIM_TimeBaseStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
////    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
////    TIM_TimeBaseStructure.TIM_Period=arr;   //�Զ���װ��ֵ
////    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;

////    TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);//��ʼ����ʱ��2

////    //��ʼ��TIM2 Channel1 PWMģʽ
////    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
////    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
////    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //�������:TIM����Ƚϼ��Ե�
////    TIM_OC1Init(TIM2, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM1 4OC1

////    TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);  //ʹ��TIM2��CCR1�ϵ�Ԥװ�ؼĴ���

////    TIM_ARRPreloadConfig(TIM2,ENABLE);//ARPEʹ��

////    TIM_Cmd(TIM2, ENABLE);  //ʹ��TIM2
////}


/////////////////////////////////////////////////
///////PW4 ��������
/////////////////////////////////////////////////
////TIM_ICInitTypeDef  PWM4_ICInitStructure;
////void PWM4_CH1_Cap_Init(u32 arr,u16 psc)
////{
////    GPIO_InitTypeDef GPIO_InitStructure;
////    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
////    NVIC_InitTypeDef NVIC_InitStructure;


////    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);  		//TIM5ʱ��ʹ��
////    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); 		//ʹ��PORTAʱ��

////    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14; 					//GPIOB14
////    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;				//���ù���
////    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;			//�ٶ�100MHz
////    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;				//���츴�����
////    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; 				//����
////    GPIO_Init(GPIOD,&GPIO_InitStructure); 						//��ʼ��PB14

////    GPIO_PinAFConfig(GPIOD,GPIO_PinSource14,GPIO_AF_TIM4); 		//PB14����λ��ʱ��4


////    TIM_TimeBaseStructure.TIM_Prescaler=psc;  					//��ʱ����Ƶ
////    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 	//���ϼ���ģʽ
////    TIM_TimeBaseStructure.TIM_Period=arr;   					//�Զ���װ��ֵ
////    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;

////    TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);


////    //��ʼ��TIM5���벶�����
////    PWM4_ICInitStructure.TIM_Channel = TIM_Channel_1; 					//CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
////    PWM4_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;		//�����ز���
////    PWM4_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; 	//ӳ�䵽TI1��
////    PWM4_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 			//���������Ƶ,����Ƶ
////    PWM4_ICInitStructure.TIM_ICFilter = 0x00;							//IC1F=0000 ���������˲��� ���˲�
////    TIM_ICInit(TIM4, &PWM4_ICInitStructure);
////    TIM_ITConfig(TIM4,TIM_IT_Update|TIM_IT_CC1,ENABLE);					//��������ж� ,����CC1IE�����ж�

////    TIM_Cmd(TIM4,ENABLE ); 					//ʹ�ܶ�ʱ��5


////    NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn ;
////    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;			//��ռ���ȼ�3
////    NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;				//�����ȼ�2
////    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					//IRQͨ��ʹ��
////    NVIC_Init(&NVIC_InitStructure);									//����ָ���Ĳ�����ʼ��VIC�Ĵ�����
////}

//////����״̬
//////[7]:0,û�гɹ��Ĳ���;1,�ɹ�����һ��.
//////[6]:0,��û���񵽵͵�ƽ;1,�Ѿ����񵽵͵�ƽ��.
//////[5:0]:����͵�ƽ������Ĵ���(����32λ��ʱ����˵,1us��������1,���ʱ��:4294��)
////u8  PWM4CH1_CAPTURE_STA=0;	//���벶��״̬
////u32	PWM4CH1_CAPTURE_VAL;	//���벶��ֵ(TIM4/TIM5��32λ)
////u32	PWM4CH1_CAPTURE_VAL_CYC;	//���벶��ֵ(TIM4/TIM5��32λ)

////void TIM4_IRQHandler(void) {

////    if((PWM4CH1_CAPTURE_STA&0X80)==0)//��δ�ɹ�����
////    {
////        if(TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)//���
////        {
////            if(PWM4CH1_CAPTURE_STA&0X40)//�Ѿ����񵽸ߵ�ƽ��
////            {
////                if((PWM4CH1_CAPTURE_STA&0X3F)==0X3F)//�ߵ�ƽ̫����
////                {
////                    PWM4CH1_CAPTURE_STA|=0X80;		//��ǳɹ�������һ��
////                    PWM4CH1_CAPTURE_VAL=0XFFFFFFFF;
////                }
////                else
////                    PWM4CH1_CAPTURE_STA++;
////            }
////        }
////        if(TIM_GetITStatus(TIM4, TIM_IT_CC1) != RESET)//����1���������¼�
////        {

////            if(PWM4CH1_CAPTURE_STA&0X40)		//����һ���½���
////            {
////                PWM4CH1_CAPTURE_STA|=0X80;		//��ǳɹ�����һ�θߵ�ƽ����
////                PWM4CH1_CAPTURE_VAL=TIM_GetCapture1(TIM4);//��ȡ��ǰ�Ĳ���ֵ.

////                PWM4CH1_CAPTURE_VAL_CYC=TIM_GetCapture2(TIM4);

////                TIM_OC1PolarityConfig(TIM4,TIM_ICPolarity_Rising); //CC1P=0 ����Ϊ�����ز���//TIM_ICPolarity_Falling
////            }

////            else  								//��δ��ʼ,��һ�β���������
////            {
////                PWM4CH1_CAPTURE_STA=0;			//���
////                PWM4CH1_CAPTURE_VAL=0;
////                PWM4CH1_CAPTURE_STA|=0X40;		//��ǲ�����������
////                TIM_Cmd(TIM4,DISABLE); 		//�رն�ʱ��5
////                TIM_SetCounter(TIM4,0);
////                TIM_OC1PolarityConfig(TIM4,TIM_ICPolarity_Falling);		//CC1P=1 ����Ϊ�½��ز���//TIM_ICPolarity_Rising
////                TIM_Cmd(TIM4,ENABLE ); 			//ʹ�ܶ�ʱ��5
////            }
////        }
////    }
////    TIM_ClearITPendingBit(TIM4, TIM_IT_CC1|TIM_IT_Update); //����жϱ�־λ
////}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////PWM5 �������
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



//////PWM�����ʼ��
//////arr���Զ���װֵ
//////psc��ʱ��Ԥ��Ƶ��
////void PWM5_CH1_Out_Init(u32 arr,u32 psc)
////{
////    //�˲������ֶ��޸�IO������

////    GPIO_InitTypeDef GPIO_InitStructure;
////    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
////    TIM_OCInitTypeDef  TIM_OCInitStructure;

////    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);  	//TIM2ʱ��ʹ��
////    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	//ʹ��PORTFʱ��

////    GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_TIM5); //GPIOA0����Ϊ��ʱ��5

////    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;           //GPIOA0
////    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //���ù���
////    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
////    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
////    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����
////    GPIO_Init(GPIOA,&GPIO_InitStructure);              //��ʼ��PA0

////    TIM_TimeBaseStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
////    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
////    TIM_TimeBaseStructure.TIM_Period=arr;   //�Զ���װ��ֵ
////    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;

////    TIM_TimeBaseInit(TIM5,&TIM_TimeBaseStructure);//��ʼ����ʱ��2

////    //��ʼ��TIM5 Channel1 PWMģʽ
////    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
////    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
////    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //�������:TIM����Ƚϼ��Ե�
////    TIM_OC1Init(TIM5, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM1 4OC1

////    TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Enable);  //ʹ��TIM2��CCR1�ϵ�Ԥװ�ؼĴ���

////    TIM_ARRPreloadConfig(TIM5,ENABLE);//ARPEʹ��

////    TIM_Cmd(TIM5, ENABLE);  //ʹ��TIM2
////}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////PWM5 �������
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////TIM_ICInitTypeDef  PWM5_ICInitStructure;
////void PWM5_CH1_Cap_Init(u32 arr,u16 psc) {
////    GPIO_InitTypeDef GPIO_InitStructure;
////    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
////    NVIC_InitTypeDef NVIC_InitStructure;


////    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM11,ENABLE);  		//TIM5ʱ��ʹ��
////    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 		//ʹ��PORTAʱ��

////    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; 					//GPIOB14
////    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;				//���ù���
////    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;			//�ٶ�100MHz
////    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;				//���츴�����
////    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; 				//����
////    GPIO_Init(GPIOB,&GPIO_InitStructure); 						//��ʼ��PB14

////    GPIO_PinAFConfig(GPIOB,GPIO_PinSource9,GPIO_AF_TIM11); 		//PB14����λ��ʱ��4


////    TIM_TimeBaseStructure.TIM_Prescaler=psc;  					//��ʱ����Ƶ
////    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 	//���ϼ���ģʽ
////    TIM_TimeBaseStructure.TIM_Period=arr;   					//�Զ���װ��ֵ
////    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;

////    TIM_TimeBaseInit(TIM11,&TIM_TimeBaseStructure);


////    //��ʼ��TIM5���벶�����
////    PWM5_ICInitStructure.TIM_Channel = TIM_Channel_1; 					//CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
////    PWM5_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;		//�����ز���
////    PWM5_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; 	//ӳ�䵽TI1��
////    PWM5_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 			//���������Ƶ,����Ƶ
////    PWM5_ICInitStructure.TIM_ICFilter = 0x00;							//IC1F=0000 ���������˲��� ���˲�
////    TIM_ICInit(TIM11, &PWM5_ICInitStructure);
////    TIM_ITConfig(TIM11,TIM_IT_Update|TIM_IT_CC1,ENABLE);					//��������ж� ,����CC1IE�����ж�

////    TIM_Cmd(TIM11,ENABLE ); 					//ʹ�ܶ�ʱ��5


////    NVIC_InitStructure.NVIC_IRQChannel = TIM1_TRG_COM_TIM11_IRQn ;
////    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;			//��ռ���ȼ�3
////    NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;				//�����ȼ�2
////    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					//IRQͨ��ʹ��
////    NVIC_Init(&NVIC_InitStructure);									//����ָ���Ĳ�����ʼ��VIC�Ĵ�����
////}
//////����״̬
//////[7]:0,û�гɹ��Ĳ���;1,�ɹ�����һ��.
//////[6]:0,��û���񵽵͵�ƽ;1,�Ѿ����񵽵͵�ƽ��.
//////[5:0]:����͵�ƽ������Ĵ���(����32λ��ʱ����˵,1us��������1,���ʱ��:4294��)
////u8  PWM5CH1_CAPTURE_STA=0;	//���벶��״̬
////u32	PWM5CH1_CAPTURE_VAL;	//���벶��ֵ(TIM4/TIM5��32λ)
////u32	PWM5CH1_CAPTURE_VAL_CYC;	//���벶��ֵ(TIM4/TIM5��32λ)
////void TIM1_TRG_COM_TIM11_IRQHandler(void) {
////    if((PWM5CH1_CAPTURE_STA&0X80)==0)//��δ�ɹ�����
////    {
////        if(TIM_GetITStatus(TIM11, TIM_IT_Update) != RESET)//���
////        {
////            if(PWM5CH1_CAPTURE_STA&0X40)//�Ѿ����񵽸ߵ�ƽ��
////            {
////                if((PWM5CH1_CAPTURE_STA&0X3F)==0X3F)//�ߵ�ƽ̫����
////                {
////                    PWM5CH1_CAPTURE_STA|=0X80;		//��ǳɹ�������һ��
////                    PWM5CH1_CAPTURE_VAL=0XFFFFFFFF;
////                }
////                else
////                    PWM5CH1_CAPTURE_STA++;
////            }
////        }
////        if(TIM_GetITStatus(TIM11, TIM_IT_CC1) != RESET)//����1���������¼�
////        {

////            if(PWM5CH1_CAPTURE_STA&0X40)		//����һ���½���
////            {
////                PWM5CH1_CAPTURE_STA|=0X80;		//��ǳɹ�����һ�θߵ�ƽ����
////                PWM5CH1_CAPTURE_VAL=TIM_GetCapture1(TIM11);//��ȡ��ǰ�Ĳ���ֵ.

////                PWM5CH1_CAPTURE_VAL_CYC=TIM_GetCapture2(TIM11);

////                TIM_OC1PolarityConfig(TIM11,TIM_ICPolarity_Rising); //CC1P=0 ����Ϊ�����ز���//TIM_ICPolarity_Falling
////            }

////            else  								//��δ��ʼ,��һ�β���������
////            {
////                PWM5CH1_CAPTURE_STA=0;			//���
////                PWM5CH1_CAPTURE_VAL=0;
////                PWM5CH1_CAPTURE_STA|=0X40;		//��ǲ�����������
////                TIM_Cmd(TIM11,DISABLE); 		//�رն�ʱ��5
////                TIM_SetCounter(TIM11,0);
////                TIM_OC1PolarityConfig(TIM11,TIM_ICPolarity_Falling);		//CC1P=1 ����Ϊ�½��ز���//TIM_ICPolarity_Rising
////                TIM_Cmd(TIM11,ENABLE ); 			//ʹ�ܶ�ʱ��5
////            }
////        }
////    }
////    TIM_ClearITPendingBit(TIM11, TIM_IT_CC1|TIM_IT_Update); //����жϱ�־λ
////}



////// TIM_ICInitTypeDef  TIM5_ICInitStructure;

////// //��ʱ��5ͨ��1���벶������
////// //arr���Զ���װֵ(TIM4,TIM5��32λ��!!)
////// //psc��ʱ��Ԥ��Ƶ��
////// void TIM5_CH1_Cap_Init(u32 arr,u16 psc)
////// {
////// 	GPIO_InitTypeDef GPIO_InitStructure;
////// 	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
////// 	NVIC_InitTypeDef NVIC_InitStructure;


////// 	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);  		//TIM5ʱ��ʹ��
////// 	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 		//ʹ��PORTAʱ��

////// 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; 					//GPIOA0
////// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;				//���ù���
////// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;			//�ٶ�100MHz
////// 	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;				//���츴�����
////// 	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; 				//����
////// 	GPIO_Init(GPIOA,&GPIO_InitStructure); 						//��ʼ��PA0

////// 	GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_TIM5); 		//PA0����λ��ʱ��5


////// 	TIM_TimeBaseStructure.TIM_Prescaler=psc;  					//��ʱ����Ƶ
////// 	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 	//���ϼ���ģʽ
////// 	TIM_TimeBaseStructure.TIM_Period=arr;   					//�Զ���װ��ֵ
////// 	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;

////// 	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseStructure);


////// 	//��ʼ��TIM5���벶�����
////// 	TIM5_ICInitStructure.TIM_Channel = TIM_Channel_1; 					//CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
////// 	TIM5_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;		//�����ز���
////// 	TIM5_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; 	//ӳ�䵽TI1��
////// 	TIM5_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 			//���������Ƶ,����Ƶ
////// 	TIM5_ICInitStructure.TIM_ICFilter = 0x00;							//IC1F=0000 ���������˲��� ���˲�
////// 	TIM_ICInit(TIM5, &TIM5_ICInitStructure);

////// 	TIM_ITConfig(TIM5,TIM_IT_Update|TIM_IT_CC1,ENABLE);					//��������ж� ,����CC1IE�����ж�

////// 	TIM_Cmd(TIM5,ENABLE ); 					//ʹ�ܶ�ʱ��5


////// 	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;
////// 	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;			//��ռ���ȼ�3
////// 	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;				//�����ȼ�3
////// 	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					//IRQͨ��ʹ��
////// 	NVIC_Init(&NVIC_InitStructure);									//����ָ���Ĳ�����ʼ��VIC�Ĵ�����


////// }


////// //����״̬
////// //[7]:0,û�гɹ��Ĳ���;1,�ɹ�����һ��.
////// //[6]:0,��û���񵽵͵�ƽ;1,�Ѿ����񵽵͵�ƽ��.
////// //[5:0]:����͵�ƽ������Ĵ���(����32λ��ʱ����˵,1us��������1,���ʱ��:4294��)
////// u8  TIM5CH1_CAPTURE_STA=0;	//���벶��״̬
////// u32	TIM5CH1_CAPTURE_VAL;	//���벶��ֵ(TIM4/TIM5��32λ)
////// u32	TIM5CH1_CAPTURE_VAL_CYC;	//���벶��ֵ(TIM4/TIM5��32λ)

////// //��ʱ��5�жϷ������
////// void TIM5_IRQHandler(void)
////// {

//////  	if((TIM5CH1_CAPTURE_STA&0X80)==0)//��δ�ɹ�����
////// 	{
////// 		if(TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)//���
////// 		{
////// 			if(TIM5CH1_CAPTURE_STA&0X40)//�Ѿ����񵽸ߵ�ƽ��
////// 			{
////// 				if((TIM5CH1_CAPTURE_STA&0X3F)==0X3F)//�ߵ�ƽ̫����
////// 				{
////// 					TIM5CH1_CAPTURE_STA|=0X80;		//��ǳɹ�������һ��
////// 					TIM5CH1_CAPTURE_VAL=0XFFFFFFFF;
////// 				}

////// 				else
////// 					TIM5CH1_CAPTURE_STA++;
////// 			}
////// 		}
////// 		if(TIM_GetITStatus(TIM5, TIM_IT_CC1) != RESET)//����1���������¼�
////// 		{

////// 			if(TIM5CH1_CAPTURE_STA&0X40)		//����һ���½���
////// 			{
////// 				TIM5CH1_CAPTURE_STA|=0X80;		//��ǳɹ�����һ�θߵ�ƽ����
////// 				TIM5CH1_CAPTURE_VAL=TIM_GetCapture1(TIM5);//��ȡ��ǰ�Ĳ���ֵ.

////// 				TIM5CH1_CAPTURE_VAL_CYC=TIM_GetCapture2(TIM5);

////// 	 			TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Rising); //CC1P=0 ����Ϊ�����ز���
////// 			}

////// 			else  								//��δ��ʼ,��һ�β���������
////// 			{
////// 				TIM5CH1_CAPTURE_STA=0;			//���
////// 				TIM5CH1_CAPTURE_VAL=0;
////// 				TIM5CH1_CAPTURE_STA|=0X40;		//��ǲ�����������
////// 				TIM_Cmd(TIM5,DISABLE ); 		//�رն�ʱ��5
////// 	 			TIM_SetCounter(TIM5,0);
////// 	 			TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Falling);		//CC1P=1 ����Ϊ�½��ز���
////// 				TIM_Cmd(TIM5,ENABLE ); 			//ʹ�ܶ�ʱ��5
////// 			}
////// 		}
//////  	}
////// 	TIM_ClearITPendingBit(TIM5, TIM_IT_CC1|TIM_IT_Update); //����жϱ�־λ
////// }

