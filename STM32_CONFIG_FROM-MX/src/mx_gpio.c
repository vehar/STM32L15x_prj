/**
  ******************************************************************************
  * File Name          : mx_gpio.c
  * Date               : 14/08/2013 15:29:54
  * Description        : This file provides code for the configuration
  *                      of all used GPIO pins.
  ******************************************************************************
  *
  * COPYRIGHT 2013 STMicroelectronics
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "mx_gpio.h"
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

void mx_pinout_config(void) {
	/* Private typedef ---------------------------------------------------------*/
	GPIO_InitTypeDef GPIO_InitStruct;


	/** ADC GPIO Configuration	
		 PA0-WKUP1	 ------> ADC_IN0
		 PA1	 ------> ADC_IN1
		 PA4	 ------> ADC_IN4
	*/


	/*Enable or disable the AHB peripheral clock */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

	/*Configure GPIO pin */
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_4;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStruct);


	/** I2C1 GPIO Configuration	
		 PB6	 ------> I2C1_SCL
		 PB7	 ------> I2C1_SDA
	*/


	/*Enable or disable the AHB peripheral clock */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);


	//!!! GPIO_Init is commented because some parameters are missing
	//GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
	//GPIO_InitStruct.GPIO_Mode = ;
	//GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	//GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	//GPIO_InitStruct.GPIO_Speed = GPIO_Speed_40MHz;
	//GPIO_Init(GPIOB, &GPIO_InitStruct);


	//!!! GPIO_Init is commented because some parameters are missing
	//GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
	//GPIO_InitStruct.GPIO_Mode = ;
	//GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	//GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	//GPIO_InitStruct.GPIO_Speed = GPIO_Speed_40MHz;
	//GPIO_Init(GPIOB, &GPIO_InitStruct);

	/*Configure GPIO pin alternate function */
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_I2C1);

	/*Configure GPIO pin alternate function */
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_I2C1);


	/** I2C2 GPIO Configuration	
		 PB10	 ------> I2C2_SCL
		 PB11	 ------> I2C2_SDA
	*/


	/*Enable or disable the AHB peripheral clock */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);


	//!!! GPIO_Init is commented because some parameters are missing
	//GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
	//GPIO_InitStruct.GPIO_Mode = ;
	//GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	//GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	//GPIO_InitStruct.GPIO_Speed = GPIO_Speed_40MHz;
	//GPIO_Init(GPIOB, &GPIO_InitStruct);


	//!!! GPIO_Init is commented because some parameters are missing
	//GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11;
	//GPIO_InitStruct.GPIO_Mode = ;
	//GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	//GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	//GPIO_InitStruct.GPIO_Speed = GPIO_Speed_40MHz;
	//GPIO_Init(GPIOB, &GPIO_InitStruct);

	/*Configure GPIO pin alternate function */
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_I2C2);

	/*Configure GPIO pin alternate function */
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_I2C2);


	/** SPI1 GPIO Configuration	
		 PA5	 ------> SPI1_SCK
		 PA6	 ------> SPI1_MISO
		 PA7	 ------> SPI1_MOSI
	*/


	/*Enable or disable the AHB peripheral clock */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);


	//!!! GPIO_Init is commented because some parameters are missing
	//GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
	//GPIO_InitStruct.GPIO_Mode = ;
	//GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	//GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	//GPIO_InitStruct.GPIO_Speed = GPIO_Speed_40MHz;
	//GPIO_Init(GPIOA, &GPIO_InitStruct);


	//!!! GPIO_Init is commented because some parameters are missing
	//GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
	//GPIO_InitStruct.GPIO_Mode = ;
	//GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	//GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	//GPIO_InitStruct.GPIO_Speed = GPIO_Speed_40MHz;
	//GPIO_Init(GPIOA, &GPIO_InitStruct);


	//!!! GPIO_Init is commented because some parameters are missing
	//GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
	//GPIO_InitStruct.GPIO_Mode = ;
	//GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	//GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	//GPIO_InitStruct.GPIO_Speed = GPIO_Speed_40MHz;
	//GPIO_Init(GPIOA, &GPIO_InitStruct);

	/*Configure GPIO pin alternate function */
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_SPI1);

	/*Configure GPIO pin alternate function */
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_SPI1);

	/*Configure GPIO pin alternate function */
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_SPI1);


	/** SPI2 GPIO Configuration	
		 PB13	 ------> SPI2_SCK
		 PB14	 ------> SPI2_MISO
		 PB15	 ------> SPI2_MOSI
	*/


	/*Enable or disable the AHB peripheral clock */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);


	//!!! GPIO_Init is commented because some parameters are missing
	//GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
	//GPIO_InitStruct.GPIO_Mode = ;
	//GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	//GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	//GPIO_InitStruct.GPIO_Speed = GPIO_Speed_40MHz;
	//GPIO_Init(GPIOB, &GPIO_InitStruct);


	//!!! GPIO_Init is commented because some parameters are missing
	//GPIO_InitStruct.GPIO_Pin = GPIO_Pin_14;
	//GPIO_InitStruct.GPIO_Mode = ;
	//GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	//GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	//GPIO_InitStruct.GPIO_Speed = GPIO_Speed_40MHz;
	//GPIO_Init(GPIOB, &GPIO_InitStruct);


	//!!! GPIO_Init is commented because some parameters are missing
	//GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15;
	//GPIO_InitStruct.GPIO_Mode = ;
	//GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	//GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	//GPIO_InitStruct.GPIO_Speed = GPIO_Speed_40MHz;
	//GPIO_Init(GPIOB, &GPIO_InitStruct);

	/*Configure GPIO pin alternate function */
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_SPI2);

	/*Configure GPIO pin alternate function */
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource14, GPIO_AF_SPI2);

	/*Configure GPIO pin alternate function */
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource15, GPIO_AF_SPI2);


	/** TIM2 GPIO Configuration	
		 PA15	 ------> TIM2_CH1_ETR
		 PB3	 ------> TIM2_CH2
	*/


	/*Enable or disable the AHB peripheral clock */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA|RCC_AHBPeriph_GPIOB, ENABLE);


	//!!! GPIO_Init is commented because some parameters are missing
	//GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15;
	//GPIO_InitStruct.GPIO_Mode = ;
	//GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	//GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	//GPIO_InitStruct.GPIO_Speed = GPIO_Speed_400KHz;
	//GPIO_Init(GPIOA, &GPIO_InitStruct);


	//!!! GPIO_Init is commented because some parameters are missing
	//GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
	//GPIO_InitStruct.GPIO_Mode = ;
	//GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	//GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	//GPIO_InitStruct.GPIO_Speed = GPIO_Speed_400KHz;
	//GPIO_Init(GPIOB, &GPIO_InitStruct);

	/*Configure GPIO pin alternate function */
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource15, GPIO_AF_TIM2);

	/*Configure GPIO pin alternate function */
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource3, GPIO_AF_TIM2);


	/** TIM3 GPIO Configuration	
		 PB4	 ------> TIM3_CH1
		 PB5	 ------> TIM3_CH2
	*/


	/*Enable or disable the AHB peripheral clock */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);


	//!!! GPIO_Init is commented because some parameters are missing
	//GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;
	//GPIO_InitStruct.GPIO_Mode = ;
	//GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	//GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	//GPIO_InitStruct.GPIO_Speed = GPIO_Speed_400KHz;
	//GPIO_Init(GPIOB, &GPIO_InitStruct);


	//!!! GPIO_Init is commented because some parameters are missing
	//GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
	//GPIO_InitStruct.GPIO_Mode = ;
	//GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	//GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	//GPIO_InitStruct.GPIO_Speed = GPIO_Speed_400KHz;
	//GPIO_Init(GPIOB, &GPIO_InitStruct);

	/*Configure GPIO pin alternate function */
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource4, GPIO_AF_TIM3);

	/*Configure GPIO pin alternate function */
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource5, GPIO_AF_TIM3);


	/** USART1 GPIO Configuration	
		 PA9	 ------> USART1_TX
		 PA10	 ------> USART1_RX
	*/


	/*Enable or disable the AHB peripheral clock */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);


	//!!! GPIO_Init is commented because some parameters are missing
	//GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
	//GPIO_InitStruct.GPIO_Mode = ;
	//GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	//GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	//GPIO_InitStruct.GPIO_Speed = GPIO_Speed_40MHz;
	//GPIO_Init(GPIOA, &GPIO_InitStruct);


	//!!! GPIO_Init is commented because some parameters are missing
	//GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
	//GPIO_InitStruct.GPIO_Mode = ;
	//GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	//GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	//GPIO_InitStruct.GPIO_Speed = GPIO_Speed_40MHz;
	//GPIO_Init(GPIOA, &GPIO_InitStruct);

	/*Configure GPIO pin alternate function */
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);

	/*Configure GPIO pin alternate function */
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);


	/** USART2 GPIO Configuration	
		 PA2	 ------> USART2_TX
		 PA3	 ------> USART2_RX
	*/


	/*Enable or disable the AHB peripheral clock */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);


	//!!! GPIO_Init is commented because some parameters are missing
	//GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
	//GPIO_InitStruct.GPIO_Mode = ;
	//GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	//GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	//GPIO_InitStruct.GPIO_Speed = GPIO_Speed_40MHz;
	//GPIO_Init(GPIOA, &GPIO_InitStruct);


	//!!! GPIO_Init is commented because some parameters are missing
	//GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
	//GPIO_InitStruct.GPIO_Mode = ;
	//GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	//GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	//GPIO_InitStruct.GPIO_Speed = GPIO_Speed_40MHz;
	//GPIO_Init(GPIOA, &GPIO_InitStruct);

	/*Configure GPIO pin alternate function */
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);

	/*Configure GPIO pin alternate function */
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);


	/** Configure pins as GPIO
		 PC0	 ------> GPIO_Input
		 PC1	 ------> GPIO_Input
		 PC2	 ------> GPIO_Input
		 PC3	 ------> GPIO_Input
		 PC4	 ------> GPIO_Input
		 PC5	 ------> GPIO_Input
		 PC6	 ------> GPIO_Input
		 PC7	 ------> GPIO_Input
		 PC8	 ------> GPIO_Input
		 PC9	 ------> GPIO_Input
	*/


	/*Enable or disable the AHB peripheral clock */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);

	/*Configure GPIO pin */
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOC, &GPIO_InitStruct);
}

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */
