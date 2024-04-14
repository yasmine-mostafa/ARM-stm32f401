/*
 * LCD.h
 *
 *  Created on: Apr 1, 2024
 *      Author: Yasmine Mostafa
 */

#ifndef HAL_INCLUDES_LCD_H_
#define HAL_INCLUDES_LCD_H_

/****************************************************************************************
 *                        	                Defines                                     *
 ****************************************************************************************/

#define LCD_CLEAR_DISPLAY 0x1
#define LCD_RETURN_HOME 0x2

#define LCD_DISPLAY_OFF 0
#define LCD_DISPLAY_ON 1

#define LCD_CURSOR_OFF 0
#define LCD_CURSOR_ON 1

#define LCD_BLINK_OFF 0
#define LCD_BLINK_ON 1

#define LCD_DECREMENT 0
#define LCD_INCREMENT 1

#define LCD_SHIFT_DISPLAY_OFF 0
#define LCD_SHIFT_DISPLAY_ON  1

#define LCD_ONE_LINE_DISPLAY 0
#define LCD_TWO_LINE_DISPLAY 1

#define LCD_5X7_CHAR_FONT 0
#define LCD_5X10_CHAR_FONT 1

/****************************************************************************************
 *                        	              Types                                         *
 ****************************************************************************************/
typedef struct
{
	void* Port;
	u32 Pin;

}LCD_Config_t;

/**
 *@brief:LCD Pins For Configuration
 */
typedef enum
{
	D0,
	D1,
	D2,
	D3,
	D4,
	D5,
	D6,
	D7,
	Enable,
	RW,
	RS,

	_LCD_Num
}LCD_Pins_t;


/****************************************************************************************
 *                        	              Function Prototypes                           *
 ****************************************************************************************/

/**
 *@brief  : Function to Initialize LCD.
 *@param  : Void.
 *@return : Error State.
 */
Error_t LCD_InitAsynch(void);
/**
 *@brief  : Function to Clear Screen.
 *@param  : Void.
 *@return : Error State.
 */
Error_t LCD_ClearScreenAsynch(void);
/**
 *@brief  : Function to Set The Position of The Cursor.
 *@param  : Row and Column.
 *@return : Error State.
 */
Error_t LCD_SetCursorPositionAsynch(u8 Row, u8 Column);
/**
 *@brief  : Function to Write String on Screen.
 *@param  : Pointer to String.
 *@return : Error State.
 */
Error_t LCD_WriteStringAsynch(u8 * Str);
/**
 *@brief  : Function to Write Number on Screen.
 *@param  : Number to be Written.
 *@return : Error State.
 */
Error_t LCD_WriteNumberAsynch(u32 Num);

#endif /* HAL_INCLUDES_LCD_H_ */
