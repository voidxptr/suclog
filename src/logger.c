#include "../include/suclog.h"
#include <stdarg.h>
#include <stdio.h>
#include <time.h>

FILE* logFilePtr;
char logFlags = (char)(LOGLevelAll | LOGFlagEnabled | LOGFlagFile);


char getLogLevel()
{
	return LOGLevel & logFlags;
}

char getLogFlag(char flag)
{
	if(!(LOGFlagEnabled & logFlags)) return (char)0b0;

	return logFlags & flag;
}

void setLogFlags(char flags)
{
	logFlags = flags;
}


// -- -- -- -- -- -- -- -- Log File -- -- -- -- -- -- -- -- //

void openLogFile(char* filename, char forceEnableLogFile)
{
	if(forceEnableLogFile)
		logFlags |= LOGFlagFile;
	
	logFilePtr = fopen(filename, "a");

	if(ferror(logFilePtr))
		printf("%sError encountered during file opening.%s\n", ANSI_COLOR_RED, ANSI_COLOR_RESET);
}

void closeLogFile()
{
	if(logFilePtr) fclose(logFilePtr);
}


// -- -- -- -- -- -- -- -- Log File Printing -- -- -- -- -- -- -- -- //

void vlogToFile(char *fmt, va_list args)
{
	if(!logFilePtr) return;
	
	vfprintf(logFilePtr, fmt, args);
	if(ferror(logFilePtr))
		printf("%sError encountered during file writing.%s\n", ANSI_COLOR_RED, ANSI_COLOR_RESET);
}

void vlogFmt(char* fmt, va_list args)
{
	if(!getLogFlag(LOGFlagEnabled)) return;

	va_list argsCpy; va_copy(argsCpy, args);

	vprintf(fmt, argsCpy);
	va_end(argsCpy);

	if(getLogFlag(LOGFlagFile))
	{
		va_copy(argsCpy, args);
		vlogToFile(fmt, argsCpy);
		va_end(argsCpy);
	}
}

void vlogColored(char *fmt, char *ansiCol, va_list args)
{
	if(!getLogFlag(LOGFlagEnabled)) return;

	va_list argsCpy; va_copy(argsCpy, args);
	
	printf("%s", ansiCol);
	vlogFmt(fmt, argsCpy);
	printf("%s\n", ANSI_COLOR_RESET);
	
	va_end(argsCpy);
}


void logToFile(char* fmt, ...)
{
	va_list args; va_start(args, fmt);
	vlogToFile(fmt, args);
	va_end(args);
}

void logFmt(char* fmt, ...)
{
	va_list args; va_start(args, fmt);
	vlogFmt(fmt, args);
	va_end(args);
}

void logColored(char* fmt, char* ansiCol, ...)
{
	va_list args; va_start(args, ansiCol);
	vlogColored(fmt, ansiCol, args);
	va_end(args);
}


// -- -- -- -- -- -- -- -- Log Printing -- -- -- -- -- -- -- -- //

void logLocation(char* file, int line)
{
	if(!getLogFlag(LOGFlagLocation)) return;

	printf("File '%s' at Line %d: ", file, line);
	if(getLogFlag(LOGFlagFile))
			logToFile("File '%s' at Line %d: ", file, line);
}

#define TIME_LOG_STR "[%d-%02d-%02d, %02d:%02d:%02d] "

void logTime()
{
	time_t timeRaw;
	struct tm* timeInfo;

	time(&timeRaw);
	timeInfo = localtime(&timeRaw);
	
	if(getLogFlag(LOGFlagEnabled))
		logFmt(
				TIME_LOG_STR,
				timeInfo->tm_year + 1900,
				timeInfo->tm_mon + 1,
				timeInfo->tm_mday,
				timeInfo->tm_hour + 1,
				timeInfo->tm_min,
				timeInfo->tm_sec
		);
}

void logTimeFileOnly()
{
	time_t timeRaw;
	struct tm* timeInfo;

	time(&timeRaw);
	timeInfo = localtime(&timeRaw);
	
	if(getLogFlag(LOGFlagFile))
		logToFile(
				TIME_LOG_STR,
				timeInfo->tm_year + 1900,
				timeInfo->tm_mon + 1,
				timeInfo->tm_mday,
				timeInfo->tm_hour + 1,
				timeInfo->tm_min,
				timeInfo->tm_sec
		);
}

void logMsg(char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	
	if(getLogLevel() >= LOGLevelAll)
	{
		if(getLogFlag(LOGFlagTime)) logTimeFileOnly();
		vlogColored(fmt, ANSI_COLOR_RESET, args);
		if(getLogFlag(LOGFlagFile)) logToFile("\n");
	}

	va_end(args);
}

void logErr(char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	
	if(getLogLevel() >= LOGLevelMin)
	{
		if(getLogFlag(LOGFlagTime)) logTimeFileOnly();
		vlogColored(fmt, ANSI_COLOR_RED, args);
		if(getLogFlag(LOGFlagFile)) logToFile("\n");
	}

	va_end(args);
}

void logWarn(char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	
	if(getLogLevel() >= LOGLevelMed)
	{
		if(getLogFlag(LOGFlagTime)) logTimeFileOnly();
		vlogColored(fmt, ANSI_COLOR_YELLOW, args);
		if(getLogFlag(LOGFlagFile)) logToFile("\n");
	}

	va_end(args);
}

void logHint(char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	
	if(getLogLevel() >= LOGLevelMost)
	{
		if(getLogFlag(LOGFlagTime)) logTimeFileOnly();
		vlogColored(fmt, ANSI_COLOR_CYAN, args);
		if(getLogFlag(LOGFlagFile)) logToFile("\n");
	}

	va_end(args);
}
