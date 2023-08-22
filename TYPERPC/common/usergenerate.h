#include <iostream> 
#include <vector>
#include <string> 
#include <fstream>

#include "osrng.h"
using CryptoPP::AutoSeededRandomPool;

#include "secblock.h"
using CryptoPP::SecByteBlock;

#include "hex.h"
using CryptoPP::HexEncoder;
using CryptoPP::HexDecoder;

#include "serpent.h"
using CryptoPP::Serpent;

#include "camellia.h"
using CryptoPP::Camellia;

#include "twofish.h"
using CryptoPP::Twofish;

#include "filters.h"
using CryptoPP::StringSink;
using CryptoPP::StringSource;

//JSON
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

// Short alias for this namespace
namespace pt = boost::property_tree;

using namespace std;

#include "contact.h"

class usergenerate
{	
	public:
	void generatenewuser();
	char *getjsongenerateduser(string name , string phone, string date);
	
	private:
	
	contact newuser;
	
	//AES GCM
	vector<string> key;
	vector<string> iv;
	   
	string GCMkey;
	string GCMiv;
	  
	//CBC
	string password;
	string salte;
	  
	string masterkey;
	string encryptionkey;
	string initializationvector;
	string authenticationkey;
	  
	string cbcekey;
	string cbciv;
	string cbcakey;  
	   
	vector<string> cbcekeyv;
	vector<string> cbcivv;
	vector<string> cbcakeyv;   
	   
	//Token
	string token;	
	
	AutoSeededRandomPool prng;
};
