#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QInputDialog>
#include "../Network/TcpClient.hpp"
#include "../Audio/AudioWrapper.hpp"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
        enum Widget {
        CONNEXION = 0,
        MAIN = 1,
        SIGN = 2
    };
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow() override;
    void changeVisibleWidget(Widget);

    public slots:
    void connectToServer();
    void addFriend();
    void deleteFriend();
    void call();
    void SignInInLogIn();
    void LogInInSignIn();
    void SignInInSignIn();
    void Disconnect();
    void registerResponse(IPacket &packet);
    void connectResponse(IPacket &packet);
    void addFriendResponse(IPacket &packet);
    void removeFriendResponse(IPacket &packet);
    void acceptFriendResponse(IPacket &packet);
    void callResponse(IPacket &packet);
    void hangUpResponse(IPacket &packet);
    void friendAccept(IPacket &packet);
    void requestFriend(IPacket &packet);
    void userInfo(IPacket &packet);
    void removedFromFriend(IPacket &packet);
    void called(IPacket &packet);
    void hangUp();

private:
    Ui::MainWindow *ui;
    TcpClient client;
    std::unique_ptr<AudioWrapper> audioManager = nullptr;
    bool isConnected = false;
};

#endif // MAINWINDOW_H
