//
// Created by abel on 26/09/2019.
//

#include <iostream>
#include <QNetworkDatagram>
#include "UdpClient.hpp"
#include "../Audio/AudioWrapper.hpp"

UdpClient::UdpClient(AudioWrapper &wrapper, const std::string &addr, unsigned short port) : wrapper(wrapper), address(QString(addr.c_str())), port(port) {
    this->udpSocket = new QUdpSocket(this);

    this->udpSocket->bind(QHostAddress::Any, this->port);
    QObject::connect(this->udpSocket, SIGNAL(readyRead()), this, SLOT(readReady()));
}

void UdpClient::readReady() {
    std::cout << "ready" << std::endl;
    while (this->udpSocket->hasPendingDatagrams())
    {
        QHostAddress host;
        unsigned short port;

        std::vector<unsigned char> ucharVector;
        QNetworkDatagram datagram = udpSocket->receiveDatagram();
        QByteArray data = datagram.data();
        std::cout << data.size() << std::endl;

        for (const auto it : data)
            ucharVector.push_back(it);
        AudioPacket packet;
        packet = AudioPacket::unserialize(ucharVector);
        std::vector<float> uncompressedAudio = this->wrapper.getCompressor().uncompress(packet);
        this->wrapper.addInQueue(std::move(uncompressedAudio));
    }
}

void UdpClient::sendData(std::vector<unsigned char> &data)
{
    QByteArray array;

    for (auto it : data)
        array.append(static_cast<char>(it));

    this->udpSocket->writeDatagram(array, this->address, this->port);
//    this->udpSocket->waitForReadyRead();
}