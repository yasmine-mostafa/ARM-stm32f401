/*
 * LCD_CFG.c
 *
 *  Created on: Apr 1, 2024
 *      Author: Yasmine Mostafa
 */
#include "STD_Types.h"
#include "Error.h"
#include "GPIO.h"
#include "LCD_CFG.h"
#include "LCD.h"

const LCD_Config_t LCD_Configs[_LCD_Num]=
{
		[D0]=
		{
				.Port = GPIO_PORTA,
				.Pin = GPIO_PIN0
		 },

		[D1]=
		{
				.Port = GPIO_PORTA,
				.Pin = GPIO_PIN1
		},

		[D2]=
		{
				.Port = GPIO_PORTA,
				.Pin = GPIO_PIN2
		},

		[D3]=
		{
				.Port = GPIO_PORTA,
				.Pin = GPIO_PIN3
		},

		[D4]=
		{
				.Port = GPIO_PORTA,
				.Pin = GPIO_PIN4
		},

		[D5]=
		{
				.Port = GPIO_PORTA,
				.Pin = GPIO_PIN5
		},

		[D6]=
		{
				.Port = GPIO_PORTA,
				.Pin = GPIO_PIN6
		},

		[D7]=
		{
				.Port = GPIO_PORTA,
				.Pin = GPIO_PIN7
		},

		[Enable]=
		{
				.Port = GPIO_PORTB,
				.Pin = GPIO_PIN0
		},

		[RW]=
		{
				.Port = GPIO_PORTB,
				.Pin = GPIO_PIN1
		},

		[RS]=
		{
				.Port = GPIO_PORTB,
				.Pin = GPIO_PIN2
		}
};


