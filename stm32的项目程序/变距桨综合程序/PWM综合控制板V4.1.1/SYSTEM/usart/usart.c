#include "sys.h"
#include "usart.h"
//////////////////////////////////////////////////////////////////////////////////
//���ʹ��ucos,����������ͷ�ļ�����.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos ʹ��	  
#endif
//////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB
#if 1
#pragma import(__use_no_semihosting)
//��׼����Ҫ��֧�ֺ���
struct __FILE
{
    int handle;
};

FILE __stdout;
//����_sys_exit()�Ա���ʹ�ð�����ģʽ
void _sys_exit(int x)
{
    x = x;
}
//�ض���fputc����
int fputc(int ch, FILE *f)
{
    while((USART1->SR&0X40)==0);//ѭ������,ֱ���������
    USART1->DR = (u8) ch;
    return ch;
}
#endif


//#if EN_USART1_RX   //���ʹ���˽���
////����1�жϷ������
////ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���
//u8 USART1_RX_BUF[USART1_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
////����״̬
////bit15��	������ɱ�־
////bit14��	���յ�0x0d
////bit13~0��	���յ�����Ч�ֽ���Ŀ
//u16 USART1_RX_STA=0;       //����״̬���

////��ʼ��IO ����1
////bound:������
//void uart1_init(u32 bound)
//{
//    //GPIO�˿�����
//    GPIO_InitTypeDef GPIO_InitStructure;
//    USART_InitTypeDef USART_InitStructure;
//    NVIC_InitTypeDef NVIC_InitStructure;

//    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //ʹ��GPIOAʱ��
//    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5,ENABLE);//ʹ��USART1ʱ��

//    //����1��Ӧ���Ÿ���ӳ��
//    GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_UART4); //GPIOA0����ΪUSART1
//    GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_UART4); //GPIOA1����ΪUSART1

//    //USART1�˿�����
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1; //GPIOA0��GPIOA1
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
//    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
//    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
//    GPIO_Init(GPIOA,&GPIO_InitStructure); //��ʼ��PA0��PA1

//    //USART1 ��ʼ������
//    USART_InitStructure.USART_BaudRate = bound;//����������
//    USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
//    USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
//    USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
//    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
//    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
//    USART_Init(UART4, &USART_InitStructure); //��ʼ������1

//    USART_Cmd(UART4, ENABLE);  //ʹ�ܴ���1

//    //USART_ClearFlag(USART1, USART_FLAG_TC);

//#if EN_USART1_RX
//    USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);//��������ж�

//    //Usart1 NVIC ����
//    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//����1�ж�ͨ��
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//��ռ���ȼ�3
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//�����ȼ�3
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
//    NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����

//#endif

//}


//void USART1_IRQHandler(void)                	//����1�жϷ������
//{
//	u8 Res;

//	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
//	{
//		Res =USART_ReceiveData(USART1);//(USART1->DR);	//��ȡ���յ�������
//
//		if((USART1_RX_STA&0x8000)==0)//����δ���
//		{
//			if(USART1_RX_STA&0x4000)//���յ���0x0d
//			{
//				if(Res!=0x0a)USART1_RX_STA=0;//���մ���,���¿�ʼ
//				else USART1_RX_STA|=0x8000;	//���������
//			}
//			else //��û�յ�0X0D
//			{
//				if(Res==0x0d)USART1_RX_STA|=0x4000;
//				else
//				{
//					USART1_RX_BUF[USART1_RX_STA&0X3FFF]=Res ;
//					USART1_RX_STA++;
//					if(USART1_RX_STA>(USART1_REC_LEN-1))USART1_RX_STA=0;//�������ݴ���,���¿�ʼ����
//				}
//			}
//		}
//	}
//}
//#endif


//////////////////////////////////////////////////////////////////////////////////



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
    NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//�����ȼ�3
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
            if(USART3_RX_STA&0x4000)//���յ���0x0d
            {
                if(Res!=0x0a)USART3_RX_STA=0;//���մ���,���¿�ʼ
                else USART3_RX_STA|=0x8000;	//���������
            }
            else //��û�յ�0X0D
            {
                if(Res==0x0d)USART3_RX_STA|=0x4000;
                else
                {
                    USART3_RX_BUF[USART3_RX_STA&0X3FFF]=Res ;
                    USART3_RX_STA++;
                    if(USART3_RX_STA>(USART3_REC_LEN-1))USART3_RX_STA=0;//�������ݴ���,���¿�ʼ����
                }
            }
						//������֤
            if((USART3_RX_STA==0||USART3_RX_STA==1)&&Res!=0x4f) {//��ʼλ��Ϊ0x4f
                 USART3_RX_STA=0;//�������ݴ���,���¿�ʼ����
            }
        }
    }
}
#endif


//////////////////////////////////////////////////////////////////////////////////


#if EN_UART4_RX   //���ʹ���˽���

