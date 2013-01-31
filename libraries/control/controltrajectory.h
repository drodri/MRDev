
#pragma once

#include "mrcore/mrcore.h"

#include <iostream>
#include <vector>


using namespace mr;
using namespace std;

class ControlTrajectory
{
public:
	ControlTrajectory();
	virtual bool getSpeed(float& forward,float& turn);
	void setPoseData(Pose3D& pose);
	void setNextGoal(int next);
	void setErrors(float degrees=10, float meters=0.1);
	void drawGL(void);
	void addPoint(Vector2D newPoint);
	bool getBlockReplanner(void){return blockReplanner;}
	

protected:
	bool computeSpeed();
	inline void changeRange(double& angle);

private:
	float speed,rot;
	Pose3D pose;
	Path3D path;
	int nextGoal;
	float maxAngleError, maxDistanceError;
	bool blockReplanner;
};
