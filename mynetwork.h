#ifndef MYNETWORK_H
#define MYNETWORK_H
#include<string>
#include<map>
#include<list>
#include<QObject>
using namespace std;
/*type=00, login,type=00 name= password=
 * type=01,new room,type=01 player1_name=
 * type=02,partition game, type=02 roomid=id player2_name=
 * type=03,speak 03 content ,type=03 content=content
 * type=04,speakto 04 playerid=id content,type=04 playerid=id content=content
 * type=10,deal type=10
 * type=11,hit type=11
 * type=12,double type=12
 * type=13,stand type=13
 * */
#define LOGIN 0x00
#define NEW_ROOM 0x01
#define PARTITION 0x02
#define SPEAK 0x10
#define SPEAKTO 0x11
#define DEAL 0x03
#define HIT 0x04
#define DOUBLE 0x05
#define STAND 0x06
#define QUIT_ROOM 0x07
#define REGISTER 0X08
#define ROOM_LIST 0x80
class Mynetwork
{
public:
    Mynetwork();
    Mynetwork(int fd);
    int mysend(char* buf);
    void myrecv(char* buf);
    void mkthread();
    //void mkrequest(char* buf,map<string,string> &m);
    void mkrequest(char* buf,list<pair<string,string>> &l);
    char* getvalue(char* buf,char* key,int& n);
    char* getvalue(char* buf,char* key);
    int get_sockfd(){return sockfd;}
    static void* recv_thread(void* arg);
private:
    int sockfd;

};

#endif // MYNETWORK_H
