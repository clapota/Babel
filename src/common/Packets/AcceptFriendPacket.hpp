/*
** EPITECH PROJECT, 2019
** Babel
** File description:
** Created by antoine_dh,
*/

#pragma once

#include <string>
#include "IPacket.hpp"

class AcceptFriendPacket : public IPacket {
    public:
        static constexpr int PacketId = 5;
        AcceptFriendPacket(bool accepted, const std::string &username);
        bool isAccepted() const;
        const std::string &getUsername() const;
        int getId() const override;

    private:
        bool accepted;
        std::string username;
};
