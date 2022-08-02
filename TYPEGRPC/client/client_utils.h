extern "C" void send_message(char *httpaddr,bool is_onion, char *uri,char *token,char * mymessage,char *time,char *data,char *type)
{	
	std::random_device rd;
	
	if(is_onion)
	{
	
		ChannelArguments chArgs = ChannelArguments();
		
		if(is_onion)
		{
			chArgs.SetString("grpc.http_proxy",string(uri));
  			//chArgs.SetString("grpc.https_proxy","http://127.0.0.1:8181");
  		}
  		
  		string target_str(httpaddr);
  		CarteiroClient Client(grpc::CreateCustomChannel(target_str, grpc::InsecureChannelCredentials(),chArgs));
  		
  		string checktype(type);
  		
  		std::string token_s(token);
  		std::string mymessage_s(mymessage);
  		std::string time_s(time);
  		std::vector<std::string> mdata;
  		std::string type_s(type);
  
  		if(checktype.compare("TEXT") == 0)
  		{
  			Client.messagesend(token_s,mymessage_s,time_s, mdata,type_s);
  		}
  		else if(checktype.compare("AUDIO") == 0)
  		{
  			std::string line;
			string temp(data);
			temp = temp + to_string(rd());
			
			std::vector<string> values;
			values.push_back("encode");
			values.push_back(string(data));
			values.push_back(temp);
		       	  
		        get_path_base64(values);
		       	  
		       	std::ifstream file_audio(temp);
		       	
		       	if ( file_audio.is_open() )
		       	{
			       	while ( file_audio ) {
					std::getline (file_audio, line);
					//std::cout << file_audio << ": " << file_audio.tellg() << '\n';
					mdata.push_back(line);
				}
		       	}
		       	  
  			Client.messagesend(token_s,mymessage_s,time_s, mdata,type_s);
  		}
	}
	else
	{
	
	}
	
}

extern "C" void transferfile(char *httpaddr,bool is_onion, char *uri,char *token,char *path,char *givenamefile)
{
	std::random_device rd;
	time_t now = time(NULL);

	ChannelArguments chArgs = ChannelArguments();
	
	if(is_onion)
	{
		chArgs.SetString("grpc.http_proxy",string(uri));
	}
	
	chArgs.SetInt("grpc.max_send_message_length",-1);
  		
  	string target_str(httpaddr);
  	CarteiroClient Client(grpc::CreateCustomChannel(target_str, grpc::InsecureChannelCredentials(),chArgs));
  		
  	string data(path);  
		
	string temp(data);
	temp = temp + to_string(rd());

	string line;
	string token_s(token);
	string namefile_s(givenamefile);	
	
	std::vector<string> values;
	values.push_back("encode");
	values.push_back(data);
	values.push_back(temp);
	std::vector<std::string> mdata;	
		
	std::cout << "try encode" << std::endl;
		
        get_path_base64(values);
		
	std::cout << "end encode" << std::endl;       	  
		       	  
	std::cout << "read data" << std::endl; 
		
       	std::ifstream file_data(temp);
		       	
       	if ( file_data.is_open() )
       	{
	       	while ( file_data ) {
			std::getline (file_data, line);
			//std::cout << file_audio << ": " << file_audio.tellg() << '\n';
			mdata.push_back(line);
		}
       	}
       	
       	Client.transferfile(namefile_s,token_s,mdata);	
}

extern "C" char * gen_token_pass()
{    
   std::vector<string> specialchar = {"A","B","C","D","E","F","G","H","I","J","L","M","N","O","P","Q","R","S","T","U","V","X","Z","a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","x","z","0","1","2","3","4","5","6","7","8","9"};
   std::uniform_int_distribution<> data_choice_special(0,specialchar.size()-1);

   std::string value_response;
   std::random_device rd;
   std::mt19937_64 gen;
      
   time_t now = time(NULL);
       
   std::seed_seq seq{time(0),time(0),time(0),time(0),time(0)};
   std::vector<std::uint64_t> seeds(10);
   seq.generate(seeds.begin(), seeds.end());
    
   gen.seed(seq);

   for(int counter = 0; counter < 256; counter++)
   {
	if(counter == 0)
	{
		value_response = specialchar[data_choice_special(gen)];
	}
	else
	{
		value_response = specialchar[data_choice_special(gen)] + value_response;
	}
    }

    value_response = value_response + "\0";

    char * cstr = new char [value_response.length()+1];
    std::strcpy (cstr, value_response.c_str());

    return &cstr[0];

} 

extern "C" char * gen_keys()
{    
   string value_response;
   random_device rd;
   std::mt19937_64 gen;
      
   time_t now = time(NULL);
       
   std::seed_seq seq{time(0),time(0),time(0),time(0),time(0)};
   std::vector<std::uint64_t> seeds(10);
   seq.generate(seeds.begin(), seeds.end());
    
   gen.seed(seq);

   for(int counter = 0; counter < 128; counter++)
   {
	if(counter == 0)
	{
		value_response = specialchar[data_choice_special(gen)];
	}
	else
	{
		value_response = specialchar[data_choice_special(gen)] + value_response;
	}
    }

    value_response = value_response + "\0";

    char * cstr = new char [value_response.length()+1];
    std::strcpy (cstr, value_response.c_str());

    return &cstr[0];

} 

