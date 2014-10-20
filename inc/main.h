/**
  ******************************************************************************
  * @file    Project/STM32L1xx_StdPeriph_Template/main.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    13-September-2011
  * @brief   Header for main.c module
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2010 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H



/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx.h"
#include "stdio.h"
#include "stdint.h"                      /*!< standard types definitions                      */

#include "discover_board.h"
#include "stm32l_discovery_lcd.h"
#include "discover_functions.h"

//#include "stm32l1xx_i2c.h"
//#include "cpal_i2c.h"
#include "defines.h"
#include "CustADC.h"
#include "CustI2C.h"
#include "CustWD.h"
#include "CustDelay.h"
#include "CustGenRec.h"
#include "CustGps.h"
#include "CustDs1820.h"
#include "CustCR95HF_SPI.h"

extern bool majorInterrupt;
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

void NVIC_Configuration(void);
void TimingDelay_Decrement(void);
void delay_ms(uint32_t nTime);

#endif /* __MAIN_H */

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
