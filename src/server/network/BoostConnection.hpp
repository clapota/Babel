#ifndef BABEL_BOOSTCONNECTION_HPP
#define BABEL_BOOSTCONNECTION_HPP

#include <boost/enable_shared_from_this.hpp>
#include "IConnection.hpp"
#include "services/BoostService.hpp"
#include "services/ServiceLocator.hpp"

class BoostConnection : public IConnection, public boost::enable_shared_from_this<BoostConnection> {
    public:
        typedef boost::shared_ptr<BoostConnection> pointer;

        static pointer create()
        {
            return pointer(new BoostConnection());
        }

        boost::asio::ip::tcp::socket& getSocket()
        {
            return _socket;
        }

        void shutdown() override;
        void read_async() override;
        void write_async(void *data, size_t size) override;
        void write_async(const std::string &message) override;
    private:
        bool _isActive = false;
        std::array<char, 4096> _bytes;
        void const handleWrite(const boost::system::error_code&, size_t);
        void const handleRead(const boost::system::error_code &, size_t);
        BoostConnection() : _socket(ServiceLocator<BoostService>::getService()->getContext()),
                            _bytes({}),
                            _isActive(true) {}
        boost::asio::ip::tcp::socket _socket;
};

#endif //BABEL_BOOSTCONNECTION_HPP
