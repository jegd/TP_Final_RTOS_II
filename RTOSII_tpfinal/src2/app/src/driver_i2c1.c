/** @file driver_i2c1.c
 *  @Created on: Dic 08, 2023
 *  @Authors:  Anthony  Maisincho              N°SIU e2011
 *             Jesus    Gonzales               N°SIU e2006
 *
 *  @brief Driver de manejo de I2C
 *
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

//Defines de la OSAL
#define ENTER_CRITICAL_()	taskENTER_CRITICAL()
#define EXIT_CRITICAL_()	taskEXIT_CRITICAL()



#define scan_address_length     30
#define trial_scan               3
#define timeout_scan            10
#define timeout_transmit       100
#define max_slave              128
#define desplazamiento_7_bits    1
#define one_byte                 1


typedef struct {
	uint8_t buffer[I2C_BUFFER_SIZE];
	size_t len;
	bool enable;
	bool error;
} i2c_tx_t;

static i2c_tx_t i2c_tx;

extern I2C_HandleTypeDef hi2c1;


/*!
 * @brief Callback del error I2C.
 *
 * @param[I2C_HandleTypeDef] Handle del I2C
 *
 * @return Función del tipo void.
 */
void Hal_i2c_errorCallback(I2C_HandleTypeDef *hi2c) {
	i2c_error_callback();
}
/*!
 * @brief Callback de finalización de transmisión I2C
 *
 * @param[I2C_HandleTypeDef] Handle del I2C
 *
 * @return Función del tipo void.
 */
void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *hi2c) {
	i2c_tx.enable = true;
}
/*!
 * @brief Función para declarar por el usuario y manejar errores
 *
 * @param[void]
 *
 * @return Función del tipo void.
 */
__weak void i2c_error_callback(void) {
	return;
}
/*!
 * @brief Copia el buffer de usuario a un buffer del driver
 *
 * @param[uint8_t *] buffer		Puntero al buffer a transmitir
 * @param[size_t]	size		Tamaño de lo que se quiere transmitir
 *
 * @return bool true si es que se envió correctamente
 */
bool cambiar_buffer(uint8_t *buffer, size_t size) {
	ENTER_CRITICAL_();
	i2c_tx.len=0;
	if(i2c_tx.enable == 1 && size > 0 && size<I2C_BUFFER_SIZE && i2c_tx.error != 1)
	{
		for(uint8_t i=0;i<size;i++)
		{
			i2c_tx.buffer[i]=*buffer;
			i2c_tx.len++;
			buffer++;
			return 0;
		}
	}
	EXIT_CRITICAL_();
	return 1;
}

/*!
 * @brief Función para declarar por el usuario y manejar errores
 *
 * @param[uint8_t *] buffer		Puntero al buffer a transmitir
 * @param[size_t]	size		Tamaño de lo que se quiere transmitir
 * @param[uint16_t] 	address	Dirección I2C
 *
 * @return bool true si es que se envió correctamente
 */
bool i2c_enviar(uint8_t *buffer, size_t size, uint16_t address) {
	if (NULL == buffer)
		i2c_error_callback();

	if(!cambiar_buffer(buffer,size))
		i2c_error_callback();

	ENTER_CRITICAL_();
	if (i2c_tx.len <= I2C_BUFFER_SIZE && i2c_tx.enable == 1 && size > 0) {
		HAL_StatusTypeDef status = HAL_I2C_Master_Transmit_IT(I2C_HAL_HANDLE_,
				address, i2c_tx.buffer, size);
		EXIT_CRITICAL_();
		switch (status) {
		case HAL_OK:
			i2c_tx.enable=false;
			break;
		case HAL_ERROR:
			i2c_error_callback();
		case HAL_BUSY:
			break;
		case HAL_TIMEOUT:
			break;
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
/*!
 * @brief Escanea las direcciones de I2C
 *
 * @param[void]
 *
 * @return uint16_t Direccion escaneada
 */
uint16_t scan_adress(void) {
	uint8_t address;
	for (address = 0; address < max_slave; address++) {
		ENTER_CRITICAL_();
		HAL_StatusTypeDef ack = HAL_I2C_IsDeviceReady(I2C_HAL_HANDLE_,
				address << desplazamiento_7_bits, trial_scan, timeout_scan); //Al enviarse 8 bits siempre, y la direccion es de 7, se hace desplazamiento de 1 a la izquierda
		switch (ack) {
		case HAL_OK:
			break;
		case HAL_ERROR:
			i2c_error_callback();
		case HAL_BUSY:
			break;
		case HAL_TIMEOUT:
			break;
		default:
			i2c_error_callback();
			break;
		}

	}
	EXIT_CRITICAL_();
	return address;
}
