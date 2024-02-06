#ifndef CLOSED_LOOP_H
#define CLOSED_LOOP_H

#include "pid.h"
#include "motor.h"
#include "foc.h"

extern void IdIq_Pi_Control(float ex_id, float ex_iq);
extern float Speed_PI_Control(float ex_speed);
extern float Position_Pid_Control(float ex_position);

#endif