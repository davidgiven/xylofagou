#include "globals.h"

std::string getenvs(std::string key)
{
	const char* p = getenv(key.c_str());
	return p ? p : "";
}

void execSql(std::string sql)
{
	char* errmsg;
	int i = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errmsg);
	if (i != SQLITE_OK)
		error("database error: {}", errmsg);
}

