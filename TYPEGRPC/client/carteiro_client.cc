#include <grpc/support/port_platform.h>

#include <chrono>
#include <iostream>
#include <memory>
#include <random>
#include <vector>
#include <string>
#include <thread>
#include <fstream>

#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>


#include "../carteiro.grpc.pb.h"

using namespace grpc;


using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReader;
using grpc::ClientReaderWriter;
using grpc::ClientWriter;
using grpc::Status;

using carteiro::Carteiro;
using carteiro::sentmessage;
using carteiro::responsemessage;
using carteiro::sendfile;
using carteiro::responsesendfile;

#include "../base64/base64.h"
#include "client_stub_class.h"
#include "client_utils.h"
#include "src/core/lib/channel/channel_args.h"

#include "client_test.h"

int main(int argc, char** argv) 
{

	test_four();

	return 0;
}
