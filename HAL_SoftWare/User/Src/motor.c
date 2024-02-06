#include "motor.h"

Motor motor = {0};

void Motor_Enable()
{
    HAL_GPIO_WritePin(ENABLE_GPIO_Port, ENABLE_Pin, GPIO_PIN_SET);
}

void Motor_Disable()
{
    HAL_GPIO_WritePin(ENABLE_GPIO_Port, ENABLE_Pin, GPIO_PIN_RESET);
}

void Elangle_cal(void)
{
    //electrical angle = mechanical angle * polepairs
    motor.el_angle = motor.mech_angle * motor.polepairs * 0.01745f; //convert to radian
//    motor.el_angle = motor.el_angle + 1.57f;   //PI/2
    if(motor.el_angle > 6.28f)
    {
        motor.el_angle = fmod(motor.el_angle, 6.28);
    }
}

void Motor_Angle_calibration(void)
{
    Motor_Enable();

    RevParkTransform(8, 0, 0); //make magnet align with a-axis,Uq=0,Ud=10
    PWM_START();
    Svpwm();

    HAL_Delay(50);

    get_as5600angle();
    Elangle_cal();
}

void Motor_Init(void)
{
    motor.polepairs = 7;
    Motor_Angle_calibration();
}

