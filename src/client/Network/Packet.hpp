//
// Created by abel on 26/09/2019.
//

#ifndef BABEL_PACKET_HPP
#define BABEL_PACKET_HPP

#include <cstddef>

struct Packet {
    int id;
    std::size_t dataSize;
    char *data;
};

#endif //BABEL_PACKET_HPP
