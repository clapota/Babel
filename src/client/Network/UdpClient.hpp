/*
** EPITECH PROJECT, 2019
** Babel
** File description:
** Created by abel,
*/

#ifndef BABEL_UDPCLIENT_HPP
#define BABEL_UDPCLIENT_HPP

#include <QUdpSocket>
#include <QtCore/QTimer>

class AudioWrapper;

class UdpClient : QObject {
    Q_OBJECT
    public:
        UdpClient(AudioWrapper &wrapper, const std::string &addr, unsigned short port);
        ~UdpClient() override = default;
        void sendData(std::vector<unsigned char> &);
        bool isConnected() const;

    public slots:
        void disconnect();
        void readReady();
    private:
        QHostAddress address;
        unsigned short port;
        AudioWrapper &wrapper;
        QUdpSocket *udpSocket;
        bool isAlive = true;
        QTimer *timer;
};

#endif //BABEL_UDPCLIENT_HPP
