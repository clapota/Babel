/*
** EPITECH PROJECT, 2019
** Babel
** File description:
** Created by antoine_dh,
*/

#include "AddFriendPacket.hpp"

const std::string &AddFriendPacket::getUsername() const
{
    return username;
}

AddFriendPacket::AddFriendPacket(const std::string &username)
    : username(username)
{
}

int AddFriendPacket::getId() const
{
    return PacketId;
}
