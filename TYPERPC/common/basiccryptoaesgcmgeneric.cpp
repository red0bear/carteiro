#include "basiccryptoaesgcmgeneric.h"

void basiccryptoaesgcmfilter::initializeserpent()
{
	 key = SecByteBlock(Serpent::DEFAULT_KEYLENGTH);
	 prng.GenerateBlock(key, key.size());
	 iv = SecByteBlock(Serpent::BLOCKSIZE);
	 prng.GenerateBlock(iv, iv.size());
	 
	 //cout << "key length: " << Serpent::DEFAULT_KEYLENGTH << endl;
	 //cout << "key length (min): " << Serpent::MIN_KEYLENGTH << endl;
	 //cout << "key length (max): " << Serpent::MAX_KEYLENGTH << endl;
	 //cout << "block size: " << Serpent::BLOCKSIZE << endl;
}

void basiccryptoaesgcmfilter::initializecamellia()
{
	 key = SecByteBlock(Camellia::DEFAULT_KEYLENGTH);
	 prng.GenerateBlock(key, key.size());
	 iv = SecByteBlock(Camellia::BLOCKSIZE);
	 prng.GenerateBlock(iv, iv.size());
	 
	 //cout << "key length: " << Camellia::DEFAULT_KEYLENGTH << endl;
	 //cout << "key length (min): " << Camellia::MIN_KEYLENGTH << endl;
	 //cout << "key length (max): " << Camellia::MAX_KEYLENGTH << endl;
	 //cout << "block size: " << Camellia::BLOCKSIZE << endl;
}

void basiccryptoaesgcmfilter::debugenc()
{
	// Pretty print key
	encoded.clear();
	StringSource(key, key.size(), true,
		new HexEncoder(
			new StringSink(encoded)
		) // HexEncoder
	); // StringSource
	cout << "key: " << encoded << endl;

	// Pretty print iv
	encoded.clear();
	StringSource(iv, iv.size(), true,
		new HexEncoder(
			new StringSink(encoded)
		) // HexEncoder
	); // StringSource
	cout << "iv: " << encoded << endl;

}

void basiccryptoaesgcmfilter::debugafter()
{
	// Pretty print
	encoded.clear();
	StringSource ss4(cipher, true,
		new HexEncoder(
			new StringSink(encoded)
		) // HexEncoder
	); // StringSource
	cout << "cipher text: " << encoded << endl;
}

string basiccryptoaesgcmfilter::getdataencrypted()
{
 	return cipher;
}

void basiccryptoaesgcmfilter::setdatatoencrypted(string dta)
{
	plain = dta;
}

void basiccryptoaesgcmfilter::setdatatodecryption(string dta)
{
	cipher = dta;
}

void basiccryptoaesgcmfilter::setkey(string ikey)
{
	string decoded;
	   
	StringSource ss(ikey, true,
	    new HexDecoder(
		new StringSink(decoded)
	    ) // HexDecoder
	); // StringSource
	
	key = SecByteBlock(reinterpret_cast<const CryptoPP::byte*>(&decoded[0]), decoded.size());
}

void basiccryptoaesgcmfilter::setiv(string iiv)
{
	string decoded;
	   
	StringSource ss(iiv, true,
	    new HexDecoder(
		new StringSink(decoded)
	    ) // HexDecoder
	); // StringSource
	
	iv = SecByteBlock(reinterpret_cast<const CryptoPP::byte*>(&decoded[0]), decoded.size());
}

//AES GCM 
void basiccryptoaesgcmfilter::aesgcmencryption()
{
	try
	{
		cout << "plain text: " << plain << endl;

		GCM< AES >::Encryption e;
		e.SetKeyWithIV(key, key.size(), iv, iv.size());

		// The StreamTransformationFilter adds padding
		//  as required. GCM and CBC Mode must be padded
		//  to the block size of the cipher.
		StringSource(plain, true, 
			new AuthenticatedEncryptionFilter(e,
				new StringSink(cipher)
			) // StreamTransformationFilter      
		); // StringSource
	}
	catch(const CryptoPP::Exception& e)
	{
		cerr << e.what() << endl;
		exit(1);
	}

}

void basiccryptoaesgcmfilter::aesgcmdecryption()
{
	try
	{
		GCM< CryptoPP::AES >::Decryption d;
		d.SetKeyWithIV(key, key.size(), iv, iv.size());

		// The StreamTransformationFilter removes
		//  padding as required.
		StringSource s(cipher, true, 
			new AuthenticatedDecryptionFilter(d,
				new StringSink(recovered)
			) // StreamTransformationFilter
		); // StringSource

		cout << "recovered text: " << recovered << endl;
	}
	catch(const CryptoPP::Exception& e)
	{
		cerr << e.what() << endl;
		exit(1);
	}
}
