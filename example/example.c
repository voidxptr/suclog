#include "../include/logger.h"

int main(int argc, char* argv[])
{
	
	setLogFlags(LOGFlagEnabled |  LOGLevelAll);
	// Sets the flags for the Logger.
	
	openLogFile("./example.log", 0b1); // Uncomment for Log-File (Remember to uncomment closing before returns).
	if(argc != 5)
	{
		LogERR("%1$s expects 3 arguments. Example: '%1$s \"Msg\" \"Hint\" \"Warn\" \"Err\"'", argv[0]);
		// The LogTYPE macros are usefull for printing messages with extra information about there origin.
		closeLogFile();
		return 0;
	}

	logMsg("Msg: %s",	argv[1]);
	logHint("Hint: %s",	argv[2]);
	logWarn("Warn: %s",	argv[3]);
	logErr("Err: %s",	argv[4]);
	closeLogFile();
	return 0;
}
