#ifndef BABEL_IBINARYREADER_HPP
#define BABEL_IBINARYREADER_HPP

#include <string>

class IBinaryReader
{
    public:
        ~IBinaryReader() = default;
        virtual int readInt() = 0;
        virtual std::string readString() = 0;
        virtual bool readBool() = 0;
};

#endif //BABEL_IBINARYREADER_HPP
