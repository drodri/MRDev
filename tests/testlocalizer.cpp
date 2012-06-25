#include "mrcore/mrcore.h"

#include "localizer.h"
#include "localizermanager.h"
#include <iostream>
#include "glutapp.h"
#include "time.h"

using namespace mr;
using namespace std;

class MyLocalizerApp: public GlutApp
{
public:
	MyLocalizerApp(string name,LocalizerManager& m):GlutApp(name), manager(m)
	{
		scene.SetViewPoint(35,160,25);	
		va=vg=0;
		useTimer=false;
	}
	virtual ~MyLocalizerApp()
	{
		
	}
	
	void Reshape(int w,int h)
	{
		scene.setViewSize(0,0,w,h);
	}
	void Draw(void)
	{
		scene.Draw();
		manager.drawGL();
	}
		     					
	void Timer(float time)
	{
		if(useTimer){
			float e;
			manager.step(e);
		}
		float va2=va,vg2=vg;
		manager.robot->move(va2,vg2);

	//	cout<<"RealPose: "<<realPose<<endl;
	//	robot->setLocation(correctedPose);
	}
	void Key(unsigned char key)
	{
		if(key=='m')
			useTimer=!useTimer;
		if(key=='p')
			manager.processAll();
		if(key=='o')
			SetTimer(0.0001);
	
		
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
	bool useTimer;
	LocalizerManager& manager;
};

void printUsage();

int main(int argc,char* argv[])
{
	mrcoreInit();
	srand(time(0));
//	Logger::SetFileStream("logLocalizer.txt");
	
	if(argc<2)
	{
		LOG_ERROR("Please introduce config file");
		return -1;
	}
	string fileConfig(argv[1]);
	LocalizerManager manager;
	if(!manager.loadConfig(fileConfig))
	{
		LOG_ERROR("Error load config file");
		return -1;
	}

	MyLocalizerApp myApp("localizer",manager);	
	myApp.Run();
	return 0;   
}

