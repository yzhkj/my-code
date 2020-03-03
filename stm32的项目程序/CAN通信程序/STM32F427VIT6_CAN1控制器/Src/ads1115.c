#include "ads1115.h"


static void ADS1115_delay(u16 D)
{
	D=D*2;
	while(--D);
}

void delay_nms(u16 ms)
{
	u16 i;
	u32 M = 0;//720W
	for(i = 0;i < ms; i++)
	for(M=12000;M > 0;M--);
}

void delay_nus(u16 us)
{
	u16 i;
	u16 M = 0;//720W
	for(i = 0;i < us; i++)
	for(M=72;M > 0;M--);
}



void ADS1115_Init(void)
{
//  GPIO_InitTypeDef GPIO_InitStructure;
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB ,ENABLE);

//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;//A SCL SDA
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//	GPIO_Init(GPIOB, &GPIO_InitStructure);

//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;//B SCL SDA
//	GPIO_Init(GPIOB, &GPIO_InitStructure);


    SDA_A1;
    SCL_A1;
	
//	  SDA_B1;
//    SCL_B1;
		
	

	delay_nms(15);
	ADS1115Config_A(0xf0,0x62);//����ADͨ��2  ����ת��ģʽAINP = AIN2 and AINN = GND
	//	delay_nms(5);
//	ADS_1115PointRegister_A();
	delay_nms(15);
//	ADS1115Config_B(0xf0,0xe2);//����ADͨ��2



//ADS1115Config(0xf0,0x62);
//	SetThresHold_A(1000,30000);//��������  ����

}

//I2C��������
void I2CStart_A(void)
{
   SDA_A1;
   ADS1115_delay(50);
   SCL_A1;
   ADS1115_delay(50);
   SDA_A0;
   ADS1115_delay(50);//MIN 160ns
   SCL_A0;
   ADS1115_delay(50);
}


//I2Cֹͣ����
void I2CStop_A(void)
{
   SDA_A0;
   ADS1115_delay(50);
   SCL_A1;
   ADS1115_delay(50);
   SDA_A1;
   ADS1115_delay(50);//MIN 160ns
}





//I2C дһ�ֽ�
void I2CWriteByte_A(u8 DATA)
{
      u8 i;
      SDA_AOUT;
      SCL_A0;
      for(i = 0;i < 8; i++)
      {
         if(DATA&0x80)
         {
              SDA_A1;
         }
         else
         {
              SDA_A0;
         }
         SCL_A1;//�����ֲ᲻����ʱ
         ADS1115_delay(50);
         SCL_A0;
         ADS1115_delay(50);
         DATA	= DATA << 1;  
      }
      SDA_A1;
      SCL_A1;
      ADS1115_delay(50);
      SCL_A0;
}


//I2C ��һ�ֽ�
u8 I2CReadByte_A(void)
{
    u8 TData=0,i;
		SDA_AIN;	
    for(i=0;i<8;i++)
    {
			SCL_A1;
			ADS1115_delay(50);
			TData=TData<<1;			
			if(SDA_AI)
			{
				TData|=0x01;
			}
			SCL_A0;
			ADS1115_delay(50);
    }	
    SCL_A0;
		SDA_AOUT;
    ADS1115_delay(50);
    SDA_A0;
    ADS1115_delay(50);
    SCL_A1;
    ADS1115_delay(50);
    SCL_A0;
    ADS1115_delay(50);
    SDA_A1;
    return TData;
}


//I2C ��һ�ֽ�


/*********************************************************************
*��������:  ADS1115Config
*��	   ���� ����ADS1115����ͨ�����ã�����ʱ��ȵ�
*��	   ���� HCMD �������ָ�8λ(ͨ�������̣�ת��ģʽ)
			LCMD : �����ֵ�8λ(���������� �Ƚ�ģʽ ��Ч��ƽ �ź��������)
*��	   �أ� ��
********************************************************************/
void ADS1115Config_A(u8 LCMD,u8 HCMD)//���üĴ���
{
    u8 i=0;
    u8 Initdata[4];

    Initdata[0] = WR_REG;  // ��ַ0x90  ����ADR�ӵ� д�Ĵ���
    Initdata[1] = CONF_REG;// ��ַ0x01  ָ�����üĴ���
    Initdata[2] = HCMD;    // ��ַ0x64  �����ָ��ֽ�
    Initdata[3] = LCMD;    // ��ַ0xf0  �����ֵ��ֽ�
    SCL_A1;
    I2CStart_A();
    for(i=0;i<4;i++)
    {
    	I2CWriteByte_A(Initdata[i]);
    	ADS1115_delay(10);
    }
    I2CStop_A();
}
/*
void ADS_1115PointRegister_A(void)
{
	u8 i=0;
	u8 InitData[2];
	InitData[0] = WR_REG;  // ��ַ0x90   д�Ĵ���
  InitData[1] = DATA_REG;// ��ַ0x00     ָ��ָ��ת�����ݼĴ���
	SCL_A1;
  I2CStart_A();
	for(i=0;i<2;i++)
    {
    	I2CWriteByte_A(InitData[i]);
    	ADS1115_delay(10);
    }
    I2CStop_A();
}
*/
void SetThresHold_A(u16 L_TH,u16 H_TH)
{
   SCL_A1;
   I2CStart_A();
   I2CWriteByte_A(WR_REG);
   I2CWriteByte_A(LOTH_REG);//��ͷ�ֵ�Ĵ���
   I2CWriteByte_A((L_TH>>8));
   I2CWriteByte_A(L_TH);
   I2CStop_A();

   I2CStart_A();
   I2CWriteByte_A(WR_REG);
   I2CWriteByte_A(HITH_REG);//��߷�ֵ�Ĵ���
   I2CWriteByte_A((H_TH>>8));
   I2CWriteByte_A(H_TH);
   I2CStop_A();
}

/*******************************************************************
*��������:  ReadAD_A
*��	   ���� ��ȡADת����ֵ
*��	   ���� ��ȡ��ֵΪ��ǰ�����õ��Ǹ�ͨ��
*��	   �أ� ��
********************************************************************/
u16 ReadAD_A(void)
{
   u16 Data[2]={0,0};

   SCL_A1;
   I2CStart_A();
   I2CWriteByte_A(WR_REG);//ָ��ָ��Ĵ���
   I2CWriteByte_A(DATA_REG);
   I2CStop_A();
	 SCL_A0;

   SCL_A1;
   I2CStart_A();
   I2CWriteByte_A(RE_REG);//��
   Data[0] = I2CReadByte_A();
   Data[1] = I2CReadByte_A();
   I2CStop_A();
   //���Գ���
//	 printf("Data[0]:0x%x\t\n",Data[0]);
//	 printf("Data[1]:0x%x\t\n",Data[1]);
   Data[0] = Data[0]<<8 | Data[1];
//	 if(Data[0]>0x7fff)      //������ת��Ϊ����
//		 Data[0]=~Data[0]+1;
   return  (Data[0]);//&0x7fff
}


u16 getad_A(void)
{
    u32 value=0;
	  ADS1115_Init();  
    delay_nms(5);
    ADS1115Config_A(0xf0,0x64);		  //AINP = AIN0 and AINN = AIN1 (default)
    delay_nms(5); 
    value=4.096*2*ReadAD_A()/65535;
    return value;
}

