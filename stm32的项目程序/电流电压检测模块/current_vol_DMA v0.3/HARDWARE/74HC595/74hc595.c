/****************************************Copyright (c)**************************************************
**				
**	��Ŀ����:			74HC595������·
**	�ļ�����:			74HC595.c
**	ģ�鹦��:			��������
**
**------------------------------------------------------------------------------------------------------

** 	�� �� ��:			�����
**	E-mail  :			lidezhong@163.com
**	QQ		:			13151999
**	Mobile	:			15870966330
**	����ʱ��:			2018-07-02
**	��    ��:			v1.0.0
**	��    ��:			��������
**
********************************************************************************************************/

#include "74hc595.h"

//����Ϊ74HC595_N376RIX2_DIP��ʾλ��
//unsigned char  wei[8]={0x7F,0xBF,0xDF,0xEF,0xF7,0xFB,0xFD,0xFE};
//����Ϊ����2X8�������ʾλ��
unsigned char wei[8]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};


/********************************************************************************************************
** 	��������:			void HC595Init(void)
**	��������:			��ʼ��74HC595
**	��ڲ���:			void
**	�� �� ��:			�����
**	����ʱ��:			2014-07-3 0:10
**	��    ��:			v1.0.0
********************************************************************************************************/

void HC595Init(void)
{
//	GPIO_InitTypeDef GPIO_InitStructure;
//	
//	RCC_APB2PeriphClockCmd(HC595_CLK_GPIO_CLK | HC595_DATA_GPIO_CLK | HC595_CS_GPIO_CLK, ENABLE);
//	
//	GPIO_InitStructure.GPIO_Pin = HC595_CLK_PIN;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//	GPIO_Init(HC595_CLK_GPIO, &GPIO_InitStructure);
//	
//	GPIO_InitStructure.GPIO_Pin = HC595_DATA_PIN;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//	GPIO_Init(HC595_DATA_GPIO, &GPIO_InitStructure);

//	GPIO_InitStructure.GPIO_Pin = HC595_CS_PIN;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//	GPIO_Init(HC595_CS_GPIO, &GPIO_InitStructure);
	
	HC595_CLK_H();
	HC595_DATA_H();
	HC595_CS_H();
	
}
void HC595Send(u8 data)
{
	u8 i;
	 for(i=0;i<8;i++)
	 {
		 	HC595_CLK_L();
		  if((data & 0x80)== 0x80)						
		  {
			  HC595_DATA_H(); //�����������
		  }
		  else
		  {
			  HC595_DATA_L();
		  } 
		 data<<=1;
		 HC595_CLK_H(); //��λ����ʱ�ӣ�����������
		 HC595_CLK_L();
	 }
}

/********************************************************************************************************
** 	��������:			bit 	DispNum(uchar * N)
**	��������:			ˢ������74HC595 8X8��ʾ����
**	��ڲ���:			*N:		��ʾ���ַ�����
**	���ڲ���:			void
**	�� �� ��:			�����
**	����ʱ��:			2018-07-05 22:38
**	��    ��:			v1.0.0
**  -----------------------------------------------------------------------------------------------------
********************************************************************************************************/
void 	DispNum(unsigned char * N)
{
	unsigned char i,Nnow[8];

	for(i=0;i<7;i++)
	{
		switch(*(N+i))
		{
				//����Ϊ74HC595_N376RIX2_DIP��ʾ���
//			case	'0':	Nnow[i]	=	0x3F;	break;
//			case	'1':	Nnow[i]	=	0x06;	break;
//			case	'2':	Nnow[i]	=	0x5B;	break;
//			case	'3':	Nnow[i]	=	0x4F;	break;
//			case	'4':	Nnow[i]	=	0x66;	break;
//			case	'5':	Nnow[i]	=	0x6D;	break;
//			case	'6':	Nnow[i]	=	0x7D;	break;
//			case	'7':	Nnow[i]	=	0x07;	break;
//			case	'8':	Nnow[i]	=	0x7F;	break;
//			case	'9':	Nnow[i]	=	0x6F;	break;
//			case	'a':	Nnow[i]	=	0x77;	break;
//			case	'f':	Nnow[i]	=	0x71;	break;
//			case	'c':	Nnow[i]	=	0x39;	break;
//			case	'h':	Nnow[i]	=	0x76;	break;
//			case	'-':	Nnow[i]	=	0x40;	break;
//			case	' ':	Nnow[i]	=	0x00;	break;
//			default:		Nnow[i]	=	0xFF;
				
//			//����Ϊ����8λ�������ʾ���			
//			case	'0':	Nnow[i]	=	0xC0;	break;
//			case	'1':	Nnow[i]	=	0xF9;	break;
//			case	'2':	Nnow[i]	=	0xA4;	break;
//			case	'3':	Nnow[i]	=	0xB0;	break;
//			case	'4':	Nnow[i]	=	0x99;	break;
//			case	'5':	Nnow[i]	=	0x92;	break;
//			case	'6':	Nnow[i]	=	0x82;	break;
//			case	'7':	Nnow[i]	=	0xF8;	break;
//			case	'8':	Nnow[i]	=	0x80;	break;
//			case	'9':	Nnow[i]	=	0x90;	break;
//			case	'a':	Nnow[i]	=	0x88;	break;
//			case	'u':	Nnow[i]	=	0xc1;	break;
//			case	'c':	Nnow[i]	=	0xC6;	break;
//			case	'd':	Nnow[i]	=	0xA1;	break;
//			case	'e':	Nnow[i]	=	0x86;	break;
//			case	'f':	Nnow[i]	=	0xFF;	break;
//			case	'-':	Nnow[i]	=	0xbf;	break;
//			case	' ':	Nnow[i]	=	0xff;	break;
//			default:		Nnow[i]	=	0xFF;


			//����Ϊ�޸ĺ��			
			case	0x00:	Nnow[i]	=	0xC0;	break;
			case	0x01:	Nnow[i]	=	0xF9;	break;
			case	0x02:	Nnow[i]	=	0xA4;	break;
			case	0x03:	Nnow[i]	=	0xB0;	break;
			case	0x04:	Nnow[i]	=	0x99;	break;
			case	0x05:	Nnow[i]	=	0x92;	break;
			case	0x06:	Nnow[i]	=	0x82;	break;
			case	0x07:	Nnow[i]	=	0xF8;	break;
			case	0x08:	Nnow[i]	=	0x80;	break;
			case	0x09:	Nnow[i]	=	0x90;	break;
			case	'a':	Nnow[i]	=	0x88;	break;
			case	'u':	Nnow[i]	=	0xc1;	break;
			case	'c':	Nnow[i]	=	0xC6;	break;
			case	'd':	Nnow[i]	=	0xA1;	break;
			case	'e':	Nnow[i]	=	0x86;	break;
			case	'f':	Nnow[i]	=	0xFF;	break;
			case	'-':	Nnow[i]	=	0xbf;	break;
			case	' ':	Nnow[i]	=	0xff;	break;
			default:		Nnow[i]	=	0xFF;
		}
		/*74HC595_N376RIX2_DIP����˳��*/
//		 HC595Send(0x00);  //�ȴ��α�
//		 HC595Send(Nnow[i]);
//		 HC595Send(wei[i]);  //λ��
		
		/*����8λLED���������˳��*/	
		 
		 HC595Send(wei[i]);  //λ��
		 HC595Send(Nnow[i]); 
		 
		 HC595_CS_L();
		 HC595_CS_H();
		 HC595_CS_L();

	}
			
}
