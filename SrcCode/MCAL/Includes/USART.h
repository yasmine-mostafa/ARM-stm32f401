/*
 * USART.h
 *
 *  Created on: Apr 9, 2024
 *      Author: Yasmine Mostafa
 */

#ifndef MCAL_INCLUDES_USART_H_
#define MCAL_INCLUDES_USART_H_

/****************************************************************************************
 *                        	              Defines                                       *
 ****************************************************************************************/
#define OVERSAMPLING_16 0x00000000
#define OVERSAMPLING_8 0x00008000

#define WORD_LENGTH_8 0x00000000
#define WORD_LENGTH_9 0x00001000

#define PARITY_DISABLED 0x00000000
#define PARITY_ENABLED  0x00000400

#define PARITY_EVEN_SELECTION 0x00000000
#define PARITY_ODD_SELECTION  0x00000200

#define STOP_BITS_1 0x00000000
#define STOP_BITS_HALF 0x00001000
#define STOP_BITS_2 0x00002000
/****************************************************************************************
 *                        	              Types                                         *
 ****************************************************************************************/
typedef void (*CallBackFunction_t)(void);

typedef enum
{
	USART1,
	USART2,
	USART6
}USART_IDs_t;

typedef struct
{
	USART_IDs_t Channel;
	u32 Size;
	u8* Data;
	CallBackFunction_t cbf;

}USART_ReqBuffer_t;

typedef struct
{
	USART_IDs_t USART_ID;
	u16 BaudRate;
	u32 OverSampling;
	u32 WordLength;
	u32 ParityEnable;
	u32 ParitySelection;
	u32 StopBits;

}USART_Config_t;

/****************************************************************************************
 *                        	              Function Prototypes                           *
 ****************************************************************************************/

/**
 *@brief  : Function to Configure The Systick.
 *@param  : Clock: AHB or AHB/8, Mode:Assert Systick Exception Request or Don't Assert.
 *@return : Error State
 */
Error_t USART_Init(USART_Config_t Usart_Config);

Error_t USART_SendByte(USART_IDs_t USART_ID, u8 Byte);
Error_t USART_ReceiveByte(USART_IDs_t USART_ID, u8* Byte);
Error_t USART_SendBufferZeroCopy(USART_ReqBuffer_t TXBuffer);
Error_t USART_ReceiveBufferZeroCopy(USART_ReqBuffer_t RXBuffer);

#endif /* MCAL_INCLUDES_USART_H_ */
