//systemlib
#include<unistd.h>
//std lib
#include"stdc++.h"
//network lib
#include<sys/socket.h>
#include<arpa/inet.h>
#include<sys/ioctl.h>
struct send_data{
	std::string message;
	std::string serverip;
	int port;
};
std::string getmessage(int new_socket){
	int count,precount;
	ioctl(new_socket,FIONREAD,&count);
	precount = -1;
	int slow = 0;
	do{
			usleep(100);
			precount = count;
			ioctl(new_socket,FIONREAD,&count);					
	}while(precount != count&&count != 0);
	if(count != 0){
		char buffer[count];
		read(new_socket,&buffer,count);    
		std::string string = buffer;
		return string;
	}else{
		return "";
	}
}
std::string send_pack(struct send_data send_data){
	//var for network
	int sock = 0,valread,port;
	struct sockaddr_in serv_addr;
	//main
	char buffer[2048] ={0};
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
	long unsigned int len = send_data.message.length();
	
	send(sock,(void*)&len,sizeof(len),0);
	std::cout << "len:" << len << "bytes" << std::endl;
	send(sock,send_data.message.c_str(),send_data.message.length(),0);
	std::cout << "raw:" << send_data.message.c_str() << std::endl;
	std::cout << "message sent" << std::endl;
	//read and return message	
		//std::string strbuffer = getmessage(sock);
		read(sock,&buffer,2048); 
		std::string strbuffer = buffer;
		std::cout << strbuffer << std::endl;

	return "";
}
