//
// Created by abel on 19/09/2019.
//

#ifndef BABEL_AUDIOWRAPPER_HPP
#define BABEL_AUDIOWRAPPER_HPP


#include <fstream>
#include <portaudio.h>
#include <vector>
#include <queue>
#include "AudioInfo.hpp"
#include "AudioCompressor.hpp"

class AudioWrapper {
    public:
        AudioWrapper();
        ~AudioWrapper();
        void Start();
        void Stop();
        AudioCompressor &getCompressor();
        void addInQueue(std::vector<float> &audioData);
        std::queue<std::vector<float>> &getQueue();
    private:
        PaStream *outStream = nullptr;
        PaStream *stream = nullptr;
        AudioCompressor compressor;
        std::queue<std::vector<float>> audioQueue;
};


#endif //BABEL_AUDIOWRAPPER_H
