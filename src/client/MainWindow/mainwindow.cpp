#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../../common/PacketFactory.hpp"
#include "../../common/IO/NativeBinaryWriter.hpp"
#include <QPushButton>
#include <iostream>
#include <QtCore/QDir>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    client("10.26.111.73", 4444)
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
    ui->widget->setVisible(false);
    ui->Sign->setVisible(false);
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
        //TODO: Build le packet et l'envoyer avec le TCPCLIENT
        //if checkpass
//              changeVisibleWidget(MAIN);
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

    std::cout << "test" << std::endl;
    auto *selected = list->currentItem();
    if (selected == nullptr) {
        auto *callButton = this->ui->pushButton;

        std::cout << "BITE" << std::endl;
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