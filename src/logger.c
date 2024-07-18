#include "../include/logger.h"
#include <stdarg.h>
#include <stdio.h>

FILE* logFilePtr;
char logFlags = (char)(LOGLevelAll | LOGFlagEnabled | LOGFlagFile);


char getLogLevel()
{
	return LOGLevel & logFlags;
}

char logFlagEnabled(char feature)
{
	if(!(LOGFlagEnabled & logFlags)) return (char)0b0;

	return logFlags & feature;
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
	fprintf(logFilePtr, "\n");
	if(ferror(logFilePtr))
		printf("%sError encountered during file writing.%s\n", ANSI_COLOR_RED, ANSI_COLOR_RESET);
}

void logToFile(char* fmt, ...)
{
	va_list args; va_start(args, fmt);
	vlogToFile(fmt, args);
	va_end(args);
}

void vlogColored(char *fmt, char *ansiCol, va_list args)
{
	if(!logFlagEnabled(LOGFlagEnabled)) return;


	printf("%s", ansiCol);

	va_list args_cpy; va_copy(args_cpy, args);

	vprintf(fmt, args_cpy);
	va_end(args_cpy);

	printf("%s\n", ANSI_COLOR_RESET);
	
	if(logFlagEnabled(LOGFlagFile))
	{
		va_copy(args_cpy, args);
		vlogToFile(fmt, args_cpy);
		va_end(args_cpy);
	}
}

// -- -- -- -- -- -- -- -- Log Printing -- -- -- -- -- -- -- -- //

void logLocation(char* file, int line)
{
	if(!logFlagEnabled(LOGFlagLocation)) return;

	printf("File '%s' at Line %d: ", file, line);
	if(logFlagEnabled(LOGFlagFile))
			logToFile("File '%s' at Line %d: ", file, line);
}

void logMsg(char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	
	if(getLogLevel() >= LOGLevelAll)
		vlogColored(fmt, ANSI_COLOR_RESET, args);

	va_end(args);
}

void logErr(char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	
	if(getLogLevel() >= LOGLevelMin)
		vlogColored(fmt, ANSI_COLOR_RED, args);

	va_end(args);
}

void logWarn(char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	
	if(getLogLevel() >= LOGLevelMed)
		vlogColored(fmt, ANSI_COLOR_YELLOW, args);

	va_end(args);
}

void logHint(char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	
	if(getLogLevel() >= LOGLevelMost)
		vlogColored(fmt, ANSI_COLOR_CYAN, args);

	va_end(args);
}
