//
// Created by abel on 03/10/2019.
//

#ifndef BABEL_CALLINGPACKET_HPP
#define BABEL_CALLINGPACKET_HPP

#include "IPacket.hpp"

class CallingPacket : public IPacket {
public:
    static constexpr int PacketId = 13;

    const int getId() const override
    {
        return PacketId;
    }

    CallingPacket() = default;

    void serialize(IBinaryWriter &writer) const override
    {
        writer.writeString(ip);
    }

    void deserialize(IBinaryReader &reader) override
    {
        setIp(reader.readString());
    }

    const std::string &getIp() const
    {
        return ip;
    }

    void setIp(const std::string &ip)
    {
        CallingPacket::ip = ip;
    }

private:
    std::string ip;

};

#endif //BABEL_CALLINGPACKET_HPP
