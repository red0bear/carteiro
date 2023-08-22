#include "basicrypto.h"

basicrypto::basicrypto(){}

void basicrypto::derivekeyandiv(const string& master, const string& salt,unsigned int iterations,SecByteBlock& ekey, unsigned int eksize,SecByteBlock& iv, unsigned int vsize,SecByteBlock& akey, unsigned int aksize)
{
    SecByteBlock tb; 
    SecByteBlock ts(SHA512::DIGESTSIZE);
    SecByteBlock tm(SHA512::DIGESTSIZE);
   
    hash.CalculateDigest(ts, (const CryptoPP::byte*)salt.data(), salt.size());
    
    static const string s1 = masterkey;
    tb = SecByteBlock((const CryptoPP::byte*)master.data(), master.size()) + SecByteBlock((const CryptoPP::byte*)s1.data(), s1.size());
    
    PKCS5_PBKDF2_HMAC<SHA512> pbkdf;
    const CryptoPP::byte unused = 0;
    pbkdf.DeriveKey(tm, tm.size(),
                    unused,
                    tb, tb.size(),
                    ts, ts.size(),
                    100);
    
    static const string s2 = bencryptionkey;
    ekey.resize(eksize);
    tb = tm + SecByteBlock((const CryptoPP::byte*)s2.data(), s2.size());
    pbkdf.DeriveKey(ekey, ekey.size(),
                    unused,
                    tb, tb.size(),
                    ts, ts.size(),
                    100);
    
    static const string s3 = initializationvector;
    iv.resize(vsize);
    tb = tm + SecByteBlock((const CryptoPP::byte*)s3.data(), s3.size());
    pbkdf.DeriveKey(iv, iv.size(),
                    unused,
                    tb, tb.size(),
                    ts, ts.size(),
                    100);
    
    static const string s4 = authenticationkey;
    akey.resize(aksize);
    tb = tm + SecByteBlock((const CryptoPP::byte*)s4.data(), s4.size());
    pbkdf.DeriveKey(akey, iv.size(),
                    unused,
                    tb, tb.size(),
                    ts, ts.size(),
                    100);
}

void basicrypto::printkeyandiv(SecByteBlock& ekey,SecByteBlock& iv,SecByteBlock& akey)
{
    // Print them
    HexEncoder encoder(new FileSink(cout));
    
    cout << "AES key: ";
    encoder.Put(ekey.data(), ekey.size());
    encoder.MessageEnd(); cout << endl;
    
    cout << "AES IV: ";
    encoder.Put(iv.data(), iv.size());
    encoder.MessageEnd(); cout << endl;
    
    cout << "HMAC key: ";
    encoder.Put(akey.data(), akey.size());
    encoder.MessageEnd(); cout << endl;
    
     cout << "AES key: " << ekey.size() <<   "AES IV: " <<  iv.size() << " HMAC key: " << akey.size() << endl;    

}

void basicrypto::setpassword(string pass)
{
	password = pass;
}

void basicrypto::setmessage(string greenbird)
{
	message = greenbird;
}

void basicrypto::setsalt(string salt)
{
	salte = salt;
}

void basicrypto::setmasterkey(string master)
{
	masterkey = master;
}

void basicrypto::encryptionkey(string enckey)
{
	bencryptionkey = enckey;
}

void basicrypto::createderivatedkeys()
{
        derivekeyandiv(password, salte, 100, ekey, ekey.size(), iv, iv.size(), akey, akey.size());
}

void basicrypto::encryption()
{
        CBC_Mode<AES>::Encryption encryptor;
        encryptor.SetKeyWithIV(ekey, ekey.size(), iv, iv.size());
        
        HMAC< SHA256> hmac1;
        hmac1.SetKey(akey, akey.size());
        
                StringSource ss1(message, true /*pumpAll*/,
                         new StreamTransformationFilter(encryptor,
                                                        new HashFilter(hmac1,
                                                                       new StringSink(cipher),
                                                                       true /*putMessage*/)));        
}

void basicrypto::decryption()
{

        CBC_Mode<AES>::Decryption decryptor;
        decryptor.SetKeyWithIV(ekey, ekey.size(), iv, iv.size());
        
        HMAC< SHA256> hmac2;
        hmac2.SetKey(akey, akey.size());  
        
        static const word32 flags = CryptoPP::HashVerificationFilter::HASH_AT_END |
        CryptoPP::HashVerificationFilter::PUT_MESSAGE |
        CryptoPP::HashVerificationFilter::THROW_EXCEPTION;
        
        StringSource ss2(cipher, true /*pumpAll*/,
                         new HashVerificationFilter(hmac2,
                                                    new StreamTransformationFilter(decryptor,
                                                                                   new StringSink(recover)),
                                                    flags));           
}

void basicrypto::debug()
{
    // Print stuff        
   cout << "Password: " << password << endl;
        
   printkeyandiv(ekey, iv, akey);
        
   cout << "Message: " << message << endl;
        
   cout << "Ciphertext+MAC: ";
   HexEncoder encoder(new FileSink(cout));

   encoder.Put((CryptoPP::byte*)cipher.data(), cipher.size());
   encoder.MessageEnd(); cout << endl;
        
   cout << "Recovered: " << recover << endl;

}


