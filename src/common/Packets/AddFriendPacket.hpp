/*
** EPITECH PROJECT, 2019
** Babel
** File description:
** Created by antoine_dh,
*/

#pragma once

#include <string>
#include "IPacket.hpp"

class AddFriendPacket : public IPacket {
    public:
        static constexpr int PacketId = 3;

        const int getId() const override
        {
            return PacketId;
        }

        AddFriendPacket() = default;

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
            AddFriendPacket::_username = username;
        }

    private:
        std::string _username;

};
