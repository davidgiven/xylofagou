#pragma once

#include <stdlib.h>
#include <sstream>
#include <map>
#include <functional>
#include <sqlite3.h>
#include <cgicc/Cgicc.h>
#include <boost/format.hpp>

using boost::format;
using boost::str;

extern void error(const std::string msg);
extern void error(boost::basic_format<char>& fmt);

extern int webfinger_cgi();

extern int addactor_cmd(const char** argv);
extern int delactor_cmd(const char** argv);
extern int setactor_cmd(const char** argv);
extern int lsactors_cmd(const char** argv);
extern int initdb_cmd(const char** argv);
extern int setprop_cmd(const char** argv);
extern int lsprops_cmd(const char** argv);

extern std::string getProp(std::string key);
extern void setProp(std::string key);

extern std::string getenvs(std::string key);
extern void execSql(std::string sql);

extern sqlite3* db;
extern std::unique_ptr<cgicc::Cgicc> cgi;
