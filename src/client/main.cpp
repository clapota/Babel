/*
** EPITECH PROJECT, 2019
** Babel
** File description:
** Created by antoine_dh,
*/

#include <stdio.h>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <iostream>
#include "Audio/AudioWrapper.hpp"
#include "CustomButton.hpp"

int main(int argc, char **argv)
{
	try {
		QApplication app(argc, argv);
		CustomButton button;

		button.show();
		return app.exec();
	} catch (const std::exception &exception) {
		std::cerr << exception.what() << std::endl;
		return (84);
	} catch (...) {
		std::cerr << "Something happened" << std::endl;
		return (84);
	}
}
