/*
** EPITECH PROJECT, 2018
** {Project name}
** File description:
** {file name}
*/

#ifndef BABEL_MAINWINDOW_HPP
#define BABEL_MAINWINDOW_HPP

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
        Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow() override;

    private:
        Ui::MainWindow *ui;
};

#endif //BABEL_MAINWINDOW_HPP
