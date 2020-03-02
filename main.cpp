#include "mainwindow.h"
#include "room21.h"
#include "login.h"
#include <QApplication>
#include"mynetwork.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //int* b=new int[3] (); delete b;
    //MainWindow w("linlang",1000);
    //Room21 room;
    Dialog login;
   // Mynetwork network;
    login.show();
   // w.show();
    //room.show();
    return a.exec();
}
