

#include "sys.h"
#include "stdio.h"
#include "stm32f4xx_conf.h"

////////////////////////////////////////////////////////////
//�������ݵĽṹ��
//////////////////////////////////////////////////////////
typedef struct SendData {
    //���Ʊ���
    double KPow;
    double KTps;
    double KAng;
    double KRpm;
    //�ɼ�����
    double Pow;
    double Ang;
    double Tps;
     double Rpm;
    int Error;
} SendData;
////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//����1 wifi ��ʼ��
#define USART1_REC_LEN  			200  	//�����������ֽ��� 200
#define EN_USART1_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����

extern u8  USART1_RX_BUF[USART1_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з�
extern u16 USART1_RX_STA;         		//����״̬���
//����봮���жϽ��գ��벻Ҫע�����º궨��
void uart1_init(u32 bound);

void Net_Init(void);
/////////////////////////////////////////////////////////////////

