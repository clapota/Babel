//
// Created by abel on 25/09/2019.
//

#ifndef BABEL_TCPCLIENT_HPP
#define BABEL_TCPCLIENT_HPP

#include <boost/asio.hpp>

class TcpClient {
    public:
        TcpClient(boost::asio::io_service &io_service, boost::asio::ip::tcp::endpoint &endpoint);
    private:
        void connect(boost::asio::ip::tcp::endpoint &endpoint);
        boost::asio::io_service &_io_service;
};


#endif //BABEL_TCPCLIENT_HPP
