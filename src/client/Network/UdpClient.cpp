/*
** EPITECH PROJECT, 2019
** Babel
** File description:
** Created by abel,
*/

#include <iostream>
#include <QNetworkDatagram>
#include "UdpClient.hpp"
#include "Audio/AudioWrapper.hpp"

UdpClient::UdpClient(AudioWrapper &wrapper, const std::string &addr, unsigned short port) : wrapper(wrapper), address(QString(addr.c_str())), port(port) {
    this->udpSocket = new QUdpSocket(this);
    this->udpSocket->bind(QHostAddress::Any, this->port);
    QObject::connect(this->udpSocket, SIGNAL(readyRead()), this, SLOT(readReady()));
    this->timer = new QTimer;
    this->timer->setInterval(5000);
    QObject::connect(this->timer, SIGNAL(timeout()), this, SLOT(disconnect()));
    this->timer->start();
}

void UdpClient::readReady() {
    while (this->udpSocket->hasPendingDatagrams())
    {
        this->timer->setInterval(5000);
        QHostAddress host;

        std::vector<unsigned char> ucharVector;
        QNetworkDatagram datagram = udpSocket->receiveDatagram();
        QByteArray data = datagram.data();
        for (const auto &it : data)
            ucharVector.push_back(static_cast<unsigned char>(it));
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
}

bool UdpClient::isConnected() const {
    return this->isAlive;
}

void UdpClient::disconnect() {
    this->wrapper.close();
}