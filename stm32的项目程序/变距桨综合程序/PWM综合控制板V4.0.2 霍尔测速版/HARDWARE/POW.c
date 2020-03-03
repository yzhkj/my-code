
#include "UserData.h"

//////////////////////////////////////////////////////////////////////////////
/// ��;: ���ǿ��ư�ɼ�POW(��ཬ������)�ķ�����
/// ��Դ: TTL����
///       ����:         �жϺ�:
/// ����: ���ڳ�ʼ�� �����ж����ݽ��� ���ݽ���������
///
//////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///PWM5 ��������
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TIM_ICInitTypeDef  PWM5_ICInitStructure;
void PWM5_CH1_Cap_Init(u32 arr,u16 psc) {
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;


    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM11,ENABLE);  		//TIM5ʱ��ʹ��
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 		//ʹ��PORTAʱ��

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; 					//GPIOB14
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;				//���ù���
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;			//�ٶ�100MHz
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;				//���츴�����
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; 				//����
    GPIO_Init(GPIOB,&GPIO_InitStructure); 						//��ʼ��PB14

    GPIO_PinAFConfig(GPIOB,GPIO_PinSource9,GPIO_AF_TIM11); 		//PB14����λ��ʱ��4


    TIM_TimeBaseStructure.TIM_Prescaler=psc;  					//��ʱ����Ƶ
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 	//���ϼ���ģʽ
    TIM_TimeBaseStructure.TIM_Period=arr;   					//�Զ���װ��ֵ
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;

    TIM_TimeBaseInit(TIM11,&TIM_TimeBaseStructure);


    //��ʼ��TIM5���벶�����
    PWM5_ICInitStructure.TIM_Channel = TIM_Channel_1; 					//CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
    PWM5_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;		//�����ز���
    PWM5_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; 	//ӳ�䵽TI1��
    PWM5_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 			//���������Ƶ,����Ƶ
    PWM5_ICInitStructure.TIM_ICFilter = 0x00;							//IC1F=0000 ���������˲��� ���˲�
    TIM_ICInit(TIM11, &PWM5_ICInitStructure);
    TIM_ITConfig(TIM11,TIM_IT_Update|TIM_IT_CC1,ENABLE);					//��������ж� ,����CC1IE�����ж�

    TIM_Cmd(TIM11,ENABLE ); 					//ʹ�ܶ�ʱ��5


    NVIC_InitStructure.NVIC_IRQChannel = TIM1_TRG_COM_TIM11_IRQn ;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;			//��ռ���ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;				//�����ȼ�2
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					//IRQͨ��ʹ��
    NVIC_Init(&NVIC_InitStructure);									//����ָ���Ĳ�����ʼ��VIC�Ĵ�����
}
//����״̬
//[7]:0,û�гɹ��Ĳ���;1,�ɹ�����һ��.
//[6]:0,��û���񵽵͵�ƽ;1,�Ѿ����񵽵͵�ƽ��.
//[5:0]:����͵�ƽ������Ĵ���(����32λ��ʱ����˵,1us��������1,���ʱ��:4294��)
u8  PWM5CH1_CAPTURE_STA=0;	//���벶��״̬
u32	PWM5CH1_CAPTURE_VAL;	//���벶��ֵ(TIM4/TIM5��32λ)
u32	PWM5CH1_CAPTURE_VAL_CYC;	//���벶��ֵ(TIM4/TIM5��32λ)
void TIM1_TRG_COM_TIM11_IRQHandler(void) {
    if((PWM5CH1_CAPTURE_STA&0X80)==0)//��δ�ɹ�����
    {
        if(TIM_GetITStatus(TIM11, TIM_IT_Update) != RESET)//���
        {
            if(PWM5CH1_CAPTURE_STA&0X40)//�Ѿ����񵽸ߵ�ƽ��
            {
                if((PWM5CH1_CAPTURE_STA&0X3F)==0X3F)//�ߵ�ƽ̫����
                {
                    PWM5CH1_CAPTURE_STA|=0X80;		//��ǳɹ�������һ��
                    PWM5CH1_CAPTURE_VAL=0XFFFFFFFF;
                }
                else
                    PWM5CH1_CAPTURE_STA++;
            }
        }
        if(TIM_GetITStatus(TIM11, TIM_IT_CC1) != RESET)//����1���������¼�
        {

            if(PWM5CH1_CAPTURE_STA&0X40)		//����һ���½���
            {
                PWM5CH1_CAPTURE_STA|=0X80;		//��ǳɹ�����һ�θߵ�ƽ����
                PWM5CH1_CAPTURE_VAL=TIM_GetCapture1(TIM11);//��ȡ��ǰ�Ĳ���ֵ.

                PWM5CH1_CAPTURE_VAL_CYC=TIM_GetCapture2(TIM11);

                TIM_OC1PolarityConfig(TIM11,TIM_ICPolarity_Rising); //CC1P=0 ����Ϊ�����ز���//TIM_ICPolarity_Falling
            }

            else  								//��δ��ʼ,��һ�β���������
            {
                PWM5CH1_CAPTURE_STA=0;			//���
                PWM5CH1_CAPTURE_VAL=0;
                PWM5CH1_CAPTURE_STA|=0X40;		//��ǲ�����������
                TIM_Cmd(TIM11,DISABLE); 		//�رն�ʱ��5
                TIM_SetCounter(TIM11,0);
                TIM_OC1PolarityConfig(TIM11,TIM_ICPolarity_Falling);		//CC1P=1 ����Ϊ�½��ز���//TIM_ICPolarity_Rising
                TIM_Cmd(TIM11,ENABLE ); 			//ʹ�ܶ�ʱ��5
            }
        }
    }
    TIM_ClearITPendingBit(TIM11, TIM_IT_CC1|TIM_IT_Update); //����жϱ�־λ
}









