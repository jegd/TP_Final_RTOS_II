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

//#define PUERTO_LED (led_t->GPIO_led)
led_t array_RGB[]={{color: BLUE_, GPIO_led: RGB_PORT,GPIO_PIN_led: PIN_BLUE,state_led: OFF_},
				   {color: RED_, GPIO_led: RGB_PORT,GPIO_PIN_led: PIN_RED,state_led: OFF_},
				   {color: GREEN_, GPIO_led: RGB_PORT,GPIO_PIN_led: PIN_GREEN,state_led: OFF_}};

led_t led_green, led_red, led_blue;
RGB led_RGB_1;

void change_state(led_t * led, bool state)
{
	CHANGE_LED_STATE(led->GPIO_led,led->GPIO_PIN_led,state);
}

void RGB_GPIOs_init(void)
{
	led_RGB_1.LED_BLUE_RGB=&array_RGB[0];
	led_RGB_1.LED_RED_RGB=&array_RGB[1];
	led_RGB_1.LED_GREEN_RGB=&array_RGB[2];
	led_RGB_1.RGB_state=OFF;
	led_RGB_1.RGB_color=WHITE;
}

void update_color_RGB(RGB* led_RGB)
{
	switch(led_RGB->RGB_color)
		{
		case RED:
			change_state(led_RGB->LED_RED_RGB,ON_);
			change_state(led_RGB->LED_BLUE_RGB,OFF_);
			change_state(led_RGB->LED_GREEN_RGB,OFF_);
				break;
		case BLUE:
			change_state(led_RGB->LED_RED_RGB,OFF_);
			change_state(led_RGB->LED_BLUE_RGB,ON_);
			change_state(led_RGB->LED_GREEN_RGB,OFF_);
				break;
		case GREEN:
			change_state(led_RGB->LED_RED_RGB,OFF_);
			change_state(led_RGB->LED_BLUE_RGB,OFF_);
			change_state(led_RGB->LED_GREEN_RGB,ON_);
				break;
		case YELLOW:
			change_state(led_RGB->LED_RED_RGB,ON_);
			change_state(led_RGB->LED_BLUE_RGB,OFF_);
			change_state(led_RGB->LED_GREEN_RGB,ON_);
				break;
		case PURPLE:
			change_state(led_RGB->LED_RED_RGB,ON_);
			change_state(led_RGB->LED_BLUE_RGB,ON_);
			change_state(led_RGB->LED_GREEN_RGB,OFF_);
				break;
		case CIAN:
			change_state(led_RGB->LED_RED_RGB,OFF_);
			change_state(led_RGB->LED_BLUE_RGB,ON_);
			change_state(led_RGB->LED_GREEN_RGB,ON_);
				break;
		case WHITE:
			change_state(led_RGB->LED_RED_RGB,ON_);
			change_state(led_RGB->LED_BLUE_RGB,ON_);
			change_state(led_RGB->LED_GREEN_RGB,ON_);
				break;
		default:
			break;
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
		break;
		change_state(led_RGB->LED_BLUE_RGB, OFF_);
		change_state(led_RGB->LED_BLUE_RGB, OFF_);
		change_state(led_RGB->LED_BLUE_RGB, OFF_);
	case BLINK:
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





