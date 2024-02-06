#ifndef DWT_H
#define DWT_H

#include "main.h"

#define  DWT_CR                 *(__IO uint32_t *)0xE0001000    //DWT Control Register
#define  DWT_CYCCNT             *(__IO uint32_t *)0xE0001004    //DWT Current PC Sampler Cycle Count Register
#define  DEM_CR                 *(__IO uint32_t *)0xE000EDFC


#define  DEM_CR_TRCEN              (1 << 24)
#define  DWT_CR_CYCCNT_ENABLE      1
#define  DWT_CR_CYCCNT_DISABLE     0XFFFE

extern void DWT_Init(void);
extern void CYCCNT_ENABLE(void);
extern void CYCCNT_DISABLE(void);
extern uint32_t Read_DWT_CYCCNT(void);

#endif