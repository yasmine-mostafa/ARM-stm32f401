/*
 * RCC.c
 *
 *  Created on: Feb 7, 2024
 *      Author: Yasmine Mostafa
 */

/****************************************************************************************
 *                        	              Includes                                      *
 ****************************************************************************************/

#include "STD_TYPES.h"
#include "RCC.h"

/****************************************************************************************
 *                        	              Defines                                       *
 ****************************************************************************************/

#define RCC_BASE_ADD     0x40023800

#define CLK_RDY_HSI 0x00000002
#define CLK_RDY_HSE 0x00020000
#define CLK_RDY_PLL 0x02000000

#define SYS_CLK_CLEAR 0xFFFFFFFC

#define SYS_CLK_HSI_STATUS 0x00
#define SYS_CLK_HSE_STATUS 0x04
#define SYS_CLK_PLL_STATUS 0x08

#define PLL_SOURCE_MASK 0x00400000
#define PLL_CONFIG_CLEAR 0xF0FC8000

#define PLL_M_BOUNDARY1 2
#define PLL_M_BOUNDARY2 63

#define PLL_N_BOUNDARY1 192
#define PLL_N_BOUNDARY2 432
#define PLL_N_SHIFTING 6

#define PLL_Q_BOUNDARY1 2
#define PLL_Q_BOUNDARY2 15
#define PLL_Q_SHIFTING 24

#define PLL_P_VALUE1 2
#define PLL_P_VALUE2 4
#define PLL_P_VALUE3 6
#define PLL_P_VALUE4 8
#define PLL_P_SHIFTING 16

#define APB_HIGH_PRESCALAR_CLEAR 0xFFFF1FFF
#define APB_LOW_PRESCALAR_CLEAR 0xFFFFE3FF
#define AHB_PRESCALAR_CLEAR 0xFFFFFF0F

/****************************************************************************************
 *                        	              Types                                         *
 ****************************************************************************************/

typedef struct
{
	u32 RCC_CR;
	u32 RCC_PLLCFGR;
	u32 RCC_CFGR;
	u32 RCC_CIR;
	u32 RCC_AHB1RSTR;
	u32 RCC_AHB2RSTR;
	u32 RCC_Reserved1;
	u32 RCC_Reserved2;
	u32 RCC_APB1RSTR;
	u32 RCC_APB2RSTR;
	u32 RCC_Reserved3;
	u32 RCC_Reserved4;
	u32 RCC_AHB1ENR;
	u32 RCC_AHB2ENR;
	u32 RCC_Reserved5;
	u32 RCC_Reserved6;
	u32 RCC_APB1ENR;
	u32 RCC_APB2ENR;
	u32 RCC_Reserved7;
	u32 RCC_Reserved8;
	u32 RCC_AHB1LPENR;
	u32 RCC_AHB2LPENR;
	u32 RCC_Reserved9;
	u32 RCC_Reserved10;
	u32 RCC_APB1LPENR;
	u32 RCC_APB2LPENR;
	u32 RCC_Reserved11;
	u32 RCC_Reserved12;
	u32 RCC_BDCR;
	u32 RCC_CSR;
	u32 RCC_Reserved13;
	u32 RCC_Reserved14;
	u32 RCC_SSCGR;
	u32 RCC_PLLI2SCFGR;
	u32 RCC_Reserved15;
	u32 RCC_DCKCFGR;

}RCC_Peri_t;


/****************************************************************************************
 *                        	            Variableles                                     *
 ****************************************************************************************/

static volatile RCC_Peri_t * const RCC=(volatile RCC_Peri_t*)(RCC_BASE_ADD);


/****************************************************************************************
 *                        	              Static Functions                              *
 ****************************************************************************************/
/**
 *@brief  : Function to Check if Clock is Ready.
 *@param  : Clock (HSI,HSE,PLL).
 *@return : Error State
 */
static RCC_Error_t RCC_GetReadyStatus(u32 Clk_Rdy);
/**
 *@brief  : Function to Get The Current Sys Clock.
 *@param  : Void.
 *@return : The Sys Clock Status
 */
static u32 RCC_GetSysClk(void);
/**
 *@brief  : Function to Check if The Clock is Enabled or Not.
 *@param  : Clock (HSI,HSE,PLL).
 *@return : 0 if Not Enabled
 */
static u32 RCC_GetClkStatus(u32 Clk);

/****************************************************************************************
 *                        	              Function Implementations                      *
 ****************************************************************************************/

