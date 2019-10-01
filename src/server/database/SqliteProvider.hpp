#ifndef BABEL_SQLITEPROVIDER_HPP
#define BABEL_SQLITEPROVIDER_HPP

#include <string>
#include <sqlite3.h>
#include <functional>
#include "IDataBaseProvider.hpp"
#include "RequestBuilder.hpp"


class SqliteProvider : IDataBaseProvider {
    public:
        bool openDataBase(const std::string &name) override;
        bool closeDataBase() override;
        bool executeRequest(const Request& request);

        ~SqliteProvider() {
           closeDataBase();
        }
    private:
        sqlite3 *db = nullptr;
};

#endif //BABEL_SQLITEPROVIDER_HPP
