#include <iostream> 
#include <string> 
#include <fstream>
#include <thread>
#include <vector>

//CBC HEADERS
#include "cryptlib.h"
using CryptoPP::lword;
using CryptoPP::word32;
using CryptoPP::word64;
using CryptoPP::Exception;
using CryptoPP::BufferedTransformation;
using CryptoPP::AuthenticatedSymmetricCipher;

#include "secblock.h"
using CryptoPP::SecByteBlock;
using CryptoPP::SecBlock;

#include "hex.h"
using CryptoPP::HexEncoder;
using CryptoPP::HexDecoder;

#include "filters.h"
using CryptoPP::Redirector;
using CryptoPP::StringSink;
using CryptoPP::StringSource;
using CryptoPP::StreamTransformationFilter;
using CryptoPP::HashVerificationFilter;
using CryptoPP::HashFilter;

using CryptoPP::AuthenticatedEncryptionFilter;
using CryptoPP::AuthenticatedDecryptionFilter;

#include "files.h"
using CryptoPP::FileSink;

#include "sha.h"
using CryptoPP::SHA256;
using CryptoPP::SHA512;

#include "aes.h"
using CryptoPP::AES;

#include "modes.h"
using CryptoPP::CBC_Mode;

#include "pwdbased.h"
using CryptoPP::PKCS5_PBKDF2_HMAC;

#include "hmac.h"
using CryptoPP::HMAC;

using namespace std;

class basicrypto
{
 public:
 basicrypto();
 
 //CBC STUFF
 void encryptionkey(string enckey);
 void setmasterkey(string master);
 void setpassword(string pass);
 void setmessage(string greenbird);
 void setsalt(string salt);
 void createderivatedkeys();
 void encryption();
 void decryption();
 void debug();
  
 private:
 
 //AES CBC
 string cipher, recover;
 
 string password = "Super secret password";
 string message  = "Now is the time for all good men to come to the aide of their country";
 string salte     = "authenticated encryption example";
 
 string masterkey            = "master key";
 string bencryptionkey        = "encryption key";
 string initializationvector = "initialization vector";
 string authenticationkey    = "authentication key";
 
 SecByteBlock ekey = SecByteBlock(16);
 SecByteBlock iv   = SecByteBlock(16);
 SecByteBlock akey = SecByteBlock(16);
    
 // Temporary salt, stretch size.
 SHA512 hash;
 void derivekeyandiv(const string& master, const string& salt,unsigned int iterations,SecByteBlock& ekey, unsigned int eksize,SecByteBlock& iv, unsigned int vsize,SecByteBlock& akey, unsigned int aksize);
 void printkeyandiv(SecByteBlock& ekey,SecByteBlock& iv,SecByteBlock& akey);

};
