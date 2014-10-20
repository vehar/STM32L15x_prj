#include "CustDs1820.h"



void TS_PinDown();
void TS_PinUp();

GPIO_InitTypeDef  GPIO_InitStructureDown;
GPIO_InitTypeDef  GPIO_InitStructureUp;

#ifndef u8
  #define u8 uint8_t
#endif

signed short temp = invalidTemp;

void CustTS1820Init()
{
  /*!< GPIOB clock enable */
  RCC_AHBPeriphClockCmd(tsPeriph, ENABLE);
//down struct
  GPIO_InitStructureDown.GPIO_Pin   = tsPin;
  GPIO_InitStructureDown.GPIO_Mode  = GPIO_Mode_OUT;
  GPIO_InitStructureDown.GPIO_Speed = GPIO_Speed_40MHz;
  GPIO_InitStructureDown.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructureDown.GPIO_PuPd  = GPIO_PuPd_NOPULL;
//up struct
  GPIO_InitStructureUp.GPIO_Pin   = tsPin;
  GPIO_InitStructureUp.GPIO_Mode  = GPIO_Mode_IN;
  GPIO_InitStructureUp.GPIO_Speed = GPIO_Speed_40MHz;
  GPIO_InitStructureUp.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructureUp.GPIO_PuPd  = GPIO_PuPd_UP;
  
  TS_PinUp();
}

uint8_t TS_GetPinStatus()
{ 
  return GPIO_ReadInputDataBit(tsGpioPort, tsPin);
}

void TS_PinDown()  
{  
  GPIO_InitTypeDef* GPIO_InitStruct = &GPIO_InitStructureDown;
  GPIO_TypeDef* GPIOx = tsGpioPort;
  GPIO_ResetBits(tsGpioPort,tsPin);
//  GPIO_Init(tsGpioPort, &GPIO_InitStructureDown);
// to increase speed, capturede from GPIO_Init;
  uint32_t pinpos = tsPinSource;
  GPIOx->MODER  &= ~(GPIO_MODER_MODER0 << (pinpos * 2));
  GPIOx->MODER |= (((uint32_t)GPIO_InitStruct->GPIO_Mode) << (pinpos * 2));

  GPIOx->OSPEEDR &= ~(GPIO_OSPEEDER_OSPEEDR0 << (pinpos * 2));
  GPIOx->OSPEEDR |= ((uint32_t)(GPIO_InitStruct->GPIO_Speed) << (pinpos * 2));

  GPIOx->OTYPER  &= ~((GPIO_OTYPER_OT_0) << ((uint16_t)pinpos)) ;
  GPIOx->OTYPER |= (uint16_t)(((uint16_t)GPIO_InitStruct->GPIO_OType) << ((uint16_t)pinpos));
  
  GPIOx->PUPDR &= ~(GPIO_PUPDR_PUPDR0 << ((uint16_t)pinpos * 2));
  GPIOx->PUPDR |= (((uint32_t)GPIO_InitStruct->GPIO_PuPd) << (pinpos * 2));
}

void TS_PinUp()
{
//  GPIO_Init(tsGpioPort, &GPIO_InitStructureUp);
  GPIO_InitTypeDef* GPIO_InitStruct = &GPIO_InitStructureUp;
  GPIO_TypeDef* GPIOx = tsGpioPort;
  uint32_t pinpos = tsPinSource;
  
//output up
  GPIO_SetBits(tsGpioPort,tsPin);
  GPIOx->MODER  &= ~(GPIO_MODER_MODER0 << (pinpos * 2));
  GPIOx->MODER |= (((uint32_t)GPIO_InitStruct->GPIO_Mode) << (pinpos * 2));

  GPIOx->OSPEEDR &= ~(GPIO_OSPEEDER_OSPEEDR0 << (pinpos * 2));
  GPIOx->OSPEEDR |= ((uint32_t)(GPIO_InitStruct->GPIO_Speed) << (pinpos * 2));

  GPIOx->OTYPER  &= ~((GPIO_OTYPER_OT_0) << ((uint16_t)pinpos)) ;
  GPIOx->OTYPER |= (uint16_t)(((uint16_t)GPIO_InitStruct->GPIO_OType) << ((uint16_t)pinpos));
  
  GPIOx->PUPDR &= ~(GPIO_PUPDR_PUPDR0 << ((uint16_t)pinpos * 2));
  GPIOx->PUPDR |= (((uint32_t)GPIO_InitStruct->GPIO_PuPd) << (pinpos * 2));
  
//input pull up  
  GPIOx->MODER  &= ~(GPIO_MODER_MODER0 << (pinpos * 2));
  GPIOx->MODER |= (((uint32_t)GPIO_InitStruct->GPIO_Mode) << (pinpos * 2));
  GPIOx->PUPDR &= ~(GPIO_PUPDR_PUPDR0 << ((uint16_t)pinpos * 2));
  GPIOx->PUPDR |= (((uint32_t)GPIO_InitStruct->GPIO_PuPd) << (pinpos * 2));
}

