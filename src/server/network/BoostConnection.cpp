#include <boost/bind.hpp>
#include "BoostConnection.hpp"

void BoostConnection::read_async()
{
    std::cout << "bite" << std::endl;
}

void BoostConnection::write_async(void *data, size_t size)
{
    auto &socket = getSocket();

    boost::asio::async_write(socket, boost::asio::buffer(data, size),
        boost::bind(&BoostConnection::handleWrite, shared_from_this(),
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
    #ifdef DEBUG
    auto log = ServiceLocator<LogService>::getService();
    log->writeHour("Sent " + std::to_string(size) + " bytes");
    #endif
}