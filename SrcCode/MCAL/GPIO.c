/*
 * GPIO.c
 *
 *  Created on: Feb 19, 2024
 *      Author: Yasmine Mostafa
 */

/****************************************************************************************
 *                        	              Includes                                      *
 ****************************************************************************************/

#include "Error.h"
#include "STD_Types.h"
#include "GPIO.h"

/****************************************************************************************
 *                        	              Defines                                       *
 ****************************************************************************************/

#define MODER_CLEAR_MASK 0x3
#define OTYPER_CLEAR_MASK 0x1
#define PUPDR_CLEAR_MASK 0x3
#define OSPEEDR_CLEAR_MASK 0x3
#define AFR_CLEAR_MASK 0x0000000F

#define NUM_OF_PINS 16

#define BITS_OFFSET_2 2
#define BITS_OFFSET_3 3
#define BITS_OFFSET_4 4

/****************************************************************************************
 *                        	              Types                                         *
 ****************************************************************************************/

typedef struct
{
	u32 GPIO_MODER;
	u32 GPIO_OTYPER;
	u32 GPIO_OSPEEDR;
	u32 GPIO_PUPDR;
	u32 GPIO_IDR;
	u32 GPIO_ODR;
	u32 GPIO_BSRR;
	u32 GPIO_LCKR;
	u32 GPIO_AFRL;
	u32 GPIO_AFRH;

}GPIO_Peri_t;


/****************************************************************************************
 *                        	              Function Implementations                      *
 ****************************************************************************************/

Error_t GPIO_InitPin(GPIO_Config_t * GPIO_Config)
{
	Error_t Ret_GPIOErrorStatus=Error_NOK;

	if(GPIO_Config == NULL)
	{
		Ret_GPIOErrorStatus=Error_NULLPointer;
	}
	else if(GPIO_Config->Pin > GPIO_PIN15)
	{
		Ret_GPIOErrorStatus=Error_InvalidInput;
	}
	else if((GPIO_Config -> Port != GPIO_PORTA) && (GPIO_Config -> Port != GPIO_PORTB) && (GPIO_Config -> Port != GPIO_PORTC) && (GPIO_Config -> Port != GPIO_PORTD) && (GPIO_Config -> Port != GPIO_PORTE) && (GPIO_Config -> Port != GPIO_PORTH))
	{
		Ret_GPIOErrorStatus=Error_InvalidInput;
	}
	else
	{
		/*Port Mode Reg*/
		u32 Loc_Temp=0;
		Loc_Temp = ((GPIO_Peri_t*)(GPIO_Config->Port))->GPIO_MODER;
		Loc_Temp &=~ (MODER_CLEAR_MASK << (GPIO_Config->Pin)*BITS_OFFSET_2);
		Loc_Temp |= (GPIO_Config->Mode & MODER_CLEAR_MASK)<<((GPIO_Config->Pin)*BITS_OFFSET_2);
		((GPIO_Peri_t*)(GPIO_Config->Port))->GPIO_MODER = Loc_Temp;

		/*Port Output Type Reg*/
		Loc_Temp = ((GPIO_Peri_t*)(GPIO_Config->Port))->GPIO_OTYPER;
		Loc_Temp &=~ (OTYPER_CLEAR_MASK << (GPIO_Config->Pin)) ;
		Loc_Temp |= ((GPIO_Config->Mode >> BITS_OFFSET_2)  &OTYPER_CLEAR_MASK ) << (GPIO_Config -> Pin);
		((GPIO_Peri_t*)(GPIO_Config->Port))->GPIO_OTYPER = Loc_Temp;

		/*Port Pull up/ Pull Down Reg*/
		Loc_Temp = ((GPIO_Peri_t*)(GPIO_Config->Port))->GPIO_PUPDR;
		Loc_Temp &=~ (PUPDR_CLEAR_MASK << (GPIO_Config->Pin)*BITS_OFFSET_2);
		Loc_Temp |= ((GPIO_Config->Mode >> BITS_OFFSET_3)  & PUPDR_CLEAR_MASK ) << (GPIO_Config -> Pin)*BITS_OFFSET_2;
		((GPIO_Peri_t*)(GPIO_Config->Port))->GPIO_PUPDR = Loc_Temp;

		/*Port Output Speed Reg*/
		Loc_Temp = ((GPIO_Peri_t*)(GPIO_Config->Port))->GPIO_OSPEEDR;
		Loc_Temp &=~ (OSPEEDR_CLEAR_MASK << (GPIO_Config->Pin)*BITS_OFFSET_2);
		Loc_Temp |= ((GPIO_Config->Speed) << (GPIO_Config->Pin)*BITS_OFFSET_2);
		((GPIO_Peri_t*)(GPIO_Config->Port))->GPIO_OSPEEDR = Loc_Temp;

		Ret_GPIOErrorStatus=Error_OK;
	}
	return Ret_GPIOErrorStatus;
}

