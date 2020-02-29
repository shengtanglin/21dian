/********************************************************************************
** Form generated from reading UI file 'room21.ui'
**
** Created by: Qt User Interface Compiler version 5.14.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ROOM21_H
#define UI_ROOM21_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_room21
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QLabel *label_2;
    QPushButton *pb_25;
    QPushButton *pb_50;
    QPushButton *pb_100;
    QLabel *label_player_bottom;
    QLabel *label_player_top;
    QLineEdit *le_wager;
    QLineEdit *le_money;
    QPushButton *pb_deal;
    QPushButton *pb_double;
    QPushButton *pb_hit;
    QPushButton *pb_stand;
    QLabel *label_5;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *room21)
    {
        if (room21->objectName().isEmpty())
            room21->setObjectName(QString::fromUtf8("room21"));
        room21->resize(800, 600);
        centralwidget = new QWidget(room21);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(6, 5, 741, 561));
        label->setStyleSheet(QString::fromUtf8("background:transparent;"));
        label->setPixmap(QPixmap(QString::fromUtf8("../Downloads/resource/desk.jpg")));
        label->setScaledContents(true);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(60, 150, 141, 191));
        label_2->setPixmap(QPixmap(QString::fromUtf8("../Downloads/resource/puke/puke_total.png")));
        pb_25 = new QPushButton(centralwidget);
        pb_25->setObjectName(QString::fromUtf8("pb_25"));
        pb_25->setGeometry(QRect(500, 490, 61, 61));
        pb_25->setStyleSheet(QString::fromUtf8("background:transparent;"));
        QIcon icon;
        icon.addFile(QString::fromUtf8("../Downloads/resource/jetton/25.png"), QSize(), QIcon::Normal, QIcon::Off);
        pb_25->setIcon(icon);
        pb_25->setIconSize(QSize(64, 64));
        pb_25->setFlat(true);
        pb_50 = new QPushButton(centralwidget);
        pb_50->setObjectName(QString::fromUtf8("pb_50"));
        pb_50->setGeometry(QRect(570, 490, 90, 61));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("../Downloads/resource/jetton/50.png"), QSize(), QIcon::Normal, QIcon::Off);
        pb_50->setIcon(icon1);
        pb_50->setIconSize(QSize(64, 64));
        pb_50->setFlat(true);
        pb_100 = new QPushButton(centralwidget);
        pb_100->setObjectName(QString::fromUtf8("pb_100"));
        pb_100->setGeometry(QRect(660, 490, 90, 61));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8("../Downloads/resource/jetton/100.png"), QSize(), QIcon::Normal, QIcon::Off);
        pb_100->setIcon(icon2);
        pb_100->setIconSize(QSize(64, 64));
        pb_100->setFlat(true);
        label_player_bottom = new QLabel(centralwidget);
        label_player_bottom->setObjectName(QString::fromUtf8("label_player_bottom"));
        label_player_bottom->setGeometry(QRect(210, 460, 57, 16));
        label_player_top = new QLabel(centralwidget);
        label_player_top->setObjectName(QString::fromUtf8("label_player_top"));
        label_player_top->setGeometry(QRect(470, 40, 57, 16));
        le_wager = new QLineEdit(centralwidget);
        le_wager->setObjectName(QString::fromUtf8("le_wager"));
        le_wager->setGeometry(QRect(320, 350, 113, 26));
        le_wager->setAlignment(Qt::AlignCenter);
        le_money = new QLineEdit(centralwidget);
        le_money->setObjectName(QString::fromUtf8("le_money"));
        le_money->setGeometry(QRect(70, 30, 113, 26));
        pb_deal = new QPushButton(centralwidget);
        pb_deal->setObjectName(QString::fromUtf8("pb_deal"));
        pb_deal->setGeometry(QRect(30, 500, 90, 32));
        pb_double = new QPushButton(centralwidget);
        pb_double->setObjectName(QString::fromUtf8("pb_double"));
        pb_double->setGeometry(QRect(520, 510, 90, 32));
        pb_hit = new QPushButton(centralwidget);
        pb_hit->setObjectName(QString::fromUtf8("pb_hit"));
        pb_hit->setGeometry(QRect(630, 510, 90, 32));
        pb_stand = new QPushButton(centralwidget);
        pb_stand->setObjectName(QString::fromUtf8("pb_stand"));
        pb_stand->setGeometry(QRect(120, 500, 90, 32));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(20, 40, 57, 16));
        room21->setCentralWidget(centralwidget);
        label->raise();
        label_2->raise();
        pb_25->raise();
        pb_50->raise();
        pb_100->raise();
        label_player_bottom->raise();
        label_player_top->raise();
        le_wager->raise();
        le_money->raise();
        pb_double->raise();
        pb_hit->raise();
        pb_stand->raise();
        label_5->raise();
        pb_deal->raise();
        menubar = new QMenuBar(room21);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 28));
        room21->setMenuBar(menubar);
        statusbar = new QStatusBar(room21);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        room21->setStatusBar(statusbar);

        retranslateUi(room21);

        QMetaObject::connectSlotsByName(room21);
    } // setupUi

    void retranslateUi(QMainWindow *room21)
    {
        room21->setWindowTitle(QCoreApplication::translate("room21", "MainWindow", nullptr));
        label->setText(QString());
        label_2->setText(QString());
        pb_25->setText(QString());
        pb_50->setText(QString());
        pb_100->setText(QString());
        label_player_bottom->setText(QCoreApplication::translate("room21", "player1", nullptr));
        label_player_top->setText(QCoreApplication::translate("room21", "player2", nullptr));
        le_wager->setText(QCoreApplication::translate("room21", "25", nullptr));
        pb_deal->setText(QCoreApplication::translate("room21", "deal", nullptr));
        pb_double->setText(QCoreApplication::translate("room21", "double", nullptr));
        pb_hit->setText(QCoreApplication::translate("room21", "hit", nullptr));
        pb_stand->setText(QCoreApplication::translate("room21", "stand", nullptr));
        label_5->setText(QCoreApplication::translate("room21", "money:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class room21: public Ui_room21 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ROOM21_H
