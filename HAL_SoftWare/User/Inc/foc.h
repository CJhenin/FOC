#ifndef FOC_H
#define FOC_H

#include "math.h"
#include "main.h"
#include "tim.h"

#include "as5600.h"

#define zero_electric_angle 0
#define abs(x) x >= 0 ? x : (-x)

typedef struct
{
    uint8_t sector;
    float Ta;
    float Tb;
    float Tc;
    uint16_t compare_Ta;
    uint16_t compare_Tb;
    uint16_t compare_Tc;

    float Ia;
    float Ib;
    float Ic;
    float Ua;
    float Ub;
    float Uc;

    float Ialpha;
    float Ibeta;
    float Ualpha;
    float Ubeta;

    float Id;
    float Iq;
    float Ud;
    float Uq;   //>0-clockwise,<0-anticlockwise
}Foc;

extern Foc foc;

extern void ClarkTransform(float ia, float ib);
extern void ParkTransform(float ialpha, float ibeta, float elangle);
extern void RevParkTransform(float ud, float uq, float elangle);
extern void Svpwm(void);

#endif
