#ifndef ROOM21_H
#define ROOM21_H

#include <QMainWindow>
#include"player.h"
#include<QTimer>
#include<QLabel>
#include<QPushButton>
#include<mynetwork.h>
#include<iostream>
#include<QCloseEvent>
using namespace std;
namespace Ui {
class room21;
}
//player1 is banker,player2 is player;
class Room21 : public QMainWindow
{
    Q_OBJECT

public:
    void closeEvent(QCloseEvent* event);
    bool isbanker;
    vector<int> card1,card2;
    int roomid;
    explicit Room21(int roomid,Mynetwork* network,QWidget *parent = nullptr);
    Room21(int roomid,Player player1,Player player2,Mynetwork* network,QWidget *parent = nullptr);
    Room21(int roomid,Player player1,Mynetwork* network,QWidget *parent = nullptr);
    ~Room21();
    //pos=1 :bottom ;pos=2:top;
    void dispatch(int pos,bool display=1);
    void set_wager(int wager);
    void show_wager();
    void round_trans();
    void show_win();
    void show_lose();
    void show_dogfall();
private slots:

    void move_up();
    void move_down();
    void on_pb_deal_clicked();

    void on_pb_25_clicked();

    void on_pb_50_clicked();

    void on_pb_100_clicked();

    void on_pb_hit_clicked();

    void on_pb_double_clicked();

    void on_pb_stand_clicked();

private:
    bool display;
    int wager;

    QLabel* label_up,*label_down;
    QTimer* timer_up,*timer_down;
    int nums_up,nums_down;
    Player player1,player2;
    vector<QLabel*> bottom_cards,top_cards;
    Ui::room21 *ui;
    Mynetwork* network;
    void quit();
    void initial(int roomid,Mynetwork*  network);
    //pos=1 :bottom ;pos=2:top;
    void show_card(int pos);
    //generated number to card picture and real value
    int num2card(int num);
    int num2real(int num);
};

#endif // Room21_H
