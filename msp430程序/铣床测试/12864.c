/***********************************************************
程序功能：在12864液晶上显示一屏汉字
测试说明：观察液晶显示
***********************************************************/
#include "msp430.h"
#include "msp430x14x.h"
#include "12864.h"

uchar x=135;
int *p;

extern const unsigned char shuzi_table[];

void Delay_1ms(void)
{
	uchar i;
    
	for(i = 150;i > 0;i--)  _NOP();
} 
/*******************************************
函数名称：Delay_Nms
功    能：延时N个1ms的时间
参    数：n--延时长度
返回值  ：无
********************************************/
void Delay_Nms(uint n)
{
    uint i;
    
    for(i = n;i > 0;i--)    Delay_1ms();
}
/*******************************************
函数名称：Write_Cmd
功    能：向液晶中写控制命令
参    数：cmd--控制命令
返回值  ：无
********************************************/
void Write_Cmd(uchar cmd)
{
    uchar lcdtemp = 0;
			
    LCD_RS_L;
    LCD_RW_H;
    LCD_DataIn;  
    do                       //判忙
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
函数名称：Write_Data
功    能：向液晶中写显示数据
参    数：dat--显示数据
返回值  ：无
********************************************/
void  Write_Data(uchar dat)
{
    uchar lcdtemp = 0;   
        
    LCD_RS_L;
    LCD_RW_H;  
    LCD_DataIn;   
    do                       //判忙
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
函数名称：Ini_Lcd
功    能：初始化液晶模块
参    数：无
返回值  ：无
********************************************/
void Ini_Lcd(void)
{                  
///////////////////////////////////////
  	LCD_RST_L;                            //复位LCD
        Delay_1ms();                        	//保证复位所需要的时间
	LCD_RST_H;                            //恢复LCD正常工作
	_NOP();
	LCD_PSB_H;                            //设置LCD为8位并口通信
  ////////////////////////////////////////
  
  LCD_CMDOut;    //液晶控制端口设置为输出
    
    Delay_Nms(500);
    Write_Cmd(0x30);   //基本指令集
    Delay_1ms();
    Write_Cmd(0x02);   // 地址归位
    Delay_1ms();
	Write_Cmd(0x0c);   //整体显示打开,游标关闭
    Delay_1ms();
	Write_Cmd(0x01);   //清除显示
    Delay_1ms();
	Write_Cmd(0x06);   //游标右移
    Delay_1ms();
	Write_Cmd(0x80);   //设定显示的起始地址
}
/*******************************************
函数名称：Disp_HZ
功    能：控制液晶显示汉字
参    数：addr--显示位置的首地址
          pt--指向显示数据的指针
          num--显示字符个数
返回值  ：无
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
/***************************主函数************************
void main( void )
{

    WDTCTL = WDTPW + WDTHOLD;    //关狗
    a[0]=1+'0';;
    a[1]=2+'0';;
    a[2]=3+'0';;
    a[3]=4+'0';;
     
    Ini_Lcd();                  //初始化液晶
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
函数名称：Delay_1ms
功    能：延时约1ms的时间
参    数：无
返回值  ：无
********************************************/