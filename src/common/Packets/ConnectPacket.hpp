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

        const int getId() const override
        {
            return PacketId;
        }

        ConnectPacket() = default;

        void serialize(IBinaryWriter &writer) override
        {
            auto userMail = getEmail();
            auto userPassword = getPassword();

            writer.writeString(userMail);
            writer.writeString(userPassword);
        }

        void deserialize(IBinaryReader &reader) override
        {
            setEmail(reader.readString());
            setPassword(reader.readString());
        }

        const std::string &getEmail() const
        {
            return _email;
        }

        void setEmail(const std::string &_email)
        {
            ConnectPacket::_email = _email;
        }

        const std::string &getPassword() const
        {
            return _password;
        }

        void setPassword(const std::string &_password)
        {
            ConnectPacket::_password = _password;
        }

    private:
        std::string _email;
        std::string _password;
};
