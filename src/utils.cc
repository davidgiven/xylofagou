#include "globals.h"

void error(const std::string s)
{
    std::cerr << "Error: " << s << '\n';
    exit(1);
}

void error(boost::basic_format<char>& fmt)
{
    error(str(fmt));
}

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
        error(str(format("database error: %s") % errmsg));
}
