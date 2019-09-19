//
// Created by abel on 19/09/2019.
//

#include <iostream>
#include "AudioWrapper.hpp"
#include <stdlib.h>

int callback(const void *inputBuffer, void *outputBuffer,
                           unsigned long framesPerBuffer,
                           const PaStreamCallbackTimeInfo* timeInfo,
                           PaStreamCallbackFlags statusFlags,
                           void *userData) {
    float *out = (float *)outputBuffer;
    float *in = (float *)inputBuffer;
    *out++ = *in++;
    *out++ = *in++;

    return 0;
}

AudioWrapper::AudioWrapper() {
    PaError err;
    PaStream *stream;

    err = Pa_Initialize();
    if (err != paNoError) {
        std::cerr << "Error while loading portAudio library" << std::endl;
        //TODO: Throw un truc
    }
    if (err != paNoError) {
        std::cerr << "Error while opening I/O stream" << std::endl;
        //TODO: Throw un truc
    }
    err = Pa_OpenDefaultStream(&stream,
            2,
            2,
            paFloat32,
            SAMPLE_RATE,
            256,
            callback,
            (void *)0);
    this->stream = stream;
    std::cout << "bite" << std::endl;
}

AudioWrapper::~AudioWrapper() {
    PaError err;

    this->Stop();
    err = Pa_Terminate();
    if (err != paNoError) {
        std::cerr << "Error while quiting portAudio" << std::endl;
        //TODO: Throw un truc
    }
}

/***
 * Start AudioStream
 */

/**
 * Pourquoi pas foutre un stream network dans cette fonction pour l'utiliser dans le callback ?
 */
void AudioWrapper::Start() {
    PaError err;

    if (Pa_IsStreamStopped(this->stream) != 0) {
        err = Pa_StartStream(this->stream);
        if (err != paNoError) {
            std::cerr << "Error while starting stream";
            //TODO: Throw un truc
        }
    }
}

/***
 * Stop audioStream
 */
void AudioWrapper::Stop() {
    PaError err;

    if (Pa_IsStreamStopped(this->stream) != 1) {
        err = Pa_StopStream(this->stream);
        if (err != paNoError) {
            std::cerr << "Error while stopping stream" << std::endl;
            //TODO: Throw un truc
        }
    }
}

/***
 * @param milliseconds
 */
void AudioWrapper::Sleep(int milliseconds) {
    Pa_Sleep(milliseconds);
}

void AudioWrapper::getInfo() {
    int numDevices = Pa_GetDeviceCount();
    const PaDeviceInfo *info;

    for (int i = 0; i < numDevices; i++) {
        info = Pa_GetDeviceInfo(i);
        printf("%s\n", info->name);
    }
}