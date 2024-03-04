/*
 * Log.c
 *
 *  Created on: Mar 3, 2024
 *      Author: Yasmine Mostafa
 */

#include "Log.h"
#include <stdio.h>
#include <time.h>

Log_OutputChannel SelectedChannel = 0;
Log_Level SelectedPriority = 0;
const char* SelectedFilePath = "./LogFile.txt";

void Log_SetOutPutChannel(Log_OutputChannel OutputChannel)
{
	SelectedChannel = OutputChannel;
}


void Log_FileCfg(const char* FilePath)
{
	SelectedFilePath=FilePath;
}

void Log_SetPriority(Log_Level Priority)
{
	SelectedPriority = Priority;
}

void Log_Write(Log_Level LogLevel,const char* message, ...)
{
	va_list args;
	va_start(args, message);

	char* Level[4]={"CRITICAL","ERROR","WARNING","INFO"};

	// Get current timestamp
	time_t rawtime;
	struct tm* timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	char timestamp[20];
	strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", timeinfo);

	// Open the log file
	FILE* LogFile = fopen(SelectedFilePath, "a");


	if(LogLevel <= SelectedPriority)
	{
		switch(SelectedChannel)
		{
		case Log_OutFile:
			if(LogFile != NULL)
			{
				fprintf(LogFile, "[%s] [%s]: ", timestamp, Level[LogLevel]);
				vfprintf(LogFile, message, args);
				fprintf(LogFile, "\n");
				fclose(LogFile);
			}
			break;

		case Log_OutConsole:
			printf("[%s] [%s]: ", timestamp, Level[LogLevel]);
			vprintf(message, args);
			printf("\n");
			break;

		default:
			perror("Invalid Output Channel");
		}
	}

	va_end(args);
}
