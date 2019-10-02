#ifndef BABEL_NATIVEBINARYWRITER_HPP
#define BABEL_NATIVEBINARYWRITER_HPP

#include <sstream>
#include <iostream>
#include "IBinaryWriter.hpp"

class NativeBinaryWriter : public IBinaryWriter
{
    public:
        std::stringstream &Data();
        void writeInt(uint32_t value) override;
        void writeString(const std::string &value) override;
        void writeBool(bool value) override;
    private:
        std::stringstream _stream;
};

#endif //BABEL_NATIVEBINARYWRITER_HPP
