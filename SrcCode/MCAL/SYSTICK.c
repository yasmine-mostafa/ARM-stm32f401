/*
 * SYSTICK.c
 *
 *  Created on: Mar 14, 2024
 *      Author: Yasmine Mostafa
 */

/****************************************************************************************
 *                        	              Includes                                      *
 ****************************************************************************************/

#include "STD_TYPES.h"
#include "Error.h"
#include "SYSTICK.h"
#include "SYSTICK_CFG.h"

/****************************************************************************************
 *                        	              Defines                                       *
 ****************************************************************************************/

#define SYSTICK_BASE_ADD 0xE000E010

#define TIME_MIN 0x00000001
#define TIME_MAX 0x00FFFFFF

#define STK_CTRL_MASK 0xFFFFFFF9
#define STK_START 0x1
#define STK_STOP 0xFFFFFFFE

/****************************************************************************************
 *                        	              Types                                         *
 ****************************************************************************************/

typedef struct
{
	u32 STK_CTRL;
	u32 STK_LOAD;
	u32 STK_VAL;
	u32 STK_CALIB;
}STK_Peri_t;

/****************************************************************************************
 *                        	            Variables                                    *
 ****************************************************************************************/

static volatile STK_Peri_t * const STK=(volatile STK_Peri_t*)(SYSTICK_BASE_ADD);

u32 G_ClkFreq = 0;

static STK_Cbf_t APP_Cbf;;

/****************************************************************************************
 *                        	              Function Implementations                      *
 ****************************************************************************************/

Error_t STK_Init(u32 Clk, u32 Mode)
{
	Error_t Ret_STKErrorStatus=Error_NOK;

	if(Clk != CLK_AHB && Clk != CLK_AHB_8)
	{
		Ret_STKErrorStatus=Error_InvalidInput;
	}
	else if (Mode != MODE_ENABLE_INT && Mode != MODE_DISABLE_INT)
	{
		Ret_STKErrorStatus=Error_InvalidInput;
	}
	else
	{
		if(Clk == CLK_AHB)
		{
			G_ClkFreq = CLK_FREQUENCY;
		}
		else
		{
			G_ClkFreq = CLK_FREQUENCY / 8;
		}

		u32 Loc_Temp = STK -> STK_CTRL;
		Loc_Temp &= STK_CTRL_MASK;
		Loc_Temp |= Clk;
		Loc_Temp |= Mode;
		STK -> STK_CTRL = Loc_Temp;
		Ret_STKErrorStatus=Error_OK;
	}

	return Ret_STKErrorStatus;
}


Error_t STK_SetTimeMs(u32 TimeMs)
{
	Error_t Ret_STKErrorStatus=Error_NOK;

	u32 Loc_TimeTemp = ((TimeMs * G_ClkFreq )/1000) - 1;

	if(Loc_TimeTemp < TIME_MIN || Loc_TimeTemp > TIME_MAX)
	{
		Ret_STKErrorStatus=Error_InvalidInput;
	}
	else
	{
		STK -> STK_LOAD = Loc_TimeTemp;
		Ret_STKErrorStatus=Error_OK;
	}

	return Ret_STKErrorStatus;
}
Error_t STK_Start(void)
{
	Error_t Ret_STKErrorStatus=Error_OK;
	STK -> STK_CTRL |= STK_START;
	return Ret_STKErrorStatus;

}
Error_t STK_Stop(void)
{
	Error_t Ret_STKErrorStatus=Error_OK;
	STK -> STK_CTRL &= STK_STOP;
	return Ret_STKErrorStatus;
}

Error_t STK_SetCallBack(STK_Cbf_t Copy_cbf)
{
	Error_t Ret_STKErrorStatus=Error_NOK;

	if(Copy_cbf == NULL)
	{
		Ret_STKErrorStatus=Error_NULLPointer;
	}
	else
	{
		Ret_STKErrorStatus=Error_OK;
		APP_Cbf = Copy_cbf;
	}

	return Ret_STKErrorStatus;
}


void SysTick_Handler(void)
{
	if(APP_Cbf)
	{
		APP_Cbf();
	}
}
