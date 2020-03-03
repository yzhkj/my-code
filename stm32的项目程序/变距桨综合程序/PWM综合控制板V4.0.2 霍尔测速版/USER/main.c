#include "stm32f4xx.h"
#include "usart.h"
#include "delay.h"
#include "led.h"
#include "get_pwm.h"
#include "UserData.h"
#include "NetData.h"
#include "s2j.h"
#include "PID.h"
#include "tim_capture.h"
#include <math.h>
void PWM1Out(u16 pwmval);
void PWM3Out(u16 pwmval);
////////////////////////////////////////////////////////
//ANG数据 PWM2
extern u8 PWM2CH1_CAPTURE_STA;  //输入捕获状态
extern u32 PWM2CH1_CAPTURE_VAL; //输入捕获值
extern u32 PWM2CH1_CAPTURE_VAL_CYC;
///////////////////////////////////////////
extern u8 PWM5CH1_CAPTURE_STA;  //输入捕获状态
extern u32 PWM5CH1_CAPTURE_VAL; //输入捕获值
extern u32 PWM5CH1_CAPTURE_VAL_CYC;
/////////////////////////////////////////
extern u8  TIM4CH3_CAPTURE_STA;		//输入捕获状态		    				
extern u32	TIM4CH3_CAPTURE_VAL;	//输入捕获值  
/////////////////////////////////////////  


void struct_to_Json(SendData SD);
_pid pid;
int main(void)
{
	long long speed_tmp;
	float temp_float;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置系统中断优先级分组2
    delay_init(168);//初始化延时函数
    KTPSANG_init();
    ANG_Int((u16)-1,84-1);
    Net_Init();
    Pow_init();
    ECU_init();
	TIM4_CH3_Cap_Init(0XFFFF,84-1); //以1Mhz的频率计数 
    PID_init(&pid);
    SendData sd= {
        .KPow=0,
        .KAng=1050,
        .KTps=1050,
        .KRpm=2000,
        .Tps=0,
        .Ang=0,
        .Pow=0
    };
    int index=0;
    int U3=0;
    int U6=0;
    int P2=0;
    int P5=0;
    int ControlEnabled=0;
    while (1)
    {
        if(USART1_RX_STA&0x8000) {

            u8 con=USART1_RX_BUF[2];//数据
            if(con==0xff) {
                ControlEnabled=1;
            } else {
                u16 temp=USART1_RX_BUF[3];
                temp<<=8;
                temp+=USART1_RX_BUF[4];
                ControlEnabled=0;
                if(con==0x00) { //急停指令
                    sd.KTps=1050;
                    sd.KAng=1050;
                } else if(con==0xf1) { //控制油门+
                    sd.KTps+=temp;
                } else if(con==0xf0) { //控制油门-
                    if( sd.KTps>=temp)
                        sd.KTps-=temp;
                    else
                        sd.KTps=0;

                } else if(con==0x1f) { //控制角度+
                    sd.KAng+=temp;
                } else if(con==0x0f) { //控制角度-
                    if( sd.KAng>=temp)
                        sd.KAng-=temp;
                    else
                        sd.KAng=0;
                } else if(con==0xEA) { //恒定转速值
                    sd.KRpm=temp;
                }
            }
            USART1_RX_STA=0;//开启下一次接收
        }
        if(USART3_RX_STA&0x8000) {
            sd.Rpm=(USART3_RX_BUF[9]*256+USART3_RX_BUF[10])/4.0;
            sd.Tps=(USART3_RX_BUF[13]*256+USART3_RX_BUF[14])/655.36;
            USART3_RX_STA=0;
            U3++;
        }
        if(USART6_RX_STA&0x8000) {
            double data;
            u32 temp=USART6_RX_BUF[5];
            u32 temp1=USART6_RX_BUF[6];
            u32 temp2=USART6_RX_BUF[7];
            u32 temp3=USART6_RX_BUF[8];
            temp<<=24;
            temp1<<=16;
            temp2<<=8;
            temp+=temp1;
            temp+=temp2;
            temp+=temp3;
            data=(int)temp;
            for(u8 i=USART6_RX_BUF[9]; i>0x00; i--) {
                data/=10;
            }
            sd.Pow=data;
            USART6_RX_STA=0;
            U6++;
        }
        if (PWM2CH1_CAPTURE_STA & 0X80) //成功捕获到了一次高电平  判断最高位是不是为1
        {
            int val;
            u32 temp = PWM2CH1_CAPTURE_VAL;	   //得到总的高电平时间
            PWM2CH1_CAPTURE_STA = 0;		   //开启下一次捕获
            val = (int)temp;
            sd.Ang=(val*3600/4100/2);
            P2++;
        }
        if (PWM5CH1_CAPTURE_STA & 0X80) //成功捕获到了一次高电平  判断最高位是不是为1
        {
            int val;
            u32 temp = PWM5CH1_CAPTURE_VAL;	   //得到总的高电平时间
            PWM5CH1_CAPTURE_STA = 0;		   //开启下一次捕获
            val = (int)temp;
            sd.KPow=(val*3600/4100/2);
            P5++;
        }
        if(index%100000==0)	{
            int er=0;
            if(U3>0)
                er+=1;
            if(U6>0)er+=10;
            if(P2>0)er+=100;
            if(P5>0)er+=1000;
            sd.Error=er;
            struct_to_Json(sd);
            U6=P2=P5=0;
        }
				if(index%1000000==0){
					U3=0;
					index=1;
				}
        index++;
        if(ControlEnabled==1) {
            float inc=PID_realize(&pid,sd.KRpm,sd.Rpm);//pid调控，有位置和增量两种选择
            sd.KTps+=inc/100000;
        }
        //printf("%f --\r\n",inc);
        // printf("sd.KTps%f --\r\n",sd.KTps);
        PWM1Out(15015-(u16)sd.KTps);//控制油门
        PWM3Out(15015-(u16)sd.KAng);//控制角度
				
		//霍尔开关器件测速
		if(TIM4CH3_CAPTURE_STA&0X80)        //成功捕获到了一次高电平
		{
//			speed_tmp=TIM4CH3_CAPTURE_STA&0X3F; 
//			speed_tmp*=0XFFFF;		 		         //溢出时间总和
//			speed_tmp+=TIM4CH3_CAPTURE_VAL;		   //得到总的高电平时间
			speed_tmp=TIM4CH3_CAPTURE_VAL;	
			TIM4CH3_CAPTURE_STA=0;			     //开启下一次捕获
			printf("HIGH:%lld us\r\n",speed_tmp); //打印总的高点平时间
			
			temp_float=(float)(speed_tmp/1000.0);
			temp_float=(60000/temp_float);
			speed_tmp=filter((uint32_t)temp_float);
			printf("转速:%.f n/pm\r\n",temp_float);
			printf("滤波转速:%d n/pm\r\n",speed_tmp);
		}				
	}
}

