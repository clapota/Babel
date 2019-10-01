/*
** EPITECH PROJECT, 2019
** Babel
** File description:
** Created by antoine_dh,
*/

#include "CallPacket.hpp"

const std::string &CallPacket::getUsername() const
{
    return username;
}

CallPacket::CallPacket(const std::string &username)
    : username(username)
{
}

int CallPacket::getId() const
{
    return PacketId;
}