RCC_Error_t RCC_EnableClk(u32 CLK)
{
	RCC_Error_t Ret_RCCErrorStatus=RCC_NOK;

	/*Enable HSI CLK*/
	if (CLK == CLK_HSI)
	{
		RCC->RCC_CR|=CLK_HSI;
		/*Check if Clock is Ready*/
		Ret_RCCErrorStatus=RCC_GetReadyStatus(CLK_RDY_HSI);
	}
	/*Enable HSE CLK*/
	else if(CLK == CLK_HSE)
	{
		RCC->RCC_CR|=CLK_HSE;
		/*Check if Clock is Ready*/
		Ret_RCCErrorStatus=RCC_GetReadyStatus(CLK_RDY_HSE);
	}
	/*Enable PLL CLK*/
	else if(CLK == CLK_PLL)
	{
		RCC->RCC_CR|=CLK_PLL;
		/*Check if Clock is Ready*/
		Ret_RCCErrorStatus=RCC_GetReadyStatus(CLK_RDY_PLL);
	}
	else
	{
		Ret_RCCErrorStatus=RCC_InvalidClk;
	}

	return Ret_RCCErrorStatus;
}

RCC_Error_t RCC_DisableClk(u32 Clk)
{
	RCC_Error_t Ret_RCCErrorStatus=RCC_NOK;

	/*Get The Current System clock*/
	u8 Loc_SysClk=RCC_GetSysClk();

	 if(Clk == CLK_HSI)
	 {
		 /*Check if the Clock is Set as System Clock*/
		 if(Loc_SysClk == SYS_CLK_HSI_STATUS)
		 {
			 Ret_RCCErrorStatus=RCC_NOK;
		 }
		 else
		 {
			 RCC->RCC_CR &= ~ CLK_HSI;
		 }
	 }
	 else if (Clk == CLK_HSE)
	 {
		 /*Check if the Clock is Set as System Clock*/
		 if(Loc_SysClk == SYS_CLK_HSE_STATUS)
		 {
			 Ret_RCCErrorStatus=RCC_NOK;
		 }
		 else
		 {
			 RCC->RCC_CR &= ~ CLK_HSE;
		 }
	 }
	 else if(Clk == CLK_PLL)
	 {
		 /*Check if the Clock is Set as System Clock*/
		 if(Loc_SysClk == SYS_CLK_PLL_STATUS)
		 {
			 Ret_RCCErrorStatus=RCC_NOK;
		 }
		 else
		 {
			 RCC->RCC_CR &= ~ CLK_PLL;
		 }
	 }
	 else
	 {
		 Ret_RCCErrorStatus=RCC_InvalidClk;
	 }

	 return Ret_RCCErrorStatus;
}

RCC_Error_t RCC_SelectSysClk(u32 Sys)
{
	RCC_Error_t Ret_RCCErrorStatus=RCC_NOK;

	if(Sys == SYS_CLK_HSI)
	{
		/*Check if The Clock is Ready*/
		if(RCC_GetReadyStatus(CLK_RDY_HSI))
		{
			/*Temporary Var to Store the CFGR Register*/
			u32 Loc_Temp=RCC->RCC_CFGR;
			/*Clear The Sys Clock Bits*/
			Loc_Temp&=SYS_CLK_CLEAR;
			/*Set The Sys Clk*/
			Loc_Temp|=Sys;
			/*Store the Var in The Register*/
			RCC->RCC_CFGR=Loc_Temp;
			Ret_RCCErrorStatus=RCC_OK;
		}
		else
		{
			Ret_RCCErrorStatus=RCC_NOK;
		}
	}
	else if(Sys == SYS_CLK_HSE)
	{
		/*Check if The Clock is Ready*/
		if(RCC_GetReadyStatus(CLK_RDY_HSE))
		{
			u32 Loc_Temp=RCC->RCC_CFGR;
			Loc_Temp&=SYS_CLK_CLEAR;
			Loc_Temp|=Sys;
			RCC->RCC_CFGR=Loc_Temp;
			Ret_RCCErrorStatus=RCC_OK;
		 }
		else
		{
			Ret_RCCErrorStatus=RCC_NOK;
		}
	}
	else if(Sys == SYS_CLK_PLL)
	{
		/*Check if The Clock is Ready*/
		if(RCC_GetReadyStatus(CLK_RDY_PLL))
		{
			u32 Loc_Temp=RCC->RCC_CFGR;
			Loc_Temp&=SYS_CLK_CLEAR;
			Loc_Temp|=Sys;
			RCC->RCC_CFGR=Loc_Temp;
			Ret_RCCErrorStatus=RCC_OK;
		 }
		else
		{
			Ret_RCCErrorStatus=RCC_NOK;
		}
	}
	else
	{
		Ret_RCCErrorStatus=RCC_InvalidClk;
	}
	return Ret_RCCErrorStatus;
}