Error_t GPIO_InitPinAF(GPIO_Config_t * GPIO_Config,u32 Copy_GPIO_AF)
{
	Error_t Ret_GPIOErrorStatus=Error_NOK;

	if(GPIO_Config == NULL)
	{
		Ret_GPIOErrorStatus=Error_NULLPointer;
	}
	else if(GPIO_Config->Pin > GPIO_PIN15)
	{
		Ret_GPIOErrorStatus=Error_InvalidInput;
	}
	else if((GPIO_Config -> Port != GPIO_PORTA) && (GPIO_Config -> Port != GPIO_PORTB) && (GPIO_Config -> Port != GPIO_PORTC) && (GPIO_Config -> Port != GPIO_PORTD) && (GPIO_Config -> Port != GPIO_PORTE) && (GPIO_Config -> Port != GPIO_PORTH))
	{
		Ret_GPIOErrorStatus=Error_InvalidInput;
	}
	else
	{
		/*Port Mode Reg*/
		u32 Loc_Temp=0;
		Loc_Temp = ((GPIO_Peri_t*)(GPIO_Config->Port))->GPIO_MODER;
		Loc_Temp &=~ (MODER_CLEAR_MASK << (GPIO_Config->Pin)*BITS_OFFSET_2);
		Loc_Temp |= (GPIO_Config->Mode & MODER_CLEAR_MASK)<<((GPIO_Config->Pin)*BITS_OFFSET_2);
		((GPIO_Peri_t*)(GPIO_Config->Port))->GPIO_MODER = Loc_Temp;

		/*Port Output Type Reg*/
		Loc_Temp = ((GPIO_Peri_t*)(GPIO_Config->Port))->GPIO_OTYPER;
		Loc_Temp &=~ (OTYPER_CLEAR_MASK << (GPIO_Config->Pin)) ;
		Loc_Temp |= ((GPIO_Config->Mode >> BITS_OFFSET_2)  &OTYPER_CLEAR_MASK ) << (GPIO_Config -> Pin);
		((GPIO_Peri_t*)(GPIO_Config->Port))->GPIO_OTYPER = Loc_Temp;

		/*Port Pull up/ Pull Down Reg*/
		Loc_Temp = ((GPIO_Peri_t*)(GPIO_Config->Port))->GPIO_PUPDR;
		Loc_Temp &=~ (PUPDR_CLEAR_MASK << (GPIO_Config->Pin)*BITS_OFFSET_2);
		Loc_Temp |= ((GPIO_Config->Mode >> BITS_OFFSET_3)  & PUPDR_CLEAR_MASK ) << (GPIO_Config -> Pin)*BITS_OFFSET_2;
		((GPIO_Peri_t*)(GPIO_Config->Port))->GPIO_PUPDR = Loc_Temp;

		/*Port Output Speed Reg*/
		Loc_Temp = ((GPIO_Peri_t*)(GPIO_Config->Port))->GPIO_OSPEEDR;
		Loc_Temp &=~ (OSPEEDR_CLEAR_MASK << (GPIO_Config->Pin)*BITS_OFFSET_2);
		Loc_Temp |= ((GPIO_Config->Speed) << (GPIO_Config->Pin)*BITS_OFFSET_2);
		((GPIO_Peri_t*)(GPIO_Config->Port))->GPIO_OSPEEDR = Loc_Temp;

		if(GPIO_Config->Pin <= 7)
		{
			Loc_Temp = ((GPIO_Peri_t*)(GPIO_Config->Port))->GPIO_AFRL;
			Loc_Temp &=~ (AFR_CLEAR_MASK << (GPIO_Config->Pin)*BITS_OFFSET_4);
			Loc_Temp |= (Copy_GPIO_AF << (GPIO_Config->Pin)*BITS_OFFSET_4);
			((GPIO_Peri_t*)(GPIO_Config->Port))->GPIO_AFRL = Loc_Temp;
		}
		else
		{
			Loc_Temp = ((GPIO_Peri_t*)(GPIO_Config->Port))->GPIO_AFRH;
			Loc_Temp &=~ (AFR_CLEAR_MASK << (GPIO_Config->Pin-8)*BITS_OFFSET_4);
			Loc_Temp |= (Copy_GPIO_AF << (GPIO_Config->Pin-8)*BITS_OFFSET_4);
			((GPIO_Peri_t*)(GPIO_Config->Port))->GPIO_AFRH = Loc_Temp;
		}
		Ret_GPIOErrorStatus=Error_OK;
	}
	return Ret_GPIOErrorStatus;

}

