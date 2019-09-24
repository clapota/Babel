#include <boost/bind.hpp>
#include "BoostListener.hpp"

void BoostListener::accept()
{
    BoostConnection::pointer new_connection = BoostConnection::create();

    _isRunning = true;
    _acceptor.async_accept(new_connection->getSocket(),
                           boost::bind(&BoostListener::handle_accept,
                                       this,
                                       new_connection,
                                       boost::asio::placeholders::error));
}

void BoostListener::stop()
{
    _isRunning = false;
}

void BoostListener::handle_accept(BoostConnection::pointer new_connection,
    const boost::system::error_code &error)
{
    auto log = ServiceLocator<LogService>::getService();

    if (!error) {
        log->writeHour("Client connected");
        new_connection->write_async("bite");
    //    new_connection.start();
        if (_isRunning)
            accept();
    } else {
        /* TODO : handle error*/
    }
}
