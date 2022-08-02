
/*this test didnt worked well*/
void test_one()
{
  ChannelArguments chArgs = ChannelArguments();
  chArgs.SetInt("GRPC_COMPRESSION_CHANNEL_DEFAULT_ALGORITHM",1);
  chArgs.SetInt("GRPC_ARG_ENABLE_HTTP_PROXY",1);
  chArgs.SetInt("GRPC_ARG_ENABLE_HTTPS_PROXY",1);
  chArgs.SetString("grpc.http_proxy","http://127.0.0.1:8080");
  chArgs.SetString("grpc.https_proxy","http://127.0.0.1:8181");
      
  string target_str("");
  CarteiroClient Client(grpc::CreateCustomChannel(target_str, grpc::InsecureChannelCredentials(),chArgs));
  
  std::string token("ASDFASDF");
  std::string mymessage("HELLO MESSAGE");
  std::string time("1223344556677");
  std::vector<std::string> mdata;
  std::string type("TEXT");
  
  Client.messagesend(token,mymessage,time, mdata,type);
}


void test_two()
{
	std::random_device rd;
	time_t now = time(NULL);

	ChannelArguments chArgs = ChannelArguments();
	chArgs.SetString("grpc.http_proxy","http://127.0.0.1:8080");
  	//chArgs.SetString("grpc.https_proxy","http://127.0.0.1:8181");
  		
  	string target_str("");
  	CarteiroClient Client(grpc::CreateCustomChannel(target_str, grpc::InsecureChannelCredentials(),chArgs));
  		
  	string data("name_data_with_full_ptah.file");	
  		
  	
  	string token("Scammers only steal time from feps");
  	string mymessage("this is a wornderfull test");
  	string time(to_string(now));
  	
  	string type("TEXT");
  	
  	std::string token_s(token);
  	std::string mymessage_s(mymessage);
  	std::string time_s(time);
  	std::vector<std::string> mdata;
  	std::string type_s(type);
  
  	
  	if(type.compare("TEXT") == 0)
  	{
  		Client.messagesend(token_s,mymessage_s,time_s, mdata,type_s);
  	}
  
}

void test_three()
{

	std::random_device rd;
	time_t now = time(NULL);

	ChannelArguments chArgs = ChannelArguments();
	chArgs.SetString("grpc.http_proxy","http://127.0.0.1:8282");
  	//chArgs.SetString("grpc.https_proxy","http://127.0.0.1:8181");
  		
  	string target_str("");
  	CarteiroClient Client(grpc::CreateCustomChannel(target_str, grpc::InsecureChannelCredentials(),chArgs));
  		
  	string data("name_data_with_full_ptah.file");  		
  	
  	string token("feps");
  	string mymessage("");
  	string time(to_string(now));
  	
  	string type("AUDIO");
  	
  	std::string token_s(token);
  	std::string mymessage_s(mymessage);
  	std::string time_s(time);
  	std::vector<std::string> mdata;
  	std::string type_s(type);
  	
  	if(type.compare("AUDIO") == 0)
  	{
  		std::string line;
		string temp(data);
		temp = temp + to_string(rd());
		
		std::vector<string> values;
		values.push_back("encode");
		values.push_back(string(data));
		values.push_back(temp);
		
		std::cout << "try encode" << std::endl;
		
	        get_path_base64(values);
		
		std::cout << "end encode" << std::endl;       	  
		       	  
		std::cout << "read data" << std::endl; 
		
	       	std::ifstream file_audio(temp);
		       	
	       	if ( file_audio.is_open() )
	       	{
		       	while ( file_audio ) {
				std::getline (file_audio, line);
				//std::cout << file_audio << ": " << file_audio.tellg() << '\n';
				mdata.push_back(line);
			}
	       	}
		       	  
		std::cout << "end push data" << mdata.size() << std::endl; 
		       	  
 		Client.messagesend(token_s,mymessage_s,time_s, mdata,type_s);
 	}
}


void test_four()
{

	std::random_device rd;
	time_t now = time(NULL);

	ChannelArguments chArgs = ChannelArguments();
	chArgs.SetString("grpc.http_proxy","http://127.0.0.1:8080");
	chArgs.SetInt("grpc.max_send_message_length",-1);
  	//chArgs.SetString("grpc.https_proxy","http://127.0.0.1:8181");
  		
  	string target_str("");
  	CarteiroClient Client(grpc::CreateCustomChannel(target_str, grpc::InsecureChannelCredentials(),chArgs));
  		
  	string data("name_data_with_full_ptah.file");  
		
	string temp(data);
	temp = temp + to_string(rd());

	string line;
	string token("feps");
	string namefile("name_file_only");
	
	
	std::vector<string> values;
	values.push_back("encode");
	values.push_back(string(data));
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
       	
       	Client.transferfile(namefile,token,mdata);
}
