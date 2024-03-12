/*
 * NVIC.c
 *
 *  Created on: Mar 6, 2024
 *      Author: Yasmine Mostafa
 */


/****************************************************************************************
 *                        	              Includes                                      *
 ****************************************************************************************/

#include "Error.h"
#include "STD_Types.h"
#include "NVIC.h"

/****************************************************************************************
 *                        	              Defines                                       *
 ****************************************************************************************/

#define NVIC_BASE_ADD 0xE000E100
#define SCB_BASE_ADD  0xE000ED00

#define REGISTER_WIDTH 32
#define PRIORITY_OFFSET 4
/****************************************************************************************
 *                        	              Types                                         *
 ****************************************************************************************/

typedef struct
{
	u32 NVIC_ISER[8];
	u32 Reserved1[24];
	u32 NVIC_ICER[8];
	u32 Reserved2[24];
	u32 NVIC_ISPR[8];
	u32 Reserved3[24];
	u32 NVIC_ICPR[8];
	u32 Reserved4[24];
	u32 NVIC_IABR[8];
	u32 Reserved5[56];
	//u32 NVIC_IPR[60];
	u8 NVIC_IPR[240];
	u32 Reserved6[644];
	u32 NVIC_STIR;

}NVIC_Peri_t;

typedef struct
{
	u32 SCB_CPUID;
	u32 SCB_ICSR;
	u32 SCB_VTOR;
	u32 SCB_AIRCR;
	u32 SCB_SCR;
	u32 SCB_CCR;
	u32 SCB_SHPR1;
	u32 SCB_SHPR2;
	u32 SCB_SHPR3;
	u32 SCB_SHCSR;
	u32 SCB_CFSR;
	u32 SCB_HFSR;
	u32 Reserved;
	u32 SCB_MMAR;
	u32 SCB_BFAR;
	u32 SCB_AFSR;
}SCB_Peri_t;


/****************************************************************************************
 *                        	            Variables                                     *
 ****************************************************************************************/

static volatile NVIC_Peri_t * const NVIC=(volatile NVIC_Peri_t*)(NVIC_BASE_ADD);
static volatile SCB_Peri_t * const SCB=(volatile SCB_Peri_t*)(SCB_BASE_ADD);

/****************************************************************************************
 *                        	              Function Implementations                      *
 ****************************************************************************************/

Error_t NVIC_EnableIRQ(IRQ_t IRQ)
{
	Error_t Ret_NVICErrorStatus=Error_NOK;

	if(IRQ >= _IRQ_NUM)
	{
		Ret_NVICErrorStatus=Error_InvalidInput;
	}
	else
	{
		u8 Loc_BitNum= IRQ % REGISTER_WIDTH;
		u8 Loc_RegNum = IRQ / REGISTER_WIDTH;

		NVIC -> NVIC_ISER[Loc_RegNum] = (1 << Loc_BitNum);

		Ret_NVICErrorStatus=Error_OK;
	}
	return Ret_NVICErrorStatus;
}

Error_t NVIC_DisableIRQ(IRQ_t IRQ)
{
	Error_t Ret_NVICErrorStatus=Error_NOK;

	if(IRQ >= _IRQ_NUM)
	{
		Ret_NVICErrorStatus=Error_InvalidInput;
	}
	else
	{
		u8 Loc_BitNum= IRQ % REGISTER_WIDTH;
		u8 Loc_RegNum = IRQ / REGISTER_WIDTH;

		NVIC -> NVIC_ICER[Loc_RegNum] = (1 << Loc_BitNum);

	    Ret_NVICErrorStatus=Error_OK;
	}
	return Ret_NVICErrorStatus;
}

Error_t NVIC_SetPending(IRQ_t IRQ)
{
	Error_t Ret_NVICErrorStatus=Error_NOK;

	if(IRQ >= _IRQ_NUM)
	{
		Ret_NVICErrorStatus=Error_InvalidInput;
	}
	else
	{
		u8 Loc_BitNum= IRQ % REGISTER_WIDTH;
		u8 Loc_RegNum = IRQ / REGISTER_WIDTH;

		NVIC -> NVIC_ISPR[Loc_RegNum] = (1 << Loc_BitNum);

		Ret_NVICErrorStatus=Error_OK;
	}
	return Ret_NVICErrorStatus;
}

