#include "closed_loop.h"

Pid iq_pi = {0};
Pid id_pi = {0};
Pid speed_pi = {0};
Pid position_pid = {0};

void IdIq_Pi_Control(float ex_id, float ex_iq)
{
    foc.Ia = motor.current[1];
    foc.Ib = motor.current[0];
    ClarkTransform(foc.Ia, foc.Ib);
    ParkTransform(foc.Ialpha, foc.Ibeta, motor.el_angle);

    foc.Ud = Pi_Control(id_pi, ex_id, foc.Id);
    foc.Uq = Pi_Control(iq_pi, ex_iq, foc.Iq);
}

float Position_Pid_Control(float ex_position)
{
    float position_out = 0;

    position_out = Pid_Control(position_pid, ex_position, motor.mech_angle);

    return position_out;
}

float Speed_PI_Control(float ex_speed)
{
    float speed_out = 0;

    speed_out = Pi_Control(speed_pi, ex_speed, motor.speed);

    return speed_out;
}

