/*
 * TrafficLightAPP.c
 *
 *  Created on: Mar 23, 2024
 *      Author: Yasmine Mostafa
 */
#include "STD_Types.h"
#include "Error.h"
#include "LED_CFG.h"
#include "LED.h"

#define PERIODICITY_SEC 2

typedef enum
{
	Green,
	Yellow,
	Red
}State_t;

//State_t G_State=Green;

static void GreenLED(void);
static void YellowLED(void);
static void RedLED(void);

//every 2 sec
void TrafficLight(void)
{
	static State_t State=Green;
	static State_t Prev_State=0;
	static u32 Sec = 0;
	Sec += PERIODICITY_SEC;

	switch(State)
	{
	case Green:
		GreenLED();
		if(Sec == 6)
		{
			State=Yellow;
			Prev_State = Green;
			Sec=0;
		}
		break;

	case Yellow:
		YellowLED();
		if(Sec == 2)
		{
			if(Prev_State == Green)
			{
				State = Red;
			}
			else
			{
				State = Green;
			}
			Sec = 0;
		}
		break;

	case Red:
		RedLED();
		if(Sec ==  4)
		{
			State = Yellow;
			Prev_State = Red;
			Sec = 0;
		}
		break;

	}
}

void GreenLED(void)
{
	LED_SetState(LED_Green,LED_ON);
	LED_SetState(LED_Yellow,LED_OFF);
	LED_SetState(LED_Red,LED_OFF);
}

void YellowLED(void)
{
	LED_SetState(LED_Green,LED_OFF);
	LED_SetState(LED_Yellow,LED_ON);
	LED_SetState(LED_Red,LED_OFF);
}

void RedLED(void)
{
	LED_SetState(LED_Green,LED_OFF);
	LED_SetState(LED_Yellow,LED_OFF);
	LED_SetState(LED_Red,LED_ON);
}
