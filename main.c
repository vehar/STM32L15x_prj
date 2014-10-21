//#include "discover_board.h"
//#include "stm32l_discovery_lcd.h"
//#include "stm32l1xx_i2c.h"

#include "stm32l1xx.h"
#include "stm32l1xx_gpio.h"
#include "stdio.h"
#include "main.h"
#include "gpio_init.h"
#include "functions.h"
#include "functions.c"

void All_init(void){
    SystemInit();
 // HSI_on_16MHz();
    All_clk_On(); 

	//PIN_CONFIGURATION(LED_GREEN);	//PIN_CONFIGURATION(LED_BLUE); 	// ����������
  //OR
 GPIOB->MODER |= GPIO_MODER_MODER6_0 | GPIO_MODER_MODER7_0 ;//B6 B7 - out       
PIN_CONFIGURATION(USER_BUTTON);        	// ������
//OR      // GPIOA->MODER &=~ GPIO_MODER_MODER1_0;//A1 IN   

/******Key`s init_section******/  
  //    Timer2_init_vs_irq(); //ovr_irq
 Timer3_init_encoder_mode(); // encoder
 Button_init_vs_irq();   
 Matrix_kbd_init();
  
/****Interface init_section****/  
 Usart_init_vs_irq ();
 Spi2_init_vs_irq  ();
 ///i2c1_init();///i2c1_rx(0xA0);
 ADC_init();

 //----------------------------------------------------------------
        //ENEBLE INTERRUPTS
        //1
 __enable_irq ();   //Global enable
       //2
// NVIC_EnableIRQ(EXTI1_IRQn); // Enable IRQn
 //NVIC_DisableIRQ(EXTI1_IRQn); // Disable IRQn      
      //3 ��������� � ��������� ���������� ���������� � ���������
 //EXTI->IMR |=(EXTI_IMR_MR1 | EXTI_IMR_MR2); //��� ������� 1 � 2
// EXTI->RTSR |= EXTI_RTSR_TR1 | EXTI_FTSR_TR2 ; //������������ - �� ��������� � ��������� �������
 //-------------------------------------------------------------------
}

void Debug_section(void){
 //**********Debug section***************//
 //*************************************//
   //  ADC_measure(10);  /*!< Start Conversion of regular channels */
   //   ADC_measure(11);
    //   ADC_measure(16);
// send_str_u(  (char*)NVIC_GetPriority (EXTI0_IRQn));
 //spi_exchange(send_data); 
 //send_data = 0x05;
 
  send_str_u("===STM_GO!===\n");
 button_port = GPIOC->IDR;  
send_to_usart(button_port>>8);
 
 
GPIOB->ODR |= GPIO_OTYPER_ODR_6;	// ��������� ���� 6 ����� B (blue)
GPIOB->ODR |= GPIO_OTYPER_ODR_7;	// ��������� ���� 7 ����� B  (green)

button_port = GPIOC->IDR;  
send_to_usart(button_port>>8);


GPIOB->ODR &= ~(GPIO_OTYPER_ODR_7);	// ����� ���� 7 ����� B
//=
GPIOB->BSRRH |= GPIO_BSRR_BS_7;   

button_port = GPIOC->IDR; send_to_usart(button_port>>8);

 PIN_ON(LED_GREEN); 
 PIN_OFF(LED_GREEN) ;
 //PIN_SIGNAL(LED_GREEN) ;
 
Get_key();

//*************************************//
//**********Debug section***************/  
}

void Encoder_proc (void){
    Encoder_curr_pos = (TIM3->CNT & 254)>>1; //get encoder data (1 byte, div 2)
   if(Encoder_curr_pos != Encoder_prev_pos)
   {
    // send_str_u("ENC");
     send_to_usart(Encoder_curr_pos);
     Encoder_prev_pos = Encoder_curr_pos;     
   }
}


