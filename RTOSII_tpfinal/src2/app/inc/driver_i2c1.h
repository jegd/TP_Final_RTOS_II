/*
 * driver_i2c1.h
 *
 *  Created on: Dec 8, 2023
 *      Author: Jesus
 */

#ifndef APP_INC_DRIVER_I2C1_H_
#define APP_INC_DRIVER_I2C1_H_

#include <stdbool.h>
#include <stdint.h>
#include "stm32f4xx_hal.h"

#define scan_address_length     30
#define trial_scan               3
#define timeout_scan            10
#define timeout_transmit       100
#define max_slave              128
#define desplazamiento_7_bits    1
#define one_byte                 1


void gpio_i2c_config(void);
bool i2c_init(void);
void i2c_error_callback(void);
void scan_address(void);
void transmit_i2c(I2C_HandleTypeDef hi2c,uint16_t address,uint8_t *pstring);
bool i2c_enviar(uint8_t * buffer,size_t size, uint16_t address);




#endif /* APP_INC_DRIVER_I2C1_H_ */
