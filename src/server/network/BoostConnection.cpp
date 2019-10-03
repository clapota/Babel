#include <boost/bind.hpp>
#include <IO/NativeBinaryReader.hpp>
#include "BoostConnection.hpp"
#include "network/BoostListener.hpp"
#include "services/UserService.hpp"
#include "services/HandlerService.hpp"
#include "services/NetworkService.hpp"
#include "services/DispatchService.hpp"

using namespace std::placeholders;

void BoostConnection::read_async()
{
    getSocket().async_read_some(boost::asio::buffer(_bytes),
                                boost::bind(&BoostConnection::handleRead,
                                            shared_from_this(),
                                            boost::asio::placeholders::error,
                                            boost::asio::placeholders::bytes_transferred));
}

/*void BoostConnection::write_async(std::string &data, size_t size)
{
    auto &socket = getSocket();

    boost::asio::async_write(socket, boost::asio::buffer(data, size),
                                     boost::bind(&BoostConnection::handleWrite,
                                                 shared_from_this(),
                                                 boost::asio::placeholders::error,
                                                 boost::asio::placeholders::bytes_transferred));
} */

void BoostConnection::write_async(const std::string &message)
{
    auto &socket = getSocket();

    boost::asio::async_write(socket, boost::asio::buffer(message),
                                     boost::bind(&BoostConnection::handleWrite,
												shared_from_this(),
												boost::asio::placeholders::error,
												boost::asio::placeholders::bytes_transferred));
}

void const BoostConnection::handleWrite(const boost::system::error_code &error, size_t size)
{
    auto log = ServiceLocator<LogService>::getService();

    if (error) {
        log->writeError("[HandleWrite] " + error.message());
        /* TODO : remove from client list */
        shutdown();
        return;
    }

    #ifdef DEBUG
        log->writeHour("Sent " + std::to_string(size) + " bytes");
    #endif
}

void const BoostConnection::handleRead(const boost::system::error_code &error, size_t size)
{
    auto _this = this->toIConnection();
    auto log = ServiceLocator<LogService>::getService();
    auto handlerService = ServiceLocator<HandlerService>::getService();

    if (!error) {
        /* Work is done asynchronously */
        // dispatch->enqueue(data);
        handlerService->handlePacket(_this, _bytes.data(), size);

        if (_isActive) {
            getSocket().async_read_some(boost::asio::buffer(_bytes),
                                        boost::bind(&BoostConnection::handleRead,
                                                    shared_from_this(),
                                                    boost::asio::placeholders::error,
                                                    boost::asio::placeholders::bytes_transferred));
        }
    } else {
        this->shutdown();

        /* TODO : put in dispatcher
         * allows you to retrieve corresponding client
         * auto iConnection = this->toIConnection();
         * auto client = ServiceLocator<UserService>::getService()->retrieveClient(iConnection); */

        auto clientsService = ServiceLocator<UserService>::getService();

        clientsService->removeClient(_this);
        log->writeHour("Client disconnected");
    }
}

void BoostConnection::shutdown()
{
    _isActive = false;
     _socket.close();
}

std::string BoostConnection::getClientIp() const {
    std::string ip = this->_socket.remote_endpoint().address().to_string();

    return ip;
}
