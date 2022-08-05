/**
  ******************************************************************************
  * @file    GPIO/GPIO_EXTI/Src/stm32f3xx_it.c
  * @author  MCD Application Team
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f3xx_it.h"
#include "stm32f303xc.h"
/** @addtogroup STM32F3xx_HAL_Examples
  * @{
  */

/** @addtogroup GPIO_EXTI
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
   
#include "gyro.h"
    
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint16_t position = 8;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
  
}

/******************************************************************************/
/*                 STM32F3xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f3xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles external lines 10 to 15 interrupt request.
  * @param  None
  * @retval None
  */
void TIM7_IRQHandler(void)
{
  TIM7->SR = 0;
  uint16_t gpioe_mask = GPIOE->ODR;
  (GPIOE->ODR != 0x8000) ? (GPIOE->ODR = gpioe_mask << 1) 
                         : (GPIOE->ODR = 0x0100);
}

void EXTI1_IRQHandler(void)
{
  EXTI->PR |= EXTI_PR_PR1;
  
  GetData(OUT_Z_H); 
  
  x_d = 0.07 * (float)axis.x;
  y_d = 0.07 * (float)axis.y;
  z_d = 0.07 * (float)axis.z;
  
  if (x_d < -100 && y_d < -100)
    GPIOE->ODR = 0x0100;
  else if (x_d < -100 && y_d > 100)
    GPIOE->ODR = 0x0400;
  else if (x_d > 100 && y_d > 100)
    GPIOE->ODR = 0x1000;
  else if (x_d > 100 && y_d < -100)
    GPIOE->ODR = 0x4000;

  else if (x_d < -100)
    GPIOE->ODR = 0x0200;
  else if (y_d > 100)
    GPIOE->ODR = 0x0800;
  else if (x_d > 100)
    GPIOE->ODR = 0x2000;
  else if (y_d < -100)
    GPIOE->ODR = 0x8000;
}


void EXTI0_IRQHandler(void)
{
  EXTI->PR |= EXTI_PR_PR0;
  
  /* interrupt disable on INT2 */
  Write(CTRL_REG3, 0x00);
  
  if (TIM7->CR1 & TIM_CR1_CEN) {
    TIM7->CR1 &= ~TIM_CR1_CEN;
    /* interrupt enable on INT2 */
    Write(CTRL_REG3, 0x08);
    return;
  }
  
  TIM7->CR1 |=  TIM_CR1_CEN;
  
  //TIM7->CR1 &= ~TIM_CR1_CEN;
  //(TIM7->ARR < 1000) ? (TIM7->ARR += 100) : (TIM7->ARR = 100 - 1);
  //TIM7->SR = 0;
  //TIM7->CR1 |= TIM_CR1_CEN;
}

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
