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
    return false;
}

bool SqliteProvider::createRelation(int a, int b)
{
    return false;
}

bool SqliteProvider::createRelation(const std::string &username1,
    const std::string &username2
)
{
    return false;
}

User SqliteProvider::getUserById(int id)
{
    return User();
}

User SqliteProvider::getUserByName(const std::string &username)
{
    return User();
}

std::vector<User> SqliteProvider::getAll()
{
    return std::vector<User>();
}

std::vector<User> SqliteProvider::getFriendsOf(int id)
{
    return std::vector<User>();
}

std::vector<User> SqliteProvider::getFriendsOf(const std::string &username)
{
    return std::vector<User>();
}

std::vector<PendingFriendRequest> SqliteProvider::getPendingFriendsRequestOf(
    int id
)
{
    return std::vector<PendingFriendRequest>();
}

std::vector<PendingFriendRequest> SqliteProvider::getPendingFriendsRequestOf(
    const std::string &username
)
{
    return std::vector<PendingFriendRequest>();
}

bool SqliteProvider::addPendingFriendRequest(int sender, int receiver)
{
    return false;
}

bool SqliteProvider::addPendingFriendRequest(const std::string &sender,
    const std::string &receiver
)
{
    return false;
}
