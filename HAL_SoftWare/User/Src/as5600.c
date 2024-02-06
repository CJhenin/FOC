#include "as5600.h"

static uint8_t first_read = 0;
static float first_mech_angle = 0.0f;

void get_as5600angle(void)
{
    uint8_t buffer[2] = {0};
    uint8_t REG_AS5600 = 0X0C;  //the data register address
    uint16_t raw_angle = 0;
    //float mech_angle = 0;

    HAL_I2C_Master_Transmit(&hi2c1, (ADDR_AS5600 << 1) | 0X00,
                            &REG_AS5600, 1, 10);
    HAL_I2C_Master_Receive(&hi2c1, (ADDR_AS5600 << 1) | 0X01,
                           buffer, 2, 10);
    raw_angle = ((((uint16_t)buffer[0] << 8) | (uint16_t)buffer[1]) & 0X0FFF);  //12bit

    if(motor.first_read_flag == 0)
    {
        motor.mech_angle = (float)(raw_angle * 0.08789);   //360degree / 2^12bit
        motor.first_mech_angle = motor.mech_angle;
        motor.first_read_flag++;

        motor.pre_mech_angle = motor.first_mech_angle;
    }
    motor.mech_angle = (float)(raw_angle * 0.08789) - motor.first_mech_angle;
    motor.mech_angle = (motor.mech_angle >= 0 ? (motor.mech_angle) : (motor.mech_angle + 360));
    //return (mech_angle >= 0 ? (mech_angle) : (mech_angle + 360));
}
