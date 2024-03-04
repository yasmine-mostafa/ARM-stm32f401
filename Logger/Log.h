/*
 * Log.h
 *
 *  Created on: Mar 3, 2024
 *      Author: Yasmine Mostafa
 */

#ifndef LOG_H_
#define LOG_H_

#include <stdarg.h>


typedef enum
{
	Log_OutConsole,
	Log_OutFile
}Log_OutputChannel;

typedef enum
{
	Log_Critical,
	Log_Error,
	Log_Warning,
	Log_Info
}Log_Level;

void Log_SetOutPutChannel(Log_OutputChannel OutputChannel);
void Log_FileCfg(const char* FilePath);
void Log_SetPriority(Log_Level Priority);
void Log_Write(Log_Level Level,const char* message, ...);
#endif /* LOG_H_ */
