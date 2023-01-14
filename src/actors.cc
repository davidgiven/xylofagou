#include "globals.h"
#include "sql.h"

int addactor_cmd(const char** argv)
{
    if (!argv[0] || argv[1])
        error("syntax: addactor <email>");

    std::string email = argv[0];
    Cursor("INSERT INTO actors (email) VALUES (:email)")
        .bind(":email", email)
        .run();

    return 0;
}

int delactor_cmd(const char** argv)
{
    if (!argv[0] || argv[1])
        error("syntax: delactor <email>");

    std::string email = argv[0];
    Cursor("DELETE FROM actors WHERE email = :email")
        .bind(":email", email)
        .run();

    return 0;
}

int setactor_cmd(const char** argv)
{
    if (!argv[0] || !argv[1] || !argv[2] || argv[3])
        error("syntax: setactor <email> <property> <value>");

    std::string email = argv[0];
    std::string property = argv[1];
    std::string value = argv[2];

    Cursor("UPDATE actors SET " + property + " = :value WHERE email = :email")
        .bind(":email", email)
        .bind(":value", value)
        .run();

    return 0;
}

int lsactors_cmd(const char** argv)
{
    if (argv[0])
        error("syntax: lsactors");

    Cursor c("SELECT * FROM actors");
    while (c.step() == SQLITE_ROW)
    {
        std::cout << format("%s %s %s\n") % c.get("email") % c.get("name") %
                         c.get("homepage");
    }

    return 0;
}
