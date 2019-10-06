
#ifdef __linux__
#include <netinet/in.h>
#else
#include <winsock2.h>
#endif

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

    std::cout << "Sending string size : " << len;

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

void NativeBinaryWriter::writeBool(bool value)
{
    _stream.write(reinterpret_cast<char *>(&value), sizeof(value));
}

void NativeBinaryWriter::writeRawString(const std::string &value) {
    _stream.write(value.c_str(), value.size());
}
