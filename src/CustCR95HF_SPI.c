#include "CustCR95HF_SPI.h"




u8 ModifyARC_bReg();
u8 UpdateARC_bReg(const u8 *UpdateARC_bRegTx);
u8 SetARC_bReg(const u8 *SetARC_bRegTx, const u8 *ReadARC_bRegTx);

//void RfidHardInit(void);
//void SPI_SendByte(char cData);
//char SPI_SendReceiveByte(char data);
//void SetCS(char state);

uint8_t SPI_SendReceiveByte(uint8_t data);
//void SPI_SendByte(uint8_t data); 

void SetIRQ_IN();
void CsPulse(void);
void RfidReady();
//void RfidReset();
void SetRfidReader();

u8 CR95HF_SPITxRx(const u8 *SendData, u8 *RecData, const int SendDataLen, const int RecDataLen, u8 interrupt);

u8 RfidGetSystemInfo(void);
u8 RfidGetCryptKey(u8 *Key);


//char CR95HF_ResetIfNeed();
u8  ISO15693ProtocolSelect(void);
//u8 RfidReadSingleBlock(u8 *ReadSingleBlockTx);
//u8 RfidWriteSingleBlock(u8 *WriteSingleBlockTx);
u8   RfidReadSingleBlock();
u8   RfidWriteSingleBlock();

u8   RfidReadMultipleBlocks(u8 Address, u8 *Data);
u8   RfidWriteMultipleBlocks(u8 Address, u8 *Data,u8);
void RdRegRxToZero();

u8  RfidIsTagPresent(void);


void SetCS(char state);
//void SPI_SendByte(char cData);
u8   GetIRQ_OUT_Level();




// ******* VARIABLES ********

// Variables for sending information
//	const u8 IDNTx[IDNTxArrayLen] = {SendCB,IDNCmd,IDNLen};
	const u8 PSTx[PSTxArrayLen] = {SendCB,PSCmd,PSLen,ISO15693PrCode,0x09};
	const u8 EchoTx[EchoTxArrayLen] = {SendCB, EchoCmd};
	const u8 Inventory[SendRecvTxArrayLen] = {SendCB,SendRecvCmd,0x03,0x26,0x01,0x00};
	const u8 GetSystemInfo[GetSystemInfoTxArrayLen] = {SendCB,SendRecvCmd,0x02,0x02,0x2B};
	u8 ReadSingleBlockTx[ReadSingleBlockTxArrayLen] = {SendCB,SendRecvCmd,0x03,0x02,0x20,0x00};
	u8 WriteSingleBlockTx[WriteSingleBlockTxArrayLen] = {SendCB,SendRecvCmd,0x07,0x02,0x21,0x00,0xFF,0xFF,0xFF,0xFF};
	const u8 ResetTx[1] = {0x01};
	const u8 RdRegTx[RdRegTxArrayLen] = {SendCB,0x08,0x03,0x62,0x01,0x00};
	const u8 WrRegTx[WrRegTxArrayLen] = {SendCB,0x09,0x04,0x68,0x01,0x18,0x00};
//      	const u8 WrRegTx[WrRegTxArrayLen] = {SendCB,0x09,0x04,0x68,0x00,0x01,0x00};
	const u8 TagDetectorModeTx[IdleTxArrayLen] = {SendCB,IdleCmd,IdleLen,0x0B,0x21,0x00,0x79,0x01,0x18,0x00,0x20,0x60,0x60,0x68,0x78/*0x55,0xaa*/,0x3F,0x1F};
	const u8 ReadARC_bRegTx[RdRegTxArrayLen] = {SendCB,0x08,0x03,0x69,0x01,0x00};
	const u8 UpdateARC_bRegTx[UpdateARC_bRegTxArrayLen] = {SendCB,0x09,0x04,0x68,0x01,0x01,0x65};
	const u8 SetARC_bRegTx[SetARC_bRegTxArrayLen] = {SendCB,0x09,0x03,0x68,0x00,0x01};


// Variables for receive information

