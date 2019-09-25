#include "SqliteProvider.hpp"

bool SqliteProvider::openDataBase(const std::string &name)
{
    return (bool)(!sqlite3_open(name.c_str(), &db));
}

bool SqliteProvider::closeDataBase()
{
    return (bool)(!sqlite3_close(db));
}
