#ifndef BABEL_DATABASESERVICE_HPP
#define BABEL_DATABASESERVICE_HPP

#define DATABASE_DEFAULT_NAME "database.db"

#include "IService.hpp"
#include "database/IDataBaseProvider.hpp"

template <class T >
class DataBaseService : public IService {
    static_assert(std::is_base_of<IDataBaseProvider, T>::value, "T must inherit from IDataBaseProvider");
    public:
        explicit DataBaseService() : _dataBase() {};
        bool openDataBase(const std::string &name = DATABASE_DEFAULT_NAME) { return _dataBase.openDataBase(name); }
        bool closeDataBase() { return _dataBase.closeDataBase(); }

     bool createUser(const std::string &username, const std::string &password) {return _dataBase.createUser(username, password);};
     bool createRelation(int a, int b) {return _dataBase.createRelation(a, b);};
     bool createRelation(const std::string &username1, const std::string &username2) { return _dataBase.createRelation(username1, username2); }
     User getUserById(int id) { return _dataBase.getUserById(id); }
     User getUserByName(const std::string &username) { return _dataBase.getUserByName(username); }
     std::vector<User> getAll() { return _dataBase.getAll(); }
     std::vector<User> getFriendsOf(int id) { return _dataBase.getFriendsOf(id); }
     std::vector<User> getFriendsOf(const std::string &username) { return _dataBase.getFriendsOf(username); }
     std::vector<PendingFriendRequest> getPendingFriendsRequestOf(int id) { return _dataBase.getPendingFriendsRequestOf(id); }
     std::vector<PendingFriendRequest> getPendingFriendsRequestOf(const std::string &username) { return _dataBase.getPendingFriendRequestOf(username); }
     bool addPendingFriendRequest(int sender, int receiver) { return _dataBase.addPendingFriendRequest(sender, receiver); }
     bool addPendingFriendRequest(const std::string &sender, const std::string &receiver) { return _dataBase.addPendingFriendRequest(sender, receiver); }

    private:
        T _dataBase;
};

#endif //BABEL_DATABASESERVICE_HPP