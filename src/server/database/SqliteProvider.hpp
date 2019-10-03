#ifndef BABEL_SQLITEPROVIDER_HPP
#define BABEL_SQLITEPROVIDER_HPP

#include <string>
#include <sqlite3.h>
#include <functional>
#include <sqlite_orm/sqlite_orm.h>
#include "IDataBaseProvider.hpp"

struct User {
    int id;
    std::string username;
    std::string password;
};

struct Friendship {
    int user1_id;
    int user2_id;
};

struct PendingFriendRequest {
    int sender_id;
    int receiver_id;
};

inline auto initStorage(const std::string &name)
{
    auto storage = sqlite_orm::make_storage(name,
        sqlite_orm::make_table("users",
            sqlite_orm::make_column("id", &User::id, sqlite_orm::autoincrement(), sqlite_orm::primary_key()),
            sqlite_orm::make_column("username", &User::username, sqlite_orm::unique()),
            sqlite_orm::make_column("password", &User::password)),
        sqlite_orm::make_table("friendship",
            sqlite_orm::make_column("user1_id", &Friendship::user1_id),
            sqlite_orm::make_column("user2_id", &Friendship::user2_id)),
        sqlite_orm::make_table("pending_friend_request",
            sqlite_orm::make_column("sender_id", &PendingFriendRequest::sender_id),
            sqlite_orm::make_column("receiver_id", &PendingFriendRequest::receiver_id)));
    storage.sync_schema();
    return storage;
}

using Storage = decltype(initStorage(""));

class SqliteProvider : public IDataBaseProvider {
    public:
        bool openDataBase(const std::string &name) override;
        bool closeDataBase() override;

        bool createUser(const std::string &username, const std::string &password) override;
        bool createRelation(int a, int b) override;
        bool createRelation(const std::string &username1, const std::string &username2) override;
        User getUserById(int id) override;
        User getUserByName(const std::string &username) override;
        std::vector<User> getAll() override;
        std::vector<User> getFriendsOf(int id) override;
        std::vector<User> getFriendsOf(const std::string &username) override;
        std::vector<PendingFriendRequest> getPendingFriendsRequestOf(int id) override;
        std::vector<PendingFriendRequest> getPendingFriendsRequestOf(const std::string &username) override;
        bool addPendingFriendRequest(int sender, int receiver) override;
        bool addPendingFriendRequest(const std::string &sender, const std::string &receiver) override;

        ~SqliteProvider() {
           closeDataBase();
        }
    private:
        Storage *db = nullptr;
};

#endif //BABEL_SQLITEPROVIDER_HPP
