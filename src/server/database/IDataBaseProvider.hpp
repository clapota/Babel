#ifndef BABEL_IDATABASEPROVIDER_HPP
#define BABEL_IDATABASEPROVIDER_HPP

#include <string>

struct User;
struct Friendship;
struct PendingFriendRequest;

class IDataBaseProvider {
    public:
        virtual bool openDataBase(const std::string &name) = 0;
        virtual bool closeDataBase() = 0;

        virtual bool createUser(const std::string &username, const std::string &password) = 0;
        virtual bool createRelation(int a, int b) = 0;
        virtual bool createRelation(const std::string &username1, const std::string &username2) = 0;
        virtual User getUserById(int id) = 0;
        virtual User getUserByName(const std::string &username) = 0;
        virtual std::vector<User> getAll() = 0;
        virtual std::vector<User> getFriendsOf(int id) = 0;
        virtual std::vector<User> getFriendsOf(const std::string &username) = 0;
        virtual std::vector<PendingFriendRequest> getPendingFriendsRequestOf(int id) = 0;
        virtual std::vector<PendingFriendRequest> getPendingFriendsRequestOf(const std::string &username) = 0;
        virtual bool addPendingFriendRequest(int sender, int receiver) = 0;
        virtual bool addPendingFriendRequest(const std::string &sender, const std::string &receiver) = 0;
};

#endif //BABEL_IDATABASEPROVIDER_HPP
