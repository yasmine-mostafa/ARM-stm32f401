/*
 * ToggleLED.c
 *
 *  Created on: Mar 24, 2024
 *      Author: Yasmine Mostafa
 */

#include "STD_Types.h"
#include "Error.h"
#include "SWITCH_CFG.h"
#include "SWITCH.h"
#include "LED_CFG.h"
#include "LED.h"


void ToggleLED_Runnable(void)
{
	u8 SW_State=SWITCH_NOT_PRESSED;
	static u8 LED_State = LED_OFF;
	SWITCH_ReadState(SWITCH_1,&SW_State);
	if(SW_State == SWITCH_PRESSED)
	{
		LED_State ^= LED_ON;
		LED_SetState(LED_Red,LED_State);
	}
}
