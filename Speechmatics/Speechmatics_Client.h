#include "/home/Naveen/Speechmatics-webscoket/boost_1_66_0/libs/beast/example/common/root_certificates.hpp"

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/beast/websocket/ssl.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/stream.hpp>
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include <cstdio>
#include <thread>

using namespace rapidjson;
using tcp = boost::asio::ip::tcp;               // from <boost/asio/ip/tcp.hpp>
namespace ssl = boost::asio::ssl;       // from <boost/asio/ssl.hpp>
namespace websocket = boost::beast::websocket;  // from <boost/beast/websocket.hpp>

enum SP_msg_value{	 
	 RecognitionStarted,
	 AudioAdded,
	 AddPartialTranscript,
	 AddTranscript,
	 EndOfTranscript,
	 Info,
	 Warning,
	 Error,
};

static std::map<std::string, SP_msg_value> SP_MSG;

class Session
{

private:

boost::asio::io_context ioc;
ssl::context ctx{ssl::context::tlsv12_client};
websocket::stream<ssl::stream<tcp::socket>> ws{ioc, ctx};
tcp::resolver resolver{ioc};
boost::beast::multi_buffer b;

public:

void InitializeMapValues();
std::string on_message(boost::beast::multi_buffer &b, std::string &callId);

//void Initialise(websocket::stream<ssl::stream<tcp::socket>> &ws, tcp::resolver &resolver)
void Initialise(std::string &callId);

void on_start(std::string &callId);

void on_write(std::string &callId);

void on_read(std::string &callId);

void on_close(std::string &callId);

std::string file_path;
};

