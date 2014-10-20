#pragma once

#include "stm32l1xx.h"
//#include "stm32l1xx_spi.h"
#include "CustDelay.h"


void CustCR95HF_SPI_Init(); //runs rcc, gpio, nvic configuration

void CustCR95HF_SPI_RccConfiguration(void);
void CustCR95HF_SPI_GpioConfiguration(void);
//void CustCR95HF_SPI_NvicConfiguration(void);
void CustCR95HF_SPI_PeriphConfiguration(void);


// data types
#define u8 unsigned char

#define CR95HF_SPI		     	SPI2
#define CR95HF_SPI_GPIO		     	GPIOB
#define CR95HF_SPI_CLK		    	RCC_APB1Periph_SPI2
#define CR95HF_SPI_RCC_AHBPeriph        RCC_AHBPeriph_GPIOB 

#define CR95HF_SPI_SCK_PIN        	GPIO_Pin_13
#define CR95HF_SPI_SCK_PIN_SRC        	GPIO_PinSource13                    
#define CR95HF_SPI_MISO_PIN        	GPIO_Pin_14                
#define CR95HF_SPI_MISO_PIN_SRC        	GPIO_PinSource14                
#define CR95HF_SPI_MOSI_PIN        	GPIO_Pin_15   
#define CR95HF_SPI_MOSI_PIN_SRC        	GPIO_PinSource15   
                       
#define CR95HF_NCS_PIN             	GPIO_Pin_12                  
#define CR95HF_nIRQOUT_PIN             	GPIO_Pin_10                  
#define CR95HF_nIRQIN_PIN             	GPIO_Pin_11                 


//Chip Select handle for SPI interface 
#define CR95HF_NSS_LOW() 			GPIO_SetBits(CR95HF_SPI_GPIO, CR95HF_NCS_PIN)
#define CR95HF_NSS_HIGH()  			GPIO_ResetBits  (CR95HF_SPI_GPIO, CR95HF_NCS_PIN)

#define CR95HF_IRQIN_LOW() 			GPIO_ResetBits  (CR95HF_SPI_GPIO, CR95HF_nIRQIN_PIN)	
#define CR95HF_IRQIN_HIGH()  			GPIO_SetBits(CR95HF_SPI_GPIO, CR95HF_nIRQIN_PIN)

// set state on IRQ in pin
#define CR95HF_GET_INTERFACE() 			GPIO_ReadInputDataBit(CR95HF_SPI_GPIO,CR95HF_nIRQOUT_PIN)


typedef struct
{
//u8 tagPresent;
    unsigned char data[24];
    unsigned char Key[8];
} RfidData; 


#define CheckTagPresentFlag 1
#define TagPresentFlag      2
#define ReadDataFlag        4
#define WriteDataFlag       8
#define WriteManufFlag     16   

typedef struct
{
  u8 flags;
  RfidData data;
} tagData_t;
#define tagDataSize 33


// *** DEFINES ***
#define UpdateARC_bRegTxArrayLen    7
#define SetARC_bRegTxArrayLen	    6

// Control Bytes
#define SendCB		        0x00
#define PollCB		        0x03
#define ReadCB		        0x02
#define ResetCB		        0x01

// Command Codes
//#define IDNCmd		0x01
#define PSCmd			0x02
#define SendRecvCmd		0x04
#define IdleCmd			0x07
#define RdRegCmd		0x08
#define WrRegCmd		0x09
#define EchoCmd			0x55

// Protocol Codes
//#define FieldOffPrCode        0x00
#define ISO15693PrCode          0x01

// Data Lenght Codes
//#define IDNLen		0x00
#define PSLen			0x02
#define IdleLen			0x0E
#define ISO15693Len		0x02

// Send Arrays Lenght
//#define IDNTxArrayLen			3
#define PSTxArrayLen		     5    
#define SendRecvTxArrayLen	     6
#define IdleTxArrayLen		    17
#define RdRegTxArrayLen		     6
#define WrRegTxArrayLen		     7
#define EchoTxArrayLen   	     2
#define ReadSingleBlockTxArrayLen    6
#define WriteSingleBlockTxArrayLen  10
#define GetSystemInfoTxArrayLen	     5

// Recv Arrays Lenght 
//#define IDNRxArrayLen		   17
#define PSRxArrayLen			2    
#define SendRecvRxArrayLen	        20
#define IdleRxArrayLen			3
#define RdRegRxArrayLen                 3

#define WrRegRxArrayLen			2

#define EchoRxArrayLen			2
#define ReadSingleBlockRxArrayLen       10
#define WriteSingleBlockRxArrayLen      9

#define RESULTOK			1 
#define ERRORCODE_GENERIC		0	 



// SPI clock modes
#define SPI_MODE_0	0x00 /* Sample (Rising) Setup (Falling) CPOL=0, CPHA=0 */
#define SPI_MODE_1	0x01 /* Setup (Rising) Sample (Falling) CPOL=0, CPHA=1 */
#define SPI_MODE_2	0x02 /* Sample (Falling) Setup (Rising) CPOL=1, CPHA=0 */
#define SPI_MODE_3	0x03 /* Setup (Falling) Sample (Rising) CPOL=1, CPHA=1 */

// data direction
#define SPI_LSB 1 /* send least significant bit (bit 0) first */
#define SPI_MSB 0 /* send most significant bit (bit 7) first */

// whether to raise interrupt when data received (SPIF bit received)
#define SPI_NO_INTERRUPT 0
#define SPI_INTERRUPT	1

// slave or master with clock diviser
#define SPI_SLAVE		0xF0
#define SPI_MSTR_CLK4	0x00 /* chip clock/4 */
#define SPI_MSTR_CLK16	0x01 /* chip clock/16 */
#define SPI_MSTR_CLK64	0x02 /* chip clock/64 */
#define SPI_MSTR_CLK128 0x03 /* chip clock/128 */
#define SPI_MSTR_CLK2	0x04 /* chip clock/2 */
#define SPI_MSTR_CLK8	0x05 /* chip clock/8 */
#define SPI_MSTR_CLK32	0x06 /* chip clock/32 */

//main or alternative SPI channel

#define SPI_MAIN_CH    0x00
#define SPI_ALT_CH 0x80

//enum Polling {NoPolling = 0, Polling};
enum Interrupt {noInterrupt = 0, interrupt};


u8   RfidIsTagPresent();
void CustCR95HF_SPI_Init();
u8 RfidIsCommunicationOk();
u8   RfidReadData(RfidData *GetData);
u8   RfidWriteData(RfidData *SetData,u8 ManufCodeWriting);


