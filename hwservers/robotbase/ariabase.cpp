#include <iostream>
#include <algorithm>
#include <map>
#include "mrcore/mrcore.h"
#include "ariabase.h"
using namespace std;
namespace mr
{
AriaBase::AriaBase(int argc, char** argv)
{
	Aria::init();
	
	laser=0;
	argParser=new ArArgumentParser (&argc,argv);
	argParser->loadDefaultArguments( );
	robotConnector=new ArRobotConnector(argParser, &robot);
	laserConnector=new ArLaserConnector(argParser, &robot, robotConnector); 
//	argParser->addDefaultArgument( "-connectLaser" );

	if (!robotConnector->connectRobot())
	{
		if (!argParser->checkHelpAndWarnUnparsed())
		{
			ArLog::log(ArLog::Terse, "Could not connect to robot, no param file so options displayed later may not include everything");
		}
		else// otherwise abort
		{
			ArLog::log(ArLog::Terse, "Error, could not connect to robot.");
			Aria::logOptions();
			Aria::exit(1);
		}
	}
	// Do this after connecting to the robot:
	if ( !Aria::parseArgs( ) || !argParser->checkHelpAndWarnUnparsed( ) )
	{
		Aria::logOptions( );
		Aria::exit( 1 );
	}

 	string robotT(robot.getRobotSubType());
	if(robotT=="patrolbot-sh")
		robotType=PATROLBOT;
	else 
		robotType=PIONEER;
	//laserConnector->logOptions();
	if(!laserConnector->connectLasers(false, true, true))
	{
		ArLog::log(ArLog::Normal, "Warning: unable to connect to requested lasers.");
	}


	map< int, ArLaser * >*  myMap= robot.getLaserMap();
	map<int, ArLaser*>::iterator it;
	cout<<"SIze: "<<myMap->size()<<endl;
	for(	it= myMap->begin();it!=myMap->end();it++)
	{
		cout<<"Laser: "<<(*it).first<<" laser: "<<endl;
	}
	
 	robot.runAsync(true);

	laser=robot.findLaser(1);
	if(laser==0)
	{
		cout<<"Unable to find laser"<<endl;
		robot.stop();
		delete laser;
		delete robotConnector;
		delete laserConnector;
		delete argParser;
 		Aria::shutdown();

		exit(1);
	}
	laser->blockingConnect();
 //	robot.runAsync(true);	
	
	robot.comInt(ArCommands::ENABLE, 1);
	robot.comInt(ArCommands::SONAR, 0);
	moveCount=0;
}


AriaBase::~AriaBase()
{
	robot.stop();
	delete laser;
	delete robotConnector;
	delete laserConnector;
	delete argParser;
 	Aria::shutdown();
}
bool AriaBase::getOdometry(Odometry& pose)
{
	MRTime tim;
	tim.tic();
	usleep(10000);
	robot.lock();
	ArPose p=robot.getPose();
	pose.pose=Transformation3D(p.getX()/1000.0,p.getY()/1000.0,0,0,0,p.getThRad());
	robot.unlock();
	int  elap=tim.toc();
	if(elap>150)
		cout<<"Warning more than 150ms to get odom "<<elap<<endl;
	return true;
}
bool AriaBase::move(double speed, double rot)
{
	MRTime tim;
	tim.tic();
	robot.lock();
	robot.setVel(speed*1000);
	robot.setRotVel(rot*RAD2DEG);
	robot.unlock();
	moveCount++;
	int elap=tim.toc();
	if(elap>150)
		cout<<"Move elap time: "<<elap<<endl;
	return true;
}
bool AriaBase::getData(LaserData& laserData)
{
	if(!laser)return false;
	 if(!laser->isConnected())
	 {
		 cout<<"laser not connected"<<endl;
		
		 return false;
	 }
	 
	laser->lockDevice();
	 
	// vector< ArPoseWithTime >*  v=sickLaser.getCurrentBufferAsVector ();ONly returns 40 measur
	 
	vector<ArSensorReading>* v2=laser->getRawReadingsAsVector();
	double startDeg=laser->getStartDegrees();
	double incDeg=laser->getIncrement();
	if(robotType==PATROLBOT)
		laserData.setProperties(-90*DEG2RAD, 1*DEG2RAD, v2->size());
	else //Pionner with LMS100
		laserData.setProperties(-135*DEG2RAD,0.5*DEG2RAD,v2->size());
	vector<double> ranges;
	for(int i=0;i<v2->size();i++)
	{
		ArSensorReading aux=(*v2)[i];
		double value=aux.getRange();
		value/=1000;
		ranges.push_back(value);
	}
	reverse(ranges.begin(),ranges.end());
	if(robotType==PATROLBOT)//Interpolation of blind readings from patrolbot
	{
		ranges[15]=(ranges[14]+ranges[16])/2.0;
		ranges[165]=(ranges[164]+ranges[166])/2.0;
	}
	laserData.setRanges(ranges);
  	laser->unlockDevice();	
//	delete v;
	return true;
}
void AriaBase::watchdog()
{
	if(moveCount==0)
	{
	//	cout<<"Wathcdog"<<endl;
		robot.lock();
		robot.stop();
		robot.unlock();
	}
	moveCount=0;
}

}; //Namespace mr
