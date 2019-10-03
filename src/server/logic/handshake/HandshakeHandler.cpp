#include <services/UserService.hpp>
#include "HandshakeHandler.hpp"
#include "PacketFactory.hpp"
#include "database/SqliteProvider.hpp"
#include "services/ServiceLocator.hpp"
#include "services/DataBaseService.hpp"


/***
 * Called every time the client send a ConnectPacket
 * @param client
 * @param packet (ConnectPacket)
 */
void HandshakeHandler::loginHandler(boost::shared_ptr<Client> client, std::unique_ptr<IPacket> &packet)
{
    auto cp = dynamic_cast<ConnectPacket &>(* packet);
    auto db = ServiceLocator<DataBaseService<SqliteProvider>>::getService();
    auto userService = ServiceLocator<UserService>::getService();

    User user = db->getUserByName(cp.getEmail());
    ResponsePacket response;

    std::cout << "received : " << cp.getEmail() << " " << cp.getPassword() << std::endl;
    std::cout << "User : " << user.id << " " << user.username << " " << user.password << std::endl;
    response.setRequestId(ConnectPacket::PacketId);
    bool ok = !(user.id == -1 || user.password != cp.getPassword() || userService->getClientByUserName(user.username) == nullptr);
    response.setOk(ok);

    client->send(response);
    if (ok) {
        client->setUser(user);
        std::cout << "User logged in " << std::endl;
        std::vector<User> friendsOfClient = db->getFriendsOf(user.id);
        for (auto &it: friendsOfClient) {
            FriendInfoPacket friendInfoPacket;

            friendInfoPacket.setUsername(it.username);
            boost::shared_ptr<Client> friendClient = userService->getClientByUserName(it.username);
            if (friendClient && friendClient->isLogged())
                friendInfoPacket.setState(FriendInfoPacket::CONNECTED);
            else
                friendInfoPacket.setState(FriendInfoPacket::DISCONNECTED);
            client->send(friendInfoPacket);
        }
        std::vector<PendingFriendRequest> requestOf = db->getPendingFriendsRequestOf(user.id);
        for (auto &it: requestOf) {
            ReceivedFriendRequestPacket rfrp;
            rfrp.setUsername(db->getUserById(it.sender_id).username);
            client->send(rfrp);
        }
    }
}

/***
 * Called every time the client send a RegisterPacket
 * @param client
 * @param packet (RegisterPacket)
 */
void HandshakeHandler::registerHandler(boost::shared_ptr<Client> client, std::unique_ptr<IPacket> &packet)
{
    auto db = ServiceLocator<DataBaseService<SqliteProvider>>::getService();
    auto rp = dynamic_cast<RegisterPacket &>(* packet);

    ResponsePacket response;

    response.setOk(db->createUser(rp.getUsername(), rp.getPassword()));
    response.setRequestId(RegisterPacket::PacketId);
    if (response.isOk())
        ServiceLocator<LogService>::getService()->writeHour("User created with success in db with username : " + rp.getUsername() + " and pass " + rp.getPassword());
    client->send(response);
}

/***
 * called every time the client send an AddFriendPacket
 * @param client
 * @param packet (AddFriendPacket)
 */
void HandshakeHandler::addFriendHandler(boost::shared_ptr<Client> client,
    std::unique_ptr<IPacket> &packet)
{
    auto userService = ServiceLocator<UserService>::getService();
    auto db = ServiceLocator<DataBaseService<SqliteProvider>>::getService();

    auto &afp = dynamic_cast<AddFriendPacket &>(*packet);

    User friendUser = db->getUserByName(afp.getUsername());

    if (friendUser.id == -1 || !client->isLogged() || afp.getUsername() == client->getUser().username)
        return client->send(ResponsePacket(packet->getId(), false));
    /* check if users are already friends */
    auto clientFriends = db->getFriendsOf(client->getUser().username);
    if (std::find_if(clientFriends.begin(), clientFriends.end(), [&](const User &u) {
        return u.username == client->getUser().username;
    }) != clientFriends.end())
        return client->send(ResponsePacket(packet->getId(), false));
    db->addPendingFriendRequest(client->getUser().username, friendUser.username);
    ServiceLocator<LogService>::getService()->writeHour(client->getUser().username + " added " + afp.getUsername() + " as friend.");
    client->send(ResponsePacket(packet->getId(), true));


    // If friendUser is connected, we send him a ReceivedFriendRequestPacket
    boost::shared_ptr<Client> friendClient = userService->getClientByUserName(friendUser.username);
    if (friendClient) {
        ReceivedFriendRequestPacket receivedFriendRequestPacket;

        try {
            receivedFriendRequestPacket.setUsername(client->getUser().username);
            friendClient->send(receivedFriendRequestPacket);
        } catch (...) {
            ServiceLocator<LogService>::getService()->writeHour("Error while sending packet to friend");
        }
    }
}
/***
 * Called every time the client send an AcceptFriendPacket
 * @param client
 * @param packet (AcceptFriendPacket)
 */
