#ifndef __CONFIG_H_
#define __CONFIG_H_
             /*
#define CPU_F ((double)8000000) 
#define delay_us(x) __delay_cycles((long)(CPU_F*(double)x/1000000.0)) 
#define delay_ms(x) __delay_cycles((long)(CPU_F*(double)x/1000.0)) 
             */
#define uchar unsigned char
#define uint  unsigned int
#define ulong unsigned long

/*当BRCLK=CPU_F时用下面的公式可以计算，否则要根据设置加入分频系数*/
#define baud           9600                                //设置波特率的大小
#define baud_setting   (uint)((ulong)CPU_F/((ulong)baud))  //波特率计算公式
#define baud_h         (uchar)(baud_setting>>8)            //提取高位
#define baud_l         (uchar)(baud_setting)               //低位
/*
#define LED8PORT        P2OUT                   //P2接8个LED灯
#define LED8SEL         P2SEL                   //P2接8个LED灯
#define LED8DIR         P2DIR                   //P2接8个LED灯
*/
#define DATAPORT	P4OUT                   //数据口所在端口P4
#define DATASEL         P4SEL                   //数据口功能寄存器，控制功能模式
#define DATADIR         P4DIR                   //数据口方向寄存器

#define CTRPORT	        P6OUT                   //控制线所在的端口P6
#define CTRSEL          P6SEL                   //控制口功能寄存器，控制功能模式
#define CTRDIR          P6DIR                   //控制口方向寄存器

#define DCTR0	        P6OUT &= ~BIT4          //数码管段控制位信号置低
#define DCTR1           P6OUT |=  BIT4          //数码管段控制位信号置高
#define WCTR0	        P6OUT &= ~BIT3          //数码管位控制位信号置低
#define WCTR1           P6OUT |=  BIT3          //数码管位控制位信号置高

#define KEYPORT	        P1OUT                   //按键所在的端口P1
#define KEYSEL          P1SEL                   //控制口功能寄存器，控制功能模式
#define KEYDIR          P1DIR                   //控制口方向寄存器
#define KEYIN           P1IN                    //键盘扫描判断需要读取IO口状态值

#define DACCS0          P5OUT &= ~BIT4          //DAC片选信号置低
#define DACCS1          P5OUT |=  BIT4          //DAC片选信号置高
#define DIN0            P3OUT &= ~BIT1          //DAC DIN管脚位数据为0
#define DIN1            P3OUT |=  BIT1          //DAC DIN管脚位数据为1
#define DOUT0           P3OUT &= ~BIT2          //DAC DOUT管脚位数据为0
#define DOUT1           P3OUT |=  BIT2          //DAC DOUT管脚位数据为0
#define SCLK0           P3OUT &= ~BIT3          //DAC SCLK管脚位数据为0
#define SCLK1           P3OUT |=  BIT3          //DAC SCLK管脚位数据为0

#define SOUNDON         P6OUT &= ~BIT2          //蜂鸣器开声音
#define SOUNDOFF        P6OUT |=  BIT2          //蜂鸣器关声音

#define RS_CLR	        P6OUT &= ~BIT3           //RS置低    
#define RS_SET	        P6OUT |=  BIT3           //RS置高

#define RW_CLR	        P6OUT &= ~BIT4           //RW置低      
#define RW_SET	        P6OUT |=  BIT4          //RW置高

#define EN_CLR	        P6OUT &= ~BIT5           //E置低     
#define EN_SET	        P6OUT |=  BIT5           //E置高

 #define PSB_CLR	        P6OUT &= ~BIT6           //PSB置低，串口方式    原为p50
 #define PSB_SET	        P6OUT |=  BIT6           //PSB置高，并口方式

#define RST_CLR	        P5OUT &= ~BIT1            //RST置低    原为p51
#define RST_SET	        P5OUT |= BIT1             //RST置高

#define DataPort        P2OUT                     

/*12864应用指令*/
#define CLEAR_SCREEN	0x01		          //清屏指令：清屏且AC值为00H
#define AC_INIT		0x02		          //将AC设置为00H。且游标移到原点位置
#define CURSE_ADD	0x06		          //设定游标移到方向及图像整体移动方向（默认游标右移，图像整体不动）
#define FUN_MODE	0x30		          //工作模式：8位基本指令集
#define DISPLAY_ON	0x0c		          //显示开,显示游标，且游标位置反白
#define DISPLAY_OFF	0x08		          //显示关
#define CURSE_DIR	0x14		          //游标向右移动:AC=AC+1
#define SET_CG_AC	0x40		          //设置AC，范围为：00H~3FH
#define SET_DD_AC	0x80                      //设置DDRAM AC

