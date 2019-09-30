/*
** EPITECH PROJECT, 2019
** Babel
** File description:
** Created by antoine_dh,
*/

#pragma once

#include <string>
#include "IPacket.hpp"

class CallPacket : public IPacket {
    public:
        static constexpr int PacketId = 6;
        const std::string &getUsername() const;
        explicit CallPacket(const std::string &username);
        int getId() const override;

    private:
        std::string username;
};
