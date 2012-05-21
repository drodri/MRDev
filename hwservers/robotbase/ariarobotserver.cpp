#include "mrcore/mrcore.h"
#include "ariabase.h"

int main(int argc, char** argv)
{
	mrcoreInit();
	AriaBase robot(argc,argv);
	WheeledBaseServer server(&robot,"base");
	LaserSensorServer laserServer(&robot,"laser");
	
	server.init(12000,1,true);
	//laserServer.init(12001,1,true);
	while(1)
	{
		Sleep(500);
		robot.watchdog();
	}	

	server.close();
	LOG_INFO("End of server");
	return 1;
}
