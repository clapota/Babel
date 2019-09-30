//
// Created by abel on 30/09/2019.
//

#ifndef BABEL_REQUESTBUILDER_HPP
#define BABEL_REQUESTBUILDER_HPP

#include <string>

struct Request {
    std::string request;
    int (*callback)(void *, int, char **, char **);
    void *data;
};

class RequestBuilder {
public:
    static Request createUserTable();
    static Request addUser(std::string username, std::string password);
    static Request createRelationTable();
    static Request addRelation(int id1, int id2, void *data);
    static Request getUsers(void *data, int(*callback)(void *, int, char **, char **));
    static Request getUserByName(std::string username, void *data, int(*callback)(void *, int, char **, char **));
    static Request getAllRelation(void *data, int (*callback)(void *, int, char **, char **));
    static Request getFriendOfUser(int userId, void *data, int(*callback)(void *, int , char **, char**));
};


#endif //BABEL_REQUESTBUILDER_HPP
