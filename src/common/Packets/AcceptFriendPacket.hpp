/*
** EPITECH PROJECT, 2019
** Babel
** File description:
** Created by antoine_dh,
*/

#pragma once

#include <string>
#include "IPacket.hpp"

class AcceptFriendPacket : public IPacket {
    public:
        static constexpr int PacketId = 5;

        AcceptFriendPacket() = default;

        const int getId() const override
        {
            return PacketId;
        }

        void serialize(IBinaryWriter &writer) override
        {
            auto userName = getUsername();
            auto accepted = isAccepted() ? 1 : 0;

            writer.writeString(userName);
            writer.writeInt(accepted);
        }

        void deserialize(IBinaryReader &reader) override
        {
            setUsername(reader.readString());
            setAccepted((bool)reader.readInt());
        }

        bool isAccepted() const
        {
            return _accepted;
        }

        void setAccepted(bool accepted)
        {
            AcceptFriendPacket::_accepted = accepted;
        }

        const std::string &getUsername() const
        {
            return _username;
        }

        void setUsername(const std::string &username)
        {
            AcceptFriendPacket::_username = username;
        }

    private:
        bool _accepted;
        std::string _username;
};
