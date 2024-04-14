/*
 * HUSART_CFG.c
 *
 *  Created on: Apr 14, 2024
 *      Author: Yasmine Mostafa
 */

#include "STD_Types.h"
#include "Error.h"
#include "GPIO.h"
#include "USART.h"
#include "HUSART.h"
#include "HUSART_CFG.h"

const HUSART_Config_t HUSART_Config[_HUSART_NUM]=
{
		[HUSART1]=
		{
				.TX_Port=GPIO_PORTA,
				.TX_Pin=GPIO_PIN9,
				.TX_AF=GPIO_AF_USART1_2,
				.RX_Port=GPIO_PORTA,
				.RX_Pin=GPIO_PIN10,
				.RX_AF=GPIO_AF_USART1_2
		}
};
