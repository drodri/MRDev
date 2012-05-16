#include "mrcore/mrcore.h"

#include "localizer.h"
#include <iostream>
#include "glutapp.h"
#include "time.h"

using namespace mr;
using namespace std;

std::ofstream log_errors("Errors.txt",std::ios::out);

class MyLocalizerApp: public GlutApp
{
public:
	MyLocalizerApp(string name):GlutApp(name),localizer(100)
	{
		robot=0;
		scene.addObject(&world);
		scene.SetViewPoint(35,160,25);	
		va=vg=0;
	}
	virtual ~MyLocalizerApp()
	{
		delete robot;
	}
	bool loadConfig(string filename)
	{	
		string fold=filename.substr(0,filename.find_last_of('/'));
		ifstream file(filename.c_str());
	
	
		while(1)
		{
			string line;
			getline(file,line);
			if(!file.good())
				break;
			if(line[0]=='#')
				continue;

			stringstream buffer(line);
			string command;
			buffer>>command;
			if(command=="world:")
			{
				string worldFile;
				buffer>>worldFile;
				string current=currentDirectory();
				changeDirectory(fold);
				localizer.loadMap(worldFile);
				changeDirectory(current);
			}
			else if(command=="initPose:")
			{
				float x,y,z;
				buffer>>x>>y>>z;
				Pose3D initPose(x,y,z);
				localizer.initializeGaussian(initPose,0.2);
				robot->setLocation(initPose);
			}
			else if(command=="robot:")
			{
				string robotName;
				buffer>>robotName;
				if(robotName=="neo")
					robot=new Neo();
				else if(robotName=="doris")
					robot=new Doris();
				else
				{
					LOG_ERROR("Robot not defined: "<<robotName);
					return false;
				}
				world+=robot;
			}
			else if(command=="connect:")
			{
				string typ;
				buffer>>typ;
				if(typ=="simulator")
				{
					string ip;int port;
					buffer>>ip>>port;
					LOG_INFO("Connect to remote robot: "<<ip<<":"<<port);
					robot->connectClients(ip,port);
				}
				else if(typ=="log")
				{
					string logFile;
					buffer>>logFile;
					LOG_INFO("Connect to datalog: "<<logFile);
					robot->connectLog(logFile);
					SetTimer(0.0001);
				}
				else
				{
					LOG_ERROR("Robot connection not defined: "<<typ);
					return false;
				}
			}
			else if(command=="numParticles:")
			{
				int num;
				buffer>>num;
				localizer=Localizer(num);
			}
			else if(command=="neff:")
			{
				float num;
				buffer>>num;
				localizer.setNeff(num);
			}
			else if(command=="log:")
			{
				string logFolder;
				buffer>>logFolder;
				if(logFolder!="")
					robot->startLogging(logFolder);
			}
		}
		file.close();
		
		return true;
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
		
		Pose3D real;
		while(1){
		if(robot->getOdometry(odom))
		{
			//Pose3D real;
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

			
			odomNoise.pose*=inc; //odometry pose + inc?
			odomNoise.pose*=noisePose;
			localizer.move(odomNoise,noise*1,&real);
		}
		else 
		{
			cout << "No odometry data" << endl;
			return;
		}
	
		if(robot->getLaserData(laserData))
		{
		//	localizer.observe(laserData);
		}
		else
		{
			cout<<"No laser data"<<endl;
			return;
		}
		localizer.checkResample();
//		localizer.printInfo();

		float va2=va,vg2=vg;
		robot->move(va2,vg2);

		//Pose3D realPose=localizer.getEstimatedPose();
		Pose3D correctedPose=localizer.getEstimatedPose();
		Pose3D realPose = real;
		
		/*log_errors << sqrt((realPose.position.x-real.position.x)*(realPose.position.x-real.position.x)+
						       (realPose.position.y-real.position.y )*(realPose.position.y-real.position.y)+  
						       (realPose.position.z-real.position.z )*(realPose.position.z-real.position.z))<< endl;*/
						       
		Pose3D rel = real.inverted()*correctedPose;
		double dis = rel.module();
		//cout << "dis 3d " << dis << endl;				       
						       
		log_errors << dis << endl;
						     
						
		
	//	cout<<"RealPose: "<<realPose<<endl;
		robot->setLocation(correctedPose);
		}
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
	MyLocalizerApp myApp("localizer");
	if(!myApp.loadConfig(fileConfig))
	{
		LOG_ERROR("Error load config file");
		return -1;
	}
	myApp.Run();
	return 0;   
}

