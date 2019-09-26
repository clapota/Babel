//
// Created by abel on 26/09/2019.
//

#include "AudioException.hpp"

const char *AudioException::what() const noexcept {
    return this->message;
}

AudioException::AudioException(const char *message) : message(message) {

}
