/***********************************************************
�����ܣ���12864Һ������ʾһ������
����˵�����۲�Һ����ʾ
***********************************************************/
#include  "msp430.h"
#include  "msp430x14x.h"
typedef unsigned char uchar;
typedef unsigned int  uint;
#define LCD_DataIn    P2DIR=0x00    //���ݿڷ�������Ϊ����
#define LCD_DataOut   P2DIR=0xff    //���ݿڷ�������Ϊ���
#define LCD2MCU_Data  P2IN
#define MCU2LCD_Data  P2OUT
#define LCD_CMDOut    P6DIR|=0xFC     //P3�ڵĵ���λ����Ϊ���
#define LCD_RS_H      P6OUT|=BIT3      //P6.2
#define LCD_RS_L      P6OUT&=~BIT3     //P6.2
#define LCD_RW_H      P6OUT|=BIT4      //P6.3
#define LCD_RW_L      P6OUT&=~BIT4     //P6.3
#define LCD_EN_H      P6OUT|=BIT5      //P6.4
#define LCD_EN_L      P6OUT&=~BIT5     //P6.4
#define LCD_PSB_H      P6OUT|=BIT6      //P6.5
#define LCD_PSB_L      P6OUT&=~BIT6     //P6.5
#define LCD_RST_H      P6OUT|=BIT6      //P6.6
#define LCD_RST_L      P6OUT&=~BIT6     //P6.6
/*******************************************/
void Delay_1ms(void);
void Delay(unsigned int n);
void Write_Cmd(unsigned char cod);
void Write_Data(unsigned char dat);
void Ini_Lcd(void);
void Disp_HZ(unsigned char addr, const unsigned char * pt,unsigned char num);
void Disp_SZ(unsigned char addr, const unsigned char * pt,unsigned char num);
void Disp_ND(unsigned char addr,unsigned int  thickness);
void Draw_TX(unsigned char Yaddr,unsigned char Xaddr,const unsigned char * dp) ; 
void Draw_PM(const unsigned char *ptr);

/*******************************************/
const char hang1[] = {"qweeeweeeeeeeeee"};
const char hang2[] = {"̫ƽ��ñ߽��ҳ�"};
const char hang3[] = {"���ð���ʦ���ε�"};
const char hang4[] = {"����������粽���"};
 
uchar x=135;
int *p;



extern const unsigned char shuzi_table[];
/***************************������************************
void main( void )
{

    WDTCTL = WDTPW + WDTHOLD;    //�ع�
    a[0]=1+'0';;
    a[1]=2+'0';;
    a[2]=3+'0';;
    a[3]=4+'0';;
     
    Ini_Lcd();                  //��ʼ��Һ��
               //"qweeeweeeeeeeeee"
    Disp_HZ(0x80,a  ,2);
    Disp_HZ(0x90,hang2,8);
    Disp_HZ(0x88,hang3,8);
    Disp_HZ(0x98,hang4,8);
    
    
}
*/



/*void translate(int data)
{ const uchar dis[];
  if(data<0)
  {
    dis[0]='-';
    data=-data;
  }
  else
    dis[0]=' ';
  dis[1]=data/100+'0';
  data=data%100;
  dis[2]=data/10+'0';
  dis[3]=data%10+'0';
  dis[4]=' '; 
}
 */
/*******************************************
�������ƣ�Delay_1ms
��    �ܣ���ʱԼ1ms��ʱ��
��    ������
����ֵ  ����
********************************************/
void Delay_1ms(void)
{
	uchar i;
    
	for(i = 150;i > 0;i--)  _NOP();
} 
/*******************************************
�������ƣ�Delay_Nms
��    �ܣ���ʱN��1ms��ʱ��
��    ����n--��ʱ����
����ֵ  ����
********************************************/
void Delay_Nms(uint n)
{
    uint i;
    
    for(i = n;i > 0;i--)    Delay_1ms();
}
/*******************************************
�������ƣ�Write_Cmd
��    �ܣ���Һ����д��������
��    ����cmd--��������
����ֵ  ����
********************************************/
void Write_Cmd(uchar cmd)
{
    uchar lcdtemp = 0;
			
    LCD_RS_L;
    LCD_RW_H;
    LCD_DataIn;  
    do                       //��æ
    {    
        LCD_EN_H;
       	_NOP();					
       	lcdtemp = LCD2MCU_Data; 
       	LCD_EN_L;
        
    }
    while(lcdtemp & 0x80); 
    
    LCD_DataOut;    
    LCD_RW_L;  		
    MCU2LCD_Data = cmd; 
    LCD_EN_H;
    _NOP();						  			
    LCD_EN_L;
}
/*******************************************
�������ƣ�Write_Data
��    �ܣ���Һ����д��ʾ����
��    ����dat--��ʾ����
����ֵ  ����
********************************************/
void  Write_Data(uchar dat)
{
    uchar lcdtemp = 0;   
        
    LCD_RS_L;
    LCD_RW_H;  
    LCD_DataIn;   
    do                       //��æ
    {    
        LCD_EN_H;
        _NOP();						
        lcdtemp = LCD2MCU_Data; 
        LCD_EN_L;      
    }
    while(lcdtemp & 0x80);  
    
    LCD_DataOut; 
    LCD_RS_H;
    LCD_RW_L;  
        
    MCU2LCD_Data = dat;
    LCD_EN_H;
    _NOP();
    LCD_EN_L;
}  
/*******************************************
�������ƣ�Ini_Lcd
��    �ܣ���ʼ��Һ��ģ��
��    ������
����ֵ  ����
********************************************/
void Ini_Lcd(void)
{                  
///////////////////////////////////////
  	LCD_RST_L;                            //��λLCD
        Delay_1ms();                        	//��֤��λ����Ҫ��ʱ��
	LCD_RST_H;                            //�ָ�LCD��������
	_NOP();
	LCD_PSB_H;                            //����LCDΪ8λ����ͨ��
  ////////////////////////////////////////
  
  LCD_CMDOut;    //Һ�����ƶ˿�����Ϊ���
    
    Delay_Nms(500);
    Write_Cmd(0x30);   //����ָ�
    Delay_1ms();
    Write_Cmd(0x02);   // ��ַ��λ
    Delay_1ms();
	Write_Cmd(0x0c);   //������ʾ��,�α�ر�
    Delay_1ms();
	Write_Cmd(0x01);   //�����ʾ
    Delay_1ms();
	Write_Cmd(0x06);   //�α�����
    Delay_1ms();
	Write_Cmd(0x80);   //�趨��ʾ����ʼ��ַ
}
/*******************************************
�������ƣ�Disp_HZ
��    �ܣ�����Һ����ʾ����
��    ����addr--��ʾλ�õ��׵�ַ
          pt--ָ����ʾ���ݵ�ָ��
          num--��ʾ�ַ�����
����ֵ  ����
********************************************/
void Disp_HZ(uchar addr,const uchar * pt,uchar num)
{
    uchar i;
		
    Write_Cmd(addr); 
   	for(i = 0;i < (num*2);i++) 
        Write_Data(*(pt++)); 
} 
void Disp_SZ(uchar addr,const uchar * pt,uchar num)
{
    uchar i;
		
    Write_Cmd(addr); 
   	for(i = 0;i < (num);i++) 
        Write_Data(*(pt++)); 
} 