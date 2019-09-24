#ifndef BABEL_BOOSTSERVICE_HPP
#define BABEL_BOOSTSERVICE_HPP

#include <boost/asio.hpp>

class BoostService {
    public:
        void const runContext() { _io_context.run(); }
        void const stopContext() { _io_context.stop(); }
        boost::asio::io_context &getContext() { return _io_context; }
    private:
        boost::asio::io_context _io_context;
};

#endif //BABEL_BOOSTSERVICE_HPP
