#include "mrcore.h"

int main()
{
	VoiceTTSClient client;
	client.connect("127.0.0.1",12000);
	
	while(1)
	{
		
		char buffer[512];
		cin.getline(buffer,512);
		string text(buffer);
		if(!client.say(text))
			break;
	}
	client.close();
}
