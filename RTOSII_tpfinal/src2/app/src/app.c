#include "main.h"
#include "cmsis_os.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "app.h"
#include "driver.h"
#include "supporting_Functions.h"
#include "eboard.h"
#include "driver_i2c1.h"

xTaskHandle Task_Alarma_Handle;
extern I2C_HandleTypeDef hi2c1;

QueueHandle_t QueueLEDS;
// ------ internal data definition -------------------------------------
//Texto de inicialización
const char *pcTextForMain = "*******RTOS II TP Final is running******* \r\n"
		                    "- Anthony  Maisincho              N°SIU e2011 \r\n"
		                    "- Jesus    Gonzales               N°SIU e2006\r\n";
//Inicia las tareas de los OA


void vTask_Alarma(void *argument)
{


	while(1)
	{

		  FSM_update(); //Actualiza la maquina de estado
		  void FSM_update(void)
		  {
		  	switch(estado_actual)
		  	{
		  	case DESARMADO_OK:
		  		enviar_msg_terminal((uint8_t *)"ESTADO ACTUAL: Desarmado_ok \r\n");
		  		CLEAR_LCD();
		  		LCD_XY(LCD_LINEA1,POS_1);
		  		STRING_LCD((uint8_t *)"Ingrese PIN: ");
		  		contador=0;
		  		uint8_t *ptro_teclado=clave_ingresada;
		  		LCD_XY(LCD_LINEA2,POS_4);
		  		while(contador < PIN_SIZE)
		  		{
		  			tecla=keypad_read();

		  			if(tecla != '\0')
		  			{
		  				*ptro_teclado = tecla;
		  				contador++;
		  				ptro_teclado++;
		  				STRING_LCD((uint8_t *)"*");

		  			}
		  		}
		  		*ptro_teclado= '\0';
		  		enviar_msg_terminal((uint8_t *)"Clave Ingresada: ");
		  		enviar_msg_terminal((uint8_t *)clave_ingresada);
		  		enviar_msg_terminal((uint8_t *)"\r\n");
		  		//Condicion de transicion, si la clave es correcta, se pasa al estado ARMANDO
		  		if (strcmp((const char *)clave_ingresada,(const char *) clave) == 0)
		  		{
		  			enviar_msg_terminal((uint8_t *)"Clave correcta \r\n");
		  			CLEAR_LCD();
		  			LCD_XY(LCD_LINEA1,POS_1);
		  			STRING_LCD((uint8_t *)"Clave correcta");
		  			start_time = HAL_GetTick();//Actualizacion de tiempo
		  			while (HAL_GetTick() - start_time < TIEMPO_TRANSITION) {}; //No bloqueante
		  			estado_actual=ARMANDO;

		  		}
		  		else
		  		{
		  			enviar_msg_terminal((uint8_t *)"Clave Incorrecta \r\n");
		  			CLEAR_LCD();
		  			LCD_XY(LCD_LINEA1,POS_0);
		  			STRING_LCD((uint8_t *)"Clave incorrecta");
		  			start_time = HAL_GetTick();//Actualizacion de tiempo
		  			while (HAL_GetTick() - start_time < TIEMPO_TRANSITION) {}; //No bloqueante
		  			estado_actual=DESARMADO_OK;
		  		}
		  		break;
		  	case ARMANDO:
		  		enviar_msg_terminal((uint8_t *)"ARMANDO ALARMA...\r\n");
		  		CLEAR_LCD();
		  		for(uint8_t i=0 ; i < TIEMPO_GUARDA; i++)
		  		{
		  			uint8_t tiempo_temp=TIEMPO_GUARDA-i; //Actualizacion de la variable i que lleva el numero de iteracion
		  			int_to_ascii(tiempo_temp,ascii_format);// Conversion a formato ascii
		  			uint32_t start_time = HAL_GetTick();//Actualizacion de tiempo
		  			while (HAL_GetTick() - start_time < one_second) {
		  				LCD_XY(LCD_LINEA1,POS_0);
		  				STRING_LCD((uint8_t *)"Tiempo de armado: ");
		  				LCD_XY(LCD_LINEA2,POS_5);
		  				STRING_LCD((uint8_t *)ascii_format);
		  			};
		  		}
		  		//Luego del tiempo de guarda se pasa al estado ARMADO_OK
		  		estado_actual=ARMADO_OK;
		  		start_time = HAL_GetTick();//Actualizacion de tiempo
		  		while (HAL_GetTick() - start_time < TIEMPO_TRANSITION)
		  		{
		  			enviar_msg_terminal((uint8_t *)"ALARMA ARMADA...\r\n");
		  		}
		  		break;
		  	case ARMADO_OK:
		  		enviar_msg_terminal((uint8_t *)"ESTADO ACTUAL: ARMADO_OK \r\n");
		  		CLEAR_LCD();
		  		LCD_XY(LCD_LINEA1,POS_0);
		  		STRING_LCD((uint8_t *)"Alarma ON");
		  		//Condicion de transicion es la lectura del sensor de presencia
		  		if(detectar_presencia())
		  		{
		  			enviar_msg_terminal((uint8_t *)"Se ha detectado una persona...\r\n");
		  			CLEAR_LCD();
		  			LCD_XY(LCD_LINEA1,POS_0);
		  			STRING_LCD((uint8_t *)"PRESENCIA: ON");
		  			estado_actual=DESARMANDO;
		  		}
		  		else
		  		{
		  			CLEAR_LCD();
		  			LCD_XY(LCD_LINEA1,POS_0);
		  			STRING_LCD((uint8_t *)"PRESENCIA: OFF");
		  		}
		  		start_time = HAL_GetTick();//Actualizacion de tiempo
		  		while (HAL_GetTick() - start_time < one_second){};
		  		break;

		  	case DESARMANDO:
		  		start_time= HAL_GetTick();
		  		while (HAL_GetTick() - start_time < one_second)
		  		{
		  			enviar_msg_terminal((uint8_t *)"Posible Intruso...\r\n");
		  		}
		  		CLEAR_LCD();
		  		LCD_XY(LCD_LINEA1,POS_1);
		  		STRING_LCD((uint8_t *)"Identifiquese: ");
		  		contador=0;
		  		uint8_t *ptro_desbloqueo=clave_ingresada;
		  		LCD_XY(LCD_LINEA2,POS_4);
		  		start_time= HAL_GetTick();
		  		//Si se ingresa correctamente la clave en menos del tiempo de guarda no se activa el estado INTRUSO
		  		while(contador < PIN_SIZE && (HAL_GetTick() - start_time < TIEMPO_IDENTIFICACION) ) //Condicion donde se valida el tiempo de guarda y si se ingresa PIN correcto
		  		{
		  			tecla=keypad_read();

		  			if(tecla!= '\0')
		  			{
		  				*ptro_desbloqueo = tecla;
		  				contador++;
		  				ptro_desbloqueo++;
		  				STRING_LCD((uint8_t *)"*");

		  			}
		  		}
		  		*ptro_desbloqueo= '\0';
		  		enviar_msg_terminal((uint8_t *)"Clave Ingresada: ");
		  		enviar_msg_terminal((uint8_t *)clave_ingresada);
		  		enviar_msg_terminal((uint8_t *)"\r\n");


		  		if (strcmp((const char *)clave_ingresada,(const char *) clave) == 0)
		  		{
		  			enviar_msg_terminal((uint8_t *)"Clave correcta \r\n");
		  			CLEAR_LCD();
		  			LCD_XY(LCD_LINEA1,POS_1);
		  			STRING_LCD((uint8_t *)"Alarma OFF");
		  			start_time = HAL_GetTick();//Actualizacion de tiempo
		  			while (HAL_GetTick() - start_time < TIEMPO_TRANSITION) {}; //No bloqueante
		  			estado_actual=DESARMADO_OK;

		  		}
		  		else
		  		{
		  			enviar_msg_terminal((uint8_t *)"Clave Incorrecta \r\n");
		  			CLEAR_LCD();
		  			LCD_XY(LCD_LINEA1,POS_2);
		  			STRING_LCD((uint8_t *)"INTRUSO!!!");
		  			start_time = HAL_GetTick();//Actualizacion de tiempo
		  			while (HAL_GetTick() - start_time < TIEMPO_TRANSITION) {}; //No bloqueante
		  			estado_actual=INTRUSO;
		  			tiempo_desarmado= HAL_GetTick();
		  		}


		  		break;
		  	case INTRUSO:
		  		enviar_msg_terminal((uint8_t *)"Estado Actual: Intruso...\r\n");
		  		if (HAL_GetTick() - tiempo_desarmado < tiempo_alarma)
		  		{
		  			alarma_on();
		  			HAL_Delay(250);
		  		}
		  		else
		  		{
		  			enviar_msg_terminal((uint8_t *)"Estado Actual: Volviendo al inicio...\r\n");
		  			estado_actual=DESARMADO_OK;
		  		}

		  		break;
		  	default:
		  		estado_actual=DESARMADO_OK;
		  		break;
		  	}
		  }

		vTaskDelay(100);
	}
}




	/* App Initialization */
void app_init( void ){
		  	vPrintString( pcTextForMain );
		    // drivers
		    {
		      eboard_init();
		    }

			BaseType_t ret;

			/* Task Alarma thread at priority 2 */
			ret = xTaskCreate(vTask_Alarma, /* Pointer to the function thats implement the task. */
			"vTask_Alarma", /* Text name for the task. This is to facilitate debugging only. */
			(2 * configMINIMAL_STACK_SIZE), /* Stack depth in words. 				*/
			NULL, /* We are not using the task parameter.		*/
			(tskIDLE_PRIORITY + 1UL), /* This task will run at priority 1. 		*/
			&Task_Alarma_Handle); /* We are using a variable as task handle.	*/

			/* Check the task was created successfully. */
			configASSERT(ret == pdPASS);


			return;

}

