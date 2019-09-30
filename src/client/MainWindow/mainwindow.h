#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QInputDialog>
#include "../Network/TcpClient.hpp"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow() override;

public slots:
    void connectToServer();
    void addFriend();
    void deleteFriend();
    void call();

private:
    Ui::MainWindow *ui;
    TcpClient client;
};

#endif // MAINWINDOW_H
