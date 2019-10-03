/*
** EPITECH PROJECT, 2019
** Babel
** File description:
** Created by antoine_dh,
*/

#pragma once

#include "IPacket.hpp"

class ResponsePacket : public IPacket {
    public:
        static constexpr int PacketId = 12;

        ResponsePacket() = default;
        ResponsePacket(int requestId, bool ok)
            : requestId(requestId), ok(ok)
        {
        }

        int getRequestId() const
        {
            return requestId;
        }

        void setRequestId(int requestId)
        {
            ResponsePacket::requestId = requestId;
        }

        bool isOk() const
        {
            return ok;
        }

        void setOk(bool ok)
        {
            ResponsePacket::ok = ok;
        }

        const int getId() const override
        {
            return ResponsePacket::PacketId;
        }

        void serialize(IBinaryWriter &writer) const override
        {
            writer.writeInt(static_cast<uint32_t>(requestId));
            writer.writeBool(ok);
        }

        void deserialize(IBinaryReader &reader) override
        {
            requestId = reader.readInt();
            ok = reader.readBool();
        }

    private:
        int requestId {};
        bool ok {};
};