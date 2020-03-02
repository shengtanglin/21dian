#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include<QLayout>
#include<iostream>
#include<mynetwork.h>
#include"room21.h"
#include<pthread.h>
#include<unistd.h>
#define WIDTH 100
#define HEIGHT 100
#define ROW_ROOMS 5
int find_id(vector<Room*>& v,int id){
    int i;
    for(i=0;i<v.size();i++){
        if(v[i]->roomid==id)
            return i;
    }
    return i;
}
/*void* Thread::recv_thread(void* arg){
    //Thread * thread=new Thread(3);
       // Thread* thread=(Thread*)arg;
        cout<<"into thread"<<endl;
        Twovalue t=*((Twovalue*)arg);
        int fd=t.fd;Thread* thread=t.thread;
       // Thread* thread=new Thread(fd);
        fd_set readset,readyset;
        FD_ZERO(&readset);
        FD_SET(fd,&readset);
        readyset=readset;
       // while(1){
            int nready=select(fd+1,&readyset,NULL,NULL,NULL);
            if(nready>0){
                cout<<"emit"<<endl;
                emit thread->notify_recv();
                sleep(2);
            }
       // }
    }
*/
MainWindow::MainWindow(Player player,vector<Room*> room_list,Mynetwork* network,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    int fd=network->get_sockfd();
    Twovalue mem;
    //Thread* thread=new Thread(fd,&mem);
     Thread* thread=new Thread(fd);
    mem.fd=fd;mem.thread=thread;
    wait_new=0;wait_partition=0;isupdating=0;
    //this->room_list=room_list;
    this->network=network;
    this->player=new Player(player.getname(),player.getmoney());
    ui->setupUi(this);
    room21=NULL;
    QPushButton* add_button=new QPushButton(ui->scrollAreaWidgetContents);
    add_button->setGeometry(0,0,WIDTH,HEIGHT);
    QIcon icon;
    icon.addFile(QString::fromUtf8("../Downloads/resource/add.png"), QSize(), QIcon::Normal, QIcon::Off);
    add_button->setIcon(icon);
    connect(add_button,SIGNAL(clicked()),this,SLOT(new_room()));
    ui->lb_name->setText(QString::fromStdString(player.getname()));
    ui->lb_money->setText(QString::number(player.getmoney()));
    for(int i=0;i<room_list.size();i++){
        createRoom(room_list[i]->roomid,room_list[i]->iswaiting,room_list[i]->player1_name,room_list[i]->player2_name);
    }
    connect(thread,SIGNAL(notify_recv()),this,SLOT(myupdate()),Qt::BlockingQueuedConnection);
    //thread->run();
    thread->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}
//row only contains 5 qwidit
void MainWindow::createRoom(int roomid,bool iswaiting,string player1_name,string player2_name){
    Room* room=new Room(ui->scrollAreaWidgetContents);
    cout<<"ui:"<<ui->scrollAreaWidgetContents<<endl;
    room->roomid=roomid;
    room->iswaiting=iswaiting;
    room->player1_name=player1_name;
    room->player2_name=player2_name;
    connect(room->get_button(),SIGNAL(clicked()),room,SLOT(myclicked()));
    connect(room,SIGNAL(click(int)),this,SLOT(partition(int)));
    int rooms=room_list.size();
    int row=(rooms+1)/ROW_ROOMS;
    int column=(rooms+1)%ROW_ROOMS;
    room->setGeometry(column*WIDTH,row*HEIGHT,WIDTH,HEIGHT);
    ui->scrollAreaWidgetContents->resize(ROW_ROOMS*WIDTH,row*HEIGHT);
    room->setText(0,player1_name);
    room->setText(1,player2_name);
    room->show();
    room_list.push_back(room);
    //   room->show();
}

void MainWindow::removeRoom(int roomid)
{
    cout<<"removeroom"<<endl;
    int pos=find_id(room_list,roomid);
    vector<Room*>::iterator it=room_list.begin();
    delete  room_list[pos];
    room_list.erase(pos+it);
    for(int i=pos;i<room_list.size();i++){
        string player1_name=room_list[i]->player1_name;
        string player2_name=room_list[i]->player1_name;
        int rooms=i;
        int row=(rooms+1)/ROW_ROOMS;
        int column=(rooms+1)%ROW_ROOMS;
        room_list[i]->setGeometry(column*WIDTH,row*HEIGHT,WIDTH,HEIGHT);
        ui->scrollAreaWidgetContents->resize(ROW_ROOMS*WIDTH,row*HEIGHT);
        room_list[i]->setText(0,player1_name);
        room_list[i]->setText(1,player2_name);
    }
}

