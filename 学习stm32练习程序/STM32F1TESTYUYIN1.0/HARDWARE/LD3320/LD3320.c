#include "LD3320.h"


#include "DemoSound.h"


/************************************************************************************
//	nAsrStatus ������main�������б�ʾ�������е�״̬������LD3320оƬ�ڲ���״̬�Ĵ���
//	LD_ASR_NONE:			��ʾû������ASRʶ��
//	LD_ASR_RUNING��		��ʾLD3320������ASRʶ����
//	LD_ASR_FOUNDOK:		��ʾһ��ʶ�����̽�������һ��ʶ����
//	LD_ASR_FOUNDZERO:	��ʾһ��ʶ�����̽�����û��ʶ����
//	LD_ASR_ERROR:			��ʾһ��ʶ��������LD3320оƬ�ڲ����ֲ���ȷ��״̬
*********************************************************************************/
uint8 nAsrStatus = 0;	
uint8 nLD_Mode = LD_MODE_IDLE;//������¼��ǰ���ڽ���ASRʶ�����ڲ���MP3
uint8 ucRegVal;

uint8 nDemoFlag=0;

uint8 bMp3Play=0;
uint32 nMp3StartPos=0;
uint32 nMp3Size=0;
uint32 nMp3Pos=0;
uint32 nCurMp3Pos=0;
uint8  ucHighInt;
uint8  ucLowInt;
uint8  ucStatus;
uint8  ucSPVol=15; // MAX=15 MIN=0		//	Speaker�������������

/************************************************************************************/
//	���¶�������ʾ�������У��������ŵ��������ݵ���ʼλ�úͳ���
//	��Щ������������PC����¼�ƺõ�MP3�ļ�����PC���Ϻϳɵ�һ���ļ� voice.dat��
//	���԰����voide.dat�洢���û�ϵͳ�еĴ洢оƬ�У����� spi-flash��
//	����Ҫ����ʱ���û�������MCU���Ե�spi-flash�и���Ҫ�����ļ�����ʼ��ַ�޶�ȡMP3����
//	������LD3320���в���
/************************************************************************************/
#define MP3_BEIJING_START	0x0000;
#define MP3_BEIJING_SIZE	0x08b8;
#define MP3_SHANGHAI_START	0x1000;
#define MP3_SHANGHAI_SIZE	0x0ab0;
#define MP3_TIANJIN_START	0x2000;
#define MP3_TIANJIN_SIZE	0x0a20;
#define MP3_CHONGQING_START	0x3000;
#define MP3_CHONGQING_SIZE	0x0990;
#define MP3_DING_START	0x4000;
#define MP3_DING_SIZE	0x0828;
#define MP3_NIHAO_START	0x5000;
#define MP3_NIHAO_SIZE	0x1170;




