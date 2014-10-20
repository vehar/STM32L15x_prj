#include "CustGenRec.h"

const uint16_t hvl_gpio_pins[] = {HVL0_GPIO_PIN, HVL1_GPIO_PIN, HVL2_GPIO_PIN};

uint8_t HardwareVersion = 0;
void CustGenRecInit()
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_AHBPeriphClockCmd( HV_Periph | RelPeriph, ENABLE);    
  /* HV pins configure  */  
  GPIO_InitStructure.GPIO_Pin = hvl_gpio_pins[0] | hvl_gpio_pins[1] | hvl_gpio_pins[2];
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
  GPIO_Init(HV_GPIO_PORT, &GPIO_InitStructure);
  /* Relay pins configure  */
  GPIO_InitStructure.GPIO_Pin = RELP_GPIO_PIN | RELM_GPIO_PIN;
  GPIO_Init(REL_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  
  
  HardwareVersion = (uint8_t)(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_5) |\
                              GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6)<<1 |\
                              GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7)<<2);
}


void GPIO_ResetCustBits(GPIO_TypeDef * GpioPort, uint32_t GpioPin)
{

  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin = GpioPin;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
  GPIO_Init(GpioPort, &GPIO_InitStructure);
  GPIO_ResetBits(GpioPort, GpioPin);    
}

void GPIO_SetCustBits(GPIO_TypeDef * GpioPort, uint32_t GpioPin)
{

  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin = GpioPin;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
  GPIO_Init(GpioPort, &GPIO_InitStructure);
  
}


void Set_HV (uint8_t hv)
{
 for(int i=0; i<3; i++) 
   if(hv >> i & 1)
     GPIO_ResetCustBits(HV_GPIO_PORT, hvl_gpio_pins[i]);     
   else
     GPIO_SetCustBits(HV_GPIO_PORT, hvl_gpio_pins[i]);
}


void RelaySet(uint8_t val)//set
{
  if(val)
    GPIO_SetBits(REL_GPIO_PORT, RELP_GPIO_PIN);
  else
    GPIO_ResetBits(REL_GPIO_PORT, RELP_GPIO_PIN);
}

void RelayClr(uint8_t val)//cls
{
  if(val)
    GPIO_SetBits(REL_GPIO_PORT, RELM_GPIO_PIN);
  else
    GPIO_ResetBits(REL_GPIO_PORT, RELM_GPIO_PIN);
}

