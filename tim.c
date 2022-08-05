#include "tim.h"

void TIM7_Init(void)
{
  RCC->APB1ENR |= RCC_APB1ENR_TIM7EN;
  TIM7->PSC = (4 * 1000) - 1;
  TIM7->ARR = 200 - 1;   /* 100 ms */
  TIM7->SR = 0;
  TIM7->DIER |= TIM_DIER_UIE;
  NVIC_SetPriority(TIM7_IRQn, 0); 
  NVIC_EnableIRQ(TIM7_IRQn);
};