///�û��޸�
void LD3320_main(void)
{
	uint8 nAsrRes=0;
	LD3320_init();	  
 	printf("1����ˮ��\r\n"); 
	printf("2����˸\r\n"); 				
	printf("3����������\r\n"); 		
	printf("4��ȫ��\r\n"); 			
	printf("5��״̬\r\n"); 		
	nAsrStatus = LD_ASR_NONE;//��ʼ״̬��û������ASR

	while(1)
	{
		switch(nAsrStatus)
		{
			case LD_ASR_RUNING:
			case LD_ASR_ERROR:		
					break;
			case LD_ASR_NONE:
					nAsrStatus=LD_ASR_RUNING;
					if (RunASR()==0)//����һ��ASRʶ�����̣�ASR��ʼ����ASR��ӹؼ��������ASR����
					{		
						nAsrStatus = LD_ASR_ERROR;
						printf("LD_ASR_ERROR\r\n");
					}
					break;
			case LD_ASR_FOUNDOK:
					 nAsrRes = LD_GetResult( );//һ��ASRʶ�����̽�����ȥȡASRʶ����										 
					 printf("\r\nʶ����:%d", nAsrRes);			 		
								
					 switch(nAsrRes)		   			//�Խ��ִ����ز���,�ͻ��޸�
						{
							case CODE_LSD:					//�����ˮ�ơ�
								printf(" ��ˮ�� ָ��ʶ��ɹ�\r\n"); 
															 break;
							case CODE_SS:	 					//�����˸��
								printf(" ��˸ ָ��ʶ��ɹ�\r\n"); 
															 break;
							case CODE_AJCF:					//�������������
								printf(" �������� ָ��ʶ��ɹ�\r\n"); 
															break;
							case CODE_QM:						//���ȫ��
								printf(" ȫ�� ָ��ʶ��ɹ�\r\n");
															break;
							case CODE_JT:						//���״̬��
								printf(" ״̬ ָ��ʶ��ɹ�\r\n");
							
							default:break;
						}	
					nAsrStatus = LD_ASR_NONE;
					break;
			case LD_ASR_FOUNDZERO:
					printf("LD_ASR_FOUNDZERO\r\n");
			default:
					nAsrStatus = LD_ASR_NONE;
					printf("default LD_ASR_NONE\r\n");
					break;
			}//switch
		//���������
		Board_text(nAsrRes );
		HAL_Delay(50);
		HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_12);
	}// while
}
void PlayDemoSound_Once()
{
	LD3320_init();
	LD_reset();
	nDemoFlag = 1;
	nMp3StartPos = 0;
	nMp3Size = DEMO_SOUND_SIZE-1;
	LD_Init_MP3();
	LD_AdjustMIX2SPVolume(5);
	LD_play();
	
}
void LD_play()
{
	nMp3Pos=0;
	bMp3Play=1;

	if (nMp3Pos >=  nMp3Size)
		return ; 

	LD_ReloadMp3Data();

    LD_WriteReg(0xBA, 0x00);
	LD_WriteReg(0x17, 0x48);
	LD_WriteReg(0x33, 0x01);
	LD_WriteReg(0x29, 0x04);
	
	LD_WriteReg(0x02, 0x01); 
	LD_WriteReg(0x85, 0x5A);

//	EX0=1;

}

static uint8 LD_AsrAddFixed(void)
{
	uint8 k, flag;
	uint8 nAsrAddLength;
	#define DATE_A 6    //�����ά��ֵ
	#define DATE_B 20		//����һά��ֵ
	//��ӹؼ��ʣ��û��޸�
	uint8  sRecog[DATE_A][DATE_B] = {
	 			"liu shui deng",\
				"shan shuo",\
				"kai deng",\
				"kai den",\
				"quan mie",\
				"zhuang tai"\
		
																	};	
	uint8  pCode[DATE_A] = {
	 															CODE_LSD,	\
																CODE_SS,	\
																CODE_AJCF,\
																CODE_AJCF,\
																CODE_QM,	\
																CODE_JT		\
															};	//���ʶ���룬�û��޸�
	flag = 1;
	for (k=0; k<DATE_A; k++)
	{			
		if(LD_Check_ASRBusyFlag_b2() == 0)
		{
			flag = 0;
			break;
		}

		LD_WriteReg(0xc1, pCode[k] );
		LD_WriteReg(0xc3, 0);
		LD_WriteReg(0x08, 0x04);
		LD3320_delay(1);
		LD_WriteReg(0x08, 0x00);
		LD3320_delay(1);

		for (nAsrAddLength=0; nAsrAddLength<DATE_B; nAsrAddLength++)
		{
			if (sRecog[k][nAsrAddLength] == 0)
				break;
			LD_WriteReg(0x5, sRecog[k][nAsrAddLength]);
		}
		LD_WriteReg(0xb9, nAsrAddLength);
		LD_WriteReg(0xb2, 0xff);
		LD_WriteReg(0x37, 0x04);
		
	}
	printf("LD_AsrAddFixed���Ĵ���bf:%x\r\n",LD_ReadReg(0xbf));	
	return flag;
}

static void Board_text(uint8 Code_Val)
{																					 
	switch(Code_Val)  //�Խ��ִ����ز���
	{
		case CODE_LSD:  //�����ˮ�ơ�
//			Glide_LED();
			printf("��ˮ��\r\n");
		break;
		case CODE_SS:	  //�����˸��
//			Flicker_LED();
			printf("��˸\r\n");
		break;
		case CODE_AJCF:	//�������������
//			Key_LED();
			printf("��������\r\n");
		break;
		case CODE_QM:		//���ȫ��
//			Off_LED();
			printf("ȫ��\r\n");
		break;
		case CODE_JT:		//���״̬��
//			Jt_LED();
			printf("״̬\r\n");
		break;
		default:break;
	}	
}

//static void Delayms(uint16 i)
//{
//	unsigned char a,b;
//	for(;i>0;i--)
//	        for(b=4;b>0;b--)
//	            for(a=113;a>0;a--);	
//}

