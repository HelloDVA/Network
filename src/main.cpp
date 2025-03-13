#include"Log.h"

int main()
{
	Log *log = Log::getlog();
	log -> WriteLog(LOG_LEVEL_INFO, "main.cpp", "main", 6, "This is an info message.");

	return 0;
	
}
