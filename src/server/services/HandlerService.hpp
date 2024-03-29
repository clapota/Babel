#ifndef BABEL_HANDLERSERVICE_HPP
#define BABEL_HANDLERSERVICE_HPP

#include <boost/asio.hpp>
#include "IPacket.hpp"
#include "IService.hpp"
#include "UserService.hpp"
#include "PacketFactory.hpp"
#include "ServiceLocator.hpp"
#include "DispatchService.hpp"
#include "network/IConnection.hpp"
#include "logic/handshake/HandshakeHandler.hpp"
#include "IO/NativeBinaryReader.hpp"

class HandlerService : public IService {
    public:
        void handlePacket(boost::shared_ptr<IConnection> &connection, void *data, size_t len) {

            auto userService = ServiceLocator<UserService>::getService();
            auto dispatchService = ServiceLocator<DispatchService>::getService();

            auto client = userService->retrieveClient(connection);

            if (client == nullptr)
                return;

            /* TODO : Build packet */
            std::stringstream stream;
            NativeBinaryReader reader;

            stream.write((const char *)data, len);
            reader.setStream(&stream);

            auto id = reader.readInt();

            /***********************/

            /* TODO : Retrieve handler from list */
            if (_handlers.find(id) != _handlers.end()) {
                const auto &handler = _handlers.at(id);
                /*************************************/

                auto packe = PacketFactory::instantiate(id);

                /* TODO : Generate DispatchData */
                DispatchData dispatchData = {
                        PacketFactory::instantiate(id),
                        client,
                        handler
                };
                dispatchData.packet->deserialize(reader);
                /********************************/

                /* TODO : Dispatch */
                dispatchService->enqueue(dispatchData);
                /*******************/
            }
        }
    private:
        using Handler = std::function<void(boost::shared_ptr<Client>, std::unique_ptr<IPacket> &)>;

        static const std::map<int, Handler> _handlers;
};

#endif //BABEL_HANDLERSERVICE_HPP
