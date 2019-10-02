#ifndef BABEL_CLIENT_HPP
#define BABEL_CLIENT_HPP

#include <boost/asio.hpp>
#include "IPacket.hpp"
#include "IO/NativeBinaryWriter.hpp"
#include "../network/IConnection.hpp"

class Client {
    public:
        static int ReferenceId;

        int getId() { return _id; }

        static boost::shared_ptr<Client> create(boost::shared_ptr<IConnection> &connection)
        {
            return boost::shared_ptr<Client>(new Client(ReferenceId++, connection));
        }

        void send(IPacket &packet)
        {
            NativeBinaryWriter finalWriter, writer;

            packet.serialize(writer);

            finalWriter.writeInt((uint32_t )packet.getId());
            finalWriter.writeString(writer.Data().str());

            /* WARNING : NOT FINAL IMPLEMENTATION */
            Connection->write_async(finalWriter.Data().str());
        }

        boost::shared_ptr<IConnection> Connection;
    private:
        int _id = 0;

        explicit Client(int id, boost::shared_ptr<IConnection> &connection) :
            Connection(connection),
            _id(id) { }
};

#endif //BABEL_CLIENT_HPP
