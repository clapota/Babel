/*
** EPITECH PROJECT, 2019
** Babel
** File description:
** Created by abel,
*/

#ifndef BABEL_AUDIOENCODER_HPP
#define BABEL_AUDIOENCODER_HPP

#include <vector>
#include <opus.h>
#include "AudioInfo.hpp"

struct AudioPacket {
    std::vector<unsigned char> data;
    int nbBytes;
    static std::vector<unsigned char> serialize(const AudioPacket &packet);
    static AudioPacket unserialize(std::vector<unsigned char> &data);
};

class AudioCompressor {
    public:
        AudioCompressor();
        ~AudioCompressor();
        AudioPacket compress(float *data);
        std::vector<float> uncompress(const AudioPacket& packet);
    private:
        OpusDecoder *decoder;
        OpusEncoder *encoder;
};

#endif //BABEL_AUDIOENCODER_H
