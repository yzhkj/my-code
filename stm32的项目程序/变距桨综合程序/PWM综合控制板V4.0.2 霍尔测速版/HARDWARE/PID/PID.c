#include "delay.h"
#include "PID.h"
#include "stdio.h"
#include "NetData.h"
/////////////////////////////////////////////位置式pid
//void PID_init( _pid* pid)
//	{
//    printf("PID_init begin \r\n");
//    pid->SetRPM=0.0;
//   pid->ActualRPM=0.0;
//    pid->err=0.0;
//    pid->err_last=0.0;
//    pid->voltage=0.0;
//    pid->integral=0.0;
//    pid->Kp=0.4;
//    pid->Ki=0.3;
//    pid->Kd=0.1;
//    printf("PID_init end \r\n");
//}

//float PID_realize(_pid *pid, float RPM){
//    pid->SetRPM=RPM;
//    pid->err=pid->SetRPM-pid->ActualRPM;
//    pid->integral+=pid->err;
//    pid->voltage=pid->Kp*pid->err+pid->Ki*pid->integral+pid->Kd*(pid->err-pid->err_last);
//    pid->err_last=pid->err;
//    pid->ActualRPM=pid->voltage*1.0;
//		delay_ms(500);
//    return pid->ActualRPM;

//}

///////////////////////////////////////////增量式pid
void PID_init( _pid* pid)
	{
    printf("PID_init begin \r\n");
    pid->SetRPM=0.0;
    pid->ActualRPM=0.0;
    pid->err=0.0;
    pid->err_last=0.0;
    pid->err_next=0.0;
    pid->Kp=0.4;
    pid->Ki=0.3;
    pid->Kd=0.1;
    printf("PID_init end \r\n");
}
float PID_realize(_pid *pid, float RPM,float ARPM){
    pid->SetRPM=RPM;
    pid->err=pid->SetRPM-ARPM;
     float incrementRPM=pid->Kp*(pid->err-pid->err_next)+pid->Ki*pid->err+pid->Kd*(pid->err-2*pid->err_next+pid->err_last);
     //pid->ActualRPM+=incrementRPM;
	 //printf("pid->ActualRPM%f --\r\n",pid->ActualRPM);
    pid->err_last=pid->err_next;
    pid->err_next=pid->err;
    return  incrementRPM;
}
