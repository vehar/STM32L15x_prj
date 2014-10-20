#pragma once

#include "stm32l1xx.h"
#include "defines.h"
#include "main.h"

extern uint8_t UsartRxBuffer[];

extern uint32_t GpsFlags;

#define GPS_CONNECTED_FLAG     1
//flag is set by client
#define GPS_READY_FLAG         (1<<1)
//flag sets by host
#define GPS_GETREADY_FLAG      (1<<2)

#define SetGpsFlag(i) gpsData.flags |= i
#define ClearGpsFlag(i) gpsData.flags &= ~i
#define GetGpsFlag(i) (((gpsData.flags & i) != 0) ? 1:0)

void CustGpsInit();
void GpsStartReceiver();
uint8_t IsGpsDataReceived();
bool ParseGpsData();

#define RXBUFFERSIZE                     300

#define DMAx_CLK                         RCC_AHBPeriph_DMA1
#define USARTx_DR_ADDRESS                0x40013804

#define USARTx_RX_DMA_CHANNEL            DMA1_Channel5
#define USARTx_RX_DMA_FLAG_TC            DMA1_FLAG_TC5
#define USARTx_RX_DMA_FLAG_GL            DMA1_FLAG_GL5

//#define USARTx_TX_DMA_CHANNEL            DMA1_Channel4
//#define USARTx_TX_DMA_FLAG_TC            DMA1_FLAG_TC4
//#define USARTx_TX_DMA_FLAG_GL            DMA1_FLAG_GL4



/* USART Communication boards Interface */
#define USARTx                           USART1
#define USARTx_CLK                       RCC_APB2Periph_USART1
#define USARTx_APBPERIPHCLOCK            RCC_APB2PeriphClockCmd
//#define USARTx_IRQn                      USART1_IRQn
//#define USARTx_IRQHandler                USART1_IRQHandler

#define USARTx_TX_PIN                    GPIO_Pin_9
#define USARTx_TX_GPIO_PORT              GPIOA
#define USARTx_TX_GPIO_CLK               RCC_AHBPeriph_GPIOA
#define USARTx_TX_SOURCE                 GPIO_PinSource9
#define USARTx_TX_AF                     GPIO_AF_USART1

#define USARTx_RX_PIN                    GPIO_Pin_10
#define USARTx_RX_GPIO_PORT              GPIOA
#define USARTx_RX_GPIO_CLK               RCC_AHBPeriph_GPIOA
#define USARTx_RX_SOURCE                 GPIO_PinSource10
#define USARTx_RX_AF                     GPIO_AF_USART1



