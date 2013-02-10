#include "mrcore/mrcore.h"
#include <iostream>
#include "mrcoreglutapp.h"

using namespace mr;
using namespace std;

class SimulatorApp: public MRCoreGlutApp
{
public:
	SimulatorApp(string name,Simulator& s):MRCoreGlutApp(name),simulator(s)
	{
		scene.addObject(simulator.getWorld());
		scene.SetViewPoint(35,160,25);	
		numRobot=-1;
	}
	void Draw(void)
	{
		Transformation3D t;
		if(numRobot>=0 && numRobot<simulator.numRobots())
		{
			simulator.getRobot(numRobot)->getPose3D(t);

			scene.SetViewCenter(t.position.x,t.position.y,t.position.z);
			double dist,alfa,beta;
			scene.GetViewPoint(dist,alfa,beta);
			double r,p,y;
			t.orientation.getRPY(r,p,y);
			scene.SetViewPoint(dist,y*RAD2DEG+180,beta);
		}
	
		MRCoreGlutApp::Draw();
	}
	void Timer(float time)
	{
		simulator.getWorld()->simulate(0.020);
	}	
	void Key(unsigned char key)
	{
		if(key=='+' && numRobot<simulator.numRobots()-1)
			numRobot++;
		if(key=='-' && numRobot>-1)
			numRobot--;

		MRCoreGlutApp::Key(key);
	}
private:
	Simulator simulator;	
	int numRobot;
};

void printUsage();
int main(int argc,char* argv[])
{
	mrcoreInit();

	string file;
	if(argc==2)
		file=string(argv[1]);
	else
	{
		cout<<"You have not specified a configuration file as command line parameter"<<endl;
		cout<<"Please type configuration file: ";
		string file;
		cin>>file;
	}
	cout<<"Loading configuration file: "<<file<<endl;

	Simulator sim;
	sim.load(file);

	SimulatorApp myApp("MR Simulator",sim);
	myApp.Run();
	return 0;   
}

void printUsage()
{
	cout<<"-------- Usage -----------------"<<endl;
	cout<<"> simulator config.txt    "<<endl;
	cout<<"example:    "<<endl;
	cout<<"> simulator configuration.conf    "<<endl;
}
/*
class Simulator
{
public:
	Simulator()
	{
		initWorld();
		
		robots.push_back(new Neo);
		MobileRobot& neo=*robots[0];
	
		neo.setLocation(Transformation3D(0,-8,0));
		world+=neo.getBase();
		neo.startServers(13000);

	//	robots.push_back(new Doris);
	//	robots.push_back(new Nemo);
	//	robots.push_back(new Neo);

	//	MobileRobot& doris=*robots[0];
	//	MobileRobot& nemo=*robots[1];
	//	MobileRobot& neo=*robots[2];

	//	doris.setLocation(Transformation3D(7,7,0));
	//	world+=doris.getBase();//doris.addToWorld(world);
	//	doris.startServers(12000);

	//	neo.setLocation(Transformation3D(4,1,2));
	//	world+=neo.getBase();
	//	neo.startServers(13000);

	//	nemo.setLocation(Transformation3D(2,3,0,0,0,-M_PI));
	//	world+=nemo.getBase();
	//	nemo.startServers(14000);

	//	quadrotor=new QuadrotorRobot("ardrone");
	//	quadrotor->startServers(15000);
	//	world+=quadrotor->getBase();
	//	quadrotor->setLocation(Transformation3D(5,5, 5));

	//	doris.move(1,1);

		kinect=new KinectSim;
		kinect->setAbsoluteT3D(Transformation3D(2,2,2));
		world+=kinect;
		kinectserver=new KinectServer(kinect,"MyKinect");
		kinectserver->init(20000);
	}
	~Simulator()
	{
		LOG_WARNING("Exiting simulator");
		for(unsigned int i=0;i<robots.size();i++)
			delete robots[i]; 
		delete quadrotor;
		world.destroyContent();
	}


	void initWorld();

	World world;
	vector<MobileRobot* > robots;
	QuadrotorRobot* quadrotor;
	KinectSim* kinect;
	KinectServer* kinectserver;
};


void OnKeyboardDown(unsigned char key, int x, int y)
{
	if(key=='s')
	{
		scene.save("glSnapshot");
	//	scene.load("glSnapshot");
	}
//	m.Lock();
	scene.KeyDown(key);
//	m.Unlock();
	
	glutPostRedisplay();	

}

*/
