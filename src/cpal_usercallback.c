/**
  ******************************************************************************
  * @file    Project/STM32_CPAL_Template/cpal_usercallback.c
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    17-June-2011
  * @brief   This file provides all the CPAL UserCallback functions .
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
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "stm32l1xx.h"
#include "cpal.h"
#include "cpal_i2c.h"

/* Private typedef -----------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/



/*------------------------------------------------------------------------------
                     CPAL User Callbacks implementations 
------------------------------------------------------------------------------*/


/*=========== Timeout UserCallback ===========*/


/**
  * @brief  User callback that manages the Timeout error.
  * @param  pDevInitStruct .
  * @retval None.
  */
//uint32_t CPAL_TIMEOUT_UserCallback(CPAL_InitTypeDef* pDevInitStruct)
//{
//     /* Set default values for the state parameters */
//  pDevInitStruct->CPAL_State = CPAL_STATE_READY;
//  pDevInitStruct->wCPAL_DevError = CPAL_I2C_ERR_NONE ;        
//  pDevInitStruct->wCPAL_Timeout  = CPAL_I2C_TIMEOUT_DEFAULT;  
//  
//  /* Reset the CPAL device */
//  CPAL_I2C_DeInit(pDevInitStruct);  
//  
//  /* Initialize CPAL device with the selected parameters */
//  CPAL_I2C_Init(pDevInitStruct);    
//  
//  return CPAL_PASS;
//}


/*=========== Transfer UserCallback ===========*/


/**
  * @brief  Manages the End of Tx transfer event.
  * @param  pDevInitStruct 
  * @retval None
  */
//void CPAL_I2C_TXTC_UserCallback(CPAL_InitTypeDef* pDevInitStruct)
//{
// static int rxCount =0;
// rxCount++;
//}


/**
  * @brief  Manages the End of Rx transfer event.
  * @param  pDevInitStruct 
  * @retval None
  */ 
//void CPAL_I2C_RXTC_UserCallback(CPAL_InitTypeDef* pDevInitStruct)
//{
// static int txCount =0;
// txCount++;
//}


/**
  * @brief  Manages Tx transfer event.
  * @param  pDevInitStruct 
  * @retval None
  */
//void CPAL_I2C_TX_UserCallback(CPAL_InitTypeDef* pDevInitStruct)
//{
// static int rxCount =0;
// rxCount++;
//}


/**
  * @brief  Manages Rx transfer event.
  * @param  pDevInitStruct 
  * @retval None
  */ 
//void CPAL_I2C_RX_UserCallback(CPAL_InitTypeDef* pDevInitStruct)
//{
//  static int txCount =0;
//  txCount++;
//}


/**
  * @brief  Manages the End of DMA Tx transfer event.
  * @param  pDevInitStruct 
  * @retval None
  */
/*void CPAL_I2C_DMATXTC_UserCallback(CPAL_InitTypeDef* pDevInitStruct)
{
 
}*/


/**
  * @brief  Manages the Half of DMA Tx transfer event.
  * @param  pDevInitStruct 
  * @retval None
  */
/*void CPAL_I2C_DMATXHT_UserCallback(CPAL_InitTypeDef* pDevInitStruct)
{
   
}*/


/**
  * @brief  Manages Error of DMA Tx transfer event.
  * @param  pDevInitStruct 
  * @retval None
  */
/*void CPAL_I2C_DMATXTE_UserCallback(CPAL_InitTypeDef* pDevInitStruct)
{
   
}*/


/**
  * @brief  Manages the End of DMA Rx transfer event.
  * @param  pDevInitStruct 
  * @retval None
  */
//void CPAL_I2C_DMARXTC_UserCallback(CPAL_InitTypeDef* pDevInitStruct)
//{
// static int txCount =0;
// txCount++;
//}


/**
  * @brief  Manages the Half of DMA Rx transfer event.
  * @param  pDevInitStruct 
  * @retval None
  */ 
