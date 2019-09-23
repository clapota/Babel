//
// Created by abel on 19/09/2019.
//

#ifndef BABEL_AUDIOWRAPPER_H
#define BABEL_AUDIOWRAPPER_H

#define SAMPLE_RATE 44100

#include <portaudio.h>

class AudioWrapper {
    public:
        AudioWrapper();
        ~AudioWrapper();
        void Start();
        void Stop();
        void Sleep(int milliseconds);
        void *getInputBuffer();
        void getInfo();
    private:
        PaStream *stream = nullptr;
};


#endif //BABEL_AUDIOWRAPPER_H
