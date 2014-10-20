/**
  ******************************************************************************
  * @file    main.c
  * @author  Microcontroller Division
  * @version V1.1.2
  * @date    September 2011
  * @brief   Main program body
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  */

/* Includes ------------------------------------------------------------------*/

/* Standard STM32L1xxx driver headers */

#include "main.h"
#include "CustCR95HF_SPI.h"
//#include "misc.h"

void StandardAnalyser(uint8_t ControlVal);
void GetVersions();
void GetGpsData();
void RFidAnalyser(u8 ControlVal);
/* Private variables ---------------------------------------------------------*/
bool majorInterrupt = false;
/*******************************************************************************/

tagData_t tagData;
/*******************************************************************************/
/**
  * @brief main entry point.
  * @par Parameters None
  * @retval void None
  * @par Required preconditions: None
  */

int main(void)
{
  uint8_t ControlValTemp=0;
  uint8_t cmd=0;
  signed short tempTemp;
  /* Configure Clocks for Application need */
  RCC_Configuration();
  Init_GPIOs();
  
//RCC_MCOConfig(RCC_MCOSource_SYSCLK, RCC_MCODiv_1);
  
  NVIC_Configuration();
  CustDelayInit();
  CustI2CInit();
  //CustWDInit();
  CustGenRecInit();
  CustADCInit();
  CustTS1820Init();
  CustGpsInit();
 
  CustCR95HF_SPI_Init();

  verData.hardwVer      = HardwareVersion & 0x0f;   // Hardware Version
  verData.SoftwVer      = SoftVersion & 0xff;      // Software Version
  CustWDReset();
  infoData.temp         = TS_GetTemp();
  gpsData.flags         = 0;
  
  I2cBufferTx       = (uint8_t *) &infoData;
  I2cBufferTxSize   = infoDataSize;

  I2cBufferRx     = 0;
  I2cBufferRxSize = 0;
  tagData.flags = 0;
  
  /********************************************************************************/
  /********************************************************************************/
  /********************************************************************************/
  while(1)
  {
    CustWDReset();
    if(majorInterrupt) majorInterrupt = false;
    if ((ControlVal != ControlValTemp) && I2cRxCommEnd)
    {
        I2cRxCommEnd = false;
        ControlValTemp = ControlVal;
        cmd = ControlValTemp>>4 & 3;
        switch (cmd)
        {
            case 0://info
                StandardAnalyser(ControlValTemp);
                break;
            case 1://get version
                  GetVersions();
                break;
            case 2://rfid
//                if((ControlVal & (1<<7)) != 0)
//                {
//                  ControlVal &= (uint8_t)~(1<<7);
//                }
                RFidAnalyser(ControlValTemp);
                break;
            case 3://gps
                 GetGpsData();
                break;
        }
    }

    if(GetGpsFlag(GPS_GETREADY_FLAG))
    {
      GpsStartReceiver();
      ClearGpsFlag(GPS_GETREADY_FLAG);
      ClearGpsFlag(GPS_READY_FLAG);
    }
    else
      if(IsGpsDataReceived() && !GetGpsFlag(GPS_READY_FLAG))
      {
        if(ParseGpsData())
        {
          SetGpsFlag(GPS_READY_FLAG);
        }
        else
          GpsStartReceiver();
      }    
//temperature
    if(!majorInterrupt)
    {
      tempTemp =  TS_GetTemp();
      if((!((I2cBufferTx == (uint8_t *)&infoData) && I2CTxBusy))&& tempTemp != invalidTemp)
       infoData.temp = tempTemp;
    }
//RFid   
//    u8   RfidReadData(RfidData *GetData);
//    u8   RfidWriteData(RfidData *SetData,u8 ManufCodeWriting);
    if(!majorInterrupt)
    {
      if(tagData.flags & CheckTagPresentFlag)
      {
        if(RfidIsTagPresent()/*RfidIsCommunicationOk()*/)
        {
          if(tagData.flags & ReadDataFlag)
          {
            if(RfidReadData(&tagData.data)==RESULTOK)
              tagData.flags &= ~ReadDataFlag;
          }
          else
          {
             if(tagData.flags & WriteDataFlag)
             {
               if(RfidWriteData(&tagData.data, ((tagData.flags & WriteManufFlag)!=0))==RESULTOK)
                 tagData.flags &= ~WriteDataFlag;
             }
          }
          tagData.flags |= TagPresentFlag;          
        }
        else
          tagData.flags &= ~TagPresentFlag;
        tagData.flags &= ~CheckTagPresentFlag;
      }
    }
  }
}

/**
  * @brief  Configures the different system clocks.
  * @param  None
  * @retval None
  */
