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

    stream.write(array.data(), array.size());
    NativeBinaryReader reader;

    reader.setStream(&stream);
    int id = reader.readInt();
    if (id == PacketFactory::RESPONSE_PACKET) {
        ResponsePacket packet;

        packet.deserialize(reader);
        int responseId = packet.getRequestId();
        this->signalMap[responseId](dynamic_cast<IPacket &>(packet));
    }
}
