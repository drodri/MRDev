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
		world+=robot;
		scene.addObject(&world);
		scene.SetViewPoint(35,160,25);	
		va=vg=0;

		localizer.loadMap("data/rampas.world");
		Pose3D initPose(2.4,7,0);
		robot->setLocation(initPose);
		localizer.initializeGaussian(initPose,0.05);
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

		robot->getOdometry(odom);
		localizer.move(odom,0.00);
	
		robot->getLaserData(laserData);
		localizer.observe(laserData);
		
		localizer.resample();
		float va2=va,vg2=vg;
		
		robot->move(va2,vg2);
		Pose3D realPose=localizer.getEstimatedPose();
	//	cout<<"RealPose: "<<realPose<<endl;
		robot->setLocation(realPose);
	}
	void Key(unsigned char key)
	{
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
};

void printUsage();

int main(int argc,char* argv[])
{
	mrcoreInit();
	MyGlutApp myApp("localizer");
	myApp.Run();
	return 0;   
}

