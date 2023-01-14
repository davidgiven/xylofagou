#include "globals.h"

int initdb_cmd(const char** argv)
{
    execSql(R"%(
		BEGIN;

		CREATE TABLE IF NOT EXISTS variables
		(
			key TEXT NOT NULL PRIMARY KEY,
			value TEXT
		);

		CREATE TABLE IF NOT EXISTS actors
		(
			email TEXT NOT NULL PRIMARY KEY
		);

		COMMIT;
	)%");

    return 0;
}
