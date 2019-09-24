#ifndef BABEL_NETWORKSERVICE_HPP
#define BABEL_NETWORKSERVICE_HPP

#include "network/BoostListener.hpp"

class NetworkService {
    public:
        explicit NetworkService(ushort port) : _listener(port) {};
        const void stop() { this->_listener.stop(); }
        const void accept() { this->_listener.accept(); }
    private:
        BoostListener _listener;
};

#endif //BABEL_NETWORKSERVICE_HPP
