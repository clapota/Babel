//
// Created by abel on 26/09/2019.
//

#ifndef BABEL_TCPCLIENT_HPP
#define BABEL_TCPCLIENT_HPP

#include <QTcpSocket>
#include <QtNetwork/QHostAddress>
#include "../../common/IPacket.hpp"

class TcpClient : public QObject {
    Q_OBJECT
    public:
        TcpClient(const std::string &addr, unsigned short port);
        ~TcpClient() override = default;
        void sendData(IPacket &);
    public slots:
        void dispatchData();
    signals:
        void friendAccepted();
        void friendRequest();
        void friendData();
        void friendRemoved();
    private:
        QTcpSocket *tcpSocket = nullptr;
        unsigned short port;
        QHostAddress address;
};


#endif //BABEL_TCPCLIENT_HPP