//static void Glide_LED(void)
//{
//	LED1_ON();
//	Delayms(0xfff);
//	LED2_ON();
//	Delayms(0xfff);
//	LED3_ON();
//	Delayms(0xfff);
//	LED4_ON();
//	Delayms(0xfff);
//	LED1_OFF();
//	Delayms(0xfff);
//	LED2_OFF();
//	Delayms(0xfff);
//	LED3_OFF();
//	Delayms(0xfff);
//	LED4_OFF();
//	Delayms(0xfff);
//}

//static void Flicker_LED(void)
//{
//	LED1_ON();
//	LED2_ON();
//	Delayms(0XFFF);
//	LED1_OFF();
//	LED2_OFF();
//	Delayms(0XFFF);
//}

//static void Key_LED(void)
//{
//	LED3_ON();
//	Delayms(0XFFF);
//	LED3_OFF();
//	Delayms(0XFFF);

//}

//static void Off_LED(void)
//{
//	LED1_OFF();
//	LED2_OFF();
//	LED3_OFF();
//	LED4_OFF();
//}

//static void Jt_LED(void)
//{
//	LED4_ON();
//	Delayms(0XFFF);
//	LED4_OFF();
//	Delayms(0XFFF);
//}
///�û��޸� end

///��س�ʼ��
static void LD3320_init(void)
{
	LD3320_GPIO_Cfg();	
	LD3320_EXTI_Cfg();
//	LD3320_SPI_cfg();
//	LED_GPIO_cfg();
	LD_reset();
//	HAL_Delay(100);
//	LD_reset();
}

static void LD3320_GPIO_Cfg(void)
{	
	GPIO_InitTypeDef GPIO_InitStructure;
	
//	RCC_APB2PeriphClockCmd(LD3320RST_GPIO_CLK | LD3320CS_GPIO_CLK,ENABLE);
	//LD_CS	/RSET
	GPIO_InitStructure.Pin =LD3320CS_PIN;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	HAL_GPIO_Init(LD3320CS_GPIO_PORT,&GPIO_InitStructure);

	GPIO_InitStructure.Pin =LD3320RST_PIN;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	HAL_GPIO_Init(LD3320RST_GPIO_PORT,&GPIO_InitStructure);
	
	GPIO_InitStructure.Pin = LD3320WR_PIN;				
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	HAL_GPIO_Init(LD3320WR_GPIO_PORT, &GPIO_InitStructure);
	
}

static void LD3320_EXTI_Cfg(void)
{
	GPIO_InitTypeDef GPIO_Initure;
    GPIO_Initure.Pin=LD3320IRQ_PIN;               //
    GPIO_Initure.Mode=GPIO_MODE_IT_FALLING;     //�½��ش���
    GPIO_Initure.Pull=GPIO_PULLUP;
    HAL_GPIO_Init(LD3320IRQ_GPIO_PORT,&GPIO_Initure);	
   
	HAL_NVIC_SetPriority(EXTI15_10_IRQn,2,3);   //��ռ���ȼ�Ϊ2�������ȼ�Ϊ3
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);         //ʹ���ж���13  

//  EXTI_InitTypeDef EXTI_InitStructure;
//  NVIC_InitTypeDef NVIC_InitStructure;
//  GPIO_InitTypeDef GPIO_InitStructure;
//  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	

//  RCC_APB2PeriphClockCmd(LD3320IRQ_GPIO_CLK, ENABLE);
//  GPIO_InitStructure.GPIO_Pin =LD3320IRQ_PIN;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_Init(LD3320IRQ_GPIO_PORT, &GPIO_InitStructure);
//	//�ⲿ�ж�������
//  GPIO_EXTILineConfig(LD3320IRQEXIT_PORTSOURCE, LD3320IRQPINSOURCE);
//  EXTI_InitStructure.EXTI_Line = LD3320IRQEXITLINE;
//  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
//  EXTI_InitStructure.EXTI_Trigger =EXTI_Trigger_Falling;
//  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//  EXTI_Init(&EXTI_InitStructure);
//	//�ж�Ƕ������
//  NVIC_InitStructure.NVIC_IRQChannel = LD3320IRQN;
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//  NVIC_Init(&NVIC_InitStructure);
}