void HandshakeHandler::acceptFriendHandler(boost::shared_ptr<Client> client, std::unique_ptr<IPacket> &packet) {
    auto db = ServiceLocator<DataBaseService<SqliteProvider>>::getService();
    auto userService = ServiceLocator<UserService>::getService();
    auto &afp = dynamic_cast<AcceptFriendPacket &>(*packet);
    bool alreadyFriend = false;
    bool FriendRequest = false;
    User futureFriend = db->getUserByName(afp.getUsername());

    ResponsePacket response;
    response.setOk(false);
    response.setRequestId(AcceptFriendPacket::PacketId);

    if (!client->isLogged()) {
        client->send(response);
    } else {
        std::vector<User> friendsOfClient = db->getFriendsOf(client->getUser().username);
        std::vector<PendingFriendRequest> requestsOfClient = db->getPendingFriendsRequestOf(client->getUser().username);

        for (auto &it: friendsOfClient) {
            if (it.username == afp.getUsername())
                alreadyFriend = true;
        }
        for (auto &it: requestsOfClient) {
            if (it.receiver_id == client->getUser().id && it.sender_id == futureFriend.id)
                FriendRequest = true;
        }
        // We need to check if they are not already friend AND if there IS a friend request
        if (!alreadyFriend && FriendRequest)
            response.setOk(true);
        client->send(response);
        // Now we will send some FriendAcceptedPacket
        if (!alreadyFriend && FriendRequest) {
            FriendAcceptedPacket fap;

            fap.setUsername(futureFriend.username);
            client->send(fap);
            auto friendClient = userService->getClientByUserName(futureFriend.username);

            if (friendClient && friendClient->isLogged()) {
                FriendAcceptedPacket fap2;

                fap2.setUsername(client->getUser().username);
                friendClient->send(fap2);
            }
        }
    }
}

/***
 * Called every time the client send a CallPacket
 * @param client
 * @param packet
 */
void HandshakeHandler::callFriendHandler(boost::shared_ptr<Client> client, std::unique_ptr<IPacket> &packet) {
    ResponsePacket response;
    auto db = ServiceLocator<DataBaseService<SqliteProvider>>::getService();
    auto userService = ServiceLocator<UserService>::getService();
    auto &callPacket = dynamic_cast<CallPacket &>(*packet);

    response.setRequestId(callPacket.getId());
    response.setOk(false);
    bool areFriends = false;

    if (client->isLogged()) {
        std::vector<User> friendOfClient = db->getFriendsOf(client->getUser().username);

        for (auto &it: friendOfClient) {
            if (it.username == callPacket.getUsername())
                areFriends = true;
        }

        ///Pour l'instant t'as pas le choix, si on t'appelle bah on t'appelle
        if (client->getUser().username != callPacket.getUsername() && areFriends && userService->getClientByUserName(callPacket.getUsername()) != nullptr) {
            response.setOk(true);
            client->send(response);

            CallingPacket cp;
            cp.setIp(userService->getClientByUserName(callPacket.getUsername())->getIp());
            client->send(cp);
            CallingPacket cp2;
            cp2.setIp(client->getIp());
            userService->getClientByUserName(callPacket.getUsername())->send(cp2);
        } else {
            client->send(response);
        }
    }
}