void MainWindow::myupdate()
   {
    /*if(isupdating==1)
       {
        cout<<"updating...."<<endl;
        return;
    }
    isupdating=1;*/
    cout<<"myupdate"<<endl;
    MainWindow* w=this;
    char recv_buf[1000];
    bzero(recv_buf,sizeof(recv_buf));
    w->network->myrecv(recv_buf);
    cout<<"recv:"<<recv_buf<<endl;
    char f[5]="type";
    string r="room_id";string p1="player1_name";string p2="player2_name";string b="broadcast";string s="status";
    string wa="wager";string c1="card1";string c2="card2";string c="card";string isb="isbanker";string bu="isbust";
    string wh="who";string m="money";
    int type=atoi(w->network->getvalue(recv_buf,f));
    switch(type){
    case NEW_ROOM:{
        int roomid=atoi(w->network->getvalue(recv_buf,(char*)r.c_str()));
        string player1_name=w->network->getvalue(recv_buf,(char*)p1.c_str());
        int broadcast=atoi(w->network->getvalue(recv_buf,(char*)b.c_str()));
        w->createRoom(roomid,1,player1_name);
        if(broadcast==0){
            room21=new Room21(roomid,*player,network);
            room21->isbanker=1;
            room21->show();
        }
        break;
    }
    case PARTITION:{
        int status=atoi(network->getvalue(recv_buf,(char*)s.c_str()));
        if(status==1){
            int roomid=atoi(w->network->getvalue(recv_buf,(char*)r.c_str()));
            int pos=find_id(room_list,roomid);
            int broadcast=atoi(w->network->getvalue(recv_buf,(char*)b.c_str()));
            string player2_name=w->network->getvalue(recv_buf,(char*)p2.c_str());
            room_list[pos]->iswaiting=0;
            room_list[pos]->player2_name=player2_name;
            room_list[pos]->setText(1,player2_name);
            if(broadcast==0){
                Player player1(room_list[pos]->player1_name,0);
                room21=new Room21(roomid,player1,*player,network);
                room21->isbanker=0;
                room21->show();
            }
            cout<<to_string(roomid)<<endl;
        }
        if(status==0){
            //nothing to do;because someone else had enter the room faster;
        }
        break;
    }
    case DEAL:{
        cout<<"DEAL"<<endl;
        int room_id=atoi(network->getvalue(recv_buf,(char*)r.c_str()));
        int wager=atoi(network->getvalue(recv_buf,(char*)wa.c_str()));
        int card1=atoi(network->getvalue(recv_buf,(char*)c1.c_str()));
        int card2=atoi(network->getvalue(recv_buf,(char*)c2.c_str()));
        cout<<"card1:"<<card1<<"card2:"<<card2<<endl;
        room21->card1.push_back(card1);
        room21->card2.push_back(card2);
        room21->set_wager(wager);
        room21->show_wager();
        if(room21->isbanker==1){
            room21->dispatch(1);
            room21->dispatch(2);
        }
        else{
            room21->dispatch(2);
            room21->dispatch(1);
        }
        break;
        //int pos=find_id(room_list,room_id);
       // room_list[pos]->
    }
    case SPEAKTO:{
        break;
    }
    case HIT:{
        cout<<"HIT"<<endl;
        int room_id=atoi(network->getvalue(recv_buf,(char*)r.c_str()));
        int card=atoi(network->getvalue(recv_buf,(char*)c.c_str()));
        int isbanker=atoi(network->getvalue(recv_buf,(char*)isb.c_str()));
        int isbust=atoi(network->getvalue(recv_buf,(char*)bu.c_str()));
        cout<<"card:"<<card<<endl;
        if(isbanker)
        {
            room21->card1.push_back(card);
            if(room21->isbanker==1){
                room21->dispatch(1);
            }else{
                room21->dispatch(2);
            }
        }
        else
           {
            room21->card2.push_back(card);
            if(room21->isbanker==1)
                room21->dispatch(2,0);
            else
                room21->dispatch(1);
        }
        if(isbust==1){
            if(isbanker){
                if(room21->isbanker){
                    room21->show_lose();
                }
                else{
                    room21->show_win();
                }
            }
            else{
                if(room21->isbanker){
                    room21->show_win();
                }
                else{
                    room21->show_lose();
                }
            }
        }
        break;
        //int pos=find_id(room_list,room_id);
       // room_list[pos]->
    }
    case STAND:{
        cout<<"stand"<<endl;
        int room_id=atoi(network->getvalue(recv_buf,(char*)r.c_str()));
        int isbanker=atoi(network->getvalue(recv_buf,(char*)isb.c_str()));
        int who=atoi(network->getvalue(recv_buf,(char*)wh.c_str()));
        cout<<"isbanker="<<isbanker<<"stand"<<endl;
        if(isbanker==0){
            if(room21->isbanker==1)
                room21->round_trans();
        }
        else{
            if(who==1){
                if(room21->isbanker==1)
                    room21->show_win();
                else
                    room21->show_lose();
            }
            if(who==2){
                if(room21->isbanker==1)
                    room21->show_lose();
                else
                    room21->show_win();
            }
            if(who==0){
                room21->show_dogfall();
            }
        }
        break;
    }
    case QUIT_ROOM:{
        //because show_win use exec() to block thread,data from server will enter recv_buf before previous data processed.so I temporary
        //use this method to solve this problem
        int offset=0;char* curpos=recv_buf;
        for(int i=0;i<2;i++){
        cout<<"quit room"<<endl;
        int room_id=atoi(network->getvalue(curpos,(char*)r.c_str()));
        int money=atoi(network->getvalue(curpos,(char*)m.c_str()));
        int isbanker=atoi(network->getvalue(curpos,(char*)isb.c_str(),offset));
        cout<<"money="<<money<<endl;
        if(room21->roomid==room_id&&room21->isbanker==isbanker)
            ui->lb_money->setText(QString::fromStdString(to_string(money)));
        int pos=find_id(room_list,room_id);
        if(isbanker)
        {
            room_list[pos]->player1_name="";
            room_list[pos]->setText(0,"");
            if(room_list[pos]->player2_name=="")
                removeRoom(room_id);
        }
        else{
            room_list[pos]->player2_name="";
            room_list[pos]->setText(1,"");
            if(room_list[pos]->player1_name=="")
                removeRoom(room_id);
        }
        curpos+=offset;
        if(network->getvalue(curpos,(char*)r.c_str())==NULL)
            break;
        }
        break;
    }
    }
   // isupdating=0;
   }
