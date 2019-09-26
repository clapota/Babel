/*
** EPITECH PROJECT, 2019
** Babel
** File description:
** Created by abel,
*/

#include "CustomButton.hpp"

CustomButton::CustomButton() {
    connect(this, SIGNAL(clicked()), this, SLOT(createWrapper()));
}

void CustomButton::createWrapper() {
    if (wrapper == nullptr) {
        wrapper = std::unique_ptr<AudioWrapper>(new AudioWrapper());
        QObject::connect(wrapper.get(), SIGNAL(hangUp()), this, SLOT(doHangUp()));
        wrapper->Start();
    }
}

void CustomButton::doHangUp() {
    this->wrapper = nullptr;
}
