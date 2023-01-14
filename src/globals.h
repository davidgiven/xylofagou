#pragma once

#include <stdlib.h>
#include <fmt/format.h>
#include <sstream>
#include <map>
#include <functional>
#include <sqlite3.h>

template<class... Args>
void error(const std::string& fmt, Args&&... args)
{
	fmt::print(stderr, "Error: ");
	fmt::print(stderr, fmt, args...);
	fmt::print(stderr, "\n");
	exit(1);
}

extern int wellknown_cgi();

extern int initdb_cmd(const char** argv);

extern std::string getenvs(std::string key);
extern void execSql(std::string sql);

extern sqlite3* db;

