# 21dian
Description: a battle platform to play 21 dian
OS required:linux 
Mysql version:perconaserver
Install:server:g++ myserver.c -o myserver -l perconaserverclient -g
        client:use qt 
Before run,please create a database  game,then create a table user(name varchar(20),password varchar(20),money int) and add 
information into it;
Run: ./myserver to start server first,then run qt to start client 
Result:
login:
in platform:
in game:
![image](https://github.com/shengtanglin/21dian/raw/master/gaming.png)
