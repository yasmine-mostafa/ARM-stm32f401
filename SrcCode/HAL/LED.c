/*
 * LED.c
 *
 *  Created on: Feb 19, 2024
 *      Author: Yasmine Mostafa
 */
#include "Error.h"
#include "STD_Types.h"
#include "GPIO.h"
#include "LED_CFG.h"
#include "LED.h"


extern const LED_Config_t LEDS_Config[_LED_Num];

Error_t LED_Init(void)
{
	Error_t Ret_LEDErrorStatus=Error_NOK;

	u8 Loc_State;
	GPIO_Config_t Loc_LED;

	/*Set Mode to Output PP*/
	Loc_LED.Mode= GPIO_MODE_OUTPUT_PP;

	/*Set Speed to High*/
	Loc_LED.Speed=GPIO_SPEED_HIGH;


	/*Configure Each Port and Pin*/
	for(u8 Loc_Iter=0; Loc_Iter < _LED_Num; Loc_Iter++)
	{
		Loc_LED.Port= LEDS_Config[Loc_Iter].Port;
		Loc_LED.Pin=LEDS_Config[Loc_Iter].Pin;
		Ret_LEDErrorStatus=GPIO_InitPin(& Loc_LED);

		/*Set State to Initial State*/
		Loc_State = (LEDS_Config[Loc_Iter].Connection) ^ (LEDS_Config[Loc_Iter].InitState);
		Ret_LEDErrorStatus=GPIO_SetPinValue(LEDS_Config[Loc_Iter].Port,LEDS_Config[Loc_Iter].Pin,Loc_State);
	}
	return Ret_LEDErrorStatus;
}

Error_t LED_SetState(LED_ID_t LED_ID, u8 LED_State)
{
	Error_t Ret_LEDErrorStatus=Error_NOK;

	if(LED_State > LED_ON || LED_State < LED_OFF)
	{
		Ret_LEDErrorStatus=Error_InvalidInput;
	}
	else
	{
		u8 Loc_State = (LEDS_Config[LED_ID].Connection) ^ LED_State;
		GPIO_SetPinValue(LEDS_Config[LED_ID].Port,LEDS_Config[LED_ID].Pin,Loc_State);
		Ret_LEDErrorStatus=Error_OK;
	}

	return Ret_LEDErrorStatus;
}
