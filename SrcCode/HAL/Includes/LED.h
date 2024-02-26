/*
 * LED.h
 *
 *  Created on: Feb 19, 2024
 *      Author: top one
 */

#ifndef HAL_INCLUDES_LED_H_
#define HAL_INCLUDES_LED_H_

/****************************************************************************************
 *                        	                Defines                                     *
 ****************************************************************************************/

/**
 *@brief  : LEDs States.
 */
#define LED_ON 1
#define LED_OFF 0

/**
 *@brief  : LEDs Connection.
 */
#define LED_REV 1
#define LED_FWD 0

/****************************************************************************************
 *                        	              Types                                         *
 ****************************************************************************************/

/**
 *@brief  : Struct to Configure LEDs.
 */
typedef struct
{
	void* Port;
	u32 Pin;
	u32 Connection;
	u32 InitState;
}LED_Config_t;

/****************************************************************************************
 *                        	              Function Prototypes                           *
 ****************************************************************************************/

/**
 *@brief  : Function to Initialize All LEDs.
 *@param  : Void.
 *@return : Error State.
 */
Error_t LED_Init(void);

/**
 *@brief  : Function to Set State of LED to ON or OFF.
 *@param  : LED ID, LED State:LED_ON or LED_OFF.
 *@return : Error State.
 */
Error_t LED_SetState(LED_ID_t LED_ID, u8 LED_State);

#endif /* HAL_INCLUDES_LED_H_ */
