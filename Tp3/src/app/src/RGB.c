/** @file RGB.c
 *  @Created on: Dic 11, 2023
 *  @Authors:  Anthony  Maisincho              N°SIU e2011
 *             Jesus    Gonzales               N°SIU e2006
 *
 *  @brief RGB driver
 *
 */
/***************************************INCLUDES***************************************/
#include "RGB.h"
/***************************************HAL DEFINES***************************************/
#define CHANGE_LED_STATE(port,pin,state) HAL_GPIO_WritePin(port,pin,state)
#define RGB_PORT 	GPIOB
#define PIN_RED		GPIO_PIN_14
#define PIN_GREEN	GPIO_PIN_0
#define PIN_BLUE	GPIO_PIN_7
#define DELAY_BLINK_MS	500
/***************************************OSAL DEFINES***************************************/
#define QUEUE_BLINK_LENGTH 1
#define CREATE_QUEUE(LENGTH,SIZE)	xQueueCreate(LENGTH,SIZE)
#define CONFIG_ASSERT(TO_ASSERT)	configASSERT(TO_ASSERT)
#define ADD_QUEUE_REGISTRY(HANDLE,NAME)	vQueueAddToRegistry(HANDLE,NAME)
#define DELETE_TASK(HANDLE)	vTaskDelete(HANDLE)
#define CREATE_TASK(POINTER,NAME,STACK,ARGUMENT,PRIORITY,HANDLE)	xTaskCreate(POINTER,NAME,STACK,ARGUMENT,PRIORITY,HANDLE)
#define PRIORITY_IDLE	tskIDLE_PRIORITY
#define SEND_TO_QUEUE(HANDLE,POINTER,TIMEOUT)	xQueueSend(HANDLE,POINTER,TIMEOUT)
#define RECEIVE_QUEUE(HANDLE,POINTER,TIMEOUT)	xQueueReceive(HANDLE,POINTER,TIMEOUT)
#define DELAY_TASK(TICKS)	vTaskDelay(TICKS)
#define ENTER_CRITICAL_()	taskENTER_CRITICAL()
#define EXIT_CRITICAL_()	taskEXIT_CRITICAL()
/***************************************PRIVATE VARIABLES***************************************/
static led_t array_RGB[]={{color: BLUE_, GPIO_led: RGB_PORT,GPIO_PIN_led: PIN_BLUE,state_led: OFF_},
				   {color: RED_, GPIO_led: RGB_PORT,GPIO_PIN_led: PIN_RED,state_led: OFF_},
				   {color: GREEN_, GPIO_led: RGB_PORT,GPIO_PIN_led: PIN_GREEN,state_led: OFF_}};
static RGB led_RGB_1;
static QueueHandle_t queue_blink;
/***************************************PRIVATE FUNCTIONS***************************************/
/*!
 * @brief Change the state of the RGB led
 *
 * @param[led_t * ] led  Pointer to the led, one of the three from a RGB led
 *
 * @return nothing
 */
static void change_state(led_t * led)
{
	CHANGE_LED_STATE(led->GPIO_led,led->GPIO_PIN_led,led->state_led);
}
/*!
 * @brief Update the color of the RGB led
 *
 * @param[RGB*] led_RGB	 Pointer to the RGb led structure
 *
 * @return nothing
 */
static void update_color_RGB(RGB* led_RGB)
{
	ENTER_CRITICAL_();
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
	EXIT_CRITICAL_();
}
/*!
 * @brief Turn off the RGB led
 *
 * @param[RGB*] led_RGB	 Pointer to the RGb led structure
 *
 * @return nothing
 */
static void turn_off_all(RGB* led_RGB)
{
	ENTER_CRITICAL_();
	led_RGB->LED_RED_RGB->state_led=OFF_;
	led_RGB->LED_BLUE_RGB->state_led=OFF_;
	led_RGB->LED_GREEN_RGB->state_led=OFF_;
	change_state(led_RGB->LED_RED_RGB);
	change_state(led_RGB->LED_BLUE_RGB);
	change_state(led_RGB->LED_GREEN_RGB);
	EXIT_CRITICAL_();
}
/*!
 * @brief Toggle the state of the RGB led
 *
 * @param[RGB*] led_RGB	 Pointer to the RGb led structure
 *
 * @return nothing
 */
static void blink_mode(RGB* led_RGB)
{
	ENTER_CRITICAL_();
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
	EXIT_CRITICAL_();
}
/*!
 * @brief Eliminate the task
 *
 *
 * @return nothing
 */
static void task_delete_(void) {
	led_RGB_1.task_blink=0;
	DELETE_TASK(NULL);
}
static void task_(void *argument)
{
	RGB* led_RGB;
	do
	{	if(pdPASS != RECEIVE_QUEUE(queue_blink,&led_RGB , 0))
		{
			//error
		}
		blink_mode(led_RGB);
		DELAY_TASK(DELAY_BLINK_MS);
	}while(led_RGB->RGB_state==BLINK);
	task_delete_();
}
/*!
 * @brief Create the blink task
 *
 * @param[RGB*] led_RGB	 Pointer to the RGb led structure
 *
 * @return bool if the task was created or not
 */
static bool task_create_(RGB* led_RGB) {
	if (led_RGB_1.task_blink==0)
	{
		led_RGB_1.task_blink=1;
		BaseType_t status;
		status = CREATE_TASK(task_, "task_blink", 128, (void*)led_RGB,
				PRIORITY_IDLE + 1UL, NULL);
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
/*!
 * @brief Update the RGB led state
 *
 * @param[RGB*] led_RGB	 Pointer to the RGb led structure
 *
 * @return nothing
 */
static void update_state_RGB(RGB* led_RGB)
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
		if (pdPASS!= SEND_TO_QUEUE(queue_blink,&led_RGB, 0))
		{
			//error
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
/***************************************GLOBAL FUNCTIONS***************************************/
/*!
 * @brief Initiate the RGB led
 *
 *
 * @return nothing
 */
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
	queue_blink = CREATE_QUEUE(QUEUE_BLINK_LENGTH,sizeof(RGB *));

	/* Check the queues was created successfully */
	CONFIG_ASSERT( queue_blink != NULL );

	/* We want this queue to be viewable in a RTOS kernel aware debugger, so register it. */
	ADD_QUEUE_REGISTRY(queue_blink, "queue_blink" );
}
/*!
 * @brief Change the color of the RGB led
 *
 * @param[color_t] color	Color of the RGB
 *
 * @return nothing
 */
void RGB_change_color(color_t color)
{
	led_RGB_1.RGB_color=color;
	update_state_RGB(&led_RGB_1);
}
/*!
 * @brief Change the state of the RGB led
 *
 * @param[state_t] state	State of the RGB
 *
 * @return nothing
 */
void RGB_change_state(state_t state)
{
	led_RGB_1.RGB_state=state;
	update_state_RGB(&led_RGB_1);
}
