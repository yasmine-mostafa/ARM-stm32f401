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
//extern void ToggleLED_Runnable1(void);
//extern void SWITCH_Runnable(void);
//extern void ToggleLED_Runnable2(void);
extern void LCD_Task(void);

Runnable_Config_t Runnables_Config[_Runnable_Num]=
{
	/*[Runnable1]=
	{
			.Periodicity_ms=2000,
			.FirstDelay_ms=2000,
			.Runnable_Cbf = TrafficLight
	}*/

	/*[Runnable1]=
	{
			.Periodicity_ms=5,
			.FirstDelay_ms=3,
			.Runnable_Cbf = SWITCH_Runnable
	},
	[Runnable2]=
    {
		    .Periodicity_ms=50,
			.FirstDelay_ms=50,
			.Runnable_Cbf = ToggleLED_Runnable1
	},

	[Runnable3]=
	    {
			    .Periodicity_ms=50,
				.FirstDelay_ms=25,
				.Runnable_Cbf = ToggleLED_Runnable2
		},*/

	 [Runnable1]=
		{
				.Periodicity_ms=2,
				.FirstDelay_ms=2,
				.Runnable_Cbf = LCD_Task
		}
};

