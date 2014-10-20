#pragma once

#include "stm32l1xx.h"

#define HV_Periph    RCC_AHBPeriph_GPIOA
#define RelPeriph    RCC_AHBPeriph_GPIOC

#define HV_GPIO_PORT 		GPIOA

#define HVL0_GPIO_PIN 	        GPIO_Pin_5
#define HVL1_GPIO_PIN 	        GPIO_Pin_6
#define HVL2_GPIO_PIN 	        GPIO_Pin_7
extern const uint16_t hvl_gpio_pins[];

#define REL_GPIO_PORT 		GPIOC
#define RELP_GPIO_PIN 	        GPIO_Pin_14
#define RELM_GPIO_PIN 	        GPIO_Pin_15

extern uint8_t HardwareVersion;
void CustGenRecInit();
void Set_HV (uint8_t hv);
void RelaySet(uint8_t val);
void RelayClr(uint8_t val);