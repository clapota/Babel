#include "HandshakeHandler.hpp"
#include "PacketFactory.hpp"
#include "database/SqliteProvider.hpp"
#include "services/ServiceLocator.hpp"
#include "services/DataBaseService.hpp"

void HandshakeHandler::loginHandler(boost::shared_ptr<Client> client, std::unique_ptr<IPacket> &packet)
{
    auto cp = dynamic_cast<ConnectPacket &>(* packet);

    std::cout << "ntm abel ton mot de passe " <<  cp.getPassword() << std::endl;
}

void HandshakeHandler::registerHandler(boost::shared_ptr<Client>, std::unique_ptr<IPacket> &packet)
{
    auto db = ServiceLocator<DataBaseService<SqliteProvider>>::getService();
    auto rp = dynamic_cast<RegisterPacket &>(* packet);

    //db->executeRequest(RequestBuilder::addUser(rp.getUsername(), rp.getPassword()));
}

void HandshakeHandler::addFriendHandler(boost::shared_ptr<Client> client,
    std::unique_ptr<IPacket> &packet)
{
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
}
