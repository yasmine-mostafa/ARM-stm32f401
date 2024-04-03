/*
 * LCD.c
 *
 *  Created on: Apr 1, 2024
 *      Author: Yasmine Mostafa
 */

/****************************************************************************************
 *                        	              Includes                                      *
 ****************************************************************************************/

#include "STD_Types.h"
#include "Error.h"
#include "GPIO.h"
#include "LCD.h"
#include "LCD_CFG.h"
#include <stdlib.h>

/****************************************************************************************
 *                        	              Defines                                       *
 ****************************************************************************************/
#define CONCAT_HELPER(Pin7, Pin6, Pin5, Pin4, Pin3, Pin2, Pin1, Pin0) (0b##Pin7##Pin6##Pin5##Pin4##Pin3##Pin2##Pin1##Pin0)
#define CONCAT(a, b, c, d, e, f, g, h) CONCAT_HELPER(a, b, c, d, e, f, g, h)


#define FUNCTION_SET CONCAT(0,0,1,1,LCD_LINE_DISPLAY,LCD_FONT,0,0)
#define DISPLAY_ON_OFF_CONTROL CONCAT(0,0,0,0,1,LCD_DISPLAY,LCD_CURSOR,LCD_BLINK)
#define DISPLAY_CLEAR 0x01
#define ENTRY_MODE_SET CONCAT(0,0,0,0,0,1,LCD_INCREMENT_MODE,LCD_SHIFT_DISPLAY)

#define NUM_OF_DATA_PINS 8
#define MAX_BUFFER_SIZE 5
#define ENABLED 1
#define DISABLED 0
#define CASE_ZERO 0
#define CASE_OTHER 1
#define FIRST_ROW 0
#define SECOND_ROW 1
#define SECOND_ROW_SHIFT 0x40
#define SET_DDRAM_LOCATION 128
#define COLUMN_NUM 15
#define ONE_LINE_DISPLAY_ROW 0
#define TWO_LINE_DISPLAY_ROW 1
/****************************************************************************************
 *                        	              Types                                         *
 ****************************************************************************************/
typedef enum
{
	State_Off,
	State_Init,
	State_Operational

}LCD_Status_t;

typedef enum
{
	PowerOn,
	FunctionSet,
	DisplayOnOff,
	DisplayClear,
	EntryMode,
	EndInit

}LCD_InitStatus_t;

typedef enum
{
	Empty, ///mfesh string
	//Ready,
	Busy

}LCD_ReqState_t;

typedef enum
{
	NoReq,
	WriteStr,
	WriteNum,
	Clear,
	SetCursor,
	ReqDone
}LCD_ReqType_t;

typedef struct
{
	u8 Row;
	u8 Column;
}LCD_Position_t;

typedef struct
{
    u8* Str;  ///For Write String Request
	u8 Length; ///For Write String Request
	u8 Num; ///for Write NumRequest
	LCD_ReqState_t State;
	LCD_ReqType_t Type;
	LCD_Position_t Position;
//	u8 BufferState;

}LCD_UserReq_t;

/****************************************************************************************
 *                        	            Variables                                     *
 ****************************************************************************************/

LCD_Status_t G_LCDStatus = State_Off;
LCD_UserReq_t G_LCD_UserReq[MAX_BUFFER_SIZE];
u8 G_LCD_CurrBuff = 0;
u8 G_EnableStatus = DISABLED;

extern const LCD_Config_t LCD_Configs[_LCD_Num];

/****************************************************************************************
 *                        	             Static Function Prototypes                      *
 ****************************************************************************************/
static void InitSM(void);

static void SendCommand(u8 Copy_Command);
static void SendData(u8 Copy_Data);
static void Enablecontrol(u8 Copy_State);

static void WriteStrProcess(void);
static void WriteNumProcess(void);
static void ClearScreenProcess(void);
static void SetCursorProcess(void);
static void ReqDoneProcess(void);
/****************************************************************************************
 *                        	              Function Implementations                      *
 ****************************************************************************************/

Error_t LCD_InitAsynch(void)
{
	Error_t Ret_LCDErrorStatus = Error_NOK;

	GPIO_Config_t Loc_LCDStructConfig;
	Loc_LCDStructConfig.Speed = GPIO_SPEED_HIGH;
	Loc_LCDStructConfig.Mode = GPIO_MODE_OUTPUT_PP; /////////////////////

	for(u8 Loc_CounterData = 0; Loc_CounterData < _LCD_Num; Loc_CounterData++)
	{
		Loc_LCDStructConfig.Port = LCD_Configs[Loc_CounterData].Port;
		Loc_LCDStructConfig.Pin = LCD_Configs[Loc_CounterData].Pin;
		Ret_LCDErrorStatus=GPIO_InitPin(&Loc_LCDStructConfig);
	};

	G_LCDStatus = State_Init;
	return Ret_LCDErrorStatus;
}

