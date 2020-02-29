#include "login.h"
#include "ui_login.h"
#include"mynetwork.h"
#include<string>
#include<map>
#include<iostream>
using namespace std;
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    w=NULL;
}

bool Dialog::connect()
{
     network=new Mynetwork();
    //shifoukeyi?
    //char type=LOGIN;
   // char stype[2];
   // stype[0]=type;stype[1]='\0';
    std::string name=(ui->le_name->text()).toStdString();
    std::string password=(ui->le_password->text()).toStdString();
    list<pair<string,string>> l;
    //m.insert(pair<string,string>("type",stype));
    l.push_back(pair<string,string>("type",to_string(LOGIN)));
    l.push_back(pair<string,string>("name",name));
    l.push_back(pair<string,string>("password",password));
    char send_buf[1000],recv_buf[1000];
    network->mkrequest(send_buf,l);
    cout<<send_buf<<endl;
    int a=network->mysend(send_buf);
    cout<<a<<endl;
    network->myrecv(recv_buf);
    char f[7]="status";
    cout<<recv_buf<<endl;
    char status=*(network->getvalue(recv_buf,f));
    cout<<status<<endl;
   // char buf1[4]={1,2,3};char buf2[4]={2,3,4};
    //int c=strcmp(buf1,"name");
    //0 success,1 don't contain this name ,2 name password not match;
    if(status=='1')
    {
        cout<<"don't contain this name"<<endl;
        return 0;
    }
    if(status=='2')
    {
        cout<<"name password not match;"<<endl;
        return 0;
    }
    if(status=='0'){
        char ff[6]="money";
        player=new Player(name,atoi(network->getvalue(recv_buf,ff)));
        cout<<"success"<<endl;
        //
        char f[5]="type";
        int type=atoi(network->getvalue(recv_buf,f));
        if(type==ROOM_LIST){
            cout<<"get room_list from server"<<endl;
            char nroom_f[]="nroom";
            char iswaiting_f[]="iswaiting";
            char player1_name_f[]="player1_name";
            char player2_name_f[]="player2_name";
            char roomid_f[]="roomid";
            int nroom=atoi(network->getvalue(recv_buf,nroom_f));
            int offset=0;char* curpos=recv_buf;
           // *next_buf=recv_buf;
            for(int i=0;i<nroom;i++){
                int roomid=atoi(network->getvalue(curpos,roomid_f));
                bool iswaiting=atoi(network->getvalue(curpos,iswaiting_f));
                string player1_name=network->getvalue(curpos,player1_name_f);
                string player2_name=network->getvalue(curpos,player2_name_f,offset);
                curpos+=offset;
                Room* room=new Room (roomid,iswaiting,player1_name,player2_name);
                room_list.push_back(room);
            }
        }
        return 1;
    }
    else{
        cout<<"server pass wrong value"<<endl;
    }//
    //get room_list
    //ui->le_name
    return 0;
}

Dialog::~Dialog()
{
    delete ui;
}

MainWindow *Dialog::get_mainwindow()
{
    return w;
}



void Dialog::on_buttonBox_accepted()
{
   bool isconnected=connect();
   if(isconnected){
       w=new MainWindow(*player,room_list,network);
      // w->start();
       //pthread_t pid;
       w->show();
   }
}
