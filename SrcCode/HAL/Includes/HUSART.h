/*
 * HUSART.h
 *
 *  Created on: Apr 13, 2024
 *      Author: top one
 */

#ifndef HAL_INCLUDES_HUSART_H_
#define HAL_INCLUDES_HUSART_H_



typedef struct
{
	void* TX_Port;
	u32 TX_Pin;
	u32 TX_AF;
	void* RX_Port;
	u32 RX_Pin;
	u32 RX_AF;

}HUSART_Config_t;


Error_t HUSART_Init(USART_Config_t USART_Config);

Error_t HUSART_SendByte(USART_IDs_t USART_ID, u8 Byte);
Error_t HUSART_ReceiveByte(USART_IDs_t USART_ID, u8* Byte);

Error_t HUSART_SendBufferZC(USART_ReqBuffer_t TXBuffer);


Error_t HUSART_ReceiveBufferZC(USART_ReqBuffer_t RXBuffer);
#endif /* HAL_INCLUDES_HUSART_H_ */
