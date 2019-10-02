#include "HandshakeHandler.hpp"
#include "Packets/ConnectPacket.hpp"
#include "Packets/RegisterPacket.hpp"
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
