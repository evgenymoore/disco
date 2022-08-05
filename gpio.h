#ifndef GPIO_H
#define GPIO_H

#include "stm32f303xc.h"

    /* GPIO port A pin configuration */

    /* SPI port & pin configurations */
#define SCLK                    ((uint16_t)0x0020)      /* PA5 */ 
#define SDI                     ((uint16_t)0x0080)      /* PA7 */       /* MOSI */
#define SDO                     ((uint16_t)0x0040)      /* PA6 */       /* MISO */
#define CS                      ((uint16_t)0x0008)      /* PE3 */
#define INT2                    ((uint16_t)0x0002)      /* PE1 */
#define INT1                    ((uint16_t)0x0001)      /* PE0 */

#define SETBIT(PORT, BIT)       PORT |=  BIT;
#define CLEARBIT(PORT, BIT)     PORT &= ~BIT;     
#define SWITCHBIT(PORT, BIT)    PORT ^=  BIT;

#define CLEARREG(REG)           REG   =  0;

void GPIO_Init(void);

#endif