void RCC_Configuration(void)
{
  /* Enable HSI Clock */
  RCC_HSICmd(ENABLE);

  /*!< Wait till HSI is ready */
  while (RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET);

  /* Set HSI as sys clock*/
  RCC_SYSCLKConfig(RCC_SYSCLKSource_HSI);

  /* Set MSI clock range to ~4.194MHz*/
  RCC_MSIRangeConfig(RCC_MSIRange_6);

  /* Enable the GPIOs clocks */
  //RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB | RCC_AHBPeriph_GPIOC| RCC_AHBPeriph_GPIOD| RCC_AHBPeriph_GPIOE| RCC_AHBPeriph_GPIOH, ENABLE);

  /* Enable comparator, LCD and PWR mngt clocks */
  // RCC_APB1Periph_TIM2 delay us x 10
  RCC_APB1PeriphClockCmd(/*RCC_APB1Periph_COMP |*/ /*RCC_APB1Periph_LCD |*/ RCC_APB1Periph_PWR , ENABLE);

  /* Enable ADC & SYSCFG clocks */
  RCC_APB2PeriphClockCmd(/*RCC_APB2Periph_ADC1 |*/ RCC_APB2Periph_SYSCFG , ENABLE);


  /* Allow access to the RTC */
 // PWR_RTCAccessCmd(ENABLE);

//  /* Reset RTC Backup Domain */
 // RCC_RTCResetCmd(ENABLE);
 // RCC_RTCResetCmd(DISABLE);
//
//  /* LSE Enable */
//  RCC_LSEConfig(RCC_LSE_ON);
//
//  /* Wait until LSE is ready */
//  while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET);
//
//   /* RTC Clock Source Selection */
//  RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
//
//  /* Enable the RTC */
//  RCC_RTCCLKCmd(ENABLE);

  /*Disable HSE*/
  RCC_HSEConfig(RCC_HSE_OFF);
  if(RCC_GetFlagStatus(RCC_FLAG_HSERDY) != RESET )
  {
    /* Stay in infinite loop if HSE is not disabled*/
    while(1);
  }
}

/**
  * @brief  To initialize the I/O ports
  * @caller main
  * @param None
  * @retval None
  */

void  Init_GPIOs (void)
{

}

/**
  * @brief  Configures the different I2C1 interrupt.
  * @param  None
  * @retval None
  */
void NVIC_Configuration(void)
{

}



#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* Infinite loop */
  static int x=0;
  x++;
   printf("Wrong parameters value: file %s on line %d\r\n", file, line);
  while (1);
}
#else
  void assert_failed(uint8_t* file, uint32_t line) {}
#endif

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/



//  SysTick_Config((SystemCoreClock / 1000));
//  NVIC_SetPriority (SysTick_IRQn, 0);
//
//  GPIO_SetBits(GPIOA, GPIO_Pin_9);
//  Delay(10);
//  GPIO_ResetBits(GPIOA, GPIO_Pin_9);
//  int i;
//  uint8_t needReset = 0;


uint8_t lastCmd=0;
#define InvalidTemp 9999
int counter = 0;
unsigned char old_rx_i2c = 2;
void StandardAnalyser(uint8_t CVal)
{
   // int i=0;
    volatile signed short Temp;
    //I2cRxCommEnd = 0;
    if (lastCmd != 0)
    {
        I2cBufferTx       = (uint8_t *) &infoData;
        I2cBufferTxSize   = infoDataSize;

        I2cBufferRx     = 0;
        I2cBufferRxSize = 0;
        lastCmd         = 0;
    }
//    else
    {
        if ((CVal>>7 & 1) == 0)
        {
            //I2cRxCommEnd = FALSE;
            Set_HV (CVal);
            if ((CVal >> 6 & 1) != old_rx_i2c)  //switch relay impendans
            {
                if (old_rx_i2c == 0)//(ControlVal >> 6 & 1)
                {
                    //printf("Clr\n");
                    RelayClr(1);
                    delay_ms(20);
                    RelayClr(0);
                    old_rx_i2c = 1;
                }
                else
                {
                    //printf("Set\n");
                    RelaySet(1);
                    delay_ms(20);
                    RelaySet(0);
                    old_rx_i2c = 0;
                }
                old_rx_i2c = CVal >> 6 & 1;
            }
        }
    }
        //StopDelay = 0;
    //}
//    else
//    {
//        Temp = 25;//TS_GetTemp();
//        if (Temp != InvalidTemp)
//        {
//            infoData.temp = Temp;
//        }
//    }
}


void GetVersions()
{
    if (lastCmd != 1)
    {
        I2cBufferTx = (uint8_t *) &verData;
        I2cBufferTxSize = verDataSize;
        I2cBufferRx = 0;
        I2cBufferRxSize = 0;
        lastCmd = 1;
    }
}

void GetGpsData()
{
    if (lastCmd != 3)
    {
      I2cBufferTx = (uint8_t *) &gpsData;
      I2cBufferTxSize = gpsDataSize;
      
      I2cBufferRx = (uint8_t *) &gpsData;
      I2cBufferRxSize = 1;
      lastCmd = 3;
    }
}


void RFidAnalyser(u8 ControlVal)
{
    if (lastCmd != 2)
    {
      I2cBufferTx     = (u8 *) &tagData;
      I2cBufferTxSize = tagDataSize;
      I2cBufferRx     = (u8 *) &tagData;
      I2cBufferRxSize = tagDataSize;
      lastCmd = 2;
    }
}