/*void CPAL_I2C_DMARXHT_UserCallback(CPAL_InitTypeDef* pDevInitStruct)
{
   
}*/


/**
  * @brief  Manages Error of DMA Rx transfer event.
  * @param  pDevInitStruct 
  * @retval None
  */ 
/*void CPAL_I2C_DMARXTE_UserCallback(CPAL_InitTypeDef* pDevInitStruct)
{
   
}*/


/*=========== Error UserCallback ===========*/


/**
  * @brief  User callback that manages the I2C device errors.
  * @note   Make sure that the define USE_SINGLE_ERROR_CALLBACK is uncommented in
  *         the cpal_conf.h file, otherwise this callback will not be functional.
  * @param  pDevInitStruct. 
  * @param  DeviceError.
  * @retval None
  */ 
//void CPAL_I2C_ERR_UserCallback(CPAL_DevTypeDef pDevInstance, uint32_t DeviceError)
//{
//  if (pDevInstance == CPAL_I2C1)
//  {
//    /* Set default values for the state parameters */
//    I2C1_DevStructure.CPAL_State = CPAL_STATE_READY;
//    I2C1_DevStructure.wCPAL_DevError = CPAL_I2C_ERR_NONE ;  
//  
//    /* Reset the CPAL device */
//    CPAL_I2C_DeInit(&I2C1_DevStructure);  
//  
//    /* Initialize CPAL device with the selected parameters */
//    CPAL_I2C_Init(&I2C1_DevStructure);    
//  }
//    
//  return;
//}

/**
  * @brief  User callback that manages BERR I2C device errors.
  * @note   Make sure that the define USE_MULTIPLE_ERROR_CALLBACK is uncommented in
  *         the cpal_conf.h file, otherwise this callback will not be functional.
  * @param  pDevInstance.
  * @retval None
  */  
/*void CPAL_I2C_BERR_UserCallback(CPAL_DevTypeDef pDevInstance)
{
   
}*/


/**
  * @brief  User callback that manages ARLO I2C device errors.
  * @note   Make sure that the define USE_MULTIPLE_ERROR_CALLBACK is uncommented in
  *         the cpal_conf.h file, otherwise this callback will not be functional.
  * @param  pDevInstance.
  * @retval None
  */
/*void CPAL_I2C_ARLO_UserCallback(CPAL_DevTypeDef pDevInstance)
{
   
}*/


/**
  * @brief  User callback that manages OVR I2C device errors.
  * @note   Make sure that the define USE_MULTIPLE_ERROR_CALLBACK is uncommented in
  *         the cpal_conf.h file, otherwise this callback will not be functional.
  * @param  pDevInstance.
  * @retval None
  */
/*void CPAL_I2C_OVR_UserCallback(CPAL_DevTypeDef pDevInstance)
{
   
}*/


/**
  * @brief  User callback that manages AF I2C device errors.
  * @note   Make sure that the define USE_MULTIPLE_ERROR_CALLBACK is uncommented in
  *         the cpal_conf.h file, otherwise this callback will not be functional.
  * @param  pDevInstance.
  * @retval None
  */ 
/*void CPAL_I2C_AF_UserCallback(CPAL_DevTypeDef pDevInstance)
{
   
}*/


/*=========== Addressing Mode UserCallback ===========*/


/**
  * @brief  User callback that manage General Call Addressing mode.
  * @param  pDevInitStruct 
  * @retval None
  */ 
/*void CPAL_I2C_GENCALL_UserCallback(CPAL_InitTypeDef* pDevInitStruct)
{
   
}*/


/**
  * @brief  User callback that manage Dual Address Addressing mode.
  * @param  pDevInitStruct 
  * @retval None
  */  
/*void CPAL_I2C_DUALF_UserCallback(CPAL_InitTypeDef* pDevInitStruct)
{
   
}*/
 

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
