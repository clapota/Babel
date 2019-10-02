#ifndef BABEL_HANDLERSERVICE_HPP
#define BABEL_HANDLERSERVICE_HPP

#include <boost/asio.hpp>
#include "IPacket.hpp"
#include "IService.hpp"
#include "UserService.hpp"
#include "ServiceLocator.hpp"
#include "DispatchService.hpp"
#include "../network/IConnection.hpp"
#include "../logic/handshake/HandshakeHandler.hpp"

class HandlerService : public IService {
    public:
        void handlePacket(boost::shared_ptr<IConnection> &connection, void *data, size_t len) {

            auto userService = ServiceLocator<UserService>::getService();
            auto dispatchService = ServiceLocator<DispatchService>::getService();

            auto client = userService->retrieveClient(connection);

            if (client == nullptr)
                return;

            /* TODO : Build packet */

            /* TODO : Retrieve handler from list */

            /* TODO : Generate DispatchData */
            /* Packet : NOT YET (NEED FACTORY)
             * Client : YES
             * Method : YES */

            /* TODO : Dispatch */
        }
    private:
        std::map<ushort, std::function<void(Client *, IPacket *)>> _handlers = {
            { 1, std::function<void(Client *, IPacket *)>(HandshakeHandler::loginHandler)}
        };
};

#endif //BABEL_HANDLERSERVICE_HPP
