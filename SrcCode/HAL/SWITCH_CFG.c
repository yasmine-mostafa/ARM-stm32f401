/*
 * SWITCH_CFG.c
 *
 *  Created on: Feb 26, 2024
 *      Author:Yasmine Mostafa
 */

#include "STD_Types.h"
#include "Error.h"
#include "GPIO.h"
#include "SWITCH_CFG.h"
#include "SWITCH.h"


const SWITCH_Config_t SWITCHES_Config[_SWITCH_NUM]=
{
		[SWITCH_1]=
		{
				.Port=GPIO_PORTB,
				.Pin=GPIO_PIN0,
				.Connection=CONNECTION_PULL_UP
		},

		[SWITCH_2]=
		{
				.Port=GPIO_PORTB,
				.Pin=GPIO_PIN2,
				.Connection=CONNECTION_PULL_DOWN
		}
};
