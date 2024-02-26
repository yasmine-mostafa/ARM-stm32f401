/*
 * LED_CFG.c
 *
 *  Created on: Feb 19, 2024
 *      Author: top one
 */

#include "Error.h"
#include "STD_Types.h"
#include "LED_CFG.h"
#include "LED.h"
#include "GPIO.h"

const LED_Config_t LEDS_Config[_LED_Num]=
{
		[LED_1]=
		{
				.Port=GPIO_PORTA,
				.Pin=GPIO_PIN0,
				.Connection = LED_FWD,
				.InitState= LED_OFF
		},
		[LED_2]=
		{
				.Port=GPIO_PORTA,
				.Pin=GPIO_PIN2,
				.Connection = LED_REV,
				.InitState= LED_OFF
		}
};
