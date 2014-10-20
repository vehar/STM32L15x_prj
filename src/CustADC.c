#include "CustADC.h"

//infoData.m5		
//infoData.m100	
//infoData.p100	
//infoData.p12	
//infoData.p5		



void CustADCInit()
{  
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_DMA1, ENABLE);    
   /* Enable ADC */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

  CustADCGpioInit();

  /* DMA1 channel1 configuration ---------------------------------------------*/
  DMA_InitTypeDef DMA_InitStructure;
  DMA_DeInit(DMA1_Channel1);
  DMA_InitStructure.DMA_PeripheralBaseAddr  = ADC1_DR_ADDRESS;
  DMA_InitStructure.DMA_MemoryBaseAddr      = (uint32_t)&infoData;
  DMA_InitStructure.DMA_DIR                 = DMA_DIR_PeripheralSRC;
  DMA_InitStructure.DMA_BufferSize          = 5;//(infoDataSize/2-1);//-temp, convert to u16
  DMA_InitStructure.DMA_PeripheralInc       = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc           = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize  = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStructure.DMA_MemoryDataSize      = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode                = DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority            = DMA_Priority_High;
  DMA_InitStructure.DMA_M2M                 = DMA_M2M_Disable;
  DMA_Init(DMA1_Channel1, &DMA_InitStructure);
   
  /* Enable DMA1 channel1 */
  DMA_Cmd(DMA1_Channel1, ENABLE);
  
 /* ADC Common Init **********************************************************/
 /* ADC1 DeInit */
  /*ADC_DeInit(ADC1);
  ADC_CommonInitTypeDef ADC_CommonInitStructure;  
  ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4;
  ADC_CommonInit(&ADC_CommonInitStructure);
  */
  /* ADC Configuration -------------------------------------------------------*/
  ADC_InitTypeDef ADC_InitStructure;
  ADC_StructInit(&ADC_InitStructure);

  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfConversion = 5;
  ADC_Init(ADC1, &ADC_InitStructure);

  /* ADC1 regular channel20 configuration */
  ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_96Cycles);
  ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_96Cycles);
  ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 3, ADC_SampleTime_96Cycles);
  ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 4, ADC_SampleTime_96Cycles);
  ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 5, ADC_SampleTime_96Cycles);
  
  /* Enable the request after last transfer for DMA Circular mode */
  ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);
  
//  //+ Enables the ADC1 Power Down during Delay
//  ADC_PowerDownCmd(ADC1, ADC_PowerDown_Idle_Delay, ENABLE);
//  //+ Delay until the converted data has been read
//  ADC_DelaySelectionConfig(ADC1, ADC_DelayLength_255Cycles);

  /* Enable ADC1 DMA */
  ADC_DMACmd(ADC1, ENABLE);
  
  /* Enable ADC1 */
  ADC_Cmd(ADC1, ENABLE);
  
  /* Wait until ADC1 ON status */
  while (ADC_GetFlagStatus(ADC1, ADC_FLAG_ADONS) == RESET)
  {
  }

  /* Start ADC1 Software Conversion */
  ADC_SoftwareStartConv(ADC1);

  /* Wait until ADC Channel 20 end of conversion */
  /*while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET)
  {
  }
  */
}

void CustADCGpioInit()
{
  GPIO_InitTypeDef GPIO_InitStructure;
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; //adc_in0 m_12v
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure); 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; //adc_in1 m_+5v
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //adc_in2 m_-5v
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3; //adc_in3 m_+100
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4; //adc_in4 m_-100
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}