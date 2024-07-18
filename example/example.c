#include "../include/suclog.h"
#include <time.h>

int main(int argc, char* argv[])
{
	
	setLogFlags(LOGFlagEnabled |  LOGLevelAll);
	// Sets the flags for the Logger.
	
	time_t rawtime; time(&rawtime);
	struct tm* timeinfo; timeinfo = localtime(&rawtime);

	openLogFile("./example.log", 0b1);
	logToFile("\n\n New Log Session %s\n", asctime(timeinfo)); //Placeholder until a suclog function for time is created.

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
