#include "globals.h"
#include "sql.h"

std::string getProp(std::string key)
{
    Cursor c("SELECT value FROM properties WHERE key = :key");
    c.bind(":key", key);

    int i = c.step();
    if (i == SQLITE_ROW)
        return c.get("value");
    return "";
}

int setprop_cmd(const char** argv)
{
    if (!argv[0] || !argv[1] || argv[2])
        error("syntax: setprop <key> <value>");

    std::string key = argv[0];
    std::string value = argv[1];
    Cursor(
        "INSERT OR REPLACE INTO properties (key, value) VALUES (:key, :value)")
        .bind(":key", key)
        .bind(":value", value)
        .run();

    return 0;
}

int lsprops_cmd(const char** argv)
{
    if (argv[0])
        error("syntax: lsprops");

    Cursor c("SELECT * FROM properties");

    while (c.step() == SQLITE_ROW)
    {
        std::cout << format("%s = %s\n") % c.get("key") % c.get("value");
    }

    return 0;
}
