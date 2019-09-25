//
// Created by abel on 25/09/2019.
//

#include "TcpClient.hpp"

TcpClient::TcpClient(boost::asio::io_service &io_service, boost::asio::ip::tcp::endpoint &endpoint) : _io_service(io_service) {
    this->connect(endpoint);
}

void TcpClient::connect(boost::asio::ip::tcp::endpoint &endpoint) {
}
