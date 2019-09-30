#include <iostream>
#include "SqliteProvider.hpp"

bool SqliteProvider::openDataBase(const std::string &name)
{
    return (bool)(!sqlite3_open(name.c_str(), &db));
}

bool SqliteProvider::closeDataBase()
{
    return (bool)(!sqlite3_close(db));
}

bool SqliteProvider::executeRequest(const Request& request) {
    char *errMessage;
    int rc;

    rc = sqlite3_exec(db, request.request.c_str(), request.callback, request.data, &errMessage);

    if (rc != SQLITE_OK) {
        std::cerr << errMessage << std::endl;
        sqlite3_free(errMessage);
    }
}