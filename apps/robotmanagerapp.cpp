#include "mrcore/mrcore.h"

#include "mobilerobotmanager.h"
#include <iostream>
#include "mrcoreglutapp.h"
#include "time.h"

using namespace mr;
using namespace std;

class RobotManagerApp: public MRCoreGlutApp
{
public:
	RobotManagerApp(string name,MobileRobotManager& m):MRCoreGlutApp(name), manager(m)
	{	
		useTimer=true;
		numRobot=-1;
	}
	virtual ~RobotManagerApp()
	{	
	}
	void Draw(void)
	{	
		if(numRobot==0)
		{
			Transformation3D t=manager.getRobotPose();

			scene.SetViewCenter(t.position.x,t.position.y,t.position.z);
			double dist,alfa,beta;
			scene.GetViewPoint(dist,alfa,beta);
			double r,p,y;
			t.orientation.getRPY(r,p,y);
			scene.SetViewPoint(dist,y*RAD2DEG+180,beta);
		}
	
		MRCoreGlutApp::Draw();
		manager.drawGL();
	}	     					
	void Timer(float time)
	{
		if(useTimer){
			manager.step();
			manager.controlStep();
		}
	}
	void Key(unsigned char key)
	{
		if(key=='m')
			useTimer=!useTimer;
		if(key=='p')
			manager.processAll();
		if(key=='o')
			SetTimer(0.0001);
	
		if(key=='+' && numRobot<0)
			numRobot++;
		if(key=='-' && numRobot>-1)
			numRobot--;
		manager.keyDown(key);

		MRCoreGlutApp::Key(key);
	}
	
private:
	bool useTimer;
	int numRobot;
	MobileRobotManager& manager;
};

void printUsage();

int main(int argc,char* argv[])
{
	mrcoreInit();
	srand(time(0));

	if(argc<2)
	{
		LOG_ERROR("Please introduce config file");
		return -1;
	}
	string fileConfig(argv[1]);
	MobileRobotManager manager;
	if(!manager.loadConfig(fileConfig))
	{
		LOG_ERROR("Error load config file");
		return -1;
	}

	RobotManagerApp myApp("RobApp 1.0",manager);	
	myApp.Run();
	return 0;   
}

