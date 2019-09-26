//
// Created by abel on 23/09/2019.
//

#include <iostream>
#include <cstring>
#include "AudioCompressor.hpp"
#include "AudioException.hpp"

AudioPacket AudioCompressor::compress(float *data) {
    float *in = data;
    std::vector<unsigned char> cbits(FRAMES_PER_BUFFER * sizeof(float) * NUMBER_CHANNELS);
    AudioPacket packet;
    int nbBytes;

    nbBytes = opus_encode_float(encoder, in, FRAMES_PER_BUFFER, cbits.data(), cbits.size());
    if (nbBytes < 0)
        throw AudioException("Failed to encode audio packet");
    packet.data = std::vector<unsigned char>(cbits.begin(), cbits.begin() + nbBytes);
    packet.nbBytes = nbBytes;
    return packet;
}

std::vector<float> AudioCompressor::uncompress(const AudioPacket& packet) {
    std::vector<float> cbits(FRAMES_PER_BUFFER * NUMBER_CHANNELS);
    int frame_size;

    frame_size = opus_decode_float(this->decoder, packet.data.data(), packet.nbBytes, cbits.data(), FRAMES_PER_BUFFER, 0);
    if (frame_size < 0)
        throw AudioException("Failed to decode audio packet");
    return cbits;
}

AudioCompressor::AudioCompressor() {
    int err;
    OpusDecoder *decoder = opus_decoder_create(SAMPLE_RATE, NUMBER_CHANNELS, &err);
    OpusEncoder *encoder;
    if (err < 0)
        throw AudioException("Failed to create decoder");
    this->decoder = decoder;

    encoder = opus_encoder_create(SAMPLE_RATE, NUMBER_CHANNELS, APPLICATION, &err);
    if (err < 0)
        throw AudioException("Failed to create encoder");
    err = opus_encoder_ctl(encoder, OPUS_SET_BITRATE(BITRATE));
    if (err < 0)
        throw AudioException("Failed to set bitrate");
    this->encoder = encoder;
}

AudioCompressor::~AudioCompressor() {
    opus_decoder_destroy(decoder);
    opus_encoder_destroy(encoder);
}

std::vector<unsigned char> AudioPacket::serialize(const AudioPacket &packet) {
    std::vector<unsigned char> byteArray(sizeof(packet.nbBytes) + packet.data.size());
    int i;

    byteArray.insert(byteArray.begin(), packet.nbBytes & 0xFF);
    byteArray.insert(byteArray.begin() + 1, packet.nbBytes >> 8 & 0xFF);
    byteArray.insert(byteArray.begin() + 2, packet.nbBytes >> 16 & 0xFF);
    byteArray.insert(byteArray.begin() + 3, packet.nbBytes >> 24 & 0xFF);
    std::memcpy(&i, byteArray.data(), 4);
    byteArray.insert(byteArray.begin() + 4, packet.data.begin(), packet.data.end());
    return byteArray;
}

AudioPacket AudioPacket::unserialize(std::vector<unsigned char> &data) {
    AudioPacket packet;

    std::memcpy(&(packet.nbBytes), data.data(), sizeof(packet.nbBytes));
    data.erase(data.begin(), data.begin() + 4);
    packet.data = data;
    return packet;
}