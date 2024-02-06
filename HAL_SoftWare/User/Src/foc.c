#include "foc.h"

Foc foc = {0};
static uint8_t Ts = 1;  //1kHz 1ms

void ClarkTransform(float ia, float ib)
{
//    foc.Ialpha = foc.Ia - 0.5f * foc.Ib - 0.5f * foc.Ic;
//    foc.Ibeta = 0.866f * foc.Ib - 0.866f * foc.Ic;    //sqrt(3)/2 = 0.866

//    foc.Ialpha = foc.Ia;
//    foc.Ibeta = foc.Ia * 0.57735f + foc.Ib * 1.1547f; //sqrt(3)/3,2sqrt(3)/3

    foc.Ialpha = ia;
    foc.Ibeta = ia * 0.57735f + ib * 1.1547f; //sqrt(3)/3,2sqrt(3)/3
}

void ParkTransform(float ialpha, float ibeta, float elangle)
{
//    foc.Id = foc.Ialpha * cos(motor.el_angle) + foc.Ibeta * sin(motor.el_angle);
//    foc.Iq = foc.Ialpha * (-sin(motor.el_angle)) + foc.Ibeta * cos(motor.el_angle);

    foc.Id = ialpha * cos(elangle) + ibeta * sin(elangle);
    foc.Iq = ialpha * (-sin(elangle)) + ibeta * cos(elangle);
}

void RevParkTransform(float ud, float uq, float elangle)
{
    foc.Ualpha = ud * cos(elangle) + uq * (-sin(elangle));
    foc.Ubeta = ud * sin(elangle) + uq * cos(elangle);
}

void Svpwm(void)
{
    float T[8] = {0};
    float k = 0;
    //u1 u2 u3 anti-clockwise
    float u1 = foc.Ubeta;
    float u2 = -0.866f * foc.Ualpha - 0.5f * foc.Ubeta;   //sqrt(3)/2 = 0.866
    float u3 = 0.866f * foc.Ualpha - 0.5f * foc.Ubeta;

    uint8_t nsector = ((u1 > 0) << 2) + ((u2 > 0) << 1) + (u3 > 0);

    if(nsector == 5)
    {
        foc.sector = 1;
        T[4] = u3;  //100
        T[6] = u1;  //110
        if((u1 + u3) > Ts)
        {
            k = Ts / (u1 + u3);
            T[4] = k * u3;
            T[6] = k * u1;
        }
        T[0] = (Ts - T[4]- T[6]) / 2;   //000
        T[7] = T[0];    //111
        foc.Ta = T[4] + T[6] + T[7];
        foc.Tb = T[6] + T[7];
        foc.Tc = T[7];
    }

    if(nsector == 4)
    {
        foc.sector = 2;
        T[2] = -u3;  //010
        T[6] = -u2;  //110
        if((-u2 - u3) > Ts)
        {
            k = Ts / (-u2 - u3);
            T[2] = k * (-u3);
            T[6] = k * (-u2);
        }
        T[0] = (Ts - T[2] - T[6]) / 2;
        T[7] = T[0];
        foc.Ta = T[6] + T[7];
        foc.Tb = T[2] + T[6] + T[7];
        foc.Tc = T[7];
    }

    if(nsector == 6)
    {
        foc.sector = 3;
        T[2] = u1;  //010
        T[3] = u2;  //011
        if((u1 + u2) > Ts)
        {
            k = Ts / (u1 + u2);
            T[2] = k * u1;
            T[3] = k * u2;
        }
        T[0] = (Ts - T[2] - T[3]) / 2;
        T[7] = T[0];
        foc.Ta = T[7];
        foc.Tb = T[2] + T[3] + T[7];
        foc.Tc = T[3] + T[7];
    }

    if(nsector == 2)
    {
        foc.sector = 4;
        T[1] = -u1;  //001
        T[3] = -u3;  //011
        if((-u1 - u3) > Ts)
        {
            k = Ts / (-u1 - u3);
            T[1] = k * (-u1);
            T[3] = k * (-u3);
        }
        T[0] = (Ts - T[1] - T[3]) / 2;
        T[7] = T[0];
        foc.Ta = T[7];
        foc.Tb = T[3] + T[7];
        foc.Tc = T[1] + T[3] + T[7];
    }

    if(nsector == 3)
    {
        foc.sector = 5;
        T[1] = u2;  //001
        T[5] = u3;  //101
        if((u2 + u3) > Ts)
        {
            k = Ts / (u2 + u3);
            T[1] = k * u2;
            T[5] = k * u3;
        }
        T[0] = (Ts - T[1] - T[5]) / 2;
        T[7] = T[0];
        foc.Ta = T[5] + T[7];
        foc.Tb = T[7];
        foc.Tc = T[1] + T[5] + T[7];
    }

    if(nsector == 1)
    {
        foc.sector = 6;
        T[4] = -u2;  //100
        T[5] = -u1;  //101
        if((-u1 - u2) > Ts)
        {
            k = Ts / (-u1 - u2);
            T[4] = k * (-u2);
            T[5] = k * (-u1);
        }
        T[0] = (Ts - T[4] - T[5]) / 2;
        T[7] = T[0];
        foc.Ta = T[4] + T[5] + T[7];
        foc.Tb = T[7];
        foc.Tc = T[5] + T[7];
    }

    foc.compare_Ta = (uint16_t)(499.0f - (foc.Ta * 1000) / 2);
    foc.compare_Tb = (uint16_t)(499.0f - (foc.Tb * 1000) / 2);
    foc.compare_Tc = (uint16_t)(499.0f - (foc.Tc * 1000) / 2);

    PWM_SET(foc.compare_Ta, foc.compare_Tb, foc.compare_Tc);
}


