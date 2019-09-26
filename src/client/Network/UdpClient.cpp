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
    while (this->udpSocket->hasPendingDatagrams())
    {
        QHostAddress host;
        unsigned short port;

        std::vector<unsigned char> ucharVector(this->udpSocket->pendingDatagramSize());
        QNetworkDatagram datagram = udpSocket->receiveDatagram();
        QByteArray data = datagram.data();
        QByteArray reverse;
        reverse.reserve(data.size());
        for (int i =data.size()-1;i>=0;--i)
            reverse.append(data.at(i));

        for (const auto &it: reverse) {
            ucharVector.push_back(static_cast<unsigned char>(it));
        }
        AudioPacket packet;
        packet = AudioPacket::unserialize(ucharVector);
        std::cout << "NB Bytes " << packet.nbBytes << std::endl;
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
    this->udpSocket->waitForReadyRead();
}