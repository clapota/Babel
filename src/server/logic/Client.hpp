#ifndef BABEL_CLIENT_HPP
#define BABEL_CLIENT_HPP

#include <boost/asio.hpp>
#include "IPacket.hpp"
#include "IO/NativeBinaryWriter.hpp"
#include "network/IConnection.hpp"
#include "database/SqliteProvider.hpp"

class Client {
    public:
        static int ReferenceId;

        int getId() { return _id; }

        static boost::shared_ptr<Client> create(boost::shared_ptr<IConnection> &connection)
        {
            return boost::shared_ptr<Client>(new Client(ReferenceId++, connection));
        }

        void send(const IPacket &packet)
        {
            NativeBinaryWriter finalWriter, writer;

            packet.serialize(writer);

            finalWriter.writeInt((uint32_t )packet.getId());
            finalWriter.writeRawString(writer.Data().str());

            /* WARNING : NOT FINAL IMPLEMENTATION */
            Connection->write_async(finalWriter.Data().str());
        }

        bool isLogged() const
        {
            return _logged;
        }

        const User &getUser() const
        {
            if (!isLogged())
                throw std::runtime_error("User not logged in");
            return _user;
        }

        void setUser(const User &user)
        {
            _user = user;
            _logged = true;
        }

        void logout()
        {
            _user = User { .id = -1 };
            _logged = false;
        }

        const std::string &getIp() const
        {
            return Connection->getClientIp();
        }

        boost::shared_ptr<IConnection> Connection;
    private:
        int _id = 0;
        bool _logged = false;
        User _user;

        explicit Client(int id, boost::shared_ptr<IConnection> &connection) :
            Connection(connection),
            _id(id) { }
};

#endif //BABEL_CLIENT_HPP
