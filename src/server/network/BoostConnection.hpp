#ifndef BABEL_BOOSTCONNECTION_HPP
#define BABEL_BOOSTCONNECTION_HPP

#include <boost/enable_shared_from_this.hpp>
#include "IConnection.hpp"
#include "services/BoostService.hpp"
#include "services/ServiceLocator.hpp"

class BoostConnection : public IConnection, public boost::enable_shared_from_this<BoostConnection> {
    public:
        using pointer = boost::shared_ptr<BoostConnection>;

        static pointer create()
        {
            return pointer(new BoostConnection());
        }

        boost::asio::ip::tcp::socket& getSocket()
        {
            return _socket;
        }

        boost::shared_ptr<IConnection> toIConnection()
        {
            return shared_from_this();
        }

        void shutdown() override;
        void read_async() override;
      /*  void write_async(std::strng *data, size_t size) override; */
        void write_async(const std::string &message) override;
        std::string getClientIp() const override;
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
