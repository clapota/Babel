#ifndef BABEL_IBINARYWRITER_HPP
#define BABEL_IBINARYWRITER_HPP

#include <string>

class IBinaryWriter
{
    public:
        virtual ~IBinaryWriter() = default;
        virtual void writeInt(uint32_t) = 0;
        virtual void writeString(const std::string &) = 0;
    private:

};

#endif //BABEL_IBINARYWRITER_HPP
