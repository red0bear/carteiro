class CarteiroClient {
 public:
  CarteiroClient(std::shared_ptr<Channel> channel)
      : stub_(Carteiro::NewStub(channel)) {}

  // Assembles the client's payload, sends it and presents the response back
  // from the server.
  std::string messagesend(const std::string& token,const std::string& mymessage,const std::string& time,const std::vector<string>& data,const std::string& type) {
    // Data we are sending to the server.
    sentmessage request;
    request.set_token(token);
    request.set_mymessage(mymessage);
    request.set_time(time);
    
   // std::cout << " prepare " <<  data.size() <<std::endl;
    
    for(int counter =0 ; counter < data.size(); counter++) 
    {
    	carteiro::datatransfer *mydata = request.add_data();
    	mydata->set_data(data[counter]);
      	
    	//std::cout << " counter " << counter << std::endl;
    }
    
  //  std::cout << " end prepare " << std::endl;
    
    request.set_type(type);

    // Container for the data we expect from the server.
    responsemessage reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    // The actual RPC.
    Status status = stub_->messagesend(&context, request, &reply);

    // Act upon its status.
    if (status.ok()) {
    	std::cout << reply.messageresponse() << std::endl;
      return reply.messageresponse();
    } else {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return "RPC failed";
    }
  }

  // Assembles the client's payload, sends it and presents the response back
  // from the server.
  std::string transferfile(const std::string& namefile, const std::string& token ,const std::vector<string>& data) {
    // Data we are sending to the server.
    sendfile request;
    request.set_namefile(namefile);
    request.set_token(token);

    
    for(int counter =0 ; counter < data.size(); counter++) 
    {
    	carteiro::datatransfer *mydata = request.add_data();
    	mydata->set_data(data[counter]);
      	
    	//std::cout << " counter " << counter << std::endl;
    }

    // Container for the data we expect from the server.
    responsesendfile reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    // The actual RPC.
    Status status = stub_->transferfile(&context, request, &reply);

    // Act upon its status.
    if (status.ok()) {
      return reply.messageresponsesnd();
    } else {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return "RPC failed";
    }
 }

 private:
  std::unique_ptr<Carteiro::Stub> stub_;
};
