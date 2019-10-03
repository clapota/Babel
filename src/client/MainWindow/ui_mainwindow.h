/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionAdd_new_friend;
    QAction *actionDelete_frind;
    QAction *actionLog_out;
    QAction *actionLog_in;
    QWidget *centralWidget;
    QWidget *widget;
    QListWidget *listWidget;
    QPushButton *pushButton;
    QPushButton *DisconnectButton;
    QListWidget *PendingFriends;
    QLabel *label_6;
    QLabel *label_7;
    QWidget *widget_2;
    QPushButton *LogInInLogIn;
    QLabel *label;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLabel *label_2;
    QPushButton *SignInInLogIn;
    QWidget *Sign;
    QPushButton *SignIninSignIn;
    QLabel *label_3;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_4;
    QLabel *label_4;
    QLineEdit *lineEdit_5;
    QLabel *label_5;
    QPushButton *LogInInSignIn;
    QMenuBar *menuBar;
    QMenu *menuSalut;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(313, 517);
        MainWindow->setMinimumSize(QSize(313, 517));
        MainWindow->setMaximumSize(QSize(313, 517));
        actionAdd_new_friend = new QAction(MainWindow);
        actionAdd_new_friend->setObjectName(QStringLiteral("actionAdd_new_friend"));
        actionDelete_frind = new QAction(MainWindow);
        actionDelete_frind->setObjectName(QStringLiteral("actionDelete_frind"));
        actionLog_out = new QAction(MainWindow);
        actionLog_out->setObjectName(QStringLiteral("actionLog_out"));
        actionLog_in = new QAction(MainWindow);
        actionLog_in->setObjectName(QStringLiteral("actionLog_in"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setEnabled(true);
        widget->setGeometry(QRect(0, 0, 311, 461));
        listWidget = new QListWidget(widget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(20, 30, 281, 211));
        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(70, 410, 161, 41));
        DisconnectButton = new QPushButton(widget);
        DisconnectButton->setObjectName(QStringLiteral("DisconnectButton"));
        DisconnectButton->setGeometry(QRect(220, 0, 81, 21));
        PendingFriends = new QListWidget(widget);
        new QListWidgetItem(PendingFriends);
        new QListWidgetItem(PendingFriends);
        new QListWidgetItem(PendingFriends);
        new QListWidgetItem(PendingFriends);
        PendingFriends->setObjectName(QStringLiteral("PendingFriends"));
        PendingFriends->setGeometry(QRect(20, 270, 281, 131));
        label_6 = new QLabel(widget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(20, 250, 91, 20));
        label_7 = new QLabel(widget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(20, 10, 91, 20));
        widget_2 = new QWidget(centralWidget);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        widget_2->setGeometry(QRect(60, 140, 221, 151));
        LogInInLogIn = new QPushButton(widget_2);
        LogInInLogIn->setObjectName(QStringLiteral("LogInInLogIn"));
        LogInInLogIn->setGeometry(QRect(30, 110, 161, 31));
        label = new QLabel(widget_2);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 10, 61, 21));
        lineEdit = new QLineEdit(widget_2);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(90, 10, 113, 25));
        lineEdit_2 = new QLineEdit(widget_2);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(90, 40, 113, 25));
        label_2 = new QLabel(widget_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 40, 61, 21));
        SignInInLogIn = new QPushButton(widget_2);
        SignInInLogIn->setObjectName(QStringLiteral("SignInInLogIn"));
        SignInInLogIn->setGeometry(QRect(30, 70, 161, 31));
        Sign = new QWidget(centralWidget);
        Sign->setObjectName(QStringLiteral("Sign"));
        Sign->setGeometry(QRect(60, 120, 221, 191));
        SignIninSignIn = new QPushButton(Sign);
        SignIninSignIn->setObjectName(QStringLiteral("SignIninSignIn"));
        SignIninSignIn->setGeometry(QRect(30, 90, 161, 31));
        label_3 = new QLabel(Sign);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(20, 10, 61, 21));
        lineEdit_3 = new QLineEdit(Sign);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(90, 10, 113, 25));
        lineEdit_4 = new QLineEdit(Sign);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));
        lineEdit_4->setGeometry(QRect(90, 40, 113, 25));
        label_4 = new QLabel(Sign);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(20, 40, 61, 21));
        lineEdit_5 = new QLineEdit(Sign);
        lineEdit_5->setObjectName(QStringLiteral("lineEdit_5"));
        lineEdit_5->setGeometry(QRect(90, 60, 113, 25));
        label_5 = new QLabel(Sign);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(30, 60, 41, 21));
        LogInInSignIn = new QPushButton(Sign);
        LogInInSignIn->setObjectName(QStringLiteral("LogInInSignIn"));
        LogInInSignIn->setGeometry(QRect(30, 130, 161, 31));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 313, 22));
        menuSalut = new QMenu(menuBar);
        menuSalut->setObjectName(QStringLiteral("menuSalut"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuSalut->menuAction());
        menuSalut->addAction(actionAdd_new_friend);
        menuSalut->addAction(actionDelete_frind);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        actionAdd_new_friend->setText(QApplication::translate("MainWindow", "Add new friend", nullptr));
        actionDelete_frind->setText(QApplication::translate("MainWindow", "Delete friend", nullptr));
        actionLog_out->setText(QApplication::translate("MainWindow", "Log out", nullptr));
        actionLog_in->setText(QApplication::translate("MainWindow", "Log in", nullptr));

        const bool __sortingEnabled = listWidget->isSortingEnabled();
        listWidget->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listWidget->item(0);
        ___qlistwidgetitem->setText(QApplication::translate("MainWindow", "Antoine", nullptr));
        QListWidgetItem *___qlistwidgetitem1 = listWidget->item(1);
        ___qlistwidgetitem1->setText(QApplication::translate("MainWindow", "Abel", nullptr));
        QListWidgetItem *___qlistwidgetitem2 = listWidget->item(2);
        ___qlistwidgetitem2->setText(QApplication::translate("MainWindow", "Lucas", nullptr));
        QListWidgetItem *___qlistwidgetitem3 = listWidget->item(3);
        ___qlistwidgetitem3->setText(QApplication::translate("MainWindow", "Donatien", nullptr));
        listWidget->setSortingEnabled(__sortingEnabled);

        pushButton->setText(QApplication::translate("MainWindow", "Call", nullptr));
        DisconnectButton->setText(QApplication::translate("MainWindow", "Disconnect", nullptr));

        const bool __sortingEnabled1 = PendingFriends->isSortingEnabled();
        PendingFriends->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem4 = PendingFriends->item(0);
        ___qlistwidgetitem4->setText(QApplication::translate("MainWindow", "Antoine", nullptr));
        QListWidgetItem *___qlistwidgetitem5 = PendingFriends->item(1);
        ___qlistwidgetitem5->setText(QApplication::translate("MainWindow", "Abel", nullptr));
        QListWidgetItem *___qlistwidgetitem6 = PendingFriends->item(2);
        ___qlistwidgetitem6->setText(QApplication::translate("MainWindow", "Lucas", nullptr));
        QListWidgetItem *___qlistwidgetitem7 = PendingFriends->item(3);
        ___qlistwidgetitem7->setText(QApplication::translate("MainWindow", "Donatien", nullptr));
        PendingFriends->setSortingEnabled(__sortingEnabled1);

        label_6->setText(QApplication::translate("MainWindow", "Pending friends", nullptr));
        label_7->setText(QApplication::translate("MainWindow", "Friends", nullptr));
        LogInInLogIn->setText(QApplication::translate("MainWindow", "Log In", nullptr));
        label->setText(QApplication::translate("MainWindow", "Username", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Password", nullptr));
        SignInInLogIn->setText(QApplication::translate("MainWindow", "Sign In", nullptr));
        SignIninSignIn->setText(QApplication::translate("MainWindow", "Sign In", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "Username", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "Password", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "Repeat", nullptr));
        LogInInSignIn->setText(QApplication::translate("MainWindow", "Log In", nullptr));
        menuSalut->setTitle(QApplication::translate("MainWindow", "Friends", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
