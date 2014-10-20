#pragma once

#include "stm32l1xx.h"
#include "defines.h"

#define ADC1_DR_ADDRESS    ((uint32_t)0x40012458)

void CustADCInit();
void CustADCGpioInit();