#if EN_USART6_RX   //���ʹ���˽���
//����1�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���
u8 USART6_RX_BUF[USART6_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 USART6_RX_STA=0;       //����״̬���
u16 USART6_flagA=0;       //����״̬���

//��ʼ��IO ����6
//bound:������
void uart6_init(u32 bound)
{
    //GPIO�˿�����
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE); //ʹ��GPIOAʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6,ENABLE);//ʹ��USART1ʱ��

    //����1��Ӧ���Ÿ���ӳ��
    GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_USART6); //GPIOA9����ΪUSART1
    GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_USART6); //GPIOA10����ΪUSART1

    //USART1�˿�����
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7; //GPIOA9��GPIOA10
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
    GPIO_Init(GPIOC,&GPIO_InitStructure); //��ʼ��PA9��PA10

    //USART1 ��ʼ������
    USART_InitStructure.USART_BaudRate = bound;//����������
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
    USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
    USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
    USART_Init(USART6, &USART_InitStructure); //��ʼ������1

    USART_Cmd(USART6, ENABLE);  //ʹ�ܴ���1

    //USART_ClearFlag(USART1, USART_FLAG_TC);

#if EN_USART6_RX
    USART_ITConfig(USART6, USART_IT_RXNE, ENABLE);//��������ж�

    //Usart1 NVIC ����
    NVIC_InitStructure.NVIC_IRQChannel = USART6_IRQn;//����1�ж�ͨ��
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//��ռ���ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;		//�����ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
    NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����

#endif

}



void USART6_IRQHandler(void)                	//����1�жϷ������
{
    u8 Res;

    if(USART_GetITStatus(USART6, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
    {
        Res =USART_ReceiveData(USART6);//(USART1->DR);	//��ȡ���յ�������

        if((USART6_RX_STA&0x8000)==0)//����δ���
        {
            if((USART6_RX_STA==0||USART6_RX_STA==1||USART6_RX_STA==2)&&Res!=0xBB) {
                USART6_RX_STA=0;//���մ���
                return;
            }
            if(USART6_RX_STA==4&&Res!=0xA1) {
                USART6_RX_STA=0;//���մ���
                return;
            }
            USART6_RX_BUF[USART6_RX_STA&0X3FFF]=Res ;
            if(USART6_RX_STA>=11) {
                USART6_RX_STA|=0x8000;	//���������
                return;
            }
            USART6_RX_STA++;

        }
    }
}
#endif

///////////////////////////////////////////////////////////////////////////
///


void Pow_init(void) {
    //��ʼ��PWM��
    PWM5_CH1_Cap_Init(10152-1,84-1);
    //��ʼ������
    uart6_init(9600);
}

