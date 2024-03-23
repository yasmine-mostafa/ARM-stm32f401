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

extern void TrafficLight(void);

Runnable_Config_t Runnables_Config[_Runnable_Num]=
{
	[Runnable1]=
	{
			.Periodicity_ms=2000,
			.FirstDelay_ms=2000,
			.Runnable_Cbf = TrafficLight
	}
};

