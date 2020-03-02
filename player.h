#ifndef PLAYER_H
#define PLAYER_H
#include<QString>
#include<string>
using namespace std;
class Player{
public:
    Player(){}
    Player(string name,int money){
        this->name=name;
        this->money=money;
    }
    string getname(){return name;}
    int getmoney(){return money;}
private:
    string name;
    int money;
};
#endif // PLAYER_H
