#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
#include<unistd.h>
#include<pthread.h>
#include<stdio.h>
#include<map>
#include<vector>
#include<bitset>
#include<list>
#include<time.h>
#include<perconaserver/mysql.h>
using namespace std;
#define SERV_PORT 1234
#define SA sockaddr
#define LISTENQ 5
#define MAX_ROOMS 60000
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
#define ROOM_LIST 0x80
#define REGISTER 0X08
//int listenfd,confd;
/*void* mythread(void* arg){
	//int confd=*(int*)arg;
	int confd=int(*((int*)arg));
	while(1){
			std::cout<<std::cin.good()<<std::endl;
			std::cin.getline(buf,20);
			std::cout<<buf<<std::endl;
			send(confd,buf,sizeof(buf),0);
	}	
}*/
/*int parse(char* buf){
	char* pos=strstr(buf,"type");
	char type=buf[pos+5];
	//char* pos=strstr(buf,"content");
	return (int)type;
	
}*/
class Player{
public:
	Player(string name,int money){
		info=new list<pair<string,string> >;
		info->push_back(pair<string,string>("name",name));
		info->push_back(pair<string,string>("money",to_string(money)));
	}
	~Player(){delete info;}
	list<pair<string,string> >* get_info(){
		return info;
	}
private:
	int playid;
	string name;
	string password;
	string img_address;
	int money;
	vector<int> friends;
	list<pair<string,string> >* info;
};
class Room{
public:
	Room(string n1,int sockfd){
		sockfd1=sockfd;
		iswaiting=1;
		room_id=-1;
		player1_name=n1;
		wager=0;
		who=-1;
		for(int i=0;i<52;i++){
			cards.push_back(i);
		}
	}
	//return card number
	int dispatch(){
		srand((unsigned)time(NULL));
		int pos=rand()%cards.size();
		int number=cards[pos];
		vector<int>::iterator it=cards.begin()+pos;
		cards.erase(it);
		cout<<"card is "<<number<<endl;
		return number;
	}
	int sum(int who){
		int sum=0;
		if(who==1){
			for(int i=0;i<card1.size();i++){
				sum+=num2real(card1[i]);
			}
		}else{
			for(int i=0;i<card2.size();i++){
				sum+=num2real(card2[i]);
			}
		}
		return sum;
	}
	 int num2real(int num){
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
	    void reset(MYSQL& mysql){
	    	cards.clear();
	    	for(int i=0;i<52;i++){
			cards.push_back(i);
		}
		string name_add,name_dec;
		if(who==1)
		{
			name_add=player1_name;
			name_dec=player2_name;
		}
		if(who==2)
		{
			name_add=player2_name;
			name_dec=player1_name;		
		}
		string sql_add="update user set money=money+"+to_string(wager)+" where name='"+name_add+"';";
		string sql_dec="update user set money=money-"+to_string(wager)+" where name='"+name_dec+"';";
		mysql_query(&mysql,sql_add.c_str());
		mysql_query(&mysql,sql_dec.c_str());
		wager=0;
	    }
         int who;
	int room_id;
	bool iswaiting;
	int sockfd1,sockfd2;
	vector<int> card1,card2;
	vector<int> cards;
        string player1_name;
        string player2_name;
        int wager;
};
 vector<Room*> room_list;
 bitset<MAX_ROOMS>  roomids;
 vector<int> conds;
 MYSQL mysql;
 MYSQL_RES *result=NULL;
 MYSQL_FIELD *field=NULL;
 int mystrcmp(char* c1,char* c2){
 	if(c1==NULL||c2==NULL)
 		return -1;
 	else
 		return strcmp(c1,c2);
 }
void mk_request(char* buf,list<pair<string,string> > & m)
{
    for(list<pair<string,string> > ::iterator it=m.begin();it!=m.end();it++){
        sprintf(buf,"%s%s=%s ",buf,it->first.c_str(),it->second.c_str());
    }
}
char* getvalue(char* buf,char* key){
	if(strstr(buf,key)==NULL)
	 	return NULL;
	char* pos=strstr(buf,key)+strlen(key)+1;
	char* end_pos=pos;
	while(*end_pos!=' '){
		end_pos++;
	}
	char* ptr_value=new char(sizeof(char)*(end_pos-pos));
	char* tmp_pos=pos;
	int i=0;
	while(tmp_pos!=end_pos){
		*(ptr_value+i)=*tmp_pos;
		tmp_pos++;
		i++;
	}
	*(ptr_value+i)='\0';
	return ptr_value;
}
int get_roomid(){
	int cur_id;
	if(room_list.size()==0)
		cur_id=0;
	else{
			cur_id=room_list.back()->room_id;
		}
	while(roomids.test(cur_id)==1){
		cur_id=(cur_id+1)%MAX_ROOMS;
	}
	roomids.set(cur_id);
	return cur_id;
}
int find(vector<Room*>& v,int id){
	int i;
	for( i=0;i<v.size();i++){
		if(v[i]->room_id==id)
			return i;
	}
	return i;
}
void handle(char* buf,int sockfd){
	char t[5]="type";
	char* ctype=getvalue(buf,t);
	int type=atoi(ctype);
	cout<<type<<endl;
	char send_buf[1000];
	bzero(send_buf,sizeof(send_buf));
	switch(type){
	case LOGIN:{
		//0 success,1 don't contain this name ,2 name password not match;
	         int login_code=-1;
	         int money=-1;
		cout<<"login"<<endl;
		char tt[5]="name";char ttt[9]="password";
		char* name=getvalue(buf,tt);char* password_input=getvalue(buf,ttt);
		//m->insert(pair<string,string>("status",'1'));
		cout<<"name="<<name<<endl;
		string sql="select * from user where name='";
		sql=sql+name+"';";
		cout<<sql<<endl;
		mysql_query(&mysql,sql.c_str());
		result=mysql_store_result(&mysql);
		if(result==NULL||mysql_num_rows(result)==0)
			{
				login_code=1;
				cout<<"don't contain this name"<<endl;
			}
		else{
			MYSQL_ROW row=mysql_fetch_row(result);
			char* password=row[1];
			money=atoi(row[2]);
			cout<<password<<" "<<money<<endl;
			if(!mystrcmp(password_input,password))
				login_code=0;
			else
				login_code=2;
		}
		if(login_code==0){
			Player* player=new Player(name,money);
			//map<string,string>* m;
			list<pair<string,string> > *l;
			l=player->get_info();
			l->push_back(pair<string,string>("status","0"));
			// type=room_list nroom roomid iswaiting play1_name player2_name roomid
			l->push_back(pair<string,string>("type",to_string(ROOM_LIST)));
			l->push_back(pair<string,string>("nroom",to_string(room_list.size())));
			for(int i=0;i<room_list.size();i++){
				l->push_back(pair<string,string>("roomid",to_string(room_list[i]->room_id)));
				l->push_back(pair<string,string>("iswaiting",to_string(room_list[i]->iswaiting)));
				l->push_back(pair<string,string>("player1_name",room_list[i]->player1_name));
				l->push_back(pair<string,string>("player2_name",room_list[i]->player2_name));
			}
			mk_request(send_buf,*l);
			cout<<l->size()<<endl;
			//delete player;
		}
		else{
			list<pair<string,string> > *l=new list<pair<string,string> >();
			if(login_code==1)
				l->push_back(pair<string,string>("status","1"));
			else
				l->push_back(pair<string,string>("status","2"));;
			mk_request(send_buf,*l);
		}
		send(sockfd,send_buf,strlen(send_buf),0);
		break;
		}
	case REGISTER:{
		cout<<"register"<<endl;
		int register_code=-1;
	         int money=-1;
		cout<<"register"<<endl;
		char tt[5]="name";char ttt[9]="password";
		char* name=getvalue(buf,tt);char* password=getvalue(buf,ttt);
		cout<<"name="<<name<<endl;
		string sql="select * from user where name='";
		sql=sql+name+"';";
		cout<<sql<<endl;
		mysql_query(&mysql,sql.c_str());
		result=mysql_store_result(&mysql);
		if(mysql_num_rows(result)!=0)
			{
				register_code=0;
				cout<<" name is used"<<endl;
			}
		else{
			sql="insert into user values('";
			sql=sql+name+"','"+password+"',"+"1000);";
			cout<<sql<<endl;
			if(mysql_query(&mysql,sql.c_str())==0)
				register_code=1;
			else 
				register_code=0;
		}
		list<pair<string,string> > *l=new list<pair<string,string> >();
		if(register_code==1)
			l->push_back(pair<string,string>("status","1"));
		else
			l->push_back(pair<string,string>("status","0"));;
		mk_request(send_buf,*l);
		send(sockfd,send_buf,strlen(send_buf),0);
		break;
		}
	case NEW_ROOM:{
		cout<<"new_room"<<endl;
		char ttt[13]="player1_name";
		char* player1_name=getvalue(buf,ttt);
		Room* room=new Room(player1_name,sockfd);
		int room_id=get_roomid();
		room->room_id=room_id;
		room_list.push_back(room);
		//list<pair<string,string> > l;
		//l.push_back(pair<string,string>("room_id",to_string(room_id)));
		//mk_request(send_buf,l);
		//send to other player
		//char s_buf[1000];
		for(int i=0;i<conds.size();i++){
			bzero(send_buf,sizeof(send_buf));
			list<pair<string,string> > ll;
			if(conds[i]==sockfd)
			{
				//sifa
				ll.push_back(pair<string,string>("broadcast",to_string(0)));
			}
			else{
				//guangbo
				ll.push_back(pair<string,string>("broadcast",to_string(1)));
			}
			ll.push_back(pair<string,string>("type",to_string(NEW_ROOM)));
			ll.push_back(pair<string,string>("room_id",to_string(room_id)));
			ll.push_back(pair<string,string>("player1_name",player1_name));
			mk_request(send_buf,ll);	
			send(conds[i],send_buf,strlen(send_buf),0);		
		}
		//end send
		break;
		}
	case PARTITION:{
		cout<<"partitioin"<<endl;
		char tt[7]="roomid";
		int roomid=atoi(getvalue(buf,tt));
		char ttt[13]="player2_name";
		char* player2_name=getvalue(buf,ttt);
		int pos=find(room_list,roomid);
		if(pos==room_list.size())
			cout<<"unknown error when partition room"<<endl;
		if(room_list[pos]->iswaiting==1){
			room_list[pos]->iswaiting=0;
			room_list[pos]->player2_name=player2_name;
			room_list[pos]->sockfd2=sockfd;
			//l.push_back(pair<string,string>("status","1"));
			//mk_request(send_buf,l);
			//send to other player
			//char send_buf[1000];
			for(int i=0;i<conds.size();i++){
				list<pair<string,string> > l;
				bzero(send_buf,sizeof(send_buf));
				l.push_back(pair<string,string>("status","1"));
				//list<pair<string,string> > ll;
				if(conds[i]==sockfd)
				{
					//sifa
					l.push_back(pair<string,string>("broadcast",to_string(0)));
				}
				else{
					//guangbo
					l.push_back(pair<string,string>("broadcast",to_string(1)));
				}
				l.push_back(pair<string,string>("type",to_string(PARTITION)));
				l.push_back(pair<string,string>("room_id",to_string(roomid)));
				l.push_back(pair<string,string>("player2_name",player2_name));
				mk_request(send_buf,l);	
				send(conds[i],send_buf,strlen(send_buf),0);		
			} 
			//end send
		}else{
			list<pair<string,string> > l;
			 l.push_back(pair<string,string>("status","0"));
			 mk_request(send_buf,l);
			 send(sockfd,send_buf,strlen(send_buf),0);
		}
		//send(sockfd,send_buf,strlen(send_buf),0);
		break;
	}
	case DEAL:{
		cout<<"deal"<<endl;
		char tt[7]="roomid";char ttt[6]="wager";
		int roomid=atoi(getvalue(buf,tt));
		int wager=atoi(getvalue(buf,ttt));
		int pos=find(room_list,roomid);
		Room* room=room_list[pos];
		int player1_card=room->dispatch();
		int player2_card=room->dispatch();
		room->card1.push_back(player1_card);
		room->card2.push_back(player2_card);
		room->wager=wager;
		list<pair<string,string> > l;
		bzero(send_buf,sizeof(send_buf));
		l.push_back(pair<string,string>("type",to_string(DEAL)));
		l.push_back(pair<string,string>("room_id",to_string(roomid)));
		l.push_back(pair<string,string>("wager",to_string(wager)));
		l.push_back(pair<string,string>("card1",to_string(player1_card)));
		l.push_back(pair<string,string>("card2",to_string(player2_card)));
		mk_request(send_buf,l);
		send(room->sockfd1,send_buf,strlen(send_buf),0);
		send(room->sockfd2,send_buf,strlen(send_buf),0);
		break;
	}
	case HIT:{
		cout<<"HIT"<<endl;
		char tt[7]="roomid";char ttt[9]="isbanker";
		int roomid=atoi(getvalue(buf,tt));
		int isbanker=atoi(getvalue(buf,ttt));
		int pos=find(room_list,roomid);
		int isbust=0;
		Room* room=room_list[pos];
		int card=room->dispatch();
		if(isbanker)
		{
			room->card1.push_back(card);
			if(room->sum(1)>21)
				{isbust=1;room->who=2;room->reset(mysql);}
		}
		else
		{
			room->card2.push_back(card);
			if(room->sum(2)>21)
				{isbust=1;room->who=1;room->reset(mysql);}
		}
		list<pair<string,string> > l;
		bzero(send_buf,sizeof(send_buf));
		l.push_back(pair<string,string>("type",to_string(HIT)));
		l.push_back(pair<string,string>("room_id",to_string(roomid)));
		l.push_back(pair<string,string>("isbanker",to_string(isbanker)));
		l.push_back(pair<string,string>("isbust",to_string(isbust)));
		l.push_back(pair<string,string>("card",to_string(card)));
		mk_request(send_buf,l);
		send(room->sockfd1,send_buf,strlen(send_buf),0);
		send(room->sockfd2,send_buf,strlen(send_buf),0);
		break;
	}
	case STAND:{
		cout<<"STAND"<<endl;
		char tt[7]="roomid";char ttt[9]="isbanker";
		int roomid=atoi(getvalue(buf,tt));
		int isbanker=atoi(getvalue(buf,ttt));
		int pos=find(room_list,roomid);
		Room* room=room_list[pos];
		int who=-1;
		if(room->sum(1)>room->sum(2)){
			who=1;room->reset(mysql);
		}
		if(room->sum(1)==room->sum(2)){
			who=0;room->reset(mysql);
		}
		if(room->sum(1)<room->sum(2)){
			who=2;room->reset(mysql);
		}
		room->who=who;
		list<pair<string,string> > l;
		bzero(send_buf,sizeof(send_buf));
		l.push_back(pair<string,string>("type",to_string(STAND)));
		l.push_back(pair<string,string>("room_id",to_string(roomid)));
		l.push_back(pair<string,string>("isbanker",to_string(isbanker)));
		l.push_back(pair<string,string>("who",to_string(who)));
		mk_request(send_buf,l);
		send(room->sockfd1,send_buf,strlen(send_buf),0);
		send(room->sockfd2,send_buf,strlen(send_buf),0);
		break;
	}
	case QUIT_ROOM:{
		cout<<"quit_room"<<endl;
		char tt[7]="roomid";char ttt[9]="isbanker";
		int roomid=atoi(getvalue(buf,tt));
		int isbanker=atoi(getvalue(buf,ttt));
		int pos=find(room_list,roomid);
		Room* room=room_list[pos];
		int money;int fd,fd2;
		vector<Room*>::iterator it=room_list.begin();
		string sql="select money from user where name='";
		if(isbanker)
		{
			sql=sql+room->player1_name+"';";
			fd=room->sockfd1;fd2=room->sockfd2;
			room->player1_name="";
			if(room->player2_name=="")
				room_list.erase(it+pos);
		}
		else
		{
			sql=sql+room->player2_name+"';";
			fd=room->sockfd2;fd2=room->sockfd1;
			room->player2_name="";
			if(room->player1_name=="")
				room_list.erase(it+pos);
		}
		mysql_query(&mysql,sql.c_str());
		result=mysql_store_result(&mysql);
		MYSQL_ROW row=mysql_fetch_row(result);
		money=atoi(row[0]);
		list<pair<string,string> > l;
		bzero(send_buf,sizeof(send_buf));
		l.push_back(pair<string,string>("type",to_string(QUIT_ROOM)));
		l.push_back(pair<string,string>("room_id",to_string(roomid)));
		l.push_back(pair<string,string>("isbanker",to_string(isbanker)));
		l.push_back(pair<string,string>("money",to_string(money)));
		mk_request(send_buf,l);
		for(int i=0;i<conds.size();i++)
		{
			//if(conds[i]!=fd2)
				send(conds[i],send_buf,strlen(send_buf),0);
		}
		//send(fd,send_buf,strlen(send_buf),0);
		break;
	}
	}
	
	//send(sockfd,send_buf,strlen(send_buf),0);
}
int main(int argc,char** argv)
{
	mysql_init(&mysql);
	if(!mysql_real_connect(&mysql,"localhost","root","940730","game",0,NULL,0)){
			cout<<"connect "<<mysql_error(&mysql)<<endl;
	}
	/*string sql="select * from user;";
	mysql_query(&mysql,sql.c_str());
	result=mysql_store_result(&mysql);
	 cout<<"ret"<<mysql_error(&mysql)<<endl;
	int rowcount=mysql_num_rows(result);
	MYSQL_ROW row;
	for (int i=0;i<rowcount;i++){
		row=mysql_fetch_row(result);
		cout<<row[0]<<row[1]<<endl;
	}
	cout<<rowcount<<endl;*/
	pthread_t pid;
    int listenfd,confd;
	//char buf[20]="hhh";
    pid_t childpid;
    socklen_t clilen;
    struct sockaddr_in cliaddr,servaddr;
     clilen=sizeof(cliaddr);
    listenfd=socket(AF_INET,SOCK_STREAM,0);
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    servaddr.sin_port=htons(SERV_PORT);
    bind(listenfd,(SA*)&servaddr,sizeof(servaddr));
    listen(listenfd,LISTENQ);
    std::cout<<"my pid is"<<getpid()<<std::endl;
    char buf[1000];
    fd_set read_set,ready_set;
    FD_ZERO(&read_set);
    FD_SET(listenfd,&read_set);
    int maxfd=listenfd;
   // vector<int> conds;
//confd=accept(listenfd,(SA*)&cliaddr,&clilen);
    for(;;)
    {
    	bzero(buf,sizeof(buf));
    	ready_set=read_set;
       int readys=select(maxfd+1,&ready_set,NULL,NULL,NULL);
       if(FD_ISSET(listenfd,&ready_set)){
		 confd=accept(listenfd,(SA*)&cliaddr,&clilen);
		 conds.push_back(confd);
		 FD_SET(confd,&read_set);
		 maxfd=confd>maxfd?confd:maxfd;
		  recv(confd,buf,sizeof(buf),0);
		  handle(buf,confd);
	}
	for(int i=0;i<conds.size();i++){
		vector<int>::iterator it=conds.begin();
		if(FD_ISSET(conds[i],&ready_set)){
			cout<<"conds="<<to_string(conds[i])<<endl;
			if( recv(conds[i],buf,sizeof(buf),0)!=0)
			 	handle(buf,conds[i]);
			 else
			 	{std::cout<<"client  "<<conds[i]<<"close"<<endl;conds.erase(it+i);i--;}
		}
	}
       //confd=accept(listenfd,(SA*)&cliaddr,&clilen);
     // recv(confd,buf,sizeof(buf),0);
      // type=parse(buf);
  //     handle(buf,confd);
	//send(confd,buf,sizeof(buf),0);
	
    }
    //Close(connfd);
}
