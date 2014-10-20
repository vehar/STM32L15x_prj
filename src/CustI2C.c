#include "CustI2C.h"


__IO uint8_t I2cSMbusAlertOccurred = 0;


//#define I2C_RxBusy    1
//#define I2C_TxBusy    2
//#define I2C_
//
//__IO uint8_t I2CFlags;

__IO bool    I2CRxBusy = 0;
__IO uint8_t I2cRxIdx = 0;
__IO uint8_t I2cRxCommEnd  = 0;
__IO uint8_t I2cRxCommSize = 0;
__IO uint8_t *I2cBufferRx = 0;
     uint8_t I2cBufferRxSize = 0;

__IO bool    I2CTxBusy = 0;
__IO uint8_t I2cTxIdx  = 0;
__IO uint8_t I2cTxCommEnd  = 0;
__IO uint8_t I2cTxCommSize = 0;
__IO uint8_t  *I2cBufferTx = 0;
     uint8_t  I2cBufferTxSize = 0;

__IO  uint8_t ControlVal=0;

void CustI2CInit()
{
  CustI2C_RccConfiguration();
  CustI2CGpioConfiguration();
  CustI2CNvicConfiguration();
  CustI2CPeriphConfiguration();
}


void CustI2CPeriphConfiguration(void)
{
  I2C_InitTypeDef  I2C_InitStructure;
  I2C_Cmd(I2C1, DISABLE);
   /* Initialize I2C peripheral */
  /*!< I2C1 Init */
  I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
  I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
  I2C_InitStructure.I2C_OwnAddress1 = SLAVE_ADDRESS;
  I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
  I2C_InitStructure.I2C_ClockSpeed = 100000;//normal mode
  I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
  I2C_Init(I2C1, &I2C_InitStructure);

  /* Enable Error Interrupt */
  I2C_ITConfig(I2C1, (I2C_IT_ERR | I2C_IT_EVT | I2C_IT_BUF), ENABLE);
  I2C_DualAddressCmd(I2C1,  DISABLE);
  I2C_StretchClockCmd(I2C1, DISABLE);
  /* I2C1 ENABLE */
  I2C_Cmd(I2C1, ENABLE);

}
void CustI2C_RccConfiguration(void)
{

  /*!< GPIOB clock enable */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

  /*!< I2C1 Periph clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
}

void CustI2CGpioConfiguration(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  /*!< Configure I2C1 SCL pin */
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;//GPIO_Mode_IN;//GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;//GPIO_PuPd_UP;//GPIO_PuPd_NOPULL;//
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  /*!< Configure I2C1 SDA pin */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  /* Connect PXx to I2C_SCL */
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_I2C1);
  /* Connect PXx to I2C_SDA */
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_I2C1);
}

void CustI2CNvicConfiguration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  /* Configure the I2C1 event priority */
  NVIC_InitStructure.NVIC_IRQChannel = I2C1_EV_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  /* Configure I2C1 error interrupt to have the higher priority */
//   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannel = I2C1_ER_IRQn;
  NVIC_Init(&NVIC_InitStructure);
}


/*******************************************************************************/
/*            STM32L1xx Peripherals Interrupt Handlers                        */
/******************************************************************************/
/**
  * @brief  This function handles I2C2 Error interrupt request.
  * @param  None
  * @retval None
  */
