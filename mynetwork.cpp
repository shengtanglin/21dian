#include "mynetwork.h"
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
#include<QDebug>
#include<iostream>
#include<pthread.h>
#include<map>
using namespace std;
#define SERV_PORT 1234
#define SA sockaddr
#define IP "127.0.0.1"
Mynetwork::Mynetwork()
{
    struct sockaddr_in servaddr;
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(SERV_PORT);
    inet_pton(AF_INET,IP,&servaddr.sin_addr);
    std::cout<<"connecting"<<std::endl;
    int a=connect(sockfd,(SA*)&servaddr,sizeof(servaddr));
    std::cout<<a<<"connected"<<std::endl;
   /* char buf[1000];
   while(1){
    recv(sockfd,buf,sizeof(buf),0);
   std::cout<<buf<<std::endl;
    }*/
}

Mynetwork::Mynetwork(int fd)
{
    sockfd=fd;
}
void* Mynetwork::recv_thread(void* arg){
    int sock_fd=*((int*)arg);
    //emit(myupdate());
}
int Mynetwork::mysend(char *buf)
{

   int send_nums=send(sockfd,buf,strlen(buf),0);
   return send_nums;
}

void Mynetwork::myrecv(char *buf)
{
    recv(sockfd,buf,1000,0);
}

void Mynetwork::mkthread()
{
    pthread_t pid;
    pthread_create(&pid,NULL,recv_thread,&sockfd);
}
/*void Mynetwork::mkrequest(char* buf,map<string,string> &m)
{
    for(map<string,string>::iterator it=m.begin();it!=m.end();it++){
        sprintf(buf,"%s%s=%s ",buf,it->first.c_str(),it->second.c_str());
    }
}*/

void Mynetwork::mkrequest(char *buf, list<pair<string, string>> &l)
{
    for(list<pair<string,string>>::iterator it=l.begin();it!=l.end();it++){
        sprintf(buf,"%s%s=%s ",buf,it->first.c_str(),it->second.c_str());
    }
}
char* Mynetwork::getvalue(char* buf,char* key){
    int n=0;
   return getvalue(buf,key,n);
}
char* Mynetwork::getvalue(char* buf,char* key,int& n){
    if (strstr(buf,key)==NULL)
        return NULL;
    char* pos=strstr(buf,key)+strlen(key)+1;
    char* end_pos=pos;
    while(*end_pos!=' '){
        end_pos++;
    }
    n=end_pos-buf;
    char* ptr_value=new char(sizeof(char)*(end_pos-pos));
    char* tmp_pos=pos;
    int i=0;
    while(tmp_pos!=end_pos){
        *(ptr_value+i)=*tmp_pos;
        tmp_pos++;
        i++;
    }
    *(ptr_value+i)='\0';
   // *next_buf=end_pos;

    return ptr_value;
}
