/*
 * USART.c
 *
 *  Created on: Apr 9, 2024
 *      Author: Yasmine Mostafa
 *
 *
 */
/****************************************************************************************
 *                        	              Includes                                      *
 ****************************************************************************************/
#include "STD_Types.h"
#include "Error.h"
#include "USART.h"
/****************************************************************************************
 *                        	              Defines                                       *
 ****************************************************************************************/
#define USART1_BASE_ADDRESS 0x40011000
#define USART2_BASE_ADDRESS 0x40004400
#define USART6_BASE_ADDRESS 0x40011400

#define USART_NUM 3
#define USART_CLK 16000000
#define OVERSAMPLING_BIT_SHIFT 15
#define MANTISSA_SHIFT 4
#define TC_BIT_SHIFT 6
#define RXNE_BIT_SHIFT 5

#define TRANSMITTER_ENABLE 0x00000008
#define RECEIVER_ENABLE 0x00000004
#define USART_ENABLE 0x00002000
#define TXEIE_ENABLE 0x00000080
#define RXNEIE_ENABLE 0x00000020
#define TX_DONE 0x00000080
#define RX_DONE 0x00000020
#define TC_NOT_COMPLETE 0x00000040
/****************************************************************************************
 *                        	              Types                                         *
 ****************************************************************************************/
typedef void (*CallBackFunction_t)(void);

typedef enum
{
	Req_Ready,
	Req_Busy
}Req_State_t;

typedef struct
{
	u32 USART_SR;
	u32 USART_DR;
	u32 USART_BRR;
	u32 USART_CR1;
	u32 USART_CR2;
	u32 USART_CR3;
	u32 USART_GTPR;
}USART_Peri_t;

typedef struct
{
	u8* Data;
	u32 Position;
	u32 Size;
	Req_State_t State;
	CallBackFunction_t cbf;
}User_Req_t;


/****************************************************************************************
 *                        	            Variables                                    *
 ****************************************************************************************/
static volatile USART_Peri_t* const USART[USART_NUM]=
{
		(volatile USART_Peri_t*)USART1_BASE_ADDRESS,
		(volatile USART_Peri_t*)USART2_BASE_ADDRESS,
		(volatile USART_Peri_t*)USART6_BASE_ADDRESS,
};

User_Req_t TX_Req[USART_NUM]={0};
User_Req_t RX_Req[USART_NUM]={0};

/****************************************************************************************
 *                        	              Function Implementations                      *
 ****************************************************************************************/
Error_t USART_Init(USART_Config_t Copy_UsartConfig)
{
	Error_t Ret_USARTErrorStatus=Error_NOK;

	if(Copy_UsartConfig.USART_ID > 2)
	{
		Ret_USARTErrorStatus=Error_InvalidInput;
	}
	else
	{
		u32 Loc_CR1;
		u32 Loc_Over8;
		u32 Loc_DIV;
		u32 Loc_Fraction;
		u32 Loc_Mantissa;

		/*USART_CR1 Conf*/
		Loc_CR1 = Copy_UsartConfig.OverSampling | Copy_UsartConfig.ParityEnable | Copy_UsartConfig.ParitySelection | Copy_UsartConfig.WordLength | USART_ENABLE;
		USART[Copy_UsartConfig.USART_ID]->USART_CR1 = Loc_CR1;

		/*USART_CR2 Conf*/
		USART[Copy_UsartConfig.USART_ID]->USART_CR2 = Copy_UsartConfig.StopBits;

		/*USART_BRR Conf*/
		Loc_Over8 = Copy_UsartConfig.OverSampling >> OVERSAMPLING_BIT_SHIFT;
		Loc_DIV=((u64)USART_CLK*1000)/(8*(2-Loc_Over8)*Copy_UsartConfig.BaudRate);
		Loc_Mantissa=Loc_DIV/1000;
		Loc_Fraction=(Loc_DIV % 1000) * (8*(2-Loc_Over8));

		if(Loc_Fraction % 1000 >= 500)
		{
			Loc_Fraction = (Loc_Fraction/1000) + 1;
		}
		else
		{
			Loc_Fraction = (Loc_Fraction/1000);
		}

		if(((Loc_Over8 == 0) && (Loc_Fraction > 15) )||((Loc_Over8 == 1) && (Loc_Fraction > 7)))
		{
			Loc_Fraction=0;
			Loc_Mantissa++;
		}
		USART[Copy_UsartConfig.USART_ID]->USART_BRR=(Loc_Mantissa << MANTISSA_SHIFT )| Loc_Fraction;

		Ret_USARTErrorStatus=Error_OK;

	}

	return Ret_USARTErrorStatus;
}

