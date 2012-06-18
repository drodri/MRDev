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
		LaserData data;
		robot.getData(data);
		cout<<"MEdidas: "<<data.getRanges().size()<<endl;
		if(data.getRanges().size()>0)
			cout<<"Medida: "<<data.getRanges()[data.getRanges().size()/2]<<endl;
	}	

	server.close();
	LOG_INFO("End of server");
	return 1;
}
