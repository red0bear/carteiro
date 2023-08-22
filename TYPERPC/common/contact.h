#include <iostream> 
#include <string> 
#include <fstream>
#include <thread>
#include <vector>
#include <ctime>
#include <sstream>

//JSON
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

// Short alias for this namespace
namespace pt = boost::property_tree;
using namespace std;

class contact 
{
  public:
  
  // AES GCM  
 
  void setcryptotype(string dta){cryptotype =dta;}
  string getcryptotype(){return cryptotype;}  
  
  vector<string> getkey(){return key;}
  void addkey(string dta){key.push_back(dta);}
  void clearkey(){key.clear();}
  
  vector<string> getiv(){return iv;}
  void addiv(string dta){iv.push_back(dta);}
  void cleariv(){iv.clear();}    
    
  //AES CBC  
    
  void setpassword(string dta){password =dta;}
  string getpassword(){return password;}    
 
  void setsalt(string dta){salte =dta;}
  string getsalt(){return salte;}
  
  void setmasterkey(string dta){masterkey =dta;}
  string getmasterkey(){return masterkey;}
  
  void setencryptionkey(string dta){encryptionkey =dta;}
  string getencryptionkey(){return encryptionkey;}
  
  void setinitializationvector(string dta){initializationvector =dta;}
  string getinitializationvector(){return initializationvector;}       
  
  void setauthenticationkey(string dta){authenticationkey =dta;}
  string getauthenticationkey(){return authenticationkey;}  
   
  vector<string> getcbckey(){return cbcekey;} 
  void addcbckey(string dta){cbcekey.push_back(dta);}
  void clearcbckey(){cbcekey.clear();}
  
  vector<string> getcbciv(){return cbciv;}
  void addcbciv(string dta){cbciv.push_back(dta);}
  void clearcbciv(){cbciv.clear();} 
  
  vector<string> getcbcakey(){return cbcakey;}
  void addcbcakey(string dta){cbcakey.push_back(dta);}
  void ClearCbcaKey(){cbcakey.clear();}   
   
    
  //GENERAL  
  
  void AddMessage(string dta){message.push_back(dta);}
  void ClearMessage(string dta){message.clear();}
  vector<string> GetChumkMessages(long datestart,long dateend)
  {
  	vector<string> result;
  	for(long counter = 0 ;counter < (long)message.size(); counter++ )
  	{
		std::stringstream ss;
		ss << message[counter];
		boost::property_tree::ptree pt;
		boost::property_tree::read_json(ss, pt);
		
		
		if(pt.get<long>("time") >= datestart && pt.get<long>("time") <= dateend)
		{
			result.push_back(message[counter]);
		}				
  	}
  	
  	return result;
  }
  //
  
  void SetName(string dta){name =dta;}
  string GetName(){return name;}
  
  void SetOnion(string dta){onion =dta;}
  string GetOnion(){return onion;}
  
  void SetPort(string dta){port =dta;}
  string GetPort(){return port;} 
  
  void setAllowMessages(){allow_messages=!allow_messages;}
  bool IsAllowMessages(){return allow_messages;} 
  
  void SetAllowImages(){allow_images=!allow_images;}
  bool IsAllowImages(){return allow_images;}    
    
  void setallowlargesFiles(){allow_large_files=!allow_large_files;}
  bool isallowlargesFiles(){return allow_large_files;} 
  
  void settoken(string dta){token = dta;}
  string gettoken(){return token;}     
    
  private:
  
  //AES GCM   
  vector<string> key;
  vector<string> iv;

  //AES CBC
  string password;
  string salte;
  
  string masterkey;
  string encryptionkey;
  string initializationvector;
  string authenticationkey;
  
  vector<string> cbcekey;
  vector<string> cbciv;
  vector<string> cbcakey;

  //GENERAL 
  
  string token;
  
  string name;
  string onion;
  string port; 
  
  string cryptotype;
  
  //NEED BE USED TO JSON
  vector<string> message;
    
  bool allow_messages;
  bool allow_images;
  bool allow_large_files;

};
