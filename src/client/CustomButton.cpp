//
// Created by abel on 26/09/2019.
//

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
