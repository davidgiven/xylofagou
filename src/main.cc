#include "globals.h"
#include <fnmatch.h>
#include <boost/algorithm/string.hpp>
#include "response.h"

sqlite3* db;
std::unique_ptr<cgicc::Cgicc> cgi;

static int help_cmd(const char**);

static const std::map<std::string, std::function<int(const char**)>>
    cliCommands = {
        {"lsactors", lsactors_cmd},
        {"addactor", addactor_cmd},
        {"delactor", delactor_cmd},
        {"help",     help_cmd    },
        {"initdb",   initdb_cmd  },
        {"setactor", setactor_cmd},
        {"setprop",  setprop_cmd },
        {"lsprops",  lsprops_cmd },
};

static const std::map<std::string, std::function<void(Response&)>> cgiCommands =
    {
        {"actor", actor_cgi},
};

int help_cmd(const char**)
{
    std::cout << "Commands:\n";
    for (auto& i : cliCommands)
        std::cout << format("  %s\n") % i.first;

    return 1;
}

static int do_command(const char** argv)
{
    if (!argv[1])
        error(
            "syntax: xylofagou <command> [<parameters>...] (try 'help' if "
            "stuck)");

    auto i = cliCommands.find(argv[1]);
    if (i == cliCommands.end())
        error(format("unrecognised command '%s' (try 'help')") % argv[1]);

    return i->second(argv + 2);
}

static int do_cgi()
{
    try
    {
        cgi = std::make_unique<cgicc::Cgicc>();

        /* This isn't returned by cgicc! */
        Response res;
        if (boost::starts_with(
                getenvs("REQUEST_URI"), "/.well-known/webfinger"))
            webfinger_cgi(res);
        else
        {
            auto cmd = (*cgi)("cmd");

            auto i = cgiCommands.find(cmd);
            if (i == cgiCommands.end())
                throw std::invalid_argument("Bad command");

            i->second(res);
        }

        std::cout << res;
        return 0;
    }
    catch (std::exception& e)
    {
        std::cout << '\n' << e.what() << '\n';
        return 1;
    }
}

int main(int argc, const char* argv[])
{
    std::string dbpath = getenvs("HOME") + "/xylofagou.db";
    if (sqlite3_open(dbpath.c_str(), &db) != SQLITE_OK)
        error("could not open database file");

    execSql(R"%(
		PRAGMA synchronous = OFF;
		PRAGMA encoding = "UTF-8";
		PRAGMA foreign_keys = ON;
		PRAGMA temp_store = MEMORY;
	)%");

    int r = 0;
    if (getenv("GATEWAY_INTERFACE"))
        r = do_cgi();
    else
        r = do_command(argv);

    sqlite3_close(db);
    return r;
}
