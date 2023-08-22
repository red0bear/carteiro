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

#include "cryptopp/hex.h"
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

//AES GCM HEADERS

#include "gcm.h"
using CryptoPP::GCM;
using CryptoPP::GCM_TablesOption;

#include <assert.h>

using namespace std;
using std::string;

class basiccryptoaesgcm 
{
 public:
 //AES GCM
 void setkey(CryptoPP::byte key[32]);
 void setiv(CryptoPP::byte Iv[12]);
 void setadata(string data);
 void setpdata(string data);
 void setcipher(string cip);
 void setencode(string enc);
 void setrdata(string rdat);
 void setrpdata(string rdat);
 
 void aesgcmencryption();
 void aesgcmdecryption();
 private:
   //AES GCM
  //KEY 0000000000000000000000000000000000000000000000000000000000000000
  //IV  000000000000000000000000
  //HDR 00000000000000000000000000000000
  //PTX 00000000000000000000000000000000
  //CTX cea7403d4d606b6e074ec5d3baf39d18
  //TAG ae9b1771dba9cf62b39be017940330b4

  // Test Vector 003
  CryptoPP::byte key[32] = {0x00};
  //memset( key, 0, sizeof(key) );
  CryptoPP::byte iv[12] = {0x00};
  //memset( iv, 0, sizeof(iv) );

  string adata = string( 16, (char)0x00 );
  string pdata = string( 16, (char)0x00 );

  const int TAG_SIZE = 16;

  // Encrypted, with Tag
  string cipher, encoded;

  // Recovered
  string radata, rpdata;
};
