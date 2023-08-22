#include "usergenerate.h"

void usergenerate::generatenewuser()
{       

   SecByteBlock tokensc = SecByteBlock(32);
   prng.GenerateBlock(tokensc, tokensc.size());
   
   SecByteBlock passwordsc = SecByteBlock(16);
   prng.GenerateBlock(passwordsc, passwordsc.size());
   
   SecByteBlock saltesc = SecByteBlock(16);
   prng.GenerateBlock(saltesc, saltesc.size());
   
   SecByteBlock masterkeysc = SecByteBlock(16);
   prng.GenerateBlock(masterkeysc, masterkeysc.size());
   
   SecByteBlock encryptionkeysc = SecByteBlock(16);
   prng.GenerateBlock(encryptionkeysc, encryptionkeysc.size());
   
   SecByteBlock initializationvectorsc = SecByteBlock(16);
   prng.GenerateBlock(initializationvectorsc, initializationvectorsc.size());
   
   SecByteBlock authenticationkeysc = SecByteBlock(16);
   prng.GenerateBlock(authenticationkeysc, authenticationkeysc.size());


   StringSource(tokensc, tokensc.size(), true,
	new HexEncoder(
		new StringSink(token)
	) // HexEncoder
   ); // StringSource
   
   
   StringSource(passwordsc, passwordsc.size(), true,
	new HexEncoder(
		new StringSink(password)
	) // HexEncoder
   ); // StringSource
   
   StringSource(saltesc, saltesc.size(), true,
	new HexEncoder(
		new StringSink(salte)
	) // HexEncoder
   ); // StringSource
   
   StringSource(masterkeysc, masterkeysc.size(), true,
	new HexEncoder(
		new StringSink(masterkey)
	) // HexEncoder
   ); // StringSource 
   
   StringSource(encryptionkeysc, encryptionkeysc.size(), true,
	new HexEncoder(
		new StringSink(encryptionkey)
	) // HexEncoder
   ); // StringSource      

   StringSource(initializationvectorsc, initializationvectorsc.size(), true,
	new HexEncoder(
		new StringSink(initializationvector)
	) // HexEncoder
   ); // StringSource
   
   StringSource(authenticationkeysc, authenticationkeysc.size(), true,
	new HexEncoder(
		new StringSink(authenticationkey)
	) // HexEncoder
   ); // StringSource
    
   for(int counter = 0 ; counter < 3; counter++ )
   { 
	   SecByteBlock ekey = SecByteBlock(16);
	   prng.GenerateBlock(ekey, ekey.size());
	   
	   SecByteBlock ivcbc   = SecByteBlock(16);
	   prng.GenerateBlock(ivcbc, ivcbc.size());
	   
	   SecByteBlock akey = SecByteBlock(16);
	   prng.GenerateBlock(akey, akey.size()); 
	 
	 
	   //ekey
	   StringSource(ekey, ekey.size(), true,
		new HexEncoder(
			new StringSink(cbcekey)
		) // HexEncoder
	   ); // StringSource
	  

	  //
	  StringSource(ivcbc, ivcbc.size(), true,
	 	new HexEncoder(
			new StringSink(cbciv)
		) // HexEncoder
	  ); // StringSource

	  
	  StringSource(akey, akey.size(), true,
	 	new HexEncoder(
			new StringSink(cbcakey)
		) // HexEncoder
	  ); // StringSource     
	  
	  cbcekeyv.push_back(cbcekey);
	  cbcivv.push_back(cbciv);
	  cbcakeyv.push_back(cbcakey);
	  
	  cbcekey = "";	   
	  cbciv = "";
	  cbcakey="";
  }
  
  //AES GCM
  
  for(int counter = 0 ; counter < 3; counter++ )
  {
   	SecByteBlock ivl   = SecByteBlock(16);
  	prng.GenerateBlock(ivl, ivl.size());
  	
   	SecByteBlock keyl = SecByteBlock(16);
  	prng.GenerateBlock(keyl, keyl.size());
	
	StringSource(keyl, keyl.size(), true,
	 	new HexEncoder(
			new StringSink(GCMkey)
		) // HexEncoder
	  ); // StringSour
	  
	StringSource(ivl, ivl.size(), true,
	 	new HexEncoder(
			new StringSink(GCMiv)
		) // HexEncoder
	  ); // StringSour 
	  
	  key.push_back(GCMkey);
	  iv.push_back(GCMiv);
	  
	  GCMkey="";
	  GCMiv=""; 	  	
  }
  
  // PUSH DATA
  
  newuser.settoken(token);
  
  newuser.setpassword(password);
  newuser.setsalt(salte);
  newuser.setmasterkey(masterkey);
  newuser.setencryptionkey(encryptionkey);
  newuser.setinitializationvector(initializationvector);
  newuser.setauthenticationkey(authenticationkey);
  
  //newuser.AddCbcKey(cbcekey);
  //newuser.AddCbcIv(cbciv);
  //newuser.AddCbcaKey(cbcakey);
 
  //cout << "Token : " << token << endl;
 
  //cout << "CBC password: " << password << endl;
  //cout << "CBC salte: " << salte << endl;
  //cout << "CBC masterkey: " << masterkey << endl;
  //cout << "CBC encryptionkey: " << encryptionkey << endl;
  //cout << "CBC initializationvector: " << initializationvector << endl;
  //cout << "CBC authenticationkey: " << authenticationkey << endl;
 
  //cout << "CBC ekey: " << cbcekey << endl; 
  //cout << "CBC iv: " << cbciv << endl;
  //cout << "CBC akey: " << cbcakey << endl;
 
}

