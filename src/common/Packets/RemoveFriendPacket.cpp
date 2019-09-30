/*
** EPITECH PROJECT, 2019
** Babel
** File description:
** Created by antoine_dh,
*/

#include "RemoveFriendPacket.hpp"

const std::string &RemoveFriendPacket::getUsername() const
{
    return username;
}

RemoveFriendPacket::RemoveFriendPacket(const std::string &username)
    : username(username)
{
}

int RemoveFriendPacket::getId() const
{
    return PacketId;
}
