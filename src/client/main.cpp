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
#include "MainWindow/Mainwindow.hpp"

int main(int argc, char **argv)
{
    AudioWrapper wrapper;
	QApplication app (argc, argv);
	QPushButton button ("Hello world !");

    MainWindow w;
    w.show();
    wrapper.Start();
	button.show();
	return app.exec();
}
