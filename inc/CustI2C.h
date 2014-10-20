#pragma once

#include "stm32l1xx.h"
#include <stdio.h>
#include "main.h"

#define SLAVE_ADDRESS 0x30

void CustI2CInit(); //runs rcc, gpio, nvic configuration

void CustI2C_RccConfiguration(void);
void CustI2CGpioConfiguration(void);
void CustI2CNvicConfiguration(void);
void CustI2CPeriphConfiguration(void);

void I2C1_ER_IRQHandler(void);
void I2C1_EV_IRQHandler(void);

#define I2cBufSize 10

extern __IO bool    I2CRxBusy;
extern __IO uint8_t I2cRxCommEnd;
extern __IO uint8_t I2cRxCommSize;
extern __IO uint8_t *I2cBufferRx;
extern      uint8_t I2cBufferRxSize;

extern __IO bool    I2CTxBusy;
extern __IO uint8_t I2cTxCommEnd;
extern __IO uint8_t I2cTxCommSize;
extern __IO uint8_t  *I2cBufferTx;
extern      uint8_t  I2cBufferTxSize;

extern __IO  uint8_t ControlVal;