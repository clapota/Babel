#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <iostream>
#include <QtCore/QDir>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    client("127.0.0.1", 4444)
{
    ui->setupUi(this);
    auto *connectionButton = this->ui->pushButton_2;
    auto *addFriend = this->ui->actionAdd_new_friend;
    auto *removeFriend =this->ui->actionDelete_frind;
    auto *callButton = this->ui->pushButton;

    ui->lineEdit_2->setEchoMode(QLineEdit::Password);
    connect(addFriend, SIGNAL(triggered()), this, SLOT(addFriend()));
    connect(connectionButton, SIGNAL(clicked()), this, SLOT(connectToServer()));
    connect(callButton, SIGNAL(clicked()), this, SLOT(call()));
    connect(removeFriend, SIGNAL(triggered()), this, SLOT(deleteFriend()));
    ui->widget->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
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
        //TODO: Build le packet et l'envoyer avec le TCPCLIENT
        //if checkpass
              changeVisibleWidget(MAIN);
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
            //TODO: Build le packet et l'envoyer avec le TCPCLIENT

            //IF SERVER RESPONSE == OK
            list->addItem(text);
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
        //TODO: Build le packet et l'envoyer avec le TCPCLIENT

        // IF RESPONSE == OK

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
        std::cout << selected->text().toStdString() << std::endl;
    }

}

void MainWindow::changeVisibleWidget(Widget wid)
{
    if (wid == MAIN) {
        ui->widget->setVisible(true);
        ui->widget_2->setVisible(false);
    } else if (wid == CONNEXION) {
        ui->widget->setVisible(false);
        ui->widget_2->setVisible(true);
    }
}