char out_data_t = 0; //tmp debug
int main(void)
{
All_init();

Debug_section();
  
 while (1)
 {

 Encoder_proc();
 
 out_data_t = Get_key();
send_to_usart(out_data_t); //debug 
SPI1->DR = out_data_t;
SPI2->DR = out_data_t;
       

//button_port = GPIOC->IDR;  
//send_to_usart(button_port>>8);
 
  
    ///////////////////////////////////////////////////////--------------------
          /*����� ������� ������ �������.
    � �������� ��������� ���������� ���������� �������� 0x01 ��� 0x03*/
 
       //spi_exchange(send_data); 
    //SPI2->DR = Encoder_curr_pos; //����� � ����� ����������� SPI2 
   // send_to_usart(Encoder_curr_pos);
 //   SPI1->DR = 0x05+512; //����� � ����� ����������� SPI1. ����� ����� �������� ����� �������
                     //�� ��������� � ����������
   //spi_exchange(send_data);  
    switch(temp)
    {/*���� SPI1 ������ 0x01, �������� ��������������� ���������, 
      � ������ �������� ���������, ������������� ������� ������ �������
      ��� ��������� ������ �� 0x03*/
    case 0x01:
      GPIOB->BSRRH |= GPIO_BSRR_BS_7;
      GPIOB->BSRRL |= GPIO_BSRR_BS_6;
      send_str_u("SPI=01");
      send_data = 0x03;
      break;
      /*���� SPI1 ������ 0x03, �������� ��������������� ���������, 
      � ������ �������� ���������, ������������� ������� ������ �������
      ��� ��������� ������ �� 0x01*/
    case 0x03:
      GPIOB->BSRRH |= GPIO_BSRR_BS_6;
      GPIOB->BSRRL |= GPIO_BSRR_BS_7;
       send_str_u("SPI=03");
      send_data = 0x01;
      break;     
     default :  GPIOB->BSRRH |= GPIO_BSRR_BS_7;
    }
    //////////////////////////////////////////////////////////////-------------------
//delay(1000);

  delay(100000);  
  
  //send_to_usart(temp);
 //   if (USART1->SR & USART_SR_RXNE) {usart_data=USART1->DR;  
  //switch(usart_data)  {
 switch(usart_data)  {
    case '1':
       Info(); 
       break;
    case '2':
       Timer2_init_vs_irq(); //ADC_measure(10);  //every second ad-conventiuon flag (in irq)setts
       break;
    case '3':
       GPS_get_data();      
       break;
    case '4':
       Current_monitor_get_data();
       break;     
    case '5':
        ADC_measure(11);  /*!< Start Conversion of regular channels */
       break;
    case '6':
        send_str_u("===HELLO_FROM_USART!===");
      break;
      case '7':
        SPI2->DR=0xABCD;
      break;
       case '8':  //Keybord_debug
  //pressed_key = Get_key();    
  //send_to_usart(pressed_key);
 
      break;
     //default :    send_str_u("Invalid_comand!");
 }
 
 
 /*
  if(strcmp(UsartRxBuffer,"led0")==0) //���� ������ ������� "led0"
   {
    GPIOB->BSRRH |= GPIO_BSRR_BS_6;  // Reset PB6 bit
   }
 if(strcmp(UsartRxBuffer,"led1")==0) //���� ������ ������� "led1"
   {
     GPIOB->BSRRL |= GPIO_BSRR_BS_6;   // Set PB6 bit
   }
*/ 

     //    }
          /*
        //��������� ������
          if (GPIOA->IDR & GPIO_IDR_IDR_1){
            delay(10000);
              if (GPIOA->IDR & GPIO_IDR_IDR_1){
                 delay(1000);
          GPIOB->ODR &= ~GPIO_ODR_ODR_7  ;
          GPIOB->ODR &= ~GPIO_ODR_ODR_6  ;
                t^=1;  }}

          */
          
        //  if (A_flag){  GPIOB->ODR ^= GPIO_ODR_ODR_6  ;  } // 
        //  RESET(A_flag);

               /*  
        GPIOB->ODR |= GPIO_ODR_ODR_6; //
    	GPIOB->ODR &= ~GPIO_ODR_ODR_7  ;
        delay(100000);
        
          else
        GPIOB->ODR |= GPIO_ODR_ODR_7  ;
        GPIOB->ODR &= ~GPIO_ODR_ODR_6  ;
        delay(100000);
         */ 
         
         
//flag state machine
 if(ADC_start_flag)    { ADC_measure(10); ADC_measure(11); RESET(ADC_start_flag);} 
 
 
 //End of main cycle
 //Cleaning all buffers 
  if(UsartRxBuffer[0]!=0)
  {
      // send_str_u(UsartRxBuffer); //return to console
       memset(UsartRxBuffer, 0, sizeof(UsartRxBuffer)); //clearing buffer
       usart_data=0;
       usart1_rx_bit=0; //reset counter
  }
   if(spi1_buf[0]!=0)
  {
       memset(spi1_buf, 0, sizeof(spi1_buf)); //������� �����
       spi1_data=0;
       spi1_bit=0; //���������� �������
  }
   
 
 }
}/*****************END MAIN*******************************/


uint8_t i=0; 

void TIM2_IRQHandler(void)
{   
    TIM2->SR &= ~TIM_SR_UIF; //Clean UIF Flag
    SET(ADC_start_flag);

    /*
    if (1 == (i++ & 0x01)) {
      GPIOB->BSRRH |= GPIO_BSRR_BS_7;  // Reset PB7 bit
    } else {
      GPIOB->BSRRL |= GPIO_BSRR_BS_7;   // Set PB7 bit
    }    
    */
    
  //  send_str_u("Timer2_IRQ!\n");
}

void TIM3_IRQHandler(void)
{   
   TIM3->SR &= ~TIM_SR_UIF; //Clean UIF Flag
   send_str_u("Timer3_IRQ!\n");
}

//------------------------------------------------------------------------------
uint8_t j=0; 