void TS_PinForceUp()
{
  GPIO_SetBits(tsGpioPort,tsPin);
  GPIO_Init(tsGpioPort, &GPIO_InitStructureDown);
}

uint8_t TS_StartImpuls()
{
  u8 Data = 0;
  TS_PinDown();
  delay_us(480);
  TS_PinUp();
  delay_us(60);
//  delay_us(50);
  Data = TS_GetPinStatus();
  return ((Data==0)? 1: 0);
}

void TS_WriteOne()
{
  TS_PinDown();
  delay_us(2);
  TS_PinUp();
  delay_us(40);
}

void TS_WriteZero()
{
  TS_PinDown();
  delay_us(40);
  TS_PinUp();
  delay_us(20);
}

u8 TS_Read()
{
  u8 Data;
  TS_PinDown();
//  delay_us(1);
  TS_PinUp();
//  delay_us(2);//5
  Data = TS_GetPinStatus();
  delay_us(36);//36
  return Data;
}

void TS_WriteByte(u8 Data)
{
  u8 i;
  for(i=0; i<8; i++)
      if(Data>>i & 1)
        TS_WriteOne();
      else
        TS_WriteZero(); 
  delay_us(10);  
}

u8 TS_ReadByte()
{
  u8 Data = 0;
  u8 i;
  for(i=0;i<8;i++)
    Data |=  (TS_Read()<<i);
  return Data;
}

u8 _crc_ibutton_update(u8 crc, u8 data)
{
  u8 i;
  crc = crc ^ data;
  for (i = 0; i < 8; i++)
  {
    if (crc & 0x01)
      crc = (crc >> 1) ^ 0x8C;
    else
      crc >>= 1;
  }
  return crc;
} 

unsigned char TS_CalcCrc(u8 code[],char BufSize)
{
  unsigned char i;
  u8 crc  = 0;
  for(i=0; i < BufSize; i++)
  {
     crc =  _crc_ibutton_update(crc, code[i]);
  }
  return crc;
} 

signed short BinToDegree(unsigned short BinData)
{
    signed short  Sum = 0;
    u8 neg = 0;
    short part;  
    int i;
    if((BinData>>8 & 0xff) == 0xff)
    {
            BinData = (BinData-1) ^ 0xffff;
            neg = 1;
    }
    for(i=0;i<8;i++)
    {
            if(BinData >> i & 0x01)
            {
                    part = 5*(1<<i);
                    Sum += part;
            }
    }
    if(neg) Sum*=-1;
    return Sum;
}

char CustDelayMs(unsigned short Ms)
{
  short Discretness= 10;//ms
  short NTimes = Ms/Discretness, i;
  if(NTimes==0) NTimes++;
  if(majorInterrupt) return 0;
  CustWDReset();
  for(i=0; i< NTimes; i++)
  {
    delay_ms(Discretness);
    CustWDReset();
    if(majorInterrupt) return 0;
  }
  return 1;
}


signed short TS_GetTemp()
{
  u8 DataBuf[10];//0- family,1-7 serial
  u8 CRCRec;
  u8 CRCCalc;
  signed char i;
  uint16_t timeCount = 0;  
  const uint16_t  timeOut= 200;
  
  TS_PinUp();
 // if(!CustDelayMs(100))
 // return invalidTemp;
  if(TS_StartImpuls())
  {
    timeCount = 0;
    while(!TS_GetPinStatus() && ((++timeCount) < timeOut));
    if(timeCount == timeOut) return invalidTemp;
    delay_us(30);

    TS_WriteByte(0x33);  //get rom data 
    
    for(i=0; i<7; i++)
      DataBuf[i] = TS_ReadByte();  
       
    CRCRec = TS_ReadByte();
    CRCCalc = TS_CalcCrc(DataBuf, 7);
    
    if(CRCCalc == CRCRec)
    {
      delay_us(30);
      TS_WriteByte(0x44); 
      TS_PinForceUp();
      if(!CustDelayMs(780))
           return invalidTemp;
      if(TS_StartImpuls())
      {
        timeCount = 0;
        while(!TS_GetPinStatus() && ((++timeCount) < timeOut));
        if(timeCount == timeOut) return invalidTemp;
        delay_us(30);
        TS_WriteByte(0xcc);   
        if(CRCCalc == CRCRec)
        {
          TS_WriteByte(0xbe); 
          for(i=0;i<8;i++)
            DataBuf[i] = TS_ReadByte();
          CRCRec = TS_ReadByte();
          CRCCalc = TS_CalcCrc(DataBuf,8);
          if(CRCCalc == CRCRec)
          { 
            return BinToDegree(DataBuf[1]<<8 | DataBuf[0]);
          }
        }
      }   
    } 
  }
  return invalidTemp;
}





