/*
 * SCHED.h
 *
 *  Created on: Mar 23, 2024
 *      Author: Yasmine Mostafa
 */

#ifndef SERVICE_INCLUDES_SCHED_H_
#define SERVICE_INCLUDES_SCHED_H_

/****************************************************************************************
 *                        	              Types                                         *
 ****************************************************************************************/

typedef void (*RunnableCbf_t)(void);

/**
 *@brief  : Struct to Configure Runnables.
 */
typedef struct
{
	u32 Periodicity_ms;
	//u32 Priority;
	u32 FirstDelay_ms;
	RunnableCbf_t Runnable_Cbf;
}Runnable_Config_t;


/****************************************************************************************
 *                        	              Function Prototypes                           *
 ****************************************************************************************/

/**
 *@brief  : Function to Configure Runnables and Systick
 *@param  : Void.
 *@return : Error State.
 */
Error_t SCHED_Init(void);
/**
 *@brief  : Function to Start The Scheduler
 *@param  : Void.
 *@return : void.
 */
void SCHED_Start(void);


#endif /* SERVICE_INCLUDES_SCHED_H_ */
