#ifndef BABEL_DATABASESERVICE_HPP
#define BABEL_DATABASESERVICE_HPP

#define DATABASE_DEFAULT_NAME "database.db"

#include "database/IDataBaseProvider.hpp"
#include "database/RequestBuilder.hpp"

template <class T >
class DataBaseService : public IService {
    static_assert(std::is_base_of<IDataBaseProvider, T>::value, "T must inherit from IDataBaseProvider");
    public:
        explicit DataBaseService() : _dataBase() {};
        bool openDataBase(const std::string &name = DATABASE_DEFAULT_NAME) { return _dataBase.openDataBase(name); }
        bool closeDataBase() { return _dataBase.closeDataBase(); }
        bool executeRequest(const Request &request) {return _dataBase.executeRequest(request);}
    private:
        T _dataBase;
};

#endif //BABEL_DATABASESERVICE_HPP