#include <stdint.h>
#include "system_stm32f3xx.h"
#include "stm32f303xc.h"

#include "tim.h"
#include "gpio.h"
#include "gyro.h"

uint32_t frequency;

int main()
{
  SystemInit();
  SystemCoreClockUpdate();
  
  GPIO_Init();
  TIM7_Init();
  
  if (Read(WHO_AM_I) == 0xD3) {
    /* power mode - normal, x, y, z are enable */
    Write(CTRL_REG1, 0x3F);
    /* interrupt enable on INT2 */
    Write(CTRL_REG3, 0x08);
    /* Full scale selection FS = 2000 dps */
    Write(CTRL_REG4, 0x30);
    
    GetData(OUT_Z_H);
  }
  
  while(1) {}
}
