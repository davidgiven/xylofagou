#include "globals.h"

std::string getenvs(std::string key)
{
	const char* p = getenv(key.c_str());
	return p ? p : "";
}

