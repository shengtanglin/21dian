#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include"mainwindow.h"
#include"player.h"
#include"mynetwork.h"
class MainWindow;
namespace Ui {
class Dialog;
}
class Room;
class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    bool connect();
    ~Dialog();
    MainWindow* get_mainwindow();
private slots:
    void on_buttonBox_accepted();

private:
    Mynetwork* network;
    Ui::Dialog *ui;
     MainWindow* w;
     Player* player;
    vector<Room*> room_list;
};

#endif // DIALOG_H
