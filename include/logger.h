#ifndef BREAK_LOGGER_H

#define BREAK_LOGGER_H

#include <stdarg.h>
#include <stdio.h>
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

extern char logFlags;
// L == Level; E = Enabled; F = File; P = LocationLogging
// E|F| | | |P|L|L|
#define LOGFlagEnabled	(char)(0b1 << 7)
#define LOGFlagFile		(char)(0b1 << 6)
//#define LOGFlagUnused	(char)(0b1 << 5)
//#define LOGFlagUnused	(char)(0b1 << 4)
//#define LOGFlagUnused	(char)(0b1 << 3)
#define LOGFlagLocation	(char)(0b1 << 2)

#define LOGLevel		(char)(0b11)
#define LOGLevelAll		(char)(0b11)
#define LOGLevelMost	(char)(0b10)
#define LOGLevelMed		(char)(0b01)
#define LOGLevelMin		(char)(0b00)


char getLogLevel();
char logFlagEnabled(char feature);
void setLogFlags(char flags);

void setLogFlags(char flags);
void openLogFile(char* filename, char forceEnableLogFile);
void closeLogFile();
void logToFile(char* fmt, ...);
void vlogToFile(char *fmt, va_list args);


void vlogColored(char* fmt, char* ansiCol, va_list args);

void logLocation(char* file, int line);
void logMsg(char *fmt, ...);
void logErr(char *fmt, ...);
void logWarn(char *fmt, ...);
void logHint(char *fmt, ...);

#define LogMSG(fmt, ...) logLocation(__FILE__, __LINE__); logMsg(fmt, __VA_ARGS__)
#define LogERR(fmt, ...) logLocation(__FILE__, __LINE__); logErr(fmt, __VA_ARGS__)
#define LogWARN(fmt, ...) logLocation(__FILE__, __LINE__); logWarn(fmt, __VA_ARGS__)
#define LogHINT(fmt, ...) logLocation(__FILE__, __LINE__); logHint(fmt, __VA_ARGS__)

#endif
