/*
 * SCHED.c
 *
 *  Created on: Mar 23, 2024
 *      Author: Yasmine Mostafa
 */

/****************************************************************************************
 *                        	              Includes                                      *
 ****************************************************************************************/

#include "STD_Types.h"
#include "Error.h"
#include "SYSTICK.h"
#include "SCHED.h"
#include "SCHED_CFG.h"

/****************************************************************************************
 *                        	              Defines                                       *
 ****************************************************************************************/
#define TICK_MS 1
/****************************************************************************************
 *                        	              Types                                         *
 ****************************************************************************************/
typedef struct
{
	Runnable_Config_t* Runnable;
	u32 RemainingTime_ms;
}Runnable_Info_t;


/****************************************************************************************
 *                        	            Variables                                    *
 ****************************************************************************************/
volatile u8 G_PendingTicks=0;
extern const Runnable_Config_t Runnables_Config[_Runnable_Num];
Runnable_Info_t G_Runnables[_Runnable_Num];

/****************************************************************************************
 *                        	        Static Functions Protoypes                           *
 ****************************************************************************************/
static void SCHED(void);
static void SCHED_TickCbf(void);

/****************************************************************************************
 *                        	        Function Implementations                            *
 ****************************************************************************************/
Error_t SCHED_Init(void)
{
	Error_t Ret_SCHEDErrorStatus=Error_OK;

	/*Configure the Runnables array with Each Remaining Time*/
	for(u32 Loc_Counter=0; Loc_Counter <_Runnable_Num; Loc_Counter++)
	{
		G_Runnables[Loc_Counter].Runnable=&Runnables_Config[Loc_Counter];
		G_Runnables[Loc_Counter].RemainingTime_ms=Runnables_Config[Loc_Counter].FirstDelay_ms;
	}

	/*Configure Systick*/
	STK_Init(CLK_AHB_8,MODE_ENABLE_INT);
	STK_SetTimeMs(TICK_MS);
	STK_SetCallBack(SCHED_TickCbf);
	return Ret_SCHEDErrorStatus;

}
void SCHED_Start(void)
{
	STK_Start();
	while(1)
	{
		if(G_PendingTicks)
		{
			G_PendingTicks--;
			SCHED();
		}
	}
}

/****************************************************************************************
 *                        	     Static Functions Implementation                        *
 ****************************************************************************************/
static void SCHED(void)
{
	for(u32 Loc_Counter=0; Loc_Counter <_Runnable_Num; Loc_Counter++)
	{
		if(G_Runnables[Loc_Counter].Runnable->Runnable_Cbf && G_Runnables[Loc_Counter].RemainingTime_ms==0)
		{
			G_Runnables[Loc_Counter].Runnable->Runnable_Cbf();
			G_Runnables[Loc_Counter].RemainingTime_ms=G_Runnables[Loc_Counter].Runnable->Periodicity_ms;
		}
		G_Runnables[Loc_Counter].RemainingTime_ms-=TICK_MS;;
	}
}

static void SCHED_TickCbf(void)
{
	G_PendingTicks++;
}
