/*
** EPITECH PROJECT, 2019
** Babel
** File description:
** Created by antoine_dh,
*/

#pragma once

#include "IPacket.hpp"

class ReceivedFriendRequestPacket : public IPacket {
    public:
        static constexpr int PacketId = 9;

        ReceivedFriendRequestPacket() = default;

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
            ReceivedFriendRequestPacket::_username = username;
        }

    private:
        std::string _username;

};