//	u8 IDNRx[IDNRxArrayLen] = {};
	u8 PSRx[PSRxArrayLen] = {0};
	u8 SendRecvRx[SendRecvRxArrayLen] = {0}; 
	u8 RdRegRx[RdRegRxArrayLen] = {0};
	u8 WrRegRx[WrRegRxArrayLen] = {0};
	u8 EchoRx[EchoRxArrayLen] = {0};
	u8 IdleRx[IdleRxArrayLen] = {0};

	const u8 TagAddress = 0x06;
	

void CR95HF_Send_IRQIN_NegativePulse(void)
{
	CR95HF_IRQIN_HIGH() ;
	delay_ms(1);
	CR95HF_IRQIN_LOW() ;
	delay_ms(1);
	CR95HF_IRQIN_HIGH() ;
}        

void ResetCR95HF()
{
    // Reseting the CR95HF
    // Select CR95HF over SPI 
    SetCS(0);
    // Send reset control byte
//    SPI_SendReceiveByte(0x01);
    SPI_SendReceiveByte(0x01);
    // Deselect CR95HF over SPI 
    SetCS(1);
    delay_ms(20);
    
    // send a pulse on IRQ_in
    CR95HF_Send_IRQIN_NegativePulse();
    //CsPulse();
}
        
void RfidReady()
{
    SetCS(1);
    SetIRQ_IN();
    delay_us(20);
}

void SetRfidReader()
{
	RfidReady();
	ResetCR95HF();
}        

void CustCR95HF_SPI_Init()
{
  SPI_I2S_DeInit(CR95HF_SPI);
  CustCR95HF_SPI_RccConfiguration();
  CustCR95HF_SPI_GpioConfiguration();
  //CR95HF_ResetIfNeed();
}


u8 ModifyARC_bReg()
{
    if(UpdateARC_bReg(UpdateARC_bRegTx) != RESULTOK) return ERRORCODE_GENERIC;
    return RESULTOK;
}

u8 UpdateARC_bReg(const u8 *UpdateARC_bRegTx)
{  
	if(!CR95HF_SPITxRx(UpdateARC_bRegTx,WrRegRx,UpdateARC_bRegTxArrayLen,WrRegRxArrayLen, interrupt)) return ERRORCODE_GENERIC;
    return RESULTOK;
}


void CustCR95HF_SPI_PeriphConfiguration(void)
{


}

void CustCR95HF_SPI_RccConfiguration(void)
{  
  //RCC_PCLK1Config(RCC_HCLK_Div2); 
  /*!< clock enable */
  RCC_AHBPeriphClockCmd(CR95HF_SPI_RCC_AHBPeriph,  ENABLE);

  /*!< I2C1 Periph clock enable */
  RCC_APB1PeriphClockCmd(CR95HF_SPI_CLK, ENABLE);
 // RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
//  RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
}


