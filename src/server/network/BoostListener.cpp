#include <boost/bind.hpp>
#include "BoostListener.hpp"
#include "services/UserService.hpp"

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
    auto log = ServiceLocator<LogService>::getService();

    log->writeHour("Closing listener ...");
    _isRunning = false;
    _acceptor.cancel();
    _acceptor.close();
    log->writeHour("Listener closed");
}

void BoostListener::handle_accept(BoostConnection::pointer &new_connection,
    const boost::system::error_code &error)
{
    auto log = ServiceLocator<LogService>::getService();
    auto clients = ServiceLocator<UserService>::getService();

    if (!error) {
        #ifdef DEBUG
        log->writeHour("Client connected");
        #endif

        boost::shared_ptr<IConnection> client = new_connection;
        clients->registerClient(client);

        new_connection->read_async();

        if (_isRunning)
            accept();
    } else {
        log->writeHour(error.message());
        /* TODO : handle error*/
    }
}
