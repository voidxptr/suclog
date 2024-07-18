#include "../include/logger.h"
#include <stdarg.h>
#include <stdio.h>

FILE* logFilePtr;
char logFlags = (char)(LOGLevelAll | LOGFlagEnabled | LOGFlagFile);


void setLogFlags(char flags)
{
	logFlags = flags;
}

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


void vlogColored(char *fmt, char *ansiCol, va_list args)
{
	if(!(logFlags & LOGFlagEnabled)) return;


	printf("%s", ansiCol);

	va_list args_cpy; va_copy(args_cpy, args);

	vprintf(fmt, args_cpy);
	va_end(args_cpy);
	if(logFilePtr && (logFlags & LOGFlagFile))
	{
		vfprintf(logFilePtr, fmt, args);
		fprintf(logFilePtr, "\n");
		if(ferror(logFilePtr))
			printf("%sError encountered during file writing.%s\n", ANSI_COLOR_RED, ANSI_COLOR_RESET);
	}

	printf("%s\n", ANSI_COLOR_RESET);
}

void logLocation(char* file, int line)
{
	if(!(logFlags & (LOGFlagLocation | LOGFlagEnabled))) return;


	printf("File '%s' at Line %d: ", file, line);
	if(logFilePtr && (logFlags & LOGFlagFile))
	{
		fprintf(logFilePtr, "File '%s' at Line %d: ", file, line);
		if(ferror(logFilePtr))
			printf("%sError encountered during file writing.%s\n", ANSI_COLOR_RED, ANSI_COLOR_RESET);
	}
}

void logMsg(char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	
	if((logFlags & LOGLevel) >= LOGLevelAll)
		vlogColored(fmt, ANSI_COLOR_RESET, args);

	va_end(args);
}

void logErr(char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	
	if((logFlags & LOGLevel) >= LOGLevelMin)
		vlogColored(fmt, ANSI_COLOR_RED, args);

	va_end(args);
}

void logWarn(char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	
	if((logFlags & LOGLevel) >= LOGLevelMed)
		vlogColored(fmt, ANSI_COLOR_YELLOW, args);

	va_end(args);
}

void logHint(char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	
	if((logFlags & LOGLevel) >= LOGLevelMost)
		vlogColored(fmt, ANSI_COLOR_CYAN, args);

	va_end(args);
}
