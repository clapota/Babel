#include <iostream>
#include <sqlite_orm/sqlite_orm.h>
#include "SqliteProvider.hpp"

bool SqliteProvider::openDataBase(const std::string &name)
{
    db = new Storage(initStorage(name));
    return true;
}

bool SqliteProvider::closeDataBase()
{
    return true;
}

bool SqliteProvider::createUser(const std::string &username,
    const std::string &password
)
{
    User user{-1, username, password};
    try {
        db->insert(user);
        return true;
    } catch (...) {
        return false;
    }
}

bool SqliteProvider::createRelation(int a, int b)
{
    Friendship friendship{a, b};
    try {

        db->insert(friendship);
        return true;
    } catch (...) {
        return false;
    }
}

bool SqliteProvider::createRelation(const std::string &username1,
    const std::string &username2
)
{
    User user1 = getUserByName(username1);
    User user2 = getUserByName(username2);

    Friendship friendship{user1.id, user2.id};
    try {
        db->insert(friendship);
        return true;
    } catch (...) {
        return false;
    }
}

User SqliteProvider::getUserById(int id)
{
    try {
        auto user = db->get<User>(id);
        return user;
    } catch (std::system_error e) {
        std::cerr << e.what() << std::endl;
        return User{-1, "", ""};
    } catch (...) {
        std::cerr << "unknown error" << std::endl;
        return User{-1, "", ""};
    }
}

User SqliteProvider::getUserByName(const std::string &username)
{
    try {
        auto user = db->get_all<User>(sqlite_orm::where(sqlite_orm::like(&User::username, username.c_str())));
        if (user.empty())
            return User{-1, "", ""};
        return user[0];
    } catch (std::system_error e) {
        std::cerr << e.what() << std::endl;
        return User{-1, "", ""};
    } catch (...) {
        std::cerr << "unknown error" << std::endl;
        return User{-1, "", ""};
    }
}

std::vector<User> SqliteProvider::getAll()
{
    auto users = db->get_all<User>();
    return users;
}

std::vector<User> SqliteProvider::getFriendsOf(int id)
{
    User user = this->getUserById(id);

    return getFriendsOf(user.username);
}

std::vector<User> SqliteProvider::getFriendsOf(const std::string &username)
{
    User user = this->getUserByName(username);
    std::vector<User> friends;

    try {
        std::vector<Friendship> friendsRelation = db->get_all<Friendship>();

        for (auto &it: friendsRelation) {
            User relation;
            if (user.id == it.user1_id)
                relation = this->getUserById(it.user2_id);
            else if (user.id == it.user2_id)
                relation = this->getUserById(it.user1_id);
            friends.push_back(relation);
        }
        return friends;
    } catch (...) {
        return std::vector<User>();
    }
}

std::vector<PendingFriendRequest> SqliteProvider::getPendingFriendsRequestOf(
    int id
)
{
    try {
        std::vector<PendingFriendRequest> friendRequests = db->get_all<PendingFriendRequest>();
        std::vector<PendingFriendRequest> friendRequestOfId;

        for (auto &it: friendRequests) {
            if (it.receiver_id == id)
                friendRequestOfId.push_back(it);
        }
        return friendRequestOfId;
    } catch (...) {
        return std::vector<PendingFriendRequest>();
    }
}

std::vector<PendingFriendRequest> SqliteProvider::getPendingFriendsRequestOf(
    const std::string &username
)
{
    User user = this->getUserByName(username);
    return this->getPendingFriendsRequestOf(user.id);
}

bool SqliteProvider::addPendingFriendRequest(int sender, int receiver)
{
    PendingFriendRequest request{sender, receiver};

    try {
        db->insert(request);
        return true;
    } catch(...) {
        return false;
    }
}

bool SqliteProvider::addPendingFriendRequest(const std::string &sender,
    const std::string &receiver
)
{
    User user1 = this->getUserByName(sender);
    User user2 = this->getUserByName(receiver);
    return addPendingFriendRequest(user1.id, user2.id);
}
