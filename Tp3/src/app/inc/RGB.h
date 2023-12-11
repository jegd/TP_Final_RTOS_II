/*
 * RGB.h
 *
 *  Created on: Dec 10, 2023
 *      Author: Jesus
 */

#ifndef APP_INC_RGB_H_
#define APP_INC_RGB_H_

#include "stm32f4xx_hal.h"
#include "cmsis_os.h"
#include "stdbool.h"
typedef enum {
	RED_,
	GREEN_,
	BLUE_
}leds_RGB_t;
typedef enum{
	OFF_ =0,
	ON_
}state_led;

typedef struct {
	state_led state_led;
	leds_RGB_t color;
	GPIO_TypeDef* GPIO_led;
	uint16_t GPIO_PIN_led;
} led_t;

typedef enum {
	OFF,
	ON,
	BLINK
}state_t;

typedef enum {
	RED,
	GREEN,
	BLUE,
	YELLOW,
	PURPLE,
	CIAN,
	WHITE
}color_t;

typedef struct{
	led_t* LED_RED_RGB;
	led_t* LED_GREEN_RGB;
	led_t* LED_BLUE_RGB;
	state_t	RGB_state;
	color_t RGB_color;
	bool task_blink;
	QueueHandle_t cola_led_RGB;
} RGB;


void RGB_GPIOs_init(void);
void RGB_change_state(state_t state);
void RGB_change_color(color_t color);

#endif /* APP_INC_RGB_H_ */
