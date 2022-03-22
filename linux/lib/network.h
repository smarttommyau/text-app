//systemlib
#include<unistd.h>
//std lib
#include"stdc++.h"
//network lib
#include<sys/socket.h>
#include<arpa/inet.h>
#include<sys/ioctl.h>
#define CLOCKS_PER_MILLISECONDS CLOCKS_PER_SEC / 1000
#define CLOCKS_PER_NANOSECONDS CLOCKS_PER_MILLISECONDS/1000
struct send_data{
	std::string message;
	std::string serverip;
	int port;
};

bool readbits(int socket,char* buffer,unsigned int size){
	int finished = 0;
	int result;
	long long run;
	clock_t end = clock() + CLOCKS_PER_SEC;
	while(finished < size&&clock() < end){
		int count = 0; 
		result = 0;
		ioctl(socket,FIONREAD,&count);
		if(count > 0){
			result = read(socket, buffer + finished, size - finished);
			finished += result;
			std::cout << "read:" << finished << "/" << size << "bytes" << std::endl;
			std::cout << "loop:" << run << "(" <<(float)(clock()- (end - CLOCKS_PER_SEC))/(CLOCKS_PER_NANOSECONDS) << "ns)" << std::endl;
			end = clock() + CLOCKS_PER_SEC;
		}
		
		run++;
	}
	
	if(finished < size){
		std::cout << "timeout" << std::endl;
		return false;
	}
	return true;
}
std::string getmessage(int new_socket){
	std::string string;
	//get length
	long unsigned int len = 0;
	char* buffer = 0;
	if(!readbits(new_socket,(char*)(&len),sizeof(len))){
		return "";
	}
	std::cout << "socket:" << len << "bytes" << std::endl;
	buffer = new char[len+1];
	if(!readbits(new_socket,(char*)buffer,len)){
		return "dead";
	}
	buffer[len] = '\0';

	string = buffer;
	delete[] buffer;
	
	return string;
	

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
	//FIXME:test code,delete it later
//	unsigned char byte[] = {0xFF,0xFF,0xFF,0xFF};
//	send(sock,(void*)&byte,sizeof(byte),0);
	send(sock,(void*)&len,sizeof(len),0);
	std::cout << "len:" << len << "bytes" << std::endl;
	send(sock,send_data.message.c_str(),send_data.message.length(),0);
	std::cout << "raw:" << send_data.message.c_str() << std::endl;
	std::cout << "message sent" << std::endl;
	//read and return message	
		std::string strbuffer = getmessage(sock);
		std::cout << strbuffer << std::endl;

	return "";
}
