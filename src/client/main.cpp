/*
** EPITECH PROJECT, 2019
** Babel
** File description:
** Created by antoine_dh,
*/

#include <stdio.h>
#include <opus/opus.h>
#include <portaudio.h>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include "Audio/AudioWrapper.hpp"
#include "CustomButton.hpp"

int main(int argc, char **argv)
{
	QApplication app (argc, argv);
	CustomButton button;

	button.show();
	return app.exec();
}