Error_t GPIO_SetPinValue(void* Port, u8 Pin, u8 State)
{
	Error_t Ret_GPIOErrorStatus=Error_NOK;

	if(Port == NULL)
	{
		Ret_GPIOErrorStatus=Error_NULLPointer;
	}
	else if(Pin > GPIO_PIN15)
	{
		Ret_GPIOErrorStatus=Error_InvalidInput;
	}
	else if((Port != GPIO_PORTA) && (Port != GPIO_PORTB) && (Port != GPIO_PORTC) && (Port != GPIO_PORTD) && (Port != GPIO_PORTE) && (Port != GPIO_PORTH))
	{
		Ret_GPIOErrorStatus=Error_InvalidInput;
	}
	else
	{
		switch(State)
		{
		case GPIO_STATE_HIGH:
			((GPIO_Peri_t*)(Port))->GPIO_BSRR |= 1 << Pin;
			Ret_GPIOErrorStatus=Error_OK;
			break;

		case GPIO_STATE_LOW:
			((GPIO_Peri_t* )(Port))->GPIO_BSRR |= 1 << (Pin + NUM_OF_PINS);
			Ret_GPIOErrorStatus=Error_OK;
			break;

		default:
			Ret_GPIOErrorStatus=Error_InvalidInput;
			break;
		}
	}
	return Ret_GPIOErrorStatus;
}

Error_t GPIO_GetPinValue(void* Port, u8 Pin, u8 * State)
{
	Error_t Ret_GPIOErrorStatus=Error_NOK;
	if(Port == NULL)
	{
		Ret_GPIOErrorStatus=Error_NULLPointer;
	}
	else if(Pin > GPIO_PIN15)
	{
		Ret_GPIOErrorStatus=Error_InvalidInput;
	}
	else if((Port != GPIO_PORTA) && (Port != GPIO_PORTB) && (Port != GPIO_PORTC) && (Port != GPIO_PORTD) && (Port != GPIO_PORTE) && (Port != GPIO_PORTH))
	{
		Ret_GPIOErrorStatus=Error_InvalidInput;
	}
	else if(State == NULL)
	{
		Ret_GPIOErrorStatus=Error_NULLPointer;
	}
	else
	{
		*State = (((GPIO_Peri_t* )(Port))->GPIO_IDR >> Pin) & 1;
		Ret_GPIOErrorStatus=Error_OK;
	}
	return Ret_GPIOErrorStatus;
}
