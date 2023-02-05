#include <google/cloud/speech/v1/cloud_speech.grpc.pb.h>
#include <grpcpp/grpcpp.h>
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>

using google::cloud::speech::v1::Speech;
using google::cloud::speech::v1::StreamingRecognizeRequest;
using google::cloud::speech::v1::StreamingRecognizeResponse;
using google::cloud::speech::v1::RecognitionConfig;

class GSession
{
	public:
	
	std::unique_ptr<Speech::Stub> speech;
	grpc::ClientContext context;
	std::unique_ptr<grpc::ClientReaderWriter<StreamingRecognizeRequest,StreamingRecognizeResponse>> streamer;
	std::string file_path;
	
	 GSession();
	~GSession(){};
	
	void on_start(std::string &callId);
	void on_write(std::string &callId);
	void on_read(std::string &callId);
	void on_close(std::string &callId);
};
