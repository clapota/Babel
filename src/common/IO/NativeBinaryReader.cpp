#include <netinet/in.h>
#include <iostream>
#include "NativeBinaryReader.hpp"

int NativeBinaryReader::readInt()
{
    uint32_t value = 0;
    _stream->read((char *)&value , sizeof(value));

    return ntohl(value);
}

std::string NativeBinaryReader::readString()
{
    size_t len = 0;
    std::string data;

    _stream->read((char*)&len, sizeof(len));
    data.resize(len);
    _stream->read(&data[0], len);

    return data;
}

void NativeBinaryReader::setStream(std::stringstream *stream)
{
    this->_stream = stream;
}

bool NativeBinaryReader::readBool()
{
    bool value = false;
    _stream->read((char *)&value , sizeof(bool));

    return value;
}
