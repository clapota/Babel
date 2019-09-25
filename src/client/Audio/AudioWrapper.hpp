//
// Created by abel on 19/09/2019.
//

#ifndef BABEL_AUDIOWRAPPER_HPP
#define BABEL_AUDIOWRAPPER_HPP


#include <fstream>
#include <portaudio.h>
#include <vector>
#include "AudioInfo.hpp"
#include "AudioCompressor.hpp"

class AudioWrapper {
    public:
        AudioWrapper();
        ~AudioWrapper();
        void Start();
        void Stop();
        void writeOutput(std::vector<float> data);
        AudioCompressor &getCompressor();
    private:
        PaStream *outStream = nullptr;
        PaStream *stream = nullptr;
        AudioCompressor compressor;
};


#endif //BABEL_AUDIOWRAPPER_H
