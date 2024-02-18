/*
 * RCC.h
 *
 *  Created on: Feb 7, 2024
 *      Author: Yasmine Mostafa
 */


#ifndef MCAL_INCLUDES_RCC_H_
#define MCAL_INCLUDES_RCC_H_

/****************************************************************************************
 *                        	                Defines                                     *
 ****************************************************************************************/
/**
 *@brief  : The Three clocks to Be Enabled/Disabled
 */
#define CLK_HSI 0x00000001
#define CLK_HSE 0x00010000
#define CLK_PLL 0x01000000

/**
 *@brief  : The Three System Clocks to Be Selected
 */
#define SYS_CLK_HSI 0x00
#define SYS_CLK_HSE 0x00000001
#define SYS_CLK_PLL 0x00000002

/**
 *@brief  :AHB1 Peripherals
 */
#define PERIPHERAL_GPIOA 0x01
#define PERIPHERAL_GPIOB 0x02
#define PERIPHERAL_GPIOC 0x04
#define PERIPHERAL_GPIOD 0x08
#define PERIPHERAL_GPIOE 0x10
#define PERIPHERAL_GPIOH 0x80
#define PERIPHERAL_CRC 0x1000
#define PERIPHERAL_DMA1 0x00200000
#define PERIPHERAL_DMA2 0x00400000

/**
 *@brief  :AHB2 Peripherals
 */
#define PERIPHERAL_OTGFS 0x80

/**
 *@brief  :APB1 Peripherals
 */
#define PERIPHERAL_TIM2 0x01
#define PERIPHERAL_TIM3 0x02
#define PERIPHERAL_TIM4 0x04
#define PERIPHERAL_TIM5 0x08
#define PERIPHERAL_WWDG 0x0800
#define PERIPHERAL_SPI2 0x4000
#define PERIPHERAL_SPI3 0x8000
#define PERIPHERAL_USART2 0x00020000
#define PERIPHERAL_I2C1 0x00200000
#define PERIPHERAL_I2C2 0x00400000
#define PERIPHERAL_I2C3 0x00800000
#define PERIPHERAL_PWR 0x10000000

/**
 *@brief  :APB2 Peripherals
 */
#define PERIPHERAL_TIM1 0x01
#define PERIPHERAL_USART1 0x10
#define PERIPHERAL_USART6 0x20
#define PERIPHERAL_ADC1 0x0100
#define PERIPHERAL_SDIO 0x0800
#define PERIPHERAL_SPI1 0x00001000
#define PERIPHERAL_SPI4 0x00002000
#define PERIPHERAL_SYSCFG 0x00004000
#define PERIPHERAL_TIM9 0x00010000
#define PERIPHERAL_TIM10 0x00020000
#define PERIPHERAL_TIM11 0x00040000

/**
 *@brief  :APB High Speed Bus PreScalars
 */
#define APB_HIGH_PRESCALAR_1 0
#define APB_HIGH_PRESCALAR_2 0x00008000
#define APB_HIGH_PRESCALAR_4 0x0000A000
#define APB_HIGH_PRESCALAR_8 0x0000C000
#define APB_HIGH_PRESCALAR_16 0x0000E000

/**
 *@brief  :APB Low Speed Bus PreScalars
 */
#define APB_LOW_PRESCALAR_1 0
#define APB_LOW_PRESCALAR_2 0x00001000
#define APB_LOW_PRESCALAR_4 0x00001400
#define APB_LOW_PRESCALAR_8 0x00001800
#define APB_LOW_PRESCALAR_16 0x00001C00

/**
 *@brief  :AHB Bus PreScalars
 */
#define AHB_PRESCALAR_1 0
#define AHB_PRESCALAR_2 0x00000080
#define AHB_PRESCALAR_4 0x00000090
#define AHB_PRESCALAR_8 0x000000A0
#define AHB_PRESCALAR_16 0x000000B0
#define AHB_PRESCALAR_64 0x000000C0
#define AHB_PRESCALAR_128 0x000000D0
#define AHB_PRESCALAR_256 0x000000E0
#define AHB_PRESCALAR_512 0x000000F0

