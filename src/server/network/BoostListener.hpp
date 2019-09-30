#ifndef BABEL_BOOSTNETWORK_HPP
#define BABEL_BOOSTNETWORK_HPP

#include <boost/asio.hpp>
#include "IListener.hpp"
#include "BoostConnection.hpp"
#include "services/BoostService.hpp"
#include "services/ServiceLocator.hpp"

class BoostListener : public IListener {
    public:
        explicit BoostListener(int port = LISTENER_DEFAULT_PORT) :
            _acceptor(ServiceLocator<BoostService>::getService()->getContext(),
                      boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)) { }
        void stop() override;
        void accept() override;
    private:
        bool _isRunning = false;
        boost::asio::ip::tcp::acceptor _acceptor;
        void handle_accept(BoostConnection::pointer new_connection, const boost::system::error_code& error);
};

#endif //BABEL_BOOSTLISTENER_HPP
