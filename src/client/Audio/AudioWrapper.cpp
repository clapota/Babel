/*
** EPITECH PROJECT, 2019
** Babel
** File description:
** Created by abel,
*/

#include <iostream>
#include "AudioWrapper.hpp"
#include "AudioCompressor.hpp"
#include "AudioException.hpp"

int outputCallback(const void *inputBuffer, void *outputBuffer,
             unsigned long framesPerBuffer,
             const PaStreamCallbackTimeInfo* timeInfo,
             PaStreamCallbackFlags statusFlags,
             void *userData) {
    auto *wrapper = reinterpret_cast<AudioWrapper *>(userData);
    auto *output = static_cast<float *>(outputBuffer);
    auto &queue = wrapper->getQueue();

    if (!queue.empty()) {
        auto &float_vector = queue.front();

        int i = 0;
        for (auto it: float_vector) {
            *output++ = it;
        }
        queue.pop();
    } else {
        for (int i = 0; i < framesPerBuffer * NUMBER_CHANNELS; ++i)
            *output++ = 0;
    }
    return (0);
}

int callback(const void *inputBuffer, void *,
                           unsigned long framesPerBuffer,
                           const PaStreamCallbackTimeInfo *,
                           PaStreamCallbackFlags,
                           void *userData) {
    auto *wrapper = reinterpret_cast<AudioWrapper *>(userData);
    auto *in = (float *)inputBuffer;
    std::vector<float> outData;

    for (unsigned long i = 0; i < framesPerBuffer; i++) {
        outData.push_back(*in++);
        outData.push_back(*in++);
    }
    AudioPacket packet = wrapper->getCompressor().compress((float *)inputBuffer);
    std::vector<unsigned char> serializedData = AudioPacket::serialize(packet);
    wrapper->addToSendList(serializedData);
    return 0;
}

// TODO séparer le UdpClient du wrapper audio
AudioWrapper::AudioWrapper(const std::string &ip) {
    this->udpClient = std::unique_ptr<UdpClient>(new UdpClient(*this, ip, 7777));
    this->timer = new QTimer(this);
    this->timer->setInterval(10);
    QObject::connect(this->timer, SIGNAL(timeout()), this, SLOT(sendData()));
    std::cout << "initializing portaudio" << std::endl;
    PaError err = Pa_Initialize();
    PaStream *stream;
    PaStream *outStream;
    PaStreamParameters inputParameters;
    PaStreamParameters outputParameters;

    if (err != paNoError)
        throw AudioException("error while loading portAudio library");
    inputParameters.device = Pa_GetDefaultInputDevice();
    if (inputParameters.device == paNoDevice)
        throw AudioException("No default input device");
    inputParameters.channelCount = NUMBER_CHANNELS;
    inputParameters.sampleFormat = paFloat32;
    inputParameters.suggestedLatency = Pa_GetDeviceInfo(inputParameters.device)->defaultLowInputLatency;
    inputParameters.hostApiSpecificStreamInfo = nullptr;

    outputParameters.device = Pa_GetDefaultOutputDevice();
    if (outputParameters.device == paNoDevice)
        throw AudioException("No default output device");
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
    if (err != paNoError)
        throw AudioException("Can't open Input stream");
    err = Pa_OpenStream(&outStream,
            nullptr,
            &outputParameters,
            SAMPLE_RATE,
            FRAMES_PER_BUFFER,
            paDitherOff,
            outputCallback,
            this);
    if (err != paNoError)
        throw AudioException("Can't open Output stream");
    this->stream = stream;
    this->outStream = outStream;
    this->timer->start();
}

AudioWrapper::~AudioWrapper() {
    this->Stop();
    Pa_Terminate();
}

/***
 * Start AudioStream
 */
void AudioWrapper::Start() {
    PaError err;

    std::cout << "Starting portaudio" << std::endl;
    if (Pa_IsStreamStopped(this->stream) != 0) {
        err = Pa_StartStream(this->stream);
        if (err != paNoError)
            throw AudioException("Error while starting Input stream");
        err = Pa_StartStream(this->outStream);
        if (err != paNoError)
            throw AudioException("Error while starting Output stream");
    }
    std::vector<float> zeroBuffer;
    for (int i = 0; i < FRAMES_PER_BUFFER * NUMBER_CHANNELS; i++)
        zeroBuffer.push_back(0);
    Pa_WriteStream(this->outStream, zeroBuffer.data(), FRAMES_PER_BUFFER);
}

/***
 * Stop audioStream
 */
void AudioWrapper::Stop() {
    PaError err;

    if (Pa_IsStreamStopped(this->stream) != 1) {
        err = Pa_StopStream(this->stream);
        if (err != paNoError)
            throw AudioException("Error while stopping Input stream");
    }
    if (Pa_IsStreamStopped(this->outStream) != 1) {
        err = Pa_StopStream(this->outStream);
        if (err != paNoError)
            throw AudioException("Error while stopping Output stream");
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

void AudioWrapper::sendData() {
    while (!this->sendList.empty()) {
        this->udpClient->sendData(this->sendList.front());
        this->sendList.pop();
    }
}

void AudioWrapper::close() {
    emit hangUp();
}

void AudioWrapper::addToSendList(std::vector<unsigned char> &data) {
    this->sendList.push(data);
}
