#include "SPclass.h"

auto const rpcJson = R"({"message": "StartRecognition","audio_format": {"type": "file"},"transcription_config": {"language": "en","enable_partials": false}})";
auto const rpcJson1 = R"({"message":"EndOfStream","last_seq_no": 4})";

void Session::InitializeMapValues()
{
	SP_MSG["RecognitionStarted"] = RecognitionStarted;
	SP_MSG["AudioAdded"] = AudioAdded ;
	SP_MSG["AddPartialTranscript"] = AddPartialTranscript;
	SP_MSG["AddTranscript"] = AddTranscript;
	SP_MSG["EndOfTranscript"] = EndOfTranscript;
	SP_MSG["Info"] = Info;
	SP_MSG["Warning"] = Warning;
	SP_MSG["Error"] = Error;
}

std::string Session::on_message(boost::beast::multi_buffer &b, std::string &callId)
{
	Document document;
	
	std::string s = boost::beast::buffers_to_string(b.data());
	
	if(document.ParseInsitu((char *)s.c_str()).HasParseError())
	{
		printf("parse json error");
		//return 1;
	}

	printf("\nParsing to document succeeded.\n");

	assert(document.IsObject()); 

	assert(document.HasMember("message"));

	assert(document["message"].IsString());

	printf("message = %s\n", document["message"].GetString());
	
	std::string k = document["message"].GetString();
	
	std::cout<<k<<std::endl;
	
	switch(SP_MSG[k])
	{
		case RecognitionStarted:
		{
				printf("\n\nRecognition Started, %s \n\n",callId.c_str());
				
				return k;
				//break;
		}
		case AudioAdded:
		{
				printf("\n\nAudio Added, %s \n\n",callId.c_str());
				
				return k;
				//break;
		}
		case AddPartialTranscript:
		{
				printf("\n\n Add Partial Transcript, %s \n\n",callId.c_str());
				
				return k;
				//break;
		}
		case AddTranscript:
		{
				printf("\n\nAdd Transcript, %s \n\n", callId.c_str());
				
				return k;
				//break;
		}
		case EndOfTranscript:
		{
				printf("\n\nEnd of transsript, %s \n\n", callId.c_str());
				
				return k;
				//break;
		}
		case Info:
		{
				printf("\n\n Info, %s \n\n", callId.c_str());
				
				return k;
				//break;
		}
		case Warning:
		{
				printf("\n\n Warning, %s \n\n", callId.c_str());
				
				return k;
				//break;
		}
		case Error:
		{
				printf("\n\n Error, %s \n\n", callId.c_str());
				
				return k;
				//break;
		}		
		default:
		{
				printf("\n\n default message, %s \n\n", callId.c_str());
				break;
		}	
	}
}

void Session::Initialise(std::string &callId)
{
	auto const host = "rtthha-speech.unifiedring.co.uk";
	auto const port = "9000";
	
	load_root_certificates(ctx);
	
	auto const results = resolver.resolve(host, port);
	
	boost::asio::connect(ws.next_layer().next_layer(), results.begin(), results.end());
	
	ws.next_layer().handshake(ssl::stream_base::client);
	
	ws.handshake(host, "/v2");
	
	std::cout << "!Connection Established" <<callId<< std::endl;
	
}

void Session::on_start(std::string &callId)
{
	ws.binary(false);
	ws.write(boost::asio::buffer(std::string(rpcJson)));
	
	ws.read(b);
	
	std::cout << boost::beast::buffers(b.data()) << callId << std::endl;
	
}

void Session::on_write(std::string &callId)
{
	std::ifstream file_stream(file_path.c_str(), std::ios::binary);
	//std::ifstream file_stream("/home/Naveen/thank_you.wav", std::ios::binary);
	auto constexpr kChunkSize = 64 * 1024;
	std::vector<char> chunk(kChunkSize);
	
	int count = 0;
	
	while(true)
	{
		
		file_stream.read(chunk.data(), chunk.size());
		
		auto const bytes_read = file_stream.gcount();
		
		if (bytes_read > 0)
		{
			ws.binary(true);
			ws.write(boost::asio::buffer(chunk.data(), bytes_read));
			printf("\n\n\n  xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxAudio Added, %s \n\n\n",callId.c_str());
			printf("%d",count);
			count++;
			
	/*		if(count == 40)
			{
			ws.binary(false);
			ws.write(boost::asio::buffer(std::string(rpcJson1)));
			//break;		
			} */
		}

#if 1
		if(!file_stream)
		{
			ws.binary(false);
			ws.write(boost::asio::buffer(std::string(rpcJson1)));
			break;
		}
#endif

	}
}

void Session::on_read(std::string &callId)
{
	InitializeMapValues();
	
	while(1)
	{
	b.consume(b.size());
	ws.read(b);
	
	std::cout << boost::beast::buffers(b.data()) << callId << std::endl;
	
	std::string k = on_message(b, callId);
		
		if(strcmp(k.c_str(),"EndOfTranscript") == 0)
		{
			printf("end of transcript arrived, %s \n", callId.c_str());
			//ws.close(websocket::close_code::normal);
			on_close(callId);
			break;
		}
	}
}

void Session::on_close(std::string &callId)
{
	ws.close(websocket::close_code::normal);
	printf("\n\n websocket connection closed, %s \n\n", callId.c_str());
}

