#pragma once

#include "mrcore/mrcore.h"

#include <iostream>
#include <vector>
#include "controltrajectory.h"
#include "controlreactive.h"

using namespace mr;
using namespace std;

class ControlManager
{
public:
	ControlManager();
	void getSpeed(float& forward,float& turn);
	void keyDown(unsigned char key);


private:
	float speed,rot;
	float maxSpeed,maxRot;
	bool manualControl;
	ControlTrajectory	trajFollow;
	ControlReactive		reactive;

};
