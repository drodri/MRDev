#pragma once

#include "mrcore/mrcore.h"

#include <iostream>
#include <vector>


using namespace mr;
using namespace std;

class ControlTrajectory
{
public:
	virtual void getSpeed(float& forward,float& turn){};

	

private:
	
};
