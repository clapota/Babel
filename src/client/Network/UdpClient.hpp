//
// Created by abel on 26/09/2019.
//

#ifndef BABEL_UDPCLIENT_HPP
#define BABEL_UDPCLIENT_HPP

#include <QUdpSocket>

class AudioWrapper;

class UdpClient : QObject {
    Q_OBJECT
    public:
        UdpClient(AudioWrapper &wrapper, const std::string &addr, unsigned short port);
        ~UdpClient() = default;
        void sendData(std::vector<unsigned char> &);

    public slots:
        void readReady();
    private:
        QHostAddress address;
        unsigned short port;
        AudioWrapper &wrapper;
        QUdpSocket *udpSocket;
};


#endif //BABEL_UDPCLIENT_HPP
