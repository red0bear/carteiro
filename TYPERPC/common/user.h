class user
{  
  public:

  void setname(std::string value);
  std::string getname();
  void setphone(std::string value);
  std::string getphone();
  void setaddress(std::string value);
  std::string getaddress(); 
  void setemail(std::string value);
  std::string getemail();
  void setuuid(std::string value);
  std::string getuuid();  
  void setkey(std::string value); 
  void setiv(std::string value);
  void lockdown();
  
 
  private: 
  std::string name;
  std::string address;
  std::string email;
  std::string uuid;
  std::string phone;

  bool lock = false;
  
  std::vector<std::string> key;
  std::vector<std::string> iv;
  
} ;
