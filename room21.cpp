#include "room21.h"
#include "ui_room21.h"
#include<QMessageBox>
void Room21::closeEvent(QCloseEvent *event)
{
    quit();
    event->accept();
    //delete this;
}

Room21::Room21(int roomid,Mynetwork* network,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::room21)
{
   initial( roomid,network);

}
//player2 is in bottom
Room21::Room21(int roomid,Player player1, Player player2,Mynetwork* network, QWidget *parent):QMainWindow(parent),
ui(new Ui::room21)
{
    initial(roomid, network);
    this->player1=player1;
    this->player2=player2;
    ui->label_player_bottom->setText(QString::fromStdString(player2.getname()));
    ui->label_player_top->setText(QString::fromStdString(player1.getname()));
    ui->le_money->setText(QString::number(player2.getmoney()));

}

Room21::Room21(int roomid,Player player1,Mynetwork* network, QWidget *parent):QMainWindow(parent),
ui(new Ui::room21)
{
    initial( roomid,network);
    this->player1=player1;
    ui->pb_deal->setVisible(false);
    ui->pb_25->setVisible(false);
    ui->pb_50->setVisible(false);
    ui->pb_100->setVisible(false);
    ui->label_player_bottom->setText(QString::fromStdString(player1.getname()));
    ui->le_money->setText(QString::number(player1.getmoney()));
}

Room21::~Room21()
{
    delete ui;
}
void Room21::set_wager(int wager){
    this->wager=wager;
}

void Room21::show_wager()
{
    ui->le_wager->setText(QString::number(wager));
}

void Room21::round_trans()
{
    if(isbanker==1){
        ui->pb_stand->setVisible(true);
        ui->pb_hit->setVisible(true);
    }
    else{
        ui->pb_stand->setVisible(false);
        ui->pb_double->setVisible(false);
        ui->pb_hit->setVisible(false);
    }
}
//when diag is a stack object,program crash,and report double free error,debug display show_lose() invoke ~room twice ?
void Room21::show_lose()
{
    QMessageBox* diag=new QMessageBox(this);
    diag->setWindowTitle("result");
    diag->setText("you lose");
    if(diag->exec()==QMessageBox::Ok){
        quit();
        delete this;
    }
}
void Room21::show_win()
{
    QMessageBox* diag=new QMessageBox(this);
    diag->setWindowTitle("result");
    diag->setText("you win");
    if(diag->exec()==QMessageBox::Ok){
        quit();
        delete this;
    }
}
void Room21::show_dogfall()
{
    QMessageBox* diag=new QMessageBox(this);
    diag->setWindowTitle("result");
    diag->setText("dogfall");
    if(diag->exec()==QMessageBox::Ok){
        quit();
    }
}
void Room21::dispatch(int pos,bool display)
{
    //label->show();
    this->display=display;
    nums_up=0;nums_down=0;
    /*label->setGeometry(QRect(70, 150, 60, 80));
    label->setPixmap(QPixmap(QString::fromUtf8("../Downloads/resource/puke/puke_back.jpg")));
    label->setScaledContents(true);
    label->show();*/
    //repaint();
    if(pos==1)
       {
        connect(timer_down,SIGNAL(timeout()),this,SLOT(move_down()));
        timer_down->start(15);
    }
    else
       {
        connect(timer_up,SIGNAL(timeout()),this,SLOT(move_up()));
        timer_up->start(15);
    }
}

void Room21::move_up()
{
    nums_up++;
    if(nums_up==25){
        timer_up->stop();
        label_up->hide();
        show_card(2);
        disconnect(timer_up,SIGNAL(timeout()),this,SLOT(move_up()));
    }
    else{
        label_up->setGeometry(QRect(70+(10*nums_up), 200-(10*nums_up), 60, 80));
        label_up->show();
    }
}
void Room21::move_down()
{
    nums_down++;
    if(nums_down==25){
        timer_down->stop();
        label_down->hide();
        show_card(1);
        disconnect(timer_down,SIGNAL(timeout()),this,SLOT(move_down()));
    }
    else{
        label_down->setGeometry(QRect(70+(10*nums_down), 200+(10*nums_down), 60, 80));
        label_down->show();
    }
}
void Room21::on_pb_deal_clicked()
{
    int wager=(ui->le_wager->text()).toInt();
    char send_buf[1000],recv_buf[1000];
    bzero(send_buf,sizeof(send_buf));bzero(recv_buf,sizeof(recv_buf));
    list<pair<string,string>> l;
    l.push_back(pair<string,string>("type",to_string(DEAL)));
     l.push_back(pair<string,string>("roomid",to_string(roomid)));
    l.push_back(pair<string,string>("wager",to_string(wager)));
    network->mkrequest(send_buf,l);
    cout<<send_buf<<endl;
    int a=network->mysend(send_buf);
    ui->pb_deal->setVisible(false);
    ui->pb_25->setVisible(false);
    ui->pb_50->setVisible(false);
    ui->pb_100->setVisible(false);
    ui->pb_stand->setVisible(true);
    ui->pb_double->setVisible(true);
    ui->pb_hit->setVisible(true);
}

void Room21::on_pb_25_clicked()
{
    QString s=ui->le_wager->text();
    int a=s.toInt();
    a=a+25;
    ui->le_wager->setText(QString::number(a));
    wager=a;
}

void Room21::on_pb_50_clicked()
{
    QString s=ui->le_wager->text();
    int a=s.toInt();
    a=a+50;
    ui->le_wager->setText(QString::number(a));
     wager=a;
}

