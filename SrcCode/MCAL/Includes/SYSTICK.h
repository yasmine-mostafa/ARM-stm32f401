/*
 * SYSTICK.h
 *
 *  Created on: Mar 14, 2024
 *      Author: Yasmine Mostafa
 */

#ifndef MCAL_INCLUDES_SYSTICK_H_
#define MCAL_INCLUDES_SYSTICK_H_

/****************************************************************************************
 *                        	              Defines                                       *
 ****************************************************************************************/
/*Clk Source AHB*/
#define CLK_AHB   0x04
/*Clk Source AHB/8*/
#define CLK_AHB_8 0x00
/*Do Not Assert the Systick Exception Request*/
#define MODE_DISABLE_INT 0x00
/*Assert the Systick Exception Request*/
#define MODE_ENABLE_INT 0x02

/****************************************************************************************
 *                        	              Types                                         *
 ****************************************************************************************/

typedef void (*STK_Cbf_t)(void);

/****************************************************************************************
 *                        	              Function Prototypes                           *
 ****************************************************************************************/

/**
 *@brief  : Function to Configure The Systick.
 *@param  : Clock: AHB or AHB/8, Mode:Assert Systick Exception Request or Don't Assert.
 *@return : Error State
 */
Error_t STK_Init(u32 Clk, u32 Mode);
/**
 *@brief  : Function to Set Time of Systick.
 *@param  : Time in ms.
 *@return : Error State
 */
Error_t STK_SetTimeMs(u32 TimeMs);
/**
 *@brief  : Function to Start Counting.
 *@param  : Void.
 *@return : Error State
 */
Error_t STK_Start(void);
/**
 *@brief  : Function to Stop Counting.
 *@param  : Void.
 *@return : Error State
 */
Error_t STK_Stop(void);
/**
 *@brief  : Function to Set Callback for the Systick Handler.
 *@param  : Pointer to the Callback Function.
 *@return : Error State
 */
Error_t STK_SetCallBack(STK_Cbf_t cbf);

#endif /* MCAL_INCLUDES_SYSTICK_H_ */
