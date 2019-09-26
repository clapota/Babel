//
// Created by abel on 19/09/2019.
//

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include "AudioWrapper.hpp"
#include "AudioCompressor.hpp"

int outputCallback(const void *inputBuffer, void *outputBuffer,
             unsigned long framesPerBuffer,
             const PaStreamCallbackTimeInfo* timeInfo,
             PaStreamCallbackFlags statusFlags,
             void *userData) {
    auto *wrapper = reinterpret_cast<AudioWrapper *>(userData);
    float *output = static_cast<float *>(outputBuffer);

    (void)inputBuffer;
    (void)timeInfo;
    (void)statusFlags;
    auto &queue = wrapper->getQueue();
    auto &float_vector = queue.front();

    if (!queue.empty()) {
        for (auto it: float_vector) {
            if (it != 0)
                std::cout << "normalement marche bien" << std::endl;
            *output++ = it;
        }
        queue.pop();
    }
    return (0);
}


int callback(const void *inputBuffer, void *outputBuffer,
                           unsigned long framesPerBuffer,
                           const PaStreamCallbackTimeInfo* timeInfo,
                           PaStreamCallbackFlags statusFlags,
                           void *userData) {
    (void)outputBuffer;
    (void)timeInfo;
    (void)statusFlags;
    auto *wrapper = reinterpret_cast<AudioWrapper *>(userData);
    auto *in = (float *)inputBuffer;
    std::vector<float> outData;

    for (unsigned long i = 0; i < framesPerBuffer; i++) {
        outData.push_back(*in++);
        outData.push_back(*in++);
    }

    AudioPacket packet = wrapper->getCompressor().compress((float *)inputBuffer);
    std::vector<unsigned char> serializedData = AudioPacket::serialize(packet);
    //TODO: Envoyer sur le réseau

    wrapper->sendData(serializedData);

//    packet = AudioPacket::unserialize(serializedData);
//    std::vector<float> outData2 = wrapper->getCompressor().uncompress(packet);

//    wrapper->addInQueue(outData2);
    return 0;
}

AudioWrapper::AudioWrapper() {
    this->udpClient = std::unique_ptr<UdpClient>(new UdpClient(*this, "10.26.111.192", 7777));
    PaError err = Pa_Initialize();
    PaStream *stream;
    PaStream *outStream;
    PaStreamParameters inputParameters;
    PaStreamParameters outputParameters;

    if (err != paNoError) {
        std::cerr << "Error while loading portAudio library" << std::endl;
        //TODO: Throw un truc
    }
    inputParameters.device = Pa_GetDefaultInputDevice();
    if (inputParameters.device == paNoDevice) {
        std::cerr << "No default input device " << std::endl;
        //TODO: Throw un truc
    }
    inputParameters.channelCount = NUMBER_CHANNELS;
    inputParameters.sampleFormat = paFloat32;
    inputParameters.suggestedLatency = Pa_GetDeviceInfo(inputParameters.device)->defaultLowInputLatency;
    inputParameters.hostApiSpecificStreamInfo = nullptr;

    outputParameters.device = Pa_GetDefaultOutputDevice();
    if (outputParameters.device == paNoDevice) {
        std::cerr << "No default output device" << std::endl;
        //TODO: Throw un truc
    }
    outputParameters.channelCount = NUMBER_CHANNELS;
    outputParameters.sampleFormat = paFloat32;
    outputParameters.suggestedLatency = Pa_GetDeviceInfo(outputParameters.device)->defaultLowOutputLatency;
    outputParameters.hostApiSpecificStreamInfo = nullptr;

    err = Pa_OpenStream(&stream,
            &inputParameters,
            nullptr,
            SAMPLE_RATE,
            FRAMES_PER_BUFFER,
            paDitherOff,
            callback,
            this);
    err = Pa_OpenStream(&outStream,
            nullptr,
            &outputParameters,
            SAMPLE_RATE,
            FRAMES_PER_BUFFER,
            paDitherOff,
            outputCallback,
            this);
    this->stream = stream;
    this->outStream = outStream;
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
            std::cerr << "Error while starting stream" << std::endl;
            //TODO: Throw un truc
        }
        err = Pa_StartStream(this->outStream);
        if (err != paNoError) {
            std::cerr << "Error while starting stream" << std::endl;
            //TODO: Throw un truc
        }
    }
    std::vector<float> zeroBuffer;
    for (int i = 0; i < FRAMES_PER_BUFFER * NUMBER_CHANNELS; i++) {
        zeroBuffer.push_back(0);
    }
    Pa_WriteStream(this->outStream, zeroBuffer.data(), FRAMES_PER_BUFFER);
}

/***
 * Stop audioStream
 */
void AudioWrapper::Stop() {
    PaError err;

    if (Pa_IsStreamStopped(this->stream) != 1) {
        err = Pa_AbortStream(this->stream);
        if (err != paNoError) {
            std::cerr << "Error while stopping stream" << std::endl;
            //TODO: Throw un truc
        }
        err = Pa_StopStream(this->stream);
        if (err != paNoError) {
            std::cerr << "Error while stopping stream" << std::endl;
            //TODO: Throw un truc
        }
    }
    if (Pa_IsStreamStopped(this->outStream) != 1) {
        err = Pa_AbortStream(this->outStream);
        if (err != paNoError) {
            std::cerr << "Error while stopping outStream" << std::endl;
            //TODO: Throw un truc
        }
        err = Pa_StopStream(this->outStream);
        if (err != paNoError) {
            std::cerr << "Error while stopping stream" << std::endl;
            //TODO: Throw un truc
        }
    }
}

AudioCompressor &AudioWrapper::getCompressor() {
    return this->compressor;
}

void AudioWrapper::addInQueue(std::vector<float> audioData) {
    this->audioQueue.push(audioData);
}

std::queue<std::vector<float>> & AudioWrapper::getQueue() {
    return this->audioQueue;
}

void AudioWrapper::sendData(std::vector<unsigned char> &data) {
    this->udpClient->sendData(data);
}
