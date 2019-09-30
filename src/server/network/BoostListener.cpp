#include <boost/bind.hpp>
#include "BoostListener.hpp"

void BoostListener::accept()
{
    BoostConnection::pointer new_connection = BoostConnection::create();

    test.push_back(new_connection);

    _isRunning = true;
    _acceptor.async_accept(new_connection->getSocket(),
                           boost::bind(&BoostListener::handle_accept,
                                       this,
                                       new_connection,
                                       boost::asio::placeholders::error));
}

void BoostListener::stop()
{
    auto log = ServiceLocator<LogService>::getService();

    log->writeHour("Closing listener ...");
    _isRunning = false;
    _acceptor.cancel();
    _acceptor.close();
    log->writeHour("Listener closed");
}

void BoostListener::handle_accept(BoostConnection::pointer new_connection,
    const boost::system::error_code &error)
{
    auto log = ServiceLocator<LogService>::getService();

    if (!error) {
        log->writeHour("Client connected");
        new_connection->read_async();
        if (_isRunning)
            accept();
    } else {
        log->writeHour(error.message());
        /* TODO : handle error*/
    }
}
