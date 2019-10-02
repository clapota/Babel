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

        const int getId() const override
        {
            return PacketId;
        }

        RegisterPacket() = default;

        void serialize(IBinaryWriter &writer) const override
        {
            auto userName = getUsername();
            auto userPassword = getPassword();

            writer.writeString(userName);
            writer.writeString(userPassword);
        }

        void deserialize(IBinaryReader &reader) override
        {
            setUsername(reader.readString());
            setPassword(reader.readString());
        }

        const std::string &getUsername() const
        {
            return _username;
        }

        void setUsername(const std::string &_username)
        {
            RegisterPacket::_username = _username;
        }

        const std::string &getPassword() const
        {
            return _password;
        }

        void setPassword(const std::string &_password)
        {
            RegisterPacket::_password = _password;
        }

    private:
        std::string _username;
        std::string _password;
};