void CustCR95HF_SPI_GpioConfiguration(void)
{
 
  GPIO_InitTypeDef  GPIO_InitStructure;
  /*!< Configure pins */
  
  /*SCK*/
  GPIO_InitStructure.GPIO_Pin   = CR95HF_SPI_SCK_PIN | CR95HF_SPI_MISO_PIN | CR95HF_SPI_MOSI_PIN;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
  GPIO_Init(CR95HF_SPI_GPIO, &GPIO_InitStructure);
  GPIO_Init(CR95HF_SPI_GPIO, &GPIO_InitStructure);
  /*
  GPIO_PuPd_NOPULL = 0x00,
  GPIO_PuPd_UP     = 0x01,
  GPIO_PuPd_DOWN   = 0x02
    */

  
  
//  GPIO_PinAFConfig(CR95HF_SPI_PORT, CR95HF_SPI_SCK_PIN_SRC, GPIO_AF_I2C2);  

  /* Configure I/O for Chip select */		
  GPIO_InitStructure.GPIO_Pin   	= CR95HF_NCS_PIN | CR95HF_nIRQIN_PIN;
  GPIO_InitStructure.GPIO_Mode  	= GPIO_Mode_OUT; 
  GPIO_InitStructure.GPIO_PuPd          = GPIO_PuPd_NOPULL;
  GPIO_Init(CR95HF_SPI_GPIO, &GPIO_InitStructure);
  

  
  GPIO_InitStructure.GPIO_Pin   			= CR95HF_nIRQOUT_PIN;
  GPIO_InitStructure.GPIO_Mode  			= GPIO_Mode_IN; 
  GPIO_Init(CR95HF_SPI_GPIO, &GPIO_InitStructure);
  
  
  
//  GPIO_InitTypeDef GPIO_InitStructure;
  
  
//  GPIO_InitStructure.GPIO_Pin = CR95HF_SPI_SCK_PIN | CR95HF_SPI_MISO_PIN | CR95HF_SPI_MOSI_PIN;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//  GPIO_Init(CR95HF_SPI_GPIO, &GPIO_InitStructure);
//  GPIO_PinAFConfig(SPIz_GPIO, GPIO_PinSource13 ,GPIO_AF_SPI2); 
//  GPIO_PinAFConfig(SPIz_GPIO, GPIO_PinSource14, GPIO_AF_SPI2); 
//  GPIO_PinAFConfig(SPIz_GPIO, GPIO_PinSource15, GPIO_AF_SPI2); 
//  
  
  GPIO_PinAFConfig(CR95HF_SPI_GPIO, CR95HF_SPI_SCK_PIN_SRC,  GPIO_AF_SPI2); 
  GPIO_PinAFConfig(CR95HF_SPI_GPIO, CR95HF_SPI_MISO_PIN_SRC, GPIO_AF_SPI2); 
  GPIO_PinAFConfig(CR95HF_SPI_GPIO, CR95HF_SPI_MOSI_PIN_SRC, GPIO_AF_SPI2);
  
  
   
  /* NSS  = High Level  */ 
  SetCS(1); 
  SPI_InitTypeDef SPI_InitStructure;
  /* Initialize the SPI with default values */
  SPI_StructInit(&SPI_InitStructure);
//  /* SPI Config master with NSS manages by software using the SSI bit*/ 
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_Mode      = SPI_Mode_Master;
  SPI_InitStructure.SPI_DataSize  = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL      = SPI_CPOL_High;//SPI_CPOL_Low;//SPI_CPOL_High;
  SPI_InitStructure.SPI_CPHA      = SPI_CPHA_2Edge;
  SPI_InitStructure.SPI_NSS       = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;
  SPI_InitStructure.SPI_FirstBit          = SPI_FirstBit_MSB;//SPI_FirstBit_LSB;



//  
//  SPI_InitStructure.SPI_CRCPolynomial = 7;
  /* Init the SPI BRIDGE */
  SPI_Init(CR95HF_SPI, &SPI_InitStructure);

//  SPI_SSOutputCmd(CR95HF_SPI, DISABLE);
  /* Enable SPI */
  SPI_Cmd(CR95HF_SPI, ENABLE);
}



void SetCS(char state)
{
 if(state)
   CR95HF_NSS_LOW();   
 else
   CR95HF_NSS_HIGH();

}


void SetIRQ_IN()
{
    CR95HF_IRQIN_HIGH();
    delay_us(200);
    CR95HF_IRQIN_LOW(); 
    delay_us(100);
    CR95HF_IRQIN_HIGH();
    //delay_ms(20);
}


uint8_t SPI_SendReceiveByte(uint8_t data) 
{	  
        //если данные уже есть в регистре, очищаем  
        if (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == SET)
           SPI_I2S_ReceiveData(SPI2);
        
	/* Wait for SPI1 Tx buffer empty */
	while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);

	/* Send byte through the SPI1 peripheral */
	SPI_I2S_SendData(SPI2, data);	

	/* Wait for SPI1 data reception	*/
	while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);

	/* Read & return SPI1 received data	*/
	return SPI_I2S_ReceiveData(SPI2);
}

void CsPulse(void)
{
    SetCS(1);
//    delay_ms(15);//20
    delay_us(100);
    SetCS(0);
    delay_ms(25);//20
//    delay_us(100);
}


u8 GetIRQ_OUT_Level()
{
  return CR95HF_GET_INTERFACE();
}


