#ifndef GYRO_H
#define GYRO_H

#include "stm32f303xc.h"
#include "gpio.h"

/* L3GD20 register's addresses */
#define WHO_AM_I                        0x0F
#define CTRL_REG1                       0x20
#define CTRL_REG2                       0x21
#define CTRL_REG3                       0x22
#define CTRL_REG4                       0x23
#define CTRL_REG5                       0x24
#define REFERENCE                       0x25
#define OUT_TEMP                        0x26
#define STATUS_REG                      0x27
#define OUT_X_L                         0x28
#define OUT_X_H                         0x29
#define OUT_Y_L                         0x2A
#define OUT_Y_H                         0x2B
#define OUT_Z_L                         0x2C
#define OUT_Z_H                         0x2D
#define FIFO_CTRL_REG                   0x2E
#define FIFO_SRC_REG                    0x2F
#define INT1_CFG                        0x30
#define INT1_SRC                        0x31

extern float x_d, y_d, z_d;

typedef union 
{
  int64_t output;
  struct
  {
    int16_t x;
    int16_t y;
    int16_t z;
  };
} Axis;

extern Axis axis;

void Write(uint8_t address, uint8_t data);
uint8_t Read(uint8_t address);
void GetData(uint8_t address);
void Delay(uint16_t time);

#endif