#include "SPclass.h"
#include<sstream>

std::string CreateUniqueCallid();
int main()
{
//for(int i =0;i<5;i++)
{

#if 0
for(int i =0; i<5; i++)
{
	Session SP;
	std::string callId = CreateUniqueCallid();

	SP.Initialise(callId);
	sleep(1);
}
#endif
//i++;
	Session SP;
	std::string callId = CreateUniqueCallid();
	SP.file_path = "/home/wave_sample/thank_you_" + std::to_string(i) + ".wav";
		SP.Initialise(callId);
        	SP.on_start(callId);
#if 1		
        	std::thread t1(std::bind(&Session::on_write, &SP, callId));
		std::thread t2(std::bind(&Session::on_read, &SP, callId));
		t1.detach();
		t2.detach();
		sleep(2);
#endif

//sleep(2);
}

//while(1);
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



