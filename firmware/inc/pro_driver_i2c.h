#ifndef PRO_DRIVER_I2C_H
#define PRO_DRIVER_I2C_H

#include "stdbool.h"
#include "stdint.h"

void init_raspberry_i2c();

void i2c_raspberry_start();

bool i2c_raspberry_addr(uint8_t addr, uint8_t timeout);

void i2c_raspberry_data(uint8_t data);

void i2c_raspberry_stop();
#endif
