#include "../include/logger.h"

int main(int argc, char* argv[])
{
	_setupLogFile(LOGFlagEnabled |  LOGLevelAll);
	if(argc != 5)
	{
		LogERR("%1$s expects 3 arguments. Example: '%1$s \"Msg\" \"Hint\" \"Warn\" \"Err\"'", argv[0]);
		// The LogTYPE macros are usefull for printing messages with extra information about there origin.
		return 0;
	}

	logMsg("Msg: %s",	argv[1]);
	logHint("Hint: %s",	argv[2]);
	logWarn("Warn: %s",	argv[3]);
	logErr("Err: %s",	argv[4]);
	return 0;
}
