#ifndef BABEL_NATIVEBINARYREADER_HPP
#define BABEL_NATIVEBINARYREADER_HPP

#include <sstream>
#include "IBinaryReader.hpp"

class NativeBinaryReader : public IBinaryReader
{
    public:
        void setStream(std::stringstream *stream);
        int readInt() override;
        std::string readString() override;
    private:
        std::stringstream *_stream;
};

#endif //BABEL_NATIVEBINARYREADER_HPP
