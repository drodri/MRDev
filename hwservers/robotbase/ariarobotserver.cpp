#include "mrcore/mrcore.h"
#include "ariabase.h"

int main(int argc, char** argv)
{
	mrcoreInit();
	AriaBase robot(argc,argv);
	WheeledBaseServer server(&robot,"base");
	LaserSensorServer laserServer(&robot,"laser");
	
	server.init(13000,1,true);
	laserServer.init(13001,1,true); 
	while(1)
	{
		Sleep(500);
		robot.watchdog();
	//	LaserData data;
	//	robot.getData(data);
		//if(data.getRanges().size()>270)
		//cout<<"Medida: "<<data.getRanges()[270]<<endl;
	}	

	server.close();
	LOG_INFO("End of server");
	return 1;
}
