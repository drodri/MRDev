#include "mobilerobotmanager.h"

#include <iostream>
#include <vector>
#include "controlmanager.h"

using namespace mr;
using namespace std;

void MobileRobotManager::processAll(){
	int cont=0;
	float e,sumE=0,maxE=0;
	MRTime t;
	t.tic();
	while(step()){
		sumE+=getError();
		if(maxE<e)
			maxE=e;
		cont++;
		if(cont%100==0)
			LOG_INFO("Iter: "<<cont);
	}
	long elpTime=t.toc();
	LOG_INFO("Steps: "<<cont<<" AvgError: "<<sumE/cont<<" MaxError:"<<maxE);
	LOG_INFO("Time:"<<elpTime/1000<<" AvgTime: "<<elpTime/cont);
	localizer.printParams();
}
bool MobileRobotManager::step()
{
	Odometry odom;
	LaserData laserData;
	
	if(robot->getOdometry(odom)){	
		robot->getPose3D(realPose);
		groundTraj.push_back(realPose.position);
		
		static Odometry lastOdom=odom;
		double noise=0.05;
		Pose3D inc=odom.getIncrement(lastOdom,noise);
		lastOdom=odom;
		localizer.move(inc,noise*1);
	}
	else 
	{
	//	cout << "No odometry data" << endl;
		return false;
	}

	if(robot->getLaserData(laserData)){
		localizer.observe(laserData);
	}
	else
	{
	//	cout<<"No laser data"<<endl;
		return false;
	}
	localizer.resample();
	robotViz->setAbsoluteT3D(localizer.getEstimatedPose());
}			
float MobileRobotManager::getError()
{
	//Pose3D realPose=localizer.getEstimatedPose();
	Pose3D correctedPose=robotViz->getAbsoluteT3D();			       
	Pose3D rel = realPose.inverted()*correctedPose;
	double dis = rel.module();
	return dis;	
}
void MobileRobotManager::controlStep()
{
	float va=0,vg=0;
	control.getSpeed(va,vg);
	robot->move(va,vg);
}
bool MobileRobotManager::loadConfig(string filename)
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
		if(command=="localizer")
		{
			localizer.loadConfig(file);
		}
		else if(command=="world:")
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
			float x,y,z,yaw;
			buffer>>x>>y>>z>>yaw;
			Pose3D initPose(x,y,z);
			Transformation3D giro(0,0,0,0,0,yaw);
			initPose*=giro;
			localizer.setInitPoseGaussian(initPose,0.001);
			robot->setLocation(initPose);
		}
		else if(command=="robot:")
		{
			string robotName;
			buffer>>robotName;
			if(robotName=="neo"){
				robot=new Neo();
				robotViz=new Neo();
			}
			else if(robotName=="doris"){
				robot=new Doris();
				robotViz=new Doris();
			}
			else if(robotName=="nemo"){
				robotViz=new Nemo();
				robot=new Nemo();
			}
			else
			{
				LOG_ERROR("Robot not defined: "<<robotName);
				return false;
			}
			
//				world+=robot;
		}
		else if(command=="connect:")
		{
			string typ;
			buffer>>typ;
			if(typ=="tcp")
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
			}
			else
			{
				LOG_ERROR("Robot connection not defined: "<<typ);
				return false;
			}
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