void Room21::on_pb_100_clicked()
{
    QString s=ui->le_wager->text();
    int a=s.toInt();
    a=a+100;
    ui->le_wager->setText(QString::number(a));
     wager=a;
}

void Room21::initial(int roomid,Mynetwork* network)
{

    this->roomid=roomid;
    this->network=network;
    timer_up=new QTimer(this);
    timer_down=new QTimer(this);
    ui->setupUi(this);

    label_up = new QLabel(ui->centralwidget);
    label_down = new QLabel(ui->centralwidget);
    label_up->setGeometry(QRect(70, 150, 60, 80));
    label_up->setPixmap(QPixmap(QString::fromUtf8("../Downloads/resource/puke/puke_back.jpg")));
    label_up->setScaledContents(true);
    label_down->setGeometry(QRect(70, 150, 60, 80));
    label_down->setPixmap(QPixmap(QString::fromUtf8("../Downloads/resource/puke/puke_back.jpg")));
    label_down->setScaledContents(true);
    label_up->setVisible(false);
    label_down->setVisible(false);
    ui->pb_stand->setVisible(false);
    ui->pb_double->setVisible(false);
    ui->pb_hit->setVisible(false);
}

void Room21::show_card(int pos)
{
    int card;
    if((isbanker==0&&pos==1)||(isbanker==1&&pos==2)){
        card=card2.back();
    }
    else{
        card=card1.back();
    }
    card=num2card(card);
    QLabel* label_card=new QLabel(ui->centralwidget);
    string path;
    if(display)
        path="../Downloads/resource/puke/"+to_string(card)+".jpg";
    else
        path="../Downloads/resource/puke/puke_back.jpg";
    label_card->setPixmap(QPixmap(path.c_str()));
    label_card->setScaledContents(true);
    if(pos==1){
        if(bottom_cards.size()==0)
            label_card->setGeometry(QRect(450, 400, 60, 80));
        else
            label_card->setGeometry(QRect(bottom_cards.back()->geometry().x()+60, 400, 60, 80));
        bottom_cards.push_back(label_card);
        for(int i=0;i<bottom_cards.size();i++){
            bottom_cards[i]->setGeometry(bottom_cards[i]->geometry().x()-30,bottom_cards[i]->geometry().y(),60,80);
        }
    }else{
        if(top_cards.size()==0)
            label_card->setGeometry(QRect(450, 70, 60, 80));
        else
            label_card->setGeometry(QRect(top_cards.back()->geometry().x()+60, 70, 60, 80));
        top_cards.push_back(label_card);
        for(int i=0;i<top_cards.size();i++){
            top_cards[i]->setGeometry(top_cards[i]->geometry().x()-30,top_cards[i]->geometry().y(),60,80);
        }

    }
    label_card->show();
}

int Room21::num2card(int num)
{
    return num+3;
}

int Room21::num2real(int num)
{
    int tmp=num%13;
    if(tmp<=10){
        return 3+tmp;
    }else{
        if(tmp==11)
            return 1;
        else
            return 2;
    }
}

void Room21::on_pb_hit_clicked()
{
    char send_buf[1000],recv_buf[1000];
    bzero(send_buf,sizeof(send_buf));bzero(recv_buf,sizeof(recv_buf));
    list<pair<string,string>> l;
    l.push_back(pair<string,string>("type",to_string(HIT)));
     l.push_back(pair<string,string>("roomid",to_string(roomid)));
    l.push_back(pair<string,string>("isbanker",to_string(isbanker)));
    network->mkrequest(send_buf,l);
    cout<<send_buf<<endl;
    int a=network->mysend(send_buf);
   //dispatch(1);
}

void Room21::on_pb_double_clicked()
{
    char send_buf[1000],recv_buf[1000];
    bzero(send_buf,sizeof(send_buf));bzero(recv_buf,sizeof(recv_buf));
    list<pair<string,string>> l;
    l.push_back(pair<string,string>("type",to_string(DOUBLE)));
     l.push_back(pair<string,string>("roomid",to_string(roomid)));
    //l.push_back(pair<string,string>("isbanker",to_string(isbanker)));
    network->mkrequest(send_buf,l);
    cout<<send_buf<<endl;
    int a=network->mysend(send_buf);
}

void Room21::on_pb_stand_clicked()
{
    round_trans();
    char send_buf[1000],recv_buf[1000];
    bzero(send_buf,sizeof(send_buf));bzero(recv_buf,sizeof(recv_buf));
    list<pair<string,string>> l;
    l.push_back(pair<string,string>("type",to_string(STAND)));
     l.push_back(pair<string,string>("roomid",to_string(roomid)));
     l.push_back(pair<string,string>("isbanker",to_string(isbanker)));
     network->mkrequest(send_buf,l);
     cout<<send_buf<<endl;
     int a=network->mysend(send_buf);
}

void Room21::quit()
{
    char send_buf[1000],recv_buf[1000];
    bzero(send_buf,sizeof(send_buf));bzero(recv_buf,sizeof(recv_buf));
    list<pair<string,string>> l;
    l.push_back(pair<string,string>("type",to_string(QUIT_ROOM)));
    l.push_back(pair<string,string>("roomid",to_string(roomid)));
    l.push_back(pair<string,string>("isbanker",to_string(isbanker)));
    network->mkrequest(send_buf,l);
    cout<<send_buf<<endl;
    int a=network->mysend(send_buf);
    //delete this;
}
