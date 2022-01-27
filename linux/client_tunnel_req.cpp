//systemlib
#include<unistd.h>
//std lib
#include"lib/stdc++.h"
//network lib
#include<sys/socket.h>
#include<arpa/inet.h>

int main(int argc,char const *argv[])
{
	//var for network
	int sock = 0,valread,port;
	struct sockaddr_in serv_addr;
	//parms
	std::string message = argv[3];
	std::string serverip = argv[2];
	std::stringstream p;
	p << argv[1];
	p >> port;
	char buffer[1024] ={0};
	std::string strbuffer;
	//create socket file
	sock = socket(AF_INET,SOCK_STREAM, 0);
	//valid if socket file create successfully
	if(sock < 0){
		std::cerr << "socket create failed";
		exit(EXIT_FAILURE);
	}
	
	//setup for connection
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);
	//valid and set connect ip address
	if(inet_pton(AF_INET,serverip.c_str(),&serv_addr.sin_addr) <= 0){
		std::cerr << "invalid address,or address not supported";
		exit(EXIT_FAILURE);
	}
	//start and valid connection
	if(connect(sock, (struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0){
		std::cerr << "connection failed";
		exit(EXIT_FAILURE);
	}
	//send message
	send(sock,message.c_str(),message.length(),0);
	std::cout << "message sent" << std::endl;
	//read message
	valread = read(sock,buffer,1024);
	strbuffer = buffer;
	std::cout << strbuffer;
	return 0;
}