RCC_Error_t RCC_SelectPLLSource(RCC_PLL_Source_t RCC_PLL_Source)
{
	RCC_Error_t Ret_RCCErrorStatus=RCC_NOK;

	/*Check if PLL is Enabled*/
	if(RCC_GetClkStatus(CLK_PLL))
	{
		Ret_RCCErrorStatus=RCC_NOK;
	}
	else
	{
		switch(RCC_PLL_Source)
		{
		case RCC_PLL_Source_HSI:
			/*Check if HSI is Ready */
			Ret_RCCErrorStatus=RCC_GetReadyStatus(CLK_RDY_HSI);

			if(Ret_RCCErrorStatus==RCC_OK)
			{
				RCC->RCC_PLLCFGR &=~ PLL_SOURCE_MASK;
			}
			else
			{}
			break;

			/*Check if HSE is Ready */
			case RCC_PLL_Source_HSE:
			Ret_RCCErrorStatus=RCC_GetReadyStatus(CLK_RDY_HSE);
			if(Ret_RCCErrorStatus==RCC_OK)
			{
		    	RCC->RCC_PLLCFGR |= PLL_SOURCE_MASK;
			}
			else
			{}
			break;

			default:
				Ret_RCCErrorStatus=RCC_InvalidClk;
				break;
		}
	}

	return Ret_RCCErrorStatus;
}

RCC_Error_t RCC_ConfigurePLL(u32 PLL_M,u32 PLL_N,u32 PLL_P,u32 PLL_Q)
{
	RCC_Error_t Ret_RCCErrorStatus = RCC_NOK;

	/*Check if PLL is Enabled*/
	if(RCC_GetClkStatus(CLK_PLL))
	{
		Ret_RCCErrorStatus = RCC_NOK;
	}
	else if(PLL_M > PLL_M_BOUNDARY2 || PLL_M < PLL_M_BOUNDARY1)
	{
		Ret_RCCErrorStatus = RCC_NOK;
	}
	else if(PLL_N > PLL_N_BOUNDARY2 || PLL_N < PLL_N_BOUNDARY1)
	{
		Ret_RCCErrorStatus = RCC_NOK;
	}
	else if(PLL_Q > PLL_Q_BOUNDARY2 || PLL_Q < PLL_Q_BOUNDARY1)
	{
		Ret_RCCErrorStatus = RCC_NOK;
	}
	else if(!(PLL_P == PLL_P_VALUE1 || PLL_P == PLL_P_VALUE2 || PLL_P == PLL_P_VALUE3 || PLL_P == PLL_P_VALUE4))
	{
		Ret_RCCErrorStatus = RCC_NOK;
	}
	else
	{
		/*Local variable to Hold the Register Value*/
		u32 Loc_Temp=RCC->RCC_PLLCFGR;

		/*Clear the PLL Config Bits*/
		Loc_Temp &= PLL_CONFIG_CLEAR;

		/*Set the PLL Config Bits*/
		Loc_Temp |= PLL_M;
		Loc_Temp |= PLL_N << PLL_N_SHIFTING;
		Loc_Temp |= PLL_P << PLL_P_SHIFTING;
		Loc_Temp |= PLL_Q << PLL_Q_SHIFTING;

		RCC->RCC_PLLCFGR=Loc_Temp;

		Ret_RCCErrorStatus = RCC_OK;
	}
	return Ret_RCCErrorStatus;
}

RCC_Error_t RCC_ConfigureAPBHighPrescalar(u32 APB_High_Prescalar)
{
	RCC_Error_t Ret_RCCErrorStatus = RCC_NOK;

	if(APB_High_Prescalar >  APB_HIGH_PRESCALAR_16)
	{
		Ret_RCCErrorStatus = RCC_NOK;
	}
	else
	{
		u32 Loc_Temp= RCC ->RCC_CFGR;
		Loc_Temp &= APB_HIGH_PRESCALAR_CLEAR;
		Loc_Temp |= APB_High_Prescalar;
		RCC->RCC_CFGR=Loc_Temp;
		Ret_RCCErrorStatus = RCC_OK;
	}

	return Ret_RCCErrorStatus;
}

