//systemlib
#include<unistd.h>
//std lib
#include"lib/stdc++.h"
//program lib
#include "lib/text-app.h"
int main(int argc,char const *argv[])
{
	struct send_data send_data;
	//parms
	send_data.message = argv[3];
	send_data.serverip = argv[2];
	//convert string to int
	std::stringstream p;
	p << argv[1];
	p >> send_data.port;
	//send pack
	std::string return_msg = send_pack(send_data);
	if(return_msg.find("err") != std::string::npos)
		std::cout << "err";
	else
		std::cout << return_msg;
	return 0;
}
