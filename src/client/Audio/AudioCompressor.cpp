//
// Created by abel on 23/09/2019.
//

#include <iostream>
#include "AudioCompressor.hpp"

AudioPacket AudioCompressor::compress(float *data) {
    float *in = data;
    std::vector<unsigned char> cbits(FRAMES_PER_BUFFER * sizeof(float) * NUMBER_CHANNELS);
    AudioPacket packet;
    int nbBytes;

    nbBytes = opus_encode_float(encoder, in, FRAMES_PER_BUFFER, cbits.data(), cbits.size());
    std::cout << cbits.size() << std::endl;
    if (nbBytes < 0) {
        std::cerr << "Failed to encode" << std::endl;
        //TODO: Throw un truc
    }
    packet.data = cbits;
    packet.nbBytes = nbBytes;
    std::cout << "NB BYTES A LENCODE : " << nbBytes << std::endl;
    return packet;
}

std::vector<float> AudioCompressor::uncompress(const AudioPacket& packet) {
    std::vector<float> cbits(FRAMES_PER_BUFFER * NUMBER_CHANNELS);
    int frame_size;

    frame_size = opus_decode_float(this->decoder, packet.data.data(), packet.nbBytes, cbits.data(), FRAMES_PER_BUFFER, 0);
    if (frame_size < 0) {
        std::cerr << "Failed to decode" << std::string(opus_strerror(frame_size)) << std::endl;
        //TODO: Throw un truc
    }
    return cbits;
}

AudioCompressor::AudioCompressor() {
    int err;
    OpusDecoder *decoder = opus_decoder_create(SAMPLE_RATE, NUMBER_CHANNELS, &err);
    OpusEncoder *encoder;
    if (err < 0) {
        std::cerr << "Failed to create decoder" << std::endl;
        //TODO: Throw un truc
    }
    this->decoder = decoder;

    encoder = opus_encoder_create(SAMPLE_RATE, NUMBER_CHANNELS, APPLICATION, &err);
    if (err < 0) {
        std::cerr << "Failed to create encoder" << std::endl;
        //TODO: Throw un truc
    }
    err = opus_encoder_ctl(encoder, OPUS_SET_BITRATE(BITRATE));
    if (err < 0) {
        std::cerr << "Failed to set bitrate" << std::endl;
        //TODO: Throw un truc
    }
    this->encoder = encoder;
}

AudioCompressor::~AudioCompressor() {
    opus_decoder_destroy(decoder);
    opus_encoder_destroy(encoder);
}
