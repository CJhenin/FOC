#include "pid.h"

float Pi_Control(Pid pid, float expect, float actual)
{
    pid.error = expect - actual;

    pid.pout = pid.kp * pid.error;
    pid.iout += pid.ki * pid.error;

    pid.out = pid.pout + pid.iout;

    return pid.out;
}

float Pid_Control(Pid pid, float expect, float actual)
{
    pid.error = expect - actual;

    pid.pout = pid.kp * pid.error;
    pid.iout += pid.ki * pid.error;
    pid.dout = pid.kd * (pid.error - pid.pre_error);

    pid.out = pid.pout + pid.iout +pid.dout;

    pid.pre_error = pid.error;

    return pid.out;
}