//static void LD3320_SPI_cfg(void)
//{
//	SPI_InitTypeDef  SPI_InitStructure;
//	GPIO_InitTypeDef GPIO_InitStructure;
//  //spi�˿�����
//	RCC_APB2PeriphClockCmd(LD3320SPI_CLK,ENABLE);		
//  RCC_APB2PeriphClockCmd(LD3320WR_GPIO_CLK | LD3320SPIMISO_GPIO_CLK | LD3320SPIMOSI_GPIO_CLK | LD3320SPISCK_GPIO_CLK,ENABLE);
//	
//	GPIO_InitStructure.GPIO_Pin = LD3320SPIMISO_PIN;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//	GPIO_Init(LD3320SPIMISO_GPIO_PORT,&GPIO_InitStructure);
//	
//	GPIO_InitStructure.GPIO_Pin = LD3320SPIMOSI_PIN;
//	GPIO_Init(LD3320SPIMOSI_GPIO_PORT,&GPIO_InitStructure);

//	GPIO_InitStructure.GPIO_Pin = LD3320SPISCK_PIN;
//	GPIO_Init(LD3320SPISCK_GPIO_PORT,&GPIO_InitStructure);
//	
//	GPIO_InitStructure.GPIO_Pin = LD3320WR_PIN;				
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//	GPIO_Init(LD3320WR_GPIO_PORT, &GPIO_InitStructure);
//	
//	LD_CS_H();
//	
//	SPI_Cmd(LD3320SPI, DISABLE);

//	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;   	//ȫ˫��
//	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;						   						//��ģʽ
//	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;					   					//8λ
//	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;						   							//ʱ�Ӽ��� ����״̬ʱ��SCK���ֵ͵�ƽ
//	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;						   						//ʱ����λ ���ݲ����ӵ�һ��ʱ�ӱ��ؿ�ʼ
//	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;							   							//�������NSS
//	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64;   //�����ʿ��� SYSCLK/128
//	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;				   					//���ݸ�λ��ǰ
//	SPI_InitStructure.SPI_CRCPolynomial = 7;							   							//CRC����ʽ�Ĵ�����ʼֵΪ7
//	SPI_Init(LD3320SPI, &SPI_InitStructure);

//	SPI_Cmd(LD3320SPI, ENABLE);
//}

//static void LED_GPIO_cfg(void)
//{	
//	GPIO_InitTypeDef GPIO_InitStructure;

//	RCC_APB2PeriphClockCmd(LED1_GPIO_CLK | LED2_GPIO_CLK | LED3_GPIO_CLK | LED4_GPIO_CLK,ENABLE);

//	GPIO_InitStructure.GPIO_Pin = LED1_PIN;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//	GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStructure);
//	GPIO_InitStructure.GPIO_Pin = LED2_PIN;
//	GPIO_Init(LED2_GPIO_PORT, &GPIO_InitStructure);
//	GPIO_InitStructure.GPIO_Pin = LED3_PIN;
//	GPIO_Init(LED3_GPIO_PORT, &GPIO_InitStructure);
//	GPIO_InitStructure.GPIO_Pin = LED4_PIN;
//	GPIO_Init(LED4_GPIO_PORT, &GPIO_InitStructure);	

//	LED1_OFF();
//	LED2_OFF();
//	LED3_OFF();
//	LED4_OFF();
//}
///��س�ʼ�� end 

///�м��
void EXTI15_10_IRQHandler(void)
{
	HAL_GPIO_EXTI_IRQHandler(LD3320IRQ_PIN);
//	if(EXTI_GetITStatus(LD3320IRQEXITLINE)!= RESET ) 
//	{
//		ProcessInt(); 
// 		printf("�����ж�12\r\n");	
//		EXTI_ClearFlag(LD3320IRQEXITLINE);
//		EXTI_ClearITPendingBit(LD3320IRQEXITLINE);//���LINE�ϵ��жϱ�־λ  
//	} 
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    HAL_Delay(10);      //����
	if(LD3320IRQ_PIN==GPIO_Pin)
	{
		ProcessInt(); 
 		printf("�����ж�12\r\n");		
	}
}
static void LD3320_delay(unsigned long uldata)
{
	unsigned int i  =  0;
	unsigned int j  =  0;
	unsigned int k  =  0;
	for (i=0;i<5;i++)
	{
		for (j=0;j<uldata;j++)
		{
			k = 200;
			while(k--);
		}
	}
}

