/*
 * SCHED_CFG.c
 *
 *  Created on: Mar 23, 2024
 *      Author: Yasmine Mostafa
 */

#include "STD_Types.h"
#include "Error.h"
#include "SCHED_CFG.H"
#include "SCHED.h"

//extern void TrafficLight(void);
extern void ToggleLED_Runnable(void);
extern void SWITCH_Runnable(void);
Runnable_Config_t Runnables_Config[_Runnable_Num]=
{
	/*[Runnable1]=
	{
			.Periodicity_ms=2000,
			.FirstDelay_ms=2000,
			.Runnable_Cbf = TrafficLight
	}*/

	[Runnable1]=
	{
			.Periodicity_ms=5,
			.FirstDelay_ms=3,
			.Runnable_Cbf = SWITCH_Runnable
	},
	[Runnable2]=
    {
		    .Periodicity_ms=50,
			.FirstDelay_ms=50,
			.Runnable_Cbf = ToggleLED_Runnable
		},


};

