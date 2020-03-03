#ifndef PID_H
#define PID_H
#include "sys.h"
//typedef  struct _pid{
//    float SetRPM;            
//    float ActualRPM;        
//    float err;               
//    float err_last;          
//    float Kp,Ki,Kd;           
//    float voltage;         
//    float integral;        
//}_pid;
 typedef  struct _pid{
    float SetRPM;           
    float ActualRPM;       
    float err;              
    float err_next;           
    float err_last;            
    float Kp,Ki,Kd;          
}_pid;
void PID_init(_pid*);

float PID_realize(_pid*,float RPM,float ARPM);

#endif