char *usergenerate::getjsongenerateduser(string name , string phone, string date)
{

     // Create a root
     pt::ptree root;
     pt::ptree children;
     pt::ptree child1;
     pt::ptree child2;
     pt::ptree child3;
     
     
     root.put("useruuid", newuser.gettoken());
     
     root.put("name", name);
     root.put("phone", phone);
     root.put("date", date);
     
     
     root.put("password", newuser.getpassword());
     root.put("salte", newuser.getsalt());
     root.put("masterkey", newuser.getmasterkey());
     root.put("encryptionkey", newuser.getencryptionkey());
     root.put("initializationvector", newuser.getinitializationvector());
     root.put("authenticationkey", newuser.getauthenticationkey());     
     
     child1.put("", cbcekeyv[0]);
     child2.put("", cbcekeyv[1]);
     child3.put("", cbcekeyv[2]);
          
     children.push_back(std::make_pair("", child1));
     children.push_back(std::make_pair("", child2));
     children.push_back(std::make_pair("", child3));
     
     root.add_child("cbcekey", children);
     
     children.clear();
     child1.clear();
     child2.clear();
     child3.clear();
  
     child1.put("", cbcivv[0]);
     child2.put("", cbcivv[1]);
     child3.put("", cbcivv[2]);
        
     children.push_back(std::make_pair("", child1));
     children.push_back(std::make_pair("", child2));
     children.push_back(std::make_pair("", child3));
     
     root.add_child("cbciv", children);
     
     children.clear();
     child1.clear();
     child2.clear();
     child3.clear();
     
     child1.put("", cbcakeyv[0]);
     child2.put("", cbcakeyv[1]);
     child3.put("", cbcakeyv[2]);
          
     children.push_back(std::make_pair("", child1));
     children.push_back(std::make_pair("", child2));
     children.push_back(std::make_pair("", child3));

     root.add_child("cbcakey", children); 
         
     children.clear();
     child1.clear();
     child2.clear();
     child3.clear();
     
     child1.put("", key[0]);
     child2.put("", key[1]);
     child3.put("", key[2]);
     
     children.push_back(std::make_pair("", child1));
     children.push_back(std::make_pair("", child2));
     children.push_back(std::make_pair("", child3));
     
     root.add_child("gcmkey", children);  
     
     children.clear();
     child1.clear();
     child2.clear();
     child3.clear();

     child1.put("", iv[0]);
     child2.put("", iv[1]);
     child3.put("", iv[2]);
               
     children.push_back(std::make_pair("", child1));
     children.push_back(std::make_pair("", child2));
     children.push_back(std::make_pair("", child3));
     
     
     root.add_child("gcmiv", children);        
     
     write_json(newuser.gettoken(), root);     

     std::stringstream ss;
     write_json(ss, root);
     string result  = ss.str();
     
     char * cstr = new char [result.length()+1];
     std::strcpy (cstr, result.c_str());     
   
     return &cstr[0];
}