static uint8 RunASR(void)
{
	uint8 i=0;
	uint8 asrflag=0;
	for (i=0; i<5; i++)		//��ֹ����Ӳ��ԭ����LD3320оƬ����������������һ������5������ASRʶ������
	{
		LD_AsrStart();			//��ʼ��ASR
		LD3320_delay(100);
		if (LD_AsrAddFixed()==0)	//��ӹؼ����ﵽLD3320оƬ��
		{
			LD_reset();				//LD3320оƬ�ڲ����ֲ���������������LD3320оƬ
			LD3320_delay(50);	//���ӳ�ʼ����ʼ����ASRʶ������
			printf("LD_AsrAddFixed error\r\n");
			continue;
		}
		LD3320_delay(10);
		if (LD_AsrRun() == 0)
		{
			LD_reset();			 //LD3320оƬ�ڲ����ֲ���������������LD3320оƬ
			LD3320_delay(50);//���ӳ�ʼ����ʼ����ASRʶ������
			printf("LD_AsrRun error\r\n");
			continue;
		}
		asrflag=1;
		break;						//ASR���������ɹ����˳���ǰforѭ������ʼ�ȴ�LD3320�ͳ����ж��ź�
	}
	LD_WriteReg(0x37, 0x06);		//���Դ���
	LD3320_delay(10);
	printf("RunASR���Ĵ���bf:%x\r\n",LD_ReadReg(0xbf));
	return asrflag;
}

static void LD_reset(void)
{
	LD_RST_H();
	LD3320_delay(100);
	LD_RST_L();
	LD3320_delay(100);
	LD_RST_H();
	LD3320_delay(100);
	LD_CS_L();
	LD3320_delay(100);
	LD_CS_H();		
	LD3320_delay(100);
	
	LD_ReadReg(0x6); 
    LD_WriteReg(0x35, 0x33);
    LD_WriteReg(0x1b, 0x55);     
	LD_WriteReg(0xb3, 0xaa);	
//	printf("���Ĵ���06:%x\r\n",LD_ReadReg(0x06));
//	printf("���Ĵ���06:%x\r\n",LD_ReadReg(0x06));
	printf("���Ĵ���35:%x\r\n",LD_ReadReg(0x35));
	printf("���Ĵ���1b:%x\r\n",LD_ReadReg(0x1b));
	printf("���Ĵ���b3:%x\r\n",LD_ReadReg(0xb3));
}

static void LD_AsrStart(void)
{
	LD_Init_ASR();
}

uint8 LD_Check_ASRBusyFlag_b2(void)
{
	uint8 j;
	uint8 flag = 0;
	for (j=0; j<10; j++)
	{
		if (LD_ReadReg(0xb2) == 0x21)
		{
			flag = 1;
			break;
		}
		LD3320_delay(10);		
	}
	return flag;
}
///�м��end


///�Ĵ�������
static uint8 spi_send_byte(uint8 byte)
{

    uint8 TxData=byte;
	uint8 RxData;
	int state=5;
    state=HAL_SPI_TransmitReceive(&hspi1,&TxData,&RxData,1, 1000); 
//	printf("spi state:%d\r\n",state);
 	return RxData; 
	
//	while (SPI_I2S_GetFlagStatus(LD3320SPI, SPI_I2S_FLAG_TXE) == RESET);
//	SPI_I2S_SendData(LD3320SPI,byte);
//	while (SPI_I2S_GetFlagStatus(LD3320SPI,SPI_I2S_FLAG_RXNE) == RESET);
//	return SPI_I2S_ReceiveData(LD3320SPI);	
}

static void LD_WriteReg(uint8 data1,uint8 data2)
{
	LD_CS_L();
	LD_SPIS_L();
	spi_send_byte(0x04);
	spi_send_byte(data1);
	spi_send_byte(data2);
	LD_CS_H();
}

static uint8 LD_ReadReg(uint8 reg_add)
{
	uint8 i;
	LD_CS_L();
	LD_SPIS_L();
	spi_send_byte(0x05);
	spi_send_byte(reg_add);
	i=spi_send_byte(0x00);
	LD_CS_H();
	return(i);
}

static uint8 LD_GetResult(void)
{
	return LD_ReadReg(0xc5);
}

