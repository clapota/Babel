#ifndef BABEL_HANDSHAKEHANDLER_HPP
#define BABEL_HANDSHAKEHANDLER_HPP

#include "../Client.hpp"

class HandshakeHandler
{
    public:
        static void loginHandler(Client *client, IPacket *packet);
};

#endif //BABEL_HANDSHAKEHANDLER_HPP
