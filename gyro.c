#include "gyro.h"

uint8_t output;
Axis axis;

uint16_t x;
float x_d, y_d, z_d;

void Write(uint8_t address, uint8_t data) 
{
  CLEARBIT(GPIOE->ODR, CS);    
  /* WRITE mode */
  CLEARBIT(GPIOA->ODR, SDI);

  for (uint8_t i = 2; i > 0; i--) 
  {
    /* SCLK = 0 */
    CLEARBIT(GPIOA->ODR, SCLK);
    Delay(125);
    /* SCLK = 1 */
    SETBIT(GPIOA->ODR, SCLK);
    Delay(125);
  }
  
  /* send the address byte */
  for (int8_t shift = 5; shift >= 0; shift--)
  {
    (address >> shift) & 0x01 ? (GPIOA->ODR |= SDI) : (GPIOA->ODR &= ~SDI);
    /* SCLK = 0 */
    CLEARBIT(GPIOA->ODR, SCLK);
    Delay(125);
    /* SCLK = 1 */
    SETBIT(GPIOA->ODR, SCLK);
    Delay(125);
  }
  
  /* send the data byte */
  for (int8_t shift = 7; shift >= 0; shift--)
  {
    /* SCLK = 0 */
    CLEARBIT(GPIOA->ODR, SCLK);
    Delay(125);
    (data >> shift) & 0x01 ? (GPIOA->ODR |= SDI) : (GPIOA->ODR &= ~SDI);
    /* SCLK = 1 */
    SETBIT(GPIOA->ODR, SCLK);
    Delay(125);
  }
  SETBIT(GPIOE->ODR, CS);
}

void Read(uint8_t address) 
{
  uint8_t i, size;
  
  CLEARBIT(GPIOE->ODR, CS);    
  /* READ mode */
  SETBIT(GPIOA->ODR, SDI);
  
  for (i = 2; i > 0; i--) 
  {
    /* SCLK = 0 */
    CLEARBIT(GPIOA->ODR, SCLK);
    Delay(125);
    /* SCLK = 1 */
    SETBIT(GPIOA->ODR, SCLK);
    Delay(125);
  }
  
  /* send the address byte */
  for (int8_t shift = 5; shift >= 0; shift--)
  {
    (address >> shift) & 0x01 ? (GPIOA->ODR |= SDI) : (GPIOA->ODR &= ~SDI);
    
    /* SCLK = 0 */
    CLEARBIT(GPIOA->ODR, SCLK);
    Delay(125);
    /* SCLK = 1 */
    SETBIT(GPIOA->ODR, SCLK);
    Delay(125);
  }
  
  /* receive the data byte */
  size = 8;
  for (i = 0; i < size; i++)
  {
    
    output <<= 1;
    /* SCLK = 0 */
    CLEARBIT(GPIOA->ODR, SCLK);
    Delay(125);
    if (GPIOA->IDR & SDO) output++;
    /* SCLK = 1 */
    SETBIT(GPIOA->ODR, SCLK);
    Delay(125);
  }
  
  SETBIT(GPIOE->ODR, CS);
}

void GetData(uint8_t address)
{
  axis.output = 0;
  while (address >= OUT_X_L)
  {
    Read(address);
    axis.output |= output;
    if (address-- > OUT_X_L)
      axis.output <<= 8;
  }
}

void Delay(uint16_t time) { for (; time > 0; time--) ; }