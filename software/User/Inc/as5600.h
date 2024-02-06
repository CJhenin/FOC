#ifndef __AS5600_H
#define __AS5600_H

#include "i2c.h"

#define ADDR_AS5600 0X36
#define REG_AS5600 0X0E

extern uint8_t a;

extern void Read_AS5600(void);

#endif
