/*
** EPITECH PROJECT, 2019
** Babel
** File description:
** Created by antoine_dh,
*/

#pragma once

#include <string>
#include "IPacket.hpp"

class RegisterPacket : public IPacket {
    public:
        static constexpr int PacketId = 1;

        RegisterPacket() = default;
        RegisterPacket(const std::string &email, const std::string &password);
        int getId() const override;
        const std::string &getUsername() const;
        const std::string &getPassword() const;

    private:
        std::string username;
        std::string password;
};
