#include "../include/logger.h"
#include <stdarg.h>
#include <stdio.h>

FILE* _logFilePtr;
char logFlags = (char)(LOGLevelAll | LOGFlagEnabled | LOGFlagFile);


void _setupLogFile(char flags)
{
	logFlags = flags;
	if(logFlags & LOGFlagFile)
	{
		_logFilePtr = fopen("./log.txt", "a");

		if(ferror(_logFilePtr))
			printf("%sError encountered during file opening.%s\n", ANSI_COLOR_RED, ANSI_COLOR_RESET);
	}
}

void _closeLogFile()
{
	if(_logFilePtr) fclose(_logFilePtr);
}


void vlogColored(char *fmt, char *ansiCol, va_list args)
{
	if(!(logFlags & LOGFlagEnabled)) return;


	printf("%s", ansiCol);

	va_list args_cpy; va_copy(args_cpy, args);

	vprintf(fmt, args_cpy);
	va_end(args_cpy);
	if(_logFilePtr && (logFlags & LOGFlagFile))
	{
		vfprintf(_logFilePtr, fmt, args);
		fprintf(_logFilePtr, "\n");
		if(ferror(_logFilePtr))
			printf("%sError encountered during file writing.%s\n", ANSI_COLOR_RED, ANSI_COLOR_RESET);
	}

	printf("%s\n", ANSI_COLOR_RESET);
}

void logLocation(char* file, int line)
{
	if(!(logFlags & (LOGFlagLocation | LOGFlagEnabled))) return;


	printf("File '%s' at Line %d: ", file, line);
	if(_logFilePtr && (logFlags & LOGFlagFile))
	{
		fprintf(_logFilePtr, "File '%s' at Line %d: ", file, line);
		if(ferror(_logFilePtr))
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
