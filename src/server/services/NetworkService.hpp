    #ifndef BABEL_NETWORKSERVICE_HPP
#define BABEL_NETWORKSERVICE_HPP

#include "network/IListener.hpp"

template <class T >
class NetworkService : public IService {
    static_assert(std::is_base_of<IListener, T>::value, "T must inherit from IListener");
    public:
        explicit NetworkService() : _listener() {};
        const void stop() { _listener.stop(); }
        const void accept() { _listener.accept(); }
    private:
        T _listener;
};

#endif //BABEL_NETWORKSERVICE_HPP