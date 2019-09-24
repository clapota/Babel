#ifndef BABEL_ICONNECTION_HPP
#define BABEL_ICONNECTION_HPP

#include <boost/asio.hpp>

class IConnection {
    public:
        virtual void read_async() = 0;
        virtual void write_async(void *data, size_t size) = 0;
        virtual void write_async(const std::string &message) = 0;
};

#endif //BABEL_ICONNECTION_HPP
