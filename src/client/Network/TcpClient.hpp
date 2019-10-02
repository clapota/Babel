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
        void friendAccepted(IPacket &);
        void friendRequest(IPacket &);
        void friendData(IPacket &);
        void friendRemoved(IPacket &);
        void registerResponse(IPacket &);
        void connectResponse(IPacket &);
        void addFriendResponse(IPacket &);
        void removeFriendResponse(IPacket &);
        void acceptFriendResponse(IPacket &);
        void callResponse(IPacket &);
        void hangUpResponse(IPacket &);
        /***
         * friendAccept is when someone accepts me in friendlist
         */
        void friendAccept(IPacket &);
        /***
         * requestFriend is when someone ask to be my friend
         */
         void requestFriend(IPacket &);
         void userInfo(IPacket &);
         void removedFromFriend(IPacket &);
    private:
        QTcpSocket *tcpSocket = nullptr;
        unsigned short port;
        QHostAddress address;
        std::map<ushort, std::function<void(IPacket &packet)>> signalMap = {
                {1, [this](IPacket &packet){emit registerResponse(packet);}},
                {2, [this](IPacket &packet){emit connectResponse(packet);}},
                {3, [this](IPacket &packet){emit addFriendResponse(packet);}},
                {4, [this](IPacket &packet){emit removeFriendResponse(packet);}},
                {5, [this](IPacket &packet){emit acceptFriendResponse(packet);}},
                {6, [this](IPacket &packet){emit callResponse(packet);}},
                {7, [this](IPacket &packet){emit hangUpResponse(packet);}},
                {8, [this](IPacket &packet){emit friendAccept(packet);}},
                {9, [this](IPacket &packet){emit requestFriend(packet);}},
                {10, [this](IPacket &packet){emit userInfo(packet);}},
                {11, [this](IPacket &packet){emit removedFromFriend(packet);}},
                };

};


#endif //BABEL_TCPCLIENT_HPP
