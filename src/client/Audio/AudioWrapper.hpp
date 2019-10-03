/*
** EPITECH PROJECT, 2019
** Babel
** File description:
** Created by abel,
*/

#ifndef BABEL_AUDIOWRAPPER_HPP
#define BABEL_AUDIOWRAPPER_HPP

#include <fstream>
#include <portaudio.h>
#include <vector>
#include <queue>
#include <memory>
#include <QObject>
#include "AudioInfo.hpp"
#include "AudioCompressor.hpp"
#include "Network/UdpClient.hpp"

class AudioWrapper : public QObject {
    Q_OBJECT

    public:
        explicit AudioWrapper(const std::string &ip);
        ~AudioWrapper() override;
        void Start();
        void Stop();
        AudioCompressor &getCompressor();
        void addInQueue(std::vector<float> audioData);
        std::queue<std::vector<float>> &getQueue();
        void close();
        void addToSendList(std::vector<unsigned char> &data);
    public slots:
        void sendData();
    signals:
        void hangUp();
    private:
        PaStream *outStream = nullptr;
        PaStream *stream = nullptr;
        QTimer *timer = nullptr;
        AudioCompressor compressor;
        std::queue<std::vector<float>> audioQueue;
        std::queue<std::vector<unsigned char>> sendList;
        std::unique_ptr<UdpClient> udpClient = nullptr;
};


#endif //BABEL_AUDIOWRAPPER_H
