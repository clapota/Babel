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
    QPushButton *pushButton;
    QListWidget *listWidget;
    QMenuBar *menuBar;
    QMenu *menuSalut;
    QMenu *menuLog_out;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(298, 517);
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
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(70, 400, 161, 51));
        listWidget = new QListWidget(centralWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(10, 0, 281, 391));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 298, 22));
        menuSalut = new QMenu(menuBar);
        menuSalut->setObjectName(QStringLiteral("menuSalut"));
        menuLog_out = new QMenu(menuBar);
        menuLog_out->setObjectName(QStringLiteral("menuLog_out"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuSalut->menuAction());
        menuBar->addAction(menuLog_out->menuAction());
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
        pushButton->setText(QApplication::translate("MainWindow", "Call", nullptr));

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

        menuSalut->setTitle(QApplication::translate("MainWindow", "Friends", nullptr));
        menuLog_out->setTitle(QApplication::translate("MainWindow", "Logout", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
