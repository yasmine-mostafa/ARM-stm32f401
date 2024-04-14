/*
 * HUSART.c
 *
 *  Created on: Apr 13, 2024
 *      Author: Yasmine Mostafa
 */


#include "STD_Types.h"
#include "Error.h"
#include "RCC.h"
#include "NVIC.h"
#include "GPIO.h"
#include "USART.h"
#include "HUSART_CFG.h"
#include "HUSART.h"
/*
extern const HUSART_Config_t HUSART_Config[_HUSART_NUM];

Error_t HUSART_Init()
{
	Error_t Ret_HUSARTErrorStatus = Error_NOK;

	GPIO_Config_t GPIO_UART_TX=
	{
			. Mode= GPIO_MODE_AF_PP,
			. Speed = GPIO_SPEED_HIGH,
	};

	GPIO_Config_t GPIO_UART_RX=
	{
			. Mode= GPIO_MODE_AF_PP,
			. Speed = GPIO_SPEED_HIGH,
	};

	for(u8 Loc_Counter=0; Loc_Counter < _HUSART_NUM; Loc_Counter++)
	{
		GPIO_UART_TX.Port=HUSART_Config[Loc_Counter].TX_Port;
		GPIO_UART_TX.Pin=HUSART_Config[Loc_Counter].TX_Pin;
		GPIO_UART_RX.Port=HUSART_Config[Loc_Counter].RX_Port;
		GPIO_UART_RX.Pin=HUSART_Config[Loc_Counter].RX_Pin;
		GPIO_InitPinAF(&GPIO_UART_TX,HUSART_Config[Loc_Counter].TX_AF);
		GPIO_InitPinAF(&GPIO_UART_RX,HUSART_Config[Loc_Counter].RX_AF);
	}
}*/



Error_t HUSART_Init(USART_Config_t USART_Config)
{
	Error_t Ret_HUSARTErrorStatus = Error_NOK;

	GPIO_Config_t GPIO_UART_TX=
	{
			. Mode= GPIO_MODE_AF_PP,
			. Speed = GPIO_SPEED_HIGH,
	};

	GPIO_Config_t GPIO_UART_RX=
	{
			. Mode= GPIO_MODE_AF_PP,
			. Speed = GPIO_SPEED_HIGH,
	};

	switch(USART_Config.USART_ID)
	{
	case USART1:
		RCC_EnablePeripheral(Bus_APB2,PERIPHERAL_USART1);

		GPIO_UART_TX.Port=GPIO_PORTA;
		GPIO_UART_TX.Pin=GPIO_PIN9;

		GPIO_UART_RX.Port=GPIO_PORTA;
		GPIO_UART_RX.Pin=GPIO_PIN10;

		NVIC_EnableIRQ(IRQ_USART1);
		Ret_HUSARTErrorStatus = Error_OK;
		break;

	case USART2:

		RCC_EnablePeripheral(Bus_APB2,PERIPHERAL_USART2);

		GPIO_UART_TX.Port=GPIO_PORTA;
		GPIO_UART_TX.Pin=GPIO_PIN2;

		GPIO_UART_RX.Port=GPIO_PORTA;
		GPIO_UART_RX.Pin=GPIO_PIN3;

		NVIC_EnableIRQ(IRQ_USART2);
		Ret_HUSARTErrorStatus = Error_OK;
		break;

	case USART6:
		RCC_EnablePeripheral(Bus_APB2,PERIPHERAL_USART6);


		GPIO_UART_TX.Port=GPIO_PORTA;
		GPIO_UART_TX.Pin=GPIO_PIN11;

		GPIO_UART_RX.Port=GPIO_PORTA;
		GPIO_UART_RX.Pin=GPIO_PIN12;
		NVIC_EnableIRQ(IRQ_USART6);
		Ret_HUSARTErrorStatus = Error_OK;
		break;

	default:
		break;
	}

	RCC_EnablePeripheral(Bus_AHB1,PERIPHERAL_GPIOA);
	GPIO_InitPinAF(&GPIO_UART_TX,GPIO_AF_USART1_2);
	GPIO_InitPinAF(&GPIO_UART_RX,GPIO_AF_USART1_2);

	USART_Init(USART_Config);

	return Ret_HUSARTErrorStatus;
}

Error_t HUSART_SendBufferZC(USART_ReqBuffer_t TXBuffer)
{
	Error_t Ret_HUSARTErrorStatus = Error_NOK;

	Ret_HUSARTErrorStatus=USART_SendBufferZeroCopy(TXBuffer);
	return Ret_HUSARTErrorStatus;
}

Error_t HUSART_ReceiveBufferZC(USART_ReqBuffer_t RXBuffer)
{
	Error_t Ret_HUSARTErrorStatus = Error_NOK;

	Ret_HUSARTErrorStatus=USART_ReceiveBufferZeroCopy(RXBuffer);
	return Ret_HUSARTErrorStatus;
}

Error_t HUSART_SendByte(USART_IDs_t USART_ID, u8 Byte)
{
	Error_t Ret_HUSARTErrorStatus = Error_NOK;

	Ret_HUSARTErrorStatus=USART_SendByte(USART_ID,Byte);
	return Ret_HUSARTErrorStatus;
}
Error_t HUSART_ReceiveByte(USART_IDs_t USART_ID, u8* Byte)
{
	Error_t Ret_HUSARTErrorStatus = Error_NOK;

	Ret_HUSARTErrorStatus=USART_ReceiveByte(USART_ID,Byte);
	return Ret_HUSARTErrorStatus;
}