/****************************************************************************************
 *                        	              Types                                         *
 ****************************************************************************************/

/**
*@brief  :Error Status For Operations
*/
typedef enum
{
	/**
	*@brief  :Operation is Done Correctly.
	*/
	RCC_OK,
	/**
	*@brief  :Operation is Not Done Correctly.
	*/
	RCC_NOK,
	/**
	*@brief  :Operation is Timed Out.
	*/
	RCC_Timeout,
	/**
	*@brief  :Invalid Clock Input.
	*/
	RCC_InvalidClk,
}RCC_Error_t;

/**
*@brief  :PLL Clock Sources (HSE/HSI)
*/
typedef enum
{
	RCC_PLL_Source_HSI,
	RCC_PLL_Source_HSE,

}RCC_PLL_Source_t;

/**
*@brief  :Bus IDs
*/
typedef enum
{
	Bus_AHB1,
	Bus_AHB2,
	Bus_APB1,
	Bus_APB2
}RCC_Bus_ID_t;

/****************************************************************************************
 *                        	              Function Prototypes                           *
 ****************************************************************************************/

/**
 *@brief  : Function to Enable One Of The Three Clocks.
 *@param  : Clock To Be Enabled (HSI,HSE,PLL).
 *@return : Error State
 */
RCC_Error_t RCC_EnableClk(u32 Clk);
/**
 *@brief  : Function to Disable One Of The Three Clocks.
 *@param  : Clock To Be Disabled (HSI,HSE,PLL).
 *@return : Error State
 */
RCC_Error_t RCC_DisableClk(u32 Clk);
/**
 *@brief  : Function to Select One Of The Three Clocks As Sys Clock.
 *@param  : Sys Clock To Be Selected (HSI,HSE,PLL).
 *@return : Error State
 */
RCC_Error_t RCC_SelectSysClk(u32 Sys);
/**
 *@brief  : Function to Select HSI/HSE As PLL Source.
 *@param  : Clock To Be Selected (HSI,HSE).
 *@return : Error State
 */
RCC_Error_t RCC_SelectPLLSource(RCC_PLL_Source_t RCC_PLL_Source);
/**
 *@brief  : Function to Configure PLL Parameters.
 *@param  : 2<=PLL_M<=63, 192<=PLL_N<=432, PLL_P=2/4/6/8, 2<=PLL_Q<=15.
 *@return : Error State
 */
RCC_Error_t RCC_ConfigurePLL(u32 PLL_M,u32 PLL_N,u32 PLL_P,u32 PLL_Q);
/**
 *@brief  : Function to Configure APB High Speed Bus prescalar.
 *@param  : APB High prescalars (none,2/4/8/16).
 *@return : Error State
 */
RCC_Error_t RCC_ConfigureAPBHighPrescalar(u32 APB_High_PreScalar);
/**
 *@brief  : Function to Configure APB Low Speed Bus prescalar.
 *@param  : APB Low prescalars (none,2/4/8/16).
 *@return : Error State
 */
RCC_Error_t RCC_ConfigureAPBLowPrescalar(u32 APB_Low_PreScalar);
/**
 *@brief  : Function to Configure AHB Bus prescalar.
 *@param  : AHB prescalars (none,2/4/8/16/64/128/256/512).
 *@return : Error State
 */
RCC_Error_t RCC_ConfigureAHBPrescalar(u32 AHB_PreScalar);
/**
 *@brief  : Function to Enable Peripheral.
 *@param  : Bus ID of Peripheral, Peripheral To Be Enabled.
 *@return : Error State
 */
RCC_Error_t RCC_EnablePeripheral(RCC_Bus_ID_t Bus_ID,u32 Peripheral);
/**
 *@brief  : Function to Disable Peripheral.
 *@param  : Bus ID of Peripheral, Peripheral To Be Disabled.
 *@return : Error State
 */
RCC_Error_t RCC_DisablePeripheral(RCC_Bus_ID_t Bus_ID,u32 Peripheral);

#endif /* MCAL_INCLUDES_RCC_H_ */