void I2C1_ER_IRQHandler(void)
{
//
//  /* Check on I2C1 SMBALERT flag and clear it */
//  if (I2C_GetITStatus(I2C1, I2C_IT_SMBALERT))
//  {
//    I2C_ClearITPendingBit(I2C1, I2C_IT_SMBALERT);
//    I2cSMbusAlertOccurred++;
//  }
//  /* Check on I2C1 Time out flag and clear it */
//  if (I2C_GetITStatus(I2C1, I2C_IT_TIMEOUT))
//  {
//    I2C_ClearITPendingBit(I2C1, I2C_IT_TIMEOUT);
//  }
//  /* Check on I2C1 Arbitration Lost flag and clear it */
//  if (I2C_GetITStatus(I2C1, I2C_IT_ARLO))
//  {
//    I2C_ClearITPendingBit(I2C1, I2C_IT_ARLO);
//  }
//
//  /* Check on I2C1 PEC error flag and clear it */
//  if (I2C_GetITStatus(I2C1, I2C_IT_PECERR))
//  {
//    I2C_ClearITPendingBit(I2C1, I2C_IT_PECERR);
//  }
//  /* Check on I2C1 Overrun/Underrun error flag and clear it */
//  if (I2C_GetITStatus(I2C1, I2C_IT_OVR))
//  {
//    I2C_ClearITPendingBit(I2C1, I2C_IT_OVR);
//  }
//  /* Check on I2C1 Acknowledge failure error flag and clear it */
//  if (I2C_GetITStatus(I2C1, I2C_IT_AF))
//  {
//    I2C_ClearITPendingBit(I2C1, I2C_IT_AF);
//
//    #ifdef USE_FULL_ASSERT
//     printf("I2C1 Acknowledge failure error\r\n");
//    #endif
//  }
//  /* Check on I2C1 Bus error flag and clear it */
//  if (I2C_GetITStatus(I2C1, I2C_IT_BERR))
//  {
//    I2C_ClearITPendingBit(I2C1, I2C_IT_BERR);
//  }
//
  if (I2C_GetITStatus(I2C1, I2C_IT_AF))
  {
    I2C_ClearITPendingBit(I2C1, I2C_IT_AF);
    I2cTxCommSize = I2cTxIdx;
    I2cTxCommEnd = 1;
    I2CTxBusy = 0;
  }
  else
    CustI2CPeriphConfiguration();

}

/**
* @brief  This function handles I2C2 Error interrupt request.
* @param  None
* @retval None
*/

__IO uint32_t Event = 0x00;
void I2C1_EV_IRQHandler(void)
{
  /* Get Last I2C Event */
  Event = I2C_GetLastEvent(I2C1);
  Event &= 0x7ffdf;
  switch (Event)
  {
//Slave Recieve Part
    /* check on EV1*/
    case I2C_EVENT_SLAVE_RECEIVER_ADDRESS_MATCHED:
      I2CRxBusy = 1;
      I2cRxIdx = 0;
      break;
    /* Check on EV2*/
    case I2C_EVENT_SLAVE_BYTE_RECEIVED:
      if(I2cBufferRx == 0)
      {
        ControlVal = I2C_ReceiveData(I2C1);
        majorInterrupt = true;
      }
      else
        if(I2cRxIdx==0)
        {
            ControlVal = I2C_ReceiveData(I2C1);
            I2cRxIdx++;           
        }else          
          if(I2cRxIdx-1 < I2cBufferRxSize)
          {
            I2cBufferRx[I2cRxIdx-1] = I2C_ReceiveData(I2C1);
            I2cRxIdx++;   
          }
          else
            I2C_ReceiveData(I2C1);
      break;
    /* Check on EV4 */
    case I2C_EVENT_SLAVE_STOP_DETECTED:
      I2cRxCommSize = I2cRxIdx;
      I2cRxCommEnd = 1;
      I2CRxBusy = 0;
      I2cRxIdx = 0;
      //to reset this flag need to read status and write something to cr1
      I2C_GetFlagStatus(I2C1, I2C_FLAG_STOPF);
      I2C1->CR1 |= I2C_CR1_ACK;
      break;
//Slave Transmit Part
    /* Check on EV1 */
    case I2C_EVENT_SLAVE_TRANSMITTER_ADDRESS_MATCHED:
          I2cTxIdx = 0;
          I2CTxBusy = 1;
          if(I2cBufferTx != 0)
          {
            I2C_SendData(I2C1, I2cBufferTx[I2cTxIdx]);
            I2cTxIdx++;
          }
          else
            I2C_SendData(I2C1, ControlVal);
//          I2C_SendData(I2C1, 0);
      break;
      /* Check on EV3 */
    case I2C_EVENT_SLAVE_BYTE_TRANSMITTING:
    case I2C_EVENT_SLAVE_BYTE_TRANSMITTED:
         if(I2cBufferTx != 0)
          {
            I2C_SendData(I2C1, I2cBufferTx[I2cTxIdx]);
            I2cTxIdx++;
            if(I2cTxIdx >= I2cBufferTxSize) I2cTxIdx = I2cBufferTxSize-1;
          }
          else
            I2C_SendData(I2C1, ControlVal);
      break;
      default:
#ifdef USE_FULL_ASSERT
        //I2C_SendData(I2C1, 35);
        printf("UEv: 0x%x\r\n", Event);
#endif
        CustI2CPeriphConfiguration();
//      break;
  }
}
