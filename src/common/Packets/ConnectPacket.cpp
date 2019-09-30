/*
** EPITECH PROJECT, 2019
** Babel
** File description:
** Created by antoine_dh,
*/

#include "ConnectPacket.hpp"

int ConnectPacket::getId() const
{
    return PacketId;
}

ConnectPacket::ConnectPacket(const std::string &email,
    const std::string &password)
    : email(email), password(password)
{
}

const std::string &ConnectPacket::getEmail() const
{
    return email;
}

const std::string &ConnectPacket::getPassword() const
{
    return password;
}
