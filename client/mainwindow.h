#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QString>
#include "login.h"
#include"player.h"
#include<QLabel>
#include<QPushButton>
#include<QLayout>
#include<mynetwork.h>
#include<QThread>
#include<iostream>
#include<room21.h>
using namespace std;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
//class MainWindow;

class Room:public QWidget{
    //friend class MainWindow;
     Q_OBJECT
public:
        Room(QWidget *parent = nullptr){
        iswaiting=1;
        this->setParent(parent);
        l=new QVBoxLayout(this);
        p=new QPushButton();
        player1=new QLabel ();
        player2=new  QLabel();
        player1->setText("player1");
        player2->setText("player2");
        l->addWidget(player1);
        l->addWidget(p);
        l->addWidget(player2);
        setLayout(l);
        //enum AlignmentFlag="Aligncenter";
        player1->setAlignment(Qt::AlignCenter);
        player2->setAlignment(Qt::AlignCenter);
        //this->setWindowFlags(Qt::FramelessWindowHint);
    }
       /* void show(){
               p->show();
               player1->show();
               player2->show();
        }*/
        Room(int roomid,bool iswaiting,string name1,string name2){
            this->iswaiting=iswaiting;
            this->roomid=roomid;
            player1_name=name1;
            player2_name=name2;
        }
        void setPlayer(int label,Player& player){
            if(label==0){
               player1->setText(QString::fromStdString(player.getname()));
            }
            if(label==1){
                player2->setText(QString::fromStdString(player.getname()));
            }
            else{
                cout<<"error label"<<endl;
            }
        }
        void setText(int label,string text){
            if(label==0){
               player1->setText(QString::fromStdString(text));
            }
            else if(label==1){
                player2->setText(QString::fromStdString(text));
            }
            else{
                cout<<"error label"<<endl;
            }
        }
        ~Room(){
            delete p;
            delete player1;
            delete player2;
            delete l;
        }
        QPushButton* get_button(){
            return p;
        }
        int roomid;
        bool iswaiting;
        string player1_name;
        string player2_name;

private:
        QLayout* l;
        QPushButton* p;
        QLabel* player1;
        QLabel* player2;
signals:
        void click(int);
public slots:
        void myclicked(){
            emit click(roomid);
        }
};
//static void* update(void*);
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(Player player,vector<Room*> room_list,Mynetwork* network,QWidget *parent = nullptr);
    ~MainWindow();
    bool wait_new;
    bool wait_partition;
    void start();
    //static void* update(void*);
    Mynetwork* network;
    Ui::MainWindow *ui;
    QGridLayout* layout;
    Player* player;
    vector<Player*> player_list;
    vector<Room*> room_list;
    void createRoom(int roomid,bool iswaiting,string player1_name,string player2_name="");
    void removeRoom(int roomid);
    void updating();
private:
    bool isupdating;
    Room21* room21;
    /*Mynetwork* network;
    Ui::MainWindow *ui;
    QGridLayout* layout;
    Player* player;
    vector<Player*> player_list;
    vector<Room*> room_list;
    void createRoom(int roomid,bool iswaiting,string player1_name,string player2_name="");*/

   // QList<>
private slots:
    //void createRoom();
   // QList<QPushButton*> on_actionpartition_triggered();
    void myupdate();
    void partition(int roomid);
    void on_actionlogin_triggered();
    void on_label_2_linkActivated(const QString &link);
    void on_actionpartition_triggered();
    void new_room();
};
class  Thread;
//extern Thread* thread;
struct Twovalue{
    int fd;
    Thread* thread;
};
/*class Thread:public QObject{
    Q_OBJECT
private:
    pthread_t pid;
    int fd;
    Twovalue* mem;
public:
    Thread(){}
    Thread(int fd,Twovalue *mem){
        this->fd=fd;this->mem=mem;
    }
    void run(){
        pid=pthread_create(&pid,NULL,recv_thread,(void*)mem);
    }
    static void* recv_thread(void* arg);
    //void invoke_slot(){emit this->notify_recv();}
signals:
   void notify_recv();
};*/
class Thread:public QThread{
    Q_OBJECT
private:
    pthread_t pid;
    int fd;
    Twovalue* mem;
public:
    //Thread(){}
    Thread(int fd){
        this->fd=fd;
    }
    void run(){
        cout<<"into thread"<<endl;
       // Thread* thread=new Thread(fd);
        fd_set readset,readyset;
        FD_ZERO(&readset);
        FD_SET(fd,&readset);
        readyset=readset;
        while(1){
            int nready=select(fd+1,&readyset,NULL,NULL,NULL);
            if(nready>0){
                cout<<"emit"<<endl;
                emit notify_recv();
               // sleep(2);
            }
            //exec();
        }
    }
    //void invoke_slot(){emit this->notify_recv();}
signals:
   void notify_recv();
};
#endif // MAINWINDOW_H
