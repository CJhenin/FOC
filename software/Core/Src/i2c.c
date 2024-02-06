/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    i2c.c
  * @brief   This file provides code for the configuration
  *          of the I2C instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "i2c.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* I2C1 init function */
void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  LL_I2C_InitTypeDef I2C_InitStruct = {0};

  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOB);
  /**I2C1 GPIO Configuration
  PB6   ------> I2C1_SCL
  PB7   ------> I2C1_SDA
  */
  GPIO_InitStruct.Pin = LL_GPIO_PIN_6|LL_GPIO_PIN_7;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
  LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* Peripheral clock enable */
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C1);

  /* USER CODE BEGIN I2C1_Init 1 */

  //LL_I2C_Disable(I2C1);

  /* USER CODE END I2C1_Init 1 */

  /** I2C Initialization
  */
  LL_I2C_DisableOwnAddress2(I2C1);
  LL_I2C_DisableGeneralCall(I2C1);
  LL_I2C_EnableClockStretching(I2C1);
  I2C_InitStruct.PeripheralMode = LL_I2C_MODE_I2C;
  I2C_InitStruct.ClockSpeed = 100000;
  I2C_InitStruct.DutyCycle = LL_I2C_DUTYCYCLE_2;
  I2C_InitStruct.OwnAddress1 = 0;
  I2C_InitStruct.TypeAcknowledge = LL_I2C_ACK;
  I2C_InitStruct.OwnAddrSize = LL_I2C_OWNADDRESS1_7BIT;
  LL_I2C_Init(I2C1, &I2C_InitStruct);
  LL_I2C_SetOwnAddress2(I2C1, 0);
  /* USER CODE BEGIN I2C1_Init 2 */
  LL_I2C_Enable(I2C1);
  /* USER CODE END I2C1_Init 2 */

}

/* USER CODE BEGIN 1 */
uint8_t I2C_Read(uint8_t Addr, uint8_t Reg)
{
    uint8_t value = 0;

    LL_I2C_Enable(I2C1);
    //LL_mDelay(1);
    LL_I2C_GenerateStartCondition(I2C1);    //generate start signal
    while(!LL_I2C_IsActiveFlag_SB(I2C1))    //generate event5, SR1->SB == 1
    {

    }

    LL_I2C_TransmitData8(I2C1, (Addr << 1));   //send as5600 address and write instruction
    LL_mDelay(5);
    while(!LL_I2C_IsActiveFlag_ADDR(I2C1))  //if slave respond,generate event6, SR1->ADDR == 1
    {

    }
    LL_I2C_ClearFlag_ADDR(I2C1);    //clear ADDR

    LL_I2C_TransmitData8(I2C1, Reg);    //send address of as5600 angle data
    while(!LL_I2C_IsActiveFlag_TXE(I2C1))
    {

    }

    LL_I2C_GenerateStartCondition(I2C1);    //generate start signal again
    while(!LL_I2C_IsActiveFlag_SB(I2C1))
    {

    }

    LL_I2C_TransmitData8(I2C1, (Addr << 1) | 0X01); //send as5600 address and read instruction
    LL_mDelay(5);
    while(!LL_I2C_IsActiveFlag_ADDR(I2C1))
    {

    }
    LL_I2C_ClearFlag_ADDR(I2C1);

    while(!LL_I2C_IsActiveFlag_RXNE(I2C1))  //if master received data, generate event7, SR1->RXNE == 1
    {

    }
    value = LL_I2C_ReceiveData8(I2C1);

    LL_I2C_AcknowledgeNextData(I2C1, LL_I2C_NACK);  //non-acknowledge signal
    LL_I2C_GenerateStopCondition(I2C1); //stop transmission

    return value;
}
/* USER CODE END 1 */
