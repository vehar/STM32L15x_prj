#include "CustGps.h"

uint8_t UsartRxBuffer[RXBUFFERSIZE];

DMA_InitTypeDef         DMA_InitStructure;
USART_InitTypeDef       USART_InitStructure;

void CustGpsInit()
{
  USART_InitTypeDef USART_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;

   /* Enable GPIO clock */
  RCC_AHBPeriphClockCmd(USARTx_TX_GPIO_CLK | USARTx_RX_GPIO_CLK, ENABLE);

  /* Enable USART clock */
  USARTx_APBPERIPHCLOCK(USARTx_CLK, ENABLE);

  /* Enable the DMA periph */
  RCC_AHBPeriphClockCmd(DMAx_CLK, ENABLE);

  /* Connect PXx to USARTx_Tx */
  GPIO_PinAFConfig(USARTx_TX_GPIO_PORT, USARTx_TX_SOURCE, USARTx_TX_AF);

  /* Connect PXx to USARTx_Rx */
  GPIO_PinAFConfig(USARTx_RX_GPIO_PORT, USARTx_RX_SOURCE, USARTx_RX_AF);

  /* Configure USART Tx and Rx as alternate function push-pull */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

  GPIO_InitStructure.GPIO_Pin = USARTx_TX_PIN;
  GPIO_Init(USARTx_TX_GPIO_PORT, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = USARTx_RX_PIN;
  GPIO_Init(USARTx_RX_GPIO_PORT, &GPIO_InitStructure);

  /* USARTx configuration ----------------------------------------------------*/
  /* USARTx configured as follow:
  - BaudRate = 230400 baud
  - Word Length = 8 Bits
  - one Stop Bit
  - No parity
  - Hardware flow control disabled (RTS and CTS signals)
  - Receive and transmit enabled
  */
  USART_InitStructure.USART_BaudRate = 9600;//230400;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  /* When using Parity the word length must be configured to 9 bits */
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx /*| USART_Mode_Tx*/;
  USART_Init(USARTx, &USART_InitStructure);

  /* DMA Configuration -------------------------------------------------------*/
  DMA_InitStructure.DMA_PeripheralBaseAddr = USARTx_DR_ADDRESS;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;

   /* Enable the USART Rx DMA request */
  USART_DMACmd(USARTx, USART_DMAReq_Rx, ENABLE);

}
void GpsStartReceiver()
{
  //USART_Cmd(USARTx, DISABLE);

  /* DMA Configuration -------------------------------------------------------*/
  DMA_DeInit(USARTx_RX_DMA_CHANNEL);
  DMA_InitStructure.DMA_BufferSize = (uint16_t)RXBUFFERSIZE;
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)UsartRxBuffer;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
  DMA_InitStructure.DMA_Priority = DMA_Priority_Low;
  DMA_Init(USARTx_RX_DMA_CHANNEL, &DMA_InitStructure);

  DMA_ClearFlag(USARTx_RX_DMA_FLAG_GL);
  DMA_ClearFlag(USARTx_RX_DMA_FLAG_TC);

  while(DMA_GetFlagStatus(USARTx_RX_DMA_FLAG_TC) == SET)
  {
     DMA_ClearFlag(USARTx_RX_DMA_FLAG_TC);
  }
  /* Enable the DMA channel */
  DMA_Cmd(USARTx_RX_DMA_CHANNEL, ENABLE);
//
   volatile uint32_t i;
   i = USARTx->SR;
   i = USARTx->CR3;
   i = USARTx->DR;

   USART_Cmd(USARTx, ENABLE);
}

uint8_t IsGpsDataReceived()
{
   uint8_t result = 0;
   if(DMA_GetFlagStatus(USARTx_RX_DMA_FLAG_TC) == SET /*USARTx_RX_DMA_CHANNEL->CNDTR == 0*/)
   {
     USART_Cmd(USARTx, DISABLE);
     DMA_Cmd(USARTx_RX_DMA_CHANNEL, DISABLE);
     result =  1;
   }

   if(DMA_GetFlagStatus(USARTx_RX_DMA_FLAG_TC) == SET /*USARTx_RX_DMA_CHANNEL->CNDTR == 0*/)
   {
     USART_Cmd(USARTx, DISABLE);
     DMA_Cmd(USARTx_RX_DMA_CHANNEL, DISABLE);
     result =  1;
   }

   return result;
}

bool ParseGpsData()
{
	bool result = false;
	uint16_t index = 0, coin = 0;//coincendence
        
	for(;index < RXBUFFERSIZE;index++)
	{
                if(index == RXBUFFERSIZE/2) CustWDReset();
                if(majorInterrupt) return 0;
		if((UsartRxBuffer[index]=='$')&&(coin==0)) {coin++; continue;}
		if((UsartRxBuffer[index]=='G')&&(coin==1)) {coin++; continue;}
		if((UsartRxBuffer[index]=='P')&&(coin==2)) {coin++; continue;}
		if((UsartRxBuffer[index]=='G')&&(coin==3)) {coin++; continue;}
		if((UsartRxBuffer[index]=='G')&&(coin==4)) {coin++; continue;}
		if((UsartRxBuffer[index]=='A')&&(coin==5)) {coin++; continue;}
		if((UsartRxBuffer[index]==',')&&(coin==6))
		{
                        SetGpsFlag(GPS_CONNECTED_FLAG);
			index++;
			if(index + 34 < RXBUFFERSIZE)
			{
				int j;
				for(j=0; j<10; j++)
					gpsData.time[j] = UsartRxBuffer[index++];
				gpsData.time[j] = 0;
				index++;
				for(j=0; j<11; j++)
					gpsData.latid[j] = UsartRxBuffer[index++];
				gpsData.latid[j] = 0;
				index++;
				for(j=0; j<12; j++)
					gpsData.longit[j] = UsartRxBuffer[index++];
				gpsData.longit[j] = 0;
 				result = true;
			}
			coin = 0;
			break;
		}
		coin = 0;
	}
	return result;
}