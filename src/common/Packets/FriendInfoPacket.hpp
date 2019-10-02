/*
** EPITECH PROJECT, 2019
** Babel
** File description:
** Created by antoine_dh,
*/

#pragma once

#include "IPacket.hpp"

class FriendInfoPacket : public IPacket {
    public:
        static constexpr int PacketId = 10;

        enum FriendState : int {
            DISCONNECTED = 0,
            CONNECTED = 1,
            CALLING = 2,
        };

        FriendInfoPacket() = default;

        FriendInfoPacket(const std::string &_username, FriendState _state)
            : _username(_username), _state(_state)
        {
        }

        const std::string &getUsername() const
        {
            return _username;
        }

        void setUsername(const std::string &_username)
        {
            FriendInfoPacket::_username = _username;
        }

        FriendState getState() const
        {
            return _state;
        }

        void setState(FriendState _state)
        {
            FriendInfoPacket::_state = _state;
        }

        const int getId() const override
        {
            return PacketId;
        }

        void serialize(IBinaryWriter &writer) const override
        {
            writer.writeString(_username);
            writer.writeInt(static_cast<uint32_t>(_state));
        }

        void deserialize(IBinaryReader &reader) override
        {
            setUsername(reader.readString());
            setState(static_cast<FriendState>(reader.readInt()));
        }

    private:
        std::string _username;
        FriendState _state = DISCONNECTED;
};
