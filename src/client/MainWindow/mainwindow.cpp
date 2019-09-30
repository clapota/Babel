#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->pushButton_2, SIGNAL(clicked()),this, SLOT(buttonclick()));
    ui->widget->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeVisibleWidget()
{
    if (ui->widget_2->isVisible() == true) {
        ui->widget->setVisible(true);
        ui->widget_2->setVisible(false);
    } else {
        ui->widget->setVisible(false);
        ui->widget_2->setVisible(true);
    }
}
