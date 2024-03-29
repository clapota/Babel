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

        const int getId() const override
        {
            return PacketId;
        }

        CallPacket() = default;

        void serialize(IBinaryWriter &writer) const override
        {
            auto userName = getUsername();

            writer.writeString(userName);
        }

        void deserialize(IBinaryReader &reader) override
        {
            setUsername(reader.readString());
        }

        const std::string &getUsername() const
        {
            return _username;
        }

        void setUsername(const std::string &username)
        {
            CallPacket::_username = username;
        }

    private:
        std::string _username;
};