void EXTI0_IRQHandler(void)
{
  EXTI->PR |= EXTI_PR_PR0; // ����� ����� ����������
 // t^=1;
//  SET(A_flag);
  
    send_str_u("You!");
  
 if (1 == (j++ & 0x01)) {
        //GPIOB->BSRR |= GPIO_BSRR_BS_6;   // Set PB4 bit
       // GPIOB->BSRR |= GPIO_BSRR_BR_7;  // Reset PB5 bit
      
   //    GPIOB->ODR &= ~GPIO_ODR_ODR_6  ;
    }
 else {
      // GPIOB->BSRR |= GPIO_BSRR_BS_7;   // Set PB5 bit
       // GPIOB->BSRR |= GPIO_BSRR_BR_6;  // Reset PB4 bit 
 
   //   GPIOB->ODR |= GPIO_ODR_ODR_6  ;
          }
}

 
// ���������� EXTI 1
void EXTI1_IRQHandler(void)
{
uint32_t	i;
EXTI->PR |= EXTI_PR_PR1;  // ����� ����� ����������
 SET(B_flag);
}

// ���������� EXTI 2
void EXTI2_IRQHandler(void)
{
uint32_t	i;
EXTI->PR |= EXTI_PR_PR2;  // ����� ����� ����������
 SET(C_flag);
}


// ���������� EXTI 3
void EXTI3_IRQHandler(void)
{
uint32_t	i;
EXTI->PR |= EXTI_PR_PR3;  // ����� ����� ����������
 SET(D_flag);
}


// ���������� EXTI 4
void EXTI4_IRQHandler(void)
{
uint32_t	i;
EXTI->PR |= EXTI_PR_PR4;  // ����� ����� ����������
 SET(E_flag);
}


// ���������� EXTI 9-5
void EXTI9_5_IRQHandler(void)
{
uint32_t	i;
EXTI->PR |= EXTI_PR_PR5;  // ����� ����� ����������
 SET(F_flag);
}

// ���������� EXTI 10-15
void EXTI15_10_IRQHandler(void)
{
uint32_t	i;
EXTI->PR |= EXTI_PR_PR10;  // ����� ����� ����������
 SET(ENKODER_flag);
}


void USART1_IRQHandler (void){

  if (USART1->SR & USART_SR_RXNE) {
    usart_data=USART1->DR;   
//USART1->DR = USART1->DR; //ECHO MODE
   UsartRxBuffer[usart1_rx_bit]=usart_data; //put recieved byte in buffer
   usart1_rx_bit++; //buffer count ++ 
  }
  USART1->SR |=  USART_SR_TC; //clear flags  
  USART1->SR |=  USART_SR_RXNE; 
}


void SPI1_IRQHandler (void){
      send_str_u("S");
 
  if( SPI1->SR & SPI_SR_RXNE){ // RXNE =1   Receive buffer contains data 
       //  GPIOB->BSRRH |= GPIO_BSRR_BS_7;   //RESet PB6 bit
   spi1_data = SPI1->DR;//��������� ������ �� ��������� ������ SPI1. ��� ���� �������� ���������� ������� ������ � ����� ����� RXNE 
   spi1_buf[spi1_bit]=spi1_data; //�������� �������� ���� � �����.
   temp=spi1_data;
   spi1_bit++; //���������� ������� ������ ������. 
  }
  
   if( SPI2->SR & SPI_SR_TXE){ // (TXE =1 - Transmit buffer empty))
       //  send_str_u("SPI1_IRQ  Transmit buffer empty");
     //   GPIOB->BSRRL |= GPIO_BSRR_BS_7;   // Set PB6 bit
  }
}

void SPI2_IRQHandler (void){
 //   send_str_u("SPI2_IRQ");
  
  if( SPI2->SR & SPI_SR_RXNE){ // (RXNE =1 - �������� ����� �������� ������))
  
       //  GPIOB->BSRRH |= GPIO_BSRR_BS_6;   //RESet PB6 bit
    
    
    temp = SPI2->DR;//��������� ������ �� ��������� ������ SPI2. ��� ���� �������� ���������� ������� ������ � ����� ����� RXNE
   // send_to_usart(temp); //?/??    
    USART1->DR = temp; 
    
    SPI2->DR = (short)Encoder_curr_pos; //����� � ����� ����������� SPI2 
   // send_to_usart(Encoder_curr_pos);
    
  }
   if( SPI2->SR & SPI_SR_TXE){ // (TXE =1 - Transmit buffer empty))

     //   GPIOB->BSRRL |= GPIO_BSRR_BS_6;   // Set PB6 bit
  }
}


void I2C1_EV_IRQHandler (void){
   send_str_u("i2c1_IRQ");
    
}


void ADC1_IRQHandler (void){
  if(ADC1->SR & ADC_SR_EOC) { /*!< End of conversion */
    ADC_data=ADC1->DR;
    
    send_str_u("ADC");
   send_to_usart(ADC_data);
   }
}