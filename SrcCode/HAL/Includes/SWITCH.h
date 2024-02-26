/*
 * SWITCH.h
 *
 *  Created on: Feb 26, 2024
 *      Author: top one
 */

#ifndef HAL_INCLUDES_SWITCH_H_
#define HAL_INCLUDES_SWITCH_H_

/****************************************************************************************
 *                        	                Defines                                     *
 ****************************************************************************************/

/**
 *@brief  : State of Switch.
 */
#define SWITCH_PRESSED 1
#define SWITCH_NOT_PRESSED 0

/**
 *@brief  : Switches Connections.
 */
#define CONNECTION_PULL_UP 0x00000008
#define CONNECTION_PULL_DOWN 0x00000010


/****************************************************************************************
 *                        	              Types                                         *
 ****************************************************************************************/

/**
 *@brief  : Struct to Configure Switch.
 */
typedef struct
{
	void* Port;
	u32 Pin;
	u32 Connection;

}SWITCH_Config_t;

/****************************************************************************************
 *                        	              Function Prototypes                           *
 ****************************************************************************************/

/**
 *@brief  : Function to Initialize All Switches.
 *@param  : Void.
 *@return : Error State.
 */
Error_t SWITCH_Init(void);

/**
 *@brief  : Function to Get The State of A Switch if Pressed or Not Pressed.
 *@param  : Switch ID, Pointer to u8 Variable That will Hold The State of The Switch(SITCH_PRESSED, SWITCH_NOT_PRESSED).
 *@return : Error State.
 */
Error_t SWITCH_ReadState(u32 Switch_ID, u8* Switch_State);

#endif /* HAL_INCLUDES_SWITCH_H_ */