RCC_Error_t RCC_ConfigureAPBLowPrescalar(u32 APB_Low_Prescalar)
{
	RCC_Error_t Ret_RCCErrorStatus = RCC_NOK;

	if(APB_Low_Prescalar >  APB_LOW_PRESCALAR_16)
	{
		Ret_RCCErrorStatus = RCC_NOK;
	}
	else
	{
		u32 Loc_Temp= RCC ->RCC_CFGR;
		Loc_Temp &= APB_LOW_PRESCALAR_CLEAR;
		Loc_Temp |= APB_Low_Prescalar;
		RCC->RCC_CFGR=Loc_Temp;
		Ret_RCCErrorStatus = RCC_OK;
	}

	return Ret_RCCErrorStatus;
}

RCC_Error_t RCC_ConfigureAHBPrescalar(u32 AHB_Prescalar)
{
	RCC_Error_t Ret_RCCErrorStatus = RCC_NOK;

	if(AHB_Prescalar >  AHB_PRESCALAR_512)
	{
		Ret_RCCErrorStatus = RCC_NOK;
	}
	else
	{
		u32 Loc_Temp= RCC ->RCC_CFGR;
		Loc_Temp &= AHB_PRESCALAR_CLEAR;
		Loc_Temp |= AHB_Prescalar;
		RCC->RCC_CFGR=Loc_Temp;
		Ret_RCCErrorStatus = RCC_OK;
	}

	return Ret_RCCErrorStatus;
}

RCC_Error_t RCC_EnablePeripheral(RCC_Bus_ID_t Bus_ID,u32 Peripheral)
{
	RCC_Error_t Ret_RCCErrorStatus = RCC_NOK;

	switch(Bus_ID)
	{
	case Bus_AHB1:
		RCC->RCC_AHB1ENR |= Peripheral;
		Ret_RCCErrorStatus = RCC_OK;
		break;

	case Bus_AHB2:
		RCC->RCC_AHB2ENR |= Peripheral;
		Ret_RCCErrorStatus = RCC_OK;
		break;

	case Bus_APB1:
		RCC->RCC_APB1ENR |= Peripheral;
		Ret_RCCErrorStatus = RCC_OK;
		break;

	case Bus_APB2:
		RCC->RCC_APB2ENR |= Peripheral;
		Ret_RCCErrorStatus = RCC_OK;
		break;

	default:
		Ret_RCCErrorStatus = RCC_NOK;
	}

	return Ret_RCCErrorStatus;
}


RCC_Error_t RCC_DisablePeripheral(RCC_Bus_ID_t Bus_ID,u32 Peripheral)
{
	RCC_Error_t Ret_RCCErrorStatus = RCC_NOK;

	switch(Bus_ID)
	{
	case Bus_AHB1:
		RCC->RCC_AHB1ENR &=~ Peripheral;
		Ret_RCCErrorStatus = RCC_OK;
		break;

	case Bus_AHB2:
		RCC->RCC_AHB2ENR &=~ Peripheral;
		Ret_RCCErrorStatus = RCC_OK;
		break;

	case Bus_APB1:
		RCC->RCC_APB1ENR &=~ Peripheral;
		Ret_RCCErrorStatus = RCC_OK;
		break;

	case Bus_APB2:
		RCC->RCC_APB2ENR &=~ Peripheral;
		Ret_RCCErrorStatus = RCC_OK;
		break;

	default:
		Ret_RCCErrorStatus = RCC_NOK;
	}

	return Ret_RCCErrorStatus;
}
/****************************************************************************************
 *                        	      Static Function Implementations                       *
 ****************************************************************************************/

/*Get if the Clock is Ready or Not*/
RCC_Error_t RCC_GetReadyStatus(u32 CLK_RDY)
{
	RCC_Error_t Ret_RCCErrorStatus=RCC_NOK;
	u16 Loc_Timeout=1000;

	while(!(RCC->RCC_CR & CLK_RDY) && Loc_Timeout)
	{
		Loc_Timeout--;
	}

	if(Loc_Timeout)
	{
		Ret_RCCErrorStatus=RCC_OK;
	}
	else
	{
     	Ret_RCCErrorStatus=RCC_Timeout;
	}
	return Ret_RCCErrorStatus;
}

/*Get the Currently Selected System Clock*/
u32 RCC_GetSysClk(void)
{
	return RCC->RCC_CFGR & 0x0C;
}

u32 RCC_GetClkStatus(u32 Clk)
{
	return RCC->RCC_CR & Clk;
}
