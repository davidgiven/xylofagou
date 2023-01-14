#include "globals.h"
#include <fnmatch.h>

sqlite3* db;

static int help_cmd(const char**);

static const std::map<std::string, std::function<int(const char**)>>
    cliCommands = {
        {"help", help_cmd},
		{"initdb", initdb_cmd},
};

static const std::map<std::string, std::function<int()>> cgiCommands = {
    {"/.well-known/something", wellknown_cgi}
};

int help_cmd(const char**)
{
    fmt::print("Commands:\n");
    for (auto& i : cliCommands)
        fmt::print("  {}\n", i.first);

    return 1;
}

static int command(const char** argv)
{
    if (!argv[1])
        error(
            "syntax: xylofagou <command> [<parameters>...] (try 'help' if "
            "stuck)");

    auto i = cliCommands.find(argv[1]);
    if (i == cliCommands.end())
        error("unrecognised command '{}' (try 'help')", argv[1]);

    return i->second(argv + 2);
}

static int cgi()
{
    std::string path = getenvs("PATH_INFO");

    for (auto& i : cgiCommands)
    {
        int r = fnmatch(i.first.c_str(), path.c_str(), FNM_PATHNAME);
        if (r == 0)
            return i.second();
    }

    fmt::print(stderr, "Bad path");
    return 1;
}

int main(int argc, const char* argv[])
{
    if (sqlite3_open("xylofagou.db", &db) != SQLITE_OK)
        error("could not open database file");

	execSql("PRAGMA synchronous=off");

    int r = 0;
    if (getenv("GATEWAY_INTERFACE"))
        r = cgi();
    else
        r = command(argv);

    sqlite3_close(db);
    return r;
}
