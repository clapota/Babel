/*
** EPITECH PROJECT, 2019
** Babel
** File description:
** Created by antoine_dh,
*/

#pragma once

#include "IPacket.hpp"

class FriendRemovedPacket : public IPacket {
    public:
        static constexpr int PacketId = 11;

        FriendRemovedPacket() = default;

        const int getId() const override
        {
            return PacketId;
        }

        void serialize(IBinaryWriter &writer) const override
        {
            writer.writeString(getUsername());
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
            FriendRemovedPacket::_username = username;
        }

    private:
        std::string _username;
};
