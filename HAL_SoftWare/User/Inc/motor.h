#ifndef MOTOR_H
#define MOTOR_H

#include "gpio.h"
#include "tim.h"
#include "as5600.h"
#include "foc.h"

#define SPEED_T 1;  //the measurement cycle

typedef struct
{
    float mech_angle;
    float mech_radian;

    float el_angle;

    float first_mech_angle;
    float first_read_flag;

    float pre_mech_angle;

    float speed;

    float voltage[3];
    float current[3];

    uint8_t polepairs;
}Motor;

extern Motor motor;

extern void Motor_Init(void);
extern void Motor_Enable(void);
extern void Motor_Disable(void);
extern void Motor_Angle_calibration(void);
extern void Elangle_cal(void);
extern void Speed_cal(void);

#endif