Error_t USART_SendByte(USART_IDs_t Copy_USART_ID, u8 Copy_Byte)
{
	Error_t Ret_USARTErrorStatus=Error_NOK;

	if(Copy_USART_ID > USART6)
	{
		Ret_USARTErrorStatus=Error_InvalidInput;
	}
	else
	{
		volatile u16 TimeOut = 6000;

		USART[Copy_USART_ID]->USART_CR1 |= TRANSMITTER_ENABLE;

		USART[Copy_USART_ID]->USART_DR = Copy_Byte;
		//while((((USART[Copy_USART_ID]->USART_SR) >> TC_BIT_SHIFT) & (0x01) == 0) && TimeOut)
		while((((USART[Copy_USART_ID]->USART_SR) & TC_NOT_COMPLETE) == 0 )&& TimeOut)
	//	while(TimeOut)
		{
			TimeOut--;
		}


		if(TimeOut == 0)
		{
			Ret_USARTErrorStatus=Error_Timeout;
		}
		else
		{
			Ret_USARTErrorStatus=Error_OK;
		}

		USART[Copy_USART_ID]->USART_CR1 &=~ TRANSMITTER_ENABLE;
	}
	return Ret_USARTErrorStatus;
}

Error_t USART_ReceiveByte(USART_IDs_t Copy_USART_ID, u8* Copy_Byte)
{
	Error_t Ret_USARTErrorStatus=Error_NOK;

	if(Copy_USART_ID > USART6)
	{
		Ret_USARTErrorStatus=Error_InvalidInput;
	}
	else
	{
		volatile u32 TimeOut = 3000;
		USART[Copy_USART_ID]->USART_CR1 |= RECEIVER_ENABLE;

		//while(((USART[Copy_USART_ID]->USART_SR >> RXNE_BIT_SHIFT) & (0x01) == 0 )&& TimeOut)
		while((((USART[Copy_USART_ID]->USART_SR) & (RX_DONE)) == 0 ) && TimeOut)
		{
			TimeOut--;
		}

		if(TimeOut == 0)
		{
			Ret_USARTErrorStatus=Error_Timeout;
		}
		else
		{
			*Copy_Byte = USART[Copy_USART_ID]->USART_DR;
			Ret_USARTErrorStatus=Error_OK;
		}

	//	USART[Copy_USART_ID]->USART_CR1 &=~ RECEIVER_ENABLE;

	}
	return Ret_USARTErrorStatus;
}

Error_t USART_SendBufferZeroCopy(USART_ReqBuffer_t Copy_TXBuffer)
{
	Error_t Ret_USARTErrorStatus=Error_NOK;

	if(Copy_TXBuffer.Channel > USART6)
	{
		Ret_USARTErrorStatus=Error_InvalidInput;
	}
	else
	{
		if(TX_Req[Copy_TXBuffer.Channel].State == Req_Busy)
		{
			Ret_USARTErrorStatus=Error_Busy;
		}
		else
		{
			TX_Req[Copy_TXBuffer.Channel].State = Req_Busy;
			TX_Req[Copy_TXBuffer.Channel].Data = Copy_TXBuffer.Data;
			TX_Req[Copy_TXBuffer.Channel].Size = Copy_TXBuffer.Size;
			TX_Req[Copy_TXBuffer.Channel].cbf = Copy_TXBuffer.cbf;
			TX_Req[Copy_TXBuffer.Channel].Position=0;

			USART[Copy_TXBuffer.Channel]->USART_CR1 |= TRANSMITTER_ENABLE;
			USART[Copy_TXBuffer.Channel]->USART_DR = Copy_TXBuffer.Data[0];
			TX_Req[Copy_TXBuffer.Channel].Position++;
			USART[Copy_TXBuffer.Channel]->USART_CR1 |= TXEIE_ENABLE;

			Ret_USARTErrorStatus=Error_OK;
		}
	}

	return Ret_USARTErrorStatus;
}
Error_t USART_ReceiveBufferZeroCopy(USART_ReqBuffer_t Copy_RXBuffer)
{
	Error_t Ret_USARTErrorStatus=Error_NOK;

	if(Copy_RXBuffer.Channel > USART6)
	{
		Ret_USARTErrorStatus=Error_InvalidInput;
	}
	else
	{
		if(RX_Req[Copy_RXBuffer.Channel].State == Req_Busy)
		{
			Ret_USARTErrorStatus=Error_Busy;
		}
		else
		{
			RX_Req[Copy_RXBuffer.Channel].State = Req_Busy;
			RX_Req[Copy_RXBuffer.Channel].Data = Copy_RXBuffer.Data;
			RX_Req[Copy_RXBuffer.Channel].Size = Copy_RXBuffer.Size;
			RX_Req[Copy_RXBuffer.Channel].cbf = Copy_RXBuffer.cbf;
			RX_Req[Copy_RXBuffer.Channel].Position=0;

			USART[Copy_RXBuffer.Channel]->USART_CR1 |= RECEIVER_ENABLE;
			//Copy_RXBuffer->Data[0]=USART[Copy_RXBuffer->Channel]->USART_DR;
			//RX_Req[Copy_RXBufferChannel].Position++;

			USART[Copy_RXBuffer.Channel]->USART_CR1 |= RXNEIE_ENABLE;

			Ret_USARTErrorStatus=Error_OK;
		}
	}

	return Ret_USARTErrorStatus;
}

