#include "controltrajectory.h"
#include <float.h>

//Constructor
ControlTrajectory::ControlTrajectory()
{
	this->setErrors();
	nextGoal=0;
	speed=0;
	rot=0;
	path.setColor(153,0,204);
	
}
bool ControlTrajectory::getSpeed(float& forward,float& turn)
{
	bool automatic=computeSpeed();
	forward=speed;
	turn=rot;
	return automatic;
}
//Copy pose to ControlTrajectory
void ControlTrajectory::setPoseData(Pose3D& pose)
{
	this->pose=pose;
}
//Calculates the speed/rot
bool ControlTrajectory::computeSpeed()
{
	//Get orientation
	double roll,pitch,yaw;
	pose.orientation.getRPY(roll,pitch,yaw);
	Vector2D error=Vector2D(path[nextGoal].x,path[nextGoal].y)-Vector2D(pose.position.x,pose.position.y);
	double wantedAng=error.argument();
	double diffAng=Angle::difference(yaw,wantedAng);
	changeRange(diffAng);
	if(error.module()<maxDistanceError)	//near final point
	{
		blockReplanner=false;
		speed=0.0;
		rot=0.0;
		++nextGoal;
		if(nextGoal>=path.size())	//final point
			return false;
		else
			return this->computeSpeed();
	}
	if (abs(diffAng)>=maxAngleError)	// too much orientation error
	{
		blockReplanner=true;
		speed=0.0;
		if(diffAng>=0)
			rot=-0.3;
		else if(diffAng<0)
			rot=0.3;
	}
	else
	{
		blockReplanner=false;
		rot=-1.1*diffAng;
		speed=0.5;	//too much distance error
		speed*=0.5;
	}
	return true;
}
void ControlTrajectory::setNextGoal(int next)
{
	this->nextGoal=next;
}
void ControlTrajectory::drawGL()
{
	path.drawGL();
	pose.drawGL();
}
void ControlTrajectory::setErrors(float degrees, float meters)
{
	maxAngleError=degrees*DEG2RAD;
	maxDistanceError=meters;
}
//Changes from [0,2*PI] to [-PI,PI]
void ControlTrajectory::changeRange(double &angle)
{
	if(angle>PI)
		angle-=2*PI;
}
//Add new point to the path (the next point)
void ControlTrajectory::addPoint(Vector2D newPoint)
{
	vector<Vector3D> copy(path.size());
	for(int i=0;i<copy.size();i++)
		copy[i]=path[i];
	copy.insert(copy.begin()+nextGoal,Vector3D(newPoint.x,newPoint.y));
	path=Path3D(copy);
	path.setColor(153,0,204);
}
