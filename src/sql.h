#pragma once

class Cursor
{
public:
    Cursor(const std::string sql);
    ~Cursor();

    Cursor& bind(const std::string param, const std::string value);

    void run();
    int step();

private:
    sqlite3_stmt* _statement;
    std::map<std::string, int> _parameters;
    bool _reset;
};
