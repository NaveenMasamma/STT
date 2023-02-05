#include "Stream.h"


GSession::GSession()
{
	//client = speech::SpeechClient(speech::MakeSpeechConnection());
	auto creds = grpc::GoogleDefaultCredentials();
	auto channel = grpc::CreateChannel("speech.googleapis.com", creds);
	speech = Speech::NewStub(channel);
}




void GSession::on_start(std::string &callId)
{
	printf("\nStart connection %s \n", callId.c_str());
try{

#if 1
StreamingRecognizeRequest request;
auto* streaming_config = request.mutable_streaming_config();

RecognitionConfig* config=streaming_config->mutable_config();
config->set_language_code("en-UK");
config->set_sample_rate_hertz(8000);  
config->set_encoding(RecognitionConfig::LINEAR16);
streamer = speech->StreamingRecognize(&context);
//streaming_config->set_interim_results(true);
// streaming_config->set_single_utterance(true);
  streamer->Write(request);

}
 catch (std::exception const& ex) {
  std::cerr << "Standard C++ exception thrown: " << ex.what() << "\n";
  //return 1;
}
#endif
}

void GSession::on_write(std::string &callId)
{
	printf("\nwrite connection %s \n", callId.c_str());
try{

#if 1
StreamingRecognizeRequest request;
  std::ifstream file_stream(file_path.c_str());
  const size_t chunk_size = 64 * 1024;
  std::vector<char> chunk(chunk_size);
  while (true) {
    // Read another chunk from the file.
    std::streamsize bytes_read =
        file_stream.rdbuf()->sgetn(&chunk[0], chunk.size());
    // And write the chunk to the stream.
    request.set_audio_content(&chunk[0], bytes_read);
    std::cout << "Sending " << bytes_read / 1024 << "k bytes." << std::endl;
    streamer->Write(request);
    if (bytes_read < chunk.size()) {
      // Done reading everything from the file, so done writing to the stream.
      streamer->WritesDone();
      break;
    }
    // Wait a second before writing the next chunk.
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
#endif
}
catch (std::exception const& ex) {
  std::cerr << "Standard C++ exception thrown: " << ex.what() << "\n";
  //return 1;
}

}

void GSession::on_read(std::string &callId)
{
	printf("\n Read connection %s \n", callId.c_str());
try{

#if 1
StreamingRecognizeResponse response;
while (streamer->Read(&response)) {  // Returns false when no more to read.
    // Dump the transcript of all the results.
    int k = response.results_size();
    printf("\n %d \n", k);
    for (int r = 0; r < response.results_size(); ++r) {
      const auto& result = response.results(r);
      std::cout << "Result stability: " << result.stability() << std::endl;
      int l = result.alternatives_size();
      printf("\n\n %d \n\n", l);
      for (int a = 0; a < result.alternatives_size(); ++a) {
        const auto& alternative = result.alternatives(a);
        std::cout << alternative.confidence() << "\t"
                  << alternative.transcript() << std::endl;
      }
    }
  //  std::cout<<response.DebugString()<<std::endl;
#endif
  }

on_close(callId);
}
catch (std::exception const& ex) {
  std::cerr << "Standard C++ exception thrown: " << ex.what() << "\n";
  //return 1;
}
}

void GSession::on_close(std::string &callId)
{
try{
	auto status = streamer->Finish();
	if (!status.ok()) throw status;
	printf("\nclosed connection %s \n", callId.c_str());
}
 catch (std::exception const& ex) {
  std::cerr << "Standard C++ exception thrown: " << ex.what() << "\n";
  //return 1;
}
}

