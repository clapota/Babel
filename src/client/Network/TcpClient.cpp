//
// Created by abel on 26/09/2019.
//

#include <sstream>
#include <iostream>
#include <IO/NativeBinaryWriter.hpp>
#include "TcpClient.hpp"
#include "../../common/IO/NativeBinaryReader.hpp"
#include "../../common/PacketFactory.hpp"

TcpClient::TcpClient(const std::string &addr, unsigned short port) : address(QString(addr.c_str())), port(port) {
    this->tcpSocket = new QTcpSocket(this);
    this->tcpSocket->connectToHost(address, port);

    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(dispatchData()));
}

void TcpClient::sendData(IPacket &packet) {
    NativeBinaryWriter writer;
    writer.writeInt(packet.getId());
    packet.serialize(writer);
    std::stringstream data(writer.Data().str());
    auto bof = data.tellg();
    data.seekg(0, std::ios::end);
    auto stream_size = std::size_t(data.tellg() - bof);
    data.seekg(0, std::ios::beg);
    std::vector<unsigned char> vectorData(stream_size);
    data.read(reinterpret_cast<char *>(vectorData.data()), std::streamsize(stream_size));

    QByteArray array;

    for (const auto &it: vectorData)
        array.append(it);
    this->tcpSocket->write(array);
}

void TcpClient::dispatchData() {
    QByteArray array = this->tcpSocket->readAll();

    std::stringstream stream;

    stream.write((const char *)array.data(), array.size());
    NativeBinaryReader reader;
    std::string toto = array.toStdString();

    std::cout << "received of size : " << stream.str().size() << " data : " << stream.str() << std::endl;
    reader.setStream(&stream);
    int id = reader.readInt();
    std::cout << "Dispatching " << id << std::endl;
    if (id == PacketFactory::RESPONSE_PACKET) {
        ResponsePacket packet;

        std::cout << "BITE BITE " << std::endl;
        packet.deserialize(reader);
        int responseId = packet.getRequestId();
        std::cout << "rId" << responseId << std::endl;
        this->signalMap[responseId](dynamic_cast<IPacket &>(packet));
    } else if (id == PacketFactory::FRIEND_ACCEPTED) {
        FriendAcceptedPacket packet;

        packet.deserialize(reader);
        this->signalMap[id](dynamic_cast<IPacket &>(packet));
    } else if (id == PacketFactory::RECEIVED_FRIEND_REQUEST) {
        ReceivedFriendRequestPacket packet;

        packet.deserialize(reader);
        this->signalMap[id](dynamic_cast<IPacket &>(packet));
    } else if (id == PacketFactory::FRIEND_INFO) {
        FriendInfoPacket packet;

        packet.deserialize(reader);
        this->signalMap[id](dynamic_cast<IPacket &>(packet));
    } else if (id == PacketFactory::FRIEND_REMOVED) {
        FriendRemovedPacket packet;

        packet.deserialize(reader);
        this->signalMap[id](dynamic_cast<IPacket &>(packet));
    }
}
