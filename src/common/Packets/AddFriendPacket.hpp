/*
** EPITECH PROJECT, 2019
** Babel
** File description:
** Created by antoine_dh,
*/

#pragma once

#include <string>
#include "IPacket.hpp"

class AddFriendPacket : public IPacket {
    public:
        static constexpr int PacketId = 3;

        explicit AddFriendPacket(const std::string &username);
        const std::string &getUsername() const;
        int getId() const override;

    private:
        std::string username;
};
