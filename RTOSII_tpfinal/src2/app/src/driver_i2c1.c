/*
 * driver_i2c1.c
 *
 *  Created on: Dec 8, 2023
 *      Author: Jesus
 */

#include "driver_i2c1.h"
#include "main.h"
#include "cmsis_os.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "app.h"
#include "driver.h"
#include "supporting_Functions.h"
//Defines de la HAL

#define HAL_I2C_INIT(PORT,I2C_GPIO_DEF) HAL_GPIO_Init(PORT,I2C_GPIO_DEF)
#define I2C_HANDLE_DEF 	I2C_HandleTypeDef
#define I2C_HAL_HANDLE_  (&hi2c1)  //por ver
#define I2C_BUFFER_SIZE (32)

#define scan_address_length     30
#define trial_scan               3
#define timeout_scan            10
#define timeout_transmit       100
#define max_slave              128
#define desplazamiento_7_bits    1
#define one_byte                 1

//Defines de la OSAL
#define ENTER_CRITICAL_()	taskENTER_CRITICAL()
#define EXIT_CRITICAL_()	taskEXIT_CRITICAL()

typedef struct {
	uint8_t buffer[I2C_BUFFER_SIZE];
	size_t len;
	bool enable;
	bool error;
} i2c_tx_t;

extern I2C_HandleTypeDef hi2c1;

static i2c_tx_t i2c_tx;
//static 	I2C_GPIO_DEF i2c_gpio;
bool flag = 1;

void Hal_i2c_errorCallback(I2C_HandleTypeDef *hi2c) {
	i2c_error_callback();
}

void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *hi2c) {
	flag = true;
}

__weak void i2c_error_callback(void) {
	return;

}
bool i2c_enviar(uint8_t *buffer, size_t size, uint16_t address) {
	if (NULL == buffer)
		i2c_error_callback();
	ENTER_CRITICAL_();
	if (size <= I2C_BUFFER_SIZE && flag == 1 && size > 0) {
		HAL_StatusTypeDef status = HAL_I2C_Master_Transmit_IT(I2C_HAL_HANDLE_,
				address, buffer, size);
		EXIT_CRITICAL_();
		switch (status) {
		case HAL_OK:
			flag = false;
			break;
		case HAL_ERROR:
			i2c_error_callback();
		case HAL_BUSY:
		case HAL_TIMEOUT:
		default:
			i2c_error_callback();
			break;
		}

	} else {
		EXIT_CRITICAL_();
		return false;
	}
	return true;
}
uint16_t scan_adress(void) {
	uint8_t address;
	for (address = 0; address < max_slave; address++) {
		ENTER_CRITICAL_();
		bool ack = HAL_I2C_IsDeviceReady(I2C_HAL_HANDLE_,
				address << desplazamiento_7_bits, trial_scan, timeout_scan); //Al enviarse 8 bits siempre, y la direccion es de 7, se hace desplazamiento de 1 a la izquierda
		if (ack == HAL_OK)
			EXIT_CRITICAL_();
	}
	return address;
}
