#ifndef BABEL_APACKET_HPP
#define BABEL_APACKET_HPP

#include "IO/IBinaryWriter.hpp"
#include "IO/IBinaryReader.hpp"

class IPacket
{
    public:
        ~IPacket() = default;
        virtual const int getId() const = 0;
        virtual void serialize(IBinaryWriter &writer) const = 0;
        virtual void deserialize(IBinaryReader &reader) = 0;
};

#endif //BABEL_APACKET_HPP