Error_t NVIC_ClearPending(IRQ_t IRQ)
{
	Error_t Ret_NVICErrorStatus=Error_NOK;

	if(IRQ >= _IRQ_NUM)
	{
		Ret_NVICErrorStatus=Error_InvalidInput;
	}
	else
	{
		u8 Loc_BitNum= IRQ % REGISTER_WIDTH;
		u8 Loc_RegNum = IRQ / REGISTER_WIDTH;

		NVIC -> NVIC_ICPR[Loc_RegNum] = (1 << Loc_BitNum);

		Ret_NVICErrorStatus=Error_OK;
	}
	return Ret_NVICErrorStatus;
}

Error_t NVIC_GetPending(IRQ_t IRQ, u8* Status)
{
	Error_t Ret_NVICErrorStatus=Error_NOK;

	if(Status == NULL)
	{
		Ret_NVICErrorStatus=Error_NULLPointer;
	}
	else if(IRQ >= _IRQ_NUM)
	{
		Ret_NVICErrorStatus=Error_InvalidInput;
	}
	else
	{
		u8 Loc_BitNum= IRQ % REGISTER_WIDTH;
		u8 Loc_RegNum = IRQ / REGISTER_WIDTH;

		*Status = (NVIC -> NVIC_ISPR[Loc_RegNum] >> Loc_BitNum) & 0x01;

		Ret_NVICErrorStatus=Error_OK;
	}
	return Ret_NVICErrorStatus;
}

Error_t NVIC_GetActiveStatus(IRQ_t IRQ , u8 * Status)
{
	Error_t Ret_NVICErrorStatus=Error_NOK;

	if(Status == NULL)
	{
		Ret_NVICErrorStatus=Error_NULLPointer;
	}

	else if(IRQ >= _IRQ_NUM)
	{
		Ret_NVICErrorStatus=Error_InvalidInput;
	}
	else
	{
		u8 Loc_BitNum= IRQ % REGISTER_WIDTH;
		u8 Loc_RegNum = IRQ / REGISTER_WIDTH;

		*Status = (NVIC -> NVIC_IABR[Loc_RegNum] >> Loc_BitNum ) & 0x01;

		Ret_NVICErrorStatus=Error_OK;
	}
	return Ret_NVICErrorStatus;
}

Error_t NVIC_SetPriorityGrouping(u32 PrioritySubGroup)
{
	Error_t Ret_NVICErrorStatus=Error_NOK;

	if(PrioritySubGroup >= PRIORITY_SUBGROUP_0 || PrioritySubGroup <= PRIORITY_SUBGROUP_4)
	{
		SCB -> SCB_AIRCR = PrioritySubGroup;
		Ret_NVICErrorStatus=Error_OK;
	}
	return Ret_NVICErrorStatus;
}

Error_t NVIC_SetPriority(IRQ_t IRQ, u8 Priority)
{
	Error_t Ret_NVICErrorStatus=Error_NOK;

	if(IRQ >= _IRQ_NUM)
	{
		Ret_NVICErrorStatus=Error_InvalidInput;
	}
	else
	{
		NVIC -> NVIC_IPR[IRQ] = (Priority << PRIORITY_OFFSET);
		Ret_NVICErrorStatus=Error_OK;
	}
	return Ret_NVICErrorStatus;
}

/////
Error_t NVIC_GetPriority(IRQ_t IRQ, u8* Priority)
{
	Error_t Ret_NVICErrorStatus=Error_NOK;

	if(Priority == NULL)
	{
		Ret_NVICErrorStatus=Error_NULLPointer;
	}
	else if(IRQ >= _IRQ_NUM)
	{
		Ret_NVICErrorStatus=Error_InvalidInput;
	}
	else
	{
		*Priority = NVIC ->NVIC_IPR[IRQ] >> PRIORITY_OFFSET;
		Ret_NVICErrorStatus=Error_OK;
	}
	return Ret_NVICErrorStatus;
}

Error_t NVIC_GenerateSWInterrupt(IRQ_t IRQ)
{
	Error_t Ret_NVICErrorStatus=Error_NOK;

	if(IRQ >= _IRQ_NUM)
	{
		Ret_NVICErrorStatus=Error_InvalidInput;
	}
	else
	{
		NVIC -> NVIC_STIR = IRQ;
		Ret_NVICErrorStatus=Error_OK;
	}
	return Ret_NVICErrorStatus;
}
