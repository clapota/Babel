#ifndef BABEL_IDATABASEPROVIDER_HPP
#define BABEL_IDATABASEPROVIDER_HPP

#include <string>
#include "database/RequestBuilder.hpp"

class IDataBaseProvider {
    public:
        virtual bool openDataBase(const std::string &name) = 0;
        virtual bool closeDataBase() = 0;
        virtual bool executeRequest(const Request &request) = 0;
};

#endif //BABEL_IDATABASEPROVIDER_HPP
