#include "UserData.h"


//////////////////////////////////////////////////////////////////////////////
/// ��;: ���ǿ��ư�ɼ�ANG(��ཬ�Ƕ�)�ķ�����
/// ��Դ: TIM?
///       ����:         �ж�ʱ��:
/// ����: PWM�����ʼ��   �����ж����ݽ���������
///
//////////////////////////////////////////////////////////////////////////////

void PWM2_CH1_Cap_Init(u32 arr,u16 psc);


///��ʼ��
void ANG_Int(u32 arr,u16 psc) {
    PWM2_CH1_Cap_Init(arr,psc);
}





/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///PWM2��������  ʹ�ö�ʱ��4 ��ΪPWM2 �Ķ�ʱ��
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TIM_ICInitTypeDef  PWM2_ICInitStructure;

//��ʱ��4ͨ��1���벶������
//arr���Զ���װֵ(TIM2,TIM5��32λ��!!)
//psc��ʱ��Ԥ��Ƶ��
void PWM2_CH1_Cap_Init(u32 arr,u16 psc)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;


    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);  		//TIM1ʱ��ʹ��
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE); 		//ʹ��PORTEʱ��

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; 					//GPIOE9
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;				//���ù���
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;			//�ٶ�100MHz
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;				//���츴�����
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; 				//  ����
    GPIO_Init(GPIOE,&GPIO_InitStructure); 						//��ʼ��PE9

    GPIO_PinAFConfig(GPIOE,GPIO_PinSource9,GPIO_AF_TIM1); 		//PE9����λ��ʱ��1

    TIM_DeInit(TIM1); //�����Ĭ��ֵ
    TIM_TimeBaseStructure.TIM_Prescaler=psc;  					//��ʱ����Ƶ
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 	//���ϼ���ģʽ
    TIM_TimeBaseStructure.TIM_Period=arr;   					//�Զ���װ��ֵ
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;//ʱ�ӷָ�ֵ

    TIM_TimeBaseStructure.TIM_RepetitionCounter=0; //�����¼ӵĲ���
    TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure);//��ʼ��ʱ��TIM1


    //��ʼ��PWM2���벶�����
    PWM2_ICInitStructure.TIM_Channel = TIM_Channel_1; 					//CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
    PWM2_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;		//�����ز���
    PWM2_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; 	//ӳ�䵽TI1��
    PWM2_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 			//���������Ƶ,����Ƶ
    PWM2_ICInitStructure.TIM_ICFilter = 0x00;							//IC1F=0000 ���������˲��� ���˲�

//    TIM_PWMIConfig(TIM1, &PWM2_ICInitStructure);
//    TIM_SelectInputTrigger(TIM1, TIM_TS_TI1FP1); //ѡ��ic1Ϊʼ�մ���Դ
//    TIM_SelectSlaveMode(TIM1, TIM_SlaveMode_Reset);//TIM ��ģʽ �����źŵ����������³�ʼ���������ʹ����Ĵ����ĸ����¼�
//    TIM_SelectMasterSlaveMode(TIM1, TIM_MasterSlaveMode_Enable); //������ʱ����������
    TIM_ICInit(TIM1, &PWM2_ICInitStructure);

    TIM_ITConfig(TIM1
                 ,TIM_IT_Update
                 |TIM_IT_CC1
                 ,ENABLE);					//��������ж� ,����CC1IE�����ж�

    // TIM_ClearFlag(TIM1, TIM_IT_Update|TIM_IT_CC1);// ����жϱ�־λ


    NVIC_InitStructure.NVIC_IRQChannel = TIM1_CC_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;			//��ռ���ȼ�4
    NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;				//�����ȼ�1
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					//IRQͨ��ʹ��
    NVIC_Init(&NVIC_InitStructure);									//����ָ���Ĳ�����ʼ��VIC�Ĵ����
    TIM_Cmd(TIM1,ENABLE ); 					//ʹ�ܶ�ʱ��1
}


//����״̬
//[7]:0,û�гɹ��Ĳ���;1,�ɹ�����һ��.
//[6]:0,��û���񵽵͵�ƽ;1,�Ѿ����񵽵͵�ƽ��.
//[5:0]:����͵�ƽ������Ĵ���(����32λ��ʱ����˵,1us��������1,���ʱ��:4294��)
u8  PWM2CH1_CAPTURE_STA=0;	//���벶��״̬
u32	PWM2CH1_CAPTURE_VAL;	//���벶��ֵ(PWM2/TIM5��32λ)
u32	PWM2CH1_CAPTURE_VAL_CYC;	//���벶��ֵ(TIM4/TIM5��32λ)

//PWM2  ��ʱ��1�жϷ������
void TIM1_CC_IRQHandler(void)
{

    if((PWM2CH1_CAPTURE_STA&0X80)==0)//��δ�ɹ�����
    {
        if(TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)//���
        {
            if(PWM2CH1_CAPTURE_STA&0X40)//�Ѿ����񵽸ߵ�ƽ��
            {
                if((PWM2CH1_CAPTURE_STA&0X3F)==0X3F)//�ߵ�ƽ̫����
                {
                    PWM2CH1_CAPTURE_STA|=0X80;		//��ǳɹ�������һ��
                    PWM2CH1_CAPTURE_VAL=0XFFFFFFFF;
                }

                else
                    PWM2CH1_CAPTURE_STA++;
            }
        }
        if(TIM_GetITStatus(TIM1, TIM_IT_CC1) != RESET)//����2���������¼�
        {


            if(PWM2CH1_CAPTURE_STA&0X40)		//����һ���½���
            {
                PWM2CH1_CAPTURE_STA|=0X80;		//��ǳɹ�����һ�θߵ�ƽ����
                PWM2CH1_CAPTURE_VAL=TIM_GetCapture1(TIM1);//��ȡ��ǰ�Ĳ���ֵ.

                PWM2CH1_CAPTURE_VAL_CYC=TIM_GetCapture2(TIM1);

                TIM_OC1PolarityConfig(TIM1,TIM_ICPolarity_Rising); //CC1P=0 ����Ϊ�����ز���
            }

            else  								//��δ��ʼ,��һ�β���������
            {
                PWM2CH1_CAPTURE_STA=0;			//���
                PWM2CH1_CAPTURE_VAL=0;
                PWM2CH1_CAPTURE_STA|=0X40;		//��ǲ�����������
                TIM_Cmd(TIM1,DISABLE ); 		//�رն�ʱ��1
                TIM_SetCounter(TIM1,0);
                TIM_OC1PolarityConfig(TIM1,TIM_ICPolarity_Falling);		//CC1P=1 ����Ϊ�½��ز���
                TIM_Cmd(TIM1,ENABLE ); 			//ʹ�ܶ�ʱ��1
            }
        }
    }
    TIM_ClearITPendingBit(TIM1, TIM_IT_CC1|TIM_IT_Update); //����жϱ�־λ
}