Error_t LCD_WriteStringAsynch(u8 * Copy_Str)
{
	Error_t Ret_LCDErrorStatus = Error_NOK;

	if(Copy_Str == NULL)
	{
		Ret_LCDErrorStatus = Error_NULLPointer;
	}
	else
	{
		u8 Loc_Counter = 0;
		for(Loc_Counter = 0; Loc_Counter < MAX_BUFFER_SIZE; Loc_Counter++)
		{
			if(G_LCD_UserReq[Loc_Counter].State == Empty)
			{
				G_LCD_UserReq[Loc_Counter].State = Busy;
				G_LCD_UserReq[Loc_Counter].Type = WriteStr;
				G_LCD_UserReq[Loc_Counter].Str = Copy_Str;

			/*	u8 i=0;
							while(G_LCD_UserReq[G_LCD_CurrBuff].Str[i] != '\0')
							{
								i++;
							}
							G_LCD_UserReq[Loc_Counter].Length = i;*/
				Ret_LCDErrorStatus = Error_OK;
				break;
			}
		}
		if(Loc_Counter == MAX_BUFFER_SIZE)
		{
			Ret_LCDErrorStatus = Error_NOK;
		}

	}
	return Ret_LCDErrorStatus;
}

Error_t LCD_WriteNumberAsynch(u8 Copy_Num)
{
	Error_t Ret_LCDErrorStatus = Error_NOK;

	u8 Loc_Counter = 0;
	for(Loc_Counter = 0; Loc_Counter < MAX_BUFFER_SIZE; Loc_Counter++)
	{
		if(G_LCD_UserReq[Loc_Counter].State == Empty)
		{
			G_LCD_UserReq[Loc_Counter].State = Busy;
			G_LCD_UserReq[Loc_Counter].Type = WriteNum;
			G_LCD_UserReq[Loc_Counter].Num = Copy_Num;
			Ret_LCDErrorStatus = Error_OK;
			break;
		}
	}
	if(Loc_Counter == MAX_BUFFER_SIZE)
	{
		Ret_LCDErrorStatus = Error_NOK;
	}

	return Ret_LCDErrorStatus;
}

Error_t LCD_ClearScreenAsynch(void)
{
	Error_t Ret_LCDErrorStatus = Error_NOK;

	u8 Loc_Counter = 0;
	for(Loc_Counter = 0; Loc_Counter < MAX_BUFFER_SIZE; Loc_Counter++)
	{
		if(G_LCD_UserReq[Loc_Counter].State == Empty)
		{
			G_LCD_UserReq[Loc_Counter].State = Busy;
			G_LCD_UserReq[Loc_Counter].Type = Clear;
			Ret_LCDErrorStatus = Error_OK;
			break;
		}
	}
	if(Loc_Counter == MAX_BUFFER_SIZE)
	{
		Ret_LCDErrorStatus = Error_NOK;
	}

	return Ret_LCDErrorStatus;
}

Error_t LCD_SetCursorPositionAsynch(u8 Copy_Row, u8 Copy_Column)
{
	Error_t Ret_LCDErrorStatus = Error_NOK;

#if LCD_LINE_DISPLAY == LCD_ONE_LINE_DISPLAY

	if(Copy_Row > ONE_LINE_DISPLAY_ROW || Copy_Column > COLUMN_NUM)
	{
		Ret_LCDErrorStatus = Error_InvalidInput;
	}
#endif

#if LCD_LINE_DISPLAY == LCD_TWO_LINE_DISPLAY

	if(Copy_Row > TWO_LINE_DISPLAY_ROW || Copy_Column > COLUMN_NUM)
	{
		Ret_LCDErrorStatus = Error_InvalidInput;
	}
#endif
	else
	{
		u8 Loc_Counter = 0;
		for(Loc_Counter = 0; Loc_Counter < MAX_BUFFER_SIZE; Loc_Counter++)
		{
			if(G_LCD_UserReq[Loc_Counter].State == Empty)
			{
				G_LCD_UserReq[Loc_Counter].State = Busy;
				G_LCD_UserReq[Loc_Counter].Type = SetCursor;
				G_LCD_UserReq[Loc_Counter].Position.Row = Copy_Row;
				G_LCD_UserReq[Loc_Counter].Position.Column = Copy_Column;
				Ret_LCDErrorStatus = Error_OK;
				break;
			}
		}
		if(Loc_Counter == MAX_BUFFER_SIZE)
		{
			Ret_LCDErrorStatus = Error_NOK;
		}
	}


	return Ret_LCDErrorStatus;
}
/****************************************************************************************
 *                        	       Static Function Implementations                      *
 ****************************************************************************************/

