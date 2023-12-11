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
xTaskHandle Task_Leds_RGB_2;
xTaskHandle Task_Leds_RGB_3;
xTaskHandle Task_dia;

color_t color_day[]={GREEN,YELLOW,WHITE};
state_t	state_day[]={ON,BLINK,OFF};
char * day[]={"good","so good","bad"};
char * today;


// ------ internal data definition -------------------------------------
//Texto de inicialización
const char *pcTextForMain = "*******RTOS II TP3 is running******* \r\n"
		                    "- Anthony  Maisincho              N°SIU e2011 \r\n"
		                    "- Jesus    Gonzales               N°SIU e2006\r\n";
/*!
 * @brief Task that evaluates wich day is today
 *
 * @return nothing
 */
void vTask_Leds_RGB(void *argument)
{

	RGB_GPIOs_init();
	while(1)
	{
		if(today==day[0])
		{
			RGB_change_color(color_day[0]);
			RGB_change_state(state_day[0]);
		}
		vTaskDelay(10);
	}
}
/*!
 * @brief Task that evaluates wich day is today
 *
 * @return nothing
 */
void vTask_Leds_RGB_2(void *argument)
{
	while(1)
	{
		if(today==day[1])
			{
				RGB_change_color(color_day[1]);
				RGB_change_state(state_day[1]);
			}
			vTaskDelay(10);
	}
}
/*!
 * @brief Task that evaluates wich day is today
 *
 * @return nothing
 */
void vTask_Leds_RGB_3(void *argument)
{

	while(1)
	{
		if(today==day[2])
			{
				RGB_change_color(color_day[2]);
				RGB_change_state(state_day[2]);
			}
			vTaskDelay(10);
	}
}
/*!
 * @brief Task that simulates sensing how is the day
 *
 * @return nothing
 */
void vTask_dia(void *argument)
{

	while(1)
	{
		for(uint8_t i=0;i<3;i++)
		{
			today=day[i];
			vTaskDelay(30000);
		}

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

			/* Task vTask_Leds_RGB thread at priority 2 */
			ret = xTaskCreate(vTask_Leds_RGB, /* Pointer to the function thats implement the task. */
			"vTask_Leds_RGB", /* Text name for the task. This is to facilitate debugging only. */
			(2 * configMINIMAL_STACK_SIZE), /* Stack depth in words. 				*/
			NULL, /* We are not using the task parameter.		*/
			(tskIDLE_PRIORITY + 1UL), /* This task will run at priority 1. 		*/
			&Task_Leds_RGB); /* We are using a variable as task handle.	*/

			/* Check the task was created successfully. */
			configASSERT(ret == pdPASS);

			/* Task vTask_Leds_RGB thread at priority 2 */
			ret = xTaskCreate(vTask_Leds_RGB_2, /* Pointer to the function thats implement the task. */
			"vTask_Leds_RGB_2", /* Text name for the task. This is to facilitate debugging only. */
			(2 * configMINIMAL_STACK_SIZE), /* Stack depth in words. 				*/
			NULL, /* We are not using the task parameter.		*/
			(tskIDLE_PRIORITY + 1UL), /* This task will run at priority 1. 		*/
			&Task_Leds_RGB_3); /* We are using a variable as task handle.	*/

			/* Check the task was created successfully. */
			configASSERT(ret == pdPASS);

			/* Task vTask_Leds_RGB thread at priority 2 */
			ret = xTaskCreate(vTask_Leds_RGB_3, /* Pointer to the function thats implement the task. */
			"vTask_Leds_RGB_3", /* Text name for the task. This is to facilitate debugging only. */
			(2 * configMINIMAL_STACK_SIZE), /* Stack depth in words. 				*/
			NULL, /* We are not using the task parameter.		*/
			(tskIDLE_PRIORITY + 1UL), /* This task will run at priority 1. 		*/
			&Task_Leds_RGB_3); /* We are using a variable as task handle.	*/

			/* Check the task was created successfully. */
			configASSERT(ret == pdPASS);

			/* Task dia thread at priority 2 */
			ret = xTaskCreate(vTask_dia, /* Pointer to the function thats implement the task. */
			"Task_dia", /* Text name for the task. This is to facilitate debugging only. */
			(2 * configMINIMAL_STACK_SIZE), /* Stack depth in words. 				*/
			NULL, /* We are not using the task parameter.		*/
			(tskIDLE_PRIORITY + 1UL), /* This task will run at priority 1. 		*/
			&Task_dia); /* We are using a variable as task handle.	*/

			/* Check the task was created successfully. */
			configASSERT(ret == pdPASS);


			return;

}

