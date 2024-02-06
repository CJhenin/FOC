#include "pid.h"

//add limit th amplitude of output and integrate

float Pi_Control(Pid pid, float expect, float actual)
{
    pid.error = expect - actual;

    pid.pout = pid.kp * pid.error;

    pid.iout += pid.ki * pid.error;
    pid.iout = (pid.iout >= LIMIT_IOUT) ? (LIMIT_IOUT) : (pid.iout);

    pid.out = pid.pout + pid.iout;
    pid.out = (pid.out >= LIMIT_OUTPUT) ? (LIMIT_OUTPUT) : (pid.out);

    return pid.out;
}

float Pid_Control(Pid pid, float expect, float actual)
{
    pid.error = expect - actual;

    pid.pout = pid.kp * pid.error;

    pid.iout += pid.ki * pid.error;
    pid.iout = (pid.iout >= LIMIT_IOUT) ? (LIMIT_IOUT) : (pid.iout);

    pid.dout = pid.kd * (pid.error - pid.pre_error);

    pid.out = pid.pout + pid.iout +pid.dout;
    pid.out = (pid.out >= LIMIT_OUTPUT) ? (LIMIT_OUTPUT) : (pid.out);

    pid.pre_error = pid.error;

    return pid.out;
}
