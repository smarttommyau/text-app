//systemlib
#include<unistd.h>
//std lib
#include"stdc++.h"
//network lib
#include<sys/socket.h>
#include<arpa/inet.h>
struct send_data{
	std::string message;
	std::string serverip;
	int port;
};
std::string send_pack(struct send_data send_data){
	//var for network
	int sock = 0,valread,port;
	struct sockaddr_in serv_addr;
	//main
	char buffer[1024] ={0};
	//create socket file
	sock = socket(AF_INET,SOCK_STREAM, 0);
	//valid if socket file create successfully
	if(sock < 0)
		return "err1:socket create failed";
	//setup for connection
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(send_data.port);
	//valid and set connect ip address
	if(inet_pton(AF_INET,send_data.serverip.c_str(),&serv_addr.sin_addr) <= 0)
		return "err2:invalid address,or address not supported";
	//start and valid connection
	if(connect(sock, (struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
		return "err3:connection failed";
	//send message
	send(sock,send_data.message.c_str(),send_data.message.length(),0);
	std::cout << "message sent" << std::endl;
	//read and return message
	valread = read(sock,buffer,1024);
	std::string strbuffer = buffer;
	return strbuffer;
}
