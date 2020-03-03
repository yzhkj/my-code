

//////////////////////////////////////////////////////////////////////////////
/// ��;: ���ǿ��ư���ECUͨѶ�ķ�����
/// ��Դ: 232����
///       ����:         ���ں�:
/// ����: ���ڳ�ʼ�� �����ж����ݽ��� ���ݽ���������
///
//////////////////////////////////////////////////////////////////////////////

#include "UserData.h"
#include "delay.h"

#if EN_USART3_RX   //���ʹ���˽���
//����1�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���
u8 USART3_RX_BUF[USART3_REC_LEN];   //���ջ���,���USART_REC_LEN���ֽ�.
//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 USART3_RX_STA=0;       //����״̬���
u16 USART3_flagA=0;       //����״̬���

//��ʼ��IO ����3
//bound:������
void uart3_init(u32 bound)
{
    //GPIO�˿�����
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE); //ʹ��GPIOCʱ��
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);//ʹ��USART3ʱ��

    //����3��Ӧ���Ÿ���ӳ��
    GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_USART3); //GPIOC10����ΪUSART3
    GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_USART3); //GPIOC11����ΪUSART3

    //USART1�˿�����
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11; //GPIOC10��GPIOAC11
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
    GPIO_Init(GPIOB,&GPIO_InitStructure); //��ʼ��PC10��PC11

    //USART1 ��ʼ������
    USART_InitStructure.USART_BaudRate = bound;//����������
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
    USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
    USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
    USART_Init(USART3, &USART_InitStructure); //��ʼ������3

    USART_Cmd(USART3, ENABLE);  //ʹ�ܴ���3

    //USART_ClearFlag(USART1, USART_FLAG_TC);

#if EN_USART3_RX
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//��������ж�

    //Usart1 NVIC ����
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;//����3�ж�ͨ��
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//��ռ���ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;		//�����ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
    NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����

#endif

}



void USART3_IRQHandler(void)                	//����1�жϷ������
{
    u8 Res;

    if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
    {
        Res =USART_ReceiveData(USART3);//(USART1->DR);	//��ȡ���յ�������

        if((USART3_RX_STA&0x8000)==0)//����δ���
        {
            if(USART3_RX_STA==0&&Res!=0x80) {
                USART3_RX_STA=0;//���մ���
                return;
            }
            if(USART3_RX_STA==1&&Res!=0x8f) {
                USART3_RX_STA=0;//���մ���
                return;
            }
            if(USART3_RX_STA==2&&Res!=0xea) {
                USART3_RX_STA=0;//���մ���
                return;
            }
            if(USART3_RX_STA==3&&Res!=0x16) {
                USART3_RX_STA=0;//���մ���
                return;
            }
            if(USART3_RX_STA==4&&Res!=0x50) {
                USART3_RX_STA=0;//���մ���
                return;
            }
            if(USART3_RX_STA==5&&Res!=0x04) {
                USART3_RX_STA=0;//���մ���
                return;
            }
            USART3_RX_BUF[USART3_RX_STA&0X3FFF]=Res ;
            if(USART3_RX_STA>=25) {
                USART3_RX_STA|=0x8000;	//���������
                return;
            }
            USART3_RX_STA++;
        }
    }
#if SYSTEM_SUPPORT_OS 	//���SYSTEM_SUPPORT_OSΪ�棬����Ҫ֧��OS.
    OSIntExit();
#endif
}
#endif