void MainWindow::updating(){

}

void MainWindow::start()
{
    pthread_t pid;
    //pid=pthread_create(&pid,NULL,update,this);
}

//void* MainWindow::update(void* arg)
/*static*/
void MainWindow::partition(int roomid)
{
    if(room21==NULL)
     {
    char send_buf[1000],recv_buf[1000];
    bzero(send_buf,sizeof(send_buf));bzero(recv_buf,sizeof(recv_buf));
    list<pair<string,string>> l;
    l.push_back(pair<string,string>("type",to_string(PARTITION)));
     l.push_back(pair<string,string>("roomid",to_string(roomid)));
    l.push_back(pair<string,string>("player2_name",player->getname()));
    network->mkrequest(send_buf,l);
    cout<<send_buf<<endl;
    int a=network->mysend(send_buf);
  /*  network->myrecv(recv_buf);
    string s="status";
    char* ss=(char*)s.data();
    int status=atoi(network->getvalue(recv_buf,ss));
    if(status==1){
        int pos=find_id(room_list,roomid);
        room_list[pos]->iswaiting=0;
        room_list[pos]->player2_name=player->getname();
        room_list[pos]->setText(1,player->getname());
        Room21* room21=new Room21();
        room21->show();
    }
    if(status==0){
        //nothing to do;because someone else had enter the room faster;
    }
    cout<<to_string(roomid)<<endl;*/
    }
}

void MainWindow::on_actionpartition_triggered()
{
    QPushButton* pushButton = new QPushButton(ui->centralwidget);
    pushButton->setText("room");
    pushButton->show();
}

void MainWindow::on_actionlogin_triggered()
{
   /* Dialog* dialog=new Dialog();
    dialog->exec();
    ui->label->setText("name:"+dialog->name);
    //ui->label->setText(name);*/
}

void MainWindow::on_label_2_linkActivated(const QString &link)
{

}

void MainWindow::new_room()
{
    if (room21==NULL)
     {
    char send_buf[1000],recv_buf[1000];
    //char type=NEW_ROOM;
    //char stype[2];
   // stype[0]=type;stype[1]='\0';
    list<pair<string,string>> l;
    //m.insert(pair<string,string>("type",stype));
    l.push_back(pair<string,string>("type",to_string(NEW_ROOM)));
    //m.insert(pair<string,string>("type",to_string(NEW_ROOM)));
    l.push_back(pair<string,string>("player1_name",player->getname()));
    network->mkrequest(send_buf,l);
    cout<<send_buf<<endl;
    int a=network->mysend(send_buf);
    //wait_new=1;
   /* network->myrecv(recv_buf);
    string s="room_id";
    char* ss=(char*)s.data();
    int roomid=atoi(network->getvalue(recv_buf,ss));
    cout<<"roomid is"<<roomid<<endl;
    createRoom(roomid,1,player->getname());*/
   // while(wait_new==1){}
    //Room21* room21=new Room21();
  //  room21->show();
    }
}
