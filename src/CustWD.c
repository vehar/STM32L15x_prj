#include "CustWD.h"

void  CustWDInit()
{
  WWDG_DeInit();
  /* WWDG configuration */
  /* Enable WWDG clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);

/* WWDG clock counter = (PCLK1 (32MHz)/4096)/8 = 977 Hz (~1024 æs)  */
/* WWDG clock counter = (PCLK1 (16MHz)/4096)/8 = 488 Hz (~2048 us)  */
  WWDG_SetPrescaler(WWDG_Prescaler_8);
  /* Set Window value to 65 */
  WWDG_SetWindowValue(CustWDWindCounter);
  /* Enable WWDG and set counter value to 127, WWDG timeout = ~2048 æs * 64 = 65.53 ms */
  WWDG_Enable(CustWDInitCounter);
  /* Clear EWI flag */
  //WWDG_ClearFlag();
  
  /* Enable EW interrupt */
//  WWDG_EnableIT();
}

void CustWDReset()
{
  //WWDG_Enable(CustWDInitCounter);
   WWDG_SetCounter(CustWDInitCounter);
}