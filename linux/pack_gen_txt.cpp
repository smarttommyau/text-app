#include"lib/stdc++.h"
#include"lib/text-app.h"
int main(int argc,char const *argv[]){
	struct msg msg;
	std::cout << "pass:" << std::endl;
	std::cin >> msg.login_pass;
	std::cout << "header:" << std::endl << "request:";
	std::cin >> msg.Header.request;
	std::cout << "target:";
	std::cin >> msg.Header.target;
	std::cout << "body:" << std::endl << "extra:";
	std::cin >> msg.Data.extra;
	std::cout << "data:";
	std::cin >> msg.Data.data;
	std::string str = Assemble_msg(msg);
	std::ofstream file(argv[1]);
	file << str;
	file.close();
	return 0;
}