u8 CR95HF_SPITxRx(const u8 *SendData, u8 *RecData, const int SendDataLen, const int RecDataLen, u8 interrupt)
{
    u8 result = 0;
    int array_count;
    int n = 0;    
    
    SetCS(0);
    CsPulse();

    for(array_count = 0; array_count < SendDataLen; array_count++)
    {
            SPI_SendReceiveByte(SendData[array_count]);
            delay_us(10);
    }
    
    // interrupt mode. interrupt the CR95HF until it is ready
    // Interrupt mode. Wait when IRQ_OUT pin goes low
    //delay_ms(330);
    CsPulse();
    if(interrupt)
    {
      unsigned int WaitCounter=0;
      while (GetIRQ_OUT_Level())
      {
              if (WaitCounter++ >= 30)//50
                      goto exit;
               delay_ms(10);
      }
    }
// Reading data from CR95HF
    if(RecDataLen)
    {
      CsPulse(); 
      SPI_SendReceiveByte(2);//reading mode
//    delay_us(50);
      for(n = 0; n < RecDataLen; n++)
      {
              RecData[n] = SPI_SendReceiveByte(0xff);
              delay_us(30);
      }
    }
    result = 1;
exit:
    SetCS(1);
//    delay_ms(20);
    return result;
}



u8 ISO15693ProtocolSelect()
{
    if(!CR95HF_SPITxRx(PSTx,PSRx,PSTxArrayLen,PSRxArrayLen,interrupt)) 
      return ERRORCODE_GENERIC;
    if(!ModifyARC_bReg()) 
      return ERRORCODE_GENERIC;
    return RESULTOK;
}

#define PollCanBeSendFlag      0x04
#define PollCanBeReceivedFlag  0x08
#define PollFilterFlag         0xf0


//u8 RfidGetPollVal();
//void WaitPollForSend()
//{
//  u8 val;
//  while(((val = RfidGetPollVal()) & PollCanBeSendFlag) == 0)
//  {
//     if(val & PollCanBeReceivedFlag)
//       SPI_SendReceiveByte(0xff);
//  }
//}

u8 RfidGetPollVal()
{
  u8 val = SPI_SendReceiveByte(0x03); 
  if((val & 0xff) != 0xff) 
    return  val;
  else
    return 0;
}

u8 RfidIsCommunicationOk()
{
  //u8 data0,data1,data2,data3,data4,data5;

//  int readTime  = 40;  
 /* 
  SetCS(0);
  CsPulse();
  
  SPI_SendReceiveByte(0x00);
  SPI_SendReceiveByte(0x55);
  CsPulse();
  while((RfidGetPollVal() & PollCanBeReceivedFlag) == 0)
  {
    delay_us(100);
  }
  CsPulse();
  SPI_SendReceiveByte(0x02);
 
  EchoRx[0] =  SPI_SendReceiveByte(0xff);
 
  SetCS(1);
  return ((EchoRx[0]==0x55)? 1:0);
 */ 

  if(!CR95HF_SPITxRx(EchoTx, EchoRx, EchoTxArrayLen, EchoRxArrayLen, interrupt)) 
    return ERRORCODE_GENERIC;
  return ((EchoRx[0]==0x55)? 1:0);
  
  //if(!CR95HF_SPITxRx(WrRegTx, WrRegRx, WrRegTxArrayLen, WrRegRxArrayLen, interrupt)) 
  //                return -1;
  //if(!CR95HF_SPITxRx(TagDetectorModeTx, IdleRx, IdleTxArrayLen, IdleRxArrayLen, interrupt)) 
    //              return -1;
  //if(!CR95HF_SPITxRx(RdRegTx,RdRegRx,RdRegTxArrayLen,RdRegRxArrayLen,interrupt)) 
  //                return -1;
 
}

u8 RfidIsTagPresent()
{
	int TagDetectCounter = 0;
        ResetCR95HF();
	do{

		if(!CR95HF_SPITxRx(WrRegTx,WrRegRx,WrRegTxArrayLen,WrRegRxArrayLen,interrupt)) 
                   return ERRORCODE_GENERIC;
               
              
		if(!CR95HF_SPITxRx(TagDetectorModeTx,IdleRx,IdleTxArrayLen,IdleRxArrayLen,interrupt)) 
                  return ERRORCODE_GENERIC;
               
          
		if(!CR95HF_SPITxRx(RdRegTx,RdRegRx,RdRegTxArrayLen,RdRegRxArrayLen,interrupt)) 
                  return ERRORCODE_GENERIC;
               
		TagDetectCounter++;
	}while ((RdRegRx[2] != 0x02)&&(TagDetectCounter <= 2));

	if (RdRegRx[2] != 0x02) 
          return ERRORCODE_GENERIC; 	//Tag is Detected . If (RdRegRx[2] == 0x01) then Timeout. Tag is not detected	
	return RESULTOK;
}


