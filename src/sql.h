#pragma once

class Cursor
{
public:
    Cursor(const std::string sql);
    ~Cursor();

    Cursor& bind(const std::string param, const std::string value);

    void run();
    int step();

    bool has(const std::string column);
    std::string get(const std::string column);

private:
    int getColumn(const std::string column);

private:
    sqlite3_stmt* _statement;
    std::map<std::string, int> _parameters;
    std::map<std::string, int> _columns;
    bool _reset;
};
