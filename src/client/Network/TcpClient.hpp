//
// Created by abel on 26/09/2019.
//

#ifndef BABEL_TCPCLIENT_HPP
#define BABEL_TCPCLIENT_HPP

#include <QTcpSocket>
#include <QtNetwork/QHostAddress>

class TcpClient : public QObject {
    Q_OBJECT
    public:
        TcpClient(const std::string &addr, unsigned short port);
        ~TcpClient() override = default;
        void sendData(std::vector<unsigned char> &);
    public slots:
        void dispatchData();
    private:
        QTcpSocket *tcpSocket = nullptr;
        unsigned short port;
        QHostAddress address;
};


#endif //BABEL_TCPCLIENT_HPP
