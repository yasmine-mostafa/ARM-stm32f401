/*
 * GPIO.h
 *
 *  Created on: Feb 19, 2024
 *      Author: Yasmine Mostafa
 */

#ifndef MCAL_INCLUDES_GPIO_H_
#define MCAL_INCLUDES_GPIO_H_

/****************************************************************************************
 *                        	                Defines                                     *
 ****************************************************************************************/

/**
 *@brief  : GPIO Ports.
 */
#define GPIO_PORTA		(void*)0x40020000
#define GPIO_PORTB 		(void*)0x40020400
#define GPIO_PORTC 		(void*)0x40020800
#define GPIO_PORTD 		(void*)0x40020C00
#define GPIO_PORTE 		(void*)0x40021000
#define GPIO_PORTH 		(void*)0x40021C00

/**
 *@brief  : GPIO Pins.
 */
#define GPIO_PIN0 		0x00000000
#define GPIO_PIN1 		0x00000001
#define GPIO_PIN2 		0x00000002
#define GPIO_PIN3 		0x00000003
#define GPIO_PIN4 		0x00000004
#define GPIO_PIN5 		0x00000005
#define GPIO_PIN6 		0x00000006
#define GPIO_PIN7 		0x00000007
#define GPIO_PIN8 		0x00000008
#define GPIO_PIN9 		0x00000009
#define GPIO_PIN10 		0x0000000A
#define GPIO_PIN11 		0x0000000B
#define GPIO_PIN12 		0x0000000C
#define GPIO_PIN13 		0x0000000D
#define GPIO_PIN14 		0x0000000E
#define GPIO_PIN15 		0x0000000F

/**
 *@brief  : GPIO Output Modes.
 */
#define GPIO_MODE_OUTPUT_PP 	0x00000001
#define GPIO_MODE_OUTPUT_PP_PU 	0x00000009
#define GPIO_MODE_OUTPUT_PP_PD	0x00000011
#define GPIO_MODE_OUTPUT_OD 	0x00000005
#define GPIO_MODE_OUTPUT_OD_PU	0x0000000D
#define GPIO_MODE_OUTPUT_OD_PD  0x00000015

/**
 *@brief  : GPIO Input Modes.
 */
#define GPIO_MODE_INPUT_PU 		0x00000008
#define GPIO_MODE_INPUT_PD 		0x00000010
#define GPIO_MODE_INPUT_FLOATING	0x00000000

/**
 *@brief  : GPIO Analog Mode.
 */
#define GPIO_MODE_ANALOG 	0x00000003

/**
 *@brief  : GPIO Alternate Functions Modes.
 */
#define GPIO_MODE_AF_PP 	0x00000002
#define GPIO_MODE_AF_PP_PU 	0x0000000A
#define GPIO_MODE_AF_PP_PD	0x00000012
#define GPIO_MODE_AF_OD 	0x00000006
#define GPIO_MODE_AF_OD_PU	0x0000000E
#define GPIO_MODE_AF_OD_PD  0x00000016

/**
 *@brief  : Alternate Functions.
 */
#define GPIO_AF_SYSTEM        0x00000000
#define GPIO_AF_TIM1_2          0x00000001
#define GPIO_AF_TIM3_5          0x00000002
#define GPIO_AF_TIME9_11        0x00000003
#define GPIO_AF_I2C1_3          0x00000004
#define GPIO_AF_SPI1_4          0x00000005
#define GPIO_AF_SPI3            0x00000006
#define GPIO_AF_USART1_2        0x00000007
#define GPIO_AF_USART6          0x00000008
#define GPIO_AF_I2C2_3          0x00000009
#define GPIO_AF_OTG_FS          0x0000000A
#define GPIO_AF_SDIO            0x0000000C
#define GPIO_AF_EVENTOUT        0x0000000F

/**
 *@brief  : Speed.
 */
#define GPIO_SPEED_LOW			0x00000000
#define GPIO_SPEED_MEDIUM		0x00000001
#define GPIO_SPEED_HIGH			0x00000002
#define GPIO_SPEED_VERY_HIGH	0x00000003

/**
 *@brief  : States.
 */
#define GPIO_STATE_HIGH 1
#define GPIO_STATE_LOW 0


/****************************************************************************************
 *                        	              Types                                         *
 ****************************************************************************************/

/**
 *@brief  : Struct For GPIO Configuration.
 */
typedef struct
{
	void* Port;
	u32 Pin;
	u32 Speed;
	u32 Mode;
}GPIO_Config_t;

/****************************************************************************************
 *                        	              Function Prototypes                           *
 ****************************************************************************************/

/**
 *@brief  : Function to Configure GPIO Pin.
 *@param  : Pointer to GPIO_Config_t Struct.
 *@return : Error State
 */
Error_t GPIO_InitPin(GPIO_Config_t * GPIO_Config);

/**
 *@brief  : Function to Configure GPIO Pin.
 *@param  : Pointer to GPIO_Config_t Struct.
 *@return : Error State
 */
Error_t GPIO_InitPinAF(GPIO_Config_t * GPIO_Config,u32 GPIO_AF);
/**
 *@brief  : Function to Set GPIO Pin Value to High or Low.
 *@param  : Port, Pin, State(High or Low).
 *@return : Error State
 */
Error_t GPIO_SetPinValue(void* GPIO_Port, u8 GPIO_Pin, u8 GPIO_State);
/**
 *@brief  : Function to Get Value of Pin.
 *@param  : Port, Pin, Pointer to u8 that Will Hold The State of The Pin(High or Low).
 *@return : Error State
 */
Error_t GPIO_GetPinValue(void* GPIO_Port, u8 GPIO_Pin, u8 * GPIO_State);


#endif /* MCAL_INCLUDES_GPIO_H_ */
