#pragma once

#include "stm32l1xx.h"

#define CustWDInitCounter 0x7f
#define CustWDWindCounter 0x7f
void CustWDInit();
void CustWDReset();