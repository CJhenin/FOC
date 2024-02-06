#include "as5600.h"

 uint8_t a = 0;

void Read_AS5600(void)
{
    a = I2C_Read(ADDR_AS5600, REG_AS5600);
}