static uint8 LD_AsrRun(void)
{
	LD_WriteReg(0x35, MIC_VOL);
	LD_WriteReg(0x1C, 0x09);
	LD_WriteReg(0xBD, 0x20);
	LD_WriteReg(0x08, 0x01);
	LD3320_delay( 5 );
	LD_WriteReg(0x08, 0x00);
	LD3320_delay( 5);

	if(LD_Check_ASRBusyFlag_b2() == 0)
	{
		return 0;
	}

	LD_WriteReg(0xB2, 0xff);	
	LD_WriteReg(0x37, 0x06);
	LD_WriteReg(0x37, 0x06);
	LD3320_delay(5);
	LD_WriteReg(0x1C, 0x0b);
	LD_WriteReg(0x29, 0x10);
	LD_WriteReg(0xBD, 0x00);   
	return 1;
}

static void ProcessInt(void)
{
	uint8 nAsrResCount=0;

	ucRegVal = LD_ReadReg(0x2B);

	if(nLD_Mode == LD_MODE_ASR_RUN)
	{	
	
	// ����ʶ��������ж�
	//�����������룬����ʶ��ɹ���ʧ�ܶ����жϣ�
		LD_WriteReg(0x29,0);
		LD_WriteReg(0x02,0);

		if((ucRegVal & 0x10) && LD_ReadReg(0xb2)==0x21 && LD_ReadReg(0xbf)==0x35)		
		{	 
				nAsrResCount = LD_ReadReg(0xba);

				if(nAsrResCount>0 && nAsrResCount<=4) 
				{
					nAsrStatus=LD_ASR_FOUNDOK; 				
				}
				else
				{
					nAsrStatus=LD_ASR_FOUNDZERO;
					printf("�ʹ���������ȫƥ��\r\n");
				}	
		}
		else
		{
			nAsrStatus=LD_ASR_FOUNDZERO;//ִ��û��ʶ��
			printf("ֻ���������������\r\n");
		}

		LD_WriteReg(0x2b,0);
		LD_WriteReg(0x1C,0);//д0:ADC������
		LD_WriteReg(0x29,0);
		LD_WriteReg(0x02,0);
		LD_WriteReg(0x2B,0);
		LD_WriteReg(0xBA,0);	
		LD_WriteReg(0xBC,0);	
		LD_WriteReg(0x08,1);//���FIFO_DATA
		LD_WriteReg(0x08,0);//���FIFO_DATA�� �ٴ�д0
		return;
		
	}
	
	if(nLD_Mode == LD_MODE_MP3)
	{	
		// �������Ų������жϣ������֣�
		// A. ����������ȫ�������ꡣ
		// B. ���������ѷ�����ϡ�
		// C. ����������ʱ��Ҫ���꣬��Ҫ�����µ����ݡ�	
		ucHighInt = LD_ReadReg(0x29); 
		ucLowInt=LD_ReadReg(0x02); 
		LD_WriteReg(0x29,0) ;
		LD_WriteReg(0x02,0) ;
		if(LD_ReadReg(0xBA)&CAUSE_MP3_SONG_END)
		{
		// A. ����������ȫ�������ꡣ

			LD_WriteReg(0x2B,  0);
			LD_WriteReg(0xBA, 0);	
			LD_WriteReg(0xBC,0x0);	
			bMp3Play=0;					// ��������ȫ����������޸�bMp3Play�ı���
			LD_WriteReg(0x08,1);
			LD3320_delay(5);
			LD_WriteReg(0x08,0);
			LD_WriteReg(0x33, 0);

			return ;
		 }

		 if(nMp3Pos>=nMp3Size)
		{
		// B. ���������ѷ�����ϡ�

			LD_WriteReg(0xBC, 0x01);
			LD_WriteReg(0x29, 0x10);
	//		bMp3Play=0;				//	��ʱ��ֻ������MCU������MP3���ݷ��͵�LD3320оƬ�ڣ����ǻ�û�а����������ȫ���������
	//		EX0=1;

			return;	
		}

		// C. ����������ʱ��Ҫ���꣬��Ҫ�����µ����ݡ�	

		LD_ReloadMp3Data();
			
		LD_WriteReg(0x29,ucHighInt); 
		LD_WriteReg(0x02,ucLowInt) ;

		LD3320_delay(15);
	//	EX0=1;
	}
}

