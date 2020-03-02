# 21dian
OS required:linux   
Mysql version:perconaserver  
Install:server:g++ myserver.c -o myserver -l perconaserverclient -g  
        client:use qt   
Before run,please create a database  game,then create a table user(name varchar(20),password varchar(20),money int).Next,put resource to proper position.  
Run: ./myserver to start server first,then run qt to start client   
Result:  
login:  
![image](https://github.com/shengtanglin/21dian/raw/master/login.png)
in platform:  
![image](https://github.com/shengtanglin/21dian/raw/master/platform.png)
in game:  
![image](https://github.com/shengtanglin/21dian/raw/master/gaming.png)
