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
#include "RGB.h"

xTaskHandle Task_Leds_RGB;

// ------ internal data definition -------------------------------------
//Texto de inicialización
const char *pcTextForMain = "*******RTOS II TP3 is running******* \r\n"
		                    "- Anthony  Maisincho              N°SIU e2011 \r\n"
		                    "- Jesus    Gonzales               N°SIU e2006\r\n";
//Inicia las tareas de los OA


void vTask_Leds_RGB(void *argument)
{

	RGB_GPIOs_init();
	RGB_change_state(ON);
	RGB_change_color(RED);
	RGB_change_state(ON);
	RGB_change_color(BLUE);
	RGB_change_color(GREEN);
	RGB_change_state(BLINK);
	//RGB_change_state(ON);
	vTaskDelay(10000);
	RGB_change_state(ON);
	RGB_change_color(BLUE);
	while(1)
	{

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
			ret = xTaskCreate(vTask_Leds_RGB, /* Pointer to the function thats implement the task. */
			"vTask_Leds_RGB", /* Text name for the task. This is to facilitate debugging only. */
			(2 * configMINIMAL_STACK_SIZE), /* Stack depth in words. 				*/
			NULL, /* We are not using the task parameter.		*/
			(tskIDLE_PRIORITY + 1UL), /* This task will run at priority 1. 		*/
			&Task_Leds_RGB); /* We are using a variable as task handle.	*/

			/* Check the task was created successfully. */
			configASSERT(ret == pdPASS);


			return;

}

