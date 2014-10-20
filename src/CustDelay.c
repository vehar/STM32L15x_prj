#include "CustDelay.h"

static volatile uint32_t TimingDelay;


void CustDelayInit()
{
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
 //ms
  SysTick_Config((SystemCoreClock / 1000));// 1ms timer
  NVIC_SetPriority (SysTick_IRQn, 0);
 //us x 10
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  /* Time base configuration */
  TIM_TimeBaseStructure.TIM_Period = 48000;
  TIM_TimeBaseStructure.TIM_Prescaler = 15;
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV2;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Down;
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

  TIM_ARRPreloadConfig(TIM2, DISABLE);
  TIM_SelectOnePulseMode(TIM2, TIM_OPMode_Single);

}

void delay_ms(uint32_t nTime)
{
  TimingDelay = nTime;
  while(TimingDelay != 0);
}

void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
    TimingDelay--;
}


void delay_us(uint16_t val)
{
  TIM_Cmd(TIM2, DISABLE);
  TIM_SetCounter(TIM2, val);
  TIM_Cmd(TIM2, ENABLE);

  while (TIM2->CR1 & TIM_CR1_CEN);
}
