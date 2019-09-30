#include <boost/bind.hpp>
#include "BoostConnection.hpp"

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
        log->writeError(error.message());
        return;
    }

    #ifdef DEBUG
        log->writeHour("Sent " + std::to_string(size) + " bytes");
    #endif
}

void const BoostConnection::handleRead(const boost::system::error_code &error, size_t size)
{
    auto log = ServiceLocator<LogService>::getService();

    if (!error) {
        #ifdef DEBUG
            std::cout.write(_bytes.data(), size);
        #endif
        getSocket().async_read_some(boost::asio::buffer(_bytes),
                                    boost::bind(&BoostConnection::handleRead,
                                                this,
                                                boost::asio::placeholders::error,
                                                boost::asio::placeholders::bytes_transferred));
    } else {
        log->writeError(error.message());
    }
}