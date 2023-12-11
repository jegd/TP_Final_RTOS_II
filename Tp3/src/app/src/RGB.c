/*
 * RGB.c
 *
 *  Created on: Dec 10, 2023
 *      Author: Jesus
 */

#include "RGB.h"

#define CHANGE_LED_STATE(port,pin,state) HAL_GPIO_WritePin(port,pin,state)
#define RGB_PORT 	GPIOB
#define PIN_RED		GPIO_PIN_14
#define PIN_GREEN	GPIO_PIN_0
#define PIN_BLUE	GPIO_PIN_7

#define QUEUE_BLINK_LENGHT 1


//#define PUERTO_LED (led_t->GPIO_led)
led_t array_RGB[]={{color: BLUE_, GPIO_led: RGB_PORT,GPIO_PIN_led: PIN_BLUE,state_led: OFF_},
				   {color: RED_, GPIO_led: RGB_PORT,GPIO_PIN_led: PIN_RED,state_led: OFF_},
				   {color: GREEN_, GPIO_led: RGB_PORT,GPIO_PIN_led: PIN_GREEN,state_led: OFF_}};

led_t led_green, led_red, led_blue;
RGB led_RGB_1;
QueueHandle_t queue_blink;


void change_state(led_t * led)
{
	CHANGE_LED_STATE(led->GPIO_led,led->GPIO_PIN_led,led->state_led);
}

void RGB_GPIOs_init(void)
{
	led_RGB_1.LED_BLUE_RGB=&array_RGB[0];
	led_RGB_1.LED_RED_RGB=&array_RGB[1];
	led_RGB_1.LED_GREEN_RGB=&array_RGB[2];
	led_RGB_1.RGB_state=OFF;
	led_RGB_1.RGB_color=WHITE;
	led_RGB_1.task_blink=0;
	led_RGB_1.cola_led_RGB=queue_blink;
	/*Creación de colas*/
	queue_blink = xQueueCreate(QUEUE_BLINK_LENGHT,sizeof(RGB *));

	/* Check the queues was created successfully */
	configASSERT( queue_blink != NULL );

	/* We want this queue to be viewable in a RTOS kernel aware debugger, so register it. */
	vQueueAddToRegistry( queue_blink, "queue_blink" );
}

void update_color_RGB(RGB* led_RGB)
{
	switch(led_RGB->RGB_color)
		{
		case RED:
			led_RGB->LED_RED_RGB->state_led=ON_;
			led_RGB->LED_BLUE_RGB->state_led=OFF_;
			led_RGB->LED_GREEN_RGB->state_led=OFF_;
				break;
		case BLUE:
			led_RGB->LED_RED_RGB->state_led=OFF_;
			led_RGB->LED_BLUE_RGB->state_led=ON_;
			led_RGB->LED_GREEN_RGB->state_led=OFF_;
				break;
		case GREEN:
			led_RGB->LED_RED_RGB->state_led=OFF_;
			led_RGB->LED_BLUE_RGB->state_led=OFF_;
			led_RGB->LED_GREEN_RGB->state_led=ON_;
				break;
		case YELLOW:
			led_RGB->LED_RED_RGB->state_led=ON_;
			led_RGB->LED_BLUE_RGB->state_led=OFF_;
			led_RGB->LED_GREEN_RGB->state_led=ON_;
				break;
		case PURPLE:
			led_RGB->LED_RED_RGB->state_led=ON_;
			led_RGB->LED_BLUE_RGB->state_led=ON_;
			led_RGB->LED_GREEN_RGB->state_led=OFF_;
				break;
		case CIAN:
			led_RGB->LED_RED_RGB->state_led=OFF_;
			led_RGB->LED_BLUE_RGB->state_led=ON_;
			led_RGB->LED_GREEN_RGB->state_led=ON_;
				break;
		case WHITE:
			led_RGB->LED_RED_RGB->state_led=ON_;
			led_RGB->LED_BLUE_RGB->state_led=ON_;
			led_RGB->LED_GREEN_RGB->state_led=ON_;
				break;
		default:
			break;
		}
	change_state(led_RGB->LED_RED_RGB);
	change_state(led_RGB->LED_BLUE_RGB);
	change_state(led_RGB->LED_GREEN_RGB);
}