///every 2 ms
void InitSM(void)
{
	static LCD_InitStatus_t InitState = PowerOn;
	static u32 Time = 0;
	Time += 2; ////
	switch(InitState)
	{
	case PowerOn:
		if(Time == 30) //wait 30 msec
		{
			InitState = FunctionSet;
		}
		break;

	case FunctionSet:
		switch(G_EnableStatus)
		{
		case DISABLED:
			SendCommand(FUNCTION_SET);
			Enablecontrol(GPIO_STATE_HIGH);
			G_EnableStatus = ENABLED;
			break;

		case ENABLED:
			Enablecontrol(GPIO_STATE_LOW);
			G_EnableStatus = DISABLED;
			InitState = DisplayOnOff;
			break;
		}
		break;

	case DisplayOnOff:
		switch(G_EnableStatus)
		{
		case DISABLED:
			SendCommand(DISPLAY_ON_OFF_CONTROL);
			Enablecontrol(GPIO_STATE_HIGH);
			G_EnableStatus = ENABLED;
			break;

		case ENABLED:
			Enablecontrol(GPIO_STATE_LOW);
			G_EnableStatus = DISABLED;
			InitState = DisplayClear;
			break;
		}
		break;

	case DisplayClear:
		switch(G_EnableStatus)
		{
		case DISABLED:
			SendCommand(DISPLAY_CLEAR);
			Enablecontrol(GPIO_STATE_HIGH);
			G_EnableStatus = ENABLED;
			break;

		case ENABLED:
			Enablecontrol(GPIO_STATE_LOW);
			G_EnableStatus = DISABLED;
			InitState =EntryMode;
			break;
		}
		break;

	case EntryMode:
		switch(G_EnableStatus)
		{
		case DISABLED:
			SendCommand(ENTRY_MODE_SET);
			Enablecontrol(GPIO_STATE_HIGH);
			G_EnableStatus = ENABLED;
			break;

		case ENABLED:
			Enablecontrol(GPIO_STATE_LOW);
			G_EnableStatus = DISABLED;
			InitState = EndInit;
			break;
		}
		break;

	case EndInit:
		G_LCDStatus = State_Operational;
		break;
	}

}

void SendCommand(u8 Copy_Command)
{
	GPIO_SetPinValue(LCD_Configs[RS].Port,LCD_Configs[RS].Pin,GPIO_STATE_LOW);
	GPIO_SetPinValue(LCD_Configs[RW].Port,LCD_Configs[RW].Pin,GPIO_STATE_LOW);

	for(u8 Loc_Counter = 0; Loc_Counter < NUM_OF_DATA_PINS; Loc_Counter++)
	{
		GPIO_SetPinValue(LCD_Configs[Loc_Counter].Port,LCD_Configs[Loc_Counter].Pin,(Copy_Command >> Loc_Counter)&0x01);
	}
}

void SendData(u8 Copy_Data)
{
	GPIO_SetPinValue(LCD_Configs[RS].Port,LCD_Configs[RS].Pin,GPIO_STATE_HIGH);
	GPIO_SetPinValue(LCD_Configs[RW].Port,LCD_Configs[RW].Pin,GPIO_STATE_LOW);

	for(u8 Loc_Counter = 0; Loc_Counter < NUM_OF_DATA_PINS; Loc_Counter++)
	{
		GPIO_SetPinValue(LCD_Configs[Loc_Counter].Port,LCD_Configs[Loc_Counter].Pin,(Copy_Data >> Loc_Counter)&0x01);
	}
}

void Enablecontrol(u8 Copy_State)
{
	GPIO_SetPinValue(LCD_Configs[Enable].Port,LCD_Configs[Enable].Pin,Copy_State);
}

void WriteStrProcess(void)
{
	static u8 Loc_Counter = 0;

	if(G_LCD_UserReq[G_LCD_CurrBuff].Str[Loc_Counter] != '\0')
	{
		switch(G_EnableStatus)
		{
		case DISABLED:
			SendData(G_LCD_UserReq[G_LCD_CurrBuff].Str[Loc_Counter]);
			Enablecontrol(GPIO_STATE_HIGH);
			G_EnableStatus = ENABLED;
			break;

		case ENABLED:
			Enablecontrol(GPIO_STATE_LOW);
			G_EnableStatus = DISABLED;
			Loc_Counter++;
			break;
		}
	}
	else
	{
		G_LCD_UserReq[G_LCD_CurrBuff].Type = ReqDone;
		Loc_Counter=0;
	}
}

