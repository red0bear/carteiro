//CBC HEADERS
#include "osrng.h"
using CryptoPP::AutoSeededRandomPool;

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include <string>
using std::string;

#include <cstdlib>
using std::exit;

#include "cryptlib.h"
using CryptoPP::Exception;

#include "hex.h"
using CryptoPP::HexEncoder;
using CryptoPP::HexDecoder;

#include "filters.h"
using CryptoPP::StringSink;
using CryptoPP::StringSource;
using CryptoPP::AuthenticatedEncryptionFilter;
using CryptoPP::AuthenticatedDecryptionFilter;

#include "serpent.h"
using CryptoPP::Serpent;

#include "camellia.h"
using CryptoPP::Camellia;

#include "twofish.h"
using CryptoPP::Twofish;

#include "gcm.h"
using CryptoPP::GCM;
using CryptoPP::GCM_TablesOption;

#include "secblock.h"
using CryptoPP::SecByteBlock;

#include "aes.h"
using CryptoPP::AES;

#include "modes.h"
using CryptoPP::CBC_Mode;

class basiccryptoaesgcmfilter 
{
 public:
 //AES GCM

 void initializeserpent();
 void initializecamellia(); 
 void debugenc();
 void debugafter();
 
 void setkey(string ikey);
 void setiv(string iiv);
 
 string getdataencrypted();
 void setdatatoencrypted(string dta);
 void setdatatodecryption(string dta);
 
 void aesgcmencryption();
 void aesgcmdecryption();
 
 private:
 AutoSeededRandomPool prng;
 SecByteBlock key;
 SecByteBlock iv;
 
 string plain = "GCM Mode Test";
 string cipher, encoded, recovered;
};
