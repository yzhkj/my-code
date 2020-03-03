#ifndef __12864_h__
#define __12864_h__
typedef unsigned char uchar;
typedef unsigned int  uint;
#define LCD_DataIn    P2DIR=0x00    //数据口方向设置为输入
#define LCD_DataOut   P2DIR=0xff    //数据口方向设置为输出
#define LCD2MCU_Data  P2IN
#define MCU2LCD_Data  P2OUT
#define LCD_CMDOut    P6DIR|=0xFC     //P3口的低三位设置为输出
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
const char hang2[] = {"太平须得边将忠臣"};
const char hang3[] = {"但得百僚师长肝胆"};
const char hang4[] = {"不用三军罗绮金银"};

#endif