void ECU_init(void ) {
    uart2_init(115200);
    uart3_init(115200);
    delay_ms(500);
    u8 data1[]= {0x80,0x8F,0xEA,0x03,0x20,0x02,0x07,0x25,0x80,0x8F,0xEA,0x01,0x9B,0x95,0x80,0x8F,0xEA,0x01,0xA1,0x9B };
    u8 data2[]= {0x80,0x8F,0xEA,0x03,0x20,0x02,0x07,0x25,0x80,0x8F,0xEA,0x22,0x10,0x82,0x04,0x01,0x02,0x2C,0xF4,0x02,0x2C,0xD2,0x02,0x2F,0x2C,0x01,0x2D,0xA6,0x01,0x2D,0xAC,0x02,0x30,0x41,0x01,0x2C,0xF6,0x02,0x2C,0x8A,0x02,0x2C,0x8C,0x02,0x2C,0xB3,0xC8,0x80
                 ,0x8F,0xEA,0x2E,0x10,0x82,0x01,0x01,0x01,0x2E,0x19,0x02,0x2E,0x55,0x01,0x28,0x6E,0x02,0x28,0x8F,0x02,0x2F,0x0C,0x02,0x2C,0x41,0x02,0x28,0x7D,0x02,0x28,0x65,0x02,0x2F,0x2C,0x02,0x2C,0xF4,0x02,0x2C,0xD0,0x02,0x2C,0x4D,0x01,0x2D,0xAC,0x02,0x30,0x41,0xFF
                };
    for(u8 i=0; i<sizeof(data1); i++) {
        USART_SendData(USART3,data1[i]);
        while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
    }
    delay_ms(500);
    for(u8 i=0; i<sizeof(data2); i++) {
        USART_SendData(USART3,data2[i]);
        while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
    }

}



#if EN_USART2_RX   //���ʹ���˽���
//����2�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���
u8 USART2_RX_BUF[USART2_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 USART2_RX_STA=0;       //����״̬���

//��ʼ��IO ����2
//bound:������
void uart2_init(u32 bound) {
    //GPIO�˿�����
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //ʹ��GPIOAʱ��
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);//ʹ��USART2ʱ��

    //����2��Ӧ���Ÿ���ӳ��
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2); //GPIOA2����ΪUSART2
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2); //GPIOA3����ΪUSART2

    //USART1�˿�����
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3; //GPIOA2��GPIOA3
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
    GPIO_Init(GPIOA,&GPIO_InitStructure); //��ʼ��PA2��PA3

    //USART2 ��ʼ������
    USART_InitStructure.USART_BaudRate = bound;//����������
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
    USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
    USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
    USART_Init(USART2, &USART_InitStructure); //��ʼ������2

    USART_Cmd(USART2, ENABLE);  //ʹ�ܴ���2

    //USART_ClearFlag(USART1, USART_FLAG_TC);

#if EN_USART2_RX
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//��������ж�

    //Usart1 NVIC ����
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;//����2�ж�ͨ��
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//��ռ���ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//�����ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
    NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����

#endif

}


void USART2_IRQHandler(void)                	//����1�жϷ������
{
    u8 Res;

    if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
    {
        Res =USART_ReceiveData(USART2);//(USART1->DR);	//��ȡ���յ�������

        if((USART2_RX_STA&0x8000)==0)//����δ���
        {
            if(USART2_RX_STA&0x4000)//���յ���0x0d
            {
                if(Res!=0x0a)USART2_RX_STA=0;//���մ���,���¿�ʼ
                else USART2_RX_STA|=0x8000;	//���������
            }
            else //��û�յ�0X0D
            {
                if(Res==0x0d)USART2_RX_STA|=0x4000;
                else
                {
                    USART2_RX_BUF[USART2_RX_STA&0X3FFF]=Res ;
                    USART2_RX_STA++;
                    if(USART2_RX_STA>(USART2_REC_LEN-1))USART2_RX_STA=0;//�������ݴ���,���¿�ʼ����
                }
            }

            //������֤
            if((USART2_RX_STA==0||USART2_RX_STA==1)&&Res!=0x4f) {//��ʼλ��Ϊ0x4f
                USART2_RX_STA=0;//�������ݴ���,���¿�ʼ����
            }
        }
    }
}
#endif



//////////////////////////////////////////////////////////////////////////////////
