#include <netinet/in.h>
#include <vector>
#include <boost/thread/csbl/memory/shared_ptr.hpp>
#include <cstring>
#include "NativeBinaryWriter.hpp"

void NativeBinaryWriter::writeInt(uint32_t value)
{
    uint32_t right_network_order = htonl(value);

    _stream.write(reinterpret_cast<char *>(&right_network_order), sizeof(value));
}

void NativeBinaryWriter::writeString(const std::string &value)
{
    size_t len = value.size();

    _stream.write((char *)&len, sizeof(len));
    _stream.write((char *)&value[0], len);
}

std::stringstream &NativeBinaryWriter::Data()
{
    _stream.seekg(0);

 /*   auto *output = new std::stringstream();
    *output << _stream.rdbuf(); */

    return _stream;
}