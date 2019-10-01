#ifndef BABEL_CLIENTSERVICE_HPP
#define BABEL_CLIENTSERVICE_HPP

#include <vector>
#include "network/IConnection.hpp"

class Client {
    public:
        static int ReferenceId;

        static boost::shared_ptr<Client> create(boost::shared_ptr<IConnection> &connection)
        {
            return boost::shared_ptr<Client>(new Client(ReferenceId++, connection));
        }

        int getId() { return _id; }

        boost::shared_ptr<IConnection> Connection;
    private:
        int _id = 0;

        explicit Client(int id, boost::shared_ptr<IConnection> &connection) :
            Connection(connection),
            _id(id) { }
};

class UserService : public IService {
    public:
        void registerClient(boost::shared_ptr<IConnection> &connection) {
            _clients.emplace_back(Client::create(connection));
        }

        boost::shared_ptr<Client> retrieveClient(boost::shared_ptr<IConnection> &connection)
        {
            auto client = std::find_if(_clients.begin(), _clients.end(), [&](const auto &e) {
                return e->Connection == connection;
            });

           if (client != _clients.end())
                return client[0];
            return nullptr;
        }

        void removeClient(boost::shared_ptr<IConnection> &connection)
        {
            _clients.erase(std::remove_if(_clients.begin(), _clients.end(), [&](const auto &e) {
                return e->Connection == connection;
            }), _clients.end());
        }

    private:
        std::vector<boost::shared_ptr<Client>> _clients;
};
#endif //BABEL_CLIENTSERVICE_HPP
