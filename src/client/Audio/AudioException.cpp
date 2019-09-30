/*
** EPITECH PROJECT, 2019
** Babel
** File description:
** Created by abel,
*/

#include "AudioException.hpp"

const char *AudioException::what() const noexcept {
    return this->message;
}

AudioException::AudioException(const char *message) : message(message) {

}
