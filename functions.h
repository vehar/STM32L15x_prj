#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <stdint.h>

#include "macros.h"

#include "stm32l1xx.h"
#include "stm32l1xx_it.h"
#include "core_cm3.h"

#include "mcu_gpio.h"



uint16_t temp, send_data = 0x01;
#define ADC_RATIO                   ((uint16_t) 806) /*ADC_RATIO = ( 3.3 * 1000 * 1000)/4095 */

void Info();
void GPS_get_data(void);
bool ParseGpsData();

void Current_monitor_get_data(void);
void delay (int a);
void HSI_on_16MHz (void);

void i2c1_init();
void i2c1_rx (int adress);
void i2c1_rx2 (void);
void i2c1_tx (int adress, int data);

void Timer2_init_vs_irq(void);
void Timer3_init_encoder_mode(void);

void Button_init_vs_irq (void);

void Matrix_kbd_init (void);
char Get_key(void);

void Usart_init_vs_irq (void);
void send_to_usart(uint8_t data);
void send_str_u(char * string);
void Spi2_init_vs_irq(void);
void recieve_from_spi(void);
void spi_exchange(uint8_t send_data);

void ADC_measure(char ch);
void DM_spi_test(void);

//void lcd_init();






char Get_key(void);



#endif /* FUNCTIONS_H_ */
