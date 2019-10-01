/*
** EPITECH PROJECT, 2019
** Babel
** File description:
** Created by antoine_dh,
*/

#pragma once

#include <string>
#include "IPacket.hpp"

class ConnectPacket : public IPacket {
    public:
        static constexpr int PacketId = 2;

        ConnectPacket() = default;
        ConnectPacket(const std::string &email, const std::string &password);
        int getId() const override;
        const std::string &getEmail() const;
        const std::string &getPassword() const;

    private:
        std::string email;
        std::string password;
};
