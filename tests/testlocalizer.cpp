#include "mrcore/mrcore.h"

#include "localizer.h"
#include <iostream>
#include "glutapp.h"

using namespace mr;
using namespace std;

class MyGlutApp: public GlutApp
{
public:
	MyGlutApp(string name):GlutApp(name),localizer(100)
	{
		robot=new Neo();
		robot->connectClients("127.0.0.1",15000);	
	//	if(!datalog.open("log/localizer"))
	//		LOG_ERROR("Unable to open log");
	//	else
	//		robot->startLogging("log/localizer");
	//	robot->connectLog("log/localizer");
	//	world+=robot;
	//	scene.addObject(&world);
		scene.SetViewPoint(35,160,25);	
		va=vg=0;

		localizer.loadMap("data/squaredRingNoWalls.world");
	//	localizer.loadMap("data/squaredRoom.world");
		Pose3D initPose(-2.4, -7, 0);
	// localizer.loadMap("data/controlTest.world");
	//	Pose3D initPose(2.4,8,0);
	//	Pose3D initPose(-7,-5,0);
		robot->setLocation(initPose);
		localizer.initializeGaussian(initPose,0.2);
	}
	void Draw(void)
	{
		scene.Draw();
		localizer.drawGL();

	}
	void Timer(float time)
	{
		Odometry odom;
		LaserData laserData;

		if(robot->getOdometry(odom))
		{
			Pose3D real;
			robot->getPose3D(real);
			static Pose3D last=odom.pose;
			static Odometry odomNoise=odom;
			Pose3D inc=last.inverted()*odom.pose;
			last=odom.pose;
			double r,p,y;
			inc.orientation.getRPY(r,p,y);
			double noise=0.01;
			double m=inc.module();
			Pose3D noisePose(m*sampleGaussian(0,noise),m*sampleGaussian(0,noise),0,
							 0,0,m*sampleGaussian(0,noise));

			/*if(rand()%100==0)
			noisePose=Pose3D (0,0.5,0,
							  0,0,0);*/

			
			odomNoise.pose*=inc;
			odomNoise.pose*=noisePose;
			localizer.move(odomNoise,noise*10,&real);
		}
	
		if(robot->getLaserData(laserData))
			localizer.observe(laserData);
		
		float va2=va,vg2=vg;
		robot->move(va2,vg2);

		//Pose3D realPose=localizer.getEstimatedPose();
	//	cout<<"RealPose: "<<realPose<<endl;
		//robot->setLocation(realPose);
	}
	void Key(unsigned char key)
	{
		/*if(key=='l')
		{
			LaserData laserData;
			if(robot->getLaserData(laserData))
				localizer.observe(laserData);
		}
		if(key=='p')
		{
			static Pose3D last=Pose3D(5,6,0);
			Pose3D inc(0.1,0,0);
			last*=inc;
			
			double noise=0.01;
			Pose3D noisePose(sampleGaussian(0,noise),sampleGaussian(0,noise),0,
							 0,0,sampleGaussian(0,noise));
			
			Odometry noiseOdom;;
			noiseOdom.pose=;
			localizer.move(noiseOdom,0.1,&odom);
			return;
		}*/
		
		if(key=='a')
			vg+=0.05;
		else if(key=='d')
			vg-=0.05;
		else if(key=='s')
			va-=0.05;
		else if(key=='w')
			va+=0.05;
		else 
		{
			va=vg=0;
		}
		scene.KeyDown(key);
	}
	void MouseMove(int x,int y)
	{
		scene.MouseMove(x,y);
		glutPostRedisplay();
	}
	void MouseClick(int b,int state, int x,int y)
	{
		bool down=(state==GLUT_DOWN);
		int button;
		if(b==GLUT_LEFT_BUTTON)
			button=MOUSE_LEFT_BUTTON;
		if(b==GLUT_RIGHT_BUTTON)
			button=MOUSE_RIGHT_BUTTON;
			
		int specialKey = glutGetModifiers();
		bool ctrlKey= (specialKey & GLUT_ACTIVE_CTRL)?true:false ;
		bool sKey= specialKey&GLUT_ACTIVE_SHIFT ;
		
		scene.MouseButton(x,y,b,down,sKey,ctrlKey);
		glutPostRedisplay();
	}
private:
	float vg,va;
	GLScene scene;
	World world;
	MobileRobot* robot;
	Localizer localizer;
	DataLogOut datalog;
};

void printUsage();

int main(int argc,char* argv[])
{
	mrcoreInit();
//	Logger::SetFileStream("logLocalizer.txt");
	MyGlutApp myApp("localizer");
	myApp.Run();
	return 0;   
}

