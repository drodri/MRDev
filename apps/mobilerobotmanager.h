#pragma once

#include "mrcore/mrcore.h"

#include <iostream>
#include <vector>
#include "localizer.h"
#include "controlmanager.h"

using namespace mr;
using namespace std;

class MobileRobotManager
{
public:
	MobileRobot* robot;
	MobileRobot* robotViz;
	Localizer localizer;
	ControlManager control;
	Path3D groundTraj;

	MobileRobotManager(){
		robot=0;
		robotViz=0;
		groundTraj.setColor(0,255,0);
	}
	virtual ~MobileRobotManager(){
		delete robot;
		delete robotViz;
	}

	Transformation3D getRobotPose(){return localizer.getEstimatedPose();}
	void drawGL(){
		groundTraj.drawGL();
		localizer.drawGL();
		if(robotViz){
			robotViz->drawGL();
		}
	}
	void keyDown(unsigned char key)
	{
		control.keyDown(key);
	}
	void processAll();
	bool step();		
	void controlStep();
	bool loadConfig(string filename);
	float getError();
	Pose3D realPose;
};
