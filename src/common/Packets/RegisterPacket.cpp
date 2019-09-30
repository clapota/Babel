/*
** EPITECH PROJECT, 2019
** Babel
** File description:
** Created by antoine_dh,
*/

#include "RegisterPacket.hpp"

RegisterPacket::RegisterPacket(const std::string &email,
    const std::string &password)
    : username(email), password(password)
{
}

int RegisterPacket::getId() const
{
    return PacketId;
}

const std::string &RegisterPacket::getUsername() const
{
    return username;
}

const std::string &RegisterPacket::getPassword() const
{
    return password;
}
