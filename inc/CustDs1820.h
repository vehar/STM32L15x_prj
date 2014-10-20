#pragma once
#include "stm32l1xx.h"
#include "CustDelay.h"
#include "main.h"

#define tsPin                  GPIO_Pin_1
#define tsGpioPort             GPIOB
#define tsPeriph               RCC_AHBPeriph_GPIOB
#define tsPinSource            GPIO_PinSource1;

#define invalidTemp 9999

//extern signed short temp;

void CustTS1820Init();
signed short TS_GetTemp();