static void LD_Init_Common(void)
{
	bMp3Play = 0;
	LD_ReadReg(0x06);  
	LD_WriteReg(0x17, 0x35); 
	LD3320_delay(5);
	LD_ReadReg(0x06);  

	LD_WriteReg(0x89, 0x03);  
	LD3320_delay(5);
	LD_WriteReg(0xCF, 0x43);   
	LD3320_delay(5);
	LD_WriteReg(0xCB, 0x02);
	
	/*PLL setting*/
	LD_WriteReg(0x11, LD_PLL_11);       
	if (nLD_Mode == LD_MODE_MP3)
	{
		LD_WriteReg(0x1E, 0x00); 
		LD_WriteReg(0x19, LD_PLL_MP3_19);   
		LD_WriteReg(0x1B, LD_PLL_MP3_1B);   
		LD_WriteReg(0x1D, LD_PLL_MP3_1D);
	}
	else
	{
		LD_WriteReg(0x1E,0x00);
		LD_WriteReg(0x19, LD_PLL_ASR_19); 
		LD_WriteReg(0x1B, LD_PLL_ASR_1B);		
	  LD_WriteReg(0x1D, LD_PLL_ASR_1D);
	}
	LD3320_delay(5);
	
	LD_WriteReg(0xCD, 0x04);
	LD_WriteReg(0x17, 0x4c); 
	LD3320_delay(1);
	LD_WriteReg(0xB9, 0x00);
	LD_WriteReg(0xCF, 0x4F); 
	LD_WriteReg(0x6F, 0xFF); 
}

static void LD_Init_ASR(void)
{
	nLD_Mode=LD_MODE_ASR_RUN;
	LD_Init_Common();

	LD_WriteReg(0xBD, 0x00);
	LD_WriteReg(0x17, 0x48);	
	LD3320_delay(5);
	LD_WriteReg(0x3C, 0x80);    
	LD_WriteReg(0x3E, 0x07);
	LD_WriteReg(0x38, 0xff);    
	LD_WriteReg(0x3A, 0x07);
	LD_WriteReg(0x40, 0);          
	LD_WriteReg(0x42, 8);
	LD_WriteReg(0x44, 0);    
	LD_WriteReg(0x46, 8); 
	LD3320_delay( 1 );
}

void LD_Init_MP3()
{
	nLD_Mode = LD_MODE_MP3;
	LD_Init_Common();

	LD_WriteReg(0xBD,0x02);
	LD_WriteReg(0x17, 0x48);
	LD3320_delay( 10 );

	LD_WriteReg(0x85, 0x52); 
	LD_WriteReg(0x8F, 0x00);  
	LD_WriteReg(0x81, 0x00);
	LD_WriteReg(0x83, 0x00);
	LD_WriteReg(0x8E, 0xff);
	LD_WriteReg(0x8D, 0xff);
    LD3320_delay( 1 );
	LD_WriteReg(0x87, 0xff);
	LD_WriteReg(0x89, 0xff);
	LD3320_delay( 1 );
	LD_WriteReg(0x22, 0x00);    
	LD_WriteReg(0x23, 0x00);
	LD_WriteReg(0x20, 0xef);    
	LD_WriteReg(0x21, 0x07);
	LD_WriteReg(0x24, 0x77);          
    LD_WriteReg(0x25, 0x03);
    LD_WriteReg(0x26, 0xbb);    
    LD_WriteReg(0x27, 0x01); 
}


void LD_AdjustMIX2SPVolume(uint8 val)
{
	ucSPVol = val;
	val = ((15-val)&0x0f) << 2;
	LD_WriteReg(0x8E, val | 0xc3); 
	LD_WriteReg(0x87, 0x78); 
}

void LD_ReloadMp3Data()
{
//	uint32 nCurMp3Pos;
	uint8 val;
//	uint8 k;
	
	if (nDemoFlag)
	{
		printf("Start Reload1 \r\n");
		ucStatus = LD_ReadReg(0x06);
		printf("Start reg6: %x \r\n",ucStatus);
		while ( !(ucStatus&MASK_FIFO_STATUS_AFULL) && (nMp3Pos<nMp3Size) )
		{
			
			val = bpDemoSound[nMp3Pos++];
			LD_WriteReg(0x01,val);
			if (nMp3Pos == DEMO_SOUND_SIZE)
				nMp3Pos = 0;
//			printf("Start Reload2 \r\n");
			ucStatus = LD_ReadReg(0x06);
		}
		
	}

}



///�Ĵ������� end
/*********************************************END OF FILE**********************/
