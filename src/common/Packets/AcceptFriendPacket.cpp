/*
** EPITECH PROJECT, 2019
** Babel
** File description:
** Created by antoine_dh,
*/

#include "AcceptFriendPacket.hpp"

bool AcceptFriendPacket::isAccepted() const
{
    return accepted;
}

const std::string &AcceptFriendPacket::getUsername() const
{
    return username;
}

AcceptFriendPacket::AcceptFriendPacket(bool accepted,
    const std::string &username)
    : accepted(accepted), username(username)
{
}

int AcceptFriendPacket::getId() const
{
    return PacketId;
}
