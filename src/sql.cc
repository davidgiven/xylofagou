#include "globals.h"
#include "sql.h"

Cursor::Cursor(const std::string sql)
{
    int i = sqlite3_prepare_v2(
        db, sql.c_str(), sql.size() + 1, &_statement, nullptr);
    if (i != SQLITE_OK)
        throw std::invalid_argument("invalid SQL");

    for (int i = 1; i <= sqlite3_bind_parameter_count(_statement); i++)
    {
        auto name = sqlite3_bind_parameter_name(_statement, i);
        _parameters[name] = i;
    }

    _reset = true;
}

Cursor::~Cursor()
{
    sqlite3_finalize(_statement);
}

Cursor& Cursor::bind(const std::string param, const std::string value)
{
    if (!_reset)
        sqlite3_reset(_statement);

    auto i = _parameters.find(param);
    if (i == _parameters.end())
        error("invalid SQL parameter '{}'", param);

    sqlite3_bind_text(
        _statement, i->second, value.c_str(), value.size(), SQLITE_TRANSIENT);
    return *this;
}

void Cursor::run()
{
    int i = step();
    if (i != SQLITE_DONE)
        error("SQL statement terminated with {}", i);
}

int Cursor::step()
{
    _reset = false;
    return sqlite3_step(_statement);
}
