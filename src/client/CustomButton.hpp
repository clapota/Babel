/*
** EPITECH PROJECT, 2019
** Babel
** File description:
** Created by abel,
*/

#ifndef BABEL_CUSTOMBUTTON_HPP
#define BABEL_CUSTOMBUTTON_HPP

#include <QPushButton>
#include <memory>
#include "Audio/AudioWrapper.hpp"

class CustomButton : public QPushButton {
    Q_OBJECT

    public:
        CustomButton();
        ~CustomButton() override = default;
    public slots:
        void createWrapper();
        void doHangUp();
    private:
        std::unique_ptr<AudioWrapper> wrapper = nullptr;

};

#endif //BABEL_CUSTOMBUTTON_HPP
