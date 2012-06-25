#pragma once

#include "mrcore/mrcore.h"

#include <iostream>
#include <vector>
#include "particle.h"
#include "gaussian.h"

using namespace mr;
using namespace std;

class LocalizerManager
{
public:
	MobileRobot* robot;
	Localizer localizer;
	bool uselaser;

	LocalizerManager(){
		robot=0;
		uselaser=true;
	}
	virtual ~LocalizerManager(){
		delete robot;
	}

	void drawGL(){
		localizer.drawGL();
	}
	void processAll(){
		int cont=0;
		float e,sumE=0,maxE=0;
		MRTime t;
		t.tic();
		while(step(e)){
			sumE+=e;
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
	bool step(float& error)
	{
		Odometry odom;
		LaserData laserData;
		
		Pose3D real;
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
			double noise=0.05;
			double m=inc.module();
			Pose3D noisePose(m*sampleGaussian(0,noise),m*sampleGaussian(0,noise),0,
							 0,0,m*sampleGaussian(0,noise));

			/*if(rand()%100==0)
			noisePose=Pose3D (0,0.5,0,
							  0,0,0);*/
		
			odomNoise.pose*=inc; //odometry pose + inc?
		//	odomNoise.pose*=noisePose;
			localizer.move(odomNoise,noise*1,&real);
		}
		else 
		{
		//	cout << "No odometry data" << endl;
			return false;
		}
	
		if(robot->getLaserData(laserData))
		{
			if(uselaser)
				localizer.observe(laserData);
		}
		else
		{
		//	cout<<"No laser data"<<endl;
			return false;
		}
		localizer.checkResample();
//		localizer.printInfo();

	
		//Pose3D realPose=localizer.getEstimatedPose();
		Pose3D correctedPose=localizer.getEstimatedPose();
		Pose3D realPose = real;
		
		/*log_errors << sqrt((realPose.position.x-real.position.x)*(realPose.position.x-real.position.x)+
						       (realPose.position.y-real.position.y )*(realPose.position.y-real.position.y)+  
						       (realPose.position.z-real.position.z )*(realPose.position.z-real.position.z))<< endl;*/
						       
		Pose3D rel = real.inverted()*correctedPose;
		double dis = rel.module();
		//cout << "dis 3d " << dis << endl;				       
						       
		//log_errors << dis << endl;
		error=dis;
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
				Transformation3D giro(0,0,0,0,0,-PI/2);
				//initPose*=giro;
				localizer.initializeGaussian(initPose,0.001);
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
				else if(robotName=="nemo")
					robot=new Nemo();
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
			else if(command=="uselaser:")
			{
				string uselas;
				buffer>>uselas;
				if(uselas=="yes")
					uselaser=true;
				else 
					uselaser=false;
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
};
