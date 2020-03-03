
#ifndef __UserData_H
#define __UserData_H
#include "sys.h"
#include "stdio.h"
#include "stm32f4xx_conf.h"


///////////////////////////////////////////////////////////////
//����2 �뷢����ͨѶ�ӿ�
#define USART3_REC_LEN  			200  	//�����������ֽ��� 200
#define EN_USART3_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����

extern u8  USART3_RX_BUF[USART3_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з�
extern u16 USART3_RX_STA;         		//����״̬���
//����봮���жϽ��գ��벻Ҫע�����º궨��
void uart3_init(u32 bound);

void ANG_Int(u32 arr,u16 psc);


/////////////////////////////////////////////////////////////
//PWM5 ң����ֵ�����   //����4 ��ֵ���ݽ��տ�

#define USART6_REC_LEN  			200  	//�����������ֽ��� 200
#define EN_USART6_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����

extern u8  USART6_RX_BUF[USART6_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з�
extern u16 USART6_RX_STA;         		//����״̬���
//����봮���жϽ��գ��벻Ҫע�����º궨��
void uart6_init(u32 bound);
void PWM5_CH1_Cap_Init(u32 arr,u16 psc);
void Pow_init(void);
/////////////////////////////////////////////////////////////
//���ư����
void KTPSANG_init(void);


/////////////////////////////////////////////////////
/////ECU
void ECU_init(void);


////////////////////////////////////////
#endif
