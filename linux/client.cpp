//systemlib
#include<unistd.h>
//std lib
#include"lib/stdc++.h"
//program lib
#include "lib/text-app.h"
#include "cryptopp/eccrypto.h"
#include "cryptopp/cryptlib.h"
#include "cryptopp/osrng.h"
#include "cryptopp/oids.h"
#include "cryptopp/hex.h"
#include "cryptopp/filters.h"
std::string encrypt_ecc(std::string text,std::string pubkey);
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
	if(argc > 4){
		std::cout << "en" << std::endl;
		send_data.message = encrypt_ecc(send_data.message,argv[4]);
	}
	//send pack
	
	std::string return_msg = send_pack(send_data);

	return 0;
}
std::string encrypt_ecc(std::string text,std::string pubkey){
    //basic variable
    std::string cipher;
    try{
    CryptoPP::StringSource key_s(pubkey,true, new CryptoPP::HexDecoder);
    CryptoPP::ECIES<CryptoPP::ECP>::Encryptor en(key_s);
    

    size_t cipher_text_size = en.CiphertextLength(text.size());
    cipher.resize(cipher_text_size);
    CryptoPP::RandomPool rnd;
    en.Encrypt(rnd,(CryptoPP::byte*)text.c_str(),text.size(),(CryptoPP::byte*)cipher.data());
	std::string output;
	std::cout << cipher << std::endl;
	CryptoPP::HexEncoder hexen(new CryptoPP::StringSink(output));
	hexen.Put((CryptoPP::byte*)cipher.data(),cipher.length());
	hexen.MessageEnd();
    return output;
}catch(const CryptoPP::Exception& e){
    std::cerr << e.what() << std::endl;
        return "";
}    
}