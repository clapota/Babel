/*
** EPITECH PROJECT, 2019
** Babel
** File description:
** Created by antoine_dh,
*/

#include <QtWidgets/QApplication>
#include <iostream>
#include <QtWidgets/QListWidget>
#include "MainWindow/mainwindow.h"

int main(int argc, char **argv)
{
	try {
		QApplication app(argc, argv);
		MainWindow window;
		window.show();
		return QApplication::exec();
	} catch (const std::exception &exception) {
		std::cerr << exception.what() << std::endl;
		return (84);
	} catch (...) {
		std::cerr << "Something happened" << std::endl;
		return (84);
    }
}
