/*
 * LED_CFG.c
 *
 *  Created on: Feb 19, 2024
 *      Author: Yasmine Mostafa
 */

#include "Error.h"
#include "STD_Types.h"
#include "LED_CFG.h"
#include "LED.h"
#include "GPIO.h"

const LED_Config_t LEDS_Config[_LED_Num]=
{
		[LED_Green]=
		{
				.Port=GPIO_PORTA,
				.Pin=GPIO_PIN0,
				.Connection = LED_FWD,
				.InitState= LED_OFF
		},
		[LED_Yellow]=
		{
				.Port=GPIO_PORTA,
				.Pin=GPIO_PIN2,
				.Connection = LED_FWD,
				.InitState= LED_OFF
		},
		[LED_Red]=
		{
				.Port=GPIO_PORTA,
				.Pin=GPIO_PIN3,
				.Connection = LED_FWD,
				.InitState= LED_OFF
		}
};
