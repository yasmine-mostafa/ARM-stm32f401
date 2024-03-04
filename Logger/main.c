/*
 * main.c
 *
 *  Created on: Mar 4, 2024
 *      Author: Yasmine Mostafa
 */

#include "Log.h"

int main()
{
	Log_SetOutPutChannel(Log_OutFile);
	Log_FileCfg("./LogFile.txt");
//	Log_SetOutPutChannel(Log_OutConsole);
	Log_SetPriority(Log_Info);
	Log_Write(Log_Critical, "%s", "Critical message");
	Log_Write(Log_Error,"%s","Error message");
	Log_Write(Log_Warning, "%s","warning message");
	Log_Write(Log_Info,"%s","info message");
	return 0;
}
