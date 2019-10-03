#ifndef BABEL_HANDSHAKEHANDLER_HPP
#define BABEL_HANDSHAKEHANDLER_HPP

#include "logic/Client.hpp"

class HandshakeHandler
{
    public:
        static void loginHandler(boost::shared_ptr<Client>, std::unique_ptr<IPacket> &packet);
        static void registerHandler(boost::shared_ptr<Client>, std::unique_ptr<IPacket> &packet);
        static void addFriendHandler(boost::shared_ptr<Client>, std::unique_ptr<IPacket> &packet);
        static void acceptFriendHandler(boost::shared_ptr<Client>, std::unique_ptr<IPacket> &packet);
};

#endif //BABEL_HANDSHAKEHANDLER_HPP