//����1�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���
u8 UART4_RX_BUF[UART4_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 UART4_RX_STA=0;       //����״̬���
u16 UART4_flagA=0;       //����״̬���

//��ʼ��IO ����3
//bound:������
void uart4_init(u32 bound)
{
    //GPIO�˿�����
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE); //ʹ��GPIOCʱ��
    //	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);//ʹ��USART4ʱ��

    //����3��Ӧ���Ÿ���ӳ��
    GPIO_PinAFConfig(GPIOC,GPIO_PinSource10,GPIO_AF_UART4); //GPIOC10����ΪUSART3
    GPIO_PinAFConfig(GPIOC,GPIO_PinSource11,GPIO_AF_UART4); //GPIOC11����ΪUSART3

    //USART1�˿�����
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11; //GPIOC10��GPIOC11
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
    GPIO_Init(GPIOC,&GPIO_InitStructure); //��ʼ��PC10��PC11

    //USART1 ��ʼ������
    USART_InitStructure.USART_BaudRate = bound;//����������
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
    USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
    USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
    USART_Init(UART4, &USART_InitStructure); //��ʼ������4

    USART_Cmd(UART4, ENABLE);  //ʹ�ܴ���3

    //USART_ClearFlag(USART1, USART_FLAG_TC);

#if EN_UART4_RX
    USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);//��������ж�

    //Usart1 NVIC ����
    NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;//����3�ж�ͨ��
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//��ռ���ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//�����ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
    NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����

#endif

}
void UART4_IRQHandler(void)                	//����1�жϷ������
{
    u8 Res;

    if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
    {
        Res =USART_ReceiveData(UART4);//(USART1->DR);	//��ȡ���յ�������

        if((UART4_RX_STA&0x8000)==0)//����δ���
        {
            if(UART4_RX_STA&0x4000)//���յ���0x0d
            {
                if(Res!=0x0a)UART4_RX_STA=0;//���մ���,���¿�ʼ
                else UART4_RX_STA|=0x8000;	//���������
            }
            else //��û�յ�0X0D
            {
                if(Res==0x0d)UART4_RX_STA|=0x4000;
                else
                {
                    UART4_RX_BUF[UART4_RX_STA&0X3FFF]=Res ;
                    UART4_RX_STA++;
                    if(UART4_RX_STA>(UART4_REC_LEN-1))UART4_RX_STA=0;//�������ݴ���,���¿�ʼ����
                }
            }
        }
    }
}
#endif




#if EN_UART5_RX   //���ʹ���˽���

//����1�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���
u8 UART5_RX_BUF[UART4_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 UART5_RX_STA=0;       //����״̬���
u16 UART5_flagA=0;       //����״̬���

//��ʼ��IO ����3
//bound:������
void uart5_init(u32 bound)
{
    //GPIO�˿�����
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //ʹ��GPIOCʱ��
    //	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5,ENABLE);//ʹ��USART4ʱ��

    //����3��Ӧ���Ÿ���ӳ��
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_UART5); //GPIOC10����ΪUSART3
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_UART5); //GPIOC11����ΪUSART3

    //UART5�˿�����
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1; //GPIOC10��GPIOC11
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
    GPIO_Init(GPIOA,&GPIO_InitStructure); //��ʼ��PC10��PC11

    //USART1 ��ʼ������
    USART_InitStructure.USART_BaudRate = bound;//����������
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
    USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
    USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
    USART_Init(UART5, &USART_InitStructure); //��ʼ������4

    USART_Cmd(UART5, ENABLE);  //ʹ�ܴ���3

    //USART_ClearFlag(USART1, USART_FLAG_TC);

#if EN_UART5_RX
    USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);//��������ж�

    //Usart1 NVIC ����
    NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;//����3�ж�ͨ��
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//��ռ���ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//�����ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
    NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����

#endif

}
void UART5_IRQHandler(void)                	//����1�жϷ������
{
    u8 Res;

    if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
    {
        Res =USART_ReceiveData(UART4);//(USART1->DR);	//��ȡ���յ�������

        if((UART4_RX_STA&0x8000)==0)//����δ���
        {
            if(UART4_RX_STA&0x4000)//���յ���0x0d
            {
                if(Res!=0x0a)UART4_RX_STA=0;//���մ���,���¿�ʼ
                else UART4_RX_STA|=0x8000;	//���������
            }
            else //��û�յ�0X0D
            {
                if(Res==0x0d)UART4_RX_STA|=0x4000;
                else
                {
                    UART4_RX_BUF[UART4_RX_STA&0X3FFF]=Res ;
                    UART4_RX_STA++;
                    if(UART4_RX_STA>(UART4_REC_LEN-1))UART4_RX_STA=0;//�������ݴ���,���¿�ʼ����
                }
            }
        }
    }
}
#endif






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
    NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//�����ȼ�3
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
            if(USART6_RX_STA&0x4000)//���յ���0x0d
            {
                if(Res!=0x0a)USART6_RX_STA=0;//���մ���,���¿�ʼ
                else USART6_RX_STA|=0x8000;	//���������
            }
            else //��û�յ�0X0D
            {
                if(Res==0x0d)USART6_RX_STA|=0x4000;
                else
                {
                    USART6_RX_BUF[USART6_RX_STA&0X3FFF]=Res ;
                    USART6_RX_STA++;
                    if(USART6_RX_STA>(USART6_REC_LEN-1))USART6_RX_STA=0;//�������ݴ���,���¿�ʼ����
                }
            }
        }
    }
}
#endif

