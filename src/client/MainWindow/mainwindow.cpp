#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../../common/PacketFactory.hpp"
#include "../../common/IO/NativeBinaryWriter.hpp"
#include <QPushButton>
#include <iostream>
#include <QtCore/QDir>
#include <memory>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    client("127.0.0.1", 4444)
{
    ui->setupUi(this);
    auto *connectionButton = this->ui->LogInInLogIn;
    auto *addFriend = this->ui->actionAdd_new_friend;
    auto *removeFriend =this->ui->actionDelete_frind;
    auto *callButton = this->ui->pushButton;
    auto *LogInInSignIn = this->ui->LogInInSignIn;
    auto *SignInInSignIn = this->ui->SignIninSignIn;
    auto *SignInInLogIn = this->ui->SignInInLogIn;
    auto *Disconnect = this->ui->DisconnectButton;

    ui->lineEdit_2->setEchoMode(QLineEdit::Password);
    ui->lineEdit_4->setEchoMode(QLineEdit::Password);
    ui->lineEdit_5->setEchoMode(QLineEdit::Password);
    connect(addFriend, SIGNAL(triggered()), this, SLOT(addFriend()));
    connect(connectionButton, SIGNAL(clicked()), this, SLOT(connectToServer()));
    connect(callButton, SIGNAL(clicked()), this, SLOT(call()));
    connect(removeFriend, SIGNAL(triggered()), this, SLOT(deleteFriend()));
    connect(SignInInLogIn, SIGNAL(clicked()), this, SLOT(SignInInLogIn()));
    connect(SignInInSignIn, SIGNAL(clicked()), this, SLOT(SignInInSignIn()));
    connect(LogInInSignIn, SIGNAL(clicked()), this, SLOT(LogInInSignIn()));
    connect(Disconnect, SIGNAL(clicked()), this, SLOT(Disconnect()));
    connect(&client, SIGNAL(registerResponse(IPacket &)), this, SLOT(registerResponse(IPacket &)));
    connect(&client, SIGNAL(connectResponse(IPacket &)), this, SLOT(connectResponse(IPacket &)));
    connect(&client, SIGNAL(addFriendResponse(IPacket &)), this, SLOT(addFriendResponse(IPacket &)));
    connect(&client, SIGNAL(removeFriendResponse(IPacket &)), this, SLOT(removeFriendResponse(IPacket &)));
    connect(&client, SIGNAL(acceptFriendResponse(IPacket &)), this, SLOT(acceptFriendResponse(IPacket &)));
    connect(&client, SIGNAL(callResponse(IPacket &)), this, SLOT(callResponse(IPacket &)));
    connect(&client, SIGNAL(hangUpResponse(IPacket &)), this, SLOT(hangUpResponse(IPacket &)));
    connect(&client, SIGNAL(friendAccept(IPacket &)), this, SLOT(friendAccept(IPacket &)));
    connect(&client, SIGNAL(requestFriend(IPacket &)), this, SLOT(requestFriend(IPacket &)));
    connect(&client, SIGNAL(userInfo(IPacket &)), this, SLOT(userInfo(IPacket &)));
    connect(&client, SIGNAL(removedFromFriend(IPacket &)), this, SLOT(removedFromFriend(IPacket &)));
    ui->widget->setVisible(false);
    ui->Sign->setVisible(false);
    ui->listWidget->clear();
    ui->PendingFriends->clear();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Disconnect()
{
    ui->lineEdit_2->clear();
    ui->lineEdit->clear();
    this->changeVisibleWidget(CONNEXION);
}

void MainWindow::LogInInSignIn()
{
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    this->changeVisibleWidget(CONNEXION);
}

void MainWindow::SignInInLogIn()
{
    ui->lineEdit_2->clear();
    ui->lineEdit->clear();
    this->changeVisibleWidget(SIGN);
}

void MainWindow::SignInInSignIn()
{
    QString text = ui->lineEdit_3->text();
    std::string username = text.toStdString();
    text = ui->lineEdit_4->text();
    std::string password = text.toStdString();
    text = ui->lineEdit_5->text();
    std::string RepeatedPassword = text.toStdString();

    if (password != RepeatedPassword)
    {
        ui->lineEdit_4->setStyleSheet("border: 1px solid red;");
        ui->lineEdit_5->setStyleSheet("border: 1px solid red;");
    } else {
        RegisterPacket packet;

        packet.setPassword(password);
        packet.setUsername(username);
        ui->lineEdit_3->clear();
        ui->lineEdit_4->clear();
        ui->lineEdit_5->clear();
        this->client.sendData(packet);
    }
}

void MainWindow::connectToServer() {
    auto *usernameLineEdit = ui->lineEdit;
    auto *passwordLineEdit = ui->lineEdit_2;

    QString text = usernameLineEdit->text();
    std::string username = text.toStdString();
    text = passwordLineEdit->text();
    std::string password = text.toStdString();

    std::cout << "password " << password << " username " << username << std::endl;

    if (!username.empty() && !password.empty()) {
        ConnectPacket packet;

        packet.setEmail(username);
        packet.setPassword(password);
        this->client.sendData(packet);
    } else {
        if (username.empty())
            usernameLineEdit->setStyleSheet("border: 1px solid red;");
        else
            usernameLineEdit->setStyleSheet("border: 1px solid black;");
        if (password.empty())
            passwordLineEdit->setStyleSheet("border: 1px solid red;");
        else
            passwordLineEdit->setStyleSheet("border: 1px solid black;");
    }
}

void MainWindow::addFriend() {
    bool ok;
    bool alreadyExist = false;
    QString text = QInputDialog::getText(this, tr("Add friend"), tr("Username :"), QLineEdit::Normal, QDir::home().dirName(), &ok);

    if (ok && !text.isEmpty())
    {
        auto *list = this->ui->listWidget;
        for (int i = 0; i < list->count(); i++) {
            auto *item = list->item(i);
            if (item->text() == text)
                alreadyExist = true;
        }
        if (!alreadyExist) {
            AddFriendPacket packet;

            packet.setUsername(text.toStdString());
            this->client.sendData(packet);
        }
    }
}

void MainWindow::deleteFriend() {
    bool ok;

    QStringList items;

    auto *list = this->ui->listWidget;

    for (int i = 0; i < list->count(); i++) {
        auto *item = list->item(i);
        items << item->text();
    }

    QString item = QInputDialog::getItem(this, tr("Remove friend"), tr("Username :"), items, 0, false, &ok);

    if (ok && !item.isEmpty())
    {
        RemoveFriendPacket packet;

        packet.setUsername(item.toStdString());

        this->client.sendData(packet);

        for (int i = 0; i < list->count(); i++) {
            auto *it = list->item(i);
            if (it->text() == item) {
                delete it;
            }
        }
    }
}

void MainWindow::call() {
    auto *list = this->ui->listWidget;

    auto *selected = list->currentItem();
    if (selected == nullptr) {
        auto *callButton = this->ui->pushButton;

        callButton->setStyleSheet("border-color: red");
    } else {
        CallPacket packet;

        packet.setUsername(selected->text().toStdString());
        this->client.sendData(packet);

        std::cout << selected->text().toStdString() << std::endl;
    }

}

void MainWindow::changeVisibleWidget(Widget wid)
{
    if (wid == MAIN) {
        ui->widget->setVisible(true);
        ui->widget_2->setVisible(false);
        ui->Sign->setVisible(false);
    } else if (wid == CONNEXION) {
        ui->widget->setVisible(false);
        ui->widget_2->setVisible(true);
        ui->Sign->setVisible(false);
    } else if (wid == SIGN) {
        ui->widget->setVisible(false);
        ui->widget_2->setVisible(false);
        ui->Sign->setVisible(true);
    }
}

void MainWindow::registerResponse(IPacket &packet) {
    auto &responsePacket = dynamic_cast<ResponsePacket &>(packet);

    if (responsePacket.isOk())
        std::cout << "Account created with success" << std::endl;
    else
        std::cerr << "Error while creating account, please retry" << std::endl;
}

void MainWindow::connectResponse(IPacket &packet) {
    auto &responsePacket = dynamic_cast<ResponsePacket &>(packet);

    std::cout << "BITE" << std::endl;
    if (responsePacket.isOk()) {
        this->changeVisibleWidget(MAIN);
        this->isConnected = true;
    } else {
        std::cerr << "Error while log in" << std::endl;
    }
}

void MainWindow::addFriendResponse(IPacket &packet) {
    auto &responsePacket = dynamic_cast<ResponsePacket &>(packet);

    if (responsePacket.isOk()) {
        std::cout << "Friend added with success, waiting for his response" << std::endl;
    } else {
        std::cerr << "error while adding friend" << std::endl;
    }
}

void MainWindow::removeFriendResponse(IPacket &packet) {
    auto &responsePacket = dynamic_cast<ResponsePacket &>(packet);

    if (responsePacket.isOk()) {
        std::cout << "Friend remove with success" << std::endl;
    } else {
        std::cerr << "Bug" << std::endl;
    }
}

void MainWindow::acceptFriendResponse(IPacket &packet) {
    auto &responsePacket = dynamic_cast<ResponsePacket &>(packet);

    if (responsePacket.isOk()) {
        std::cout << "Friend accepted with success" << std::endl;
    } else {
        std::cerr << "Bug" << std::endl;
    }
}

void MainWindow::callResponse(IPacket &packet) {
    auto &responsePacket = dynamic_cast<ResponsePacket &>(packet);

    if (responsePacket.isOk()) {
        std::cout << "Call ready to be setup" << std::endl;
    } else {
        std::cerr << "Bug" << std::endl;
    }

}

void MainWindow::hangUpResponse(IPacket &packet) {
    auto &responsePacket = dynamic_cast<ResponsePacket &>(packet);

    if (responsePacket.isOk()) {
        std::cout << "Hanging Up" << std::endl;
        this->audioManager = nullptr;
    } else {
        std::cerr << "Bug" << std::endl;
    }
}

void MainWindow::friendAccept(IPacket &packet) {
    auto &friendAcceptPacket = dynamic_cast<FriendAcceptedPacket &>(packet);

    auto *list = this->ui->listWidget;
    list->addItem(QString(friendAcceptPacket.getUsername().c_str()));
}

void MainWindow::requestFriend(IPacket &packet) {
    auto &requestFriend = dynamic_cast<ReceivedFriendRequestPacket &>(packet);

    auto *list = this->ui->PendingFriends;
    list->addItem(QString(requestFriend.getUsername().c_str()));
}

void MainWindow::userInfo(IPacket &packet) {
    auto &friendInfo = dynamic_cast<FriendInfoPacket &>(packet);

    bool inList = false;
    auto *list = this->ui->listWidget;
    for (int i = 0; i < list->count(); i++) {
        auto *it = list->item(i);

        if (it->text().toStdString() == friendInfo.getUsername())
            inList = true;
    }
    if (!inList)
        list->addItem(QString(friendInfo.getUsername().c_str()));
}

void MainWindow::removedFromFriend(IPacket &packet) {
    auto &rffPacket = dynamic_cast<FriendRemovedPacket &>(packet);

    auto *list = this->ui->listWidget;
    for (int i = 0; i < list->count(); i++) {
        auto *it = list->item(i);
        if (it->text().toStdString() == rffPacket.getUsername())
            delete it;
    }
}

void MainWindow::called(IPacket &packet) {
    auto &cPacket = dynamic_cast<CallingPacket &>(packet);

    const std::string& ip = cPacket.getIp();
    this->audioManager = std::unique_ptr<AudioWrapper>(new AudioWrapper(ip));
    QObject::connect(audioManager.get(), SIGNAL(hangUp()), this, SLOT(hangUp()));
}

void MainWindow::hangUp() {
    this->audioManager = nullptr;

    HangUpPacket packet;

    this->client.sendData(packet);
}