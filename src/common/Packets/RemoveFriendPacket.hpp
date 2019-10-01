/*
** EPITECH PROJECT, 2019
** Babel
** File description:
** Created by antoine_dh,
*/

#pragma once

#include <string>
#include "IPacket.hpp"

class RemoveFriendPacket : public IPacket {
    public:
        static constexpr int PacketId = 4;
        explicit RemoveFriendPacket(const std::string &username);
        const std::string &getUsername() const;
        int getId() const override;

    private:
        std::string username;
};
