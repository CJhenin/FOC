#ifndef PID_H
#define PID_H

typedef struct
{
    float kp;
    float ki;
    float kd;

//    float expect;
//    float actual;

    float pre_error;
    float error;

    float pout;
    float iout;
    float dout;
    float out;
}Pid;

extern float Pi_Control(Pid pid, float expect, float actual);
extern float Pid_Control(Pid pid, float expect, float actual);

#endif
