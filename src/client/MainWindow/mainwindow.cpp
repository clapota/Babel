#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    client("127.0.0.1", 4444)
{
    ui->setupUi(this);
    auto *connectionButton = this->ui->pushButton_2;

    ui->lineEdit_2->setEchoMode(QLineEdit::Password);
    connect(connectionButton, SIGNAL(clicked()), this, SLOT(connectToServer()));
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
}