void struct_to_Json(SendData SD) {
    printf("-----Start{\"KPow\":%f,\"KTps\":%f,\"KAng\":%f,\"Pow\":%f,\"Ang\":%.f,\"Tps\":%.3f,\"Rpm\":%f,\"Error\":%d}ENDD----------\r\n	",SD.KPow,SD.KTps,SD.KAng,SD.Pow,SD.Ang,SD.Tps,SD.Rpm,SD.Error);
}
////串口2发送程序
//void SendDatatoUSART2(u16 pow,u16 tps,u16 ang ) {
//    u32 p=(int)pow;
//    u32 t=(int)tps;
//    u32 a=(int)ang;
//    char w1[]="ASSSSAStartP";
//    char w2[]="ENDDDDDDDDDD\r\n";
//    char w3[]="T";
//    char w31[]="A";
//    char data[30];//=w1+p+w3+t+w31+a+w2;  //ASSSSAStartP1026T1120a1002A1001ENDDDDDDDD
//    sprintf(data,"%s%d%s%d%s%d%s",w1,p,w3,t,w31,a,w2);
//    for(u8 i=0; i<sizeof(data); i++) {
//        USART_SendData(USART2,data[i]);
//        while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//等待发送结束
//    }
//}
////串口3发送程序
//void SendDatatoUSART3(u16 pow,u16 tps,u16 ang,u16 _ang ) {
//    u32 p=(int)pow;
//    u32 t=(int)tps;
//    u32 a=(int)ang;
//    u32 A=(int)_ang;
//    char w1[]="ASSSSAStartP";
//    char w2[]="ENDDDDDD\r\n";
//    char w3[]="T";
//    char w31[]="a";
//    char w32[]="A";
//    u32 temp1=0, result = 0 ;
//    temp1 =A;
//    while( temp1 % 10 == 0 && temp1 != 0 )
//        temp1 /= 10 ;
//    do {
//        result = result * 10 + temp1 % 10 ;
//        temp1 /= 10 ;
//    } while( temp1 != 0 ) ;
//    char data[50];//=w1+p+w3+t+w31+a+w2;  //ASSSSAStartP1026T1120A1002ENDDDDDDDD
//    sprintf(data,"%s%d%s%d%s%d%s%d%s%d%s",w1,p,w3,t,w31,a,w32,A,w32,result,w2);
//    for(u8 i=0; i<sizeof(data); i++) {
//        USART_SendData(USART3,data[i]);
//        while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);//等待发送结束
//    }
//}
//Pwm1发送
void PWM1Out(u16 pwmval) {
    TIM_SetCompare1(TIM3,pwmval);
}
////Pwm2发送
//void PWM2Out(u16 pwmval) {
//    TIM_SetCompare1(TIM1,pwmval);
//}

//Pwm3发送
void PWM3Out(u16 pwmval) {
    TIM_SetCompare1(TIM2,pwmval);
}
////Pwm4发送
//void PWM4Out(u16 pwmval) {
//    TIM_SetCompare1(TIM2,pwmval);
//}
////Pwm5发送
//void PWM5Out(u16 pwmval) {
//    TIM_SetCompare1(TIM5,pwmval);
//}


