/*
 * SWITCH.c
 *
 *  Created on: Feb 26, 2024
 *      Author: Yasmine Mostafa
 */

#include "STD_Types.h"
#include "Error.h"
#include "GPIO.h"
#include "SWITCH_CFG.h"
#include "SWITCH.h"

extern const SWITCH_Config_t SWITCHES_Config[_SWITCH_NUM];

Error_t SWITCH_Init()
{
	Error_t Ret_SWITCHErrorStatus=Error_NOK;

	GPIO_Config_t Loc_SWITCH;

	/*Set The Speed to High*/
	Loc_SWITCH.Speed=GPIO_SPEED_HIGH;

	/*Set Each Port, Pin and Mode*/
	for(u8 Loc_Counter=0; Loc_Counter < _SWITCH_NUM; Loc_Counter++)
	{
		Loc_SWITCH.Port=SWITCHES_Config[Loc_Counter].Port;
		Loc_SWITCH.Pin=SWITCHES_Config[Loc_Counter].Pin;
		Loc_SWITCH.Mode=SWITCHES_Config[Loc_Counter].Connection;

		/*Configure Each Switch*/
		Ret_SWITCHErrorStatus=GPIO_InitPin(& Loc_SWITCH);
	}

	return Ret_SWITCHErrorStatus;
}

Error_t SWITCH_ReadState(u32 Copy_SwitchID, u8* Add_SwitchState)
{
	Error_t Ret_SWITCHErrorStatus=Error_NOK;

	if(Add_SwitchState == NULL)
	{
		Ret_SWITCHErrorStatus=Error_NULLPointer;
	}
	else
	{
		u8 Loc_State;
		Ret_SWITCHErrorStatus=GPIO_GetPinValue(SWITCHES_Config[Copy_SwitchID].Port,SWITCHES_Config[Copy_SwitchID].Pin,&Loc_State);

		*Add_SwitchState=!(Loc_State ^ ((SWITCHES_Config[Copy_SwitchID].Connection) >> 4));
	}

	return Ret_SWITCHErrorStatus;
}

void SWITCH_Runnable(void)
{

}
