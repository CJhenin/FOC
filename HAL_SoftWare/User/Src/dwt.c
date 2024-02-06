#include "dwt.h"

void DWT_Init(void)
{
    DEM_CR |= (uint32_t)DEM_CR_TRCEN; //set the 25th TRCENA to 1

    DWT_CYCCNT = (uint32_t)(0u);    //clean the CYCCNT register's value

//    DWT_CR |= (uint32_t)DWT_CR_CYCCNT_ENABLE;   //enable CYCCNT
}

void CYCCNT_ENABLE(void)
{
    DWT_CR |= (uint32_t)DWT_CR_CYCCNT_ENABLE;   //enable CYCCNT
}

void CYCCNT_DISABLE(void)
{
    DWT_CR &= (uint32_t)DWT_CR_CYCCNT_DISABLE;   //disable CYCCNT
}

uint32_t Read_DWT_CYCCNT(void)
{
    return ((uint32_t)DWT_CYCCNT);
}