void turn_off_all(RGB* led_RGB)
{
	led_RGB->LED_RED_RGB->state_led=OFF_;
	led_RGB->LED_BLUE_RGB->state_led=OFF_;
	led_RGB->LED_GREEN_RGB->state_led=OFF_;
	change_state(led_RGB->LED_RED_RGB);
	change_state(led_RGB->LED_BLUE_RGB);
	change_state(led_RGB->LED_GREEN_RGB);
}

void blink_mode(RGB* led_RGB)
{
	switch(led_RGB->RGB_color)
	{
	case RED:
		led_RGB->LED_RED_RGB->state_led=!(led_RGB->LED_RED_RGB->state_led);
			break;
	case BLUE:
		led_RGB->LED_BLUE_RGB->state_led=!(led_RGB->LED_BLUE_RGB->state_led);
			break;
	case GREEN:
		led_RGB->LED_GREEN_RGB->state_led=!(led_RGB->LED_GREEN_RGB->state_led);
			break;
	case YELLOW:
		led_RGB->LED_RED_RGB->state_led=!(led_RGB->LED_RED_RGB->state_led);
		led_RGB->LED_GREEN_RGB->state_led=!(led_RGB->LED_GREEN_RGB->state_led);
			break;
	case PURPLE:
		led_RGB->LED_RED_RGB->state_led=!(led_RGB->LED_RED_RGB->state_led);
		led_RGB->LED_BLUE_RGB->state_led=!(led_RGB->LED_BLUE_RGB->state_led);
			break;
	case CIAN:
		led_RGB->LED_BLUE_RGB->state_led=!(led_RGB->LED_BLUE_RGB->state_led);
		led_RGB->LED_GREEN_RGB->state_led=!(led_RGB->LED_GREEN_RGB->state_led);
			break;
	case WHITE:
		led_RGB->LED_RED_RGB->state_led=!(led_RGB->LED_RED_RGB->state_led);
		led_RGB->LED_BLUE_RGB->state_led=!(led_RGB->LED_BLUE_RGB->state_led);
		led_RGB->LED_GREEN_RGB->state_led=!(led_RGB->LED_GREEN_RGB->state_led);
			break;
	default:
		break;
	}
	change_state(led_RGB->LED_RED_RGB);
	change_state(led_RGB->LED_BLUE_RGB);
	change_state(led_RGB->LED_GREEN_RGB);
}
static void task_delete_(void) {
	led_RGB_1.task_blink=0;
	vTaskDelete(NULL);
}
void task_(void *argument)
{
	RGB* led_RGB;
	do
	{	if(pdPASS == xQueueReceive(queue_blink,&led_RGB , 0))
		{

		}
		blink_mode(led_RGB);
		vTaskDelay(1000);
	}while(led_RGB->RGB_state==BLINK);
	task_delete_();
}

static bool task_create_(RGB* led_RGB) {
	if (led_RGB_1.task_blink==0)
	{
		led_RGB_1.task_blink=1;
		BaseType_t status;
		status = xTaskCreate(task_, "task_blink", 128, (void*)led_RGB,
				tskIDLE_PRIORITY + 1UL, NULL);
		while (pdPASS != status)
		{
			// error
		}
		return true;
	}
	else
	{
		return false;
	}
}
void update_state_RGB(RGB* led_RGB)
{
	switch(led_RGB->RGB_state)
	{
	case ON:
		update_color_RGB(led_RGB);
		break;
	case OFF:
		turn_off_all(led_RGB);
		break;
	case BLINK:
		if (pdPASS== xQueueSend(queue_blink,&led_RGB, 0))
		{

		}
		if(!task_create_(led_RGB))
		{
			//task blink already created
		}
		break;
	default:
		break;
	}
}

void RGB_change_color(color_t color)
{
	led_RGB_1.RGB_color=color;
	update_state_RGB(&led_RGB_1);
}

void RGB_change_state(state_t state)
{
	led_RGB_1.RGB_state=state;
	update_state_RGB(&led_RGB_1);
}