void WriteNumProcess(void)
{

	static u32 Loc_ReversedNum =1;
	static u8 Loc_Case = CASE_ZERO;

	switch(Loc_Case )
	{
	case 0:
		if(G_LCD_UserReq[G_LCD_CurrBuff].Num == 0)
		{
			switch(G_EnableStatus)
			{
			case DISABLED:
				SendData('0'+G_LCD_UserReq[G_LCD_CurrBuff].Num);
				Enablecontrol(GPIO_STATE_HIGH);
				G_EnableStatus = ENABLED;
				break;

			case ENABLED:
				Enablecontrol(GPIO_STATE_LOW);
				G_EnableStatus = DISABLED;
				G_LCD_UserReq[G_LCD_CurrBuff].Type = ReqDone;
				break;
			}
		}
		else
		{
			Loc_Case = CASE_OTHER;
		}
		break;

	case CASE_OTHER:
		while(G_LCD_UserReq[G_LCD_CurrBuff].Num != 0)
		{
			Loc_ReversedNum *=10;
			Loc_ReversedNum += G_LCD_UserReq[G_LCD_CurrBuff].Num%10;
			G_LCD_UserReq[G_LCD_CurrBuff].Num /=10;
		}

		if(Loc_ReversedNum != 1)
		{
			switch(G_EnableStatus)
			{
			case DISABLED:
				SendData('0'+Loc_ReversedNum%10);
				Enablecontrol(GPIO_STATE_HIGH);
				G_EnableStatus = ENABLED;
				break;

			case ENABLED:
				Enablecontrol(GPIO_STATE_LOW);
				G_EnableStatus = DISABLED;
				Loc_ReversedNum/=10;
				break;
			}
		}
		else
		{
			G_LCD_UserReq[G_LCD_CurrBuff].Type = ReqDone;
			Loc_Case = CASE_ZERO;
		}
		break;
	}




}

void ClearScreenProcess(void)
{
	switch(G_EnableStatus)
	{
	case DISABLED:
		SendCommand(DISPLAY_CLEAR);
		Enablecontrol(GPIO_STATE_HIGH);
	    G_EnableStatus = ENABLED;
		break;

	case ENABLED:
		Enablecontrol(GPIO_STATE_LOW);
		G_EnableStatus = DISABLED;
		G_LCD_UserReq[G_LCD_CurrBuff].Type = ReqDone;
		break;
	}
}

void SetCursorProcess(void)
{
	u8 Loc_Location = 0;
	switch(G_EnableStatus)
	{
	case DISABLED:
		if(G_LCD_UserReq[G_LCD_CurrBuff].Position.Row == FIRST_ROW)
		{
			Loc_Location = G_LCD_UserReq[G_LCD_CurrBuff].Position.Column;
		    SendCommand(SET_DDRAM_LOCATION+Loc_Location);
		}
		else if(G_LCD_UserReq[G_LCD_CurrBuff].Position.Row == SECOND_ROW)
		{
			Loc_Location = G_LCD_UserReq[G_LCD_CurrBuff].Position.Column + SECOND_ROW_SHIFT;
		    SendCommand(SET_DDRAM_LOCATION+Loc_Location);
		}
		Enablecontrol(GPIO_STATE_HIGH);
	    G_EnableStatus = ENABLED;
		break;

	case ENABLED:
		Enablecontrol(GPIO_STATE_LOW);
		G_EnableStatus = DISABLED;
		G_LCD_UserReq[G_LCD_CurrBuff].Type = ReqDone;
		break;
	}
}

void ReqDoneProcess(void)
{
	G_LCD_UserReq[G_LCD_CurrBuff].Type = ReqDone;
	G_LCD_UserReq[G_LCD_CurrBuff].State = Empty;
	G_LCD_CurrBuff++;
	if(G_LCD_CurrBuff == MAX_BUFFER_SIZE)
	{
		G_LCD_CurrBuff = 0;
	}
}
/****************************************************************************************
 *                        	              Runnables                                   *
 ****************************************************************************************/

///Every 2 ms?
void LCD_Task(void)
{
	if(G_LCDStatus == State_Init )
	{
		InitSM();
	}
	else if(G_LCDStatus == State_Operational )
	{
		//&& G_LCD_UserReq[G_LCD_CurrBuff].State == Busy
		switch(G_LCD_UserReq[G_LCD_CurrBuff].Type)
		{
		case WriteStr:
			WriteStrProcess();
			break;

		case WriteNum:
			WriteNumProcess();
			break;

		case Clear:
			ClearScreenProcess();
			break;

		case SetCursor:
			SetCursorProcess();
			break;

		case ReqDone:
			ReqDoneProcess();
			break;

		default:
			G_LCD_CurrBuff++;
			if(G_LCD_CurrBuff == MAX_BUFFER_SIZE)
			{
				G_LCD_CurrBuff = 0;
			}
			break;
		}
	}

}
