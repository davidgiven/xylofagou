#include "globals.h"

int initdb_cmd(const char** argv)
{
    execSql(R"%(
		BEGIN;

		CREATE TABLE IF NOT EXISTS properties
		(
			key TEXT NOT NULL PRIMARY KEY,
			value TEXT
		);

		CREATE TABLE IF NOT EXISTS actors
		(
			email TEXT NOT NULL PRIMARY KEY,
			name TEXT,
			homepage TEXT
		);

		COMMIT;
	)%");

    return 0;
}