void USART1_IRQHandler(void)
{
	if((USART[USART1]->USART_SR) & TX_DONE)
	{
		if(TX_Req[USART1].Position < TX_Req[USART1].Size)
		{
			USART[USART1]->USART_DR =TX_Req[USART1].Data[TX_Req[USART1].Position];
			TX_Req[USART1].Position++;

		}
		else
		{
			TX_Req[USART1].State = Req_Ready;

			USART[USART1]->USART_CR1 &=~ TRANSMITTER_ENABLE;
			USART[USART1]->USART_CR1 &=~ TXEIE_ENABLE;
			if(TX_Req[USART1].cbf)
			{
				TX_Req[USART1].cbf();
			}

		}
	}

	if((USART[USART1]->USART_SR)& RX_DONE)
	{
		if(RX_Req[USART1].Position < RX_Req[USART1].Size)
		{
			RX_Req[USART1].Data[RX_Req[USART1].Position] = USART[USART1]->USART_DR;
			RX_Req[USART1].Position++;

			if(RX_Req[USART1].Position == RX_Req[USART1].Size)
				{
					RX_Req[USART1].State = Req_Ready;

					USART[USART1]->USART_SR &=~ RX_DONE;
					USART[USART1]->USART_CR1 &=~ RECEIVER_ENABLE;
					USART[USART1]->USART_CR1 &=~ RXNEIE_ENABLE;
					if(RX_Req[USART1].cbf)
					{
						RX_Req[USART1].cbf();
					}
				}
		}

	}
}

void USART2_IRQHandler(void)
{
	if((USART[USART2]->USART_SR) & TX_DONE)
	{
		if(TX_Req[USART2].Position < TX_Req[USART2].Size)
		{
			USART[USART2]->USART_DR =TX_Req[USART2].Data[TX_Req[USART2].Position];
			TX_Req[USART2].Position++;

		}
		else
		{
			TX_Req[USART2].State = Req_Ready;

			USART[USART2]->USART_CR1 &=~ TRANSMITTER_ENABLE;
			USART[USART2]->USART_CR1 &=~ TXEIE_ENABLE;
			if(TX_Req[USART2].cbf)
			{
				TX_Req[USART2].cbf();
			}

		}
	}

	if((USART[USART2]->USART_SR)& RX_DONE)
	{
		if(RX_Req[USART2].Position < RX_Req[USART2].Size)
		{
			RX_Req[USART2].Data[RX_Req[USART2].Position] = USART[USART2]->USART_DR;
			RX_Req[USART2].Position++;

			if(RX_Req[USART2].Position == RX_Req[USART2].Size)
				{
					RX_Req[USART2].State = Req_Ready;

					USART[USART2]->USART_SR &=~ RX_DONE;
					USART[USART2]->USART_CR1 &=~ RECEIVER_ENABLE;
					USART[USART2]->USART_CR1 &=~ RXNEIE_ENABLE;
					if(RX_Req[USART2].cbf)
					{
						RX_Req[USART2].cbf();
					}
				}
		}

	}
}

void USART6_IRQHandler(void)
{
	if((USART[USART6]->USART_SR) & TX_DONE)
	{
		if(TX_Req[USART6].Position < TX_Req[USART6].Size)
		{
			USART[USART6]->USART_DR =TX_Req[USART6].Data[TX_Req[USART6].Position];
			TX_Req[USART6].Position++;

		}
		else
		{
			TX_Req[USART6].State = Req_Ready;

			USART[USART6]->USART_CR1 &=~ TRANSMITTER_ENABLE;
			USART[USART6]->USART_CR1 &=~ TXEIE_ENABLE;
			if(TX_Req[USART6].cbf)
			{
				TX_Req[USART6].cbf();
			}

		}
	}

	if((USART[USART6]->USART_SR)& RX_DONE)
	{
		if(RX_Req[USART6].Position < RX_Req[USART6].Size)
		{
			RX_Req[USART6].Data[RX_Req[USART6].Position] = USART[USART6]->USART_DR;
			RX_Req[USART6].Position++;

			if(RX_Req[USART6].Position == RX_Req[USART6].Size)
				{
					RX_Req[USART6].State = Req_Ready;

					USART[USART6]->USART_SR &=~ RX_DONE;
					USART[USART6]->USART_CR1 &=~ RECEIVER_ENABLE;
					USART[USART6]->USART_CR1 &=~ RXNEIE_ENABLE;
					if(RX_Req[USART6].cbf)
					{
						RX_Req[USART6].cbf();
					}
				}
		}

	}
}
