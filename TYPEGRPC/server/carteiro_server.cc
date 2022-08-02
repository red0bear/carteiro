#include <chrono>
#include <iostream>
#include <memory>
#include <random>
#include <fstream>
#include <string>
#include <thread>
#include <ctime>
#include <experimental/filesystem>

#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>
//JSON
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>


#include "../carteiro.grpc.pb.h"

using namespace grpc;
using namespace std;
namespace fs = std::experimental::filesystem;

// Short alias for this namespace
namespace pt = boost::property_tree;

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using carteiro::Carteiro;
using carteiro::sentmessage;
using carteiro::responsemessage;
using carteiro::sendfile;
using carteiro::responsesendfile;

std::map<string, string> person;
string path; 

#include "server_utils.h"
#include "server_tests.h"

class CarteiroServiceImpl final : public Carteiro::Service {
		

  Status messagesend(ServerContext* context, const sentmessage* request,
			  responsemessage* reply) override {

     if(fs::create_directory(path+"/users/"))
	    std::cout << "Created a directory\n";
     else
	    std::cerr << "Failed to create a directory\n";

     // Create a root
     pt::ptree root;
     ofstream myFile_Handler;
     fstream file;
          
     auto search = person.find(request->token());
     
     if (search != person.end()) 
     {
	     std::cout << "Peer " << context->peer() << endl; 
	     std::cout << "token " << request->token() << endl;
	     std::cout << "mymessage " << request->mymessage() << endl;
	     std::cout << "time " << request->time() << endl;

	     string peer = context->peer();     
	     string token = request->token();
	     string mymessage = request->mymessage();
	     string time = request->time();
	     string message;
	     string datavoice;
	     
	     if(request->type().compare("TEXT") == 0)
	     {
	     	root.put("type", request->type());	
	     	root.put("token", token);
	     	root.put("mymessage", mymessage);
	     	root.put("time", time);


		myFile_Handler.open(path+"/users/" + person[token] + "/messages/" + time +".txt",ios::out);
		
		if(myFile_Handler.is_open())
		{
			pt::write_json(path+"/users/" + person[token] + "/messages/" + time +".txt", root);
		}
		else
		{
		
			if(fs::create_directory(path+"/users/" + person[token]))
			     std::cout << "Created a directory\n";
			else
			     std::cerr << "Failed to create a directory\n";
		     	
			if(fs::create_directory(path+"/users/" + person[token] + "/messages/"))
			     std::cout << "Created a directory\n";
			else
			     std::cerr << "Failed to create a directory\n";
			     
			pt::write_json(path+"/users/" + person[token] + "/messages/" + time +".txt", root);
	     	
	     	}
	     	
	     	reply->set_messageresponse("RECEIVED");
	     }
	     else if(request->type().compare("AUDIO") == 0)
	     {
	     
	     	 file.open(path + "/users/" + person[token] + "/audios/" + time+".txt",ios::out);		
	     		
	     	if(file.is_open())
	     	{}	
	     	else
	     	{	
	     			
	     		if(fs::create_directory(path+"/users/" + person[token]))
			     std::cout << "Created a directory\n";
			else
			     std::cerr << "Failed to create a directory\n";
			     
		     	if(fs::create_directory(path+"/users/" + person[token] + "/audios/"))
			     std::cout << "Created a directory\n";
			else
			     std::cerr << "Failed to create a directory\n";   
			     
			file.open(path + "/users/" + person[token] + "/audios/" + time+".txt",ios::out);
 
		}  
		
				     	 
		  for (long counter = 0; counter < request->data_size(); counter++)
		  {
		  	carteiro::datatransfer mydata = request->data(counter);
		     	 	
		  	if(counter == request->data_size()-1)
		  		file << mydata.data();
		  	else
		  		file << mydata.data() << endl;
		 }
		 
		 file.close(); 
		
		reply->set_messageresponse("RECEIVED");  

	     }
	     else
	     {
	     
	     }
	
     } else 
     {
     	reply->set_messageresponse("");
     	std::cout << "Not found\n";
     }   
       
     return Status::OK;
    }

  Status transferfile(ServerContext* context, const sendfile* request,
			  responsesendfile* reply) override {
    //std::string prefix("Capctha arrive");
	//reply->set_result("0");    
    
	cout << context->peer() << endl;
	string token = request->token();
	
	pt::ptree root;
	pt::ptree datas_node;
	fstream file;
	        
	auto search = person.find(request->token());
	
	if (search != person.end()) 
	{
		     
		root.put("namefile", request->namefile());	
	     	root.put("token", request->token());
	     	
	     	file.open(path + "/users/" + person[token] + "/files/" + request->namefile()+".json",ios::out);		
	     		
	     	if(file.is_open())
	     	{}	
	     	else
	     	{	
	     			
	     		if(fs::create_directory(path+"/users/" + person[token]))
			     std::cout << "Created a directory\n";
			else
			     std::cerr << "Failed to create a directory\n";
			     
		     	if(fs::create_directory(path+"/users/" + person[token] + "/files/"))
			     std::cout << "Created a directory\n";
			else
			     std::cerr << "Failed to create a directory\n";   
			     
			//file.open(path + "/users/" + person[token] + "/files/" + time+".txt",ios::out);
 
		}  			     	 
		file.close();
		
		
		for (long counter = 0; counter < request->data_size(); counter++)
		{
		  	carteiro::datatransfer mydata = request->data(counter);
		     	 	
			 
		  	if(counter == request->data_size()-1)
			{}
		  	else
		  	{
			     	// Create an unnamed node containing the value
				pt::ptree data_node;

				data_node.put("", mydata.data());

				    // Add this node to the list.
				datas_node.push_back(std::make_pair("", data_node));		  	
		  	}
		  	
		}
		 
		root.add_child("data", datas_node);
		pt::write_json(path+"/users/" + person[token] + "/files/" + request->namefile()+".json", root); 
		 //file.close(); 
		 	     	
	}
	else
	{
	
	} 
	     
     return Status::OK;
    }
	
};

extern "C" void  RunServer(char *ipport) {
  std::string server_address(ipport);
  CarteiroServiceImpl service;

  grpc::EnableDefaultHealthCheckService(true);
  grpc::reflection::InitProtoReflectionServerBuilderPlugin();
  ServerBuilder builder;
  // Listen on the given address without any authentication mechanism. 
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.SetMaxReceiveMessageSize(-1);
  builder.SetMaxSendMessageSize(-1);
  // Register "service" as the instance through which we'll communicate with
  // clients. In this case it corresponds to an *synchronous* service.
  builder.RegisterService(&service);
  // Finally assemble the server.
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  // Wait for the server to shutdown. Note that some other thread must be
  // responsible for shutting down the server for this call to ever return.
  server->Wait();
}

int main(int argc, char** argv) {

  test_one();
  RunServer("unix:/home/felipe/Documentos/TORSITES/var/person0.sock");

  return 0;
}

