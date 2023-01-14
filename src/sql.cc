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

    for (int i = 0; i < sqlite3_column_count(_statement); i++)
    {
        auto name = sqlite3_column_name(_statement, i);
        _columns[name] = i;
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
        error(format("invalid SQL parameter '%s'") % param);

    sqlite3_bind_text(
        _statement, i->second, value.c_str(), value.size(), SQLITE_TRANSIENT);
    return *this;
}

void Cursor::run()
{
    int i = step();
    if (i != SQLITE_DONE)
        error(format("SQL statement terminated with {}") % i);
}

int Cursor::step()
{
    _reset = false;
    return sqlite3_step(_statement);
}

bool Cursor::has(std::string column)
{
    return sqlite3_column_type(_statement, getColumn(column)) != SQLITE_NULL;
}

std::string Cursor::get(std::string column)
{
    auto ptr = (char*)sqlite3_column_text(_statement, getColumn(column));
    if (!ptr)
        return "";
    return ptr;
}

int Cursor::getColumn(std::string column)
{
    auto i = _columns.find(column);
    if (i == _columns.end())
        error(format("invalid SQL column '%s'") % column);

    return i->second;
}
