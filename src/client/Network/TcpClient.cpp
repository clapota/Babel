//
// Created by abel on 26/09/2019.
//

#include "TcpClient.hpp"

TcpClient::TcpClient(const std::string &addr, unsigned short port) : address(QString(addr.c_str())), port(port) {
    this->tcpSocket = new QTcpSocket(this);
    this->tcpSocket->connectToHost(address, port);

    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(dispatchData()));
}

void TcpClient::sendData(std::vector<unsigned char> &data) {
    QByteArray array;

    for (const auto &it: data)
        array.append(it);
    this->tcpSocket->write(array);
}

void TcpClient::dispatchData() {
    QByteArray array = this->tcpSocket->readAll();

}
