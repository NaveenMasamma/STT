#include "Stream.h"
#include<sstream>

std::string CreateUniqueCallid();

int main(int argc, char** argv)
{
int j = 0; 
for(j = 0;j<5;j++)
{
	std::string callId = CreateUniqueCallid();
	sleep(2);
	GSession *GSP = new GSession();
	
	GSP->file_path = "/root/radio_" + std::to_string(j+1) + ".wav";
	GSP->on_start(callId);
	std::thread t2(std::bind(&GSession::on_read, GSP, callId));
	std::thread t1(std::bind(&GSession::on_write, GSP, callId));
	t1.detach();
	t2.detach();
}
while(1);
}
std::string CreateUniqueCallid()
{
	std::string UniqueCallid = "";

	std::srand(static_cast<unsigned int>(std::time(NULL)));
	std::ostringstream t_uuid;
	t_uuid << std::rand();
	UniqueCallid = t_uuid.str();
	printf("CreateUniqueCallid(%s)",UniqueCallid.c_str());

	return UniqueCallid;
}
