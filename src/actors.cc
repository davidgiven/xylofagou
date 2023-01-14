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