u8 RfidGetSystemInfo()
{
	if(!CR95HF_SPITxRx(GetSystemInfo, SendRecvRx,SendRecvTxArrayLen,SendRecvRxArrayLen,interrupt)) return ERRORCODE_GENERIC;
    delay_us(50);
    return RESULTOK;
}

u8 RfidGetCryptKey(u8 *Key)
{
    u8 i = 0;
		for (i = 0; i<8;i++)
			{
				Key[i] = SendRecvRx[11-i];
			}
    if (Key[0] != 0xE0) return ERRORCODE_GENERIC;
        else return RESULTOK;            
}
			                                                                                                                                                                                                                                                                                                                                                                                                                        
u8 RfidReadSingleBlock()
{
    u8 counter = 0;
    do{
	if(!CR95HF_SPITxRx(ReadSingleBlockTx,SendRecvRx,ReadSingleBlockTxArrayLen,SendRecvRxArrayLen,interrupt)) return ERRORCODE_GENERIC;
    } while (((SendRecvRx[0] != 0x80)|(SendRecvRx[9] != 0x00))&&(counter <=0x05));
	
    if ((SendRecvRx[9] == 0x00)&(counter <=0x05)) return RESULTOK;
    else return ERRORCODE_GENERIC;
}

u8 RfidWriteSingleBlock()
{
	if(!CR95HF_SPITxRx(WriteSingleBlockTx,SendRecvRx,WriteSingleBlockTxArrayLen,SendRecvRxArrayLen,interrupt)) return ERRORCODE_GENERIC;
	return RESULTOK;
}

u8 RfidWriteData(RfidData *SetData, u8 ManufCodeWriting)
{
	if(RfidIsTagPresent() != RESULTOK) return ERRORCODE_GENERIC;
	if(ISO15693ProtocolSelect() != RESULTOK) return ERRORCODE_GENERIC;
    delay_us(50);
	if (RfidWriteMultipleBlocks(TagAddress, SetData->data, ManufCodeWriting) != RESULTOK) return ERRORCODE_GENERIC;
	return RESULTOK;	
}

u8 RfidReadData(RfidData *GetData)
{
    if(ISO15693ProtocolSelect() != RESULTOK) return ERRORCODE_GENERIC;
    delay_us(100);
    if(RfidGetSystemInfo() != RESULTOK) return ERRORCODE_GENERIC;
    delay_us(100);
    if(RfidGetCryptKey(GetData->Key) != RESULTOK) return ERRORCODE_GENERIC;
    if(RfidReadMultipleBlocks(TagAddress, GetData->data) != RESULTOK) return ERRORCODE_GENERIC;
    return RESULTOK;	
}
  
u8 RfidReadMultipleBlocks(u8 Address, u8 *Data)
{
    u8 i = 0;
	int n = 0,m = 0;
    int SingleBlock = 4;
	u8 TryNum = 12;

	for(i=0;i<Address;i++)
		{
		ReadSingleBlockTx[5] = i;		// Select addresses of RFID tag
		for (u8 p = 0; p < TryNum; p++)
		{
			if(RfidReadSingleBlock() == RESULTOK) break;
			if(TryNum > 12) return ERRORCODE_GENERIC;				
		}		
		for(m = 0; m < SingleBlock; m++)
			{
				Data[n] = SendRecvRx[3+m];
				n++;
			}
		}
	return RESULTOK;
}

u8 RfidWriteMultipleBlocks(u8 Address, u8 *Data, u8 ManufCodeWriting)
{
	u8 y = 0;
	int n = 0,m = 0;
	int SingleBlock = 4;
		
    if(ManufCodeWriting == 1) {y = 0; n = 0;}
        else {y = 1; n = 4;}
	for(u8 i = y;i<Address;i++)
	{
		WriteSingleBlockTx[5] = i;
		for(m = 0; m < SingleBlock; m++)
		{
			WriteSingleBlockTx[6+m] = Data[n];
			n++;
		}
	if(RfidWriteSingleBlock() == ERRORCODE_GENERIC) return ERRORCODE_GENERIC;
    }
    return RESULTOK;
}
