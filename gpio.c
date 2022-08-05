#include "gpio.h"

void GPIO_Init(void)
{
  RCC->AHBENR |= RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOEEN;
  
  /* SPI CONFIGURATION */
  GPIOA->MODER |= GPIO_MODER_MODER5_0;                                          /* SCLK - output mode */
  GPIOA->MODER |= GPIO_MODER_MODER7_0;                                          /* SDI / MOSI  - output mode */
  //GPIOA->MODER |= GPIO_MODER_MODER6_0;                                        /* SDO / MISO  - input mode */
  GPIOE->MODER |= GPIO_MODER_MODER3_0;                                          /* CS   - output mode */
  //GPIOE->MODER |= GPIO_MODER_MODER1_0;                                        /* INT2 - input mode */
  //GPIOE->MODER |= GPIO_MODER_MODER0_0;                                        /* INT1 - input mode */
  
  /* PA1 - pull up */
  GPIOE->PUPDR |= 0x2;
  
  /* LED's */
  GPIOE->MODER |= 0x55550000;
  GPIOE->PUPDR |= 0xAAAA0000;
  
  RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
  SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI1_PE;
  SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI0_PA;
  
  /*EXTI SETTINGS*/
  EXTI->IMR |= EXTI_IMR_IM1;
  EXTI->RTSR |= EXTI_RTSR_TR1;
  NVIC_EnableIRQ(EXTI1_IRQn);
  NVIC_SetPriority(EXTI1_IRQn, 1);
  
  EXTI->IMR |= EXTI_IMR_IM0;
  EXTI->RTSR |= EXTI_RTSR_TR0;
  NVIC_EnableIRQ(EXTI0_IRQn);
  NVIC_SetPriority(EXTI0_IRQn, 1);  
  
  /* pin configuration */
  SETBIT(GPIOE->ODR, CS);
  SETBIT(GPIOA->ODR, SCLK);
}