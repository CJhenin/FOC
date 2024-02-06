#include "current.h"


//IN5 - A , IN4 - B, IN6 - C
void current_collection(void)
{
    //static float voltage[3] = {0};
//    for(uint8_t i = 0; i < 3; i++)
//    {
//        HAL_ADC_Start(&hadc1);
//        HAL_ADC_PollForConversion(&hadc1, 10);
//        motor.voltage[i] = HAL_ADC_GetValue(&hadc1) / 4096.0 * 3.3;   //resolution 12bit Vref = 3.3V
//        motor.current[i] = (motor.voltage[i] - 1.65f) * 0.05f;
//    }
//    HAL_ADC_Stop(&hadc1);

    uint16_t ADC_values[3] = {0};
    HAL_ADC_Start_DMA(&hadc1, (uint32_t *)ADC_values, 3);
    for(uint8_t i = 0; i < 3; i++)
    {
        motor.voltage[i] = ADC_values[i] / 4096.0 * 3.3;   //resolution 12bit Vref = 3.3V
        motor.current[i] = (motor.voltage[i] - 1.65f) * 0.05f;  // 50,1mR
    }
}