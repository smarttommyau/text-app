//std lib
#include "stdc++.h"

//message struct
struct Header{
	std::string request;
	std::string target;
};
struct Data{
	std::string extra;
	std::string data;
};
struct msg{
	std::string login_pass;
	struct Header Header;
	struct Data Data;
};
std::string Assemble_data(struct Data data);
std::string Assemble_msg(struct msg msg){
	std::stringstream str;
	str << "pass->" << msg.login_pass << "<-pass";
	str << "header->";
	str << "request:" << msg.Header.request << ";";
	str << "target:" << msg.Header.target << ";";
	str << "<-header";
	str << "start->" << Assemble_data(msg.Data) << "<-end";
	return str.str();
}

std::string Assemble_data(struct Data data){
	//need encrypte
	std::stringstream str;
	str << "extra->" << data.extra << "<-extra";
	str << "data->" << data.data << "<-data";
	return str.str();
}
