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

	char * palabra = "hoala";


	while(1)
	{

		i2c_enviar((uint8_t *)palabra,(size_t)4,(uint16_t)0x30);

		vTaskDelay(1000);
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

