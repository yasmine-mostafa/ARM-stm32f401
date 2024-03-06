/*
 * NVIC.h
 *
 *  Created on: Mar 6, 2024
 *      Author: Yasmine Mostafa
 */

#ifndef MCAL_INCLUDES_NVIC_H_
#define MCAL_INCLUDES_NVIC_H_

#define PRIORITY_SUBGROUP_0 0x05FA0000   /*4 Group-Priority Bits [7:4] / 0 Sub-Priority Bits [None]*/
#define PRIORITY_SUBGROUP_1 0x05FA0400   /*3 Group-Priority Bits [7:5] / 1 Sub-Priority Bits [4]*/
#define PRIORITY_SUBGROUP_2 0x05FA0500   /*2 Group-Priority Bits [7:6] / 2 Sub-Priority Bits [5:4]*/
#define PRIORITY_SUBGROUP_3 0x05FA0600   /*1 Group-Priority Bits [7] / 3 Sub-Priority Bits [6:4]*/
#define PRIORITY_SUBGROUP_4 0x05FA0700   /*0 Group-Priority Bits [None] / 3 Sub-Priority Bits [7:4]*/


typedef enum
{
    IRQ_WWDG = 0,               /*!< Window Watchdog interrupt */
    IRQ_EXTI16,              /*!< External Interrupt Line 16 */
    IRQ_EXTI21,              /*!< External Interrupt Line 21 */
    IRQ_EXTI22,              /*!< External Interrupt Line 22 */
    IRQ_FLASH,               /*!< Flash global interrupt */
    IRQ_RCC,                 /*!< RCC global interrupt */
    IRQ_EXTI0,               /*!< External Interrupt Line 0 */
    IRQ_EXTI1,               /*!< External Interrupt Line 1 */
    IRQ_EXTI2,               /*!< External Interrupt Line 2 */
    IRQ_EXTI3,               /*!< External Interrupt Line 3 */
    IRQ_EXTI4,               /*!< External Interrupt Line 4 */
    IRQ_DMA1_STREAM0,        /*!< DMA1 Stream 0 global interrupt */
    IRQ_DMA1_STREAM1,        /*!< DMA1 Stream 1 global interrupt */
    IRQ_DMA1_STREAM2,        /*!< DMA1 Stream 2 global interrupt */
    IRQ_DMA1_STREAM3,        /*!< DMA1 Stream 3 global interrupt */
    IRQ_DMA1_STREAM4,        /*!< DMA1 Stream 4 global interrupt */
    IRQ_DMA1_STREAM5,        /*!< DMA1 Stream 5 global interrupt */
    IRQ_DMA1_STREAM6,        /*!< DMA1 Stream 6 global interrupt */
    IRQ_ADC,                 /*!< ADC global interrupt */
    IRQ_EXTI9_5 = 23,          /*!< External Interrupt Line 9 */
    IRQ_TIM1_BRK_TIM9,       /*!< TIM1 Break interrupt and TIM9 global interrupt */
    IRQ_TIM1_UP_TIM10,       /*!< TIM1 Update interrupt and TIM10 global interrupt */
    IRQ_TIM1_TRG_COM_TIM11,  /*!< TIM1 Trigger and Commutation interrupts and TIM11 global interrupt */
    IRQ_TIM1_CC,             /*!< TIM1 Capture Compare interrupt */
    IRQ_TIM2,                /*!< TIM2 global interrupt */
    IRQ_TIM3,                /*!< TIM3 global interrupt */
    IRQ_TIM4,                /*!< TIM4 global interrupt */
    IRQ_I2C1_EV,             /*!< I2C1 event interrupt */
    IRQ_I2C1_ER,             /*!< I2C1 error interrupt */
    IRQ_I2C2_EV,             /*!< I2C2 event interrupt */
    IRQ_I2C2_ER,             /*!< I2C2 error interrupt */
    IRQ_SPI1,                /*!< SPI1 global interrupt */
    IRQ_SPI2,                /*!< SPI2 global interrupt */
    IRQ_USART1,              /*!< USART1 global interrupt */
    IRQ_USART2,              /*!< USART2 global interrupt */
    IRQ_EXTI15_10 = 40,      /*!< External Interrupt Lines 15 to 10 */
    IRQ_EXTI17,              /*!< External Interrupt Line 17 */
    IRQ_EXTI18,              /*!< External Interrupt Line 18 */
    IRQ_DMA1_STREAM7 = 47,   /*!< DMA1 Stream 7 global interrupt */
    IRQ_SDIO = 49,           /*!< SDIO global interrupt */
    IRQ_TIM5,                /*!< TIM5 global interrupt */
    IRQ_SPI3,                /*!< SPI3 global interrupt */
    IRQ_DMA2_STREAM0 = 56,   /*!< DMA2 Stream 0 global interrupt */
    IRQ_DMA2_STREAM1,        /*!< DMA2 Stream 1 global interrupt */
    IRQ_DMA2_STREAM2,        /*!< DMA2 Stream 2 global interrupt */
    IRQ_DMA2_STREAM3,        /*!< DMA2 Stream 3 global interrupt */
    IRQ_DMA2_STREAM4,        /*!< DMA2 Stream 4 global interrupt */
    IRQ_OTG_FS = 67,         /*!< USB OTG FS global interrupt */
    IRQ_DMA2_STREAM5,        /*!< DMA2 Stream 5 global interrupt */
    IRQ_DMA2_STREAM6,        /*!< DMA2 Stream 6 global interrupt */
    IRQ_DMA2_STREAM7,        /*!< DMA2 Stream 7 global interrupt */
    IRQ_USART6,              /*!< USART6 global interrupt */
    IRQ_I2C3_EV,             /*!< I2C3 event interrupt */
    IRQ_I2C3_ER,             /*!< I2C3 error interrupt */
    IRQ_FPU = 81,            /*!< FPU global interrupt */
    IRQ_SPI4 = 84,           /*!< SPI4 global interrupt */
    _IRQ_NUM                /*!< Total number of NVIC IRQs */
} IRQ_t;



Error_t NVIC_EnableIRQ(IRQ_t IRQ);
Error_t NVIC_DisableIRQ(IRQ_t IRQ);
Error_t NVIC_SetPending(IRQ_t IRQ);
Error_t NVIC_ClearPending(IRQ_t IRQ);
Error_t NVIC_GetPending(IRQ_t IRQ, u8* Status);
Error_t NVIC_GetActiveStatus(IRQ_t IRQ , u8 * Status);
Error_t NVIC_SetPriorityGrouping(u32 PrioritySubGroup);
Error_t NVIC_SetPriority(IRQ_t IRQ, u8 Priority);
Error_t NVIC_GetPriority(IRQ_t IRQ, u8* Priority);
Error_t NVIC_GenerateSWInterrupt(IRQ_t IRQ);

#endif /* MCAL_INCLUDES_NVIC_H_ */
