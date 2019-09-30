#include <boost/bind.hpp>
#include "BoostConnection.hpp"
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

void BoostConnection::write_async(void *data, size_t size)
{
    auto &socket = getSocket();

    boost::asio::async_write(socket, boost::asio::buffer(data, size),
                                     boost::bind(&BoostConnection::handleWrite,
                                                 shared_from_this(),
                                                 boost::asio::placeholders::error,
                                                 boost::asio::placeholders::bytes_transferred));
}

void BoostConnection::write_async(const std::string &message)
{
    auto &socket = getSocket();

    boost::asio::async_write(socket, boost::asio::buffer(message),
                                     boost::bind(&BoostConnection::handleWrite, shared_from_this(),
                                     boost::asio::placeholders::error,
                                     boost::asio::placeholders::bytes_transferred));
}

void const BoostConnection::handleWrite(const boost::system::error_code &error, size_t size)
{
    auto log = ServiceLocator<LogService>::getService();

    if (error) {
        log->writeError("[HandleWrite] " + error.message());
        return;
    }

    #ifdef DEBUG
        log->writeHour("Sent " + std::to_string(size) + " bytes");
    #endif
}

void const BoostConnection::handleRead(const boost::system::error_code &error, size_t size)
{
    auto log = ServiceLocator<LogService>::getService();
    auto dispatch = ServiceLocator<DispatchService>::getService();

    if (!error) {
        DispatchData data = { this, std::function<void(IConnection &)>(bite) };

        dispatch->enqueue(data);

        getSocket().async_read_some(boost::asio::buffer(_bytes),
                                    boost::bind(&BoostConnection::handleRead,
                                                this,
                                                boost::asio::placeholders::error,
                                                boost::asio::placeholders::bytes_transferred));
    } else {
        log->writeError("[HandleRead] " + error.message());
    }
}

void bite(IConnection &connection)
{
    std::cout << "Executing handler" << std::endl;
    std::string a("bite");
    connection.write_async(a);
}