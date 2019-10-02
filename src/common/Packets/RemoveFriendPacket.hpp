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

        const int getId() const override
        {
            return PacketId;
        }

        RemoveFriendPacket() = default;

        void serialize(IBinaryWriter &writer) override
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

        void setUsername(const std::string &_username)
        {
            RemoveFriendPacket::_username = _username;
        }

    private:
        std::string _username;
};
