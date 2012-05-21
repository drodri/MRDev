#include "mrcore.h"

#include <string>
#include <stdlib.h>
#include "speak_lib.h"

using namespace std;

class eSpeak : public VoiceTTS
{
public:
	eSpeak()
	{
		espeak_Initialize(AUDIO_OUTPUT_PLAYBACK, 0, NULL,0);
		setVoices(2,30);
		lang("spanish");
		espeak_SetParameter(espeakRATE, 210, 0);
		espeak_SetParameter(espeakVOLUME, 100, 0);
		espeak_SetParameter(espeakPITCH, 100, 0);
		espeak_SetParameter( espeakRANGE, 1, 0);
		espeak_SetParameter( espeakWORDGAP, 1, 0);	
		espeak_SetParameter(  espeakPUNCTUATION, 0, 0);	
	}
	~eSpeak()
	{
		espeak_Terminate();
	}
	void lang(const char *lang)
	{
		espeak_SetVoiceByName(lang);
	}

	bool say(const string& wor)
	{
		if(wor.length()==0)return false;
		string word=wor+'\0';
		//cout<<"Saying: "<<word.c_str()<<" l="<<word.length()<<endl;
		espeak_Synth((char*)word.c_str(), word.length(), 0, POS_CHARACTER, 0, espeakCHARS_AUTO |espeakENDPAUSE, NULL, NULL);
		//espeak_Synchronize();
		return true;
	}

	void setVoices(unsigned char gender,unsigned char age)
	{
		espeak_VOICE *voice_spec=espeak_GetCurrentVoice();
		voice_spec->gender=gender;
		voice_spec->age = age;
		espeak_SetVoiceByProperties(voice_spec);
	}
};




int main(int argc, char** argv)
{
	eSpeak e;
	VoiceTTSServer server(&e);
	server.init(12000,1,false);
	server.close();
	LOG_INFO("End of server");
	return 1;
}
