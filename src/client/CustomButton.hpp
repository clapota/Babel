//
// Created by abel on 26/09/2019.
//

#ifndef BABEL_CUSTOMBUTTON_HPP
#define BABEL_CUSTOMBUTTON_HPP

#include <QPushButton>
#include <memory>
#include "Audio/AudioWrapper.hpp"

class CustomButton : public QPushButton {
    Q_OBJECT

    public:
        CustomButton();
        ~CustomButton() = default;
    public slots:
        void createWrapper();
        void doHangUp();
    private:
        std::unique_ptr<AudioWrapper> wrapper = nullptr;

};


#endif //BABEL_CUSTOMBUTTON_HPP
