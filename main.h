/*
 * File: main.c
 * Date: 15.08.2011
 * Denis Zheleznjakov http://ziblog.ru
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <stdint.h>

#include "macros.h"

#include "stm32l1xx.h"
#include "stm32l1xx_it.h"

#include "discover_board.h"
#include "core_cm3.h"

#include "mcu_gpio.h"

#define LED_GREEN	B, 7, HIGH, MODE_OUTPUT_PUSH_PULL, SPEED_400KHZ, AF_NO
#define LED_BLUE	B, 6, HIGH, MODE_OUTPUT_PUSH_PULL, SPEED_400KHZ, AF_NO

/****BUTTON SECTION_START*****************/
#define USER_BUTTON	A, 0, HIGH, MODE_INPUT_FLOATING, SPEED_400KHZ, AF_NO

#define IN_1	C, 0, HIGH, MODE_INPUT_PULL_UP, SPEED_2MHZ, AF_NO //IN
#define IN_2	C, 1, HIGH, MODE_INPUT_PULL_UP, SPEED_2MHZ, AF_NO //IN
#define IN_3	C, 2, HIGH, MODE_INPUT_PULL_UP, SPEED_2MHZ, AF_NO //IN
#define IN_4	C, 3, HIGH, MODE_INPUT_PULL_UP, SPEED_2MHZ, AF_NO //IN
#define IN_5	C, 4, HIGH, MODE_INPUT_PULL_UP, SPEED_2MHZ, AF_NO //IN
#define IN_6	C, 5, HIGH, MODE_INPUT_PULL_UP, SPEED_2MHZ, AF_NO //IN


#define OUT_1	C, 6, HIGH, MODE_OUTPUT_OPEN_DRAIN, SPEED_2MHZ, AF_NO //OUT
#define OUT_2	C, 7, HIGH, MODE_OUTPUT_OPEN_DRAIN, SPEED_2MHZ, AF_NO //OUT

/****BUTTON SECTION_END*****************/

#define USART1_RX	A, 10,HIGH, MODE_AF_PUSH_PULL, SPEED_2MHZ, AF7
#define USART1_TX	A, 9, HIGH, MODE_AF_PUSH_PULL, SPEED_2MHZ, AF7

#define PIN_I2C1_SCL		B, 6, HIGH, MODE_AF_OPEN_DRAIN_PULL_UP, SPEED_40MHZ, AF4
#define PIN_I2C1_SDA		B, 7, HIGH, MODE_AF_OPEN_DRAIN_PULL_UP, SPEED_40MHZ, AF4

#define ENCODER_CH1	B, 4, HIGH, MODE_AF_PUSH_PULL_PULL_UP, SPEED_40MHZ, AF2 // 
#define ENCODER_CH2	B, 5, HIGH, MODE_AF_PUSH_PULL_PULL_UP, SPEED_40MHZ, AF2 // 

#define ADC_CH_10       C, 0, HIGH, MODE_ANALOG, SPEED_40MHZ, AF_NO // 
 /* Configure PB.12 (ADC Channel18) as analog input -------------------------*/
#define ADC_CH_11       C, 1, HIGH, MODE_ANALOG, SPEED_40MHZ, AF_NO // 
 /* Configure PB.12 (ADC Channel20) as analog input -------------------------*/

#define ADC_CH_3       A, 2, HIGH, MODE_ANALOG, SPEED_40MHZ, AF_NO //   
#define ADC_CH_4       A, 3, HIGH, MODE_ANALOG, SPEED_40MHZ, AF_NO //   
  


#define PIN_MCO		A, 8, HIGH, MODE_AF_PUSH_PULL, SPEED_40MHZ, AF0


//button pins define
//----------------------------------------

//----------------------------------------
//

//button flags
uint8_t A_flag = 0;
uint8_t B_flag = 0;
uint8_t C_flag = 0;
uint8_t D_flag = 0;
uint8_t E_flag = 0;
uint8_t F_flag = 0;
uint8_t G_flag = 0;
uint8_t H_flag = 0;
uint8_t I_flag = 0;
uint8_t J_flag = 0;

char pressed_key;
uint16_t button_port  = 0;

uint8_t ENKODER_flag = 0;
uint8_t ADC_start_flag = 0;
uint8_t ADC_data_rdy_flag = 0;


uint8_t Encoder_prev_pos = 0;
uint8_t Encoder_curr_pos = 0;

#define USART_RX_BUFF_SIZE (50)
#define SPI1_BUFF_SIZE (50)
#define I2C_RX_BUFF_SIZE (50)

uint8_t t=1;

uint8_t usart_data=0;
uint8_t UsartRxBuffer[USART_RX_BUFF_SIZE];
uint8_t usart1_rx_bit=0;

uint8_t spi1_data=0;
uint8_t spi1_buf[SPI1_BUFF_SIZE];
uint8_t spi1_bit=0;

uint8_t i2c_data=0;
uint8_t i2c_rx_buf[I2C_RX_BUFF_SIZE];
uint8_t i2c_rx_bit=0;

//char tmp=0;
char rv3voltage=0;
char ADC_data=0;

//160521.109,0000.0000,N,00000.0000,E
typedef struct
{
        uint8_t flags;
	uint8_t time[11];	//+1 end string
	uint8_t latid[12];	//+1
	uint8_t longit[13];	//+1
}   gpsData_t;
#define gpsDataSize 37

//extern gpsData_t  gpsData;
gpsData_t  gpsData;
//extern verData_t  verData;
//extern infoData_t infoData;




#endif /* MAIN_H_ */