///////////////红外遥控
#define RED_IN	        P1DIR &= ~BIT5	//设置输入，红外接收头接单片机PE3口
#define RED_OUT	        P1DIR |=  BIT5	//设置输出
#define RED_L	        P1OUT &= ~BIT5	//置低电平
#define RED_H	        P1OUT |= BIT5   //置高电平
#define RED_R	        (P1IN & BIT5)	//读电平



/*DS1302管脚定义*/
/*DS1302复位脚*/
#define RESET_CLR	P1OUT &= ~BIT7            //电平置低
#define RESET_SET	P1OUT |=  BIT7            //电平置高
#define RESET_IN	P1DIR &= ~BIT7            //方向输入
#define RESET_OUT	P1DIR |=  BIT7            //方向输出

/*DS1302双向数据*/
#define IO_CLR	        P1OUT &= ~BIT6            //电平置低
#define IO_SET	        P1OUT |=  BIT6            //电平置高
#define IO_R	        P1IN & BIT6               //电平读取
#define IO_IN	        P1DIR &= ~BIT6            //方向输入
#define IO_OUT	        P1DIR |=  BIT6            //方向输出

/*DS1302时钟信号*/
#define SCK_CLR	        P1OUT &= ~BIT5            //时钟信号
#define SCK_SET	        P1OUT |=  BIT5            //电平置高
#define SCK_IN	        P1DIR &= ~BIT5            //方向输入
#define SCK_OUT	        P1DIR |=  BIT5            //方向输出

/*DS1302命令与相关地址*/
#define DS1302_sec_add		0x80		  //秒数据地址
#define DS1302_min_add		0x82		  //分数据地址
#define DS1302_hr_add		0x84		  //时数据地址
#define DS1302_date_add		0x86		  //日数据地址
#define DS1302_month_add	0x88		  //月数据地址
#define DS1302_day_add		0x8a		  //星期数据地址
#define DS1302_year_add		0x8c		  //年数据地址
#define DS1302_control_add	0x8e		  //控制数据地址
#define DS1302_charger_add	0x90 					 
#define DS1302_clkburst_add	0xbe




 
//***********************************************************************
//			遥控器键码
//***********************************************************************

#define KEY_0     0x16                 //键0
#define KEY_1     0x0C                 //键1
#define KEY_2     0x18                 //键2
#define KEY_3     0x5E                 //键3
#define KEY_4     0x08                 //键4
#define KEY_5     0x1C                 //键5
#define KEY_6     0x5A                 //键6
#define KEY_7     0x42                 //键7
#define KEY_8     0x52                 //键8
#define KEY_9     0x4A                 //键9
#define KEY11     0x45                 //  CH-
#define KEY12     0x46                 //  CH
#define KEY13     0x47                 //  CH+
#define KEY14     0x44                 //  |<<
#define KEY15     0x40                 //  >>|
#define KEY16     0x43                 //  >||
#define KEY17     0x07                 //  -
#define KEY18     0x15                 //  +
#define KEY19     0xd9                 //  EQ
#define KEY20     0x19                 //  100+
#define KEY21     0x0d                 //  200+


#endif



//uchar   key=0xFF;                                 //键值变量

//***********************************************************************
//			共阴数码管显示的断码表
//***********************************************************************

 
//***********************************************************************
//                   系统时钟初始化
//***********************************************************************
      /*
void Clock_Init()
{
  uchar i;
  BCSCTL1&=~XT2OFF;                 //打开XT2振荡器
  BCSCTL2|=SELM1+SELS;              //MCLK为8MHZ，SMCLK为8MHZ
  do{
    IFG1&=~OFIFG;                   //清楚振荡器错误标志
    for(i=0;i<100;i++)
       _NOP();
  }
  while((IFG1&OFIFG)!=0);           //如果标志位1，则继续循环等待
  IFG1&=~OFIFG; 
}
*///**********************************************************************
//               MSP430内部看门狗初始化
//***********************************************************************
       /*
void WDT_Init()
{
   WDTCTL = WDTPW + WDTHOLD;       //关闭看门狗
}      */



         /*
void UTR0_Init()
  { //波特率 2400
    P3SEL |= 0x30;                            // P3.4,5选择为UART收发端口
    ME1 |= UTXE0 + URXE0;                     // 使能USART0收发  使能
    UCTL0 |= CHAR;                            // 8-bit character
    UTCTL0 |= SSEL0;                          // UCLK = ACLK
    UBR00 = 0x0D;                             // 32k/2400 - 13.65 USART 0 Baud Rate 0 
    UBR10 = 0x00;                             //
    UMCTL0 = 0x6B;                            // Modulation
    UCTL0 &= ~SWRST;                          // 初始化UART0状态机
    IE1 |= URXIE0;                            // 使能接收中断
    _EINT();
  }
        */

 