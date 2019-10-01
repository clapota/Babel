//
// Created by abel on 30/09/2019.
//

#include <iostream>
#include "RequestBuilder.hpp"

/***
 *
 * @return request to create the user table
 */
Request RequestBuilder::createUserTable() {
    Request request;

    request.request = "CREATE TABLE USERS("
                      "ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
                      "USERNAME TEXT NOT NULL,"
                      "PASSWORD NOT NULL,"
                      "CONSTRAINT username_unique UNIQUE(USERNAME)"
                      ");";
    request.callback = nullptr;
    request.data = nullptr;
    return request;
}

/***
 * this method is called when a user has been added to database
 */
int addUserCallback(void *, int, char **, char **)
{
    std::cout << "User created successfully" << std::endl;
    return 0;
}

/***
 *
 * @param username
 * @param password
 * @return request to create new user
 */
Request RequestBuilder::addUser(std::string username, std::string password) {
    Request request;

    request.request = "INSERT INTO USERS(USERNAME, PASSWORD) VALUES('" + username + "', '" + password + "');";
    request.callback = addUserCallback;
    request.data = nullptr;
    return request;
}


/***
 *
 * @return request to create friendship relation table
 */
Request RequestBuilder::createRelationTable() {
    Request request;

    request.request = "CREATE TABLE FRIENDSHIP("
                      "user1_id INT NOT NULL,"
                      "user2_id INT NOT NULL);";
    request.callback = nullptr;
    request.data = nullptr;
    return request;
}

int addRelationCallback(void *data, int, char **, char **)
{
    std::cout << "Relation added" << std::endl;
    //TODO: FAIRE DES TRUCS
    return 0;
}

Request RequestBuilder::addRelation(int id1, int id2, void *data) {
    Request request;

    request.request = "INSERT INTO FRIENDSHIP(user1_id, user2_id) VALUES(" + std::to_string(id1) + ", " + std::to_string(id2) + ");";
    request.callback = addRelationCallback;
    request.data = data;
    return request;
}



Request RequestBuilder::getUsers(void *data, int (*callback)(void *, int, char **, char **)) {
    Request request;

    request.request = "SELECT * FROM TABLE USERS;";
    request.data = data;
    request.callback = callback;
    return request;
}

Request RequestBuilder::getUserByName(std::string username, void *data, int (*callback)(void *, int, char **, char **)) {
    Request request;

    request.request = "SELECT * FROM TABLE USERS WHERE USERNAME = '" + username + "';";
    request.data = data;
    request.callback = callback;
    return request;
}

Request RequestBuilder::getAllRelation(void *data, int (*callback)(void *, int, char **, char **)) {
    Request request;

    request.request = "SELECT * FROM TABLE FRIENDSHIP;";
    request.data = data;
    request.callback = callback;
    return request;
}

Request RequestBuilder::getFriendOfUser(int userId, void *data, int (*callback)(void *, int, char **, char **)) {
    Request request;

    request.request = "SELECT * FROM FRIENDSHIP "
                      "WHERE "
                      "user1_id = " + std::to_string(userId) + " OR user2_id = " + std::to_string(userId) + ";";
    request.data = data;
    request.callback = callback;
	return request;
}